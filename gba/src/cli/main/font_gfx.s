@ Font, text window graphics and sprite palettes, extracted from the retail image.

	.section .data

	.global gFont
	.balign 4
gFont:
	.incbin "gFont.bin"

	.global gTextGfx
	.balign 4
gTextGfx:
	.incbin "gTextGfx.bin"

	.global gSpFontPalettes
	.balign 4
gSpFontPalettes:
	.incbin "gSpFontPalettes.bin"

	.global gSpObjPalettes
	.balign 4
gSpObjPalettes:
	.incbin "gSpObjPalettes.bin"

	.global gSpTextPalettes
	.balign 4
gSpTextPalettes:
	.incbin "gSpTextPalettes.bin"
