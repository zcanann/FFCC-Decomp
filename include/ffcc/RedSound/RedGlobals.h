#ifndef FFCC_REDSOUND_REDGLOBALS_H
#define FFCC_REDSOUND_REDGLOBALS_H

#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/file_io.h"
#include "dolphin/os.h"
#include "ffcc/RedSound/RedStream.h"
#include "types.h"

class CRedDriver;
class CRedEntry;
class CRedMemory;

extern int gRedCommandHandlerTable[];
extern FILE DAT_8021d1a8;
extern u32 DAT_8021d7f0[];
extern int DAT_8021d820[];
extern int DAT_8021dc20[];
extern signed char DAT_8021dcce[];
extern s16 DAT_8021ddce[];
extern s16 DAT_8021de4e;
extern s16 DAT_8021dfce[];
extern int DAT_8021e1d0[];
extern int DAT_8021ec10[];
extern CRedEntry c_RedEntry;
extern OSSemaphore m_MusicSkipSemaphore;
extern void* p_SeBlockData[];
extern void* p_ZeroData;
extern void* p_SoundControlBuffer;
extern void* p_SoundControl;
extern int m_KeyOnEntry;
extern void* p_KeyOnData;
extern int m_SoundPlayMode;
extern int m_SoundMasterControl;
extern int m_ReportPrint;
extern int m_MusicFastSpeed;
extern int m_MusicSkipLine;
extern int m_MusicKeySignature;
extern void* p_MusicReplayPoint;
extern int* p_MusicTempoControl;
extern int* p_MusicPitchControl;
extern int m_MusicPhraseStop;
extern int m_CrossTime;
extern int m_MasterMusicVolume;
extern int m_MasterSEVolume;
extern RedStreamDATA* p_Stream;
extern int m_SeSkipStep;
extern unsigned int* p_VoiceData;
extern int p_EditorVoice[2];
extern void* p_EditorTrack;
extern void* p_MusicSkipThreadStack;
extern int m_MusicSkipComplete;
extern void* p_ReverbDepth;
extern int m_Mute[2];
extern CRedMemory c_RedMemory;
extern int m_DMAExecute;
extern int m_DMAInThread;
extern int m_DataBuffer;
extern int m_ADataBuffer;
extern int m_DataBufferSize;
extern int m_ADataBufferSize;
extern int* m_MemoryBank;
extern int* m_AMemoryBank;
extern u32 m_ChangeStatus;
extern CRedDriver c_Driver;

#endif
