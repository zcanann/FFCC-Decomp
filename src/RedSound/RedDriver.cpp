#include "ffcc/RedSound/RedDriver.h"
#include "ffcc/RedSound/RedMemory.h"
#include "ffcc/RedSound/RedEntry.h"
#include "ffcc/RedSound/RedStream.h"
#include "ffcc/RedSound/RedCommand.h"
#include "ffcc/RedSound/RedExecute.h"
#include "ffcc/RedSound/RedGlobals.h"
#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/file_io.h"
#include "dolphin/ar.h"
#include "dolphin/ax.h"
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
    void __dl__FPv(void*);
    void* RedNew__Fi(int);
    void RedDelete__FPv(void*);
    void* memcpy(void*, const void*, unsigned long);
    void* memmove(void*, const void*, unsigned long);
    void* memset(void*, int, unsigned long);
    void SetMusicData__9CRedEntryFP12RedMusicHEAD(CRedEntry*, RedMusicHEAD*);
    int SetSeSepData__9CRedEntryFP12RedSeSepHEAD(CRedEntry*, RedSeSepHEAD*);
    void ClearSeSepData__9CRedEntryFi(CRedEntry*, int);
    void ClearSeSepDataMG__9CRedEntryFiiii(void*, int, int, int, int);
    int ReentrySeSepData__9CRedEntryFi(void*, int);
    int ReentryMusicData__9CRedEntryFi(void*, int);
    int SearchMusicSequence__9CRedEntryFi(void*, int);
    int SearchSeSepSequence__9CRedEntryFi(void*, int);
    int ReentryWaveData__9CRedEntryFi(void*, int);
    void ClearWaveData__9CRedEntryFi(void*, int);
    void ClearWaveDataM__9CRedEntryFiiii(void*, int, int, int, int);
    void ClearWaveBank__9CRedEntryFi(void*, int);
    void MusicStop__Fi(int);
    void MusicPlay__Fiii(int, int, int);
    void AXSetCompressor(int);
    void AXFXSetHooks(void (*)(unsigned long), void (*)(void*));
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
int m_RedMasterTime;
int m_SequencialID;
int m_ThreadControl;
int m_ThreadExecute;
int m_SoundMode;
int* p_Tick;
void* p_ZeroData;
void* p_ExecCommand;
void* p_ExecCommandNow;
void* p_ExecCommandOld;
void* p_DmaControlNow[2];
void* p_DmaControlOld[2];
void* p_SoundControlBuffer;
void* p_SoundControl;
int m_KeyOnEntry;
void* p_KeyOnData;
int m_SoundPlayMode;
int m_SoundMasterControl;
int m_ReportPrint;
int m_MusicFastSpeed;
int m_MusicSkipLine;
int m_MusicKeySignature;
void* p_MusicReplayPoint;
int* p_MusicTempoControl;
int* p_MusicPitchControl;
int m_MusicPhraseStop;
int* p_MusicNextPlay;
int m_CrossTime;
int m_MasterMusicVolume;
int m_MasterSEVolume;
RedStreamDATA* p_Stream;
int m_DMAMode;
int m_SeSkipStep;
unsigned int* p_VoiceData;
int p_EditorVoice[2];
void* p_EditorTrack;
void* p_MainThreadStack;
int m_MainThreadTime;
void* p_WaveSettingThreadStack;
int m_WaveSettingStatus;
void* p_DmaExecuteThreadStack;
int m_DMAStatus;
void* p_MusicSkipThreadStack;
int m_MusicSkipComplete;
void* p_ReverbDepth;
int m_Mute[2];
CRedMemory c_RedMemory;
int m_DMAExecute;
int m_DMAInThread;
u8 gRedDriverSyncBuffer[0x1F18];
OSSemaphore m_MainSemaphore;
OSThread m_WaveSettingThread;
OSSemaphore m_WaveSettingSemaphore;
RedWaveSettingState m_WaveSettingData;
OSThread m_DmaExecuteThread;
OSSemaphore m_DmaExecuteSemaphore;
ARQRequest m_DMARequest;
OSThread m_MusicSkipThread;
OSSemaphore m_MusicSkipSemaphore;
void* p_SeBlockData[4];
CRedEntry c_RedEntry;

static inline RedDriverSyncState& RedDriverSync()
{
    return *reinterpret_cast<RedDriverSyncState*>(gRedDriverSyncBuffer);
}

static inline int* RedDriverMainDmaQueue()
{
    return RedDriverSync().m_dmaQueue;
}

static inline int* RedDriverStreamDmaQueue()
{
    return RedDriverSync().m_streamDmaQueue;
}

static inline int* RedDriverStreamDmaQueueEnd()
{
    return reinterpret_cast<int*>(&RedDriverSync().m_mainThread);
}

static inline OSThread& RedDriverMainThread()
{
    return RedDriverSync().m_mainThread;
}

extern void ReverbAreaAlloc(unsigned long);
extern void ReverbAreaFree(void*);
extern void InitReverb();

/*
 * --INFO--
 * PAL Address: 0x801bcf0c
 * PAL Size: 124b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void _SetSoundMode(int* param_1)
{
    m_SoundMode = *param_1;
    if (*param_1 == 1) {
        OSGetSoundMode(0);
    } else {
        OSGetSoundMode(1);
    }
    if ((m_SoundPlayMode = m_SoundMode) != 2) {
        AXSetMode(0);
    } else {
        AXSetMode(2);
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
void _SetReverbDepth(int* param_1)
{
    unsigned int reverbIndex;
    unsigned int reverbDepth;
    unsigned int fadeFrame;
    int fadeStep;
    int* seInfo;

    reverbIndex = (unsigned int)param_1[0];
    reverbDepth = (unsigned int)param_1[1] & 0x7f;
    fadeFrame = (unsigned int)param_1[2];
    if (reverbDepth != 0) {
        reverbDepth = (((reverbDepth + 1) * 0x100) - 1) * 0x1000;
    }
    *(unsigned int*)((char*)p_ReverbDepth + (reverbIndex & 1) * 0xc) = reverbDepth;
    if ((reverbIndex & 1) != 0) {
        fadeStep = (int)(fadeFrame * 0x60) / 0x3c + ((int)(fadeFrame * 0x60) >> 0x1f);
        fadeStep = fadeStep - (fadeStep >> 0x1f);
        if (fadeStep == 0) {
            fadeStep = 1;
        }
        seInfo = *(int**)((char*)p_SoundControlBuffer + 0xdbc);
        do {
            if (*seInfo != 0) {
                seInfo[0x1b] = (int)((reverbDepth | 0x800) - (seInfo[0x1a] & 0xfffff000U)) / fadeStep;
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
void _SetMusicData(int* param_1)
{
    SetMusicData__9CRedEntryFP12RedMusicHEAD(&c_RedEntry, (RedMusicHEAD*)*param_1);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _MusicStop(int* param_1)
{
    MusicStop__Fi(*param_1);
    if ((*param_1 == -1) || (p_MusicNextPlay[0] == *param_1)) {
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
void _MusicPlaySequence(int* param_1)
{
    int iVar1;
    int srcBuffer;

    srcBuffer = (int)p_SoundControlBuffer;
    if ((((*param_1 != *(int*)(srcBuffer + 0x470)) &&
          (*param_1 != *(int*)(srcBuffer + 0x904))) &&
         (*param_1 != *(int*)(srcBuffer + 0xd98))) &&
        ((iVar1 = SearchMusicSequence__9CRedEntryFi(&c_RedEntry, *param_1)), -1 < iVar1)) {
        iVar1 = param_1[2];
        if (*(int*)(srcBuffer + 0x470) != -1) {
            if (*(int*)(srcBuffer + 0x904) != -1) {
                MusicStop__Fi(*(int*)(srcBuffer + 0x904));
            }
            if (iVar1 == 0) {
                iVar1 = *(int*)((int)p_MusicReplayPoint + *param_1 * 4);
                *(int*)((int)p_MusicReplayPoint + *param_1 * 4) = 0;
            }
            if (iVar1 == 0) {
                memcpy((void*)(srcBuffer + 0x494), (void*)srcBuffer, 0x494);
                *(int*)(srcBuffer + 0x470) = -1;
            }
        }
        MusicPlay__Fiii(*param_1, param_1[1], iVar1);
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
void _MusicCrossPlaySequence(int* param_1)
{
    int iVar1;
    void* pvVar2;
    
    param_1[2] = param_1[2] * 200;
    iVar1 = param_1[2] / 0x3c + (param_1[2] >> 0x1f);
    param_1[2] = iVar1 - (iVar1 >> 0x1f);
    if (param_1[2] == 0) {
        param_1[2] = param_1[2] + 1;
    }
    pvVar2 = p_SoundControlBuffer;
    if ((*param_1 != *(int*)((int)p_SoundControlBuffer + 0x470)) &&
       (*param_1 != *(int*)((int)p_SoundControlBuffer + 0xd98))) {
        if (*param_1 == *(int*)((int)p_SoundControlBuffer + 0x904)) {
            *(int*)((int)p_SoundControlBuffer + 0x458) = -*(int*)((int)p_SoundControlBuffer + 0x454) / param_1[2];
            *(int*)((int)pvVar2 + 0x45c) = param_1[2];
            pvVar2 = p_SoundControlBuffer;
            *(int*)((int)p_SoundControlBuffer + 0x8ec) =
                 (0x1ff800 - *(int*)((int)p_SoundControlBuffer + 0x8e8)) / param_1[2];
            *(int*)((int)pvVar2 + 0x8f0) = param_1[2];
            pvVar2 = RedNew__Fi(0x494);
            memcpy(pvVar2, (void*)((int)p_SoundControlBuffer + 0x494), 0x494);
            memcpy((void*)((int)p_SoundControlBuffer + 0x494), p_SoundControlBuffer, 0x494);
            memcpy(p_SoundControlBuffer, pvVar2, 0x494);
            RedDelete__FPv(pvVar2);
        }
        else {
            iVar1 = SearchMusicSequence__9CRedEntryFi(&c_RedEntry, *param_1);
            if (-1 < iVar1) {
                m_CrossTime = param_1[2];
                iVar1 = 0;
                if (*(int*)((int)pvVar2 + 0x470) != -1) {
                    if (*(int*)((int)pvVar2 + 0x904) != -1) {
                        MusicStop__Fi(*(int*)((int)pvVar2 + 0x904));
                    }
                    *(int*)((int)pvVar2 + 0x458) = -*(int*)((int)pvVar2 + 0x454) / param_1[2];
                    *(int*)((int)pvVar2 + 0x45c) = param_1[2];
                    iVar1 = *(int*)((char*)p_MusicReplayPoint + *param_1 * 4);
                    *(int*)((char*)p_MusicReplayPoint + *param_1 * 4) = 0;
                    if (iVar1 == 0) {
                        memcpy((void*)((int)pvVar2 + 0x494), pvVar2, 0x494);
                        *(int*)((int)pvVar2 + 0x470) = 0xffffffff;
                    }
                }
                MusicPlay__Fiii(*param_1, param_1[1], iVar1);
            }
        }
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _MusicNextPlaySequence(int* param_1)
{
    int iVar1;

    if ((((*param_1 != *(int*)((int)p_SoundControlBuffer + 0x470)) &&
          (*param_1 != *(int*)((int)p_SoundControlBuffer + 0x904))) &&
         (*param_1 != *(int*)((int)p_SoundControlBuffer + 0xd98))) &&
        ((iVar1 = SearchMusicSequence__9CRedEntryFi(&c_RedEntry, *param_1)), -1 < iVar1)) {
        p_MusicNextPlay[0] = *param_1;
        p_MusicNextPlay[1] = param_1[1];
        p_MusicNextPlay[2] = param_1[2];
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _MusicMasterVolume(int* param_1)
{
    unsigned int* puVar1;

    m_MasterMusicVolume = *param_1 & 0x7f;
    puVar1 = p_VoiceData;
    if (m_MasterMusicVolume != 0) {
        m_MasterMusicVolume = (m_MasterMusicVolume + 1) * 4 - 1;
    }
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
void _MusicVolume(int* param_1)
{
    if (param_1[3] == 1) {
        p_MusicNextPlay[0] = -1;
        m_MusicPhraseStop = 0;
    }
    SetMusicVolume(param_1[0], param_1[1], param_1[2], param_1[3]);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _SetMusicPhraseStop(int* param_1)
{
    m_MusicPhraseStop = *param_1;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _SetSeBlockData(int* param_1)
{
    u32 index = (u32)*param_1 & 3;
    char* seBlockData;

    if (p_SeBlockData[index] != 0) {
        RedDelete__FPv(p_SeBlockData[index]);
        p_SeBlockData[index] = 0;
    }

    if (param_1[1] != 0) {
        seBlockData = (char*)param_1[1];
        if ((*seBlockData = 'S') && (seBlockData[1] = 'e') && (seBlockData[2] = 'B') &&
            (seBlockData[3] = 'l') && (seBlockData[4] = 'o') && (seBlockData[5] = 'c') &&
            (seBlockData[6] = 'k')) {
            p_SeBlockData[index] = seBlockData;
        } else {
            RedDelete__FPv(seBlockData);
        }
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _SetSeSepData(int* param_1)
{
    SetSeSepData__9CRedEntryFP12RedSeSepHEAD(&c_RedEntry, (RedSeSepHEAD*)*param_1);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _ClearSeSepData(int* param_1)
{
    ClearSeSepData__9CRedEntryFi(&c_RedEntry, *param_1);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _ClearSeSepDataMG(int* param_1)
{
    ClearSeSepDataMG__9CRedEntryFiiii(&c_RedEntry, param_1[0], param_1[1], param_1[2], param_1[3]);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _SeStop(int* param_1)
{
    SeStopID(param_1[0]);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _SeStopMG(int* param_1)
{
    SeStopMG(param_1[0], param_1[1], param_1[2], param_1[3]);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _SeBlockPlay(int* param_1)
{
    m_SeSkipStep = param_1[5];
    SeBlockPlay(param_1[0], param_1[1], param_1[2], param_1[3], param_1[4]);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _SeSepPlay(int* param_1)
{
    int iVar1;

    iVar1 = SetSeSepData__9CRedEntryFP12RedSeSepHEAD(&c_RedEntry, (RedSeSepHEAD*)param_1[1]);
    if (iVar1 != 0) {
        m_SeSkipStep = param_1[4];
        SeSepPlay(param_1[0], *(int*)(iVar1 + 8), param_1[2], param_1[3]);
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _SeSepPlaySequence(int* param_1)
{
    int iVar1;

    iVar1 = SearchSeSepSequence__9CRedEntryFi(&c_RedEntry, param_1[1]);
    if (iVar1 >= 0) {
        m_SeSkipStep = param_1[4];
        SeSepPlay(param_1[0], param_1[1], param_1[2], param_1[3]);
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _SeMasterVolume(int* param_1)
{
    unsigned int* puVar1;

    m_MasterSEVolume = *param_1 & 0x7f;
    puVar1 = p_VoiceData;
    if (m_MasterSEVolume != 0) {
        m_MasterSEVolume = (m_MasterSEVolume + 1) * 4 - 1;
    }
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
void _SeVolume(int* param_1)
{
    SetSeVolume(param_1[0], param_1[1], param_1[2], param_1[3]);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _SePan(int* param_1)
{
    SetSePan(param_1[0], param_1[1], param_1[2]);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _SePitch(int* param_1)
{
    SetSePitch(param_1[0], param_1[1], param_1[2]);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _SePause(int* param_1)
{
    SePause(param_1[0], param_1[1]);
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
void _StreamStop(int* param_1)
{
	StreamStop(*param_1);
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
void _StreamPlay(int* param_1)
{
	StreamPlay(param_1[0], (void*)param_1[1], param_1[2], param_1[3], param_1[4]);
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
void _StreamVolume(int* param_1)
{
	SetStreamVolume(param_1[0], param_1[1], param_1[2]);
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
void _StreamPause(int* param_1)
{
	StreamPause(param_1[0], param_1[1]);
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
void _EntryExecCommand(void (*param_1)(int*), int param_2, int param_3, int param_4, int param_5,
                       int param_6, int param_7, int param_8)
{
    unsigned int interruptLevel;
    int* writePos;
    int* nextPos;

    interruptLevel = OSDisableInterrupts();
    writePos = (int*)p_ExecCommandNow;
    writePos[0] = (int)param_1;
    writePos[1] = param_2;
    writePos[2] = param_3;
    writePos[3] = param_4;
    writePos[4] = param_5;
    writePos[5] = param_6;
    writePos[6] = param_7;
    writePos[7] = param_8;
    nextPos = writePos + 8;
    if (nextPos == (int*)p_ExecCommand + 0x800) {
        nextPos = (int*)p_ExecCommand;
    }
    p_ExecCommandNow = nextPos;
    OSRestoreInterrupts(interruptLevel);
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
	unsigned int* executePos = (unsigned int*)p_ExecCommandNow;
	unsigned int* readPos = (unsigned int*)p_ExecCommandOld;

	while (executePos != readPos) {
		if (*readPos != 0) {
			((void (*)(int*))(*readPos))((int*)(readPos + 1));
		}
		readPos += 8;
		if (readPos == (unsigned int*)p_ExecCommand + 0x800) {
			readPos = (unsigned int*)p_ExecCommand;
		}
	}

	p_ExecCommandOld = readPos;
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
    m_SequencialID = (m_SequencialID + 1) & 0x7fffffff;
    if (m_SequencialID == 0) {
        m_SequencialID = 1;
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
void _MyAlarmHandler(OSAlarm* param_1, OSContext*)
{
    OSResumeThread(((RedSleepAlarm*)param_1)->thread);
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
void RedSleep(int param_1)
{
    unsigned int interruptLevel;
    OSThread* currentThread;
    RedSleepAlarm alarm;

    if (param_1 < 0xfa) {
        param_1 = 0xfa;
    }
    interruptLevel = OSDisableInterrupts();
    currentThread = OSGetCurrentThread();
    OSCreateAlarm(&alarm.alarm);
    alarm.thread = currentThread;
    OSSetAlarm(&alarm.alarm, (param_1 * (OS_BUS_CLOCK / 500000)) >> 3, _MyAlarmHandler);
    OSSuspendThread(currentThread);
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
int _WaveSettingThread(void* param_1)
{
    int threadResult;
    RedWaveSettingState* waveSetting;

    waveSetting = (RedWaveSettingState*)param_1;
    m_ThreadExecute = m_ThreadExecute | 4;
    m_WaveSettingStatus = 0;
    while (m_ThreadControl != 0) {
        OSWaitSemaphore(&m_WaveSettingSemaphore);
        if (m_ThreadControl != 0) {
            m_WaveSettingStatus = m_WaveSettingStatus + 1;
            c_RedEntry.SetWaveData(waveSetting->waveID, waveSetting->waveData, waveSetting->waveSize);
            *(int*)waveSetting->slot = 0;
            do {
                threadResult = OSTryWaitSemaphore(&m_WaveSettingSemaphore);
            } while (0 < threadResult);
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
    int semCount;
    int* dmaInfo;

    if (m_ReportPrint != 0) {
        OSReport("[%s]------DMA_CHECK_PROCESS------\n", "RedDriver");
        fflush(&DAT_8021d1a8);

        semCount = OSGetSemaphoreCount(&m_DmaExecuteSemaphore);
        OSReport("[%s]Status = %d Semaphore = %d Entry = %d/%d\n", "RedDriver", m_DMAStatus, semCount, m_DMAExecute,
                 m_DMAInThread);
        fflush(&DAT_8021d1a8);
    }

    dmaInfo = RedDriverMainDmaQueue();
    do {
        if ((*dmaInfo != 0) && (m_ReportPrint != 0)) {
            OSReport("[%s]ID = %d MMem = %8.8X AMem = %8.8X Size = %d %d\n", "RedDriver", dmaInfo[0], dmaInfo[2], dmaInfo[3], dmaInfo[4], dmaInfo[5]);
            fflush(&DAT_8021d1a8);
        }
        dmaInfo += 7;
    } while (dmaInfo < RedDriverStreamDmaQueueEnd());

    fflush(&DAT_8021d1a8);
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

    do {
        do {
            if ((p_DmaControlNow[0] == p_DmaControlOld[0]) && (p_DmaControlNow[1] == p_DmaControlOld[1])) {
                m_DMAInThread = 0;
                return;
            }
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
                piVar6 = piVar7;
            }
            piVar8 = piVar7 + 7;
            if (piVar4 + 0x380 <= piVar7 + 7) {
                piVar8 = piVar4;
            }
            *ppiVar5 = piVar8;
        } while (piVar6 == 0);
        while (piVar6 != 0) {
            m_DMAInThread = 7;
            if (m_DMAStatus == 0) {
                m_DMAInThread = 8;
                if (piVar6[5] != 0) {
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
    } while (true);
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
            m_DMAExecute = 0;
        }
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
extern "C" CRedDriver* __dt__10CRedDriverFv(CRedDriver* redDriver, short shouldDelete)
{
    if ((redDriver != 0) && (0 < shouldDelete)) {
        __dl__FPv(redDriver);
    }
    return redDriver;
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
    p_Tick = (int*)RedNew__Fi(400);
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
    p_ZeroData = RedNew__Fi(0x1000);
    memset(p_ZeroData, 0, 0x1000);
    p_MusicReplayPoint = RedNew__Fi(0x400);
    memset(p_MusicReplayPoint, 0, 0x400);
    p_MusicTempoControl = (int*)RedNew__Fi(0xc);
    memset(p_MusicTempoControl, 0, 0xc);
    p_MusicPitchControl = (int*)RedNew__Fi(0xc);
    memset(p_MusicPitchControl, 0, 0xc);
    p_ExecCommand = RedNew__Fi(0x2000);
    p_ExecCommandNow = p_ExecCommand;
    p_ExecCommandOld = p_ExecCommand;
    memset(p_ExecCommand, 0, 0x2000);
    p_SoundControlBuffer = RedNew__Fi(0x1250);
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
    p_KeyOnData = RedNew__Fi(0x600);
    memset(p_KeyOnData, 0, 0x600);
    p_VoiceData = (unsigned int*)RedNew__Fi(0x3000);
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
    uVar3 = RedNew__Fi(0x2a80);
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
    p_EditorTrack = RedNew__Fi(0x154);
    memset(p_EditorTrack, 0, 0x154);
    p_ReverbDepth = RedNew__Fi(0x18);
    memset(p_ReverbDepth, 0, 0x18);
    m_Mute[1] = 0;
    m_Mute[0] = 0;
    p_MusicNextPlay = (int*)RedNew__Fi(0x10);
    p_MusicNextPlay[0] = -1;
    m_MusicPhraseStop = 0;
    p_Stream = (RedStreamDATA*)RedNew__Fi(0x4c0);
    memset(p_Stream, 0, 0x4c0);
    m_DMAMode = 0;
    memset(&gRedDriverSyncBuffer, 0, 0x1c00);
    p_DmaControlNow[0] = RedDriverMainDmaQueue();
    p_DmaControlOld[0] = RedDriverMainDmaQueue();
    p_DmaControlNow[1] = RedDriverStreamDmaQueue();
    p_DmaControlOld[1] = RedDriverStreamDmaQueue();
    m_RedMasterTime = 0;
    AXRegisterCallback(_RedAXCallback);
    AXFXSetHooks(ReverbAreaAlloc, ReverbAreaFree);
    InitReverb();
    OSInitSemaphore(&m_DmaExecuteSemaphore, 0);
    p_DmaExecuteThreadStack = RedNew__Fi(0x1000);
    OSCreateThread(&m_DmaExecuteThread, (void* (*)(void*))_DmaExecuteThread, 0, (char*)p_DmaExecuteThreadStack + 0x1000, 0x1000,
                   3, 1);
    OSResumeThread(&m_DmaExecuteThread);
    OSInitSemaphore(&m_WaveSettingSemaphore, 0);
    p_WaveSettingThreadStack = RedNew__Fi(0x1000);
    OSCreateThread(&m_WaveSettingThread, (void* (*)(void*))_WaveSettingThread, &m_WaveSettingData,
                   (char*)p_WaveSettingThreadStack + 0x1000, 0x1000, 4, 1);
    OSResumeThread(&m_WaveSettingThread);
    OSInitSemaphore(&m_MusicSkipSemaphore, 0);
    p_MusicSkipThreadStack = RedNew__Fi(0x1000);
    OSCreateThread(&m_MusicSkipThread, (void* (*)(void*))_MusicSkipThread, 0, (char*)p_MusicSkipThreadStack + 0x1000, 0x1000,
                   4, 1);
    OSResumeThread(&m_MusicSkipThread);
    OSInitSemaphore(&m_MainSemaphore, 0);
    m_MainThreadTime = 0;
    p_MainThreadStack = RedNew__Fi(0x1000);
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

    while (p < p_Tick + 100) {
        sum += *p;
        p++;
    }
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
int CRedDriver::SetMusicData(void* param_1)
{
    char localHeader[0x20];
    char* musicHeader = (char*)param_1;
    void* copiedHeader;
    int headerSize;
    short musicID;

    if (((musicHeader[0] == 'B') && (musicHeader[1] == 'G')) && (musicHeader[2] == 'M')) {
        memcpy(localHeader, musicHeader, sizeof(localHeader));
        headerSize = *(int*)(localHeader + 0x10);
        copiedHeader = RedNew__Fi(headerSize);
        if (copiedHeader != 0) {
            memcpy(copiedHeader, musicHeader, headerSize);
            _EntryExecCommand(_SetMusicData, (int)copiedHeader, 0, 0, 0, 0, 0, 0);
            musicID = *(short*)(localHeader + 4);
            return musicID;
        }
        return -1;
    }
    if (m_ReportPrint != 0) {
        OSReport("Music Header was broken.\n");
        fflush(&DAT_8021d1a8);
    }
    return -1;
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
    int result;

    interrupt = OSDisableInterrupts();
    result = ReentryMusicData__9CRedEntryFi(&c_RedEntry, musicID);
    OSRestoreInterrupts(interrupt);
    return result;
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
void CRedDriver::MusicVolume(int param_1, int param_2, int param_3)
{
    _EntryExecCommand(_MusicVolume, param_1, param_2, param_3, 0, 0, 0, 0);
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
void CRedDriver::SetSeBlockData(int param_1, void* param_2)
{
    void* copiedBuffer = 0;
    int copySize;

    if (param_2 != 0) {
        copySize = *(int*)((char*)param_2 + 0xc);
        if (copySize < 1) {
        } else {
            copiedBuffer = RedNew__Fi(copySize);
            if (copiedBuffer != 0) {
                memcpy(copiedBuffer, param_2, copySize);
            }
        }
    }
    _EntryExecCommand(_SetSeBlockData, param_1, (int)copiedBuffer, 0, 0, 0, 0, 0);
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
int CRedDriver::SetSeSepData(void* param_1)
{
    int iVar1;
    int iVar2;
    void* pvVar3;
    char* pcVar4;

    pcVar4 = (char*)param_1;
    if ((((pcVar4[0] == 'S') && (pcVar4[1] == 'e')) && (pcVar4[2] == 'S')) &&
        ((pcVar4[3] == 'e' && (pcVar4[4] == 'p')))) {
        iVar1 = *(int*)(pcVar4 + 0xc) & 0x7fffffff;
        pvVar3 = RedNew__Fi(iVar1);
        if (pvVar3 != 0) {
            memcpy(pvVar3, param_1, iVar1);
            iVar2 = *(int*)((int)pvVar3 + 8);
            _EntryExecCommand(_SetSeSepData, (int)pvVar3, 0, 0, 0, 0, 0, 0);
            return iVar2;
        }
        return -1;
    }
    if (m_ReportPrint != 0) {
        OSReport("SE Sep Header was broken.\n");
        fflush(&DAT_8021d1a8);
    }
    return -1;
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
    int result;

    interrupts = OSDisableInterrupts();
    result = ReentrySeSepData__9CRedEntryFi(&c_RedEntry, id);
    OSRestoreInterrupts(interrupts);
    return result;
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
int CRedDriver::SePlayState(int param_1)
{
    unsigned int uVar1;
    int* piVar2;
    int* piVar3;

    uVar1 = OSDisableInterrupts();
    piVar3 = *(int**)((int)p_SoundControlBuffer + 0xdbc);
    do {
        piVar2 = piVar3;
        if ((*piVar2 != 0) && ((param_1 == -1 || (piVar2[0x3e] == param_1)))) {
            break;
        }
        piVar3 = piVar2 + 0x55;
        piVar2 = 0;
    } while (piVar3 < (int*)(*(int*)((int)p_SoundControlBuffer + 0xdbc) + 0x2a80));
    piVar3 = (int*)p_ExecCommandOld;
    if (piVar2 == 0) {
        while ((int*)p_ExecCommandNow != piVar3) {
            if (((*piVar3 != 0) &&
                ((((void (*)(int*))*piVar3 == _SeBlockPlay) ||
                  (((void (*)(int*))*piVar3 == _SeSepPlay))) ||
                 ((void (*)(int*))*piVar3 == _SeSepPlaySequence))) &&
                ((param_1 == -1 || (param_1 == piVar3[1])))) {
                piVar2 = (int*)1;
                break;
            }
            piVar3 = piVar3 + 8;
            if (piVar3 == (int*)p_ExecCommand + 0x800) {
                piVar3 = (int*)p_ExecCommand;
            }
        }
    }
    OSRestoreInterrupts(uVar1);
    return (int)piVar2;
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
void CRedDriver::SeVolume(int param_1, int param_2, int param_3)
{
    _EntryExecCommand(_SeVolume, param_1, param_2, param_3, 0, 0, 0, 0);
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
void CRedDriver::SePan(int param_1, int param_2, int param_3)
{
    _EntryExecCommand(_SePan, param_1, param_2, param_3, 0, 0, 0, 0);
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
void CRedDriver::SePitch(int param_1, int param_2, int param_3)
{
    _EntryExecCommand(_SePitch, param_1, param_2, param_3, 0, 0, 0, 0);
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
void CRedDriver::SePause(int param_1, int param_2)
{
    _EntryExecCommand(_SePause, param_1, param_2, 0, 0, 0, 0, 0);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CRedDriver::GetSeVolume(int param_1, int param_2)
{
    int* seInfo;

    seInfo = *(int**)((int)p_SoundControlBuffer + 0xdbc);
    while (1) {
        if ((*seInfo != 0) && ((param_1 == -1) || (param_1 == seInfo[0x3e]))) {
            if (param_2 == 1) {
                return seInfo[0x15];
            }
            return seInfo[0x13] >> 0xc;
        }
        seInfo += 0x55;
        if ((int*)(*(int*)((int)p_SoundControlBuffer + 0xdbc) + 0x2a80) <= seInfo) {
            return 0;
        }
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
int CRedDriver::ReportSeLoop(int param_1)
{
    unsigned int* seInfo;

    seInfo = *(unsigned int**)((int)p_SoundControlBuffer + 0xdbc);
    while (1) {
        if ((*seInfo != 0) &&
            (((param_1 == -1) || (param_1 == (int)seInfo[0x3e])) && ((seInfo[0x40] & 1U) != 0))) {
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
int CRedDriver::StreamPlayState(int param_1)
{
	unsigned int interrupts;
	unsigned int streamData;
	int result;
	int* command;

	interrupts = OSDisableInterrupts();
	result = 0;
	streamData = (unsigned int)p_Stream;
	do {
		if ((*(int*)(streamData + 0x10C) != 0) &&
		    ((param_1 == -1) || (*(int*)(streamData + 0x10C) == param_1))) {
			result = 1;
			break;
		}
		streamData += 0x130;
	} while (streamData < (unsigned int)p_Stream + 0x4C0);

	command = (int*)p_ExecCommandOld;
	if (result == 0) {
		while ((void*)command != p_ExecCommandNow) {
			if ((*command != 0) && ((void (*)(int*))*command == _StreamPlay) &&
			    ((param_1 == -1) || (param_1 == command[1]))) {
				result = 1;
				break;
			}
			command += 8;
			if (command == (int*)p_ExecCommand + 0x800) {
				command = (int*)p_ExecCommand;
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
int CRedDriver::GetStreamPlayPoint(int param_1, int* param_2, int* param_3)
{
	unsigned int streamData;
	int found;

	found = 0;
	if (param_2 != 0) {
		*param_2 = 0;
	}
	if (param_3 != 0) {
		*param_3 = 0;
	}
	streamData = (unsigned int)p_Stream;
	while (streamData < (unsigned int)p_Stream + 0x4C0) {
		if ((*(int*)(streamData + 0x10C) != 0) && (*(int*)(streamData + 0x10C) == param_1)) {
			if (param_2 != 0) {
				*param_2 = *(int*)(streamData + 0x11C);
			}
			if (param_3 != 0) {
				*param_3 = *(int*)(streamData + 0x120);
			}
			found = 1;
			break;
		}
		streamData += 0x130;
	}
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
void CRedDriver::StreamStop(int param_1)
{
    _EntryExecCommand(_StreamStop, param_1, 0, 0, 0, 0, 0, 0);
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
int CRedDriver::StreamPlay(int param_1, void* param_2, int param_3, int param_4, int param_5)
{
	int streamID = param_1;
	int data = (int)param_2;
	int arg3 = param_3;
	int arg4 = param_4;
	int arg5 = param_5;

	_EntryExecCommand(_StreamPlay, streamID, data, arg3, arg4, arg5, 0, 0);
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
void CRedDriver::StreamVolume(int param_1, int param_2, int param_3)
{
    _EntryExecCommand(_StreamVolume, param_1, param_2, param_3, 0, 0, 0, 0);
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
void CRedDriver::StreamPause(int param_1, int param_2)
{
    _EntryExecCommand(_StreamPause, param_1, param_2, 0, 0, 0, 0, 0);
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
void CRedDriver::ClearWaveData(int param_1)
{
    ClearWaveData__9CRedEntryFi(&c_RedEntry, param_1);
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
    ClearWaveDataM__9CRedEntryFiiii(&c_RedEntry, param_1, param_2, param_3, param_4);
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
void CRedDriver::ClearWaveBank(int param_1)
{
    ClearWaveBank__9CRedEntryFi(&c_RedEntry, param_1);
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
    m_WaveSettingData.waveSize = waveSize;

    if (waveSize == -1) {
        RedWaveHEAD* const waveHeader = (RedWaveHEAD*)waveData;

        if ((waveHeader->magic[0] == 'W') && (waveHeader->magic[1] == 'D')) {
            m_WaveSettingData.waveSize =
                waveHeader->dataSize + (((waveHeader->regionCount * 4) + 0x3fU) & 0xffffffc0) +
                (waveHeader->sampleCount * 0x60) + 0x20;
        } else {
            m_WaveSettingData.waveSize = 0;
        }
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
    int result;

    interrupts = OSDisableInterrupts();
    result = ReentryWaveData__9CRedEntryFi(&c_RedEntry, id);
    OSRestoreInterrupts(interrupts);
    return result;
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
    ::SetReverb(bank, *(int*)((char*)DAT_8021ec10 + kind * 0x1c), (int*)((char*)DAT_8021ec10 + kind * 0x1c + 4));
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
