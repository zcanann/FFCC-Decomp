#include "global.h"
#include "main.h"
#include "text.h"

/* 2bpp proportional font; offsets are relative to the start of the font. */
struct Font {
    u8 unk0[10];
    u16 split;      /* glyphs from here on use the second bit plane */
    u32 unkC;
    u32 widths;
    u32 palettes;
    u16 glyphWidth;
    u16 height;
    u32 glyphs;
    u8 unk20[14];
    u16 first;
    char map[4];    /* NUL-terminated list of the characters in glyph order */
};

/* Text background patterns and palettes; offsets are relative to the start. */
struct TextGfx {
    u32 unk0;
    u32 unk4;
    u32 unk8;
    u32 fills;
    u32 unk10;
    u32 unk14;
};

extern struct Font gFont;
extern struct TextGfx gTextGfx;
extern u8 gSpFontPalettes[];
extern u16 gSpTextPalettes[][16];

extern u8 sTextCanvas[];
extern u32 sTextX;
extern struct Font *sFont;
extern u8 sTextFill[];
extern s32 sTextFillOn;
extern u32 sNibbleMasks[];

void Text_Init(void)
{
    DmaClear32(0, 0, sTextCanvas, 0x800);
    sTextX = 0;
    sFont = &gFont;
    DmaClear32(0, 0, sTextFill, 0x80);
    sTextFillOn = 0;
}

void Text_SetFill(s32 on, s32 no)
{
    u8 *src;

    sTextFillOn = on;
    if (on != 0) {
        src = (u8 *)&gTextGfx;
        src += gTextGfx.fills;
        src += no * 128;
        DmaCopy32(3, src, sTextFill, 0x80);
    } else {
        DmaClear32(0, on, sTextFill, 0x80);
    }
}

void Text_Clear(void)
{
    s32 i;
    u8 *dst;
    s32 count;

    sTextX = 0;
    count = 16;
    if (sTextFillOn != 0) {
        dst = sTextCanvas;
        for (i = 0; i < count; i++) {
            DmaCopy32(0, sTextFill, dst, 0x80);
            dst += 0x80;
        }
    } else {
        DmaClear32(0, sTextFillOn, sTextCanvas, 0x800);
    }
}

s32 Text_Print(const char *str, s32 mode)
{
    u32 height;
    s32 shift;
    s32 rest;
    s32 over;
    s32 pad;
    s32 total;
    u32 len;
    s32 mapLen;
    char *map;
    u8 *widths;
    u8 *glyphs;
    s32 second;
    struct Font *font;
    const char *p;
    u32 i;
    s32 base;
    s32 limit;
    s32 k;
    u32 index;
    u32 *glyph;
    s32 w;
    s32 first;
    u32 *dst;
    u32 *dst2;
    u32 *dst3;
    u32 row;
    u32 bits;
    s32 v;
    s32 num;
    s32 rs;

    if (str == NULL)
        return 0;
    len = strlen(str);
    font = sFont;
    p = str;
    map = font->map;
    widths = (u8 *)font + font->widths;
    height = font->height;
    glyphs = (u8 *)font + font->glyphs;
    mapLen = strlen(map);
    total = 0;
    for (i = 0; i < len; i++) {
        base = font->first;
        limit = mapLen - base * 2;
        if (*p == ' ') {
            if (mode == TEXT_WIDTH)
                total += 6;
            else
                sTextX += 6;
        } else {
            for (k = 0; k < limit && map[base * 2 + k] != *p; k++)
                ;
            index = base + k;
            if (mode == TEXT_WIDTH) {
                total += widths[index];
            } else {
                if (mode == TEXT_CHAR)
                    return widths[index];
                second = index >= font->split;
                num = index;
                if (second)
                    num = index - font->split;
                glyph = (u32 *)(glyphs + (font->glyphWidth >> 1) * font->height * num);
                w = widths[index];
                pad = 0;
                if (mode != TEXT_DRAW && w <= 8) {
                    first = 9 - w;
                    pad = first >> 1;
                    sTextX += pad;
                }
                first = 8 - (sTextX & 7);
                if (first >= w) {
                    shift = first;
                    over = 0;
                    rest = 0;
                } else {
                    shift = first;
                    rest = w - first;
                    over = 0;
                    if (rest & 8) {
                        over = rest & 7;
                        rest = 8;
                    }
                }
                first &= 7;
                dst = (u32 *)&sTextCanvas[(sTextX >> 3) * 64];
                for (row = height; row != 0; row--) {
                    dst2 = dst + 16;
                    dst3 = dst2 + 16;
                    if (second)
                        bits = (glyph[0] & 0xCCCCCCCC) >> 2;
                    else
                        bits = glyph[0] & 0x33333333;
                    if (first != 0) {
                        rs = 8 - shift;
                        v = bits;
                        if (rest == 0)
                            v = sNibbleMasks[shift] & bits;
                        v = (v >> (shift * 4)) | (v << (32 - shift * 4));
                        *dst |= v & ~sNibbleMasks[rs];
                        if (rest != 0) {
                            *dst2 |= v & sNibbleMasks[rs];
                            if (rest > rs) {
                                if (second)
                                    bits = (glyph[1] & 0xCCCCCCCC) >> 2;
                                else
                                    bits = glyph[1] & 0x33333333;
                                v = bits;
                                if (over == 0)
                                    v = sNibbleMasks[rest - rs] & bits;
                                v = (v >> (shift * 4)) | (v << (32 - shift * 4));
                                *dst2 |= v & ~sNibbleMasks[rs];
                                if (over != 0)
                                    *dst3 |= v & sNibbleMasks[rs];
                            }
                        }
                    } else {
                        *dst |= bits;
                        if (rest != 0) {
                            if (second)
                                bits = (glyph[1] & 0xCCCCCCCC) >> 2;
                            else
                                bits = glyph[1] & 0x33333333;
                            *dst2 |= bits & sNibbleMasks[rest];
                        }
                    }
                    glyph += 2;
                    dst++;
                }
                if (mode != TEXT_DRAW)
                    sTextX += 9 - pad;
                else
                    sTextX += widths[index];
            }
        }
        p++;
    }
    if (mode == TEXT_WIDTH)
        return total;
    return 0;
}

void Text_CopyToVram(u32 dst, s32 n)
{
    s32 size = n * 64;

    DmaCopy16(0, sTextCanvas, dst, size);
}

void Text_LoadPalette(s32 no, s32 id, s32 base)
{
    u16 buf[16];
    u16 *tbl;
    u16 *pal;
    u16 *dst;
    u8 *src;
    s32 i;
    u16 c;

    if (gSpMode == 0) {
        tbl = (u16 *)&gTextGfx;
        tbl += 8;
    } else {
        tbl = gSpTextPalettes[0];
    }
    pal = tbl + base * 16;
    dst = (u16 *)(0x05000000 + no * 32);
    if (gSpMode == 0) {
        src = gFont.palettes + (u8 *)&gFont;
        src += id * 32;
    } else {
        src = gSpFontPalettes;
        src += id * 32;
    }
    DmaCopy16(3, src, buf, 32);
    for (i = 1; i <= 2; i++) {
        c = buf[i];
        buf[i | 4] = c;
        buf[i | 8] = c;
        buf[i | 12] = c;
    }
    buf[4] = pal[4];
    buf[8] = pal[8];
    buf[12] = pal[12];
    DmaCopy16(3, buf, dst, 32);
}

void Font_LoadPalette(u32 dst, s32 no)
{
    u8 *src;

    if (gSpMode == 0) {
        src = gFont.palettes + (u8 *)&gFont;
        src += no * 32;
    } else {
        src = gSpFontPalettes;
        src += no * 32;
    }
    DmaCopy16(3, src, dst, 32);
}

void Text_CopyFill(u32 dst)
{
    DmaCopy16(0, sTextFill, dst, 0x80);
}

void Text_SetX(s32 x)
{
    sTextX = x;
}

void Text_AddX(s32 dx)
{
    sTextX += dx;
}

u32 Text_GetX(void)
{
    return sTextX;
}

void Text_CopyToObj(s32 which, s32 n, s32 color)
{
    u8 buf[0x800];
    u8 *src;
    u8 *dst;
    u8 *p;
    s32 i;
    s32 size;
    u8 v;
    u8 hi;
    u8 lo;
    s32 t;

    src = sTextCanvas;
    memset(buf, 0, sizeof(buf));
    size = n * 128;
    if (color != 0) {
        for (i = 0, p = buf; i < size; p++, i++) {
            v = src[i];
            hi = v & 0xF0;
            if (hi != 0)
                t = hi + (color << 6);
            else
                t = 0;
            *p = t;
            lo = v & 0x0F;
            if (lo != 0)
                *p = (lo + (color << 2)) | t;
        }
    } else {
        memcpy(buf, src, size);
    }
    dst = (u8 *)0x06017880;
    if (which != 0)
        dst = (u8 *)0x06017380;
    src = buf;
    for (i = 0; i < n; i++) {
        DmaCopy16(0, src, dst, 32);
        src += 32;
        dst += 64;
        DmaCopy16(0, src, dst, 32);
        src += 32;
        dst -= 32;
        DmaCopy16(0, src, dst, 32);
        src += 32;
        dst += 64;
        DmaCopy16(0, src, dst, 32);
        src += 32;
        dst += 32;
    }
}

void Text_ClearObj(s32 which)
{
    void *dst;
    s32 n;

    if (which != 0) {
        dst = (void *)0x06017380;
        n = 40;
    } else {
        dst = (void *)0x06017880;
        n = 60;
    }
    n *= 32;
    DmaClear32(0, 0, dst, n);
}

void Text_SwapFill(void)
{
    u8 tmp[32];
    u8 *p;

    p = sTextFill;
    memcpy(tmp, p, 32);
    memcpy(p, p + 32, 32);
    memcpy(p + 32, tmp, 32);
    p += 64;
    memcpy(tmp, p, 32);
    memcpy(p, p + 32, 32);
    memcpy(p + 32, tmp, 32);
}
