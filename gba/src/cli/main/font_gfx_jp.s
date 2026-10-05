@ Japanese font and text palettes, in retail resource order.

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

	.global gSpTextPalettes
	.balign 4
gSpTextPalettes:
	.incbin "gSpTextPalettes.bin"

	.global gSpObjPalettes
	.balign 4
gSpObjPalettes:
	.incbin "gSpObjPalettes.bin"
