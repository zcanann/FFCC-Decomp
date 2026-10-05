@ Font tiles and the BG palettes.

	.section .rodata

	.global gFontTilesLz
	.balign 4
gFontTilesLz:
	.incbin "gFontTilesLz.bin"

@ The first 14 palette banks are unused; Text_Init uploads the final two.
	.global gUnusedFontPalettes
	.balign 4
gUnusedFontPalettes:
	.incbin "gUnusedFontPalettes.bin"

	.global gFontPalette
	.balign 4
gFontPalette:
	.incbin "gFontPalette.bin"

	.global gBgPalette
	.balign 4
gBgPalette:
	.incbin "gBgPalette.bin"
