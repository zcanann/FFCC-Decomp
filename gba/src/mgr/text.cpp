#include "global.h"
#include "main.h"
#include "text.h"

#if defined(VERSION_GCCJGC)
u8 gCharset[] = "!@#$%^&()-+*/=:       0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
#else
u8 gCharset[] = "!@#$%^&()-+*/=:abcdefg0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ. ";
#endif

struct Glyph gGlyphs[] = {
    { 0xF2, 2, 2 },
    { 0xBD, 2, 2 },
    { 0xBB, 2, 2 },
    { 0xB9, 2, 2 },
    { 0xB7, 2, 2 },
    { 0x4, 4, 4 },
    { 0x8, 4, 4 },
    { 0xC, 4, 4 },
#if defined(VERSION_GCCJGC)
    { 0x80, 15, 6 },
#else
    { 0x80, 10, 6 },
#endif
    { 0x140, 15, 6 },
    { 0x10, 2, 2 },
    { 0x50, 2, 2 },
    { 0x90, 2, 2 },
    { 0xD0, 2, 2 },
    { 0x12, 4, 2 },
#if defined(VERSION_GCCJGC)
    { 0x72, 9, 2 },
#else
    { 0x8A, 6, 2 },
    { 0xCA, 6, 2 },
    { 0x10A, 1, 2 },
#endif
    { 0x16, 3, 3 },
    { 0x19, 3, 3 },
    { 0x12F, 11, 2 },
};

void Text_Init(struct TextLayer *layer)
{
    u32 i;
    const u8 *str;
    u8 c;
    u8 no;

    for (i = 0; i < 128; i++)
        layer->charmap[i] = 15;
    str = gCharset;
    no = 0;
    while ((c = *str++) != 0) {
        if ((u8)(c - 'A') <= 'Z' - 'A')
            layer->charmap[c + 32] = no;
        layer->charmap[c] = no++;
    }
    Text_LoadFont(layer);
    LZ77UnCompWram(gFontTilesLz, gDecompBuffer);
    DmaSet(gDecompBuffer, VRAM + 0x1000, 0x84000E00);
    DmaSet(gFontPalette, PLTT + 0x1C0, 0x84000010);
    Text_Clear(layer, 15);
}

void Text_Clear(struct TextLayer *layer, u8 palette)
{
    u16 fill = (palette << 12) | 22;

    DmaFill16(fill, layer, 0x81000280);
    layer->dirty = 1;
}

void Text_DrawGlyph(struct TextLayer *layer, s32 x, s32 y, u16 id, u16 palette)
{
    u16 attr = palette << 12;
    const struct Glyph *g = &gGlyphs[id];
    s32 x1 = x + g->w;
    s32 y1 = y + g->h;
    u16 tile = g->tile;
    u16 t;
    s32 i;

    for (; y < y1; y++) {
        t = tile;
        tile = t + 32;
        for (i = x; i < x1; i++, t++)
            layer->map[y][i] = attr | t;
    }
    layer->dirty = 1;
}

void Text_EraseGlyph(struct TextLayer *layer, s32 x, s32 y, u16 id)
{
    u16 blank = 0xF016;
    const struct Glyph *g = &gGlyphs[id];
    s32 x1 = x + g->w;
    s32 y1 = y + g->h;
    s32 i;

    for (; y < y1; y++) {
        for (i = x; i < x1; i++)
            layer->map[y][i] = blank;
    }
    layer->dirty = 1;
}

void Text_Print(struct TextLayer *layer, s32 x, s32 y, u16 palette, const char *str)
{
    u16 attr = palette << 12;
    u8 c;

    while ((c = *str++) != 0) {
        layer->map[y][x] = (layer->charmap[c] + 0x200) | attr;
        x++;
    }
    layer->dirty = 1;
}

void Text_Printf(struct TextLayer *layer, s32 x, s32 y, const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    vsprintf(gPrintBuffer, fmt, ap);
    Text_Print(layer, x, y, 14, gPrintBuffer);
    va_end(ap);
}

void Text_LoadScreen(struct TextLayer *layer, const void *src)
{
    LZ77UnCompWram(src, layer);
    layer->dirty = 1;
}

void Text_LoadRows(struct TextLayer *layer, const void *src, u8 row)
{
    LZ77UnCompWram(src, (void *)layer->map[row]);
    layer->dirty = 1;
}

void Text_Save(struct TextLayer *layer)
{
    DmaSet(layer, layer->backup, 0x84000140);
}

void Text_Restore(struct TextLayer *layer)
{
    DmaSet(layer->backup, layer, 0x84000140);
    layer->dirty = 1;
}

void Text_Flush(struct TextLayer *layer)
{
    if (layer->dirty) {
        CpuFastSet(layer, (void *)(VRAM + 0x6800), 0x140);
        layer->dirty = 0;
    }
}

void Text_LoadFont(struct TextLayer *layer)
{
    LZ77UnCompWram(gBgTilesLz, gTileBuffer);
    DmaSet(gTileBuffer, VRAM, 0x84000400);
}

void Text_LoadSleepScreen(struct TextLayer *layer)
{
    LZ77UnCompWram(gSleepTilesLz, gTileBuffer);
    DmaSet(gTileBuffer, VRAM, 0x84000400);
    Text_LoadScreen(layer, gSleepScreenLz);
}

void Text_LoadPauseMenu(struct TextLayer *layer, u8 linked)
{
    if (linked == 0)
        Text_LoadRows(layer, gPauseSoloRowsLz, 5);
    else
        Text_LoadRows(layer, gPauseLinkRowsLz, 5);
}

void Text_LoadSelectPauseMenu(struct TextLayer *layer)
{
    Text_LoadScreen(layer, gSelectPauseScreenLz);
}
