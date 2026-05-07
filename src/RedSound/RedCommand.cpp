#include "ffcc/RedSound/RedCommand.h"
#include "ffcc/RedSound/RedEntry.h"
#include "ffcc/RedSound/RedDriver.h"
#include "ffcc/RedSound/RedGlobals.h"
#include "ffcc/RedSound/RedMemory.h"
#include "ffcc/RedSound/RedMidiCtrl.h"
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

enum RedCommandEraseTrack {
	REDSOUND_ERASE_TRACK_SENTINEL = 0x100,
	REDSOUND_SEP_DIRECT_PLAY_ID = 1000000,
	REDSOUND_TRACK_PLAY_TIME_SENTINEL = -1,
	REDSOUND_SE_DEFAULT_PITCH_BEND_RANGE = 2,
};

enum RedCommandMusicTrackBlock {
	REDSOUND_MUSIC_TRACK_BLOCK_SIZE_FIELD_SIZE = sizeof(u32),
};

RedReverbModeData t_ReverbModeData[] = {
    {REDSOUND_REVERB_KIND_HI, {0xA, 0x578, 0x1E, 0x46, 0x64, 0x0}},
    {REDSOUND_REVERB_KIND_HI, {0x14, 0x708, 0x1E, 0x50, 0x64, 0x0}},
    {REDSOUND_REVERB_KIND_HI, {0x1E, 0x960, 0x1E, 0x50, 0x64, 0x0}},
    {REDSOUND_REVERB_KIND_HI, {0x28, 0xAF0, 0x1E, 0x50, 0x64, 0x0}},
    {REDSOUND_REVERB_KIND_HI, {0xF, 0x352, 0x32, 0x50, 0x64, 0x0}},
    {REDSOUND_REVERB_KIND_HI, {0x1E, 0x5DC, 0x32, 0x3C, 0x64, 0x0}},
    {REDSOUND_REVERB_KIND_HI, {0x28, 0x9C4, 0x32, 0x28, 0x64, 0x0}},
    {REDSOUND_REVERB_KIND_HI, {0x28, 0x9C4, 0x32, 0x50, 0x64, 0x0}},
};

static void _EraseAttribute(int, int);
static int _EraseTime(int);
static int _SePlayStart(RedSeINFO*, int, int, int, int);
static RedTrackDATA* _MusicPlayStart(RedMusicHEAD*, RedWaveHeadWD*, int, int, int);

/*
 * --INFO--
 * PAL Address: 0x801ca038
 * PAL Size: 364b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void _EraseAttribute(int eraseTrack, int attrMask)
{
	RedTrackDATA** trackBasePtr = &p_SoundControlBuffer[REDSOUND_CONTROL_SE].m_tracks;
	RedTrackDATA* track = *trackBasePtr;

	do {
		if ((track->m_command != 0) && (track->m_eraseTrack <= eraseTrack) &&
		    ((((unsigned int)track->m_attrMask) & (unsigned int)attrMask) != 0)) {
			int trackNo;

			KeyOnReserveClear(p_KeyOnData, track);
			track->m_seId = 0;
			track->m_flags = 0;
			track->m_command = 0;
			track->m_mixVolumeMode = 0;

			trackNo = track->m_trackNo;
			(p_VoiceData + trackNo)->m_stateFlags &= REDSOUND_VOICE_STATE_CLEAR_PLAYING_MASK;
			(p_VoiceData + trackNo)->m_voiceSwitch &= REDSOUND_VOICE_SWITCH_CLEAR_SE_MASK;
			(p_VoiceData + trackNo)->m_flags &= REDSOUND_VOICE_FLAGS_CLEAR_ACTIVE_MASK;
			(p_VoiceData + trackNo)->m_flags |= REDSOUND_VOICE_FLAGS_RELEASED;
			(p_VoiceData + trackNo)->m_active = 0;

			c_RedEntry.SeSepHistoryManager(0, track->m_seSepId);
			if (track->m_waveBankData != 0) {
				c_RedEntry.WaveHistoryManager(
				    0, track->m_waveBankData->m_waveNo);
			}
		}
		track++;
	} while (track < *trackBasePtr + REDSOUND_SE_TRACK_COUNT);
}

/*
 * --INFO--
 * PAL Address: 0x801ca1a4
 * PAL Size: 536b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static int _EraseTime(int eraseTrack)
{
	int minTrack = REDSOUND_ERASE_TRACK_SENTINEL;
	RedTrackDATA** trackBasePtr = &p_SoundControlBuffer[REDSOUND_CONTROL_SE].m_tracks;
	RedTrackDATA* track = *trackBasePtr;

	do {
		if ((track->m_command != 0) && (track->m_attrMask == 0) && (track->m_eraseTrack < minTrack)) {
			minTrack = track->m_eraseTrack;
		}
		track++;
	} while (track < *trackBasePtr + REDSOUND_SE_TRACK_COUNT);

	if (eraseTrack > minTrack) {
		eraseTrack = minTrack;
	}

	track = *trackBasePtr;
	minTrack = 0;
	int sepId = 0;
	do {
		if ((track->m_command != 0) && (track->m_attrMask == 0) && (track->m_eraseTrack <= eraseTrack) &&
		    (track->m_playTime > minTrack)) {
			minTrack = track->m_playTime;
			sepId = track->m_seSepId;
		}
		track++;
	} while (track < *trackBasePtr + REDSOUND_SE_TRACK_COUNT);

	track = *trackBasePtr;
	int erasedCount = 0;
	do {
		if ((track->m_command != 0) && (track->m_attrMask == 0) && (track->m_eraseTrack <= eraseTrack) &&
		    (track->m_playTime == minTrack)) {
			int trackNo;

			KeyOnReserveClear(p_KeyOnData, track);
			track->m_seId = 0;
			track->m_flags = 0;
			track->m_command = 0;
			track->m_mixVolumeMode = 0;

			trackNo = track->m_trackNo;
			(p_VoiceData + trackNo)->m_stateFlags &= REDSOUND_VOICE_STATE_CLEAR_PLAYING_MASK;
			(p_VoiceData + trackNo)->m_voiceSwitch &= REDSOUND_VOICE_SWITCH_CLEAR_SE_MASK;
			(p_VoiceData + trackNo)->m_flags &= REDSOUND_VOICE_FLAGS_CLEAR_ACTIVE_MASK;
			(p_VoiceData + trackNo)->m_flags |= REDSOUND_VOICE_FLAGS_RELEASED;
			(p_VoiceData + trackNo)->m_active = 0;

			if (track->m_waveBankData != 0) {
				c_RedEntry.WaveHistoryManager(0, track->m_waveBankData->m_waveNo);
			}
			erasedCount++;
		}
		track++;
	} while (track < *trackBasePtr + REDSOUND_SE_TRACK_COUNT);

	if (erasedCount != 0) {
		c_RedEntry.SeSepHistoryManager(0, sepId);
	}

	return erasedCount;
}

/*
 * --INFO--
 * PAL Address: 0x801ca3bc
 * PAL Size: 252b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
RedTrackDATA* SearchSeEmptyTrack(int trackCount, int eraseTrack, int attrMask)
{
	RedTrackDATA** trackBasePtr = &p_SoundControlBuffer[REDSOUND_CONTROL_SE].m_tracks;
	RedTrackDATA* scan;
	RedTrackDATA* track;
	int remaining;
	int erasedCount;

	if (attrMask != 0) {
		_EraseAttribute(eraseTrack, attrMask);
	}
	erasedCount = 0;

	for (;;) {
		scan = *trackBasePtr + REDSOUND_SE_TRACK_LAST_INDEX;
		do {
			track = scan;
			remaining = trackCount - 1;
			while (remaining != 0) {
				if ((track->m_command != 0) ||
				    ((track->m_note.m_allocFlags & REDSOUND_NOTE_ALLOC_STREAM) != 0)) {
					break;
				}
				track--;
				remaining--;
			}
			if ((track->m_command != 0) || ((track->m_note.m_allocFlags & REDSOUND_NOTE_ALLOC_STREAM) != 0)) {
				scan = track;
				remaining = 1;
			}
			scan--;
		} while ((remaining != 0) && (track >= *trackBasePtr));

		if (track >= *trackBasePtr) {
			break;
		}
		erasedCount = _EraseTime(eraseTrack);
		if (erasedCount == 0) {
			break;
		}
	}

	if (track >= *trackBasePtr) {
		return track;
	}

	return 0;
}

/*
 * --INFO--
 * PAL Address: 0x801ca4b8
 * PAL Size: 384b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int SeStopID(int seId)
{
	RedSoundCONTROL* soundControl;
	RedTrackDATA* track;

	soundControl = &p_SoundControlBuffer[REDSOUND_CONTROL_SE];
	soundControl->m_updateFlags = 0;
	track = soundControl->m_tracks;
	do {
		if ((track->m_command != 0) && ((seId == -1) || (track->m_seId == seId))) {
			int trackNo;

			KeyOnReserveClear(p_KeyOnData, track);
			track->m_seId = 0;
			track->m_flags = 0;
			track->m_command = 0;
			track->m_mixVolumeMode = 0;

			trackNo = track->m_trackNo;
			(p_VoiceData + trackNo)->m_stateFlags &= REDSOUND_VOICE_STATE_CLEAR_PLAYING_MASK;
			(p_VoiceData + trackNo)->m_voiceSwitch &= REDSOUND_VOICE_SWITCH_CLEAR_SE_MASK;
			(p_VoiceData + trackNo)->m_flags &= REDSOUND_VOICE_FLAGS_CLEAR_ACTIVE_MASK;
			(p_VoiceData + trackNo)->m_flags |= REDSOUND_VOICE_FLAGS_RELEASED;
			(p_VoiceData + trackNo)->m_track = 0;
			(p_VoiceData + trackNo)->m_active = 0;

			if (track->m_waveBankData != 0) {
				c_RedEntry.WaveHistoryManager(0, track->m_waveBankData->m_waveNo);
			}
			c_RedEntry.SeSepHistoryManager(0, track->m_seSepId);
		}
		track++;
	} while (track < soundControl->m_tracks + REDSOUND_SE_TRACK_COUNT);

	return 0;
}

/*
 * --INFO--
 * PAL Address: 0x801ca638
 * PAL Size: 464b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int SeStopMG(int bank, int sep, int group, int kind)
{
	RedSoundCONTROL* soundControl;
	RedTrackDATA* track;

	soundControl = &p_SoundControlBuffer[REDSOUND_CONTROL_SE];
	soundControl->m_updateFlags = 0;
	track = soundControl->m_tracks;
	do {
		if ((track->m_command != 0) && ((track->m_seSepId & REDSOUND_SE_BLOCK_DATA_FLAG) == 0)) {
			int id = track->m_seSepId / 1000;
			if ((bank != id) && (sep != id) && (group != id) && (kind != id)) {
				int trackNo;

				KeyOnReserveClear(p_KeyOnData, track);
				track->m_seId = 0;
				track->m_flags = 0;
				track->m_command = 0;
				track->m_mixVolumeMode = 0;

				trackNo = track->m_trackNo;
				(p_VoiceData + trackNo)->m_stateFlags &= REDSOUND_VOICE_STATE_CLEAR_PLAYING_MASK;
				(p_VoiceData + trackNo)->m_voiceSwitch &= REDSOUND_VOICE_SWITCH_CLEAR_SE_MASK;
				(p_VoiceData + trackNo)->m_flags &= REDSOUND_VOICE_FLAGS_CLEAR_ACTIVE_MASK;
				(p_VoiceData + trackNo)->m_flags |= REDSOUND_VOICE_FLAGS_RELEASED;
				(p_VoiceData + trackNo)->m_track = 0;
				(p_VoiceData + trackNo)->m_active = 0;

				if (track->m_waveBankData != 0) {
					c_RedEntry.WaveHistoryManager(0, track->m_waveBankData->m_waveNo);
				}
				c_RedEntry.SeSepHistoryManager(0, track->m_seSepId);
			}
		}
		track++;
	} while (track < soundControl->m_tracks + REDSOUND_SE_TRACK_COUNT);

	return 0;
}

/*
 * --INFO--
 * PAL Address: 0x801ca808
 * PAL Size: 936b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static int _SePlayStart(RedSeINFO* info, int seId, int sepId, int pan, int volume)
{
	unsigned char flag;
	RedWaveHeadWD* waveBase;
	RedTrackDATA* track;
	unsigned int state;
	unsigned char attrMask;
	unsigned char* seq;
	int deltaTime;
	unsigned int count;
	unsigned char* current;
	unsigned int remaining;
	RedVoiceDATA* seTrack;
	int isMulti;

	p_SoundControlBuffer[REDSOUND_CONTROL_SE].m_updateFlags = 0;
	deltaTime = (unsigned int)info->m_waveNoHi * REDSOUND_SE_INFO_U16_HIGH_SCALE +
	            (unsigned int)info->m_waveNoLo;
	waveBase = c_RedEntry.SearchWaveBase(deltaTime);
	if (waveBase != 0) {
		c_RedEntry.WaveHistoryManager(1, waveBase->m_waveNo);
	} else {
		if (m_ReportPrint != 0) {
			OSReport(sRedCommandWaveNotEntryFmt, sRedCommandLogPrefix, sRedCommandLogWarnColor,
			         deltaTime, sRedCommandLogReset);
			fflush(__files + 1);
		}
	}

	flag = info->m_flagsAndCount;
	if ((flag & REDSOUND_SE_INFO_MULTI_FLAG) != 0) {
		isMulti = 1;
	} else {
		isMulti = 0;
	}
	seq = info->m_sequence;
	attrMask = info->m_attrMask;
	count = info->m_flagsAndCount & REDSOUND_SE_INFO_COUNT_MASK;
	current = seq + count * REDSOUND_SE_INFO_SEQUENCE_ENTRY_SIZE;
	do {
		remaining = count;
		if (sepId != REDSOUND_SEP_DIRECT_PLAY_ID) {
			remaining = 0;
			do {
				remaining = remaining + 1;
				if ((seq[remaining * REDSOUND_SE_INFO_SEQUENCE_ENTRY_SIZE + 1] & REDSOUND_SE_INFO_SEQUENCE_CONTINUE_FLAG) == 0) {
					break;
				}
			} while ((int)remaining < (int)count);
		}

		track = SearchSeEmptyTrack((int)remaining, info->m_eraseTrack, attrMask);
		attrMask = 0;
		if (track == 0) {
			break;
		}

		seTrack = p_VoiceData + track->m_trackNo;
		while (true) {
			track->m_waveBankData = waveBase;
			track->m_command = current;
			current = current +
			          (((unsigned int)seq[1] * REDSOUND_SE_INFO_U16_HIGH_SCALE + (unsigned int)*seq) &
			           REDSOUND_SE_INFO_SEQUENCE_OFFSET_MASK);
			deltaTime = (int)DeltaTimeSumup((unsigned char**)track);
			track->m_deltaTime = deltaTime + 1;
			if (m_SeSkipStep != 0) {
				track->m_deltaTime = track->m_deltaTime - m_SeSkipStep;
			}

			track->m_seSepId = sepId;
			track->m_seId = seId;
			track->m_loopStepCurrent = 0;
			if (m_SeSkipStep != 0) {
				state = 0;
			} else {
				state = REDSOUND_TRACK_PLAY_TIME_SENTINEL;
			}
			track->m_playTime = state;

			if (*track->m_command != '\0') {
				track->m_eraseTrack = info->m_eraseTrack;
				track->m_attrMask = info->m_attrMask;
				track->m_mixVolume = volume << REDSOUND_FIXED_SHIFT;
				track->m_mixVolumeDelta = 0;
				track->m_mixVolumeMode = 0;
				track->m_pitchDelta = 0;
				track->m_pitch = 0;
				track->m_voiceSwitch = isMulti;
				track->m_volume = REDSOUND_VOLUME_FULL;
				track->m_expression = REDSOUND_VOLUME_DEFAULT;
				track->m_pan = pan << REDSOUND_FIXED_SHIFT;
				track->m_reverbDepth = p_ReverbDepth[REDSOUND_REVERB_DEPTH_SE].m_depth;
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
				track->m_shakeFunc = 0;
				track->m_tremoloFunc = 0;
				track->m_vibrateFunc = 0;
				track->m_shakePan = 0;
				track->m_tremoloDelay = 0;
				track->m_vibrateDelay = 0;
				track->m_tremoloDelayDepth = 0;
				track->m_vibrateDelayDepth = 0;
				track->m_waveData = 0;
				track->m_flags = 0;
				track->m_step2 = 0;
				track->m_step = 0;
				track->m_fuzzyAdsrDepth = 0;
				track->m_fuzzyDeltaTimeDepth = 0;
				track->m_fuzzyPanDepth = 0;
				track->m_fuzzyVolumeDepth = 0;
				track->m_fuzzyPitchDepth = 0;
				track->m_portamentPitch = -1;
				track->m_voiceSwitch = REDSOUND_VOICE_SWITCH_DRY_STEREO;
				memset(&track->m_adsrAR, REDSOUND_TRACK_ADSR_DEFAULT_BYTE, REDSOUND_TRACK_ADSR_SIZE);
				track->m_note.m_allocFlags = REDSOUND_NOTE_ALLOC_DIRECT_MASK;
				track->m_seTickCounter = 1;
				seTrack->m_track = track;
				seTrack->m_stateFlags = REDSOUND_VOICE_STATE_PLAYING | REDSOUND_VOICE_STATE_SE;
				seTrack->m_flags = REDSOUND_VOICE_FLAGS_RELEASED;
				seTrack->m_volumeModPhase = 0;
				seTrack->m_pitchModPhase = 0;
				seTrack->m_updateFlags = 0;
			}

			remaining = remaining - 1;
			seq = seq + REDSOUND_SE_INFO_SEQUENCE_ENTRY_SIZE;
			count = count - 1;
			if (remaining == 0) {
				break;
			}
			track++;
			seTrack++;
		}

		if (count == 0) {
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
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int SeBlockPlay(int seId, int bank, int no, int pan, int volume)
{
	bank = bank & REDSOUND_SE_BLOCK_BANK_MASK;
	no = no & REDSOUND_SE_BLOCK_SEQUENCE_MASK;

	if (p_SeBlockData[bank] != 0) {
		RedSeBlockHEAD* bankData = reinterpret_cast<RedSeBlockHEAD*>(p_SeBlockData[bank]);
		int seNo = no;

		no += bank << REDSOUND_SE_BLOCK_BANK_SHIFT;
		no |= REDSOUND_SE_BLOCK_DATA_FLAG;
		if (seNo < bankData->m_seCount) {
			int* entries = bankData->m_entries;

			if (entries[seNo] != REDSOUND_SE_BLOCK_ENTRY_EMPTY) {
				RedSeINFO* seInfo = reinterpret_cast<RedSeINFO*>(
				    reinterpret_cast<unsigned char*>(entries + bankData->m_seCount) +
				    ((unsigned int)entries[seNo] & REDSOUND_SE_BLOCK_ENTRY_MASK));
				RedSeINFO* playInfo = seInfo;

				if (((unsigned int)entries[seNo] & REDSOUND_SE_BLOCK_DATA_FLAG) != 0) {
					playInfo->m_flagsAndCount |= REDSOUND_SE_INFO_MULTI_FLAG;
				}
				if (_SePlayStart(playInfo, seId, no, pan, volume) != 0) {
					return seNo;
				}
			}
		}
	}

	return -1;
}

/*
 * --INFO--
 * PAL Address: 0x801cacb8
 * PAL Size: 192b
 * EN Address: TODO
 * EN Size: TODO
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
		sepHead = reinterpret_cast<RedSeSepHEAD*>(sepBank->m_data);
		sepInfo = reinterpret_cast<RedSeINFO*>(&sepHead->m_seInfoFlags);
		if ((sepHead->m_sizeAndFlags & REDSOUND_SESEP_FLAGS_MASK) != 0) {
			sepInfo->m_flagsAndCount |= REDSOUND_SE_INFO_MULTI_FLAG;
		}
		if (_SePlayStart(sepInfo, seId, sepId, pan, volume) != 0) {
			c_RedEntry.SeSepHistoryManager(1, sepId);
			return sepId;
		}
	}
	return -1;
}

/*
 * --INFO--
 * PAL Address: 0x801cad78
 * PAL Size: 168b
 * EN Address: TODO
 * EN Size: TODO
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
	track = p_SoundControlBuffer[REDSOUND_CONTROL_SE].m_tracks;

	do {
		if ((track->m_command != 0) && ((seId < 0) || (track->m_seId == seId))) {
			int delta = volume - track->m_mixVolume;
			delta /= frameCount;
			track->m_mixVolumeAdd = delta;
			track->m_mixVolumeDelta = frameCount;
			track->m_mixVolumeMode = mode;
		}
		track++;
	} while (track < p_SoundControlBuffer[REDSOUND_CONTROL_SE].m_tracks + REDSOUND_SE_TRACK_COUNT);
}

/*
 * --INFO--
 * PAL Address: 0x801cae20
 * PAL Size: 164b
 * EN Address: TODO
 * EN Size: TODO
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
	track = p_SoundControlBuffer[REDSOUND_CONTROL_SE].m_tracks;

	do {
		if ((track->m_command != 0) && ((seId < 0) || (track->m_seId == seId))) {
			int delta = pan - track->m_pan;
			delta /= frameCount;
			track->m_panAdd = delta;
			track->m_panDelta = frameCount;
		}
		track++;
	} while (track < p_SoundControlBuffer[REDSOUND_CONTROL_SE].m_tracks + REDSOUND_SE_TRACK_COUNT);
}

/*
 * --INFO--
 * PAL Address: 0x801caec4
 * PAL Size: 164b
 * EN Address: TODO
 * EN Size: TODO
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
	track = p_SoundControlBuffer[REDSOUND_CONTROL_SE].m_tracks;

	do {
		if ((track->m_command != 0) && ((seId < 0) || (track->m_seId == seId))) {
			int delta = pitch - track->m_pitch;
			track->m_pitchAdd = delta / frameCount;
			track->m_pitchDelta = frameCount;
		}
		track++;
	} while (track < p_SoundControlBuffer[REDSOUND_CONTROL_SE].m_tracks + REDSOUND_SE_TRACK_COUNT);
}

/*
 * --INFO--
 * PAL Address: 0x801caf68
 * PAL Size: 312b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void SePause(int seId, int pause)
{
	RedTrackDATA** trackBasePtr;
	RedTrackDATA* track;
	RedVoiceDATA* voice;

	if (m_ReportPrint != 0) {
		if (pause == REDSOUND_PAUSE_ON) {
			OSReport(sRedCommandSePauseOnFmt, sRedCommandLogPrefix, seId);
		} else {
			OSReport(sRedCommandSePauseOffFmt, sRedCommandLogPrefix, seId);
		}
		fflush(__files + 1);
	}

	trackBasePtr = &p_SoundControlBuffer[REDSOUND_CONTROL_SE].m_tracks;
	track = *trackBasePtr;
	voice = p_VoiceData + REDSOUND_SE_VOICE_BASE_INDEX;
	do {
		if ((track->m_seId != 0) && ((seId == -1) || (seId == track->m_seId))) {
			if (pause == REDSOUND_PAUSE_ON) {
				if (voice->m_axVoice != 0) {
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
	} while (track < *trackBasePtr + REDSOUND_SE_TRACK_COUNT);
}

/*
 * --INFO--
 * PAL Address: 0x801cb0a0
 * PAL Size: 1360b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static RedTrackDATA* _MusicPlayStart(RedMusicHEAD* musicHead, RedWaveHeadWD* waveHead, int musicId, int volume, int mode)
{
	if (c_RedEntry.SearchWaveBase(musicHead->m_waveNo) == 0) {
		return (RedTrackDATA*)-1;
	}

	m_MusicSkipLine = mode;
	RedSoundCONTROL* music = p_SoundControlBuffer;
	if (m_MusicSkipLine != 0) {
		music += REDSOUND_CONTROL_MUSIC_SKIP;
	}

	music->m_musicId = musicId;
	music->m_flags &= REDSOUND_CONTROL_FLAG_CLEAR_STOP_ON_VOLUME_ZERO_MASK;
	music->m_updateFlags = 0;

	if (m_CrossTime != 0) {
		music->m_masterVolume = 0;
		music->m_masterVolumeAdd = REDSOUND_MASTER_VOLUME_FULL_FIXED_HALF;
		music->m_masterVolumeAdd = music->m_masterVolumeAdd / m_CrossTime;
		music->m_masterVolumeDelta = m_CrossTime;
		m_CrossTime = 0;
	} else {
		music->m_masterVolume = REDSOUND_MASTER_VOLUME_FULL_FIXED;
		music->m_masterVolumeDelta = 0;
	}

	RedTrackDATA* trackBase = (RedTrackDATA*)RedNew(musicHead->m_trackCount * REDSOUND_TRACK_SIZE);
	if (trackBase == 0) {
		if (m_ReportPrint != 0) {
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

	music->m_tracks = trackBase;

	if (musicHead->m_reverbKind != 0) {
		unsigned int reverbKind = ((int)musicHead->m_reverbKind - 1U) & 7;
		SetReverb(0, t_ReverbModeData[reverbKind].m_kind, t_ReverbModeData[reverbKind].m_params);
	}

	p_ReverbDepth[REDSOUND_REVERB_DEPTH_MUSIC].m_depth = (int)musicHead->m_reverbDepth;
	if (p_ReverbDepth[REDSOUND_REVERB_DEPTH_MUSIC].m_depth != 0) {
		p_ReverbDepth[REDSOUND_REVERB_DEPTH_MUSIC].m_depth = (p_ReverbDepth[REDSOUND_REVERB_DEPTH_MUSIC].m_depth + 1) << 8;
		p_ReverbDepth[REDSOUND_REVERB_DEPTH_MUSIC].m_depth = (p_ReverbDepth[REDSOUND_REVERB_DEPTH_MUSIC].m_depth - 1) << REDSOUND_FIXED_SHIFT;
	}
	p_ReverbDepth[REDSOUND_REVERB_DEPTH_MUSIC].m_step = 0;
	p_ReverbDepth[REDSOUND_REVERB_DEPTH_MUSIC].m_count = 0;
	music->m_waveNo = musicHead->m_waveNo;

	unsigned char* current = (unsigned char*)musicHead + REDSOUND_MUSIC_HEADER_SIZE;
	RedTrackDATA* track = music->m_tracks;
	int count = musicHead->m_trackCount;
	char trackNo = 0;
	while (count != 0) {
		unsigned int blockSize = ((unsigned int)current[3] << 24) | ((unsigned int)current[2] << 16) |
		                         ((unsigned int)current[1] << 8) | (unsigned int)current[0];
		track->m_trackNo = trackNo - 1;
		track->m_waveBankData = waveHead;
		track->m_command = current + REDSOUND_MUSIC_TRACK_BLOCK_SIZE_FIELD_SIZE;
		current = current + REDSOUND_MUSIC_TRACK_BLOCK_SIZE_FIELD_SIZE + blockSize;
		track->m_deltaTime = DeltaTimeSumup((unsigned char**)track) + 1;
		track->m_seSepId = 0;
		track->m_keySignatureData =
		    (m_MusicKeySignature == 0) ? 0 : t_KeySignatureData + REDSOUND_KEY_SIGNATURE_DEFAULT_OFFSET;
		track->m_mixVolume = REDSOUND_VOLUME_DEFAULT;
		track->m_mixVolumeDelta = 0;
		track->m_volume = REDSOUND_VOLUME_FULL;
		track->m_expression = REDSOUND_VOLUME_DEFAULT;
		track->m_pan = REDSOUND_PAN_CENTER;
		track->m_reverbDepth = p_ReverbDepth[REDSOUND_REVERB_DEPTH_MUSIC].m_depth;
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
		track->m_shakeFunc = 0;
		track->m_tremoloFunc = 0;
		track->m_vibrateFunc = 0;
		track->m_shakePan = 0;
		track->m_tremoloDelay = 0;
		track->m_vibrateDelay = 0;
		track->m_tremoloDelayDepth = 0;
		track->m_vibrateDelayDepth = 0;
		track->m_waveData = 0;
		track->m_flags = ((musicHead->m_playFlags & REDSOUND_MUSIC_PLAY_FLAG_RELEASE_NOTES) == 0) ? REDSOUND_TRACK_FLAG_TENUTO : 0;
		track->m_step2 = 0;
		track->m_step = 0;
		track->m_fuzzyAdsrDepth = 0;
		track->m_fuzzyDeltaTimeDepth = 0;
		track->m_fuzzyPanDepth = 0;
		track->m_fuzzyVolumeDepth = 0;
		track->m_fuzzyPitchDepth = 0;
		track->m_portamentPitch = -1;
		track->m_note.m_allocFlags = 0;
		track->m_voiceSwitch = REDSOUND_VOICE_SWITCH_DRY_STEREO | REDSOUND_VOICE_SWITCH_REVERB_AUX_A;
		memset(&track->m_adsrAR, REDSOUND_TRACK_ADSR_DEFAULT_BYTE, REDSOUND_TRACK_ADSR_SIZE);

		count--;
		trackNo++;
		if (count != 0) {
			track++;
		}
	}

	music->m_skipFrames = 1;
	music->m_channelAlloc = 0;
	music->m_keySignature = 0;
	music->m_keySignatureData = t_KeySignatureData + REDSOUND_KEY_SIGNATURE_DEFAULT_OFFSET;
	music->m_trackCount = musicHead->m_trackCount;
	music->m_activeTrackCount = (short)musicHead->m_trackCount;
	music->m_volumeScale = (unsigned char)(musicHead->m_flags & REDSOUND_MUSIC_HEADER_VOLUME_SCALE_MASK);
	music->m_tickCounter = 1;
	music->m_tempo = REDSOUND_FIXED_ONE;
	music->m_ticksPerMeasure = 10000;
	music->m_tick = -1;
	music->m_measure = 1;
	music->m_elapsedTime = 0;
	if (volume != 0) {
		volume = (((volume + 1) * REDSOUND_MASTER_VOLUME_SCALE) - 1) * REDSOUND_FIXED_ONE;
	}
	music->m_volume = volume;
	music->m_volumeDelta = 0;
	music->m_updateFlags = 0;
	music->m_flags &= REDSOUND_CONTROL_FLAG_PAUSE;
	if ((musicHead->m_playFlags & REDSOUND_MUSIC_PLAY_FLAG_RELEASE_NOTES) != 0) {
		music->m_flags |= REDSOUND_MUSIC_PLAY_FLAG_RELEASE_NOTES;
	}

	c_RedEntry.WaveHistoryManager(1, music->m_waveNo);
	c_RedEntry.MusicHistoryManager(1, musicId);
	if (m_MusicSkipLine != 0) {
		OSSignalSemaphore(&m_MusicSkipSemaphore);
	}
	return track;
}

/*
 * --INFO--
 * PAL Address: 0x801cb5f0
 * PAL Size: 480b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int MusicStop(int musicId)
{
	RedSoundCONTROL* music = p_SoundControlBuffer;

	do {
		if ((musicId == -1) || ((music->m_musicId >= 0) && (music->m_musicId == musicId))) {
			unsigned int stoppedMusicId = music->m_musicId;
			music->m_updateFlags = 0;
			music->m_musicId = -1;
			if (music->m_activeTrackCount != 0) {
				RedVoiceDATA* seTrack = p_VoiceData;
				do {
					if ((seTrack->m_track >= music->m_tracks) &&
					    (seTrack->m_track < music->m_tracks + music->m_trackCount)) {
						seTrack->m_voiceSwitch &= REDSOUND_VOICE_SWITCH_CLEAR_SUSTAIN_PAUSE_MASK;
						seTrack->m_flags &= REDSOUND_VOICE_FLAGS_CLEAR_ACTIVE_MASK;
						seTrack->m_flags |= REDSOUND_VOICE_FLAGS_RELEASED;
						seTrack->m_stateFlags &= ~REDSOUND_VOICE_STATE_SE;
						seTrack->m_track = 0;
						seTrack->m_active = 0;
					}
					seTrack++;
				} while (seTrack < p_VoiceData + REDSOUND_VOICE_COUNT);

				RedTrackDATA* track = music->m_tracks;
				do {
					if (track->m_command != 0) {
						KeyOnReserveClear(p_KeyOnData, track);
						track->m_command = 0;
					}
					track++;
				} while (track < music->m_tracks + music->m_trackCount);

				music->m_activeTrackCount = 0;
				music->m_trackCount = 0;
				RedDelete(music->m_tracks);
				music->m_tracks = 0;
				c_RedEntry.WaveHistoryManager(0, music->m_waveNo);
				c_RedEntry.MusicHistoryManager(0, stoppedMusicId);
			}
		}
		music++;
	} while (music < p_SoundControlBuffer + REDSOUND_CONTROL_MUSIC_SKIP);

	music = p_SoundControlBuffer;
	if ((music->m_musicId < 0) && (music[REDSOUND_CONTROL_MUSIC_SECONDARY].m_musicId >= 0)) {
		memcpy(p_SoundControlBuffer, p_SoundControlBuffer + REDSOUND_CONTROL_MUSIC_SECONDARY, REDSOUND_CONTROL_SIZE);
		music[REDSOUND_CONTROL_MUSIC_SECONDARY].m_activeTrackCount = 0;
		music[REDSOUND_CONTROL_MUSIC_SECONDARY].m_trackCount = 0;
		music[REDSOUND_CONTROL_MUSIC_SECONDARY].m_musicId = -1;
		music[REDSOUND_CONTROL_MUSIC_SECONDARY].m_tracks = 0;
	}

	return musicId;
}

/*
 * --INFO--
 * PAL Address: 0x801cb7d0
 * PAL Size: 160b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int MusicPlay(int musicId, int volume, int mode)
{
	RedMusicHEAD* musicHead;
	RedHistoryBANK* musicBank = c_RedEntry.SearchMusicBank(musicId);

	if (musicBank != 0) {
		musicHead = (RedMusicHEAD*)musicBank->m_data;
		RedWaveHeadWD* waveHead = c_RedEntry.SearchWaveBase(musicHead->m_waveNo);

		if (waveHead == 0) {
			return -1;
		}

		_MusicPlayStart(musicHead, waveHead, musicId, volume, mode);
	}

	return 0;
}

/*
 * --INFO--
 * PAL Address: 0x801cb870
 * PAL Size: 204b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void SetMusicVolume(int seId, int volume, int duration, int mode)
{
	RedSoundCONTROL* music;

	if (volume != 0) {
		volume++;
		volume <<= 2;
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

	music = p_SoundControlBuffer;
	do {
		if ((seId == -1) || (seId == music->m_musicId) || (music->m_musicId < 0)) {
			if (mode == 1) {
				music->m_masterVolumeAdd = -music->m_masterVolume / duration;
				music->m_masterVolumeDelta = duration;
			} else {
				music->m_volumeAdd = (volume - music->m_volume) / duration;
				music->m_volumeDelta = duration;
			}
		}
		music++;
	} while (music < p_SoundControlBuffer + REDSOUND_CONTROL_SE);
}
