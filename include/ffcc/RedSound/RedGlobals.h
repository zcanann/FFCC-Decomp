#ifndef FFCC_REDSOUND_REDGLOBALS_H
#define FFCC_REDSOUND_REDGLOBALS_H

#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/file_io.h"
#include "dolphin/os.h"
#include "ffcc/RedSound/RedStream.h"
#include "types.h"

class CRedDriver;
class CRedEntry;
class CRedMemory;

extern int p_MidiControl_Function[];
extern u32 t_TonePitch[];
extern int t_FinePitch[];
extern int t_KeySignatureIndex[];
extern signed char t_KeySignatureData[];
extern signed char t_RandomData[];
extern s16 t_PanningData[];
extern s16 t_PanningDataR[];
extern int m_SignDataTable[];
extern int t_ReverbModeData[];
extern CRedEntry c_RedEntry;
extern OSSemaphore m_MusicSkipSemaphore;
extern void* p_SeBlockData[];
extern void* p_ZeroData;
extern void* p_SoundControlBuffer;
extern void* volatile p_SoundControl;
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
extern RedStreamDATA* volatile p_Stream;
extern int m_SeSkipStep;
extern unsigned int* volatile p_VoiceData;
extern int p_EditorVoice[2];
extern void* p_EditorTrack;
extern void* p_MusicSkipThreadStack;
extern int m_MusicSkipComplete;
extern void* p_ReverbDepth;
extern int m_Mute[2];
extern CRedMemory c_RedMemory;
extern volatile u32 m_ChangeStatus;
extern CRedDriver c_Driver;

#endif
