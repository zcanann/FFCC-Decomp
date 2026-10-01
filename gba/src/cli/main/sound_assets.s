@ m4a sound data (DirectSound samples and songs) linked before the voice group and tables.

	.section .rodata

	.global gWaveSample0
	.balign 4
gWaveSample0:
	.incbin "gWaveSample0.bin"

	.global gWaveSample1
	.balign 4
gWaveSample1:
	.incbin "gWaveSample1.bin"

	.global gWaveSample2
	.balign 4
gWaveSample2:
	.incbin "gWaveSample2.bin"

	.include "lbl_0202DC60.inc"
	.include "lbl_0202DC90.inc"
	.include "gSong04.inc"
	.include "lbl_0202DCC8.inc"
	.include "lbl_0202DCE4.inc"
	.include "gSong05.inc"

	.global gWaveSample3
	.balign 4
gWaveSample3:
	.incbin "gWaveSample3.bin"

	.global gWaveSample4
	.balign 4
gWaveSample4:
	.incbin "gWaveSample4.bin"

	.global gWaveSample5
	.balign 4
gWaveSample5:
	.incbin "gWaveSample5.bin"
