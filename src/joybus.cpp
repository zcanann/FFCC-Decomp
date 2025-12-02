#include "ffcc/joybus.h"

#include "ffcc/file.h"
#include "ffcc/system.h"

#include "dolphin/os.h"
#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/printf.h"

#include "string.h"

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

    if (m_gbaBootParamA == 0)
    {
        // TODO: __nwa__FUlPQ27CMemory6CStagePci
        m_gbaBootParamA = (unsigned int)__nwa(0x38000);

        if (m_gbaBootParamA == 0 && System.mExecParam != 0)
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

    if (!file && System.mExecParam > 1)
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

        if (m_fileBaseA == (unsigned int*)nullptr && System.mExecParam != 0)
        {
            System.Printf("%s(%d): Error: memory allocation", "joybus.cpp", 0x13A);
        }
    }

    memset((void*)m_fileBaseA, 0, len);
    memcpy((void*)m_fileBaseA, File.mReadBuffer, len);

    File.Close(file);

    if (m_fileBaseB == 0)
    {
        // TODO: __nwa__FUlPQ27CMemory6CStagePci
        m_fileBaseB = new unsigned int[0x5000];

        if (m_fileBaseB == 0 && System.mExecParam != 0)
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
            m_letterBuffer[i] = (unsigned int)__nwa(0x2800);

            if (m_letterBuffer[i] == 0 && System.mExecParam != 0)
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

    if (m_gbaBootParamA != 0)
    {
        // TODO: __dla__FPv
        // free((void*)m_gbaBootParamA);
        m_gbaBootParamA = 0;
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
        m_threadParams[i].m_padType   = 0x40;

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
void JoyBus::LoadBin()
{
	// TODO
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
    m_mapId   = (unsigned char)mapId;

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
        if ((unsigned int)System.mExecParam > 1)
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
    memcpy(&m_fileBaseB, File.mReadBuffer, m_fileBaseB_dup);
	
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
void JoyBus::ThreadMain(void *)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void* JoyBus::_ThreadMain(void* param)
{
	// TODO
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
            JoyBus::_ThreadMain,
            threadParam,
            stackBase,
            sizeof(m_sendBuffer[0]),
            8,
            1
        );

        OSResumeThread(thread);

        m_threadRunningMask |= (1 << i);
    }

    if ((unsigned int)System.mExecParam >= 2u)
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
 * Address:	TODO
 * Size:	TODO
 */
void ThreadAlarmHandler(OSAlarm *, OSContext *)
{
	// TODO
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
void JoyBus::GetPadData(int)
{
	// TODO
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

    // TODO: isSingle = IsSingleMode__8GbaQueueFi(&GbaQue, port);
    bool isSingle = (bool)this; // isSingle = IsSingleMode__8GbaQueueFi(&GbaQue, port);

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
    unsigned int count    = 0;

    OSWaitSemaphore(&m_accessSemaphores[port]);
    count = m_cmdCount[port];
	
    if (count > 0)
	{
        firstCmd = m_cmdQueueData[port][0];
	}
	
    OSSignalSemaphore(&m_accessSemaphores[port]);

    if (static_cast<int>(count) < 1)
	{
        return 0;
	}


	// TODO
    // bool isSingle = (IsSingleMode__8GbaQueueFi(&GbaQue, port) != 0);
    bool isSingle = (bool)this;

    if (!isSingle || port == 1)
    {
		// TODO: gba.c
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

    if (threadParam->m_unk3 & 0x02)
	{
		return 0;
	}

	// TODO: Gba.c
    int gbaResult = (int)this; // GBAWrite(port, &firstCmd, &threadParam->m_unk3);
	
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
void JoyBus::GBARecvSend(ThreadParam *, unsigned int *)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::ResetQueue(ThreadParam* threadParam)
{
	// TODO
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
void JoyBus::InitialCode(ThreadParam* threadParam)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::SetSendQueue(ThreadParam *, unsigned int)
{
	// TODO
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
    unsigned char p3     = static_cast<unsigned char>(param3);
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
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::SendMBase(ThreadParam* threadParam)
{
    const int port = threadParam->m_portIndex;

    // TODO
    // short posX, posY;
    // GetMBasePos__8GbaQueueFiPsPs(&GbaQue, port, &posX, &posY);
    short posX = (short)this;
    short posY = (short)this;
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

    // TODO restore:
    // unsigned char bufA[3];
    // unsigned char bufB[3];
    // GetStageNo(&GbaQue, port, bufA, bufB);
    // stageA = bufA[2];
    // stageB = bufB[2];
    unsigned char stageA = (unsigned char)this;
    unsigned char stageB = (unsigned char)this;

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
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::MakeJoyData(char *, int, unsigned int *)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::SendPlayerStat(ThreadParam* threadParam)
{
	// TODO
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

	// TODO
    // hpStatus = GetPlayerHP(&GbaQue, threadParam->m_portIndex, (unsigned char*)hpData);
    int hpStatus = (int)this;

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
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::SendMapObj(ThreadParam* threadParam)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::SendCompatibility(ThreadParam* threadParam)
{
	// TODO
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
	
	// TODO
    // bool isSingle = IsSingleMode__8GbaQueueFi(&GbaQue, port) != 0;
    bool isSingle = (bool)this;

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

    // TODO restore:
    // GetMapObjDrawFlg(&GbaQue, &flgByte);

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
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::SendFavorite(ThreadParam* threadParam)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::RequestData(ThreadParam *, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::SetRecvBuffer(ThreadParam *, unsigned int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::ClrRecvBuffer(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::GetRecvBuffer(int, unsigned char *)
{
	// TODO
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
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::SendCmd(ThreadParam* threadParam)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::SendBonusStr(ThreadParam* threadParam)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::SendArtifact(ThreadParam* threadParam)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::SendTmpArtifact(ThreadParam* threadParam)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::SendMapObjInfo(ThreadParam* threadParam)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::SendStrength(ThreadParam* threadParam)
{
    // Strength data returned as 3 bytes
    unsigned char strength0 = 0;
    unsigned char strength1 = 0;
    unsigned char strength2 = 0;

    // TODO: restore when GbaQue exists
    // GetStrengthData__8GbaQueueFiPUc(&GbaQue, threadParam->m_portIndex, &strength0);
    // strength1 = ... (filled by GbaQue)
    // strength2 = ...

    const unsigned short opcode = static_cast<unsigned short>(0x1900 | strength0);
    const unsigned int cmd = MakeJoyCmd16(opcode, strength1, strength2);

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

    // unsigned char radarType = GetRadarType__8GbaQueueFi(&GbaQue, port);
    unsigned char radarType = 0; // TODO restore when GbaQueue exists
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

    // unsigned char radarMode = GetRadarMode__8GbaQueueFi(&GbaQue, port);
    unsigned char radarMode = 0; // TODO restore when GbaQueue exists
    unsigned short opcode = 0x140D;
    unsigned int cmd = MakeJoyCmd16(opcode, radarMode, 0);

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
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::SendOpenMenu(ThreadParam* threadParam, char menuId)
{
    const int port = threadParam->m_portIndex;

    // Skip sending when in "single mode" (stubbed out for now)
    bool isSingle = (bool)this;
    // isSingle = IsSingleMode__8GbaQueueFi(&GbaQue, port);

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

    // TODO
    // isSingle = (IsSingleMode__8GbaQueueFi(&GbaQue, port) != 0);
    bool isSingle = (bool)this;

    if (isSingle)
    {
        return 0;
    }

    // TODO
    unsigned char itemId = (unsigned char)this;
    // itemId = GetItemUse__8GbaQueueFi(&GbaQue, port);

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
    // Fetch SP mode (commented out until GbaQueue exists)
    // unsigned int mode = GetSPMode__8GbaQueueFi(&GbaQue, threadParam->m_portIndex);
    unsigned int mode = (int)threadParam; // TODO: replace when GbaQueue is implemented

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

    // TODO
    // unsigned char value = GetMemorys__8GbaQueueFi(&GbaQue, port);
    unsigned char value = (unsigned char)this;
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

    // TODO
    // cmdNum = GetCmdNum__8GbaQueueFi(&GbaQue, port);
    unsigned char cmdNum = 0;
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
void JoyBus::GetGBAStat(ThreadParam* threadParam)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::ChgCtrlMode(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::SetCtrlMode(int portIndex, int controlMode)
{
    // TODO: restore when GbaQue exists
    bool isSingle = portIndex > 0;
    // isSingle = (IsSingleMode__8GbaQueueFi(&GbaQue, portIndex) != 0);

    if (isSingle)
	{
        return 0;
	}

    unsigned char modeFlag = (controlMode != 0) ? 1 : 0;

    // TODO: restore when GbaQue exists
    bool isSinglePort = portIndex > 0;
    // isSinglePort = (IsSingleMode__8GbaQueueFi(&GbaQue,
    //                    m_threadParams[portIndex].m_portIndex) != 0);

    if (isSinglePort)
	{
        modeFlag = 0;
	}

    const unsigned short opcode = 0x0900;
    const unsigned int cmd    = MakeJoyCmd16(opcode, modeFlag, 0);

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
void JoyBus::GetCtrlMode(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::GetGBAConnect(int)
{
	// TODO
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
void JoyBus::GetGBAStart(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::GBAReady(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::SendAllStat(int portIndex)
{
    ThreadParam& threadParam = m_threadParams[portIndex];
    const int port = threadParam.m_portIndex;

    threadParam.m_state = 0;
    threadParam.m_altState  = 0;

    OSWaitSemaphore(&m_accessSemaphores[port]);
	
	// TODO: The compiler is either somehow unrolling this, or our assumptions are wrong about recvQueue format
    for (int i = 0; i < 64; i++)
    {
        m_cmdQueueData[port][i] = 0;
        m_recvQueueEntriesArr[port][i] = 0;
    }

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
void JoyBus::GetLetterBuffer(int)
{
	// TODO
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
		const unsigned char money_hi  = (money >> 24) & 0xFF;
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
		const unsigned char money_lo  =  money       & 0xFF;
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
void JoyBus::GetMType(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::GetPadType(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::ExitThread()
{
	// TODO
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
	// TODO
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
    const unsigned int cmd    = MakeJoyCmd16(opcode, static_cast<unsigned char>(itemId), 0);

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
		// TODO: restore when GbaQue exists
        bool isSingle = false;
        // isSingle = (IsSingleMode__8GbaQueueFi(&GbaQue, m_threadParams[1].m_portIndex) != 0);

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
		// TODO: restore when GbaQue exists
        bool isSingle = false;
        // isSingle = (IsSingleMode__8GbaQueueFi(
        //                 &GbaQue,
        //                 m_threadParams[playerIndex].m_portIndex) != 0);

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
void DEBPRINT(char *, ...)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
unsigned short JoyBus::Crc16(int len, unsigned char* data, unsigned short* crc)
{
    while (len-- > 0)
    {
        unsigned short c = *crc;
        unsigned char b  = *data++;

        unsigned char idx = (unsigned char)((c >> 8) ^ b);
        unsigned short hi = (unsigned short)(c << 8);

        *crc = hi ^ JoyBusCrcTable[idx];
    }

    return (unsigned short)~(*crc);
}

