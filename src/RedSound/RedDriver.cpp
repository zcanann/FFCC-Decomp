#include "ffcc/RedSound/RedDriver.h"
#include "ffcc/RedSound/RedMemory.h"
#include "ffcc/RedSound/RedEntry.h"
#include "ffcc/RedSound/RedStream.h"
#include "ffcc/RedSound/RedCommand.h"
#include "ffcc/RedSound/RedExecute.h"
#include "ffcc/RedSound/RedGlobals.h"
#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/file_io.h"
#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/string.h"
#include "dolphin/ar.h"
#include "dolphin/ax.h"
#include "dolphin/axfx.h"
#include "dolphin/os.h"

// Global objects that need initialization

struct RedMusicHEAD;
struct RedSeSepHEAD;
struct RedWaveHEAD {
    char magic[2];
    short waveID;
    int dataSize;
    int regionCount;
    int sampleCount;
};

extern "C" {
    int __OSReadROM();
}

struct RedWaveSettingState {
    int slot;
    int waveID;
    void* waveData;
    int waveSize;
};

struct RedDriverSyncState {
    int m_dmaQueue[0x380];
    int m_streamDmaQueue[0x380];
    OSThread m_mainThread;
    OSSemaphore m_mainSemaphore;
    u8 m_pad2240[0x2240 - 0x1F18 - sizeof(OSSemaphore)];
    OSSemaphore m_waveSemaphore;
    u8 m_pad2578[0x2578 - 0x2240 - sizeof(OSSemaphore)];
    OSSemaphore m_dmaSemaphore;
    u8 m_pad28c0[0x28C0 - 0x2578 - sizeof(OSSemaphore)];
    OSSemaphore m_musicSemaphore;
};

// RedDriver-owned linkage (sbss/sdata tracked symbols)
static int m_RedMasterTime;
static volatile int m_SequencialID;
static volatile int m_ThreadControl;
static volatile int m_ThreadExecute;
static int m_SoundMode;
static int* volatile p_Tick;
void* volatile p_ZeroData;
static void* volatile p_ExecCommand;
static void* volatile p_ExecCommandNow;
static void* volatile p_ExecCommandOld;
static void* p_DmaControlNow[2];
static void* p_DmaControlOld[2];
void* volatile p_SoundControlBuffer;
void* volatile p_SoundControl;
volatile int m_KeyOnEntry;
void* volatile p_KeyOnData;
int m_SoundPlayMode;
int m_SoundMasterControl;
volatile int m_ReportPrint;
int m_MusicFastSpeed;
volatile int m_MusicSkipLine;
int m_MusicKeySignature;
void* volatile p_MusicReplayPoint;
int* volatile p_MusicTempoControl;
int* volatile p_MusicPitchControl;
int m_MusicPhraseStop;
static int* volatile p_MusicNextPlay;
int m_CrossTime;
volatile int m_MasterMusicVolume;
volatile int m_MasterSEVolume;
RedStreamDATA* volatile p_Stream;
static int m_DMAMode;
volatile int m_SeSkipStep;
unsigned int* volatile p_VoiceData;
int p_EditorVoice[2];
void* p_EditorTrack;
static void* volatile p_MainThreadStack;
static int m_MainThreadTime;
static void* volatile p_WaveSettingThreadStack;
static int m_WaveSettingStatus;
static void* volatile p_DmaExecuteThreadStack;
static volatile int m_DMAStatus;
void* volatile p_MusicSkipThreadStack;
volatile int m_MusicSkipComplete;
void* volatile p_ReverbDepth;
int m_Mute[2];
static int m_DmaControl[0x700];
static OSThread m_MainThread;
static OSSemaphore m_MainSemaphore;
static OSThread m_WaveSettingThread;
static OSSemaphore m_WaveSettingSemaphore;
static RedWaveSettingState m_WaveSettingData;
static OSThread m_DmaExecuteThread;
static OSSemaphore m_DmaExecuteSemaphore;
static ARQRequest m_DMARequest;
OSThread m_MusicSkipThread;
OSSemaphore m_MusicSkipSemaphore;
void* volatile p_SeBlockData[4];
CRedMemory c_RedMemory;
static volatile int m_DMAExecute;
static volatile int m_DMAInThread;
CRedEntry c_RedEntry;

static inline RedDriverSyncState& RedDriverSync()
{
    return *reinterpret_cast<RedDriverSyncState*>(m_DmaControl);
}

static inline int* RedDriverMainDmaQueue()
{
    return m_DmaControl;
}

static inline int* RedDriverStreamDmaQueue()
{
    return m_DmaControl + 0x380;
}

static inline int* RedDriverStreamDmaQueueEnd()
{
    return m_DmaControl + 0x700;
}

static inline OSThread& RedDriverMainThread()
{
    return m_MainThread;
}

static const char s_redDriverDmaCheckHeaderFmt[] = "%s **** DMA CHECK PROCESS ****\n";
static const char sRedDriverLogPrefix[] = "\x1B[7;34mSound\x1B[0m:";
static const char sRedDriverDmaStatusFmt[] = "%s Status = %d, Semaphore = %d, Execute = %d, In Thread = %d\n";
static const char sRedDriverDmaEntryFmt[] = "%s ID = %d, MMem = %8.8X, AMem = %8.8X, Size = %8.8X, Callback = %8.8X\n";
static const char sRedDriverMusicHeaderErrorFmt[] = "%s%sMusic-Header was broken !!%s\n";
static const char sRedDriverSeSepHeaderErrorFmt[] = "%s%sSE-Sep-Header was broken !!%s\n";
static const char sRedDriverLogWarnColor[] = "\x1B[4;31m";
static const char sRedDriverLogReset[] = "\x1B[0m";

/*
 * --INFO--
 * PAL Address: 0x801bcf0c
 * PAL Size: 124b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void _SetSoundMode(int* command)
{
    m_SoundMode = *command;
    if (*command == 1) {
        OSGetSoundMode(0);
    } else {
        OSGetSoundMode(1);
    }
    m_SoundPlayMode = m_SoundMode;
    switch (m_SoundPlayMode) {
    case 2:
        AXSetMode(2);
        break;
    default:
        AXSetMode(0);
        break;
    }
}

/*
 * --INFO--
 * PAL Address: 0x801bcf88
 * PAL Size: 192b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void _SetReverbDepth(int* command)
{
    int reverbBank;
    int reverbDepth;
    int fadeStep;
    int fadeDepth;
    int* seInfo;

    reverbBank = command[0] & 1;
    reverbDepth = command[1] & 0x7f;
    fadeStep = command[2];
    if (reverbDepth != 0) {
        reverbDepth += 1;
        reverbDepth <<= 8;
        reverbDepth -= 1;
        reverbDepth <<= 12;
    }
    *(unsigned int*)((char*)p_ReverbDepth + reverbBank * 0xc) = reverbDepth;
    if (reverbBank != 0) {
        fadeStep = fadeStep * 0x60;
        fadeStep = fadeStep / 0x3c;
        if (fadeStep == 0) {
            fadeStep++;
        }
        reverbDepth |= 0x800;
        seInfo = *(int**)((char*)p_SoundControlBuffer + 0xdbc);
        do {
            if ((u32)*seInfo != 0) {
                fadeDepth = reverbDepth - (seInfo[0x1a] & 0xfffff000U);
                seInfo[0x1b] = fadeDepth / fadeStep;
                seInfo[0x1c] = fadeStep;
            }
            seInfo += 0x55;
        } while (seInfo < (int*)(*(int*)((char*)p_SoundControlBuffer + 0xdbc) + 0x2a80));
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _SetMusicData(int* command)
{
    c_RedEntry.SetMusicData((RedMusicHEAD*)*command);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _MusicStop(int* command)
{
    MusicStop(*command);
    if ((*command == -1) || (p_MusicNextPlay[0] == *command)) {
        p_MusicNextPlay[0] = -1;
    }
    if (p_MusicNextPlay[0] < 0) {
        m_MusicPhraseStop = 0;
    }
}

/*
 * --INFO--
 * PAL Address: 0x801bd0f4
 * PAL Size: 264b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void _MusicPlaySequence(int* command)
{
    int iVar1;
    int srcBuffer;

    srcBuffer = (int)p_SoundControlBuffer;
    if ((*command == *(int*)(srcBuffer + 0x470)) ||
        (*command == *(int*)(srcBuffer + 0x904)) ||
        (*command == *(int*)(srcBuffer + 0xd98))) {
        return;
    }
    if (c_RedEntry.SearchMusicSequence(*command) >= 0) {
        iVar1 = command[2];
        if (*(int*)(srcBuffer + 0x470) != -1) {
            if (*(int*)(srcBuffer + 0x904) != -1) {
                MusicStop(*(int*)(srcBuffer + 0x904));
            }
            if (iVar1 == 0) {
                iVar1 = *(int*)((int)p_MusicReplayPoint + *command * 4);
                *(int*)((int)p_MusicReplayPoint + *command * 4) = 0;
            }
            if (iVar1 == 0) {
                memcpy((void*)(srcBuffer + 0x494), (void*)srcBuffer, 0x494);
                *(int*)(srcBuffer + 0x470) = -1;
            }
        }
        MusicPlay(*command, command[1], iVar1);
    }
}

/*
 * --INFO--
 * PAL Address: 0x801bd1fc
 * PAL Size: 520b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void _MusicCrossPlaySequence(int* command)
{
    int iVar1;
    void* pvVar2;
    
    command[2] = command[2] * 200;
    command[2] = command[2] / 0x3c;
    if (command[2] == 0) {
        command[2] = command[2] + 1;
    }
    pvVar2 = p_SoundControlBuffer;
    if ((*command == *(int*)((int)pvVar2 + 0x470)) ||
       (*command == *(int*)((int)pvVar2 + 0xd98))) {
        return;
    }
    if (*command == *(int*)((int)pvVar2 + 0x904)) {
        *(int*)((int)pvVar2 + 0x458) = -*(int*)((int)pvVar2 + 0x454) / command[2];
        *(int*)((int)pvVar2 + 0x45c) = command[2];
        pvVar2 = p_SoundControlBuffer;
        *(int*)((int)pvVar2 + 0x8ec) =
             (0x1ff800 - *(int*)((int)pvVar2 + 0x8e8)) / command[2];
        *(int*)((int)pvVar2 + 0x8f0) = command[2];
        pvVar2 = (void*)RedNew(0x494);
        memcpy(pvVar2, (void*)((int)p_SoundControlBuffer + 0x494), 0x494);
        memcpy((void*)((int)p_SoundControlBuffer + 0x494), p_SoundControlBuffer, 0x494);
        memcpy(p_SoundControlBuffer, pvVar2, 0x494);
        RedDelete(pvVar2);
    } else {
        if (c_RedEntry.SearchMusicSequence(*command) >= 0) {
            m_CrossTime = command[2];
            iVar1 = 0;
            if (*(int*)((int)pvVar2 + 0x470) != -1) {
                if (*(int*)((int)pvVar2 + 0x904) != -1) {
                    MusicStop(*(int*)((int)pvVar2 + 0x904));
                }
                *(int*)((int)pvVar2 + 0x458) = -*(int*)((int)pvVar2 + 0x454) / command[2];
                *(int*)((int)pvVar2 + 0x45c) = command[2];
                iVar1 = *(int*)((char*)p_MusicReplayPoint + *command * 4);
                *(int*)((char*)p_MusicReplayPoint + *command * 4) = 0;
                if (iVar1 == 0) {
                    memcpy((void*)((int)pvVar2 + 0x494), pvVar2, 0x494);
                    *(int*)((int)pvVar2 + 0x470) = 0xffffffff;
                }
            }
            MusicPlay(*command, command[1], iVar1);
        }
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _MusicNextPlaySequence(int* command)
{
    int srcBuffer;

    srcBuffer = (int)p_SoundControlBuffer;
    if ((*command == *(int*)(srcBuffer + 0x470)) ||
        (*command == *(int*)(srcBuffer + 0x904)) ||
        (*command == *(int*)(srcBuffer + 0xd98))) {
        return;
    }
    if (c_RedEntry.SearchMusicSequence(*command) >= 0) {
        p_MusicNextPlay[0] = *command;
        p_MusicNextPlay[1] = command[1];
        p_MusicNextPlay[2] = command[2];
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _MusicMasterVolume(int* command)
{
    unsigned int* puVar1;

    m_MasterMusicVolume = *command & 0x7f;
    if (m_MasterMusicVolume != 0) {
        m_MasterMusicVolume = m_MasterMusicVolume + 1;
        m_MasterMusicVolume = m_MasterMusicVolume * 4;
        m_MasterMusicVolume = m_MasterMusicVolume - 1;
    }
    puVar1 = p_VoiceData;
    do {
        puVar1[0x2e] = puVar1[0x2e] | 2;
        puVar1 += 0x30;
    } while (puVar1 < p_VoiceData + 0xc00);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _MusicVolume(int* command)
{
    if (command[3] == 1) {
        p_MusicNextPlay[0] = -1;
        m_MusicPhraseStop = 0;
    }
    SetMusicVolume(command[0], command[1], command[2], command[3]);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _SetMusicPhraseStop(int* command)
{
    m_MusicPhraseStop = *command;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _SetSeBlockData(int* command)
{
    u32 index = (u32)*command & 3;
    char* seBlockData;

    if (p_SeBlockData[index] != 0) {
        RedDelete(p_SeBlockData[index]);
        p_SeBlockData[index] = 0;
    }

    if (command[1] != 0) {
        seBlockData = (char*)command[1];
        if ((*seBlockData = 'S') && (seBlockData[1] = 'e') && (seBlockData[2] = 'B') &&
            (seBlockData[3] = 'l') && (seBlockData[4] = 'o') && (seBlockData[5] = 'c') &&
            (seBlockData[6] = 'k')) {
            p_SeBlockData[index] = seBlockData;
        } else {
            RedDelete(seBlockData);
        }
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _SetSeSepData(int* command)
{
    c_RedEntry.SetSeSepData((RedSeSepHEAD*)*command);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _ClearSeSepData(int* command)
{
    c_RedEntry.ClearSeSepData(*command);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _ClearSeSepDataMG(int* command)
{
    c_RedEntry.ClearSeSepDataMG(command[0], command[1], command[2], command[3]);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _SeStop(int* command)
{
    SeStopID(command[0]);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _SeStopMG(int* command)
{
    SeStopMG(command[0], command[1], command[2], command[3]);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _SeBlockPlay(int* command)
{
    m_SeSkipStep = command[5];
    SeBlockPlay(command[0], command[1], command[2], command[3], command[4]);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _SeSepPlay(int* command)
{
    int iVar1;

    iVar1 = c_RedEntry.SetSeSepData((RedSeSepHEAD*)command[1]);
    if (iVar1 != 0) {
        m_SeSkipStep = command[4];
        int seID = command[0];
        SeSepPlay(seID, *(int*)(iVar1 + 8), command[2], command[3]);
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _SeSepPlaySequence(int* command)
{
    if (c_RedEntry.SearchSeSepSequence(command[1]) >= 0) {
        m_SeSkipStep = command[4];
        SeSepPlay(command[0], command[1], command[2], command[3]);
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _SeMasterVolume(int* command)
{
    unsigned int* puVar1;

    m_MasterSEVolume = *command & 0x7f;
    if (m_MasterSEVolume != 0) {
        m_MasterSEVolume = m_MasterSEVolume + 1;
        m_MasterSEVolume = m_MasterSEVolume * 4;
        m_MasterSEVolume = m_MasterSEVolume - 1;
    }
    puVar1 = p_VoiceData;
    do {
        puVar1[0x2e] = puVar1[0x2e] | 2;
        puVar1 += 0x30;
    } while (puVar1 < p_VoiceData + 0xc00);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _SeVolume(int* command)
{
    SetSeVolume(command[0], command[1], command[2], command[3]);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _SePan(int* command)
{
    SetSePan(command[0], command[1], command[2]);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _SePitch(int* command)
{
    SetSePitch(command[0], command[1], command[2]);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _SePause(int* command)
{
    SePause(command[0], command[1]);
}

/*
 * --INFO--
 * PAL Address: 0x801bda34
 * PAL Size: 48b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void _StreamStop(int* command)
{
	StreamStop(*command);
}

/*
 * --INFO--
 * PAL Address: 0x801bda64
 * PAL Size: 64b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void _StreamPlay(int* command)
{
	StreamPlay(command[0], (void*)command[1], command[2], command[3], command[4]);
}

/*
 * --INFO--
 * PAL Address: 0x801bdaa4
 * PAL Size: 56b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void _StreamVolume(int* command)
{
	SetStreamVolume(command[0], command[1], command[2]);
}

/*
 * --INFO--
 * PAL Address: 0x801bdadc
 * PAL Size: 52b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void _StreamPause(int* command)
{
	StreamPause(command[0], command[1]);
}

/*
 * --INFO--
 * PAL Address: 0x801bdb10
 * PAL Size: 192b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int* _EntryExecCommand(void (*func)(int*), int arg1, int arg2, int arg3, int arg4,
                       int arg5, int arg6, int arg7)
{
    unsigned int interruptLevel;
    int* writePos;

    interruptLevel = OSDisableInterrupts();
    writePos = (int*)p_ExecCommandNow;
    writePos[0] = (int)func;
    writePos[1] = arg1;
    writePos[2] = arg2;
    writePos[3] = arg3;
    writePos[4] = arg4;
    writePos[5] = arg5;
    writePos[6] = arg6;
    writePos[7] = arg7;
    writePos += 8;
    if (writePos == (int*)p_ExecCommand + 0x800) {
        writePos = (int*)p_ExecCommand;
    }
    p_ExecCommandNow = writePos;
    OSRestoreInterrupts(interruptLevel);
    return writePos;
}

/*
 * --INFO--
 * PAL Address: 0x801bdbd0
 * PAL Size: 120b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void _ExecuteCommand()
{
	volatile unsigned int* readPos;
	volatile unsigned int* executePos;

	executePos = (volatile unsigned int*)p_ExecCommandNow;
	readPos = (volatile unsigned int*)p_ExecCommandOld;

	while (executePos != readPos) {
		if (*readPos != 0) {
			((void (*)(int*))(*readPos))((int*)(readPos + 1));
		}
		readPos += 8;
		if (readPos == (volatile unsigned int*)p_ExecCommand + 0x800) {
			readPos = (volatile unsigned int*)p_ExecCommand;
		}
	}

	p_ExecCommandOld = (void*)readPos;
}

/*
 * --INFO--
 * PAL Address: 0x801bdc48
 * PAL Size: 112b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned int DeltaTimeSumup(unsigned char** buffer)
{
	unsigned int deltaTime = 0;

	if (buffer != 0) {
		deltaTime = **buffer & 0x7f;
		while ((**buffer & 0x80) != 0) {
			*buffer += 1;
			deltaTime <<= 7;
			deltaTime |= **buffer & 0x7f;
		}
		*buffer += 1;
	}

	return deltaTime;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
unsigned int GetMyEntryID()
{
    m_SequencialID++;
    m_SequencialID &= 0x7fffffff;
    if (m_SequencialID == 0) {
        m_SequencialID++;
    }
    return m_SequencialID;
}

struct RedSleepAlarm {
    OSAlarm alarm;
    OSThread* thread;
};

/*
 * --INFO--
 * PAL Address: 0x801bdcf0
 * PAL Size: 44b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void _MyAlarmHandler(OSAlarm* alarm, OSContext*)
{
    OSResumeThread(((RedSleepAlarm*)alarm)->thread);
}

/*
 * --INFO--
 * PAL Address: 0x801bdd1c
 * PAL Size: 160b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void RedSleep(int microseconds)
{
    unsigned int interruptLevel;
    RedSleepAlarm alarm;

    if (microseconds < 0xfa) {
        microseconds = 0xfa;
    }
    interruptLevel = OSDisableInterrupts();
    alarm.thread = OSGetCurrentThread();
    OSCreateAlarm(&alarm.alarm);
    OSSetAlarm(&alarm.alarm, (microseconds * (OS_TIMER_CLOCK / 125000)) >> 3, _MyAlarmHandler);
    OSSuspendThread(alarm.thread);
    OSRestoreInterrupts(interruptLevel);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int _MainThread(void*)
{
    int iVar1;
    int iVar2;
    int iVar3;
    unsigned int uVar4;

    m_ThreadExecute = m_ThreadExecute | 1;
    while (m_ThreadControl != 0) {
        OSWaitSemaphore(&m_MainSemaphore);
        if (m_ThreadControl != 0) {
            iVar2 = OSGetTick();
            iVar1 = (int)p_SoundControlBuffer;
            iVar3 = m_RedMasterTime;
            uVar4 = (unsigned int)(m_RedMasterTime - m_MainThreadTime);
            if (*(short*)(iVar1 + 0x48e) != 0) {
                *(unsigned int*)(iVar1 + 0x478) = *(unsigned int*)(iVar1 + 0x478) + uVar4;
            }
            m_MainThreadTime = iVar3;
            if (4 < uVar4) {
                uVar4 = 4;
            }
            MainControl(uVar4);
            StreamControl();
            _ExecuteCommand();
            if ((-1 < p_MusicNextPlay[0]) && (*(int*)(iVar1 + 0x470) < 0)) {
                _MusicPlaySequence(p_MusicNextPlay);
                p_MusicNextPlay[0] = -1;
                m_MusicPhraseStop = 0;
            }
            do {
                iVar3 = OSTryWaitSemaphore(&m_MainSemaphore);
            } while (0 < iVar3);
            memmove((int*)p_Tick + 1, p_Tick, 0x18c);
            iVar3 = OSGetTick();
            *(int*)p_Tick = iVar3 - iVar2;
        }
    }
    m_ThreadExecute = m_ThreadExecute & ~1;
    return 0;
}

/*
 * --INFO--
 * PAL Address: 0x801bdee8
 * PAL Size: 196b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int _WaveSettingThread(void* threadArg)
{
    m_ThreadExecute = m_ThreadExecute | 4;
    m_WaveSettingStatus = 0;
    while (m_ThreadControl != 0) {
        OSWaitSemaphore(&m_WaveSettingSemaphore);
        if (m_ThreadControl != 0) {
            RedWaveSettingState* waveSetting = (RedWaveSettingState*)threadArg;
            m_WaveSettingStatus = m_WaveSettingStatus + 1;
            c_RedEntry.SetWaveData(waveSetting->waveID, waveSetting->waveData, waveSetting->waveSize);
            *(int*)waveSetting->slot = 0;
            do {
            } while (OSTryWaitSemaphore(&m_WaveSettingSemaphore) > 0);
            m_WaveSettingStatus = 0;
        }
    }
    m_ThreadExecute = m_ThreadExecute & ~4;
    return 0;
}

/*
 * --INFO--
 * PAL Address: 0x801bdfac
 * PAL Size: 280b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void _DMACheckProcess()
{
    int* dmaInfo;

    if (m_ReportPrint != 0) {
        OSReport(s_redDriverDmaCheckHeaderFmt, sRedDriverLogPrefix);
        fflush(__files + 1);

        OSReport(sRedDriverDmaStatusFmt, sRedDriverLogPrefix, m_DMAStatus,
                 OSGetSemaphoreCount(&m_DmaExecuteSemaphore), m_DMAExecute, m_DMAInThread);
        fflush(__files + 1);
    }

    dmaInfo = RedDriverMainDmaQueue();
    do {
        if ((*dmaInfo != 0) && (m_ReportPrint != 0)) {
            OSReport(sRedDriverDmaEntryFmt, sRedDriverLogPrefix,
                     dmaInfo[0], dmaInfo[2], dmaInfo[3], dmaInfo[4], dmaInfo[5]);
            fflush(__files + 1);
        }
        dmaInfo += 7;
    } while (dmaInfo < RedDriverStreamDmaQueueEnd());

    fflush(__files + 1);
}

/*
 * --INFO--
 * PAL Address: 0x801be0c4
 * PAL Size: 12b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void _DmaCallback(unsigned long)
{
    m_DMAStatus = 0;
}

/*
 * --INFO--
 * PAL Address: 0x801be0d0
 * PAL Size: 356b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int RedDmaEntry(int param_1, int param_2, int param_3, int param_4, int param_5, void (*param_6)(void*), void* param_7)
{
    unsigned int interrupt;
    int* queueBase;
    int** queuePtr;
    unsigned int entryID;
    unsigned int size;
    unsigned int chunkSize;
    int* queueEntry;
    int* queueEnd;
    int* nextEntry;

    interrupt = OSDisableInterrupts();
    if ((param_1 & 0xffff7fff) != 0) {
        queuePtr = (int**)&p_DmaControlNow[0];
        queueBase = RedDriverMainDmaQueue();
    } else {
        queueBase = RedDriverStreamDmaQueue();
        queuePtr = (int**)&p_DmaControlNow[1];
    }
    queueEntry = *queuePtr;
    entryID = GetMyEntryID();
    size = (unsigned int)(param_5 + 0x1f) & 0xffffffe0;
    if ((m_DMAMode != 0) || ((param_1 & 0x8000) != 0)) {
        queueEnd = queueBase + 0x380;
        do {
            chunkSize = size;
            if ((int)size > 0x40000) {
                chunkSize = 0x40000;
            }
            queueEntry[0] = entryID;
            size -= chunkSize;
            queueEntry[1] = param_2;
            queueEntry[2] = param_3;
            param_3 += chunkSize;
            queueEntry[3] = param_4;
            param_4 += chunkSize;
            queueEntry[4] = chunkSize;
            queueEntry[6] = (int)param_7;
            if ((int)size < 1) {
                queueEntry[5] = (int)param_6;
            } else {
                queueEntry[5] = 0;
            }
            queueEntry += 7;
            if (queueEnd <= queueEntry) {
                queueEntry = queueBase;
            }
        } while ((int)size > 0);
        *queuePtr = queueEntry;
    } else {
        nextEntry = queueEntry + 7;
        queueEnd = queueBase + 0x380;
        queueEntry[0] = entryID;
        queueEntry[1] = param_2;
        queueEntry[2] = param_3;
        queueEntry[3] = param_4;
        queueEntry[4] = size;
        queueEntry[5] = (int)param_6;
        queueEntry[6] = (int)param_7;
        if (queueEnd <= nextEntry) {
            nextEntry = queueBase;
        }
        *queuePtr = nextEntry;
    }
    OSSignalSemaphore(&m_DmaExecuteSemaphore);
    OSRestoreInterrupts(interrupt);
    return entryID;
}

/*
 * --INFO--
 * PAL Address: 0x801be234
 * PAL Size: 168b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int RedDmaSearchID(int id)
{
    unsigned int interruptLevel;
    int found;
    int* queueEntry;

    found = 0;
    interruptLevel = OSDisableInterrupts();
    if (id != 0) {
        queueEntry = RedDriverMainDmaQueue();
        do {
            if ((*queueEntry != 0) && ((id == 0) || (*queueEntry == id))) {
                found = 1;
                break;
            }
            queueEntry += 7;
        } while (queueEntry < RedDriverStreamDmaQueueEnd());
    }
    OSRestoreInterrupts(interruptLevel);
    return found;
}

/*
 * --INFO--
 * PAL Address: 0x801be2dc
 * PAL Size: 496b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void _DmaExecute()
{
    unsigned int uVar1;
    int iVar2;
    int iVar3;
    int* piVar4;
    int** ppiVar5;
    int* piVar6;
    int* piVar7;
    int* piVar8;

    while ((p_DmaControlNow[0] != p_DmaControlOld[0]) || (p_DmaControlNow[1] != p_DmaControlOld[1])) {
        m_DMAInThread = 1;
        if (p_DmaControlNow[0] == p_DmaControlOld[0]) {
            ppiVar5 = (int**)&p_DmaControlOld[1];
            piVar4 = RedDriverStreamDmaQueue();
        } else {
            ppiVar5 = (int**)&p_DmaControlOld[0];
            piVar4 = RedDriverMainDmaQueue();
        }
        piVar7 = *ppiVar5;
        m_DMAInThread = 2;
        piVar6 = 0;
        if (*piVar7 != 0) {
            m_DMAStatus = 1;
            if (piVar7[1] == 0) {
                DCFlushRange((void*)piVar7[2], (u32)piVar7[4]);
                iVar3 = piVar7[2];
                iVar2 = piVar7[3];
            } else {
                DCInvalidateRange((void*)piVar7[2], (u32)piVar7[4]);
                iVar3 = piVar7[3];
                iVar2 = piVar7[2];
            }
            m_DMAInThread = 3;
            ARQSetChunkSize((u32)piVar7[4]);
            ARQPostRequest(&m_DMARequest, 0x469, (u32)piVar7[1], 1, (u32)iVar3, (u32)iVar2,
                           (u32)piVar7[4], _DmaCallback);
            m_DMAInThread = 4;
            piVar6 = piVar7;
        }
        piVar8 = piVar7 + 7;
        m_DMAInThread = 5;
        if (piVar4 + 0x380 <= piVar7 + 7) {
            piVar8 = piVar4;
        }
        *ppiVar5 = piVar8;
        m_DMAInThread = 6;

        while (piVar6 != 0) {
            m_DMAInThread = 7;
            if (m_DMAStatus == 0) {
                m_DMAInThread = 8;
                if ((u32)piVar6[5] != 0) {
                    uVar1 = OSDisableInterrupts();
                    ((void (*)(void*))piVar6[5])((void*)piVar6[6]);
                    OSRestoreInterrupts(uVar1);
                }
                m_DMAInThread = 9;
                if (piVar6[1] == 1) {
                    DCFlushRange((void*)piVar6[2], (u32)piVar6[4]);
                }
                *piVar6 = 0;
                break;
            }
            RedSleep(0);
        }
    }
    m_DMAInThread = 0;
}

/*
 * --INFO--
 * PAL Address: 0x801be4cc
 * PAL Size: 132b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int _DmaExecuteThread(void*)
{
    m_ThreadExecute |= 2;
    m_DMAExecute = 0;
    m_DMAInThread = 0;
    while (m_ThreadControl != 0) {
        OSWaitSemaphore(&m_DmaExecuteSemaphore);
        m_DMAExecute = 1;
        if (m_ThreadControl != 0) {
            _DmaExecute();
        }
        m_DMAExecute = 0;
    }
    m_ThreadExecute &= ~2;
    return 0;
}

/*
 * --INFO--
 * PAL Address: 0x801be550
 * PAL Size: 128b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int _MusicSkipThread(void*)
{
    m_ThreadExecute |= 8;
    m_MusicSkipComplete = 0;
    while (m_ThreadControl != 0) {
        OSWaitSemaphore(&m_MusicSkipSemaphore);
        if (m_ThreadControl != 0) {
            MusicSkipFunction();
        }
        while (OSTryWaitSemaphore(&m_MusicSkipSemaphore) > 0) {
        }
    }
    m_ThreadExecute &= ~8;
    return 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _RedAXCallback()
{
    m_RedMasterTime = m_RedMasterTime + 1;
    EnvelopeKeyExecute();
    OSSignalSemaphore(&m_MainSemaphore);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CRedDriver::CRedDriver()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x801be60c
 * PAL Size: 72b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CRedDriver::~CRedDriver()
{
}

/*
 * --INFO--
 * PAL Address: 0x801be654
 * PAL Size: 1316b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedDriver::Init()
{
    char cVar1;
    int iVar2;
    int iVar4;
    int iVar5;
    int iVar6;
    void* uVar3;

    m_ThreadExecute = 0;
    m_ThreadControl = 1;
    m_ReportPrint = 1;
    m_SoundMode = 0;
    GetSoundMode();
    if (m_SoundPlayMode == 2) {
        AXSetMode(2);
    } else {
        AXSetMode(0);
    }
    p_Tick = (int*)RedNew(400);
    memset(p_Tick, 0, 400);
    AXSetCompressor(0);
    m_MusicKeySignature = 0;
    m_SoundMasterControl = 0;
    m_MusicSkipLine = 0;
    m_MusicFastSpeed = 0;
    m_DMAStatus = 0;
    m_CrossTime = 0;
    m_MasterSEVolume = 0x1ff;
    m_MasterMusicVolume = 0x1ff;
    iVar6 = 0;
    do {
        iVar5 = iVar6 + 1;
        p_SeBlockData[iVar6] = 0;
        iVar6 = iVar5;
    } while (iVar5 < 4);
    p_ZeroData = (void*)RedNew(0x1000);
    memset(p_ZeroData, 0, 0x1000);
    p_MusicReplayPoint = (void*)RedNew(0x400);
    memset(p_MusicReplayPoint, 0, 0x400);
    p_MusicTempoControl = (int*)RedNew(0xc);
    memset(p_MusicTempoControl, 0, 0xc);
    p_MusicPitchControl = (int*)RedNew(0xc);
    memset(p_MusicPitchControl, 0, 0xc);
    p_ExecCommand = (void*)RedNew(0x2000);
    p_ExecCommandNow = p_ExecCommand;
    p_ExecCommandOld = p_ExecCommand;
    memset(p_ExecCommand, 0, 0x2000);
    p_SoundControlBuffer = (void*)RedNew(0x1250);
    p_SoundControl = p_SoundControlBuffer;
    memset(p_SoundControlBuffer, 0, 0x1250);
    *(int*)((char*)p_SoundControl + 0xdd8) = 0x1ff000;
    *(int*)((char*)p_SoundControl + 0x944) = 0x1ff000;
    *(int*)((char*)p_SoundControl + 0x4b0) = 0x1ff000;
    *(int*)((char*)p_SoundControl + 0x1c) = 0x1ff000;
    *(int*)((char*)p_SoundControl + 0x1210) = 0x1ff000;
    *(int*)((char*)p_SoundControl + 0xd7c) = 0x1ff000;
    *(int*)((char*)p_SoundControl + 0x8e8) = 0x1ff000;
    *(int*)((char*)p_SoundControl + 0x454) = 0x1ff000;
    *(int*)((char*)p_SoundControl + 0xd98) = -1;
    *(int*)((char*)p_SoundControl + 0x904) = -1;
    *(int*)((char*)p_SoundControl + 0x470) = -1;
    p_KeyOnData = (void*)RedNew(0x600);
    memset(p_KeyOnData, 0, 0x600);
    p_VoiceData = (unsigned int*)RedNew(0x3000);
    memset(p_VoiceData, 0, 0x3000);
    iVar6 = 0;
    do {
        iVar2 = iVar6 * 0xc0;
        iVar5 = iVar6 * 0x8000000;
        iVar4 = iVar6 >> 0x1f;
        iVar6 = iVar6 + 1;
        *(unsigned int*)((char*)p_VoiceData + iVar2 + 0xa8) =
            (iVar4 * 0x20 | (unsigned int)(iVar5 + iVar4) >> 0x1b) - iVar4;
    } while (iVar6 < 0x40);
    p_EditorVoice[1] = 0;
    p_EditorVoice[0] = 0;
    uVar3 = (void*)RedNew(0x2a80);
    *(void**)((char*)p_SoundControlBuffer + 0xdbc) = uVar3;
    memset(*(void**)((char*)p_SoundControlBuffer + 0xdbc), 0, 0x2a80);
    iVar5 = 0;
    iVar6 = (int)*(void**)((char*)p_SoundControlBuffer + 0xdbc);
    do {
        iVar4 = iVar5 * 0x154;
        cVar1 = (char)iVar5;
        iVar5 = iVar5 + 1;
        *(char*)(iVar6 + iVar4 + 0x14e) = (char)(cVar1 + ' ');
    } while (iVar5 < 0x20);
    p_EditorTrack = (void*)RedNew(0x154);
    memset(p_EditorTrack, 0, 0x154);
    p_ReverbDepth = (void*)RedNew(0x18);
    memset(p_ReverbDepth, 0, 0x18);
    m_Mute[1] = 0;
    m_Mute[0] = 0;
    p_MusicNextPlay = (int*)RedNew(0x10);
    p_MusicNextPlay[0] = -1;
    m_MusicPhraseStop = 0;
    p_Stream = (RedStreamDATA*)RedNew(0x4c0);
    memset(p_Stream, 0, 0x4c0);
    m_DMAMode = 0;
    memset(m_DmaControl, 0, sizeof(m_DmaControl));
    p_DmaControlNow[0] = RedDriverMainDmaQueue();
    p_DmaControlOld[0] = RedDriverMainDmaQueue();
    p_DmaControlNow[1] = RedDriverStreamDmaQueue();
    p_DmaControlOld[1] = RedDriverStreamDmaQueue();
    m_RedMasterTime = 0;
    AXRegisterCallback(_RedAXCallback);
    AXFXSetHooks(ReverbAreaAlloc, ReverbAreaFree);
    InitReverb();
    OSInitSemaphore(&m_DmaExecuteSemaphore, 0);
    p_DmaExecuteThreadStack = (void*)RedNew(0x1000);
    OSCreateThread(&m_DmaExecuteThread, (void* (*)(void*))_DmaExecuteThread, 0, (char*)p_DmaExecuteThreadStack + 0x1000, 0x1000,
                   3, 1);
    OSResumeThread(&m_DmaExecuteThread);
    OSInitSemaphore(&m_WaveSettingSemaphore, 0);
    p_WaveSettingThreadStack = (void*)RedNew(0x1000);
    OSCreateThread(&m_WaveSettingThread, (void* (*)(void*))_WaveSettingThread, &m_WaveSettingData,
                   (char*)p_WaveSettingThreadStack + 0x1000, 0x1000, 4, 1);
    OSResumeThread(&m_WaveSettingThread);
    OSInitSemaphore(&m_MusicSkipSemaphore, 0);
    p_MusicSkipThreadStack = (void*)RedNew(0x1000);
    OSCreateThread(&m_MusicSkipThread, (void* (*)(void*))_MusicSkipThread, 0, (char*)p_MusicSkipThreadStack + 0x1000, 0x1000,
                   4, 1);
    OSResumeThread(&m_MusicSkipThread);
    OSInitSemaphore(&m_MainSemaphore, 0);
    m_MainThreadTime = 0;
    p_MainThreadStack = (void*)RedNew(0x1000);
    OSCreateThread(&RedDriverMainThread(), (void* (*)(void*))_MainThread, 0, (char*)p_MainThreadStack + 0x1000, 0x1000,
                   4, 1);
    OSResumeThread(&RedDriverMainThread());
}

/*
 * --INFO--
 * PAL Address: 0x801beb78
 * PAL Size: 140b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedDriver::End()
{
    RedDriverSyncState& sync = RedDriverSync();

    AXRegisterCallback(0);
    m_ThreadControl = 0;
    OSSignalSemaphore(&sync.m_mainSemaphore);
    OSSignalSemaphore(&sync.m_waveSemaphore);
    OSSignalSemaphore(&sync.m_dmaSemaphore);
    OSSignalSemaphore(&sync.m_musicSemaphore);
    while (m_ThreadExecute != 0) {
        RedSleep(0);
    }
    AXRegisterAuxACallback(0, 0);
    AXRegisterAuxBCallback(0, 0);
}

/*
 * --INFO--
 * PAL Address: 0x801bec04
 * PAL Size: 68b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedDriver::GetProgramTime()
{
    int sum = 0;
    int* p = p_Tick;

    do {
        sum += *p;
        p++;
    } while (p < p_Tick + 100);
    return sum;
}

/*
 * --INFO--
 * PAL Address: 0x801bec48
 * PAL Size: 72b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedDriver::SetSoundMode(int soundMode)
{
    _EntryExecCommand(_SetSoundMode, soundMode, 0, 0, 0, 0, 0, 0);
}

/*
 * --INFO--
 * PAL Address: 0x801bec90
 * PAL Size: 72b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedDriver::GetSoundMode()
{
    int soundMode = __OSReadROM();

    if (soundMode == 0) {
        m_SoundPlayMode = 1;
    } else {
        m_SoundPlayMode = m_SoundMode;
    }
    return m_SoundPlayMode;
}

/*
 * --INFO--
 * PAL Address: 0x801becd8
 * PAL Size: 276b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedDriver::SetMusicData(void* musicData)
{
    char localHeader[0x20];
    void* copiedHeader;
    int headerSize;
    int result;

    result = -1;
    if (((((char*)musicData)[0] == 'B') && (((char*)musicData)[1] == 'G')) && (((char*)musicData)[2] == 'M')) {
        memcpy(localHeader, musicData, sizeof(localHeader));
        headerSize = *(int*)(localHeader + 0x10);
        copiedHeader = (void*)RedNew(headerSize);
        if (copiedHeader != 0) {
            memcpy(copiedHeader, musicData, headerSize);
            result = *(short*)(localHeader + 4);
            _EntryExecCommand(_SetMusicData, (int)copiedHeader, 0, 0, 0, 0, 0, 0);
        }
    } else if (m_ReportPrint != 0) {
        OSReport(sRedDriverMusicHeaderErrorFmt, sRedDriverLogPrefix, sRedDriverLogWarnColor, sRedDriverLogReset);
        fflush(__files + 1);
    }
    return result;
}

/*
 * --INFO--
 * PAL Address: 0x801bedec
 * PAL Size: 92b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedDriver::ReentryMusicData(int musicID)
{
    unsigned int interrupt;

    interrupt = OSDisableInterrupts();
    musicID   = c_RedEntry.ReentryMusicData(musicID);
    OSRestoreInterrupts(interrupt);
    return musicID;
}

/*
 * --INFO--
 * PAL Address: 0x801bee48
 * PAL Size: 72b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedDriver::MusicStop(int musicID)
{
    _EntryExecCommand(_MusicStop, musicID, 0, 0, 0, 0, 0, 0);
}

/*
 * --INFO--
 * PAL Address: 0x801BEE90
 * PAL Size: 88b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedDriver::MusicPlay(int musicID, int volume, int mode)
{
    _EntryExecCommand(_MusicPlaySequence, musicID, volume, mode, 0, 0, 0, 0);
    return musicID;
}

/*
 * --INFO--
 * PAL Address: 0x801beee8
 * PAL Size: 88b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedDriver::MusicCrossPlay(int musicID, int volume, int mode)
{
    _EntryExecCommand(_MusicCrossPlaySequence, musicID, volume, mode, 0, 0, 0, 0);
    return musicID;
}

/*
 * --INFO--
 * PAL Address: 0x801bef40
 * PAL Size: 88b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedDriver::MusicNextPlay(int musicID, int volume, int mode)
{
    _EntryExecCommand(_MusicNextPlaySequence, musicID, volume, mode, 0, 0, 0, 0);
    return musicID;
}

/*
 * --INFO--
 * PAL Address: 0x801bef98
 * PAL Size: 72b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedDriver::MusicMasterVolume(int volume)
{
    _EntryExecCommand(_MusicMasterVolume, volume, 0, 0, 0, 0, 0, 0);
}

/*
 * --INFO--
 * PAL Address: 0x801befe0
 * PAL Size: 76b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedDriver::MusicFadeOut(int musicID, int fadeTime)
{
    _EntryExecCommand(_MusicVolume, musicID, 0, fadeTime, 1, 0, 0, 0);
}

/*
 * --INFO--
 * PAL Address: 0x801bf02c
 * PAL Size: 80b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedDriver::MusicVolume(int musicID, int volume, int frameCount)
{
    _EntryExecCommand(_MusicVolume, musicID, volume, frameCount, 0, 0, 0, 0);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedDriver::SetMusicPhraseStop(int stop)
{
    _EntryExecCommand(_SetMusicPhraseStop, stop, 0, 0, 0, 0, 0, 0);
}

/*
 * --INFO--
 * PAL Address: 0x801bf0c4
 * PAL Size: 168b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void* CRedDriver::SetSeBlockData(int blockIndex, void* seBlockData)
{
    void* copiedBuffer;
    int copySize;

    if (seBlockData != 0) {
        copySize = *(int*)((char*)seBlockData + 0xc);
        if (copySize > 0) {
            copiedBuffer = (void*)RedNew(copySize);
            if (copiedBuffer != 0) {
                memcpy(copiedBuffer, seBlockData, copySize);
            }
        } else {
            copiedBuffer = 0;
        }
    } else {
        copiedBuffer = 0;
    }
    _EntryExecCommand(_SetSeBlockData, blockIndex, (int)copiedBuffer, 0, 0, 0, 0, 0);
    return copiedBuffer;
}

/*
 * --INFO--
 * PAL Address: 0x801bf16c
 * PAL Size: 288b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedDriver::SetSeSepData(void* seSepData)
{
    void* copiedHeader;
    int headerSize;
    int result;

    result = -1;
    if ((((((char*)seSepData)[0] == 'S') && (((char*)seSepData)[1] == 'e')) && (((char*)seSepData)[2] == 'S')) &&
        ((((char*)seSepData)[3] == 'e' && (((char*)seSepData)[4] == 'p')))) {
        headerSize = *(int*)((char*)seSepData + 0xc) & 0x7fffffff;
        copiedHeader = (void*)RedNew(headerSize);
        if (copiedHeader != 0) {
            memcpy(copiedHeader, seSepData, headerSize);
            result = *(int*)((int)copiedHeader + 8);
            _EntryExecCommand(_SetSeSepData, (int)copiedHeader, 0, 0, 0, 0, 0, 0);
        }
    } else if (m_ReportPrint != 0) {
        OSReport(sRedDriverSeSepHeaderErrorFmt, sRedDriverLogPrefix,
                 sRedDriverLogWarnColor, sRedDriverLogReset);
        fflush(__files + 1);
    }
    return result;
}

/*
 * --INFO--
 * PAL Address: 0x801bf28c
 * PAL Size: 72b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedDriver::ClearSeSepData(int id)
{
    _EntryExecCommand(_ClearSeSepData, id, 0, 0, 0, 0, 0, 0);
}

/*
 * --INFO--
 * PAL Address: 0x801bf2d4
 * PAL Size: 84b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedDriver::ClearSeSepDataMG(int id1, int id2, int id3, int id4)
{
    _EntryExecCommand(_ClearSeSepDataMG, id1, id2, id3, id4, 0, 0, 0);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CRedDriver::ReentrySeSepData(int id)
{
    unsigned int interrupts;

    interrupts = OSDisableInterrupts();
    id         = c_RedEntry.ReentrySeSepData(id);
    OSRestoreInterrupts(interrupts);
    return id;
}

/*
 * --INFO--
 * PAL Address: 0x801bf384
 * PAL Size: 288b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedDriver::SePlayState(int seID)
{
    unsigned int uVar1;
    int result;
    int* seInfo;
    int** seInfoBase;
    int* commandNow;
    int* command;

    uVar1 = OSDisableInterrupts();
    result = 0;
    seInfoBase = (int**)((int)p_SoundControlBuffer + 0xdbc);
    seInfo = *seInfoBase;
    do {
        if (((u32)*seInfo != 0) && ((seID == -1 || (seInfo[0x3e] == seID)))) {
            result = (int)seInfo;
            break;
        }
        seInfo += 0x55;
    } while (seInfo < (int*)((int)*seInfoBase + 0x2a80));
    if (result == 0) {
        commandNow = (int*)p_ExecCommandNow;
        command = (int*)p_ExecCommandOld;
        while (commandNow != command) {
            if ((((u32)*command != 0) &&
                ((((void (*)(int*))*command == _SeBlockPlay) ||
                  (((void (*)(int*))*command == _SeSepPlay))) ||
                 ((void (*)(int*))*command == _SeSepPlaySequence))) &&
                ((seID == -1 || (seID == command[1])))) {
                result = 1;
                break;
            }
            command += 8;
            if (command == (int*)p_ExecCommand + 0x800) {
                command = (int*)p_ExecCommand;
            }
        }
    }
    OSRestoreInterrupts(uVar1);
    return result;
}

/*
 * --INFO--
 * PAL Address: 0x801bf4a4
 * PAL Size: 72b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedDriver::SeStop(int id)
{
    _EntryExecCommand(_SeStop, id, 0, 0, 0, 0, 0, 0);
}

/*
 * --INFO--
 * PAL Address: 0x801bf4ec
 * PAL Size: 84b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedDriver::SeStopMG(int id1, int id2, int id3, int id4)
{
    _EntryExecCommand(_SeStopMG, id1, id2, id3, id4, 0, 0, 0);
}

/*
 * --INFO--
 * PAL Address: 0x801bf540
 * PAL Size: 196b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedDriver::SePlay(int bank, int sep, int autoID, int unk, int volume, int pitch)
{
	if (bank == -1) {
		if (sep >= 0) {
			_EntryExecCommand(_SeSepPlaySequence, autoID, sep, unk, volume, pitch, 0, 0);
		}
	} else if ((bank >= 0) && (bank < 4) && (sep >= 0) && (sep < 0x200)) {
		_EntryExecCommand(_SeBlockPlay, autoID, bank, sep, unk, volume, pitch, 0);
	}
    return autoID;
}

/*
 * --INFO--
 * PAL Address: 0x801bf604
 * PAL Size: 72b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedDriver::SeMasterVolume(int volume)
{
    _EntryExecCommand(_SeMasterVolume, volume, 0, 0, 0, 0, 0, 0);
}

/*
 * --INFO--
 * PAL Address: 0x801bf64c
 * PAL Size: 76b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedDriver::SeFadeOut(int seID, int fadeTime)
{
    _EntryExecCommand(_SeVolume, seID, 0, fadeTime, 1, 0, 0, 0);
}

/*
 * --INFO--
 * PAL Address: 0x801bf698
 * PAL Size: 80b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedDriver::SeVolume(int seID, int volume, int frameCount)
{
    _EntryExecCommand(_SeVolume, seID, volume, frameCount, 0, 0, 0, 0);
}

/*
 * --INFO--
 * PAL Address: 0x801bf6e8
 * PAL Size: 80b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedDriver::SePan(int seID, int pan, int frameCount)
{
    _EntryExecCommand(_SePan, seID, pan, frameCount, 0, 0, 0, 0);
}

/*
 * --INFO--
 * PAL Address: 0x801bf738
 * PAL Size: 80b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedDriver::SePitch(int seID, int pitch, int frameCount)
{
    _EntryExecCommand(_SePitch, seID, pitch, frameCount, 0, 0, 0, 0);
}

/*
 * --INFO--
 * PAL Address: 0x801bf788
 * PAL Size: 76b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedDriver::SePause(int seID, int pause)
{
    _EntryExecCommand(_SePause, seID, pause, 0, 0, 0, 0, 0);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CRedDriver::GetSeVolume(int seID, int mode)
{
    unsigned int* seInfo;

    seInfo = *(unsigned int**)((int)p_SoundControlBuffer + 0xdbc);
    while (1) {
        if ((*seInfo != 0) && ((seID == -1) || (seID == (int)seInfo[0x3e]))) {
            if (*seInfo != 0) {
                if (mode == 1) {
                    return seInfo[0x15];
                }
                return (int)seInfo[0x13] >> 0xc;
            }
        }
        seInfo += 0x55;
        if (seInfo < (unsigned int*)(*(int*)((int)p_SoundControlBuffer + 0xdbc) + 0x2a80)) {
            continue;
        }
        return 0;
    }
}

/*
 * --INFO--
 * PAL Address: 0x801bf854
 * PAL Size: 108b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedDriver::ReportSeLoop(int seID)
{
    unsigned int* seInfo;

    seInfo = *(unsigned int**)((int)p_SoundControlBuffer + 0xdbc);
    while (1) {
        if ((*seInfo != 0) &&
            (((seID == -1) || (seID == (int)seInfo[0x3e])) && ((seInfo[0x40] & 1U) != 0))) {
            return 1;
        }
        seInfo += 0x55;
        if (seInfo < (unsigned int*)(*(int*)((int)p_SoundControlBuffer + 0xdbc) + 0x2a80)) {
            continue;
        }
        return 0;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedDriver::DisplaySePlayInfo()
{
	c_RedEntry.DisplaySePlayInfo();
}

/*
 * --INFO--
 * PAL Address: 0x801bf8e8
 * PAL Size: 240b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedDriver::StreamPlayState(int streamID)
{
	void* commandNow;
	unsigned int interrupts;
	unsigned int streamData;
	int result;
	unsigned int* command;

	interrupts = OSDisableInterrupts();
	result = 0;
	streamData = (unsigned int)p_Stream;
	do {
		if ((*(int*)(streamData + 0x10C) != 0) &&
		    ((streamID == -1) || (*(int*)(streamData + 0x10C) == streamID))) {
			result = 1;
			break;
		}
		streamData += 0x130;
	} while (streamData < (unsigned int)p_Stream + 0x4C0);

	if (result == 0) {
		commandNow = p_ExecCommandNow;
		command = (unsigned int*)p_ExecCommandOld;
		while (commandNow != (void*)command) {
			if ((*command != 0) && ((void (*)(int*))*command == _StreamPlay) &&
			    ((streamID == -1) || (streamID == (int)command[1]))) {
				result = 1;
				break;
			}
			command += 8;
			if (command == (unsigned int*)p_ExecCommand + 0x800) {
				command = (unsigned int*)p_ExecCommand;
			}
		}
	}
	OSRestoreInterrupts(interrupts);
	return result;
}

/*
 * --INFO--
 * PAL Address: 0x801bf9d8
 * PAL Size: 156b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedDriver::GetStreamPlayPoint(int streamID, int* outPoint1, int* outPoint2)
{
	unsigned int streamData;
	int found;

	found = 0;
	if (outPoint1 != 0) {
		*outPoint1 = 0;
	}
	if (outPoint2 != 0) {
		*outPoint2 = 0;
	}
	streamData = (unsigned int)p_Stream;
	do {
		if ((*(int*)(streamData + 0x10C) != 0) && (*(int*)(streamData + 0x10C) == streamID)) {
			if (outPoint1 != 0) {
				*outPoint1 = *(int*)(streamData + 0x11C);
			}
			if (outPoint2 != 0) {
				*outPoint2 = *(int*)(streamData + 0x120);
			}
			found = 1;
			break;
		}
		streamData += 0x130;
	} while (streamData < (unsigned int)p_Stream + 0x4C0);
	return found;
}

/*
 * --INFO--
 * PAL Address: 0x801bfa74
 * PAL Size: 72b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedDriver::StreamStop(int streamID)
{
    _EntryExecCommand(_StreamStop, streamID, 0, 0, 0, 0, 0, 0);
}

/*
 * --INFO--
 * PAL Address: 0x801bfabc
 * PAL Size: 96b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedDriver::StreamPlay(int streamID, void* streamData, int volume, int pan, int loopMode)
{
	_EntryExecCommand(_StreamPlay, streamID, (int)streamData, volume, pan, loopMode, 0, 0);
	return streamID;
}

/*
 * --INFO--
 * PAL Address: 0x801bfb1c
 * PAL Size: 80b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedDriver::StreamVolume(int streamID, int volume, int frameCount)
{
    _EntryExecCommand(_StreamVolume, streamID, volume, frameCount, 0, 0, 0, 0);
}

/*
 * --INFO--
 * PAL Address: 0x801bfb6c
 * PAL Size: 76b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedDriver::StreamPause(int streamID, int pause)
{
    _EntryExecCommand(_StreamPause, streamID, pause, 0, 0, 0, 0, 0);
}

/*
 * --INFO--
 * PAL Address: 0x801bfbb8
 * PAL Size: 48b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedDriver::ClearWaveData(int waveID)
{
    c_RedEntry.ClearWaveData(waveID);
}

/*
 * --INFO--
 * PAL Address: 0x801bfbe8
 * PAL Size: 72b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedDriver::ClearWaveDataM(int param_1, int param_2, int param_3, int param_4)
{
    c_RedEntry.ClearWaveDataM(param_1, param_2, param_3, param_4);
}

/*
 * --INFO--
 * PAL Address: 0x801bfc30
 * PAL Size: 48b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedDriver::ClearWaveBank(int waveBank)
{
    c_RedEntry.ClearWaveBank(waveBank);
}

/*
 * --INFO--
 * PAL Address: 0x801bfc60
 * PAL Size: 276b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedDriver::SetWaveData(int slot, int waveID, void* waveData, int waveSize)
{
    while (true) {
        if (m_WaveSettingStatus == 0) {
            break;
        }

        RedSleep(0);
    }

    m_WaveSettingData.slot = slot;
    m_WaveSettingData.waveID = waveID;
    m_WaveSettingData.waveData = waveData;

    if (waveSize == -1) {
        RedWaveHEAD* const waveHeader = (RedWaveHEAD*)waveData;

        if ((waveHeader->magic[0] == 'W') && (waveHeader->magic[1] == 'D')) {
            int dataSize =
                (((waveHeader->regionCount * 4) + 0x3fU) & 0xffffffc0) + (waveHeader->sampleCount * 0x60);
            dataSize = waveHeader->dataSize + dataSize;
            dataSize += 0x20;
            m_WaveSettingData.waveSize = dataSize;
        } else {
            m_WaveSettingData.waveSize = 0;
        }
    } else {
        m_WaveSettingData.waveSize = waveSize;
    }
    OSSignalSemaphore(&m_WaveSettingSemaphore);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CRedDriver::ReentryWaveData(int id)
{
    unsigned int interrupts;

    interrupts = OSDisableInterrupts();
    id         = c_RedEntry.ReentryWaveData(id);
    OSRestoreInterrupts(interrupts);
    return id;
}

/*
 * --INFO--
 * PAL Address: 0x801bfdd0
 * PAL Size: 40b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedDriver::DisplayWaveInfo()
{
    c_RedEntry.DisplayWaveInfo();
}

/*
 * --INFO--
 * PAL Address: 0x801BFDF8
 * PAL Size: 92b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedDriver::SetReverb(int bank, int kind)
{
    ::SetReverb(bank, *(int*)((char*)t_ReverbModeData + kind * 0x1c),
                (int*)((char*)t_ReverbModeData + kind * 0x1c + 4));
}

/*
 * --INFO--
 * PAL Address: 0x801bfe54
 * PAL Size: 80b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedDriver::SetReverbDepth(int bank, int mode, int depth)
{
    _EntryExecCommand(_SetReverbDepth, bank, mode, depth, 0, 0, 0, 0);
}

/*
 * --INFO--
 * PAL Address: 0x801bfea4
 * PAL Size: 52b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedDriver::TestProcess(int processType)
{
    switch (processType) {
    case 1:
        _DMACheckProcess();
        break;
    }
}
