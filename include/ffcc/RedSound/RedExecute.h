#ifndef _FFCC_REDSOUND_REDEXECUTE_H
#define _FFCC_REDSOUND_REDEXECUTE_H

#include <dolphin/ax.h>
#include "types.h"

class AXFX_BUFFERUPDATE;
struct RedTrackDATA;
struct RedSoundCONTROL;
struct RedKeyOnDATA;

struct RedReverbDATA {
	int callback;
	void* context;
	int kind;
};

struct RedReverbSize {
	u32 m_requested;
	u32 m_aligned;
};

struct RedNoteDATA {
	signed char m_key;
	signed char m_velocity;
	unsigned char m_allocFlags;
	unsigned char m_pad03;
};

struct RedWaveDATA {
	unsigned int m_flags;
	int m_sampleStart;
	int m_loopStart;
	int m_loopEnd;
	unsigned char m_pad10[0x14 - 0x10];
	int m_pitch;
	signed char m_splitKey;
	unsigned char m_splitVelocity;
	unsigned char m_volume;
	unsigned char m_pan;
	signed char m_reverbMix;
	unsigned char m_pad1D[0x22 - 0x1D];
	unsigned char m_adpcmData[0x4A - 0x22];
	unsigned char m_adpcmLoop[0x50 - 0x4A];
	unsigned char m_adsr[0x5C - 0x50];
	unsigned char m_pad5C[0x60 - 0x5C];
};

struct RedVoiceDATA {
	RedTrackDATA* m_track;
	RedWaveDATA* m_waveData;
	int* m_trackVolume;
	int* m_trackExpression;
	int* m_trackPan;
	AXVPB* m_axVoice;
	signed char m_key;
	signed char m_velocity;
	unsigned char m_stateFlags;
	unsigned char m_notePad;
	int m_pitchModPhase;
	int m_pitchModFrames;
	int m_pitchModFrame;
	short m_pitchModDelay;
	unsigned char m_pad2A[0x2C - 0x2A];
	int m_volumeModPhase;
	int m_volumeModFrames;
	int m_volumeModFrame;
	short m_volumeModDelay;
	unsigned char m_pad3A[0x3C - 0x3A];
	int m_randomPitch;
	int m_randomVolume;
	int m_randomPan;
	unsigned char m_pad48[0x50 - 0x48];
	unsigned short m_adsrTime[4];
	unsigned char m_adsrLevel[4];
	int m_adsrStage;
	int m_adsrStepFrames;
	int m_adsrStepAdd;
	unsigned short m_axMix[0x12];
	int m_active;
	unsigned int m_flags;
	unsigned int m_voiceSwitch;
	int m_pitch;
	int m_targetPitch;
	int m_basePitch;
	unsigned char m_padA4[0xA8 - 0xA4];
	int m_voiceIndex;
	int m_adsrCurrentLevel;
	int m_envelopeLevel;
	unsigned char m_padB4[0xB8 - 0xB4];
	unsigned int m_updateFlags;
	unsigned char m_padBC[0xC0 - 0xBC];
};

enum RedVoiceCleanupMask {
	REDSOUND_VOICE_STATE_CLEAR_PLAYING_MASK = -6,
	REDSOUND_VOICE_SWITCH_SUSTAIN = 4,
	REDSOUND_VOICE_SWITCH_PAUSE = 8,
	REDSOUND_VOICE_SWITCH_FUZZY_PITCH = 0x4000,
	REDSOUND_VOICE_SWITCH_FUZZY_VOLUME = 0x8000,
	REDSOUND_VOICE_SWITCH_FUZZY_PAN = 0x10000,
	REDSOUND_VOICE_SWITCH_FUZZY_DELTA_TIME = 0x20000,
	REDSOUND_VOICE_SWITCH_FUZZY_ADSR = 0x40000,
	REDSOUND_VOICE_SWITCH_CLEAR_PAUSE_MASK = ~REDSOUND_VOICE_SWITCH_PAUSE,
	REDSOUND_VOICE_SWITCH_CLEAR_SE_MASK = 0xfffffff7,
	REDSOUND_VOICE_FLAGS_START = 1,
	REDSOUND_VOICE_FLAGS_CLEAR_ACTIVE_MASK = 0xfffffffe,
	REDSOUND_VOICE_FLAGS_RELEASED = 2,
	REDSOUND_VOICE_FLAGS_ADPCM_DIRTY = 8,
	REDSOUND_VOICE_FLAGS_PITCH_DIRTY = 0x10,
	REDSOUND_VOICE_FLAGS_PAUSE_DIRTY = REDSOUND_VOICE_FLAGS_ADPCM_DIRTY | REDSOUND_VOICE_FLAGS_PITCH_DIRTY,
	REDSOUND_VOICE_FLAGS_STREAM_START =
	    REDSOUND_VOICE_FLAGS_START | REDSOUND_VOICE_FLAGS_ADPCM_DIRTY | REDSOUND_VOICE_FLAGS_PITCH_DIRTY,
};

enum RedVoiceUpdateFlag {
	REDSOUND_VOICE_UPDATE_PITCH = 1,
	REDSOUND_VOICE_UPDATE_VOLUME = 2,
	REDSOUND_VOICE_UPDATE_ALL = REDSOUND_VOICE_UPDATE_PITCH | REDSOUND_VOICE_UPDATE_VOLUME,
};

u8 GetRandomData();
int PitchCompute(int, int, int, int);
void _ReverbNullCallback(AXFX_BUFFERUPDATE*, void*);
void* ReverbAreaAlloc(unsigned long);
void ReverbAreaFree(void*);
void InitReverb();
void _SetReverbData(RedReverbDATA*, int*);
void _ClearReverb(int);
int* SetReverb(int, int, int*);

RedVoiceDATA* EntryVoiceSearch(RedTrackDATA*);
void _VoiceEnvelopeCheck();
void SetVoiceVolumeMix(RedVoiceDATA*, int, int);
void _VolumeExecute(RedVoiceDATA*, int);
void _PitchExecute(RedVoiceDATA*);
RedWaveDATA* _WaveSplitSelect(RedWaveDATA*, RedNoteDATA*);
void _VoiceDataAsign(RedTrackDATA*, RedVoiceDATA*, RedNoteDATA*, int*);
RedVoiceDATA* _VoiceDataSelect(RedTrackDATA*, RedNoteDATA*, int*);
void SetVoiceAccess(RedTrackDATA*, int);
void SetVoiceSwitch(RedTrackDATA*, int);

void _AdsrStart(RedVoiceDATA*);
void _AdsrDataCompute(RedVoiceDATA*);
u32 _AdsrDataExecute(RedVoiceDATA*);
void _VoiceDropedCallback(void*);
void EnvelopeKeyExecute();
void _KeyOnControl();
void _ExecuteExtraData();

void _MusicTrackDataExecute(RedTrackDATA*, int);
void _MidiTrackExecute(RedSoundCONTROL*, RedKeyOnDATA*, int);
int _MusicMidiNoteExecute(RedSoundCONTROL*, RedKeyOnDATA*, int);
void _MusicNoteExecute();
int _MusicMidiNoteSkipExecute(RedSoundCONTROL*, RedKeyOnDATA*, int);
void _SkipMusicEntry();
void MusicSkipFunction();

void _SeTrackDataExecute(RedTrackDATA*, int);
int _SeMidiNoteExecute(RedSoundCONTROL*, RedKeyOnDATA*, RedTrackDATA*, int, int);

void MainControl(int);

#endif // _FFCC_REDSOUND_REDEXECUTE_H
