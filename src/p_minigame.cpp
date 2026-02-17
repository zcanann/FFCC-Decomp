#include "ffcc/p_minigame.h"
#include "ffcc/file.h"
#include "ffcc/memory.h"

#include <dolphin/gba/GBA.h>
#include <string.h>

extern CMiniGamePcs MiniGamePcs;
extern unsigned char PartPcs[];
extern unsigned int lbl_802121A8[];
extern unsigned int lbl_802121B4[];
extern unsigned int lbl_802121C0[];
extern unsigned int lbl_802121CC[];
extern unsigned int lbl_80212348[];
extern int DAT_800000f8;
extern char DAT_80331bf0[];

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
    unsigned int* table = lbl_802121CC;
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
 * Address:	TODO
 * Size:	TODO
 */
void CMiniGamePcs::GetTable(unsigned long)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMiniGamePcs::Init()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMiniGamePcs::Quit()
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CMiniGamePcs::destroy()
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CMiniGamePcs::OpenCallback(MgGbaThreadParam*, void*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMiniGamePcs::calc()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMiniGamePcs::PadCodeProc(int, unsigned short)
{
	// TODO
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
