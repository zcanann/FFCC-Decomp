import argparse
import errno
import os
import signal
import subprocess
import sys
import time
from datetime import datetime
from pathlib import Path
from typing import Optional

AGENTS_FILE_CANDIDATES = ("AGENTS.md", "AGENTS.MD")


def _resolve_agents_file_in_dir(directory: Path) -> Optional[Path]:
    # Match exact directory entries first so case-variant names are handled
    # predictably even on case-insensitive filesystems.
    try:
        dir_entries = set(os.listdir(directory))
    except OSError:
        # If listing fails, still check canonical candidates directly.
        for filename in AGENTS_FILE_CANDIDATES:
            candidate = directory / filename
            if candidate.is_file():
                return candidate
        return None

    for filename in AGENTS_FILE_CANDIDATES:
        candidate = directory / filename
        if filename in dir_entries and candidate.is_file():
            return candidate

    # Fall back to any case variant like "Agents.md" on case-sensitive filesystems.
    canonical_name = AGENTS_FILE_CANDIDATES[0].casefold()
    case_insensitive_matches = sorted(
        directory / entry
        for entry in dir_entries
        if entry.casefold() == canonical_name and (directory / entry).is_file()
    )
    if case_insensitive_matches:
        return case_insensitive_matches[0]

    return None


def _resolve_agents_filename() -> str:
    try:
        cwd = Path.cwd()
    except OSError:
        return AGENTS_FILE_CANDIDATES[0]

    for directory in [cwd, *cwd.parents]:
        agents_file = _resolve_agents_file_in_dir(directory)
        if agents_file is None:
            continue
        try:
            return os.path.relpath(agents_file, cwd)
        except ValueError:
            return str(agents_file)

    return AGENTS_FILE_CANDIDATES[0]


def _default_prompt() -> str:
    agents_file = _resolve_agents_filename()
    return (
        f"Follow the instructions in {agents_file}. NEVER ask the user for input. "
        "Simply follow the instructions and make a PR if there is an improvement. "
        "Pay careful attention to any important rules."
    )


DEFAULT_PROMPT = _default_prompt()

KILL_SIGNAL = getattr(signal, "SIGKILL", signal.SIGTERM)
KILL_WAIT_SECONDS = 5


def log(message: str) -> None:
    timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    print(f"[{timestamp}] {message}", flush=True)


def _read_int_env(var_name: str, default: int, minimum: Optional[int] = None) -> int:
    raw_value = os.getenv(var_name)
    if raw_value is None:
        return default

    try:
        value = int(raw_value)
    except ValueError:
        log(f"invalid integer for {var_name}={raw_value!r}; using default {default}")
        return default

    if minimum is not None and value < minimum:
        log(
            f"invalid integer for {var_name}={raw_value!r}; minimum is {minimum}; "
            f"using default {default}"
        )
        return default

    return value


def _read_optional_int_env(var_name: str, minimum: Optional[int] = None) -> Optional[int]:
    raw_value = os.getenv(var_name)
    if raw_value is None:
        return None

    try:
        value = int(raw_value)
    except ValueError:
        log(f"invalid integer for {var_name}={raw_value!r}; ignoring value")
        return None

    if minimum is not None and value < minimum:
        log(
            f"invalid integer for {var_name}={raw_value!r}; minimum is {minimum}; "
            "ignoring value"
        )
        return None

    return value


def _signal_process_tree(proc: subprocess.Popen, sig: int) -> None:
    """Signal the full process tree when possible."""
    if proc.poll() is not None:
        return

    try:
        if os.name == "posix":
            os.killpg(proc.pid, sig)
        else:
            # Use taskkill so child processes are also terminated on Windows.
            force = sig == KILL_SIGNAL
            cmd = ["taskkill", "/PID", str(proc.pid), "/T"]
            if force:
                cmd.append("/F")
            subprocess.run(cmd, check=False, capture_output=True)
    except ProcessLookupError:
        pass
    except OSError:
        # Fall back to the direct process if group/tree signaling is unavailable.
        try:
            proc.send_signal(sig)
        except (ProcessLookupError, OSError, ValueError):
            # Best-effort signaling; ignore errors for already-exited processes.
            pass


def _stop_process_tree(proc: subprocess.Popen, grace_seconds: int) -> None:
    _signal_process_tree(proc, signal.SIGTERM)
    try:
        proc.wait(timeout=grace_seconds)
    except subprocess.TimeoutExpired:
        _signal_process_tree(proc, KILL_SIGNAL)
        try:
            proc.wait(timeout=KILL_WAIT_SECONDS)
        except subprocess.TimeoutExpired:
            log(
                f"process did not exit after forced kill within {KILL_WAIT_SECONDS}s; "
                "continuing"
            )


def _sleep_interruptible(seconds: int) -> bool:
    """Sleep and return False if interrupted by Ctrl+C."""
    try:
        time.sleep(seconds)
        return True
    except KeyboardInterrupt:
        log("keyboard interrupt received; stopping loop")
        return False


def _read_prompt_env(var_name: str, default: str) -> str:
    raw_value = os.getenv(var_name)
    if raw_value is None:
        return default
    prompt = raw_value.strip()
    if not prompt:
        log(f"empty prompt for {var_name}; using default prompt")
        return default
    return prompt


def _backoff_seconds(consecutive_failures: int, max_backoff_seconds: int) -> int:
    return min(2 ** min(consecutive_failures, 8), max_backoff_seconds)


def _can_retry(run_count: int, max_runs: Optional[int]) -> bool:
    """Return whether another retry attempt is allowed."""
    return max_runs is None or run_count < max_runs


def _normalize_process_return_code(returncode: Optional[int]) -> int:
    """Map subprocess return codes to conventional shell exit statuses."""
    if returncode is None or returncode == 0:
        return 1
    if returncode < 0:
        # Python uses negative values for signal termination; shells use 128+signal.
        return 128 + abs(returncode)
    return returncode


def _is_interrupt_return_code(returncode: Optional[int]) -> bool:
    """Return whether a process exit code indicates user interrupt."""
    if returncode is None:
        return False
    return returncode == 130 or returncode == -getattr(signal, "SIGINT", 2)


def _parse_args(argv: Optional[list[str]] = None) -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Run codex in a supervised retry loop with timeout, "
            "graceful termination, and exponential backoff."
        )
    )
    parser.add_argument(
        "--prompt",
        help="Prompt to pass to `codex exec --yolo` (defaults to AGENTIC_PROMPT/env).",
    )
    parser.add_argument(
        "--timeout-seconds",
        type=int,
        help="Timeout for each codex run in seconds.",
    )
    parser.add_argument(
        "--terminate-grace-seconds",
        type=int,
        help="Seconds to wait after SIGTERM before force-killing.",
    )
    parser.add_argument(
        "--max-backoff-seconds",
        type=int,
        help="Maximum exponential backoff delay in seconds between retries.",
    )
    parser.add_argument(
        "--max-runs",
        type=int,
        help=(
            "Maximum number of codex runs before exiting. "
            "By default, the loop runs indefinitely."
        ),
    )
    return parser.parse_args([] if argv is None else argv)


def _resolve_runtime_config(
    argv: Optional[list[str]] = None,
) -> tuple[str, int, int, int, Optional[int]]:
    args = _parse_args(argv)
    prompt = args.prompt
    if prompt is None:
        prompt = _read_prompt_env("AGENTIC_PROMPT", DEFAULT_PROMPT)
    elif not prompt.strip():
        log("empty prompt for --prompt; using AGENTIC_PROMPT/default prompt")
        prompt = _read_prompt_env("AGENTIC_PROMPT", DEFAULT_PROMPT)
    else:
        prompt = prompt.strip()

    timeout_seconds = (
        args.timeout_seconds
        if args.timeout_seconds is not None
        else _read_int_env("AGENTIC_TIMEOUT_SECONDS", 25 * 60, minimum=1)
    )
    terminate_grace_seconds = (
        args.terminate_grace_seconds
        if args.terminate_grace_seconds is not None
        else _read_int_env("AGENTIC_TERMINATE_GRACE_SECONDS", 10, minimum=0)
    )
    max_backoff_seconds = (
        args.max_backoff_seconds
        if args.max_backoff_seconds is not None
        else _read_int_env("AGENTIC_MAX_BACKOFF_SECONDS", 300, minimum=1)
    )
    max_runs = (
        args.max_runs
        if args.max_runs is not None
        else _read_optional_int_env("AGENTIC_MAX_RUNS", minimum=1)
    )

    if timeout_seconds < 1:
        log(
            f"invalid value for --timeout-seconds={timeout_seconds!r}; minimum is 1; "
            "using default 1500"
        )
        timeout_seconds = 25 * 60
    if terminate_grace_seconds < 0:
        log(
            "invalid value for --terminate-grace-seconds="
            f"{terminate_grace_seconds!r}; minimum is 0; using default 10"
        )
        terminate_grace_seconds = 10
    if max_backoff_seconds < 1:
        log(
            f"invalid value for --max-backoff-seconds={max_backoff_seconds!r}; "
            "minimum is 1; using default 300"
        )
        max_backoff_seconds = 300
    if max_runs is not None and max_runs < 1:
        log(
            f"invalid value for --max-runs={max_runs!r}; minimum is 1; "
            "running indefinitely"
        )
        max_runs = None

    return prompt, timeout_seconds, terminate_grace_seconds, max_backoff_seconds, max_runs


def run_agentic_loop(
    prompt: str,
    timeout_seconds: int,
    terminate_grace_seconds: int,
    max_backoff_seconds: int,
    max_runs: Optional[int] = None,
) -> int:
    cmd = ["codex", "exec", "--yolo", prompt]
    consecutive_failures = 0
    run_count = 0
    exit_code = 0

    while True:
        if max_runs is not None and run_count >= max_runs:
            log(f"reached max runs ({max_runs}); stopping loop")
            break

        run_count += 1
        log(f"starting codex run #{run_count}")
        try:
            proc = subprocess.Popen(
                cmd,
                start_new_session=(os.name == "posix"),
            )
        except OSError as exc:
            if exc.errno in (errno.ENOENT, errno.EACCES):
                log(f"failed to launch codex ({exc}); unrecoverable error, stopping loop")
                return 127 if exc.errno == errno.ENOENT else 126
            consecutive_failures += 1
            exit_code = 1
            if not _can_retry(run_count, max_runs):
                log(f"failed to launch codex ({exc}); reached max runs, stopping loop")
                break
            backoff = _backoff_seconds(consecutive_failures, max_backoff_seconds)
            log(f"failed to launch codex ({exc}); sleeping {backoff}s before retry")
            if not _sleep_interruptible(backoff):
                exit_code = 130
                break
            continue

        try:
            proc.wait(timeout=timeout_seconds)
            if proc.returncode == 0:
                consecutive_failures = 0
                exit_code = 0
                log("codex run completed successfully")
            elif _is_interrupt_return_code(proc.returncode):
                exit_code = 130
                log("codex run interrupted; stopping loop")
                break
            else:
                consecutive_failures += 1
                exit_code = _normalize_process_return_code(proc.returncode)
                if not _can_retry(run_count, max_runs):
                    log(f"codex exited with code {proc.returncode}; reached max runs, stopping loop")
                    break
                backoff = _backoff_seconds(consecutive_failures, max_backoff_seconds)
                log(
                    f"codex exited with code {proc.returncode}; "
                    f"sleeping {backoff}s before retry"
                )
                if not _sleep_interruptible(backoff):
                    exit_code = 130
                    break
        except subprocess.TimeoutExpired:
            log(f"codex exceeded timeout ({timeout_seconds}s); terminating process")
            _stop_process_tree(proc, terminate_grace_seconds)
            log("codex process stopped after timeout")
            consecutive_failures += 1
            exit_code = 124
            if not _can_retry(run_count, max_runs):
                log("reached max runs after timeout; stopping loop")
                break
            backoff = _backoff_seconds(consecutive_failures, max_backoff_seconds)
            log(f"sleeping {backoff}s before retry")
            if not _sleep_interruptible(backoff):
                exit_code = 130
                break
        except KeyboardInterrupt:
            log("keyboard interrupt received; stopping loop")
            _stop_process_tree(proc, terminate_grace_seconds)
            exit_code = 130
            break

    return exit_code

def main(argv: Optional[list[str]] = None) -> int:
    (
        prompt,
        timeout_seconds,
        terminate_grace_seconds,
        max_backoff_seconds,
        max_runs,
    ) = _resolve_runtime_config(argv)
    return run_agentic_loop(
        prompt=prompt,
        timeout_seconds=timeout_seconds,
        terminate_grace_seconds=terminate_grace_seconds,
        max_backoff_seconds=max_backoff_seconds,
        max_runs=max_runs,
    )


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
