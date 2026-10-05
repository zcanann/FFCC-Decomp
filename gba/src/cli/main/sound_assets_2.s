@ m4a samples, song tracks and headers, extracted with symbolic pointers.

	.section .rodata

	.global gWaveSample6
	.balign 4
gWaveSample6:
	.incbin "gWaveSample6.bin"

	.include "gSong00Track0.inc"
	.include "gSong00Track1.inc"
	.include "gSong00.inc"

	.include "gSongUnused0Track0.inc"
	.include "gSongUnused0Track1.inc"
	.include "gSongUnused0.inc"

	.include "gSong03Track0.inc"
	.include "gSong03Track1.inc"
	.include "gSong03.inc"

	.include "gSongUnused1Track0.inc"
	.include "gSongUnused1Track1.inc"
	.include "gSongUnused1.inc"

	.include "gSong01Track0.inc"
	.include "gSong01Track1.inc"
	.include "gSong01.inc"

	.include "gSong02Track0.inc"
	.include "gSong02Track1.inc"
	.include "gSong02.inc"

	.include "gSong06Track0.inc"
	.include "gSong06Track1.inc"
	.include "gSong06.inc"

	.global gWaveSample7
	.balign 4
gWaveSample7:
	.incbin "gWaveSample7.bin"

	.global gWaveSample8
	.balign 4
gWaveSample8:
	.incbin "gWaveSample8.bin"
