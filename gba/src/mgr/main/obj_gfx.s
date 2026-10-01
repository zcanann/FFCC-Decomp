@ Object animation chunk file, OBJ tiles and palettes.

	.section .rodata

	.global gObjData
	.balign 4
gObjData:
	.incbin "gObjData.bin"

	.global gObjTilesLz
	.balign 4
gObjTilesLz:
	.incbin "gObjTilesLz.bin"

	.global gObjPaletteLz
	.balign 4
gObjPaletteLz:
	.incbin "gObjPaletteLz.bin"
