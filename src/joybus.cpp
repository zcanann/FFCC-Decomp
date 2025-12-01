#include "ffcc/joybus.h"

#include "ffcc/system.h"

#include "string.h"

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
void JoyBus::ReadInitialCode(ThreadParam *)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::WriteInitialCode(ThreadParam *)
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
    u32 level = OSDisableInterrupts();

    OSSetAlarm(&alarm, ticks, ThreadAlarmHandler);
    OSSuspendThread(thread);
    OSRestoreInterrupts(level);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::ReadContext(ThreadParam *)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::ReadHostId(ThreadParam *)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::WriteHostId(ThreadParam *)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::WriteContext(ThreadParam *)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::SetPadData(ThreadParam *, unsigned char *)
{
	// TODO
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
void JoyBus::SendGBA(ThreadParam *)
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
void JoyBus::ResetQueue(ThreadParam *)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::CleanQueue(ThreadParam *)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::InitialCode(ThreadParam *)
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
void JoyBus::SendGBAStart(ThreadParam *, unsigned int *)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::SendGBAStop(ThreadParam *)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::SendChkCrc(ThreadParam *, int, unsigned short, unsigned int *)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::SendCancel(ThreadParam *)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::SendDataFile(ThreadParam *)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::SendMBase(ThreadParam *)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::SendMapNo(ThreadParam *)
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
void JoyBus::SendPpos(ThreadParam *)
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
void JoyBus::SendPlayerStat(ThreadParam *)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::SendPlayerHP(ThreadParam *)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::SendItemAll(ThreadParam *)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::SendMapObj(ThreadParam *)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::SendCompatibility(ThreadParam *)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::SendCtrlMode(ThreadParam *, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::SendMapObjDrawFlg(ThreadParam *)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::SendFavorite(ThreadParam *)
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
void JoyBus::SendMType(ThreadParam *, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::SendEquip(ThreadParam *)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::SendCmd(ThreadParam *)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::SendBonusStr(ThreadParam *)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::SendArtifact(ThreadParam *)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::SendTmpArtifact(ThreadParam *)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::SendMapObjInfo(ThreadParam *)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::SendStrength(ThreadParam *)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::SendRaderType(ThreadParam *)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::SendRaderMode(ThreadParam *)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::SendScouInfo(ThreadParam *)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::SendOpenMenu(ThreadParam *, char)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::SendItemUse(ThreadParam *)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::SendSPMode(ThreadParam *)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::SendMemorys(ThreadParam *)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::SendChgCmdNum(ThreadParam *)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::SendStartBonus(ThreadParam *)
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
void JoyBus::GetGBAStat(ThreadParam *)
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
void JoyBus::SetCtrlMode(int, int)
{
	// TODO
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
void JoyBus::SendAllStat(int)
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
void JoyBus::SetLetterSize(int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::SendResult(int, int, int, int)
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
void JoyBus::SendAddLetter(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::SetItem(int, unsigned char, short)
{
	// TODO
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
void JoyBus::SendMask(int, unsigned short)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::SetMoney(int, unsigned int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::SetMType(int, int)
{
	// TODO
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
void JoyBus::SetCmdLst(int, int, short)
{
	// TODO
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
void JoyBus::SendUseItem(int, char)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::SendHitEnemy(int, char, short)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void JoyBus::SetOpenMenu(int, char)
{
	// TODO
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
