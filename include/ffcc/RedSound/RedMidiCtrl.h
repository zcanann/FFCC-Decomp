#ifndef _FFCC_REDSOUND_REDMIDICTRL_H
#define _FFCC_REDSOUND_REDMIDICTRL_H

#include "ffcc/RedSound/RedExecute.h"

struct RedSoundCONTROL;
struct RedWaveHeadWD;

enum RedMidiLayoutSize {
	REDSOUND_KEY_ON_SLOT_COUNT = 0x40,
	REDSOUND_MUSIC_TRACK_SAVE_COUNT = 0x40,
	REDSOUND_TRACK_LOOP_STACK_COUNT = 4,
	REDSOUND_SWING_FUNCTION_COUNT = 0x10,
	REDSOUND_MIDI_CONTROL_FUNCTION_COUNT = 0x80,
	REDSOUND_TRACK_RESERVED04_SIZE = 0x04,
	REDSOUND_TRACK_RESERVED88_SIZE = 0x04,
	REDSOUND_TRACK_RESERVEDA8_SIZE = 0x04,
	REDSOUND_TRACK_RESERVED149_SIZE = 0x02,
	REDSOUND_TRACK_RESERVED14C_SIZE = 0x01,
	REDSOUND_TRACK_RESERVED151_SIZE = 0x03,
	REDSOUND_CONTROL_RESERVED04_SIZE = 0x04,
	REDSOUND_CONTROL_RESERVED460_SIZE = 0x0C,
	REDSOUND_CONTROL_RESERVED493_SIZE = 0x01,
};

typedef int (*RedSwingFunc)(int phase);

#define REDSOUND_TRACK_COMMAND_NONE 0
#define REDSOUND_TRACK_NONE 0
#define REDSOUND_TRACK_SESEP_ID_NONE 0
#define REDSOUND_TRACK_ATTR_NONE 0
#define REDSOUND_TRACK_FLAGS_NONE 0
#define REDSOUND_SWING_FUNC_NONE ((RedSwingFunc)0)
#define REDSOUND_WAVE_BANK_DATA_NONE 0
#define REDSOUND_WAVE_BASE_NONE 0

struct RedTrackDATA {
	unsigned char* m_command;
	unsigned char m_reserved04[REDSOUND_TRACK_RESERVED04_SIZE];
	unsigned char* m_loopCommand[REDSOUND_TRACK_LOOP_STACK_COUNT];
	RedWaveHeadWD* m_waveBankData;
	RedWaveDATA* m_waveData;
	signed char* m_keySignatureData;
	RedNoteDATA m_note;
	int m_volume;
	int m_volumeAdd;
	int m_volumeDelta;
	int m_expression;
	int m_expressionAdd;
	int m_expressionDelta;
	int m_pan;
	int m_panAdd;
	int m_panDelta;
	int m_mixVolume;
	int m_mixVolumeAdd;
	int m_mixVolumeDelta;
	int m_mixVolumeMode;
	int m_pitch;
	int m_pitchAdd;
	int m_pitchDelta;
	int m_reverbDepth;
	int m_reverbDepthAdd;
	int m_reverbDepthDelta;
	RedSwingFunc m_vibrateFunc;
	int m_vibrateRate;
	int m_vibrateRateAdd;
	int m_vibrateDepth;
	int m_vibrateDepthAdd;
	unsigned char m_reserved88[REDSOUND_TRACK_RESERVED88_SIZE];
	short m_vibrateRateDelta;
	short m_vibrateDepthDelta;
	short m_vibrateDelay;
	short m_vibrateDelayDepth;
	RedSwingFunc m_tremoloFunc;
	int m_tremoloRate;
	int m_tremoloRateAdd;
	int m_tremoloDepth;
	int m_tremoloDepthAdd;
	unsigned char m_reservedA8[REDSOUND_TRACK_RESERVEDA8_SIZE];
	short m_tremoloRateDelta;
	short m_tremoloDepthDelta;
	short m_tremoloDelay;
	short m_tremoloDelayDepth;
	RedSwingFunc m_shakeFunc;
	int m_shakeRate;
	int m_shakeRateAdd;
	int m_shakeDepth;
	int m_shakeDepthAdd;
	int m_shakeOutput;
	int m_shakePan;
	short m_shakeRateDelta;
	short m_shakeDepthDelta;
	RedAdsrDATA m_adsr;
	int m_fuzzyPitchDepth;
	int m_fuzzyVolumeDepth;
	int m_fuzzyPanDepth;
	int m_fuzzyDeltaTimeDepth;
	int m_fuzzyAdsrDepth;
	int m_seSepId;
	int m_seId;
	int m_voiceSwitch;
	int m_loopReport;
	unsigned int m_flags;
	int m_deltaTime;
	int m_playTime;
	int m_sweepDelta;
	int m_sweepAdd;
	int m_portamentTime;
	int m_waveBase;
	int m_portamentPitch;
	int m_waveNo;
	short m_loopCount[REDSOUND_TRACK_LOOP_STACK_COUNT];
	short m_loopStep[REDSOUND_TRACK_LOOP_STACK_COUNT];
	short m_step;
	short m_step2;
	short m_loopDepth;
	short m_pitchBend;
	short m_pitchBendRaw;
	short m_keyTranspose;
	short m_loopStepCurrent;
	short m_seTickCounter;
	signed char m_fineTune;
	unsigned char m_reserved149[REDSOUND_TRACK_RESERVED149_SIZE];
	signed char m_pitchBendRange;
	unsigned char m_reserved14C[REDSOUND_TRACK_RESERVED14C_SIZE];
	unsigned char m_waveBankNo;
	signed char m_trackNo;
	unsigned char m_eraseTrack;
	unsigned char m_attrMask;
	unsigned char m_reserved151[REDSOUND_TRACK_RESERVED151_SIZE];
};

enum RedTrackAdsrLayout {
	REDSOUND_TRACK_ADSR_DEFAULT_BYTE = 0xFF,
	REDSOUND_TRACK_ADSR_DEFAULT_WORD = -1,
	REDSOUND_TRACK_ADSR_SIZE = REDSOUND_ADSR_DATA_SIZE,
};

inline void RedTrackAdsrSetDefaultWords(RedAdsrDATA* adsr)
{
	*(int*)&adsr->m_time[REDSOUND_VOICE_ADSR_ATTACK] = REDSOUND_TRACK_ADSR_DEFAULT_WORD;
	*(int*)&adsr->m_time[REDSOUND_VOICE_ADSR_SUSTAIN] = REDSOUND_TRACK_ADSR_DEFAULT_WORD;
}

enum RedTrackLayoutWord {
	REDSOUND_TRACK_COMMAND_WORD_OFFSET = (unsigned int)&(((RedTrackDATA*)0)->m_command) / sizeof(int),
	REDSOUND_TRACK_LOOP_COMMAND_WORD_OFFSET = (unsigned int)&(((RedTrackDATA*)0)->m_loopCommand) / sizeof(int),
	REDSOUND_TRACK_WAVE_BANK_DATA_WORD_OFFSET = (unsigned int)&(((RedTrackDATA*)0)->m_waveBankData) / sizeof(int),
	REDSOUND_TRACK_KEY_SIGNATURE_DATA_WORD_OFFSET =
	    (unsigned int)&(((RedTrackDATA*)0)->m_keySignatureData) / sizeof(int),
	REDSOUND_TRACK_VOLUME_WORD_OFFSET = (unsigned int)&(((RedTrackDATA*)0)->m_volume) / sizeof(int),
	REDSOUND_TRACK_VOLUME_ADD_WORD_OFFSET = (unsigned int)&(((RedTrackDATA*)0)->m_volumeAdd) / sizeof(int),
	REDSOUND_TRACK_VOLUME_DELTA_WORD_OFFSET = (unsigned int)&(((RedTrackDATA*)0)->m_volumeDelta) / sizeof(int),
	REDSOUND_TRACK_EXPRESSION_WORD_OFFSET = (unsigned int)&(((RedTrackDATA*)0)->m_expression) / sizeof(int),
	REDSOUND_TRACK_EXPRESSION_ADD_WORD_OFFSET = (unsigned int)&(((RedTrackDATA*)0)->m_expressionAdd) / sizeof(int),
	REDSOUND_TRACK_EXPRESSION_DELTA_WORD_OFFSET =
	    (unsigned int)&(((RedTrackDATA*)0)->m_expressionDelta) / sizeof(int),
	REDSOUND_TRACK_PAN_WORD_OFFSET = (unsigned int)&(((RedTrackDATA*)0)->m_pan) / sizeof(int),
	REDSOUND_TRACK_PAN_ADD_WORD_OFFSET = (unsigned int)&(((RedTrackDATA*)0)->m_panAdd) / sizeof(int),
	REDSOUND_TRACK_PAN_DELTA_WORD_OFFSET = (unsigned int)&(((RedTrackDATA*)0)->m_panDelta) / sizeof(int),
	REDSOUND_TRACK_MIX_VOLUME_WORD_OFFSET = (unsigned int)&(((RedTrackDATA*)0)->m_mixVolume) / sizeof(int),
	REDSOUND_TRACK_MIX_VOLUME_ADD_WORD_OFFSET = (unsigned int)&(((RedTrackDATA*)0)->m_mixVolumeAdd) / sizeof(int),
	REDSOUND_TRACK_MIX_VOLUME_DELTA_WORD_OFFSET =
	    (unsigned int)&(((RedTrackDATA*)0)->m_mixVolumeDelta) / sizeof(int),
	REDSOUND_TRACK_MIX_VOLUME_MODE_WORD_OFFSET =
	    (unsigned int)&(((RedTrackDATA*)0)->m_mixVolumeMode) / sizeof(int),
	REDSOUND_TRACK_PITCH_WORD_OFFSET = (unsigned int)&(((RedTrackDATA*)0)->m_pitch) / sizeof(int),
	REDSOUND_TRACK_PITCH_ADD_WORD_OFFSET = (unsigned int)&(((RedTrackDATA*)0)->m_pitchAdd) / sizeof(int),
	REDSOUND_TRACK_PITCH_DELTA_WORD_OFFSET = (unsigned int)&(((RedTrackDATA*)0)->m_pitchDelta) / sizeof(int),
	REDSOUND_TRACK_REVERB_DEPTH_WORD_OFFSET = (unsigned int)&(((RedTrackDATA*)0)->m_reverbDepth) / sizeof(int),
	REDSOUND_TRACK_REVERB_DEPTH_ADD_WORD_OFFSET =
	    (unsigned int)&(((RedTrackDATA*)0)->m_reverbDepthAdd) / sizeof(int),
	REDSOUND_TRACK_REVERB_DEPTH_DELTA_WORD_OFFSET =
	    (unsigned int)&(((RedTrackDATA*)0)->m_reverbDepthDelta) / sizeof(int),
	REDSOUND_TRACK_VIBRATE_FUNC_WORD_OFFSET = (unsigned int)&(((RedTrackDATA*)0)->m_vibrateFunc) / sizeof(int),
	REDSOUND_TRACK_VIBRATE_RATE_WORD_OFFSET = (unsigned int)&(((RedTrackDATA*)0)->m_vibrateRate) / sizeof(int),
	REDSOUND_TRACK_VIBRATE_RATE_ADD_WORD_OFFSET =
	    (unsigned int)&(((RedTrackDATA*)0)->m_vibrateRateAdd) / sizeof(int),
	REDSOUND_TRACK_VIBRATE_DEPTH_WORD_OFFSET = (unsigned int)&(((RedTrackDATA*)0)->m_vibrateDepth) / sizeof(int),
	REDSOUND_TRACK_VIBRATE_DEPTH_ADD_WORD_OFFSET =
	    (unsigned int)&(((RedTrackDATA*)0)->m_vibrateDepthAdd) / sizeof(int),
	REDSOUND_TRACK_VIBRATE_RATE_DELTA_HALFWORD =
	    (unsigned int)&(((RedTrackDATA*)0)->m_vibrateRateDelta) / sizeof(short),
	REDSOUND_TRACK_VIBRATE_DEPTH_DELTA_HALFWORD =
	    (unsigned int)&(((RedTrackDATA*)0)->m_vibrateDepthDelta) / sizeof(short),
	REDSOUND_TRACK_VIBRATE_DELAY_HALFWORD = (unsigned int)&(((RedTrackDATA*)0)->m_vibrateDelay) / sizeof(short),
	REDSOUND_TRACK_VIBRATE_DELAY_DEPTH_HALFWORD =
	    (unsigned int)&(((RedTrackDATA*)0)->m_vibrateDelayDepth) / sizeof(short),
	REDSOUND_TRACK_TREMOLO_FUNC_WORD_OFFSET = (unsigned int)&(((RedTrackDATA*)0)->m_tremoloFunc) / sizeof(int),
	REDSOUND_TRACK_TREMOLO_RATE_WORD_OFFSET = (unsigned int)&(((RedTrackDATA*)0)->m_tremoloRate) / sizeof(int),
	REDSOUND_TRACK_TREMOLO_RATE_ADD_WORD_OFFSET =
	    (unsigned int)&(((RedTrackDATA*)0)->m_tremoloRateAdd) / sizeof(int),
	REDSOUND_TRACK_TREMOLO_DEPTH_WORD_OFFSET = (unsigned int)&(((RedTrackDATA*)0)->m_tremoloDepth) / sizeof(int),
	REDSOUND_TRACK_TREMOLO_DEPTH_ADD_WORD_OFFSET =
	    (unsigned int)&(((RedTrackDATA*)0)->m_tremoloDepthAdd) / sizeof(int),
	REDSOUND_TRACK_TREMOLO_RATE_DELTA_HALFWORD =
	    (unsigned int)&(((RedTrackDATA*)0)->m_tremoloRateDelta) / sizeof(short),
	REDSOUND_TRACK_TREMOLO_DEPTH_DELTA_HALFWORD =
	    (unsigned int)&(((RedTrackDATA*)0)->m_tremoloDepthDelta) / sizeof(short),
	REDSOUND_TRACK_TREMOLO_DELAY_HALFWORD = (unsigned int)&(((RedTrackDATA*)0)->m_tremoloDelay) / sizeof(short),
	REDSOUND_TRACK_TREMOLO_DELAY_DEPTH_HALFWORD =
	    (unsigned int)&(((RedTrackDATA*)0)->m_tremoloDelayDepth) / sizeof(short),
	REDSOUND_TRACK_SHAKE_FUNC_WORD_OFFSET = (unsigned int)&(((RedTrackDATA*)0)->m_shakeFunc) / sizeof(int),
	REDSOUND_TRACK_SHAKE_RATE_WORD_OFFSET = (unsigned int)&(((RedTrackDATA*)0)->m_shakeRate) / sizeof(int),
	REDSOUND_TRACK_SHAKE_RATE_ADD_WORD_OFFSET = (unsigned int)&(((RedTrackDATA*)0)->m_shakeRateAdd) / sizeof(int),
	REDSOUND_TRACK_SHAKE_DEPTH_WORD_OFFSET = (unsigned int)&(((RedTrackDATA*)0)->m_shakeDepth) / sizeof(int),
	REDSOUND_TRACK_SHAKE_DEPTH_ADD_WORD_OFFSET =
	    (unsigned int)&(((RedTrackDATA*)0)->m_shakeDepthAdd) / sizeof(int),
	REDSOUND_TRACK_SHAKE_OUTPUT_WORD_OFFSET = (unsigned int)&(((RedTrackDATA*)0)->m_shakeOutput) / sizeof(int),
	REDSOUND_TRACK_SHAKE_PAN_WORD_OFFSET = (unsigned int)&(((RedTrackDATA*)0)->m_shakePan) / sizeof(int),
	REDSOUND_TRACK_SHAKE_RATE_DELTA_HALFWORD =
	    (unsigned int)&(((RedTrackDATA*)0)->m_shakeRateDelta) / sizeof(short),
	REDSOUND_TRACK_SHAKE_DEPTH_DELTA_HALFWORD =
	    (unsigned int)&(((RedTrackDATA*)0)->m_shakeDepthDelta) / sizeof(short),
	REDSOUND_TRACK_FUZZY_PITCH_DEPTH_WORD_OFFSET =
	    (unsigned int)&(((RedTrackDATA*)0)->m_fuzzyPitchDepth) / sizeof(int),
	REDSOUND_TRACK_FUZZY_VOLUME_DEPTH_WORD_OFFSET =
	    (unsigned int)&(((RedTrackDATA*)0)->m_fuzzyVolumeDepth) / sizeof(int),
	REDSOUND_TRACK_FUZZY_PAN_DEPTH_WORD_OFFSET = (unsigned int)&(((RedTrackDATA*)0)->m_fuzzyPanDepth) / sizeof(int),
	REDSOUND_TRACK_FUZZY_DELTA_TIME_DEPTH_WORD_OFFSET =
	    (unsigned int)&(((RedTrackDATA*)0)->m_fuzzyDeltaTimeDepth) / sizeof(int),
	REDSOUND_TRACK_FUZZY_ADSR_DEPTH_WORD_OFFSET = (unsigned int)&(((RedTrackDATA*)0)->m_fuzzyAdsrDepth) / sizeof(int),
	REDSOUND_TRACK_SE_SEP_ID_WORD_OFFSET = (unsigned int)&(((RedTrackDATA*)0)->m_seSepId) / sizeof(int),
	REDSOUND_TRACK_SE_ID_WORD_OFFSET = (unsigned int)&(((RedTrackDATA*)0)->m_seId) / sizeof(int),
	REDSOUND_TRACK_FLAGS_WORD_OFFSET = (unsigned int)&(((RedTrackDATA*)0)->m_flags) / sizeof(int),
	REDSOUND_TRACK_DELTA_TIME_WORD_OFFSET = (unsigned int)&(((RedTrackDATA*)0)->m_deltaTime) / sizeof(int),
	REDSOUND_TRACK_PLAY_TIME_WORD_OFFSET = (unsigned int)&(((RedTrackDATA*)0)->m_playTime) / sizeof(int),
	REDSOUND_TRACK_SWEEP_DELTA_WORD_OFFSET = (unsigned int)&(((RedTrackDATA*)0)->m_sweepDelta) / sizeof(int),
	REDSOUND_TRACK_SWEEP_ADD_WORD_OFFSET = (unsigned int)&(((RedTrackDATA*)0)->m_sweepAdd) / sizeof(int),
	REDSOUND_TRACK_PORTAMENT_TIME_WORD_OFFSET = (unsigned int)&(((RedTrackDATA*)0)->m_portamentTime) / sizeof(int),
	REDSOUND_TRACK_WAVE_BASE_WORD_OFFSET = (unsigned int)&(((RedTrackDATA*)0)->m_waveBase) / sizeof(int),
	REDSOUND_TRACK_PORTAMENT_PITCH_WORD_OFFSET = (unsigned int)&(((RedTrackDATA*)0)->m_portamentPitch) / sizeof(int),
	REDSOUND_TRACK_PORTAMENT_PITCH_NONE = -1,
	REDSOUND_TRACK_WAVE_NO_WORD_OFFSET = (unsigned int)&(((RedTrackDATA*)0)->m_waveNo) / sizeof(int),
};

enum RedTrackLayoutHalfword {
	REDSOUND_TRACK_LOOP_COUNT_HALFWORD = (unsigned int)&(((RedTrackDATA*)0)->m_loopCount) / sizeof(short),
	REDSOUND_TRACK_LOOP_STEP_HALFWORD = (unsigned int)&(((RedTrackDATA*)0)->m_loopStep) / sizeof(short),
	REDSOUND_TRACK_STEP_HALFWORD = (unsigned int)&(((RedTrackDATA*)0)->m_step) / sizeof(short),
	REDSOUND_TRACK_STEP2_HALFWORD = (unsigned int)&(((RedTrackDATA*)0)->m_step2) / sizeof(short),
	REDSOUND_TRACK_LOOP_DEPTH_HALFWORD = (unsigned int)&(((RedTrackDATA*)0)->m_loopDepth) / sizeof(short),
	REDSOUND_TRACK_PITCH_BEND_HALFWORD = (unsigned int)&(((RedTrackDATA*)0)->m_pitchBend) / sizeof(short),
	REDSOUND_TRACK_PITCH_BEND_RAW_HALFWORD = (unsigned int)&(((RedTrackDATA*)0)->m_pitchBendRaw) / sizeof(short),
	REDSOUND_TRACK_KEY_TRANSPOSE_HALFWORD = (unsigned int)&(((RedTrackDATA*)0)->m_keyTranspose) / sizeof(short),
	REDSOUND_TRACK_LOOP_STEP_CURRENT_HALFWORD =
	    (unsigned int)&(((RedTrackDATA*)0)->m_loopStepCurrent) / sizeof(short),
	REDSOUND_TRACK_SE_TICK_COUNTER_HALFWORD = (unsigned int)&(((RedTrackDATA*)0)->m_seTickCounter) / sizeof(short),
};

enum RedTrackAdsrOffsetLayout {
	REDSOUND_TRACK_ADSR_TIME_ATTACK_HALFWORD =
	    (unsigned int)&(((RedTrackDATA*)0)->m_adsr.m_time[REDSOUND_VOICE_ADSR_ATTACK]) / sizeof(unsigned short),
	REDSOUND_TRACK_ADSR_TIME_DECAY_HALFWORD =
	    (unsigned int)&(((RedTrackDATA*)0)->m_adsr.m_time[REDSOUND_VOICE_ADSR_DECAY]) / sizeof(unsigned short),
	REDSOUND_TRACK_ADSR_TIME_SUSTAIN_HALFWORD =
	    (unsigned int)&(((RedTrackDATA*)0)->m_adsr.m_time[REDSOUND_VOICE_ADSR_SUSTAIN]) / sizeof(unsigned short),
	REDSOUND_TRACK_ADSR_TIME_RELEASE_HALFWORD =
	    (unsigned int)&(((RedTrackDATA*)0)->m_adsr.m_time[REDSOUND_VOICE_ADSR_RELEASE]) / sizeof(unsigned short),
	REDSOUND_TRACK_ADSR_LEVEL_ATTACK_OFFSET =
	    (unsigned int)&(((RedTrackDATA*)0)->m_adsr.m_level[REDSOUND_VOICE_ADSR_ATTACK]),
	REDSOUND_TRACK_ADSR_LEVEL_DECAY_OFFSET =
	    (unsigned int)&(((RedTrackDATA*)0)->m_adsr.m_level[REDSOUND_VOICE_ADSR_DECAY]),
	REDSOUND_TRACK_ADSR_LEVEL_SUSTAIN_OFFSET =
	    (unsigned int)&(((RedTrackDATA*)0)->m_adsr.m_level[REDSOUND_VOICE_ADSR_SUSTAIN]),
	REDSOUND_TRACK_ADSR_LEVEL_RELEASE_OFFSET =
	    (unsigned int)&(((RedTrackDATA*)0)->m_adsr.m_level[REDSOUND_VOICE_ADSR_RELEASE]),
};

enum RedTrackLayoutByte {
	REDSOUND_TRACK_RESERVED04_BYTE = (unsigned int)&(((RedTrackDATA*)0)->m_reserved04),
	REDSOUND_TRACK_RESERVED88_BYTE = (unsigned int)&(((RedTrackDATA*)0)->m_reserved88),
	REDSOUND_TRACK_RESERVEDA8_BYTE = (unsigned int)&(((RedTrackDATA*)0)->m_reservedA8),
	REDSOUND_TRACK_FINE_TUNE_BYTE = (unsigned int)&(((RedTrackDATA*)0)->m_fineTune),
	REDSOUND_TRACK_RESERVED149_BYTE = (unsigned int)&(((RedTrackDATA*)0)->m_reserved149),
	REDSOUND_TRACK_PITCH_BEND_RANGE_BYTE = (unsigned int)&(((RedTrackDATA*)0)->m_pitchBendRange),
	REDSOUND_TRACK_RESERVED14C_BYTE = (unsigned int)&(((RedTrackDATA*)0)->m_reserved14C),
	REDSOUND_TRACK_WAVE_BANK_NO_BYTE = (unsigned int)&(((RedTrackDATA*)0)->m_waveBankNo),
	REDSOUND_TRACK_TRACK_NO_BYTE = (unsigned int)&(((RedTrackDATA*)0)->m_trackNo),
	REDSOUND_TRACK_ERASE_TRACK_BYTE = (unsigned int)&(((RedTrackDATA*)0)->m_eraseTrack),
	REDSOUND_TRACK_ATTR_MASK_BYTE = (unsigned int)&(((RedTrackDATA*)0)->m_attrMask),
	REDSOUND_TRACK_RESERVED151_BYTE = (unsigned int)&(((RedTrackDATA*)0)->m_reserved151),
};

enum RedTrackWordLayout {
	REDSOUND_TRACK_WAVE_DATA_WORD_OFFSET = (unsigned int)&(((RedTrackDATA*)0)->m_waveData) / sizeof(int),
	REDSOUND_TRACK_NOTE_WORD_OFFSET = (unsigned int)&(((RedTrackDATA*)0)->m_note) / sizeof(int),
	REDSOUND_TRACK_NOTE_KEY_OFFSET = (unsigned int)&(((RedTrackDATA*)0)->m_note.m_key),
	REDSOUND_TRACK_NOTE_ALLOC_FLAGS_OFFSET = (unsigned int)&(((RedTrackDATA*)0)->m_note.m_allocFlags),
	REDSOUND_TRACK_VOLUME_OFFSET = (unsigned int)&(((RedTrackDATA*)0)->m_volume),
	REDSOUND_TRACK_EXPRESSION_OFFSET = (unsigned int)&(((RedTrackDATA*)0)->m_expression),
	REDSOUND_TRACK_PAN_OFFSET = (unsigned int)&(((RedTrackDATA*)0)->m_pan),
	REDSOUND_TRACK_VOICE_SWITCH_WORD_OFFSET = (unsigned int)&(((RedTrackDATA*)0)->m_voiceSwitch) / sizeof(int),
	REDSOUND_TRACK_LOOP_REPORT_WORD_OFFSET = (unsigned int)&(((RedTrackDATA*)0)->m_loopReport) / sizeof(int),
	REDSOUND_TRACK_LOOP_REPORT_ACTIVE = 1,
};

enum RedKeySignatureLayout {
	REDSOUND_KEY_SIGNATURE_INDEX_MASK = 0x1F,
	REDSOUND_KEY_SIGNATURE_INDEX_COUNT = REDSOUND_KEY_SIGNATURE_INDEX_MASK + 1,
	REDSOUND_KEY_SIGNATURE_DATA_COUNT = 0x2E,
	REDSOUND_KEY_SIGNATURE_DEFAULT_DATA_OFFSET = 0x0B,
	REDSOUND_KEY_SIGNATURE_DEFAULT_OFFSET = REDSOUND_KEY_SIGNATURE_DEFAULT_DATA_OFFSET,
};

enum RedTrackFlag {
	REDSOUND_TRACK_FLAG_SLUR = 0x80000,
	REDSOUND_TRACK_FLAG_SLUR_RELEASE = 0x100000,
	REDSOUND_TRACK_FLAG_TENUTO = 0x200000,
};

enum RedTrackDefault {
	REDSOUND_SE_DEFAULT_PITCH_BEND_RANGE = 2,
};

struct RedKeyOnSlot {
	RedTrackDATA* m_track;
	RedNoteDATA m_note;
};

enum RedKeyOnSlotLayout {
	REDSOUND_KEY_ON_SLOT_TRACK_OFFSET = (unsigned int)&(((RedKeyOnSlot*)0)->m_track),
	REDSOUND_KEY_ON_SLOT_NOTE_OFFSET = (unsigned int)&(((RedKeyOnSlot*)0)->m_note),
	REDSOUND_KEY_ON_SLOT_SIZE = sizeof(RedKeyOnSlot),
	REDSOUND_KEY_ON_SLOT_WORD_COUNT = REDSOUND_KEY_ON_SLOT_SIZE / sizeof(int),
};

struct RedKeyOnDATA {
	RedKeyOnSlot m_fixed[REDSOUND_KEY_ON_SLOT_COUNT];
	RedKeyOnSlot m_priority[REDSOUND_KEY_ON_SLOT_COUNT];
	RedKeyOnSlot m_normal[REDSOUND_KEY_ON_SLOT_COUNT];
};

enum RedKeyOnWordOffset {
	REDSOUND_KEY_ON_PRIORITY_WORD_OFFSET = REDSOUND_KEY_ON_SLOT_WORD_COUNT * REDSOUND_KEY_ON_SLOT_COUNT,
	REDSOUND_KEY_ON_NORMAL_WORD_OFFSET =
	    REDSOUND_KEY_ON_PRIORITY_WORD_OFFSET + REDSOUND_KEY_ON_SLOT_WORD_COUNT * REDSOUND_KEY_ON_SLOT_COUNT,
	REDSOUND_KEY_ON_TOTAL_WORD_COUNT =
	    REDSOUND_KEY_ON_NORMAL_WORD_OFFSET + REDSOUND_KEY_ON_SLOT_WORD_COUNT * REDSOUND_KEY_ON_SLOT_COUNT,
};

enum RedKeyOnByteOffset {
	REDSOUND_KEY_ON_PRIORITY_BYTE_OFFSET = REDSOUND_KEY_ON_PRIORITY_WORD_OFFSET * sizeof(int),
	REDSOUND_KEY_ON_NORMAL_BYTE_OFFSET = REDSOUND_KEY_ON_NORMAL_WORD_OFFSET * sizeof(int),
	REDSOUND_KEY_ON_END_BYTE_OFFSET = REDSOUND_KEY_ON_TOTAL_WORD_COUNT * sizeof(int),
};

struct RedSoundControlPosition {
	int m_measure;
	int m_tick;
	int m_ticksPerMeasure;
	short m_timeNumerator;
	short m_timeDenominator;
};

struct RedSoundControlTempo {
	int m_tempo;
	int m_tempoAdd;
	int m_tempoDelta;
};

struct RedSavedTrackDATA {
	unsigned char* m_command[REDSOUND_MUSIC_TRACK_SAVE_COUNT];
	int m_delta[REDSOUND_MUSIC_TRACK_SAVE_COUNT];
	unsigned int m_flags[REDSOUND_MUSIC_TRACK_SAVE_COUNT];
	RedNoteDATA m_note[REDSOUND_MUSIC_TRACK_SAVE_COUNT];
};

struct RedSoundCONTROL {
	RedTrackDATA* m_tracks;
	unsigned char m_reserved04[REDSOUND_CONTROL_RESERVED04_SIZE];
	signed char* m_keySignatureData;
	int m_measure;
	int m_tick;
	int m_ticksPerMeasure;
	short m_timeNumerator;
	short m_timeDenominator;
	int m_volume;
	int m_volumeAdd;
	int m_volumeDelta;
	RedSavedTrackDATA m_savedTracks;
	RedSoundControlTempo m_savedTempo;
	int m_savedActiveTrackCount;
	RedSoundControlPosition m_savedPosition;
	int m_tempo;
	int m_tempoAdd;
	int m_tempoDelta;
	int m_masterVolume;
	int m_masterVolumeAdd;
	int m_masterVolumeDelta;
	unsigned char m_reserved460[REDSOUND_CONTROL_RESERVED460_SIZE];
	unsigned int m_flags;
	int m_musicId;
	int m_skipFrames;
	unsigned int m_elapsedTime;
	int m_waveNo;
	int m_keySignature;
	int m_loopBase;
	unsigned int m_updateFlags;
	short m_tickCounter;
	short m_activeTrackCount;
	unsigned char m_channelAlloc;
	unsigned char m_trackCount;
	signed char m_volumeScale;
	unsigned char m_reserved493;
};

#define RedSoundControlGetTrackEnd(control) ((control)->m_tracks + (control)->m_trackCount)
#define RedSoundControlGetSeTrackEnd(control) ((control)->m_tracks + REDSOUND_SE_TRACK_COUNT)

enum RedSoundControlFlag {
	REDSOUND_CONTROL_FLAG_WHOLE_LOOP_ACTIVE = 1,
	REDSOUND_CONTROL_FLAG_WHOLE_LOOP_END = 2,
	REDSOUND_CONTROL_FLAG_PAUSE = 0x10,
	REDSOUND_CONTROL_FLAG_STOP_ON_VOLUME_ZERO = 0x10000,
	REDSOUND_CONTROL_FLAG_CLEAR_STOP_ON_VOLUME_ZERO_MASK = ~REDSOUND_CONTROL_FLAG_STOP_ON_VOLUME_ZERO,
};

enum RedSoundControlDefault {
	REDSOUND_CONTROL_CHANNEL_ALLOC_NONE = 0,
	REDSOUND_CONTROL_KEY_SIGNATURE_NONE = 0,
	REDSOUND_CONTROL_ELAPSED_TIME_NONE = 0,
	REDSOUND_CONTROL_VOLUME_DELTA_NONE = 0,
	REDSOUND_CONTROL_UPDATE_FLAGS_NONE = 0,
	REDSOUND_CONTROL_INITIAL_TICK_COUNTER = 1,
	REDSOUND_CONTROL_INITIAL_SKIP_FRAMES = 1,
	REDSOUND_CONTROL_DEFAULT_TICKS_PER_MEASURE = 10000,
	REDSOUND_CONTROL_INITIAL_TICK = -1,
	REDSOUND_CONTROL_INITIAL_MEASURE = 1,
};

enum RedSoundControlWordOffset {
	REDSOUND_CONTROL_MEASURE_WORD_OFFSET = (unsigned int)&(((RedSoundCONTROL*)0)->m_measure) / sizeof(int),
	REDSOUND_CONTROL_SAVED_COMMAND_WORD_OFFSET =
	    (unsigned int)&(((RedSoundCONTROL*)0)->m_savedTracks.m_command) / sizeof(int),
	REDSOUND_CONTROL_SAVED_DELTA_WORD_OFFSET =
	    (unsigned int)&(((RedSoundCONTROL*)0)->m_savedTracks.m_delta) / sizeof(int),
	REDSOUND_CONTROL_SAVED_FLAGS_WORD_OFFSET =
	    (unsigned int)&(((RedSoundCONTROL*)0)->m_savedTracks.m_flags) / sizeof(int),
	REDSOUND_CONTROL_SAVED_NOTE_WORD_OFFSET = (unsigned int)&(((RedSoundCONTROL*)0)->m_savedTracks.m_note) / sizeof(int),
	REDSOUND_CONTROL_SAVED_TEMPO_WORD_OFFSET =
	    (unsigned int)&(((RedSoundCONTROL*)0)->m_savedTempo) / sizeof(int),
	REDSOUND_CONTROL_SAVED_ACTIVE_TRACK_COUNT_WORD_OFFSET =
	    (unsigned int)&(((RedSoundCONTROL*)0)->m_savedActiveTrackCount) / sizeof(int),
	REDSOUND_CONTROL_SAVED_MEASURE_WORD_OFFSET =
	    (unsigned int)&(((RedSoundCONTROL*)0)->m_savedPosition.m_measure) / sizeof(int),
	REDSOUND_CONTROL_SAVED_TICK_WORD_OFFSET =
	    (unsigned int)&(((RedSoundCONTROL*)0)->m_savedPosition.m_tick) / sizeof(int),
	REDSOUND_CONTROL_SAVED_TICKS_PER_MEASURE_WORD_OFFSET =
	    (unsigned int)&(((RedSoundCONTROL*)0)->m_savedPosition.m_ticksPerMeasure) / sizeof(int),
	REDSOUND_CONTROL_TEMPO_WORD_OFFSET = (unsigned int)&(((RedSoundCONTROL*)0)->m_tempo) / sizeof(int),
};

enum RedSoundControlByteOffset {
	REDSOUND_CONTROL_TRACKS_OFFSET = (unsigned int)&(((RedSoundCONTROL*)0)->m_tracks),
	REDSOUND_CONTROL_RESERVED04_OFFSET = (unsigned int)&(((RedSoundCONTROL*)0)->m_reserved04),
	REDSOUND_CONTROL_KEY_SIGNATURE_DATA_OFFSET = (unsigned int)&(((RedSoundCONTROL*)0)->m_keySignatureData),
	REDSOUND_CONTROL_TICK_OFFSET = (unsigned int)&(((RedSoundCONTROL*)0)->m_tick),
	REDSOUND_CONTROL_TICKS_PER_MEASURE_OFFSET = (unsigned int)&(((RedSoundCONTROL*)0)->m_ticksPerMeasure),
	REDSOUND_CONTROL_TIME_NUMERATOR_OFFSET = (unsigned int)&(((RedSoundCONTROL*)0)->m_timeNumerator),
	REDSOUND_CONTROL_TIME_DENOMINATOR_OFFSET = (unsigned int)&(((RedSoundCONTROL*)0)->m_timeDenominator),
	REDSOUND_CONTROL_VOLUME_OFFSET = (unsigned int)&(((RedSoundCONTROL*)0)->m_volume),
	REDSOUND_CONTROL_RESERVED460_OFFSET = (unsigned int)&(((RedSoundCONTROL*)0)->m_reserved460),
	REDSOUND_CONTROL_FLAGS_OFFSET = (unsigned int)&(((RedSoundCONTROL*)0)->m_flags),
	REDSOUND_CONTROL_SKIP_FRAMES_OFFSET = (unsigned int)&(((RedSoundCONTROL*)0)->m_skipFrames),
	REDSOUND_CONTROL_ELAPSED_TIME_OFFSET = (unsigned int)&(((RedSoundCONTROL*)0)->m_elapsedTime),
	REDSOUND_CONTROL_WAVE_NO_OFFSET = (unsigned int)&(((RedSoundCONTROL*)0)->m_waveNo),
	REDSOUND_CONTROL_KEY_SIGNATURE_OFFSET = (unsigned int)&(((RedSoundCONTROL*)0)->m_keySignature),
	REDSOUND_CONTROL_LOOP_BASE_OFFSET = (unsigned int)&(((RedSoundCONTROL*)0)->m_loopBase),
	REDSOUND_CONTROL_UPDATE_FLAGS_OFFSET = (unsigned int)&(((RedSoundCONTROL*)0)->m_updateFlags),
	REDSOUND_CONTROL_TICK_COUNTER_OFFSET = (unsigned int)&(((RedSoundCONTROL*)0)->m_tickCounter),
	REDSOUND_CONTROL_ACTIVE_TRACK_COUNT_OFFSET = (unsigned int)&(((RedSoundCONTROL*)0)->m_activeTrackCount),
	REDSOUND_CONTROL_CHANNEL_ALLOC_OFFSET = (unsigned int)&(((RedSoundCONTROL*)0)->m_channelAlloc),
	REDSOUND_CONTROL_TRACK_COUNT_OFFSET = (unsigned int)&(((RedSoundCONTROL*)0)->m_trackCount),
	REDSOUND_CONTROL_VOLUME_SCALE_OFFSET = (unsigned int)&(((RedSoundCONTROL*)0)->m_volumeScale),
	REDSOUND_CONTROL_RESERVED493_OFFSET = (unsigned int)&(((RedSoundCONTROL*)0)->m_reserved493),
};

enum RedSoundControlBufferOffset {
	REDSOUND_CONTROL_WORD_COUNT = sizeof(RedSoundCONTROL) / sizeof(int),
	REDSOUND_CONTROL_SECONDARY_TRACKS_WORD_OFFSET = REDSOUND_CONTROL_WORD_COUNT,
	REDSOUND_CONTROL_SECONDARY_FLAGS_WORD_OFFSET =
	    REDSOUND_CONTROL_SECONDARY_TRACKS_WORD_OFFSET + REDSOUND_CONTROL_FLAGS_OFFSET / sizeof(int),
	REDSOUND_CONTROL_SECONDARY_ACTIVE_TRACK_COUNT_OFFSET =
	    REDSOUND_CONTROL_SECONDARY_TRACKS_WORD_OFFSET * sizeof(int) + REDSOUND_CONTROL_ACTIVE_TRACK_COUNT_OFFSET,
	REDSOUND_CONTROL_SECONDARY_TRACK_COUNT_OFFSET =
	    REDSOUND_CONTROL_SECONDARY_TRACKS_WORD_OFFSET * sizeof(int) + REDSOUND_CONTROL_TRACK_COUNT_OFFSET,
	REDSOUND_CONTROL_SECONDARY_END_WORD_OFFSET =
	    REDSOUND_CONTROL_SECONDARY_TRACKS_WORD_OFFSET + REDSOUND_CONTROL_WORD_COUNT,
	REDSOUND_CONTROL_MUSIC_END_WORD_OFFSET = REDSOUND_CONTROL_SECONDARY_END_WORD_OFFSET + REDSOUND_CONTROL_WORD_COUNT,
};

enum RedSoundControlUpdateFlag {
	REDSOUND_CONTROL_UPDATE_VOICE_STEAL = 2,
};

enum RedSoundControlSaveSize {
	REDSOUND_CONTROL_SAVED_POSITION_WORD_COUNT = 4,
	REDSOUND_CONTROL_SAVED_POSITION_ALLOC_SIZE = sizeof(RedSoundControlPosition),
	REDSOUND_CONTROL_SAVED_POSITION_SIZE = sizeof(RedSoundControlPosition),
	REDSOUND_CONTROL_SAVED_TEMPO_WORD_COUNT = 3,
	REDSOUND_CONTROL_SAVED_TEMPO_ALLOC_SIZE = sizeof(RedSoundControlTempo),
	REDSOUND_CONTROL_SAVED_TEMPO_SIZE = sizeof(RedSoundControlTempo),
};

typedef void (*RedMidiControlFunc)(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);

enum RedMidiCtrlStatusIndex {
	REDSOUND_MIDI_CTRL_STATUS_0 = 0,
	REDSOUND_MIDI_CTRL_STATUS_1 = 1,
	REDSOUND_MIDI_CTRL_STATUS_2 = 2,
	REDSOUND_MIDI_CTRL_STATUS_COUNT = 3,
};

class CRedMidiCtrl
{
public:
	CRedMidiCtrl();
	~CRedMidiCtrl();

	void Init();

private:
	int m_status[REDSOUND_MIDI_CTRL_STATUS_COUNT];
};

int DataAddCompute(int* current, int target, int* delta);
void KeyOnReserveClear(RedKeyOnDATA* keyOnData, RedTrackDATA* track);
void KeyOnReserve(RedKeyOnDATA* keyOnData, RedTrackDATA* track);
void KeyOffSet(RedSoundCONTROL* control, RedKeyOnDATA* keyOnData, RedTrackDATA* track);

extern RedMidiControlFunc p_MidiControl_Function[REDSOUND_MIDI_CONTROL_FUNCTION_COUNT];
extern RedSwingFunc SwingEntryFunction[REDSOUND_SWING_FUNCTION_COUNT];

#endif // _FFCC_REDSOUND_REDMIDICTRL_H
