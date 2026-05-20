#ifndef _FFCC_REDSOUND_REDEXECUTE_H
#define _FFCC_REDSOUND_REDEXECUTE_H

#include <dolphin/ax.h>
#include "types.h"

class AXFX_BUFFERUPDATE;
struct RedTrackDATA;
struct RedSoundCONTROL;
struct RedKeyOnDATA;

enum RedReverbKind {
	REDSOUND_REVERB_KIND_NONE = 0,
	REDSOUND_REVERB_KIND_STD = 1,
	REDSOUND_REVERB_KIND_HI = 2,
	REDSOUND_REVERB_KIND_DELAY = 3,
	REDSOUND_REVERB_KIND_CHORUS = 4,
	REDSOUND_REVERB_KIND_HI_DPL2 = 5,
};

struct RedReverbDATA {
	int m_callback;
	void* m_context;
	RedReverbKind m_kind;
};

#define REDSOUND_REVERB_CONTEXT_NONE ((void*)0)

enum RedReverbCallbackValue {
	REDSOUND_REVERB_CALLBACK_NONE = 0,
};

enum RedReverbLayoutOffset {
	REDSOUND_REVERB_CALLBACK_OFFSET = (unsigned int)&(((RedReverbDATA*)0)->m_callback),
	REDSOUND_REVERB_CONTEXT_OFFSET = (unsigned int)&(((RedReverbDATA*)0)->m_context),
	REDSOUND_REVERB_KIND_OFFSET = (unsigned int)&(((RedReverbDATA*)0)->m_kind),
	REDSOUND_REVERB_SIZE = sizeof(RedReverbDATA),
};

struct RedReverbSize {
	u32 m_requested;
	u32 m_aligned;
};

enum RedReverbSizeLayoutOffset {
	REDSOUND_REVERB_SIZE_REQUESTED_OFFSET = (unsigned int)&(((RedReverbSize*)0)->m_requested),
	REDSOUND_REVERB_SIZE_ALIGNED_OFFSET = (unsigned int)&(((RedReverbSize*)0)->m_aligned),
	REDSOUND_REVERB_SIZE_SIZE = sizeof(RedReverbSize),
};

struct RedNoteDATA {
	signed char m_key;
	signed char m_velocity;
	unsigned char m_allocFlags;
	unsigned char m_reserved03;
};

#define RedNoteCopy(dst, src) (*(int*)&(dst)->m_key = *(int*)&(src)->m_key)
#define RedNoteGetKey(note) (*(char*)&(note)->m_key)
#define RedVoiceSetNote(voice, note) (*(int*)&(voice)->m_key = *(int*)&(note)->m_key)

enum RedNoteLayoutOffset {
	REDSOUND_NOTE_KEY_OFFSET = (unsigned int)&(((RedNoteDATA*)0)->m_key),
	REDSOUND_NOTE_VELOCITY_OFFSET = (unsigned int)&(((RedNoteDATA*)0)->m_velocity),
	REDSOUND_NOTE_ALLOC_FLAGS_OFFSET = (unsigned int)&(((RedNoteDATA*)0)->m_allocFlags),
	REDSOUND_NOTE_RESERVED03_OFFSET = (unsigned int)&(((RedNoteDATA*)0)->m_reserved03),
	REDSOUND_NOTE_SIZE = sizeof(RedNoteDATA),
};

enum RedNoteLayoutSize {
	REDSOUND_NOTE_RESERVED03_SIZE = REDSOUND_NOTE_SIZE - REDSOUND_NOTE_RESERVED03_OFFSET,
};

enum RedNoteAllocFlag {
	REDSOUND_NOTE_ALLOC_NONE = 0,
	REDSOUND_NOTE_ALLOC_DIRECT = 1,
	REDSOUND_NOTE_ALLOC_STREAM = 2,
	REDSOUND_NOTE_ALLOC_RESERVED = 4,
	REDSOUND_NOTE_ALLOC_PRIORITY = 8,
	REDSOUND_NOTE_ALLOC_DIRECT_MASK = REDSOUND_NOTE_ALLOC_DIRECT | REDSOUND_NOTE_ALLOC_RESERVED,
};

#define RedNoteAllocHasDirect(flags) (((flags) & REDSOUND_NOTE_ALLOC_DIRECT) != 0)
#define RedNoteAllocHasPriority(flags) (((flags) & REDSOUND_NOTE_ALLOC_PRIORITY) != 0)
#define RedNoteAllocHasDirectMask(flags) (((static_cast<s8>(flags)) & REDSOUND_NOTE_ALLOC_DIRECT_MASK) != 0)

struct RedWaveADPCMInfo {
	AXPBADPCM m_data;
	AXPBADPCMLOOP m_loop;
};

enum RedWaveAdpcmLayoutOffset {
	REDSOUND_WAVE_ADPCM_DATA_OFFSET = (unsigned int)&(((RedWaveADPCMInfo*)0)->m_data),
	REDSOUND_WAVE_ADPCM_LOOP_OFFSET = (unsigned int)&(((RedWaveADPCMInfo*)0)->m_loop),
	REDSOUND_WAVE_ADPCM_INFO_SIZE = sizeof(RedWaveADPCMInfo),
	REDSOUND_WAVE_ADPCM_DATA_SIZE = REDSOUND_WAVE_ADPCM_LOOP_OFFSET - REDSOUND_WAVE_ADPCM_DATA_OFFSET,
	REDSOUND_WAVE_ADPCM_LOOP_SIZE = REDSOUND_WAVE_ADPCM_INFO_SIZE - REDSOUND_WAVE_ADPCM_LOOP_OFFSET,
};

enum RedWaveReservedLayoutSize {
	REDSOUND_WAVE_RESERVED10_SIZE = 0x04,
	REDSOUND_WAVE_RESERVED1D_SIZE = 0x05,
	REDSOUND_WAVE_ADSR_SIZE = 0x0C,
	REDSOUND_WAVE_RESERVED5C_SIZE = 0x04,
};

enum RedVoiceLayoutCount {
	REDSOUND_VOICE_ADSR_TIME_COUNT = 4,
	REDSOUND_VOICE_ADSR_LEVEL_COUNT = 4,
	REDSOUND_VOICE_ADSR_TIME_BYTE_STRIDE = sizeof(u16),
	REDSOUND_VOICE_RESERVED1B_SIZE = 0x01,
	REDSOUND_VOICE_RESERVED2A_SIZE = 0x02,
	REDSOUND_VOICE_RESERVED3A_SIZE = 0x02,
	REDSOUND_VOICE_RESERVED48_SIZE = 0x08,
	REDSOUND_VOICE_RESERVEDA4_SIZE = 0x04,
	REDSOUND_VOICE_RESERVEDB4_SIZE = 0x04,
	REDSOUND_VOICE_RESERVEDBC_SIZE = 0x04,
	REDSOUND_TERMINATE_NOTE_WORD_COUNT = 1,
};

struct RedAdsrDATA {
	unsigned short m_time[REDSOUND_VOICE_ADSR_TIME_COUNT];
	unsigned char m_level[REDSOUND_VOICE_ADSR_LEVEL_COUNT];
};

struct RedWaveDATA {
	unsigned int m_flags;
	int m_sampleStart;
	int m_loopStart;
	int m_loopEnd;
	unsigned char m_reserved10[REDSOUND_WAVE_RESERVED10_SIZE];
	int m_pitch;
	signed char m_splitKey;
	unsigned char m_splitVelocity;
	unsigned char m_volume;
	unsigned char m_pan;
	signed char m_reverbMix;
	unsigned char m_reserved1D[REDSOUND_WAVE_RESERVED1D_SIZE];
	RedWaveADPCMInfo m_adpcm;
	RedAdsrDATA m_adsr;
	unsigned char m_reserved5C[REDSOUND_WAVE_RESERVED5C_SIZE];
};

#define REDSOUND_WAVE_DATA_NONE ((RedWaveDATA*)0)

enum RedWaveLayoutSize {
	REDSOUND_WAVE_DATA_SIZE = sizeof(RedWaveDATA),
};

enum RedWaveFlag {
	REDSOUND_WAVE_FLAG_PAIRED_ENTRY = 1,
	REDSOUND_WAVE_FLAG_SPLIT_END = 0x200,
	REDSOUND_WAVE_FLAG_SPLIT_TABLE = 0x30000,
	REDSOUND_WAVE_FLAG_USE_WAVE_KEY = 0x20000,
};

enum RedWaveLayoutOffset {
	REDSOUND_WAVE_FLAGS_OFFSET = (unsigned int)&(((RedWaveDATA*)0)->m_flags),
	REDSOUND_WAVE_SAMPLE_START_OFFSET = (unsigned int)&(((RedWaveDATA*)0)->m_sampleStart),
	REDSOUND_WAVE_LOOP_START_OFFSET = (unsigned int)&(((RedWaveDATA*)0)->m_loopStart),
	REDSOUND_WAVE_LOOP_END_OFFSET = (unsigned int)&(((RedWaveDATA*)0)->m_loopEnd),
	REDSOUND_WAVE_RESERVED10_OFFSET = (unsigned int)&(((RedWaveDATA*)0)->m_reserved10),
	REDSOUND_WAVE_PITCH_OFFSET = (unsigned int)&(((RedWaveDATA*)0)->m_pitch),
	REDSOUND_WAVE_SPLIT_KEY_OFFSET = (unsigned int)&(((RedWaveDATA*)0)->m_splitKey),
	REDSOUND_WAVE_SPLIT_VELOCITY_OFFSET = (unsigned int)&(((RedWaveDATA*)0)->m_splitVelocity),
	REDSOUND_WAVE_VOLUME_OFFSET = (unsigned int)&(((RedWaveDATA*)0)->m_volume),
	REDSOUND_WAVE_PAN_OFFSET = (unsigned int)&(((RedWaveDATA*)0)->m_pan),
	REDSOUND_WAVE_REVERB_MIX_OFFSET = (unsigned int)&(((RedWaveDATA*)0)->m_reverbMix),
	REDSOUND_WAVE_RESERVED1D_OFFSET = (unsigned int)&(((RedWaveDATA*)0)->m_reserved1D),
	REDSOUND_WAVE_ADPCM_OFFSET = (unsigned int)&(((RedWaveDATA*)0)->m_adpcm),
	REDSOUND_WAVE_ADSR_OFFSET = (unsigned int)&(((RedWaveDATA*)0)->m_adsr),
	REDSOUND_WAVE_RESERVED5C_OFFSET = (unsigned int)&(((RedWaveDATA*)0)->m_reserved5C),
};

enum RedWaveLayoutWord {
	REDSOUND_WAVE_PITCH_WORD_OFFSET = REDSOUND_WAVE_PITCH_OFFSET / sizeof(int),
};

enum RedAdsrDataLayout {
	REDSOUND_ADSR_TIME_OFFSET = (unsigned int)&(((RedAdsrDATA*)0)->m_time),
	REDSOUND_ADSR_LEVEL_OFFSET = (unsigned int)&(((RedAdsrDATA*)0)->m_level),
	REDSOUND_ADSR_DATA_SIZE = sizeof(RedAdsrDATA),
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
	unsigned char m_reserved1B;
	int m_pitchModPhase;
	int m_pitchModFrames;
	int m_pitchModFrame;
	short m_pitchModDelay;
	unsigned char m_reserved2A[REDSOUND_VOICE_RESERVED2A_SIZE];
	int m_volumeModPhase;
	int m_volumeModFrames;
	int m_volumeModFrame;
	short m_volumeModDelay;
	unsigned char m_reserved3A[REDSOUND_VOICE_RESERVED3A_SIZE];
	int m_randomPitch;
	int m_randomVolume;
	int m_randomPan;
	unsigned char m_reserved48[REDSOUND_VOICE_RESERVED48_SIZE];
	RedAdsrDATA m_adsr;
	int m_adsrStage;
	int m_adsrStepFrames;
	int m_adsrStepAdd;
	AXPBMIX m_axMix;
	int m_active;
	unsigned int m_flags;
	unsigned int m_voiceSwitch;
	int m_pitch;
	int m_targetPitch;
	int m_basePitch;
	unsigned char m_reservedA4[REDSOUND_VOICE_RESERVEDA4_SIZE];
	int m_voiceIndex;
	int m_adsrCurrentLevel;
	int m_envelopeLevel;
	unsigned char m_reservedB4[REDSOUND_VOICE_RESERVEDB4_SIZE];
	unsigned int m_updateFlags;
	unsigned char m_reservedBC[REDSOUND_VOICE_RESERVEDBC_SIZE];
};

#define REDSOUND_VOICE_TRACK_NONE 0
#define REDSOUND_VOICE_DATA_NONE 0
#define REDSOUND_AX_VOICE_NONE 0

enum RedVoiceAdsrIndex {
	REDSOUND_VOICE_ADSR_ATTACK = 0,
	REDSOUND_VOICE_ADSR_DECAY = 1,
	REDSOUND_VOICE_ADSR_SUSTAIN = 2,
	REDSOUND_VOICE_ADSR_RELEASE = 3,
	REDSOUND_VOICE_ADSR_DONE = 4,
};

enum RedVoiceLayoutOffset {
	REDSOUND_VOICE_TRACK_OFFSET = (unsigned int)&(((RedVoiceDATA*)0)->m_track),
	REDSOUND_VOICE_KEY_OFFSET = (unsigned int)&(((RedVoiceDATA*)0)->m_key),
	REDSOUND_VOICE_VELOCITY_OFFSET = (unsigned int)&(((RedVoiceDATA*)0)->m_velocity),
	REDSOUND_VOICE_STATE_FLAGS_OFFSET = (unsigned int)&(((RedVoiceDATA*)0)->m_stateFlags),
	REDSOUND_VOICE_RESERVED1B_OFFSET = (unsigned int)&(((RedVoiceDATA*)0)->m_reserved1B),
	REDSOUND_VOICE_RESERVED2A_OFFSET = (unsigned int)&(((RedVoiceDATA*)0)->m_reserved2A),
	REDSOUND_VOICE_RESERVED3A_OFFSET = (unsigned int)&(((RedVoiceDATA*)0)->m_reserved3A),
	REDSOUND_VOICE_RESERVED48_OFFSET = (unsigned int)&(((RedVoiceDATA*)0)->m_reserved48),
	REDSOUND_VOICE_ADSR_TIME_OFFSET = (unsigned int)&(((RedVoiceDATA*)0)->m_adsr.m_time),
	REDSOUND_VOICE_ADSR_LEVEL_OFFSET = (unsigned int)&(((RedVoiceDATA*)0)->m_adsr.m_level),
	REDSOUND_VOICE_ADSR_STAGE_OFFSET = (unsigned int)&(((RedVoiceDATA*)0)->m_adsrStage),
	REDSOUND_VOICE_ACTIVE_OFFSET = (unsigned int)&(((RedVoiceDATA*)0)->m_active),
	REDSOUND_VOICE_FLAGS_OFFSET = (unsigned int)&(((RedVoiceDATA*)0)->m_flags),
	REDSOUND_VOICE_SWITCH_OFFSET = (unsigned int)&(((RedVoiceDATA*)0)->m_voiceSwitch),
	REDSOUND_VOICE_RESERVEDA4_OFFSET = (unsigned int)&(((RedVoiceDATA*)0)->m_reservedA4),
	REDSOUND_VOICE_INDEX_OFFSET = (unsigned int)&(((RedVoiceDATA*)0)->m_voiceIndex),
	REDSOUND_VOICE_RESERVEDB4_OFFSET = (unsigned int)&(((RedVoiceDATA*)0)->m_reservedB4),
	REDSOUND_VOICE_UPDATE_FLAGS_OFFSET = (unsigned int)&(((RedVoiceDATA*)0)->m_updateFlags),
	REDSOUND_VOICE_RESERVEDBC_OFFSET = (unsigned int)&(((RedVoiceDATA*)0)->m_reservedBC),
};

enum RedVoiceAdsrLayout {
	REDSOUND_VOICE_ADSR_TIME_HALFWORD = REDSOUND_VOICE_ADSR_TIME_OFFSET / sizeof(u16),
	REDSOUND_VOICE_ADSR_LEVEL_ATTACK_OFFSET = REDSOUND_VOICE_ADSR_LEVEL_OFFSET,
	REDSOUND_VOICE_ADSR_LEVEL_DECAY_OFFSET =
	    (unsigned int)&(((RedVoiceDATA*)0)->m_adsr.m_level[REDSOUND_VOICE_ADSR_DECAY]),
	REDSOUND_VOICE_ADSR_LEVEL_SUSTAIN_OFFSET =
	    (unsigned int)&(((RedVoiceDATA*)0)->m_adsr.m_level[REDSOUND_VOICE_ADSR_SUSTAIN]),
	REDSOUND_VOICE_ADSR_LEVEL_RELEASE_OFFSET =
	    (unsigned int)&(((RedVoiceDATA*)0)->m_adsr.m_level[REDSOUND_VOICE_ADSR_RELEASE]),
	REDSOUND_VOICE_ADSR_TIME_ATTACK_HALFWORD = REDSOUND_VOICE_ADSR_TIME_OFFSET / sizeof(u16),
	REDSOUND_VOICE_ADSR_TIME_DECAY_HALFWORD =
	    (unsigned int)&(((RedVoiceDATA*)0)->m_adsr.m_time[REDSOUND_VOICE_ADSR_DECAY]) / sizeof(u16),
	REDSOUND_VOICE_ADSR_TIME_SUSTAIN_HALFWORD =
	    (unsigned int)&(((RedVoiceDATA*)0)->m_adsr.m_time[REDSOUND_VOICE_ADSR_SUSTAIN]) / sizeof(u16),
	REDSOUND_VOICE_ADSR_TIME_RELEASE_HALFWORD =
	    (unsigned int)&(((RedVoiceDATA*)0)->m_adsr.m_time[REDSOUND_VOICE_ADSR_RELEASE]) / sizeof(u16),
	REDSOUND_VOICE_ADSR_TIME_RELEASE_BYTE =
	    REDSOUND_VOICE_ADSR_RELEASE * REDSOUND_VOICE_ADSR_TIME_BYTE_STRIDE,
	REDSOUND_VOICE_ADSR_TIME_RELEASE_BYTE_OFFSET = REDSOUND_VOICE_ADSR_TIME_RELEASE_HALFWORD * sizeof(u16),
	REDSOUND_VOICE_ADSR_LEVEL_BASE = 9,
	REDSOUND_VOICE_ADSR_NEXT_LEVEL_OFFSET = REDSOUND_VOICE_ADSR_DECAY - REDSOUND_VOICE_ADSR_ATTACK,
	REDSOUND_VOICE_ADSR_STAGE_COUNT = 3,
	REDSOUND_ADSR_STATE_STAGE = 0,
	REDSOUND_ADSR_STATE_STEP_FRAMES = 1,
	REDSOUND_ADSR_STATE_STEP_ADD = 2,
	REDSOUND_ADSR_LEVEL_BYTE_SHIFT = 8,
};

#define RedAdsrGetStageLevel(adsrData, stage)                                                      \
	(&(adsrData)->m_level[REDSOUND_VOICE_ADSR_NEXT_LEVEL_OFFSET])[(stage)]

enum RedVoiceLayoutWord {
	REDSOUND_VOICE_TRACK_WORD = REDSOUND_VOICE_TRACK_OFFSET / sizeof(u32),
	REDSOUND_VOICE_WAVE_DATA_WORD = (unsigned int)&(((RedVoiceDATA*)0)->m_waveData) / sizeof(u32),
	REDSOUND_VOICE_TRACK_VOLUME_WORD = (unsigned int)&(((RedVoiceDATA*)0)->m_trackVolume) / sizeof(u32),
	REDSOUND_VOICE_TRACK_EXPRESSION_WORD = (unsigned int)&(((RedVoiceDATA*)0)->m_trackExpression) / sizeof(u32),
	REDSOUND_VOICE_TRACK_PAN_WORD = (unsigned int)&(((RedVoiceDATA*)0)->m_trackPan) / sizeof(u32),
	REDSOUND_VOICE_AX_VOICE_WORD = (unsigned int)&(((RedVoiceDATA*)0)->m_axVoice) / sizeof(u32),
	REDSOUND_VOICE_NOTE_WORD = REDSOUND_VOICE_KEY_OFFSET / sizeof(u32),
	REDSOUND_VOICE_PITCH_MOD_PHASE_WORD = (unsigned int)&(((RedVoiceDATA*)0)->m_pitchModPhase) / sizeof(u32),
	REDSOUND_VOICE_PITCH_MOD_FRAMES_WORD = (unsigned int)&(((RedVoiceDATA*)0)->m_pitchModFrames) / sizeof(u32),
	REDSOUND_VOICE_PITCH_MOD_FRAME_WORD = (unsigned int)&(((RedVoiceDATA*)0)->m_pitchModFrame) / sizeof(u32),
	REDSOUND_VOICE_PITCH_MOD_DELAY_HALFWORD =
	    (unsigned int)&(((RedVoiceDATA*)0)->m_pitchModDelay) / sizeof(unsigned short),
	REDSOUND_VOICE_VOLUME_MOD_PHASE_WORD = (unsigned int)&(((RedVoiceDATA*)0)->m_volumeModPhase) / sizeof(u32),
	REDSOUND_VOICE_VOLUME_MOD_FRAMES_WORD = (unsigned int)&(((RedVoiceDATA*)0)->m_volumeModFrames) / sizeof(u32),
	REDSOUND_VOICE_VOLUME_MOD_FRAME_WORD = (unsigned int)&(((RedVoiceDATA*)0)->m_volumeModFrame) / sizeof(u32),
	REDSOUND_VOICE_VOLUME_MOD_DELAY_HALFWORD =
	    (unsigned int)&(((RedVoiceDATA*)0)->m_volumeModDelay) / sizeof(unsigned short),
	REDSOUND_VOICE_RANDOM_PITCH_WORD = (unsigned int)&(((RedVoiceDATA*)0)->m_randomPitch) / sizeof(u32),
	REDSOUND_VOICE_RANDOM_VOLUME_WORD = (unsigned int)&(((RedVoiceDATA*)0)->m_randomVolume) / sizeof(u32),
	REDSOUND_VOICE_RANDOM_PAN_WORD = (unsigned int)&(((RedVoiceDATA*)0)->m_randomPan) / sizeof(u32),
	REDSOUND_VOICE_ACTIVE_WORD = REDSOUND_VOICE_ACTIVE_OFFSET / sizeof(u32),
	REDSOUND_VOICE_FLAGS_WORD = REDSOUND_VOICE_FLAGS_OFFSET / sizeof(u32),
	REDSOUND_VOICE_SWITCH_WORD = REDSOUND_VOICE_SWITCH_OFFSET / sizeof(u32),
	REDSOUND_VOICE_INDEX_WORD = REDSOUND_VOICE_INDEX_OFFSET / sizeof(u32),
	REDSOUND_VOICE_INDEX_MASK = 0x1F,
	REDSOUND_VOICE_ADSR_TIME_WORD = REDSOUND_VOICE_ADSR_TIME_OFFSET / sizeof(u32),
	REDSOUND_VOICE_ADSR_STAGE_WORD = REDSOUND_VOICE_ADSR_STAGE_OFFSET / sizeof(u32),
	REDSOUND_VOICE_ADSR_STEP_FRAMES_WORD = (unsigned int)&(((RedVoiceDATA*)0)->m_adsrStepFrames) / sizeof(u32),
	REDSOUND_VOICE_ADSR_STEP_ADD_WORD = (unsigned int)&(((RedVoiceDATA*)0)->m_adsrStepAdd) / sizeof(u32),
	REDSOUND_VOICE_PITCH_WORD = (unsigned int)&(((RedVoiceDATA*)0)->m_pitch) / sizeof(u32),
	REDSOUND_VOICE_TARGET_PITCH_WORD = (unsigned int)&(((RedVoiceDATA*)0)->m_targetPitch) / sizeof(u32),
	REDSOUND_VOICE_BASE_PITCH_WORD = (unsigned int)&(((RedVoiceDATA*)0)->m_basePitch) / sizeof(u32),
	REDSOUND_VOICE_ADSR_CURRENT_WORD = (unsigned int)&(((RedVoiceDATA*)0)->m_adsrCurrentLevel) / sizeof(u32),
	REDSOUND_VOICE_ENVELOPE_WORD = (unsigned int)&(((RedVoiceDATA*)0)->m_envelopeLevel) / sizeof(u32),
	REDSOUND_VOICE_UPDATE_FLAGS_WORD = REDSOUND_VOICE_UPDATE_FLAGS_OFFSET / sizeof(u32),
};

enum RedVoiceActiveState {
	REDSOUND_VOICE_ACTIVE_OFF = 0,
	REDSOUND_VOICE_ACTIVE_ON = 1,
};

enum RedVoiceBufferWordOffset {
	REDSOUND_VOICE_MASK_WORD_BIT_COUNT = 32,
	REDSOUND_VOICE_SECOND_MASK_WORD_OFFSET =
	    (sizeof(RedVoiceDATA) * REDSOUND_VOICE_MASK_WORD_BIT_COUNT) / sizeof(u32),
};

enum RedRandomByteLayout {
	REDSOUND_RANDOM_BYTE_MASK = 0xFF,
	REDSOUND_RANDOM_DATA_COUNT = REDSOUND_RANDOM_BYTE_MASK + 1,
	REDSOUND_RANDOM_BYTE_SIGN_BIT = 0x80,
	REDSOUND_RANDOM_FUZZY_DEPTH_SHIFT = 8,
	REDSOUND_RANDOM_FUZZY_PITCH_SHIFT = 15,
	REDSOUND_RANDOM_FUZZY_PITCH_NEGATIVE_SHIFT = 16,
};

enum RedVoiceCleanupMask {
	REDSOUND_VOICE_STATE_PLAYING = 1,
	REDSOUND_VOICE_STATE_STREAM = 2,
	REDSOUND_VOICE_STATE_SE = 4,
	REDSOUND_VOICE_STATE_PLAYING_MASK = REDSOUND_VOICE_STATE_PLAYING | REDSOUND_VOICE_STATE_STREAM,
	REDSOUND_VOICE_STATE_ANY_MASK =
	    REDSOUND_VOICE_STATE_PLAYING | REDSOUND_VOICE_STATE_STREAM | REDSOUND_VOICE_STATE_SE,
	REDSOUND_VOICE_STATE_CLEAR_STREAM_MASK = ~REDSOUND_VOICE_STATE_STREAM,
	REDSOUND_VOICE_STATE_CLEAR_PLAYING_MASK = -6,
	REDSOUND_VOICE_SWITCH_LOOP = 1,
	REDSOUND_VOICE_SWITCH_REVERB_AUX_A = 2,
	REDSOUND_VOICE_SWITCH_SUSTAIN = 4,
	REDSOUND_VOICE_SWITCH_PAUSE = 8,
	REDSOUND_VOICE_SWITCH_SKIP_UPDATE = REDSOUND_VOICE_SWITCH_LOOP | REDSOUND_VOICE_SWITCH_PAUSE,
	REDSOUND_VOICE_SWITCH_PAIRED_LEFT = 0x40,
	REDSOUND_VOICE_SWITCH_PAIRED_RIGHT = 0x80,
	REDSOUND_VOICE_SWITCH_PAIRED_PAN = REDSOUND_VOICE_SWITCH_PAIRED_LEFT | REDSOUND_VOICE_SWITCH_PAIRED_RIGHT,
	REDSOUND_VOICE_SWITCH_DRY_LEFT = 0x400,
	REDSOUND_VOICE_SWITCH_DRY_RIGHT = 0x800,
	REDSOUND_VOICE_SWITCH_DRY_STEREO = REDSOUND_VOICE_SWITCH_DRY_LEFT | REDSOUND_VOICE_SWITCH_DRY_RIGHT,
	REDSOUND_VOICE_SWITCH_REVERB_LEFT = 0x1000,
	REDSOUND_VOICE_SWITCH_REVERB_RIGHT = 0x2000,
	REDSOUND_VOICE_SWITCH_REVERB_STEREO = REDSOUND_VOICE_SWITCH_REVERB_LEFT | REDSOUND_VOICE_SWITCH_REVERB_RIGHT,
	REDSOUND_VOICE_SWITCH_MIX_ALL = REDSOUND_VOICE_SWITCH_DRY_STEREO | REDSOUND_VOICE_SWITCH_REVERB_STEREO,
	REDSOUND_VOICE_SWITCH_MUSIC_DEFAULT = REDSOUND_VOICE_SWITCH_DRY_STEREO | REDSOUND_VOICE_SWITCH_REVERB_AUX_A,
	REDSOUND_VOICE_SWITCH_STREAM_DEFAULT = REDSOUND_VOICE_SWITCH_DRY_STEREO | REDSOUND_VOICE_SWITCH_LOOP,
	REDSOUND_VOICE_SWITCH_FUZZY_PITCH = 0x4000,
	REDSOUND_VOICE_SWITCH_FUZZY_VOLUME = 0x8000,
	REDSOUND_VOICE_SWITCH_FUZZY_PAN = 0x10000,
	REDSOUND_VOICE_SWITCH_FUZZY_DELTA_TIME = 0x20000,
	REDSOUND_VOICE_SWITCH_FUZZY_ADSR = 0x40000,
	REDSOUND_VOICE_SWITCH_CLEAR_PAUSE_MASK = ~REDSOUND_VOICE_SWITCH_PAUSE,
	REDSOUND_VOICE_SWITCH_CLEAR_SUSTAIN_PAUSE_MASK = ~(REDSOUND_VOICE_SWITCH_SUSTAIN | REDSOUND_VOICE_SWITCH_PAUSE),
	REDSOUND_VOICE_SWITCH_CLEAR_REVERB_MASK = ~REDSOUND_VOICE_SWITCH_REVERB_STEREO,
	REDSOUND_VOICE_SWITCH_CLEAR_MIX_MASK = ~REDSOUND_VOICE_SWITCH_MIX_ALL,
	REDSOUND_VOICE_SWITCH_CLEAR_SE_MASK = 0xfffffff7,
	REDSOUND_VOICE_FLAGS_START = 1,
	REDSOUND_VOICE_FLAGS_CLEAR_ACTIVE_MASK = 0xfffffffe,
	REDSOUND_VOICE_FLAGS_RELEASED = 2,
	REDSOUND_VOICE_FLAGS_RELEASE_ACTIVE = 4,
	REDSOUND_VOICE_FLAGS_CLEAR_RELEASE_ACTIVE_MASK = ~REDSOUND_VOICE_FLAGS_RELEASE_ACTIVE,
	REDSOUND_VOICE_FLAGS_ADPCM_DIRTY = 8,
	REDSOUND_VOICE_FLAGS_PITCH_DIRTY = 0x10,
	REDSOUND_VOICE_FLAGS_ADSR_START = 0x20,
	REDSOUND_VOICE_FLAGS_ADSR_DIRTY = 0x3C0,
	REDSOUND_VOICE_FLAGS_PAUSE_DIRTY = REDSOUND_VOICE_FLAGS_ADPCM_DIRTY | REDSOUND_VOICE_FLAGS_PITCH_DIRTY,
	REDSOUND_VOICE_FLAGS_STREAM_START =
	    REDSOUND_VOICE_FLAGS_START | REDSOUND_VOICE_FLAGS_ADPCM_DIRTY | REDSOUND_VOICE_FLAGS_PITCH_DIRTY,
	REDSOUND_VOICE_FLAGS_EXECUTE_KEEP_MASK = 0xFFFFFC24,
};

#define RedVoiceStateIsPlaying(flags) (((flags) & REDSOUND_VOICE_STATE_PLAYING_MASK) != 0)
#define RedVoiceIsPlaying(voice) RedVoiceStateIsPlaying((voice)->m_stateFlags)
#define RedVoiceIsNotPlaying(voice) (!RedVoiceIsPlaying(voice))

enum RedVoiceUpdateFlag {
	REDSOUND_VOICE_UPDATE_PITCH = 1,
	REDSOUND_VOICE_UPDATE_VOLUME = 2,
	REDSOUND_VOICE_UPDATE_ALL = REDSOUND_VOICE_UPDATE_PITCH | REDSOUND_VOICE_UPDATE_VOLUME,
};

enum RedAxVoicePlayback {
	REDSOUND_AX_VOICE_STOP = 0,
	REDSOUND_AX_VOICE_PLAY = 1,
	REDSOUND_AX_VOICE_LOOP_OFF = 0,
	REDSOUND_AX_VOICE_LOOP_ON = 1,
	REDSOUND_AX_VOICE_TYPE_ONE_SHOT = 0,
	REDSOUND_AX_VOICE_TYPE_LOOP = 1,
	REDSOUND_AX_SRC_SELECT_ADPCM = 1,
	REDSOUND_AX_ADDR_FORMAT_ADPCM = 0,
};

u8 GetRandomData();
int PitchCompute(int basePitch, int pitchOffset, int wavePitch, int fineTune);
void* ReverbAreaAlloc(unsigned long size);
void ReverbAreaFree(void* area);
void InitReverb();
RedReverbSize* GetReverbInfo();
RedReverbSize* SetReverb(int bank, int kind, int* reverbParams);

RedVoiceDATA* EntryVoiceSearch(RedTrackDATA* track);
void SetVoiceVolumeMix(RedVoiceDATA* voice, int pan, int volume);
void SetVoiceAccess(RedTrackDATA* track, int mask);
void SetAllVoiceAccess(RedSoundCONTROL* control, int mask);
void SetVoiceSwitch(RedTrackDATA* track, int voiceSwitch);

void EnvelopeKeyExecute();

void MusicSkipFunction();

void MainControl(int frames);

#endif // _FFCC_REDSOUND_REDEXECUTE_H
