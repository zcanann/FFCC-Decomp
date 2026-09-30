# Libraries

`libgcc/` and `ginclude/` are from [pret/agbcc](https://github.com/pret/agbcc) at
`da598c1` (GPL-2.0, see `COPYING`). `fp-bit.c` and `dp-bit.c` are generated from
`fp-bit-base.c` exactly as agbcc's `libgcc/Makefile` does. They are built the same
way as agbcc's libgcc: `lib1thumb.asm` per `L_<name>` routine with the assembler,
the rest with `old_agbcc -O2`.
