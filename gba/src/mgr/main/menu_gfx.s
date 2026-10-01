@ Menu, retry, pause and sleep screens (LZ77), with their BG tiles.

	.section .rodata

	.global gSelectScreenLz
	.balign 4
gSelectScreenLz:
	.incbin "gSelectScreenLz.bin"

	.global gSelectBgMapLz
	.balign 4
gSelectBgMapLz:
	.incbin "gSelectBgMapLz.bin"

	.global gRetryLinkScreenLz
	.balign 4
gRetryLinkScreenLz:
	.incbin "gRetryLinkScreenLz.bin"

	.global gSelectPauseScreenLz
	.balign 4
gSelectPauseScreenLz:
	.incbin "gSelectPauseScreenLz.bin"

	.global gRetrySoloScreenLz
	.balign 4
gRetrySoloScreenLz:
	.incbin "gRetrySoloScreenLz.bin"

	.global gSleepScreenLz
	.balign 4
gSleepScreenLz:
	.incbin "gSleepScreenLz.bin"

	.global gPauseSoloRowsLz
	.balign 4
gPauseSoloRowsLz:
	.incbin "gPauseSoloRowsLz.bin"

	.global gPauseLinkRowsLz
	.balign 4
gPauseLinkRowsLz:
	.incbin "gPauseLinkRowsLz.bin"

	.global gBgTilesLz
	.balign 4
gBgTilesLz:
	.incbin "gBgTilesLz.bin"

	.global gSleepTilesLz
	.balign 4
gSleepTilesLz:
	.incbin "gSleepTilesLz.bin"
