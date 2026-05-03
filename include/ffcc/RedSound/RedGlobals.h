#ifndef FFCC_REDSOUND_REDGLOBALS_H
#define FFCC_REDSOUND_REDGLOBALS_H

#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/file_io.h"
#include "dolphin/os.h"
#include "ffcc/RedSound/RedMidiCtrl.h"
#include "ffcc/RedSound/RedStream.h"
#include "types.h"

class CRedDriver;
class CRedEntry;
class CRedMemory;

struct RedControlRamp {
	int m_value;
	int m_step;
	int m_count;
};

struct RedReverbDepth {
	int m_depth;
	int m_step;
	int m_count;
};

enum RedSoundControlIndex {
	REDSOUND_CONTROL_MUSIC_PRIMARY = 0,
	REDSOUND_CONTROL_MUSIC_SECONDARY = 1,
	REDSOUND_CONTROL_MUSIC_SKIP = 2,
	REDSOUND_CONTROL_SE = 3,
};

enum RedSoundLayoutSize {
	REDSOUND_TRACK_SIZE = sizeof(RedTrackDATA),
	REDSOUND_CONTROL_SIZE = 0x494,
	REDSOUND_CONTROL_COUNT = 4,
	REDSOUND_CONTROL_BUFFER_SIZE = REDSOUND_CONTROL_SIZE * REDSOUND_CONTROL_COUNT,
	REDSOUND_CONTROL_SECONDARY_OFFSET = REDSOUND_CONTROL_SIZE * REDSOUND_CONTROL_MUSIC_SECONDARY,
	REDSOUND_CONTROL_SKIP_OFFSET = REDSOUND_CONTROL_SIZE * REDSOUND_CONTROL_MUSIC_SKIP,
	REDSOUND_SE_TRACK_COUNT = 0x20,
	REDSOUND_SE_TRACK_ARENA_SIZE = REDSOUND_TRACK_SIZE * REDSOUND_SE_TRACK_COUNT,
	REDSOUND_VOICE_COUNT = 0x40,
	REDSOUND_VOICE_SIZE = sizeof(RedVoiceDATA),
	REDSOUND_VOICE_BUFFER_SIZE = REDSOUND_VOICE_SIZE * REDSOUND_VOICE_COUNT,
	REDSOUND_KEY_ON_BUFFER_SIZE = sizeof(RedKeyOnDATA),
	REDSOUND_CONTROL_RAMP_SIZE = sizeof(RedControlRamp),
	REDSOUND_REVERB_DEPTH_COUNT = 2,
	REDSOUND_REVERB_DEPTH_BUFFER_SIZE = sizeof(RedReverbDepth) * REDSOUND_REVERB_DEPTH_COUNT,
	REDSOUND_STREAM_COUNT = 4,
	REDSOUND_STREAM_BUFFER_SIZE = sizeof(RedStreamDATA) * REDSOUND_STREAM_COUNT,
};

enum RedSoundFixedPoint {
	REDSOUND_FIXED_SHIFT = 12,
	REDSOUND_FIXED_HALF = 0x800,
	REDSOUND_FIXED_ONE = 0x1000,
	REDSOUND_VOLUME_FULL = 0x7FFF000,
	REDSOUND_VOLUME_DEFAULT = 0x7F000,
	REDSOUND_PAN_CENTER = 0x40000,
};

struct RedSeBlockHEAD;

extern RedMidiControlFunc p_MidiControl_Function[];
extern u32 t_TonePitch[];
extern int t_FinePitch[];
extern int t_KeySignatureIndex[];
extern signed char t_KeySignatureData[];
extern signed char t_RandomData[];
extern s16 t_PanningData[];
extern s16 t_PanningDataR[];
extern CRedEntry c_RedEntry;
extern OSSemaphore m_MusicSkipSemaphore;
extern RedSeBlockHEAD* volatile p_SeBlockData[];
extern u8* volatile p_ZeroData;
extern RedSoundCONTROL* volatile p_SoundControlBuffer;
extern RedSoundCONTROL* volatile p_SoundControl;
extern volatile int m_KeyOnEntry;
extern RedKeyOnDATA* volatile p_KeyOnData;
extern int m_SoundPlayMode;
extern int m_SoundMasterControl;
extern volatile int m_ReportPrint;
extern int m_MusicFastSpeed;
extern volatile int m_MusicSkipLine;
extern int m_MusicKeySignature;
extern int* volatile p_MusicReplayPoint;
extern RedControlRamp* volatile p_MusicTempoControl;
extern RedControlRamp* volatile p_MusicPitchControl;
extern int m_MusicPhraseStop;
extern int m_CrossTime;
extern volatile int m_MasterMusicVolume;
extern volatile int m_MasterSEVolume;
extern RedStreamDATA* volatile p_Stream;
extern volatile int m_SeSkipStep;
extern RedVoiceDATA* volatile p_VoiceData;
extern int p_EditorVoice[2];
extern RedTrackDATA* p_EditorTrack;
extern u8* volatile p_MusicSkipThreadStack;
extern volatile int m_MusicSkipComplete;
extern RedReverbDepth* volatile p_ReverbDepth;
extern int m_Mute[2];
extern CRedMemory c_RedMemory;
extern volatile u32 m_ChangeStatus;
extern CRedDriver c_Driver;

#endif
