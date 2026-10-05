@ m4a samples, song tracks and headers, extracted with symbolic pointers.

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

	.include "gSong04Track0.inc"
	.include "gSong04Track1.inc"
	.include "gSong04.inc"

	.include "gSong05Track0.inc"
	.include "gSong05Track1.inc"
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
