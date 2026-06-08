#include "ffcc/joybus.h"

#include "ffcc/file.h"
#include "ffcc/gbaque.h"
#include "ffcc/game.h"
#include "ffcc/p_menu.h"
#include "ffcc/p_gba.h"
#include "ffcc/memory.h"
#include "ffcc/system.h"
#include "global.h"

#include <dolphin/gba/GBA.h>
#include <dolphin/si.h>
#include "dolphin/os.h"
#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/printf.h"
#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/string.h"
#include <Runtime.PPCEABI.H/NMWException.h>

#include "string.h"

JoyBus Joybus;

int gJoyBusThreadExitValue = 0;

extern const unsigned short JoyBusCrcTable[256] =
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

static const char s_dvd_gba_dir[] = "dvd/gba/";
static const char s_ffcc_cli_bin[] = "ffcc_cli.bin";
static const char s_objdat_spt[] = "objdat.spt";
static const char s_joybus_cpp[] = "joybus.cpp";
static const char s_mem_alloc_error_fmt[] = "%s(%d): Error: memory allocation";
static const char s_not_found_error_fmt[] = "Error: %s not found";
static const char s_map_filename_fmt[] = "m%02d_%d.mcd";
static const char s_thread_init_end_nl[] = "JoyBus::ThreadInit end\n";
static const char s_recv_type_mismatch_warn_fmt[] = "(%d):%s(%d): Warning: Recv data type mismatch";
static const char s_send_ppos_bad_state_fmt[] = "JoyBus::SendPpos: bad state (port=%d, cnt=%d)\n";
static const char s_load_bin_error[] = "JoyBus::LoadBin() error";
static const char s_thread_init_end[] = "JoyBus::ThreadInit end";
extern char s_pctd_Error_send_type_error_pct02x_801DA350[];

extern const u32 kPppYmMeltMaskBit0;
extern const u32 kPppYmMeltMaskBit4;

namespace JoyBusConst {
static char* DVD_DIR = const_cast<char*>(s_dvd_gba_dir);
static char* CLIENT_FILE = const_cast<char*>(s_ffcc_cli_bin);
static char* OBJ_FILE = const_cast<char*>(s_objdat_spt);
const unsigned int CTRL_GBA = 0x10;
const unsigned int JOY_CODE_MASK = 0x1;
}

enum {
	kJoyDataPacketHeaderBytes = 2,
	kJoyDataPacketPayloadBytes = 0x400,
	kJoyDataLargePayloadClearBytes = 0x300,
	kJoyDataMapPayloadClearBytes = 0x200,
	kJoyDataSmallPayloadClearBytes = 0x100,
	kJoyDataFavoritePayloadClearBytes = 0x40,
};

STATIC_ASSERT(sizeof(ThreadParam) == 0x3C);
STATIC_ASSERT(sizeof(JoyBus::JoyBusRecvBuffer) == 0x408);

static inline void ClearJoyDataPacketPayload(JoyBus* joybus, int port)
{
	memset(joybus->m_joyDataPacketBuffer[port] + kJoyDataPacketHeaderBytes, 0, kJoyDataPacketPayloadBytes);
}

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
inline JoyBus::JoyBus()
{
    m_threadRunningMask = 0;
    m_binLoaded = false;
    m_fileBaseA_dup = 0;
    m_fileBaseB_dup = 0;
    m_gbaBootImage = 0;
    m_fileBaseA = 0;
    m_fileBaseB = 0;

    for (int i = 0; i < 4; i++)
    {
        m_letterBuffer[i] = 0;
        m_letterSizeArr[i] = 0;
    }

    strcpy(m_pathBuf, JoyBusConst::DVD_DIR);
    strcat(m_pathBuf, JoyBusConst::CLIENT_FILE);

    memset(m_sendBuffer, 0, sizeof(m_sendBuffer));
    memset(m_stageFlags, 0, sizeof(m_stageFlags));
    memset(m_cmdQueueData, 0, sizeof(m_cmdQueueData));
    memset(m_recvQueueEntriesArr, 0, sizeof(m_recvQueueEntriesArr));
    memset(m_threadParams, 0, sizeof(m_threadParams));
    memset(m_perThreadTemp, 0, sizeof(m_perThreadTemp));
    memset(m_recvBuffer, 0, sizeof(m_recvBuffer));

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
    memset(m_sendBuffer, 0, sizeof(m_sendBuffer));
    memset(m_stageFlags, 0, sizeof(m_stageFlags));
    memset(m_cmdQueueData, 0, sizeof(m_cmdQueueData));
    memset(m_recvQueueEntriesArr, 0, sizeof(m_recvQueueEntriesArr));
    memset(m_threadParams, 0, sizeof(m_threadParams));
    memset(m_perThreadTemp, 0, sizeof(m_perThreadTemp));
    memset(m_recvBuffer, 0, sizeof(m_recvBuffer));

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
        m_gbaBootImage = new (GbaPcs.m_stage, const_cast<char*>(s_joybus_cpp), 0x122) char[0x38000];

        if (m_gbaBootImage == 0 && (unsigned int)System.m_execParam >= 1)
        {
            System.Printf(const_cast<char*>(s_mem_alloc_error_fmt),
                const_cast<char*>(s_joybus_cpp), 0x126);
        }
    }

    char path[140];
    strcpy(path, JoyBusConst::DVD_DIR);

    strcat(path, JoyBusConst::OBJ_FILE);

    CFile::CHandle* file = File.Open(path, 0, CFile::PRI_LOW);

    if (!file && (unsigned int)System.m_execParam >= 2)
    {
        System.Printf(const_cast<char*>(s_not_found_error_fmt), path);
    }

    File.Read(file);
    File.SyncCompleted(file);

    unsigned int len = File.GetLength(file);
    m_fileBaseA_dup = len;

    if (m_fileBaseA == 0)
    {
        m_fileBaseA = reinterpret_cast<unsigned int*>(new (GbaPcs.m_stage, const_cast<char*>(s_joybus_cpp), 0x137) char[len + 0x20]);

        if (m_fileBaseA == (unsigned int*)nullptr && (unsigned int)System.m_execParam >= 1)
        {
            System.Printf(const_cast<char*>(s_mem_alloc_error_fmt), const_cast<char*>(s_joybus_cpp), 0x13A);
        }
    }

    memset((void*)m_fileBaseA, 0, len);
    memcpy((void*)m_fileBaseA, File.m_readBuffer, len);

    File.Close(file);

    if (m_fileBaseB == 0)
    {
        m_fileBaseB = reinterpret_cast<unsigned int*>(new (GbaPcs.m_stage, const_cast<char*>(s_joybus_cpp), 0x143) char[0x5000]);

        if (m_fileBaseB == 0 && (unsigned int)System.m_execParam >= 1)
        {
            System.Printf(const_cast<char*>(s_mem_alloc_error_fmt), const_cast<char*>(s_joybus_cpp), 0x146);
        }
    }

    m_fileBaseB_dup = 0;

    memset(m_cmdBuffer, 0, 8);

    for (int i = 0; i < 4; i++)
    {
        if (m_letterBuffer[i] == 0)
        {
            m_letterBuffer[i] = new (GbaPcs.m_stage, const_cast<char*>(s_joybus_cpp), 0x152) char[0x2800];

            if (m_letterBuffer[i] == 0 && (unsigned int)System.m_execParam >= 1)
            {
                System.Printf(const_cast<char*>(s_mem_alloc_error_fmt), const_cast<char*>(s_joybus_cpp), 0x155);
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

    while (static_cast<signed char>(Joybus.m_threadRunningMask) != 0)
    {
    }

    if (m_gbaBootImage != 0)
    {
        delete[] m_gbaBootImage;
        m_gbaBootImage = 0;
    }

    if (m_fileBaseA != 0)
    {
        delete[] m_fileBaseA;
        m_fileBaseA = 0;
    }

    if (m_fileBaseB != 0)
    {
        delete[] m_fileBaseB;
        m_fileBaseB = 0;
    }

    for (int i = 0; i < 4; i++)
    {
        if (m_letterBuffer[i] != 0)
        {
            delete[] m_letterBuffer[i];
            m_letterBuffer[i] = 0;
        }
    }

    memset(m_sendBuffer, 0, sizeof(m_sendBuffer));
    memset(m_stageFlags, 0, sizeof(m_stageFlags));
    memset(m_cmdQueueData, 0, sizeof(m_cmdQueueData));
    memset(m_recvQueueEntriesArr, 0, sizeof(m_recvQueueEntriesArr));
    memset(m_threadParams, 0, sizeof(m_threadParams));
    memset(m_perThreadTemp, 0, sizeof(m_perThreadTemp));
    memset(m_recvBuffer, 0, sizeof(m_recvBuffer));

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
    if (static_cast<signed char>(m_binLoaded) != 0)
    {
        return 0;
    }

    {
        CFile::CHandle* file = File.Open((char*)this, 0, CFile::PRI_LOW);

        if (file == 0)
        {
            if ((unsigned int)System.m_execParam >= 2)
            {
                System.Printf(const_cast<char*>(s_not_found_error_fmt), (char*)this);
            }

            return -1;
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

    return 0;
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

    char path[128];
    char tmp[16];

    strcpy(path, JoyBusConst::DVD_DIR);
    sprintf(tmp, const_cast<char*>(s_map_filename_fmt), stageId, mapId);
    strcat(path, tmp);

    CFile::CHandle* fileHandle = File.Open(path, 0, CFile::PRI_LOW);

    if (fileHandle == 0)
    {
        if ((unsigned int)System.m_execParam >= 2)
        {
            System.Printf(const_cast<char*>(s_not_found_error_fmt), path);
        }
        return -1;
    }

    File.Read(fileHandle);
    File.SyncCompleted(fileHandle);

    unsigned int len = File.GetLength(fileHandle);

    m_fileBaseB_dup = len;

    memset(m_fileBaseB, 0, 0x5000UL);
    memcpy(m_fileBaseB, File.m_readBuffer, m_fileBaseB_dup);

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

    unsigned int padType = 0;
    long long stateTimeoutTicks = 0;
    long long stateStartTime = 0;

    unsigned short localCrc[2];
    unsigned int localWord;
    unsigned int localCmd;
    unsigned char localBuf[4];

    threadParam->m_gbaStatus = GBAReset(threadParam->m_portIndex, &threadParam->m_unk3);

    ThreadSleep(OSMillisecondsToTicks(15));

recompute_timeout:
    switch ((unsigned int)threadParam->m_state)
    {
    case 4:
        stateTimeoutTicks = OSMillisecondsToTicks(500);
        break;
    case 5:
    case 900:
        stateTimeoutTicks = OSMillisecondsToTicks(500);
        break;
    case 2:
        stateTimeoutTicks = OSMillisecondsToTicks(2000);
        break;
    default:
        stateTimeoutTicks = OSMillisecondsToTicks(1000);
        break;
    }

    stateStartTime = OSGetTime();
    goto loop_body;

sleep_retry:
    ThreadSleep(OSMillisecondsToTicks(15));

loop_body:
    for (;;)
    {
        if (File.IsDiskError() != 0)
        {
            threadParam->m_state = (unsigned char)0x86;
            ResetQueue(threadParam);
            ClrRecvBuffer(threadParam->m_portIndex);
            goto sleep_retry;
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
                    memset(threadParam, 0, sizeof(*threadParam));
                    threadParam->m_portIndex = (int)idx;
                    break;
                }

                jb = (JoyBus*)(jb->m_pathBuf + 0x3c);
                idx++;
                left--;
            }
        }

        if (m_threadInitFlag != 0)
        {
            m_threadRunningMask = (unsigned char)(m_threadRunningMask & ~(unsigned char)(1 << threadParam->m_portIndex));
            m_stageFlags[threadParam->m_portIndex] = 0;
            OSExitThread(&gJoyBusThreadExitValue);
        }

        if (GbaQue.IsSingleMode(threadParam->m_portIndex) && threadParam->m_portIndex != 1)
        {
            threadParam->m_state = 0;
            stateStartTime = OSGetTime();
            goto sleep_retry;
        }

        padType = SIProbe(threadParam->m_portIndex);

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

        if (m_nextModeTypeArr[threadParam->m_portIndex] != m_modeXArr[threadParam->m_portIndex])
        {
            threadParam->m_state    = (unsigned char)0x14;
            threadParam->m_subState = 0;
            m_modeXArr[threadParam->m_portIndex]        = m_nextModeTypeArr[threadParam->m_portIndex];
        }

        unsigned int statusIndex;
        if (GbaQue.IsSingleMode(threadParam->m_portIndex) && threadParam->m_portIndex == 1)
        {
            statusIndex = 0;
        }
        else
        {
            statusIndex = (unsigned int)threadParam->m_portIndex;
        }

        unsigned int gamePadState = (int)Game.m_scriptFoodBase[statusIndex];

        if (gamePadState == 0 && padType != 0x00040000)
        {
            int s = (unsigned int)threadParam->m_state;

            if ((s >= 0x1D && s <= 0x20))
            {
                if (SendCancel(threadParam) < 0)
                {
                    goto sleep_retry;
                }
                threadParam->m_state = ';';
                goto timeout_expiry;
            }
            else if (s == 5 || (s >= 7 && s <= 0x13) || (s >= 0x17 && s <= 0x1C) ||
                     (s >= 0x21 && s <= 0x383) || s >= 0x387)
            {
                if (GBARecvSend(threadParam, reinterpret_cast<unsigned int*>(localBuf)) < 0)
                {
                    goto sleep_retry;
                }
                if (m_ctrlModeArr[threadParam->m_portIndex] == 0)
                {
                    goto recompute_timeout;
                }
                if (SendCtrlMode(threadParam, 0) < 0)
                {
                    goto sleep_retry;
                }
                goto recompute_timeout;
            }
        }
        else
        {
            if (gamePadState != 0 && padType == 0x00040000)
            {
                goto timeout_expiry;
            }

            m_ctrlModeArr[threadParam->m_portIndex] = 0;

            if (Game.m_scriptFoodBase[statusIndex] != 0)
            {
                if (threadParam->m_state == 2)
                {
                    threadParam->m_state = 1;
                }
                else
                {
                    threadParam->m_state = 0;
                }
            }
            else
            {
                threadParam->m_state = 0;
            }

            ThreadSleep(OSMillisecondsToTicks(15));
            goto recompute_timeout;
        }

timeout_expiry:
        {
            long long now = OSGetTime();
            long long elapsed = now - stateStartTime;

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

                goto recompute_timeout;
            }
        }

        if (threadParam->m_skipProcessingFlag != 0)
        {
            threadParam->m_skipProcessingFlag = 0;
        }

        unsigned int state = (unsigned int)threadParam->m_state;

        switch (state)
        {
        case 0x00:
        {
            threadParam->m_state = 1;

            GbaQue.SetChgUseItemFlg(threadParam->m_portIndex);
            GbaQue.SetResetFlg(threadParam->m_portIndex);

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

            m_ctrlModeArr[threadParam->m_portIndex] = 0;

            char controllerMode = GbaQue.GetControllerMode();

            if (controllerMode == 0)
                m_nextModeTypeArr[threadParam->m_portIndex] = 0;
            else
                m_nextModeTypeArr[threadParam->m_portIndex] = 4;

            ResetQueue(threadParam);

            threadParam->m_gbaStatus =
                GBAJoyBoot(threadParam->m_portIndex, threadParam->m_portIndex << 1, 2, reinterpret_cast<unsigned char*>(m_gbaBootImage), m_gbaBootImageSize,
                           &threadParam->m_unk3);

            if (threadParam->m_gbaStatus == 3 && (threadParam->m_unk3 & 0x10) != 0)
            {
                threadParam->m_flags[0] = 0;
                threadParam->m_state    = 4;
            }
            else if (threadParam->m_gbaStatus == 0)
            {
                char cm = GbaQue.GetControllerMode();

                if (cm == 0)
                    m_nextModeTypeArr[threadParam->m_portIndex] = 0;
                else
                    m_nextModeTypeArr[threadParam->m_portIndex] = 4;

                threadParam->m_state    = 2;
                threadParam->m_subState = 0;

                threadParam->m_timestamp = OSGetTick();

                ThreadSleep(OSMillisecondsToTicks(15));
                stateStartTime = OSGetTime();
            }
            else if (threadParam->m_gbaStatus == 3)
            {
                int stat = GetGBAStat(threadParam);
                if (stat == 0)
                {
                    threadParam->m_state    = 2;
                    threadParam->m_subState = 0;
                    ThreadSleep(OSMillisecondsToTicks(15));
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
            int result = InitialCode(threadParam);

            if (result == 1)
            {
                stateStartTime = OSGetTime();
            }
            else if (result == 2)
            {
                ThreadSleep(OSMillisecondsToTicks(15));
            }

            break;
        }

        case 0x03:
        {
            GbaQue.SetResetFlg(threadParam->m_portIndex);

            ResetQueue(threadParam);

            threadParam->m_gbaStatus = GBAReset(threadParam->m_portIndex, &threadParam->m_unk3);

            if (threadParam->m_gbaStatus == 0)
            {
                threadParam->m_state    = 2;
                threadParam->m_subState = 0;

                ThreadSleep(OSMillisecondsToTicks(15));
                stateStartTime = OSGetTime();
            }

            break;
        }

        case 0x04:
        {
            ResetQueue(threadParam);

            int bootRetry = 0;
            do
            {
                threadParam->m_gbaStatus =
                    GBAJoyBoot(threadParam->m_portIndex, threadParam->m_portIndex << 1, 2,
                               reinterpret_cast<unsigned char*>(m_gbaBootImage), m_gbaBootImageSize,
                               &threadParam->m_unk3);
                if (threadParam->m_gbaStatus == 1)
                {
                    break;
                }
                bootRetry++;
            } while (bootRetry < 100);

            if (threadParam->m_gbaStatus == 1)
            {
                threadParam->m_state = 0;
                ThreadSleep(OSMillisecondsToTicks(15));
                threadParam->m_errorRetry = 0;
                OSGetTime();
            }
            else
            {
                threadParam->m_state = (unsigned char)0x86;
                goto sleep_retry;
            }

            break;
        }

        case 0x05:
        {
            threadParam->m_errorRetry = 0;

            if (GBARecvSend(threadParam, reinterpret_cast<unsigned int*>(localBuf)) < 0)
            {
                goto sleep_retry;
            }
            if (threadParam->m_skipProcessingFlag != 0)
            {
                goto recompute_timeout;
            }
            if (threadParam->m_sentStartFlag == 0)
            {
                if (SendGBAStart(threadParam, &localWord) < 0)
                {
                    goto sleep_retry;
                }
            }

            if (GbaQue.GetPlayModeFlg(threadParam->m_portIndex))
            {
                threadParam->m_state = 2;
                goto recompute_timeout;
            }

            unsigned char spMode = (GbaQue.GetSPMode(threadParam->m_portIndex) & 0xFF) != 0;
            if (threadParam->m_flags[5] == 0 ||
                GbaQue.GetSPModeFlg(threadParam->m_portIndex) != 0 ||
                spMode != threadParam->m_flags[6])
            {
                if (SendSPMode(threadParam) < 0)
                {
                    goto sleep_retry;
                }
                threadParam->m_flags[5] = 1;
                GbaQue.ClrSPModeFlg(threadParam->m_portIndex);
            }

            if (threadParam->m_flags[4] != GbaQue.GetPauseMode())
            {
                char menuId = (char)((threadParam->m_flags[4] != 0) + 0xB);
                if (SendOpenMenu(threadParam, menuId) < 0)
                {
                    goto sleep_retry;
                }
                threadParam->m_flags[4] = (threadParam->m_flags[4] == 0);
            }

            if (GbaQue.GetControllerMode() != 0)
            {
                m_ctrlModeArr[threadParam->m_portIndex] = 4;
            }

            if (m_ctrlModeArr[threadParam->m_portIndex] == 4)
            {
                if (SendMType(threadParam, m_ctrlModeArr[threadParam->m_portIndex]) < 0)
                {
                    goto sleep_retry;
                }
                threadParam->m_state = 6;
                goto recompute_timeout;
            }

            if (GbaQue.GetStartBonusFlg(threadParam->m_portIndex))
            {
                if (SendStartBonus(threadParam) < 0)
                {
                    goto sleep_retry;
                }
                GbaQue.ClrStartBonusFlg(threadParam->m_portIndex);
            }

            int cmdNumFlg = GbaQue.GetCmdNumFlg(threadParam->m_portIndex);
            if (cmdNumFlg != 0)
            {
                if ((cmdNumFlg & 2) != 0)
                {
                    threadParam->m_state = 0x17;
                    goto recompute_timeout;
                }
                if (SendChgCmdNum(threadParam) < 0)
                {
                    goto sleep_retry;
                }
                GbaQue.ClrCmdNumFlg(threadParam->m_portIndex);
                goto recompute_timeout;
            }

            if (m_stateCodeArr[threadParam->m_portIndex] == 0xFF)
            {
                if (RequestData(threadParam, 0xE, 0) < 0)
                {
                    goto sleep_retry;
                }
            }

            if (System.GetCounter() % 3 == 0)
            {
                if (SendItemUse(threadParam) < 0)
                {
                    goto sleep_retry;
                }
            }

            char radarType = GbaQue.GetRadarType(threadParam->m_portIndex);
            if (GbaQue.GetStageFlg(threadParam->m_portIndex) == 0 && radarType == 2)
            {
                if (GbaQue.GetChgScouFlg(threadParam->m_portIndex) != 0 ||
                    (m_stateFlagArr[threadParam->m_portIndex] != 0 &&
                     m_stateCodeArr[threadParam->m_portIndex] == 0))
                {
                    threadParam->m_state = 0x49;
                    goto recompute_timeout;
                }

                if (GbaQue.GetChgHitFlg(threadParam->m_portIndex) != 0)
                {
                    unsigned int hitInfo = GbaQue.GetHitEInfo(threadParam->m_portIndex);
                    if (SendHitEnemy(threadParam->m_portIndex, (char)(unsigned short)(hitInfo >> 16),
                                     (short)hitInfo) < 0)
                    {
                        goto sleep_retry;
                    }
                    GbaQue.ClrChgHitFlg(threadParam->m_portIndex);
                }
            }

            if (m_stateCodeArr[threadParam->m_portIndex] == 2)
            {
                if (GbaQue.GetChgUseItemFlg(threadParam->m_portIndex))
                {
                    char useItem = (char)GbaQue.GetUseItemFlg(threadParam->m_portIndex);
                    if (SendUseItem(threadParam->m_portIndex, useItem) < 0)
                    {
                        goto sleep_retry;
                    }
                    GbaQue.ClrChgUseItemFlg(threadParam->m_portIndex);
                }
            }

            if (m_stateFlagArr[threadParam->m_portIndex] != 0 &&
                m_stateCodeArr[threadParam->m_portIndex] == 5)
            {
                threadParam->m_state = 0x43;
                goto recompute_timeout;
            }

            if (GbaQue.GetStrengthFlg(threadParam->m_portIndex))
            {
                if (SendStrength(threadParam) < 0)
                {
                    goto sleep_retry;
                }
                GbaQue.ClrStrengthFlg(threadParam->m_portIndex);
            }

            if (GbaQue.GetMemorysFlg(threadParam->m_portIndex))
            {
                if (SendMemorys(threadParam) < 0)
                {
                    goto sleep_retry;
                }
                GbaQue.ClrMemorysFlg(threadParam->m_portIndex);
            }

            if (GbaQue.GetChgRadarMode(threadParam->m_portIndex))
            {
                if (SendRaderMode(threadParam) < 0)
                {
                    goto sleep_retry;
                }
                GbaQue.ClrChgRadarMode(threadParam->m_portIndex);
            }

            if (SendPlayerHP(threadParam) < 0)
            {
                goto sleep_retry;
            }

            if (GbaQue.GetArtifactFlg(threadParam->m_portIndex))
            {
                threadParam->m_state = 0x3e;
                goto recompute_timeout;
            }

            if (GbaQue.GetStageFlg(threadParam->m_portIndex) != 0 && GbaQue.GetScrFlg() != 0)
            {
                ResetQueue(threadParam);
                threadParam->m_subState = 0;
                if (SendMapNo(threadParam) < 0)
                {
                    goto sleep_retry;
                }
                if (SendRaderType(threadParam) < 0)
                {
                    goto sleep_retry;
                }
                if (threadParam->m_gbaBootFlag == 0)
                {
                    if (SendMBase(threadParam) < 0)
                    {
                        goto sleep_retry;
                    }
                }
                GbaQue.ClrStageFlg(threadParam->m_portIndex);
                threadParam->m_state = 0x3b;
                goto recompute_timeout;
            }

            if (m_stateFlagArr[threadParam->m_portIndex] != 0 &&
                m_stateCodeArr[threadParam->m_portIndex] == 3)
            {
                threadParam->m_state = 0x32;
                goto recompute_timeout;
            }
            if (m_stateFlagArr[threadParam->m_portIndex] != 0 &&
                m_stateCodeArr[threadParam->m_portIndex] == 1)
            {
                threadParam->m_state = 0x4c;
                goto recompute_timeout;
            }
            if (m_stateCodeArr[threadParam->m_portIndex] == 0)
            {
                if (GbaQue.GetRadarType(threadParam->m_portIndex) == 0)
                {
                    if (System.GetCounter() % 5 == 0)
                    {
                        if (SendMapObjDrawFlg(threadParam) < 0)
                        {
                            goto sleep_retry;
                        }
                    }
                }
                if (System.GetCounter() % 3 == 0)
                {
                    if (SendMBase(threadParam) < 0)
                    {
                        goto sleep_retry;
                    }
                }
                if (SendPpos(threadParam) < 0)
                {
                    goto sleep_retry;
                }
            }

            if (m_stateCodeArr[threadParam->m_portIndex] == 7)
            {
                if (GbaQue.GetFavoriteFlg(threadParam->m_portIndex) != 0)
                {
                    threadParam->m_state = 0x2c;
                    goto recompute_timeout;
                }
            }

            if (GbaQue.GetMoneyFlg(threadParam->m_portIndex) == 1)
            {
                unsigned int money = GbaQue.GetMoney(threadParam->m_portIndex);
                if (SetMoney(threadParam->m_portIndex, money) == 0)
                {
                    GbaQue.ClrMoneyFlg(threadParam->m_portIndex);
                }
            }

            if (GbaQue.GetCompatibilityFlg(threadParam->m_portIndex) == 1 &&
                m_stateCodeArr[threadParam->m_portIndex] != 0)
            {
                threadParam->m_state = 0x2f;
            }

            break;
        }

        case 0x06:
        {
            threadParam->m_errorRetry = 0;

            if (GBARecvSend(threadParam, reinterpret_cast<unsigned int*>(localBuf)) < 0)
            {
                goto sleep_retry;
            }
            if (threadParam->m_skipProcessingFlag != 0)
            {
                goto recompute_timeout;
            }
            if (threadParam->m_sentStartFlag == 0)
            {
                if (SendGBAStart(threadParam, &localWord) < 0)
                {
                    goto sleep_retry;
                }
            }

            unsigned char spMode = (GbaQue.GetSPMode(threadParam->m_portIndex) & 0xFF) != 0;
            if (threadParam->m_flags[5] == 0 ||
                GbaQue.GetSPModeFlg(threadParam->m_portIndex) != 0 ||
                spMode != threadParam->m_flags[6])
            {
                if (SendSPMode(threadParam) < 0)
                {
                    goto sleep_retry;
                }
                threadParam->m_flags[5] = 1;
                GbaQue.ClrSPModeFlg(threadParam->m_portIndex);
            }

            if (threadParam->m_flags[4] != GbaQue.GetPauseMode())
            {
                char menuId = (char)((threadParam->m_flags[4] != 0) + 0xB);
                if (SendOpenMenu(threadParam, menuId) < 0)
                {
                    goto sleep_retry;
                }
                threadParam->m_flags[4] = (threadParam->m_flags[4] == 0);
            }

            if (m_nextModeTypeArr[threadParam->m_portIndex] == 0)
            {
                if (SendGBAStop(threadParam) < 0)
                {
                    goto sleep_retry;
                }
                threadParam->m_state = 0x14;
                goto recompute_timeout;
            }

            if (GbaQue.GetMoneyFlg(threadParam->m_portIndex) == 1)
            {
                unsigned int money = GbaQue.GetMoney(threadParam->m_portIndex);
                if (SetMoney(threadParam->m_portIndex, money) == 0)
                {
                    GbaQue.ClrMoneyFlg(threadParam->m_portIndex);
                }
            }

            break;
        }

        case 0x14:
        {
            int res = GBARecvSend(threadParam, reinterpret_cast<unsigned int*>(localBuf));
            if (res < 0 || threadParam->m_skipProcessingFlag != 0)
            {
                break;
            }

            threadParam->m_state = 0x15;

            localCrc[0] = 0xFFFF;
            unsigned short crcA = Crc16(m_fileBaseA_dup, reinterpret_cast<unsigned char*>(m_fileBaseA), localCrc);
            int chkA = SendChkCrc(threadParam, 0, crcA, &localWord);
            if (chkA != 0)
            {
                threadParam->m_altState = threadParam->m_state;
                threadParam->m_recvWriteIdx = localWord;
                threadParam->m_state = 0x84;
            }

            break;
        }

        case 0x15:
        {
            unsigned int res = GBARecvSend(threadParam, reinterpret_cast<unsigned int*>(localBuf));
            if ((int)res >= 0 && threadParam->m_skipProcessingFlag == 0 && (res & 1) != 0)
            {
                if ((localBuf[0] & 0x3F) == 7)
                {
                    threadParam->m_state = 0x16;
                    memset(m_perThreadTemp[threadParam->m_portIndex], 0, sizeof(m_perThreadTemp[threadParam->m_portIndex]));
                    m_perThreadTemp[threadParam->m_portIndex][0] = 0;
                    int cancelRes = SendCancel(threadParam);
                    if (cancelRes != 0)
                    {
                        threadParam->m_altState = threadParam->m_state;
                        threadParam->m_recvWriteIdx = localWord;
                        threadParam->m_state = 0x84;
                    }
                }
                else if (m_nextModeTypeArr[threadParam->m_portIndex] == 0)
                {
                    threadParam->m_state = ';';
                }
                else
                {
                    threadParam->m_state = 6;
                    int startRes = SendGBAStart(threadParam, &localWord);
                    if (startRes != 0)
                    {
                        threadParam->m_altState = threadParam->m_state;
                        threadParam->m_recvWriteIdx = localWord;
                        threadParam->m_state = 0x84;
                    }
                }

                DecRecvQueue(threadParam->m_portIndex);
            }

            break;
        }

        case 0x16:
        {
            int dataRes = SendDataFile(threadParam);
            if (dataRes == -2)
            {
                threadParam->m_state = 3;
            }
            if (threadParam->m_skipProcessingFlag == 0 && dataRes == 1)
            {
                if (m_nextModeTypeArr[threadParam->m_portIndex] == 0)
                {
                    threadParam->m_state = ';';
                }
                else
                {
                    threadParam->m_state = 6;
                    int startRes = SendGBAStart(threadParam, &localWord);
                    if (startRes != 0)
                    {
                        threadParam->m_altState = threadParam->m_state;
                        threadParam->m_recvWriteIdx = localWord;
                        threadParam->m_state = 0x84;
                    }
                }
            }

            break;
        }

        case 0x17:
        {
            m_stateFlagArr[threadParam->m_portIndex] = 0;
            int res = GBARecvSend(threadParam, reinterpret_cast<unsigned int*>(localBuf));
            if (res >= 0 && threadParam->m_skipProcessingFlag == 0 && GbaQue.GetScrFlg() != 0)
            {
                threadParam->m_subState = 0;
                int sendRes = SendItemAll(threadParam);
                if (sendRes == 0)
                {
                    threadParam->m_state = 0x18;
                }
            }

            break;
        }

        case 0x18:
        {
            unsigned int res = GBARecvSend(threadParam, reinterpret_cast<unsigned int*>(localBuf));
            if ((int)res > 0 && threadParam->m_skipProcessingFlag == 0 && (res & 2) != 0)
            {
                if ((res & 1) != 0 && (localBuf[0] & 0x3F) == 7)
                {
                    threadParam->m_state = 0x17;
                }
                else
                {
                    int sendRes = SendItemAll(threadParam);
                    if (sendRes >= 0 && sendRes == 1)
                    {
                        threadParam->m_state = 0x19;
                    }
                }
            }

            break;
        }

        case 0x19:
        {
            unsigned int res = GBARecvSend(threadParam, reinterpret_cast<unsigned int*>(localBuf));
            if ((int)res > 0 && threadParam->m_skipProcessingFlag == 0 && (res & 1) != 0)
            {
                if ((localBuf[0] & 0x3F) == 7)
                {
                    threadParam->m_state = 0x17;
                }
                else
                {
                    if (threadParam->m_gbaBootFlag == 0)
                    {
                        threadParam->m_state = 'F';
                    }
                    else
                    {
                        threadParam->m_state = 0x1D;
                    }
                    GbaQue.ClrArtifactFlg(threadParam->m_portIndex);
                    GbaQue.ClrCmdNumFlg(threadParam->m_portIndex);
                }

                int startRes = SendGBAStart(threadParam, &localWord);
                if (startRes != 0)
                {
                    threadParam->m_altState = threadParam->m_state;
                    threadParam->m_recvWriteIdx = localWord;
                    threadParam->m_state = 0x84;
                }
            }

            break;
        }

        case 0x1A:
        {
            int res = GBARecvSend(threadParam, reinterpret_cast<unsigned int*>(localBuf));
            if (res >= 0 && threadParam->m_skipProcessingFlag == 0 && GbaQue.GetScrFlg() != 0)
            {
                threadParam->m_subState = 0;
                int sendRes = SendPlayerStat(threadParam);
                if (sendRes >= 0)
                {
                    threadParam->m_state = 0x1B;
                }
            }

            break;
        }

        case 0x1B:
        {
            unsigned int res = GBARecvSend(threadParam, reinterpret_cast<unsigned int*>(localBuf));
            if ((int)res > 0 && threadParam->m_skipProcessingFlag == 0 && (res & 2) != 0)
            {
                if ((res & 1) != 0 && (localBuf[0] & 0x3F) == 7)
                {
                    threadParam->m_state = 0x1A;
                }
                else
                {
                    int sendRes = SendPlayerStat(threadParam);
                    if (sendRes >= 0 && sendRes == 1)
                    {
                        threadParam->m_state = 0x1C;
                    }
                }
            }

            break;
        }

        case 0x1C:
        {
            unsigned int res = GBARecvSend(threadParam, reinterpret_cast<unsigned int*>(localBuf));
            if ((int)res > 0 && threadParam->m_skipProcessingFlag == 0 && (res & 1) != 0)
            {
                if ((localBuf[0] & 0x3F) == 7)
                {
                    threadParam->m_state = 0x1A;
                }
                else
                {
                    threadParam->m_state = 0x17;
                    GbaQue.ClrFavoriteFlg(threadParam->m_portIndex);
                    GbaQue.ClrMoneyFlg(threadParam->m_portIndex);
                    GbaQue.ClrStrengthFlg(threadParam->m_portIndex);
                }
            }

            break;
        }

        case 0x1D:
        {
            int res = GBARecvSend(threadParam, reinterpret_cast<unsigned int*>(localBuf));

            if (res >= 0 && threadParam->m_skipProcessingFlag == 0)
            {
                int sendRes = SendMapNo(threadParam);
                if (sendRes >= 0)
                {
                    if (m_fileBaseB_dup == 0)
                    {
                        GbaQue.ClrStageFlg(threadParam->m_portIndex);
                        threadParam->m_state = 'F';
                    }
                    else
                    {
                        threadParam->m_state = 0x1E;
                        localCrc[0] = 0xFFFF;
                        unsigned short crcB = Crc16(m_fileBaseB_dup, reinterpret_cast<unsigned char*>(m_fileBaseB), localCrc);
                        int chkB = SendChkCrc(threadParam, 1, crcB, &localWord);
                        if (chkB != 0)
                        {
                            threadParam->m_altState = threadParam->m_state;
                            threadParam->m_recvWriteIdx = localWord;
                            threadParam->m_state = 0x84;
                        }
                    }
                }
            }

            break;
        }

        case 0x29:
        {
            int res = GBARecvSend(threadParam, reinterpret_cast<unsigned int*>(localBuf));
            if (res >= 0 && threadParam->m_skipProcessingFlag == 0 && GbaQue.GetScrFlg() != 0)
            {
                threadParam->m_subState = 0;
                int sendRes = SendMapObj(threadParam);
                if (sendRes >= 0)
                {
                    threadParam->m_state = '*';
                }
            }

            break;
        }

        case 0x2A:
        {
            unsigned int res = GBARecvSend(threadParam, reinterpret_cast<unsigned int*>(localBuf));
            if ((int)res > 0 && threadParam->m_skipProcessingFlag == 0 && (res & 2) != 0)
            {
                if ((res & 1) != 0 && (localBuf[0] & 0x3F) == 7)
                {
                    threadParam->m_state = ')';
                }
                else
                {
                    int sendRes = SendMapObj(threadParam);
                    if (sendRes >= 0 && sendRes == 1)
                    {
                        threadParam->m_state = '+';
                    }
                }
            }

            break;
        }

        case 0x2B:
        {
            unsigned int res = GBARecvSend(threadParam, reinterpret_cast<unsigned int*>(localBuf));
            if ((int)res > 0 && threadParam->m_skipProcessingFlag == 0 && (res & 1) != 0)
            {
                if ((localBuf[0] & 0x3F) == 7)
                {
                    threadParam->m_state = ')';
                }
                else
                {
                    threadParam->m_state = 5;
                }
            }

            break;
        }

        case 0x2C:
        {
            int res = GBARecvSend(threadParam, reinterpret_cast<unsigned int*>(localBuf));
            if (res >= 0 && threadParam->m_skipProcessingFlag == 0 && GbaQue.GetScrFlg() != 0)
            {
                threadParam->m_subState = 0;
                int sendRes = SendFavorite(threadParam);
                if (sendRes >= 0)
                {
                    threadParam->m_state = '-';
                }
            }

            break;
        }

        case 0x2D:
        {
            unsigned int res = GBARecvSend(threadParam, reinterpret_cast<unsigned int*>(localBuf));
            if ((int)res > 0 && threadParam->m_skipProcessingFlag == 0 && (res & 2) != 0)
            {
                if ((res & 1) != 0 && (localBuf[0] & 0x3F) == 7)
                {
                    threadParam->m_state = ',';
                }
                else
                {
                    int sendRes = SendFavorite(threadParam);
                    if (sendRes >= 0 && sendRes == 1)
                    {
                        threadParam->m_state = '.';
                    }
                }
            }

            break;
        }

        case 0x2E:
        {
            unsigned int res = GBARecvSend(threadParam, reinterpret_cast<unsigned int*>(localBuf));
            if ((int)res > 0 && threadParam->m_skipProcessingFlag == 0 && (res & 1) != 0)
            {
                if ((localBuf[0] & 0x3F) == 7)
                {
                    threadParam->m_state = ',';
                }
                else
                {
                    threadParam->m_state = 5;
                    GbaQue.ClrFavoriteFlg(threadParam->m_portIndex);
                }
            }

            break;
        }

        case 0x2F:
        {
            int res = GBARecvSend(threadParam, reinterpret_cast<unsigned int*>(localBuf));
            if (res >= 0 && threadParam->m_skipProcessingFlag == 0 && GbaQue.GetScrFlg() != 0)
            {
                threadParam->m_subState = 0;
                int sendRes = SendCompatibility(threadParam);
                if (sendRes >= 0)
                {
                    threadParam->m_state = '0';
                }
            }

            break;
        }

        case 0x30:
        {
            unsigned int res = GBARecvSend(threadParam, reinterpret_cast<unsigned int*>(localBuf));
            if ((int)res > 0 && threadParam->m_skipProcessingFlag == 0 && (res & 2) != 0)
            {
                if ((res & 1) != 0 && (localBuf[0] & 0x3F) == 7)
                {
                    threadParam->m_state = '/';
                }
                else
                {
                    int sendRes = SendCompatibility(threadParam);
                    if (sendRes >= 0 && sendRes == 1)
                    {
                        threadParam->m_state = '1';
                    }
                }
            }

            break;
        }

        case 0x31:
        {
            unsigned int res = GBARecvSend(threadParam, reinterpret_cast<unsigned int*>(localBuf));
            if ((int)res > 0 && threadParam->m_skipProcessingFlag == 0 && (res & 1) != 0)
            {
                if ((localBuf[0] & 0x3F) == 7)
                {
                    threadParam->m_state = '/';
                }
                else
                {
                    threadParam->m_state = 5;
                    GbaQue.ClrCompatibilityFlg(threadParam->m_portIndex);
                }
            }

            break;
        }

        case 0x32:
        {
            m_stateFlagArr[threadParam->m_portIndex] = 0;
            int res = GBARecvSend(threadParam, reinterpret_cast<unsigned int*>(localBuf));
            if (res >= 0 && threadParam->m_skipProcessingFlag == 0 && GbaQue.GetScrFlg() != 0)
            {
                threadParam->m_subState = 0;
                int sendRes = SendEquip(threadParam);
                if (sendRes >= 0)
                {
                    threadParam->m_state = '3';
                }
            }

            break;
        }

        case 0x33:
        {
            unsigned int res = GBARecvSend(threadParam, reinterpret_cast<unsigned int*>(localBuf));
            if ((int)res > 0 && threadParam->m_skipProcessingFlag == 0 && (res & 2) != 0)
            {
                if ((res & 1) != 0 && (localBuf[0] & 0x3F) == 7)
                {
                    threadParam->m_state = '2';
                }
                else
                {
                    int sendRes = SendEquip(threadParam);
                    if (sendRes >= 0 && sendRes == 1)
                    {
                        threadParam->m_state = '4';
                    }
                }
            }

            break;
        }

        case 0x34:
        {
            unsigned int res = GBARecvSend(threadParam, reinterpret_cast<unsigned int*>(localBuf));
            if ((int)res > 0 && threadParam->m_skipProcessingFlag == 0 && (res & 1) != 0)
            {
                if ((localBuf[0] & 0x3F) == 7)
                {
                    threadParam->m_state = '2';
                }
                else
                {
                    threadParam->m_state = 5;
                }
            }

            break;
        }

        case 0x35:
        {
            int res = GBARecvSend(threadParam, reinterpret_cast<unsigned int*>(localBuf));
            if (res >= 0 && threadParam->m_skipProcessingFlag == 0 && GbaQue.GetSellFlg(threadParam->m_portIndex) != 0)
            {
                threadParam->m_state = '6';
                memset(m_perThreadTemp[threadParam->m_portIndex], 0, sizeof(m_perThreadTemp[threadParam->m_portIndex]));
                m_perThreadTemp[threadParam->m_portIndex][0] = 6;
                int cancelRes = SendCancel(threadParam);
                if (cancelRes != 0)
                {
                    threadParam->m_altState = threadParam->m_state;
                    threadParam->m_recvWriteIdx = localWord;
                    threadParam->m_state = 0x84;
                }
            }

            break;
        }

        case 0x36:
        {
            int dataRes = SendDataFile(threadParam);
            if (dataRes == -2)
            {
                threadParam->m_state = 3;
            }
            if (threadParam->m_skipProcessingFlag == 0 && dataRes == 1)
            {
                threadParam->m_state = 6;
            }

            break;
        }

        case 0x37:
        {
            int res = GBARecvSend(threadParam, reinterpret_cast<unsigned int*>(localBuf));
            if (res >= 0 && threadParam->m_skipProcessingFlag == 0 && GbaQue.GetBuyFlg(threadParam->m_portIndex) != 0)
            {
                threadParam->m_state = '8';
                memset(m_perThreadTemp[threadParam->m_portIndex], 0, sizeof(m_perThreadTemp[threadParam->m_portIndex]));
                m_perThreadTemp[threadParam->m_portIndex][0] = 7;
                int cancelRes = SendCancel(threadParam);
                if (cancelRes != 0)
                {
                    threadParam->m_altState = threadParam->m_state;
                    threadParam->m_recvWriteIdx = localWord;
                    threadParam->m_state = 0x84;
                }
            }

            break;
        }

        case 0x38:
        {
            int dataRes = SendDataFile(threadParam);
            if (dataRes == -2)
            {
                threadParam->m_state = 3;
            }
            if (threadParam->m_skipProcessingFlag == 0 && dataRes == 1)
            {
                threadParam->m_state = 6;
            }

            break;
        }

        case 0x39:
        {
            int res = GBARecvSend(threadParam, reinterpret_cast<unsigned int*>(localBuf));
            if (res >= 0 && threadParam->m_skipProcessingFlag == 0 && GbaQue.GetMkSmithFlg(threadParam->m_portIndex) != 0)
            {
                threadParam->m_state = ':';
                memset(m_perThreadTemp[threadParam->m_portIndex], 0, sizeof(m_perThreadTemp[threadParam->m_portIndex]));
                m_perThreadTemp[threadParam->m_portIndex][0] = 8;
                int cancelRes = SendCancel(threadParam);
                if (cancelRes != 0)
                {
                    threadParam->m_altState = threadParam->m_state;
                    threadParam->m_recvWriteIdx = localWord;
                    threadParam->m_state = 0x84;
                }
            }

            break;
        }

        case 0x3A:
        {
            int dataRes = SendDataFile(threadParam);
            if (dataRes == -2)
            {
                threadParam->m_state = 3;
            }
            if (threadParam->m_skipProcessingFlag == 0 && dataRes == 1)
            {
                threadParam->m_state = 6;
                ThreadSleep(OSMillisecondsToTicks(1));
                stateStartTime = OSGetTime();
            }

            break;
        }

        case 0x3B:
        {
            int res = GBARecvSend(threadParam, reinterpret_cast<unsigned int*>(localBuf));
            if (res >= 0)
            {
                int stopRes = SendGBAStop(threadParam);
                if (stopRes >= 0 && threadParam->m_skipProcessingFlag == 0 && GbaQue.GetScrFlg() != 0)
                {
                    threadParam->m_subState = 0;
                    int sendRes = SendBonusStr(threadParam);
                    if (sendRes >= 0)
                    {
                        threadParam->m_state = '<';
                    }
                }
            }

            break;
        }

        case 0x3C:
        {
            unsigned int res = GBARecvSend(threadParam, reinterpret_cast<unsigned int*>(localBuf));
            if ((int)res > 0 && threadParam->m_skipProcessingFlag == 0 && (res & 2) != 0)
            {
                if ((res & 1) != 0 && (localBuf[0] & 0x3F) == 7)
                {
                    threadParam->m_state = ';';
                }
                else
                {
                    int sendRes = SendBonusStr(threadParam);
                    if (sendRes >= 0 && sendRes == 1)
                    {
                        threadParam->m_state = '=';
                    }
                }
            }

            break;
        }

        case 0x3D:
        {
            unsigned int res = GBARecvSend(threadParam, reinterpret_cast<unsigned int*>(localBuf));
            if ((int)res > 0 && threadParam->m_skipProcessingFlag == 0 && (res & 1) != 0)
            {
                if ((localBuf[0] & 0x3F) == 7)
                {
                    threadParam->m_state = ';';
                }
                else
                {
                    threadParam->m_state = 0x1A;
                }
            }

            break;
        }

        case 0x3E:
        {
            m_stateFlagArr[threadParam->m_portIndex] = 0;
            int res = GBARecvSend(threadParam, reinterpret_cast<unsigned int*>(localBuf));
            if (res >= 0 && threadParam->m_skipProcessingFlag == 0 && GbaQue.GetScrFlg() != 0)
            {
                threadParam->m_subState = 0;
                int sendRes = SendArtifact(threadParam);
                if (sendRes >= 0)
                {
                    threadParam->m_state = '?';
                }
            }

            break;
        }

        case 0x3F:
        {
            unsigned int res = GBARecvSend(threadParam, reinterpret_cast<unsigned int*>(localBuf));
            if ((int)res > 0 && threadParam->m_skipProcessingFlag == 0 && (res & 2) != 0)
            {
                if ((res & 1) != 0 && (localBuf[0] & 0x3F) == 7)
                {
                    threadParam->m_state = '>';
                }
                else
                {
                    int sendRes = SendArtifact(threadParam);
                    if (sendRes >= 0 && sendRes == 1)
                    {
                        threadParam->m_state = '@';
                    }
                }
            }

            break;
        }

        case 0x40:
        {
            unsigned int res = GBARecvSend(threadParam, reinterpret_cast<unsigned int*>(localBuf));
            if ((int)res > 0 && threadParam->m_skipProcessingFlag == 0 && (res & 1) != 0)
            {
                if ((localBuf[0] & 0x3F) == 7)
                {
                    threadParam->m_state = '>';
                }
                else
                {
                    GbaQue.ClrArtifactFlg(threadParam->m_portIndex);
                    threadParam->m_state = 5;
                }
            }

            break;
        }

        case 0x41:
        {
            int res = GBARecvSend(threadParam, reinterpret_cast<unsigned int*>(localBuf));
            if (res >= 0 && threadParam->m_skipProcessingFlag == 0 && GbaQue.GetArtiDatFlg(threadParam->m_portIndex) != 0)
            {
                threadParam->m_state = 'B';
                memset(m_perThreadTemp[threadParam->m_portIndex], 0, sizeof(m_perThreadTemp[threadParam->m_portIndex]));
                m_perThreadTemp[threadParam->m_portIndex][0] = 9;
                int cancelRes = SendCancel(threadParam);
                if (cancelRes != 0)
                {
                    threadParam->m_altState = threadParam->m_state;
                    threadParam->m_recvWriteIdx = localWord;
                    threadParam->m_state = 0x84;
                }
            }

            break;
        }

        case 0x42:
        {
            int dataRes = SendDataFile(threadParam);
            if (dataRes == -2)
            {
                threadParam->m_state = 3;
            }
            if (threadParam->m_skipProcessingFlag == 0 && dataRes == 1)
            {
                GbaQue.ClrArtiDatFlg(threadParam->m_portIndex);
                threadParam->m_state = 5;
            }

            break;
        }

        case 0x43:
        {
            m_stateFlagArr[threadParam->m_portIndex] = 0;
            int res = GBARecvSend(threadParam, reinterpret_cast<unsigned int*>(localBuf));
            if (res >= 0 && threadParam->m_skipProcessingFlag == 0 && GbaQue.GetScrFlg() != 0)
            {
                threadParam->m_subState = 0;
                int sendRes = SendTmpArtifact(threadParam);
                if (sendRes >= 0)
                {
                    threadParam->m_state = 'D';
                }
            }

            break;
        }

        case 0x44:
        {
            unsigned int res = GBARecvSend(threadParam, reinterpret_cast<unsigned int*>(localBuf));
            if ((int)res > 0 && threadParam->m_skipProcessingFlag == 0 && (res & 2) != 0)
            {
                if ((res & 1) != 0 && (localBuf[0] & 0x3F) == 7)
                {
                    threadParam->m_state = 'C';
                }
                else
                {
                    int sendRes = SendTmpArtifact(threadParam);
                    if (sendRes >= 0 && sendRes == 1)
                    {
                        threadParam->m_state = 'E';
                    }
                }
            }

            break;
        }

        case 0x45:
        {
            unsigned int res = GBARecvSend(threadParam, reinterpret_cast<unsigned int*>(localBuf));
            if ((int)res > 0 && threadParam->m_skipProcessingFlag == 0 && (res & 1) != 0)
            {
                if ((localBuf[0] & 0x3F) == 7)
                {
                    threadParam->m_state = 'C';
                }
                else
                {
                    GbaQue.ClrArtifactFlg(threadParam->m_portIndex);
                    threadParam->m_state = 5;
                }
            }

            break;
        }

        case 0x46:
        {
            m_stateFlagArr[threadParam->m_portIndex] = 0;
            int res = GBARecvSend(threadParam, reinterpret_cast<unsigned int*>(localBuf));
            if (res >= 0 && threadParam->m_skipProcessingFlag == 0 && GbaQue.GetScrFlg() != 0)
            {
                int typeRes = SendRaderType(threadParam);
                if (typeRes >= 0)
                {
                    int modeRes = SendRaderMode(threadParam);
                    if (modeRes >= 0)
                    {
                        threadParam->m_subState = 0;
                        int sendRes = SendMapObjInfo(threadParam);
                        if (sendRes >= 0)
                        {
                            threadParam->m_state = 'G';
                        }
                    }
                }
            }

            break;
        }

        case 0x47:
        {
            unsigned int res = GBARecvSend(threadParam, reinterpret_cast<unsigned int*>(localBuf));
            if ((int)res > 0 && threadParam->m_skipProcessingFlag == 0 && (res & 2) != 0)
            {
                if ((res & 1) != 0 && (localBuf[0] & 0x3F) == 7)
                {
                    threadParam->m_state = 'F';
                }
                else
                {
                    int sendRes = SendMapObjInfo(threadParam);
                    if (sendRes >= 0 && sendRes == 1)
                    {
                        threadParam->m_state = 'H';
                    }
                }
            }

            break;
        }

        case 0x48:
        {
            unsigned int res = GBARecvSend(threadParam, reinterpret_cast<unsigned int*>(localBuf));
            if ((int)res > 0 && threadParam->m_skipProcessingFlag == 0 && (res & 1) != 0)
            {
                if ((localBuf[0] & 0x3F) == 7)
                {
                    threadParam->m_state = 'F';
                }
                else
                {
                    threadParam->m_state = ')';
                }
            }

            break;
        }

        case 0x49:
        {
            m_stateFlagArr[threadParam->m_portIndex] = 0;
            int res = GBARecvSend(threadParam, reinterpret_cast<unsigned int*>(localBuf));
            if (res >= 0 && threadParam->m_skipProcessingFlag == 0 && GbaQue.GetScrFlg() != 0)
            {
                ResetQueue(threadParam);
                threadParam->m_subState = 0;
                int sendRes = SendScouInfo(threadParam);
                if (sendRes >= 0)
                {
                    threadParam->m_state = 'J';
                }
            }

            break;
        }

        case 0x4A:
        {
            unsigned int res = GBARecvSend(threadParam, reinterpret_cast<unsigned int*>(localBuf));
            if ((int)res > 0 && threadParam->m_skipProcessingFlag == 0 && (res & 2) != 0)
            {
                if ((res & 1) != 0 && (localBuf[0] & 0x3F) == 7)
                {
                    threadParam->m_state = 'I';
                }
                else
                {
                    int sendRes = SendScouInfo(threadParam);
                    if (sendRes >= 0 && sendRes == 1)
                    {
                        threadParam->m_state = 'K';
                    }
                }
            }

            break;
        }

        case 0x4B:
        {
            unsigned int res = GBARecvSend(threadParam, reinterpret_cast<unsigned int*>(localBuf));
            if ((int)res > 0 && threadParam->m_skipProcessingFlag == 0 && (res & 1) != 0)
            {
                if ((localBuf[0] & 0x3F) == 7)
                {
                    threadParam->m_state = 'I';
                }
                else
                {
                    GbaQue.ClrChgScouFlg(threadParam->m_portIndex);
                    threadParam->m_state = 5;
                }
            }

            break;
        }

        case 0x4C:
        {
            m_stateFlagArr[threadParam->m_portIndex] = 0;
            int res = GBARecvSend(threadParam, reinterpret_cast<unsigned int*>(localBuf));
            if (res >= 0 && threadParam->m_skipProcessingFlag == 0 && GbaQue.GetScrFlg() != 0)
            {
                threadParam->m_subState = 0;
                int sendRes = SendCmd(threadParam);
                if (sendRes >= 0)
                {
                    threadParam->m_state = 'M';
                }
            }

            break;
        }

        case 0x4D:
        {
            unsigned int res = GBARecvSend(threadParam, reinterpret_cast<unsigned int*>(localBuf));
            if ((int)res > 0 && threadParam->m_skipProcessingFlag == 0 && (res & 2) != 0)
            {
                if ((res & 1) != 0 && (localBuf[0] & 0x3F) == 7)
                {
                    threadParam->m_state = 'L';
                }
                else
                {
                    int sendRes = SendCmd(threadParam);
                    if (sendRes >= 0 && sendRes == 1)
                    {
                        threadParam->m_state = 'N';
                    }
                }
            }

            break;
        }

        case 0x4E:
        {
            unsigned int r = GBARecvSend(threadParam, reinterpret_cast<unsigned int*>(localBuf));

            if ((int)r > 0 && threadParam->m_skipProcessingFlag == 0 && (r & 1) != 0)
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
            int res = GBARecvSend(threadParam, reinterpret_cast<unsigned int*>(localBuf));

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

        goto recompute_timeout;
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

    for (int i = 0; i < 4; i++)
    {
        m_threadParams[i].m_portIndex = i;
        m_threadParams[i].m_gbaStatus = 1;

        unsigned char* stackBase = m_sendBuffer[i] + sizeof(m_sendBuffer[0]);

        OSCreateThread(
            &m_threads[i],
            (void* (*)(void*))JoyBus::_ThreadMain,
            &m_threadParams[i],
            stackBase,
            sizeof(m_sendBuffer[0]),
            8,
            1
        );

        OSResumeThread(&m_threads[i]);

        m_threadRunningMask |= (1 << i);
    }

    if ((unsigned int)System.m_execParam >= 2u)
    {
        System.Printf(const_cast<char*>(s_thread_init_end_nl));
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

struct ThreadSleepAlarm {
    OSAlarm alarm;
    OSThread* thread;
};

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
    OSResumeThread(((ThreadSleepAlarm*)alarm)->thread);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::ThreadSleep(long long ticks)
{
    ThreadSleepAlarm alarm;

    OSCreateAlarm(&alarm.alarm);
    OSSetAlarmTag(&alarm.alarm, 1);

    alarm.thread = OSGetCurrentThread();
    unsigned int level = OSDisableInterrupts();

    OSSetAlarm(&alarm.alarm, ticks, ThreadAlarmHandler);
    OSSuspendThread(alarm.thread);
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
    unsigned char bytes[2];
    bytes[1] = data[1];
    bytes[0] = data[2];
    unsigned short combined = *reinterpret_cast<unsigned short*>(bytes);

    if (combined & 0x0001) flags |= 0x0100;
    if (combined & 0x0002) flags |= 0x0200;
    if (combined & 0x0008) flags |= 0x1000;
    if (combined & 0x0010) flags |= 0x0002;
    if (combined & 0x0020) flags |= 0x0001;
    if (combined & 0x0040) flags |= 0x0008;
    if (combined & 0x0080) flags |= 0x0004;

    unsigned char state = threadParam->m_state;

    if ((((state != 0x05) && (state != 0x21)) && (state != 0x22)) &&
        ((state != 0x23 && (state != 0x24))))
    {
        if (m_stageId != 0x21)
        {
            goto skipStartFlag;
        }
    }

    if (combined & 0x0004)
    {
        flags |= 0x0010;
    }

skipStartFlag:

    if (combined & 0x0100) flags |= 0x0020;
    if (combined & 0x0200) flags |= 0x0040;

    OSWaitSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);
    m_stageFlags[threadParam->m_portIndex] = flags;
    OSSignalSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
unsigned short JoyBus::GetPadData(int portIndex)
{
    OSWaitSemaphore(&m_accessSemaphores[portIndex]);

    unsigned short value = m_stageFlags[portIndex];

    m_stageFlags[portIndex] = 0;

    if ((signed char)m_threadInitFlag != 0) {
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
    unsigned int secCount;

    *recvBuffer = 0;

    OSWaitSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);
    secCount = m_secCmdCount[threadParam->m_portIndex];
    OSSignalSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);

    if ((int)secCount >= 0x40)
    {
        return 0;
    }

    bool isSingle = GbaQue.IsSingleMode(threadParam->m_portIndex);

    if (isSingle && (int)threadParam->m_portIndex != 1)
    {
        threadParam->m_gbaStatus = 0;
    }
    else
    {
        threadParam->m_gbaStatus = GBAGetStatus(threadParam->m_portIndex, &threadParam->m_unk3);
    }

    if ((int)threadParam->m_gbaStatus != 0)
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

    unsigned int data;

    threadParam->m_gbaStatus = GBARead(threadParam->m_portIndex, (unsigned char*)&data, &threadParam->m_unk3);

    if ((int)threadParam->m_gbaStatus != 0)
    {
        return -1;
    }

    *recvBuffer = data;

    unsigned char* dataBytes = reinterpret_cast<unsigned char*>(&data);
    unsigned char op = dataBytes[0] & 0x3F;

    if ((int)op == 4)
    {
        SetPadData(threadParam, (unsigned char*)&data);
        return 1;
    }
    else if ((int)op == 0x0E)
    {
        unsigned char b1 = dataBytes[1];

        if (b1 == 0)
        {
            m_stateCodeArr[threadParam->m_portIndex] = dataBytes[2];
            m_stateFlagArr[threadParam->m_portIndex] = 1;
            return 1;
        }
        else
        {
            OSWaitSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);
            m_recvQueueEntriesArr[threadParam->m_portIndex][ m_secCmdCount[threadParam->m_portIndex] ] = data;
            m_secCmdCount[threadParam->m_portIndex]++;
            OSSignalSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);
            return 2;
        }
    }

    OSWaitSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);
    m_recvQueueEntriesArr[threadParam->m_portIndex][ m_secCmdCount[threadParam->m_portIndex] ] = data;
    m_secCmdCount[threadParam->m_portIndex]++;
    OSSignalSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);

    return 2;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::SendGBA(ThreadParam* threadParam)
{
    unsigned int firstCmd;
    unsigned int count;

    OSWaitSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);
    count = m_cmdCount[threadParam->m_portIndex];
    firstCmd = m_cmdQueueData[threadParam->m_portIndex][0];
    OSSignalSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);

    if (static_cast<int>(count) <= 0)
	{
        return 0;
	}

    bool isSingle = GbaQue.IsSingleMode(threadParam->m_portIndex);

    if (isSingle != 0 && (int)threadParam->m_portIndex != 1)
    {
        threadParam->m_gbaStatus = 0;
    }
    else
    {
        threadParam->m_gbaStatus = GBAGetStatus(threadParam->m_portIndex, &threadParam->m_unk3);
    }

    if ((int)threadParam->m_gbaStatus != 0)
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

    int gbaResult = GBAWrite(threadParam->m_portIndex, (unsigned char*)&firstCmd, &threadParam->m_unk3);

    threadParam->m_gbaStatus = gbaResult;

    if ((int)threadParam->m_gbaStatus != 0)
	{
        return -1;
	}

    unsigned char* cmdBytes = reinterpret_cast<unsigned char*>(&firstCmd);

    if (m_stateCodeArr[threadParam->m_portIndex] == 0x09 && (cmdBytes[0] & 0x3F) == 0x09 && cmdBytes[1] == 0x01)
    {
        threadParam->m_state = '!';
        threadParam->m_subState = 0;
        threadParam->m_skipProcessingFlag = 1;
    }

    OSWaitSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);

    for (int i = 1; i < (int)m_cmdCount[threadParam->m_portIndex]; ++i)
	{
        m_cmdQueueData[threadParam->m_portIndex][i - 1] = m_cmdQueueData[threadParam->m_portIndex][i];
	}

    m_cmdCount[threadParam->m_portIndex]--;

    OSSignalSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);

    return 1;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::GBARecvSend(ThreadParam* threadParam, unsigned int* cmdOut)
{

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
        int op = cmdBytes[0] & 0x3F;

        if (op == 0x14 || op == 0x17 || op == 0x1A ||
            op == 0x1C || op == 0x1D || op == 0x1E ||
            op == 0x1F || (op == 0x06 && cmdBytes[1] == 0x18))
        {
            OSWaitSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);

            unsigned int prevCmd = m_recvQueueEntriesArr[threadParam->m_portIndex][m_secCmdCount[threadParam->m_portIndex] - 1];
            m_secCmdCount[threadParam->m_portIndex]--;

            OSSignalSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);

            GbaQue.SetQueue(threadParam->m_portIndex, prevCmd);

            recvResult = 0;
            *cmdOut = 0;
        }
        else if (op == 0x0C)
        {
            OSWaitSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);

            unsigned int prevCmd = m_recvQueueEntriesArr[threadParam->m_portIndex][m_secCmdCount[threadParam->m_portIndex] - 1];
            m_secCmdCount[threadParam->m_portIndex]--;

            OSSignalSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);

            unsigned char sub = cmdBytes[1];

            if (sub == 0x03)
            {
                GbaQue.ClrLetterLstFlg(threadParam->m_portIndex);
                GbaQue.SetQueue(threadParam->m_portIndex, prevCmd);

                threadParam->m_state = '!';
                threadParam->m_subState = 0;
                threadParam->m_skipProcessingFlag = 1;
            }
            else if (sub == 0x02)
            {
                GbaQue.ClrLetterDatFlg(threadParam->m_portIndex);
                GbaQue.SetQueue(threadParam->m_portIndex, prevCmd);

                threadParam->m_state = '%';
                threadParam->m_subState = 0;
                threadParam->m_skipProcessingFlag = 1;
            }
            else if (sub == 0x06)
            {
                GbaQue.ClrSellFlg(threadParam->m_portIndex);
                GbaQue.SetQueue(threadParam->m_portIndex, prevCmd);

                threadParam->m_state = '5';
                threadParam->m_subState = 0;
                threadParam->m_skipProcessingFlag = 1;
            }
            else if (sub == 0x07)
            {
                GbaQue.ClrBuyFlg(threadParam->m_portIndex);
                GbaQue.SetQueue(threadParam->m_portIndex, prevCmd);

                threadParam->m_state = '7';
                threadParam->m_subState = 0;
                threadParam->m_skipProcessingFlag = 1;
            }
            else if (sub == 0x08)
            {
                GbaQue.ClrMkSmithFlg(threadParam->m_portIndex);
                GbaQue.SetQueue(threadParam->m_portIndex, prevCmd);

                threadParam->m_state = '9';
                threadParam->m_subState = 0;
                threadParam->m_skipProcessingFlag = 1;
            }
            else if (sub == 0x09)
            {
                GbaQue.ClrArtiDatFlg(threadParam->m_portIndex);
                GbaQue.SetQueue(threadParam->m_portIndex, prevCmd);

                threadParam->m_state = 'A';
                threadParam->m_subState = 0;
                threadParam->m_skipProcessingFlag = 1;
            }
        }
        else if (op == 0x15)
        {
            OSWaitSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);

            unsigned int prevCmd = m_recvQueueEntriesArr[threadParam->m_portIndex][m_secCmdCount[threadParam->m_portIndex] - 1];
            m_secCmdCount[threadParam->m_portIndex]--;

            OSSignalSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);

            unsigned char header = cmdBytes[0];

            if ((header >> 6) == 0)
            {
                OSWaitSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);
                memset(&m_recvBuffer[threadParam->m_portIndex], 0, sizeof(m_recvBuffer[threadParam->m_portIndex]));
                OSSignalSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);
            }

            unsigned int word = *cmdOut;
            JoyBusRecvBuffer& buf = m_recvBuffer[threadParam->m_portIndex];

            if (buf.m_cmdFlags != 0)
            {
                unsigned char cmdId = static_cast<unsigned char>(word >> 24);

                if (buf.m_cmdFlags != (cmdId & 0x3F))
                {
                    if (static_cast<unsigned int>(System.m_execParam) >= 2u)
                    {
                        System.Printf(const_cast<char*>(s_recv_type_mismatch_warn_fmt), threadParam->m_portIndex, const_cast<char*>(s_joybus_cpp), 0x1079);
                    }

                    OSWaitSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);
                    memset(&m_recvBuffer[threadParam->m_portIndex], 0, sizeof(m_recvBuffer[threadParam->m_portIndex]));
                    OSSignalSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);
                }
            }

            OSWaitSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);

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

            OSSignalSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);

            if ((header >> 6) == 2)
            {
                unsigned short crc = 0xFFFF;
                unsigned int len = buf.m_length;
                unsigned char* data = buf.m_payload;

                while (len-- > 0)
                {
                    unsigned char b = *data++;
                    unsigned char idxC = static_cast<signed char>(((crc >> 8) ^ b));
                    crc = static_cast<unsigned short>((crc << 8) ^ JoyBusCrcTable[idxC]);
                }

                if (static_cast<short>(~crc) == buf.m_crc)
                {
                    GbaQue.SetQueue(threadParam->m_portIndex, prevCmd);
                }
                else
                {
                    if (m_threadRunningMask != 0)
                    {
                        const unsigned int tPort = m_threadParams[threadParam->m_portIndex].m_portIndex;
                        OSWaitSemaphore(&m_accessSemaphores[tPort]);

                        if (static_cast<int>(m_cmdCount[tPort]) >= 0x40)
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

                    OSWaitSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);
                    memset(&m_recvBuffer[threadParam->m_portIndex], 0, sizeof(m_recvBuffer[threadParam->m_portIndex]));
                    OSSignalSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);
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
            OSWaitSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);

            unsigned int newCount = 0;

            for (int i = 0; i < (int)m_cmdCount[threadParam->m_portIndex]; ++i)
            {
                unsigned int cmd = m_cmdQueueData[threadParam->m_portIndex][i];
                unsigned char op = static_cast<unsigned char>(cmd >> 24) & 0x3F;

                if (op == 0x0A || op == 0x10 || op == 0x14 ||
                    op == 0x1B || op == 0x13 || op == 0x09)
                {
                    m_recvQueueEntriesArr[threadParam->m_portIndex][newCount++] = cmd;
                }
            }

            for (int i = 0; i < 0x20; ++i)
            {
                if (i < newCount)
                {
                    m_cmdQueueData[threadParam->m_portIndex][i] = m_recvQueueEntriesArr[threadParam->m_portIndex][i];
                }
                else
                {
                    m_cmdQueueData[threadParam->m_portIndex][i] = 0;
                }

                m_recvQueueEntriesArr[threadParam->m_portIndex][i] = 0;
            }

            m_secCmdCount[threadParam->m_portIndex] = 0;
            m_cmdCount[threadParam->m_portIndex] = newCount;

            OSSignalSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);
        }

        const int state = threadParam->m_state;

        if (m_stateFlagArr[threadParam->m_portIndex] != 0 &&
            m_stateCodeArr[threadParam->m_portIndex] != 0x09 &&
            state != 0x05 &&
            state > 0x20 && state < 0x29)
        {
            OSWaitSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);

            unsigned int newCount = 0;

            for (unsigned int i = 0; i < m_cmdCount[threadParam->m_portIndex]; ++i)
            {
                int cmd = m_cmdQueueData[threadParam->m_portIndex][i];
                unsigned char op = static_cast<signed char>(cmd >> 24) & 0x3F;

                if (op == 0x0A || op == 0x10 || op == 0x14 ||
                    op == 0x1B || op == 0x13 || op == 0x09)
                {
                    m_recvQueueEntriesArr[threadParam->m_portIndex][newCount++] = cmd;
                }
            }

            for (int i = 0; i < 0x20; ++i)
            {
                if (i < newCount)
                {
                    m_cmdQueueData[threadParam->m_portIndex][i] = m_recvQueueEntriesArr[threadParam->m_portIndex][i];
                }
                else
                {
                    m_cmdQueueData[threadParam->m_portIndex][i] = 0;
                }

                m_recvQueueEntriesArr[threadParam->m_portIndex][i] = 0;
            }

            m_secCmdCount[threadParam->m_portIndex] = 0;
            m_cmdCount[threadParam->m_portIndex] = newCount;

            OSSignalSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);

            threadParam->m_state = 0x05;
            threadParam->m_subState = 0;
            threadParam->m_skipProcessingFlag = 1;
        }
    }

    unsigned int recvBit = static_cast<unsigned int>(__cntlzw(2 - recvResult)) >> 5;
    unsigned int sendBit = ((-sendResult | sendResult) >> 31) & 2u;

    return static_cast<int>(recvBit | sendBit);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::ResetQueue(ThreadParam* threadParam)
{
    OSWaitSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);

    for (int index = 0; index < 8; index++)
	{
		int base = index * 8;

        m_cmdQueueData[threadParam->m_portIndex][base] = 0;
        m_recvQueueEntriesArr[threadParam->m_portIndex][base] = 0;

        m_cmdQueueData[threadParam->m_portIndex][base + 1] = 0;
        m_recvQueueEntriesArr[threadParam->m_portIndex][base + 1] = 0;

        m_cmdQueueData[threadParam->m_portIndex][base + 2] = 0;
        m_recvQueueEntriesArr[threadParam->m_portIndex][base + 2] = 0;

        m_cmdQueueData[threadParam->m_portIndex][base + 3] = 0;
        m_recvQueueEntriesArr[threadParam->m_portIndex][base + 3] = 0;

        m_cmdQueueData[threadParam->m_portIndex][base + 4] = 0;
        m_recvQueueEntriesArr[threadParam->m_portIndex][base + 4] = 0;

        m_cmdQueueData[threadParam->m_portIndex][base + 5] = 0;
        m_recvQueueEntriesArr[threadParam->m_portIndex][base + 5] = 0;

        m_cmdQueueData[threadParam->m_portIndex][base + 6] = 0;
        m_recvQueueEntriesArr[threadParam->m_portIndex][base + 6] = 0;

        m_cmdQueueData[threadParam->m_portIndex][base + 7] = 0;
        m_recvQueueEntriesArr[threadParam->m_portIndex][base + 7] = 0;
    }

    m_cmdCount[threadParam->m_portIndex] = 0;
    m_secCmdCount[threadParam->m_portIndex] = 0;

    OSSignalSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);
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
    int result = 0;

    switch ((unsigned char)threadParam->m_subState)
    {
    case 0:
    {
        // Clear per-threadParam->m_portIndex state
        m_stateFlagArr[threadParam->m_portIndex] = 0;

        ResetQueue(threadParam);

        // Get initial GBA status
        bool singleMode = GbaQue.IsSingleMode(threadParam->m_portIndex);

        if (singleMode && (int)threadParam->m_portIndex != 1)
        {
            threadParam->m_gbaStatus = 0;
        }
        else
        {
            threadParam->m_gbaStatus = GBAGetStatus(threadParam->m_portIndex, &threadParam->m_unk3);
        }

        if ((int)threadParam->m_gbaStatus == 0 && threadParam->m_unk3 == 0x28)
        {
            unsigned int readBuf[4];

            threadParam->m_gbaStatus = GBARead(threadParam->m_portIndex, reinterpret_cast<unsigned char*>(readBuf), &threadParam->m_unk3);

            if ((int)threadParam->m_gbaStatus == 0)
            {
                threadParam->m_recvReadIdx = readBuf[0];

                *reinterpret_cast<unsigned int*>(&threadParam->m_deviceType) = 1;
            }
        }

        threadParam->m_subState = 1;
        result = 0;
        break;
    }

    case 1:
    {
        bool singleMode = GbaQue.IsSingleMode(threadParam->m_portIndex);

        if (singleMode && (int)threadParam->m_portIndex != 1)
        {
            threadParam->m_gbaStatus = 0;
        }
        else
        {
            threadParam->m_gbaStatus = GBAGetStatus(threadParam->m_portIndex, &threadParam->m_unk3);
        }

        int status = threadParam->m_gbaStatus;

        if (status == 0)
        {
            if (threadParam->m_unk3 == ' ')
            {
                threadParam->m_gbaStatus = GBAWrite(threadParam->m_portIndex, reinterpret_cast<unsigned char*>(m_diskId), &threadParam->m_unk3);
                status = threadParam->m_gbaStatus;

                if (status == 0)
                {
                    bool singleMode2 = GbaQue.IsSingleMode(threadParam->m_portIndex);

                    if (singleMode2 && (int)threadParam->m_portIndex != 1)
                    {
                        threadParam->m_gbaStatus = 0;
                    }
                    else
                    {
                        threadParam->m_gbaStatus = GBAGetStatus(threadParam->m_portIndex, &threadParam->m_unk3);
                    }

                    status = threadParam->m_gbaStatus;

                    if (status == 0)
                    {
                        if ((threadParam->m_unk3 & 0x30) != 0x20)
                            status = 1;
                        else
                            status = 0;
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
        bool singleMode = GbaQue.IsSingleMode(threadParam->m_portIndex);

        if (singleMode && (int)threadParam->m_portIndex != 1)
        {
            threadParam->m_gbaStatus = 0;
        }
        else
        {
            threadParam->m_gbaStatus = GBAGetStatus(threadParam->m_portIndex, &threadParam->m_unk3);
        }

        int status = threadParam->m_gbaStatus;

        if (status == 0)
        {
            if (threadParam->m_unk3 == 0x28)
            {
                char header;
                unsigned char flags = 0; // will land in local_1f

                // GBARead fills header + flag byte (and maybe more); we only care about these two.
                struct
                {
                    char          h;
                    unsigned char f;
                } tmpBuf;

                threadParam->m_gbaStatus = GBARead(threadParam->m_portIndex, reinterpret_cast<unsigned char*>(&tmpBuf), &threadParam->m_unk3);
                status = threadParam->m_gbaStatus;

                if (status == 0)
                {
                    header = tmpBuf.h;

                    if (header == 1)
                    {
                        status = 0;

                        threadParam->m_gbaBootFlag    = (unsigned char)((int)(signed char)tmpBuf.f >> 6);
                        threadParam->m_unk2           = (unsigned char)((tmpBuf.f >> 4) & 0x03);
                        threadParam->m_bootRetryCount = (unsigned char)(tmpBuf.f & 0x0F);
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
        bool singleMode = GbaQue.IsSingleMode(threadParam->m_portIndex);

        if (singleMode && (int)threadParam->m_portIndex != 1)
        {
            threadParam->m_gbaStatus = 0;
        }
        else
        {
            threadParam->m_gbaStatus = GBAGetStatus(threadParam->m_portIndex, &threadParam->m_unk3);
        }

        int status = threadParam->m_gbaStatus;

        if (status == 0)
        {
            if (threadParam->m_unk3 == 0x28)
            {
                unsigned int timeValue;
                threadParam->m_gbaStatus = GBARead(threadParam->m_portIndex, reinterpret_cast<unsigned char*>(&timeValue), &threadParam->m_unk3);
                status = threadParam->m_gbaStatus;

                if (status == 0)
                {
                    // Bit-twiddly inequality check preserved from decomp
                    unsigned int a = timeValue - threadParam->m_timestamp;
                    unsigned int b = threadParam->m_timestamp - timeValue;

                    threadParam->m_timeChangedFlag = (unsigned char)((a | b) >> 31);
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
        bool singleMode = GbaQue.IsSingleMode(threadParam->m_portIndex);

        if (singleMode && (int)threadParam->m_portIndex != 1)
        {
            threadParam->m_gbaStatus = 0;
        }
        else
        {
            threadParam->m_gbaStatus = GBAGetStatus(threadParam->m_portIndex, &threadParam->m_unk3);
        }

        int status = threadParam->m_gbaStatus;

        if (status == 0)
        {
            if (threadParam->m_unk3 == ' ')
            {
                if (threadParam->m_timeChangedFlag != 0 ||
                    (threadParam->m_gbaBootFlag == 0 && threadParam->m_timestamp == 0))
                {
                    threadParam->m_timestamp = OSGetTick();
                }

                threadParam->m_gbaStatus = GBAWrite(threadParam->m_portIndex, reinterpret_cast<unsigned char*>(&threadParam->m_timestamp), &threadParam->m_unk3);

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
        bool singleMode = GbaQue.IsSingleMode(threadParam->m_portIndex);

        if (singleMode && (int)threadParam->m_portIndex != 1)
        {
            threadParam->m_gbaStatus = 0;
        }
        else
        {
            threadParam->m_gbaStatus = GBAGetStatus(threadParam->m_portIndex, &threadParam->m_unk3);
        }

        int status = threadParam->m_gbaStatus;

        if (status == 0)
        {
            if (threadParam->m_unk3 == ' ')
            {
                bool singleMode2 = GbaQue.IsSingleMode(threadParam->m_portIndex);

                unsigned char portVal = singleMode2 ? 0 : (unsigned char)threadParam->m_portIndex;
                unsigned char header = 1;
                signed char flags = (unsigned char)(portVal | (threadParam->m_gbaBootFlag << 6) | (threadParam->m_unk2 << 4));
                unsigned int word = (1u << 24) | ((unsigned int)flags << 16);

                threadParam->m_gbaStatus = GBAWrite(threadParam->m_portIndex, reinterpret_cast<unsigned char*>(&word), &threadParam->m_unk3);
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
        int err = SendMType(threadParam, (int)m_nextModeTypeArr[threadParam->m_portIndex]);
        if (err < 0)
        {
            result = 1;
            break;
        }

        int stageMajor;
        int stageMinor;

        GbaQue.GetStageNo(threadParam->m_portIndex, &stageMajor, &stageMinor);

        unsigned int cmdStage = MakeJoyCmd32(0x0E, 1, ((unsigned char*)&stageMajor)[3], ((unsigned char*)&stageMinor)[3]);
        int stageResult = 0;

        if (static_cast<signed char>(m_threadRunningMask) == 0)
        {
            stageResult = 0;
        }
        else
        {
            OSWaitSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);

            unsigned int qPort = threadParam->m_portIndex;
            if ((int)m_cmdCount[qPort] >= 0x40)
            {
                OSSignalSemaphore(&m_accessSemaphores[qPort]);
                stageResult = 0xFFFFFFFF;
            }
            else
            {
                m_cmdQueueData[qPort][m_cmdCount[qPort]] = cmdStage;
                m_cmdCount[threadParam->m_portIndex]++;

                OSSignalSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);
                stageResult = 0;
            }
        }

        if (((-stageResult | stageResult) >> 31) != 0)
        {
            result = 1;
            break;
        }

        unsigned char gameFlags =
            (unsigned char)((Game.m_gameWork.m_languageId - 1) | kPppYmMeltMaskBit4);
        unsigned int cmdGame = MakeJoyCmd32(0x14, 0x16, gameFlags, 0);

        if (static_cast<signed char>(m_threadRunningMask) == 0)
        {
            err = 0;
        }
        else
        {
            OSWaitSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);

            if ((int)m_cmdCount[threadParam->m_portIndex] >= 0x40)
            {
                OSSignalSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);
                err = -1;
            }
            else
            {
                m_cmdQueueData[threadParam->m_portIndex][m_cmdCount[threadParam->m_portIndex]] = cmdGame;
                m_cmdCount[threadParam->m_portIndex]++;

                OSSignalSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);
                err = 0;
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

        GbaQue.ClrPlayModeFlg(threadParam->m_portIndex);

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
    if (static_cast<signed char>(m_threadRunningMask) == 0)
    {
        return 0;
    }

    OSWaitSemaphore(m_accessSemaphores + threadParam->m_portIndex);

    int result = 0;
    unsigned int port = threadParam->m_portIndex;
    if ((int)m_cmdCount[port] >= 0x40)
    {
        OSSignalSemaphore(m_accessSemaphores + port);
        result = -1;
    }
    else
    {
        m_cmdQueueData[port][m_cmdCount[port]] = command;
        m_cmdCount[threadParam->m_portIndex]++;

        OSSignalSemaphore(m_accessSemaphores + threadParam->m_portIndex);
        result = 0;
    }

    return result;
}


/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::SendGBAStart(ThreadParam* threadParam, unsigned int* outCmd)
{
    unsigned int cmd = 0;
    unsigned char* cmdBytes = reinterpret_cast<unsigned char*>(&cmd);
    cmdBytes[0] = 0x0A;
    cmdBytes[1] = 1;

    *outCmd = cmd;
    unsigned int word = cmd;

    int result = 0;

    if (static_cast<signed char>(m_threadRunningMask) != 0)
    {
        OSWaitSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);

        unsigned int queuePort = threadParam->m_portIndex;
        if (static_cast<int>(m_cmdCount[queuePort]) >= 0x40)
        {
            OSSignalSemaphore(&m_accessSemaphores[queuePort]);
            result = 0xFFFFFFFF;
        }
        else
        {
            m_cmdQueueData[queuePort][m_cmdCount[queuePort]] = word;
            m_cmdCount[threadParam->m_portIndex]++;
            OSSignalSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);
            result = 0;
        }
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
    unsigned int cmd = 0;
    unsigned char* cmdBytes = reinterpret_cast<unsigned char*>(&cmd);
    cmdBytes[0] = 0x0A;
    cmdBytes[1] = 0;
    unsigned int word = cmd;

    int result = 0;

    if (static_cast<signed char>(m_threadRunningMask) != 0)
    {
        OSWaitSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);

        unsigned int queuePort = threadParam->m_portIndex;
        if ((int)m_cmdCount[queuePort] >= 0x40)
        {
            OSSignalSemaphore(&m_accessSemaphores[queuePort]);
            result = -1;
        }
        else
        {
            m_cmdQueueData[queuePort][m_cmdCount[queuePort]] = word;
            m_cmdCount[threadParam->m_portIndex]++;
            OSSignalSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);
            result = 0;
        }
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
    unsigned int cmd = 0;
    unsigned char* cmdBytes = reinterpret_cast<unsigned char*>(&cmd);
    unsigned short crcValue = crc;

    cmdBytes[0] = 0x0D;
    cmdBytes[1] = static_cast<unsigned char>(param3);
    *reinterpret_cast<unsigned short*>(cmdBytes + 2) = __lhbrx(&crcValue, 0);

    *outCmd = cmd;
    unsigned int word = cmd;

    unsigned int result = 0;

    if (static_cast<signed char>(m_threadRunningMask) == 0)
    {
        return result;
    }

    OSWaitSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);

    unsigned int queuePort = threadParam->m_portIndex;
    if (static_cast<int>(m_cmdCount[queuePort]) >= 0x40)
    {
        OSSignalSemaphore(&m_accessSemaphores[queuePort]);
        result = 0xFFFFFFFF;
    }
    else
    {
        m_cmdQueueData[queuePort][m_cmdCount[queuePort]] = word;
        m_cmdCount[threadParam->m_portIndex]++;
        OSSignalSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);
        result = 0;
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
    unsigned int cmd = 0;
    unsigned char* cmdBytes = reinterpret_cast<unsigned char*>(&cmd);
    cmdBytes[0] = 0x10;
    unsigned int word = cmd;

    int result = 0;

    if (static_cast<signed char>(m_threadRunningMask) == 0)
    {
        return result;
    }

    OSWaitSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);

    unsigned int queuePort = threadParam->m_portIndex;
    if (static_cast<int>(m_cmdCount[queuePort]) >= 0x40)
    {
        OSSignalSemaphore(&m_accessSemaphores[queuePort]);
        result = -1;
    }
    else
    {
        m_cmdQueueData[queuePort][m_cmdCount[queuePort]] = word;
        m_cmdCount[threadParam->m_portIndex]++;
        OSSignalSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);
        result = 0;
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

    unsigned int localWord;
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
        if (phase == 2 && chunkCount <= step)
        {
            return -1;
        }

        return 0;
    }

    OSWaitSemaphore(&m_accessSemaphores[port]);

    m_recvQueueEntriesArr[port][m_secCmdCount[port]] = 0;
    m_secCmdCount[port]--;

    localWord = (localWord & 0xFFFF0000u) |
                static_cast<unsigned short>(static_cast<char>(localWord >> 24));

    OSSignalSemaphore(&m_accessSemaphores[port]);

    const unsigned char cmd = static_cast<unsigned char>(localWord & 0x3F);
    const unsigned char seq = static_cast<signed char>((localWord >> 8) & 0xFF);

    if (cmd == 7)
    {
        step = 0;
        phase = 0;
        blockIndex = 0;
        localWord = 0;

        ResetQueue(threadParam);

        result = 0;

        if (static_cast<signed char>(m_threadRunningMask) != 0)
        {
            OSWaitSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);

            unsigned int qPort = threadParam->m_portIndex;
            if ((int)m_cmdCount[qPort] >= 0x40)
            {
                OSSignalSemaphore(&m_accessSemaphores[qPort]);
                result = -1;
            }
            else
            {
                m_cmdQueueData[qPort][m_cmdCount[qPort]] = 0x10000000;
                m_cmdCount[threadParam->m_portIndex]++;

                OSSignalSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);
                result = 0;
            }
        }

        const unsigned int typeVal = static_cast<char>(sendType);
        const int respVal = seq;

        if (result != 0)
        {
            int diffMask = ((typeVal - respVal) | (respVal - typeVal)) >> 31;
            return -2 - diffMask;
        }

        int diffMask = ((respVal - typeVal) | (typeVal - respVal)) >> 31;
        return diffMask - 1;
    }

    if ((int)seq == (int)static_cast<char>(sendType))
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
            signed char type = sendType;

            if (type != 3 && type != 2 && type != 6 && type != 7 && type != 8 && type != 9)
            {
                GbaQue.IsSingleMode(threadParam->m_portIndex);

                if (static_cast<signed char>(m_threadRunningMask) == 0)
                {
                    result = 0;
                }
                else
                {
                    OSWaitSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);

                    unsigned int qPort = threadParam->m_portIndex;
                    if ((int)m_cmdCount[qPort] >= 0x40)
                    {
                        OSSignalSemaphore(&m_accessSemaphores[qPort]);
                        result = -1;
                    }
                    else
                    {
                        m_cmdQueueData[qPort][m_cmdCount[qPort]] = 0x09000000;
                        m_cmdCount[threadParam->m_portIndex]++;

                        OSSignalSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);
                        result = 0;
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
                if (type != 3 && type != 2 && type != 6 && type != 7 && type != 8 && type != 9)
                {
                    if (System.m_execParam != 0)
                    {
                        System.Printf(s_pctd_Error_send_type_error_pct02x_801DA350, threadParam->m_portIndex);
                    }
                    return -1;
                }

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

                OSWaitSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);

                if ((int)m_cmdCount[threadParam->m_portIndex] >= 0x40)
                {
                    OSSignalSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);
                    result = -1;
                }
                else
                {
                    m_cmdQueueData[threadParam->m_portIndex][m_cmdCount[threadParam->m_portIndex]] = word;
                    m_cmdCount[threadParam->m_portIndex]++;

                    OSSignalSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);
                    result = 0;
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
                (static_cast<unsigned int>(len & 0x00FF) << 8) |
                static_cast<unsigned int>(len >> 8);

            if (m_threadRunningMask != 0)
            {
                localWord = word;

                OSWaitSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);

                if ((int)m_cmdCount[threadParam->m_portIndex] >= 0x40)
                {
                    OSSignalSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);
                    result = -1;
                }
                else
                {
                    m_cmdQueueData[threadParam->m_portIndex][m_cmdCount[threadParam->m_portIndex]] = word;
                    m_cmdCount[threadParam->m_portIndex]++;

                    OSSignalSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);
                    result = 0;
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

                OSWaitSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);

                if ((int)m_cmdCount[threadParam->m_portIndex] >= 0x40)
                {
                    OSSignalSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);
                    result = -1;
                }
                else
                {
                    m_cmdQueueData[threadParam->m_portIndex][m_cmdCount[threadParam->m_portIndex]] = word;
                    m_cmdCount[threadParam->m_portIndex]++;

                    OSSignalSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);
                    result = 0;
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

            unsigned int word = (static_cast<unsigned int>(0x4B) << 24) |
                                (static_cast<unsigned int>(rowCount) << 16) |
                                (static_cast<unsigned int>(len & 0x00FF) << 8) |
                                static_cast<unsigned int>(len >> 8);

            if (m_threadRunningMask == 0)
            {
                result = 0;
            }
            else
            {
                localWord = word;

                OSWaitSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);

                if ((int)m_cmdCount[threadParam->m_portIndex] >= 0x40)
                {
                    OSSignalSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);
                    result = -1;
                }
                else
                {
                    m_cmdQueueData[threadParam->m_portIndex][m_cmdCount[threadParam->m_portIndex]] = word;
                    m_cmdCount[threadParam->m_portIndex]++;

                    OSSignalSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);
                    result = 0;
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

                OSWaitSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);

                if ((int)m_cmdCount[threadParam->m_portIndex] >= 0x40)
                {
                    OSSignalSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);
                    result = -1;
                }
                else
                {
                    m_cmdQueueData[threadParam->m_portIndex][m_cmdCount[threadParam->m_portIndex]] = word;
                    m_cmdCount[threadParam->m_portIndex]++;

                    OSSignalSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);
                    result = 0;
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
        unsigned char* p = dataBase;

        signed char b0 = *p++;
        unsigned char b1 = *p++;
        unsigned char b2 = *p++;

        dataBase = p;

        unsigned int word =
            (static_cast<unsigned int>(0x8B) << 24) |
            (static_cast<unsigned int>(b0) << 16) |
            (static_cast<unsigned int>(b1) << 8) |
            static_cast<unsigned int>(b2);

        if (m_threadRunningMask != 0)
        {
            localWord = word;

            OSWaitSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);

            if ((int)m_cmdCount[threadParam->m_portIndex] >= 0x40)
            {
                OSSignalSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);
                result = -1;
            }
            else
            {
                m_cmdQueueData[threadParam->m_portIndex][m_cmdCount[threadParam->m_portIndex]] = word;
                m_cmdCount[threadParam->m_portIndex]++;

                OSSignalSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);
                result = 0;
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
    short posX, posY;

    GbaQue.GetMBasePos(threadParam->m_portIndex, &posX, &posY);

    unsigned int cmdX = 0;
    unsigned char* cmdXBytes = reinterpret_cast<unsigned char*>(&cmdX);
    cmdXBytes[0] = 0x0F;
    *reinterpret_cast<unsigned short*>(cmdXBytes + 2) = __lhbrx(&posX, 0);
    unsigned int wordX = cmdX;
    int result = 0;

    if (static_cast<signed char>(m_threadRunningMask) != 0)
    {
        OSWaitSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);

        unsigned int queuePort = threadParam->m_portIndex;
        if ((int)m_cmdCount[queuePort] >= 0x40)
        {
            OSSignalSemaphore(&m_accessSemaphores[queuePort]);
            result = -1;
        }
        else
        {
            m_cmdQueueData[queuePort][m_cmdCount[queuePort]] = wordX;
            m_cmdCount[threadParam->m_portIndex]++;
            OSSignalSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);
            result = 0;
        }
    }

    if (result != 0)
	{
        return -1;
	}

    unsigned int cmdY = 0;
    unsigned char* cmdYBytes = reinterpret_cast<unsigned char*>(&cmdY);
    cmdYBytes[0] = 0x4F;
    *reinterpret_cast<unsigned short*>(cmdYBytes + 2) = __lhbrx(&posY, 0);
    unsigned int wordY = cmdY;

    if (static_cast<signed char>(m_threadRunningMask) != 0)
    {
        OSWaitSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);

        unsigned int queuePort = threadParam->m_portIndex;
        if ((int)m_cmdCount[queuePort] >= 0x40)
        {
            OSSignalSemaphore(&m_accessSemaphores[queuePort]);
            result = -1;
        }
        else
        {
            m_cmdQueueData[queuePort][m_cmdCount[queuePort]] = wordY;
            m_cmdCount[threadParam->m_portIndex]++;
            OSSignalSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);
            result = 0;
        }
    }

    return result != 0 ? -1 : 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::SendMapNo(ThreadParam* threadParam)
{
    int port = threadParam->m_portIndex;

    char stageMajor[4];
    char stageMinor[4];

    GbaQue.GetStageNo(port, (int*)&stageMajor, (int*)&stageMinor);

    unsigned int cmd = 0;
    unsigned char* cmdBytes = reinterpret_cast<unsigned char*>(&cmd);
    cmdBytes[0] = 0x0E;
    cmdBytes[1] = 1;
    cmdBytes[2] = stageMajor[3];
    cmdBytes[3] = stageMinor[3];
    unsigned int queueCmd = cmd;

    unsigned int result = 0;

    if (static_cast<signed char>(m_threadRunningMask) != 0)
    {
        OSWaitSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);

        port = threadParam->m_portIndex;
        if ((int)m_cmdCount[port] >= 0x40)
        {
            OSSignalSemaphore(&m_accessSemaphores[port]);
            result = 0xFFFFFFFF;
        }
        else
        {
            m_cmdQueueData[port][m_cmdCount[port]] = queueCmd;
            m_cmdCount[threadParam->m_portIndex]++;
            OSSignalSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);
            result = 0;
        }
    }

    return result != 0 ? -1 : 0;
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

    unsigned char& state = threadParam->m_pposCounter;
    unsigned char* posBytes = m_playerPosPacketBuffer[threadParam->m_portIndex] + 2;
    unsigned int* posWords = (unsigned int*)posBytes;

    switch (state)
    {
    case 0:
    {
        if (((int)System.m_frameCounter % 4) != 0)
        {
            return 0;
        }

        memset(posBytes, 0, sizeof(m_playerPosPacketBuffer[threadParam->m_portIndex]));

        GbaQue.GetPlayerPos(threadParam->m_portIndex, posWords);

        m_cmdBuffer[threadParam->m_portIndex] = 3;
        m_pposWordIndex[threadParam->m_portIndex] = 0;
        state += 1;

        break;
    }

    case 1:
    {
        int sent = m_pposWordIndex[threadParam->m_portIndex];
        int totalWord = (int)(signed char)m_cmdBuffer[threadParam->m_portIndex];

        while (sent < totalWord)
        {
            unsigned int word = posWords[sent];

            if (static_cast<signed char>(m_threadRunningMask) != 0)
            {
                OSWaitSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);

                unsigned int queuePort = threadParam->m_portIndex;
                if ((int)m_cmdCount[queuePort] >= 0x40)
                {
                    OSSignalSemaphore(&m_accessSemaphores[queuePort]);
                    result = -1;
                }
                else
                {
                    m_cmdQueueData[queuePort][m_cmdCount[queuePort]] = word;
                    m_cmdCount[threadParam->m_portIndex]++;

                    OSSignalSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);
                    result = 0;
                }
            }

            if (result != 0)
            {
                break;
            }

            sent++;
        }

        m_pposWordIndex[threadParam->m_portIndex] += sent;

        // Done with all player-pos words?
        if (m_pposWordIndex[threadParam->m_portIndex] >= (int)(signed char)m_cmdBuffer[threadParam->m_portIndex])
        {
            m_cmdBuffer[threadParam->m_portIndex] = 0;
            m_pposWordIndex[threadParam->m_portIndex] = 0;
            state += 1;
        }
        break;
    }

    case 2:
    {
        memset(posBytes, 0, sizeof(m_playerPosPacketBuffer[threadParam->m_portIndex]));
        m_pposWordIndex[threadParam->m_portIndex] = 0;
        m_cmdBuffer[4 + threadParam->m_portIndex] = 0;

        int enemyCount = 0;

        GbaQue.GetEnemyPos(threadParam->m_portIndex, posWords, &enemyCount);

        m_cmdBuffer[4 + threadParam->m_portIndex] = (unsigned char)enemyCount;

        // If there are no enemies, skip straight to treasure (state 4)
        if (m_cmdBuffer[4 + threadParam->m_portIndex] == 0)
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
        int sent = m_pposWordIndex[threadParam->m_portIndex];
        int totalWord = (int)(unsigned char)m_cmdBuffer[4 + threadParam->m_portIndex];

        while (sent < totalWord)
        {
            unsigned int word = posWords[sent];

            if (static_cast<signed char>(m_threadRunningMask) != 0)
            {
                OSWaitSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);

                unsigned int queuePort = threadParam->m_portIndex;
                if ((int)m_cmdCount[queuePort] >= 0x40)
                {
                    OSSignalSemaphore(&m_accessSemaphores[queuePort]);
                    result = -1;
                }
                else
                {
                    m_cmdQueueData[queuePort][m_cmdCount[queuePort]] = word;
                    m_cmdCount[threadParam->m_portIndex]++;

                    OSSignalSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);
                    result = 0;
                }
            }

            if (result != 0)
            {
                break;
            }

            sent++;
        }

        m_pposWordIndex[threadParam->m_portIndex] += sent;

        if (m_pposWordIndex[threadParam->m_portIndex] >= (int)(signed char)m_cmdBuffer[4 + threadParam->m_portIndex])
        {
            m_cmdBuffer[4 + threadParam->m_portIndex] = 0;
            m_pposWordIndex[threadParam->m_portIndex] = 0;
            state += 1;
        }

        break;
    }

    case 4:
    {
        memset(posBytes, 0, sizeof(m_playerPosPacketBuffer[threadParam->m_portIndex]));
        m_pposWordIndex[threadParam->m_portIndex] = 0;
        m_cmdBuffer[4 + threadParam->m_portIndex] = 0;

        int treasureCount = 0;

        GbaQue.GetTreasurePos(threadParam->m_portIndex, posWords, &treasureCount);

        m_cmdBuffer[4 + threadParam->m_portIndex] = (unsigned char)treasureCount;

        if (m_cmdBuffer[4 + threadParam->m_portIndex] == 0)
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
        int sent = m_pposWordIndex[threadParam->m_portIndex];
        int totalWord = (int)(signed char)m_cmdBuffer[4 + threadParam->m_portIndex];

        while (sent < totalWord)
        {
            unsigned int word = posWords[sent];

            if (static_cast<signed char>(m_threadRunningMask) != 0)
            {
                OSWaitSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);

                unsigned int queuePort = threadParam->m_portIndex;
                if ((int)m_cmdCount[queuePort] >= 0x40)
                {
                    OSSignalSemaphore(&m_accessSemaphores[queuePort]);
                    result = -1;
                }
                else
                {
                    m_cmdQueueData[queuePort][m_cmdCount[queuePort]] = word;
                    m_cmdCount[threadParam->m_portIndex]++;

                    OSSignalSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);
                    result = 0;
                }
            }

            if (result != 0)
            {
                break;
            }

            sent++;
        }

        m_pposWordIndex[threadParam->m_portIndex] += sent;

        if (m_pposWordIndex[threadParam->m_portIndex] >= (int)(signed char)m_cmdBuffer[4 + threadParam->m_portIndex])
        {
            state = 0;
            m_cmdBuffer[4 + threadParam->m_portIndex] = 0;
            m_pposWordIndex[threadParam->m_portIndex] = 0;
        }

        break;
    }

    default:
    {
        if ((unsigned int)System.m_execParam >= 2u)
        {
            signed char cnt = (signed char)m_cmdBuffer[threadParam->m_portIndex];

            System.Printf(const_cast<char*>(s_send_ppos_bad_state_fmt), threadParam->m_portIndex, (int)cnt);
        }

        m_cmdBuffer[threadParam->m_portIndex] = 0;
        m_cmdBuffer[4 + threadParam->m_portIndex] = 0;
        m_pposWordIndex[threadParam->m_portIndex] = 0;
        result = -1;

        break;
    }
    }

    return result;
}


/*
 * --INFO--
 * PAL Address: 0x800AB24C
 * PAL Size: 420b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
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
    int chunkCount;
    unsigned int uVar8;

    uVar5 = 0xFFFF;
    chunkCount = length;
    pbVar4 = param_2;

    while (--chunkCount >= 0) {
        bVar2 = *pbVar4;
        pbVar4 = pbVar4 + 1;
        uVar5 = ((uVar5 << 8) ^ static_cast<unsigned int>(JoyBusCrcTable[(uVar5 >> 8) ^ static_cast<unsigned int>(bVar2)])) & 0xFFFF;
    }

    unsigned short inv = static_cast<unsigned short>(~static_cast<unsigned short>(uVar5));
    chunkCount = (length - 1) / 3;
    param_4[0] = 5;

    if ((length - 1) - (chunkCount * 3) != 0) {
        chunkCount = chunkCount + 1;
    }

    iVar3 = chunkCount + 2;

    if (iVar3 > 0xFF) {
        iVar3 = -1;
    } else {
        param_4[1] = static_cast<unsigned char>(iVar3);

        *reinterpret_cast<unsigned short*>(param_4 + 2) = __lhbrx(&inv, 0);

        puVar6 = param_4 + 8;
        param_4[4] = 0x45;
        pbVar4 = param_2 + 1;
        param_4[5] = static_cast<unsigned char>(length);
        param_4[6] = static_cast<unsigned char>(static_cast<unsigned int>(length) >> 8);
        param_4[7] = *param_2;

        if (1 < iVar3) {
            uVar5 = static_cast<unsigned int>(iVar3 - 1);
            uVar8 = uVar5 >> 2;
            unsigned char marker = 0x85;

            if (uVar8 != 0) {
                do {
                    puVar6[0] = marker;
                    puVar6[1] = pbVar4[0];
                    puVar6[2] = pbVar4[1];
                    puVar6[3] = pbVar4[2];

                    puVar6[4] = marker;
                    puVar6[5] = pbVar4[3];
                    puVar6[6] = pbVar4[4];
                    puVar6[7] = pbVar4[5];

                    puVar6[8] = marker;
                    puVar6[9] = pbVar4[6];
                    puVar6[10] = pbVar4[7];
                    puVar6[11] = pbVar4[8];

                    puVar6[12] = marker;
                    puVar6[13] = pbVar4[9];
                    puVar6[14] = pbVar4[10];

                    pbVar1 = pbVar4 + 0x0B;
                    pbVar4 = pbVar4 + 0x0C;

                    puVar6[15] = *pbVar1;
                    puVar6 = puVar6 + 0x10;

                    uVar8 = uVar8 - 1;
                } while (uVar8 != 0);

                uVar5 = uVar5 & 3;
                if (uVar5 == 0) {
                    return iVar3;
                }
            }

            do {
                puVar6[0] = marker;
                puVar6[1] = pbVar4[0];
                puVar6[2] = pbVar4[1];
                pbVar1 = pbVar4 + 2;
                pbVar4 = pbVar4 + 3;
                puVar6[3] = *pbVar1;
                puVar6 = puVar6 + 4;
                uVar5 = uVar5 - 1;
            } while (uVar5 != 0);
        }
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
    unsigned int result = 0;

    switch ((unsigned char)threadParam->m_subState)
    {
    case 0:
        {
            GbaPInfo playerInfo;

            GbaQue.GetPlayerStat(threadParam->m_portIndex, &playerInfo);

            m_txWordIndex[threadParam->m_portIndex] = 0;

            unsigned char classFlags[4];
            memset(classFlags, 0xFF, sizeof(classFlags));

            unsigned char payload[0x300];
            memset(payload, 0, sizeof(payload));

            ClearJoyDataPacketPayload(this, threadParam->m_portIndex);

            payload[0] = 1;

            GbaQue.GetCaravanName((char*)&payload[1]);

            signed char* p = (signed char*)&playerInfo;
            unsigned char lowBits = 0;
            unsigned char highBits = 0;

            for (int count = 0; count < 2; count++)
            {
                if (p[0x16] != 0)
                {
                    int idx = (int)p[0] >> 1;
                    signed char v = (classFlags[idx] & 0x0F) | lowBits;

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
                        (classFlags[idx] & 0x0F) | (signed char)(lowBits + 0x10);

                    if ((p[0xDC] & 1) != 0)
                    {
                        v = (classFlags[idx] & 0xF0) | (signed char)(highBits + 1);
                    }

                    classFlags[idx] = v;
                }

                p       += 0x1B8;
                lowBits += 0x20;
                highBits += 2;
            }

            memcpy(&payload[0x81], classFlags, sizeof(classFlags));

            unsigned char* playerData = playerInfo.m_data;
            int playerOffset = threadParam->m_portIndex * 0xDC;

            payload[0x85] = playerData[0x16];
            payload[0x86] = playerData[0x17];
            payload[0x87] = playerData[0xF2];
            payload[0x88] = playerData[0xF3];
            payload[0x89] = playerData[0x1CE];
            payload[0x8A] = playerData[0x1CF];
            payload[0x8B] = playerData[0x2AA];
            payload[0x8C] = playerData[0x2AB];
            payload[0x8D] = playerData[playerOffset + 2];

            memcpy(&payload[0x8E], &playerData[playerOffset + 0x20], 3);

            payload[0x91] = playerData[playerOffset + 0x14];
            payload[0x92] = playerData[playerOffset + 0x15];

            unsigned char compatBuf[64];
            memset(compatBuf, 0, sizeof(compatBuf));

            int compatLen = GbaQue.GetCompatibility(threadParam->m_portIndex, compatBuf);

            unsigned char* body = &payload[0x93];

            memcpy(body, compatBuf, compatLen);

            memcpy(body + compatLen, &playerData[playerOffset + 0x18], 8);

            unsigned int statWord = ((unsigned int)playerData[playerOffset + 0x27] << 24) |
                                    ((unsigned int)playerData[playerOffset + 0x26] << 16) |
                                    ((unsigned int)playerData[playerOffset + 0x25] << 8) |
                                     (unsigned int)playerData[playerOffset + 0x24];
            memcpy(body + compatLen + 8, &statWord, sizeof(statWord));

            const int byteLen = compatLen + 0xA3;

            int wordCount = MakeJoyData((char*)payload, byteLen, (unsigned int*)(void*)(m_joyDataPacketBuffer[threadParam->m_portIndex] + 2));

            if (wordCount < 0)
            {
                return wordCount;
            }

            m_txWordCount[threadParam->m_portIndex] = wordCount;
            threadParam->m_subState = (unsigned char)(threadParam->m_subState + 1);

            // Immediately queue the first word (same as the subState == 1 path)
            unsigned int sendPort = threadParam->m_portIndex;
            unsigned int word = *(unsigned int*)&m_joyDataPacketBuffer[sendPort][2 + m_txWordIndex[sendPort] * 4];

            if (static_cast<signed char>(m_threadRunningMask) == 0)
            {
                result = 0;
            }
            else
            {
                OSWaitSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);

                unsigned int queuePort = threadParam->m_portIndex;
                if ((int)m_cmdCount[queuePort] >= 0x40)
                {
                    OSSignalSemaphore(&m_accessSemaphores[queuePort]);
                    result = -1;
                }
                else
                {
                    m_cmdQueueData[queuePort][m_cmdCount[queuePort]] = word;
                    m_cmdCount[threadParam->m_portIndex]++;

                    OSSignalSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);
                    result = 0;
                }
            }
        }
        break;

    case 1:
        {
            unsigned int statPort = threadParam->m_portIndex;
            unsigned int word = *(unsigned int*)&m_joyDataPacketBuffer[statPort][2 + m_txWordIndex[statPort] * 4];

            if (static_cast<signed char>(m_threadRunningMask) == 0)
            {
                result = 0;
            }
            else
            {
                OSWaitSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);

                if ((int)m_cmdCount[threadParam->m_portIndex] >= 0x40)
                {
                    OSSignalSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);
                    result = -1;
                }
                else
                {
                    m_cmdQueueData[threadParam->m_portIndex][m_cmdCount[threadParam->m_portIndex]] = word;
                    m_cmdCount[threadParam->m_portIndex]++;

                    OSSignalSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);
                    result = 0;
                }
            }
        }
        break;
    }

    // Common tail: advance word index and clear GBA flag when finished.
    if (result == 0)
    {
        m_txWordIndex[threadParam->m_portIndex]++;

        if (m_txWordCount[threadParam->m_portIndex] <= m_txWordIndex[threadParam->m_portIndex])
        {
            GbaQue.ClrCompatibilityFlg(threadParam->m_portIndex);

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
    unsigned int hpData[2];

    int sync = GBARecvSend(threadParam, hpData);

    if (sync < 0)
	{
        return -1;
	}

    hpData[0] = 0;

    unsigned int hpStatus = GbaQue.GetPlayerHP(threadParam->m_portIndex, (unsigned char*)hpData);

    if (((-hpStatus | hpStatus) >> 31) == 0)
	{
        return 0;
	}

    ((unsigned char*)hpData)[1] |= 0x80;

    unsigned int cmd = hpData[0];
    int result = 0;

    if (static_cast<signed char>(m_threadRunningMask) == 0)
    {
        return result;
    }

    OSWaitSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);

    unsigned int port = threadParam->m_portIndex;
    if ((int)m_cmdCount[port] >= 0x40)
    {
        OSSignalSemaphore(&m_accessSemaphores[port]);
        result = -1;
    }
    else
    {
        m_cmdQueueData[port][m_cmdCount[port]] = cmd;
        m_cmdCount[threadParam->m_portIndex]++;
        OSSignalSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);
        result = 0;
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
    unsigned int port;
    int result = 0;
    unsigned char subState = threadParam->m_subState;

    switch (subState)
    {
    case 0:
    {
            m_txWordIndex[threadParam->m_portIndex] = 0;

            unsigned char payload[780];

            memset(payload, 0, kJoyDataLargePayloadClearBytes);

            ClearJoyDataPacketPayload(this, threadParam->m_portIndex);

            payload[0] = 2;

            unsigned char* itemBuf = &payload[1];

            int byteLen = GbaQue.GetItemAll(threadParam->m_portIndex, itemBuf) + 1; // +1 for the type byte

            int wordCount = MakeJoyData(
                (char*)payload,
                byteLen,
                (unsigned int*)(m_joyDataPacketBuffer[threadParam->m_portIndex] + 2)
            );

            if (wordCount < 0)
            {
                return wordCount;
            }

            m_txWordCount[threadParam->m_portIndex] = wordCount;
            threadParam->m_subState = (unsigned char)(threadParam->m_subState + 1);

            port = threadParam->m_portIndex;
            unsigned int word = *(unsigned int*)&m_joyDataPacketBuffer[port][2 + m_txWordIndex[port] * 4];

            if (static_cast<signed char>(m_threadRunningMask) == 0)
            {
                result = 0;
            }
            else
            {
                OSWaitSemaphore(&m_accessSemaphores[port]);

                port = threadParam->m_portIndex;
                if ((int)m_cmdCount[port] >= 0x40)
                {
                    OSSignalSemaphore(&m_accessSemaphores[port]);
                    result = -1;
                }
                else
                {
                    m_cmdQueueData[port][m_cmdCount[port]] = word;
                    m_cmdCount[threadParam->m_portIndex]++;

                    OSSignalSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);
                    result = 0;
                }
            }
        break;
    }
    case 1:
    {
        port = threadParam->m_portIndex;
        unsigned int word = *(unsigned int*)&m_joyDataPacketBuffer[port][2 + m_txWordIndex[port] * 4];

        if (static_cast<signed char>(m_threadRunningMask) == 0)
        {
            result = 0;
        }
        else
        {
            OSWaitSemaphore(&m_accessSemaphores[port]);

            port = threadParam->m_portIndex;
            if ((int)m_cmdCount[port] >= 0x40)
            {
                OSSignalSemaphore(&m_accessSemaphores[port]);
                result = -1;
            }
            else
            {
                m_cmdQueueData[port][m_cmdCount[port]] = word;
                m_cmdCount[threadParam->m_portIndex]++;

                OSSignalSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);
                result = 0;
            }
        }
        break;
    }
    }

    if (result == 0)
    {
        m_txWordIndex[threadParam->m_portIndex]++;

        if (m_txWordIndex[threadParam->m_portIndex] >= m_txWordCount[threadParam->m_portIndex])
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
    int port;
    int result = 0;
    unsigned char subState = threadParam->m_subState;

    switch (subState)
    {
    case 0:
    {
            m_txWordIndex[threadParam->m_portIndex] = 0;

            unsigned char payload[524];

            memset(payload, 0, kJoyDataMapPayloadClearBytes);

            payload[0] = 3;

            unsigned char* mapObjBuf = &payload[1];

            int byteLen = GbaQue.GetMapObj(mapObjBuf) + 1;

            int wordCount = MakeJoyData((char*)payload, byteLen, (unsigned int*)(m_joyDataPacketBuffer[threadParam->m_portIndex] + 2));

            if (wordCount < 0)
            {
                return wordCount;
            }

            m_txWordCount[threadParam->m_portIndex] = wordCount;

            port = threadParam->m_portIndex;
            unsigned int word = *(unsigned int*)&m_joyDataPacketBuffer[port][2 + m_txWordIndex[port] * 4];

            if (static_cast<signed char>(m_threadRunningMask) == 0)
            {
                result = 0;
            }
            else
            {
                OSWaitSemaphore(&m_accessSemaphores[port]);

                port = threadParam->m_portIndex;
                if ((int)m_cmdCount[port] >= 0x40)
                {
                    OSSignalSemaphore(&m_accessSemaphores[port]);
                    result = -1;
                }
                else
                {
                    m_cmdQueueData[port][m_cmdCount[port]] = word;
                    m_cmdCount[threadParam->m_portIndex]++;

                    OSSignalSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);
                    result = 0;
                }
            }

            threadParam->m_subState = (unsigned char)(threadParam->m_subState + 1);
        
        break;
    }
    case 1:
    {
        port = threadParam->m_portIndex;
        unsigned int word = *(unsigned int*)&m_joyDataPacketBuffer[port][2 + m_txWordIndex[port] * 4];

        if (static_cast<signed char>(m_threadRunningMask) == 0)
        {
            result = 0;
        }
        else
        {
            OSWaitSemaphore(&m_accessSemaphores[port]);

            port = threadParam->m_portIndex;
            if ((int)m_cmdCount[port] >= 0x40)
            {
                OSSignalSemaphore(&m_accessSemaphores[port]);
                result = -1;
            }
            else
            {
                m_cmdQueueData[port][m_cmdCount[port]] = word;
                m_cmdCount[threadParam->m_portIndex]++;

                OSSignalSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);
                result = 0;
            }
        }

        break;
    }
    }

    if (result == 0)
    {
        m_txWordIndex[threadParam->m_portIndex]++;

        if (m_txWordIndex[threadParam->m_portIndex] >= m_txWordCount[threadParam->m_portIndex])
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
    unsigned int port;
    int result = 0;
    unsigned char subState = threadParam->m_subState;

    switch (subState)
    {
    case 0:
    {
            m_txWordIndex[threadParam->m_portIndex] = 0;
            unsigned char payload[268];

            memset(payload, 0, kJoyDataSmallPayloadClearBytes);

            ClearJoyDataPacketPayload(this, threadParam->m_portIndex);
            payload[0] = 5;

            unsigned char* compatBuf = &payload[1];

            int byteLen = GbaQue.GetCompatibility(threadParam->m_portIndex, compatBuf) + 1;

            int wordCount = MakeJoyData((char*)payload, byteLen, (unsigned int*)(void*)(m_joyDataPacketBuffer[threadParam->m_portIndex] + 2));

            if (wordCount < 0)
            {
                return wordCount;
            }

            m_txWordCount[threadParam->m_portIndex] = wordCount;
            threadParam->m_subState = (unsigned char)(threadParam->m_subState + 1);

            port = threadParam->m_portIndex;
            unsigned int word = *(unsigned int*)&m_joyDataPacketBuffer[port][2 + m_txWordIndex[port] * 4];

            if (static_cast<signed char>(m_threadRunningMask) == 0)
            {
                result = 0;
            }
            else
            {
                OSWaitSemaphore(&m_accessSemaphores[port]);

                port = threadParam->m_portIndex;
                if ((int)m_cmdCount[port] >= 0x40)
                {
                    OSSignalSemaphore(&m_accessSemaphores[port]);
                    result = -1;
                }
                else
                {
                    m_cmdQueueData[port][m_cmdCount[port]] = word;
                    m_cmdCount[threadParam->m_portIndex]++;

                    OSSignalSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);

                    result = 0;
                }
            }
        
        break;
    }
    case 1:
    {
        port = threadParam->m_portIndex;
        unsigned int word = *(unsigned int*)&m_joyDataPacketBuffer[port][2 + m_txWordIndex[port] * 4];

        if (static_cast<signed char>(m_threadRunningMask) == 0)
        {
            result = 0;
        }
        else
        {
            OSWaitSemaphore(&m_accessSemaphores[port]);

            port = threadParam->m_portIndex;
            if ((int)m_cmdCount[port] >= 0x40)
            {
                OSSignalSemaphore(&m_accessSemaphores[port]);
                result = -1;
            }
            else
            {
                m_cmdQueueData[port][m_cmdCount[port]] = word;
                m_cmdCount[threadParam->m_portIndex]++;

                OSSignalSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);
                result = 0;
            }
        }
    
        break;
    }
    }

    if (result == 0)
    {
        m_txWordIndex[threadParam->m_portIndex]++;

        if (m_txWordIndex[threadParam->m_portIndex] >= m_txWordCount[threadParam->m_portIndex])
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
    unsigned int cmd = 0;
    unsigned char* cmdBytes = (unsigned char*)&cmd;
    int modeByte = controlMode;
    bool isSingle = GbaQue.IsSingleMode(threadParam->m_portIndex);

    // If single-player, force modeByte = 0
    if (isSingle)
	{
        modeByte = 0;
	}

    cmdBytes[0] = 9;
    cmdBytes[1] = modeByte;
    unsigned int cmdWord = cmd;
    int result = 0;

    if (static_cast<signed char>(m_threadRunningMask) != 0)
    {
        OSWaitSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);

        unsigned int queuePort = threadParam->m_portIndex;
        if (static_cast<int>(m_cmdCount[queuePort]) >= 0x40)
        {
            OSSignalSemaphore(&m_accessSemaphores[queuePort]);
            result = -1;
        }
        else
        {
            m_cmdQueueData[queuePort][m_cmdCount[queuePort]] = cmdWord;
            m_cmdCount[threadParam->m_portIndex]++;
            OSSignalSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);
            result = 0;
        }
    }

    if (result == 0)
	{
        m_ctrlModeArr[threadParam->m_portIndex] = modeByte;
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
    unsigned int flgWord = 0;
    int result = GBARecvSend(threadParam, &flgWord);

    if (result < 0)
    {
        result = -1;
    }
    else
    {
        GbaQue.GetMapObjDrawFlg(&flgWord);

        unsigned char* data = (unsigned char*)&flgWord;
        unsigned char crcBytes[4];
        crcBytes[3] = data[0];
        crcBytes[2] = data[1];
        crcBytes[1] = data[2];
        crcBytes[0] = data[3];
        unsigned char* crcData = crcBytes;
        unsigned short crc = 0xFFFF;
        int crcCount = 4;

        while (--crcCount >= 0)
        {
            unsigned char byte = *crcData++;
            unsigned int index = (crc >> 8) ^ byte;
            crc = (crc << 8) ^ JoyBusCrcTable[index];
        }

        crc = ~crc;

        unsigned int cmds[2];
        cmds[0] = 0;
        cmds[1] = 0;
        unsigned char* cmdBytes = (unsigned char*)cmds;
        cmdBytes[0] = 0x16;
        cmdBytes[1] = (unsigned char)(crc & 0xFF);
        cmdBytes[2] = (unsigned char)((crc >> 8) & 0xFF);
        cmdBytes[3] = crcBytes[0];
        cmdBytes[4] = 0x56;
        cmdBytes[5] = crcBytes[1];
        cmdBytes[6] = crcBytes[2];
        cmdBytes[7] = crcBytes[3];
        unsigned int cmd1 = cmds[0];
        unsigned int cmd2 = cmds[1];

        if (static_cast<signed char>(m_threadRunningMask) == 0)
        {
            result = 0;
        }
        else
        {
            OSWaitSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);

            unsigned int port = threadParam->m_portIndex;
            if ((int)m_cmdCount[port] >= 0x40)
            {
                OSSignalSemaphore(&m_accessSemaphores[port]);
                result = -1;
            }
            else
            {
                m_cmdQueueData[port][m_cmdCount[port]] = cmd1;
                m_cmdCount[threadParam->m_portIndex]++;
                OSSignalSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);
                result = 0;
            }
        }

        if (result == 0)
        {
            if (m_threadRunningMask == 0)
            {
                result = 0;
            }
            else
            {
                OSWaitSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);

                unsigned int port = threadParam->m_portIndex;
                if ((int)m_cmdCount[port] >= 0x40)
                {
                    OSSignalSemaphore(&m_accessSemaphores[port]);
                    result = -1;
                }
                else
                {
                    m_cmdQueueData[port][m_cmdCount[port]] = cmd2;
                    m_cmdCount[threadParam->m_portIndex]++;
                    OSSignalSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);
                    result = 0;
                }
            }
        }
    }

    return result;
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
    unsigned char subState = threadParam->m_subState;

    switch (subState)
    {
    case 0:
    {
            unsigned char payload[1 + 75];

            memset(payload, 0, kJoyDataFavoritePayloadClearBytes);
            ClearJoyDataPacketPayload(this, threadParam->m_portIndex);

            payload[0] = 4;

            unsigned char* favBuf = &payload[1];

            int byteLen = GbaQue.GetFavorite(threadParam->m_portIndex, (char*)favBuf) + 1;

            int wordCount = MakeJoyData(
                (char*)payload,
                byteLen,
                (unsigned int*)(m_joyDataPacketBuffer[threadParam->m_portIndex] + 2)
            );

            if (wordCount < 0)
            {
                return wordCount;
            }

            result = 0;
            m_txWordCount[threadParam->m_portIndex] = wordCount;
            m_txWordIndex[threadParam->m_portIndex] = 0;

            unsigned int port = threadParam->m_portIndex;
            unsigned int word = *(unsigned int*)&m_joyDataPacketBuffer[port][2 + m_txWordIndex[port] * 4];

            if (static_cast<signed char>(m_threadRunningMask) != 0)
            {
                OSWaitSemaphore(&m_accessSemaphores[port]);

                port = threadParam->m_portIndex;
                if ((int)m_cmdCount[port] >= 0x40)
                {
                    OSSignalSemaphore(&m_accessSemaphores[port]);
                    result = -1;
                }
                else
                {
                    m_cmdQueueData[port][m_cmdCount[port]] = word;
                    m_cmdCount[threadParam->m_portIndex]++;

                    OSSignalSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);
                    result = 0;
                }
            }

            threadParam->m_subState = (unsigned char)(threadParam->m_subState + 1);
        
        break;
    }
    case 1:
    {
        unsigned int port = threadParam->m_portIndex;
        unsigned int word = *(unsigned int*)&m_joyDataPacketBuffer[port][2 + m_txWordIndex[port] * 4];

        if (static_cast<signed char>(m_threadRunningMask) == 0)
        {
            result = 0;
        }
        else
        {
            OSWaitSemaphore(&m_accessSemaphores[port]);

            port = threadParam->m_portIndex;
            if ((int)m_cmdCount[port] >= 0x40)
            {
                OSSignalSemaphore(&m_accessSemaphores[port]);
                result = -1;
            }
            else
            {
                m_cmdQueueData[port][m_cmdCount[port]] = word;
                m_cmdCount[threadParam->m_portIndex]++;

                OSSignalSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);
                result = 0;
            }
        }
    
        break;
    }
    }

    if (result == 0)
    {
        m_txWordIndex[threadParam->m_portIndex]++;

        if (m_txWordIndex[threadParam->m_portIndex] >= m_txWordCount[threadParam->m_portIndex])
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
    unsigned char* cmdBytes = reinterpret_cast<unsigned char*>(&cmd);
    cmdBytes[0] = 0x0C;
    cmdBytes[1] = static_cast<signed char>(a);
    cmdBytes[2] = static_cast<unsigned char>(b);
    unsigned int word = cmd;
    int result = 0;

    if (static_cast<signed char>(m_threadRunningMask) == 0)
    {
        return result;
    }

    OSWaitSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);

    unsigned int p = threadParam->m_portIndex;

    if ((int)m_cmdCount[p] >= 0x40)
    {
        OSSignalSemaphore(&m_accessSemaphores[p]);
        result = -1;
    }
    else
    {
        m_cmdQueueData[p][m_cmdCount[p]] = word;
        m_cmdCount[threadParam->m_portIndex]++;

        OSSignalSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);
        result = 0;
    }

    return result;
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
    ResetQueue(threadParam);

    unsigned int cmd0 = 0;
    unsigned char* cmd0Bytes = reinterpret_cast<unsigned char*>(&cmd0);
    cmd0Bytes[0] = 0x10;
    unsigned int word0 = cmd0;

    int result = 0;

    if (static_cast<signed char>(m_threadRunningMask) != 0)
    {
        OSWaitSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);

        unsigned int port = threadParam->m_portIndex;
        if ((int)m_cmdCount[port] >= 0x40)
        {
            OSSignalSemaphore(&m_accessSemaphores[port]);
            result = -1;
        }
        else
        {
            m_cmdQueueData[port][m_cmdCount[port]] = word0;
            m_cmdCount[threadParam->m_portIndex]++;
            OSSignalSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);
            result = 0;
        }
    }

    if (result != 0)
	{
        return result;
	}


    unsigned int cmd = 0;
    unsigned char* cmdBytes = reinterpret_cast<unsigned char*>(&cmd);
    cmdBytes[0] = 0x1B;
    cmdBytes[1] = static_cast<unsigned char>(modeType);
    unsigned int word = cmd;

    if (static_cast<signed char>(m_threadRunningMask) != 0)
    {
        OSWaitSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);

        unsigned int port = threadParam->m_portIndex;
        if ((int)m_cmdCount[port] >= 0x40)
        {
            OSSignalSemaphore(&m_accessSemaphores[port]);
            result = -1;
        }
        else
        {
            m_cmdQueueData[port][m_cmdCount[port]] = word;
            m_cmdCount[threadParam->m_portIndex]++;
            OSSignalSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);
            result = 0;
        }
    }

    if (result != 0)
	{
        return result;
	}

    m_modeXArr[threadParam->m_portIndex] = m_nextModeTypeArr[threadParam->m_portIndex];
    m_nextModeTypeArr[threadParam->m_portIndex] = (unsigned char)modeType;

    if (modeType == 0 || modeType == 4)
	{
        m_ctrlModeArr[threadParam->m_portIndex] = 0;
	}
    else
	{
        m_ctrlModeArr[threadParam->m_portIndex] = 1;
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
    unsigned int port;
    int result = 0;
    unsigned char subState = threadParam->m_subState;

    switch (subState)
    {
    case 0:
    {
            m_txWordIndex[threadParam->m_portIndex] = 0;

            unsigned char payload[1 + 779];

            memset(payload, 0, kJoyDataLargePayloadClearBytes);
            ClearJoyDataPacketPayload(this, threadParam->m_portIndex);

            payload[0] = 6;

            unsigned char* equipBuf = &payload[1];

            int byteLen = GbaQue.GetEquipData(threadParam->m_portIndex, equipBuf) + 1;

            int wordCount = MakeJoyData((char*)payload, byteLen, (unsigned int*)(m_joyDataPacketBuffer[threadParam->m_portIndex] + 2));

            if (wordCount < 0)
            {
                return wordCount;
            }

            m_txWordCount[threadParam->m_portIndex] = wordCount;

            threadParam->m_subState = (unsigned char)(threadParam->m_subState + 1);

            port = threadParam->m_portIndex;
            unsigned int word = *(unsigned int*)&m_joyDataPacketBuffer[port][2 + m_txWordIndex[port] * 4];

            if (static_cast<signed char>(m_threadRunningMask) == 0)
            {
                result = 0;
            }
            else
            {
                OSWaitSemaphore(&m_accessSemaphores[port]);

                port = threadParam->m_portIndex;
                if ((int)m_cmdCount[port] >= 0x40)
                {
                    OSSignalSemaphore(&m_accessSemaphores[port]);
                    result = -1;
                }
                else
                {
                    m_cmdQueueData[port][m_cmdCount[port]] = word;
                    m_cmdCount[threadParam->m_portIndex]++;

                    OSSignalSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);
                    result = 0;
                }
            }
        
        break;
    }
    case 1:
    {
        port = threadParam->m_portIndex;
        unsigned int word = *(unsigned int*)&m_joyDataPacketBuffer[port][2 + m_txWordIndex[port] * 4];

        if (static_cast<signed char>(m_threadRunningMask) == 0)
        {
            result = 0;
        }
        else
        {
            OSWaitSemaphore(&m_accessSemaphores[port]);

            port = threadParam->m_portIndex;
            if ((int)m_cmdCount[port] >= 0x40)
            {
                OSSignalSemaphore(&m_accessSemaphores[port]);
                result = -1;
            }
            else
            {
                m_cmdQueueData[port][m_cmdCount[port]] = word;
                m_cmdCount[threadParam->m_portIndex]++;

                OSSignalSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);
                result = 0;
            }
        }
    
        break;
    }
    }

    if (result == 0)
    {
        m_txWordIndex[threadParam->m_portIndex]++;

        if (m_txWordIndex[threadParam->m_portIndex] >= m_txWordCount[threadParam->m_portIndex])
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
    unsigned int port;
    int result = 0;
    unsigned char subState = threadParam->m_subState;

    switch (subState)
    {
    case 0:
    {
            m_txWordIndex[threadParam->m_portIndex] = 0;

            unsigned char payload[1 + 779];

            memset(payload, 0, kJoyDataLargePayloadClearBytes);
            ClearJoyDataPacketPayload(this, threadParam->m_portIndex);

            payload[0] = 0x0c;

            unsigned char* cmdBuf = &payload[1];

            int byteLen = GbaQue.GetCmdData(threadParam->m_portIndex, cmdBuf) + 1;

            int wordCount = MakeJoyData((char*)payload, byteLen, (unsigned int*)(m_joyDataPacketBuffer[threadParam->m_portIndex] + 2));

            if (wordCount < 0)
            {
                return wordCount;
            }

            m_txWordCount[threadParam->m_portIndex] = wordCount;

            threadParam->m_subState = (unsigned char)(threadParam->m_subState + 1);

            port = threadParam->m_portIndex;
            unsigned int word = *(unsigned int*)&m_joyDataPacketBuffer[port][2 + m_txWordIndex[port] * 4];

            if (static_cast<signed char>(m_threadRunningMask) == 0)
            {
                result = 0;
            }
            else
            {
                OSWaitSemaphore(&m_accessSemaphores[port]);

                port = threadParam->m_portIndex;
                if ((int)m_cmdCount[port] >= 0x40)
                {
                    OSSignalSemaphore(&m_accessSemaphores[port]);
                    result = -1;
                }
                else
                {
                    m_cmdQueueData[port][m_cmdCount[port]] = word;
                    m_cmdCount[threadParam->m_portIndex]++;

                    OSSignalSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);
                    result = 0;
                }
            }
        
        break;
    }
    case 1:
    {
        port = threadParam->m_portIndex;
        unsigned int word = *(unsigned int*)&m_joyDataPacketBuffer[port][2 + m_txWordIndex[port] * 4];

        if (static_cast<signed char>(m_threadRunningMask) == 0)
        {
            result = 0;
        }
        else
        {
            OSWaitSemaphore(&m_accessSemaphores[port]);

            port = threadParam->m_portIndex;
            if ((int)m_cmdCount[port] >= 0x40)
            {
                OSSignalSemaphore(&m_accessSemaphores[port]);
                result = -1;
            }
            else
            {
                m_cmdQueueData[port][m_cmdCount[port]] = word;
                m_cmdCount[threadParam->m_portIndex]++;

                OSSignalSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);
                result = 0;
            }
        }
    
        break;
    }
    }

    if (result == 0)
    {
        m_txWordIndex[threadParam->m_portIndex]++;

        if (m_txWordIndex[threadParam->m_portIndex] >= m_txWordCount[threadParam->m_portIndex])
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
    unsigned int port;
    int result = 0;
    unsigned char subState = threadParam->m_subState;

    switch (subState)
    {
    case 0:
    {
            m_txWordIndex[threadParam->m_portIndex] = 0;

            unsigned char payload[1 + 1 + 258];

            memset(payload, 0, kJoyDataSmallPayloadClearBytes);
            ClearJoyDataPacketPayload(this, threadParam->m_portIndex);

            payload[0] = 7;

            unsigned char* bonusStr = &payload[1];
            unsigned char* extraBuf = &payload[2];

            int byteLen;
            if (Game.m_gameWork.m_bossArtifactStageIndex < 0xE)
            {
                unsigned int bonusPort;
                if (GbaQue.IsSingleMode(threadParam->m_portIndex) && (int)threadParam->m_portIndex == 1)
                {
                    bonusPort = 0;
                }
                else
                {
                    bonusPort = threadParam->m_portIndex;
                }

                int bonusIndex = GbaQue.GetBonus(bonusPort);
                char** bonusTable = Game.m_cFlatDataArr[1].TableStrings(7);
                strcpy((char*)bonusStr, bonusTable[bonusIndex * 2]);

                int firstLen = strlen((char*)bonusStr);
                strcpy((char*)extraBuf + firstLen, bonusTable[bonusIndex * 2 + 1]);

                int secondLen = strlen((char*)extraBuf + firstLen);
                byteLen = firstLen + secondLen + 3;
            }
            else
            {
                byteLen = 3;
                bonusStr[0] = 0;
                extraBuf[0] = 0;
            }

            int wordCount = MakeJoyData((char*)payload, byteLen, (unsigned int*)(m_joyDataPacketBuffer[threadParam->m_portIndex] + 2));

            if (wordCount < 0)
            {
                return wordCount;
            }

            m_txWordCount[threadParam->m_portIndex] = wordCount;

            threadParam->m_subState = (unsigned char)(threadParam->m_subState + 1);

            port = threadParam->m_portIndex;
            unsigned int word = *(unsigned int*)&m_joyDataPacketBuffer[port][2 + m_txWordIndex[port] * 4];

            if (static_cast<signed char>(m_threadRunningMask) == 0)
            {
                result = 0;
            }
            else
            {
                OSWaitSemaphore(&m_accessSemaphores[port]);

                port = threadParam->m_portIndex;
                if ((int)m_cmdCount[port] >= 0x40)
                {
                    OSSignalSemaphore(&m_accessSemaphores[port]);
                    result = -1;
                }
                else
                {
                    m_cmdQueueData[port][m_cmdCount[port]] = word;
                    m_cmdCount[threadParam->m_portIndex]++;

                    OSSignalSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);
                    result = 0;
                }
            }
        
        break;
    }
    case 1:
    {
        port = threadParam->m_portIndex;
        unsigned int word = *(unsigned int*)&m_joyDataPacketBuffer[port][2 + m_txWordIndex[port] * 4];

        if (static_cast<signed char>(m_threadRunningMask) == 0)
        {
            result = 0;
        }
        else
        {
            OSWaitSemaphore(&m_accessSemaphores[port]);

            port = threadParam->m_portIndex;
            if ((int)m_cmdCount[port] >= 0x40)
            {
                OSSignalSemaphore(&m_accessSemaphores[port]);
                result = -1;
            }
            else
            {
                m_cmdQueueData[port][m_cmdCount[port]] = word;
                m_cmdCount[threadParam->m_portIndex]++;

                OSSignalSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);
                result = 0;
            }
        }
    
        break;
    }
    }

    if (result == 0)
    {
        m_txWordIndex[threadParam->m_portIndex]++;

        if (m_txWordIndex[threadParam->m_portIndex] >= m_txWordCount[threadParam->m_portIndex])
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
    unsigned int port;
    int result = 0;
    unsigned char subState = threadParam->m_subState;

    switch (subState)
    {
    case 0:
    {
            m_txWordIndex[threadParam->m_portIndex] = 0;

            unsigned char payload[1 + 267];

            memset(payload, 0, kJoyDataSmallPayloadClearBytes);
            ClearJoyDataPacketPayload(this, threadParam->m_portIndex);

            payload[0] = 8;

            unsigned char* artiBuf = &payload[1];

            int byteLen = GbaQue.GetArtifactData(threadParam->m_portIndex, artiBuf) + 1;
            int wordCount = MakeJoyData((char*)payload, byteLen, (unsigned int*)(m_joyDataPacketBuffer[threadParam->m_portIndex] + 2));

            if (wordCount < 0)
            {
                return wordCount;
            }

            m_txWordCount[threadParam->m_portIndex] = wordCount;

            threadParam->m_subState = (unsigned char)(threadParam->m_subState + 1);

            port = threadParam->m_portIndex;
            unsigned int word = *(unsigned int*)&m_joyDataPacketBuffer[port][2 + m_txWordIndex[port] * 4];

            if (static_cast<signed char>(m_threadRunningMask) == 0)
            {
                result = 0;
            }
            else
            {
                OSWaitSemaphore(&m_accessSemaphores[port]);

                port = threadParam->m_portIndex;
                if ((int)m_cmdCount[port] >= 0x40)
                {
                    OSSignalSemaphore(&m_accessSemaphores[port]);
                    result = -1;
                }
                else
                {
                    m_cmdQueueData[port][m_cmdCount[port]] = word;
                    m_cmdCount[threadParam->m_portIndex]++;

                    OSSignalSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);
                    result = 0;
                }
            }
        
        break;
    }
    case 1:
    {
        port = threadParam->m_portIndex;
        unsigned int word = *(unsigned int*)&m_joyDataPacketBuffer[port][2 + m_txWordIndex[port] * 4];

        if (static_cast<signed char>(m_threadRunningMask) == 0)
        {
            result = 0;
        }
        else
        {
            OSWaitSemaphore(&m_accessSemaphores[port]);

            port = threadParam->m_portIndex;
            if ((int)m_cmdCount[port] >= 0x40)
            {
                OSSignalSemaphore(&m_accessSemaphores[port]);
                result = -1;
            }
            else
            {
                m_cmdQueueData[port][m_cmdCount[port]] = word;
                m_cmdCount[threadParam->m_portIndex]++;

                OSSignalSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);
                result = 0;
            }
        }
    
        break;
    }
    }

    if (result == 0)
    {
        m_txWordIndex[threadParam->m_portIndex]++;

        if (m_txWordIndex[threadParam->m_portIndex] >= m_txWordCount[threadParam->m_portIndex])
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
    unsigned int port;
    int result = 0;
    unsigned char subState = threadParam->m_subState;

    switch (subState)
    {
    case 0:
    {
            m_txWordIndex[threadParam->m_portIndex] = 0;

            unsigned char payload[1 + 267];

            memset(payload, 0, kJoyDataSmallPayloadClearBytes);
            ClearJoyDataPacketPayload(this, threadParam->m_portIndex);

            payload[0] = 9;

            unsigned char* artiBuf = &payload[1];

            int byteLen = GbaQue.GetTmpArtifactData(threadParam->m_portIndex, artiBuf) + 1;
            int wordCount = MakeJoyData((char*)payload, byteLen, (unsigned int*)(m_joyDataPacketBuffer[threadParam->m_portIndex] + 2));

            if (wordCount < 0)
            {
                return wordCount;
            }

            m_txWordCount[threadParam->m_portIndex] = wordCount;

            threadParam->m_subState = (unsigned char)(threadParam->m_subState + 1);

            port = threadParam->m_portIndex;
            unsigned int word = *(unsigned int*)&m_joyDataPacketBuffer[port][2 + m_txWordIndex[port] * 4];

            if (static_cast<signed char>(m_threadRunningMask) == 0)
            {
                result = 0;
            }
            else
            {
                OSWaitSemaphore(&m_accessSemaphores[port]);

                port = threadParam->m_portIndex;
                if ((int)m_cmdCount[port] >= 0x40)
                {
                    OSSignalSemaphore(&m_accessSemaphores[port]);
                    result = -1;
                }
                else
                {
                    m_cmdQueueData[port][m_cmdCount[port]] = word;
                    m_cmdCount[threadParam->m_portIndex]++;

                    OSSignalSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);
                    result = 0;
                }
            }
        
        break;
    }
    case 1:
    {
        port = threadParam->m_portIndex;
        unsigned int word = *(unsigned int*)&m_joyDataPacketBuffer[port][2 + m_txWordIndex[port] * 4];

        if (static_cast<signed char>(m_threadRunningMask) == 0)
        {
            result = 0;
        }
        else
        {
            OSWaitSemaphore(&m_accessSemaphores[port]);

            port = threadParam->m_portIndex;
            if ((int)m_cmdCount[port] >= 0x40)
            {
                OSSignalSemaphore(&m_accessSemaphores[port]);
                result = -1;
            }
            else
            {
                m_cmdQueueData[port][m_cmdCount[port]] = word;
                m_cmdCount[threadParam->m_portIndex]++;

                OSSignalSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);
                result = 0;
            }
        }
    
        break;
    }
    }

    if (result == 0)
    {
        m_txWordIndex[threadParam->m_portIndex]++;

        if (m_txWordIndex[threadParam->m_portIndex] >= m_txWordCount[threadParam->m_portIndex])
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
    unsigned int port;
    int result = 0;
    unsigned char subState = threadParam->m_subState;

    switch (subState)
    {
    case 0:
    {
            m_txWordIndex[threadParam->m_portIndex] = 0;

            unsigned char payload[268];

            memset(payload, 0, kJoyDataSmallPayloadClearBytes);
            ClearJoyDataPacketPayload(this, threadParam->m_portIndex);

            payload[0] = 10;

            unsigned char* mapObjBuf = &payload[1];

            int byteLen = GbaQue.GetMapObjInfo(threadParam->m_portIndex, mapObjBuf) + 1;

            int wordCount = MakeJoyData(
                (char*)payload,
                byteLen,
                (unsigned int*)(m_joyDataPacketBuffer[threadParam->m_portIndex] + 2)
            );

            if (wordCount < 0)
            {
                return wordCount;
            }

            m_txWordCount[threadParam->m_portIndex] = wordCount;
            threadParam->m_subState = (unsigned char)(threadParam->m_subState + 1);

            port = threadParam->m_portIndex;
            unsigned int word = *(unsigned int*)&m_joyDataPacketBuffer[port][2 + m_txWordIndex[port] * 4];

            if (static_cast<signed char>(m_threadRunningMask) == 0)
            {
                result = 0;
            }
            else
            {
                OSWaitSemaphore(&m_accessSemaphores[port]);

                port = threadParam->m_portIndex;
                if ((int)m_cmdCount[port] >= 0x40)
                {
                    OSSignalSemaphore(&m_accessSemaphores[port]);
                    result = -1;
                }
                else
                {
                    m_cmdQueueData[port][m_cmdCount[port]] = word;
                    m_cmdCount[threadParam->m_portIndex]++;

                    OSSignalSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);
                    result = 0;
                }
            }
        
        break;
    }
    case 1:
    {
        port = threadParam->m_portIndex;
        unsigned int word = *(unsigned int*)&m_joyDataPacketBuffer[port][2 + m_txWordIndex[port] * 4];

        if (static_cast<signed char>(m_threadRunningMask) == 0)
        {
            result = 0;
        }
        else
        {
            OSWaitSemaphore(&m_accessSemaphores[port]);

            port = threadParam->m_portIndex;
            if ((int)m_cmdCount[port] >= 0x40)
            {
                OSSignalSemaphore(&m_accessSemaphores[port]);
                result = -1;
            }
            else
            {
                m_cmdQueueData[port][m_cmdCount[port]] = word;
                m_cmdCount[threadParam->m_portIndex]++;

                OSSignalSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);
                result = 0;
            }
        }
    
        break;
    }
    }

    if (result == 0)
    {
        m_txWordIndex[threadParam->m_portIndex]++;

        if (m_txWordIndex[threadParam->m_portIndex] >= m_txWordCount[threadParam->m_portIndex])
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
    unsigned int cmd = 0;
    unsigned char* cmdBytes = (unsigned char*)&cmd;
    unsigned char strength[3];

    GbaQue.GetStrengthData(threadParam->m_portIndex, strength);

    cmdBytes[0] = 0x19;
    cmdBytes[1] = strength[0];
    cmdBytes[2] = strength[1];
    cmdBytes[3] = strength[2];
    unsigned int word = cmd;

    if (static_cast<signed char>(m_threadRunningMask) == 0)
	{
        return 0;
	}

    OSWaitSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);

    int result = 0;

    unsigned int queuePort = threadParam->m_portIndex;
    if ((int)m_cmdCount[queuePort] >= 0x40)
    {
        OSSignalSemaphore(&m_accessSemaphores[queuePort]);
        result = -1;
    }
    else
    {
        m_cmdQueueData[queuePort][m_cmdCount[queuePort]] = word;
        m_cmdCount[threadParam->m_portIndex]++;
        OSSignalSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);
        result = 0;
    }

    return result;
}


/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::SendRaderType(ThreadParam* threadParam)
{
    unsigned int cmd = 0;
    unsigned char* cmdBytes = (unsigned char*)&cmd;
    cmdBytes[0] = 0x14;
    cmdBytes[1] = 0x0D;
    cmdBytes[2] = GbaQue.GetRadarType(threadParam->m_portIndex);
    unsigned int word = cmd;

    if (static_cast<signed char>(m_threadRunningMask) == 0)
    {
        return 0;
    }

    OSWaitSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);

    int result = 0;

    unsigned int queuePort = threadParam->m_portIndex;
    if ((int)m_cmdCount[queuePort] >= 0x40)
    {
        OSSignalSemaphore(&m_accessSemaphores[queuePort]);
        result = -1;
    }
    else
    {
        m_cmdQueueData[queuePort][m_cmdCount[queuePort]] = word;
        m_cmdCount[threadParam->m_portIndex]++;
        OSSignalSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);
        result = 0;
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
    unsigned int cmd = 0;
    unsigned char* cmdBytes = (unsigned char*)&cmd;
    cmdBytes[0] = 0x14;
    cmdBytes[1] = 0x0E;
    cmdBytes[2] = GbaQue.GetRadarMode(threadParam->m_portIndex);
    unsigned int word = cmd;

    if (static_cast<signed char>(m_threadRunningMask) == 0)
    {
        return 0;
    }

    OSWaitSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);

    int result = 0;

    unsigned int queuePort = threadParam->m_portIndex;
    if ((int)m_cmdCount[queuePort] >= 0x40)
    {
        OSSignalSemaphore(&m_accessSemaphores[queuePort]);
        result = -1;
    }
    else
    {
        m_cmdQueueData[queuePort][m_cmdCount[queuePort]] = word;
        m_cmdCount[threadParam->m_portIndex]++;
        OSSignalSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);
        result = 0;
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
    unsigned int port;
    int result = 0;
    unsigned char subState = threadParam->m_subState;

    switch (subState)
    {
    case 0:
    {
            m_txWordIndex[threadParam->m_portIndex] = 0;

            unsigned char payload[0x400];
            memset(payload, 0, sizeof(payload));

            ClearJoyDataPacketPayload(this, threadParam->m_portIndex);

            payload[0] = 0x0B;

            unsigned char* scouterBuf = &payload[1];

            int byteLen = GbaQue.GetScouterInfo(threadParam->m_portIndex, scouterBuf) + 1;

            int wordCount = MakeJoyData((char*)payload, byteLen, (unsigned int*)(void*)(m_joyDataPacketBuffer[threadParam->m_portIndex] + 2));

            if (wordCount < 0)
            {
                return wordCount;
            }

            m_txWordCount[threadParam->m_portIndex] = wordCount;
            threadParam->m_subState = (unsigned char)(threadParam->m_subState + 1);

            port = threadParam->m_portIndex;
            unsigned int word = *(unsigned int*)&m_joyDataPacketBuffer[port][2 + m_txWordIndex[port] * 4];

            if (static_cast<signed char>(m_threadRunningMask) == 0)
            {
                result = 0;
            }
            else
            {
                OSWaitSemaphore(&m_accessSemaphores[port]);

                port = threadParam->m_portIndex;
                if ((int)m_cmdCount[port] >= 0x40)
                {
                    OSSignalSemaphore(&m_accessSemaphores[port]);
                    result = -1;
                }
                else
                {
                    m_cmdQueueData[port][m_cmdCount[port]] = word;
                    m_cmdCount[threadParam->m_portIndex]++;

                    OSSignalSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);
                    result = 0;
                }
            }
        
        break;
    }
    case 1:
    {
        port = threadParam->m_portIndex;
        unsigned int word = *(unsigned int*)&m_joyDataPacketBuffer[port][2 + m_txWordIndex[port] * 4];

        if (static_cast<signed char>(m_threadRunningMask) == 0)
        {
            result = 0;
        }
        else
        {
            OSWaitSemaphore(&m_accessSemaphores[port]);

            port = threadParam->m_portIndex;
            if ((int)m_cmdCount[port] >= 0x40)
            {
                OSSignalSemaphore(&m_accessSemaphores[port]);
                result = -1;
            }
            else
            {
                m_cmdQueueData[port][m_cmdCount[port]] = word;
                m_cmdCount[threadParam->m_portIndex]++;

                OSSignalSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);
                result = 0;
            }
        }
    
        break;
    }
    }

    if (result == 0)
    {
        m_txWordIndex[threadParam->m_portIndex]++;

        if (m_txWordIndex[threadParam->m_portIndex] >= m_txWordCount[threadParam->m_portIndex])
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
    unsigned int cmd = 0;

    bool isSingle = GbaQue.IsSingleMode(threadParam->m_portIndex);

    if (isSingle)
	{
        return 0;
	}

    // Command: [0x14][0x0F][menuId][0]
    unsigned char* cmdBytes = reinterpret_cast<unsigned char*>(&cmd);
    cmdBytes[0] = 0x14;
    cmdBytes[1] = 0x0F;
    cmdBytes[2] = menuId;
    unsigned int word = cmd;

    if (static_cast<signed char>(m_threadRunningMask) == 0)
    {
        return 0;
    }

    OSWaitSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);

    int result = 0;

    unsigned int queuePort = threadParam->m_portIndex;
    if ((int)m_cmdCount[queuePort] >= 0x40)
    {
        OSSignalSemaphore(&m_accessSemaphores[queuePort]);
        result = -1;
    }
    else
    {
        m_cmdQueueData[queuePort][m_cmdCount[queuePort]] = word;
        m_cmdCount[threadParam->m_portIndex]++;
        OSSignalSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);
        result = 0;
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
    unsigned int cmd = 0;

    bool isSingle = GbaQue.IsSingleMode(threadParam->m_portIndex);

    if (isSingle)
    {
        return 0;
    }

    unsigned char itemId = GbaQue.GetItemUse(threadParam->m_portIndex);

    unsigned char* cmdBytes = reinterpret_cast<unsigned char*>(&cmd);
    cmdBytes[0] = 0x14;
    cmdBytes[1] = 0x10;
    cmdBytes[2] = itemId;
    unsigned int word = cmd;

    if (static_cast<signed char>(m_threadRunningMask) == 0)
    {
        return 0;
    }

    OSWaitSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);

    int result = 0;

    unsigned int queuePort = threadParam->m_portIndex;
    if (static_cast<int>(m_cmdCount[queuePort]) >= 0x40)
    {
        OSSignalSemaphore(&m_accessSemaphores[queuePort]);
        result = -1;
    }
    else
    {
        m_cmdQueueData[queuePort][m_cmdCount[queuePort]] = word;
        m_cmdCount[threadParam->m_portIndex]++;
        OSSignalSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);
        result = 0;
    }

    return result;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::SendSPMode(ThreadParam* threadParam)
{
    unsigned int cmd = 0;
    unsigned char* cmdBytes = (unsigned char*)&cmd;
    unsigned int mode = GbaQue.GetSPMode(threadParam->m_portIndex) & 0xFF;
    const unsigned char bVar1 = (unsigned char)(((unsigned int)(-(int)mode | (int)mode)) >> 31);
    cmdBytes[0] = 0x14;
    cmdBytes[1] = 0x11;
    cmdBytes[2] = bVar1;
    unsigned int cmdWord = cmd;
    int result;

    if (static_cast<signed char>(m_threadRunningMask) == 0)
    {
        result = 0;
    }
    else
    {
        OSWaitSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);

        unsigned int queuePort = threadParam->m_portIndex;
        if ((int)m_cmdCount[queuePort] >= 0x40)
        {
            OSSignalSemaphore(&m_accessSemaphores[queuePort]);
            result = -1;
        }
        else
        {
            m_cmdQueueData[queuePort][m_cmdCount[queuePort]] = cmdWord;
            m_cmdCount[threadParam->m_portIndex]++;
            OSSignalSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);
            result = 0;
        }
    }

    // On success, update the threadParam flags
    if (result == 0)
    {
        threadParam->m_flags[6] = bVar1;
    }

    return result;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::SendMemorys(ThreadParam* threadParam)
{
    unsigned int cmd = 0;
    unsigned char* cmdBytes = (unsigned char*)&cmd;
    unsigned char value = GbaQue.GetMemorys(threadParam->m_portIndex);
    cmdBytes[0] = 0x14;
    cmdBytes[1] = 0x13;
    cmdBytes[2] = value;
    unsigned int word = cmd;

    if (static_cast<signed char>(m_threadRunningMask) == 0)
	{
        return 0;
	}

    OSWaitSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);

    int result = 0;

    unsigned int queuePort = threadParam->m_portIndex;
    if ((int)m_cmdCount[queuePort] >= 0x40)
    {
        OSSignalSemaphore(&m_accessSemaphores[queuePort]);
        result = -1;
    }
    else
    {
        m_cmdQueueData[queuePort][m_cmdCount[queuePort]] = word;
        m_cmdCount[threadParam->m_portIndex]++;
        OSSignalSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);
        result = 0;
    }

    return result;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::SendChgCmdNum(ThreadParam* threadParam)
{
    unsigned int cmd = 0;
    unsigned char* cmdBytes = reinterpret_cast<unsigned char*>(&cmd);
    unsigned char cmdNum = GbaQue.GetCmdNum(threadParam->m_portIndex);
    cmdBytes[0] = 0x14;
    cmdBytes[1] = 0x12;
    cmdBytes[2] = cmdNum;
    unsigned int word = cmd;

    if (static_cast<signed char>(m_threadRunningMask) == 0)
    {
        return 0;
    }

    OSWaitSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);

    int result = 0;

    unsigned int queuePort = threadParam->m_portIndex;
    if (static_cast<int>(m_cmdCount[queuePort]) >= 0x40)
    {
        OSSignalSemaphore(&m_accessSemaphores[queuePort]);
        result = -1;
    }
    else
    {
        m_cmdQueueData[queuePort][m_cmdCount[queuePort]] = word;
        m_cmdCount[threadParam->m_portIndex]++;
        OSSignalSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);
        result = 0;
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
    unsigned int cmd = 0;
    unsigned char* cmdBytes = reinterpret_cast<unsigned char*>(&cmd);
    cmdBytes[0] = 0x14;
    cmdBytes[1] = 0x14;
    unsigned int word = cmd;
    unsigned int result = 0;

    if (static_cast<signed char>(m_threadRunningMask) == 0)
    {
        return result;
    }

    OSWaitSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);

    unsigned int queuePort = threadParam->m_portIndex;
    if ((int)m_cmdCount[queuePort] >= 0x40)
    {
        OSSignalSemaphore(&m_accessSemaphores[queuePort]);
        result = 0xFFFFFFFF;
    }
    else
    {
        m_cmdQueueData[queuePort][m_cmdCount[queuePort]] = word;
        m_cmdCount[threadParam->m_portIndex]++;
        OSSignalSemaphore(&m_accessSemaphores[threadParam->m_portIndex]);
        result = 0;
    }

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

    if (single && static_cast<int>(threadParam->m_portIndex) != 1)
    {
        threadParam->m_gbaStatus = 0;
    }
    else
    {
        threadParam->m_gbaStatus = GBAGetStatus(threadParam->m_portIndex, &threadParam->m_unk3);
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
    unsigned int word = 0;
    unsigned char* wordBytes = reinterpret_cast<unsigned char*>(&word);
    unsigned char mode = m_ctrlModeArr[portIndex];

    if (GbaQue.IsSingleMode(portIndex))
    {
        return 0;
    }

    unsigned int x = mode ^ kPppYmMeltMaskBit0;
    wordBytes[0] = 0x09;
    wordBytes[1] = (unsigned char)x;
    mode = (unsigned char)x;
    unsigned int wordCache = word;
    int ret = 0;

    if (static_cast<signed char>(m_threadRunningMask) != 0)
    {
        OSWaitSemaphore(&m_accessSemaphores[m_threadParams[portIndex].m_portIndex]);

        unsigned int queuePort = m_threadParams[portIndex].m_portIndex;
        if ((int)m_cmdCount[queuePort] >= 0x40)
        {
            OSSignalSemaphore(&m_accessSemaphores[queuePort]);
            ret = -1;
        }
        else
        {
            m_cmdQueueData[queuePort][m_cmdCount[queuePort]] = wordCache;
            queuePort = m_threadParams[portIndex].m_portIndex;
            m_cmdCount[queuePort] = m_cmdCount[queuePort] + 1;

            OSSignalSemaphore(&m_accessSemaphores[m_threadParams[portIndex].m_portIndex]);
            ret = 0;
        }
    }

    if (ret == 0)
    {
        m_ctrlModeArr[portIndex] = mode;
    }

    return ret;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::SetCtrlMode(int portIndex, int controlMode)
{
    if (GbaQue.IsSingleMode(portIndex))
	{
        return 0;
	}

    unsigned char modeFlag =
        (unsigned char)(((unsigned int)(controlMode | -controlMode)) >> 31);

    unsigned int cmd = 0;
    unsigned char* cmdBytes = reinterpret_cast<unsigned char*>(&cmd);

    bool isSinglePort = GbaQue.IsSingleMode(m_threadParams[portIndex].m_portIndex);

    if (isSinglePort)
	{
        modeFlag = 0;
	}

    cmdBytes[0] = 0x09;
    cmdBytes[1] = modeFlag;
    unsigned int cmdWord = cmd;

    int result;

    if (static_cast<signed char>(m_threadRunningMask) == 0)
    {
        result = 0;
    }
    else
    {
        OSWaitSemaphore(&m_accessSemaphores[m_threadParams[portIndex].m_portIndex]);

        if ((int)m_cmdCount[m_threadParams[portIndex].m_portIndex] >= 0x40)
        {
            OSSignalSemaphore(&m_accessSemaphores[m_threadParams[portIndex].m_portIndex]);
            result = -1;
        }
        else
        {
            m_cmdQueueData[m_threadParams[portIndex].m_portIndex][m_cmdCount[m_threadParams[portIndex].m_portIndex]] = cmdWord;
            m_cmdCount[m_threadParams[portIndex].m_portIndex]++;
            OSSignalSemaphore(&m_accessSemaphores[m_threadParams[portIndex].m_portIndex]);
            result = 0;
        }
    }

    // If successful, update local mode tracking
    if (result == 0)
    {
        m_ctrlModeArr[m_threadParams[portIndex].m_portIndex] = modeFlag;
    }

    return result;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::GetCtrlMode(int portIndex)
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

    OSWaitSemaphore(&m_accessSemaphores[portIndex]);
    int state = m_threadParams[portIndex].m_state;
    OSSignalSemaphore(&m_accessSemaphores[portIndex]);

    unsigned int result = 0;

    // Determine desired "init send" state
    if (m_threadParams[portIndex].m_sentStartFlag == 0 && state <= 0x384)
    {
        if (state < 2)
        {
            result = 0;
        }
        else if (state == 2)
        {
            result = (m_threadParams[portIndex].m_flags[0] ? 1 : 0);
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
    if (m_threadParams[portIndex].m_flags[2] == result)
    {
        m_threadParams[portIndex].m_flags[3] = 0;
    }
    else
    {
        unsigned char cnt = m_threadParams[portIndex].m_flags[3];

        if (cnt < 8)
        {
            m_threadParams[portIndex].m_flags[3] = cnt + 1;
            result = m_threadParams[portIndex].m_flags[2];
        }
        else
        {
            m_threadParams[portIndex].m_flags[2] = (unsigned char)result;
            m_threadParams[portIndex].m_flags[3] = 0;
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

    int ready = static_cast<unsigned int>(__cntlzw(0x40000 - padType)) >> 5;
    bool isSingle = GbaQue.IsSingleMode(portIndex);

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
    m_threadParams[portIndex].m_state = 0;
    m_threadParams[portIndex].m_altState = 0;

    OSWaitSemaphore(&m_accessSemaphores[m_threadParams[portIndex].m_portIndex]);

    int wordOffset = 0;

    for (int i = 0; i < 8; i++)
    {
        m_cmdQueueData[m_threadParams[portIndex].m_portIndex][wordOffset + 0] = 0;
        m_recvQueueEntriesArr[m_threadParams[portIndex].m_portIndex][wordOffset + 0] = 0;
        m_cmdQueueData[m_threadParams[portIndex].m_portIndex][wordOffset + 1] = 0;
        m_recvQueueEntriesArr[m_threadParams[portIndex].m_portIndex][wordOffset + 1] = 0;
        m_cmdQueueData[m_threadParams[portIndex].m_portIndex][wordOffset + 2] = 0;
        m_recvQueueEntriesArr[m_threadParams[portIndex].m_portIndex][wordOffset + 2] = 0;
        m_cmdQueueData[m_threadParams[portIndex].m_portIndex][wordOffset + 3] = 0;
        m_recvQueueEntriesArr[m_threadParams[portIndex].m_portIndex][wordOffset + 3] = 0;
        m_cmdQueueData[m_threadParams[portIndex].m_portIndex][wordOffset + 4] = 0;
        m_recvQueueEntriesArr[m_threadParams[portIndex].m_portIndex][wordOffset + 4] = 0;
        m_cmdQueueData[m_threadParams[portIndex].m_portIndex][wordOffset + 5] = 0;
        m_recvQueueEntriesArr[m_threadParams[portIndex].m_portIndex][wordOffset + 5] = 0;
        m_cmdQueueData[m_threadParams[portIndex].m_portIndex][wordOffset + 6] = 0;
        m_recvQueueEntriesArr[m_threadParams[portIndex].m_portIndex][wordOffset + 6] = 0;
        m_cmdQueueData[m_threadParams[portIndex].m_portIndex][wordOffset + 7] = 0;
        m_recvQueueEntriesArr[m_threadParams[portIndex].m_portIndex][wordOffset + 7] = 0;

        wordOffset += 8;
    }

    m_cmdCount[m_threadParams[portIndex].m_portIndex] = 0;
    m_secCmdCount[m_threadParams[portIndex].m_portIndex] = 0;

    OSSignalSemaphore(&m_accessSemaphores[m_threadParams[portIndex].m_portIndex]);

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
    unsigned char a = static_cast<signed char>(param4);
    unsigned char b = static_cast<unsigned char>(param5);
    unsigned char firstByte = (param3 == 0) ? 6 : 7;

    unsigned int cmd = 0;
    unsigned char* cmdBytes = reinterpret_cast<unsigned char*>(&cmd);
    cmdBytes[0] = firstByte;
    cmdBytes[1] = a;
    cmdBytes[2] = b;
    unsigned int word = cmd;

    int result = 0;

    if (static_cast<signed char>(m_threadRunningMask) == 0)
    {
        return result;
    }

    OSWaitSemaphore(&m_accessSemaphores[m_threadParams[portIndex].m_portIndex]);

    unsigned int queuePort = m_threadParams[portIndex].m_portIndex;
    if (static_cast<int>(m_cmdCount[queuePort]) >= 0x40)
    {
        OSSignalSemaphore(&m_accessSemaphores[queuePort]);
        result = -1;
    }
    else
    {
        m_cmdQueueData[queuePort][m_cmdCount[queuePort]] = word;
        m_cmdCount[m_threadParams[portIndex].m_portIndex]++;
        OSSignalSemaphore(&m_accessSemaphores[m_threadParams[portIndex].m_portIndex]);
        result = 0;
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
    int result;
    unsigned int cmd = 0;
    unsigned char* cmdBytes = reinterpret_cast<unsigned char*>(&cmd);
    cmdBytes[0] = 0x14;
    cmdBytes[1] = 1;
    unsigned int cmdWord = cmd;

    if (static_cast<signed char>(m_threadRunningMask) == 0)
    {
        result = 0;
    }
    else
    {
        OSWaitSemaphore(m_accessSemaphores + m_threadParams[portIndex].m_portIndex);

        port = m_threadParams[portIndex].m_portIndex;
        if ((int)m_cmdCount[port] >= 0x40)
        {
            OSSignalSemaphore(m_accessSemaphores + port);
            result = -1;
        }
        else
        {
            m_cmdQueueData[port][ m_cmdCount[port] ] = cmdWord;
            port = m_threadParams[portIndex].m_portIndex;
            m_cmdCount[port]++;

            OSSignalSemaphore(m_accessSemaphores + m_threadParams[portIndex].m_portIndex);
            result = 0;
        }
    }

    return result;
}



/*
 * --INFO--
 * PAL Address: 0x800b014c
 * PAL Size: 256b
 * EN Address: 0x800c4cd8
 * EN Size: 172b
 * JP Address: TODO
 * JP Size: TODO
 */
int JoyBus::SetItem(int portIndex, unsigned char itemId, short amount)
{
    unsigned char cmdBytes[4];
    unsigned short amountBytes = amount;
    itemId &= 0x3F;
    cmdBytes[0] = 0x17;
    cmdBytes[1] = itemId;
    *reinterpret_cast<unsigned short*>(cmdBytes + 2) = __lhbrx(&amountBytes, 0);
    unsigned int cmd = *reinterpret_cast<unsigned int*>(cmdBytes);
    unsigned int port;
    unsigned int result;

    if (static_cast<signed char>(m_threadRunningMask) == 0)
    {
        result = 0;
    }
    else
    {
        OSWaitSemaphore(m_accessSemaphores + m_threadParams[portIndex].m_portIndex);

        port = m_threadParams[portIndex].m_portIndex;
        if ((int)m_cmdCount[port] >= 0x40)
        {
            OSSignalSemaphore(m_accessSemaphores + port);
            result = 0xFFFFFFFF;
        }
        else
        {
            m_cmdQueueData[port][m_cmdCount[port]] = cmd;
            port = m_threadParams[portIndex].m_portIndex;
            m_cmdCount[port]++;
            OSSignalSemaphore(m_accessSemaphores + m_threadParams[portIndex].m_portIndex);
            result = 0;
        }
    }

    return result;
}

/*
 * --INFO--
 * PAL Address: 0x800b0048
 * PAL Size: 260b
 * EN Address: 0x800c4d84
 * EN Size: 60b
 * JP Address: TODO
 * JP Size: TODO
 */
int JoyBus::DelItem(int portIndex, unsigned char itemId)
{
    unsigned char cmdBytes[4];
    short tail = -1;
    cmdBytes[0] = 0x17;
    cmdBytes[1] = itemId & 0x3F;
    *reinterpret_cast<unsigned short*>(cmdBytes + 2) = __lhbrx(reinterpret_cast<unsigned short*>(&tail), 0);
    unsigned int cmd = *reinterpret_cast<unsigned int*>(cmdBytes);
    unsigned int port;
    int result;

    if (static_cast<signed char>(m_threadRunningMask) == 0)
    {
        result = 0;
    }
    else
    {
        OSWaitSemaphore(m_accessSemaphores + m_threadParams[portIndex].m_portIndex);

        port = m_threadParams[portIndex].m_portIndex;
        if ((int)m_cmdCount[port] >= 0x40)
        {
            OSSignalSemaphore(m_accessSemaphores + port);
            result = -1;
        }
        else
        {
            m_cmdQueueData[port][m_cmdCount[port]] = cmd;
            port = m_threadParams[portIndex].m_portIndex;
            m_cmdCount[port]++;
            OSSignalSemaphore(m_accessSemaphores + m_threadParams[portIndex].m_portIndex);
            result = 0;
        }
    }

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
    unsigned int cmd = 0;
    unsigned char* cmdBytes = reinterpret_cast<unsigned char*>(&cmd);

	// TODO: This 3E check feels like a < 40 check in shorts (ie size 20, cmp < 20). Might need to unfuck some of this.

    // Need room for *two* commands (this early check is against the caller's portIndex)
    if ((int)m_cmdCount[portIndex] >= 0x3E)
	{
        return -1;
    }

	{
		cmdBytes[0] = 0x1A;
		cmdBytes[1] = 0;
		cmdBytes[2] = money >> 24;
		cmdBytes[3] = money >> 16;
		unsigned int word = cmd;

		if (static_cast<signed char>(m_threadRunningMask) != 0)
		{

			OSWaitSemaphore(&m_accessSemaphores[m_threadParams[portIndex].m_portIndex]);

			if ((int)m_cmdCount[m_threadParams[portIndex].m_portIndex] >= 0x40)
			{
				OSSignalSemaphore(&m_accessSemaphores[m_threadParams[portIndex].m_portIndex]);
				result = -1;
			}
			else
			{
				m_cmdQueueData[m_threadParams[portIndex].m_portIndex][m_cmdCount[m_threadParams[portIndex].m_portIndex]] = word;
				m_cmdCount[m_threadParams[portIndex].m_portIndex]++;
				OSSignalSemaphore(&m_accessSemaphores[m_threadParams[portIndex].m_portIndex]);
				result = 0;
			}
		}

		if (result != 0)
		{
			return result;
		}
	}

	{
		cmd = 0;
		cmdBytes[0] = 0x5A;
		cmdBytes[1] = money >> 8;
		cmdBytes[2] = money;
		unsigned int word = cmd;

		if (static_cast<signed char>(m_threadRunningMask) != 0)
		{

			OSWaitSemaphore(&m_accessSemaphores[m_threadParams[portIndex].m_portIndex]);

			if ((int)m_cmdCount[m_threadParams[portIndex].m_portIndex] >= 0x40)
			{
				OSSignalSemaphore(&m_accessSemaphores[m_threadParams[portIndex].m_portIndex]);
				result = -1;
			}
			else
			{
				m_cmdQueueData[m_threadParams[portIndex].m_portIndex][m_cmdCount[m_threadParams[portIndex].m_portIndex]] = word;
				m_cmdCount[m_threadParams[portIndex].m_portIndex]++;
				OSSignalSemaphore(&m_accessSemaphores[m_threadParams[portIndex].m_portIndex]);
				result = 0;
			}
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
    int state;

    OSWaitSemaphore(&m_accessSemaphores[portIndex]);
    state = m_threadParams[portIndex].m_state;
    OSSignalSemaphore(&m_accessSemaphores[portIndex]);

    if (state <= 4)
	{
        return -1;
    }
	if (state >= 0x14 && state <= 0x16)
	{
        return -1;
    }
    if (state >= 900)
    {
        return -1;
    }
    return SendMType(&m_threadParams[portIndex], mtype);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
unsigned char JoyBus::GetMType(int portIndex)
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
    return (signed char)m_threadRunningMask != 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::RestartThread()
{
    m_threadInitFlag = 0;
    CreateInit();
    int err = 0;

    if (static_cast<signed char>(Joybus.m_binLoaded) == 0)
    {
        CFile::CHandle* file = File.Open((char*)&Joybus, 0, CFile::PRI_LOW);

        if (file == 0)
        {
            if ((unsigned int)System.m_execParam >= 2)
                System.Printf(const_cast<char*>(s_not_found_error_fmt), (char*)&Joybus);

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
                (signed char)(
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
        System.Printf(const_cast<char*>(s_load_bin_error));
	}

    memset(Joybus.m_threadParams, 0, sizeof(Joybus.m_threadParams));

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
        System.Printf(const_cast<char*>(s_thread_init_end));
}

/*
 * --INFO--
 * PAL Address: 0x800af830
 * PAL Size: 260b
 * EN Address: 0x800c50f8
 * EN Size: 160b
 * JP Address: TODO
 * JP Size: TODO
 */
int JoyBus::SetCmdLst(int portIndex, int param_3, short param_4)
{
    unsigned int cmd = 0;
    unsigned char* cmdBytes = reinterpret_cast<unsigned char*>(&cmd);
    unsigned short param = param_4;
    cmdBytes[0] = 0x1F;
    cmdBytes[1] = static_cast<unsigned char>(param_3);
    *reinterpret_cast<unsigned short*>(cmdBytes + 2) = __lhbrx(&param, 0);
    unsigned int cmdWord = cmd;
    unsigned int result;

    if (static_cast<signed char>(m_threadRunningMask) == 0)
    {
        result = 0;
    }
    else
    {
        OSWaitSemaphore(m_accessSemaphores + m_threadParams[portIndex].m_portIndex);

        unsigned int port = m_threadParams[portIndex].m_portIndex;
        if ((int)m_cmdCount[port] >= 0x40)
        {
            OSSignalSemaphore(m_accessSemaphores + port);
            result = 0xFFFFFFFF;
        }
        else
        {
            m_cmdQueueData[port][m_cmdCount[port]] = cmdWord;
            port = m_threadParams[portIndex].m_portIndex;
            m_cmdCount[port]++;
            OSSignalSemaphore(m_accessSemaphores + m_threadParams[portIndex].m_portIndex);
            result = 0;
        }
    }

    return result;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::SetTmpArti(int portIndex, int param3, int param4)
{
    unsigned int cmd = 0;
    unsigned char* cmdBytes = reinterpret_cast<unsigned char*>(&cmd);
    cmdBytes[0] = 0x20;
    cmdBytes[1] = static_cast<unsigned char>(param3);
    cmdBytes[2] = static_cast<unsigned char>(param4 - 0x9f);
    unsigned int word = cmd;
    unsigned int port;

    if (static_cast<signed char>(m_threadRunningMask) == 0)
    {
        return 0;
    }

    OSWaitSemaphore(m_accessSemaphores + m_threadParams[portIndex].m_portIndex);

    int result = 0;

    port = m_threadParams[portIndex].m_portIndex;
    if ((int)m_cmdCount[port] >= 0x40)
    {
        OSSignalSemaphore(m_accessSemaphores + port);
        result = -1;
    }
    else
    {
        m_cmdQueueData[port][m_cmdCount[port]] = word;
        port = m_threadParams[portIndex].m_portIndex;
        m_cmdCount[port]++;
        OSSignalSemaphore(m_accessSemaphores + m_threadParams[portIndex].m_portIndex);
        result = 0;
    }

    return result;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::SendUseItem(int portIndex, char itemId)
{
    unsigned int cmd = 0;
    unsigned char* cmdBytes = reinterpret_cast<unsigned char*>(&cmd);
    cmdBytes[0] = 0x14;
    cmdBytes[1] = 0x0C;
    cmdBytes[2] = itemId;
    unsigned int word = cmd;
    unsigned int port;

    if (static_cast<signed char>(m_threadRunningMask) == 0)
    {
        return 0;
    }

    OSWaitSemaphore(m_accessSemaphores + m_threadParams[portIndex].m_portIndex);

    unsigned int result = 0;

    port = m_threadParams[portIndex].m_portIndex;
    if ((int)m_cmdCount[port] >= 0x40)
    {
        OSSignalSemaphore(m_accessSemaphores + port);
        result = 0xFFFFFFFF;
    }
    else
    {
        m_cmdQueueData[port][m_cmdCount[port]] = word;
        port = m_threadParams[portIndex].m_portIndex;
        m_cmdCount[port]++;
        OSSignalSemaphore(m_accessSemaphores + m_threadParams[portIndex].m_portIndex);
        result = 0;
    }

    return result;
}


/*
 * --INFO--
 * PAL Address: 0x800A6324
 * PAL Size: 260b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int JoyBus::SendHitEnemy(int portIndex, char enemyId, short hitValue)
{
    unsigned int result = 0;
    unsigned short hit = hitValue;
    unsigned int cmd = 0;
    unsigned char* cmdBytes = reinterpret_cast<unsigned char*>(&cmd);

    cmdBytes[0] = 0x22;
    cmdBytes[1] = enemyId;
    *reinterpret_cast<unsigned short*>(cmdBytes + 2) = __lhbrx(&hit, 0);
    unsigned int word = cmd;

    if (static_cast<signed char>(m_threadRunningMask) == 0) {
        return result;
    }

    OSWaitSemaphore(&m_accessSemaphores[m_threadParams[portIndex].m_portIndex]);

    unsigned int port = m_threadParams[portIndex].m_portIndex;
    if (static_cast<int>(m_cmdCount[port]) >= 0x40) {
        OSSignalSemaphore(&m_accessSemaphores[port]);
        result = 0xFFFFFFFF;
    } else {
        m_cmdQueueData[port][m_cmdCount[port]] = word;
        port = m_threadParams[portIndex].m_portIndex;
        m_cmdCount[port]++;
        OSSignalSemaphore(&m_accessSemaphores[m_threadParams[portIndex].m_portIndex]);
        result = 0;
    }

    return result;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::SetOpenMenu(int playerIndex, char menuId)
{
    int result;

    if (playerIndex == 0 && GbaQue.IsSingleMode(playerIndex) && menuId != 0)
    {
        Game.m_gameWork.m_singleShopOrSmithMenuActiveFlag = 1;
        result = 0;
        MenuPcs.m_singleMenuMode = menuId - 1;
        m_ctrlModeArr[playerIndex] = 1;
    }
    else if (playerIndex == 1 && GbaQue.IsSingleMode(playerIndex) && menuId == 0)
    {
        bool isSingle = GbaQue.IsSingleMode(m_threadParams[playerIndex].m_portIndex);

        if (!isSingle)
        {
            unsigned int cmd = 0;
            unsigned char* cmdBytes = reinterpret_cast<unsigned char*>(&cmd);
            cmdBytes[0] = 0x14;
            cmdBytes[1] = 0x0F;
            cmdBytes[2] = menuId;
            unsigned int cmdCache = cmd;

            if (static_cast<signed char>(m_threadRunningMask) == 0)
            {
                result = 0;
            }
            else
            {
                OSWaitSemaphore(&m_accessSemaphores[m_threadParams[playerIndex].m_portIndex]);
                unsigned int queuePort = m_threadParams[playerIndex].m_portIndex;
                if (static_cast<int>(m_cmdCount[queuePort]) >= 0x40)
                {
                    OSSignalSemaphore(&m_accessSemaphores[queuePort]);
                    result = -1;
                }
                else
                {
                    m_cmdQueueData[queuePort][m_cmdCount[queuePort]] = cmdCache;
                    m_cmdCount[m_threadParams[playerIndex].m_portIndex]++;
                    OSSignalSemaphore(&m_accessSemaphores[m_threadParams[playerIndex].m_portIndex]);
                    result = 0;
                }
            }
        }
        else
        {
            result = 0;
        }
    }
    else
    {
        bool isSingle = GbaQue.IsSingleMode(m_threadParams[playerIndex].m_portIndex);

        if (!isSingle)
        {
            unsigned int cmd = 0;
            unsigned char* cmdBytes = reinterpret_cast<unsigned char*>(&cmd);
            cmdBytes[0] = 0x14;
            cmdBytes[1] = 0x0F;
            cmdBytes[2] = menuId;

            if (static_cast<signed char>(m_threadRunningMask) == 0)
            {
                result = 0;
            }
            else
            {
                OSWaitSemaphore(&m_accessSemaphores[m_threadParams[playerIndex].m_portIndex]);
                unsigned int queuePort = m_threadParams[playerIndex].m_portIndex;
                if (static_cast<int>(m_cmdCount[queuePort]) >= 0x40)
                {
                    OSSignalSemaphore(&m_accessSemaphores[queuePort]);
                    result = -1;
                }
                else
                {
                    m_cmdQueueData[queuePort][m_cmdCount[queuePort]] = cmd;
                    m_cmdCount[m_threadParams[playerIndex].m_portIndex]++;
                    OSSignalSemaphore(&m_accessSemaphores[m_threadParams[playerIndex].m_portIndex]);
                    result = 0;
                }
            }
        }
        else
        {
            result = 0;
        }
    }

    return result;
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
    unsigned int idx;
    unsigned int hi;

    goto check_len;

loop:
    idx = *crc;
    hi = idx << 8;
    idx = (unsigned int)((int)idx >> 8);
    idx = (unsigned char)idx;
    idx = idx ^ (unsigned int)*data;
    data = data + 1;
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
