#include "link.h"
#include "screen.h"

extern const u16 gBackdropPalettes[];
extern const u16 *gBackdropTiles[];
extern const u16 *gBackdropMaps[];

/*
 * --INFO--
 * PAL Address: 0x020007D8
 * PAL Size: 248b
 * EN Address: 0x020007D8
 * EN Size: 248b
 * JP Address: 0x020046D8
 * JP Size: 248b
 */
void Bg_LoadBackdrop(s32 no)
{
    u16 buf[40];
    const u16 *tiles;
    const u16 *pal;
    const u16 *map;
    s32 pal_no;
    s32 x;
    s32 y;
    s32 w;
    s32 h;
    u32 size;
    u32 dst;

    w = 8;
    h = 8;
    tiles = gBackdropTiles[no];
    pal_no = Link_GetPlayerNo();
    if (gSpMode) {
        pal_no += 4;
    }
    pal = &gBackdropPalettes[pal_no * 16];
    map = gBackdropMaps[no];
    DmaCopy16(3, tiles, 0x0600D7E0, 0x800);
    DmaCopy16(3, pal, 0x05000000, 32);
    size = 64;
    for (y = 0; y < h; y++) {
        for (x = 0; x < 32; x += w) {
            memcpy(&buf[x], &map[y * w], 16);
        }
        for (x = 0; x < 32; x++) {
            buf[x] += 0x2BF;
        }
        for (x = y; x < 32; x += h) {
            dst = 0x0600F800 + x * size;
            DmaCopy16(3, buf, dst, size);
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x020008D0
 * PAL Size: 192b
 * EN Address: 0x020008D0
 * EN Size: 192b
 * JP Address: 0x020047D0
 * JP Size: 192b
 */
void Bg_CopyBackdropToRadar(void)
{
    u16 buf[40];
    s32 i;
    s32 j;
    s32 size;
    s32 n;
    u32 ofs;
    u32 dst;

    DmaCopy16(0, 0x0600D7E0, 0x06007060, 0x800);
    size = 24;
    for (i = 0; i < 16; i++) {
        DmaCopy16(0, 0x0600F800 + i * 64 + 40, buf, size);
        n = size / sizeof(u16);
        for (j = 0; j < n; j++) {
            buf[j] += 0xC4;
        }
        dst = 0x0600E800 + (i * 32 + 20) * 2;
        DmaCopy16(0, buf, dst, size);
    }
    for (i = 16; i < 32; i++) {
        ofs = i * 64;
        DmaCopy16(0, 0x0600F800 + ofs, buf, 64);
        for (j = 0; j < 32; j++) {
            buf[j] += 0xC4;
        }
        dst = 0x0600E800 + ofs;
        DmaCopy16(0, buf, dst, 64);
    }
}

/*
 * --INFO--
 * PAL Address: 0x02000990
 * PAL Size: 116b
 * EN Address: 0x02000990
 * EN Size: 116b
 * JP Address: 0x02004890
 * JP Size: 116b
 */
void Bg_ClearMaps(void)
{
    if (Link_IsConnected() || gScreen != SCREEN_WAITING) {
        DmaClear16(0, 0x3FF, 0x0600E000, 0x800);
        DmaClear16(0, 0x3FF, 0x0600E800, 0x800);
        DmaClear16(0, 0x2FF, 0x0600F000, 0x800);
    }
}

/*
 * --INFO--
 * PAL Address: 0x02000A04
 * PAL Size: 60b
 * EN Address: 0x02000A04
 * EN Size: 60b
 * JP Address: 0x02004904
 * JP Size: 60b
 */
void Bg_LoadPlayerPalette(void)
{
    s32 pal = Link_GetPlayerNo();
    const u16 *src;

    if (gSpMode) {
        pal += 4;
    }
    src = &gBackdropPalettes[pal * 16];
    DmaCopy16(3, src, 0x05000000, 32);
}

