#include "global.h"
#include "link.h"
#include "xfer.h"
#include "main.h"
#include "session.h"
#include "radar.h"
#include "screen.h"

/* JOY Bus handshake and connection state */
struct LinkWork {
    vu8 connected : 8;
    vu8 step : 8;       /* handshake step */
    vu8 watchdog : 8;   /* frames since the last JOY interrupt */
    vu8 timedOut : 8;
    vu8 firstReset : 8;
    u8 resetCount;      /* JOY resets in quick succession */
    u8 resetGap;        /* other JOY interrupts since the last reset */
    u8 unk7;
    vu32 idleWord;      /* word presented to the GameCube before the handshake */
    u32 gameCode;
    u32 idleCode;
    u8 bootMode;
    u8 playerNo;
    u8 multiboot;
    u8 hostChanged;
    u32 hostId;         /* boot tick written into the image by the GameCube */
};

/* Reassembly of a GameCube "small message" (cmd 5). */
struct MsgXfer {
    u32 pending;
    u16 crc;
    u16 size;
    u16 pos;
    u8 total;
    u8 count;
    u8 data[0x400];
};

extern struct LinkWork gLinkWork;

extern u16 sCrc16Table[];
extern u32 sIdleCode;
extern u32 sLinkUnused;
extern s32 sTxCount;
extern u32 sTxQueue[];
extern s32 sRxIsrCount;
extern u32 sRxIsrQueue[];
extern u32 sRxBuf[];
extern s32 sRxCount;
extern s32 sRxDone;
extern struct MsgXfer sMsgXfer;
extern u16 sBasePosIn[];
extern u8 sPartyPosSeq;
extern u32 sPartyPosIn[];
extern u32 sGilIn;
extern s8 sGilOp;
extern u32 sGilUnused;

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
        gLinkWork.connected = 0;
        gLinkWork.step = 0;
        Link_JoyReset();
    }
    if (stat & 1) {
        Link_JoyReset();
        if (gLinkWork.resetGap <= 2 && ++gLinkWork.resetCount >= 30)
            JoyBus_HardReset();
        gLinkWork.resetGap = 0;
    } else if (gLinkWork.resetGap >= 2) {
        gLinkWork.resetCount = 0;
    } else {
        gLinkWork.resetGap++;
    }
    REG_JOYCNT = stat;
    gLinkWork.watchdog = 0;
}

void Link_Init(void)
{
    u16 ime = REG_IME;
    u32 i;

    REG_IME = 0;
    for (i = 0; i < sizeof(gLinkWork); i++)
        ((u8 *)&gLinkWork)[i] = 0;
    gLinkWork.firstReset = 0xFF;
    Link_Reset();
    REG_IE |= 0x80;
    if (*(u8 *)0x020000C4 != 0) {
        gLinkWork.idleCode = gLinkWork.idleWord = *(u32 *)0x020000AC;
        gLinkWork.bootMode = *(u8 *)0x020000C4;
        gLinkWork.playerNo = *(u8 *)0x020000C5;
        gLinkWork.multiboot = 1;
        gLinkWork.hostId = *(u32 *)0x020000C8;
    } else {
        gLinkWork.idleWord = *(u32 *)0x080000AC;
        gLinkWork.idleCode = sIdleCode;
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
    if (gLinkWork.firstReset == 0)
        REG_RCNT = 0x8000;
    REG_RCNT = 0xC000;
    REG_JOYSTAT = 0;
    REG_JOY_RECV;
    REG_JOY_TRANS = 0;
    REG_JOYCNT = 0x47;
    REG_IF = 0x80;
    gLinkWork.watchdog = 0;
    gLinkWork.connected = 0;
    gLinkWork.step = 0;
    gLinkWork.firstReset = 0;
    gLinkWork.resetCount = 0;
    gLinkWork.resetGap = 0;
    sLinkUnused = 0;
    Link_ClearQueues();
    for (i = 0; i < 2; i++)
        sBasePosIn[i] = 0;
    sPartyPosSeq = 0;
    for (i = 0; i < 3; i++)
        sPartyPosIn[i] = 0;
    gDataFlags &= ~(DATA_LETTER | DATA_LETTER_LIST);
    gMsgScreenId = 4;
    gScreen = 13;
    gLetterAttachKind = 0;
    sGilIn = 0;
    sGilOp = 0;
    sGilUnused = 0;
    gXferErrorCount = 0;
    Reply_Clear();
    REG_IME = ime;
    m4aMPlayAllStop();
}

s32 Link_CheckTimeout(void)
{
    s32 ret;
    vu16 ime;

    if (gLinkWork.watchdog > 10) {
        gLinkWork.timedOut = 0xFF;
        Link_Reset();
        ret = -1;
    } else {
        ime = REG_IME;
        REG_IME = 0;
        gLinkWork.watchdog++;
        REG_IME = ime;
        ret = 0;
    }
    return ret;
}

void Link_JoyReset(void)
{
    REG_JOY_RECV;
    REG_JOY_TRANS = gLinkWork.idleWord;
    REG_JOYSTAT = 0x20;
    gLinkWork.connected = 0;
    gLinkWork.step = 1;
    gLinkStarted = 0;
}

s32 Link_Recv(u32 data)
{
    u8 *recv = (u8 *)&data;
    u32 *word;
    u32 pkt;
    u8 *p;

    if (gLinkWork.connected == 0) {
        gDataFlags &= ~(DATA_LETTER | DATA_LETTER_LIST);
        if (gLinkWork.step == 2) {
            gLinkWork.gameCode = data;
            p = (u8 *)&pkt;
            p[0] = 1;
            p[1] = (gLinkWork.bootMode << 6) | (gLinkWork.multiboot << 4) | gLinkWork.playerNo;
            p[2] = 0;
            p[3] = 0;
            REG_JOY_TRANS = pkt;
            REG_JOYSTAT = 0x20;
            gLinkWork.step = 3;
        } else {
            word = (u32 *)recv;
            if (gLinkWork.step == 5) {
                if (gLinkWork.hostId == data)
                    gLinkWork.hostChanged = 0;
                else
                    gLinkWork.hostChanged = 1;
                gLinkWork.hostId = *word;
                REG_JOYSTAT = 0x20;
                gLinkWork.step = 6;
            } else if (gLinkWork.step == 6) {
                gLinkWork.playerNo = recv[1] & 0xF;
                REG_JOYSTAT = 0;
                gLinkWork.connected = 0xFF;
                gLinkWork.step = 0;
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
    if (gLinkWork.connected == 0) {
        if (gLinkWork.step == 1) {
            gLinkWork.step = 2;
        } else if (gLinkWork.step == 3) {
            REG_JOY_TRANS = gLinkWork.hostId;
            REG_JOYSTAT = 0x20;
            gLinkWork.step = 4;
        } else if (gLinkWork.step == 4) {
            gLinkWork.step = 5;
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
    return gLinkWork.connected;
}

void Link_SendPad(u16 keys)
{
    vu16 ie = REG_IE;
    u32 pkt;
    u8 *p;

    REG_IE = 0;
    pkt = 0;
    p = (u8 *)&pkt;
    p[0] = 4;
    p[1] = ((u8 *)&keys)[0];
    p[2] = ((u8 *)&keys)[1];
    Link_Write(pkt);
    REG_IE = ie;
}

void Link_SendScreenId(screen)
u8 screen;
{
    vu16 ie = REG_IE;
    u32 pkt;
    u8 *p;

    REG_IE = 0;
    pkt = 0;
    p = (u8 *)&pkt;
    p[0] = 14;
    p[1] = 0;
    p[2] = screen;
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
    u8 *p;
    s32 done;
    s32 i;
    s32 k;
    u8 *msg;
    u8 v;
    s32 n;
    s32 ret;

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
    for (i = 0; i < sRxCount; i++)
        ;
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
            if (gMode == MODE_FIELD)
                gMenuHasInput = msg[1];
        } else if ((msg[0] & 0x3F) == 10) {
            if (msg[1] != 0)
                gLinkStarted = 1;
            else
                gLinkStarted = 0;
        } else if ((msg[0] & 0x3F) == 5) {
            v = msg[0] & 0xC0;
            if (v == 0) {
                memset(&sMsgXfer, 0, sizeof(sMsgXfer));
                sMsgXfer.count++;
                sMsgXfer.total = msg[1];
                ((u8 *)&sMsgXfer.crc)[0] = msg[2];
                ((u8 *)&sMsgXfer.crc)[1] = msg[3];
            } else if ((v >> 6) == 1 && sMsgXfer.count == 1) {
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
                    p = (u8 *)&pkt;
                    p[0] = 7;
                    p[1] = 0;
                    if (Link_Write(pkt) != 0) {
                        sMsgXfer.pending = pkt;
                        goto resend;
                    }
                }
                sMsgXfer.data[sMsgXfer.pos++] = msg[1];
                sMsgXfer.data[sMsgXfer.pos++] = msg[2];
                sMsgXfer.data[sMsgXfer.pos++] = msg[3];
            check:
                if (sMsgXfer.count == sMsgXfer.total) {
                    crc = 0xFFFF;
                    if (Crc16(sMsgXfer.size, sMsgXfer.data, &crc) != sMsgXfer.crc
                        || sMsgXfer.size > sMsgXfer.pos) {
                        p = (u8 *)&pkt;
                        p[0] = 7;
                        p[1] = 0;
                        if (Link_Write(pkt) != 0) {
                            sMsgXfer.pending = pkt;
                            goto resend;
                        }
                    } else {
                        pkt = 0;
                        p = (u8 *)&pkt;
                        p[0] = 6;
                        p[1] = 0;
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
                p = (u8 *)&pkt;
                p[0] = 7;
                p[1] = 0xFF;
                goto send;
            }
        } else if ((msg[0] & 0x3F) == 13) {
            gXferActive = 0;
            if (Xfer_CheckCrc(*(u32 *)msg) != 0) {
                p = (u8 *)&pkt;
                p[0] = 7;
                p[1] = 3;
                goto send;
            }
            p = (u8 *)&pkt;
            p[0] = 6;
            p[1] = 3;
            if (Link_Write(pkt) != 0) {
                sMsgXfer.pending = pkt;
                goto resend;
            }
        } else if ((msg[0] & 0x3F) == 11) {
            ret = Xfer_Receive(*(u32 *)msg, &result);
            if (ret != 0) {
                p = (u8 *)&pkt;
                pkt = 0;
                if (ret < 0)
                    p[0] = 7;
                else
                    p[0] = 6;
                p[1] = result;
                goto send;
            }
        } else if ((msg[0] & 0x3F) == 14) {
            if (msg[1] == 1) {
                sGilIn = 0;
                sGilOp = 0;
                sGilUnused = 0;
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
            Header_Clear();
        } else if ((msg[0] & 0x3F) == 8) {
            memset(&sMsgXfer, 0, sizeof(sMsgXfer));
        } else if ((msg[0] & 0x3F) == 17) {
            n = msg[0] >> 6;
            if (n != 0 && n - 1 != (s8)sPartyPosSeq) {
                p = (u8 *)&pkt;
                p[0] = 7;
                p[1] = 0xFF;
                if (Link_Write(pkt) != 0) {
                    sMsgXfer.pending = pkt;
                    goto resend;
                }
            }
            sPartyPosSeq = n;
            sPartyPosIn[n] = sRxBuf[i];
            if (n == 2)
                Radar_OnPartyPos((s8 *)sPartyPosIn);
        } else if ((msg[0] & 0x3F) == 18) {
            Radar_OnEnemyPos((s8 *)&sRxBuf[i]);
        } else if ((msg[0] & 0x3F) == 33) {
            Radar_OnTreasurePos((s8 *)&sRxBuf[i]);
        } else if ((msg[0] & 0x3F) == 19) {
            Session_OnPartyHp((s8 *)&sRxBuf[i]);
        } else if ((msg[0] & 0x3F) == 12) {
            if (msg[1] == 14 && msg[2] == 0)
                Link_SendScreenId((s8)gScreen);
        } else if ((msg[0] & 0x3F) == 6) {
            Reply_Set(0);
        } else if ((msg[0] & 0x3F) == 7) {
            Reply_Set(-1);
        } else if ((msg[0] & 0x3F) == 22) {
            Radar_OnMapObjDrawFlags((u8 *)&sRxBuf[i]);
        } else if ((msg[0] & 0x3F) == 20) {
            if (msg[1] == 1) {
                if (gScreen == 9) {
                    gNewLetter = 1;
                    gDataFlags &= ~DATA_LETTER_LIST;
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
                if (sGilOp == 0) {
                    if (Link_SendEvent(21, 0, 0) != 0) {
                        sMsgXfer.pending = pkt;
                        goto resend;
                    }
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
            Session_OnMask(*(struct JoyBytes *)&sRxBuf[i]);
            pkt = 0;
            p = (u8 *)&pkt;
            p[0] = 6;
            p[1] = 24;
        send:
            if (Link_Write(pkt) != 0) {
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
    if (done != 0) {
    resend:
        for (k = 0; k < sRxCount - (1 + i); k++)
            sRxBuf[k] = sRxBuf[k + i + 1];
        sRxCount = sRxCount - (1 + i);
        sRxDone = 0;
    } else {
        memset(sRxBuf, 0, 0x200);
        sRxCount = done;
        sRxDone = done;
    }
    sRxDone = sRxCount;
}

void Link_DispatchMessage(void)
{
    struct MsgXfer *cmd = &sMsgXfer;

    if (cmd->data[0] == 1)
        Session_OnPlayerStat(&cmd->data[1]);
    else if (cmd->data[0] == 3)
        Radar_OnMapObj(&cmd->data[1]);
    else if (cmd->data[0] == 2)
        Session_OnItemAll(&cmd->data[1]);
    else if (cmd->data[0] == 4)
        Session_OnFavorite(&cmd->data[1]);
    else if (cmd->data[0] == 5)
        Session_OnCompatibility(&cmd->data[1]);
    else if (cmd->data[0] == 6)
        Session_OnEquipList(&cmd->data[1]);
    else if (cmd->data[0] == 7)
        Session_OnBonusStr(&cmd->data[1]);
    else if (cmd->data[0] == 8)
        Session_OnArtifacts(&cmd->data[1]);
    else if (cmd->data[0] == 9)
        Session_OnTmpArtifacts(&cmd->data[1]);
    else if (cmd->data[0] == 10)
        Radar_OnMarkerKinds(&cmd->data[1]);
    else if (cmd->data[0] == 11)
        Scouter_OnInfo(&cmd->data[1]);
    else if (cmd->data[0] == 12)
        Session_OnCmdList(&cmd->data[1]);
}

s32 Link_GetPlayerNo(void)
{
    return gLinkWork.playerNo;
}

s32 Link_SendRequest(u8 a, u8 b)
{
    u32 packet;
    u8 *p;

    packet = 0;
    p = (u8 *)&packet;
    p[0] = 12;
    p[1] = a;
    p[2] = b;
    return Link_Write(packet);
}

s32 Link_SendEvent(u8 a, u8 b, u8 c)
{
    u32 packet;
    u8 *p;

    packet = 0;
    p = (u8 *)&packet;
    p[0] = 20;
    p[1] = a;
    p[2] = b;
    p[3] = c;
    return Link_Write(packet);
}

s32 Link_SendLetterReply(a, b, c, d)
u8 a;
u8 b;
u8 c;
u32 d;
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
    sum = Crc16(7, buf, &crc);
    packet = 0;
    p = (u8 *)&packet;
    p[0] = 21;
    p[1] = sum >> 8;
    p[2] = sum;
    p[3] = buf[0];
    if (Link_Write(packet) != 0)
        return -1;
    packet = 0;
    p[0] = 0x55;
    p[1] = buf[1];
    p[2] = buf[2];
    p[3] = buf[3];
    if (Link_Write(packet) != 0)
        return -1;
    packet = 0;
    p[0] = 0x95;
    p[1] = buf[4];
    p[2] = buf[5];
    p[3] = buf[6];
    return Link_Write(packet);
}

void Link_SendItemOp(u8 a, u8 b, u8 c)
{
    u32 packet;
    u8 *p = (u8 *)&packet;

    p[0] = 23;
    p[1] = a;
    p[2] = b;
    p[3] = c;
    while (Link_Write(packet) != 0)
        ;
}

void Link_SendGil(u8 a, u32 b)
{
    u32 packet;
    u8 *p = (u8 *)&packet;

    p[0] = 26;
    p[1] = a;
    p[2] = b >> 24;
    p[3] = b >> 16;
    while (Link_Write(packet) != 0)
        ;
    packet = 0;
    p[0] = 0x5A;
    p[1] = b >> 8;
    p[2] = b;
    while (Link_Write(packet) != 0)
        ;
}

void Link_SendCMakeName(u8 *data)
{
    u16 crc;
    u32 packet;
    u8 *p;
    u16 sum;
    s32 i;

    crc = 0xFFFF;
    sum = Crc16(16, data, &crc);
    p = (u8 *)&packet;
    p[0] = 28;
    p[1] = sum >> 8;
    p[2] = sum;
    p[3] = *data++;
    while (Link_Write(packet) != 0)
        ;
    for (i = 0; i < 5; i++) {
        packet = 0;
        p[0] = 0x5C;
        p[1] = *data++;
        p[2] = *data++;
        p[3] = *data++;
        while (Link_Write(packet) != 0)
            ;
    }
}

void Link_SendCMakeLook(a)
u8 a;
{
    while (Link_SendEvent(2, a, 0) != 0)
        ;
}

void Link_SendCMakeJob(u8 a)
{
    while (Link_SendEvent(3, a, 0) != 0)
        ;
}

void Link_SendCMakeCancel(void)
{
    while (Link_SendEvent(4, 0, 0) != 0)
        ;
}

void Link_SendCMakeEnd(void)
{
    while (Link_SendEvent(5, 0, 0) != 0)
        ;
}

void Link_SendCMakeBirthday(s32 a, s32 b)
{
    while (Link_SendEvent(6, a, b) != 0)
        ;
}

void Link_SendCMakeFavorite(u8 *data)
{
    u16 crc;
    u32 packet;
    u8 *p;
    u16 sum;

    crc = 0xFFFF;
    sum = Crc16(4, data, &crc);
    p = (u8 *)&packet;
    p[0] = 29;
    p[1] = sum >> 8;
    p[2] = sum;
    p[3] = *data++;
    while (Link_Write(packet) != 0)
        ;
    packet = 0;
    p[0] = 0x5D;
    p[1] = *data++;
    p[2] = data[0];
    p[3] = data[1];
    while (Link_Write(packet) != 0)
        ;
}

void Link_SendEquipSlot(u8 a, u8 b)
{
    u32 packet;
    u8 *p = (u8 *)&packet;

    p[0] = 30;
    p[1] = a;
    p[2] = b;
    p[3] = 0;
    while (Link_Write(packet) != 0)
        ;
}

void Link_SendCmdSlot(a, b)
u8 a;
u16 b;
{
    u32 packet;
    u8 *p = (u8 *)&packet;

    p[0] = 31;
    p[1] = a;
    *(u16 *)&p[2] = b;
    while (Link_Write(packet) != 0)
        ;
}
