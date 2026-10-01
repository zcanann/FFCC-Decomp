@ Mode 7 field tiles and map, and the sky tiles.

	.section .rodata

	.global gFieldTilesLz
	.balign 4
gFieldTilesLz:
	.incbin "gFieldTilesLz.bin"

	.global gSkyTilesLz
	.balign 4
gSkyTilesLz:
	.incbin "gSkyTilesLz.bin"

	.global gFieldMapLz
	.balign 4
gFieldMapLz:
	.incbin "gFieldMapLz.bin"
