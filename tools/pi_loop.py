#!/usr/bin/env python3
"""Serial, COW-cloned, headless-pi agent loop for FFCC-Decomp.

One job:
  1. refresh `base/` to origin/staging and build it (warm build dir for cheap clones)
  2. pick the next unit target from build/GCCP01/report.json (project selector rules)
  3. `cp -ac base clone-<unit>` (APFS clonefile: fast, block-shared) + fresh branch
  4. run one headless `pi -p` agent inside the clone (fresh context); `--workers`
     jobs are in flight at once, one clone each
  5. gate on report.json: unit fuzzy must improve and `ninja` must pass
  6. publish a fork branch + PR against `staging` only when the gate passes

Usage:
  python3 tools/pi_loop.py --dry-run            # show next target + prompt, do nothing
  python3 tools/pi_loop.py --iterations 3       # run 3 serial iterations
  python3 tools/pi_loop.py --unit main/mes --minutes 30 --no-push
"""

import argparse
import json
import re
import shlex
import shutil
import subprocess
import sys
import threading
import time
from concurrent.futures import ThreadPoolExecutor, as_completed
from pathlib import Path

REPO = Path(__file__).resolve().parent.parent
UPSTREAM = "zcanann/FFCC-Decomp"
FORK_OWNER = "frioux"
UNIT = "GCCP01"
REGIONS = ("GCCP01", "GCCE01", "GCCJGC")

# WORK_SPLIT.md "CONFIRMED DEAD-ENDS": exhausted by earlier campaigns.
DEAD_END_UNITS = {
    "main/bonus_menu",
    "main/wm_menu",
    "main/menu_cmd",
    "main/MenuUtil",
    "main/shopmenu",
    "main/singmenu",
}

MAX_ATTEMPTS = 3
PR_BODY_FILE = ".pi_loop_pr_body.md"
BASE_SHA_FILE = ".pi_loop_base_sha"
PR_SECTIONS = ("what changed", "evidence", "validation")

NUDGE = (
    "You are continuing the same FFCC-Decomp unit task. On your first turn you stopped after "
    "about {elapsed} min of a {minutes} min budget without a reliable gain. Do not re-derive "
    "what you already measured. Work the biggest untested lever you identified (your own "
    "'not checked' note, the next function on the unit's list, or the next entry in the "
    "WORK_SPLIT lever catalog), and run at least five more measured edit -> ninja -> "
    "report.json cycles before you consider stopping. Commit anything that improves the unit; "
    "keep the tree in its best-scoring plausible state."
)


def sh(cmd, cwd, timeout=None, check=False, log=None):
    """Run a command, tee its output to `log` when given, return CompletedProcess."""
    proc = subprocess.run(
        cmd,
        cwd=str(cwd),
        timeout=timeout,
        capture_output=True,
        text=True,
    )
    if log:
        with open(log, "a") as f:
            f.write(f"$ {' '.join(shlex.quote(c) for c in cmd)}\n")
            f.write(proc.stdout or "")
            f.write(proc.stderr or "")
            f.write(f"[exit {proc.returncode}]\n")
    if check and proc.returncode != 0:
        sys.stderr.write((proc.stdout or "")[-4000:] + (proc.stderr or "")[-4000:])
        raise SystemExit(f"command failed ({proc.returncode}): {' '.join(cmd)}")
    return proc


def git(cwd, *args, **kw):
    return sh(["git", *args], cwd, **kw)


# ---------------------------------------------------------------- base + clones


def configure_args(region=UNIT):
    """Reuse this machine's configure flags (e.g. --gba-compilers) from build.ninja."""
    try:
        text = (REPO / "build.ninja").read_text()
    except OSError:
        text = ""
    m = re.search(r"^configure_args = (.*)$", text, re.MULTILINE)
    args = m.group(1).split() if m else ["--version", UNIT]
    if "--version" in args:
        args[args.index("--version") + 1] = region
    else:
        args = ["--version", region, *args]
    return args


def configure(cwd, region, log):
    sh(["python3", "configure.py", *configure_args(region)], cwd, check=True, log=log)


def region_scores(cwd, region, log):
    """Build all configured source for a region, verify the DOL hash, return scores."""
    sh(["ninja", "all_source", "progress", f"build/{region}/report.json"],
       cwd, timeout=7200, check=True, log=log)
    ok = sh(["ninja", f"build/{region}/ok"], cwd, timeout=3600, log=log).returncode == 0
    scores = {name: fuzzy
              for name, (fuzzy, _, _) in report_units(load_report(cwd, region)).items()}
    return {"scores": scores, "ok": ok}


def refresh_base(work, log):
    base = work / "base"
    if not base.exists():
        sh(["cp", "-ac", str(REPO), str(base)], work, check=True, log=log)
    git(base, "fetch", "origin", "staging", "-q", log=log)
    git(base, "checkout", "-f", "-q", "--detach", "origin/staging", log=log)
    git(base, "clean", "-qfd", log=log)
    # A checkout bumps download_tool.py's mtime, which makes ninja re-download (and
    # fail offline) every toolchain binary we already have. Backdate it instead.
    sh(["touch", "-t", "202401010000", "tools/download_tool.py"], base, check=True, log=log)
    # Same flags as this machine's existing build, so a warm build dir stays warm.
    # Build all three regions once so a clone's per-region builds are incremental.
    for region in REGIONS:
        configure(base, region, log)
        region_scores(base, region, log)
    configure(base, UNIT, log)  # leave base PAL-configured for the clones
    ninja(base, log)
    return base


def make_clone(work, base, unit, branch, log):
    slug = unit.split("/")[-1]
    clone = work / f"{time.strftime('%m%d-%H%M%S')}-{slug}"
    sh(["cp", "-ac", str(base), str(clone)], work, check=True, log=log)
    git(clone, "switch", "-q", "-c", branch, log=log)
    return clone


def ninja(cwd, log, timeout=3600):
    return sh(["ninja"], cwd, timeout=timeout, check=True, log=log)


# ---------------------------------------------------------------------- targets


def load_report(clone, region=UNIT):
    with open(clone / f"build/{region}/report.json") as f:
        return json.load(f)


def report_units(report):
    """unit name -> (fuzzy, matched_code, total_code)."""
    out = {}
    for unit in report.get("units", []):
        m = unit.get("measures") or {}
        try:
            out[unit["name"]] = (
                float(m.get("fuzzy_match_percent") or 0.0),
                int(m.get("matched_code") or 0),
                int(m.get("total_code") or 0),
            )
        except (KeyError, TypeError, ValueError):
            continue
    return out


def open_pr_blob():
    proc = sh(
        ["gh", "pr", "list", "--repo", UPSTREAM, "--state", "open",
         "--json", "headRefName,title", "--limit", "100"],
        REPO,
    )
    if proc.returncode != 0:
        return ""
    try:
        prs = json.loads(proc.stdout)
    except json.JSONDecodeError:
        return ""
    return " ".join(f"{p.get('headRefName', '')} {p.get('title', '')}" for p in prs)


def candidates(base):
    """Viable targets per the project selector, minus units with no real source."""
    sys.path.insert(0, str(base / "tools"))
    try:
        import agent_select_target as ast
    finally:
        sys.path.pop(0)
    report_path = base / f"build/{UNIT}/report.json"
    words = {}
    for cand in ast.extract_candidates(report_path):
        src = cand.get("source_path") or ""
        if not src.startswith("src/"):
            continue  # gba/* binaries and other source-less units are out of scope
        words[cand["name"]] = cand
    return words


def pick_target(base, state, forced, blob, claimed=()):
    report = load_report(base)
    units = report_units(report)
    funcs = {unit["name"]: unit.get("functions", []) for unit in report.get("units", [])}
    cands = candidates(base)
    scored = []
    for name, cand in cands.items():
        fuzzy, matched, total = units.get(name, (0.0, 0, 0))
        if total == 0 or fuzzy >= 99.999:
            continue
        attempts = state["units"].get(name, {}).get("attempts", 0)
        best = state["units"].get(name, {}).get("best_delta", 0.0)
        if attempts >= MAX_ATTEMPTS or (attempts >= 2 and best <= 0):
            continue
        if name in claimed:
            continue  # another worker just took it
        stem = Path(cand["source_path"]).stem
        if blob and re.search(rf"\b{re.escape(stem)}\b", blob, re.IGNORECASE):
            continue  # an open PR already owns this unit
        cand = dict(cand)
        cand["worst_functions"] = worst_functions(funcs.get(name, []))
        # fresh units first, biggest unmatched code first, documented dead-ends last
        scored.append(((name in DEAD_END_UNITS, attempts > 0, -(total - matched)), cand))
    if forced:
        wanted = [c for _, c in scored if c["name"] in forced]
        if not wanted:
            raise SystemExit(f"forced unit(s) not selectable: {forced}")
        return wanted[0]
    if not scored:
        raise SystemExit("no selectable targets left")
    scored.sort(key=lambda item: item[0])
    return scored[0][1]


def worst_functions(functions, limit=6):
    """Unit functions with the most unmatched bytes, best guess at where to start."""
    rows = []
    for f in functions:
        fuzzy = float(f.get("fuzzy_match_percent") or 100.0)
        size = int(f.get("size") or 0)
        if fuzzy >= 99.99 or size == 0:
            continue
        rows.append((size * (100.0 - fuzzy) / 100.0, f["name"], fuzzy, size))
    rows.sort(reverse=True)
    return [f"{name} ({fuzzy:.1f}%, {size}b)" for _, name, fuzzy, size in rows[:limit]]


def prompt_for(cand, clone, branch, minutes):
    name = cand["name"]
    fuzzy = cand["fuzzy_match"]
    total = cand["total_code"]
    funcs = ", ".join(cand["worst_functions"]) or "none above 99%"
    return f"""Automated serial loop iteration: you are the only agent on this machine. Work alone; never ask questions, never wait for input.

REPO: {clone} (your cwd). BRANCH: {branch} (already checked out, based on origin/staging).
TARGET UNIT: {name} ({cand['source_path']}), {total} code bytes, currently {fuzzy:.2f}% fuzzy.
Biggest remaining functions: {funcs}
Wall-clock budget: about {minutes} minutes. Work the WHOLE budget: when one hypothesis dies, immediately start the next (another function from the list above, another lever from the catalog). Do not stop early to report progress; the only reasons to stop are the unit reaching 100% fuzzy or the budget running out.
Most residual diffs in this project are register-allocation/scheduling walls, so the winning moves are structural source recovery plus the WORK_SPLIT idiom catalog (tools/permute_fn.py, switch-case order, declaration/statement order sweeps). Work the diff, not the score.

GOAL: raise this unit's fuzzy_match_percent in build/GCCP01/report.json by recovering plausible original source.
Start by reading AGENTS.md, the lever catalog + CONFIRMED DEAD-ENDS in WORK_SPLIT.md, and docs/agent_playbook.md
(how to measure fast and which levers actually pay) - all in your cwd.

MEASURE FAST (this is what separates a landed delta from a wasted budget):
- One translation unit is `ninja build/GCCP01/src/<file>.o` (~1.5 s). Score it with
  `build/tools/objdiff-cli diff -p . -u {name} -o -` and read `.left.sections[] | select(.name==".text").match_percent`
  - that number equals the unit's report.json fuzzy. Only run a full `ninja` when you need the project report.
- Check the build's exit status before reading any score: a failed build leaves a stale/empty report.json.
- If a candidate produces a bit-identical object, the axis is dead for that function - move on, do not measure it.
- Automate sweeps (mutate -> build object -> score -> keep best); a script does 400 candidates in ~5 minutes.
- Classify the residual first: only register-number differences = allocation wall (live-range/value-form edits,
  not declaration order); extra/missing instructions = real source gap (fix that first); reordered independent
  statements = scheduling. `@NNN` vs named pool symbols at the same address is cosmetic and scores zero.
- Never switch region inside a measurement loop (it costs ~38 s and invalidates every edge).
The project report (`ninja` -> build/GCCP01/report.json) is the final gate. Per symbol:
  build/tools/objdiff-cli diff -p . -u {name} -o - <symbol> > /tmp/{Path(name).stem}-<symbol>.json

HARD RULES
- Commit locally on {branch} as you go. NEVER push, never create/delete/switch branches, never rebase or reset --hard, never touch origin refs.
- No hardcoded addresses, no fake lbl_/fn_ names, no manual vtables/RTTI/ctors/dtors, no per-unit compiler-flag overrides, no pragma tricks to buy score (see AGENTS.md Critical Rules).
- Keep changes unit-local. If a shared header/struct/symbol fix is genuinely required, keep it minimal and call it out in your summary.
- NO REGION MAY REGRESS. The unit's fuzzy score must be >= baseline in GCCP01, GCCE01 and GCCJGC, and no other unit may change score in any region. If a PAL/EN win costs Japan (or vice versa), keep searching for a variant that satisfies all three; if none exists, revert and say so.
- `ninja` must succeed before you stop (it produces build/GCCP01/ok and refreshes report.json).
- Revert experiments that do not pay off; leave the tree in its best-scoring plausible state.

FINISH by writing the pull-request body to `{PR_BODY_FILE}` in the repo root (untracked; never commit it). A maintainer reads this instead of the diff first, and it must be legible prose with measured numbers - no transcript, no thinking, no tool dumps. Exact shape:

# {name}: <one-line description of the source change> (<before> -> <after>)    [3 decimal places]

## What changed

Which file and function, what construct changed, why it now has this shape.

## Evidence

| | before | after |
|---|---:|---:|
| `<mangled or C++ function signature>` | 97.00284 | 98.09787 |
| unit `{name}` (GCCP01) | 98.73549 | 99.19749 |
| unit `{name}` (GCCE01) | 98.73549 | 99.19749 |
| unit `{name}` (GCCJGC) | 98.73322 | 99.19605 |

One row per function you improved (PAL), plus one row per region for the unit. Numbers from
`build/<version>/report.json`. Every region's unit row must show after >= before; a PR that
trades one region for another is rejected.

## Why this is plausible original source, not compiler coaxing

What the retail binary implies and why a developer would have written it this way.

## Validation

- For EACH of the three regions (GCCP01, GCCE01, GCCJGC): `python3 configure.py --version <v> --gba-compilers /nonexistent`, then `ninja all_source progress build/<v>/report.json` and `ninja build/<v>/ok`. State the result per region. The driver re-verifies this, so do not claim a region you did not build.
- Per region: the unit's score did not regress and nothing outside the unit changed score (both are hard requirements).
- The dead ends you measured and reverted, one line each.
- The GBA images: say whether they were checked (this machine needs a docker GBA toolchain, so usually they are not).

Then reply with at most 5 plain-text lines: unit before -> after, functions improved, and whether `{PR_BODY_FILE}` is written.
"""


# --------------------------------------------------------------------- measure


def unit_measure(clone, unit):
    fuzzy, _, _ = report_units(load_report(clone)).get(unit, (0.0, 0, 0))
    return fuzzy


def summarize(text, limit=4000, line_max=500):
    """Keep the agent's closing words, minus any giant one-line provider error dump."""
    lines = [line[:line_max] for line in text.strip().splitlines() if line.strip()]
    return "\n".join(lines)[-limit:]


def render_regions(unit, regions):
    """Driver-measured cross-region table: the claim a reviewer checks first."""
    if not regions:
        return ""
    rows = ["| region | unit `%s` | DOL sha1 | other units |" % unit, "|---|---:|---|---|"]
    for region in REGIONS:
        r = regions.get(region) or {}
        ub, ua = r.get("unit_before"), r.get("unit_after")
        sha = "matches retail" if r.get("ok") else "FAILED"
        if ub is None or ua is None:
            rows.append(f"| {region} | not measured | {sha} | not measured |")
            continue
        others = sorted((set(r.get("regressed", [])) | set(r.get("improved", []))) - {unit})
        if unit in r.get("regressed", []):
            cell = "**unit regressed**" + ("" if not others else ", " + ", ".join(others))
        else:
            cell = "unchanged" if not others else ", ".join(f"`{n}`" for n in others)
        rows.append(f"| {region} | {ub:.5f} -> {ua:.5f} | {sha} | {cell} |")
    return ("\n\n## Cross-region validation\n\n"
            "Built and DOL-checksum-verified in this clone for all three regions "
            "(`ninja all_source progress build/<v>/report.json`, then `ninja build/<v>/ok`); "
            "every unit's score in every region was compared against `origin/staging`.\n\n"
            + "\n".join(rows))


def render_pr_body(unit, branch, before, after, draft, commits, model, regions=None):
    """Agent-authored body in the repo's PR shape; a structured fallback otherwise."""
    lines = draft.splitlines()
    title = lines[0][2:].strip() if lines and lines[0].startswith("# ") else ""
    title = re.sub(r"[;,]\s*3 decimal(?: places|s)?(?=\)?$)", "", title).strip()
    text = "\n".join(lines[1:] if title else lines).strip()
    missing = [sec for sec in PR_SECTIONS if sec not in text.lower()]
    if not title or missing:
        what = "\n".join(f"- `{c}`" for c in commits) or "- (no commits recorded)"
        subject = commits[0].removeprefix("loop: ") if commits else "unit progress"
        title = f"{unit}: {subject} ({before:.3f} -> {after:.3f})"
        text = (f"## What changed\n\n{what}\n\n"
                f"## Evidence\n\n| | before | after |\n|---|---:|---:|\n"
                f"| unit `{unit}` (GCCP01) | {before:.5f} | {after:.5f} |\n\n"
                f"## Validation\n\n- `ninja` passes in the loop clone (`build/GCCP01/ok`)\n"
                f"- not checked: GCCE01/GCCJGC and the GBA images")
    footer = (f"\n\n---\n\nAutomated: `tools/pi_loop.py`, branch `{branch}`, model `{model}`. "
              "Unit and per-function numbers read from `build/<version>/report.json`.")
    return title, text + render_regions(unit, regions) + footer


def commit_local(clone, unit, log):
    """Commit whatever the agent left dirty, minus the loop's own scratch files."""
    if not git(clone, "status", "--porcelain", log=log).stdout.strip():
        return
    git(clone, "add", "-A", log=log)
    git(clone, "reset", "-q", "--", "tools/pi_loop.py", PR_BODY_FILE, BASE_SHA_FILE, log=log)
    if git(clone, "diff", "--cached", "--quiet", log=log).returncode != 0:
        git(clone, "commit", "-q", "-m", f"loop: {unit} unit progress", log=log)


def publish(clone, unit, branch, before, after, exit_code, log, work, model, regions=None):
    ahead = git(clone, "rev-list", "--count", "origin/staging..HEAD", log=log).stdout.strip()
    if ahead in ("", "0"):
        return None, "no commits to publish"
    commits = [s.strip() for s in git(clone, "log", "--format=%s",
                                      "origin/staging..HEAD", log=log).stdout.splitlines() if s.strip()]
    draft_path = clone / PR_BODY_FILE
    draft = draft_path.read_text() if draft_path.exists() else ""
    title, body_text = render_pr_body(unit, branch, before, after, draft, commits, model, regions)
    git(clone, "push", "-q", "fork", f"HEAD:refs/heads/{branch}", log=log, check=True)
    body = work / "logs" / f"{branch.replace('/', '_')}.md"
    body.write_text(body_text + "\n")
    proc = sh(
        ["gh", "pr", "create", "--repo", UPSTREAM, "--base", "staging",
         "--head", f"{FORK_OWNER}:{branch}", "--title", title, "--body-file", str(body)],
        clone,
        log=log,
    )
    if proc.returncode != 0:
        return None, f"gh pr create failed: {proc.stderr.strip()[-500:]}"
    return proc.stdout.strip().splitlines()[-1], "ok"


# ---------------------------------------------------------------------- driver


def prepare_job(args, work, ctx):
    """Serialized: refresh base if stale, pick a target, hand out a fresh clone."""
    if ctx["stop"]:
        return None
    if time.time() - ctx["refreshed"] > args.refresh_minutes * 60:
        ctx["base"] = refresh_base(work, None)
        ctx["refreshed"] = time.time()
    if args.unit:
        forced, blob = args.unit, ""
    else:
        forced, blob = None, open_pr_blob()
    try:
        cand = pick_target(ctx["base"], ctx["state"], forced, blob, ctx["claimed"])
    except SystemExit as exc:
        ctx["stop"] = str(exc)
        return None

    unit = cand["name"]
    slug = unit.split("/")[-1].lower()
    stamp = time.strftime("%Y%m%d-%H%M%S")
    branch = f"loop/{slug}-{stamp}"
    log = work / "logs" / f"{stamp}-{slug}.log"
    clone = make_clone(work, ctx["base"], unit, branch, log)
    playbook = REPO / "docs/agent_playbook.md"
    if playbook.exists() and not (clone / "docs/agent_playbook.md").exists():
        # guidance ships with the loop until it is merged into staging
        (clone / "docs").mkdir(exist_ok=True)
        shutil.copy2(playbook, clone / "docs/agent_playbook.md")
    prompt = prompt_for(cand, clone, branch, args.minutes)
    (work / "logs" / f"{stamp}-{slug}.prompt.txt").write_text(prompt)
    base_sha = git(clone, "rev-parse", "HEAD", log=log).stdout.strip()
    (clone / BASE_SHA_FILE).write_text(base_sha + "\n")
    ctx["active"].add(str(clone))
    ctx["claimed"].add(unit)
    return {"cand": cand, "unit": unit, "branch": branch, "clone": clone,
            "log": log, "prompt": prompt, "base_sha": base_sha}


def run_agent(args, job):
    """One serial agent conversation (plus nudges) inside the job's clone."""
    clone, unit, prompt, log = job["clone"], job["unit"], job["prompt"], job["log"]
    started = time.time()
    deadline = started + args.minutes * 60
    outs = []
    exit_code = 0
    for turn in range(args.nudges + 1):
        elapsed = int(time.time() - started)
        if turn and (elapsed > args.minutes * 60 * 0.75 or elapsed + 120 >= args.minutes * 60):
            break  # not enough budget left for another turn
        cmd = ["pi", "-p", "--provider", args.provider, "--model", args.model,
               "--thinking", args.thinking]
        if turn:
            cmd.append("--continue")
            cmd.append(NUDGE.format(minutes=args.minutes, elapsed=elapsed // 60))
        else:
            cmd.append(prompt)
        try:
            proc = sh(cmd, clone, timeout=max(120, int(deadline - time.time())), log=log)
        except subprocess.TimeoutExpired:
            # keep whatever the agent left in the tree: the gate still evaluates it
            print(f"[loop] {unit}: turn {turn + 1} hit the time budget", flush=True)
            outs.append(f"--- turn {turn + 1}: timed out after {int(time.time()-started)}s ---")
            exit_code = 0
            break
        outs.append(f"--- turn {turn + 1} (exit {proc.returncode}, {int(time.time()-started)}s) ---\n"
                    + (proc.stdout or "") + ("\n" + proc.stderr if proc.stderr else ""))
        exit_code = proc.returncode if turn == 0 else exit_code
        if proc.returncode != 0:
            break
        # stop nudging once the unit already improved
        if turn and unit_measure(clone, unit) > job["cand"]["fuzzy_match"] + 1e-9:
            break
    print(f"[loop] {unit}: agent exited {exit_code} in {int(time.time()-started)}s "
          f"({len(outs)} turn(s))", flush=True)
    return exit_code, "\n".join(outs)


def validate_regions(clone, unit, base_sha, log):
    """Measure the branch tip and its own base commit in every region, then diff every unit."""
    out = {}
    head = git(clone, "rev-parse", "HEAD", log=log).stdout.strip()
    for region in REGIONS:
        configure(clone, region, log)
        after = region_scores(clone, region, log)
        git(clone, "checkout", "-f", "-q", base_sha, log=log)
        before = region_scores(clone, region, log)
        git(clone, "checkout", "-f", "-q", head, log=log)
        b, a = before["scores"], after["scores"]
        out[region] = {
            "unit_before": b.get(unit),
            "unit_after": a.get(unit),
            "ok": after["ok"],
            "ok_before": before["ok"],
            "regressed": sorted(n for n, v in a.items() if n in b and v < b[n] - 1e-9),
            "improved": sorted(n for n, v in a.items() if n in b and v > b[n] + 1e-9),
        }
    configure(clone, UNIT, log)  # leave the clone PAL-configured
    return out


def run_job(args, work, ctx, job):
    unit, clone, branch, log = job["unit"], job["clone"], job["branch"], job["log"]
    before = job["cand"]["fuzzy_match"]
    exit_code, _ = run_agent(args, job)
    result = {"unit": unit, "branch": branch, "clone": str(clone), "log": str(log),
              "agent_exit": exit_code, "before": before}
    commit_local(clone, unit, log)
    try:
        regions = validate_regions(clone, unit, job["base_sha"], log)
    except SystemExit as exc:
        result.update(after=before, delta=0.0, published=None,
                      note=f"build failed: {exc}")
    else:
        pal = regions[UNIT]
        after = pal["unit_after"] if pal["unit_after"] is not None else before
        result.update(after=after, delta=round(after - before, 4), regions=regions)
        print(f"[loop] {unit}: gate {before:.4f}% -> {after:.4f}% ({result['delta']:+.4f}) "
              + " ".join(f"{r}:{v['unit_after']:.4f}" for r, v in regions.items()
                         if v["unit_after"] is not None), flush=True)
        regressions = {r: v["regressed"] for r, v in regions.items() if v["regressed"]}
        with ctx["lock"]:
            entry = ctx["state"]["units"].setdefault(unit, {"attempts": 0, "best_delta": 0.0})
            if exit_code != 0 and result["delta"] <= 0:
                # agent crashed (API/billing/tool error): not a verdict on the unit
                result.update(published=None, note=f"agent error (exit {exit_code}), not counted")
            else:
                entry["attempts"] += 1
                entry["best_delta"] = max(entry["best_delta"], result["delta"])
                entry["last_delta"] = result["delta"]
        broken = [r for r, v in regions.items() if v.get("ok_before") and not v.get("ok")]
        regressed = {r: v["regressed"] for r, v in regions.items() if v["regressed"]}
        if "published" not in result and result["delta"] > 0 and broken:
            result.update(published=None,
                          note=f"region checksum broke in {', '.join(broken)}, not published")
            print(f"[loop] {unit}: {result['note']}", flush=True)
        elif "published" not in result and result["delta"] > 0 and regressed:
            detail = "; ".join(f"{r}: {', '.join(n)}" for r, n in regressed.items())
            result.update(published=None,
                          note=f"regresses a region ({detail}), not published")
            print(f"[loop] {unit}: {result['note']}", flush=True)
        elif "published" not in result and result["delta"] > 0 and not args.no_push:
            url, note = publish(clone, unit, branch, before, result["after"],
                                exit_code, log, work, args.model, regions)
            result.update(published=url, note=note)
            print(f"[loop] {unit}: publish {url or note}", flush=True)
        elif "published" not in result:
            result.update(published=None,
                          note="no improvement, discarded" if result["delta"] <= 0
                          else "improvement kept locally (--no-push)")
    with ctx["lock"]:
        ctx["active"].discard(str(clone))
        ctx["claimed"].discard(unit)
        ctx["state_path"].write_text(json.dumps(ctx["state"], indent=1, sort_keys=True))
        with open(work / "iterations.jsonl", "a") as f:
            f.write(json.dumps(result, sort_keys=True) + "\n")
        prune(work, args.keep_clones, ctx["active"])
    return result


def prune(work, keep, active):
    """Drop old clone dirs only - never other scratch dirs in the work dir."""
    clones = sorted(
        (p for p in work.iterdir()
         if p.is_dir() and re.match(r"^\d{4}-\d{6}-", p.name) and str(p) not in active),
        key=lambda p: p.stat().st_mtime,
    )
    for old in clones[: max(0, len(clones) - keep)]:
        shutil.rmtree(old, ignore_errors=True)


def parse_args(argv):
    p = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    p.add_argument("--iterations", type=int, default=1, help="jobs to run")
    p.add_argument("--workers", type=int, default=2, help="jobs in flight (2 = two priority queues)")
    p.add_argument("--refresh-minutes", type=float, default=30,
                   help="re-sync base from origin/staging after this long")
    p.add_argument("--minutes", type=int, default=45, help="minutes per target")
    p.add_argument("--nudges", type=int, default=2,
                   help="resume turns after an agent stops early with no gain")
    p.add_argument("--unit", action="append", help="force a unit (repeatable), skips ranking")
    p.add_argument("--provider", default="lunaroute", help="pi provider (lunaroute only)")
    p.add_argument("--model", default="deepseek-4.1-flash")
    p.add_argument("--thinking", default="high")
    p.add_argument("--work-dir", default="/tmp/ffcc-loop")
    p.add_argument("--no-push", action="store_true", help="keep wins local, do not open PRs")
    p.add_argument("--keep-clones", type=int, default=4)
    p.add_argument("--dry-run", action="store_true", help="print target + prompt, then exit")
    return p.parse_args(argv)


def main(argv=None):
    args = parse_args(argv)
    work = Path(args.work_dir)
    work.mkdir(parents=True, exist_ok=True)
    (work / "logs").mkdir(exist_ok=True)
    state_path = work / "state.json"
    state = {"units": {}}
    if state_path.exists():
        state = json.loads(state_path.read_text())

    if not args.no_push and not args.dry_run:
        if sh(["gh", "auth", "status"], REPO).returncode != 0:
            raise SystemExit("gh is not authenticated; rerun with --no-push or auth gh")

    if args.dry_run:
        base = refresh_base(work, None)
        cand = pick_target(base, state, args.unit, "" if args.unit else open_pr_blob())
        print(prompt_for(cand, work / "clone", "loop/<slug>", args.minutes))
        return 0

    base = refresh_base(work, None)
    ctx = {
        "lock": threading.Lock(),
        "state": state,
        "state_path": state_path,
        "stop": None,
        "base": base,
        "refreshed": time.time(),
        "active": set(),
        "claimed": set(),
    }
    print(f"[loop] {args.workers} worker(s), {args.iterations} job(s), "
          f"{args.minutes}m/{args.model}", flush=True)

    def worker(index):
        if ctx["stop"]:
            return {"skipped": ctx["stop"]}
        with ctx["lock"]:
            job = prepare_job(args, work, ctx)
        if job is None:
            return {"skipped": ctx["stop"] or "stopped"}
        print(f"[loop] job {index + 1}/{args.iterations}: {job['unit']} "
              f"({job['cand']['fuzzy_match']:.3f}%) -> {job['clone'].name}", flush=True)
        return run_job(args, work, ctx, job)

    with ThreadPoolExecutor(max_workers=args.workers) as pool:
        futures = [pool.submit(worker, i) for i in range(args.iterations)]
        for future in as_completed(futures):
            exc = future.exception()
            if exc:
                print(f"[loop] job failed: {exc!r}", flush=True)
    print(f"[loop] done: {ctx['stop'] or 'iterations exhausted'}", flush=True)
    return 0


if __name__ == "__main__":
    sys.exit(main())
