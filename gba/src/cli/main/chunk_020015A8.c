#include "gba_types.h"

#define REG_BLDCNT (*(vu16 *)0x04000050)
#define REG_BLDALPHA (*(vu16 *)0x04000052)
#define REG_RCNT (*(vu16 *)0x04000134)
#define REG_JOYCNT (*(vu16 *)0x04000140)
#define REG_JOY_RECV (*(vu32 *)0x04000150)
#define REG_JOY_TRANS (*(vu32 *)0x04000154)
#define REG_JOYSTAT (*(vu16 *)0x04000158)
#define REG_IE (*(vu16 *)0x04000200)
#define REG_IF (*(vu16 *)0x04000202)
#define REG_IME (*(vu16 *)0x04000208)

#define REG_DMA0 ((vu32 *)0x040000B0)
#define REG_DMA3 ((vu32 *)0x040000D4)

#define DmaSet(regs, src, dest, control) \
    {                                    \
        vu32 *dmaRegs = regs;            \
        dmaRegs[0] = (vu32)(src);        \
        dmaRegs[1] = (vu32)(dest);       \
        dmaRegs[2] = (vu32)(control);    \
        dmaRegs[2];                      \
    }

#define DmaCopy16(regs, src, dest, size) \
    DmaSet(regs, src, dest, 0x80000000 | ((size) >> 1))

#define DmaFill16(regs, value, dest, size)                     \
    {                                                          \
        vu16 tmp = (vu16)(value);                              \
        DmaSet(regs, &tmp, dest, 0x81000000 | ((size) >> 1)); \
    }

struct BgHeader {
    u32 unk0;
    u32 unk4;
    u32 tileOffset;
    u32 mapOffset;
    u32 unk10;
    u16 width;
    u16 height;
    u32 unk18;
    u32 unk1C;
    u16 palette[16];
};

struct MapInfo {
    s16 x;
    s16 y;
    u32 dataOffset;
    u8 rowLen[1];
};

struct LinkWork {
    vu8 unk0 : 8;
    vu8 unk1 : 8;
    vu8 unk2 : 8;
    vu8 unk3 : 8;
    vu8 unk4 : 8;
    u8 unk5;
    u8 unk6;
    u8 unk7;
    vu32 unk8;
    u32 unkC;
    u32 unk10;
    u8 unk14;
    u8 unk15;
    u8 unk16;
    u8 unk17;
    u32 unk18;
};

struct Transfer {
    u32 pending;
    u16 crc;
    u16 size;
    u16 pos;
    u8 total;
    u8 count;
    u8 data[0x400];
};

struct Unk03000030 {
    u16 unk0;
    u16 unk2;
    u16 unk4;
    u16 unk6;
};

extern u16 lbl_03002AEC;
extern u8 lbl_03002AFC;
extern s8 lbl_03002AE4;
extern s8 lbl_03002AF4;
extern s8 lbl_03002AF0;
extern u8 lbl_03000018[];
extern struct Unk03000030 lbl_03000030;
extern struct BgHeader lbl_02038000;
extern u8 lbl_02038008[];
extern u8 lbl_02038020[];
extern struct BgHeader *lbl_03000054;
extern struct MapInfo *lbl_03000058;
extern u8 *lbl_0300005C;
extern u16 *lbl_03000060;
extern s32 lbl_03000064;
extern s32 lbl_03000068;
extern u16 lbl_0300006C;
extern u16 lbl_0300006E;
extern struct LinkWork lbl_03000070;
extern u16 lbl_0201CD10[];
extern u32 lbl_0201CF10;
extern u32 lbl_0300008C;
extern s32 lbl_03000190;
extern u32 lbl_03000090[];
extern s32 lbl_03000298;
extern u32 lbl_03000198[];
extern u32 lbl_030002A0[];
extern s32 lbl_030004A0;
extern s32 lbl_030004A4;
extern struct Transfer lbl_030004A8;
extern u16 lbl_030008B4[];
extern u8 lbl_030008B8;
extern u32 lbl_030008C0[];
extern u32 lbl_030008CC;
extern u8 lbl_030008D0;
extern u32 lbl_030008D4;
extern u8 lbl_030029A4;
extern u8 lbl_03002ACC;
extern u8 lbl_030032F0;
extern u8 lbl_030032F8;
extern u32 lbl_03003090;
extern u8 lbl_0300309C;
extern u32 lbl_03003094;
extern u8 lbl_03002AE8;
extern u8 lbl_03002AE0;

void LZ77UnCompVram(const void *src, void *dest);
void LZ77UnCompWram(const void *src, void *dest);
void fn_020045F4(s16 *, s16 *);
void fn_02000AD4(s32, u16, u16);
void fn_020022BC(void);
void fn_02001578(void);
void fn_0201C734(void);
void *memset(void *, s32, u32);
void m4aMPlayAllStop(void);
s32 fn_02002538(void);
s32 fn_02002460(u32);
void fn_0200242C(void);
void fn_02002620(void);
s32 fn_02002698(u32);
void fn_02002714(void);
void fn_0200275C(void);
void fn_02002F0C(void);
s32 fn_0200108C(u32);
s32 fn_0200110C(u32, u8 *);
void fn_02001438(s32, s32);
void fn_020045B4(s32, s32);
void fn_02000A74(void);
void fn_0200469C(u32 *);
s32 fn_02002FE4(s32, s32, s32);
void fn_020046FC(u32 *);
void fn_0200471C(u32 *);
void fn_020048B4(u32 *);
void fn_020049B8(u32 *);
void fn_02004D88(u32);
void fn_02004F1C(u32);
void fn_02004F54(u32);
void fn_02009ED4(u32);
void fn_02005010(u32);
void fn_02005024(u32);
void fn_02005038(u32);
void fn_0200508C(u32);
void fn_020050B8(void);
void fn_020050D4(u32);
void fn_02004514(u32);
void fn_02004AB4(u32);
void fn_02008F48(u32);
void fn_0200911C(u32);
void fn_02004E38(u32);
void fn_02004BB8(u32);
void fn_02004BD4(u32);
void fn_02004C1C(u32);
void fn_02004FC0(u32);

void fn_020015A8(arg0)
u8 arg0;
{
    lbl_03002AEC |= 0x8000;
    lbl_03002AFC = arg0;
    lbl_03002AE4 = 0;
    lbl_03002AF4 = 0;
}

void fn_020015DC(void)
{
    if (lbl_03002AF4 != 0 && lbl_03002AF4 < 30)
        lbl_03002AE4++;
}

s32 fn_02001604(void)
{
    s32 n;

    if (lbl_03002AF4 == 0)
        n = 0;
    else
        n = lbl_03002AE4;
    return n >= 30;
}

u8 *fn_02001634(void)
{
    return lbl_03000018;
}

void fn_0200163C(void)
{
    lbl_03002AEC &= ~8;
    lbl_03000030.unk6 = 0;
    lbl_03002AEC &= ~4;
    lbl_03000030.unk4 = 0;
}

void fn_0200166C(void)
{
    if (++lbl_03002AF0 > 10)
        fn_020022BC();
}

void fn_0200168C(u8 *data, void *tileDest, u16 *mapDest, u16 *palDest, s32 tileBase)
{
    struct BgHeader *hdr = (struct BgHeader *)data;
    u16 buf[0x258];
    u16 *pal;
    u16 *src;
    u16 *dst;
    s32 w;
    s32 h;
    s32 i;
    s32 j;

    LZ77UnCompVram(data + hdr->tileOffset, tileDest);
    LZ77UnCompWram(data + hdr->mapOffset, buf);
    pal = hdr->palette;
    h = hdr->height >> 3;
    w = hdr->width >> 3;
    src = buf;
    dst = mapDest;
    for (i = 0; i < h; i++) {
        DmaCopy16(REG_DMA0, src, dst, w * sizeof(u16));
        src += w;
        dst += 32;
    }
    if (pal != (u16 *)(data + hdr->tileOffset))
        DmaCopy16(REG_DMA3, pal, palDest, 0x20);
    if (tileBase == 0 && palDest == (u16 *)0x05000020)
        return;
    if (palDest != (u16 *)0x05000020)
        tileBase |= (((s32)palDest - 0x05000020) / 32) << 12;
    dst = mapDest;
    for (i = 0; i < h; i++) {
        for (j = 0; j < w; j++)
            dst[j] += tileBase;
        dst += 32;
    }
}

void fn_020017C8(struct BgHeader *hdr)
{
    LZ77UnCompVram((u8 *)hdr + hdr->tileOffset, (void *)0x0600F000);
}

void fn_020017DC(void)
{
    DmaFill16(REG_DMA0, 0x1111, (void *)0x06008000, 0x20);
    DmaFill16(REG_DMA0, 0x1000, (void *)0x0600F000, 0x800);
}

void fn_02001828(void)
{
    u16 tmp;
    struct BgHeader *hdr;
    struct MapInfo *info;

    if (lbl_03002AEC & 2) {
        info = (struct MapInfo *)lbl_02038020;
        LZ77UnCompVram(info, (void *)0x06008000);
        lbl_03000054 = hdr = &lbl_02038000;
        info = (struct MapInfo *)((u8 *)hdr + hdr->mapOffset);
        lbl_03000058 = info;
        lbl_0300005C = lbl_02038008 + hdr->mapOffset;
        lbl_03000060 = (u16 *)((u8 *)info + info->dataOffset);
        tmp = 0x1000;
        DmaSet(REG_DMA0, &tmp, (void *)0x0600F000, 0x81000400);
        fn_02000AD4(15, 0, 0);
        lbl_0300006C = 0;
        lbl_0300006E = 0;
    }
}

void fn_020018C8(void)
{
    u16 pal[16];
    s32 i;

    for (i = 0; i < 16; i++)
        pal[i] = 0;
    pal[1] = pal[5] = pal[9] = 0;
    pal[2] = pal[6] = pal[10] = 0x7FFF;
    DmaCopy16(REG_DMA0, pal, (void *)0x05000020, sizeof(pal));
    for (i = 0; i < 16; i++)
        pal[i] = 0;
    pal[5] = pal[6] = 0;
    pal[9] = pal[10] = 0x7FFF;
    DmaCopy16(REG_DMA0, pal, (void *)0x05000040, sizeof(pal));
}

void fn_0200194C(s32 arg0)
{
    u16 mode = 0;

    if (arg0)
        mode = 0x40;
    REG_BLDCNT = mode | 0x1F04;
    REG_BLDALPHA = 0x0808;
}

void fn_0200197C(void)
{
    u16 out[24];
    u16 line[256];
    s16 x;
    s16 y;
    s16 tx;
    s16 ty;
    s32 row;
    s32 col;
    s32 dst;
    u16 *data;
    s16 mapW;
    s16 mapH;
    s32 sum;
    s32 i;
    s32 k;
    s32 m;
    s32 n;
    s32 r;
    s32 c;
    u16 code;
    s32 cnt;
    u16 v;
    s16 len;

    if (!(lbl_03002AEC & 2))
        return;
    fn_020045F4(&x, &y);
    lbl_03000064 = x - 80;
    lbl_03000068 = y - 64;
    tx = (lbl_03000064 - lbl_03000058->x) >> 3;
    ty = (lbl_03000068 - lbl_03000058->y) >> 3;
    lbl_0300006C = lbl_03000064 - lbl_03000058->x;
    lbl_0300006E = lbl_03000068 - lbl_03000058->y;
    fn_02000AD4(4, lbl_0300006C, lbl_0300006E);
    row = (s16)((ty - 1) % 32);
    if (row < 0)
        row += 32;
    dst = 0x0600F000 + row * 64;
    col = (s16)((tx - 1) % 32);
    if (col < 0)
        col += 32;
    dst += col * 2;
    mapW = lbl_03000054->width >> 3;
    mapH = lbl_03000054->height >> 3;
    sum = 0;
    for (i = 0; i < ty - 1 && i < mapH; i++)
        sum += lbl_0300005C[i];
    data = lbl_03000060 + sum;
    for (i = -1; i <= 16; i++) {
        r = i + ty;
        if (r >= 0 && r < mapH) {
            n = 0;
            for (k = 0; k < lbl_0300005C[r]; k++) {
                code = data[k];
                if (code & 0x8000) {
                    cnt = code & 0x3FF;
                    v = (code >> 10) & 3;
                    for (; cnt != 0; cnt--)
                        line[n++] = v | 0x1000;
                } else {
                    line[n++] = code;
                }
            }
            data += lbl_0300005C[i + ty];
        }
        for (m = -1; m <= 21; m++) {
            c = m + tx;
            if (r < 0 || c < 0 || r >= mapH || c >= mapW)
                out[m + 1] = 0x1000;
            else
                out[m + 1] = line[c];
        }
        if (col + 23 <= 32) {
            DmaCopy16(REG_DMA0, out, dst, 23 * 2);
        } else {
            len = 32 - col;
            DmaCopy16(REG_DMA0, out, dst, len * 2);
            DmaCopy16(REG_DMA0, out + len, dst - col * 2, (23 - len) * 2);
        }
        dst += 64;
        if (dst > 0x0600F7FF)
            dst -= 0x800;
    }
}

void fn_02001C44(s32 dx, s32 dy)
{
    u16 out[24];
    u16 line[256];
    s16 tx;
    s16 ty;
    s16 mapW;
    s16 mapH;
    u16 oldX;
    u16 oldY;
    s32 dst;
    u16 *data;
    s32 sum;
    s32 i;
    s32 k;
    s32 m;
    s32 n;
    s32 c;
    s32 r;
    s32 row;
    s32 col;
    u32 u;
    s32 fine;
    s32 oldFine;
    u16 code;
    s32 cnt;
    u16 v;

    if (!(lbl_03002AEC & 2))
        return;
    if (dx == 0 && dy == 0)
        return;
    lbl_03000064 += dx;
    lbl_03000068 += dy;
    oldX = lbl_0300006C;
    oldY = lbl_0300006E;
    lbl_0300006C = oldX + dx;
    lbl_0300006E += dy;
    fn_02000AD4(4, lbl_0300006C, lbl_0300006E);
    tx = (lbl_03000064 - lbl_03000058->x) >> 3;
    ty = (lbl_03000068 - lbl_03000058->y) >> 3;
    mapW = lbl_03000054->width >> 3;
    mapH = lbl_03000054->height >> 3;

    fine = lbl_0300006C & 7;
    oldFine = oldX & 7;
    if (dx != 0 && ((oldFine <= 3 && fine > 3) || (oldFine > 4 && fine <= 4))) {
        if (dx < 0)
            c = tx - 1;
        else
            c = tx + 21;
        sum = 0;
        for (i = 0; i < ty - 1 && i < mapH; i++)
            sum += lbl_0300005C[i];
        data = lbl_03000060 + sum;
        row = (ty - 1) % 32;
        if (row < 0)
            row += 32;
        dst = 0x0600F000 + row * 64;
        col = c % 32;
        if (col < 0)
            col += 32;
        dst += col * 2;
        for (i = -1; i <= 16; i++) {
            r = i + ty;
            if (r >= 0 && r < mapH) {
                n = 0;
                for (k = 0; k < lbl_0300005C[i + ty]; k++) {
                    code = data[k];
                    if (code & 0x8000) {
                        cnt = code & 0x3FF;
                        v = (code >> 10) & 3;
                        n += cnt;
                        if (n > c) {
                            line[0] = v | 0x1000;
                            break;
                        }
                    } else {
                        if (n == c) {
                            line[0] = code;
                            break;
                        }
                        n++;
                    }
                }
                data += lbl_0300005C[i + ty];
            }
            if (r < 0 || c < 0 || r >= mapH || c >= mapW)
                *(u16 *)dst = 0x1000;
            else
                *(u16 *)dst = line[0];
            dst += 64;
            if (dst > 0x0600F7FF)
                dst -= 0x800;
        }
    }

    fine = lbl_0300006E & 7;
    oldFine = oldY & 7;
    if (dy != 0 && ((oldFine <= 3 && fine > 3) || (oldFine > 4 && fine <= 4))) {
        if (dy < 0)
            r = ty - 1;
        else
            r = ty + 16;
        sum = 0;
        for (i = 0; i < r && i < mapH; i++)
            sum += lbl_0300005C[i];
        data = lbl_03000060 + sum;
        if (r >= 0 && r < mapH) {
            n = 0;
            for (k = 0; k < lbl_0300005C[r]; k++) {
                code = data[k];
                if (code & 0x8000) {
                    cnt = code & 0x3FF;
                    v = (code >> 10) & 3;
                    for (; cnt != 0; cnt--)
                        line[n++] = v | 0x1000;
                } else {
                    line[n++] = code;
                }
            }
        } else {
            for (u = 0; u < 256; u++)
                line[u] = 0x1000;
        }
        for (m = -1; m <= 21; m++) {
            c = m + tx;
            if (r < 0 || c < 0 || r >= mapH || c >= mapW)
                out[m + 1] = 0x1000;
            else
                out[m + 1] = line[c];
        }
        row = r % 32;
        if (row < 0)
            row += 32;
        dst = 0x0600F000 + row * 64;
        col = (tx - 1) % 32;
        if (col < 0)
            col += 32;
        dst += col * 2;
        if (col + 23 <= 32) {
            DmaCopy16(REG_DMA0, out, dst, 23 * 2);
        } else {
            n = 32 - col;
            DmaCopy16(REG_DMA0, out, dst, n * 2);
            DmaCopy16(REG_DMA0, out + n, dst - col * 2, (23 - n) * 2);
        }
    }
}

u32 fn_020020C0(u32 data)
{
    u32 crc = 0;
    u32 bit;
    u32 i;

    for (i = 2; i != 0; i--) {
        for (bit = 0x80; bit != 0; bit >>= 1) {
            crc <<= 1;
            if (data & bit) {
                if (crc & 0x100)
                    crc ^= 0xCC;
                else
                    crc++;
            } else if (crc & 0x100) {
                crc ^= 0xCD;
            }
        }
        data >>= 8;
    }
    for (i = 0; i < 8; i++) {
        crc <<= 1;
        if (crc & 0x100)
            crc ^= 0xCD;
    }
    return crc & 0xFF;
}

u16 fn_02002130(s32 n, u8 *data, u16 *crc)
{
    while (--n >= 0) {
        *crc = (*crc << 8) ^ lbl_0201CD10[(*crc >> 8) ^ *data++];
    }
    return ~*crc;
}

void fn_02002170(void)
{
    u16 stat = REG_JOYCNT;

    if (((stat & 4) && !fn_02002538()) || ((stat & 2) && !fn_02002460(REG_JOY_RECV))) {
        REG_JOYSTAT = 0;
        lbl_03000070.unk0 = 0;
        lbl_03000070.unk1 = 0;
        fn_0200242C();
    }
    if (stat & 1) {
        fn_0200242C();
        if (lbl_03000070.unk6 <= 2 && ++lbl_03000070.unk5 >= 30)
            fn_0201C734();
        lbl_03000070.unk6 = 0;
    } else if (lbl_03000070.unk6 >= 2) {
        lbl_03000070.unk5 = 0;
    } else {
        lbl_03000070.unk6++;
    }
    REG_JOYCNT = stat;
    lbl_03000070.unk2 = 0;
}

void fn_02002218(void)
{
    u16 ime = REG_IME;
    u32 i;

    REG_IME = 0;
    for (i = 0; i < sizeof(lbl_03000070); i++)
        ((u8 *)&lbl_03000070)[i] = 0;
    lbl_03000070.unk4 = 0xFF;
    fn_020022BC();
    REG_IE |= 0x80;
    if (*(u8 *)0x020000C4 != 0) {
        lbl_03000070.unk10 = lbl_03000070.unk8 = *(u32 *)0x020000AC;
        lbl_03000070.unk14 = *(u8 *)0x020000C4;
        lbl_03000070.unk15 = *(u8 *)0x020000C5;
        lbl_03000070.unk16 = 1;
        lbl_03000070.unk18 = *(u32 *)0x020000C8;
    } else {
        lbl_03000070.unk8 = *(u32 *)0x080000AC;
        lbl_03000070.unk10 = lbl_0201CF10;
    }
    lbl_03002ACC = 0;
    lbl_030029A4 = 0;
    REG_IME = ime;
}

void fn_020022BC(void)
{
    u16 ime = REG_IME;
    s32 i;

    REG_IME = 0;
    if (lbl_03000070.unk4 == 0)
        REG_RCNT = 0x8000;
    REG_RCNT = 0xC000;
    REG_JOYSTAT = 0;
    REG_JOY_RECV;
    REG_JOY_TRANS = 0;
    REG_JOYCNT = 0x47;
    REG_IF = 0x80;
    lbl_03000070.unk2 = 0;
    lbl_03000070.unk0 = 0;
    lbl_03000070.unk1 = 0;
    lbl_03000070.unk4 = 0;
    lbl_03000070.unk5 = 0;
    lbl_03000070.unk6 = 0;
    lbl_0300008C = 0;
    fn_02002620();
    for (i = 0; i < 2; i++)
        lbl_030008B4[i] = 0;
    lbl_030008B8 = 0;
    for (i = 0; i < 3; i++)
        lbl_030008C0[i] = 0;
    lbl_03002AEC &= ~0xC;
    lbl_030032F8 = 4;
    lbl_03003090 = 13;
    lbl_0300309C = 0;
    lbl_030008CC = 0;
    lbl_030008D0 = 0;
    lbl_030008D4 = 0;
    lbl_03002AF0 = 0;
    fn_02001578();
    REG_IME = ime;
    m4aMPlayAllStop();
}

s32 fn_020023E4(void)
{
    s32 ret;
    vu16 ime;

    if (lbl_03000070.unk2 > 10) {
        lbl_03000070.unk3 = 0xFF;
        fn_020022BC();
        ret = -1;
    } else {
        ime = REG_IME;
        REG_IME = 0;
        lbl_03000070.unk2++;
        REG_IME = ime;
        ret = 0;
    }
    return ret;
}

void fn_0200242C(void)
{
    REG_JOY_RECV;
    REG_JOY_TRANS = lbl_03000070.unk8;
    REG_JOYSTAT = 0x20;
    lbl_03000070.unk0 = 0;
    lbl_03000070.unk1 = 1;
    lbl_030029A4 = 0;
}

s32 fn_02002460(u32 data)
{
    u8 *recv = (u8 *)&data;
    u32 *word;
    u32 pkt;
    u8 *p;

    if (lbl_03000070.unk0 == 0) {
        lbl_03002AEC &= ~0xC;
        if (lbl_03000070.unk1 == 2) {
            lbl_03000070.unkC = data;
            p = (u8 *)&pkt;
            p[0] = 1;
            p[1] = (lbl_03000070.unk14 << 6) | (lbl_03000070.unk16 << 4) | lbl_03000070.unk15;
            p[2] = 0;
            p[3] = 0;
            REG_JOY_TRANS = pkt;
            REG_JOYSTAT = 0x20;
            lbl_03000070.unk1 = 3;
        } else {
            word = (u32 *)recv;
            if (lbl_03000070.unk1 == 5) {
                if (lbl_03000070.unk18 == data)
                    lbl_03000070.unk17 = 0;
                else
                    lbl_03000070.unk17 = 1;
                lbl_03000070.unk18 = *word;
                REG_JOYSTAT = 0x20;
                lbl_03000070.unk1 = 6;
            } else if (lbl_03000070.unk1 == 6) {
                lbl_03000070.unk15 = recv[1] & 0xF;
                REG_JOYSTAT = 0;
                lbl_03000070.unk0 = 0xFF;
                lbl_03000070.unk1 = 0;
                lbl_030032F0 = 1;
            } else {
                return 0;
            }
        }
    } else {
        fn_0200275C();
    }
    return -1;
}

s32 fn_02002538(void)
{
    if (lbl_03000070.unk0 == 0) {
        if (lbl_03000070.unk1 == 1) {
            lbl_03000070.unk1 = 2;
        } else if (lbl_03000070.unk1 == 3) {
            REG_JOY_TRANS = lbl_03000070.unk18;
            REG_JOYSTAT = 0x20;
            lbl_03000070.unk1 = 4;
        } else if (lbl_03000070.unk1 == 4) {
            lbl_03000070.unk1 = 5;
        } else {
            return 0;
        }
    } else {
        fn_02002714();
    }
    return -1;
}

u8 fn_02002594(void)
{
    return lbl_03000070.unk0;
}

void fn_020025A0(u16 arg0)
{
    vu16 ie = REG_IE;
    u32 pkt;
    u8 *p;

    REG_IE = 0;
    pkt = 0;
    p = (u8 *)&pkt;
    p[0] = 4;
    p[1] = ((u8 *)&arg0)[0];
    p[2] = ((u8 *)&arg0)[1];
    fn_02002698(pkt);
    REG_IE = ie;
}

void fn_020025E4(arg0)
u8 arg0;
{
    vu16 ie = REG_IE;
    u32 pkt;
    u8 *p;

    REG_IE = 0;
    pkt = 0;
    p = (u8 *)&pkt;
    p[0] = 14;
    p[1] = 0;
    p[2] = arg0;
    fn_02002698(pkt);
    REG_IE = ie;
}

void fn_02002620(void)
{
    s32 i;

    lbl_03000190 = 0;
    lbl_03000298 = 0;
    lbl_030004A0 = 0;
    lbl_030004A4 = 0;
    for (i = 0; i < 128; i++) {
        if (i < 64) {
            lbl_03000090[i] = 0;
            lbl_03000198[i] = 0;
        }
        lbl_030002A0[i] = 0;
    }
    memset(&lbl_030004A8, 0, sizeof(lbl_030004A8));
    lbl_030029A4 = 0;
    lbl_03002ACC = 0;
}

s32 fn_02002698(u32 data)
{
    vu16 ie = REG_IE;

    REG_IE = 0;
    if (lbl_03000190 >= 64) {
        REG_IE = ie;
        return -1;
    }
    if (lbl_03000190 == 0 && !(REG_JOYSTAT & 8)) {
        REG_JOY_TRANS = data;
        REG_JOYSTAT = 0;
    } else {
        lbl_03000090[lbl_03000190++] = data;
    }
    REG_IE = ie;
    return 0;
}

void fn_02002714(void)
{
    s32 i;

    if (lbl_03000190 != 0) {
        REG_JOY_TRANS = lbl_03000090[0];
        REG_JOYSTAT = 0;
        for (i = 1; i < lbl_03000190; i++)
            lbl_03000090[i - 1] = lbl_03000090[i];
        lbl_03000190--;
    }
}

void fn_0200275C(void)
{
    s32 n;
    u32 data;

    if ((n = lbl_03000298) < 64) {
        data = REG_JOY_RECV;
        lbl_03000198[n] = data;
        lbl_03000298 = n + 1;
        REG_JOYSTAT = 0;
    }
}

void fn_02002794(void)
{
    vu16 ie;
    u16 crc;
    u8 result;
    u32 pkt;
    s32 done;
    s32 i;
    s32 k;
    u8 *msg;
    u8 v;
    s32 n;

    ie = REG_IE;
    REG_IE = 0;
    if (lbl_030004A8.pending != 0 && fn_02002698(lbl_030004A8.pending) == 0) {
        if (*(s8 *)&lbl_030004A8.pending == 6)
            fn_02002F0C();
        memset(&lbl_030004A8, 0, sizeof(lbl_030004A8));
    }
    if (lbl_03000298 <= 0 && lbl_030004A0 <= 0) {
        lbl_030004A4 = lbl_030004A0;
        REG_IE = ie;
        return;
    }
    for (i = 0; i < lbl_03000298; i++)
        lbl_030002A0[lbl_030004A4 + i] = lbl_03000198[i];
    lbl_030004A0 += lbl_03000298;
    lbl_03000298 = 0;
    REG_IE = ie;
    if (lbl_030004A0 > 0) {
        for (i = lbl_030004A0; i != 0; i--)
            ;
    }
    done = 0;
restart:
    for (i = lbl_030004A4; i < lbl_030004A0; i++) {
        msg = (u8 *)&lbl_030002A0[i];
        if ((msg[0] & 0x3F) == 8) {
            for (k = 0; k < lbl_030004A0 - (1 + i); k++)
                lbl_030002A0[k] = lbl_030002A0[k + i + 1];
            lbl_030004A0 = lbl_030004A0 - (1 + i);
            lbl_030004A4 = 0;
            goto restart;
        } else if ((msg[0] & 0x3F) == 9) {
            if (lbl_03003094 == 0)
                lbl_03002ACC = msg[1];
        } else if ((msg[0] & 0x3F) == 10) {
            if (msg[1] != 0)
                lbl_030029A4 = 1;
            else
                lbl_030029A4 = 0;
        } else if ((msg[0] & 0x3F) == 5) {
            if ((msg[0] & 0xC0) == 0) {
                memset(&lbl_030004A8, 0, sizeof(lbl_030004A8));
                lbl_030004A8.count++;
                lbl_030004A8.total = msg[1];
                ((u8 *)&lbl_030004A8.crc)[0] = msg[2];
                ((u8 *)&lbl_030004A8.crc)[1] = msg[3];
            } else if ((msg[0] >> 6) == 1 && lbl_030004A8.count == 1) {
                if (lbl_030004A8.pending != 0)
                    goto resend;
                lbl_030004A8.count++;
                lbl_030004A8.size = msg[1] | (msg[2] << 8);
                lbl_030004A8.data[0] = msg[3];
                lbl_030004A8.pos = 1;
                goto check;
            } else if ((msg[0] >> 6) == 2 && lbl_030004A8.count > 1) {
                if (lbl_030004A8.pending != 0)
                    goto resend;
                lbl_030004A8.count++;
                if (lbl_030004A8.pos + 3 > sizeof(lbl_030004A8.data)) {
                    ((u8 *)&pkt)[0] = 7;
                    ((u8 *)&pkt)[1] = 0;
                    if (fn_02002698(pkt) != 0)
                        goto pend;
                }
                lbl_030004A8.data[lbl_030004A8.pos++] = msg[1];
                lbl_030004A8.data[lbl_030004A8.pos++] = msg[2];
                lbl_030004A8.data[lbl_030004A8.pos++] = msg[3];
            check:
                if (lbl_030004A8.count == lbl_030004A8.total) {
                    crc = 0xFFFF;
                    if (lbl_030004A8.crc != fn_02002130(lbl_030004A8.size, lbl_030004A8.data, &crc)
                        || lbl_030004A8.size > lbl_030004A8.pos) {
                        ((u8 *)&pkt)[0] = 7;
                        ((u8 *)&pkt)[1] = 0;
                        if (fn_02002698(pkt) != 0)
                            goto pend;
                    } else {
                        pkt = 0;
                        ((u8 *)&pkt)[0] = 6;
                        ((u8 *)&pkt)[1] = 0;
                        if (fn_02002698(pkt) != 0) {
                            lbl_030004A8.pending = pkt;
                            done = 1;
                        }
                        fn_02002F0C();
                        memset(&lbl_030004A8, 0, sizeof(lbl_030004A8));
                    }
                }
            } else {
                pkt = 0;
                ((u8 *)&pkt)[0] = 7;
                ((u8 *)&pkt)[1] = 0xFF;
                goto send;
            }
        } else if ((msg[0] & 0x3F) == 13) {
            lbl_03002AE8 = 0;
            if (fn_0200108C(*(u32 *)msg) != 0) {
                ((u8 *)&pkt)[0] = 7;
                ((u8 *)&pkt)[1] = 3;
                goto send;
            }
            ((u8 *)&pkt)[0] = 6;
            ((u8 *)&pkt)[1] = 3;
            if (fn_02002698(pkt) != 0)
                goto pend;
        } else if ((msg[0] & 0x3F) == 11) {
            n = fn_0200110C(*(u32 *)msg, &result);
            if (n != 0) {
                pkt = 0;
                if (n < 0)
                    ((u8 *)&pkt)[0] = 7;
                else
                    ((u8 *)&pkt)[0] = 6;
                ((u8 *)&pkt)[1] = result;
                goto send;
            }
        } else if ((msg[0] & 0x3F) == 14) {
            if (msg[1] == 1) {
                lbl_030008CC = 0;
                lbl_030008D0 = 0;
                lbl_030008D4 = 0;
                lbl_03002AE8 = 0;
                fn_02001438((s8)msg[2], (s8)msg[3]);
            }
        } else if ((msg[0] & 0x3F) == 15) {
            lbl_030008B4[msg[0] >> 6] = *(u16 *)&msg[2];
            if (msg[0] & 0xC0)
                fn_020045B4((s16)lbl_030008B4[0], (s16)lbl_030008B4[1]);
        } else if ((msg[0] & 0x3F) == 16) {
            lbl_03002AE8 = 0;
            memset(&lbl_030004A8, 0, sizeof(lbl_030004A8));
            fn_02000A74();
        } else if ((msg[0] & 0x3F) == 8) {
            memset(&lbl_030004A8, 0, sizeof(lbl_030004A8));
        } else if ((msg[0] & 0x3F) == 17) {
            n = msg[0] >> 6;
            if (n != 0 && n - 1 != (s8)lbl_030008B8) {
                ((u8 *)&pkt)[0] = 7;
                ((u8 *)&pkt)[1] = 0xFF;
                if (fn_02002698(pkt) != 0)
                    goto pend;
            }
            lbl_030008B8 = n;
            lbl_030008C0[n] = lbl_030002A0[i];
            if (n == 2)
                fn_0200469C(lbl_030008C0);
        } else if ((msg[0] & 0x3F) == 18) {
            fn_020046FC(&lbl_030002A0[i]);
        } else if ((msg[0] & 0x3F) == 33) {
            fn_0200471C(&lbl_030002A0[i]);
        } else if ((msg[0] & 0x3F) == 19) {
            fn_020048B4(&lbl_030002A0[i]);
        } else if ((msg[0] & 0x3F) == 12) {
            if (msg[1] == 14 && msg[2] == 0)
                fn_020025E4((s8)lbl_03003090);
        } else if ((msg[0] & 0x3F) == 6) {
            fn_020015A8(0);
        } else if ((msg[0] & 0x3F) == 7) {
            fn_020015A8(-1);
        } else if ((msg[0] & 0x3F) == 22) {
            fn_020049B8(&lbl_030002A0[i]);
        } else if ((msg[0] & 0x3F) == 20) {
            if (msg[1] == 1) {
                if (lbl_03003090 == 9) {
                    lbl_03002AE0 = msg[1];
                    lbl_03002AEC &= ~8;
                }
            } else if (msg[1] == 12) {
                fn_02004D88(lbl_030002A0[i]);
            } else if (msg[1] == 13) {
                fn_02004F1C(lbl_030002A0[i]);
            } else if (msg[1] == 14) {
                fn_02004F54(lbl_030002A0[i]);
            } else if (msg[1] == 15) {
                fn_02009ED4(lbl_030002A0[i]);
            } else if (msg[1] == 16) {
                fn_02005010(lbl_030002A0[i]);
            } else if (msg[1] == 17) {
                fn_02005024(lbl_030002A0[i]);
            } else if (msg[1] == 18) {
                fn_02005038(lbl_030002A0[i]);
            } else if (msg[1] == 19) {
                fn_0200508C(lbl_030002A0[i]);
            } else if (msg[1] == 20) {
                fn_020050B8();
            } else if (msg[1] == 22) {
                fn_020050D4(lbl_030002A0[i]);
            }
        } else if ((msg[0] & 0x3F) == 23) {
            fn_02004514(lbl_030002A0[i]);
        } else if ((msg[0] & 0x3F) == 26) {
            if ((msg[0] >> 6) == 0) {
                lbl_030008D0 = msg[1] | 0x80;
                lbl_030008CC = msg[2] << 24;
                lbl_030008CC |= msg[3] << 16;
            } else {
                v = lbl_030008D0;
                if ((s8)lbl_030008D0 == 0) {
                    if (fn_02002FE4(21, 0, 0) != 0)
                        goto pend;
                } else {
                    lbl_030008CC |= msg[1] << 8;
                    lbl_030008CC |= msg[2];
                    if (!(v & 7))
                        fn_02004AB4(lbl_030008CC);
                }
                lbl_030008D0 = 0;
                lbl_030008CC = 0;
            }
        } else if ((msg[0] & 0x3F) == 24) {
            fn_02008F48(lbl_030002A0[i]);
            pkt = 0;
            ((u8 *)&pkt)[0] = 6;
            ((u8 *)&pkt)[1] = 24;
        send:
            if (fn_02002698(pkt) != 0) {
            pend:
                lbl_030004A8.pending = pkt;
                goto resend;
            }
        } else if ((msg[0] & 0x3F) == 27) {
            fn_0200911C(lbl_030002A0[i]);
        } else if ((msg[0] & 0x3F) == 25) {
            fn_02004E38(lbl_030002A0[i]);
        } else if ((msg[0] & 0x3F) == 30) {
            fn_02004BB8(lbl_030002A0[i]);
        } else if ((msg[0] & 0x3F) == 31) {
            fn_02004BD4(lbl_030002A0[i]);
        } else if ((msg[0] & 0x3F) == 32) {
            fn_02004C1C(lbl_030002A0[i]);
        } else if ((msg[0] & 0x3F) == 34) {
            fn_02004FC0(lbl_030002A0[i]);
        }
    }
    if (done == 0) {
        memset(lbl_030002A0, 0, 0x200);
        lbl_030004A0 = done;
        lbl_030004A4 = done;
    } else {
    resend:
        for (k = 0; k < lbl_030004A0 - (1 + i); k++)
            lbl_030002A0[k] = lbl_030002A0[k + i + 1];
        lbl_030004A0 = lbl_030004A0 - (1 + i);
        lbl_030004A4 = 0;
    }
    lbl_030004A4 = lbl_030004A0;
}
