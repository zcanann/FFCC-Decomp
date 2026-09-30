#include "gba_types.h"

#define DMA0 0x040000B0
#define DMA3 0x040000D4

#define DmaSet(dmaAddr, src, dst, cnt) \
    { \
        vu32 *dmaRegs = (vu32 *)(dmaAddr); \
        dmaRegs[0] = (u32)(src); \
        dmaRegs[1] = (u32)(dst); \
        dmaRegs[2] = (u32)(cnt); \
        dmaRegs[2]; \
    }

#define DmaCopy16(dmaAddr, src, dst, size) DmaSet(dmaAddr, src, dst, 0x80000000 | ((size) / 2))
#define DmaCopy32(dmaAddr, src, dst, size) DmaSet(dmaAddr, src, dst, 0x84000000 | ((size) / 4))

#define DmaClear32(dmaAddr, value, dst, size) \
    { \
        vu32 tmp = (vu32)(value); \
        DmaSet(dmaAddr, &tmp, dst, 0x85000000 | ((size) / 4)); \
    }

#define CpuFastCopy(src, dst, size) CpuFastSet(src, dst, ((size) / 4) & 0x1FFFFF)
#define CpuFastClear(value, dst, size) \
    { \
        vu32 tmp = (vu32)(value); \
        CpuFastSet((void *)&tmp, dst, 0x01000000 | (((size) / 4) & 0x1FFFFF)); \
    }

struct DataHeader {
    u32 unk0;
    u32 unk4;
    u32 unk8;
    u32 unkC;
    u32 unk10;
    u32 unk14;
};

struct Command {
    u8 unk0[12];
    u8 type;
    u8 data[0x3FF];
};

struct LinkWork {
    vu8 unk0;
    vu8 unk1;
    vu8 unk2;
    vu8 unk3;
    vu8 unk4;
    u8 unk5;
    u8 unk6;
    u8 unk7;
    u32 unk8;
    u32 unkC;
    u32 unk10;
    u8 unk14;
    u8 unk15;
    u8 unk16;
    u8 unk17;
    u32 unk18;
};

struct Font {
    u8 unk0[10];
    u16 split;
    u32 unkC;
    u32 widths;
    u32 palettes;
    u16 glyphWidth;
    u16 height;
    u32 glyphs;
    u8 unk20[14];
    u16 first;
    char map[4];
};

struct ResHeader {
    u32 unk0;
    u32 unk4;
    u16 unk8;
    u8 unkA;
    u8 unkB;
    u8 unkC;
    u8 unkD;
    u16 unkE;
    u8 *unk10;
    u8 *unk14;
    u8 *unk18;
    u8 *unk1C;
};

struct Oam {
    u32 attr01;
    u32 attr23;
};

struct OamAffine {
    u16 pad0[3];
    s16 pa;
    u16 pad1[3];
    s16 pb;
    u16 pad2[3];
    s16 pc;
    u16 pad3[3];
    s16 pd;
};

#define OAM_PRIORITY(oam) ((s32)(((oam)->attr23 >> 10) & 3))

union OamBuffer {
    struct Oam obj[128];
    struct OamAffine aff[32];
};

struct CellInfo {
    u8 shape;
    u8 unk1;
    u8 palette;
    u8 unk3;
    u8 unk4;
    u8 unk5;
    u16 unk6;
    u32 tiles;
};

extern struct Command lbl_030004A8;
extern struct LinkWork lbl_03000070;
extern u8 lbl_030008D8[];
extern u32 lbl_030010D8;
extern struct Font *lbl_030010DC;
extern u8 lbl_030010E0[];
extern s32 lbl_03001160;
extern union OamBuffer lbl_03001168[2];
extern s32 lbl_03001968;
extern struct CellInfo lbl_03001970[];
extern u8 lbl_03002070[];
extern struct ResHeader lbl_03002670;
extern s8 lbl_03002690;
extern s16 lbl_03002698[];
extern s16 lbl_030026D8[];
extern s8 lbl_03002718[];
extern u8 lbl_03002738[];
extern u8 lbl_03002AC4;
extern u16 lbl_03002AEC;
extern s16 lbl_0201CC7C[];
extern u32 lbl_0201CF14[];
extern s16 lbl_0202FA20[];
extern struct Font lbl_02034698;
extern struct DataHeader lbl_02036720;
extern u8 lbl_02036910[];
extern u16 lbl_02036A30[];
extern u16 lbl_02036E90[][16];
extern struct ResHeader lbl_02038000;
extern u8 lbl_02038020[];

void fn_02000C2C(s8 *x, s8 *y);
s16 fn_02000EC0(s16 a, s16 b);
s16 fn_02000EE8(s16 a);
u16 fn_02002130(s32 n, u8 *data, u16 *crc);
s32 fn_02002698(u32 packet);
void fn_02004740(u8 *data);
void fn_02004920(u8 *data);
void fn_02004A30(u8 *data);
void fn_02004AA0(u8 *data);
void fn_02004AC4(u8 *data);
void fn_02004B68(u8 *data);
void fn_02004C74(u8 *data);
void fn_02004E90(u8 *data);
void fn_02004ED4(u8 *data);
void fn_02004EE8(u8 *data);
void fn_02004F8C(u8 *data);
void fn_02004FE4(u8 *data);
void fn_02003C00(void);
void fn_02003D64(void);
void fn_02003E48(void);
void LZ77UnCompVram(const void *src, void *dest);
void CpuFastSet(const void *src, void *dest, u32 control);
void *memcpy(void *dst, const void *src, u32 n);
void *memset(void *dst, s32 c, u32 n);
u32 strlen(const char *s);

void fn_02002F0C(void)
{
    struct Command *cmd = &lbl_030004A8;

    if (cmd->type == 1)
        fn_02004740(cmd->data);
    else if (cmd->type == 3)
        fn_02004920(cmd->data);
    else if (cmd->type == 2)
        fn_02004A30(cmd->data);
    else if (cmd->type == 4)
        fn_02004AA0(cmd->data);
    else if (cmd->type == 5)
        fn_02004AC4(cmd->data);
    else if (cmd->type == 6)
        fn_02004B68(cmd->data);
    else if (cmd->type == 7)
        fn_02004C74(cmd->data);
    else if (cmd->type == 8)
        fn_02004E90(cmd->data);
    else if (cmd->type == 9)
        fn_02004ED4(cmd->data);
    else if (cmd->type == 10)
        fn_02004EE8(cmd->data);
    else if (cmd->type == 11)
        fn_02004F8C(cmd->data);
    else if (cmd->type == 12)
        fn_02004FE4(cmd->data);
}

u8 fn_02002FAC(void)
{
    return lbl_03000070.unk15;
}

s32 fn_02002FB8(u8 a, u8 b)
{
    u32 packet;
    u8 *p;

    packet = 0;
    p = (u8 *)&packet;
    p[0] = 12;
    p[1] = a;
    p[2] = b;
    return fn_02002698(packet);
}

s32 fn_02002FE4(u8 a, u8 b, u8 c)
{
    u32 packet;
    u8 *p;

    packet = 0;
    p = (u8 *)&packet;
    p[0] = 20;
    p[1] = a;
    p[2] = b;
    p[3] = c;
    return fn_02002698(packet);
}

s32 fn_02003014(u8 a, u8 b, u8 c, u32 d)
{
    u8 buf[9];
    u16 crc;
    u32 packet;
    u8 *p;
    u32 i;
    u16 sum;

    for (i = 0; i < 9; i++)
        buf[i] = 0;
    buf[0] = a;
    buf[1] = b;
    buf[2] = c;
    buf[3] = d >> 24;
    buf[4] = d >> 16;
    buf[5] = d >> 8;
    buf[6] = d;
    crc = 0xFFFF;
    sum = fn_02002130(7, buf, &crc);
    packet = 0;
    p = (u8 *)&packet;
    p[0] = 21;
    p[1] = sum >> 8;
    p[2] = sum;
    p[3] = buf[0];
    if (fn_02002698(packet) != 0)
        return -1;
    packet = 0;
    p[0] = 0x55;
    p[1] = buf[1];
    p[2] = buf[2];
    p[3] = buf[3];
    if (fn_02002698(packet) != 0)
        return -1;
    packet = 0;
    p[0] = 0x95;
    p[1] = buf[4];
    p[2] = buf[5];
    p[3] = buf[6];
    return fn_02002698(packet);
}

void fn_0200311C(u8 a, u8 b, u8 c)
{
    u32 packet;
    u8 *p = (u8 *)&packet;

    p[0] = 23;
    p[1] = a;
    p[2] = b;
    p[3] = c;
    while (fn_02002698(packet) != 0)
        ;
}

void fn_0200314C(u8 a, u32 b)
{
    u32 packet;
    u8 *p = (u8 *)&packet;

    p[0] = 26;
    p[1] = a;
    p[2] = b >> 24;
    p[3] = b >> 16;
    while (fn_02002698(packet) != 0)
        ;
    packet = 0;
    p[0] = 0x5A;
    p[1] = b >> 8;
    p[2] = b;
    while (fn_02002698(packet) != 0)
        ;
}

void fn_02003190(u8 *data)
{
    u16 crc;
    u32 packet;
    u8 *p;
    u16 sum;
    s32 i;

    crc = 0xFFFF;
    sum = fn_02002130(16, data, &crc);
    p = (u8 *)&packet;
    p[0] = 28;
    p[1] = sum >> 8;
    p[2] = sum;
    p[3] = *data++;
    while (fn_02002698(packet) != 0)
        ;
    for (i = 0; i < 5; i++) {
        packet = 0;
        p[0] = 0x5C;
        p[1] = *data++;
        p[2] = *data++;
        p[3] = *data++;
        while (fn_02002698(packet) != 0)
            ;
    }
}

void fn_02003200(u8 a)
{
    while (fn_02002FE4(2, a, 0) != 0)
        ;
}

void fn_0200321C(u8 a)
{
    while (fn_02002FE4(3, a, 0) != 0)
        ;
}

void fn_02003238(void)
{
    while (fn_02002FE4(4, 0, 0) != 0)
        ;
}

void fn_0200324C(void)
{
    while (fn_02002FE4(5, 0, 0) != 0)
        ;
}

void fn_02003260(s32 a, s32 b)
{
    while (fn_02002FE4(6, a, b) != 0)
        ;
}

void fn_0200327C(u8 *data)
{
    u16 crc;
    u32 packet;
    u8 *p;
    u16 sum;

    crc = 0xFFFF;
    sum = fn_02002130(4, data, &crc);
    p = (u8 *)&packet;
    p[0] = 29;
    p[1] = sum >> 8;
    p[2] = sum;
    p[3] = *data++;
    while (fn_02002698(packet) != 0)
        ;
    packet = 0;
    p[0] = 0x5D;
    p[1] = *data++;
    p[2] = data[0];
    p[3] = data[1];
    while (fn_02002698(packet) != 0)
        ;
}

void fn_020032DC(u8 a, u8 b)
{
    u32 packet;
    u8 *p = (u8 *)&packet;

    p[0] = 30;
    p[1] = a;
    p[2] = b;
    p[3] = 0;
    while (fn_02002698(packet) != 0)
        ;
}

void fn_0200330C(u8 a, u16 b)
{
    u32 packet;
    u8 *p = (u8 *)&packet;

    p[0] = 31;
    p[1] = a;
    *(u16 *)&p[2] = b;
    while (fn_02002698(packet) != 0)
        ;
}

void fn_02003338(void)
{
    DmaClear32(DMA0, 0, lbl_030008D8, 0x800);
    lbl_030010D8 = 0;
    lbl_030010DC = &lbl_02034698;
    DmaClear32(DMA0, 0, lbl_030010E0, 0x80);
    lbl_03001160 = 0;
}

void fn_02003394(s32 on, s32 no)
{
    u8 *src;

    lbl_03001160 = on;
    if (on != 0) {
        src = (u8 *)&lbl_02036720;
        src += lbl_02036720.unkC;
        src += no * 128;
        DmaCopy32(DMA3, src, lbl_030010E0, 0x80);
    } else {
        DmaClear32(DMA0, on, lbl_030010E0, 0x80);
    }
}

void fn_020033F4(void)
{
    s32 i;
    u8 *dst;

    lbl_030010D8 = 0;
    if (lbl_03001160 != 0) {
        dst = lbl_030008D8;
        for (i = 0; i < 16; i++) {
            DmaCopy32(DMA0, lbl_030010E0, dst, 0x80);
            dst += 0x80;
        }
    } else {
        DmaClear32(DMA0, lbl_03001160, lbl_030008D8, 0x800);
    }
}

s32 fn_02003464(const char *str, s32 mode)
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
    font = lbl_030010DC;
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
            if (mode == 2)
                total += 6;
            else
                lbl_030010D8 += 6;
        } else {
            for (k = 0; k < limit && map[base * 2 + k] != *p; k++)
                ;
            index = base + k;
            if (mode == 2) {
                total += widths[index];
            } else {
                if (mode == 3)
                    return widths[index];
                second = index >= font->split;
                num = index;
                if (second)
                    num = index - font->split;
                glyph = (u32 *)(glyphs + (font->glyphWidth >> 1) * font->height * num);
                w = widths[index];
                pad = 0;
                if (mode != 0 && w <= 8) {
                    first = 9 - w;
                    pad = first >> 1;
                    lbl_030010D8 += pad;
                }
                first = 8 - (lbl_030010D8 & 7);
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
                dst = (u32 *)&lbl_030008D8[(lbl_030010D8 >> 3) * 64];
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
                            v = lbl_0201CF14[shift] & bits;
                        v = (v >> (shift * 4)) | (v << (32 - shift * 4));
                        *dst |= v & ~lbl_0201CF14[rs];
                        if (rest != 0) {
                            *dst2 |= v & lbl_0201CF14[rs];
                            if (rest > rs) {
                                if (second)
                                    bits = (glyph[1] & 0xCCCCCCCC) >> 2;
                                else
                                    bits = glyph[1] & 0x33333333;
                                v = bits;
                                if (over == 0)
                                    v = lbl_0201CF14[rest - rs] & bits;
                                v = (v >> (shift * 4)) | (v << (32 - shift * 4));
                                *dst2 |= v & ~lbl_0201CF14[rs];
                                if (over != 0)
                                    *dst3 |= v & lbl_0201CF14[rs];
                            }
                        }
                    } else {
                        *dst |= bits;
                        if (rest != 0) {
                            if (second)
                                bits = (glyph[1] & 0xCCCCCCCC) >> 2;
                            else
                                bits = glyph[1] & 0x33333333;
                            *dst2 |= bits & lbl_0201CF14[rest];
                        }
                    }
                    glyph += 2;
                    dst++;
                }
                if (mode != 0)
                    lbl_030010D8 += 9 - pad;
                else
                    lbl_030010D8 += widths[index];
            }
        }
        p++;
    }
    if (mode == 2)
        return total;
    return 0;
}

void fn_020037A8(void *dst, s32 n)
{
    s32 size = n * 64;

    DmaCopy16(DMA0, lbl_030008D8, dst, size);
}

void fn_020037C8(s32 no, s32 id, s32 base)
{
    u16 buf[16];
    u16 *tbl;
    u16 *pal;
    u16 *dst;
    u8 *src;
    s32 i;

    if (lbl_03002AC4 == 0) {
        tbl = (u16 *)&lbl_02036720;
        tbl += 8;
    } else {
        tbl = lbl_02036E90[0];
    }
    pal = tbl + base * 16;
    dst = (u16 *)(0x05000000 + no * 32);
    if (lbl_03002AC4 == 0) {
        src = lbl_02034698.palettes + (u8 *)&lbl_02034698;
        src += id * 32;
    } else {
        src = lbl_02036910;
        src += id * 32;
    }
    DmaCopy16(DMA3, src, buf, 32);
    for (i = 1; i <= 2; i++) {
        buf[i | 4] = buf[i];
        buf[i | 8] = buf[i];
        buf[i | 12] = buf[i];
    }
    buf[4] = pal[4];
    buf[8] = pal[8];
    buf[12] = pal[12];
    DmaCopy16(DMA3, buf, dst, 32);
}

void fn_02003890(void *dst, s32 no)
{
    u8 *src;

    if (lbl_03002AC4 == 0) {
        src = lbl_02034698.palettes + (u8 *)&lbl_02034698;
        src += no * 32;
    } else {
        src = lbl_02036910;
        src += no * 32;
    }
    DmaCopy16(DMA3, src, dst, 32);
}

void fn_020038D8(void *dst)
{
    DmaCopy16(DMA0, lbl_030010E0, dst, 0x80);
}

void fn_020038F4(s32 x)
{
    lbl_030010D8 = x;
}

void fn_02003900(s32 dx)
{
    lbl_030010D8 += dx;
}

u32 fn_02003910(void)
{
    return lbl_030010D8;
}

void fn_0200391C(s32 which, s32 n, s32 color)
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

    src = lbl_030008D8;
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
        DmaCopy16(DMA0, src, dst, 32);
        src += 32;
        dst += 64;
        DmaCopy16(DMA0, src, dst, 32);
        src += 32;
        dst -= 32;
        DmaCopy16(DMA0, src, dst, 32);
        src += 32;
        dst += 64;
        DmaCopy16(DMA0, src, dst, 32);
        src += 32;
        dst += 32;
    }
}

void fn_02003A00(s32 which)
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
    DmaClear32(DMA0, 0, dst, n);
}

void fn_02003A48(void)
{
    u8 tmp[32];
    u8 *p;

    p = lbl_030010E0;
    memcpy(tmp, p, 32);
    memcpy(p, p + 32, 32);
    memcpy(p + 32, tmp, 32);
    p += 64;
    memcpy(tmp, p, 32);
    memcpy(p, p + 32, 32);
    memcpy(p + 32, tmp, 32);
}

void fn_02003AA0(void)
{
    s32 i;
    u8 *src;
    u32 ctrl;
    s32 size;

    lbl_03002690 = 0;
    fn_02003C00();
    lbl_03002690 = 1;
    fn_02003C00();
    lbl_03002690 = 0;
    for (i = 0; i < 32; i++) {
        lbl_03002698[i] = 0x100;
        lbl_030026D8[i] = 0x100;
        lbl_03002718[i] = 0;
    }
    DmaCopy32(DMA3, &lbl_03001168[lbl_03002690], 0x07000000, 0x400);
    if (lbl_03002AEC & 1) {
        src = lbl_02038020;
        LZ77UnCompVram(src, (void *)0x06010000);
        memcpy(&lbl_03002670, &lbl_02038000, 32);
        CpuFastClear(0, lbl_03001970, 0x700);
        src = lbl_03002670.unk10 + (u32)&lbl_02038000;
        size = lbl_03002670.unkD * 32;
        DmaCopy16(DMA3, src, lbl_03002070, size);
        src = lbl_03002AC4 == 0 ? lbl_03002070 : (u8 *)lbl_02036A30;
        DmaCopy16(DMA3, src, 0x05000200, size);
        src = lbl_03002670.unk14 + (u32)&lbl_02038000;
        size = lbl_03002670.unk8 >> 1;
        if (lbl_03002670.unk8 & 1)
            size++;
        if (size & 3)
            size += 4 - size % 4;
        size += lbl_03002670.unk1C - lbl_03002670.unk14;
        CpuFastCopy(src, lbl_03001970, size);
        memset(lbl_03002738, 0, 18);
    }
}

void fn_02003C00(void)
{
    struct Oam hide;
    s32 i;
    struct Oam *oam;

    hide.attr01 = 0x200;
    hide.attr23 = 0;
    for (i = 0; i < 128; i++) {
        oam = (struct Oam *)&((u8 *)lbl_03001168)[lbl_03002690 * 0x400 + i * 8];
        *oam = hide;
    }
    lbl_03001968 = 0;
}

void fn_02003C3C(s32 x, s32 y, s32 id, s32 frame, s32 pal, s32 prio, u32 flags)
{
    struct CellInfo *cell;
    s8 dx;
    s8 dy;
    u32 attr;
    u32 tile;
    u8 shape;
    s32 n;
    u32 (*oam)[256];

    if (!(lbl_03002AEC & 1))
        return;
    cell = &lbl_03001970[id];
    if ((u32)(id - 3) <= 17 && cell->unk5 == 0)
        return;
    fn_02000C2C(&dx, &dy);
    x += dx;
    y += dy;
    shape = cell->shape;
    attr = (y & 0xFF) | ((x & 0x1FF) << 16) | (((shape & 12) << 12) | (shape << 30));
    if (flags & 0x300)
        flags &= 0x3E000300;
    else
        flags &= 0x30000C00;
    attr |= flags;
    oam = (void *)lbl_03001168;
    n = lbl_03001968;
    oam[lbl_03002690][n * 2] = attr;
    tile = (cell->tiles - 0x06010000) >> 5;
    attr = tile + frame * (lbl_0202FA20[shape] / 32);
    attr |= (((cell->palette >> 4) + pal) << 12) | (prio << 10);
    oam[lbl_03002690][n * 2 + 1] = attr;
    lbl_03001968 = n + 1;
}

void fn_02003D60(void)
{
}

void fn_02003D64(void)
{
    struct Oam *oam;
    struct Oam tmp;
    s32 prio;
    s32 n;
    s32 j;

    if (!(lbl_03002AEC & 1))
        return;
    oam = (struct Oam *)&((u8 *)lbl_03001168)[lbl_03002690 * 0x400];
    n = 0;
    for (prio = 0; prio < 4; prio++) {
        for (; n < lbl_03001968; n++) {
            if (OAM_PRIORITY(&oam[n]) > prio)
                break;
        }
        if (n >= lbl_03001968)
            break;
        for (j = n + 1; j < lbl_03001968; j++) {
            if (OAM_PRIORITY(&oam[j]) <= prio) {
                tmp = oam[n];
                oam[n] = oam[j];
                oam[j] = tmp;
                n++;
            }
        }
        if (n >= lbl_03001968)
            break;
    }
}

void fn_02003E48(void)
{
    struct OamAffine *aff;
    s16 m[4];
    s32 i;

    aff = lbl_03001168[lbl_03002690].aff;
    for (i = 0; i < 32; i++) {
        m[0] = fn_02000EC0(lbl_0201CC7C[lbl_03002718[i] + 8], fn_02000EE8(lbl_03002698[i]));
        m[1] = fn_02000EC0(lbl_0201CC7C[lbl_03002718[i]], fn_02000EE8(lbl_03002698[i]));
        m[2] = fn_02000EC0(-lbl_0201CC7C[lbl_03002718[i]], fn_02000EE8(lbl_030026D8[i]));
        m[3] = fn_02000EC0(lbl_0201CC7C[lbl_03002718[i] + 8], fn_02000EE8(lbl_030026D8[i]));
        aff->pa = m[0];
        aff->pb = m[1];
        aff->pc = m[2];
        aff->pd = m[3];
        aff++;
    }
}

void fn_02003F74(s32 no, s32 angle, s32 sx, s32 sy)
{
    lbl_03002698[no] = sx;
    lbl_030026D8[no] = sy;
    lbl_03002718[no] = angle & 31;
}

void fn_02003FA0(void)
{
    struct Oam hide;
    s32 i;
    struct Oam *oam;

    hide.attr01 = 0x200;
    hide.attr23 = 0;
    fn_02003D64();
    for (i = lbl_03001968; i < 128; i++) {
        oam = (struct Oam *)&((u8 *)lbl_03001168)[lbl_03002690 * 0x400 + i * 8];
        *oam = hide;
    }
    fn_02003E48();
    lbl_03002690 ^= 1;
    fn_02003C00();
}

void fn_02003FF4(void)
{
    lbl_03001968 = 0;
}

u8 fn_02004000(s32 id)
{
    struct CellInfo *cell;

    if (!(lbl_03002AEC & 1))
        return 0;
    cell = lbl_03001970;
    cell += id;
    return cell->unk1;
}
