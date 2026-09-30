#ifndef GUARD_TEXT_H
#define GUARD_TEXT_H

#include "global.h"

/* BG0 text/HUD screen, copied to VRAM when dirty */
struct TextLayer {
    vu16 map[20][32];
    u16 backup[20][32];
    vu8 dirty;
    u8 charmap[128];
};

/* Rectangular block of pre-drawn tiles (big numbers, banners) */
struct Glyph {
    u16 tile;
    u8 w;
    u8 h;
};

extern struct TextLayer gTextLayer;
extern char gPrintBuffer[];
extern const u8 gCharset[];
extern const struct Glyph gGlyphs[];
extern const u8 gFontTilesLz[];
extern const u8 gFontPalette[];
extern const u8 gBgTilesLz[];
extern const u8 gSleepTilesLz[];
extern const u8 gSleepScreenLz[];
extern const u8 gPauseSoloRowsLz[];
extern const u8 gPauseLinkRowsLz[];
extern const u8 gSelectPauseScreenLz[];
extern const u8 gRetryLinkScreenLz[];
extern const u8 gRetrySoloScreenLz[];
extern u8 gTileBuffer[];

void Text_Init(struct TextLayer *layer);
void Text_Clear(struct TextLayer *layer, u8 palette);
void Text_DrawGlyph(struct TextLayer *layer, s32 x, s32 y, u16 id, u16 palette);
void Text_EraseGlyph(struct TextLayer *layer, s32 x, s32 y, u16 id);
void Text_Print(struct TextLayer *layer, s32 x, s32 y, u16 palette, const char *str);
void Text_Printf(struct TextLayer *layer, s32 x, s32 y, const char *fmt, ...);
void Text_LoadScreen(struct TextLayer *layer, const void *src);
void Text_LoadRows(struct TextLayer *layer, const void *src, u8 row);
void Text_Save(struct TextLayer *layer);
void Text_Restore(struct TextLayer *layer);
void Text_Flush(struct TextLayer *layer);
void Text_LoadFont(struct TextLayer *layer);
void Text_LoadSleepScreen(struct TextLayer *layer);
void Text_LoadPauseMenu(struct TextLayer *layer, u8 linked);
void Text_LoadSelectPauseMenu(struct TextLayer *layer);

#endif
