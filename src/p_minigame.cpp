#include "ffcc/p_minigame.h"
#include "global.h"
#include "ffcc/joybus.h"
#include "ffcc/file.h"
#include "ffcc/game.h"
#include "ffcc/linkage.h"
#include "ffcc/memory.h"
#include "ffcc/p_tina.h"
#include "ffcc/cflat_runtime2.h"

#include <dolphin/gba/GBA.h>
#include <dolphin/os.h>
#include <dolphin/si.h>
#include <string.h>
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdio.h>

extern "C" unsigned int g_tempFlag;

extern "C" {
void create__12CMiniGamePcsFv(CMiniGamePcs*);
void destroy__12CMiniGamePcsFv(CMiniGamePcs*);
void calc__12CMiniGamePcsFv(CMiniGamePcs*);
}

inline CMiniGamePcs::CMiniGamePcs()
{
    STATIC_ASSERT(offsetof(CMiniGamePcs, m_managerThread) == 0x8);
    STATIC_ASSERT(offsetof(CMiniGamePcs, m_managerQueue) == 0x320);
    STATIC_ASSERT(offsetof(CMiniGamePcs, m_managerMessage) == 0x340);
    STATIC_ASSERT(offsetof(CMiniGamePcs, m_managerStack) == 0x344);
    STATIC_ASSERT(offsetof(CMiniGamePcs, m_managerTag) == 0x1344);
    STATIC_ASSERT(offsetof(CMiniGamePcs, m_sessionId) == 0x1364);
    STATIC_ASSERT(sizeof(MgGbaContext) == 0x60);
    STATIC_ASSERT(sizeof(MgGbaThreadParam) == 0xC8);
    STATIC_ASSERT(offsetof(MgGbaThreadParam, m_context) == 0x28);
    STATIC_ASSERT(offsetof(MgGbaThreadParam, m_image) == 0x8C);
    STATIC_ASSERT(offsetof(MgGbaThreadParam, m_channel) == 0xBC);
    STATIC_ASSERT(offsetof(CMiniGamePcs, m_gbaParams) == 0x138C);
    STATIC_ASSERT(offsetof(CMiniGamePcs, m_gbaContexts) == 0x16AC);
    STATIC_ASSERT(offsetof(CMiniGamePcs, m_gbaThreads) == 0x1830);
    STATIC_ASSERT(offsetof(CMiniGamePcs, m_flags) == 0x6484);
    STATIC_ASSERT(offsetof(CMiniGamePcs, m_playerMessageReady) == 0x6490);
    STATIC_ASSERT(offsetof(CMiniGamePcs, m_workerStoppedMask) == 0x649D);
    STATIC_ASSERT(sizeof(CMiniGamePcs) == 0x64A0);
    static CProcessTableCallback desc0 = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(create__12CMiniGamePcsFv)};
    static CProcessTableCallback desc1 = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(destroy__12CMiniGamePcsFv)};
    static CProcessTableCallback desc2 = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(calc__12CMiniGamePcsFv)};
    CProcessTable* table = &m_table;

    table->m_fields.m_create = desc0;
    table->m_fields.m_destroy = desc1;
    table->m_fields.m_entries[0].m_callback = desc2;
}

extern const char sMiniGameGbaDvdDir[] = "dvd/gba/";
extern const char sMiniGameClientBinaryName[] = "ffcc_cli.bin";
extern const char sMiniGameObjDataScriptName[] = "objdat.spt";
extern const char sMiniGamePcsGameProcessName[] = "CMiniGamePcs(GAME)";
extern const char sMiniGamePcsProcessName[] = "CMiniGamePcs";
extern const char sMiniGameManagerClassName[] = "CManager";
extern const char sMiniGameProcessClassName[12] = "CProcess";
CProcessTable CMiniGamePcs::m_table = {
    const_cast<char*>(sMiniGamePcsGameProcessName),
    {
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0x24,
    },
};
CMiniGamePcs MiniGamePcs;
static const char s_miniGameManagerTag[] = "GMGR";
static const char s_miniGameEnd0000Text[] = "MiniGameEnd 0000\n";
static const char s_miniGameEnd1111Text[] = "MiniGameEnd 1111\n";
static const char s_miniGameEnd2222Text[] = "MiniGameEnd 2222\n";
static const char s_miniGamePadRaceResultFmt[] = "GBA_PADCODE_RACE_RESULT  play=%d  result=%d\n";
static const char s_miniGamePadRaceEndText[] = "GBA_PADCODE_RACE_END\n";
static const char s_miniGamePadMgrEndText[] = "GBA_PADCODE_MGR_END\n";
static const char s_miniGamePadMgrContinueText[] = "GBA_PADCODE_MGR_CONTINUE\n";
static const char s_miniGameManagerFileFmt[] = "%s/mgr%02d.bin";
static const char s_miniGameManagerDir[] = "dvd/minigame/mgr";
static const char s_miniGameManagerSpFileFmt[] = "%s/mgrsp%02d.bin";
static const char s_miniGameFileInfoFmt[] = "\n\nMINIGAME FILE=%s  SPFILE=%s\n\n\n";
static const char s_miniGameRaceHeader[] = "\n\n===================================================\n\n\nm_IsRaceEnd\n";
static const char s_miniGameRaceResultFmt[] = "    P%d = %d\n";
static const char s_miniGameSeparator[] = "\n\n==================================================\n";
static const char s_miniGameContinueText[] = "\n\nMINI GAME CONTINUE\n\n";
static const char s_miniGameMgrEndStartText[] = "CallMiniGameParam  MGR_CALL_MGR_END\n";
static const char s_miniGameMgrEndEndText[] = "CallMiniGameParam  MGR_CALL_MGR_END OK!!!\n";
static const char s_miniGameEndBannerText[] = "\x83\x7E\x83\x6A\x83\x51\x81\x5B\x83\x80\x8F\x49\x97\xB9\n";
static const char s_miniGameConnectedLineFmt[] = "isConnectedLine Chan=%d  Line = %d\n";
static const char s_miniGameSetPortFmt[] = "chan=%d  MG_GBA_THREAD_MSG_SETPORT_ct=%d\n";
static const char s_miniGameRetryFmt[] = "retry=%d  chan=%d\n";
static const char s_miniGameContextRecvFmt[] = "chan=%d  step=%d  contextRecvOffset=%d\n";
static const char s_miniGameSourceLineFmt[] = "%s : %d\n";
static const char s_miniGameSourceName[] = "p_minigame.cpp";
static const char s_miniGameRecvStatusFmt[] = "ret=%d  status=0x%02x  step=%d  contextRecvOffset=%d\n";
static const char s_miniGameFlagsRetryFmt[] = "GBA_JSTAT_FLAGS_MASK retry chan=%d\n";
static const char s_miniGamePsf1RetryFmt[] = "GBA_JSTAT_PSF1 retry chan=%d\n\0\0";

struct MiniGameAlarm {
    OSAlarm alarm;
    OSThread* thread;
};

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 128b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void GbaThreadSleep(long long ticks)
{
    MiniGameAlarm alarm;
    OSCreateAlarm(&alarm.alarm);
    OSSetAlarmTag(&alarm.alarm, 1);
    OSThread* currentThread = OSGetCurrentThread();
    alarm.thread = currentThread;
    BOOL interruptLevel = OSDisableInterrupts();
    OSSetAlarm(&alarm.alarm, ticks, GbaThreadAlarmHandler);
    OSSuspendThread(alarm.thread);
    OSRestoreInterrupts(interruptLevel);
}

static inline bool MiniGameThreadTimedOut(OSTime start, OSTime timeout)
{
    return OSGetTime() - start > timeout;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void ChgHL16(unsigned short)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 196b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void MiniGameFileRead(char* path, void* destination, unsigned long& size)
{
    CFile::CHandle* handle = File.Open(path, 0, CFile::PRI_LOW);
    if (handle != 0)
    {
        size = File.GetLength(handle);
        File.Read(handle);
        File.SyncCompleted(handle);
        void* buffer = File.m_readBuffer;
        File.Close(handle);
        memcpy(destination, buffer, size);
    }
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 296b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void AdjustGbaImageRegistry(char* image, char* tag)
{
    signed char* bytes = reinterpret_cast<signed char*>(image);
    int offset = 0xA0;
    int checksum = 0xE7;

    bytes[0xAC] = tag[0];
    bytes[0xAD] = tag[1];
    bytes[0xAE] = tag[2];
    bytes[0xAF] = tag[3];

    while (offset < 0xBD)
    {
        checksum -= bytes[offset];
        offset++;
    }
    bytes[offset] = checksum;
}

/*
 * --INFO--
 * PAL Address: 0x8012b09c
 * PAL Size: 52b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void _OpenCallback(MgGbaThreadParam* param, void* context)
{
    MiniGamePcs.OpenCallback(param, context);
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 344b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void getKoubutsuList(unsigned char* food, int player)
{
    for (int i = 0; i < 16; i++)
    {
        food[i] = 0xFF;
    }
    if (Game.m_partyObjArr[player] != 0)
    {
        for (int i = 0; i < 8; i++)
        {
            int foodLevel;
            if (Game.m_gameWork.m_menuStageMode != 0)
            {
                foodLevel = Game.GetFoodLevel(0, i);
            }
            else
            {
                foodLevel = Game.GetFoodLevel(player, i);
            }
            if (foodLevel < 1)
            {
                foodLevel = 1;
            }
            else if (foodLevel > 100)
            {
                foodLevel = 100;
            }
            food[i] = static_cast<unsigned char>(foodLevel);
        }
    }
    else
    {
        for (int i = 0; i < 8; i++)
        {
            food[i] = 5 + i * 100 / 8;
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x8012a5d0
 * PAL Size: 36b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void GbaThreadAlarmHandler(OSAlarm* alarm, OSContext*)
{
    OSResumeThread(reinterpret_cast<MiniGameAlarm*>(alarm)->thread);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaThreadReadInitialCode(MgGbaThreadParam*)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x801290a0
 * PAL Size: 44b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void _GbaThreadMain(void* param)
{
    MiniGamePcs.GbaThreadMain(param);
}

/*
 * --INFO--
 * PAL Address: 0x80128574
 * PAL Size: 44b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void _MngThreadMain(void* param)
{
    MiniGamePcs.MngThreadMain(param);
}

/*
 * --INFO--
 * PAL Address: 0x8012b188
 * PAL Size: 20b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMiniGamePcs::GetTable(unsigned long index)
{
    return reinterpret_cast<int>(&m_table + index);
}

/*
 * --INFO--
 * PAL Address: 0x8012b184
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMiniGamePcs::Init()
{
    return;
}

/*
 * --INFO--
 * PAL Address: 0x8012b180
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMiniGamePcs::Quit()
{
    return;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: TODO
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMiniGamePcs::SetNumPlayer()
{
    m_playerCount = 0;
    for (int player = 0; player < 4; player++)
    {
        if ((m_playerMask & (1 << player)) != 0)
        {
            m_playerCount++;
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x8012b0d4
 * PAL Size: 172b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMiniGamePcs::create()
{
    m_managerState = 0;
    m_managerIndex = 0;
    m_managerImage = 0;
    m_managerSpImage = 0;
    m_managerMode = 0;
    m_playerMask = 0xF;
    m_managerThreadStop = 0;
    SetNumPlayer();
}

/*
 * --INFO--
 * PAL Address: 0x8012b0d0
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMiniGamePcs::destroy()
{
    return;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 368b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMiniGamePcs::EndThread()
{
    if (m_managerImage != 0)
    {
        m_managerThreadStop = 1;

        while (m_managerThreadStop != 0)
        {
            GbaThreadSleep(OSMillisecondsToTicks(100));
        }

        while (OSIsThreadTerminated(&m_managerThread) == 0)
        {
            GbaThreadSleep(OSMillisecondsToTicks(100));
        }

        if (m_managerImage != 0)
        {
            delete m_managerImage;
            m_managerImage = 0;
        }

        if (m_managerSpImage != 0)
        {
            delete m_managerSpImage;
            m_managerSpImage = 0;
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x8012aac8
 * PAL Size: 1492b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMiniGamePcs::MiniGameGo(char* managerFilePath, char* managerSpFilePath)
{
    EndThread();

    m_miniGameParams[0] = -1;
    m_miniGameParams[1] = -1;
    m_miniGameParams[2] = -1;
    m_miniGameParams[3] = -1;
    m_miniGameFailed = 0;
    m_raceEnded = 0;
    m_continueRequested = 0;
    m_statusCode = 0;
    m_miniGameReady = 0;

    m_managerImage =
        new (PartPcs.m_usbStreamState.m_stageLoad, const_cast<char*>(s_miniGameSourceName), 0xF1) unsigned char[0x40000];
    m_managerSpImage =
        new (PartPcs.m_usbStreamState.m_stageLoad, const_cast<char*>(s_miniGameSourceName), 0xF2) unsigned char[0x40000];

    m_sessionId = OSGetTick();
    *reinterpret_cast<unsigned int*>(m_managerImage + 200) = m_sessionId;
    *reinterpret_cast<unsigned int*>(m_managerSpImage + 200) = m_sessionId;

    strncpy(m_managerTag, s_miniGameManagerTag, 4);

    MiniGameFileRead(managerFilePath, m_managerImage, m_managerImageSize);
    AdjustGbaImageRegistry(reinterpret_cast<char*>(m_managerImage), m_managerTag);
    MiniGameFileRead(managerSpFilePath, m_managerSpImage, m_managerSpImageSize);
    AdjustGbaImageRegistry(reinterpret_cast<char*>(m_managerSpImage), m_managerTag);

    u8 gbaStatus[8];
    GBAReset(0, gbaStatus);

    memset(&m_managerThread, 0, sizeof(m_managerThread));
    memset(&m_managerQueue, 0, sizeof(m_managerQueue));
    memset(&m_managerMessage, 0, sizeof(m_managerMessage));
    OSInitMessageQueue(&m_managerQueue, &m_managerMessage, 1);
    OSCreateThread(&m_managerThread,
                   reinterpret_cast<void* (*)(void*)>(_MngThreadMain), 0,
                   m_managerStack + sizeof(m_managerStack), sizeof(m_managerStack), 8, 1);
    OSResumeThread(&m_managerThread);
}

/*
 * --INFO--
 * PAL Address: 0x8012a5f4
 * PAL Size: 1236b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMiniGamePcs::GbaThreadInitGbaContext(MgGbaThreadParam* param, int initMode)
{
    MgGbaContext* gbaContext = &m_gbaContexts[param->m_channel];

    memset(gbaContext, 0, sizeof(MgGbaContext));
    if (initMode == 0)
    {
        gbaContext->m_initialConnect = 1;
    }

    gbaContext->m_channel = param->m_channel;
    gbaContext->m_initialized = 1;
    gbaContext->m_sessionId = m_sessionId;
    gbaContext->m_managerMode = m_managerMode;
    gbaContext->m_playerMask = m_playerMask;

    getKoubutsuList(gbaContext->m_foodLevels[0], 0);
    getKoubutsuList(gbaContext->m_foodLevels[1], 1);
    getKoubutsuList(gbaContext->m_foodLevels[2], 2);
    getKoubutsuList(gbaContext->m_foodLevels[3], 3);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMiniGamePcs::GbaThreadWriteInitialCode(MgGbaThreadParam*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMiniGamePcs::GbaThreadReadContext(MgGbaThreadParam*)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x801290cc
 * PAL Size: 5380b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMiniGamePcs::GbaThreadMain(void* threadParam)
{
    MgGbaThreadParam* param = static_cast<MgGbaThreadParam*>(threadParam);
    unsigned int messageBuf[2];
    unsigned char gbaReadScratch[4];
    unsigned int command;
    unsigned int command7;
    unsigned int command8;
    unsigned int identity7;
    unsigned int identity8;
    int ret;
    int step;
    int contextRecvOffset;
    int retryLine;
    OSTime timeoutTicks;
    OSTime startTime;
    OSTime elapsed;
#define channel (param->m_channel)
#define message (messageBuf[0])

receive_message:
    ret = OSReceiveMessage(&param->m_queue, reinterpret_cast<OSMessage*>(messageBuf), 0);
    if (ret == 0)
    {
        param->m_busy = 0;
        OSReceiveMessage(&param->m_queue, reinterpret_cast<OSMessage*>(messageBuf), 1);
        param->m_stopRequested = 0;
    }

    if (message == 1)
    {
        GbaThreadSleep(OSMillisecondsToTicks(10));
        command = 0x80000000;
        for (int i = 0; i < 100; i++)
        {
            GBAWrite(channel, reinterpret_cast<u8*>(&command), &param->m_status);
            GbaThreadSleep(OSMillisecondsToTicks(10));
        }
        GbaThreadSleep(OSMillisecondsToTicks(10));
        m_workerStoppedMask |= (1 << channel);
        OSExitThread(0);
        return;
    }

    if (message == 7 && param->m_image == 0)
    {
        message = 8;
    }

    param->m_busy = 1;
    contextRecvOffset = 0;
    step = 0;
    param->m_transferComplete = 0;
    switch (message)
    {
    case 3:
        timeoutTicks = OSMillisecondsToTicks(500);
        break;
    case 10:
        timeoutTicks = OSMillisecondsToTicks(500);
        break;
    case 5:
        timeoutTicks = OSMillisecondsToTicks(1000);
        break;
    default:
        timeoutTicks = OSMillisecondsToTicks(1000);
        break;
    }
    startTime = OSGetTime();
    retryLine = 0x22C;
    goto retry_loop;

retry_sleep:
    GbaThreadSleep(OSMillisecondsToTicks(1));

retry_loop:
    if (param->m_stopRequested != 0)
    {
        param->m_result = 3;
        if (param->m_connected != 0)
        {
            System.Printf(const_cast<char*>(s_miniGameConnectedLineFmt), channel, 0x234);
        }
        param->m_connected = 0;
        goto receive_message;
    }

    elapsed = OSGetTime() - startTime;
    if (elapsed > timeoutTicks)
    {
        System.Printf(const_cast<char*>(s_miniGameRetryFmt), retryLine, channel);
        if (ret != 3)
        {
            ret = 1;
        }
        param->m_result = static_cast<unsigned char>(ret);
        if (param->m_connected != 0)
        {
            System.Printf(const_cast<char*>(s_miniGameConnectedLineFmt), channel, 0x241);
        }
        param->m_connected = 0;
        goto receive_message;
    }

    switch (message)
    {
    default:
        goto receive_message;
    case 2:
        if (param->m_connected != 0)
        {
            System.Printf(const_cast<char*>(s_miniGameConnectedLineFmt), channel, 0x248);
        }
        param->m_connected = 0;
        param->m_result = static_cast<unsigned char>(GBAReset(channel, &param->m_status));
        goto receive_message;
    case 3:
        if (param->m_connected != 0)
        {
            System.Printf(const_cast<char*>(s_miniGameConnectedLineFmt), channel, 0x24F);
        }
        param->m_connected = 0;
        ret = GBAReset(channel, &param->m_status);
        if (ret == 0)
        {
            ret = 3;
            retryLine = 0x256;
            goto retry_sleep;
        }
        param->m_result = 0;
        goto receive_message;
    case 4:
        if (param->m_connected != 0)
        {
            System.Printf(const_cast<char*>(s_miniGameConnectedLineFmt), channel, 0x25D);
        }
        param->m_connected = 0;
        ret = GBAGetStatus(channel, &param->m_status);
        if (ret != 0)
        {
            goto comm_fail;
        }
        if ((param->m_status & GBA_JSTAT_RECV) != 0)
        {
            retryLine = 0x266;
            goto retry_loop;
        }
        if (step == 1)
        {
            param->m_result = 0;
            goto receive_message;
        }
        command = 0x50000000;
        ret = GBAWrite(channel, reinterpret_cast<u8*>(&command), &param->m_status);
        if (ret == 0)
        {
            retryLine = 0x274;
            step++;
            goto retry_loop;
        }
        goto comm_fail;
    case 5:
        System.Printf(const_cast<char*>(s_miniGameContextRecvFmt), channel, step, contextRecvOffset);
        if (contextRecvOffset >= 0x60)
        {
            retryLine = 0x27A;
            goto retry_loop;
        }
        ret = GBAGetStatus(channel, &param->m_status);
        if (ret == 0 && (param->m_status & GBA_JSTAT_FLAGS_MASK) == GBA_JSTAT_FLAGS_MASK)
        {
            goto context_proc;
        }
        System.Printf(const_cast<char*>(s_miniGameSourceLineFmt), s_miniGameSourceName, 0x27F);
comm_fail:
        System.Printf(const_cast<char*>(s_miniGameRecvStatusFmt), ret,
                             param->m_status & GBA_JSTAT_FLAGS_MASK, step, contextRecvOffset);
        if (ret == 0)
        {
            ret = 3;
        }
        param->m_result = static_cast<unsigned char>(ret);
        if (param->m_connected != 0)
        {
            System.Printf(const_cast<char*>(s_miniGameConnectedLineFmt), channel, 0x287);
        }
        param->m_connected = 0;
        goto receive_message;

context_proc:
        if (step < 0x19)
        {
            u8* writeSrc;

            if ((param->m_status & GBA_JSTAT_RECV) != 0)
            {
                retryLine = 0x292;
                goto retry_loop;
            }
            if (step == 0)
            {
                writeSrc = reinterpret_cast<u8*>(&command);
                command = 0x30000000;
            }
            else
            {
                writeSrc = reinterpret_cast<u8*>(&m_gbaContexts[channel]) + (step - 1) * 4;
            }
            ret = GBAWrite(channel, writeSrc, &param->m_status);
            if (!(ret == 0 && (param->m_status & GBA_JSTAT_FLAGS_MASK) == GBA_JSTAT_FLAGS_MASK))
            {
                System.Printf(const_cast<char*>(s_miniGameSourceLineFmt), s_miniGameSourceName, 0x2A1);
                goto comm_fail;
            }
            step++;
            goto recv_next;
        }
        else
        {
            if ((param->m_status & GBA_JSTAT_SEND) == 0)
            {
                retryLine = 0x2AA;
                goto retry_loop;
            }
            ret = GBARead(channel, reinterpret_cast<u8*>(&param->m_context) + contextRecvOffset, &param->m_status);
            if (!(ret == 0 && (param->m_status & GBA_JSTAT_FLAGS_MASK) == GBA_JSTAT_FLAGS_MASK))
            {
                System.Printf(const_cast<char*>(s_miniGameSourceLineFmt), s_miniGameSourceName, 0x2B2);
                goto comm_fail;
            }
            contextRecvOffset += 4;
            if (contextRecvOffset == 0x60)
            {
                param->m_connected = 1;
                param->m_bootRetries = 0;
                param->m_connectionReady = 1;
                param->m_result = 0;
                goto receive_message;
            }
recv_next:
            retryLine = 0x2BF;
            goto retry_loop;
        }
    case 6:
        ret = 1;
        if (param->m_connected != 0)
        {
            System.Printf(const_cast<char*>(s_miniGameConnectedLineFmt), channel, 0x2C3);
        }
        param->m_connected = 0;
        param->m_imageType = 1;
        param->m_identityReceived = 0;
        {
            unsigned int probe = SIProbe(channel);
            param->m_lastProbeResult = probe;
            if (probe == 0x80)
            {
                retryLine = 0x2CB;
                goto retry_sleep;
            }
            if (probe == 0x40000)
            {
                param->m_deviceType = probe;
                param->m_result = 0;
            }
            else
            {
                if (probe != 8 && probe != 0x40)
                {
                    param->m_deviceType = probe;
                }
                param->m_result = 1;
            }
        }
        goto receive_message;
    case 7:
        if (param->m_connected != 0)
        {
            System.Printf(const_cast<char*>(s_miniGameConnectedLineFmt), channel, 0x2DC);
        }
        param->m_connected = 0;
        param->m_imageType = 1;
        param->m_identityReceived = 0;

        if (param->m_bootRetries >= 2)
        {
            ret = 1;
            for (int i = 0; i < 100; i++)
            {
                ret = GBAJoyBoot(channel, channel << 1, 2, param->m_image,
                                 param->m_imageSize, &param->m_status);
                if (ret == 0)
                {
                    break;
                }
            }
        }
        else
        {
            ret = GBAJoyBoot(channel, channel << 1, 2, param->m_image,
                             param->m_imageSize, &param->m_status);
            param->m_bootRetries++;
        }

        if (ret == 0)
        {
            GbaThreadInitGbaContext(param, 0);
            message = 8;
            startTime = OSGetTime();
            retryLine = 0x2F7;
            goto retry_loop;
        }

        GbaThreadSleep(OSMillisecondsToTicks(500));
        if (ret == 3)
        {
            if ((param->m_status & (GBA_JSTAT_SEND | GBA_JSTAT_RECV)) == (GBA_JSTAT_SEND | GBA_JSTAT_RECV))
            {
                if ((param->m_status & GBA_JSTAT_FLAGS_MASK) != GBA_JSTAT_PSF0)
                {
                    GBARead(channel, gbaReadScratch, &param->m_status);
                }
            }
            else
            {
                int status;
                int failed;

                status = GBAGetStatus(channel, &param->m_status);
                switch (status)
                {
                case 0:
                    break;
                default:
                    goto identity_done7;
                }
                if (param->m_status != 0x28)
                {
                    status = 1;
                    goto identity_done7;
                }
                status = GBARead(channel, reinterpret_cast<u8*>(&identity7), &param->m_status);
                switch (status)
                {
                case 0:
                    break;
                default:
                    goto identity_done7;
                }
                status = 0;
                param->m_identity = identity7;
                param->m_identityReceived = 1;
identity_done7:;
                if (status == 0 &&
                    (memcmp(&param->m_identity, m_managerTag, 4) == 0 || param->m_identity == 0x414D4752))
                {
                    if (memcmp(&param->m_identity, m_managerTag, 4) == 0)
                    {
                        param->m_imageType = 0;
                    }

                    status = GBAGetStatus(channel, &param->m_status);
                    switch (status)
                    {
                    case 0:
                        break;
                    default:
                        goto write_done7;
                    }
                    if (param->m_status != 0x20)
                    {
                        status = 1;
                        goto write_done7;
                    }
                    status = GBAWrite(channel, reinterpret_cast<u8*>(m_managerTag), &param->m_status);
                    switch (status)
                    {
                    case 0:
                        break;
                    default:
                        goto write_done7;
                    }
                    status = GBAGetStatus(channel, &param->m_status);
                    switch (status)
                    {
                    case 0:
                        break;
                    default:
                        goto write_done7;
                    }
                    if (param->m_status != 0x30)
                    {
                        status = 1;
                        goto write_done7;
                    }
                    status = 0;
write_done7:;
                    if (status != 0)
                    {
                        goto ctx_fail7;
                    }
                    command7 = 0x60000000;
                    status = GBAWrite(channel, reinterpret_cast<u8*>(&command7), &param->m_status);
                    if (!(status == 0 && (param->m_status & GBA_JSTAT_FLAGS_MASK) == GBA_JSTAT_FLAGS_MASK))
                    {
                        failed = 1;
                    }
                    else
                    {
                        int i = 0;
                        do
                        {
                            int st = GBAGetStatus(channel, &param->m_status);
                            if (st != 0 || param->m_status != 0x38)
                            {
                                failed = 1;
                                goto ctx_done7;
                            }
                            st = GBARead(channel, reinterpret_cast<u8*>(&param->m_context) + i, &param->m_status);
                            if (st != 0 || (param->m_status & GBA_JSTAT_FLAGS_MASK) != GBA_JSTAT_FLAGS_MASK)
                            {
                                failed = 1;
                                goto ctx_done7;
                            }
                            i += 4;
                        } while (i < 0x60);
                        failed = 0;
                    }
                }
                else
                {
ctx_fail7:
                    failed = 1;
                }
ctx_done7:
                if (failed == 0)
                {
                    param->m_openCallback(
                        param, reinterpret_cast<void*>(message));
                    goto receive_message;
                }
            }
        }
        retryLine = 0x30F;
        goto retry_sleep;
    case 8:
        if (param->m_connected != 0)
        {
            System.Printf(const_cast<char*>(s_miniGameConnectedLineFmt), channel, 0x312);
        }
        param->m_connected = 0;
        param->m_imageType = 1;
        param->m_identityReceived = 0;
        ret = GBAReset(channel, &param->m_status);
        if (ret != 0)
        {
            retryLine = 0x31A;
            goto retry_sleep;
        }
        {
            int status;
            int failed;

            status = GBAGetStatus(channel, &param->m_status);
            switch (status)
            {
            case 0:
                break;
            default:
                goto identity_done8;
            }
            if (param->m_status != 0x28)
            {
                status = 1;
                goto identity_done8;
            }
            status = GBARead(channel, reinterpret_cast<u8*>(&identity8), &param->m_status);
            switch (status)
            {
            case 0:
                break;
            default:
                goto identity_done8;
            }
            status = 0;
            param->m_identity = identity8;
            param->m_identityReceived = 1;
identity_done8:;
            if (status == 0 &&
                (memcmp(&param->m_identity, m_managerTag, 4) == 0 || param->m_identity == 0x414D4752))
            {
                if (memcmp(&param->m_identity, m_managerTag, 4) == 0)
                {
                    param->m_imageType = 0;
                }
                status = GBAGetStatus(channel, &param->m_status);
                switch (status)
                {
                case 0:
                    break;
                default:
                    goto write_done8;
                }
                if (param->m_status != 0x20)
                {
                    status = 1;
                    goto write_done8;
                }
                status = GBAWrite(channel, reinterpret_cast<u8*>(m_managerTag), &param->m_status);
                switch (status)
                {
                case 0:
                    break;
                default:
                    goto write_done8;
                }
                status = GBAGetStatus(channel, &param->m_status);
                switch (status)
                {
                case 0:
                    break;
                default:
                    goto write_done8;
                }
                if (param->m_status != 0x30)
                {
                    status = 1;
                    goto write_done8;
                }
                status = 0;
write_done8:;
                if (status != 0)
                {
                    goto ctx_fail8;
                }
                command8 = 0x60000000;
                status = GBAWrite(channel, reinterpret_cast<u8*>(&command8), &param->m_status);
                if (!(status == 0 && (param->m_status & GBA_JSTAT_FLAGS_MASK) == GBA_JSTAT_FLAGS_MASK))
                {
                    failed = 1;
                }
                else
                {
                    int i = 0;
                    do
                    {
                        int st = GBAGetStatus(channel, &param->m_status);
                        if (st != 0 || param->m_status != 0x38)
                        {
                            failed = 1;
                            goto ctx_done8;
                        }
                        st = GBARead(channel, reinterpret_cast<u8*>(&param->m_context) + i, &param->m_status);
                        if (st != 0 || (param->m_status & GBA_JSTAT_FLAGS_MASK) != GBA_JSTAT_FLAGS_MASK)
                        {
                            failed = 1;
                            goto ctx_done8;
                        }
                        i += 4;
                    } while (i < 0x60);
                    failed = 0;
                }
            }
            else
            {
ctx_fail8:
                failed = 1;
            }
ctx_done8:
            if (failed == 0)
            {
                param->m_openCallback(
                    param, reinterpret_cast<void*>(message));
                goto receive_message;
            }
            retryLine = 0x322;
        }
        goto retry_sleep;
    case 10:
        if (step == 0)
        {
            if (param->m_connected == 0)
            {
                param->m_result = 1;
                goto receive_message;
            }

            ret = GBAGetStatus(channel, &param->m_status);
            if (!(ret == 0 && (param->m_status & GBA_JSTAT_FLAGS_MASK) == GBA_JSTAT_PSF0))
            {
                GbaThreadSleep(OSMicrosecondsToTicks(100));
                retryLine = 0x333;
                goto retry_loop;
            }

            command = 0x10000000;
            ret = GBAWrite(channel, reinterpret_cast<u8*>(&command), &param->m_status);
            if (ret != 0)
            {
                System.Printf(const_cast<char*>(s_miniGameSourceLineFmt), s_miniGameSourceName, 0x33C);
                goto comm_fail;
            }
            startTime = OSGetTime();
            retryLine = 0x341;
            step++;
            goto retry_loop;
        }

        if (step == 1)
        {
            ret = GBAGetStatus(channel, &param->m_status);
            if ((param->m_status & GBA_JSTAT_FLAGS_MASK) != GBA_JSTAT_FLAGS_MASK)
            {
                GbaThreadSleep(OSMicrosecondsToTicks(100));
                if (OSGetTime() - startTime > OSMillisecondsToTicks(200))
                {
                    System.Printf(const_cast<char*>(s_miniGameFlagsRetryFmt), channel);
                    command = 0x10000000;
                    ret = GBAWrite(channel, reinterpret_cast<u8*>(&command), &param->m_status);
                    startTime = OSGetTime();
                    GbaThreadSleep(OSMicrosecondsToTicks(100));
                }
                retryLine = 0x352;
                goto retry_loop;
            }

            if ((param->m_status & (GBA_JSTAT_SEND | GBA_JSTAT_RECV)) != GBA_JSTAT_SEND)
            {
                retryLine = 0x367;
                goto retry_loop;
            }
            GbaThreadSleep(OSMicrosecondsToTicks(10));
            ret = GBARead(channel, reinterpret_cast<u8*>(&param->m_receivedPacket), &param->m_status);
            if (ret != 0 || ((param->m_receivedPacket >> 24) != 0x20))
            {
                System.Printf(const_cast<char*>(s_miniGameSourceLineFmt), s_miniGameSourceName, 0x372);
                goto comm_fail;
            }
            retryLine = 0x376;
            step++;
            goto retry_loop;
        }

        ret = GBAGetStatus(channel, &param->m_status);
        if (ret != 0 || (param->m_status & GBA_JSTAT_RECV) != 0)
        {
            retryLine = 0x37E;
            goto retry_loop;
        }
        if (ret != 0)
        {
            System.Printf(const_cast<char*>(s_miniGameSourceLineFmt), s_miniGameSourceName, 0x383);
            goto comm_fail;
        }

        if (step == 7)
        {
            ret = GBAGetStatus(channel, &param->m_status);
            if (ret == 0 && (param->m_status & GBA_JSTAT_FLAGS_MASK) != GBA_JSTAT_FLAGS_MASK)
            {
                goto transfer_done;
            }
            if (elapsed > OSMillisecondsToTicks(200))
            {
                System.Printf(const_cast<char*>(s_miniGamePsf1RetryFmt), channel);
                command = 0x70000000;
                ret = GBAWrite(channel, reinterpret_cast<u8*>(&command), &param->m_status);
                if (ret != 0)
                {
                    System.Printf(const_cast<char*>(s_miniGameSourceLineFmt), s_miniGameSourceName, 0x397);
                    goto comm_fail;
                }
                startTime = OSGetTime();
                step = 2;
            }
            GbaThreadSleep(OSMicrosecondsToTicks(1000));
            retryLine = 0x39E;
            goto retry_loop;

transfer_done:
            param->m_transferComplete = 1;
            param->m_result = 0;
            goto receive_message;
        }

        ret = GBAWrite(channel, reinterpret_cast<u8*>(&param->m_sendPackets[step - 2]), &param->m_status);
        GbaThreadSleep(OSMicrosecondsToTicks(100));
        if (ret == 0)
        {
            goto write_next;
        }
        System.Printf(const_cast<char*>(s_miniGameSourceLineFmt), s_miniGameSourceName, 0x3AC);
        goto comm_fail;
write_next:
        retryLine = 0x3B0;
        step++;
        goto retry_loop;
    }
}
#undef channel

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 180b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMiniGamePcs::GbaThreadInit(long channel, MgGbaThreadParam* param, OSThread* thread,
    unsigned char* stackTop, unsigned long stackSize, long priority,
    void (*callback)(MgGbaThreadParam*, void*), unsigned char* image, long imageSize)
{
    memset(param, 0, sizeof(MgGbaThreadParam));
    param->m_channel = channel;
    param->m_openCallback = callback;
    param->m_image = image;
    param->m_imageSize = imageSize;
    memset(thread, 0, sizeof(OSThread));
    OSInitMessageQueue(&param->m_queue, &param->m_message, 1);
    OSCreateThread(thread, reinterpret_cast<void* (*)(void*)>(_GbaThreadMain), param,
                   stackTop, stackSize, priority, 1);
    OSResumeThread(thread);
}

/*
 * --INFO--
 * PAL Address: 0x80128ccc
 * PAL Size: 980b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMiniGamePcs::OpenCallback(MgGbaThreadParam* param, void* context)
{
    int doWrite = 1;
    unsigned char swapByte;
    int swapWord;
    unsigned int baseTick;
    int wasResync = 0;

    if (param->m_connected != 0)
    {
        System.Printf(const_cast<char*>(s_miniGameConnectedLineFmt), static_cast<int>(param->m_channel), 0x3E1);
    }
    param->m_connected = 0;
    param->m_connectionReset = 0;
    param->m_result = 3;
    baseTick = param->m_context.m_tick;
    param->m_context.m_tick = m_gbaContexts[param->m_channel].m_tick;

    if (param->m_context.m_initialConnect == 0)
    {
        if (param->m_context.m_initialized == 0)
        {
            GbaThreadInitGbaContext(param, 1);
            m_gbaContexts[param->m_channel].m_portId = param->m_context.m_portId;
            m_gbaContexts[param->m_channel].m_transferId = param->m_context.m_transferId;
            param->m_lastTick = OSGetTick();
            m_gbaContexts[param->m_channel].m_tick = param->m_lastTick;

            if (param->m_connected != 0)
            {
                System.Printf(const_cast<char*>(s_miniGameConnectedLineFmt), static_cast<int>(param->m_channel), 0x3FC);
            }
            System.Printf(const_cast<char*>(s_miniGameSetPortFmt), static_cast<int>(param->m_channel), g_tempFlag);
            OSSendMessage(&param->m_queue, reinterpret_cast<OSMessage>(5), 1);
        }
        else
        {
            int compareResult = memcmp(&param->m_context, &m_gbaContexts[param->m_channel], 0x60);
            if (compareResult == 0)
            {
                unsigned int savedTick = m_gbaContexts[param->m_channel].m_tick;
                if (baseTick == savedTick || baseTick == param->m_lastTick)
                {
                    m_gbaContexts[param->m_channel].m_tick = baseTick;
                    param->m_lastTick = baseTick;
                    doWrite = 0;
                }
            }
            if (doWrite)
            {
                wasResync = 1;
                OSSendMessage(&param->m_queue, reinterpret_cast<OSMessage>(4), 1);
            }
        }
    }
    else
    {
        swapByte = param->m_context.m_portId;

        param->m_context.m_portId = m_gbaContexts[param->m_channel].m_portId;
        swapWord = param->m_context.m_transferId;
        param->m_context.m_transferId = m_gbaContexts[param->m_channel].m_transferId;

        int compareResult = memcmp(&param->m_context, &m_gbaContexts[param->m_channel], 0x60);
        if (compareResult == 0)
        {
            unsigned int savedTick = m_gbaContexts[param->m_channel].m_tick;
            if (baseTick == savedTick || baseTick == param->m_lastTick)
            {
                m_gbaContexts[param->m_channel].m_tick = baseTick;
                param->m_lastTick = baseTick;
                m_gbaContexts[param->m_channel].m_portId = swapByte;
                m_gbaContexts[param->m_channel].m_transferId = swapWord;
                doWrite = 0;
            }
        }
        if (doWrite)
        {
            OSSendMessage(&param->m_queue, reinterpret_cast<OSMessage>(3), 1);
        }
    }

    if ((!doWrite || wasResync) && GBAGetStatus(static_cast<int>(param->m_channel), &param->m_status) == 0 && param->m_status == 0x30u)
    {
        unsigned int sendTick;
        int readTick;
        int readStatus;

        if (wasResync)
        {
            sendTick = baseTick;
        }
        else
        {
            sendTick = OSGetTick();
            m_gbaContexts[param->m_channel].m_tick = sendTick;
        }

        if (GBAWrite(static_cast<int>(param->m_channel), reinterpret_cast<u8*>(&sendTick), &param->m_status) == 0 &&
            (param->m_status & 0x30) == 0x30 &&
            GBAGetStatus(static_cast<int>(param->m_channel), &param->m_status) == 0 && param->m_status == 0x38u &&
            (readStatus = GBARead(static_cast<int>(param->m_channel), reinterpret_cast<u8*>(&readTick), &param->m_status), !wasResync) &&
            readStatus == 0 &&
            sendTick == readTick && (param->m_status & 0x30) == 0x30)
        {
            param->m_lastTick = sendTick;
            param->m_connected = 1;
            param->m_bootRetries = 0;
            param->m_connectionReady = 1;
            param->m_result = 0;
        }
    }
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 496b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMiniGamePcs::MiniGameEnd()
{
    if (1 <= (unsigned int)System.m_execParam)
    {
        System.Printf(const_cast<char*>(s_miniGameEnd0000Text));
    }

    EndThread();

    m_playerMask = 0xF;
    if (1 <= (unsigned int)System.m_execParam)
    {
        System.Printf(const_cast<char*>(s_miniGameEnd1111Text));
    }

    Joybus.RestartThread();

    if (1 <= (unsigned int)System.m_execParam)
    {
        System.Printf(const_cast<char*>(s_miniGameEnd2222Text));
    }
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 76b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMiniGamePcs::CallMiniGameParam(int code, int param1, int param2)
{
    CFlatRuntime::CStack stack[3];
    stack[0].m_word = code;
    stack[1].m_word = param1;
    stack[2].m_word = param2;
    gCFlatRuntime().SystemCall(0, 1, 8, 3, stack, 0);
}

/*
 * --INFO--
 * PAL Address: 0x801287f0
 * PAL Size: 1244b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */

void CMiniGamePcs::calc(void)
{

    switch (m_managerState) {
    case 1:
        Joybus.ExitThread();
        m_managerState = 2;
    case 2:
        if (!Joybus.IsThreadRunning())
        {
            char managerFile[256];
            char managerSpFile[256];

            sprintf(managerFile, s_miniGameManagerFileFmt, s_miniGameManagerDir, m_managerIndex);
            sprintf(managerSpFile, s_miniGameManagerSpFileFmt, s_miniGameManagerDir, m_managerIndex);

            if ((unsigned int)System.m_execParam >= 3)
            {
                System.Printf(const_cast<char*>(s_miniGameFileInfoFmt), managerFile, managerSpFile);
            }

            MiniGameGo(managerFile, managerSpFile);
            m_managerState = 3;
        }

        return;
    case 3:
        break;
    case 0:
    default:
        return;
    }

    if (m_raceEnded != 0)
    {
        System.Printf(const_cast<char*>(s_miniGameRaceHeader));
        for (int i = 0; i < 4; i++)
        {
            System.Printf(const_cast<char*>(s_miniGameRaceResultFmt), i + 1, static_cast<int>(m_miniGameParams[i]));
        }
        System.Printf(const_cast<char*>(s_miniGameSeparator));

        CallMiniGameParam(0x3000, 0, 0);
        m_raceEnded = 0;
    }

    if (m_continueRequested != 0)
    {
        m_miniGameParams[0] = -1;
        m_miniGameParams[1] = -1;
        m_miniGameParams[2] = -1;
        m_miniGameParams[3] = -1;
        if ((unsigned int)System.m_execParam >= 3)
        {
            System.Printf(const_cast<char*>(s_miniGameContinueText));
        }

        CallMiniGameParam(0x3002, 0, 0);
        m_continueRequested = 0;
    }

    if (m_miniGameFailed == 0)
    {
        return;
    }

    if (1 <= (unsigned int)System.m_execParam)
    {
        System.Printf(const_cast<char*>(s_miniGameMgrEndStartText));
    }

    CallMiniGameParam(0x3001, 0, 0);

    if (1 <= (unsigned int)System.m_execParam)
    {
        System.Printf(const_cast<char*>(s_miniGameMgrEndEndText));
    }

    MiniGameEnd();

    if (1 <= (unsigned int)System.m_execParam)
    {
        System.Printf(g_MsgFlashy);
    }

    if (1 <= (unsigned int)System.m_execParam)
    {
        System.Printf(const_cast<char*>(s_miniGameEndBannerText));
    }

    if (1 <= (unsigned int)System.m_execParam)
    {
        System.Printf(g_MsgFlashy);
    }

    m_miniGameFailed = 0;
    m_managerState = 0;
}

/*
 * --INFO--
 * PAL Address: 0x801285a0
 * PAL Size: 592b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMiniGamePcs::PadCodeProc(int player, unsigned short padCode)
{
    unsigned int rawPadCode = padCode;
    unsigned short codeType = rawPadCode & 0x7F00;

    switch (codeType) {
    case 0x1000:
        if (1 <= (unsigned int)System.m_execParam) {
            System.Printf(g_MsgFlashy);
        }
        if (1 <= (unsigned int)System.m_execParam) {
            System.Printf(const_cast<char*>(s_miniGamePadRaceResultFmt), player, rawPadCode & 0xFF);
        }
        if (1 <= (unsigned int)System.m_execParam) {
            System.Printf(g_MsgFlashy);
        }
        m_miniGameParams[player] = static_cast<signed char>(rawPadCode);
        break;
    case 0x1100:
        if (1 <= (unsigned int)System.m_execParam) {
            System.Printf(g_MsgFlashy);
        }
        if (1 <= (unsigned int)System.m_execParam) {
            System.Printf(const_cast<char*>(s_miniGamePadRaceEndText));
        }
        if (1 <= (unsigned int)System.m_execParam) {
            System.Printf(g_MsgFlashy);
        }
        m_raceEnded = 1;
        break;
    case 0x1200:
        if (1 <= (unsigned int)System.m_execParam) {
            System.Printf(g_MsgFlashy);
        }
        if (1 <= (unsigned int)System.m_execParam) {
            System.Printf(const_cast<char*>(s_miniGamePadMgrEndText));
        }
        if (1 <= (unsigned int)System.m_execParam) {
            System.Printf(g_MsgFlashy);
        }
        m_miniGameFailed = 1;
        break;
    case 0x1300:
        if (1 <= (unsigned int)System.m_execParam) {
            System.Printf(g_MsgFlashy);
        }
        if (1 <= (unsigned int)System.m_execParam) {
            System.Printf(const_cast<char*>(s_miniGamePadMgrContinueText));
        }
        if (1 <= (unsigned int)System.m_execParam) {
            System.Printf(g_MsgFlashy);
        }
        m_continueRequested = 1;
        break;
    }
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 184b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline unsigned long CalcCrc(unsigned long value)
{
    unsigned int crc = 0;
    unsigned int data = ((value >> 16) & 0xFF) | (value & 0xFF00);

    for (int byte = 0; byte < 2; byte++)
    {
        for (unsigned int mask = 0x80; mask != 0; mask >>= 1)
        {
            crc = crc * 2;
            if ((data & mask) != 0)
            {
                if ((crc & 0x100) != 0)
                {
                    crc ^= 0xCC;
                }
                else
                {
                    crc += 1;
                }
            }
            else if ((crc & 0x100) != 0)
            {
                crc ^= 0xCD;
            }
        }
        data >>= 8;
    }

    unsigned int i = 0;
    do
    {
        crc <<= 1;
        if ((crc & 0x100) != 0)
        {
            crc ^= 0xCD;
        }
        i++;
    } while (i < 8);

    return crc;
}

/*
 * --INFO--
 * PAL Address: 0x80127b74
 * PAL Size: 2560b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMiniGamePcs::MngThreadMain(void*)
{
    unsigned char* self = reinterpret_cast<unsigned char*>(this);
    for (int i = 0; i < 4; i++)
    {
        int mode = Game.m_gameWork.m_spModeFlags[i];
        unsigned long imageSize = mode == 0 ? m_managerImageSize : m_managerSpImageSize;
        unsigned char* image = mode == 0 ? m_managerImage : m_managerSpImage;
        GbaThreadInit(i, &m_gbaParams[i], &m_gbaThreads[i], self + 0x2490 + (i + 1) * 0x1000,
                      0x1000, 7, _OpenCallback, image, imageSize);
    }

    OSTime startTime = OSGetTime();
    unsigned int loopCounter = 0;

    while (true)
    {
        GbaThreadSleep(OSMillisecondsToTicks(1));

        if (m_managerThreadStop != 0)
        {
            m_workerStoppedMask = 0;

            for (int i = 0; i <= 3; i++)
            {
                GbaThreadSleep(OSMillisecondsToTicks(100));

                OSSendMessage(&m_gbaParams[i].m_queue, reinterpret_cast<OSMessage>(1), 1);
            }

            GbaThreadSleep(OSMillisecondsToTicks(200));

            while (m_workerStoppedMask != 0x0F)
            {
                GbaThreadSleep(OSMillisecondsToTicks(100));
            }

            do
            {
                int count = 0;
                for (;;)
                {
                    if (OSIsThreadTerminated(&m_gbaThreads[count]) == 0)
                    {
                        break;
                    }
                    count++;
                    if (count > 3)
                    {
                        GbaThreadSleep(OSMillisecondsToTicks(100));

                        m_managerThreadStop = 0;
                        OSExitThread(0);
                        return;
                    }
                }
            } while (true);
        }

        if (m_playerMask != 0)
        {
            unsigned int successMask = 0;
            int i = 0;
            do
            {
                unsigned int bit = 1U << i;
                if ((m_playerMask & bit) != 0 && m_gbaParams[i].m_busy == 0)
                {
                    if (m_gbaParams[i].m_deviceType == 0x40000)
                    {
                        switch ((s32)m_gbaParams[i].m_result)
                        {
                        case 0:
                            if (m_gbaParams[i].m_connected == 0)
                            {
                                if (m_gbaParams[i].m_connectionReset != 0)
                                {
                                    goto disconnect_player;
                                }
                                m_statusCode = 0;
                                if (i == -1)
                                {
                                    OSSendMessage(&m_gbaParams[i].m_queue, reinterpret_cast<OSMessage>(8), 1);
                                }
                                else
                                {
                                    OSSendMessage(&m_gbaParams[i].m_queue, reinterpret_cast<OSMessage>(7), 1);
                                }
                            }
                            else if (m_gbaParams[i].m_connectionReady != 0)
                            {
                                m_gbaParams[i].m_connectionReset = 1;
                                m_playerMessageReady[i] = 1;
                                successMask = (successMask | bit) & 0xFF;
                                m_receivedWords[i] = 0;
                            }
                            else
                            {
                                if (m_gbaParams[i].m_transferComplete != 0)
                                {
                                    unsigned int packet = m_gbaParams[i].m_receivedPacket;
                                    unsigned int crc = CalcCrc(packet);
                                    if ((packet & 0xFF) == (crc & 0xFF))
                                    {
                                        m_playerMessageReady[i] = m_gbaParams[i].m_transferComplete;
                                        successMask = (successMask | bit) & 0xFF;
                                        m_receivedWords[i] =
                                            m_gbaParams[i].m_receivedPacket & 0xFFFF00;
                                    }
                                }
                            }
                            break;
                        case 3:
                            m_gbaParams[i].m_deviceType = 0;
                            break;
                        default:
                            m_gbaParams[i].m_deviceType = 0;
                            break;
                        }
                    }
                    else if (m_gbaParams[i].m_deviceType == 0 || (int)(loopCounter & 0x1F) == 0)
                    {
                        OSTime now = OSGetTime();
                        if ((s64)OSMillisecondsToTicks(5000) < now - startTime)
                        {
disconnect_player:
                            if ((m_playerMask & bit) != 0)
                            {
                                m_playerMask = static_cast<unsigned char>(m_playerMask & ~bit);
                                if (m_playerMask == 0)
                                {
                                    m_miniGameFailed = 1;
                                    goto next_player;
                                }
                                m_playerMessageReady[i] = 1;
                                m_receivedWords[i] = 0x40000000;
                                m_receivedWords[i] |= 0x12000;
                                unsigned long crc = CalcCrc(m_receivedWords[i]);
                                m_receivedWords[i] |= crc & 0xFF;
                            }
                        }
                        OSSendMessage(&m_gbaParams[i].m_queue, reinterpret_cast<OSMessage>(6), 1);
                    }
                }
next_player:
                i++;
            } while (i <= 3);

            if (successMask == (m_playerMask & 0xF))
            {
                m_miniGameReady = 1;
                int j = 0;
                do
                {
                    unsigned int word = m_receivedWords[j];
                    unsigned int masked = word & 0xFFFF00;
                    if ((word & 0x8000) != 0)
                    {
                        PadCodeProc(j, static_cast<unsigned short>(masked | ((int)(unsigned short)(masked >> 8) >> 8)));
                    }
                    unsigned int crc = 0;
                    m_broadcastWords[j] = (j + 0x40) * 0x1000000;
                    m_broadcastWords[j] =
                        m_broadcastWords[j] | masked;
                    crc = CalcCrc(m_broadcastWords[j]);
                    m_broadcastWords[j] = m_broadcastWords[j] | (crc & 0xFF);
                    j++;
                } while (j < 4);

                unsigned int seqCrc = 0;
                m_broadcastWords[4] = 0x44000000;
                m_broadcastWords[4] =
                    m_broadcastWords[4] |
                    (static_cast<unsigned int>(static_cast<unsigned short>(
                         m_statusCode >> 8 |
                         m_statusCode << 8)) << 8);
                seqCrc = CalcCrc(m_broadcastWords[4]);
                int k = 0;
                m_broadcastWords[4] =
                    m_broadcastWords[4] | (seqCrc & 0xFF);
                do
                {
                    if ((successMask & (1U << k)) != 0)
                    {
                        m_gbaParams[k].m_connectionReady = 0;
                        memcpy(m_gbaParams[k].m_sendPackets, m_broadcastWords, sizeof(m_broadcastWords));
                        OSSendMessage(&m_gbaParams[k].m_queue, reinterpret_cast<OSMessage>(10), 1);
                    }
                    k++;
                } while (k < 4);

                m_statusCode = static_cast<short>(m_statusCode + 1);
                if (0x0FFF <= m_statusCode)
                {
                    m_statusCode = 0x0FFF;
                }
            }
        }

        loopCounter += 1;
    }
}
