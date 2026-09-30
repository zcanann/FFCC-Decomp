# Libraries

- `libgcc/`, `ginclude/`: from [pret/agbcc](https://github.com/pret/agbcc) at `da598c1`
  (GPL-2.0, see `COPYING`). `fp-bit.c` and `dp-bit.c` are generated from
  `fp-bit-base.c` exactly as agbcc's `libgcc/Makefile` does. Built the same way as
  agbcc's libgcc: `lib1thumb.asm` per `L_<name>` routine with the assembler, the rest
  with `old_agbcc -O2`.
- `m4a/`: the MusicPlayer2000 sound engine, adapted from
  [pret/pokeruby](https://github.com/pret/pokeruby) (`5784633`) to the older version
  both programs use. This version runs `SoundMain`, the sequence commands, `MidiKey2Freq`
  and the player continue/fade-out routines from the BIOS, so `m4a_1.s` keeps only the
  routines outside the BIOS and several `m4a.c` functions are SWI calls. Built with
  `old_agbcc -mthumb-interwork -O2`. The sound mode differs per program
  (`M4A_SOUND_FREQ`, set in `tools/gba_project.py`).
- `align.s`: appended to compiler output before assembling, like pret and agbcc's
  libgcc, so sections end with zero-filled word alignment.
- `libagbsyscall/`: BIOS call wrappers from pret/pokeemerald's `libagbsyscall.s`,
  assembled once per routine (`L_<name>`) like pret's granular build. The programs
  link them in alphabetical (archive) order.
- `asm/`: shared assembler includes for the library sources.
