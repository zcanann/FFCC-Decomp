#include "global.h"
#include "link.h"
#include "xfer.h"
#include "main.h"
#include "obj.h"
#include "radar.h"
#include "screen.h"

struct StageNo {
    s8 area;
    s8 map;
};

extern struct BulkXfer sBulkXfer;
extern u16 gXferCrc[16];
extern struct StageNo gStageNo;

extern s8 gReplyTimer;

extern const s8 sStaticMapStages[12][2];

void Xfer_Init(void)
{
    s32 i;

    gDataFlags = 0;
    gXferActive = 0;
    for (i = 0; i < 16; i++) {
        gXferCrc[i] = 0;
    }
    memset(&sBulkXfer, 0, sizeof(sBulkXfer));
    gStageNo.area = 0;
    gStageNo.map = 0;
    gStaticMap = 1;
    gNewLetter = 0;
    gXferErrorCount = 0;
}

s32 Xfer_CheckCrc(u32 packet)
{
    struct JoyWord *pkt = (struct JoyWord *)&packet;
    s32 result;

    if ((gDataFlags >> pkt->arg) & 1) {
        result = (gXferCrc[pkt->arg] == pkt->value) ? 0 : -1;
        if (result) {
            gDataFlags &= ~(1 << pkt->arg);
        }
    } else {
        result = -1;
    }
    return result;
}

void Xfer_Begin(void)
{
    gXferActive = 1;
    memset(&sBulkXfer, 0, sizeof(sBulkXfer));
    sBulkXfer.base = gDownloadBuf;
    sBulkXfer.cur = gDownloadBuf;
}

s32 Xfer_Receive(u32 packet, u8 *out)
{
    struct JoyWord *pkt = (struct JoyWord *)&packet;
    s32 kind;
    u8 *cur;
    u16 crc;

    kind = pkt->cmd >> 6;
    if (kind > 2) {
        *out = gXferActive ? sBulkXfer.type : 0xFF;
        gXferActive = 0;
        Xfer_OnError();
        return -1;
    }
    if (gXferActive == 0) {
        if (kind != 0) {
            *out = 0xFF;
            gXferActive = 0;
            Xfer_OnError();
            return -1;
        }
        Xfer_Begin();
    }
    *out = sBulkXfer.type;
    if (sBulkXfer.state == 0 && kind != 0) {
        gXferActive = 0;
        Xfer_OnError();
        return -1;
    }
    cur = sBulkXfer.cur;
    if ((u32)(cur - (u8 *)0x02038000) > 0x7FFF
        || (s32)sBulkXfer.base <= 0x02037FFF || (s32)sBulkXfer.base > 0x0203FFFF) {
        Xfer_Begin();
        gXferActive = 0;
        Xfer_OnError();
        return -1;
    }
    sBulkXfer.state = kind;
    if (kind == 0) {
        if (sBulkXfer.step == 0) {
            sBulkXfer.type = pkt->arg;
            if (sBulkXfer.type == 3 || sBulkXfer.type == 6 || sBulkXfer.type == 7
                || sBulkXfer.type == 8 || sBulkXfer.type == 9) {
                sBulkXfer.cur = sBulkXfer.base = gListBuf;
            } else if (sBulkXfer.type == 2) {
                sBulkXfer.cur = sBulkXfer.base = gDetailBuf;
            }
            if (sBulkXfer.type == 6) {
                gDataFlags &= ~DATA_SELL_LIST;
            } else if (sBulkXfer.type == 7) {
                gDataFlags &= ~DATA_BUY_LIST;
            } else if (sBulkXfer.type == 8) {
                gDataFlags &= ~DATA_SMITH_LIST;
            } else if (sBulkXfer.type == 9) {
                gDataFlags &= ~DATA_ARTIFACTS;
            } else {
                gDataFlags &= ~(1 << sBulkXfer.type);
            }
            sBulkXfer.count = pkt->value;
            sBulkXfer.step++;
        } else if (sBulkXfer.step == 1) {
            sBulkXfer.total = pkt->value;
            sBulkXfer.step++;
        } else if (sBulkXfer.step == 2) {
            gXferCrc[sBulkXfer.type] = pkt->value;
            sBulkXfer.step = 0;
            sBulkXfer.state = 1;
        } else {
            gXferActive = 0;
            Xfer_OnError();
            return -1;
        }
    } else if (kind == 1) {
        if (sBulkXfer.step == 0) {
            sBulkXfer.blocks = pkt->arg;
            sBulkXfer.blockSize = pkt->value;
            sBulkXfer.step++;
        } else if (sBulkXfer.step == 1) {
            sBulkXfer.index = pkt->arg;
            sBulkXfer.crc = pkt->value;
            sBulkXfer.step = 0;
            sBulkXfer.state = 2;
        }
    } else {
        *sBulkXfer.cur++ = pkt->arg;
        *sBulkXfer.cur++ = ((u8 *)&pkt->value)[0];
        *sBulkXfer.cur++ = ((u8 *)&pkt->value)[1];
        if (++sBulkXfer.step >= sBulkXfer.blocks) {
            crc = 0xFFFF;
            if (Crc16(sBulkXfer.blockSize, sBulkXfer.base, &crc) != sBulkXfer.crc) {
                gXferActive = 0;
                Xfer_OnError();
                return -1;
            }
            sBulkXfer.base += sBulkXfer.blockSize;
            sBulkXfer.cur = sBulkXfer.base;
            sBulkXfer.step = 0;
            sBulkXfer.state = 1;
            if (sBulkXfer.index + 1 >= sBulkXfer.count) {
                gXferActive = 0;
                Header_Clear();
                if (sBulkXfer.type == 6) {
                    gDataFlags |= DATA_SELL_LIST;
                } else if (sBulkXfer.type == 7) {
                    gDataFlags |= DATA_BUY_LIST;
                } else if (sBulkXfer.type == 8) {
                    gDataFlags |= DATA_SMITH_LIST;
                } else if (sBulkXfer.type == 9) {
                    gDataFlags |= DATA_ARTIFACTS;
                } else {
                    gDataFlags |= DATA_OBJ << sBulkXfer.type;
                }
                if (sBulkXfer.type == 0) {
                    Obj_Init();
                } else if (sBulkXfer.type == 1) {
                    if (gScreen == 0) {
                        Screen_Reset();
                    }
                } else if (sBulkXfer.type == 3) {
                    gNewLetter = 0;
                }
            }
            gXferErrorCount = 0;
            return 1;
        }
    }
    return 0;
}

void Map_SetStage(area, map)
u8 area;
u8 map;
{
    s8 table[12][2];
    s32 i;

    memcpy(table, sStaticMapStages, sizeof(table));
    gDataFlags &= ~DATA_BASE_POS;
    Scouter_SetDirty(0);
    Header_Clear();
    if (gStageNo.area != (s8)area && gScreen != 0) {
        if (gWasConnected) {
            gScreen = 0;
        } else {
            gSavedScreen = 0;
        }
    }
    Bg_SetBlend(0);
    REG_DISPCNT = 0x9F40;
    Bg_ClearMaps();
    Screen_Reset();
    Radar_ClearMarkers();
    memset(&gMapObjs, 0, 0x188);
    if (gStageNo.area != (s8)area || gStageNo.map != (s8)map) {
        gStageNo.area = area;
        gStageNo.map = map;
        gDataFlags &= ~DATA_MAP;
        gXferCrc[1] = 0;
        gStaticMap = 0;
        for (i = 0; table[i][0] >= 0; i++) {
            if ((s8)area == table[i][0] && (s8)map == table[i][1]) {
                gStaticMap = 1;
                break;
            }
        }
    }
}

void Map_GetStage(s8 *area, s8 *map)
{
    *area = gStageNo.area;
    *map = gStageNo.map;
}

void Reply_Clear(void)
{
    gDataFlags &= 0x7FFF;
    gReplyResult = 0;
    gReplyTimer = 0;
    gReplyWaiting = 0;
}

void Reply_Set(result)
u8 result;
{
    gDataFlags |= DATA_REPLY;
    gReplyResult = result;
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

struct BulkXfer *Xfer_GetWork(void)
{
    return &sBulkXfer;
}

void Xfer_ClearLetterData(void)
{
    gDataFlags &= ~DATA_LETTER_LIST;
    gXferCrc[3] = 0;
    gDataFlags &= ~DATA_LETTER;
    gXferCrc[2] = 0;
}

void Xfer_OnError(void)
{
    if (++gXferErrorCount > 10)
        Link_Reset();
}
