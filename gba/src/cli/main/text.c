#include "global.h"
#include "main.h"
#include "text.h"

/* 2bpp proportional font; offsets are relative to the start of the font. */
struct Font {
    u32 magic;      /* "PCD " */
    u32 version;    /* Resource format version. */
    u16 count;      /* glyphs in map */
    u16 split;      /* glyphs from here on use the second bit plane */
    u32 paletteCount;
    u32 widths;
    u32 palettes;
    u16 glyphWidth;
    u16 height;
    u32 glyphs;
    u8 unk20[8];
    u16 firstHiragana;
    u16 firstKatakana;
    u16 firstKanji;
    u16 first;
    char map[4];    /* NUL-terminated list of the characters in glyph order */
};

/* Text background patterns and palettes; offsets are relative to the start. */
struct TextGfx {
    u32 magic;      /* "FBD " */
    u32 version;    /* "0.10" */
    u32 count;      /* fill patterns, and palettes */
    u32 fills;
    u16 palettes[1][16];
};

extern struct Font gFont;
extern struct TextGfx gTextGfx;
extern u8 gSpFontPalettes[];
extern u16 gSpTextPalettes[][16];

static u8 sTextCanvas[0x800];
static u32 sTextX;
static struct Font *sFont;
static u8 sTextFill[0x80];
static s32 sTextFillOn;
extern u32 gNibbleMasks[];

#if defined(VERSION_GCCJGC)
#define TEXT_MASK(width) (*(gNibbleMasks + (width) - 1))
#else
#define TEXT_MASK(width) gNibbleMasks[width]
#endif

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

/*
 * --INFO--
 * PAL Address: 0x02003464
 * PAL Size: 836b
 * EN Address: 0x02003464
 * EN Size: 834b
 * JP Address: 0x020035A4
 * JP Size: 1030b
 */
s32 Text_Print(const char *str, s32 mode)
{
#if defined(VERSION_GCCJGC)
    u32 i;
#endif
    s32 height;
    s32 shift;
    s32 rest;
    s32 over;
    s32 pad;
    s32 total;
    u32 len;
    s32 mapLen;
    u32 *dst3;
#if defined(VERSION_GCCJGC)
    const char *p;
#endif
    char *map;
    u8 *widths;
    u8 *glyphs;
    u8 second;
    struct Font *font;
#if !defined(VERSION_GCCJGC)
    u32 i;
    const char *p;
#endif
    u32 index;
    u32 *glyph;
    s32 w;
    s32 m;
    u32 *dst;
    u32 *dst2;
    s32 k;
    u32 bits;
    s32 v;
    s32 rs;
#if defined(VERSION_GCCJGC)
    s32 group;
    u16 *wideMap;
    u32 code;
#endif

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
    for (i = 0; i < len; i++, p++) {
#if defined(VERSION_GCCJGC)
        if ((s8)*p >= 0) {
            group = 0;
            index = font->first;
            m = mapLen - index * 2;
        } else if (*p == 0x81) {
            group = 1;
            index = 0;
            m = font->firstHiragana;
        } else if (*p == 0x82) {
            group = 2;
            index = font->firstHiragana;
            m = font->firstKatakana - index;
        } else if (*p == 0x83) {
            group = 3;
            index = font->firstKatakana;
            m = font->firstKanji ? font->firstKanji : font->first;
            m -= index;
        } else {
            group = 4;
            index = font->firstKanji;
            m = font->first - index;
        }
        wideMap = (u16 *)(map + index * 2);
        if (group != 0) {
            if (*p == 0x81 && p[1] == 0x40) {
                if (mode == TEXT_WIDTH)
                    total += 7;
                else
                    sTextX += 7;
                p++;
                i++;
                continue;
            }
            k = 0;
            if (k < m) {
                do {
                    code = *wideMap;
                    if ((code & 0xFF) == *p && (code >> 8) == p[1])
                        break;
                    k++;
                    wideMap++;
                } while (k < m);
            }
            index += k;
            p++;
            i++;
        } else {
            if (*p == ' ') {
                if (mode == TEXT_WIDTH)
                    total += 7;
                else
                    sTextX += 7;
                continue;
            }
            for (k = 0; k < m && *((char *)wideMap + k) != *p; k++)
                ;
            index += k;
        }
#else
        index = font->first;
        m = mapLen - index * 2;
        if (*p == ' ') {
            if (mode == TEXT_WIDTH)
                total += 6;
            else
                sTextX += 6;
        } else {
            w = index * 2;
            for (k = 0; k < m && *(map + w + k) != *p; k++)
                ;
            index += k;
#endif
            if (mode == TEXT_WIDTH) {
                total += widths[index];
            } else {
                if (mode == TEXT_CHAR)
                    return widths[index];
                second = index >= font->split;
                w = index;
                if (second)
                    w = index - font->split;
                glyph = (u32 *)(glyphs + (font->glyphWidth >> 1) * font->height * w);
                w = widths[index];
                pad = 0;
                if (mode != TEXT_DRAW && w <= 8) {
                    m = 9 - w;
                    pad = m >> 1;
                    sTextX += pad;
                }
                m = 8 - (sTextX & 7);
                if (m >= w) {
                    shift = m;
                    over = 0;
                    rest = 0;
                } else {
                    shift = m;
                    rest = w - m;
                    over = 0;
                    if (rest & 8) {
                        over = rest & 7;
                        rest = 8;
                    }
                }
                m &= 7;
                w = sTextX >> 3;
                dst = (u32 *)&sTextCanvas[w * 64];
                dst2 = dst + 16;
                dst3 = dst2 + 16;
                for (k = 0; k < height; k++, glyph += 2, dst++, dst2++, dst3++) {
                    if (second)
                        bits = (glyph[0] & 0xCCCCCCCC) >> 2;
                    else
                        bits = glyph[0] & 0x33333333;
                    if (m != 0) {
                        rs = 8 - shift;
                        v = bits;
                        if (rest == 0)
                            v = TEXT_MASK(shift) & bits;
                        v = (v >> (shift * 4)) | (v << (32 - shift * 4));
                        *dst |= v & ~TEXT_MASK(rs);
                        if (rest != 0) {
                            *dst2 |= v & TEXT_MASK(rs);
                            if (rest > rs) {
                                if (second)
                                    bits = (glyph[1] & 0xCCCCCCCC) >> 2;
                                else
                                    bits = glyph[1] & 0x33333333;
                                v = bits;
                                if (over == 0)
                                    v = TEXT_MASK(rest - rs) & bits;
                                v = (v >> (shift * 4)) | (v << (32 - shift * 4));
                                *dst2 |= v & ~TEXT_MASK(rs);
                                if (over != 0)
                                    *dst3 |= v & TEXT_MASK(rs);
                            }
                        }
                    } else {
                        *dst |= bits;
                        if (rest != 0) {
                            if (second)
                                bits = (glyph[1] & 0xCCCCCCCC) >> 2;
                            else
                                bits = glyph[1] & 0x33333333;
                            *dst2 |= bits & TEXT_MASK(rest);
                        }
                    }
                }
                if (mode != TEXT_DRAW)
                    sTextX += 9 - pad;
                else
                    sTextX += widths[index];
            }
#if !defined(VERSION_GCCJGC)
        }
#endif
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
    u8 *src;
    s32 i;

    if (gSpMode == 0) {
        tbl = (u16 *)&gTextGfx;
        tbl += 8;
        pal = tbl + base * 16;
    } else {
        tbl = gSpTextPalettes[0];
        pal = tbl + base * 16;
    }
    tbl = (u16 *)(0x05000000 + no * 32);
    if (gSpMode == 0) {
        src = gFont.palettes + (u8 *)&gFont;
        src += id * 32;
    } else {
        src = gSpFontPalettes;
        src += id * 32;
    }
    DmaCopy16(3, src, buf, 32);
    for (i = 1; i <= 2; i++) {
        *(buf + (i | 4)) = *(buf + i);
        *(buf + (i | 8)) = *(buf + i);
        *(buf + (i | 12)) = *(buf + i);
    }
    buf[4] = pal[4];
    buf[8] = pal[8];
    buf[12] = pal[12];
    DmaCopy16(3, buf, tbl, 32);
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
        i = 0;
        if (i < size) {
            p = buf;
            do {
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
                p++;
                i++;
            } while (i < size);
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
