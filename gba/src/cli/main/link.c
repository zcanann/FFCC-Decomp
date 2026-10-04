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
    u8 pad;
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

static struct LinkWork sLinkWork;

const u16 sCrc16Table[] = {
    0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50A5, 0x60C6, 0x70E7,
    0x8108, 0x9129, 0xA14A, 0xB16B, 0xC18C, 0xD1AD, 0xE1CE, 0xF1EF,
    0x1231, 0x0210, 0x3273, 0x2252, 0x52B5, 0x4294, 0x72F7, 0x62D6,
    0x9339, 0x8318, 0xB37B, 0xA35A, 0xD3BD, 0xC39C, 0xF3FF, 0xE3DE,
    0x2462, 0x3443, 0x0420, 0x1401, 0x64E6, 0x74C7, 0x44A4, 0x5485,
    0xA56A, 0xB54B, 0x8528, 0x9509, 0xE5EE, 0xF5CF, 0xC5AC, 0xD58D,
    0x3653, 0x2672, 0x1611, 0x0630, 0x76D7, 0x66F6, 0x5695, 0x46B4,
    0xB75B, 0xA77A, 0x9719, 0x8738, 0xF7DF, 0xE7FE, 0xD79D, 0xC7BC,
    0x48C4, 0x58E5, 0x6886, 0x78A7, 0x0840, 0x1861, 0x2802, 0x3823,
    0xC9CC, 0xD9ED, 0xE98E, 0xF9AF, 0x8948, 0x9969, 0xA90A, 0xB92B,
    0x5AF5, 0x4AD4, 0x7AB7, 0x6A96, 0x1A71, 0x0A50, 0x3A33, 0x2A12,
    0xDBFD, 0xCBDC, 0xFBBF, 0xEB9E, 0x9B79, 0x8B58, 0xBB3B, 0xAB1A,
    0x6CA6, 0x7C87, 0x4CE4, 0x5CC5, 0x2C22, 0x3C03, 0x0C60, 0x1C41,
    0xEDAE, 0xFD8F, 0xCDEC, 0xDDCD, 0xAD2A, 0xBD0B, 0x8D68, 0x9D49,
    0x7E97, 0x6EB6, 0x5ED5, 0x4EF4, 0x3E13, 0x2E32, 0x1E51, 0x0E70,
    0xFF9F, 0xEFBE, 0xDFDD, 0xCFFC, 0xBF1B, 0xAF3A, 0x9F59, 0x8F78,
    0x9188, 0x81A9, 0xB1CA, 0xA1EB, 0xD10C, 0xC12D, 0xF14E, 0xE16F,
    0x1080, 0x00A1, 0x30C2, 0x20E3, 0x5004, 0x4025, 0x7046, 0x6067,
    0x83B9, 0x9398, 0xA3FB, 0xB3DA, 0xC33D, 0xD31C, 0xE37F, 0xF35E,
    0x02B1, 0x1290, 0x22F3, 0x32D2, 0x4235, 0x5214, 0x6277, 0x7256,
    0xB5EA, 0xA5CB, 0x95A8, 0x8589, 0xF56E, 0xE54F, 0xD52C, 0xC50D,
    0x34E2, 0x24C3, 0x14A0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405,
    0xA7DB, 0xB7FA, 0x8799, 0x97B8, 0xE75F, 0xF77E, 0xC71D, 0xD73C,
    0x26D3, 0x36F2, 0x0691, 0x16B0, 0x6657, 0x7676, 0x4615, 0x5634,
    0xD94C, 0xC96D, 0xF90E, 0xE92F, 0x99C8, 0x89E9, 0xB98A, 0xA9AB,
    0x5844, 0x4865, 0x7806, 0x6827, 0x18C0, 0x08E1, 0x3882, 0x28A3,
    0xCB7D, 0xDB5C, 0xEB3F, 0xFB1E, 0x8BF9, 0x9BD8, 0xABBB, 0xBB9A,
    0x4A75, 0x5A54, 0x6A37, 0x7A16, 0x0AF1, 0x1AD0, 0x2AB3, 0x3A92,
    0xFD2E, 0xED0F, 0xDD6C, 0xCD4D, 0xBDAA, 0xAD8B, 0x9DE8, 0x8DC9,
    0x7C26, 0x6C07, 0x5C64, 0x4C45, 0x3CA2, 0x2C83, 0x1CE0, 0x0CC1,
    0xEF1F, 0xFF3E, 0xCF5D, 0xDF7C, 0xAF9B, 0xBFBA, 0x8FD9, 0x9FF8,
    0x6E17, 0x7E36, 0x4E55, 0x5E74, 0x2E93, 0x3EB2, 0x0ED1, 0x1EF0,
};

const char sIdleCode[4] = "RELS";
static u32 sLinkUnused;
static u32 sTxQueue[64];
static s32 sTxCount;
static u32 sRxIsrQueue[64];
static s32 sRxIsrCount;
static u32 sRxBuf[128];
static s32 sRxCount;
static s32 sRxDone;
static struct MsgXfer sMsgXfer;
static u16 sBasePosIn[2];
static u8 sPartyPosSeq;
static u32 sPartyPosIn[3];
static u32 sGilIn;
static s8 sGilOp;
static u32 sGilUnused;

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
    for (; i < 8; i++) {
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
        sLinkWork.connected = 0;
        sLinkWork.step = 0;
        Link_JoyReset();
    }
    if (stat & 1) {
        Link_JoyReset();
        if (sLinkWork.resetGap <= 2 && ++sLinkWork.resetCount >= 30)
            JoyBus_HardReset();
        sLinkWork.resetGap = 0;
    } else if (sLinkWork.resetGap >= 2) {
        sLinkWork.resetCount = 0;
    } else {
        sLinkWork.resetGap++;
    }
    REG_JOYCNT = stat;
    sLinkWork.watchdog = 0;
}

void Link_Init(void)
{
    u16 ime = REG_IME;
    u32 i;

    REG_IME = 0;
    for (i = 0; i < sizeof(sLinkWork); i++)
        ((u8 *)&sLinkWork)[i] = 0;
    sLinkWork.firstReset = 0xFF;
    Link_Reset();
    REG_IE |= 0x80;
    if (*(u8 *)0x020000C4 != 0) {
        sLinkWork.idleCode = sLinkWork.idleWord = *(u32 *)0x020000AC;
        sLinkWork.bootMode = *(u8 *)0x020000C4;
        sLinkWork.playerNo = *(u8 *)0x020000C5;
        sLinkWork.multiboot = 1;
        sLinkWork.hostId = *(u32 *)0x020000C8;
    } else {
        sLinkWork.idleWord = *(u32 *)0x080000AC;
        sLinkWork.idleCode = *(u32 *)sIdleCode;
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
    if (sLinkWork.firstReset == 0)
        REG_RCNT = 0x8000;
    REG_RCNT = 0xC000;
    REG_JOYSTAT = 0;
    REG_JOY_RECV;
    REG_JOY_TRANS = 0;
    REG_JOYCNT = 0x47;
    REG_IF = 0x80;
    sLinkWork.watchdog = 0;
    sLinkWork.connected = 0;
    sLinkWork.step = 0;
    sLinkWork.firstReset = 0;
    sLinkWork.resetCount = 0;
    sLinkWork.resetGap = 0;
    sLinkUnused = 0;
    Link_ClearQueues();
    for (i = 0; i < 2; i++)
        sBasePosIn[i] = 0;
    sPartyPosSeq = 0;
    for (i = 0; i < 3; i++)
        sPartyPosIn[i] = 0;
    gDataFlags &= ~(DATA_LETTER | DATA_LETTER_LIST);
    gMsgScreenId = NOTICE_WAITING;
    gScreen = SCREEN_WAITING;
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

    if (sLinkWork.watchdog > 10) {
        sLinkWork.timedOut = 0xFF;
        Link_Reset();
        ret = -1;
    } else {
        ime = REG_IME;
        REG_IME = 0;
        sLinkWork.watchdog++;
        REG_IME = ime;
        ret = 0;
    }
    return ret;
}

void Link_JoyReset(void)
{
    REG_JOY_RECV;
    REG_JOY_TRANS = sLinkWork.idleWord;
    REG_JOYSTAT = 0x20;
    sLinkWork.connected = 0;
    sLinkWork.step = 1;
    gLinkStarted = 0;
}

s32 Link_Recv(u32 data)
{
    u8 *recv = (u8 *)&data;
    u32 *word;
    u32 pkt;
    u8 *p;

    if (sLinkWork.connected == 0) {
        gDataFlags &= ~(DATA_LETTER | DATA_LETTER_LIST);
        if (sLinkWork.step == 2) {
            sLinkWork.gameCode = data;
            p = (u8 *)&pkt;
            p[0] = LINK_CONTEXT;
            p[1] = (sLinkWork.bootMode << 6) | (sLinkWork.multiboot << 4) | sLinkWork.playerNo;
            p[2] = 0;
            p[3] = 0;
            REG_JOY_TRANS = pkt;
            REG_JOYSTAT = 0x20;
            sLinkWork.step = 3;
        } else {
            word = (u32 *)recv;
            if (sLinkWork.step == 5) {
                if (sLinkWork.hostId == data)
                    sLinkWork.hostChanged = 0;
                else
                    sLinkWork.hostChanged = 1;
                sLinkWork.hostId = *word;
                REG_JOYSTAT = 0x20;
                sLinkWork.step = 6;
            } else if (sLinkWork.step == 6) {
                sLinkWork.playerNo = recv[1] & 0xF;
                REG_JOYSTAT = 0;
                sLinkWork.connected = 0xFF;
                sLinkWork.step = 0;
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
    if (sLinkWork.connected == 0) {
        if (sLinkWork.step == 1) {
            sLinkWork.step = 2;
        } else if (sLinkWork.step == 3) {
            REG_JOY_TRANS = sLinkWork.hostId;
            REG_JOYSTAT = 0x20;
            sLinkWork.step = 4;
        } else if (sLinkWork.step == 4) {
            sLinkWork.step = 5;
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
    return sLinkWork.connected;
}

void Link_SendPad(u16 keys)
{
    vu16 ie = REG_IE;
    u32 pkt;
    u8 *p;

    REG_IE = 0;
    pkt = 0;
    p = (u8 *)&pkt;
    p[0] = LINK_PAD;
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
    p[0] = LINK_STATE;
    p[1] = STATE_SCREEN;
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
    u16 sum;
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
    u32 mask;

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
        if ((msg[0] & LINK_CMD_MASK) == LINK_FLUSH) {
            for (k = 0; k < sRxCount - (1 + i); k++)
                sRxBuf[k] = sRxBuf[k + i + 1];
            sRxCount = sRxCount - (1 + i);
            sRxDone = 0;
            goto restart;
        } else if ((msg[0] & LINK_CMD_MASK) == LINK_CTRL_MODE) {
            if (gMode == MODE_FIELD)
                gMenuHasInput = msg[1];
        } else if ((msg[0] & LINK_CMD_MASK) == LINK_START) {
            if (msg[1] != 0)
                gLinkStarted = 1;
            else
                gLinkStarted = 0;
        } else if ((msg[0] & LINK_CMD_MASK) == LINK_MESSAGE) {
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
                    p[0] = LINK_NAK;
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
                    sum = Crc16(sMsgXfer.size, sMsgXfer.data, &crc);
                    if (sMsgXfer.crc != sum
                        || sMsgXfer.size > sMsgXfer.pos) {
                        p = (u8 *)&pkt;
                        p[0] = LINK_NAK;
                        p[1] = 0;
                        if (Link_Write(pkt) != 0) {
                            sMsgXfer.pending = pkt;
                            goto resend;
                        }
                    } else {
                        pkt = 0;
                        p = (u8 *)&pkt;
                        p[0] = LINK_ACK;
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
                p[0] = LINK_NAK;
                p[1] = 0xFF;
                if (Link_Write(pkt) != 0) {
                    sMsgXfer.pending = pkt;
                    goto resend;
                }
            }
        } else if ((msg[0] & LINK_CMD_MASK) == LINK_CHECK_CRC) {
            gXferActive = 0;
            if (Xfer_CheckCrc(*(u32 *)msg) != 0) {
                p = (u8 *)&pkt;
                p[0] = LINK_NAK;
                p[1] = 3;
                ret = Link_Write(pkt);
            } else {
                p = (u8 *)&pkt;
                p[0] = LINK_ACK;
                p[1] = 3;
                ret = Link_Write(pkt);
            }
            if (ret != 0) {
                sMsgXfer.pending = pkt;
                goto resend;
            }
        } else if ((msg[0] & LINK_CMD_MASK) == LINK_DATA) {
            ret = Xfer_Receive(*(u32 *)msg, &result);
            if (ret != 0) {
                p = (u8 *)&pkt;
                pkt = 0;
                if (ret < 0)
                    p[0] = LINK_NAK;
                else
                    p[0] = LINK_ACK;
                p[1] = result;
                if (Link_Write(pkt) != 0) {
                    sMsgXfer.pending = pkt;
                    goto resend;
                }
            }
        } else if ((msg[0] & LINK_CMD_MASK) == LINK_STATE) {
            if (msg[1] == STATE_MAP) {
                sGilIn = 0;
                sGilOp = 0;
                sGilUnused = 0;
                gXferActive = 0;
                Map_SetStage((s8)msg[2], (s8)msg[3]);
            }
        } else if ((msg[0] & LINK_CMD_MASK) == LINK_BASE_POS) {
            sBasePosIn[msg[0] >> 6] = *(u16 *)&msg[2];
            if (msg[0] & 0xC0)
                Radar_SetBasePos((s16)sBasePosIn[0], (s16)sBasePosIn[1]);
        } else if ((msg[0] & LINK_CMD_MASK) == LINK_CANCEL) {
            gXferActive = 0;
            memset(&sMsgXfer, 0, sizeof(sMsgXfer));
            Header_Clear();
        } else if ((msg[0] & LINK_CMD_MASK) == LINK_FLUSH) {
            memset(&sMsgXfer, 0, sizeof(sMsgXfer));
        } else if ((msg[0] & LINK_CMD_MASK) == LINK_PARTY_POS) {
            n = msg[0] >> 6;
            if (n != 0 && n - 1 != (s8)sPartyPosSeq) {
                p = (u8 *)&pkt;
                p[0] = LINK_NAK;
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
        } else if ((msg[0] & LINK_CMD_MASK) == LINK_ENEMY_POS) {
            Radar_OnEnemyPos((s8 *)&sRxBuf[i]);
        } else if ((msg[0] & LINK_CMD_MASK) == LINK_TREASURE_POS) {
            Radar_OnTreasurePos((s8 *)&sRxBuf[i]);
        } else if ((msg[0] & LINK_CMD_MASK) == LINK_PARTY_HP) {
            Session_OnPartyHp((s8 *)&sRxBuf[i]);
        } else if ((msg[0] & LINK_CMD_MASK) == LINK_REQUEST) {
            if (msg[1] == REQ_STATE && msg[2] == STATE_SCREEN)
                Link_SendScreenId((s8)gScreen);
        } else if ((msg[0] & LINK_CMD_MASK) == LINK_ACK) {
            Reply_Set(0);
        } else if ((msg[0] & LINK_CMD_MASK) == LINK_NAK) {
            Reply_Set(-1);
        } else if ((msg[0] & LINK_CMD_MASK) == LINK_MAPOBJ_FLAGS) {
            Radar_OnMapObjDrawFlags((u8 *)&sRxBuf[i]);
        } else if ((msg[0] & LINK_CMD_MASK) == LINK_EVENT) {
            if (msg[1] == EVT_ADD_LETTER) {
                if (gScreen == SCREEN_LETTERS) {
                    gNewLetter = 1;
                    gDataFlags &= ~DATA_LETTER_LIST;
                }
            } else if (msg[1] == EVT_USE_ITEM) {
                Session_OnUseItem(sRxBuf[i]);
            } else if (msg[1] == EVT_RADAR_TYPE) {
                Radar_OnType(sRxBuf[i]);
            } else if (msg[1] == EVT_RADAR_MODE) {
                Radar_OnMode(sRxBuf[i]);
            } else if (msg[1] == EVT_OPEN_MENU) {
                Menu_OnOpen(sRxBuf[i]);
            } else if (msg[1] == EVT_ITEM_USE_FLAGS) {
                Session_OnItemUseFlags(sRxBuf[i]);
            } else if (msg[1] == EVT_SP_MODE) {
                Session_OnSpMode(sRxBuf[i]);
            } else if (msg[1] == EVT_CMD_NUM) {
                Session_OnCmdNum(sRxBuf[i]);
            } else if (msg[1] == EVT_MEMORIES) {
                Session_OnMemories(sRxBuf[i]);
            } else if (msg[1] == EVT_START_BONUS) {
                Session_OnStartBonus();
            } else if (msg[1] == EVT_LANGUAGE) {
                Session_OnLanguage(sRxBuf[i]);
            }
        } else if ((msg[0] & LINK_CMD_MASK) == LINK_ITEM) {
            Session_OnItemChange(sRxBuf[i]);
        } else if ((msg[0] & LINK_CMD_MASK) == LINK_GIL) {
            if ((msg[0] >> 6) == 0) {
                sGilOp = msg[1] | 0x80;
                sGilIn = msg[2] << 24;
                sGilIn |= msg[3] << 16;
            } else {
                v = sGilOp;
                if (sGilOp == 0) {
                    if (Link_SendEvent(EVT_GIL_RESEND, 0, 0) != 0) {
                        sMsgXfer.pending = pkt;
                        goto resend;
                    }
                } else {
                    sGilIn |= msg[1] << 8;
                    sGilIn |= msg[2];
                    mask = 7;
                    mask &= v;
                    if (mask == 0)
                        Session_SetGil(sGilIn);
                }
                sGilOp = 0;
                sGilIn = 0;
            }
        } else if ((msg[0] & LINK_CMD_MASK) == LINK_MASK) {
            Session_OnMask(*(struct JoyBytes *)&sRxBuf[i]);
            pkt = 0;
            p = (u8 *)&pkt;
            p[0] = LINK_ACK;
            p[1] = LINK_MASK;
            if (Link_Write(pkt) != 0) {
                sMsgXfer.pending = pkt;
                goto resend;
            }
        } else if ((msg[0] & LINK_CMD_MASK) == LINK_MODE) {
            Mode_OnSet(sRxBuf[i]);
        } else if ((msg[0] & LINK_CMD_MASK) == LINK_STRENGTH) {
            Session_OnStrength(sRxBuf[i]);
        } else if ((msg[0] & LINK_CMD_MASK) == LINK_EQUIP_SLOT) {
            Session_OnEquipSlot(sRxBuf[i]);
        } else if ((msg[0] & LINK_CMD_MASK) == LINK_CMD_SLOT) {
            Session_OnCmdSlot(sRxBuf[i]);
        } else if ((msg[0] & LINK_CMD_MASK) == LINK_TMP_ARTIFACT) {
            Session_OnTmpArtifact(sRxBuf[i]);
        } else if ((msg[0] & LINK_CMD_MASK) == LINK_HIT_ENEMY) {
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

    if (cmd->data[0] == MSG_PLAYER_STAT)
        Session_OnPlayerStat(&cmd->data[1]);
    else if (cmd->data[0] == MSG_MAP_OBJ)
        Radar_OnMapObj(&cmd->data[1]);
    else if (cmd->data[0] == MSG_ITEM_ALL)
        Session_OnItemAll(&cmd->data[1]);
    else if (cmd->data[0] == MSG_FAVORITE)
        Session_OnFavorite(&cmd->data[1]);
    else if (cmd->data[0] == MSG_COMPATIBILITY)
        Session_OnCompatibility(&cmd->data[1]);
    else if (cmd->data[0] == MSG_EQUIP_LIST)
        Session_OnEquipList(&cmd->data[1]);
    else if (cmd->data[0] == MSG_BONUS_STR)
        Session_OnBonusStr(&cmd->data[1]);
    else if (cmd->data[0] == MSG_ARTIFACTS)
        Session_OnArtifacts(&cmd->data[1]);
    else if (cmd->data[0] == MSG_TMP_ARTIFACTS)
        Session_OnTmpArtifacts(&cmd->data[1]);
    else if (cmd->data[0] == MSG_MARKER_KINDS)
        Radar_OnMarkerKinds(&cmd->data[1]);
    else if (cmd->data[0] == MSG_SCOUTER_INFO)
        Scouter_OnInfo(&cmd->data[1]);
    else if (cmd->data[0] == MSG_CMD_LIST)
        Session_OnCmdList(&cmd->data[1]);
}

s32 Link_GetPlayerNo(void)
{
    return sLinkWork.playerNo;
}

s32 Link_SendRequest(u8 type, u8 arg)
{
    u32 packet;
    u8 *p;

    packet = 0;
    p = (u8 *)&packet;
    p[0] = LINK_REQUEST;
    p[1] = type;
    p[2] = arg;
    return Link_Write(packet);
}

s32 Link_SendEvent(u8 sub, u8 a, u8 b)
{
    u32 packet;
    u8 *p;

    packet = 0;
    p = (u8 *)&packet;
    p[0] = LINK_EVENT;
    p[1] = sub;
    p[2] = a;
    p[3] = b;
    return Link_Write(packet);
}

s32 Link_SendLetterReply(letter, answer, isGil, value)
u8 letter;
u8 answer;
u8 isGil;
u32 value;
{
    u8 buf[9];
    u16 crc;
    u32 packet;
    u8 *p;
    u32 i;
    u16 sum;

    for (i = 0; i < 9; i++)
        buf[i] = 0;
    i = 0;
    buf[i++] = letter;
    buf[i++] = answer;
    buf[i++] = isGil;
    buf[i++] = value >> 24;
    buf[i++] = value >> 16;
    buf[i++] = value >> 8;
    buf[i++] = value;
    crc = 0xFFFF;
    sum = Crc16(7, buf, &crc);
    packet = 0;
    p = (u8 *)&packet;
    p[0] = LINK_LETTER_REPLY;
    p[1] = sum >> 8;
    p[2] = sum;
    i = 0;
    p[3] = buf[i++];
    if (Link_Write(packet) != 0)
        return -1;
    packet = 0;
    p[0] = LINK_LETTER_REPLY | LINK_KIND_SECOND;
    p[1] = buf[i++];
    p[2] = buf[i++];
    p[3] = buf[i++];
    if (Link_Write(packet) != 0)
        return -1;
    packet = 0;
    p[0] = LINK_LETTER_REPLY | LINK_KIND_DATA;
    p[1] = buf[i++];
    p[2] = buf[i++];
    p[3] = buf[i++];
    return Link_Write(packet);
}

void Link_SendItemOp(u8 op, u8 slot, u8 arg)
{
    u32 packet;
    u8 *p = (u8 *)&packet;

    p[0] = LINK_ITEM;
    p[1] = op;
    p[2] = slot;
    p[3] = arg;
    while (Link_Write(packet) != 0)
        ;
}

void Link_SendGil(u8 op, u32 gil)
{
    u32 packet;
    u8 *p = (u8 *)&packet;

    p[0] = LINK_GIL;
    p[1] = op;
    p[2] = gil >> 24;
    p[3] = gil >> 16;
    while (Link_Write(packet) != 0)
        ;
    packet = 0;
    p[0] = LINK_GIL | LINK_KIND_SECOND;
    p[1] = gil >> 8;
    p[2] = gil;
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
    p[0] = LINK_CMAKE_NAME;
    p[1] = sum >> 8;
    p[2] = sum;
    p[3] = *data++;
    while (Link_Write(packet) != 0)
        ;
    for (i = 0; i < 5; i++) {
        packet = 0;
        p[0] = LINK_CMAKE_NAME | LINK_KIND_SECOND;
        p[1] = *data++;
        p[2] = *data++;
        p[3] = *data++;
        while (Link_Write(packet) != 0)
            ;
    }
}

void Link_SendCMakeLook(look)
u8 look;
{
    while (Link_SendEvent(EVT_CMAKE_LOOK, look, 0) != 0)
        ;
}

void Link_SendCMakeJob(u8 job)
{
    while (Link_SendEvent(EVT_CMAKE_JOB, job, 0) != 0)
        ;
}

void Link_SendCMakeCancel(void)
{
    while (Link_SendEvent(EVT_CMAKE_CANCEL, 0, 0) != 0)
        ;
}

void Link_SendCMakeEnd(void)
{
    while (Link_SendEvent(EVT_CMAKE_END, 0, 0) != 0)
        ;
}

void Link_SendCMakeBirthday(s32 month, s32 day)
{
    while (Link_SendEvent(EVT_CMAKE_BIRTHDAY, month, day) != 0)
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
    p[0] = LINK_CMAKE_FOODS;
    p[1] = sum >> 8;
    p[2] = sum;
    p[3] = *data++;
    while (Link_Write(packet) != 0)
        ;
    packet = 0;
    p[0] = LINK_CMAKE_FOODS | LINK_KIND_SECOND;
    p[1] = *data++;
    p[2] = data[0];
    p[3] = data[1];
    while (Link_Write(packet) != 0)
        ;
}

void Link_SendEquipSlot(u8 slot, u8 item)
{
    u32 packet;
    u8 *p = (u8 *)&packet;

    p[0] = LINK_EQUIP_SLOT;
    p[1] = slot;
    p[2] = item;
    p[3] = 0;
    while (Link_Write(packet) != 0)
        ;
}

void Link_SendCmdSlot(slot, item)
u8 slot;
u16 item;
{
    u32 packet;
    u8 *p = (u8 *)&packet;

    p[0] = LINK_CMD_SLOT;
    p[1] = slot;
    *(u16 *)&p[2] = item;
    while (Link_Write(packet) != 0)
        ;
}
