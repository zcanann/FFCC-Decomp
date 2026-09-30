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

extern u16 gDataFlags;
extern u8 gReplyResult;
extern s8 gReplyTimer;
extern s8 gReplyWaiting;
extern s8 gXferErrorCount;
extern u8 sBulkXfer[];
extern struct Unk03000030 gXferCrc;
extern struct BgHeader gDownloadBuf;
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
extern struct LinkWork gLinkWork;
extern u16 sCrc16Table[];
extern u32 lbl_0201CF10;
extern u32 lbl_0300008C;
extern s32 sTxCount;
extern u32 sTxQueue[];
extern s32 sRxIsrCount;
extern u32 sRxIsrQueue[];
extern u32 sRxBuf[];
extern s32 sRxCount;
extern s32 sRxDone;
extern struct Transfer sMsgXfer;
extern u16 sBasePosIn[];
extern u8 sPartyPosSeq;
extern u32 sPartyPosIn[];
extern u32 sGilIn;
extern u8 sGilOp;
extern u32 lbl_030008D4;
extern u8 gLinkStarted;
extern u8 gMenuHasInput;
extern u8 gLinkEstablished;
extern u8 gMsgScreenId;
extern u32 gScreen;
extern u8 gLetterAttachKind;
extern u32 gMode;
extern u8 gXferActive;
extern u8 gNewLetter;

void LZ77UnCompVram(const void *src, void *dest);
void LZ77UnCompWram(const void *src, void *dest);
void Radar_GetBasePos(s16 *, s16 *);
void fn_02000AD4(s32, u16, u16);
void Link_Reset(void);
void Reply_Clear(void);
void fn_0201C734(void);
void *memset(void *, s32, u32);
void m4aMPlayAllStop(void);
s32 Link_Send(void);
s32 Link_Recv(u32);
void Link_JoyReset(void);
void Link_ClearQueues(void);
s32 Link_Write(u32);
void Link_TxPop(void);
void Link_RxPush(void);
void Link_DispatchMessage(void);
s32 Xfer_CheckCrc(u32);
s32 Xfer_Receive(u32, u8 *);
void Map_SetStage(s32, s32);
void Radar_SetBasePos(s32, s32);
void fn_02000A74(void);
void Radar_OnPartyPos(u32 *);
s32 Link_SendEvent(s32, s32, s32);
void Radar_OnEnemyPos(u32 *);
void Radar_OnTreasurePos(u32 *);
void Session_OnPartyHp(u32 *);
void Radar_OnMapObjDrawFlags(u32 *);
void Session_OnUseItem(u32);
void Radar_OnType(u32);
void Radar_OnMode(u32);
void Menu_OnOpen(u32);
void Session_OnItemUseFlags(u32);
void Session_OnSpMode(u32);
void Session_OnCmdNum(u32);
void Session_OnMemories(u32);
void Session_OnStartBonus(void);
void Session_OnLanguage(u32);
void Session_OnItemChange(u32);
void Session_SetGil(u32);
void Session_OnMask(u32);
void Mode_OnSet(u32);
void Session_OnStrength(u32);
void Session_OnEquipSlot(u32);
void Session_OnCmdSlot(u32);
void Session_OnTmpArtifact(u32);
void Scouter_OnHitEnemy(u32);

void Reply_Set(arg0)
u8 arg0;
{
    gDataFlags |= 0x8000;
    gReplyResult = arg0;
    gReplyTimer = 0;
    gReplyWaiting = 0;
}

void Reply_Tick(void)
{
    if (gReplyWaiting != 0 && gReplyWaiting < 30)
        gReplyTimer++;
}

s32 Reply_IsTimedOut(void)
{
    s32 n;

    if (gReplyWaiting == 0)
        n = 0;
    else
        n = gReplyTimer;
    return n >= 30;
}

u8 *Xfer_GetWork(void)
{
    return sBulkXfer;
}

void Xfer_ClearLetterData(void)
{
    gDataFlags &= ~8;
    gXferCrc.unk6 = 0;
    gDataFlags &= ~4;
    gXferCrc.unk4 = 0;
}

void Xfer_OnError(void)
{
    if (++gXferErrorCount > 10)
        Link_Reset();
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

void Radar_InitMap(void)
{
    u16 tmp;
    struct BgHeader *hdr;
    struct MapInfo *info;

    if (gDataFlags & 2) {
        info = (struct MapInfo *)lbl_02038020;
        LZ77UnCompVram(info, (void *)0x06008000);
        lbl_03000054 = hdr = &gDownloadBuf;
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

    if (!(gDataFlags & 2))
        return;
    Radar_GetBasePos(&x, &y);
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

    if (!(gDataFlags & 2))
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

u32 Crc8(u32 data)
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

u16 Crc16(s32 n, u8 *data, u16 *crc)
{
    while (--n >= 0) {
        *crc = (*crc << 8) ^ sCrc16Table[(*crc >> 8) ^ *data++];
    }
    return ~*crc;
}

void Link_JoyIntr(void)
{
    u16 stat = REG_JOYCNT;

    if (((stat & 4) && !Link_Send()) || ((stat & 2) && !Link_Recv(REG_JOY_RECV))) {
        REG_JOYSTAT = 0;
        gLinkWork.unk0 = 0;
        gLinkWork.unk1 = 0;
        Link_JoyReset();
    }
    if (stat & 1) {
        Link_JoyReset();
        if (gLinkWork.unk6 <= 2 && ++gLinkWork.unk5 >= 30)
            fn_0201C734();
        gLinkWork.unk6 = 0;
    } else if (gLinkWork.unk6 >= 2) {
        gLinkWork.unk5 = 0;
    } else {
        gLinkWork.unk6++;
    }
    REG_JOYCNT = stat;
    gLinkWork.unk2 = 0;
}

void Link_Init(void)
{
    u16 ime = REG_IME;
    u32 i;

    REG_IME = 0;
    for (i = 0; i < sizeof(gLinkWork); i++)
        ((u8 *)&gLinkWork)[i] = 0;
    gLinkWork.unk4 = 0xFF;
    Link_Reset();
    REG_IE |= 0x80;
    if (*(u8 *)0x020000C4 != 0) {
        gLinkWork.unk10 = gLinkWork.unk8 = *(u32 *)0x020000AC;
        gLinkWork.unk14 = *(u8 *)0x020000C4;
        gLinkWork.unk15 = *(u8 *)0x020000C5;
        gLinkWork.unk16 = 1;
        gLinkWork.unk18 = *(u32 *)0x020000C8;
    } else {
        gLinkWork.unk8 = *(u32 *)0x080000AC;
        gLinkWork.unk10 = lbl_0201CF10;
    }
    gMenuHasInput = 0;
    gLinkStarted = 0;
    REG_IME = ime;
}

void Link_Reset(void)
{
    u16 ime = REG_IME;
    s32 i;

    REG_IME = 0;
    if (gLinkWork.unk4 == 0)
        REG_RCNT = 0x8000;
    REG_RCNT = 0xC000;
    REG_JOYSTAT = 0;
    REG_JOY_RECV;
    REG_JOY_TRANS = 0;
    REG_JOYCNT = 0x47;
    REG_IF = 0x80;
    gLinkWork.unk2 = 0;
    gLinkWork.unk0 = 0;
    gLinkWork.unk1 = 0;
    gLinkWork.unk4 = 0;
    gLinkWork.unk5 = 0;
    gLinkWork.unk6 = 0;
    lbl_0300008C = 0;
    Link_ClearQueues();
    for (i = 0; i < 2; i++)
        sBasePosIn[i] = 0;
    sPartyPosSeq = 0;
    for (i = 0; i < 3; i++)
        sPartyPosIn[i] = 0;
    gDataFlags &= ~0xC;
    gMsgScreenId = 4;
    gScreen = 13;
    gLetterAttachKind = 0;
    sGilIn = 0;
    sGilOp = 0;
    lbl_030008D4 = 0;
    gXferErrorCount = 0;
    Reply_Clear();
    REG_IME = ime;
    m4aMPlayAllStop();
}

s32 Link_CheckTimeout(void)
{
    s32 ret;
    vu16 ime;

    if (gLinkWork.unk2 > 10) {
        gLinkWork.unk3 = 0xFF;
        Link_Reset();
        ret = -1;
    } else {
        ime = REG_IME;
        REG_IME = 0;
        gLinkWork.unk2++;
        REG_IME = ime;
        ret = 0;
    }
    return ret;
}

void Link_JoyReset(void)
{
    REG_JOY_RECV;
    REG_JOY_TRANS = gLinkWork.unk8;
    REG_JOYSTAT = 0x20;
    gLinkWork.unk0 = 0;
    gLinkWork.unk1 = 1;
    gLinkStarted = 0;
}

s32 Link_Recv(u32 data)
{
    u8 *recv = (u8 *)&data;
    u32 *word;
    u32 pkt;
    u8 *p;

    if (gLinkWork.unk0 == 0) {
        gDataFlags &= ~0xC;
        if (gLinkWork.unk1 == 2) {
            gLinkWork.unkC = data;
            p = (u8 *)&pkt;
            p[0] = 1;
            p[1] = (gLinkWork.unk14 << 6) | (gLinkWork.unk16 << 4) | gLinkWork.unk15;
            p[2] = 0;
            p[3] = 0;
            REG_JOY_TRANS = pkt;
            REG_JOYSTAT = 0x20;
            gLinkWork.unk1 = 3;
        } else {
            word = (u32 *)recv;
            if (gLinkWork.unk1 == 5) {
                if (gLinkWork.unk18 == data)
                    gLinkWork.unk17 = 0;
                else
                    gLinkWork.unk17 = 1;
                gLinkWork.unk18 = *word;
                REG_JOYSTAT = 0x20;
                gLinkWork.unk1 = 6;
            } else if (gLinkWork.unk1 == 6) {
                gLinkWork.unk15 = recv[1] & 0xF;
                REG_JOYSTAT = 0;
                gLinkWork.unk0 = 0xFF;
                gLinkWork.unk1 = 0;
                gLinkEstablished = 1;
            } else {
                return 0;
            }
        }
    } else {
        Link_RxPush();
    }
    return -1;
}

s32 Link_Send(void)
{
    if (gLinkWork.unk0 == 0) {
        if (gLinkWork.unk1 == 1) {
            gLinkWork.unk1 = 2;
        } else if (gLinkWork.unk1 == 3) {
            REG_JOY_TRANS = gLinkWork.unk18;
            REG_JOYSTAT = 0x20;
            gLinkWork.unk1 = 4;
        } else if (gLinkWork.unk1 == 4) {
            gLinkWork.unk1 = 5;
        } else {
            return 0;
        }
    } else {
        Link_TxPop();
    }
    return -1;
}

u8 Link_IsConnected(void)
{
    return gLinkWork.unk0;
}

void Link_SendPad(u16 arg0)
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
    Link_Write(pkt);
    REG_IE = ie;
}

void Link_SendScreenId(arg0)
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
    Link_Write(pkt);
    REG_IE = ie;
}

void Link_ClearQueues(void)
{
    s32 i;

    sTxCount = 0;
    sRxIsrCount = 0;
    sRxCount = 0;
    sRxDone = 0;
    for (i = 0; i < 128; i++) {
        if (i < 64) {
            sTxQueue[i] = 0;
            sRxIsrQueue[i] = 0;
        }
        sRxBuf[i] = 0;
    }
    memset(&sMsgXfer, 0, sizeof(sMsgXfer));
    gLinkStarted = 0;
    gMenuHasInput = 0;
}

s32 Link_Write(u32 data)
{
    vu16 ie = REG_IE;

    REG_IE = 0;
    if (sTxCount >= 64) {
        REG_IE = ie;
        return -1;
    }
    if (sTxCount == 0 && !(REG_JOYSTAT & 8)) {
        REG_JOY_TRANS = data;
        REG_JOYSTAT = 0;
    } else {
        sTxQueue[sTxCount++] = data;
    }
    REG_IE = ie;
    return 0;
}

void Link_TxPop(void)
{
    s32 i;

    if (sTxCount != 0) {
        REG_JOY_TRANS = sTxQueue[0];
        REG_JOYSTAT = 0;
        for (i = 1; i < sTxCount; i++)
            sTxQueue[i - 1] = sTxQueue[i];
        sTxCount--;
    }
}

void Link_RxPush(void)
{
    s32 n;
    u32 data;

    if ((n = sRxIsrCount) < 64) {
        data = REG_JOY_RECV;
        sRxIsrQueue[n] = data;
        sRxIsrCount = n + 1;
        REG_JOYSTAT = 0;
    }
}

void Link_ProcessRecv(void)
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
    if (sMsgXfer.pending != 0 && Link_Write(sMsgXfer.pending) == 0) {
        if (*(s8 *)&sMsgXfer.pending == 6)
            Link_DispatchMessage();
        memset(&sMsgXfer, 0, sizeof(sMsgXfer));
    }
    if (sRxIsrCount <= 0 && sRxCount <= 0) {
        sRxDone = sRxCount;
        REG_IE = ie;
        return;
    }
    for (i = 0; i < sRxIsrCount; i++)
        sRxBuf[sRxDone + i] = sRxIsrQueue[i];
    sRxCount += sRxIsrCount;
    sRxIsrCount = 0;
    REG_IE = ie;
    if (sRxCount > 0) {
        for (i = sRxCount; i != 0; i--)
            ;
    }
    done = 0;
restart:
    for (i = sRxDone; i < sRxCount; i++) {
        msg = (u8 *)&sRxBuf[i];
        if ((msg[0] & 0x3F) == 8) {
            for (k = 0; k < sRxCount - (1 + i); k++)
                sRxBuf[k] = sRxBuf[k + i + 1];
            sRxCount = sRxCount - (1 + i);
            sRxDone = 0;
            goto restart;
        } else if ((msg[0] & 0x3F) == 9) {
            if (gMode == 0)
                gMenuHasInput = msg[1];
        } else if ((msg[0] & 0x3F) == 10) {
            if (msg[1] != 0)
                gLinkStarted = 1;
            else
                gLinkStarted = 0;
        } else if ((msg[0] & 0x3F) == 5) {
            if ((msg[0] & 0xC0) == 0) {
                memset(&sMsgXfer, 0, sizeof(sMsgXfer));
                sMsgXfer.count++;
                sMsgXfer.total = msg[1];
                ((u8 *)&sMsgXfer.crc)[0] = msg[2];
                ((u8 *)&sMsgXfer.crc)[1] = msg[3];
            } else if ((msg[0] >> 6) == 1 && sMsgXfer.count == 1) {
                if (sMsgXfer.pending != 0)
                    goto resend;
                sMsgXfer.count++;
                sMsgXfer.size = msg[1] | (msg[2] << 8);
                sMsgXfer.data[0] = msg[3];
                sMsgXfer.pos = 1;
                goto check;
            } else if ((msg[0] >> 6) == 2 && sMsgXfer.count > 1) {
                if (sMsgXfer.pending != 0)
                    goto resend;
                sMsgXfer.count++;
                if (sMsgXfer.pos + 3 > sizeof(sMsgXfer.data)) {
                    ((u8 *)&pkt)[0] = 7;
                    ((u8 *)&pkt)[1] = 0;
                    if (Link_Write(pkt) != 0)
                        goto pend;
                }
                sMsgXfer.data[sMsgXfer.pos++] = msg[1];
                sMsgXfer.data[sMsgXfer.pos++] = msg[2];
                sMsgXfer.data[sMsgXfer.pos++] = msg[3];
            check:
                if (sMsgXfer.count == sMsgXfer.total) {
                    crc = 0xFFFF;
                    if (sMsgXfer.crc != Crc16(sMsgXfer.size, sMsgXfer.data, &crc)
                        || sMsgXfer.size > sMsgXfer.pos) {
                        ((u8 *)&pkt)[0] = 7;
                        ((u8 *)&pkt)[1] = 0;
                        if (Link_Write(pkt) != 0)
                            goto pend;
                    } else {
                        pkt = 0;
                        ((u8 *)&pkt)[0] = 6;
                        ((u8 *)&pkt)[1] = 0;
                        if (Link_Write(pkt) != 0) {
                            sMsgXfer.pending = pkt;
                            done = 1;
                        }
                        Link_DispatchMessage();
                        memset(&sMsgXfer, 0, sizeof(sMsgXfer));
                    }
                }
            } else {
                pkt = 0;
                ((u8 *)&pkt)[0] = 7;
                ((u8 *)&pkt)[1] = 0xFF;
                goto send;
            }
        } else if ((msg[0] & 0x3F) == 13) {
            gXferActive = 0;
            if (Xfer_CheckCrc(*(u32 *)msg) != 0) {
                ((u8 *)&pkt)[0] = 7;
                ((u8 *)&pkt)[1] = 3;
                goto send;
            }
            ((u8 *)&pkt)[0] = 6;
            ((u8 *)&pkt)[1] = 3;
            if (Link_Write(pkt) != 0)
                goto pend;
        } else if ((msg[0] & 0x3F) == 11) {
            n = Xfer_Receive(*(u32 *)msg, &result);
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
                sGilIn = 0;
                sGilOp = 0;
                lbl_030008D4 = 0;
                gXferActive = 0;
                Map_SetStage((s8)msg[2], (s8)msg[3]);
            }
        } else if ((msg[0] & 0x3F) == 15) {
            sBasePosIn[msg[0] >> 6] = *(u16 *)&msg[2];
            if (msg[0] & 0xC0)
                Radar_SetBasePos((s16)sBasePosIn[0], (s16)sBasePosIn[1]);
        } else if ((msg[0] & 0x3F) == 16) {
            gXferActive = 0;
            memset(&sMsgXfer, 0, sizeof(sMsgXfer));
            fn_02000A74();
        } else if ((msg[0] & 0x3F) == 8) {
            memset(&sMsgXfer, 0, sizeof(sMsgXfer));
        } else if ((msg[0] & 0x3F) == 17) {
            n = msg[0] >> 6;
            if (n != 0 && n - 1 != (s8)sPartyPosSeq) {
                ((u8 *)&pkt)[0] = 7;
                ((u8 *)&pkt)[1] = 0xFF;
                if (Link_Write(pkt) != 0)
                    goto pend;
            }
            sPartyPosSeq = n;
            sPartyPosIn[n] = sRxBuf[i];
            if (n == 2)
                Radar_OnPartyPos(sPartyPosIn);
        } else if ((msg[0] & 0x3F) == 18) {
            Radar_OnEnemyPos(&sRxBuf[i]);
        } else if ((msg[0] & 0x3F) == 33) {
            Radar_OnTreasurePos(&sRxBuf[i]);
        } else if ((msg[0] & 0x3F) == 19) {
            Session_OnPartyHp(&sRxBuf[i]);
        } else if ((msg[0] & 0x3F) == 12) {
            if (msg[1] == 14 && msg[2] == 0)
                Link_SendScreenId((s8)gScreen);
        } else if ((msg[0] & 0x3F) == 6) {
            Reply_Set(0);
        } else if ((msg[0] & 0x3F) == 7) {
            Reply_Set(-1);
        } else if ((msg[0] & 0x3F) == 22) {
            Radar_OnMapObjDrawFlags(&sRxBuf[i]);
        } else if ((msg[0] & 0x3F) == 20) {
            if (msg[1] == 1) {
                if (gScreen == 9) {
                    gNewLetter = msg[1];
                    gDataFlags &= ~8;
                }
            } else if (msg[1] == 12) {
                Session_OnUseItem(sRxBuf[i]);
            } else if (msg[1] == 13) {
                Radar_OnType(sRxBuf[i]);
            } else if (msg[1] == 14) {
                Radar_OnMode(sRxBuf[i]);
            } else if (msg[1] == 15) {
                Menu_OnOpen(sRxBuf[i]);
            } else if (msg[1] == 16) {
                Session_OnItemUseFlags(sRxBuf[i]);
            } else if (msg[1] == 17) {
                Session_OnSpMode(sRxBuf[i]);
            } else if (msg[1] == 18) {
                Session_OnCmdNum(sRxBuf[i]);
            } else if (msg[1] == 19) {
                Session_OnMemories(sRxBuf[i]);
            } else if (msg[1] == 20) {
                Session_OnStartBonus();
            } else if (msg[1] == 22) {
                Session_OnLanguage(sRxBuf[i]);
            }
        } else if ((msg[0] & 0x3F) == 23) {
            Session_OnItemChange(sRxBuf[i]);
        } else if ((msg[0] & 0x3F) == 26) {
            if ((msg[0] >> 6) == 0) {
                sGilOp = msg[1] | 0x80;
                sGilIn = msg[2] << 24;
                sGilIn |= msg[3] << 16;
            } else {
                v = sGilOp;
                if ((s8)sGilOp == 0) {
                    if (Link_SendEvent(21, 0, 0) != 0)
                        goto pend;
                } else {
                    sGilIn |= msg[1] << 8;
                    sGilIn |= msg[2];
                    if (!(v & 7))
                        Session_SetGil(sGilIn);
                }
                sGilOp = 0;
                sGilIn = 0;
            }
        } else if ((msg[0] & 0x3F) == 24) {
            Session_OnMask(sRxBuf[i]);
            pkt = 0;
            ((u8 *)&pkt)[0] = 6;
            ((u8 *)&pkt)[1] = 24;
        send:
            if (Link_Write(pkt) != 0) {
            pend:
                sMsgXfer.pending = pkt;
                goto resend;
            }
        } else if ((msg[0] & 0x3F) == 27) {
            Mode_OnSet(sRxBuf[i]);
        } else if ((msg[0] & 0x3F) == 25) {
            Session_OnStrength(sRxBuf[i]);
        } else if ((msg[0] & 0x3F) == 30) {
            Session_OnEquipSlot(sRxBuf[i]);
        } else if ((msg[0] & 0x3F) == 31) {
            Session_OnCmdSlot(sRxBuf[i]);
        } else if ((msg[0] & 0x3F) == 32) {
            Session_OnTmpArtifact(sRxBuf[i]);
        } else if ((msg[0] & 0x3F) == 34) {
            Scouter_OnHitEnemy(sRxBuf[i]);
        }
    }
    if (done == 0) {
        memset(sRxBuf, 0, 0x200);
        sRxCount = done;
        sRxDone = done;
    } else {
    resend:
        for (k = 0; k < sRxCount - (1 + i); k++)
            sRxBuf[k] = sRxBuf[k + i + 1];
        sRxCount = sRxCount - (1 + i);
        sRxDone = 0;
    }
    sRxDone = sRxCount;
}
