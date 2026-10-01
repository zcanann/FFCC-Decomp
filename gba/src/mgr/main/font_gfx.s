@ Font tiles and the BG palettes.

	.section .rodata

	.global gFontTilesLz
	.balign 4
gFontTilesLz:
	.incbin "gFontTilesLz.bin"

	.global lbl_02021B6C
	.balign 4
lbl_02021B6C:
	.incbin "lbl_02021B6C.bin"

	.global gFontPalette
	.balign 4
gFontPalette:
	.incbin "gFontPalette.bin"

	.global gBgPalette
	.balign 4
gBgPalette:
	.incbin "gBgPalette.bin"
