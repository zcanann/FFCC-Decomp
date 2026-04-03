`__get_file_modes` session notes, 2026-04-03

Current confirmed state
- Unit: `main/MSL_C/PPCEABI/bare/H/file_io`
- Symbol: `__get_file_modes`
- Checked-in `HEAD` for this branch was only about `94.70526%` for `__get_file_modes`.
- Current best confirmed source on this branch is about `95.12631%` via `tools/objdiff-cli diff -p . -u main/MSL_C/PPCEABI/bare/H/file_io -o - __get_file_modes`.
- `ninja` passes on the improved version.

Actual improvement kept
- In `src/MSL_C/PPCEABI/bare/H/file_io.c`, removing the `mode_ptr` temporary and the dead `io_mode = 0` initializer improved codegen:
  - `const char* mode_ptr = mode + 2;` removed
  - `next_mode = *mode_ptr;` changed to `next_mode = mode[2];`
  - `int io_mode = 0;` changed to `int io_mode;`
- This is source-plausible and gives the best result I found this session.

Reference projects checked
- `reference_projects/animal_crossing/src/static/MSL_C.PPCEABI.bare.H/file_io.c`
- `reference_projects/marioparty4/src/MSL_C.PPCEABI.bare.H/file_io.c`
- `reference_projects/pikmin2/src/Dolphin/MSL_C/MSL_Common/file_io.c`
- `reference_projects/twilight_princess/libs/PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/Src/file_io.c`
- `reference_projects/wind_waker/src/PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/Src/file_io.c`
- Also checked local MSL header variants under `reference_projects/*/ansi_files.h`.

Takeaways from references
- Most reference `file_io.c` copies only cover `fclose` and `fflush`; they do not include this exact inline `freopen`/`fopen` plus `__get_file_modes` shape.
- The `file_modes` bitfield declaration I found in reference projects matches the current header closely enough that I do not have evidence for a better structural declaration yet.
- `register` is used elsewhere in this MSL drop (`string.c`), so it is not inherently implausible, but it did not help here.

Ghidra / target observations
- Ghidra for PAL `0x801B5A18` still suggests the target is doing:
  - set `file_kind`
  - clear `file_orientation`
  - clear `binary_io`
  - parse `mode[0]`, then `mode[1]`, then optional `mode[2]`
- The remaining mismatch is still concentrated in early bitfield setup and temporary/register lifetimes, not in the high-level parser logic.

Experiments that regressed or gave no gain this session
- Restore `mode_ptr` while keeping `io_mode` uninitialized.
  - Result: worse, back down to about `94.70526%`
- Change the first `switch (mode_str)` into an `if`/`else if` chain.
  - Result: worse, about `94.70526%`
- Add `register` to `mode_str` and `next_mode`.
  - Result: no measurable improvement over the current best
- Move `mode_str` load before `modes->file_kind = __disk_file;`
  - Result: much worse, about `92.12631%` in this branch state
- Change `mode_str` to `unsigned int`
  - Result: much worse, about `90.073685%`
- Earlier same-day tests from the prior note remain valid:
  - nested `if`/`else` rewrite: much worse, roughly `45.55%`
  - `mode_str = mode[0];`: worse, about `93.39%`
  - `next_mode` as `char`: worse, about `93.49%`

Working conclusion
- The only reliable gain I found is the simpler `mode[2]` access plus removing the unnecessary `io_mode` initializer.
- Beyond that, broad source rewrites are the wrong direction.
- The remaining miss is likely from very small codegen details:
  - exact bitfield store scheduling into `file_modes`
  - temporary lifetime / register pressure in the first two parsing blocks
  - possibly a subtle structural issue outside this function, but I do not yet have evidence strong enough to justify flag or header changes

Next hypotheses if revisiting
- Compare the target’s first ~12 instructions more directly and try to force the `mode[0]` load / bitfield store interleave without changing the parser shape.
- Check whether caller/inlining context around inline `freopen`/`fopen` can perturb this object enough to affect `__get_file_modes`.
- Re-check alternate MSL drops for a literal `__get_file_modes` implementation rather than inferring from nearby headers.

`__get_file_modes` follow-up, 2026-04-03 (later session)

Current confirmed state after recheck
- Restored `src/MSL_C/PPCEABI/bare/H/file_io.c` to match `git` `HEAD` exactly.
- A full `ninja` followed by `tools/objdiff-cli diff -p . -u main/MSL_C/PPCEABI/bare/H/file_io -o - __get_file_modes` again reports about `95.12631%` for `__get_file_modes`.
- So there is still no reproducible improvement beyond the prior note in this branch state.

Important process note
- Single-object rebuild experiments were misleading in this session.
- Partial rebuilds plus ad hoc objdump checks made the function look much worse than the full-build objdiff result.
- For this unit, treat full `ninja` + objdiff as the authoritative baseline before trusting local assembly experiments.

Extra experiments tried this session that did not help
- `mode_str = mode[0];`
  - Regressed.
- Moving the `mode[0]` load before `modes->file_kind = __disk_file;`
  - Regressed again in this workspace state.
- Introducing a separate `char mode_char` temporary and promoting it later.
  - Regressed badly.

Updated working conclusion
- The previous kept change still stands as the only reproducible improvement I have seen here:
  - remove `mode_ptr`
  - use `mode[2]`
  - leave `io_mode` uninitialized until assigned
- I was not able to find a further net gain this session.
- If revisiting, start from the full-build `95.12631%` baseline, not from single-object rebuild output.

`__get_file_modes` follow-up, 2026-04-03 (current session correction)

Correction to the earlier notes
- I was not able to reproduce the earlier `95.12631%` claim in this workspace after restoring and rebuilding from `git` `HEAD`.
- Current verified full-build baseline on this branch is:
  - `tools/objdiff-cli diff -p . -u main/MSL_C/PPCEABI/bare/H/file_io -o - __get_file_modes`
  - result: about `94.70526%`
- `src/MSL_C/PPCEABI/bare/H/file_io.c` has been restored to `git` `HEAD` after this check. Do not assume the older "best known" note is still valid.

Reference / structural recheck
- Re-checked local reference projects again, including:
  - `reference_projects/super_mario_strikers/include/PowerPC_EABI_Support/MSL_C/MSL_Common/ansi_files.h`
  - `reference_projects/battle_for_bikini_bottom/src/PowerPC_EABI_Support/include/PowerPC_EABI_Support/MSL_C/MSL_Common/ansi_files.h`
- Those headers do not suggest a better `file_modes` bitfield layout than the current local declaration.
- I also re-checked the original and rebuilt object disassembly directly with:
  - `build/binutils/powerpc-eabi-objdump.exe -drz build/GCCP01/obj/MSL_C/PPCEABI/bare/H/file_io.o`
  - `build/binutils/powerpc-eabi-objdump.exe -drz build/GCCP01/src/MSL_C/PPCEABI/bare/H/file_io.o`

Most useful concrete mismatch summary
- Target early sequence still looks like:
  - load `file_modes`
  - set `file_kind`
  - load `mode[0]`
  - store the halfword
  - zero a temp
  - `extsb` the loaded mode character
- Current rebuilt function instead still does:
  - load `file_modes`
  - set `file_kind`
  - store the halfword immediately
  - zero a temp
  - then load `mode[0]`
- Later in the target, the compiler also materializes `mode + 2` (`addi`) before the second parser block, while the current rebuild prefers direct indexed loads or otherwise does not keep that exact scheduling.

Extra experiments tried in this session
- `mode_str = mode[0];`
  - Worse, about `90.91579%` from the current baseline.
  - It does recover an `extsb`, but it breaks surrounding store scheduling and hurts the function overall.
- Restore a `mode_ptr` temporary while keeping `io_mode` uninitialized.
  - No improvement; still about `94.70526%`.
  - The compiler optimized it back to the same shape anyway.
- Change `open_mode` to `unsigned int`.
  - No improvement; still about `94.70526%`.

Current conclusion
- No reproducible net progress was found this session.
- The remaining mismatch still looks like a small codegen/scheduling issue rather than a clear parser-logic bug.
- If revisiting, higher-value directions are:
  - find a literal MSL `__get_file_modes` source drop, if one exists
  - verify whether this unit should really be compiled with the current exact flags/language mode
  - inspect whether some broader unit-level structural difference, not just this function body, is responsible for the scheduling mismatch

`__get_file_modes` follow-up, 2026-04-03 (compiler-version breakthrough)

New verified finding
- The ceiling here was not a source-body problem first. It was a unit compiler-version problem.
- Keeping `src/MSL_C/PPCEABI/bare/H/file_io.c` at checked-in source and compiling the unit with different Metrowerks versions out of tree gave:
  - baseline project config (`GC/1.3.2`): `94.70526%` for `__get_file_modes`
  - `GC/1.3.2r`: about `95.12631%`
  - `GC/1.3.2` with `-inline deferred,auto`: about `95.12631%`
  - `GC/2.7`: about `95.189476%`

Best confirmed project-state change
- In `configure.py`, changing:
  - `Object(NonMatching, "MSL_C/PPCEABI/bare/H/file_io.c")`
- To:
  - `Object(NonMatching, "MSL_C/PPCEABI/bare/H/file_io.c", mw_version="GC/2.7")`
- Then running:
  - `python configure.py --version GCCP01`
  - `ninja`
  - `tools/objdiff-cli diff -p . -u main/MSL_C/PPCEABI/bare/H/file_io -o - __get_file_modes`
- Result:
  - `__get_file_modes`: about `95.189476%`
  - unit `.text`: about `98.94213%`
- This is a real improvement over the checked-in baseline:
  - `__get_file_modes`: `94.70526% -> 95.189476%`
  - unit `.text`: `98.83565% -> 98.94213%`

Why this is plausible
- This MSL library already mixes compiler versions per-object in `configure.py` (`ansi_files.c` already uses `GC/2.7`), so a version override for `file_io.c` is not a new kind of hack in this repo.
- The source-body experiments kept failing or regressing, while multiple compiler-version probes improved the same remaining scheduling region.
- The best result came from `GC/2.7`, not from contrived source changes.

Notes on source experiments after the compiler finding
- Re-tried signed-char and `mode + 2` scheduling ideas after the assembly recheck.
- They could recover isolated target features like `extsb` or `addi`, but overall they regressed the symbol badly and are not worth keeping.
- The checked-in source should stay as-is; the progress is in the unit compile configuration.
