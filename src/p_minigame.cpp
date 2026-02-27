#include "ffcc/p_minigame.h"
#include "ffcc/joybus.h"
#include "ffcc/file.h"
#include "ffcc/memory.h"

#include <dolphin/gba/GBA.h>
#include <string.h>

extern CMiniGamePcs MiniGamePcs;
extern unsigned char CFlat[];
extern unsigned char PartPcs[];
extern unsigned int lbl_802121A8[];
extern unsigned int lbl_802121B4[];
extern unsigned int lbl_802121C0[];
extern unsigned char lbl_802121CC[];
extern unsigned int lbl_80212348[];
extern int DAT_800000f8;
extern char DAT_80331bf0[];

extern "C" void Printf__7CSystemFPce(CSystem* system, const char* format, ...);
extern "C" int sprintf(char* buffer, const char* format, ...);
extern "C" int memcmp(const void* lhs, const void* rhs, unsigned long count);
extern "C" void SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack(
    void* flatRuntime, int object, int a, int b, int c, void* inStack, void* outStack);

extern "C" void* __nwa__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);
extern "C" void __dl__FPv(void*);

/*
 * --INFO--
 * PAL Address: 0x8012b19c
 * PAL Size: 176b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void __sinit_p_minigame_cpp(void)
{
    unsigned int* table = reinterpret_cast<unsigned int*>(lbl_802121CC);
    unsigned int* desc0 = lbl_802121A8;
    unsigned int* desc1 = lbl_802121B4;
    unsigned int* desc2 = lbl_802121C0;

    *reinterpret_cast<unsigned int*>(&MiniGamePcs) = reinterpret_cast<unsigned int>(lbl_80212348);

    table[1] = desc0[0];
    table[2] = desc0[1];
    table[3] = desc0[2];
    table[4] = desc1[0];
    table[5] = desc1[1];
    table[6] = desc1[2];
    table[7] = desc2[0];
    table[8] = desc2[1];
    table[9] = desc2[2];
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
 * Address:	TODO
 * Size:	TODO
 */
void MiniGameFileRead(char*, void*, unsigned long&)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CalcCrc(unsigned long)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void AdjustGbaImageRegistry(char*, char*)
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void getKoubutsuList(unsigned char*, int)
{
	// TODO
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
    OSResumeThread(reinterpret_cast<OSThread*>(alarm->start));
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GbaThreadSleep(long long)
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
CMiniGamePcs::CMiniGamePcs()
{
	// TODO
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
    return (int)(lbl_802121CC + (int)index * 0x15C);
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
 * PAL Address: 0x8012b0d4
 * PAL Size: 172b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMiniGamePcs::create()
{
    unsigned char* self = reinterpret_cast<unsigned char*>(this);

    self[0x1348] = 0;
    self[0x1350] = 0;
    *reinterpret_cast<unsigned int*>(self + 0x1354) = 0;
    *reinterpret_cast<unsigned int*>(self + 0x135C) = 0;
    self[0x134A] = 0;
    self[0x134B] = 0xF;
    self[0x649C] = 0;
    self[0x134C] = 0;

    if ((self[0x134B] & 1) != 0)
    {
        self[0x134C] += 1;
    }

    if ((self[0x134B] & 2) != 0)
    {
        self[0x134C] += 1;
    }

    if ((self[0x134B] & 4) != 0)
    {
        self[0x134C] += 1;
    }

    if ((self[0x134B] & 8) != 0)
    {
        self[0x134C] += 1;
    }
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
 * PAL Address: 0x8012aac8
 * PAL Size: 1492b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMiniGamePcs::MiniGameGo(char* managerFilePath, char* managerSpFilePath)
{
    unsigned char* self = reinterpret_cast<unsigned char*>(this);

    if (*reinterpret_cast<int*>(self + 0x1354) != 0)
    {
        self[0x649C] = 1;

        while (self[0x649C] != 0)
        {
            OSAlarm alarm;

            OSCreateAlarm(&alarm);
            OSSetAlarmTag(&alarm, 1);
            OSThread* currentThread = OSGetCurrentThread();
            alarm.start = reinterpret_cast<OSTime>(currentThread);

            BOOL interruptLevel = OSDisableInterrupts();
            OSSetAlarm(&alarm, (DAT_800000f8 / 4000) * 100, GbaThreadAlarmHandler);
            OSSuspendThread(currentThread);
            OSRestoreInterrupts(interruptLevel);
        }

        while (OSIsThreadTerminated(reinterpret_cast<OSThread*>(self + 8)) == 0)
        {
            OSAlarm alarm;

            OSCreateAlarm(&alarm);
            OSSetAlarmTag(&alarm, 1);
            OSThread* currentThread = OSGetCurrentThread();
            alarm.start = reinterpret_cast<OSTime>(currentThread);

            BOOL interruptLevel = OSDisableInterrupts();
            OSSetAlarm(&alarm, (DAT_800000f8 / 4000) * 100, GbaThreadAlarmHandler);
            OSSuspendThread(currentThread);
            OSRestoreInterrupts(interruptLevel);
        }

        if (*reinterpret_cast<void**>(self + 0x1354) != 0)
        {
            __dl__FPv(*reinterpret_cast<void**>(self + 0x1354));
            *reinterpret_cast<void**>(self + 0x1354) = 0;
        }

        if (*reinterpret_cast<void**>(self + 0x135C) != 0)
        {
            __dl__FPv(*reinterpret_cast<void**>(self + 0x135C));
            *reinterpret_cast<void**>(self + 0x135C) = 0;
        }
    }

    self[0x6498] = 0xFF;
    self[0x6499] = 0xFF;
    self[0x649A] = 0xFF;
    self[0x649B] = 0xFF;
    self[0x6495] = 0;
    self[0x6496] = 0;
    self[0x6497] = 0;
    *reinterpret_cast<unsigned short*>(self + 0x134E) = 0;
    self[0x6494] = 0;

    CMemory::CStage* stageLoad = reinterpret_cast<CMemory::CStage*>(PartPcs + 0x20);
    *reinterpret_cast<void**>(self + 0x1354) =
        __nwa__FUlPQ27CMemory6CStagePci(0x40000, stageLoad, "p_minigame.cpp", 0xF1);
    *reinterpret_cast<void**>(self + 0x135C) =
        __nwa__FUlPQ27CMemory6CStagePci(0x40000, stageLoad, "p_minigame.cpp", 0xF2);

    *reinterpret_cast<unsigned int*>(self + 0x1364) = OSGetTick();
    *reinterpret_cast<unsigned int*>(*reinterpret_cast<unsigned int*>(self + 0x1354) + 200) =
        *reinterpret_cast<unsigned int*>(self + 0x1364);
    *reinterpret_cast<unsigned int*>(*reinterpret_cast<unsigned int*>(self + 0x135C) + 200) =
        *reinterpret_cast<unsigned int*>(self + 0x1364);

    strncpy(reinterpret_cast<char*>(self + 0x1344), DAT_80331bf0, 4);

    void* managerImage = *reinterpret_cast<void**>(self + 0x1354);
    CFile::CHandle* fileHandle = File.Open(managerFilePath, 0, CFile::PRI_LOW);
    if (fileHandle != 0)
    {
        *reinterpret_cast<unsigned int*>(self + 0x1358) = File.GetLength(fileHandle);
        File.Read(fileHandle);
        File.SyncCompleted(fileHandle);
        void* readBuffer = File.m_readBuffer;
        File.Close(fileHandle);
        memcpy(managerImage, readBuffer, *reinterpret_cast<unsigned int*>(self + 0x1358));
    }

    int offset = 0xA0;
    int managerBase = *reinterpret_cast<int*>(self + 0x1354);
    char checksum = static_cast<char>(-0x19);

    *reinterpret_cast<unsigned char*>(managerBase + 0xAC) = self[0x1344];
    *reinterpret_cast<unsigned char*>(managerBase + 0xAD) = self[0x1345];
    *reinterpret_cast<unsigned char*>(managerBase + 0xAE) = self[0x1346];
    *reinterpret_cast<unsigned char*>(managerBase + 0xAF) = self[0x1347];

    for (int i = 0; i < 2; i++)
    {
        char* bytes = reinterpret_cast<char*>(managerBase + offset);
        char* bytes2 = reinterpret_cast<char*>(managerBase + offset + 7);

        checksum = (((((((((((((checksum - bytes[0]) - bytes[1]) - bytes[2]) - bytes[3]) - bytes[4]) -
                        bytes[5]) - bytes[6]) - bytes2[0]) - bytes2[1]) - bytes2[2]) - bytes2[3]) -
                     bytes2[4]) - bytes2[5]) - bytes2[6];
        offset += 0xE;
    }

    for (; offset < 0xBD; offset++)
    {
        checksum -= *reinterpret_cast<char*>(managerBase + offset);
    }
    *reinterpret_cast<char*>(managerBase + offset) = checksum;

    void* managerSpImage = *reinterpret_cast<void**>(self + 0x135C);
    fileHandle = File.Open(managerSpFilePath, 0, CFile::PRI_LOW);
    if (fileHandle != 0)
    {
        *reinterpret_cast<unsigned int*>(self + 0x1360) = File.GetLength(fileHandle);
        File.Read(fileHandle);
        File.SyncCompleted(fileHandle);
        void* readBuffer = File.m_readBuffer;
        File.Close(fileHandle);
        memcpy(managerSpImage, readBuffer, *reinterpret_cast<unsigned int*>(self + 0x1360));
    }

    offset = 0xA0;
    managerBase = *reinterpret_cast<int*>(self + 0x135C);
    checksum = static_cast<char>(-0x19);

    *reinterpret_cast<unsigned char*>(managerBase + 0xAC) = self[0x1344];
    *reinterpret_cast<unsigned char*>(managerBase + 0xAD) = self[0x1345];
    *reinterpret_cast<unsigned char*>(managerBase + 0xAE) = self[0x1346];
    *reinterpret_cast<unsigned char*>(managerBase + 0xAF) = self[0x1347];

    for (int i = 0; i < 2; i++)
    {
        char* bytes = reinterpret_cast<char*>(managerBase + offset);
        char* bytes2 = reinterpret_cast<char*>(managerBase + offset + 7);

        checksum = (((((((((((((checksum - bytes[0]) - bytes[1]) - bytes[2]) - bytes[3]) - bytes[4]) -
                        bytes[5]) - bytes[6]) - bytes2[0]) - bytes2[1]) - bytes2[2]) - bytes2[3]) -
                     bytes2[4]) - bytes2[5]) - bytes2[6];
        offset += 0xE;
    }

    for (; offset < 0xBD; offset++)
    {
        checksum -= *reinterpret_cast<char*>(managerBase + offset);
    }
    *reinterpret_cast<char*>(managerBase + offset) = checksum;

    u8 gbaStatus[8];
    GBAReset(0, gbaStatus);

    memset(self + 8, 0, 0x318);
    memset(self + 800, 0, 0x20);
    memset(self + 0x340, 0, 4);
    OSInitMessageQueue(reinterpret_cast<OSMessageQueue*>(self + 800),
                       reinterpret_cast<OSMessage*>(self + 0x340), 1);
    OSCreateThread(reinterpret_cast<OSThread*>(self + 8),
                   reinterpret_cast<void* (*)(void*)>(_MngThreadMain), 0, self + 0x1344, 0x1000,
                   8, 1);
    OSResumeThread(reinterpret_cast<OSThread*>(self + 8));
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMiniGamePcs::GbaThreadInitGbaContext(MgGbaThreadParam*, int)
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CMiniGamePcs::GbaThreadMain(void*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMiniGamePcs::GbaThreadInit(long, MgGbaThreadParam*, OSThread*, unsigned char*, unsigned long, long, void (*) (MgGbaThreadParam*, void*), unsigned char*, long)
{
	// TODO
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
    unsigned char* self = reinterpret_cast<unsigned char*>(this);
    unsigned char* paramBytes = reinterpret_cast<unsigned char*>(context);
    int channel = static_cast<int>(paramBytes[0xBC]);
    int stateOffset = channel * 0x60;
    bool doWrite = true;
    bool wasResync = false;
    int baseTick = *reinterpret_cast<int*>(paramBytes + 0x30);

    if (paramBytes[0xC4] != 0)
    {
        Printf__7CSystemFPce(&System, "isConnectedLine=%d,Line=%d\n", channel, 0x3E1);
    }
    paramBytes[0xC4] = 0;
    paramBytes[0xC6] = 0;
    paramBytes[0xBF] = 3;
    *reinterpret_cast<int*>(paramBytes + 0x30) = *reinterpret_cast<int*>(self + stateOffset + 0x16B4);

    if (paramBytes[0x28] == 0)
    {
        if (paramBytes[0x2B] == 0)
        {
            GbaThreadInitGbaContext(param, 1);
            self[stateOffset + 0x16AE] = paramBytes[0x2A];
            *reinterpret_cast<int*>(self + stateOffset + 0x16B8) = *reinterpret_cast<int*>(paramBytes + 0x34);
            *reinterpret_cast<int*>(paramBytes + 0x88) = OSGetTick();
            *reinterpret_cast<int*>(self + stateOffset + 0x16B4) = *reinterpret_cast<int*>(paramBytes + 0x88);

            if (paramBytes[0xC4] != 0)
            {
                Printf__7CSystemFPce(&System, "isConnectedLine=%d,Line=%d\n", channel, 0x3FC);
            }
            Printf__7CSystemFPce(&System, "chan=%d MG_GBA_THREAD_MSG_SETPORT line=%d\n", channel, 0x403);
            OSSendMessage(reinterpret_cast<OSMessageQueue*>(paramBytes), reinterpret_cast<OSMessage>(5), 1);
        }
        else
        {
            int compareResult = memcmp(paramBytes + 0x28, self + stateOffset + 0x16AC, 0x60);
            if (compareResult == 0)
            {
                int savedTick = *reinterpret_cast<int*>(self + stateOffset + 0x16B4);
                int currentTick = *reinterpret_cast<int*>(paramBytes + 0x88);
                if (baseTick == savedTick || baseTick == currentTick)
                {
                    *reinterpret_cast<int*>(self + stateOffset + 0x16B4) = baseTick;
                    *reinterpret_cast<int*>(paramBytes + 0x88) = baseTick;
                    doWrite = false;
                }
            }
            if (doWrite)
            {
                wasResync = true;
                OSSendMessage(reinterpret_cast<OSMessageQueue*>(paramBytes), reinterpret_cast<OSMessage>(4), 1);
            }
        }
    }
    else
    {
        unsigned char swapByte = paramBytes[0x2A];
        int swapWord = *reinterpret_cast<int*>(paramBytes + 0x34);

        paramBytes[0x2A] = self[stateOffset + 0x16AE];
        *reinterpret_cast<int*>(paramBytes + 0x34) = *reinterpret_cast<int*>(self + stateOffset + 0x16B8);

        int compareResult = memcmp(paramBytes + 0x28, self + stateOffset + 0x16AC, 0x60);
        if (compareResult == 0)
        {
            int savedTick = *reinterpret_cast<int*>(self + stateOffset + 0x16B4);
            int currentTick = *reinterpret_cast<int*>(paramBytes + 0x88);
            if (baseTick == savedTick || baseTick == currentTick)
            {
                *reinterpret_cast<int*>(self + stateOffset + 0x16B4) = baseTick;
                *reinterpret_cast<int*>(paramBytes + 0x88) = baseTick;
                self[stateOffset + 0x16AE] = swapByte;
                *reinterpret_cast<int*>(self + stateOffset + 0x16B8) = swapWord;
                doWrite = false;
            }
        }
        if (doWrite)
        {
            OSSendMessage(reinterpret_cast<OSMessageQueue*>(paramBytes), reinterpret_cast<OSMessage>(3), 1);
        }
    }

    if ((!doWrite || wasResync) && GBAGetStatus(channel, paramBytes + 0xC0) == 0 && paramBytes[0xC0] == '0')
    {
        int sendTick = baseTick;
        int readTick = 0;

        if (!wasResync)
        {
            sendTick = OSGetTick();
            *reinterpret_cast<int*>(self + stateOffset + 0x16B4) = sendTick;
        }

        if (GBAWrite(channel, reinterpret_cast<u8*>(&sendTick), paramBytes + 0xC0) == 0 &&
            (paramBytes[0xC0] & 0x30) == 0x30 &&
            GBAGetStatus(channel, paramBytes + 0xC0) == 0 && paramBytes[0xC0] == '8' &&
            !wasResync &&
            GBARead(channel, reinterpret_cast<u8*>(&readTick), paramBytes + 0xC0) == 0 &&
            sendTick == readTick && (paramBytes[0xC0] & 0x30) == 0x30)
        {
            *reinterpret_cast<int*>(paramBytes + 0x88) = sendTick;
            paramBytes[0xC4] = 1;
            paramBytes[0xC7] = 0;
            paramBytes[0xC5] = 1;
            paramBytes[0xBF] = 0;
        }
    }
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
    unsigned char* self = reinterpret_cast<unsigned char*>(this);

    if (self[0x1348] == 0)
    {
        return;
    }

    if (self[0x1348] == 1)
    {
        Joybus.ExitThread();
        self[0x1348] = 2;
    }

    if (self[0x1348] == 2)
    {
        if (!Joybus.IsThreadRunning())
        {
            char managerFile[260];
            char managerSpFile[256];

            sprintf(managerFile, "%s/mgr%02d.bin", "dvd/minigame", self[0x1350]);
            sprintf(managerSpFile, "%s/mgrsp%02d.bin", "dvd/minigame", self[0x1350]);

            if ((unsigned int)System.m_execParam > 2)
            {
                Printf__7CSystemFPce(&System, "MINIGAME FILE=%s SPFILE=%s\n", managerFile, managerSpFile);
            }

            MiniGameGo(managerFile, managerSpFile);
            self[0x1348] = 3;
        }

        return;
    }

    if (self[0x1348] != 3)
    {
        return;
    }

    if (self[0x6496] != 0)
    {
        int raceEndStack[3];

        Printf__7CSystemFPce(&System, "--------------------------------\n");
        for (int i = 0; i < 4; i++)
        {
            Printf__7CSystemFPce(&System, "P%d = %d\n", i + 1, static_cast<int>(self[0x6498 + i]));
        }
        Printf__7CSystemFPce(&System, "--------------------------------\n");

        raceEndStack[0] = 0x3000;
        raceEndStack[1] = 0;
        raceEndStack[2] = 0;
        SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack(
            &CFlat, 0, 1, 8, 3, raceEndStack, 0);
        self[0x6496] = 0;
    }

    if (self[0x6497] != 0)
    {
        int continueStack[3];

        self[0x6498] = 0xFF;
        self[0x6499] = 0xFF;
        self[0x649A] = 0xFF;
        self[0x649B] = 0xFF;
        if ((unsigned int)System.m_execParam > 2)
        {
            Printf__7CSystemFPce(&System, "MINI GAME CONTINUE\n");
        }

        continueStack[0] = 0x3002;
        continueStack[1] = 0;
        continueStack[2] = 0;
        SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack(
            &CFlat, 0, 1, 8, 3, continueStack, 0);
        self[0x6497] = 0;
    }

    if (self[0x6495] == 0)
    {
        return;
    }

    if (System.m_execParam != 0)
    {
        Printf__7CSystemFPce(&System, "CallMiniGameParam MGR_CALL_MGR_END:START\n");
    }

    {
        int mgrEndStack[3];
        mgrEndStack[0] = 0x3001;
        mgrEndStack[1] = 0;
        mgrEndStack[2] = 0;
        SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack(
            &CFlat, 0, 1, 8, 3, mgrEndStack, 0);
    }

    if (System.m_execParam != 0)
    {
        Printf__7CSystemFPce(&System, "CallMiniGameParam MGR_CALL_MGR_END:END\n");
        Printf__7CSystemFPce(&System, "MiniGameEnd 0000\n");
    }

    if (*reinterpret_cast<void**>(self + 0x1354) != 0)
    {
        self[0x649C] = 1;
        while (self[0x649C] != 0)
        {
            OSAlarm alarm;

            OSCreateAlarm(&alarm);
            OSSetAlarmTag(&alarm, 1);
            OSThread* currentThread = OSGetCurrentThread();
            alarm.start = reinterpret_cast<OSTime>(currentThread);

            BOOL interruptLevel = OSDisableInterrupts();
            OSSetAlarm(&alarm, (DAT_800000f8 / 4000) * 100, GbaThreadAlarmHandler);
            OSSuspendThread(currentThread);
            OSRestoreInterrupts(interruptLevel);
        }

        while (OSIsThreadTerminated(reinterpret_cast<OSThread*>(self + 8)) == 0)
        {
            OSAlarm alarm;

            OSCreateAlarm(&alarm);
            OSSetAlarmTag(&alarm, 1);
            OSThread* currentThread = OSGetCurrentThread();
            alarm.start = reinterpret_cast<OSTime>(currentThread);

            BOOL interruptLevel = OSDisableInterrupts();
            OSSetAlarm(&alarm, (DAT_800000f8 / 4000) * 100, GbaThreadAlarmHandler);
            OSSuspendThread(currentThread);
            OSRestoreInterrupts(interruptLevel);
        }

        if (*reinterpret_cast<void**>(self + 0x1354) != 0)
        {
            __dl__FPv(*reinterpret_cast<void**>(self + 0x1354));
            *reinterpret_cast<void**>(self + 0x1354) = 0;
        }

        if (*reinterpret_cast<void**>(self + 0x135C) != 0)
        {
            __dl__FPv(*reinterpret_cast<void**>(self + 0x135C));
            *reinterpret_cast<void**>(self + 0x135C) = 0;
        }
    }

    self[0x134B] = 0xF;
    if (System.m_execParam != 0)
    {
        Printf__7CSystemFPce(&System, "MiniGameEnd 1111\n");
    }

    Joybus.RestartThread();

    if (System.m_execParam != 0)
    {
        Printf__7CSystemFPce(&System, "MiniGameEnd 2222\n");
        Printf__7CSystemFPce(&System, "--------------------------------\n");
        Printf__7CSystemFPce(&System, "     MINI GAME END \n");
        Printf__7CSystemFPce(&System, "--------------------------------\n");
    }

    self[0x6495] = 0;
    self[0x1348] = 0;
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
    unsigned short codeType = padCode & 0x7F00;
    unsigned char* self = reinterpret_cast<unsigned char*>(this);

    if (codeType == 0x1200)
    {
        if (System.m_execParam != 0)
        {
            Printf__7CSystemFPce(&System, "--------------------------------\n");
            Printf__7CSystemFPce(&System, "GBA PADCODE MGR END\n");
            Printf__7CSystemFPce(&System, "--------------------------------\n");
        }
        self[0x6495] = 1;
    }
    else if (codeType == 0x1100)
    {
        if (System.m_execParam != 0)
        {
            Printf__7CSystemFPce(&System, "--------------------------------\n");
            Printf__7CSystemFPce(&System, "GBA PADCODE RACE END\n");
            Printf__7CSystemFPce(&System, "--------------------------------\n");
        }
        self[0x6496] = 1;
    }
    else if (codeType == 0x1000)
    {
        if (System.m_execParam != 0)
        {
            Printf__7CSystemFPce(&System, "--------------------------------\n");
            Printf__7CSystemFPce(&System, "GBA PADCODE RACE RESULT play=%d r=%d\n", player, padCode & 0xFF);
            Printf__7CSystemFPce(&System, "--------------------------------\n");
        }
        self[0x6498 + player] = static_cast<unsigned char>(padCode);
    }
    else if (codeType == 0x1300)
    {
        if (System.m_execParam != 0)
        {
            Printf__7CSystemFPce(&System, "--------------------------------\n");
            Printf__7CSystemFPce(&System, "GBA PADCODE MGR CONTINUE\n");
            Printf__7CSystemFPce(&System, "--------------------------------\n");
        }
        self[0x6497] = 1;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMiniGamePcs::EndThread()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMiniGamePcs::MngThreadMain(void*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMiniGamePcs::MiniGameEnd()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMiniGamePcs::CallMiniGameParam(int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMiniGamePcs::SetNumPlayer()
{
	// TODO
}
