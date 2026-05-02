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

RedReverbModeData t_ReverbModeData[] = {
    {0x2, {0xA, 0x578, 0x1E, 0x46, 0x64, 0x0}},
    {0x2, {0x14, 0x708, 0x1E, 0x50, 0x64, 0x0}},
    {0x2, {0x1E, 0x960, 0x1E, 0x50, 0x64, 0x0}},
    {0x2, {0x28, 0xAF0, 0x1E, 0x50, 0x64, 0x0}},
    {0x2, {0xF, 0x352, 0x32, 0x50, 0x64, 0x0}},
    {0x2, {0x1E, 0x5DC, 0x32, 0x3C, 0x64, 0x0}},
    {0x2, {0x28, 0x9C4, 0x32, 0x28, 0x64, 0x0}},
    {0x2, {0x28, 0x9C4, 0x32, 0x50, 0x64, 0x0}},
};

/*
 * --INFO--
 * PAL Address: 0x801ca038
 * PAL Size: 364b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void _EraseAttribute(int eraseTrack, int attrMask)
{
	RedTrackDATA** trackBasePtr = &((RedSoundCONTROL*)p_SoundControlBuffer)[3].m_tracks;
	RedTrackDATA* track = *trackBasePtr;

	do {
		if (((u32)track->m_command != 0) && ((int)track->m_eraseTrack <= eraseTrack) &&
		    ((((unsigned int)track->m_attrMask) & (unsigned int)attrMask) != 0)) {
			int trackNo;

			KeyOnReserveClear((RedKeyOnDATA*)p_KeyOnData, track);
			track->m_seId = 0;
			track->m_flags = 0;
			track->m_command = 0;
			track->m_mixVolumeMode = 0;

			trackNo = track->m_trackNo;
			*(unsigned char*)((int)p_VoiceData + trackNo * 0xc0 + 0x1a) &= -6;
			*(unsigned int*)((unsigned char*)p_VoiceData + trackNo * 0xc0 + 0x94) &= 0xfffffff7;
			*(unsigned int*)((unsigned char*)p_VoiceData + trackNo * 0xc0 + 0x90) &= 0xfffffffe;
			*(unsigned int*)((unsigned char*)p_VoiceData + trackNo * 0xc0 + 0x90) |= 2;
			*(unsigned int*)((unsigned char*)p_VoiceData + trackNo * 0xc0 + 0x8c) = 0;

			c_RedEntry.SeSepHistoryManager(0, track->m_seSepId);
			if ((u32)track->m_waveBankData != 0) {
				c_RedEntry.WaveHistoryManager(
				    0, reinterpret_cast<RedWaveHeadWD*>(track->m_waveBankData)->m_waveNo);
			}
		}
		track++;
	} while (track < *trackBasePtr + 0x20);
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
int _EraseTime(int eraseTrack)
{
	int minTrack = 0x100;
	RedTrackDATA** trackBasePtr = &((RedSoundCONTROL*)p_SoundControlBuffer)[3].m_tracks;
	RedTrackDATA* track = *trackBasePtr;

	do {
		if (((u32)track->m_command != 0) && (track->m_attrMask == 0) && ((int)track->m_eraseTrack < minTrack)) {
			minTrack = track->m_eraseTrack;
		}
		track++;
	} while (track < *trackBasePtr + 0x20);

	if (eraseTrack > minTrack) {
		eraseTrack = minTrack;
	}

	track = *trackBasePtr;
	int maxWait = 0;
	int sepId = 0;
	do {
		if (((u32)track->m_command != 0) && (track->m_attrMask == 0) && ((int)track->m_eraseTrack <= eraseTrack) &&
		    (track->m_playTime > maxWait)) {
			maxWait = track->m_playTime;
			sepId = track->m_seSepId;
		}
		track++;
	} while (track < *trackBasePtr + 0x20);

	track = *trackBasePtr;
	int erasedCount = 0;
	do {
		if (((u32)track->m_command != 0) && (track->m_attrMask == 0) && ((int)track->m_eraseTrack <= eraseTrack) &&
		    (track->m_playTime == maxWait)) {
			int trackNo;

			KeyOnReserveClear((RedKeyOnDATA*)p_KeyOnData, track);
			track->m_seId = 0;
			track->m_flags = 0;
			track->m_command = 0;
			track->m_mixVolumeMode = 0;

			trackNo = track->m_trackNo;
			*(unsigned char*)((int)p_VoiceData + trackNo * 0xc0 + 0x1a) &= -6;
			*(unsigned int*)((unsigned char*)p_VoiceData + trackNo * 0xc0 + 0x94) &= 0xfffffff7;
			*(unsigned int*)((unsigned char*)p_VoiceData + trackNo * 0xc0 + 0x90) &= 0xfffffffe;
			*(unsigned int*)((unsigned char*)p_VoiceData + trackNo * 0xc0 + 0x90) |= 2;
			*(unsigned int*)((unsigned char*)p_VoiceData + trackNo * 0xc0 + 0x8c) = 0;

			if ((u32)track->m_waveBankData != 0) {
				c_RedEntry.WaveHistoryManager(0, reinterpret_cast<RedWaveHeadWD*>(track->m_waveBankData)->m_waveNo);
			}
			erasedCount++;
		}
		track++;
	} while (track < *trackBasePtr + 0x20);

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
	RedTrackDATA** trackBasePtr = &((RedSoundCONTROL*)p_SoundControlBuffer)[3].m_tracks;
	RedTrackDATA* scan;
	RedTrackDATA* track;
	int remaining;

	if (attrMask != 0) {
		_EraseAttribute(eraseTrack, attrMask);
	}

	do {
		track = *trackBasePtr + 0x1f;
		scan = track;
		remaining = trackCount;
		do {
			track = scan;
			remaining--;
			if ((remaining != 0) && ((u32)track->m_command == 0) && ((track->m_note.m_allocFlags & 2) == 0)) {
				scan = track - 1;
			} else {
				if (((u32)track->m_command != 0) || ((track->m_note.m_allocFlags & 2) != 0)) {
					remaining = 1;
					scan = track;
				}
				scan = scan - 1;
			}
		} while ((remaining != 0) && (*trackBasePtr <= track));
	} while ((track < *trackBasePtr) && (_EraseTime(eraseTrack) != 0));

	if (track < *trackBasePtr) {
		track = 0;
	}

	return track;
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
	RedTrackDATA** trackBasePtr;
	RedTrackDATA* track;

	trackBasePtr = &((RedSoundCONTROL*)p_SoundControlBuffer)[3].m_tracks;
	((RedSoundCONTROL*)p_SoundControlBuffer)[3].m_updateFlags = 0;
	track = *trackBasePtr;
	do {
		if (((u32)track->m_command != 0) && ((seId == -1) || (track->m_seId == seId))) {
			int trackNo;

			KeyOnReserveClear((RedKeyOnDATA*)p_KeyOnData, track);
			track->m_seId = 0;
			track->m_flags = 0;
			track->m_command = 0;
			track->m_mixVolumeMode = 0;

			trackNo = track->m_trackNo;
			*(unsigned char*)((int)p_VoiceData + trackNo * 0xc0 + 0x1a) &= -6;
			*(unsigned int*)((unsigned char*)p_VoiceData + trackNo * 0xc0 + 0x94) &= 0xfffffff7;
			*(unsigned int*)((unsigned char*)p_VoiceData + trackNo * 0xc0 + 0x90) &= 0xfffffffe;
			*(unsigned int*)((unsigned char*)p_VoiceData + trackNo * 0xc0 + 0x90) |= 2;
			*(unsigned int*)((unsigned char*)p_VoiceData + trackNo * 0xc0) = 0;
			*(unsigned int*)((unsigned char*)p_VoiceData + trackNo * 0xc0 + 0x8c) = 0;

			if ((u32)track->m_waveBankData != 0) {
				c_RedEntry.WaveHistoryManager(0, reinterpret_cast<RedWaveHeadWD*>(track->m_waveBankData)->m_waveNo);
			}
			c_RedEntry.SeSepHistoryManager(0, track->m_seSepId);
		}
		track++;
	} while (track < *trackBasePtr + 0x20);

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
	RedTrackDATA** trackBasePtr;
	RedTrackDATA* track;

	trackBasePtr = &((RedSoundCONTROL*)p_SoundControlBuffer)[3].m_tracks;
	((RedSoundCONTROL*)p_SoundControlBuffer)[3].m_updateFlags = 0;
	track = *trackBasePtr;
	do {
		if (((u32)track->m_command != 0) && ((track->m_seSepId & 0x80000000U) == 0)) {
			int id = track->m_seSepId / 1000;
			if ((bank != id) && (sep != id) && (group != id) && (kind != id)) {
				int trackNo;

				KeyOnReserveClear((RedKeyOnDATA*)p_KeyOnData, track);
				track->m_seId = 0;
				track->m_flags = 0;
				track->m_command = 0;
				track->m_mixVolumeMode = 0;

				trackNo = track->m_trackNo;
				*(unsigned char*)((int)p_VoiceData + trackNo * 0xc0 + 0x1a) &= -6;
				*(unsigned int*)((unsigned char*)p_VoiceData + trackNo * 0xc0 + 0x94) &= 0xfffffff7;
				*(unsigned int*)((unsigned char*)p_VoiceData + trackNo * 0xc0 + 0x90) &= 0xfffffffe;
				*(unsigned int*)((unsigned char*)p_VoiceData + trackNo * 0xc0 + 0x90) |= 2;
				*(unsigned int*)((unsigned char*)p_VoiceData + trackNo * 0xc0) = 0;
				*(unsigned int*)((unsigned char*)p_VoiceData + trackNo * 0xc0 + 0x8c) = 0;

				if ((u32)track->m_waveBankData != 0) {
					c_RedEntry.WaveHistoryManager(0, reinterpret_cast<RedWaveHeadWD*>(track->m_waveBankData)->m_waveNo);
				}
				c_RedEntry.SeSepHistoryManager(0, track->m_seSepId);
			}
		}
		track++;
	} while (track < *trackBasePtr + 0x20);

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
int _SePlayStart(RedSeINFO* info, int seId, int sepId, int pan, int volume)
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

	((RedSoundCONTROL*)p_SoundControlBuffer)[3].m_updateFlags = 0;
	deltaTime = (unsigned int)info->m_waveNoHi * 0x100 + (unsigned int)info->m_waveNoLo;
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
	if ((flag & 0x80) != 0) {
		isMulti = 1;
	} else {
		isMulti = 0;
	}
	seq = info->m_sequence;
	attrMask = info->m_attrMask;
	count = info->m_flagsAndCount & 0x7f;
	current = seq + count * 2;
	do {
		remaining = count;
		if (sepId != 1000000) {
			remaining = 0;
			do {
				remaining = remaining + 1;
				if ((seq[remaining * 2 + 1] & 0x80) == 0) {
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
			track->m_waveBankData = (int)waveBase;
			track->m_command = current;
			current = current +
			          (((unsigned int)seq[1] * 0x100 + (unsigned int)*seq) & 0x7fff);
			deltaTime = (int)DeltaTimeSumup((unsigned char**)track);
			track->m_deltaTime = deltaTime + 1;
			if (m_SeSkipStep != 0) {
				track->m_deltaTime = track->m_deltaTime - m_SeSkipStep;
			}

			track->m_seSepId = sepId;
			track->m_seId = seId;
			track->m_loopStepCurrent = 0;
			if (m_SeSkipStep == 0) {
				state = 0xffffffff;
			} else {
				state = 0;
			}
			track->m_playTime = state;

			if (*(char*)track->m_command != '\0') {
				track->m_eraseTrack = info->m_eraseTrack;
				track->m_attrMask = info->m_attrMask;
				track->m_mixVolume = volume << 0xc;
				track->m_mixVolumeDelta = 0;
				track->m_mixVolumeMode = 0;
				track->m_pitchDelta = 0;
				track->m_pitch = 0;
				track->m_voiceSwitch = isMulti;
				track->m_volume = 0x7fff000;
				track->m_expression = 0x7f000;
				track->m_pan = pan << 0xc;
				track->m_reverbDepth = p_ReverbDepth[1].m_depth;
				track->m_reverbDepthDelta = 0;
				track->m_panDelta = 0;
				track->m_expressionDelta = 0;
				track->m_volumeDelta = 0;
				track->m_sweepAdd = 0;
				track->m_sweepDelta = 0;
				track->m_portamentTime = 0;
				track->m_loopDepth = 0;
				track->m_keyTranspose = 0;
				track->m_pitchBendRange = 2;
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
				track->m_voiceSwitch = 0xc00;
				memset(&track->m_adsrAR, 0xff, 0xc);
				track->m_note.m_allocFlags = 5;
				track->m_seTickCounter = 1;
				seTrack->m_track = track;
				seTrack->m_stateFlags = 5;
				seTrack->m_flags = 2;
				seTrack->m_volumeModPhase = 0;
				seTrack->m_pitchModPhase = 0;
				seTrack->m_updateFlags = 0;
			}

			remaining = remaining - 1;
			seq = seq + 2;
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
	bank = bank & 3;
	no = no & 0x1FF;

	if (p_SeBlockData[bank] != 0) {
		RedSeBlockHEAD* bankData = reinterpret_cast<RedSeBlockHEAD*>(p_SeBlockData[bank]);
		int seNo = no;

		no += bank << 9;
		no |= 0x80000000;
		if (seNo < bankData->m_seCount) {
			int dataBase = reinterpret_cast<int>(bankData->m_entries);

			if (*(int*)(dataBase + seNo * 4) != -1) {
				RedSeINFO* seInfo =
				    (RedSeINFO*)(dataBase + bankData->m_seCount * 4 +
				                 (*(unsigned int*)(dataBase + seNo * 4) & 0x7FFFFFFF));

				if ((*(unsigned int*)(dataBase + seNo * 4) & 0x80000000) != 0) {
					seInfo->m_flagsAndCount |= 0x80;
				}
				if (_SePlayStart(seInfo, seId, no, pan, volume) != 0) {
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
	int sepBase;
	RedSeINFO* sepInfo;

	sepBank = c_RedEntry.SearchSeSepBank(sepId);
	if (sepBank != 0) {
		sepBase = sepBank->m_data;
		sepInfo = reinterpret_cast<RedSeINFO*>(sepBase + 0x10);
		if ((*(unsigned int*)(sepBase + 0xc) & 0x80000000) != 0) {
			sepInfo->m_flagsAndCount |= 0x80;
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
	volume <<= 12;
	volume |= 0x800;

	if (frameCount < 1) {
		frameCount = 1;
	}

	frameCount *= 0x60;
	frameCount /= 0x3c;
	track = ((RedSoundCONTROL*)p_SoundControlBuffer)[3].m_tracks;

	do {
		if (((u32)track->m_command != 0) && ((seId < 0) || (track->m_seId == seId))) {
			int delta = volume - track->m_mixVolume;
			delta /= frameCount;
			track->m_mixVolumeAdd = delta;
			track->m_mixVolumeDelta = frameCount;
			track->m_mixVolumeMode = mode;
		}
		track++;
	} while (track < ((RedSoundCONTROL*)p_SoundControlBuffer)[3].m_tracks + 0x20);
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
	pan <<= 12;
	pan |= 0x800;

	if (frameCount < 1) {
		frameCount = 1;
	}

	frameCount *= 0x60;
	frameCount /= 0x3c;
	track = ((RedSoundCONTROL*)p_SoundControlBuffer)[3].m_tracks;

	do {
		if (((u32)track->m_command != 0) && ((seId < 0) || (track->m_seId == seId))) {
			int delta = pan - track->m_pan;
			delta /= frameCount;
			track->m_panAdd = delta;
			track->m_panDelta = frameCount;
		}
		track++;
	} while (track < ((RedSoundCONTROL*)p_SoundControlBuffer)[3].m_tracks + 0x20);
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
	pitch <<= 12;
	pitch |= 0x800;

	if (frameCount < 1) {
		frameCount = 1;
	}

	frameCount *= 0x60;
	frameCount /= 0x3c;
	track = ((RedSoundCONTROL*)p_SoundControlBuffer)[3].m_tracks;

	do {
		if (((u32)track->m_command != 0) && ((seId < 0) || (track->m_seId == seId))) {
			int delta = pitch - track->m_pitch;
			track->m_pitchAdd = delta / frameCount;
			track->m_pitchDelta = frameCount;
		}
		track++;
	} while (track < ((RedSoundCONTROL*)p_SoundControlBuffer)[3].m_tracks + 0x20);
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
		if (pause == 1) {
			OSReport(sRedCommandSePauseOnFmt, sRedCommandLogPrefix, seId);
		} else {
			OSReport(sRedCommandSePauseOffFmt, sRedCommandLogPrefix, seId);
		}
		fflush(__files + 1);
	}

	trackBasePtr = &((RedSoundCONTROL*)p_SoundControlBuffer)[3].m_tracks;
	track = *trackBasePtr;
	voice = p_VoiceData + 0x20;
	do {
		if ((track->m_seId != 0) && ((seId == -1) || (seId == track->m_seId))) {
			if (pause == 1) {
				if (voice->m_axVoice != 0) {
					voice->m_targetPitch = 0;
					voice->m_flags |= 0x18;
				}
				track->m_voiceSwitch |= 8;
				voice->m_voiceSwitch |= 8;
			} else {
				voice->m_updateFlags |= 3;
				track->m_voiceSwitch &= 0xfffffff7;
				voice->m_voiceSwitch &= 0xfffffff7;
			}
		}
		track++;
		voice++;
	} while (track < *trackBasePtr + 0x20);
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
void _MusicPlayStart(RedMusicHEAD* musicHead, RedWaveHeadWD* waveHead, int musicId, int volume, int mode)
{
	RedWaveHeadWD* waveBase = c_RedEntry.SearchWaveBase(musicHead->m_waveNo);
	if (waveBase == 0) {
		return;
	}

	int* music = (int*)p_SoundControlBuffer;
	if (mode != 0) {
		music += 0x24a;
	}

	m_MusicSkipLine = mode;
	((RedSoundCONTROL*)music)->m_musicId = musicId;
	((RedSoundCONTROL*)music)->m_flags &= 0xfffeffff;
	((RedSoundCONTROL*)music)->m_updateFlags = 0;

	if (m_CrossTime == 0) {
		((RedSoundCONTROL*)music)->m_masterVolume = 0x1ff000;
		((RedSoundCONTROL*)music)->m_masterVolumeDelta = 0;
	} else {
		((RedSoundCONTROL*)music)->m_masterVolume = 0;
		((RedSoundCONTROL*)music)->m_masterVolumeAdd = 0x1ff800;
		((RedSoundCONTROL*)music)->m_masterVolumeAdd = ((RedSoundCONTROL*)music)->m_masterVolumeAdd / m_CrossTime;
		((RedSoundCONTROL*)music)->m_masterVolumeDelta = m_CrossTime;
		m_CrossTime = 0;
	}

	int trackBase = RedNew(musicHead->m_trackCount * 0x154);
	if (trackBase == 0) {
		if (m_ReportPrint != 0) {
			OSReport(sRedCommandMusicTrackCreateErrorFmt,
			         sRedCommandLogPrefix, sRedCommandLogErrorColor, sRedCommandLogReset);
			fflush(__files + 1);
			OSReport(sRedCommandMusicNeedMemoryFmt,
			         sRedCommandLogPrefix, sRedCommandLogErrorColor,
			         (int)musicHead->m_musicNo, musicHead->m_trackCount * 0x154, sRedCommandLogReset);
			fflush(__files + 1);
		}
		c_RedEntry.DisplayMMemoryInfo();
		return;
	}

	*music = trackBase;

	if (musicHead->m_reverbKind != 0) {
		unsigned int reverbKind = ((int)musicHead->m_reverbKind - 1U) & 7;
		SetReverb(0, t_ReverbModeData[reverbKind].kind, t_ReverbModeData[reverbKind].params);
	}

	p_ReverbDepth[0].m_depth = (int)musicHead->m_reverbDepth;
	if (p_ReverbDepth[0].m_depth != 0) {
		p_ReverbDepth[0].m_depth = (p_ReverbDepth[0].m_depth + 1) << 8;
		p_ReverbDepth[0].m_depth = (p_ReverbDepth[0].m_depth - 1) << 0xc;
	}
	p_ReverbDepth[0].m_step = 0;
	p_ReverbDepth[0].m_count = 0;
	((RedSoundCONTROL*)music)->m_waveNo = musicHead->m_waveNo;

	unsigned char* current = (unsigned char*)musicHead + 0x20;
	int* track = (int*)*music;
	int count = musicHead->m_trackCount;
	char trackNo = 0;
	while (count != 0) {
		unsigned int blockSize = ((unsigned int)current[3] << 24) | ((unsigned int)current[2] << 16) |
		                         ((unsigned int)current[1] << 8) | (unsigned int)current[0];
		((RedTrackDATA*)track)->m_trackNo = trackNo - 1;
		((RedTrackDATA*)track)->m_waveBankData = (int)waveHead;
		((RedTrackDATA*)track)->m_command = current + 4;
		current = current + 4 + blockSize;
		((RedTrackDATA*)track)->m_deltaTime = DeltaTimeSumup((unsigned char**)track) + 1;
		((RedTrackDATA*)track)->m_seSepId = 0;
		((RedTrackDATA*)track)->m_keySignatureData = (m_MusicKeySignature == 0) ? 0 : t_KeySignatureData + 0xb;
		((RedTrackDATA*)track)->m_mixVolume = 0x7f000;
		((RedTrackDATA*)track)->m_mixVolumeDelta = 0;
		((RedTrackDATA*)track)->m_volume = 0x7fff000;
		((RedTrackDATA*)track)->m_expression = 0x7f000;
		((RedTrackDATA*)track)->m_pan = 0x40000;
		((RedTrackDATA*)track)->m_reverbDepth = p_ReverbDepth[0].m_depth;
		((RedTrackDATA*)track)->m_reverbDepthDelta = 0;
		((RedTrackDATA*)track)->m_panDelta = 0;
		((RedTrackDATA*)track)->m_expressionDelta = 0;
		((RedTrackDATA*)track)->m_volumeDelta = 0;
		((RedTrackDATA*)track)->m_sweepAdd = 0;
		((RedTrackDATA*)track)->m_sweepDelta = 0;
		((RedTrackDATA*)track)->m_portamentTime = 0;
		((RedTrackDATA*)track)->m_loopDepth = 0;
		((RedTrackDATA*)track)->m_keyTranspose = 0;
		((RedTrackDATA*)track)->m_pitchBendRange = 2;
		((RedTrackDATA*)track)->m_pitchBend = 0;
		((RedTrackDATA*)track)->m_pitchBendRaw = 0;
		((RedTrackDATA*)track)->m_fineTune = 0;
		((RedTrackDATA*)track)->m_shakeFunc = 0;
		((RedTrackDATA*)track)->m_tremoloFunc = 0;
		((RedTrackDATA*)track)->m_vibrateFunc = 0;
		((RedTrackDATA*)track)->m_shakePan = 0;
		((RedTrackDATA*)track)->m_tremoloDelay = 0;
		((RedTrackDATA*)track)->m_vibrateDelay = 0;
		((RedTrackDATA*)track)->m_tremoloDelayDepth = 0;
		((RedTrackDATA*)track)->m_vibrateDelayDepth = 0;
		((RedTrackDATA*)track)->m_waveData = 0;
		((RedTrackDATA*)track)->m_flags = ((musicHead->m_playFlags & 0x40000) == 0) ? 0x200000 : 0;
		((RedTrackDATA*)track)->m_step2 = 0;
		((RedTrackDATA*)track)->m_step = 0;
		((RedTrackDATA*)track)->m_fuzzyAdsrDepth = 0;
		((RedTrackDATA*)track)->m_fuzzyDeltaTimeDepth = 0;
		((RedTrackDATA*)track)->m_fuzzyPanDepth = 0;
		((RedTrackDATA*)track)->m_fuzzyVolumeDepth = 0;
		((RedTrackDATA*)track)->m_fuzzyPitchDepth = 0;
		((RedTrackDATA*)track)->m_portamentPitch = -1;
		((RedTrackDATA*)track)->m_note.m_allocFlags = 0;
		((RedTrackDATA*)track)->m_voiceSwitch = 0xc02;
		memset(&((RedTrackDATA*)track)->m_adsrAR, 0xff, 0xc);

		count--;
		trackNo++;
		if (count != 0) {
			track += 0x55;
		}
	}

	((RedSoundCONTROL*)music)->m_skipFrames = 1;
	((RedSoundCONTROL*)music)->m_channelAlloc = 0;
	((RedSoundCONTROL*)music)->m_keySignature = 0;
	((RedSoundCONTROL*)music)->m_keySignatureData = t_KeySignatureData + 0xb;
	((RedSoundCONTROL*)music)->m_trackCount = musicHead->m_trackCount;
	((RedSoundCONTROL*)music)->m_activeTrackCount = (short)musicHead->m_trackCount;
	*(unsigned char*)((char*)music + 0x492) = (unsigned char)(musicHead->m_flags & 0x7f);
	((RedSoundCONTROL*)music)->m_tickCounter = 1;
	((RedSoundCONTROL*)music)->m_tempo = 0x1000;
	((RedSoundCONTROL*)music)->m_ticksPerMeasure = 10000;
	((RedSoundCONTROL*)music)->m_tick = -1;
	((RedSoundCONTROL*)music)->m_measure = 1;
	((RedSoundCONTROL*)music)->m_elapsedTime = 0;
	if (volume != 0) {
		volume = (((volume + 1) * 4) - 1) * 0x1000;
	}
	((RedSoundCONTROL*)music)->m_volume = volume;
	((RedSoundCONTROL*)music)->m_volumeDelta = 0;
	((RedSoundCONTROL*)music)->m_updateFlags = 0;
	((RedSoundCONTROL*)music)->m_flags &= 0x10;
	if ((musicHead->m_playFlags & 0x40000) != 0) {
		((RedSoundCONTROL*)music)->m_flags |= 0x40000;
	}

	c_RedEntry.WaveHistoryManager(1, ((RedSoundCONTROL*)music)->m_waveNo);
	c_RedEntry.MusicHistoryManager(1, musicId);
	if (m_MusicSkipLine != 0) {
		OSSignalSemaphore(&m_MusicSkipSemaphore);
	}
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
int MusicStop(int seId)
{
	RedSoundCONTROL* music = p_SoundControlBuffer;

	do {
		if ((seId == -1) || ((music->m_musicId >= 0) && (music->m_musicId == seId))) {
			unsigned int musicId = music->m_musicId;
			music->m_updateFlags = 0;
			music->m_musicId = -1;
			if (music->m_activeTrackCount != 0) {
				RedVoiceDATA* seTrack = (RedVoiceDATA*)p_VoiceData;
				do {
					if ((seTrack->m_track >= music->m_tracks) &&
					    (seTrack->m_track <
					     (RedTrackDATA*)((u32)music->m_tracks + (unsigned int)music->m_trackCount * 0x154))) {
						seTrack->m_voiceSwitch &= 0xfffffff3;
						seTrack->m_flags &= 0xfffffffe;
						seTrack->m_flags |= 2;
						seTrack->m_stateFlags &= ~4;
						seTrack->m_track = 0;
						seTrack->m_active = 0;
					}
					seTrack++;
				} while (seTrack < (RedVoiceDATA*)p_VoiceData + 0x40);

				int* track = (int*)music->m_tracks;
				do {
					if ((u32)*track != 0) {
						KeyOnReserveClear((RedKeyOnDATA*)p_KeyOnData, (RedTrackDATA*)track);
						((RedTrackDATA*)track)->m_command = 0;
					}
					track += 0x55;
				} while (track < (int*)((u32)music->m_tracks + (unsigned int)music->m_trackCount * 0x154));

				music->m_activeTrackCount = 0;
				music->m_trackCount = 0;
				RedDelete(music->m_tracks);
				music->m_tracks = 0;
				c_RedEntry.WaveHistoryManager(0, music->m_waveNo);
				c_RedEntry.MusicHistoryManager(0, musicId);
			}
		}
		music++;
	} while (music < p_SoundControlBuffer + 2);

	music = p_SoundControlBuffer;
	if ((music->m_musicId < 0) && (music[1].m_musicId >= 0)) {
		memcpy((void*)p_SoundControlBuffer, (RedSoundCONTROL*)p_SoundControlBuffer + 1, 0x494);
		music[1].m_activeTrackCount = 0;
		music[1].m_trackCount = 0;
		music[1].m_musicId = -1;
		music[1].m_tracks = 0;
	}

	return seId;
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
		volume <<= 12;
	}
	volume |= 0x800;

	if (duration < 1) {
		duration = 1;
	} else {
		duration *= 200;
		duration /= 0x3c;
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
	} while (music < p_SoundControlBuffer + 3);
}
