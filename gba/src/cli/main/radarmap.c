#include "global.h"
#include "xfer.h"
#include "main.h"
#include "radar.h"

/* Run-length encoded radar map rows, found at BgHeader.mapOffset. */
struct MapInfo {
    s16 x;
    s16 y;
    u32 dataOffset;
    u8 rowLen[1];
};

static struct BgHeader *sMapHeader;
static struct MapInfo *sMapInfo;
static u8 *sMapRowLen;
static u16 *sMapData;
static s32 sMapX;
static s32 sMapY;
static u16 sMapScrollX;
static u16 sMapScrollY;

void Bg_LoadImage(u8 *data, void *tileDest, u16 *mapDest, u16 *palDest, s32 tileBase)
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
        DmaCopy16(0, src, dst, w << 1);
        src += w;
        dst += 32;
    }
    if (pal != (u16 *)(data + hdr->tileOffset))
        DmaCopy16(3, pal, palDest, 0x20);
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

void Bg_LoadMapLz(struct BgHeader *hdr)
{
    LZ77UnCompVram((u8 *)hdr + hdr->tileOffset, (void *)0x0600F000);
}

void Radar_ClearMap(void)
{
    DmaClear16(0, 0x1111, (void *)0x06008000, 0x20);
    DmaClear16(0, 0x1000, (void *)0x0600F000, 0x800);
}

void Radar_InitMap(void)
{
    u16 tmp;
    struct BgHeader *hdr;
    struct MapInfo *info;

    if (gDataFlags & DATA_MAP) {
        info = (struct MapInfo *)DOWNLOAD_DATA;
        LZ77UnCompVram(info, (void *)0x06008000);
        sMapHeader = hdr = (struct BgHeader *)DOWNLOAD_BUF;
        info = (struct MapInfo *)((u8 *)hdr + hdr->mapOffset);
        sMapInfo = info;
        sMapRowLen = DOWNLOAD_BUF + 8 + hdr->mapOffset;
        sMapData = (u16 *)((u8 *)info + info->dataOffset);
        tmp = 0x1000;
        DmaSet(0, &tmp, (void *)0x0600F000, 0x81000400);
        Bg_SetScroll(15, 0, 0);
        sMapScrollX = 0;
        sMapScrollY = 0;
    }
}

void Radar_LoadPalette(void)
{
    u16 pal[16];
    s32 i;

    for (i = 0; i < 16; i++)
        pal[i] = 0;
    pal[1] = pal[5] = pal[9] = 0;
    pal[2] = pal[6] = pal[10] = 0x7FFF;
    DmaCopy16(0, pal, (void *)0x05000020, sizeof(pal));
    for (i = 0; i < 16; i++)
        pal[i] = 0;
    pal[5] = pal[6] = 0;
    pal[9] = pal[10] = 0x7FFF;
    DmaCopy16(0, pal, (void *)0x05000040, sizeof(pal));
}

void Bg_SetBlend(s32 on)
{
    u16 mode = 0;

    if (on)
        mode = 0x40;
    REG_BLDCNT = mode | 0x1F04;
    REG_BLDALPHA = 0x0808;
}

void Radar_DrawMap(void)
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

    if (!(gDataFlags & DATA_MAP))
        return;
    Radar_GetBasePos(&x, &y);
    sMapX = x - 80;
    sMapY = y - 64;
    tx = (sMapX - sMapInfo->x) >> 3;
    ty = (sMapY - sMapInfo->y) >> 3;
    sMapScrollX = sMapX - sMapInfo->x;
    sMapScrollY = sMapY - sMapInfo->y;
    Bg_SetScroll(4, sMapScrollX, sMapScrollY);
    row = (s16)((ty - 1) % 32);
    if (row < 0)
        row += 32;
    dst = 0x0600F000 + row * 64;
    col = (s16)((tx - 1) % 32);
    if (col < 0)
        col += 32;
    dst += col * 2;
    mapW = sMapHeader->width >> 3;
    mapH = sMapHeader->height >> 3;
    sum = 0;
    for (i = 0; i < ty - 1 && i < mapH; i++)
        sum += sMapRowLen[i];
    data = sMapData + sum;
    for (i = -1; i <= 16; i++) {
        r = i + ty;
        if (r >= 0 && r < mapH) {
            n = 0;
            for (k = 0; k < sMapRowLen[r]; k++) {
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
            data += sMapRowLen[i + ty];
        }
        for (m = -1; m <= 21; m++) {
            c = m + tx;
            if (r < 0 || c < 0 || r >= mapH || c >= mapW)
                out[m + 1] = 0x1000;
            else
                out[m + 1] = line[c];
        }
        if (col + 23 <= 32) {
            DmaCopy16(0, out, dst, 23 * 2);
        } else {
            len = 32 - col;
            DmaCopy16(0, out, dst, len << 1);
            DmaCopy16(0, out + len, dst - col * 2, (23 - len) << 1);
        }
        dst += 64;
        if (dst > 0x0600F7FF)
            dst -= 0x800;
    }
}

void Radar_ScrollMap(s32 dx, s32 dy)
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
    s32 i;
    s32 k;
    s32 m;
    s32 n;
    s32 c;
    s32 r;
    s32 col;
    u32 u;
    s32 fine;
    s32 oldFine;
    u16 code;
    s32 cnt;
    u16 v;

    if (!(gDataFlags & DATA_MAP))
        return;
    if (dx == 0 && dy == 0)
        return;
    sMapX += dx;
    sMapY += dy;
    oldX = sMapScrollX;
    oldY = sMapScrollY;
    sMapScrollX = oldX + dx;
    sMapScrollY += dy;
    Bg_SetScroll(4, sMapScrollX, sMapScrollY);
    tx = (sMapX - sMapInfo->x) >> 3;
    ty = (sMapY - sMapInfo->y) >> 3;
    mapW = sMapHeader->width >> 3;
    mapH = sMapHeader->height >> 3;

    fine = sMapScrollX & 7;
    oldFine = oldX & 7;
    if (dx != 0 && ((oldFine <= 3 && fine > 3) || (oldFine > 4 && fine <= 4))) {
        if (dx < 0)
            c = tx - 1;
        else
            c = tx + 21;
        k = 0;
        for (i = 0; i < ty - 1 && i < mapH; i++)
            k += sMapRowLen[i];
        data = sMapData + k;
        n = (ty - 1) % 32;
        if (n < 0)
            n += 32;
        dst = 0x0600F000 + n * 64;
        col = c % 32;
        if (col < 0)
            col += 32;
        dst += col * 2;
        for (i = -1; i <= 16; i++) {
            r = i + ty;
            if (r >= 0 && r < mapH) {
                n = 0;
                for (k = 0; k < sMapRowLen[i + ty]; k++) {
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
                data += sMapRowLen[i + ty];
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

    fine = sMapScrollY & 7;
    oldFine = oldY & 7;
    if (dy != 0 && ((oldFine <= 3 && fine > 3) || (oldFine > 4 && fine <= 4))) {
        if (dy < 0)
            r = ty - 1;
        else
            r = ty + 16;
        k = 0;
        for (i = 0; i < r && i < mapH; i++)
            k += sMapRowLen[i];
        data = sMapData + k;
        if (r >= 0 && r < mapH) {
            n = 0;
            for (k = 0; k < sMapRowLen[r]; k++) {
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
        n = r % 32;
        if (n < 0)
            n += 32;
        dst = 0x0600F000 + n * 64;
        col = (tx - 1) % 32;
        if (col < 0)
            col += 32;
        dst += col * 2;
        if (col + 23 <= 32) {
            DmaCopy16(0, out, dst, 23 * 2);
        } else {
            n = 32 - col;
            DmaCopy16(0, out, dst, n << 1);
            DmaCopy16(0, out + n, dst - col * 2, (23 - n) << 1);
        }
    }
}
