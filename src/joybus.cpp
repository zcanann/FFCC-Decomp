#include "ffcc/joybus.h"

#include "ffcc/file.h"
#include "ffcc/gbaque.h"
#include "ffcc/system.h"

#include <dolphin/gba/GBA.h>
#include "dolphin/os.h"
#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/printf.h"
#include <Runtime.PPCEABI.H/NMWException.h>

#include "string.h"

extern int DAT_800000f8 = 0;
extern int DAT_8032edb8 = 0;
extern "C" void __dt__6JoyBusFv(void*);
extern unsigned char ARRAY_802eaab0[];

const unsigned short JoyBusCrcTable[256] =
{
    0x0000, 0x1021, 0x2042, 0x3063,
    0x4084, 0x50A5, 0x60C6, 0x70E7,
    0x8108, 0x9129, 0xA14A, 0xB16B,
    0xC18C, 0xD1AD, 0xE1CE, 0xF1EF,

    0x1231, 0x0210, 0x3273, 0x2252,
    0x52B5, 0x4294, 0x72F7, 0x62D6,
    0x9339, 0x8318, 0xB37B, 0xA35A,
    0xD3BD, 0xC39C, 0xF3FF, 0xE3DE,

    0x2462, 0x3443, 0x0420, 0x1401,
    0x64E6, 0x74C7, 0x44A4, 0x5485,
    0xA56A, 0xB54B, 0x8528, 0x9509,
    0xE5EE, 0xF5CF, 0xC5AC, 0xD58D,

    0x3653, 0x2672, 0x1611, 0x0630,
    0x76D7, 0x66F6, 0x5695, 0x46B4,
    0xB75B, 0xA77A, 0x9719, 0x8738,
    0xF7DF, 0xE7FE, 0xD79D, 0xC7BC,

    0x48C4, 0x58E5, 0x6886, 0x78A7,
    0x0840, 0x1861, 0x2802, 0x3823,
    0xC9CC, 0xD9ED, 0xE98E, 0xF9AF,
    0x8948, 0x9969, 0xA90A, 0xB92B,

    0x5AF5, 0x4AD4, 0x7AB7, 0x6A96,
    0x1A71, 0x0A50, 0x3A33, 0x2A12,
    0xDBFD, 0xCBDC, 0xFBBF, 0xEB9E,
    0x9B79, 0x8B58, 0xBB3B, 0xAB1A,

    0x6CA6, 0x7C87, 0x4CE4, 0x5CC5,
    0x2C22, 0x3C03, 0x0C60, 0x1C41,
    0xEDAE, 0xFD8F, 0xCDEC, 0xDDCD,
    0xAD2A, 0xBD0B, 0x8D68, 0x9D49,

    0x7E97, 0x6EB6, 0x5ED5, 0x4EF4,
    0x3E13, 0x2E32, 0x1E51, 0x0E70,
    0xFF9F, 0xEFBE, 0xDFDD, 0xCFFC,
    0xBF1B, 0xAF3A, 0x9F59, 0x8F78,

    0x9188, 0x81A9, 0xB1CA, 0xA1EB,
    0xD10C, 0xC12D, 0xF14E, 0xE16F,
    0x1080, 0x00A1, 0x30C2, 0x20E3,
    0x5004, 0x4025, 0x7046, 0x6067,

    0x83B9, 0x9398, 0xA3FB, 0xB3DA,
    0xC33D, 0xD31C, 0xE37F, 0xF35E,
    0x02B1, 0x1290, 0x22F3, 0x32D2,
    0x4235, 0x5214, 0x6277, 0x7256,

    0xB5EA, 0xA5CB, 0x95A8, 0x8589,
    0xF56E, 0xE54F, 0xD52C, 0xC50D,
    0x34E2, 0x24C3, 0x14A0, 0x0481,
    0x7466, 0x6447, 0x5424, 0x4405,

    0xA7DB, 0xB7FA, 0x8799, 0x97B8,
    0xE75F, 0xF77E, 0xC71D, 0xD73C,
    0x26D3, 0x36F2, 0x0691, 0x16B0,
    0x6657, 0x7676, 0x4615, 0x5634,

    0xD94C, 0xC96D, 0xF90E, 0xE92F,
    0x99C8, 0x89E9, 0xB98A, 0xA9AB,
    0x5844, 0x4865, 0x7806, 0x6827,
    0x18C0, 0x08E1, 0x3882, 0x28A3,

    0xCB7D, 0xDB5C, 0xEB3F, 0xFB1E,
    0x8BF9, 0x9BD8, 0xABBB, 0xBB9A,
    0x4A75, 0x5A54, 0x6A37, 0x7A16,
    0x0AF1, 0x1AD0, 0x2AB3, 0x3A92,

    0xFD2E, 0xED0F, 0xDD6C, 0xCD4D,
    0xBDAA, 0xAD8B, 0x9DE8, 0x8DC9,
    0x7C26, 0x6C07, 0x5C64, 0x4C45,
    0x3CA2, 0x2C83, 0x1CE0, 0x0CC1,

    0xEF1F, 0xFF3E, 0xCF5D, 0xDF7C,
    0xAF9B, 0xBFBA, 0x8FD9, 0x9FF8,
    0x6E17, 0x7E36, 0x4E55, 0x5E74,
    0x2E93, 0x3EB2, 0x0ED1, 0x1EF0
};

inline unsigned int MakeJoyCmd32(unsigned char op, unsigned char a, unsigned char b, unsigned char c)
{
    return  (static_cast<unsigned int>(op) << 24) | (static_cast<unsigned int>(a)  << 16) | (static_cast<unsigned int>(b)  << 8)  | static_cast<unsigned int>(c);
}

static inline unsigned int MakeJoyCmd16(unsigned short opcode, unsigned char arg0 = 0, unsigned char arg1 = 0)
{
	return ((unsigned int)(opcode) << 16) | ((unsigned int)(arg0) << 8) | (unsigned int)(arg1);
}

/*
 * --INFO--
 * PAL Address: 0x800b138c
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned int CSystem::GetCounter()
{
	return m_frameCounter;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
JoyBus::JoyBus()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
JoyBus::~JoyBus()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::Init()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::CreateInit()
{
    memset(m_sendBuffer, 0, 0x4000);
    memset(m_stageFlags, 0, 8);
    memset(m_cmdQueueData, 0, 0x400);
    memset(m_recvQueueEntriesArr, 0, 0x400);
    memset(m_threadParams, 0, 0xF0);
    memset(m_perThreadTemp, 0, 0x60);
    memset(m_recvBuffer, 0, 0x1020);

    m_mapId = 0xFF;
    m_stageId = 0xFF;

    for (int i = 0; i < 4; i++)
    {
        m_threadParams[i].m_gbaStatus = 1;
        m_threadParams[i].m_padType = 0x40;

        m_cmdCount[i] = 0;
        m_secCmdCount[i] = 0;

        OSInitSemaphore(&m_accessSemaphores[i], 1);

        m_ctrlModeArr[i] = 0;
        m_nextModeTypeArr[i] = 0;
        m_modeXArr[i] = 0;
        m_stateCodeArr[i] = 0xFF;
        m_stateFlagArr[i] = 0;
    }

    if (m_gbaBootImage == 0)
    {
        // TODO: __nwa__FUlPQ27CMemory6CStagePci
        m_gbaBootImage = (char*)__nwa(0x38000);

        if (m_gbaBootImage == 0 && System.m_execParam != 0)
        {
            System.Printf("%s(%d): Error: memory allocation",
                "joybus.cpp", 0x126);
        }
    }

    char path[140];
    strcpy(path, "dvd/gba/");

    // MWCC PPC requires 3-arg strcat
    strcat(path, "objdat.spt", 131UL);

    CFile::CHandle* file = File.Open(path, 0, CFile::PRI_LOW);

    if (!file && System.m_execParam > 1)
    {
        System.Printf("Error: %s not found", path);
    }

    File.Read(file);
    File.SyncCompleted(file);

    unsigned int len = File.GetLength(file);
    m_fileBaseA_dup = len;

    if (m_fileBaseA == 0)
    {
		// TODO: __nwa__FUlPQ27CMemory6CStagePci
        m_fileBaseA = new unsigned int[0x20];

        if (m_fileBaseA == (unsigned int*)nullptr && System.m_execParam != 0)
        {
            System.Printf("%s(%d): Error: memory allocation", "joybus.cpp", 0x13A);
        }
    }

    memset((void*)m_fileBaseA, 0, len);
    memcpy((void*)m_fileBaseA, File.m_readBuffer, len);

    File.Close(file);

    if (m_fileBaseB == 0)
    {
        // TODO: __nwa__FUlPQ27CMemory6CStagePci
        m_fileBaseB = new unsigned int[0x5000];

        if (m_fileBaseB == 0 && System.m_execParam != 0)
        {
            System.Printf("%s(%d): Error: memory allocation", "joybus.cpp", 0x146);
        }
    }
	
    m_fileBaseB_dup = 0;
	
    memset(m_cmdBuffer, 0, 8);

    for (int i = 0; i < 4; i++)
    {
        if (m_letterBuffer[i] == 0)
        {
            // TODO: __nwa__FUlPQ27CMemory6CStagePci
            m_letterBuffer[i] = (char*)__nwa(0x2800);

            if (m_letterBuffer[i] == 0 && System.m_execParam != 0)
            {
                System.Printf("%s(%d): Error: memory allocation", "joybus.cpp", 0x155);
            }

            m_letterSizeArr[i] = 0;
        }
    }
}


/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::Destroy()
{
    m_stageFlags[0] = 0;
    m_stageFlags[1] = 0;
    m_stageFlags[2] = 0;
    m_stageFlags[3] = 0;

    m_threadInitFlag = 1;

    while (m_threadRunningMask != 0)
    {
    }

    if (m_gbaBootImage != 0)
    {
        // TODO: __dla__FPv
        // free((void*)m_gbaBootImage);
        m_gbaBootImage = 0;
    }

    if (m_fileBaseA != 0)
    {
        // TODO: __dla__FPv
        // free((void*)m_fileBaseA);
        m_fileBaseA = 0;
    }

    if (m_fileBaseB != 0)
    {
        // TODO: __dla__FPv
        // free((void*)m_fileBaseB);
        m_fileBaseB = 0;
    }

    for (int i = 0; i < 4; i++)
    {
        if (m_letterBuffer[i] != 0)
        {
            // TODO: __dla__FPv
            // free((void*)m_letterBuffer[i]);
            m_letterBuffer[i] = 0;
        }
    }

    memset(m_sendBuffer, 0, 0x4000);
    memset(m_stageFlags, 0, 8);
    memset(m_cmdQueueData, 0, 0x400);
    memset(m_recvQueueEntriesArr, 0, 0x400);
    memset(m_threadParams, 0, 0xF0);
    memset(m_perThreadTemp, 0, 0x60);
    memset(m_recvBuffer, 0, 0x1020);

    m_mapId = 0xFF;
    m_stageId = 0xFF;

    for (int i = 0; i < 4; i++)
    {
        m_threadParams[i].m_gbaStatus = 1;
        m_threadParams[i].m_padType = 0x40;

        m_cmdCount[i] = 0;
        m_secCmdCount[i] = 0;

        OSInitSemaphore(&m_accessSemaphores[i], 1);

        m_ctrlModeArr[i] = 0;
        m_nextModeTypeArr[i] = 0;
        m_modeXArr[i] = 0;
        m_stateCodeArr[i] = 0xFF;
        m_stateFlagArr[i] = 0;
    }

    m_fileBaseA_dup = 0;
    m_fileBaseB_dup = 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::LoadBin()
{
    int result = 0;

    if (!m_binLoaded)
    {
        CFile::CHandle* file = File.Open((char*)this, 0, CFile::PRI_LOW);

        if (file == 0)
        {
            if ((unsigned int)System.m_execParam > 1)
            {
                System.Printf("Error: %s not found", (char*)this);
            }

            result = -1;
        }
        else
        {
            File.Read(file);
            File.SyncCompleted(file);

            m_gbaBootImageSize = File.GetLength(file);
            memcpy(m_gbaBootImage, File.m_readBuffer, m_gbaBootImageSize);

            File.Close(file);

            m_diskId = (char*)File.GetCurrentDiskID();

            m_gbaBootImage[0xAC] = (unsigned char)m_diskId[0];
            m_gbaBootImage[0xAD] = (unsigned char)m_diskId[1];
            m_gbaBootImage[0xAE] = (unsigned char)m_diskId[2];
            m_gbaBootImage[0xAF] = (unsigned char)m_diskId[3];

            int idx = 0xBC;
            unsigned char* p = (unsigned char*)m_gbaBootImage + 0xBC;
            int left = 1;

            unsigned char sum = (unsigned char)(
                ((((((((((((((((((((((((((((-0x19
                - (unsigned char)m_gbaBootImage[0xA0])
                - (unsigned char)m_gbaBootImage[0xA1])
                - (unsigned char)m_gbaBootImage[0xA2])
                - (unsigned char)m_gbaBootImage[0xA3])
                - (unsigned char)m_gbaBootImage[0xA4])
                - (unsigned char)m_gbaBootImage[0xA5])
                - (unsigned char)m_gbaBootImage[0xA6])
                - (unsigned char)m_gbaBootImage[0xA7])
                - (unsigned char)m_gbaBootImage[0xA8])
                - (unsigned char)m_gbaBootImage[0xA9])
                - (unsigned char)m_gbaBootImage[0xAA])
                - (unsigned char)m_gbaBootImage[0xAB])
                - (unsigned char)m_gbaBootImage[0xAC])
                - (unsigned char)m_gbaBootImage[0xAD])
                - (unsigned char)m_gbaBootImage[0xAE])
                - (unsigned char)m_gbaBootImage[0xAF])
                - (unsigned char)m_gbaBootImage[0xB0])
                - (unsigned char)m_gbaBootImage[0xB1])
                - (unsigned char)m_gbaBootImage[0xB2])
                - (unsigned char)m_gbaBootImage[0xB3])
                - (unsigned char)m_gbaBootImage[0xB4])
                - (unsigned char)m_gbaBootImage[0xB5])
                - (unsigned char)m_gbaBootImage[0xB6])
                - (unsigned char)m_gbaBootImage[0xB7])
                - (unsigned char)m_gbaBootImage[0xB8])
                - (unsigned char)m_gbaBootImage[0xB9])
                - (unsigned char)m_gbaBootImage[0xBA])
                - (unsigned char)m_gbaBootImage[0xBB])
            );

            do
            {
                unsigned char v = *p++;
                idx++;
                sum = (unsigned char)(sum - v);
                left--;
            }
            while (left != 0);

            m_gbaBootImage[idx] = sum;

            *(unsigned int*)(m_gbaBootImage + 200) = OSGetTick();

            m_binLoaded = true;
        }
    }

    return result;
}


/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::LoadMap(int stageId, int mapId)
{
    int i;
	
    for (i = 0; i < 4; i++)
    {
        OSWaitSemaphore(&m_accessSemaphores[i]);
    }

    m_stageId = (unsigned char)stageId;
    m_mapId = (unsigned char)mapId;

    for (i = 0; i < 4; i++)
    {
        OSSignalSemaphore(&m_accessSemaphores[i]);
    }

    m_fileBaseB_dup = 0;

    char path[132];
    char tmp[16];

    strcpy(path, "dvd/gba/");
    sprintf(tmp, "m%02d_%d.mcd", stageId, mapId);
    strcat(path, tmp, 132UL);

    CFile::CHandle* fileHandle = File.Open(path, 0, CFile::PRI_LOW);

    if (fileHandle == 0)
    {
        if ((unsigned int)System.m_execParam > 1)
        {
            System.Printf("Error: %s not found", path);
        }
        return -1;
    }

    File.Read(fileHandle);
    File.SyncCompleted(fileHandle);

    unsigned int len = File.GetLength(fileHandle);

    m_fileBaseB_dup = len;

    memset(&m_fileBaseB, 0, 0x5000UL);
    memcpy(&m_fileBaseB, File.m_readBuffer, m_fileBaseB_dup);
	
	File.Close(fileHandle);

    return 0;
}


/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::BlockSem(int portIndex)
{
	OSWaitSemaphore(&m_accessSemaphores[portIndex]);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::ReleaseSem(int portIndex)
{
	OSSignalSemaphore(&m_accessSemaphores[portIndex]);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::ThreadMain(void* arg)
{
	ThreadParam* threadParam = (ThreadParam*)arg;
    unsigned int port = (unsigned int)threadParam->m_portIndex;

    unsigned int padType = 0;
    unsigned int stateTimeoutTicks = 0;
    unsigned long long stateStartTime = 0;

    unsigned short localCrc[2];
    unsigned int localWord = 0;
    unsigned int localCmd = 0;
    unsigned char localBuf[4] = {};

    threadParam->m_gbaStatus = 0;
    // TODO: threadParam->m_gbaStatus = GBAReset(threadParam->m_portIndex, &threadParam->m_unk3);

    ThreadSleep((DAT_800000f8 / 4000) * 0xF);
    stateStartTime = OSGetTime();

    for (;;)
    {
        int diskError = File.IsDiskError();

        if (diskError != 0)
        {
            threadParam->m_state = (unsigned char)0x86;
            ResetQueue(threadParam);
            ClrRecvBuffer(threadParam->m_portIndex);

            ThreadSleep((DAT_800000f8 / 4000) * 0xF);
            stateStartTime = OSGetTime();
            continue;
        }

        if (threadParam != &m_threadParams[threadParam->m_portIndex])
        {
            unsigned int idx = 0;
            int left = 4;
            JoyBus* jb = this;

            while (left > 0)
            {
                if (threadParam == jb->m_threadParams)
                {
                    memset(threadParam, 0, 0x3c);
                    threadParam->m_portIndex = (int)idx;
                    break;
                }

                jb = (JoyBus*)(jb->m_pathBuf + 0x3c);
                idx++;
                left--;
            }

            port = (unsigned int)threadParam->m_portIndex;
        }

        if (m_threadInitFlag != 0)
        {
            m_threadRunningMask = (unsigned char)(m_threadRunningMask & ~(unsigned char)(1 << port));
            m_stageFlags[port] = 0;
            OSExitThread(&DAT_8032edb8);
        }

        {
            unsigned int s = (unsigned int)threadParam->m_state;

            if (s == 5 || s == 900)
            {
                stateTimeoutTicks = (DAT_800000f8 / 4000) * 500;
            }
            else if (s > 2 && s < 5)
            {
                stateTimeoutTicks = (DAT_800000f8 / 4000) * 500;
            }
            else if (s == 2)
            {
                stateTimeoutTicks = (DAT_800000f8 / 4000) * 2000;
            }
            else
            {
                stateTimeoutTicks = (DAT_800000f8 / 4000) * 1000;
            }
        }

        {
            unsigned long long now = OSGetTime();
            unsigned int elapsed = (unsigned int)(now - stateStartTime);

            if (elapsed > stateTimeoutTicks)
            {
                threadParam->m_prevState = threadParam->m_state;

                if (threadParam->m_gbaStatus == 3)
                {
                    threadParam->m_state = (unsigned char)0x86;
                }
                else
                {
                    threadParam->m_gbaStatus = 1;
                    threadParam->m_state = (unsigned char)0x85;
                }

                stateStartTime = OSGetTime();
                ThreadSleep((DAT_800000f8 / 4000) * 0xF);
                continue;
            }
        }

        if (threadParam->m_skipProcessingFlag != 0)
        {
            threadParam->m_skipProcessingFlag = 0;
        }

        padType = 0; // TODO: SIProbe(threadParam->m_portIndex);

        BlockSem(threadParam->m_portIndex);

        if (padType == 0x00040000 ||
            padType == 0x09000000 ||
            padType == 0x8B100000 ||
            padType == 0x88000000)
        {
            threadParam->m_padType = padType;
        }
        else if (padType != 0x80)
        {
            threadParam->m_padType = 0x40;
            threadParam->m_sentStartFlag = 0;
        }

        ReleaseSem(threadParam->m_portIndex);

        if (m_nextModeTypeArr[port] != m_modeXArr[port])
        {
            threadParam->m_state    = (unsigned char)0x14;
            threadParam->m_subState = 0;
            m_modeXArr[port]        = m_nextModeTypeArr[port];
        }

        int gamePadState = 0;
        bool single = GbaQue.IsSingleMode(threadParam->m_portIndex);
        // TODO: unsigned int statusIndex = (single != 0 && threadParam->m_portIndex != 1) ? 0 : (unsigned int)threadParam->m_portIndex;
        // TODO: int* padPtr = (int*)(&Game.game.field_0xc5c0 + statusIndex * 4);
        // TODO: gamePadState = *padPtr;

        unsigned int state = (unsigned int)threadParam->m_state;

        switch (state)
        {
        case 0x00:
        {
            threadParam->m_state = 1;

            GbaQue.SetChgUseItemFlg(port);
            GbaQue.SetResetFlg(port);

            threadParam->m_subState      = 0;
            threadParam->m_pposCounter   = 0;
            threadParam->m_counter0x2B   = 0;
            threadParam->m_sentStartFlag = 0;
            threadParam->m_flags[0]      = 0;
            threadParam->m_flags[1]      = 0;
            threadParam->m_flags[5]      = 0;
            threadParam->m_flags[4]      = 0;
            threadParam->m_flags[2]      = 0;
            threadParam->m_flags[3]      = 0;

            m_ctrlModeArr[port] = 0;

            char controllerMode = 0;
            // TODO: controllerMode = GetControllerMode(&GbaQue);

            if (controllerMode == 0)
                m_nextModeTypeArr[port] = 0;
            else
                m_nextModeTypeArr[port] = 4;

            ResetQueue(threadParam);

            threadParam->m_gbaStatus = 0;
            // TODO: threadParam->m_gbaStatus = GBAJoyBoot(port, port << 1, 2, m_gbaBootParamA, m_gbaBootParamB, &threadParam->m_unk3);

            if (threadParam->m_gbaStatus == 3 && (threadParam->m_unk3 & 0x10) != 0)
            {
                threadParam->m_flags[0] = 0;
                threadParam->m_state    = 4;
            }
            else if (threadParam->m_gbaStatus == 0)
            {
                char cm = GbaQue.GetControllerMode();

                if (cm == 0)
                    m_nextModeTypeArr[port] = 0;
                else
                    m_nextModeTypeArr[port] = 4;

                threadParam->m_state    = 2;
                threadParam->m_subState = 0;

                threadParam->m_timestamp = OSGetTick();

                ThreadSleep((DAT_800000f8 / 4000) * 0xF);
                stateStartTime = OSGetTime();
            }
            else if (threadParam->m_gbaStatus == 3)
            {
                int stat = GetGBAStat(threadParam);
                if (stat == 0)
                {
                    threadParam->m_state    = 2;
                    threadParam->m_subState = 0;
                    ThreadSleep((DAT_800000f8 / 4000) * 0xF);
                    stateStartTime = OSGetTime();
                }
                else
                {
                    threadParam->m_flags[0] = 0;
                }
            }

            break;
        }

        case 0x01:
        {
            // TODO: optionally split logic from case 0 if needed
            break;
        }

        case 0x02:
        {
            int result = 0;
            // TODO: result = InitialCode(threadParam);

            if (result == 1)
            {
                stateStartTime = OSGetTime();
            }
            else if (result == 2)
            {
                ThreadSleep((DAT_800000f8 / 4000) * 0xF);
            }

            break;
        }

        case 0x03:
        {
            GbaQue.SetResetFlg(port);

            ResetQueue(threadParam);

            threadParam->m_gbaStatus = 0;
            // TODO: threadParam->m_gbaStatus = GBAReset(threadParam->m_portIndex, &threadParam->m_unk3);

            if (threadParam->m_gbaStatus == 0)
            {
                threadParam->m_state    = 2;
                threadParam->m_subState = 0;

                ThreadSleep((DAT_800000f8 / 4000) * 0xF);
                stateStartTime = OSGetTime();
            }

            break;
        }

        case 0x04:
        {
            threadParam->m_flags[0] = 0;
            break;
        }

        case 0x05:
        {
            // TODO: main in-game loop logic (SendGBAStart/Stop, SPMode, pause, map, radar, money, etc.)
            break;
        }

        case 0x06:
        {
            // TODO: controller mode 4 / SP-mode specific loop
            break;
        }

        case 0x14:
        {
            threadParam->m_state = 0x15;

            localCrc[0] = 0xFFFF;
            // TODO: unsigned short crcA = Crc16(m_fileBaseA_dup, m_fileBaseA, localCrc);
            // TODO: int chkA = SendChkCrc(threadParam, 0, crcA, &localWord);
            // TODO: if (chkA != 0) { threadParam->m_altState = threadParam->m_state; threadParam->m_recvWriteIdx = localWord; threadParam->m_state = 0x84; }

            break;
        }

        case 0x1D:
        {
            int res = 0;
            // TODO: res = GBARecvSend(threadParam, (unsigned int*)localBuf);

            if (res >= 0 && threadParam->m_skipProcessingFlag == 0)
            {
                int sendRes = SendMapNo(threadParam);
                if (sendRes >= 0)
                {
                    // TODO: stage flag / fileB CRC logic
                }
            }

            break;
        }

        case 0x4E:
        {
            unsigned int r = 0;
            // TODO: r = GBARecvSend(threadParam, (unsigned int*)localBuf);

            if ((int)r > 0 && threadParam->m_skipProcessingFlag == 0)
            {
                if ((localBuf[0] & 0x3F) == 7)
                    threadParam->m_state = 'L';
                else
                    threadParam->m_state = 5;
            }

            break;
        }

        case 900:
        {
            int res = 0;
            // TODO: res = GBARecvSend(threadParam, (unsigned int*)localBuf);

            if (res >= 0 && threadParam->m_skipProcessingFlag == 0)
            {
                int qres = SetSendQueue(threadParam, threadParam->m_recvWriteIdx);
                if (qres == 0)
                {
                    threadParam->m_state        = threadParam->m_altState;
                    threadParam->m_recvWriteIdx = 0;
                }
            }

            break;
        }

        default:
        {
            // TODO: add remaining state handling as you decompile them
            break;
        }
        }

        ThreadSleep((DAT_800000f8 / 4000) * 0xF);
        stateStartTime = OSGetTime();
    }
}


/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::_ThreadMain(void* param)
{
    Joybus.ThreadMain(param);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::ThreadInit()
{
    memset(m_threadParams, 0, sizeof(m_threadParams));

    m_threadInitFlag = 0;
    m_threadRunningMask = 0;
    ThreadParam* threadParam = m_threadParams;
    OSThread* thread = m_threads;

    for (int i = 0; i < 4; i++, threadParam++, thread++)
    {
        threadParam->m_portIndex = i;
        threadParam->m_gbaStatus = 1;
		
        unsigned char* stackBase = m_sendBuffer[i] + sizeof(m_sendBuffer[0]);

        OSCreateThread(
            thread,
            (void* (*)(void*))JoyBus::_ThreadMain,
            threadParam,
            stackBase,
            sizeof(m_sendBuffer[0]),
            8,
            1
        );

        OSResumeThread(thread);

        m_threadRunningMask |= (1 << i);
    }

    if ((unsigned int)System.m_execParam >= 2u)
    {
        System.Printf("JoyBus::ThreadInit end\n");
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::ReadInitialCode(ThreadParam* threadParam)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::WriteInitialCode(ThreadParam* threadParam)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x800ae228
 * PAL Size: 36b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void ThreadAlarmHandler(OSAlarm* alarm, OSContext*)
{
    OSResumeThread((OSThread*)alarm->start);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::ThreadSleep(long long ticks)
{
    OSAlarm alarm;
	
    OSCreateAlarm(&alarm);
    OSSetAlarmTag(&alarm, 1);
	
    OSThread* thread = OSGetCurrentThread();
    unsigned int level = OSDisableInterrupts();

    OSSetAlarm(&alarm, ticks, ThreadAlarmHandler);
    OSSuspendThread(thread);
    OSRestoreInterrupts(level);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::ReadContext(ThreadParam* threadParam)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::ReadHostId(ThreadParam* threadParam)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::WriteHostId(ThreadParam* threadParam)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::WriteContext(ThreadParam* threadParam)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::SetPadData(ThreadParam* threadParam, unsigned char* data)
{
    unsigned short flags = 0;
    unsigned char b1 = data[1];

    if (b1 & 0x01) flags |= 0x0100;
    if (b1 & 0x02) flags |= 0x0200;
    if (b1 & 0x08) flags |= 0x1000;
    if (b1 & 0x10) flags |= 0x0002;
    if (b1 & 0x20) flags |= 0x0001;
    if (b1 & 0x40) flags |= 0x0008;
    if (b1 & 0x80) flags |= 0x0004;

    unsigned char state = threadParam->m_state;

    if (state == 0x05 || state == '!' || state == '"' || state == '#' || state == '$' || m_stageId == '!')
    {
        if (b1 & 0x04)
        {
            flags |= 0x0010;
        }
    }

    unsigned char b2 = data[2];

    if (b2 & 0x01) flags |= 0x0020;
    if (b2 & 0x02) flags |= 0x0040;

    int port = threadParam->m_portIndex;

    OSWaitSemaphore(&m_accessSemaphores[port]);
    m_stageFlags[port] = flags;
    OSSignalSemaphore(&m_accessSemaphores[port]);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
short JoyBus::GetPadData(int portIndex)
{
    OSWaitSemaphore(&m_accessSemaphores[portIndex]);

    short value = m_stageFlags[portIndex];
	
    m_stageFlags[portIndex] = 0;

    if (m_threadInitFlag != 0) {
        value = 0;
    }

    OSSignalSemaphore(&m_accessSemaphores[portIndex]);

    bool isSingleMode = GbaQue.IsSingleMode(portIndex);
	
    if (isSingleMode != 0)
	{
        value = 0;
    }

    return value;
}

/*
 * --INFO--
 * Address: TODO
 * Size:    TODO
 */
int JoyBus::RecvGBA(ThreadParam* threadParam, unsigned int* recvBuffer)
{
    const int port = threadParam->m_portIndex;
    unsigned int secCount;

    *recvBuffer = 0;

    OSWaitSemaphore(&m_accessSemaphores[port]);
    secCount = m_secCmdCount[port];
    OSSignalSemaphore(&m_accessSemaphores[port]);

    if ((int)secCount >= 0x40)
    {
        return 0;
    }

    bool isSingle = GbaQue.IsSingleMode(port);

    if (!isSingle || port == 1)
    {
        // TODO: threadParam->m_gbaStatus = GBAGetStatus(port, &threadParam->m_unk3);
        threadParam->m_gbaStatus = (int)this; // GBAGetStatus(port, &threadParam->m_unk3);
    }
    else
    {
        threadParam->m_gbaStatus = 0;
    }

    if (threadParam->m_gbaStatus != 0)
    {
        return -1;
    }

    if (threadParam->m_unk3 & 0x30)
    {
        return -1;
    }

    if ((threadParam->m_unk3 & 8) == 0)
    {
        return 0;
    }

    unsigned int data = 0;

    // TODO: threadParam->m_gbaStatus = GBARead(port, &data, &threadParam->m_unk3);
    threadParam->m_gbaStatus = (int)this; // GBARead(port, &data, &threadParam->m_unk3);

    if (threadParam->m_gbaStatus != 0)
    {
        return -1;
    }

    *recvBuffer = data;

    unsigned char op = data & 0x3F;

    if (op == 4)
    {
        SetPadData(threadParam, (unsigned char*)&data);
        return 1;
    }
    else if (op == 0x0E)
    {
        unsigned char b1 = (data >> 8) & 0xFF;
        unsigned char b2 = (data >> 16) & 0xFF;

        if (b1 == 0)
        {
            m_stateCodeArr[port] = b2;
            m_stateFlagArr[port] = 1;
            return 1;
        }
        else
        {
            OSWaitSemaphore(&m_accessSemaphores[port]);
            m_recvQueueEntriesArr[port][ m_secCmdCount[port] ] = data;
            m_secCmdCount[port]++;
            OSSignalSemaphore(&m_accessSemaphores[port]);
            return 2;
        }
    }

    OSWaitSemaphore(&m_accessSemaphores[port]);
    m_recvQueueEntriesArr[port][ m_secCmdCount[port] ] = data;
    m_secCmdCount[port]++;
    OSSignalSemaphore(&m_accessSemaphores[port]);

    return 2;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::SendGBA(ThreadParam* threadParam)
{
    const int port = threadParam->m_portIndex;
    unsigned int firstCmd = 0;
    unsigned int count = 0;

    OSWaitSemaphore(&m_accessSemaphores[port]);
    count = m_cmdCount[port];
    firstCmd = m_cmdQueueData[port][0];
    OSSignalSemaphore(&m_accessSemaphores[port]);

    if (static_cast<int>(count) < 1)
	{
        return 0;
	}

    char isSingle = GbaQue.IsSingleMode(port);

    if (isSingle == 0 || port == 1)
    {
        threadParam->m_gbaStatus = GBAGetStatus(port, &threadParam->m_unk3);
    }
    else
    {
        threadParam->m_gbaStatus = 0;
    }

    if (threadParam->m_gbaStatus != 0)
	{
        return -1;
	}
	
    if (threadParam->m_unk3 & 0x30)
	{
		return -1;
	}

    if (threadParam->m_unk3 & 0x02)
	{
		return 0;
	}

    int gbaResult = GBAWrite(port, (unsigned char*)&firstCmd, &threadParam->m_unk3);
	
    threadParam->m_gbaStatus = gbaResult;

    if (gbaResult != 0)
	{
        return -1;
	}
	
    unsigned char opcode = (firstCmd >> 24) & 0xFF;   // upper byte
    unsigned char param = (firstCmd >> 16) & 0xFF;

    if (m_stateCodeArr[port] == 0x09 && opcode == 0x09 && param == 0x01)
    {
        threadParam->m_state = '!';
        threadParam->m_subState = 0;
        threadParam->m_skipProcessingFlag = 1;
    }
	
    OSWaitSemaphore(&m_accessSemaphores[port]);
	
    for (unsigned int i = 1; i < m_cmdCount[port]; ++i)
	{
        m_cmdQueueData[port][i - 1] = m_cmdQueueData[port][i];
	}
	
    m_cmdCount[port]--;
	
    OSSignalSemaphore(&m_accessSemaphores[port]);
	
    return 1;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::GBARecvSend(ThreadParam* threadParam, unsigned int* cmdOut)
{
    const int port = threadParam->m_portIndex;

    int recvResult = RecvGBA(threadParam, cmdOut);

    if (recvResult < 0)
    {
        threadParam->m_state = 0x02;
        threadParam->m_subState = 0;
        return recvResult;
    }

    if (recvResult == 2)
    {
        unsigned char* cmdBytes = reinterpret_cast<unsigned char*>(cmdOut);
        unsigned char op = cmdBytes[0] & 0x3F;

        if (op == 0x14 || op == 0x17 || op == 0x1A ||
            op == 0x1C || op == 0x1D || op == 0x1E ||
            op == 0x1F || (op == 0x06 && cmdBytes[1] == 0x18))
        {
            OSWaitSemaphore(&m_accessSemaphores[port]);

            unsigned int idx = (m_secCmdCount[port] + 63) & 0x3F;
            unsigned int prevCmd = m_recvQueueEntriesArr[port][idx];
            m_secCmdCount[port]--;

            OSSignalSemaphore(&m_accessSemaphores[port]);

            GbaQue.SetQueue(port, prevCmd);

            recvResult = 0;
            *cmdOut = 0;
        }
        else if (op == 0x0C)
        {
            OSWaitSemaphore(&m_accessSemaphores[port]);

            unsigned int idx = (m_secCmdCount[port] + 63) & 0x3F;
            unsigned int prevCmd = m_recvQueueEntriesArr[port][idx];
            m_secCmdCount[port]--;

            OSSignalSemaphore(&m_accessSemaphores[port]);

            unsigned char sub = cmdBytes[1];

            if (sub == 0x03)
            {
                GbaQue.ClrLetterLstFlg(port);
                GbaQue.SetQueue(port, prevCmd);

                threadParam->m_state = '!';
                threadParam->m_subState = 0;
                threadParam->m_skipProcessingFlag = 1;
            }
            else if (sub == 0x02)
            {
                GbaQue.ClrLetterDatFlg(port);
                GbaQue.SetQueue(port, prevCmd);

                threadParam->m_state = '%';
                threadParam->m_subState = 0;
                threadParam->m_skipProcessingFlag = 1;
            }
            else if (sub == 0x06)
            {
                GbaQue.ClrSellFlg(port);
                GbaQue.SetQueue(port, prevCmd);

                threadParam->m_state = '5';
                threadParam->m_subState = 0;
                threadParam->m_skipProcessingFlag = 1;
            }
            else if (sub == 0x07)
            {
                GbaQue.ClrBuyFlg(port);
                GbaQue.SetQueue(port, prevCmd);

                threadParam->m_state = '7';
                threadParam->m_subState = 0;
                threadParam->m_skipProcessingFlag = 1;
            }
            else if (sub == 0x08)
            {
                GbaQue.ClrMkSmithFlg(port);
                GbaQue.SetQueue(port, prevCmd);

                threadParam->m_state = '9';
                threadParam->m_subState = 0;
                threadParam->m_skipProcessingFlag = 1;
            }
            else if (sub == 0x09)
            {
                GbaQue.ClrArtiDatFlg(port);
                GbaQue.SetQueue(port, prevCmd);

                threadParam->m_state = 'A';
                threadParam->m_subState = 0;
                threadParam->m_skipProcessingFlag = 1;
            }
        }
        else if (op == 0x15)
        {
            OSWaitSemaphore(&m_accessSemaphores[port]);

            unsigned int idx = (m_secCmdCount[port] + 63) & 0x3F;
            unsigned int prevCmd = m_recvQueueEntriesArr[port][idx];
            m_secCmdCount[port]--;

            OSSignalSemaphore(&m_accessSemaphores[port]);

            unsigned char header = cmdBytes[0];

            if ((header >> 6) == 0)
            {
                OSWaitSemaphore(&m_accessSemaphores[port]);
                memset(&m_recvBuffer[port], 0, 0x408);
                OSSignalSemaphore(&m_accessSemaphores[port]);
            }

            unsigned int word = *cmdOut;
            JoyBusRecvBuffer& buf = m_recvBuffer[port];

            if (buf.m_cmdFlags != 0)
            {
                unsigned char cmdId = static_cast<unsigned char>(word >> 24);

                if (buf.m_cmdFlags != (cmdId & 0x3F))
                {
                    if (static_cast<unsigned int>(System.m_execParam) > 1u)
                    {
                        System.Printf("(%d):%s(%d): Warning: Recv data type mismatch", port, "joybus.cpp", 0x1079);
                    }

                    OSWaitSemaphore(&m_accessSemaphores[port]);
                    memset(&m_recvBuffer[port], 0, 0x408);
                    OSSignalSemaphore(&m_accessSemaphores[port]);
                }
            }

            OSWaitSemaphore(&m_accessSemaphores[port]);

            unsigned int length = buf.m_length;
            unsigned char b0 = static_cast<unsigned char>(word);
            unsigned char b1 = static_cast<unsigned char>(word >> 8);
            unsigned char b2 = static_cast<unsigned char>(word >> 16);

            if (length == 0)
            {
                buf.m_crc = static_cast<unsigned short>(word >> 8);
                unsigned int idx0 = buf.m_length;
                buf.m_length = idx0 + 1;
                buf.m_payload[idx0] = b0;
            }
            else
            {
                buf.m_length = length + 1;
                buf.m_payload[length] = b2;

                unsigned int idx1 = buf.m_length;
                buf.m_length = idx1 + 1;
                buf.m_payload[idx1] = b1;

                unsigned int idx2 = buf.m_length;
                buf.m_length = idx2 + 1;
                buf.m_payload[idx2] = b0;
            }

            OSSignalSemaphore(&m_accessSemaphores[port]);

            if ((header >> 6) == 2)
            {
                unsigned short crc = 0xFFFF;
                unsigned int len = buf.m_length;
                unsigned char* data = buf.m_payload;

                while (len-- > 0)
                {
                    unsigned char b = *data++;
                    unsigned char idxC = static_cast<unsigned char>(((crc >> 8) ^ b));
                    crc = static_cast<unsigned short>((crc << 8) ^ JoyBusCrcTable[idxC]);
                }

                if (static_cast<unsigned short>(~crc) == buf.m_crc)
                {
                    GbaQue.SetQueue(port, prevCmd);
                }
                else
                {
                    if (m_threadRunningMask != 0)
                    {
                        const unsigned int tPort = m_threadParams[port].m_portIndex;
                        OSWaitSemaphore(&m_accessSemaphores[tPort]);

                        if (static_cast<int>(m_cmdCount[tPort]) < 0x40)
                        {
                            m_cmdQueueData[tPort][m_cmdCount[tPort]] = 0x07150000;
                            m_cmdCount[tPort]++;
                            OSSignalSemaphore(&m_accessSemaphores[tPort]);
                        }
                        else
                        {
                            OSSignalSemaphore(&m_accessSemaphores[tPort]);
                        }
                    }

                    OSWaitSemaphore(&m_accessSemaphores[port]);
                    memset(&m_recvBuffer[port], 0, 0x408);
                    OSSignalSemaphore(&m_accessSemaphores[port]);
                }
            }
        }
    }

    int sendResult = SendGBA(threadParam);

    if (sendResult < 0)
    {
        threadParam->m_state = 0x02;
        threadParam->m_subState = 0;
        threadParam->m_skipProcessingFlag = 1;
    }
    else
    {
        if (threadParam->m_skipProcessingFlag != 0)
        {
            OSWaitSemaphore(&m_accessSemaphores[port]);

            unsigned int newCount = 0;

            for (unsigned int i = 0; i < m_cmdCount[port]; ++i)
            {
                unsigned int cmd = m_cmdQueueData[port][i];
                unsigned char op = static_cast<unsigned char>(cmd >> 24) & 0x3F;

                if (op == 0x0A || op == 0x10 || op == 0x14 ||
                    op == 0x1B || op == 0x13 || op == 0x09)
                {
                    m_recvQueueEntriesArr[port][newCount++] = cmd;
                }
            }

            for (unsigned int i = 0; i < 0x20; ++i)
            {
                if (i < newCount)
                {
                    m_cmdQueueData[port][i] = m_recvQueueEntriesArr[port][i];
                }
                else
                {
                    m_cmdQueueData[port][i] = 0;
                }

                m_recvQueueEntriesArr[port][i] = 0;
            }

            m_secCmdCount[port] = 0;
            m_cmdCount[port] = newCount;

            OSSignalSemaphore(&m_accessSemaphores[port]);
        }

        const unsigned char state = threadParam->m_state;

        if (m_stateFlagArr[port] != 0 &&
            m_stateCodeArr[port] != 0x09 &&
            state != 0x05 &&
            state > 0x20 && state < 0x29)
        {
            OSWaitSemaphore(&m_accessSemaphores[port]);

            unsigned int newCount = 0;

            for (unsigned int i = 0; i < m_cmdCount[port]; ++i)
            {
                unsigned int cmd = m_cmdQueueData[port][i];
                unsigned char op = static_cast<unsigned char>(cmd >> 24) & 0x3F;

                if (op == 0x0A || op == 0x10 || op == 0x14 ||
                    op == 0x1B || op == 0x13 || op == 0x09)
                {
                    m_recvQueueEntriesArr[port][newCount++] = cmd;
                }
            }

            for (unsigned int i = 0; i < 0x20; ++i)
            {
                if (i < newCount)
                {
                    m_cmdQueueData[port][i] = m_recvQueueEntriesArr[port][i];
                }
                else
                {
                    m_cmdQueueData[port][i] = 0;
                }

                m_recvQueueEntriesArr[port][i] = 0;
            }

            m_secCmdCount[port] = 0;
            m_cmdCount[port] = newCount;

            OSSignalSemaphore(&m_accessSemaphores[port]);

            threadParam->m_state = 0x05;
            threadParam->m_subState = 0;
            threadParam->m_skipProcessingFlag = 1;
        }
    }

    unsigned int recvBit = (recvResult == 2) ? 1u : 0u;
    unsigned int sendBit = (sendResult != 0) ? 2u : 0u;

    return static_cast<int>(recvBit | sendBit);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::ResetQueue(ThreadParam* threadParam)
{
    int port = threadParam->m_portIndex;

    OSWaitSemaphore(&m_accessSemaphores[port]);

    for (int index = 0; index < 8; index++)
	{
		int offset = 0x20 * index;
		
        *(unsigned int*)((char*)m_cmdQueueData[port] + offset) = 0;
        *(unsigned int*)((char*)m_recvQueueEntriesArr[port] + offset) = 0;

        *(unsigned int*)((char*)m_cmdQueueData[port] + offset + 4) = 0;
        *(unsigned int*)((char*)m_recvQueueEntriesArr[port] + offset + 4) = 0;

        *(unsigned int*)((char*)m_cmdQueueData[port] + offset + 8) = 0;
        *(unsigned int*)((char*)m_recvQueueEntriesArr[port] + offset + 8) = 0;

        *(unsigned int*)((char*)m_cmdQueueData[port] + offset + 0xC) = 0;
        *(unsigned int*)((char*)m_recvQueueEntriesArr[port] + offset + 0xC) = 0;

        *(unsigned int*)((char*)m_cmdQueueData[port] + offset + 0x10) = 0;
        *(unsigned int*)((char*)m_recvQueueEntriesArr[port] + offset + 0x10) = 0;

        *(unsigned int*)((char*)m_cmdQueueData[port] + offset + 0x14) = 0;
        *(unsigned int*)((char*)m_recvQueueEntriesArr[port] + offset + 0x14) = 0;

        *(unsigned int*)((char*)m_cmdQueueData[port] + offset + 0x18) = 0;
        *(unsigned int*)((char*)m_recvQueueEntriesArr[port] + offset + 0x18) = 0;

        *(unsigned int*)((char*)m_cmdQueueData[port] + offset + 0x1C) = 0;
        *(unsigned int*)((char*)m_recvQueueEntriesArr[port] + offset + 0x1C) = 0;
    }

    m_cmdCount[port] = 0;
    m_secCmdCount[port] = 0;

    OSSignalSemaphore(&m_accessSemaphores[port]);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::CleanQueue(ThreadParam* threadParam)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::InitialCode(ThreadParam* threadParam)
{
    const int port = threadParam->m_portIndex;
    int result = 0;

    switch (threadParam->m_subState)
    {
    case 0:
    {
        // Clear per-port state
        m_stateFlagArr[port] = 0;

        OSWaitSemaphore(&m_accessSemaphores[port]);

        // Clear command / receive queues for this port
        memset(m_cmdQueueData[port],         0, sizeof(m_cmdQueueData[port]));
        memset(m_recvQueueEntriesArr[port],  0, sizeof(m_recvQueueEntriesArr[port]));

        m_cmdCount[port]    = 0;
        m_secCmdCount[port] = 0;

        OSSignalSemaphore(&m_accessSemaphores[port]);

        // Get initial GBA status
        bool singleMode = GbaQue.IsSingleMode(port);

        if (!singleMode || port == 1)
        {
            threadParam->m_gbaStatus = 1; // TODO: GBAGetStatus(port, &threadParam->m_unk3);
        }
        else
        {
            threadParam->m_gbaStatus = 0;
        }

        if (threadParam->m_gbaStatus == 0 && threadParam->m_unk3 == '(')
        {
            unsigned int readBuf[4] = {};

            threadParam->m_gbaStatus = 0; // TODO: GBARead(port, readBuf, &threadParam->m_unk3);

            if (threadParam->m_gbaStatus == 0)
            {
                threadParam->m_recvReadIdx = readBuf[0];

                threadParam->m_deviceType   = 0;
                threadParam->m_padding[0]   = 0;
                threadParam->m_padding[1]   = 0;
                threadParam->m_padding[2]   = 1;
            }
        }

        threadParam->m_subState = 1;
        result = 0;
        break;
    }

    case 1:
    {
        bool singleMode = GbaQue.IsSingleMode(port);

        if (!singleMode || port == 1)
        {
            threadParam->m_gbaStatus = 1; // TODO: GBAGetStatus(port, &threadParam->m_unk3);
        }
        else
        {
            threadParam->m_gbaStatus = 0;
        }

        unsigned int status = threadParam->m_gbaStatus;

        if (status == 0)
        {
            if (threadParam->m_unk3 == ' ')
            {
                threadParam->m_gbaStatus = 0; // TODO: GBAWrite(port, m_diskId, &threadParam->m_unk3);
                status = threadParam->m_gbaStatus;

                if (status == 0)
                {
                    bool singleMode2 = GbaQue.IsSingleMode(port);

                    if (!singleMode2 || port == 1)
                    {
                        threadParam->m_gbaStatus = 1; // TODO: GBAGetStatus(port, &threadParam->m_unk3);
                    }
                    else
                    {
                        threadParam->m_gbaStatus = 0;
                    }

                    status = threadParam->m_gbaStatus;

                    if (status == 0)
                    {
                        if ((threadParam->m_unk3 & 0x30) == 0x20)
                            status = 0;
                        else
                            status = 1;
                    }
                }
            }
            else
            {
                status = 1;
            }
        }

        if (status == 0)
        {
            threadParam->m_subState = 2;
            result = 0;
        }
        else
        {
            result = 1;
        }

        break;
    }

    case 2:
    {
        bool singleMode = false;
        // TODO: singleMode = IsSingleMode__8GbaQueueFi(&GbaQue, port);

        if (!singleMode || port == 1)
        {
            threadParam->m_gbaStatus = 1; // TODO: GBAGetStatus(port, &threadParam->m_unk3);
        }
        else
        {
            threadParam->m_gbaStatus = 0;
        }

        unsigned int status = threadParam->m_gbaStatus;

        if (status == 0)
        {
            if (threadParam->m_unk3 == '(')
            {
                char header;
                unsigned char flags = 0; // will land in local_1f

                // GBARead fills header + flag byte (and maybe more); we only care about these two.
                struct
                {
                    char          h;
                    unsigned char f;
                } tmpBuf = {};

                threadParam->m_gbaStatus = 1; // TODO: GBARead(port, &tmpBuf, &threadParam->m_unk3);
                status = threadParam->m_gbaStatus;

                if (status == 0)
                {
                    header = tmpBuf.h;
                    flags  = tmpBuf.f;

                    if (header == 1)
                    {
                        status = 0;

                        threadParam->m_gbaBootFlag    = (unsigned char)((int)(unsigned char)flags >> 6);
                        threadParam->m_unk2           = (unsigned char)((flags >> 4) & 0x03);
                        threadParam->m_bootRetryCount = (unsigned char)(flags & 0x0F);
                    }
                    else
                    {
                        status = 1;
                    }
                }
            }
            else
            {
                status = 1;
            }
        }

        if (status == 0)
        {
            threadParam->m_subState = 3;
            result = 0;
        }
        else
        {
            result = 1;
        }

        break;
    }

    case 3:
    {
        bool singleMode = false;
        // TODO: singleMode = IsSingleMode__8GbaQueueFi(&GbaQue, port);

        if (!singleMode || port == 1)
        {
            threadParam->m_gbaStatus = 1; // TODO: GBAGetStatus(port, &threadParam->m_unk3);
        }
        else
        {
            threadParam->m_gbaStatus = 0;
        }

        unsigned int status = threadParam->m_gbaStatus;

        if (status == 0)
        {
            if (threadParam->m_unk3 == '(')
            {
                unsigned int timeValue = 0;
                threadParam->m_gbaStatus = 1; // TODO: GBARead(port, &timeValue, &threadParam->m_unk3);
                status = threadParam->m_gbaStatus;

                if (status == 0)
                {
                    // Bit-twiddly inequality check preserved from decomp
                    unsigned char a = (unsigned char)((timeValue - threadParam->m_timestamp) >> 24);
                    unsigned char b = (unsigned char)((threadParam->m_timestamp - timeValue) >> 24);

                    threadParam->m_timeChangedFlag = (unsigned char)((a | b) >> 7);
                    threadParam->m_timestamp = timeValue;
                    status = 0;
                }
            }
            else
            {
                status = 1;
            }
        }

        if (status == 0)
        {
            threadParam->m_subState = 4;
            // fall through into case 4
        }
        else
        {
            result = 1;
            break;
        }
    }

    case 4:
    {
        bool singleMode = false;
        // TODO: singleMode = IsSingleMode__8GbaQueueFi(&GbaQue, port);

        if (!singleMode || port == 1)
        {
            threadParam->m_gbaStatus = 1; // TODO: GBAGetStatus(port, &threadParam->m_unk3);
        }
        else
        {
            threadParam->m_gbaStatus = 0;
        }

        unsigned int status = threadParam->m_gbaStatus;

        if (status == 0)
        {
            if (threadParam->m_unk3 == ' ')
            {
                if (threadParam->m_timeChangedFlag != 0 ||
                    (threadParam->m_gbaBootFlag == 0 && threadParam->m_timestamp == 0))
                {
                    threadParam->m_timestamp = OSGetTick();
                }

                threadParam->m_gbaStatus = 1; // TODO: GBAWrite(port, &threadParam->m_timestamp, &threadParam->m_unk3);

                status = threadParam->m_gbaStatus;

                if (status == 0)
                {
                    status = 0;
                }
            }
            else
            {
                status = 1;
            }
        }

        if (status == 0)
        {
            threadParam->m_subState = 5;
            result = 0;
        }
        else
        {
            result = 1;
        }

        break;
    }

    case 5:
    {
        bool singleMode = GbaQue.IsSingleMode(port);

        if (!singleMode || port == 1)
        {
            threadParam->m_gbaStatus = 1; // TODO: GBAGetStatus(port, &threadParam->m_unk3);
        }
        else
        {
            threadParam->m_gbaStatus = 0;
        }

        unsigned int status = threadParam->m_gbaStatus;

        if (status == 0)
        {
            if (threadParam->m_unk3 == ' ')
            {
                bool singleMode2 = GbaQue.IsSingleMode(port);

                unsigned char portVal = singleMode2 ? 0 : (unsigned char)port;
                unsigned char header = 1;
                unsigned char flags = (unsigned char)(portVal | (threadParam->m_gbaBootFlag << 6) | (threadParam->m_unk2 << 4));
                unsigned int word = (1u << 24) | ((unsigned int)flags << 16);

                threadParam->m_gbaStatus = 0; // TODO GBAWrite(port, &word, &threadParam->m_unk3);
                status = threadParam->m_gbaStatus;

                if (status == 0)
                {
                    status = 0;
                }
            }
            else
            {
                status = 1;
            }
        }

        if (status == 0)
        {
            threadParam->m_subState = 6;
            result = 0;
        }
        else
        {
            result = 1;
        }

        break;
    }

    case 6:
    {
        int err = SendMType(threadParam, (int)m_nextModeTypeArr[port]);
        if (err < 0)
        {
            result = 1;
            break;
        }

        char stageMajor[3] = { 0, 0, 0 };
        char stageMinor[3] = { 0, 0, 0 };

        GbaQue.GetStageNo(port, (int*)&stageMajor, (int*)&stageMinor);

        unsigned int cmdStage = 0;
        // TODO: cmdStage = build stage command from stageMajor / stageMinor, like local_34.

        if (m_threadRunningMask != 0)
        {
            OSWaitSemaphore(&m_accessSemaphores[port]);

            if ((int)m_cmdCount[port] < 0x40)
            {
                m_cmdQueueData[port][m_cmdCount[port]] = cmdStage;
                m_cmdCount[port]++;

                OSSignalSemaphore(&m_accessSemaphores[port]);
                err = 0;
            }
            else
            {
                OSSignalSemaphore(&m_accessSemaphores[port]);
                err = -1;
            }
        }

        if (err < 0)
        {
            result = 1;
            break;
        }

        unsigned int cmdGame = 0;
        // TODO: cmdGame = (build from Game.game.gameWork._6_1_ and DAT_80330b24, like local_38).

        err = 0;

        if (m_threadRunningMask != 0)
        {
            OSWaitSemaphore(&m_accessSemaphores[port]);

            if ((int)m_cmdCount[port] < 0x40)
            {
                m_cmdQueueData[port][m_cmdCount[port]] = cmdGame;
                m_cmdCount[port]++;

                OSSignalSemaphore(&m_accessSemaphores[port]);
                err = 0;
            }
            else
            {
                OSSignalSemaphore(&m_accessSemaphores[port]);
                err = -1;
            }
        }

        if (err < 0)
        {
            result = 1;
            break;
        }

        threadParam->m_subState  = 0;
        threadParam->m_state     = 0x14;
        threadParam->m_flags[0]  = 1;

        // TODO: ClrPlayModeFlg__8GbaQueueFi(&GbaQue, port);

        result = 0;
        break;
    }

    default:
        // Unknown state, treat as error / busy
        result = 1;
        break;
    }

    return result;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::SetSendQueue(ThreadParam* threadParam, unsigned int command)
{
    if (m_threadRunningMask == 0) {
        return 0;
    }

    int port = threadParam->m_portIndex;

    OSWaitSemaphore(m_accessSemaphores + port);

    if ((int)m_cmdCount[port] < 0x40)
    {
        m_cmdQueueData[port][m_cmdCount[port]] = command;
        m_cmdCount[port]++;

        OSSignalSemaphore(m_accessSemaphores + port);
		
        return 0;
    }

    OSSignalSemaphore(m_accessSemaphores + port);
	
    return -1;
}


/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::SendGBAStart(ThreadParam* threadParam, unsigned int* outCmd)
{
    const int port = threadParam->m_portIndex;
    unsigned int cmd = MakeJoyCmd16(0x0A01, 0x00);

    *outCmd = cmd;

    int result = 0;

    if (m_threadRunningMask != 0)
    {
        OSWaitSemaphore(&m_accessSemaphores[port]);

        if (static_cast<int>(m_cmdCount[port]) < 0x40)
        {
            m_cmdQueueData[port][m_cmdCount[port]] = cmd;
            m_cmdCount[port]++;
        }
        else
        {
            result = -1;
        }

        OSSignalSemaphore(&m_accessSemaphores[port]);
    }

    if (result == 0)
    {
        threadParam->m_sentStartFlag = 1;
    }

    return result;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::SendGBAStop(ThreadParam* threadParam)
{
    const int port = threadParam->m_portIndex;
    unsigned int cmd = MakeJoyCmd16(0x0A00, 0x00);
    int result = 0;

    if (m_threadRunningMask != 0)
    {
        OSWaitSemaphore(&m_accessSemaphores[port]);

        if ((int)m_cmdCount[port] < 0x40)
        {
            m_cmdQueueData[port][m_cmdCount[port]] = cmd;
            m_cmdCount[port]++;
        }
        else
        {
            result = -1;
        }

        OSSignalSemaphore(&m_accessSemaphores[port]);
    }

    if (result == 0)
    {
        threadParam->m_sentStartFlag = 0;
    }

    return result;
}


/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::SendChkCrc(ThreadParam* threadParam, int param3, unsigned short crc, unsigned int* outCmd)
{
    const int port = threadParam->m_portIndex;
    unsigned char crc_lo = static_cast<unsigned char>(crc & 0xFF);
    unsigned char crc_hi = static_cast<unsigned char>((crc >> 8) & 0xFF);
    unsigned char p3 = static_cast<unsigned char>(param3);
    unsigned int cmd = (0x0Du << 24) | (static_cast<unsigned int>(p3) << 16) | (static_cast<unsigned int>(crc_lo) << 8) | static_cast<unsigned int>(crc_hi);

    *outCmd = cmd;
	
    int result = 0;

    if (m_threadRunningMask != 0)
    {
        OSWaitSemaphore(&m_accessSemaphores[port]);

        if (static_cast<int>(m_cmdCount[port]) < 0x40)
        {
            m_cmdQueueData[port][m_cmdCount[port]] = cmd;
            m_cmdCount[port]++;
        }
        else
        {
            result = -1;
        }

        OSSignalSemaphore(&m_accessSemaphores[port]);
    }

    return result;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::SendCancel(ThreadParam* threadParam)
{
    const int port = threadParam->m_portIndex;
    unsigned int cmd = 0x10000000u;
    int result = 0;

    if (m_threadRunningMask != 0)
    {
        OSWaitSemaphore(&m_accessSemaphores[port]);

        if (static_cast<int>(m_cmdCount[port]) < 0x40)
        {
            m_cmdQueueData[port][m_cmdCount[port]] = cmd;
            m_cmdCount[port]++;
        }
        else
        {
            result = -1;
        }

        OSSignalSemaphore(&m_accessSemaphores[port]);
    }

    return result;
}


/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::SendDataFile(ThreadParam* threadParam)
{
    const int port = threadParam->m_portIndex;
    int result = 0;

    unsigned char* temp = m_perThreadTemp[port];

    unsigned char& sendType = temp[0];
    unsigned char& phase = temp[1];
    unsigned short& crc = *reinterpret_cast<unsigned short*>(temp + 0x02);
    unsigned char*& dataPtr = *reinterpret_cast<unsigned char**>(temp + 0x04);
    unsigned char*& dataBase = *reinterpret_cast<unsigned char**>(temp + 0x08);
    unsigned char& blockCount = temp[0x0C];
    unsigned char& blockIndex = temp[0x0D];
    unsigned short& step = *reinterpret_cast<unsigned short*>(temp + 0x0E);
    unsigned short& chunkCount = *reinterpret_cast<unsigned short*>(temp + 0x10);
    unsigned short& totalSize = *reinterpret_cast<unsigned short*>(temp + 0x12);
    unsigned short& chunkSize = *reinterpret_cast<unsigned short*>(temp + 0x14);

    unsigned int localWord = 0;
    unsigned int gbaStatus = GBARecvSend(threadParam, &localWord);

    if (threadParam->m_skipProcessingFlag != 0)
    {
        return 0;
    }

    if ((int)gbaStatus < 0)
    {
        return -1;
    }

    if (threadParam->m_unk3 & 2)
    {
        return 0;
    }

    if ((gbaStatus & 1) == 0)
    {
        if (phase == 2)
        {
            unsigned short sentBlocks = chunkCount;
            unsigned short doneBlocks = step;

            if (sentBlocks <= doneBlocks)
            {
                return -1;
            }
        }

        return 0;
    }

    {
        OSWaitSemaphore(&m_accessSemaphores[port]);

        m_recvQueueEntriesArr[port][m_secCmdCount[port]] = 0;
        m_secCmdCount[port]--;

        localWord = (localWord & 0xFFFF0000u) |
                    static_cast<unsigned short>(static_cast<char>(localWord >> 24));

        OSSignalSemaphore(&m_accessSemaphores[port]);
    }

    const unsigned char cmd = static_cast<unsigned char>(localWord & 0x3F);
    const unsigned char seq = static_cast<unsigned char>((localWord >> 8) & 0xFF);

    if (cmd == 7)
    {
        step = 0;
        phase = 0;
        blockIndex = 0;
        localWord = 0;

        OSWaitSemaphore(&m_accessSemaphores[port]);

        memset(m_cmdQueueData[port], 0, sizeof(m_cmdQueueData[port]));
        memset(m_recvQueueEntriesArr[port], 0, sizeof(m_recvQueueEntriesArr[port]));

        m_cmdCount[port] = 0;
        m_secCmdCount[port] = 0;

        OSSignalSemaphore(&m_accessSemaphores[port]);

        result = 0;

        if (m_threadRunningMask != 0)
        {
            OSWaitSemaphore(&m_accessSemaphores[port]);

            if ((int)m_cmdCount[port] < 0x40)
            {
                m_cmdQueueData[port][m_cmdCount[port]] = 0x10000000;
                m_cmdCount[port]++;

                OSSignalSemaphore(&m_accessSemaphores[port]);
                result = 0;
            }
            else
            {
                OSSignalSemaphore(&m_accessSemaphores[port]);
                result = -1;
            }
        }

        const int typeVal = static_cast<char>(sendType);
        const int respVal = static_cast<char>(seq);

        if (result != 0)
        {
            int diffMask = ((typeVal - respVal) | (respVal - typeVal)) >> 31;
            return -2 - diffMask;
        }

        int diffMask = ((respVal - typeVal) | (typeVal - respVal)) >> 31;
        return diffMask - 1;
    }

    if (seq == sendType)
    {
        step = 0;
        phase = 1;
        blockIndex++;
        dataPtr += chunkSize;

        if (blockCount <= blockIndex)
        {
            return 1;
        }
    }

    result = 0;
    localWord = 0x0B000000;

    if (phase == 0)
    {
        if (step == 0)
        {
            unsigned char type = sendType;

            if (type != 3 && type != 2 && type != 6 && type != 7 && type != 8 && type != 9)
            {
                // TODO: IsSingleMode__8GbaQueueFi(&GbaQue, port);

                if (m_threadRunningMask == 0)
                {
                    result = 0;
                }
                else
                {
                    OSWaitSemaphore(&m_accessSemaphores[port]);

                    if ((int)m_cmdCount[port] < 0x40)
                    {
                        m_cmdQueueData[port][m_cmdCount[port]] = 0x09000000;
                        m_cmdCount[port]++;

                        OSSignalSemaphore(&m_accessSemaphores[port]);
                        result = 0;
                    }
                    else
                    {
                        OSSignalSemaphore(&m_accessSemaphores[port]);
                        result = -1;
                    }
                }

                if (result != 0)
                {
                    return -1;
                }

                m_ctrlModeArr[port] = 0;
            }

            if (type == 0)
            {
                dataBase = reinterpret_cast<unsigned char*>(m_fileBaseA);
                dataPtr = dataBase;
                totalSize = static_cast<unsigned short>(m_fileBaseA_dup);
            }
            else if (type == 1)
            {
                dataBase = reinterpret_cast<unsigned char*>(m_fileBaseB);
                dataPtr = dataBase;
                totalSize = static_cast<unsigned short>(m_fileBaseB_dup);
            }
            else
            {
                unsigned char* letter = reinterpret_cast<unsigned char*>(m_letterBuffer[port]);
                dataBase = letter;
                dataPtr = letter;
                totalSize = static_cast<unsigned short>(m_letterSizeArr[port]);
            }

            unsigned short size = totalSize;
            unsigned char blocks = static_cast<unsigned char>(size / 0x2FD);

            if (static_cast<unsigned short>(blocks) * 0x2FD != size)
            {
                blocks++;
            }

            blockCount = blocks;

            unsigned short crcAcc = 0xFFFF;
            unsigned char* p = dataBase;
            unsigned int count = size;

            while (static_cast<int>(count) > 0)
            {
                unsigned char b = *p++;
                count--;

                crcAcc = static_cast<unsigned short>(
                    (crcAcc << 8) ^
                    JoyBusCrcTable[(crcAcc >> 8) ^ b]
                );
            }

            crc = static_cast<unsigned short>(~crcAcc);

            unsigned int word =
                (static_cast<unsigned int>(0x0B) << 24) |
                (static_cast<unsigned int>(sendType) << 16) |
                (static_cast<unsigned int>(blockCount) << 8);

            if (m_threadRunningMask == 0)
            {
                result = 0;
            }
            else
            {
                localWord = word;

                OSWaitSemaphore(&m_accessSemaphores[port]);

                if ((int)m_cmdCount[port] < 0x40)
                {
                    m_cmdQueueData[port][m_cmdCount[port]] = word;
                    m_cmdCount[port]++;

                    OSSignalSemaphore(&m_accessSemaphores[port]);
                    result = 0;
                }
                else
                {
                    OSSignalSemaphore(&m_accessSemaphores[port]);
                    result = -1;
                }
            }

            if (result != 0)
            {
                return -1;
            }

            step++;
        }
        else if (step == 1)
        {
            unsigned short size = totalSize;
            unsigned short len = size;

            unsigned int word =
                (static_cast<unsigned int>(0x0B00) << 16) |
                static_cast<unsigned int>(len);

            if (m_threadRunningMask != 0)
            {
                localWord = word;

                OSWaitSemaphore(&m_accessSemaphores[port]);

                if ((int)m_cmdCount[port] < 0x40)
                {
                    m_cmdQueueData[port][m_cmdCount[port]] = word;
                    m_cmdCount[port]++;

                    OSSignalSemaphore(&m_accessSemaphores[port]);
                    result = 0;
                }
                else
                {
                    OSSignalSemaphore(&m_accessSemaphores[port]);
                    result = -1;
                }
            }

            if (result != 0)
            {
                return -1;
            }

            step++;
        }
        else
        {
            unsigned short crcAcc = 0xFFFF;
            unsigned char* p = dataBase;
            unsigned int count = chunkSize;

            while (static_cast<int>(count) > 0)
            {
                unsigned char b = *p++;
                count--;

                crcAcc = static_cast<unsigned short>(
                    (crcAcc << 8) ^
                    JoyBusCrcTable[(crcAcc >> 8) ^ b]
                );
            }

            unsigned short crcChunk = static_cast<unsigned short>(~crcAcc);

            unsigned int word =
                (static_cast<unsigned int>(0x0B00) << 16) |
                static_cast<unsigned int>(crcChunk);

            if (m_threadRunningMask != 0)
            {
                localWord = word;

                OSWaitSemaphore(&m_accessSemaphores[port]);

                if ((int)m_cmdCount[port] < 0x40)
                {
                    m_cmdQueueData[port][m_cmdCount[port]] = word;
                    m_cmdCount[port]++;

                    OSSignalSemaphore(&m_accessSemaphores[port]);
                    result = 0;
                }
                else
                {
                    OSSignalSemaphore(&m_accessSemaphores[port]);
                    result = -1;
                }
            }

            if (result != 0)
            {
                return -1;
            }

            phase = 2;
            step = 0;
        }
    }
    else if (phase == 1)
    {
        if (step == 0)
        {
            if (static_cast<int>(blockIndex) < static_cast<int>(blockCount - 1))
            {
                chunkCount = 0x00FF;
                chunkSize = 0x02FD;
            }
            else
            {
                unsigned int remaining = totalSize % 0x2FD;

                if (totalSize != 0 && remaining == 0)
                {
                    remaining = 0x2FD;
                }

                unsigned int rows = remaining / 3;

                if (rows * 3 != remaining)
                {
                    rows++;
                }

                chunkCount = static_cast<unsigned short>(rows);
                chunkSize = static_cast<unsigned short>(remaining);
            }

            unsigned short len = chunkSize;
            unsigned char rowCount = static_cast<unsigned char>(chunkCount);

            unsigned int word = (static_cast<unsigned int>(0x4B) << 24) | (static_cast<unsigned int>(rowCount) << 16) | static_cast<unsigned int>(len);

            if (m_threadRunningMask == 0)
            {
                result = 0;
            }
            else
            {
                localWord = word;

                OSWaitSemaphore(&m_accessSemaphores[port]);

                if ((int)m_cmdCount[port] < 0x40)
                {
                    m_cmdQueueData[port][m_cmdCount[port]] = word;
                    m_cmdCount[port]++;

                    OSSignalSemaphore(&m_accessSemaphores[port]);
                    result = 0;
                }
                else
                {
                    OSSignalSemaphore(&m_accessSemaphores[port]);
                    result = -1;
                }
            }

            if (result != 0)
            {
                return -1;
            }

            step++;
        }
        else
        {
            unsigned short crcAcc = 0xFFFF;
            unsigned char* p = dataPtr;
            unsigned int count = chunkSize;

            while (static_cast<int>(count) > 0)
            {
                unsigned char b = *p++;
                count--;

                crcAcc = static_cast<unsigned short>(
                    (crcAcc << 8) ^
                    JoyBusCrcTable[(crcAcc >> 8) ^ b]
                );
            }

            unsigned short crcChunk = static_cast<unsigned short>(~crcAcc);

            unsigned int word =
                (static_cast<unsigned int>(0x4B) << 24) |
                (static_cast<unsigned int>(blockIndex) << 16) |
                static_cast<unsigned int>(crcChunk);

            if (m_threadRunningMask == 0)
            {
                result = 0;
            }
            else
            {
                localWord = word;

                OSWaitSemaphore(&m_accessSemaphores[port]);

                if ((int)m_cmdCount[port] < 0x40)
                {
                    m_cmdQueueData[port][m_cmdCount[port]] = word;
                    m_cmdCount[port]++;

                    OSSignalSemaphore(&m_accessSemaphores[port]);
                    result = 0;
                }
                else
                {
                    OSSignalSemaphore(&m_accessSemaphores[port]);
                    result = -1;
                }
            }

            if (result != 0)
            {
                return -1;
            }

            phase = 2;
            step = 0;
        }
    }
    else
    {
        unsigned char* p = dataPtr;

        unsigned char b0 = *p++;
        unsigned char b1 = *p++;
        unsigned char b2 = *p++;

        dataPtr = p;

        unsigned int word =
            (static_cast<unsigned int>(0x8B) << 24) |
            (static_cast<unsigned int>(b0) << 16) |
            (static_cast<unsigned int>(b1) << 8) |
            static_cast<unsigned int>(b2);

        if (m_threadRunningMask != 0)
        {
            localWord = word;

            OSWaitSemaphore(&m_accessSemaphores[port]);

            if ((int)m_cmdCount[port] < 0x40)
            {
                m_cmdQueueData[port][m_cmdCount[port]] = word;
                m_cmdCount[port]++;

                OSSignalSemaphore(&m_accessSemaphores[port]);
                result = 0;
            }
            else
            {
                OSSignalSemaphore(&m_accessSemaphores[port]);
                result = -1;
            }
        }

        if (result != 0)
        {
            return -1;
        }

        step++;
    }

    return result;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::SendMBase(ThreadParam* threadParam)
{
    const int port = threadParam->m_portIndex;
    short posX, posY;

    GbaQue.GetMBasePos(port, &posX, &posY);

    unsigned int cmdX = (0x0Fu << 24) | (0x00u << 16) | ((unsigned char)(posX & 0xFF) << 8) | ((unsigned char)((posX >> 8) & 0xFF));
    int result = 0;

    if (m_threadRunningMask != 0)
    {
        OSWaitSemaphore(&m_accessSemaphores[port]);

        if ((int)m_cmdCount[port] < 0x40)
        {
            m_cmdQueueData[port][m_cmdCount[port]] = cmdX;
            m_cmdCount[port]++;
        }
        else
        {
            result = -1;
        }

        OSSignalSemaphore(&m_accessSemaphores[port]);
    }

    if (result != 0)
	{
        return -1;
	}

    unsigned int cmdY = (0x4Fu << 24) | (0x00u << 16) | ((unsigned char)(posY & 0xFF) << 8) | ((unsigned char)((posY >> 8) & 0xFF));

    if (m_threadRunningMask != 0)
    {
        OSWaitSemaphore(&m_accessSemaphores[port]);

        if ((int)m_cmdCount[port] < 0x40)
        {
            m_cmdQueueData[port][m_cmdCount[port]] = cmdY;
            m_cmdCount[port]++;
            result = 0;
        }
        else
        {
            result = -1;
        }

        OSSignalSemaphore(&m_accessSemaphores[port]);
    }

    return result;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::SendMapNo(ThreadParam* threadParam)
{
    const int port = threadParam->m_portIndex;

    char stageMajor[3] = { 0, 0, 0 };
    char stageMinor[3] = { 0, 0, 0 };

    GbaQue.GetStageNo(port, (int*)&stageMajor, (int*)&stageMinor);

    unsigned char stageA = stageMajor[2];
    unsigned char stageB = stageMinor[2];

    unsigned int cmd = (0x0Eu << 24) | (0x01u << 16) | (stageA << 8) | (stageB);

    int result = 0;

    if (m_threadRunningMask != 0)
    {
        OSWaitSemaphore(&m_accessSemaphores[port]);

        if ((int)m_cmdCount[port] < 0x40)
        {
            m_cmdQueueData[port][m_cmdCount[port]] = cmd;
            m_cmdCount[port]++;
        }
        else
        {
            result = -1;
        }

        OSSignalSemaphore(&m_accessSemaphores[port]);
    }

    return result;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::InitPpos()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::SendPpos(ThreadParam* threadParam)
{
    int result = 0;
    const int port = threadParam->m_portIndex;
    unsigned char& state = threadParam->m_pposCounter;
    unsigned char& playerCount = m_cmdBuffer[port];
    unsigned char& mobCount = m_cmdBuffer[4 + port];
    unsigned char* posBytes = m_playerPosPacketBuffer[port];
    unsigned int* posWords = (unsigned int*)posBytes;
    int& wordIndex = m_pposWordIndex[port];

    switch (state)
    {
    case 0:
    {
        if ((System.m_execParam % 4) != 0)
        {
            return 0;
        }

        memset(posBytes, 0, 0x100);

        GbaQue.GetPlayerPos(port, posWords);

        playerCount = 3;
        wordIndex = 0;
        state += 1;
		
        break;
    }

    case 1:
    {
        int sent = 0;
        int totalWord = (int)(signed char)playerCount;

        while (sent < totalWord)
        {
            unsigned int word = posWords[wordIndex + sent];

            if (m_threadRunningMask != 0)
            {
                OSWaitSemaphore(&m_accessSemaphores[port]);

                if ((int)m_cmdCount[port] >= 0x40)
                {
                    OSSignalSemaphore(&m_accessSemaphores[port]);
                    result = -1;
                }
                else
                {
                    m_cmdQueueData[port][m_cmdCount[port]] = word;
                    m_cmdCount[port]++;

                    OSSignalSemaphore(&m_accessSemaphores[port]);
                }
            }

            if (result != 0)
            {
                break;
            }

            sent++;
        }

        // Advance index by number of words we actually pushed this call
        wordIndex += sent;

        // Done with all player-pos words?
        if (wordIndex >= (unsigned int)(signed char)playerCount)
        {
            playerCount = 0;
            wordIndex = 0;
            state += 1;
        }
        break;
    }

    case 2:
    {
        memset(posBytes, 0, 0x100);
        wordIndex = 0;
        mobCount = 0;

        int enemyCount = 0;

        // TODO
        // GbaQueue::GetEnemyPos(&GbaQue, port, posWords, &enemyCount);
		
        mobCount = (unsigned char)enemyCount;

        // If there are no enemies, skip straight to treasure (state 4)
        if (mobCount == 0)
        {
            state += 2; // 2 -> 4
        }
        else
        {
            state += 1; // 2 -> 3
        }
        break;
    }

    case 3:
    {
        int sent = 0;
        int totalWord = (int)(signed char)mobCount;

        while (sent < totalWord)
        {
            unsigned int word = posWords[wordIndex + sent];

            if (m_threadRunningMask != 0)
            {
                OSWaitSemaphore(&m_accessSemaphores[port]);

                if ((int)m_cmdCount[port] >= 0x40)
                {
                    OSSignalSemaphore(&m_accessSemaphores[port]);
                    result = -1;
                }
                else
                {
                    m_cmdQueueData[port][m_cmdCount[port]] = word;
                    m_cmdCount[port]++;

                    OSSignalSemaphore(&m_accessSemaphores[port]);
                }
            }

            if (result != 0)
            {
                break;
            }

            sent++;
        }

        wordIndex += sent;

        if (wordIndex >= (unsigned int)(signed char)mobCount)
        {
            mobCount = 0;
            wordIndex = 0;
            state += 1;
        }
		
        break;
    }

    case 4:
    {
        memset(posBytes, 0, 0x100);
        wordIndex = 0;
        mobCount = 0;

        int treasureCount = 0;
        
        GbaQue.GetTreasurePos(port, posWords, &treasureCount);

        mobCount = (unsigned char)treasureCount;

        if (mobCount == 0)
        {
            state = 0;
        }
        else
        {
            state += 1;
        }

        break;
    }

    case 5:
    {
        int sent = 0;
        int totalWord = (int)(signed char)mobCount;

        while (sent < totalWord)
        {
            unsigned int word = posWords[wordIndex + sent];

            if (m_threadRunningMask != 0)
            {
                OSWaitSemaphore(&m_accessSemaphores[port]);

                if ((int)m_cmdCount[port] >= 0x40)
                {
                    OSSignalSemaphore(&m_accessSemaphores[port]);
                    result = -1;
                }
                else
                {
                    m_cmdQueueData[port][m_cmdCount[port]] = word;
                    m_cmdCount[port]++;

                    OSSignalSemaphore(&m_accessSemaphores[port]);
                }
            }

            if (result != 0)
            {
                break;
            }

            sent++;
        }

        wordIndex += sent;

        if (wordIndex >= (unsigned int)(signed char)mobCount)
        {
            state = 0;
            mobCount = 0;
            wordIndex = 0;
        }

        break;
    }

    default:
    {
        if ((unsigned int)System.m_execParam >= 2u)
        {
            signed char cnt = (signed char)m_cmdBuffer[port];

            System.Printf("JoyBus::SendPpos: bad state (port=%d, cnt=%d)\n", port, (int)cnt);
        }

        m_cmdBuffer[port] = 0;
        m_cmdBuffer[4 + port] = 0;
        m_pposWordIndex[port] = 0;
        result = -1;
		
        break;
    }
    }

    return result;
}


/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::MakeJoyData(char* src, int length, unsigned int* outBuffer)
{
    unsigned char* param_2 = reinterpret_cast<unsigned char*>(src);
    unsigned char* param_4 = reinterpret_cast<unsigned char*>(outBuffer);
    unsigned char* pbVar1;
    unsigned bVar2;
    int iVar3;
    unsigned char* pbVar4;
    unsigned int uVar5;
    unsigned char* puVar6;
    unsigned int uVar8;
    unsigned char local_8;
    unsigned char uStack_7;

    uVar5 = 0xFFFF;
    pbVar4 = param_2;

	for (int i = length; i < 0; i--)
	{
        bVar2 = *pbVar4;
        pbVar4 = pbVar4 + 1;
        uVar5 = ((uVar5 << 8) ^ static_cast<unsigned int>(JoyBusCrcTable[(uVar5 >> 8) ^ static_cast<unsigned int>(bVar2)])) & 0xFFFF;
	}

    length = (length - 1) / 3;
    param_4[0] = 5;

    if (length - 1 != length * 3)
    {
        length = length + 1;
    }

    iVar3 = length + 2;

    if (iVar3 >= 0x100)
    {
        return -1;
    }

    param_4[1] = static_cast<unsigned char>(iVar3);

    {
        unsigned short inv = static_cast<unsigned short>(~static_cast<unsigned short>(uVar5));
		
        uStack_7 = static_cast<unsigned char>(inv);
        local_8 = static_cast<unsigned char>(inv >> 8);

        unsigned short stored = static_cast<unsigned short>((static_cast<unsigned short>(uStack_7) << 8) | static_cast<unsigned short>(local_8));

        *reinterpret_cast<unsigned short*>(param_4 + 2) = stored;
    }

    puVar6 = param_4 + 8;
    pbVar4 = param_2 + 1;
    uVar5 = static_cast<unsigned int>(length + 1);
	
    param_4[4] = 0x45;
    param_4[5] = static_cast<unsigned char>(length);
    param_4[6] = static_cast<unsigned char>(static_cast<unsigned int>(length) >> 8);
    param_4[7] = *param_2;
	
    if (1 < iVar3)
    {
        // uVar8 = uVar5 >> 2;
        uVar8 = uVar5 >> 2;

        // The big unrolled loop: handles blocks of 4 groups (= 12 bytes)
        if (uVar8 != 0)
        {
            do
            {
                puVar6[0] = 0x85;
                puVar6[1] = pbVar4[0];
                puVar6[2] = pbVar4[1];
                puVar6[3] = pbVar4[2];

                puVar6[4] = 0x85;
                puVar6[5] = pbVar4[3];
                puVar6[6] = pbVar4[4];
                puVar6[7] = pbVar4[5];

                puVar6[8] = 0x85;
                puVar6[9] = pbVar4[6];
                puVar6[10] = pbVar4[7];
                puVar6[11] = pbVar4[8];

                puVar6[12] = 0x85;
                puVar6[13] = pbVar4[9];
                puVar6[14] = pbVar4[10];

                pbVar1 = pbVar4 + 0x0B; // pbVar4 + 11
                pbVar4 = pbVar4 + 0x0C; // advance by 12 bytes

                puVar6[15] = *pbVar1;       // last byte of this 12-byte chunk
                puVar6 = puVar6 + 0x10; // advance out pointer by 16 bytes

                uVar8 = uVar8 - 1;
            }
            while (uVar8 != 0);

            uVar5 %= 4;

            // if (uVar5 == 0) return iVar3;
            if (uVar5 == 0)
            {
                return iVar3;
            }
        }

        // Tail processing: remaining groups (1-3)
        do
        {
            puVar6[0] = 0x85;
            puVar6[1] = pbVar4[0];
            puVar6[2] = pbVar4[1];
            pbVar1 = pbVar4 + 2;
            pbVar4 = pbVar4 + 3;
            puVar6[3] = *pbVar1;
            puVar6 = puVar6 + 4;
            uVar5 = uVar5 - 1;
        } while (uVar5 != 0);
    }

    return iVar3;
}


/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::SendPlayerStat(ThreadParam* threadParam)
{
    const int port = threadParam->m_portIndex;
    int result = 0;

    if (threadParam->m_subState == 1)
    {
        unsigned char* base = m_joyDataPacketBuffer[port];
        unsigned int* wordPtr = (unsigned int*)(void*)(base + m_txWordIndex[port] * 4 + 2);
        unsigned int word = *wordPtr;

        if (m_threadRunningMask == 0)
        {
            result = 0;
        }
        else
        {
            OSWaitSemaphore(&m_accessSemaphores[port]);

            if ((int)m_cmdCount[port] < 0x40)
            {
                m_cmdQueueData[port][m_cmdCount[port]] = word;
                m_cmdCount[port]++;

                OSSignalSemaphore(&m_accessSemaphores[port]);
                result = 0;
            }
            else
            {
                OSSignalSemaphore(&m_accessSemaphores[port]);
                result = -1;
            }
        }
    }
    else
    {
        if (threadParam->m_subState == 0)
        {
            GbaPInfo playerInfo;
            memset(&playerInfo, 0, sizeof(playerInfo));

            GbaQue.GetPlayerStat(port, &playerInfo);

            m_txWordIndex[port] = 0;

            unsigned char classFlags[4];
            memset(classFlags, 0xFF, sizeof(classFlags));

            unsigned char payload[0x300];
            memset(payload, 0, sizeof(payload));

            memset(m_joyDataPacketBuffer[port] + 2, 0, 0x400);

            payload[0] = 1;

            char caravanName[128];
            memset(caravanName, 0, sizeof(caravanName));
            
            GbaQue.GetCaravanName(caravanName);

            memcpy(&payload[1], caravanName, sizeof(caravanName));

            unsigned char* p = (unsigned char*)&playerInfo;
            unsigned char lowBits = 0;
            unsigned char highBits = 0;

            for (int i = 0; i < 2; ++i)
            {
                if (p[0x16] != 0)
                {
                    int idx = (int)p[0] >> 1;
                    unsigned char v = (classFlags[idx] & 0x0F) | lowBits;

                    if ((p[0] & 1) != 0)
                    {
                        v = (classFlags[idx] & 0xF0) | highBits;
                    }

                    classFlags[idx] = v;
                }

                if (p[0xF2] != 0)
                {
                    int idx = (int)p[0xDC] >> 1;
                    unsigned char v =
                        (classFlags[idx] & 0x0F) | (unsigned char)(lowBits + 0x10);

                    if ((p[0xDC] & 1) != 0)
                    {
                        v = (classFlags[idx] & 0xF0) | (unsigned char)(highBits + 1);
                    }

                    classFlags[idx] = v;
                }

                p       += 0x1B8;
                lowBits += 0x20;
                highBits += 2;
            }

            memcpy(&payload[1 + sizeof(caravanName)], classFlags, sizeof(classFlags));

            unsigned char compatBuf[64];
            memset(compatBuf, 0, sizeof(compatBuf));

            int compatLen = GbaQue.GetCompatibility(port, compatBuf);

            if (compatLen < 0)
            {
                compatLen = 0;
            }
            if (compatLen > (int)sizeof(compatBuf))
            {
                compatLen = (int)sizeof(compatBuf);
            }

            unsigned char* body = &payload[0xA3];

            if (compatLen > 0)
            {
                memcpy(body, compatBuf, (unsigned int)compatLen);
            }
			
            const int byteLen = compatLen + 0xA3;

            int wordCount = MakeJoyData((char*)payload, byteLen, (unsigned int*)(void*)(m_joyDataPacketBuffer[port] + 2));

            if (wordCount < 0)
            {
                return wordCount;
            }

            m_txWordCount[port] = wordCount;
            threadParam->m_subState = 1;

            // Immediately queue the first word (same as the subState == 1 path)
            unsigned char* base = m_joyDataPacketBuffer[port];
            unsigned int* wordPtr =
                (unsigned int*)(void*)(base + m_txWordIndex[port] * 4 + 2);
            unsigned int word = *wordPtr;

            if (m_threadRunningMask == 0)
            {
                result = 0;
            }
            else
            {
                OSWaitSemaphore(&m_accessSemaphores[port]);

                if ((int)m_cmdCount[port] < 0x40)
                {
                    m_cmdQueueData[port][m_cmdCount[port]] = word;
                    m_cmdCount[port]++;

                    OSSignalSemaphore(&m_accessSemaphores[port]);
                    result = 0;
                }
                else
                {
                    OSSignalSemaphore(&m_accessSemaphores[port]);
                    result = -1;
                }
            }
        }
    }

    // Common tail: advance word index and clear GBA flag when finished.
    if (result == 0)
    {
        m_txWordIndex[port]++;

        if (m_txWordCount[port] <= m_txWordIndex[port])
        {
            GbaQue.ClrCompatibilityFlg(port);

            return 1;
        }
    }

    return result;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::SendPlayerHP(ThreadParam* threadParam)
{
    unsigned int hpData[3];
	
	// TODO
    // sync = GBARecvSend(this, threadParam, hpData);
    int sync = 0;
	
    if (sync < 0)
	{
        return -1;
	}

    hpData[0] = 0;

    int hpStatus = GbaQue.GetPlayerHP(threadParam->m_portIndex, (unsigned char*)hpData);

    if (hpStatus >= 0)
	{
        return 0;
	}

    hpData[0] |= 0x00800000;

    unsigned int cmd = hpData[0];
    int result = 0;

    if (m_threadRunningMask != 0)
    {
        unsigned int port = threadParam->m_portIndex;

        OSWaitSemaphore(&m_accessSemaphores[port]);

        if ((int)m_cmdCount[port] < 0x40)
        {
            m_cmdQueueData[port][m_cmdCount[port]] = cmd;
            m_cmdCount[port]++;
        }
        else
        {
            result = -1;
        }

        OSSignalSemaphore(&m_accessSemaphores[port]);
    }

    return result;
}


/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::SendItemAll(ThreadParam* threadParam)
{
    const int port = threadParam->m_portIndex;
    int result = 0;

    if (threadParam->m_subState != 0 && threadParam->m_subState != 1)
    {
        return 0;
    }

    if (threadParam->m_subState == 1)
    {
        unsigned int* wordPtr = (unsigned int*)(m_joyDataPacketBuffer[port] + 2 + m_txWordIndex[port] * 4);
        unsigned int word = *wordPtr;

        if (m_threadRunningMask == 0)
        {
            result = 0;
        }
        else
        {
            OSWaitSemaphore(&m_accessSemaphores[port]);

            if ((int)m_cmdCount[port] < 0x40)
            {
                m_cmdQueueData[port][m_cmdCount[port]] = word;
                m_cmdCount[port]++;

                OSSignalSemaphore(&m_accessSemaphores[port]);
                result = 0;
            }
            else
            {
                OSSignalSemaphore(&m_accessSemaphores[port]);
                result = -1;
            }
        }
    }
    else
    {
        m_txWordIndex[port] = 0;

        unsigned char payload[780];

        memset(payload, 0, 0x300);

        memset(m_joyDataPacketBuffer[port] + 2, 0, 0x400);

        payload[0] = 2;

        unsigned char* itemBuf = &payload[1];

        int itemLen = GbaQue.GetItemAll(port, itemBuf);

        if (itemLen < 0)
        {
            itemLen = 0;
        }
        if (itemLen > 779)
        {
            itemLen = 779;
        }

        const int byteLen = itemLen + 1; // +1 for the type byte

        int wordCount = MakeJoyData(
            (char*)payload,
            byteLen,
            (unsigned int*)(m_joyDataPacketBuffer[port] + 2)
        );

        if (wordCount < 0)
        {
            return wordCount;
        }

        m_txWordCount[port] = wordCount;
        threadParam->m_subState = 1;

        unsigned int* wordPtr = (unsigned int*)(m_joyDataPacketBuffer[port] + 2 + m_txWordIndex[port] * 4);
        unsigned int word = *wordPtr;

        if (m_threadRunningMask == 0)
        {
            result = 0;
        }
        else
        {
            OSWaitSemaphore(&m_accessSemaphores[port]);

            if ((int)m_cmdCount[port] < 0x40)
            {
                m_cmdQueueData[port][m_cmdCount[port]] = word;
                m_cmdCount[port]++;

                OSSignalSemaphore(&m_accessSemaphores[port]);
                result = 0;
            }
            else
            {
                OSSignalSemaphore(&m_accessSemaphores[port]);
                result = -1;
            }
        }
    }

    if (result == 0)
    {
        m_txWordIndex[port]++;

        if (m_txWordCount[port] <= m_txWordIndex[port])
        {
            result = 1;
        }
    }

    return result;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::SendMapObj(ThreadParam* threadParam)
{
    const int port = threadParam->m_portIndex;
    int result = 0;

    if (threadParam->m_subState != 0 && threadParam->m_subState != 1)
    {
        return 0;
    }

    if (threadParam->m_subState == 1)
    {
        unsigned int* wordPtr = (unsigned int*)(m_joyDataPacketBuffer[port] + 2 + m_txWordIndex[port] * 4);
        unsigned int word = *wordPtr;

        if (m_threadRunningMask == 0)
        {
            result = 0;
        }
        else
        {
            OSWaitSemaphore(&m_accessSemaphores[port]);

            if ((int)m_cmdCount[port] < 0x40)
            {
                m_cmdQueueData[port][m_cmdCount[port]] = word;
                m_cmdCount[port]++;

                OSSignalSemaphore(&m_accessSemaphores[port]);
                result = 0;
            }
            else
            {
                OSSignalSemaphore(&m_accessSemaphores[port]);
                result = -1;
            }
        }
    }
    else
    {
        m_txWordIndex[port] = 0;

        unsigned char payload[524];
		
        memset(payload, 0, 0x200);

        payload[0] = 3;

        unsigned char* mapObjBuf = &payload[1];

        int dataLen = GbaQue.GetMapObj(mapObjBuf);

        if (dataLen < 0)
        {
            dataLen = 0;
        }
        if (dataLen > 523)
        {
            dataLen = 523;
        }

        const int byteLen = dataLen + 1;

        int wordCount = MakeJoyData((char*)payload, byteLen, (unsigned int*)(m_joyDataPacketBuffer[port] + 2));

        if (wordCount < 0)
        {
            return wordCount;
        }

        m_txWordCount[port] = wordCount;

        unsigned int* wordPtr = (unsigned int*)(m_joyDataPacketBuffer[port] + 2 + m_txWordIndex[port] * 4);
        unsigned int word = *wordPtr;

        if (m_threadRunningMask == 0)
        {
            result = 0;
        }
        else
        {
            OSWaitSemaphore(&m_accessSemaphores[port]);

            if ((int)m_cmdCount[port] < 0x40)
            {
                m_cmdQueueData[port][m_cmdCount[port]] = word;
                m_cmdCount[port]++;

                OSSignalSemaphore(&m_accessSemaphores[port]);
                result = 0;
            }
            else
            {
                OSSignalSemaphore(&m_accessSemaphores[port]);
                result = -1;
            }
        }

        threadParam->m_subState = (unsigned char)(threadParam->m_subState + 1);
    }

    if (result == 0)
    {
        m_txWordIndex[port]++;

        if (m_txWordCount[port] <= m_txWordIndex[port])
        {
            result = 1;
        }
    }

    return result;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::SendCompatibility(ThreadParam* threadParam)
{
    const int port = threadParam->m_portIndex;
    int result = 0;

    if (threadParam->m_subState != 0 && threadParam->m_subState != 1)
    {
        return 0;
    }

    if (threadParam->m_subState == 1)
    {
        unsigned char* base = m_joyDataPacketBuffer[port];
        unsigned int* wordPtr = (unsigned int*)(void*)(base + m_txWordIndex[port] * 4 + 2);
        unsigned int word = *wordPtr;

        if (m_threadRunningMask == 0)
        {
            result = 0;
        }
        else
        {
            OSWaitSemaphore(&m_accessSemaphores[port]);

            if ((int)m_cmdCount[port] < 0x40)
            {
                m_cmdQueueData[port][m_cmdCount[port]] = word;
                m_cmdCount[port]++;

                OSSignalSemaphore(&m_accessSemaphores[port]);
                result = 0;
            }
            else
            {
                OSSignalSemaphore(&m_accessSemaphores[port]);
                result = -1;
            }
        }
    }
    else
    {
        m_txWordIndex[port] = 0;
        unsigned char payload[268];
		
        memset(payload, 0, sizeof(payload));

        memset(m_joyDataPacketBuffer[port] + 2, 0, 0x400);
        payload[0] = 5;

        unsigned char* compatBuf = &payload[1];

        int compatLen = GbaQue.GetCompatibility(port, compatBuf);

        if (compatLen < 0)
        {
            compatLen = 0;
        }

        const int byteLen = compatLen + 1;

        int wordCount = MakeJoyData((char*)payload, byteLen, (unsigned int*)(void*)(m_joyDataPacketBuffer[port] + 2));

        if (wordCount < 0)
        {
            return wordCount;
        }

        m_txWordCount[port] = wordCount;
        threadParam->m_subState = 1;

        unsigned char* base = m_joyDataPacketBuffer[port];
        unsigned int* wordPtr = (unsigned int*)(void*)(base + m_txWordIndex[port] * 4 + 2);
        unsigned int word = *wordPtr;

        if (m_threadRunningMask == 0)
        {
            result = 0;
        }
        else
        {
            OSWaitSemaphore(&m_accessSemaphores[port]);

            if ((int)m_cmdCount[port] < 0x40)
            {
                m_cmdQueueData[port][m_cmdCount[port]] = word;
                m_cmdCount[port]++;

                OSSignalSemaphore(&m_accessSemaphores[port]);
				
                result = 0;
            }
            else
            {
                OSSignalSemaphore(&m_accessSemaphores[port]);
                result = -1;
            }
        }
    }

    if (result == 0)
    {
        m_txWordIndex[port]++;

        if (m_txWordCount[port] <= m_txWordIndex[port])
        {
            result = 1;
        }
    }

    return result;
}


/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::SendCtrlMode(ThreadParam* threadParam, int controlMode)
{
    const int port = threadParam->m_portIndex;
    unsigned char modeByte = static_cast<unsigned char>(controlMode);
    bool isSingle = GbaQue.IsSingleMode(port);

    // If single-player, force modeByte = 0
    if (isSingle)
	{
        modeByte = 0;
	}

    unsigned int cmd = (0x09u << 24) | (static_cast<unsigned int>(modeByte) << 16);
    int result = 0;

    if (m_threadRunningMask != 0)
    {
        OSWaitSemaphore(&m_accessSemaphores[port]);

        if (static_cast<int>(m_cmdCount[port]) < 0x40)
        {
            m_cmdQueueData[port][m_cmdCount[port]] = cmd;
            m_cmdCount[port]++;
            result = 0;
        }
        else
        {
            result = -1;
        }

        OSSignalSemaphore(&m_accessSemaphores[port]);
    }

    if (result == 0)
	{
        m_ctrlModeArr[port] = modeByte;
	}
	
	return result;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::SendMapObjDrawFlg(ThreadParam* threadParam)
{
    const int port = threadParam->m_portIndex;

    // TODO restore:
    // if (GBARecvSend(this, threadParam, &flgByte) < 0)
    //     return -1;
    unsigned char flgByte = 0;

    GbaQue.GetMapObjDrawFlg((unsigned int*)&flgByte);

    unsigned char data[4] = { 0, 0, 0, flgByte };
    unsigned int crc = 0xFFFF;

    for (int i = 0; i < 4; ++i)
    {
        unsigned char byte = data[i];
        unsigned int index = (crc >> 8) ^ byte;
        crc = ((crc << 8) ^ JoyBusCrcTable[index]) & 0xFFFF;
    }

    crc = (~crc) & 0xFFFF;

    unsigned int cmd1 = (0x16u << 24) | ((unsigned char)(crc & 0xFF) << 16) | ((unsigned char)((crc >> 8) & 0xFF) << 8) | data[0];
    unsigned int cmd2 = (0x56u << 24) | (data[1] << 16) | (data[2] << 8)  | (data[3]);

    if (m_threadRunningMask != 0)
    {
        OSWaitSemaphore(&m_accessSemaphores[port]);

        if ((int)m_cmdCount[port] < 0x40)
        {
            m_cmdQueueData[port][m_cmdCount[port]] = cmd1;
            m_cmdCount[port]++;
        }
        else
        {
            OSSignalSemaphore(&m_accessSemaphores[port]);
            return -1;
        }

        OSSignalSemaphore(&m_accessSemaphores[port]);
    }

    if (m_threadRunningMask != 0)
    {
        OSWaitSemaphore(&m_accessSemaphores[port]);

        if ((int)m_cmdCount[port] < 0x40)
        {
            m_cmdQueueData[port][m_cmdCount[port]] = cmd2;
            m_cmdCount[port]++;
        }
        else
        {
            OSSignalSemaphore(&m_accessSemaphores[port]);
            return -1;
        }

        OSSignalSemaphore(&m_accessSemaphores[port]);
    }

    return 0;
}

/*
 * --INFO--
 * PAL Address: 0x800a9df0
 * PAL Size: 700b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int JoyBus::SendFavorite(ThreadParam* threadParam)
{
    int result = 0;

    if (threadParam->m_subState != 0 && threadParam->m_subState != 1)
    {
        return 0;
    }

    if (threadParam->m_subState == 1)
    {
        unsigned int port = threadParam->m_portIndex;
        unsigned int* wordPtr = (unsigned int*)(m_joyDataPacketBuffer[port] + 2 + m_txWordIndex[port] * 4);
        unsigned int word = *wordPtr;

        if (m_threadRunningMask == 0)
        {
            result = 0;
        }
        else
        {
            OSWaitSemaphore(&m_accessSemaphores[port]);

            if ((int)m_cmdCount[port] < 0x40)
            {
                m_cmdQueueData[port][m_cmdCount[port]] = word;
                m_cmdCount[port]++;

                OSSignalSemaphore(&m_accessSemaphores[port]);
                result = 0;
            }
            else
            {
                OSSignalSemaphore(&m_accessSemaphores[port]);
                result = -1;
            }
        }
    }
    else
    {
        unsigned char payload[1 + 75];
        unsigned int port = threadParam->m_portIndex;

        memset(payload, 0, 0x40);
        memset(m_joyDataPacketBuffer[port] + 2, 0, 0x400);

        payload[0] = 4;

        unsigned char* favBuf = &payload[1];

        int dataLen = GbaQue.GetFavorite(port, (char*)favBuf);

        int wordCount = MakeJoyData(
            (char*)payload,
            dataLen + 1,
            (unsigned int*)(m_joyDataPacketBuffer[port] + 2)
        );

        if (wordCount < 0)
        {
            return wordCount;
        }

        m_txWordCount[port] = wordCount;
        m_txWordIndex[port] = 0;

        unsigned int* wordPtr = (unsigned int*)(m_joyDataPacketBuffer[port] + 2 + m_txWordIndex[port] * 4);
        unsigned int word = *wordPtr;

        if (m_threadRunningMask == 0)
        {
            result = 0;
        }
        else
        {
            OSWaitSemaphore(&m_accessSemaphores[port]);

            if ((int)m_cmdCount[port] < 0x40)
            {
                m_cmdQueueData[port][m_cmdCount[port]] = word;
                m_cmdCount[port]++;

                OSSignalSemaphore(&m_accessSemaphores[port]);
                result = 0;
            }
            else
            {
                OSSignalSemaphore(&m_accessSemaphores[port]);
                result = -1;
            }
        }

        threadParam->m_subState = (unsigned char)(threadParam->m_subState + 1);
    }

    if (result == 0)
    {
        unsigned int port = threadParam->m_portIndex;
        m_txWordIndex[port]++;

        if (m_txWordCount[port] <= m_txWordIndex[port])
        {
            result = 1;
        }
    }

    return result;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
unsigned int JoyBus::RequestData(ThreadParam* threadParam, int a, int b)
{
    unsigned int cmd = 0;
    unsigned int word = 0;

    word = (unsigned int)0x0C << 24;
    word |= (unsigned int)(unsigned char)a << 16;
    word |= (unsigned int)(unsigned char)b << 8;

    if (m_threadRunningMask != 0)
    {
        OSWaitSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);

        unsigned int p = threadParam->m_portIndex;

        if ((int)m_cmdCount[p] < 0x40)
        {
            m_cmdQueueData[p][m_cmdCount[p]] = word;
            m_cmdCount[p] = m_cmdCount[p] + 1;

            OSSignalSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);
            cmd = 0;
        }
        else
        {
            OSSignalSemaphore(&m_accessSemaphores[p]);
            cmd = 0xFFFFFFFF;
        }
    }

    return cmd;
}


/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::SetRecvBuffer(ThreadParam*, unsigned int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::ClrRecvBuffer(int portIndex)
{
    OSWaitSemaphore(&m_accessSemaphores[portIndex]);
    memset(&m_recvBuffer[portIndex], 0, sizeof(JoyBusRecvBuffer));
    OSSignalSemaphore(&m_accessSemaphores[portIndex]);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::GetRecvBuffer(int playerIndex, unsigned char* outBuffer)
{
    OSWaitSemaphore(&m_accessSemaphores[playerIndex]);
    memcpy(outBuffer, m_recvBuffer[playerIndex].m_payload, m_recvBuffer[playerIndex].m_length);
    OSSignalSemaphore(&m_accessSemaphores[playerIndex]);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::SendMType(ThreadParam* threadParam, int modeType)
{
    const int port = threadParam->m_portIndex;

    OSWaitSemaphore(&m_accessSemaphores[port]);

    memset(m_cmdQueueData[port], 0, sizeof(m_cmdQueueData[port]));
    memset(m_recvQueueEntriesArr[port], 0, sizeof(m_recvQueueEntriesArr[port]));

    m_cmdCount[port] = 0;
    m_secCmdCount[port] = 0;

    OSSignalSemaphore(&m_accessSemaphores[port]);

    int result = 0;

    if (m_threadRunningMask != 0)
    {
        OSWaitSemaphore(&m_accessSemaphores[port]);

        if ((int)m_cmdCount[port] < 0x40)
        {
            m_cmdQueueData[port][m_cmdCount[port]] = 0x10000000;
            m_cmdCount[port]++;
        }
        else
        {
            result = -1;
        }

        OSSignalSemaphore(&m_accessSemaphores[port]);
    }

    if (result != 0)
	{
        return result;
	}


    unsigned int cmd = (0x1Bu << 24) | ((unsigned char)modeType << 16);

    if (m_threadRunningMask != 0)
    {
        OSWaitSemaphore(&m_accessSemaphores[port]);

        if ((int)m_cmdCount[port] < 0x40)
        {
            m_cmdQueueData[port][m_cmdCount[port]] = cmd;
            m_cmdCount[port]++;
        }
        else
        {
            result = -1;
        }

        OSSignalSemaphore(&m_accessSemaphores[port]);
    }

    if (result != 0)
	{
        return result;
	}

    m_modeXArr[port] = m_nextModeTypeArr[port];
    m_nextModeTypeArr[port] = (unsigned char)modeType;

    if (modeType == 0 || modeType == 4)
	{
        m_ctrlModeArr[port] = 0;
	}
    else
	{
        m_ctrlModeArr[port] = 1;
	}
	
    return result;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::SendEquip(ThreadParam* threadParam)
{
    const int port = threadParam->m_portIndex;
    int result = 0;

    if (threadParam->m_subState != 0 && threadParam->m_subState != 1)
    {
        return 0;
    }

    if (threadParam->m_subState == 1)
    {
        unsigned int* wordPtr = (unsigned int*)(m_joyDataPacketBuffer[port] + 2 + m_txWordIndex[port] * 4);
        unsigned int word = *wordPtr;

        if (m_threadRunningMask == 0)
        {
            result = 0;
        }
        else
        {
            OSWaitSemaphore(&m_accessSemaphores[port]);

            if ((int)m_cmdCount[port] < 0x40)
            {
                m_cmdQueueData[port][m_cmdCount[port]] = word;
                m_cmdCount[port]++;

                OSSignalSemaphore(&m_accessSemaphores[port]);
                result = 0;
            }
            else
            {
                OSSignalSemaphore(&m_accessSemaphores[port]);
                result = -1;
            }
        }
    }
    else
    {
        m_txWordIndex[port] = 0;

        unsigned char payload[1 + 779];

        memset(payload, 0, 0x300);
        memset(m_joyDataPacketBuffer[port] + 2, 0, 0x400);

        payload[0] = 6;

        unsigned char* equipBuf = &payload[1];

        int dataLen = GbaQue.GetEquipData(port, equipBuf);

        if (dataLen < 0)
        {
            dataLen = 0;
        }

        if (dataLen > 779)
        {
            dataLen = 779;
        }

        const int byteLen = dataLen + 1;

        int wordCount = MakeJoyData((char*)payload, byteLen, (unsigned int*)(m_joyDataPacketBuffer[port] + 2));

        if (wordCount < 0)
        {
            return wordCount;
        }

        m_txWordCount[port] = wordCount;

        threadParam->m_subState = (unsigned char)(threadParam->m_subState + 1);

        unsigned int* wordPtr = (unsigned int*)(m_joyDataPacketBuffer[port] + 2 + m_txWordIndex[port] * 4);
        unsigned int word = *wordPtr;

        if (m_threadRunningMask == 0)
        {
            result = 0;
        }
        else
        {
            OSWaitSemaphore(&m_accessSemaphores[port]);

            if ((int)m_cmdCount[port] < 0x40)
            {
                m_cmdQueueData[port][m_cmdCount[port]] = word;
                m_cmdCount[port]++;

                OSSignalSemaphore(&m_accessSemaphores[port]);
                result = 0;
            }
            else
            {
                OSSignalSemaphore(&m_accessSemaphores[port]);
                result = -1;
            }
        }
    }

    if (result == 0)
    {
        m_txWordIndex[port]++;

        if (m_txWordCount[port] <= m_txWordIndex[port])
        {
            result = 1;
        }
    }

    return result;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::SendCmd(ThreadParam* threadParam)
{
    const int port = threadParam->m_portIndex;
    int result = 0;

    if (threadParam->m_subState != 0 && threadParam->m_subState != 1)
    {
        return 0;
    }

    if (threadParam->m_subState == 1)
    {
        unsigned int* wordPtr = (unsigned int*)(m_joyDataPacketBuffer[port] + 2 + m_txWordIndex[port] * 4);
        unsigned int word = *wordPtr;

        if (m_threadRunningMask == 0)
        {
            result = 0;
        }
        else
        {
            OSWaitSemaphore(&m_accessSemaphores[port]);

            if ((int)m_cmdCount[port] < 0x40)
            {
                m_cmdQueueData[port][m_cmdCount[port]] = word;
                m_cmdCount[port]++;

                OSSignalSemaphore(&m_accessSemaphores[port]);
                result = 0;
            }
            else
            {
                OSSignalSemaphore(&m_accessSemaphores[port]);
                result = -1;
            }
        }
    }
    else
    {
        m_txWordIndex[port] = 0;

        unsigned char payload[1 + 779];

        memset(payload, 0, 0x300);
        memset(m_joyDataPacketBuffer[port] + 2, 0, 0x400);

        payload[0] = 0x0c;

        unsigned char* cmdBuf = &payload[1];

        int dataLen = 3; // TODO: GetCmdData__8GbaQueueFiPUc(&GbaQue, port, cmdBuf);

        if (dataLen < 0)
        {
            dataLen = 0;
        }

        if (dataLen > 779)
        {
            dataLen = 779;
        }

        const int byteLen = dataLen + 1;

        int wordCount = MakeJoyData((char*)payload, byteLen, (unsigned int*)(m_joyDataPacketBuffer[port] + 2));

        if (wordCount < 0)
        {
            return wordCount;
        }

        m_txWordCount[port] = wordCount;

        threadParam->m_subState = (unsigned char)(threadParam->m_subState + 1);

        unsigned int* wordPtr = (unsigned int*)(m_joyDataPacketBuffer[port] + 2 + m_txWordIndex[port] * 4);
        unsigned int word = *wordPtr;

        if (m_threadRunningMask == 0)
        {
            result = 0;
        }
        else
        {
            OSWaitSemaphore(&m_accessSemaphores[port]);

            if ((int)m_cmdCount[port] < 0x40)
            {
                m_cmdQueueData[port][m_cmdCount[port]] = word;
                m_cmdCount[port]++;

                OSSignalSemaphore(&m_accessSemaphores[port]);
                result = 0;
            }
            else
            {
                OSSignalSemaphore(&m_accessSemaphores[port]);
                result = -1;
            }
        }
    }

    if (result == 0)
    {
        m_txWordIndex[port]++;

        if (m_txWordCount[port] <= m_txWordIndex[port])
        {
            result = 1;
        }
    }

    return result;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::SendBonusStr(ThreadParam* threadParam)
{
    const int port = threadParam->m_portIndex;
    int result = 0;

    if (threadParam->m_subState != 0 && threadParam->m_subState != 1)
    {
        return 0;
    }

    if (threadParam->m_subState == 1)
    {
        unsigned int* wordPtr = (unsigned int*)(m_joyDataPacketBuffer[port] + 2 + m_txWordIndex[port] * 4);
        unsigned int word = *wordPtr;

        if (m_threadRunningMask == 0)
        {
            result = 0;
        }
        else
        {
            OSWaitSemaphore(&m_accessSemaphores[port]);

            if ((int)m_cmdCount[port] < 0x40)
            {
                m_cmdQueueData[port][m_cmdCount[port]] = word;
                m_cmdCount[port]++;

                OSSignalSemaphore(&m_accessSemaphores[port]);
                result = 0;
            }
            else
            {
                OSSignalSemaphore(&m_accessSemaphores[port]);
                result = -1;
            }
        }
    }
    else
    {
        m_txWordIndex[port] = 0;

        unsigned char payload[1 + 1 + 258];

        memset(payload, 0, 0x100);
        memset(m_joyDataPacketBuffer[port] + 2, 0, 0x400);

        payload[0] = 7;

        unsigned char* bonusStr = &payload[1];
        unsigned char* extraBuf = &payload[2];

        (void)bonusStr;
        (void)extraBuf;

        int byteLen = 3; // TODO
        int wordCount = MakeJoyData((char*)payload, byteLen, (unsigned int*)(m_joyDataPacketBuffer[port] + 2));

        if (wordCount < 0)
        {
            return wordCount;
        }

        m_txWordCount[port] = wordCount;

        threadParam->m_subState = (unsigned char)(threadParam->m_subState + 1);

        unsigned int* wordPtr = (unsigned int*)(m_joyDataPacketBuffer[port] + 2 + m_txWordIndex[port] * 4);
        unsigned int word = *wordPtr;

        if (m_threadRunningMask == 0)
        {
            result = 0;
        }
        else
        {
            OSWaitSemaphore(&m_accessSemaphores[port]);

            if ((int)m_cmdCount[port] < 0x40)
            {
                m_cmdQueueData[port][m_cmdCount[port]] = word;
                m_cmdCount[port]++;

                OSSignalSemaphore(&m_accessSemaphores[port]);
                result = 0;
            }
            else
            {
                OSSignalSemaphore(&m_accessSemaphores[port]);
                result = -1;
            }
        }
    }

    if (result == 0)
    {
        m_txWordIndex[port]++;

        if (m_txWordCount[port] <= m_txWordIndex[port])
        {
            result = 1;
        }
    }

    return result;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::SendArtifact(ThreadParam* threadParam)
{
    const int port = threadParam->m_portIndex;
    int result = 0;

    if (threadParam->m_subState != 0 && threadParam->m_subState != 1)
    {
        return 0;
    }

    if (threadParam->m_subState == 1)
    {
        unsigned int* wordPtr = (unsigned int*)(m_joyDataPacketBuffer[port] + 2 + m_txWordIndex[port] * 4);
        unsigned int word = *wordPtr;

        if (m_threadRunningMask == 0)
        {
            result = 0;
        }
        else
        {
            OSWaitSemaphore(&m_accessSemaphores[port]);

            if ((int)m_cmdCount[port] < 0x40)
            {
                m_cmdQueueData[port][m_cmdCount[port]] = word;
                m_cmdCount[port]++;

                OSSignalSemaphore(&m_accessSemaphores[port]);
                result = 0;
            }
            else
            {
                OSSignalSemaphore(&m_accessSemaphores[port]);
                result = -1;
            }
        }
    }
    else
    {
        m_txWordIndex[port] = 0;

        unsigned char payload[1 + 267];

        memset(payload, 0, 0x100);
        memset(m_joyDataPacketBuffer[port] + 2, 0, 0x400);

        payload[0] = 8;

        unsigned char* artiBuf = &payload[1];

        int dataLen = GbaQue.GetArtifactData(port, artiBuf);

        if (dataLen < 0)
        {
            dataLen = 0;
        }
		
        if (dataLen > 267)
        {
            dataLen = 267;
        }

        const int byteLen = dataLen + 1;
        int wordCount = MakeJoyData((char*)payload, byteLen, (unsigned int*)(m_joyDataPacketBuffer[port] + 2));

        if (wordCount < 0)
        {
            return wordCount;
        }

        m_txWordCount[port] = wordCount;

        threadParam->m_subState = (unsigned char)(threadParam->m_subState + 1);

        unsigned int* wordPtr = (unsigned int*)(m_joyDataPacketBuffer[port] + 2 + m_txWordIndex[port] * 4);
        unsigned int word = *wordPtr;

        if (m_threadRunningMask == 0)
        {
            result = 0;
        }
        else
        {
            OSWaitSemaphore(&m_accessSemaphores[port]);

            if ((int)m_cmdCount[port] < 0x40)
            {
                m_cmdQueueData[port][m_cmdCount[port]] = word;
                m_cmdCount[port]++;

                OSSignalSemaphore(&m_accessSemaphores[port]);
                result = 0;
            }
            else
            {
                OSSignalSemaphore(&m_accessSemaphores[port]);
                result = -1;
            }
        }
    }

    if (result == 0)
    {
        m_txWordIndex[port]++;

        if (m_txWordCount[port] <= m_txWordIndex[port])
        {
            result = 1;
        }
    }

    return result;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::SendTmpArtifact(ThreadParam* threadParam)
{
    const int port = threadParam->m_portIndex;
    int result = 0;

    if (threadParam->m_subState != 0 && threadParam->m_subState != 1)
    {
        return 0;
    }

    if (threadParam->m_subState == 1)
    {
        unsigned int* wordPtr = (unsigned int*)(m_joyDataPacketBuffer[port] + 2 + m_txWordIndex[port] * 4);
        unsigned int word = *wordPtr;

        if (m_threadRunningMask == 0)
        {
            result = 0;
        }
        else
        {
            OSWaitSemaphore(&m_accessSemaphores[port]);

            if ((int)m_cmdCount[port] < 0x40)
            {
                m_cmdQueueData[port][m_cmdCount[port]] = word;
                m_cmdCount[port]++;

                OSSignalSemaphore(&m_accessSemaphores[port]);
                result = 0;
            }
            else
            {
                OSSignalSemaphore(&m_accessSemaphores[port]);
                result = -1;
            }
        }
    }
    else
    {
        m_txWordIndex[port] = 0;

        unsigned char payload[1 + 267];

        memset(payload, 0, 0x100);
        memset(m_joyDataPacketBuffer[port] + 2, 0, 0x400);

        payload[0] = 9;

        unsigned char* artiBuf = &payload[1];

        int dataLen = GbaQue.GetTmpArtifactData(port, artiBuf);

        if (dataLen < 0)
        {
            dataLen = 0;
        }
		
        if (dataLen > 267)
        {
            dataLen = 267;
        }

        const int byteLen = dataLen + 1;
        int wordCount = MakeJoyData((char*)payload, byteLen, (unsigned int*)(m_joyDataPacketBuffer[port] + 2));

        if (wordCount < 0)
        {
            return wordCount;
        }

        m_txWordCount[port] = wordCount;

        threadParam->m_subState = (unsigned char)(threadParam->m_subState + 1);

        unsigned int* wordPtr = (unsigned int*)(m_joyDataPacketBuffer[port] + 2 + m_txWordIndex[port] * 4);
        unsigned int word = *wordPtr;

        if (m_threadRunningMask == 0)
        {
            result = 0;
        }
        else
        {
            OSWaitSemaphore(&m_accessSemaphores[port]);

            if ((int)m_cmdCount[port] < 0x40)
            {
                m_cmdQueueData[port][m_cmdCount[port]] = word;
                m_cmdCount[port]++;

                OSSignalSemaphore(&m_accessSemaphores[port]);
                result = 0;
            }
            else
            {
                OSSignalSemaphore(&m_accessSemaphores[port]);
                result = -1;
            }
        }
    }

    if (result == 0)
    {
        m_txWordIndex[port]++;

        if (m_txWordCount[port] <= m_txWordIndex[port])
        {
            result = 1;
        }
    }

    return result;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::SendMapObjInfo(ThreadParam* threadParam)
{
    const int port = threadParam->m_portIndex;
    int result = 0;

    if (threadParam->m_subState != 0 && threadParam->m_subState != 1)
    {
        return 0;
    }

    if (threadParam->m_subState == 1)
    {
        unsigned char* base = m_joyDataPacketBuffer[port];
        unsigned int* wordPtr = (unsigned int*)(m_joyDataPacketBuffer[port] + 2 + m_txWordIndex[port] * 4);
        unsigned int word = *wordPtr;

        if (m_threadRunningMask == 0)
        {
            result = 0;
        }
        else
        {
            OSWaitSemaphore(&m_accessSemaphores[port]);

            if ((int)m_cmdCount[port] < 0x40)
            {
                m_cmdQueueData[port][m_cmdCount[port]] = word;
                m_cmdCount[port]++;

                OSSignalSemaphore(&m_accessSemaphores[port]);
                result = 0;
            }
            else
            {
                OSSignalSemaphore(&m_accessSemaphores[port]);
                result = -1;
            }
        }
    }
    else
    {
        m_txWordIndex[port] = 0;

        unsigned char payload[268];
		
        memset(payload, 0, 0x100);
        memset(m_joyDataPacketBuffer[port] + 2, 0, 0x400);

        payload[0] = 10;

        unsigned char* mapObjBuf = &payload[1];

        int dataLen = GbaQue.GetMapObjInfo(port, mapObjBuf);

        if (dataLen < 0)
        {
            dataLen = 0;
        }
        if (dataLen > 267)
        {
            dataLen = 267;
        }

        const int byteLen = dataLen + 1;

        int wordCount = MakeJoyData(
            (char*)payload,
            byteLen,
            (unsigned int*)(m_joyDataPacketBuffer[port] + 2)
        );

        if (wordCount < 0)
        {
            return wordCount;
        }

        m_txWordCount[port] = wordCount;
        threadParam->m_subState = 1;

        unsigned int* wordPtr = (unsigned int*)(m_joyDataPacketBuffer[port] + 2 + m_txWordIndex[port] * 4);
        unsigned int word = *wordPtr;

        if (m_threadRunningMask == 0)
        {
            result = 0;
        }
        else
        {
            OSWaitSemaphore(&m_accessSemaphores[port]);

            if ((int)m_cmdCount[port] < 0x40)
            {
                m_cmdQueueData[port][m_cmdCount[port]] = word;
                m_cmdCount[port]++;

                OSSignalSemaphore(&m_accessSemaphores[port]);
                result = 0;
            }
            else
            {
                OSSignalSemaphore(&m_accessSemaphores[port]);
                result = -1;
            }
        }
    }

    if (result == 0)
    {
        m_txWordIndex[port]++;

        if (m_txWordCount[port] <= m_txWordIndex[port])
        {
            result = 1;
        }
    }

    return result;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::SendStrength(ThreadParam* threadParam)
{
    // Strength data returned as 3 bytes
    unsigned char strength[3];

    GbaQue.GetStrengthData(threadParam->m_portIndex, (unsigned char*)&strength);

    const unsigned short opcode = static_cast<unsigned short>(0x1900 | strength[0]);
    const unsigned int cmd = MakeJoyCmd16(opcode, strength[1], strength[2]);

    // If threads not running, return success
    if (m_threadRunningMask == 0)
	{
        return 0;
	}

    const unsigned int port = threadParam->m_portIndex;

    OSWaitSemaphore(&m_accessSemaphores[port]);

    int result = 0;

    if ((int)m_cmdCount[port] < 0x40)
    {
        m_cmdQueueData[port][m_cmdCount[port]] = cmd;
        m_cmdCount[port]++;
    }
    else
    {
        result = -1;
    }

    OSSignalSemaphore(&m_accessSemaphores[port]);
	
    return result;
}


/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::SendRaderType(ThreadParam* threadParam)
{
    const int port = threadParam->m_portIndex;
    unsigned char radarType = GbaQue.GetRadarType(port);
    unsigned short opcode = 0x140D;
    unsigned int cmd = MakeJoyCmd16(opcode, radarType, 0);

    int result = 0;

    if (m_threadRunningMask != 0)
    {
        OSWaitSemaphore(&m_accessSemaphores[port]);

        if ((int)m_cmdCount[port] < 0x40)
        {
            m_cmdQueueData[port][m_cmdCount[port]] = cmd;
            m_cmdCount[port]++;
        }
        else
        {
            result = -1;
        }

        OSSignalSemaphore(&m_accessSemaphores[port]);
    }

    return result;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::SendRaderMode(ThreadParam* threadParam)
{
    const int port = threadParam->m_portIndex;

    unsigned char radarType = GbaQue.GetRadarType(port);
    unsigned short opcode = 0x140D;
    unsigned int cmd = MakeJoyCmd16(opcode, radarType, 0);

    int result = 0;

    if (m_threadRunningMask != 0)
    {
        OSWaitSemaphore(&m_accessSemaphores[port]);

        if ((int)m_cmdCount[port] < 0x40)
        {
            m_cmdQueueData[port][m_cmdCount[port]] = cmd;
            m_cmdCount[port]++;
        }
        else
        {
            result = -1;
        }

        OSSignalSemaphore(&m_accessSemaphores[port]);
    }

    return result;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::SendScouInfo(ThreadParam* threadParam)
{
    const int port = threadParam->m_portIndex;
    int result = 0;

    if (threadParam->m_subState != 0 && threadParam->m_subState != 1)
    {
        return 0;
    }

    if (threadParam->m_subState == 1)
    {
        unsigned char* base = m_joyDataPacketBuffer[port];
        unsigned int* wordPtr = (unsigned int*)(void*)(base + m_txWordIndex[port] * 4 + 2);
        unsigned int word = *wordPtr;

        if (m_threadRunningMask == 0)
        {
            result = 0;
        }
        else
        {
            OSWaitSemaphore(&m_accessSemaphores[port]);

            if ((int)m_cmdCount[port] < 0x40)
            {
                m_cmdQueueData[port][m_cmdCount[port]] = word;
                m_cmdCount[port]++;

                OSSignalSemaphore(&m_accessSemaphores[port]);
                result = 0;
            }
            else
            {
                OSSignalSemaphore(&m_accessSemaphores[port]);
                result = -1;
            }
        }
    }
    else
    {
        m_txWordIndex[port] = 0;

        unsigned char payload[0x400];
        memset(payload, 0, sizeof(payload));

        memset(m_joyDataPacketBuffer[port] + 2, 0, 0x400);

        payload[0] = 0x0B;

        unsigned char* scouterBuf = &payload[1];

        int dataLen = GbaQue.GetScouterInfo(port, scouterBuf);

        if (dataLen < 0)
        {
            dataLen = 0;
        }

        const int byteLen = dataLen + 1;

        int wordCount = MakeJoyData((char*)payload, byteLen, (unsigned int*)(void*)(m_joyDataPacketBuffer[port] + 2));

        if (wordCount < 0)
        {
            return wordCount;
        }

        m_txWordCount[port] = wordCount;
        threadParam->m_subState = 1;

        unsigned char* base = m_joyDataPacketBuffer[port];
        unsigned int* wordPtr = (unsigned int*)(void*)(base + m_txWordIndex[port] * 4 + 2);
        unsigned int word = *wordPtr;

        if (m_threadRunningMask == 0)
        {
            result = 0;
        }
        else
        {
            OSWaitSemaphore(&m_accessSemaphores[port]);

            if ((int)m_cmdCount[port] < 0x40)
            {
                m_cmdQueueData[port][m_cmdCount[port]] = word;
                m_cmdCount[port]++;

                OSSignalSemaphore(&m_accessSemaphores[port]);
                result = 0;
            }
            else
            {
                OSSignalSemaphore(&m_accessSemaphores[port]);
                result = -1;
            }
        }
    }

    if (result == 0)
    {
        m_txWordIndex[port]++;

        if (m_txWordCount[port] <= m_txWordIndex[port])
        {
            result = 1;
        }
    }

    return result;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::SendOpenMenu(ThreadParam* threadParam, char menuId)
{
    const int port = threadParam->m_portIndex;
    bool isSingle = GbaQue.IsSingleMode(port);

    if (isSingle)
	{
        return 0;
	}

    // Command: [0x14][0x0F][menuId][0]
    unsigned short opcode = 0x140F;
    unsigned int cmd = MakeJoyCmd16(opcode, menuId, 0);

    int result = 0;

    if (m_threadRunningMask != 0)
    {
        OSWaitSemaphore(&m_accessSemaphores[port]);

        if ((int)m_cmdCount[port] < 0x40)
        {
            m_cmdQueueData[port][m_cmdCount[port]] = cmd;
            m_cmdCount[port]++;
        }
        else
        {
            result = -1;
        }

        OSSignalSemaphore(&m_accessSemaphores[port]);
    }

    return result;
}


/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::SendItemUse(ThreadParam* threadParam)
{
    const int port = threadParam->m_portIndex;
    bool isSingle = GbaQue.IsSingleMode(port);

    if (isSingle)
    {
        return 0;
    }

    unsigned char itemId = GbaQue.GetItemUse(port);
    unsigned int cmd = MakeJoyCmd16(0x1410, itemId);
    int result = 0;

    if (m_threadRunningMask != 0)
    {
        OSWaitSemaphore(&m_accessSemaphores[port]);

        if (static_cast<int>(m_cmdCount[port]) < 0x40)
        {
            m_cmdQueueData[port][m_cmdCount[port]] = cmd;
            m_cmdCount[port]++;
        }
        else
        {
            result = -1;
        }

        OSSignalSemaphore(&m_accessSemaphores[port]);
    }

    return result;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::SendSPMode(ThreadParam* threadParam)
{
    unsigned int mode = GbaQue.GetSPMode(threadParam->m_portIndex);
    const unsigned char bVar1 = (mode != 0) ? 1 : 0;
    const unsigned short opcode = 0x1411;
    const unsigned int cmd = MakeJoyCmd16(opcode, bVar1, 0);
    int result = 0;

    if (m_threadRunningMask != 0)
    {
        const unsigned int port = threadParam->m_portIndex;

        OSWaitSemaphore(&m_accessSemaphores[port]);

        if ((int)m_cmdCount[port] < 0x40)
        {
            m_cmdQueueData[port][m_cmdCount[port]] = cmd;
            m_cmdCount[port]++;
        }
        else
        {
            result = -1;
        }

        OSSignalSemaphore(&m_accessSemaphores[port]);
    }

    // On success, update the threadParam flags
    if (result == 0)
    {
        threadParam->m_flags[6] = bVar1;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::SendMemorys(ThreadParam* threadParam)
{
    const int port = threadParam->m_portIndex;
    unsigned char value = GbaQue.GetMemorys(port);
    unsigned int cmd = (0x14u << 24) | (0x13u << 16) | (value << 8);

    if (m_threadRunningMask == 0)
	{
        return 0;
	}

    unsigned int result = 0;

    OSWaitSemaphore(&m_accessSemaphores[port]);

    if ((int)m_cmdCount[port] < 0x40)
    {
        m_cmdQueueData[port][m_cmdCount[port]] = cmd;
        m_cmdCount[port]++;
    }
    else
    {
        result = 0xFFFFFFFF;
    }

    OSSignalSemaphore(&m_accessSemaphores[port]);

    return result;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::SendChgCmdNum(ThreadParam* threadParam)
{
    const int port = threadParam->m_portIndex;
    unsigned char cmdNum = GbaQue.GetCmdNum(port);
    unsigned int cmd = (0x14u << 24) | (0x12u << 16) | (static_cast<unsigned int>(cmdNum) << 8);
    int result = 0;

    if (m_threadRunningMask != 0)
    {
        OSWaitSemaphore(&m_accessSemaphores[port]);

        if (static_cast<int>(m_cmdCount[port]) < 0x40)
        {
            m_cmdQueueData[port][m_cmdCount[port]] = cmd;
            m_cmdCount[port]++;
        }
        else
        {
            result = -1;
        }

        OSSignalSemaphore(&m_accessSemaphores[port]);
    }

    return result;
}


/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::SendStartBonus(ThreadParam* threadParam)
{
    const unsigned int cmd = MakeJoyCmd16(0x1414, 0, 0);

    if (m_threadRunningMask == 0)
	{
        return 0;
	}

    const unsigned int port = threadParam->m_portIndex;

    OSWaitSemaphore(&m_accessSemaphores[port]);

    int result = 0;

    if ((int)m_cmdCount[port] < 0x40)
    {
        m_cmdQueueData[port][m_cmdCount[port]] = cmd;
        m_cmdCount[port]++;
    }
    else
    {
        result = -1;
    }

    OSSignalSemaphore(&m_accessSemaphores[port]);
    return result;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::DecRecvQueue(int portIndex)
{
    OSWaitSemaphore(&m_accessSemaphores[portIndex]);

    m_recvQueueEntriesArr[portIndex][ m_secCmdCount[portIndex] ] = 0;
    m_secCmdCount[portIndex]--;

    OSSignalSemaphore(&m_accessSemaphores[portIndex]);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::GetGBAStat(ThreadParam* threadParam)
{
    bool single = GbaQue.IsSingleMode(threadParam->m_portIndex);

    if (!single || threadParam->m_portIndex == 1)
    {
		// TODO // GBAGetStatus(threadParam->m_portIndex, &threadParam->m_unk3);
        threadParam->m_gbaStatus = (int)this;
    }
    else
    {
        threadParam->m_gbaStatus = 0;
    }

    return threadParam->m_gbaStatus;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::ChgCtrlMode(int portIndex)
{
    unsigned char mode = m_ctrlModeArr[portIndex];
    bool single = GbaQue.IsSingleMode(portIndex);

    if (!single)
    {
        mode ^= 1; // TODO (unsigned char)DAT_80330b20;

        unsigned int word = ((unsigned int)9 << 24) | ((unsigned int)mode << 16);
        int ret = 0;

        if (m_threadRunningMask != 0)
        {
            int p = m_threadParams[portIndex].m_portIndex;

            OSWaitSemaphore(&m_accessSemaphores[p]);

            if ((int)m_cmdCount[p] < 0x40)
            {
                m_cmdQueueData[p][m_cmdCount[p]] = word;
                m_cmdCount[p] = m_cmdCount[p] + 1;

                OSSignalSemaphore(&m_accessSemaphores[p]);
                ret = 0;
            }
            else
            {
                OSSignalSemaphore(&m_accessSemaphores[p]);
                ret = -1;
            }
        }

        if (ret == 0)
        {
            m_ctrlModeArr[portIndex] = mode;
        }

        return ret;
    }

    return 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::SetCtrlMode(int portIndex, int controlMode)
{
    bool isSingle = GbaQue.IsSingleMode(portIndex);

    if (isSingle)
	{
        return 0;
	}

    unsigned char modeFlag = (controlMode != 0) ? 1 : 0;
    bool isSinglePort = GbaQue.IsSingleMode(m_threadParams[portIndex].m_portIndex);

    if (isSinglePort)
	{
        modeFlag = 0;
	}

    const unsigned short opcode = 0x0900;
    const unsigned int cmd = MakeJoyCmd16(opcode, modeFlag, 0);

    int result = 0;

    if (m_threadRunningMask != 0)
    {
        const unsigned int port = m_threadParams[portIndex].m_portIndex;

        OSWaitSemaphore(&m_accessSemaphores[port]);

        if ((int)m_cmdCount[port] < 0x40)
        {
            m_cmdQueueData[port][m_cmdCount[port]] = cmd;
            m_cmdCount[port]++;
        }
        else
        {
            result = -1;
        }

        OSSignalSemaphore(&m_accessSemaphores[port]);
    }

    // If successful, update local mode tracking
    if (result == 0)
    {
        const unsigned int port = m_threadParams[portIndex].m_portIndex;
        m_ctrlModeArr[port] = modeFlag;
    }

    return result;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
unsigned char JoyBus::GetCtrlMode(int portIndex)
{
    bool single = GbaQue.IsSingleMode(portIndex);

    if (!single)
    {
        return m_ctrlModeArr[portIndex];
    }

    return 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::GetGBAConnect(int portIndex)
{
    OSWaitSemaphore(m_accessSemaphores + portIndex);
    int state = m_threadParams[portIndex].m_state;
    OSSignalSemaphore(m_accessSemaphores + portIndex);

    if (state < 5 || state >= 900)
	{
        return 0;
    }
    else if (state >= 0x14 && state <= 0x16)
	{
        return 0;
    }
    else
	{
        return 1;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::IsInitSend(int portIndex)
{
    ThreadParam& tp = m_threadParams[portIndex];

    OSWaitSemaphore(&m_accessSemaphores[portIndex]);
    unsigned int state = tp.m_state;
    OSSignalSemaphore(&m_accessSemaphores[portIndex]);

    unsigned int result = 0;

    // Determine desired "init send" state
    if (tp.m_sentStartFlag == 0 && state < 0x385)
    {
        if (state < 2)
        {
            result = 0;
        }
        else if (state == 2)
        {
            result = (tp.m_flags[0] ? 0 : 1);
        }
        else
        {
            result = 1;
        }
    }
    else
    {
        result = 0;
    }

    // Stabilizer logic: detect and debounce changes to result
    if (tp.m_flags[2] == result)
    {
        tp.m_flags[3] = 0;
    }
    else
    {
        unsigned char cnt = tp.m_flags[3];

        if (cnt < 8)
        {
            tp.m_flags[3] = cnt + 1;
            result = tp.m_flags[2];
        }
        else
        {
            tp.m_flags[2] = (unsigned char)result;
            tp.m_flags[3] = 0;
        }
    }

    return result;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
bool JoyBus::GetGBAStart(int portIndex)
{
	return m_threadParams[portIndex].m_sentStartFlag != 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::GBAReady(int portIndex)
{
    unsigned int padType;

    OSWaitSemaphore(&m_accessSemaphores[portIndex]);
    padType = m_threadParams[portIndex].m_padType;
    OSSignalSemaphore(&m_accessSemaphores[portIndex]);
	
	// TODO: No idea
    int ready = padType;

    // TODO: IsSingleMode__8GbaQueueFi
    bool isSingle = (bool)this;

    if (isSingle)
    {
        ready = 0;
    }

    return ready;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::SendAllStat(int portIndex)
{
    ThreadParam* threadParam = &m_threadParams[portIndex];
    int port = threadParam->m_portIndex;

    threadParam->m_state = 0;
    threadParam->m_altState = 0;

    OSWaitSemaphore(&m_accessSemaphores[port]);

    unsigned int* cmdQueue = m_cmdQueueData[port];
    unsigned int* recvQueue = m_recvQueueEntriesArr[port];
    int i = 8;

    do
    {
        cmdQueue[0] = 0;
        recvQueue[0] = 0;
        cmdQueue[1] = 0;
        recvQueue[1] = 0;
        cmdQueue[2] = 0;
        recvQueue[2] = 0;
        cmdQueue[3] = 0;
        recvQueue[3] = 0;
        cmdQueue[4] = 0;
        recvQueue[4] = 0;
        cmdQueue[5] = 0;
        recvQueue[5] = 0;
        cmdQueue[6] = 0;
        recvQueue[6] = 0;
        cmdQueue[7] = 0;
        recvQueue[7] = 0;

        cmdQueue += 8;
        recvQueue += 8;
        i--;
    } while (i != 0);

    m_cmdCount[port] = 0;
    m_secCmdCount[port] = 0;

    OSSignalSemaphore(&m_accessSemaphores[port]);

    return 0;
}


/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
char* JoyBus::GetLetterBuffer(int portIndex)
{
	return m_letterBuffer[portIndex];
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::SetLetterSize(int portIndex, int letterSize)

{
	m_letterSizeArr[portIndex] = letterSize;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::SendResult(int portIndex, int param3, int param4, int param5)
{
    unsigned char a = static_cast<unsigned char>(param4);
    unsigned char b = static_cast<unsigned char>(param5);
    unsigned char firstByte = (param3 == 0) ? 6 : 7;
    unsigned short opcode = static_cast<unsigned short>((static_cast<unsigned short>(firstByte) << 8) | a);
    unsigned int cmd = MakeJoyCmd16(opcode, b, 0);

    int result = 0;

    if (m_threadRunningMask != 0)
    {
        unsigned int port = m_threadParams[portIndex].m_portIndex;

        OSWaitSemaphore(&m_accessSemaphores[port]);

        if (static_cast<int>(m_cmdCount[port]) < 0x40)
        {
            m_cmdQueueData[port][m_cmdCount[port]] = cmd;
            m_cmdCount[port]++;
        }
        else
        {
            result = -1;
        }

        OSSignalSemaphore(&m_accessSemaphores[port]);
    }

    return result;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
bool JoyBus::IsLetterMenu(int portIndex)
{
    OSWaitSemaphore(&m_accessSemaphores[portIndex]);
	
    unsigned char menuCode = m_stateCodeArr[portIndex];
	
    OSSignalSemaphore(&m_accessSemaphores[portIndex]);

    return menuCode == 9;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::SendAddLetter(int portIndex)
{
    int port;
    int result = 0;

    if (m_threadRunningMask != 0)
    {
        port = m_threadParams[portIndex].m_portIndex;

        OSWaitSemaphore(m_accessSemaphores + port);

        if ((int)m_cmdCount[port] < 0x40)
        {
            m_cmdQueueData[port][ m_cmdCount[port] ] = 0x14010000;
            m_cmdCount[port]++;

            OSSignalSemaphore(m_accessSemaphores + port);
            result = 0;
        }
        else
        {
            OSSignalSemaphore(m_accessSemaphores + port);
            result = -1;
        }
    }

    return result;
}



/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::SetItem(int portIndex, unsigned char itemId, short amount)
{
    unsigned short opcode = static_cast<unsigned short>(0x1700 | itemId);
    unsigned char amtLo = static_cast<unsigned char>(amount & 0xFF);
    unsigned char amtHi = static_cast<unsigned char>((amount >> 8) & 0xFF);
    unsigned int cmd = MakeJoyCmd16(opcode, amtLo, amtHi);

    cmd &= 0xFF3FFFFF;

    // If threads are not running, treat as success
    if (m_threadRunningMask == 0)
	{
        return 0;
	}

    const unsigned int port = m_threadParams[portIndex].m_portIndex;

    OSWaitSemaphore(&m_accessSemaphores[port]);

    int result = 0;

    if ((int)m_cmdCount[port] < 0x40)
    {
        m_cmdQueueData[port][m_cmdCount[port]] = cmd;
        m_cmdCount[port]++;
    }
    else
    {
        result = -1;
    }

    OSSignalSemaphore(&m_accessSemaphores[port]);
	
    return result;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::DelItem(int portIndex, unsigned char itemId)
{
    unsigned int cmd = ((0x17u << 16) | (itemId << 8) | 0xFF) & 0xFF3FFFFF;

    if (m_threadRunningMask == 0)
    {
        return 0;
    }

    const unsigned int port = m_threadParams[portIndex].m_portIndex;

    OSWaitSemaphore(&m_accessSemaphores[port]);

    int result = 0;

    if ((int)m_cmdCount[port] < 0x40)
    {
        m_cmdQueueData[port][m_cmdCount[port]] = cmd;
        m_cmdCount[port]++;
    }
    else
    {
        result = -1;
    }

    OSSignalSemaphore(&m_accessSemaphores[port]);
    return result;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::SendMask(int, unsigned short)
{
	return 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::SetMoney(int portIndex, unsigned int money)
{
    int result = 0;
	
	// TODO: This 3E check feels like a < 40 check in shorts (ie size 20, cmp < 20). Might need to unfuck some of this.

    // Need room for *two* commands (this early check is against the caller's portIndex)
    if ((int)m_cmdCount[portIndex] >= 0x3E)
	{
        return -1;
    }
	
	{
		const unsigned char money_hi = (money >> 24) & 0xFF;
		const unsigned char money_mid = (money >> 16) & 0xFF;
		const unsigned int cmdHi = MakeJoyCmd16(0x1A00, money_hi, money_mid);

		if (m_threadRunningMask != 0)
		{
			unsigned int port = m_threadParams[portIndex].m_portIndex;

			OSWaitSemaphore(&m_accessSemaphores[port]);

			if ((int)m_cmdCount[port] < 0x40)
			{
				m_cmdQueueData[port][m_cmdCount[port]] = cmdHi;
				m_cmdCount[port]++;
				result = 0;
			}
			else
			{
				result = -1;
			}

			OSSignalSemaphore(&m_accessSemaphores[port]);
		}

		if (result != 0)
		{
			return result;
		}
	}
	
	{
		const unsigned char money_mid = (money >> 8) & 0xFF;
		const unsigned char money_lo =  money       & 0xFF;
		const unsigned short opcode = static_cast<unsigned short>(0x5A00 | money_mid);
		const unsigned int cmdLo = MakeJoyCmd16(opcode, money_lo, 0);

		if (m_threadRunningMask != 0)
		{
			unsigned int port = m_threadParams[portIndex].m_portIndex;

			OSWaitSemaphore(&m_accessSemaphores[port]);

			if ((int)m_cmdCount[port] < 0x40)
			{
				m_cmdQueueData[port][m_cmdCount[port]] = cmdLo;
				m_cmdCount[port]++;
				result = 0;
			} else {
				result = -1;
			}

			OSSignalSemaphore(&m_accessSemaphores[port]);
		}
	}

		return result;
}


/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::SetMType(int portIndex, int mtype)
{
    unsigned int state;

    OSWaitSemaphore(&m_accessSemaphores[portIndex]);
    state = m_threadParams[portIndex].m_state;
    OSSignalSemaphore(&m_accessSemaphores[portIndex]);

    if (state < 5)
	{
        return -1;
    }
	else if (state < 0x14 || state > 0x16)
	{
        if (state < 900)
		{
            return SendMType(&m_threadParams[portIndex], mtype);
        } else
		{
            return -1;
        }
    } else
	{
        return -1;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
char JoyBus::GetMType(int portIndex)
{
    OSWaitSemaphore(&m_accessSemaphores[portIndex]);
	
    unsigned char type = m_nextModeTypeArr[portIndex];
	
    OSSignalSemaphore(&m_accessSemaphores[portIndex]);
	
    return type;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
unsigned int JoyBus::GetPadType(int playerIndex)
{
    OSWaitSemaphore(&m_accessSemaphores[playerIndex]);
	
    unsigned int type = m_threadParams[playerIndex].m_padType;
	
    OSSignalSemaphore(&m_accessSemaphores[playerIndex]);
	
    return type;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::ExitThread()
{
	m_threadInitFlag = 1;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
bool JoyBus::IsThreadRunning()
{
    return m_threadRunningMask != 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::RestartThread()
{
    m_threadInitFlag = 0;
    // TODO: CreateInit__6JoyBusFv
    int err = 0;

    if (!Joybus.m_binLoaded)
    {
        CFile::CHandle* file = File.Open((char*)&Joybus, 0, CFile::PRI_LOW);

        if (file == 0)
        {
            if ((unsigned int)System.m_execParam > 1)
                System.Printf("Error: %s not found", (char*)&Joybus);

            err = -1;
        }
        else
        {
            File.Read(file);
            File.SyncCompleted(file);

            Joybus.m_gbaBootImageSize = File.GetLength(file);
            memcpy(Joybus.m_gbaBootImage, File.m_readBuffer, Joybus.m_gbaBootImageSize);

            File.Close(file);

            Joybus.m_diskId = (char*)File.GetCurrentDiskID();

            int idx = 0xBC;

            Joybus.m_gbaBootImage[0xAC] = Joybus.m_diskId[0];
            Joybus.m_gbaBootImage[0xAD] = Joybus.m_diskId[1];
            Joybus.m_gbaBootImage[0xAE] = Joybus.m_diskId[2];
            Joybus.m_gbaBootImage[0xAF] = Joybus.m_diskId[3];

            char* p = Joybus.m_gbaBootImage + 0xBC;
            int left = 1;

            unsigned char sum =
                (unsigned char)(
                    ((((((((((((((((((((((((((((-0x19
                    - Joybus.m_gbaBootImage[0xA0])
                    - Joybus.m_gbaBootImage[0xA1])
                    - Joybus.m_gbaBootImage[0xA2])
                    - Joybus.m_gbaBootImage[0xA3])
                    - Joybus.m_gbaBootImage[0xA4])
                    - Joybus.m_gbaBootImage[0xA5])
                    - Joybus.m_gbaBootImage[0xA6])
                    - Joybus.m_gbaBootImage[0xA7])
                    - Joybus.m_gbaBootImage[0xA8])
                    - Joybus.m_gbaBootImage[0xA9])
                    - Joybus.m_gbaBootImage[0xAA])
                    - Joybus.m_gbaBootImage[0xAB])
                    - Joybus.m_gbaBootImage[0xAC])
                    - Joybus.m_gbaBootImage[0xAD])
                    - Joybus.m_gbaBootImage[0xAE])
                    - Joybus.m_gbaBootImage[0xAF])
                    - Joybus.m_gbaBootImage[0xB0])
                    - Joybus.m_gbaBootImage[0xB1])
                    - Joybus.m_gbaBootImage[0xB2])
                    - Joybus.m_gbaBootImage[0xB3])
                    - Joybus.m_gbaBootImage[0xB4])
                    - Joybus.m_gbaBootImage[0xB5])
                    - Joybus.m_gbaBootImage[0xB6])
                    - Joybus.m_gbaBootImage[0xB7])
                    - Joybus.m_gbaBootImage[0xB8])
                    - Joybus.m_gbaBootImage[0xB9])
                    - Joybus.m_gbaBootImage[0xBA])
                    - Joybus.m_gbaBootImage[0xBB])
                );

            do
            {
                unsigned char v = *p++;
                idx++;
                sum -= v;
                left--;
            }
            while (left != 0);

            Joybus.m_gbaBootImage[idx] = sum;

            *(unsigned int*)(Joybus.m_gbaBootImage + 200) = OSGetTick();

            Joybus.m_binLoaded = 1;
        }
    }

    if (err != 0 && (unsigned int)System.m_execParam > 1)
	{
        System.Printf("JoyBus::LoadBin() error");
	}

    memset((void*)0x802F07D0, 0, 0xF0);

    Joybus.m_threadInitFlag = 0;
    Joybus.m_threadRunningMask = 0;

    JoyBus* jbA = &Joybus;
    JoyBus* jbB = &Joybus;

    for (int i = 0; i < 4; i++)
    {
        jbB->m_threadParams[i].m_portIndex = i;
        jbB->m_threadParams[i].m_gbaStatus = 1;
		
        unsigned char* stackBase = (unsigned char*)m_sendBuffer;

        OSCreateThread(
            &jbA->m_threads[i],
            (void* (*)(void*))JoyBus::_ThreadMain,
            &jbB->m_threadParams[i],
            stackBase,
            sizeof(jbA->m_sendBuffer[0]),
            8,
            1
        );

        OSResumeThread(&jbA->m_threads[0]);

        Joybus.m_threadRunningMask |= (unsigned char)(1 << i);

        jbA = (JoyBus*)(jbA->m_recvBuffer[0].m_payload + 0x290);
        jbB = (JoyBus*)(jbB->m_pathBuf + 0x3C);

    }

    if ((unsigned int)System.m_execParam > 1)
        System.Printf("JoyBus::ThreadInit end");
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::SetCmdLst(int portIndex, int param_3, short param_4)
{
    unsigned char argLo = static_cast<unsigned char>(param_4 & 0xFF);
    unsigned char argHi = static_cast<unsigned char>((param_4 >> 8) & 0xFF);
    unsigned short opcode = static_cast<unsigned short>(0x1F00 | (param_3 & 0xFF));
    unsigned int cmd = MakeJoyCmd16(opcode, argLo, argHi);

    if (m_threadRunningMask == 0)
	{
        return 0;
	}

    const unsigned int port = m_threadParams[portIndex].m_portIndex;

    OSWaitSemaphore(&m_accessSemaphores[port]);

    int result = 0;

    if ((int)m_cmdCount[port] < 0x40)
    {
        m_cmdQueueData[port][m_cmdCount[port]] = cmd;
        m_cmdCount[port]++;
    }
    else
    {
        result = -1;
    }

    OSSignalSemaphore(&m_accessSemaphores[port]);

    return result;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::SetTmpArti(int portIndex, int param3, int param4)
{
	// TODO: Decomp jank
    unsigned int cmd = (static_cast<unsigned char>('a' + param4) << 24);

    if (m_threadRunningMask == 0)
	{
        return 0;
    }

    unsigned int port = m_threadParams[portIndex].m_portIndex;

    OSWaitSemaphore(&m_accessSemaphores[port]);

	// TODO: Decomp jank
    if (static_cast<int>(m_cmdCount[port]) < 0x40)
	{
        m_cmdQueueData[port][m_cmdCount[port]] = cmd;
        m_cmdCount[port]++;

        OSSignalSemaphore(&m_accessSemaphores[port]);
        return 0;
    }
	else
	{
        OSSignalSemaphore(&m_accessSemaphores[port]);
        return -1;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::SendUseItem(int portIndex, char itemId)
{
    const unsigned short opcode = 0x140C;
    const unsigned int cmd = MakeJoyCmd16(opcode, static_cast<unsigned char>(itemId), 0);

    int result = 0;

    if (m_threadRunningMask != 0)
    {
        const unsigned int port = m_threadParams[portIndex].m_portIndex;

        OSWaitSemaphore(&m_accessSemaphores[port]);

        if ((int)m_cmdCount[port] < 0x40)
        {
            m_cmdQueueData[port][m_cmdCount[port]] = cmd;
			m_cmdCount[port]++;
        }
        else
        {
            result = -1;
        }

        OSSignalSemaphore(&m_accessSemaphores[port]);
    }

    return result;
}


/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::SendHitEnemy(int portIndex, char enemyId, short hitValue)
{
    unsigned int cmd = MakeJoyCmd32(0x22, enemyId, hitValue & 0xFF, hitValue >> 8);

    if (m_threadRunningMask == 0)
	{
        return 0;
	}

    const int port = m_threadParams[portIndex].m_portIndex;
    unsigned int result = 0;

    OSWaitSemaphore(&m_accessSemaphores[port]);

    if (static_cast<int>(m_cmdCount[port]) < 0x40)
    {
        m_cmdQueueData[port][m_cmdCount[port]] = cmd;
        m_cmdCount[port]++;
    }
    else
    {
        result = 0xFFFFFFFF;
    }

    OSSignalSemaphore(&m_accessSemaphores[port]);
    return result;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::SetOpenMenu(int playerIndex, char menuId)
{
	// TODO: restore when GbaQue exists
    if (playerIndex == 0 /* && IsSingleMode__8GbaQueueFi(&GbaQue, 0) */ && menuId != 0)
    {
        // MenuPcs._2148_2_ = menuId - 1; // TODO: restore when MenuPcs exists
        // Game.game.gameWork._5075_1_ = 1; // TODO: restore when Game exists
        m_ctrlModeArr[0] = 1;
		
        return 0;
    }
	// TODO: restore when GbaQue exists
    else if (playerIndex == 1 /* && IsSingleMode__8GbaQueueFi(&GbaQue, 1) */   && menuId == 0)
    {
        bool isSingle = GbaQue.IsSingleMode(m_threadParams[1].m_portIndex);

        if (!isSingle)
        {
            if (m_threadRunningMask == 0)
            {
                return 0;
            }

            unsigned int port = m_threadParams[1].m_portIndex;
            OSWaitSemaphore(&m_accessSemaphores[port]);

            int result = 0;
            if (static_cast<int>(m_cmdCount[port]) < 0x40)
            {
                const unsigned int cmd = MakeJoyCmd16(0x140F, 0, 0);
				
                m_cmdQueueData[port][m_cmdCount[port]] = cmd;
                m_cmdCount[port]++;
            }
            else
            {
                result = -1;
            }

            OSSignalSemaphore(&m_accessSemaphores[port]);
            return result;
        }

        return 0;
    }
    else
    {
        bool isSingle = GbaQue.IsSingleMode(m_threadParams[playerIndex].m_portIndex);
        
        if (!isSingle)
        {
            if (m_threadRunningMask == 0)
            {
                return 0;
            }

            unsigned int port = m_threadParams[playerIndex].m_portIndex;
			
            OSWaitSemaphore(&m_accessSemaphores[port]);

            int result = 0;
			
            if (static_cast<int>(m_cmdCount[port]) < 0x40)
            {
                const unsigned short opcode = static_cast<unsigned short>(0x140F);
				const unsigned int cmd = MakeJoyCmd16(opcode, static_cast<unsigned char>(menuId), 0);
			
                m_cmdQueueData[port][m_cmdCount[port]] = cmd;
                m_cmdCount[port]++;
            }
            else
            {
                result = -1;
            }

            OSSignalSemaphore(&m_accessSemaphores[port]);
            return result;
        }

        return 0;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void DEBPRINT(char*, ...)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x800b26d8
 * PAL Size: 80b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned short JoyBus::Crc16(int len, unsigned char* data, unsigned short* crc)
{
    unsigned int c;
    unsigned char b;
    unsigned int idx;
    unsigned int hi;

    goto check_len;

loop:
    c = *crc;
    b = *data;
    data = data + 1;
    idx = (unsigned int)((int)c >> 8);
    idx = (unsigned char)idx;
    idx = idx ^ (unsigned int)b;
    hi = c << 8;
    *crc = (unsigned short)(hi ^ JoyBusCrcTable[idx]);

check_len:
    len = len - 1;

    if (len >= 0)
    {
        goto loop;
    }

    return (unsigned short)~(*crc);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CFile::IsDiskError()
{
	return m_isDiskError;
}

/*
 * --INFO--
 * PAL Address: 0x800b2728
 * PAL Size: 456b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void __sinit_joybus_cpp()
{
    JoyBus* threadParamBase;
    JoyBus* cmdCountBase;
    JoyBus* semBase;
    JoyBus* stateBase;
    int i;

    Joybus.m_threadRunningMask = 0;
    Joybus.m_binLoaded = false;
    Joybus.m_fileBaseA_dup = 0;
    Joybus.m_fileBaseB_dup = 0;
    Joybus.m_gbaBootImage = 0;
    Joybus.m_fileBaseA = 0;
    Joybus.m_fileBaseB = 0;
    
    for (i = 0; i < 4; i++)
    {
        Joybus.m_letterBuffer[i] = 0;
        Joybus.m_letterSizeArr[i] = 0;
    }

    strcpy(Joybus.m_pathBuf, "dvd_gba/");
    strcat(Joybus.m_pathBuf, "ffcc_cli.bin", 128UL);

    memset((void*)0x802ec7d0, 0, 0x4000);
    memset((void*)0x802f08f0, 0, 8);
    memset((void*)0x802f08f8, 0, 0x400);
    memset((void*)0x802f0cf8, 0, 0x400);
    memset((void*)0x802f07d0, 0, 0xf0);
    memset((void*)0x802f1160, 0, 0x60);
    memset((void*)0x802eab40, 0, 0x1020);
    
    Joybus.m_mapId = 0xff;
    Joybus.m_stageId = 0xff;

    threadParamBase = &Joybus;
    cmdCountBase = &Joybus;
    semBase = &Joybus;
    stateBase = &Joybus;
    i = 0;
    do
    {
        threadParamBase->m_threadParams[0].m_gbaStatus = 1;
        threadParamBase->m_threadParams[0].m_padType = 0x40;
        cmdCountBase->m_cmdCount[0] = 0;
        cmdCountBase->m_secCmdCount[0] = 0;
        OSInitSemaphore(semBase->m_accessSemaphores, 1);
        stateBase->m_ctrlModeArr[0] = 0;
        i = i + 1;
        threadParamBase = reinterpret_cast<JoyBus*>(threadParamBase->m_pathBuf + 0x3c);
        stateBase->m_nextModeTypeArr[0] = 0;
        cmdCountBase = reinterpret_cast<JoyBus*>(cmdCountBase->m_pathBuf + 4);
        semBase = reinterpret_cast<JoyBus*>(semBase->m_pathBuf + 0xc);
        stateBase->m_modeXArr[0] = 0;
        stateBase->m_stateCodeArr[0] = 0xff;
        stateBase->m_stateFlagArr[0] = 0;
        stateBase = reinterpret_cast<JoyBus*>(stateBase->m_pathBuf + 1);
    } while (i < 4);

    __register_global_object(&Joybus, reinterpret_cast<void*>(__dt__6JoyBusFv), ARRAY_802eaab0);
}
