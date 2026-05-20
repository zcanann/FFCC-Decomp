#include "ffcc/RedSound/RedCommand.h"
#include "ffcc/RedSound/RedEntry.h"
#include "ffcc/RedSound/RedDriver.h"
#include "ffcc/RedSound/RedGlobals.h"
#include "ffcc/RedSound/RedMemory.h"
#include "ffcc/RedSound/RedMidiCtrl.h"
#include "global.h"
#include <dolphin/os.h>
#include <string.h>

static const char sRedCommandLogWarnColor[] = "\x1B[4;31m";
static const char sRedCommandLogReset[] = "\x1B[0m";
static const char sRedCommandLogErrorColor[] = "\x1B[7;31m";
static const char sRedCommandWaveNotEntryFmt[] = "%s%sWave is not Entry. (wave%4.4u)%s\n";
static const char sRedCommandLogPrefix[] = "\x1B[7;34mSound\x1B[0m:";
static const char sRedCommandSePauseOnFmt[] = "%sPause : SE     : ON  %d\n";
static const char sRedCommandSePauseOffFmt[] = "%sPause : SE     : OFF %d\n";
static const char sRedCommandMusicTrackCreateErrorFmt[] = "%s%sMusic Start : Couldn't Create Track.%s\n";
static const char sRedCommandMusicNeedMemoryFmt[] = "%s%s            : music%3.3u.bgm : need 0x%6.6X%s\n";
static const char sRedCommandMusicPauseOnFmt[] = "%sPause : Music  : ON  %d\n";
static const char sRedCommandMusicPauseOffFmt[] = "%sPause : Music  : OFF %d\n";

enum RedCommandStringLayout {
	REDSOUND_COMMAND_WARN_COLOR_SIZE = 0x08,
	REDSOUND_COMMAND_RESET_SIZE = 0x05,
	REDSOUND_COMMAND_ERROR_COLOR_SIZE = 0x08,
	REDSOUND_COMMAND_WAVE_NOT_ENTRY_FMT_SIZE = 0x26,
	REDSOUND_COMMAND_LOG_PREFIX_SIZE = 0x12,
	REDSOUND_COMMAND_SE_PAUSE_ON_FMT_SIZE = 0x1B,
	REDSOUND_COMMAND_SE_PAUSE_OFF_FMT_SIZE = 0x1B,
	REDSOUND_COMMAND_MUSIC_TRACK_CREATE_ERROR_FMT_SIZE = 0x2C,
	REDSOUND_COMMAND_MUSIC_NEED_MEMORY_FMT_SIZE = 0x33,
	REDSOUND_COMMAND_MUSIC_PAUSE_ON_FMT_SIZE = 0x1B,
	REDSOUND_COMMAND_MUSIC_PAUSE_OFF_FMT_SIZE = 0x1B,
	REDSOUND_COMMAND_RODATA_STRING_SIZE = 0x103,
	REDSOUND_COMMAND_SDATA2_STRING_SIZE = 0x15,
};

enum RedCommandMapLayout {
	REDSOUND_COMMAND_MAP_RODATA_STRING_OFFSET = 0x00,
	REDSOUND_COMMAND_MAP_RODATA_STRING_SIZE = 0x103,
	REDSOUND_COMMAND_MAP_SDATA2_STRING_OFFSET = 0x00,
	REDSOUND_COMMAND_MAP_SDATA2_STRING_SIZE = 0x15,
	REDSOUND_COMMAND_MAP_DATA_REVERB_MODE_TABLE_OFFSET = 0x00,
	REDSOUND_COMMAND_MAP_DATA_SIZE = 0xE0,
};

struct RedCommandDataTable {
	RedReverbModeData t_ReverbModeData[REDSOUND_REVERB_MODE_COUNT];
};

enum RedCommandDataLayout {
	REDSOUND_COMMAND_REVERB_MODE_TABLE_OFFSET = (unsigned int)&(((RedCommandDataTable*)0)->t_ReverbModeData),
	REDSOUND_COMMAND_DATA_TABLE_SIZE = sizeof(RedCommandDataTable),
};

enum RedCommandReverbPresetParam {
	REDSOUND_REVERB_PRE_DELAY_10MS = 10,
	REDSOUND_REVERB_PRE_DELAY_15MS = 15,
	REDSOUND_REVERB_PRE_DELAY_20MS = 20,
	REDSOUND_REVERB_PRE_DELAY_30MS = 30,
	REDSOUND_REVERB_PRE_DELAY_40MS = 40,
	REDSOUND_REVERB_TIME_850MS = 850,
	REDSOUND_REVERB_TIME_1400MS = 1400,
	REDSOUND_REVERB_TIME_1500MS = 1500,
	REDSOUND_REVERB_TIME_1800MS = 1800,
	REDSOUND_REVERB_TIME_2400MS = 2400,
	REDSOUND_REVERB_TIME_2500MS = 2500,
	REDSOUND_REVERB_TIME_2800MS = 2800,
	REDSOUND_REVERB_EFFECT_30 = 30,
	REDSOUND_REVERB_EFFECT_40 = 40,
	REDSOUND_REVERB_EFFECT_50 = 50,
	REDSOUND_REVERB_EFFECT_60 = 60,
	REDSOUND_REVERB_EFFECT_70 = 70,
	REDSOUND_REVERB_EFFECT_80 = 80,
	REDSOUND_REVERB_EFFECT_100 = 100,
	REDSOUND_REVERB_CROSSTALK_NONE = 0,
};

enum RedCommandVolumeParam {
	REDSOUND_MUSIC_VOLUME_INPUT_SCALE_SHIFT = 2,
};

enum RedCommandEraseTrack {
	REDSOUND_ERASE_TRACK_SENTINEL = 0x100,
	REDSOUND_SEP_DIRECT_PLAY_ID = 1000000,
	REDSOUND_TRACK_PLAY_TIME_SENTINEL = -1,
};

enum RedCommandMusicTrackBlock {
	REDSOUND_MUSIC_TRACK_BLOCK_SIZE_FIELD_SIZE = sizeof(u32),
	REDSOUND_REVERB_DEPTH_BYTE_SHIFT = 8,
};

enum RedSeInfoSequenceByte {
	REDSOUND_SE_COMMAND_NONE = 0,
};

STATIC_ASSERT(offsetof(RedReverbModeData, m_kind) == REDSOUND_REVERB_MODE_KIND_OFFSET);
STATIC_ASSERT(offsetof(RedReverbModeData, m_params) == REDSOUND_REVERB_MODE_PARAMS_OFFSET);
STATIC_ASSERT(sizeof(t_ReverbModeData[0].m_params) == REDSOUND_REVERB_MODE_PARAMS_ALLOC_SIZE);
STATIC_ASSERT(REDSOUND_REVERB_MODE_PARAMS_SIZE == REDSOUND_REVERB_MODE_PARAMS_ALLOC_SIZE);
STATIC_ASSERT(REDSOUND_REVERB_MODE_PARAMS_OFFSET + REDSOUND_REVERB_MODE_PARAMS_SIZE == REDSOUND_REVERB_MODE_SIZE);
STATIC_ASSERT(sizeof(RedReverbModeData) == REDSOUND_REVERB_MODE_SIZE);
STATIC_ASSERT(REDSOUND_REVERB_MODE_TABLE_SIZE == REDSOUND_REVERB_MODE_TABLE_ALLOC_SIZE);
STATIC_ASSERT(sizeof(t_ReverbModeData) == REDSOUND_REVERB_MODE_TABLE_SIZE);
STATIC_ASSERT(REDSOUND_COMMAND_REVERB_MODE_TABLE_OFFSET ==
              REDSOUND_COMMAND_MAP_DATA_REVERB_MODE_TABLE_OFFSET);
STATIC_ASSERT(sizeof(((RedCommandDataTable*)0)->t_ReverbModeData) == REDSOUND_REVERB_MODE_TABLE_SIZE);
STATIC_ASSERT(REDSOUND_COMMAND_REVERB_MODE_TABLE_OFFSET + sizeof(t_ReverbModeData) ==
              REDSOUND_COMMAND_DATA_TABLE_SIZE);
STATIC_ASSERT(REDSOUND_COMMAND_DATA_TABLE_SIZE == REDSOUND_REVERB_MODE_TABLE_ALLOC_SIZE);
STATIC_ASSERT(REDSOUND_COMMAND_DATA_TABLE_SIZE == REDSOUND_COMMAND_MAP_DATA_SIZE);
STATIC_ASSERT(REDSOUND_MUSIC_TRACK_BLOCK_SIZE_FIELD_SIZE == REDSOUND_MUSIC_TRACK_BLOCK_COMMAND_OFFSET);
STATIC_ASSERT(sizeof(sRedCommandLogWarnColor) == REDSOUND_COMMAND_WARN_COLOR_SIZE);
STATIC_ASSERT(sizeof(sRedCommandLogReset) == REDSOUND_COMMAND_RESET_SIZE);
STATIC_ASSERT(sizeof(sRedCommandLogErrorColor) == REDSOUND_COMMAND_ERROR_COLOR_SIZE);
STATIC_ASSERT(sizeof(sRedCommandWaveNotEntryFmt) == REDSOUND_COMMAND_WAVE_NOT_ENTRY_FMT_SIZE);
STATIC_ASSERT(sizeof(sRedCommandLogPrefix) == REDSOUND_COMMAND_LOG_PREFIX_SIZE);
STATIC_ASSERT(sizeof(sRedCommandSePauseOnFmt) == REDSOUND_COMMAND_SE_PAUSE_ON_FMT_SIZE);
STATIC_ASSERT(sizeof(sRedCommandSePauseOffFmt) == REDSOUND_COMMAND_SE_PAUSE_OFF_FMT_SIZE);
STATIC_ASSERT(sizeof(sRedCommandMusicTrackCreateErrorFmt) == REDSOUND_COMMAND_MUSIC_TRACK_CREATE_ERROR_FMT_SIZE);
STATIC_ASSERT(sizeof(sRedCommandMusicNeedMemoryFmt) == REDSOUND_COMMAND_MUSIC_NEED_MEMORY_FMT_SIZE);
STATIC_ASSERT(sizeof(sRedCommandMusicPauseOnFmt) == REDSOUND_COMMAND_MUSIC_PAUSE_ON_FMT_SIZE);
STATIC_ASSERT(sizeof(sRedCommandMusicPauseOffFmt) == REDSOUND_COMMAND_MUSIC_PAUSE_OFF_FMT_SIZE);
STATIC_ASSERT(sizeof(sRedCommandWaveNotEntryFmt) + sizeof(sRedCommandLogPrefix) +
                  sizeof(sRedCommandSePauseOnFmt) + sizeof(sRedCommandSePauseOffFmt) +
                  sizeof(sRedCommandMusicTrackCreateErrorFmt) + sizeof(sRedCommandMusicNeedMemoryFmt) +
                  sizeof(sRedCommandMusicPauseOnFmt) + sizeof(sRedCommandMusicPauseOffFmt) ==
              REDSOUND_COMMAND_RODATA_STRING_SIZE);
STATIC_ASSERT(REDSOUND_COMMAND_MAP_RODATA_STRING_OFFSET == 0);
STATIC_ASSERT(REDSOUND_COMMAND_RODATA_STRING_SIZE == REDSOUND_COMMAND_MAP_RODATA_STRING_SIZE);
STATIC_ASSERT(sizeof(sRedCommandLogWarnColor) + sizeof(sRedCommandLogReset) +
                  sizeof(sRedCommandLogErrorColor) ==
              REDSOUND_COMMAND_SDATA2_STRING_SIZE);
STATIC_ASSERT(REDSOUND_COMMAND_MAP_SDATA2_STRING_OFFSET == 0);
STATIC_ASSERT(REDSOUND_COMMAND_SDATA2_STRING_SIZE == REDSOUND_COMMAND_MAP_SDATA2_STRING_SIZE);

RedReverbModeData t_ReverbModeData[REDSOUND_REVERB_MODE_COUNT] = {
    {REDSOUND_REVERB_KIND_HI, {REDSOUND_REVERB_PRE_DELAY_10MS, REDSOUND_REVERB_TIME_1400MS,
                               REDSOUND_REVERB_EFFECT_30, REDSOUND_REVERB_EFFECT_70,
                               REDSOUND_REVERB_EFFECT_100, REDSOUND_REVERB_CROSSTALK_NONE}},
    {REDSOUND_REVERB_KIND_HI, {REDSOUND_REVERB_PRE_DELAY_20MS, REDSOUND_REVERB_TIME_1800MS,
                               REDSOUND_REVERB_EFFECT_30, REDSOUND_REVERB_EFFECT_80,
                               REDSOUND_REVERB_EFFECT_100, REDSOUND_REVERB_CROSSTALK_NONE}},
    {REDSOUND_REVERB_KIND_HI, {REDSOUND_REVERB_PRE_DELAY_30MS, REDSOUND_REVERB_TIME_2400MS,
                               REDSOUND_REVERB_EFFECT_30, REDSOUND_REVERB_EFFECT_80,
                               REDSOUND_REVERB_EFFECT_100, REDSOUND_REVERB_CROSSTALK_NONE}},
    {REDSOUND_REVERB_KIND_HI, {REDSOUND_REVERB_PRE_DELAY_40MS, REDSOUND_REVERB_TIME_2800MS,
                               REDSOUND_REVERB_EFFECT_30, REDSOUND_REVERB_EFFECT_80,
                               REDSOUND_REVERB_EFFECT_100, REDSOUND_REVERB_CROSSTALK_NONE}},
    {REDSOUND_REVERB_KIND_HI, {REDSOUND_REVERB_PRE_DELAY_15MS, REDSOUND_REVERB_TIME_850MS,
                               REDSOUND_REVERB_EFFECT_50, REDSOUND_REVERB_EFFECT_80,
                               REDSOUND_REVERB_EFFECT_100, REDSOUND_REVERB_CROSSTALK_NONE}},
    {REDSOUND_REVERB_KIND_HI, {REDSOUND_REVERB_PRE_DELAY_30MS, REDSOUND_REVERB_TIME_1500MS,
                               REDSOUND_REVERB_EFFECT_50, REDSOUND_REVERB_EFFECT_60,
                               REDSOUND_REVERB_EFFECT_100, REDSOUND_REVERB_CROSSTALK_NONE}},
    {REDSOUND_REVERB_KIND_HI, {REDSOUND_REVERB_PRE_DELAY_40MS, REDSOUND_REVERB_TIME_2500MS,
                               REDSOUND_REVERB_EFFECT_50, REDSOUND_REVERB_EFFECT_40,
                               REDSOUND_REVERB_EFFECT_100, REDSOUND_REVERB_CROSSTALK_NONE}},
    {REDSOUND_REVERB_KIND_HI, {REDSOUND_REVERB_PRE_DELAY_40MS, REDSOUND_REVERB_TIME_2500MS,
                               REDSOUND_REVERB_EFFECT_50, REDSOUND_REVERB_EFFECT_80,
                               REDSOUND_REVERB_EFFECT_100, REDSOUND_REVERB_CROSSTALK_NONE}},
};

static void _EraseAttribute(int eraseTrack, int attrMask);
static int _EraseTime(int eraseTrack);
static int _SePlayStart(RedSeINFO* seInfo, int seId, int sepId, int pan, int volume);
static RedTrackDATA* _MusicPlayStart(RedMusicHEAD* musicHead, RedWaveHeadWD* waveHead, int musicId, int volume,
                                     int mode);

static inline void RedTrackAdsrFillDefault(RedAdsrDATA* adsr)
{
	memset(adsr, REDSOUND_TRACK_ADSR_DEFAULT_BYTE, REDSOUND_TRACK_ADSR_SIZE);
}

/*
 * --INFO--
 * PAL Address: 0x801ca038
 * PAL Size: 364b
 * EN Address: 0x8020bf5c
 * EN Size: 364b
 * JP Address: TODO
 * JP Size: TODO
 */
static void _EraseAttribute(int eraseTrack, int attrMask)
{
	RedTrackDATA** trackBasePtr = &RedSoundControlGet(REDSOUND_CONTROL_SE)->m_tracks;
	RedTrackDATA* track = *trackBasePtr;

	do {
		if ((track->m_command != REDSOUND_TRACK_COMMAND_NONE) && (track->m_eraseTrack <= eraseTrack) &&
		    ((((unsigned int)track->m_attrMask) & (unsigned int)attrMask) != 0)) {
			int trackNo;

			KeyOnReserveClear(RedKeyOnDataGet(), track);
			track->m_seId = REDSOUND_SE_ID_NONE;
			track->m_flags = REDSOUND_TRACK_FLAGS_NONE;
			track->m_command = REDSOUND_TRACK_COMMAND_NONE;
			track->m_mixVolumeMode = REDSOUND_SE_VOLUME_MODE_NORMAL;

			trackNo = track->m_trackNo;
			RedVoiceDataGet(trackNo)->m_stateFlags &= REDSOUND_VOICE_STATE_CLEAR_PLAYING_MASK;
			RedVoiceDataGet(trackNo)->m_voiceSwitch &= REDSOUND_VOICE_SWITCH_CLEAR_SE_MASK;
			RedVoiceDataGet(trackNo)->m_flags &= REDSOUND_VOICE_FLAGS_CLEAR_ACTIVE_MASK;
			RedVoiceDataGet(trackNo)->m_flags |= REDSOUND_VOICE_FLAGS_RELEASED;
			RedVoiceDataGet(trackNo)->m_active = REDSOUND_VOICE_ACTIVE_OFF;

			c_RedEntry.SeSepHistoryManager(REDSOUND_HISTORY_MODE_RELEASE, track->m_seSepId);
			if (track->m_waveBankData != REDSOUND_WAVE_BANK_DATA_NONE) {
				c_RedEntry.WaveHistoryManager(REDSOUND_HISTORY_MODE_RELEASE, track->m_waveBankData->m_waveNo);
			}
		}
		track++;
	} while (track < RedSeTrackGetEnd(*trackBasePtr));
}
/*
 * --INFO--
 * PAL Address: 0x801ca1a4
 * PAL Size: 536b
 * EN Address: 0x8020c0c8
 * EN Size: 536b
 * JP Address: TODO
 * JP Size: TODO
 */
static int _EraseTime(int eraseTrack)
{
	int minEraseTrack = REDSOUND_ERASE_TRACK_SENTINEL;
	RedTrackDATA** trackBasePtr = &RedSoundControlGet(REDSOUND_CONTROL_SE)->m_tracks;
	RedTrackDATA* track = *trackBasePtr;
	int sepId;
	int erasedCount;

	do {
		if ((track->m_command != REDSOUND_TRACK_COMMAND_NONE) && (track->m_attrMask == REDSOUND_TRACK_ATTR_NONE) &&
		    (track->m_eraseTrack < minEraseTrack)) {
			minEraseTrack = track->m_eraseTrack;
		}
		track++;
	} while (track < RedSeTrackGetEnd(*trackBasePtr));

	if (eraseTrack > minEraseTrack) {
		eraseTrack = minEraseTrack;
	}

	track = *trackBasePtr;
	minEraseTrack = 0;
	sepId = 0;
	do {
		if ((track->m_command != REDSOUND_TRACK_COMMAND_NONE) && (track->m_attrMask == REDSOUND_TRACK_ATTR_NONE) &&
		    (track->m_eraseTrack <= eraseTrack) &&
		    (track->m_playTime > minEraseTrack)) {
			minEraseTrack = track->m_playTime;
			sepId = track->m_seSepId;
		}
		track++;
	} while (track < RedSeTrackGetEnd(*trackBasePtr));

	track = *trackBasePtr;
	erasedCount = 0;
	do {
		if ((track->m_command != REDSOUND_TRACK_COMMAND_NONE) && (track->m_attrMask == REDSOUND_TRACK_ATTR_NONE) &&
		    (track->m_eraseTrack <= eraseTrack) &&
		    (track->m_playTime == minEraseTrack)) {
			int trackNo;

			KeyOnReserveClear(RedKeyOnDataGet(), track);
			track->m_seId = REDSOUND_SE_ID_NONE;
			track->m_flags = REDSOUND_TRACK_FLAGS_NONE;
			track->m_command = REDSOUND_TRACK_COMMAND_NONE;
			track->m_mixVolumeMode = REDSOUND_SE_VOLUME_MODE_NORMAL;

			trackNo = track->m_trackNo;
			RedVoiceDataGet(trackNo)->m_stateFlags &= REDSOUND_VOICE_STATE_CLEAR_PLAYING_MASK;
			RedVoiceDataGet(trackNo)->m_voiceSwitch &= REDSOUND_VOICE_SWITCH_CLEAR_SE_MASK;
			RedVoiceDataGet(trackNo)->m_flags &= REDSOUND_VOICE_FLAGS_CLEAR_ACTIVE_MASK;
			RedVoiceDataGet(trackNo)->m_flags |= REDSOUND_VOICE_FLAGS_RELEASED;
			RedVoiceDataGet(trackNo)->m_active = REDSOUND_VOICE_ACTIVE_OFF;

			if (track->m_waveBankData != REDSOUND_WAVE_BANK_DATA_NONE) {
				c_RedEntry.WaveHistoryManager(REDSOUND_HISTORY_MODE_RELEASE, track->m_waveBankData->m_waveNo);
			}
			erasedCount++;
		}
		track++;
	} while (track < RedSeTrackGetEnd(*trackBasePtr));

	if (erasedCount != 0) {
		c_RedEntry.SeSepHistoryManager(REDSOUND_HISTORY_MODE_RELEASE, sepId);
	}

	return erasedCount;
}
/*
 * --INFO--
 * PAL Address: 0x801ca3bc
 * PAL Size: 252b
 * EN Address: 0x8020c2e0
 * EN Size: 252b
 * JP Address: TODO
 * JP Size: TODO
 */
RedTrackDATA* SearchSeEmptyTrack(int trackCount, int eraseTrack, int attrMask)
{
	RedTrackDATA** trackBasePtr = &RedSoundControlGet(REDSOUND_CONTROL_SE)->m_tracks;
	RedTrackDATA* scan;
	RedTrackDATA* track;
	int remaining;
	int erasedCount;

	if (attrMask != 0) {
		_EraseAttribute(eraseTrack, attrMask);
	}
	volatile int unused = 0;
	erasedCount = 0;

	do {
		scan = RedSeTrackGetLast(*trackBasePtr);
		do {
			track = scan;
			remaining = trackCount - 1;
			while (remaining != 0) {
				if ((track->m_command != REDSOUND_TRACK_COMMAND_NONE) ||
				    ((track->m_note.m_allocFlags & REDSOUND_NOTE_ALLOC_STREAM) != 0)) {
					break;
				}
				track--;
				remaining--;
			}
			if ((track->m_command != REDSOUND_TRACK_COMMAND_NONE) ||
			    ((track->m_note.m_allocFlags & REDSOUND_NOTE_ALLOC_STREAM) != 0)) {
				scan = track;
				remaining = 1;
			}
			scan--;
		} while ((remaining != 0) && (track >= *trackBasePtr));
	} while ((track < *trackBasePtr) && ((erasedCount = _EraseTime(eraseTrack)) != 0));

	if (track >= *trackBasePtr) {
		return track;
	}

	return REDSOUND_TRACK_NONE;
}
/*
 * --INFO--
 * PAL Address: 0x801ca4b8
 * PAL Size: 384b
 * EN Address: 0x8020c3dc
 * EN Size: 384b
 * JP Address: TODO
 * JP Size: TODO
 */
int SeStopID(int seId)
{
	RedSoundCONTROL* soundControl;
	RedTrackDATA* track;

	soundControl = RedSoundControlGet(REDSOUND_CONTROL_SE);
	soundControl->m_updateFlags = 0;
	track = soundControl->m_tracks;
	do {
		if ((track->m_command != REDSOUND_TRACK_COMMAND_NONE) &&
		    ((seId == REDSOUND_SE_ID_ALL) || (track->m_seId == seId))) {
			int trackNo;

			KeyOnReserveClear(RedKeyOnDataGet(), track);
			track->m_seId = REDSOUND_SE_ID_NONE;
			track->m_flags = REDSOUND_TRACK_FLAGS_NONE;
			track->m_command = REDSOUND_TRACK_COMMAND_NONE;
			track->m_mixVolumeMode = REDSOUND_SE_VOLUME_MODE_NORMAL;

			trackNo = track->m_trackNo;
			RedVoiceDataGet(trackNo)->m_stateFlags &= REDSOUND_VOICE_STATE_CLEAR_PLAYING_MASK;
			RedVoiceDataGet(trackNo)->m_voiceSwitch &= REDSOUND_VOICE_SWITCH_CLEAR_SE_MASK;
			RedVoiceDataGet(trackNo)->m_flags &= REDSOUND_VOICE_FLAGS_CLEAR_ACTIVE_MASK;
			RedVoiceDataGet(trackNo)->m_flags |= REDSOUND_VOICE_FLAGS_RELEASED;
			RedVoiceDataGet(trackNo)->m_track = REDSOUND_VOICE_TRACK_NONE;
			RedVoiceDataGet(trackNo)->m_active = REDSOUND_VOICE_ACTIVE_OFF;

			if (track->m_waveBankData != REDSOUND_WAVE_BANK_DATA_NONE) {
				c_RedEntry.WaveHistoryManager(REDSOUND_HISTORY_MODE_RELEASE, track->m_waveBankData->m_waveNo);
			}
			c_RedEntry.SeSepHistoryManager(REDSOUND_HISTORY_MODE_RELEASE, track->m_seSepId);
		}
		track++;
	} while (track < RedSoundControlGetSeTrackEnd(soundControl));

	return 0;
}
/*
 * --INFO--
 * PAL Address: 0x801ca638
 * PAL Size: 464b
 * EN Address: 0x8020c55c
 * EN Size: 464b
 * JP Address: TODO
 * JP Size: TODO
 */
int SeStopMG(int bank, int sep, int group, int kind)
{
	RedSoundCONTROL* soundControl;
	RedTrackDATA* track;

	soundControl = RedSoundControlGet(REDSOUND_CONTROL_SE);
	soundControl->m_updateFlags = 0;
	track = soundControl->m_tracks;
	do {
		if ((track->m_command != REDSOUND_TRACK_COMMAND_NONE) &&
		    RedSeBlockIdIsSeSepData(track->m_seSepId)) {
			int id = track->m_seSepId / REDSOUND_SE_MG_ID_DIVISOR;
			if ((bank != id) && (sep != id) && (group != id) && (kind != id)) {
				int trackNo;

				KeyOnReserveClear(RedKeyOnDataGet(), track);
				track->m_seId = REDSOUND_SE_ID_NONE;
				track->m_flags = REDSOUND_TRACK_FLAGS_NONE;
				track->m_command = REDSOUND_TRACK_COMMAND_NONE;
				track->m_mixVolumeMode = REDSOUND_SE_VOLUME_MODE_NORMAL;

				trackNo = track->m_trackNo;
				RedVoiceDataGet(trackNo)->m_stateFlags &= REDSOUND_VOICE_STATE_CLEAR_PLAYING_MASK;
				RedVoiceDataGet(trackNo)->m_voiceSwitch &= REDSOUND_VOICE_SWITCH_CLEAR_SE_MASK;
				RedVoiceDataGet(trackNo)->m_flags &= REDSOUND_VOICE_FLAGS_CLEAR_ACTIVE_MASK;
				RedVoiceDataGet(trackNo)->m_flags |= REDSOUND_VOICE_FLAGS_RELEASED;
				RedVoiceDataGet(trackNo)->m_track = REDSOUND_VOICE_TRACK_NONE;
				RedVoiceDataGet(trackNo)->m_active = REDSOUND_VOICE_ACTIVE_OFF;

				if (track->m_waveBankData != REDSOUND_WAVE_BANK_DATA_NONE) {
					c_RedEntry.WaveHistoryManager(REDSOUND_HISTORY_MODE_RELEASE, track->m_waveBankData->m_waveNo);
				}
				c_RedEntry.SeSepHistoryManager(REDSOUND_HISTORY_MODE_RELEASE, track->m_seSepId);
			}
		}
		track++;
	} while (track < RedSoundControlGetSeTrackEnd(soundControl));

	return 0;
}
/*
 * --INFO--
 * PAL Address: 0x801ca808
 * PAL Size: 936b
 * EN Address: 0x8020c72c
 * EN Size: 936b
 * JP Address: TODO
 * JP Size: TODO
 */
static int _SePlayStart(RedSeINFO* seInfo, int seId, int sepId, int pan, int volume)
{
	unsigned char seFlagsAndSequenceCount;
	RedWaveHeadWD* waveHead;
	RedTrackDATA* seTrack;
	int eraseAttrMask;
	RedSeInfoSequence* sequence;
	int waveNo;
	int remainingSequences;
	unsigned char* sequenceCommandData;
	int tracksToStart;
	RedVoiceDATA* voice;
	int multiLoopReport;

	RedSoundControlGet(REDSOUND_CONTROL_SE)->m_updateFlags = 0;
	waveNo = (unsigned int)seInfo->m_waveNoHi * REDSOUND_SE_INFO_U16_HIGH_SCALE +
	         (unsigned int)seInfo->m_waveNoLo;
	waveHead = c_RedEntry.SearchWaveBase(waveNo);
	if (waveHead != 0) {
		c_RedEntry.WaveHistoryManager(REDSOUND_HISTORY_MODE_USE, waveHead->m_waveNo);
	} else {
		if (RedReportPrintIsEnabled()) {
			OSReport(sRedCommandWaveNotEntryFmt, sRedCommandLogPrefix, sRedCommandLogWarnColor,
			         waveNo, sRedCommandLogReset);
			fflush(__files + 1);
		}
	}

	seFlagsAndSequenceCount = seInfo->m_flagsAndCount;
	if (RedSeInfoFlagsHasMulti(seFlagsAndSequenceCount)) {
		multiLoopReport = 1;
	} else {
		multiLoopReport = 0;
	}
	sequence = RedSeInfoGetSequences(seInfo);
	eraseAttrMask = seInfo->m_attrMask;
	remainingSequences = RedSeInfoGetSequenceCount(seInfo);
	sequenceCommandData = RedSeInfoGetCommandData(sequence, remainingSequences);
	do {
		if (sepId != REDSOUND_SEP_DIRECT_PLAY_ID) {
			tracksToStart = 0;
			do {
				tracksToStart = tracksToStart + 1;
				if (!RedSeInfoSequenceHasContinue(sequence, tracksToStart)) {
					break;
				}
			} while ((int)tracksToStart < (int)remainingSequences);
		} else {
			tracksToStart = remainingSequences;
		}

		seTrack = SearchSeEmptyTrack((int)tracksToStart, seInfo->m_eraseTrack, eraseAttrMask);
		eraseAttrMask = 0;
		if (seTrack == 0) {
			break;
		}

		voice = RedVoiceDataGet(seTrack->m_trackNo);
		while (true) {
			seTrack->m_waveBankData = waveHead;
			seTrack->m_command = sequenceCommandData;
			sequenceCommandData = RedSeInfoCommandGetNext(sequenceCommandData, sequence);
			seTrack->m_deltaTime = (int)DeltaTimeSumup((unsigned char**)&seTrack->m_command) + 1;
			if (RedSeSkipStepIsActive()) {
				seTrack->m_deltaTime = seTrack->m_deltaTime - RedSeSkipStepGet();
			}

			seTrack->m_seSepId = sepId;
			seTrack->m_seId = seId;
			seTrack->m_loopStepCurrent = 0;
			seTrack->m_playTime = RedSeSkipStepIsActive() ? 0 : REDSOUND_TRACK_PLAY_TIME_SENTINEL;

			if (*seTrack->m_command != REDSOUND_SE_COMMAND_NONE) {
				seTrack->m_eraseTrack = seInfo->m_eraseTrack;
				seTrack->m_attrMask = seInfo->m_attrMask;
				seTrack->m_mixVolume = volume << REDSOUND_FIXED_SHIFT;
				seTrack->m_mixVolumeDelta = 0;
				seTrack->m_mixVolumeMode = REDSOUND_SE_VOLUME_MODE_NORMAL;
				seTrack->m_pitchDelta = 0;
				seTrack->m_pitch = 0;
				seTrack->m_loopReport = multiLoopReport;
				seTrack->m_volume = REDSOUND_VOLUME_FULL;
				seTrack->m_expression = REDSOUND_VOLUME_DEFAULT;
				seTrack->m_pan = pan << REDSOUND_FIXED_SHIFT;
				seTrack->m_reverbDepth = RedReverbDepthGetDepth(REDSOUND_REVERB_DEPTH_SE);
				seTrack->m_reverbDepthDelta = 0;
				seTrack->m_panDelta = 0;
				seTrack->m_expressionDelta = 0;
				seTrack->m_volumeDelta = 0;
				seTrack->m_sweepAdd = 0;
				seTrack->m_sweepDelta = 0;
				seTrack->m_portamentTime = 0;
				seTrack->m_loopDepth = 0;
				seTrack->m_keyTranspose = 0;
				seTrack->m_pitchBendRange = REDSOUND_SE_DEFAULT_PITCH_BEND_RANGE;
				seTrack->m_pitchBend = 0;
				seTrack->m_pitchBendRaw = 0;
				seTrack->m_fineTune = 0;
				seTrack->m_shakeFunc = REDSOUND_SWING_FUNC_NONE;
				seTrack->m_tremoloFunc = REDSOUND_SWING_FUNC_NONE;
				seTrack->m_vibrateFunc = REDSOUND_SWING_FUNC_NONE;
				seTrack->m_shakePan = 0;
				seTrack->m_tremoloDelay = 0;
				seTrack->m_vibrateDelay = 0;
				seTrack->m_tremoloDelayDepth = 0;
				seTrack->m_vibrateDelayDepth = 0;
				seTrack->m_waveData = REDSOUND_WAVE_DATA_NONE;
				seTrack->m_flags = REDSOUND_TRACK_FLAGS_NONE;
				seTrack->m_step2 = 0;
				seTrack->m_step = 0;
				seTrack->m_fuzzyAdsrDepth = 0;
				seTrack->m_fuzzyDeltaTimeDepth = 0;
				seTrack->m_fuzzyPanDepth = 0;
				seTrack->m_fuzzyVolumeDepth = 0;
				seTrack->m_fuzzyPitchDepth = 0;
				seTrack->m_portamentPitch = REDSOUND_TRACK_PORTAMENT_PITCH_NONE;
				seTrack->m_voiceSwitch = REDSOUND_VOICE_SWITCH_DRY_STEREO;
				memset(&seTrack->m_adsr, REDSOUND_TRACK_ADSR_DEFAULT_WORD, REDSOUND_TRACK_ADSR_SIZE);
				seTrack->m_note.m_allocFlags = REDSOUND_NOTE_ALLOC_DIRECT_MASK;
				seTrack->m_seTickCounter = 1;
				voice->m_track = seTrack;
				voice->m_stateFlags = REDSOUND_VOICE_STATE_PLAYING | REDSOUND_VOICE_STATE_SE;
				voice->m_flags = REDSOUND_VOICE_FLAGS_RELEASED;
				voice->m_volumeModFrames = 0;
				voice->m_pitchModFrames = 0;
				voice->m_updateFlags = 0;
			}

			tracksToStart = tracksToStart - 1;
			sequence++;
			remainingSequences = remainingSequences - 1;
			if (tracksToStart == 0) {
				break;
			}
			seTrack++;
			voice++;
		}

		if (remainingSequences == 0) {
			return seId;
		}
	} while (true);

	SeStopID(seId);
	return 0;
}
/*
 * --INFO--
 * PAL Address: 0x801cabb0
 * PAL Size: 264b
 * EN Address: 0x8020cad4
 * EN Size: 264b
 * JP Address: TODO
 * JP Size: TODO
 */
int SeBlockPlay(int seId, int bank, int sequenceNo, int pan, int volume)
{
	RedSeBlockHEAD* seBlock;
	int blockSequence;
	int* entries;
	RedSeINFO* seInfo;
	RedSeINFO* playInfo;

	bank = bank & REDSOUND_SE_BLOCK_BANK_MASK;
	sequenceNo = sequenceNo & REDSOUND_SE_BLOCK_SEQUENCE_MASK;

	if (RedSeBlockDataGet(bank) != REDSOUND_SE_BLOCK_DATA_NONE) {
		seBlock = RedSeBlockDataGet(bank);
		blockSequence = sequenceNo;

		RedSeBlockIdAddBank(sequenceNo, bank);
		RedSeBlockIdSetDataFlag(sequenceNo);
		if (blockSequence < seBlock->m_seCount) {
			entries = seBlock->m_entries;

			if (entries[blockSequence] != REDSOUND_SE_BLOCK_ENTRY_EMPTY) {
				seInfo = RedSeBlockGetInfoFromEntry(seBlock, entries, blockSequence);
				playInfo = seInfo;

				if (RedSeBlockIdIsBlockData((unsigned int)entries[blockSequence])) {
					playInfo->m_flagsAndCount |= REDSOUND_SE_INFO_MULTI_FLAG;
				}
				if (_SePlayStart(playInfo, seId, sequenceNo, pan, volume) != 0) {
					return blockSequence;
				}
			}
		}
	}

	return REDSOUND_SE_PLAY_FAILED;
}
/*
 * --INFO--
 * PAL Address: 0x801cacb8
 * PAL Size: 192b
 * EN Address: 0x8020cbdc
 * EN Size: 192b
 * JP Address: TODO
 * JP Size: TODO
 */
int SeSepPlay(int seId, int sepId, int pan, int volume)
{
	RedHistoryBANK* sepBank;
	RedSeSepHEAD* sepHead;
	RedSeINFO* sepInfo;

	sepBank = c_RedEntry.SearchSeSepBank(sepId);
	if (sepBank != 0) {
		sepHead = sepBank->m_seSepHead;
		sepInfo = RedSeSepGetInfo(sepHead);
		if (RedSeSepHasFlags(sepHead)) {
			sepInfo->m_flagsAndCount |= REDSOUND_SE_INFO_MULTI_FLAG;
		}
		if (_SePlayStart(sepInfo, seId, sepId, pan, volume) != 0) {
			c_RedEntry.SeSepHistoryManager(REDSOUND_HISTORY_MODE_USE, sepId);
			return sepId;
		}
	}
	return REDSOUND_SE_PLAY_FAILED;
}
/*
 * --INFO--
 * PAL Address: 0x801cad78
 * PAL Size: 168b
 * EN Address: 0x8020cc9c
 * EN Size: 168b
 * JP Address: TODO
 * JP Size: TODO
 */
void SetSeVolume(int seId, int volume, int frameCount, int mode)
{
	RedTrackDATA* track;
	volume <<= REDSOUND_FIXED_SHIFT;
	volume |= REDSOUND_FIXED_HALF;

	if (frameCount < 1) {
		frameCount = 1;
	}

	frameCount *= REDSOUND_SE_FADE_TICKS_PER_SECOND;
	frameCount /= REDSOUND_FRAMES_PER_SECOND;
	track = RedSoundControlGet(REDSOUND_CONTROL_SE)->m_tracks;

	do {
		if ((track->m_command != REDSOUND_TRACK_COMMAND_NONE) &&
		    ((seId < REDSOUND_SE_ID_MIN) || (track->m_seId == seId))) {
			int delta = volume - track->m_mixVolume;
			delta /= frameCount;
			track->m_mixVolumeAdd = delta;
			track->m_mixVolumeDelta = frameCount;
			track->m_mixVolumeMode = mode;
		}
		track++;
	} while (track < RedSoundControlGetSeTrackEnd(RedSoundControlGet(REDSOUND_CONTROL_SE)));
}
/*
 * --INFO--
 * PAL Address: 0x801cae20
 * PAL Size: 164b
 * EN Address: 0x8020cd44
 * EN Size: 164b
 * JP Address: TODO
 * JP Size: TODO
 */
void SetSePan(int seId, int pan, int frameCount)
{
	RedTrackDATA* track;
	pan <<= REDSOUND_FIXED_SHIFT;
	pan |= REDSOUND_FIXED_HALF;

	if (frameCount < 1) {
		frameCount = 1;
	}

	frameCount *= REDSOUND_SE_FADE_TICKS_PER_SECOND;
	frameCount /= REDSOUND_FRAMES_PER_SECOND;
	track = RedSoundControlGet(REDSOUND_CONTROL_SE)->m_tracks;

	do {
		if ((track->m_command != REDSOUND_TRACK_COMMAND_NONE) &&
		    ((seId < REDSOUND_SE_ID_MIN) || (track->m_seId == seId))) {
			int delta = pan - track->m_pan;
			delta /= frameCount;
			track->m_panAdd = delta;
			track->m_panDelta = frameCount;
		}
		track++;
	} while (track < RedSoundControlGetSeTrackEnd(RedSoundControlGet(REDSOUND_CONTROL_SE)));
}
/*
 * --INFO--
 * PAL Address: 0x801caec4
 * PAL Size: 164b
 * EN Address: 0x8020cde8
 * EN Size: 164b
 * JP Address: TODO
 * JP Size: TODO
 */
void SetSePitch(int seId, int pitch, int frameCount)
{
	RedTrackDATA* track;
	pitch <<= REDSOUND_FIXED_SHIFT;
	pitch |= REDSOUND_FIXED_HALF;

	if (frameCount < 1) {
		frameCount = 1;
	}

	frameCount *= REDSOUND_SE_FADE_TICKS_PER_SECOND;
	frameCount /= REDSOUND_FRAMES_PER_SECOND;
	track = RedSoundControlGet(REDSOUND_CONTROL_SE)->m_tracks;

	do {
		if ((track->m_command != REDSOUND_TRACK_COMMAND_NONE) &&
		    ((seId < REDSOUND_SE_ID_MIN) || (track->m_seId == seId))) {
			int delta = pitch - track->m_pitch;
			track->m_pitchAdd = delta / frameCount;
			track->m_pitchDelta = frameCount;
		}
		track++;
	} while (track < RedSoundControlGetSeTrackEnd(RedSoundControlGet(REDSOUND_CONTROL_SE)));
}
/*
 * --INFO--
 * PAL Address: 0x801caf68
 * PAL Size: 312b
 * EN Address: 0x8020ce8c
 * EN Size: 312b
 * JP Address: TODO
 * JP Size: TODO
 */
void SePause(int seId, int pause)
{
	RedTrackDATA** trackBasePtr;
	RedTrackDATA* track;
	RedVoiceDATA* voice;

	if (RedReportPrintIsEnabled()) {
		if (pause == REDSOUND_PAUSE_ON) {
			OSReport(sRedCommandSePauseOnFmt, sRedCommandLogPrefix, seId);
		} else {
			OSReport(sRedCommandSePauseOffFmt, sRedCommandLogPrefix, seId);
		}
		fflush(__files + 1);
	}

	trackBasePtr = &RedSoundControlGet(REDSOUND_CONTROL_SE)->m_tracks;
	track = *trackBasePtr;
	voice = RedVoiceDataGet(REDSOUND_SE_VOICE_BASE_INDEX);
	do {
		if ((track->m_seId != REDSOUND_SE_ID_NONE) && ((seId == REDSOUND_SE_ID_ALL) || (seId == track->m_seId))) {
			if (pause == REDSOUND_PAUSE_ON) {
				if (voice->m_axVoice != REDSOUND_AX_VOICE_NONE) {
					voice->m_targetPitch = 0;
					voice->m_flags |= REDSOUND_VOICE_FLAGS_PAUSE_DIRTY;
				}
				track->m_voiceSwitch |= REDSOUND_VOICE_SWITCH_PAUSE;
				voice->m_voiceSwitch |= REDSOUND_VOICE_SWITCH_PAUSE;
			} else {
				voice->m_updateFlags |= REDSOUND_VOICE_UPDATE_ALL;
				track->m_voiceSwitch &= REDSOUND_VOICE_SWITCH_CLEAR_PAUSE_MASK;
				voice->m_voiceSwitch &= REDSOUND_VOICE_SWITCH_CLEAR_PAUSE_MASK;
			}
		}
		track++;
		voice++;
	} while (track < RedSeTrackGetEnd(*trackBasePtr));
}
/*
 * --INFO--
 * PAL Address: 0x801cb0a0
 * PAL Size: 1360b
 * EN Address: 0x8020cfc4
 * EN Size: 1360b
 * JP Address: TODO
 * JP Size: TODO
 */
static RedTrackDATA* _MusicPlayStart(RedMusicHEAD* musicHead, RedWaveHeadWD* waveHead, int musicId, int volume, int mode)
{
	if (c_RedEntry.SearchWaveBase(musicHead->m_waveNo) == 0) {
		return (RedTrackDATA*)-1;
	}

	RedMusicSkipLineSet(mode);
	RedSoundCONTROL* music;
	if (RedMusicSkipLineIsActive()) {
		music = RedSoundControlGet(REDSOUND_CONTROL_MUSIC_SKIP);
	} else {
		music = RedSoundControlGet(REDSOUND_CONTROL_MUSIC_PRIMARY);
	}

	music->m_musicId = musicId;
	music->m_flags &= REDSOUND_CONTROL_FLAG_CLEAR_STOP_ON_VOLUME_ZERO_MASK;
	music->m_updateFlags = 0;

	if (RedCrossTimeIsActive()) {
		music->m_masterVolume = 0;
		music->m_masterVolumeAdd = REDSOUND_MASTER_VOLUME_FULL_FIXED_HALF;
		music->m_masterVolumeAdd = music->m_masterVolumeAdd / RedCrossTimeGet();
		music->m_masterVolumeDelta = RedCrossTimeGet();
		RedCrossTimeClear();
	} else {
		music->m_masterVolume = REDSOUND_MASTER_VOLUME_FULL_FIXED;
		music->m_masterVolumeDelta = 0;
	}

	RedTrackDATA* track = (RedTrackDATA*)RedNew(musicHead->m_trackCount * REDSOUND_TRACK_SIZE);
	if (track == 0) {
		if (RedReportPrintIsEnabled()) {
			OSReport(sRedCommandMusicTrackCreateErrorFmt,
			         sRedCommandLogPrefix, sRedCommandLogErrorColor, sRedCommandLogReset);
			fflush(__files + 1);
			OSReport(sRedCommandMusicNeedMemoryFmt,
			         sRedCommandLogPrefix, sRedCommandLogErrorColor,
			         (int)musicHead->m_musicNo, musicHead->m_trackCount * REDSOUND_TRACK_SIZE, sRedCommandLogReset);
			fflush(__files + 1);
		}
		c_RedEntry.DisplayMMemoryInfo();
		return (RedTrackDATA*)-1;
	}

	music->m_tracks = track;

	if (musicHead->m_reverbKind != 0) {
		unsigned int reverbKind = ((int)musicHead->m_reverbKind - 1U) & REDSOUND_REVERB_MODE_INDEX_MASK;
		SetReverb(0, RedReverbModeDataGet(reverbKind)->m_kind, RedReverbModeDataGet(reverbKind)->m_params);
	}

	RedReverbDepthSetDepth(REDSOUND_REVERB_DEPTH_MUSIC, (int)musicHead->m_reverbDepth);
	if (RedReverbDepthGetDepth(REDSOUND_REVERB_DEPTH_MUSIC) != 0) {
		RedReverbDepthSetDepth(REDSOUND_REVERB_DEPTH_MUSIC,
		    (RedReverbDepthGetDepth(REDSOUND_REVERB_DEPTH_MUSIC) + 1) << REDSOUND_REVERB_DEPTH_BYTE_SHIFT);
		RedReverbDepthSetDepth(REDSOUND_REVERB_DEPTH_MUSIC,
		    (RedReverbDepthGetDepth(REDSOUND_REVERB_DEPTH_MUSIC) - 1) << REDSOUND_FIXED_SHIFT);
	}
	RedReverbDepthSetStep(REDSOUND_REVERB_DEPTH_MUSIC, 0);
	RedReverbDepthSetCount(REDSOUND_REVERB_DEPTH_MUSIC, 0);
	music->m_waveNo = musicHead->m_waveNo;

	RedMusicTrackBlock* musicTrackBlock = RedMusicGetTrackBlocks(musicHead);
	int remainingTrackCount = musicHead->m_trackCount;
	char musicTrackNo = 0;
	do {
		int musicTrackBlockSize = RedMusicTrackBlockGetSize(musicTrackBlock);
		track->m_trackNo = musicTrackNo - 1;
		track->m_waveBankData = waveHead;
		musicTrackBlock = RedMusicTrackBlockGetCommandBlock(musicTrackBlock);
		track->m_command = (unsigned char*)musicTrackBlock;
		musicTrackBlock = RedMusicTrackBlockGetNext(musicTrackBlock, musicTrackBlockSize);
		track->m_deltaTime = DeltaTimeSumup((unsigned char**)&track->m_command) + 1;
		track->m_seSepId = REDSOUND_TRACK_SESEP_ID_NONE;
		signed char* defaultKeySignatureData;
		if (RedMusicKeySignatureIsEnabled()) {
			defaultKeySignatureData = RedKeySignatureGetDefaultData();
		} else {
			defaultKeySignatureData = 0;
		}
		track->m_keySignatureData = defaultKeySignatureData;
		track->m_mixVolume = REDSOUND_VOLUME_DEFAULT;
		track->m_mixVolumeDelta = 0;
		track->m_volume = REDSOUND_VOLUME_FULL;
		track->m_expression = REDSOUND_VOLUME_DEFAULT;
		track->m_pan = REDSOUND_PAN_CENTER;
		track->m_reverbDepth = RedReverbDepthGetDepth(REDSOUND_REVERB_DEPTH_MUSIC);
		track->m_reverbDepthDelta = 0;
		track->m_panDelta = 0;
		track->m_expressionDelta = 0;
		track->m_volumeDelta = 0;
		track->m_sweepAdd = 0;
		track->m_sweepDelta = 0;
		track->m_portamentTime = 0;
		track->m_loopDepth = 0;
		track->m_keyTranspose = 0;
		track->m_pitchBendRange = REDSOUND_SE_DEFAULT_PITCH_BEND_RANGE;
		track->m_pitchBend = 0;
		track->m_pitchBendRaw = 0;
		track->m_fineTune = 0;
		track->m_shakeFunc = REDSOUND_SWING_FUNC_NONE;
		track->m_tremoloFunc = REDSOUND_SWING_FUNC_NONE;
		track->m_vibrateFunc = REDSOUND_SWING_FUNC_NONE;
		track->m_shakePan = 0;
		track->m_tremoloDelay = 0;
		track->m_vibrateDelay = 0;
		track->m_tremoloDelayDepth = 0;
		track->m_vibrateDelayDepth = 0;
		track->m_waveData = REDSOUND_WAVE_DATA_NONE;
		track->m_flags = ((musicHead->m_playFlags & REDSOUND_MUSIC_PLAY_FLAG_RELEASE_NOTES) != 0) ? REDSOUND_TRACK_FLAGS_NONE : REDSOUND_TRACK_FLAG_TENUTO;
		track->m_step2 = 0;
		track->m_step = 0;
		track->m_fuzzyAdsrDepth = 0;
		track->m_fuzzyDeltaTimeDepth = 0;
		track->m_fuzzyPanDepth = 0;
		track->m_fuzzyVolumeDepth = 0;
		track->m_fuzzyPitchDepth = 0;
		track->m_portamentPitch = REDSOUND_TRACK_PORTAMENT_PITCH_NONE;
		track->m_note.m_allocFlags = REDSOUND_NOTE_ALLOC_NONE;
		track->m_voiceSwitch = REDSOUND_VOICE_SWITCH_MUSIC_DEFAULT;
		RedTrackAdsrFillDefault(&track->m_adsr);

		remainingTrackCount--;
		musicTrackNo++;
		if (remainingTrackCount != 0) {
			track++;
		}
	} while (remainingTrackCount != 0);

	music->m_skipFrames = REDSOUND_CONTROL_INITIAL_SKIP_FRAMES;
	music->m_channelAlloc = REDSOUND_CONTROL_CHANNEL_ALLOC_NONE;
	music->m_keySignature = REDSOUND_CONTROL_KEY_SIGNATURE_NONE;
	music->m_keySignatureData = RedKeySignatureGetDefaultData();
	music->m_trackCount = musicHead->m_trackCount;
	music->m_activeTrackCount = musicHead->m_trackCount;
	music->m_volumeScale = musicHead->m_flags & REDSOUND_MUSIC_HEADER_VOLUME_SCALE_MASK;
	music->m_tickCounter = REDSOUND_CONTROL_INITIAL_TICK_COUNTER;
	music->m_tempo = REDSOUND_FIXED_ONE;
	music->m_ticksPerMeasure = REDSOUND_CONTROL_DEFAULT_TICKS_PER_MEASURE;
	music->m_tick = REDSOUND_CONTROL_INITIAL_TICK;
	music->m_measure = REDSOUND_CONTROL_INITIAL_MEASURE;
	music->m_elapsedTime = REDSOUND_CONTROL_ELAPSED_TIME_NONE;
	if (volume != 0) {
		volume = (((volume + 1) * REDSOUND_MASTER_VOLUME_SCALE) - 1) * REDSOUND_FIXED_ONE;
	}
	music->m_volume = volume;
	music->m_volumeDelta = REDSOUND_CONTROL_VOLUME_DELTA_NONE;
	music->m_updateFlags = REDSOUND_CONTROL_UPDATE_FLAGS_NONE;
	music->m_flags &= REDSOUND_CONTROL_FLAG_PAUSE;
	if ((musicHead->m_playFlags & REDSOUND_MUSIC_PLAY_FLAG_RELEASE_NOTES) != 0) {
		music->m_flags |= REDSOUND_MUSIC_PLAY_FLAG_RELEASE_NOTES;
	}

	c_RedEntry.WaveHistoryManager(REDSOUND_HISTORY_MODE_USE, music->m_waveNo);
	c_RedEntry.MusicHistoryManager(REDSOUND_HISTORY_MODE_USE, musicId);
	if (RedMusicSkipLineIsActive()) {
		OSSignalSemaphore(RedMusicSkipSemaphoreGet());
	}
	return track;
}
/*
 * --INFO--
 * PAL Address: 0x801cb5f0
 * PAL Size: 480b
 * EN Address: 0x8020d514
 * EN Size: 480b
 * JP Address: TODO
 * JP Size: TODO
 */
int MusicStop(int musicId)
{
	RedSoundCONTROL* music = RedSoundControlGet(REDSOUND_CONTROL_MUSIC_PRIMARY);

	do {
		if ((musicId == REDSOUND_MUSIC_ID_NONE) ||
		    ((music->m_musicId >= REDSOUND_MUSIC_ID_MIN) && (music->m_musicId == musicId))) {
			int stoppedMusicId = music->m_musicId;
			music->m_updateFlags = 0;
			music->m_musicId = REDSOUND_MUSIC_ID_NONE;
			if (music->m_activeTrackCount != 0) {
				RedVoiceDATA* voiceData = RedVoiceDataGetBegin();
				do {
					if ((voiceData->m_track >= music->m_tracks) &&
					    (voiceData->m_track < music->m_tracks + music->m_trackCount)) {
						voiceData->m_voiceSwitch &= REDSOUND_VOICE_SWITCH_CLEAR_SUSTAIN_PAUSE_MASK;
						voiceData->m_flags &= REDSOUND_VOICE_FLAGS_CLEAR_ACTIVE_MASK;
						voiceData->m_flags |= REDSOUND_VOICE_FLAGS_RELEASED;
						voiceData->m_stateFlags &= ~REDSOUND_VOICE_STATE_SE;
						voiceData->m_track = REDSOUND_VOICE_TRACK_NONE;
						voiceData->m_active = REDSOUND_VOICE_ACTIVE_OFF;
					}
					voiceData++;
				} while (voiceData < RedVoiceDataGetEnd());

				RedTrackDATA* track = music->m_tracks;
				do {
					if (track->m_command != REDSOUND_TRACK_COMMAND_NONE) {
						KeyOnReserveClear(RedKeyOnDataGet(), track);
						track->m_command = REDSOUND_TRACK_COMMAND_NONE;
					}
					track++;
				} while (track < music->m_tracks + music->m_trackCount);

				music->m_activeTrackCount = 0;
				music->m_trackCount = 0;
				RedDelete(music->m_tracks);
				music->m_tracks = REDSOUND_TRACK_NONE;
				c_RedEntry.WaveHistoryManager(REDSOUND_HISTORY_MODE_RELEASE, music->m_waveNo);
				c_RedEntry.MusicHistoryManager(REDSOUND_HISTORY_MODE_RELEASE, stoppedMusicId);
			}
		}
		music++;
	} while (music < RedSoundControlGetMusicPlayEnd());

	music = RedSoundControlGet(REDSOUND_CONTROL_MUSIC_PRIMARY);
	if ((music->m_musicId < REDSOUND_MUSIC_ID_MIN) &&
	    (music[REDSOUND_CONTROL_MUSIC_SECONDARY].m_musicId >= REDSOUND_MUSIC_ID_MIN)) {
		memcpy(RedSoundControlGet(REDSOUND_CONTROL_MUSIC_PRIMARY),
		       RedSoundControlGet(REDSOUND_CONTROL_MUSIC_SECONDARY), REDSOUND_CONTROL_SIZE);
		music[REDSOUND_CONTROL_MUSIC_SECONDARY].m_activeTrackCount = 0;
		music[REDSOUND_CONTROL_MUSIC_SECONDARY].m_trackCount = 0;
		music[REDSOUND_CONTROL_MUSIC_SECONDARY].m_musicId = REDSOUND_MUSIC_ID_NONE;
		music[REDSOUND_CONTROL_MUSIC_SECONDARY].m_tracks = REDSOUND_TRACK_NONE;
	}

	return musicId;
}
/*
 * --INFO--
 * PAL Address: 0x801cb7d0
 * PAL Size: 160b
 * EN Address: 0x8020d6f4
 * EN Size: 160b
 * JP Address: TODO
 * JP Size: TODO
 */
int MusicPlay(int musicId, int volume, int mode)
{
	RedMusicHEAD* musicHead;
	RedHistoryBANK* musicBank = c_RedEntry.SearchMusicBank(musicId);

	if (musicBank != 0) {
		musicHead = musicBank->m_musicHead;
		RedWaveHeadWD* waveHead = c_RedEntry.SearchWaveBase(musicHead->m_waveNo);

		if (waveHead == 0) {
			return REDSOUND_MUSIC_PLAY_FAILED;
		}

		_MusicPlayStart(musicHead, waveHead, musicId, volume, mode);
	}

	return 0;
}
/*
 * --INFO--
 * PAL Address: 0x801cb870
 * PAL Size: 204b
 * EN Address: 0x8020d794
 * EN Size: 204b
 * JP Address: TODO
 * JP Size: TODO
 */
void SetMusicVolume(int musicId, int volume, int duration, int mode)
{
	RedSoundCONTROL* music;

	if (volume != 0) {
		volume++;
		volume <<= REDSOUND_MUSIC_VOLUME_INPUT_SCALE_SHIFT;
		volume--;
		volume <<= REDSOUND_FIXED_SHIFT;
	}
	volume |= REDSOUND_FIXED_HALF;

	if (duration < 1) {
		duration = 1;
	} else {
		duration *= REDSOUND_MUSIC_FADE_TICKS_PER_SECOND;
		duration /= REDSOUND_FRAMES_PER_SECOND;
	}

	music = RedSoundControlGet(REDSOUND_CONTROL_MUSIC_PRIMARY);
	do {
		if ((musicId == REDSOUND_MUSIC_ID_NONE) || (musicId == music->m_musicId) ||
		    (music->m_musicId < REDSOUND_MUSIC_ID_MIN)) {
			if (mode == REDSOUND_MUSIC_VOLUME_MODE_FADE_OUT) {
				music->m_masterVolumeAdd = -music->m_masterVolume / duration;
				music->m_masterVolumeDelta = duration;
			} else {
				music->m_volumeAdd = (volume - music->m_volume) / duration;
				music->m_volumeDelta = duration;
			}
		}
		music++;
	} while (music < RedSoundControlGetMusicAllEnd());
}
/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 408b
 * EN Address: UNUSED
 * EN Size: 408b
 * JP Address: TODO
 */
int SeStopG(int group)
{
	RedSoundCONTROL* soundControl;
	RedTrackDATA* track;

	soundControl = RedSoundControlGet(REDSOUND_CONTROL_SE);
	soundControl->m_updateFlags = 0;
	track = soundControl->m_tracks;
	do {
		if ((track->m_command != REDSOUND_TRACK_COMMAND_NONE) &&
		    RedSeBlockIdIsSeSepData(track->m_seSepId) &&
		    (track->m_seSepId / REDSOUND_SE_MG_ID_DIVISOR == group)) {
			int trackNo;

			KeyOnReserveClear(RedKeyOnDataGet(), track);
			track->m_seId = REDSOUND_SE_ID_NONE;
			track->m_flags = REDSOUND_TRACK_FLAGS_NONE;
			track->m_command = REDSOUND_TRACK_COMMAND_NONE;
			track->m_mixVolumeMode = REDSOUND_SE_VOLUME_MODE_NORMAL;

			trackNo = track->m_trackNo;
			RedVoiceDataGet(trackNo)->m_stateFlags &= REDSOUND_VOICE_STATE_CLEAR_PLAYING_MASK;
			RedVoiceDataGet(trackNo)->m_voiceSwitch &= REDSOUND_VOICE_SWITCH_CLEAR_SE_MASK;
			RedVoiceDataGet(trackNo)->m_flags &= REDSOUND_VOICE_FLAGS_CLEAR_ACTIVE_MASK;
			RedVoiceDataGet(trackNo)->m_flags |= REDSOUND_VOICE_FLAGS_RELEASED;
			RedVoiceDataGet(trackNo)->m_track = REDSOUND_VOICE_TRACK_NONE;
			RedVoiceDataGet(trackNo)->m_active = REDSOUND_VOICE_ACTIVE_OFF;

			if (track->m_waveBankData != REDSOUND_WAVE_BANK_DATA_NONE) {
				c_RedEntry.WaveHistoryManager(REDSOUND_HISTORY_MODE_RELEASE, track->m_waveBankData->m_waveNo);
			}
			c_RedEntry.SeSepHistoryManager(REDSOUND_HISTORY_MODE_RELEASE, track->m_seSepId);
		}
		track++;
	} while (track < RedSoundControlGetSeTrackEnd(soundControl));

	return 0;
}
/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 104b
 * EN Address: UNUSED
 * EN Size: 104b
 * JP Address: TODO
 */
void SetMusicTempo(int tempo, int frameCount)
{
	tempo <<= REDSOUND_FIXED_SHIFT;
	tempo |= REDSOUND_FIXED_HALF;

	if (frameCount < 1) {
		frameCount = 1;
	} else {
		frameCount *= REDSOUND_MUSIC_FADE_TICKS_PER_SECOND;
		frameCount /= REDSOUND_FRAMES_PER_SECOND;
	}

	RedControlRamp* tempoControl = RedMusicTempoControlGet();
	tempoControl->m_step = (tempo - tempoControl->m_value) / frameCount;
	RedMusicTempoControlSetCount(frameCount);
}
/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 92b
 * EN Address: UNUSED
 * EN Size: 92b
 * JP Address: TODO
 */
void SetMusicPitch(int pitch, int frameCount)
{
	pitch <<= REDSOUND_FIXED_SHIFT;
	pitch |= REDSOUND_FIXED_HALF;

	if (frameCount < 1) {
		frameCount = 1;
	} else {
		frameCount *= REDSOUND_MUSIC_FADE_TICKS_PER_SECOND;
		frameCount /= REDSOUND_FRAMES_PER_SECOND;
	}

	RedMusicPitchControlSetStep((pitch - RedMusicPitchControlGetValue()) / frameCount);
	RedMusicPitchControlSetCount(frameCount);
}
/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 476b
 * EN Address: UNUSED
 * EN Size: 476b
 * JP Address: TODO
 */
void MusicPause(int musicId, int pause)
{
	RedSoundCONTROL* music;
	RedVoiceDATA* voice;

	if (RedReportPrintIsEnabled()) {
		if (pause == REDSOUND_PAUSE_ON) {
			OSReport(sRedCommandMusicPauseOnFmt, sRedCommandLogPrefix, musicId);
		} else {
			OSReport(sRedCommandMusicPauseOffFmt, sRedCommandLogPrefix, musicId);
		}
		fflush(__files + 1);
	}

	music = RedSoundControlGet(REDSOUND_CONTROL_MUSIC_PRIMARY);
	do {
		if ((musicId == REDSOUND_MUSIC_ID_NONE) ||
		    ((music->m_musicId >= REDSOUND_MUSIC_ID_MIN) && (music->m_musicId == musicId))) {
			if (pause == REDSOUND_PAUSE_ON) {
				if (music->m_activeTrackCount != 0) {
					voice = RedVoiceDataGetBegin();
					do {
						if ((voice->m_track >= music->m_tracks) &&
						    (voice->m_track < music->m_tracks + music->m_trackCount)) {
							if (voice->m_axVoice != REDSOUND_AX_VOICE_NONE) {
								voice->m_targetPitch = 0;
								voice->m_flags |= REDSOUND_VOICE_FLAGS_PAUSE_DIRTY;
							}
							voice->m_track->m_voiceSwitch |= REDSOUND_VOICE_SWITCH_PAUSE;
							voice->m_voiceSwitch |= REDSOUND_VOICE_SWITCH_PAUSE;
						}
						voice++;
					} while (voice < RedVoiceDataGetEnd());
				}
				music->m_flags |= REDSOUND_CONTROL_FLAG_PAUSE;
			} else {
				voice = RedVoiceDataGetBegin();
				do {
					if ((voice->m_track >= music->m_tracks) &&
					    (voice->m_track < music->m_tracks + music->m_trackCount)) {
						voice->m_updateFlags |= REDSOUND_VOICE_UPDATE_ALL;
						voice->m_track->m_voiceSwitch &= REDSOUND_VOICE_SWITCH_CLEAR_PAUSE_MASK;
						voice->m_voiceSwitch &= REDSOUND_VOICE_SWITCH_CLEAR_PAUSE_MASK;
					}
					voice++;
				} while (voice < RedVoiceDataGetEnd());
				music->m_flags &= ~REDSOUND_CONTROL_FLAG_PAUSE;
			}
		}
		music++;
	} while (music < RedSoundControlGetMusicAllEnd());
}
