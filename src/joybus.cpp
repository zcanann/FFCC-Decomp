#include "ffcc/joybus.h"

#include "ffcc/system.h"

#include "string.h"

static inline unsigned int MakeJoyCmd16(u16 opcode, unsigned char arg0 = 0, unsigned char arg1 = 0)
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
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::Destroy()
{
	// TODO
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
void JoyBus::LoadMap(int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::BlockSem(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::ReleaseSem(int)
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::RecvGBA(ThreadParam *, unsigned int *)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::SendGBA(ThreadParam* threadParam)
{
	// TODO
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
int JoyBus::SendGBAStart(ThreadParam *, unsigned int *)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::SendGBAStop(ThreadParam* threadParam)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::SendChkCrc(ThreadParam *, int, unsigned short, unsigned int *)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::SendCancel(ThreadParam* threadParam)
{
	// TODO
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
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::SendMapNo(ThreadParam* threadParam)
{
	// TODO
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
	// TODO
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
int JoyBus::SendCtrlMode(ThreadParam *, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::SendMapObjDrawFlg(ThreadParam* threadParam)
{
	// TODO
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
int JoyBus::SendMType(ThreadParam *, int)
{
	return 0;
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

    const u16 opcode = static_cast<u16>(0x1900 | strength0);
    const u32 cmd = MakeJoyCmd16(opcode, strength1, strength2);

    // If threads not running, return success
    if (m_threadRunningMask == 0)
	{
        return 0;
	}

    const u32 port = threadParam->m_portIndex;

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
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::SendRaderMode(ThreadParam* threadParam)
{
	// TODO
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
int JoyBus::SendOpenMenu(ThreadParam *, char)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::SendItemUse(ThreadParam* threadParam)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::SendSPMode(ThreadParam* threadParam)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::SendMemorys(ThreadParam* threadParam)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::SendChgCmdNum(ThreadParam* threadParam)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::SendStartBonus(ThreadParam* threadParam)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::DecRecvQueue(int)
{
	// TODO
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

    const u16 opcode = 0x0900;
    const u32 cmd    = MakeJoyCmd16(opcode, modeFlag, 0);

    int result = 0;

    if (m_threadRunningMask != 0)
    {
        const u32 port = m_threadParams[portIndex].m_portIndex;

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
        const u32 port = m_threadParams[portIndex].m_portIndex;
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
void JoyBus::IsInitSend(int)
{
	// TODO
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
int JoyBus::SendAllStat(int)
{
	// TODO
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
int JoyBus::SendResult(int, int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::IsLetterMenu(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::SendAddLetter(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::SetItem(int portIndex, unsigned char itemId, short amount)
{
    u16 opcode = static_cast<u16>(0x1700 | itemId);
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
void JoyBus::DelItem(int, unsigned char)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int JoyBus::SendMask(int, unsigned short)
{
	// TODO
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
		const unsigned short opcode = static_cast<u16>(0x5A00 | money_mid);
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
void JoyBus::IsThreadRunning()
{
	// TODO
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
    u16 opcode = static_cast<u16>(0x1F00 | (param_3 & 0xFF));
    u32 cmd = MakeJoyCmd16(opcode, argLo, argHi);

    if (m_threadRunningMask == 0)
	{
        return 0;
	}

    const u32 port = m_threadParams[portIndex].m_portIndex;

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
    const u16 opcode = 0x140C;
    const u32 cmd    = MakeJoyCmd16(opcode, static_cast<unsigned char>(itemId), 0);

    int result = 0;

    if (m_threadRunningMask != 0)
    {
        const u32 port = m_threadParams[portIndex].m_portIndex;

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
int JoyBus::SendHitEnemy(int, char, short)
{
	// TODO
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
                const unsigned short opcode = static_cast<u16>(0x140F);
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
void JoyBus::Crc16(int, unsigned char *, unsigned short *)
{
	// TODO
}
