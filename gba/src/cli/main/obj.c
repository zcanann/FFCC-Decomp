#include "global.h"
#include "link.h"
#include "xfer.h"
#include "main.h"
#include "obj.h"

/* Header of the downloaded sprite data (bulk type 0); offsets from its start. */
struct ObjHeader {
    u32 unk0;
    u32 unk4;
    u16 palMapCount;
    u8 unkA;
    u8 unkB;
    u8 cellCount;
    u8 paletteCount;
    u16 unkE;
    u8 *palettesOffset;
    u8 *cellsOffset;
    u8 *cellPalettesOffset;
    u8 *palMapOffset;
};

/* One sprite cell (a set of animation frames sharing a shape). */
struct ObjCell {
    u8 shape;
    u8 frames;
    u8 palette;
    u8 firstPalette;
    u8 paletteCount;
    u8 palLoaded;
    u16 unk6;
    u8 *tiles;
};

struct Oam {
    u32 attr01;
    u32 attr23;
};

#define OAM_PRIORITY(oam) ((s32)(((oam)->attr23 >> 10) & 3))

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

union OamBuffer {
    struct Oam obj[128];
    struct OamAffine aff[32];
};

static union OamBuffer sOamBuf[2];
static s32 sOamCount;
static struct ObjCell sObjCells[0x700 / sizeof(struct ObjCell)];
static u8 sObjPalettes[0x600];
s16 gObjShapeSizes[] = {
    32, 128, 512, 2048, 64, 128, 256, 1024, 64, 128, 256, 1024,
};
extern u16 gSpObjPalettes[][16];
extern s16 gSinTable[];
static struct ObjHeader sObjHeader;
static s8 sOamBufIndex;
static s16 sAffineScaleX[32];

static s16 sAffineScaleY[32];
static s8 sAffineAngle[32];
static u8 sObjPalUsage[24];

void Obj_Init(void)
{
    s32 i;
    u8 *src;
    u32 ctrl;
    s32 size;

    sOamBufIndex = 0;
    Oam_ClearBuffer();
    sOamBufIndex = 1;
    Oam_ClearBuffer();
    sOamBufIndex = 0;
    for (i = 0; i < 32; i++) {
        sAffineScaleX[i] = 0x100;
        sAffineScaleY[i] = 0x100;
        sAffineAngle[i] = 0;
    }
    DmaCopy32(3, &sOamBuf[sOamBufIndex], 0x07000000, 0x400);
    if (gDataFlags & DATA_OBJ) {
        src = DOWNLOAD_DATA;
        LZ77UnCompVram(src, (void *)0x06010000);
        memcpy(&sObjHeader, DOWNLOAD_BUF, 32);
        CpuFastClear(0, sObjCells, 0x700);
        src = sObjHeader.palettesOffset + (u32)DOWNLOAD_BUF;
        size = sObjHeader.paletteCount * 32;
        DmaCopy16(3, src, sObjPalettes, size);
        src = gSpMode == 0 ? sObjPalettes : (u8 *)gSpObjPalettes;
        DmaCopy16(3, src, 0x05000200, size);
        src = sObjHeader.cellsOffset + (u32)DOWNLOAD_BUF;
        size = sObjHeader.palMapCount >> 1;
        if (sObjHeader.palMapCount & 1)
            size++;
        if (size & 3)
            size += 4 - size % 4;
        size += sObjHeader.palMapOffset - sObjHeader.cellsOffset;
        CpuFastCopy(src, sObjCells, size);
        memset(sObjPalUsage, 0, 18);
    }
}

void Oam_ClearBuffer(void)
{
    struct Oam hide;
    s32 i;
    struct Oam *oam;

    hide.attr01 = 0x200;
    hide.attr23 = 0;
    for (i = 0; i < 128; i++) {
        oam = (struct Oam *)&((u8 *)sOamBuf)[sOamBufIndex * 0x400 + i * 8];
        *oam = hide;
    }
    sOamCount = 0;
}

void Obj_Draw(s32 x, s32 y, s32 id, s32 frame, s32 pal, s32 prio, u32 flags)
{
    struct ObjCell *cell;
    s8 dx;
    s8 dy;
    u32 attr;
    u32 tile;
    u8 shape;

    if (!(gDataFlags & DATA_OBJ))
        return;
    cell = sObjCells;
    cell += id;
    if ((u32)(id - 3) <= 17 && cell->palLoaded == 0)
        return;
    Shake_GetOffset(&dx, &dy);
    x += dx;
    y += dy;
    shape = cell->shape;
    attr = (y & 0xFF) | ((x & 0x1FF) << 16) | (((shape & 12) << 12) | (shape << 30));
    if (flags & 0x300)
        flags &= 0x3E000300;
    else
        flags &= 0x30000C00;
    attr |= flags;
    sOamBuf[sOamBufIndex].obj[sOamCount].attr01 = attr;
    tile = ((u32)cell->tiles - 0x06010000) >> 5;
    attr = tile + frame * (gObjShapeSizes[shape] / 32);
    tile = (cell->palette >> 4) + pal;
    attr |= (tile << 12) | (prio << 10);
    sOamBuf[sOamBufIndex].obj[sOamCount].attr23 = attr;
    sOamCount++;
}

void Obj_Nop(void)
{
}

void Oam_SortByPriority(void)
{
    struct Oam *oam;
    struct Oam tmp;
    s32 prio;
    s32 n;
    s32 j;

    if (!(gDataFlags & DATA_OBJ))
        return;
    oam = (struct Oam *)&((u8 *)sOamBuf)[sOamBufIndex * 0x400];
    n = 0;
    for (prio = 0; prio < 4; prio++) {
        for (; n < sOamCount; n++) {
            if (OAM_PRIORITY(&oam[n]) > prio)
                break;
        }
        if (n >= sOamCount)
            break;
        for (j = n + 1; j < sOamCount; j++) {
            if (OAM_PRIORITY(&oam[j]) <= prio) {
                tmp = oam[n];
                oam[n] = oam[j];
                oam[j] = tmp;
                n++;
            }
        }
        if (n >= sOamCount)
            break;
    }
}

void Oam_UpdateAffine(void)
{
    struct OamAffine *aff;
    s16 m[4];
    s32 i;

    aff = sOamBuf[sOamBufIndex].aff;
    for (i = 0; i < 32; i++) {
        m[0] = FixMul(gSinTable[sAffineAngle[i] + 8], FixInverse(sAffineScaleX[i]));
        m[1] = FixMul(gSinTable[sAffineAngle[i]], FixInverse(sAffineScaleX[i]));
        m[2] = FixMul(-gSinTable[sAffineAngle[i]], FixInverse(sAffineScaleY[i]));
        m[3] = FixMul(gSinTable[sAffineAngle[i] + 8], FixInverse(sAffineScaleY[i]));
        aff->pa = m[0];
        aff->pb = m[1];
        aff->pc = m[2];
        aff->pd = m[3];
        aff++;
    }
}

void Obj_SetAffine(s32 no, s32 angle, s32 sx, s32 sy)
{
    sAffineScaleX[no] = sx;
    sAffineScaleY[no] = sy;
    sAffineAngle[no] = angle & 31;
}

void Oam_Commit(void)
{
    struct Oam hide;
    s32 i;
    struct Oam *oam;

    hide.attr01 = 0x200;
    hide.attr23 = 0;
    Oam_SortByPriority();
    for (i = sOamCount; i < 128; i++) {
        oam = (struct Oam *)&((u8 *)sOamBuf)[sOamBufIndex * 0x400 + i * 8];
        *oam = hide;
    }
    Oam_UpdateAffine();
    sOamBufIndex ^= 1;
    Oam_ClearBuffer();
}

void Oam_Reset(void)
{
    sOamCount = 0;
}

u8 Obj_GetFrameCount(s32 id)
{
    struct ObjCell *cell;

    if (!(gDataFlags & DATA_OBJ))
        return 0;
    cell = sObjCells;
    cell += id;
    return cell->frames;
}

s32 Obj_GetPalette(s32 idx, s32 pos)
{
    s32 sum;
    s32 i;
    struct ObjCell *e;
    s8 *p;

    if (!(gDataFlags & DATA_OBJ))
        return 0;

    sum = sObjHeader.palMapOffset - sObjHeader.cellsOffset;
    p = (s8 *)((u8 *)sObjCells + sum);
    e = sObjCells;
    sum = 0;
    for (i = 0; i < idx; i++, e++)
        sum += e->frames;
    sum += pos;
    p += sum >> 1;
    if (sum & 1)
        return *p & 0xF;
    else
        return *p >> 4;
}

void Obj_LoadToBg(s32 idx, s32 bank, s32 mode, s32 frame)
{
    struct ObjCell *e;
    s32 size;
    u32 dest;
    u32 pal;
    u8 *src;

    if (idx == 17)
        frame = Link_GetPlayerNo();
    if (!(gDataFlags & DATA_OBJ))
        return;

    e = sObjCells;
    e += idx;
    size = e->frames * (gObjShapeSizes[e->shape] / 32 << 5);
    if (bank == 0) {
        dest = 0;
        pal = 0x05000140;
    } else if (bank == 1) {
        dest = 0x400;
        pal = 0x05000160;
    } else if (bank == 2) {
        dest = 0x800;
        pal = 0x05000180;
    } else if (bank == 3) {
        dest = 0xC00;
        pal = 0x050001A0;
    } else {
        dest = 0x6000;
        pal = 0x050001C0;
    }
    if (frame < 0)
        pal = 0x05000020;
    dest += 0x80;
    if (mode <= 1)
        dest += 0x06000000;
    else
        dest += 0x06008000;
    DmaSet(3, e->tiles, dest, 0x80000000 | (size >> 1));

    if (gSpMode == 0) {
        src = (u8 *)sObjCells + (sObjHeader.cellPalettesOffset - sObjHeader.cellsOffset);
    } else {
        src = (u8 *)gSpObjPalettes;
        src += sObjHeader.paletteCount * 32;
    }
    if (frame < 0) {
        size = e->paletteCount * 32;
        src += e->firstPalette * 32;
    } else {
        size = 32;
        src += (e->firstPalette + frame) * 32;
    }
    DmaSet(3, src, pal, 0x80000000 | (size >> 1));
}

void Obj_AllocPalette(s32 idx, s32 frame)
{
    struct ObjCell *cells;
    struct ObjCell *e;
    s32 count;
    u16 used;
    s32 i;
    u8 *src;
    u32 dest;

    if (idx == 17)
        frame = Link_GetPlayerNo();
    if (!(gDataFlags & DATA_OBJ))
        return;

    cells = sObjCells;
    e = &cells[idx];
    if (e->palLoaded)
        return;

    count = 1;
    if (frame < 0)
        count = e->paletteCount;

    used = 0;
    for (i = 3; i < sObjHeader.cellCount; i++) {
        e = &cells[i];
        if (i != idx && e->palLoaded)
            used |= 1 << (e->palette >> 4);
    }

    e = &cells[idx];
    for (i = sObjHeader.paletteCount; i <= 15; i++) {
        if (!((used >> i) & 1))
            break;
    }
    e->palette = (i << 4) | 1;
    e->palLoaded = 1;

    if (gSpMode == 0) {
        src = (u8 *)sObjCells + (sObjHeader.cellPalettesOffset - sObjHeader.cellsOffset);
    } else {
        src = (u8 *)gSpObjPalettes;
        src += sObjHeader.paletteCount * 32;
    }
    if (frame < 0)
        src += e->firstPalette * 32;
    else
        src += (e->firstPalette + frame) * 32;
    dest = 0x05000200 + i * 32;
    DmaSet(3, src, dest, 0x80000000 | (count * 16));
    sObjPalUsage[idx - 3] = count;
}

void Obj_FreePalette(s32 idx)
{
    struct ObjCell *e;

    if ((gDataFlags & DATA_OBJ) && idx > 2) {
        e = sObjCells;
        e += idx;
        e->palette = 0xFF;
        e->palLoaded = 0;
        sObjPalUsage[idx - 3] = 0;
    }
}

void Obj_FreeAllPalettes(void)
{
    s32 i;

    for (i = 3; i <= 20; i++)
        Obj_FreePalette(i);
    memset(sObjPalUsage, 0, 18);
}

void Oam_Transfer(void)
{
    DmaSet(3, &sOamBuf[(s8)(sOamBufIndex ^ 1)], 0x07000000, 0x84000100);
}

void Obj_ReloadPalettes(void)
{
    u8 *src;
    s32 size;

    src = gSpMode == 0 ? sObjPalettes : (u8 *)gSpObjPalettes[0];
    size = sObjHeader.paletteCount * 32;
    DmaSet(3, src, 0x05000200, 0x80000000 | (size >> 1));
}
