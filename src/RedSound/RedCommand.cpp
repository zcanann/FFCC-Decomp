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

int* SetReverb(int, int, int*);

int t_ReverbModeData[] = {
    0x2, 0xA, 0x578, 0x1E, 0x46, 0x64, 0x0,
    0x2, 0x14, 0x708, 0x1E, 0x50, 0x64, 0x0,
    0x2, 0x1E, 0x960, 0x1E, 0x50, 0x64, 0x0,
    0x2, 0x28, 0xAF0, 0x1E, 0x50, 0x64, 0x0,
    0x2, 0xF, 0x352, 0x32, 0x50, 0x64, 0x0,
    0x2, 0x1E, 0x5DC, 0x32, 0x3C, 0x64, 0x0,
    0x2, 0x28, 0x9C4, 0x32, 0x28, 0x64, 0x0,
    0x2, 0x28, 0x9C4, 0x32, 0x50, 0x64, 0x0,
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
	int* trackBasePtr = (int*)((char*)p_SoundControlBuffer + 0xdbc);
	int* track = (int*)*trackBasePtr;
	u8 mask = (u8)attrMask;

	do {
		if ((*track != 0) && ((int)*(unsigned char*)((char*)track + 0x14f) <= eraseTrack) &&
		    ((((unsigned int)*(unsigned char*)(track + 0x54)) & (unsigned int)mask) != 0)) {
			int trackNo;
			int seTrackOffset;

			KeyOnReserveClear((RedKeyOnDATA*)p_KeyOnData, (RedTrackDATA*)track);
			track[0x3e] = 0;
			track[0x41] = 0;
			*track = 0;
			track[0x16] = 0;

			trackNo = *(char*)((char*)track + 0x14e);
			seTrackOffset = trackNo * 0xc0;
			((unsigned char*)p_VoiceData)[seTrackOffset + 0x1a] &= (unsigned char)0xfa;
			*(unsigned int*)((unsigned char*)p_VoiceData + seTrackOffset + 0x94) &= 0xfffffff7;
			*(unsigned int*)((unsigned char*)p_VoiceData + seTrackOffset + 0x90) &= 0xfffffffe;
			*(unsigned int*)((unsigned char*)p_VoiceData + seTrackOffset + 0x90) |= 2;
			*(unsigned int*)((unsigned char*)p_VoiceData + seTrackOffset + 0x8c) = 0;

			c_RedEntry.SeSepHistoryManager(0, track[0x3d]);
			if (track[6] != 0) {
				c_RedEntry.WaveHistoryManager(0, *(short*)(track[6] + 2));
			}
		}
		track += 0x55;
	} while (track < (int*)(*trackBasePtr + 0x2a80));
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
	unsigned int minTrack = 0x100;
	int* trackBasePtr = (int*)((char*)p_SoundControlBuffer + 0xdbc);
	int* track = (int*)*trackBasePtr;

	do {
		if ((*track != 0) && (*(char*)(track + 0x54) == '\0') &&
		    ((unsigned int)*(unsigned char*)((char*)track + 0x14f) < minTrack)) {
			minTrack = *(unsigned char*)((char*)track + 0x14f);
		}
		track += 0x55;
	} while (track < (int*)(*trackBasePtr + 0x2a80));

	if ((int)minTrack < eraseTrack) {
		eraseTrack = (int)minTrack;
	}

	track = (int*)*trackBasePtr;
	int maxWait = 0;
	int sepId = 0;
	do {
		if ((*track != 0) && (*(char*)(track + 0x54) == '\0') &&
		    ((int)*(unsigned char*)((char*)track + 0x14f) <= eraseTrack) &&
		    (maxWait < track[0x43])) {
			maxWait = track[0x43];
			sepId = track[0x3d];
		}
		track += 0x55;
	} while (track < (int*)(*trackBasePtr + 0x2a80));

	track = (int*)*trackBasePtr;
	int erasedCount = 0;
	do {
		if ((*track != 0) && (*(char*)(track + 0x54) == '\0') &&
		    ((int)*(unsigned char*)((char*)track + 0x14f) <= eraseTrack) &&
		    (track[0x43] == maxWait)) {
			unsigned char trackNo;
			unsigned int* seTrack;

			KeyOnReserveClear((RedKeyOnDATA*)p_KeyOnData, (RedTrackDATA*)track);
			track[0x3e] = 0;
			track[0x41] = 0;
			*track = 0;
			track[0x16] = 0;

			trackNo = *(unsigned char*)((char*)track + 0x14e);
			((unsigned char*)p_VoiceData)[trackNo * 0xc0 + 0x1a] &=
			    (unsigned char)0xfa;
			seTrack = (unsigned int*)((unsigned char*)p_VoiceData + trackNo * 0xc0);
			seTrack[0x25] &= 0xfffffff7;
			seTrack[0x24] &= 0xfffffffe;
			seTrack[0x24] |= 2;
			seTrack[0x23] = 0;

			if (track[6] != 0) {
				c_RedEntry.WaveHistoryManager(0, *(short*)(track[6] + 2));
			}
			erasedCount++;
		}
		track += 0x55;
	} while (track < (int*)(*trackBasePtr + 0x2a80));

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
int* SearchSeEmptyTrack(int trackCount, int eraseTrack, int attrMask)
{
	int* trackBasePtr = (int*)((char*)p_SoundControlBuffer + 0xdbc);
	int* scan;
	int* track;
	int remaining;
	int* minTrack;

	if (attrMask != 0) {
		_EraseAttribute(eraseTrack, attrMask);
	}

	minTrack = (int*)*trackBasePtr;
	do {
		track = (int*)(*trackBasePtr + 0x292c);
		scan = track;
		remaining = trackCount;
		do {
			track = scan;
			remaining--;
			if ((remaining != 0) && (*track == 0) && ((((unsigned char*)track)[0x26] & 2) == 0)) {
				scan = track - 0x55;
			} else {
				if ((*track != 0) || ((((unsigned char*)track)[0x26] & 2) != 0)) {
					remaining = 1;
					scan = track;
				}
				scan = scan - 0x55;
			}
		} while ((remaining != 0) && (minTrack <= track));
	} while ((track < minTrack) && (_EraseTime(eraseTrack) != 0));

	if (track < minTrack) {
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
	int* trackBasePtr = (int*)((char*)p_SoundControlBuffer + 0xdbc);
	int* track;

	*(unsigned int*)((char*)p_SoundControlBuffer + 0x1244) = 0;
	track = (int*)*trackBasePtr;
	do {
		if ((*track != 0) && ((seId == -1) || (track[0x3e] == seId))) {
			int trackNo;
			int seTrackOffset;

			KeyOnReserveClear((RedKeyOnDATA*)p_KeyOnData, (RedTrackDATA*)track);
			track[0x3e] = 0;
			track[0x41] = 0;
			*track = 0;
			track[0x16] = 0;

			trackNo = *(char*)((char*)track + 0x14e);
			seTrackOffset = trackNo * 0xc0;
			((unsigned char*)p_VoiceData)[seTrackOffset + 0x1a] &= (unsigned char)0xfa;
			*(unsigned int*)((unsigned char*)p_VoiceData + seTrackOffset + 0x94) &= 0xfffffff7;
			*(unsigned int*)((unsigned char*)p_VoiceData + seTrackOffset + 0x90) &= 0xfffffffe;
			*(unsigned int*)((unsigned char*)p_VoiceData + seTrackOffset + 0x90) |= 2;
			*(unsigned int*)((unsigned char*)p_VoiceData + seTrackOffset) = 0;
			*(unsigned int*)((unsigned char*)p_VoiceData + seTrackOffset + 0x8c) = 0;

			if (track[6] != 0) {
				c_RedEntry.WaveHistoryManager(0, *(short*)(track[6] + 2));
			}
			c_RedEntry.SeSepHistoryManager(0, track[0x3d]);
		}
		track += 0x55;
	} while (track < (int*)(*trackBasePtr + 0x2a80));

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
	int soundBase;
	int* trackBasePtr;
	int* track;

	soundBase = (int)p_SoundControlBuffer;
	trackBasePtr = (int*)(soundBase + 0xdbc);
	*(unsigned int*)(soundBase + 0x1244) = 0;
	track = *(int**)(soundBase + 0xdbc);
	do {
		if ((*track != 0) && ((track[0x3d] & 0x80000000U) == 0)) {
			int id = track[0x3d] / 1000;
			if ((bank != id) && (sep != id) && (group != id) && (kind != id)) {
				int trackNo;
				int seTrackOffset;

				KeyOnReserveClear((RedKeyOnDATA*)p_KeyOnData, (RedTrackDATA*)track);
				track[0x3e] = 0;
				track[0x41] = 0;
				*track = 0;
				track[0x16] = 0;

				trackNo = *(char*)((char*)track + 0x14e);
				seTrackOffset = trackNo * 0xc0;
				((unsigned char*)p_VoiceData)[seTrackOffset + 0x1a] &= (unsigned char)0xfa;
				*(unsigned int*)((unsigned char*)p_VoiceData + seTrackOffset + 0x94) &= 0xfffffff7;
				*(unsigned int*)((unsigned char*)p_VoiceData + seTrackOffset + 0x90) &= 0xfffffffe;
				*(unsigned int*)((unsigned char*)p_VoiceData + seTrackOffset + 0x90) |= 2;
				*(unsigned int*)((unsigned char*)p_VoiceData + seTrackOffset) = 0;
				*(unsigned int*)((unsigned char*)p_VoiceData + seTrackOffset + 0x8c) = 0;

				if (track[6] != 0) {
					c_RedEntry.WaveHistoryManager(0, *(short*)(track[6] + 2));
				}
				c_RedEntry.SeSepHistoryManager(0, track[0x3d]);
			}
		}
		track += 0x55;
	} while (track < (int*)(*trackBasePtr + 0x2a80));

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
	int waveBase;
	int* track;
	unsigned int state;
	unsigned char attrMask;
	unsigned char* seq;
	int deltaTime;
	unsigned int count;
	unsigned char* current;
	unsigned int remaining;
	int* seTrack;

	*(unsigned int*)((char*)p_SoundControlBuffer + 0x1244) = 0;
	deltaTime = (unsigned int)((unsigned char*)info)[2] * 0x100 + (unsigned int)((unsigned char*)info)[1];
	waveBase = c_RedEntry.SearchWaveBase(deltaTime);
	if (waveBase != 0) {
		c_RedEntry.WaveHistoryManager(1, *(short*)(waveBase + 2));
	} else {
		if (m_ReportPrint != 0) {
			OSReport(sRedCommandWaveNotEntryFmt, sRedCommandLogPrefix, sRedCommandLogWarnColor,
			         deltaTime, sRedCommandLogReset);
			fflush(__files + 1);
		}
	}

	flag = ((unsigned char*)info)[0];
	seq = (unsigned char*)info + 5;
	attrMask = ((unsigned char*)info)[4];
	count = ((unsigned char*)info)[0] & 0x7f;
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

		track = SearchSeEmptyTrack((int)remaining, ((unsigned char*)info)[3], attrMask);
		attrMask = 0;
		if (track == 0) {
			SeStopID(seId);
			return 0;
		}

		seTrack = (int*)((unsigned char*)p_VoiceData + *(char*)((char*)track + 0x14e) * 0xc0);
		while (true) {
			track[6] = waveBase;
			*(unsigned char**)track = current;
			current = current +
			          (((unsigned int)seq[1] * 0x100 + (unsigned int)*seq) & 0x7fff);
			deltaTime = (int)DeltaTimeSumup((unsigned char**)track);
			track[0x42] = deltaTime + 1;
			if (m_SeSkipStep != 0) {
				track[0x42] = track[0x42] - m_SeSkipStep;
			}

			track[0x3d] = sepId;
			track[0x3e] = seId;
			*(short*)(track + 0x51) = 0;
			if (m_SeSkipStep == 0) {
				state = 0xffffffff;
			} else {
				state = 0;
			}
			track[0x43] = state;

			if (*(char*)*track != '\0') {
				*(unsigned char*)((char*)track + 0x14f) = ((unsigned char*)info)[3];
				*(unsigned char*)(track + 0x54) = ((unsigned char*)info)[4];
				track[0x13] = volume << 0xc;
				track[0x15] = 0;
				track[0x16] = 0;
				track[0x19] = 0;
				track[0x17] = 0;
				track[0x40] = (unsigned int)((flag & 0x80) != 0);
				track[10] = 0x7fff000;
				track[0xd] = 0x7f000;
				track[0x10] = pan << 0xc;
				track[0x1a] = *(int*)((char*)p_ReverbDepth + 0xc);
				track[0x1c] = 0;
				track[0x12] = 0;
				track[0xf] = 0;
				track[0xc] = 0;
				track[0x45] = 0;
				track[0x44] = 0;
				track[0x46] = 0;
				*(short*)(track + 0x4f) = 0;
				*(short*)((char*)track + 0x142) = 0;
				*(unsigned char*)((char*)track + 0x14b) = 2;
				*(short*)((char*)track + 0x13e) = 0;
				*(short*)(track + 0x50) = 0;
				*(unsigned char*)(track + 0x52) = 0;
				track[0x2d] = 0;
				track[0x25] = 0;
				track[0x1d] = 0;
				track[0x33] = 0;
				*(short*)(track + 0x2c) = 0;
				*(short*)(track + 0x24) = 0;
				*(short*)((char*)track + 0xb2) = 0;
				*(short*)((char*)track + 0x92) = 0;
				track[7] = 0;
				track[0x41] = 0;
				*(short*)((char*)track + 0x13a) = 0;
				*(short*)(track + 0x4e) = 0;
				track[0x3c] = 0;
				track[0x3b] = 0;
				track[0x3a] = 0;
				track[0x39] = 0;
				track[0x38] = 0;
				track[0x48] = 0xffffffff;
				track[0x3f] = 0xc00;
				memset(track + 0x35, 0xff, 0xc);
				*(unsigned char*)((char*)track + 0x26) = 5;
				*(short*)((char*)track + 0x146) = 1;
				*seTrack = (int)track;
				*(unsigned char*)((char*)seTrack + 0x1a) = 5;
				seTrack[0x24] = 2;
				seTrack[0xc] = 0;
				seTrack[8] = 0;
				seTrack[0x2e] = 0;
			}

			remaining = remaining - 1;
			seq = seq + 2;
			count = count - 1;
			if (remaining == 0) {
				break;
			}
			track = track + 0x55;
			seTrack = seTrack + 0x30;
		}

		if (count == 0) {
			return seId;
		}
	} while (true);
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
		int bankData = (int)p_SeBlockData[bank];
		int seNo = no;
		int playNo = no + (bank << 9);

		playNo |= 0x80000000;
		if (seNo < *(short*)(bankData + 10)) {
			int dataBase = bankData + 0x10;
			int offset = *(int*)(dataBase + seNo * 4);

			if (offset != -1) {
				RedSeINFO* seInfo =
				    (RedSeINFO*)(dataBase + *(short*)(bankData + 10) * 4 + ((unsigned int)offset & 0x7FFFFFFF));

				if (((unsigned int)offset & 0x80000000) != 0) {
					*(unsigned char*)seInfo |= 0x80;
				}
				if (_SePlayStart(seInfo, seId, playNo, pan, volume) != 0) {
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
	int* sepBank;
	unsigned char* sepInfo;

	sepBank = c_RedEntry.SearchSeSepBank(sepId);
	if (sepBank != 0) {
		sepInfo = (unsigned char*)(sepBank[2] + 0x10);
		if ((*(unsigned int*)(sepBank[2] + 0xc) & 0x80000000) != 0) {
			*sepInfo |= 0x80;
		}
		if (_SePlayStart((RedSeINFO*)sepInfo, seId, sepId, pan, volume) != 0) {
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
	int* track;
	volume <<= 12;
	volume |= 0x800;

	if (frameCount < 1) {
		frameCount = 1;
	}

	frameCount *= 0x60;
	frameCount /= 0x3c;
	track = *(int**)((char*)p_SoundControlBuffer + 0xdbc);

	do {
		if (((u32)*track != 0) && ((seId < 0) || (track[0x3e] == seId))) {
			int delta = volume - track[0x13];
			delta /= frameCount;
			track[0x14] = delta;
			track[0x15] = frameCount;
			track[0x16] = mode;
		}
		track += 0x55;
	} while (track < (int*)(*(int*)((char*)p_SoundControlBuffer + 0xdbc) + 0x2a80));
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
	int* track;
	pan <<= 12;
	pan |= 0x800;

	if (frameCount < 1) {
		frameCount = 1;
	}

	frameCount *= 0x60;
	frameCount /= 0x3c;
	track = *(int**)((char*)p_SoundControlBuffer + 0xdbc);

	do {
		if (((u32)*track != 0) && ((seId < 0) || (track[0x3e] == seId))) {
			int delta = pan - track[0x10];
			delta /= frameCount;
			track[0x11] = delta;
			track[0x12] = frameCount;
		}
		track += 0x55;
	} while (track < (int*)(*(int*)((char*)p_SoundControlBuffer + 0xdbc) + 0x2a80));
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
	int* track;
	pitch <<= 12;
	pitch |= 0x800;

	if (frameCount < 1) {
		frameCount = 1;
	}

	frameCount *= 0x60;
	frameCount /= 0x3c;
	track = *(int**)((char*)p_SoundControlBuffer + 0xdbc);

	do {
		if (((u32)*track != 0) && ((seId < 0) || (track[0x3e] == seId))) {
			int delta = pitch - track[0x17];
			track[0x18] = delta / frameCount;
			track[0x19] = frameCount;
		}
		track += 0x55;
	} while (track < (int*)(*(int*)((char*)p_SoundControlBuffer + 0xdbc) + 0x2a80));
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
	unsigned int* trackBasePtr;
	unsigned int track;
	unsigned int voice;

	if (m_ReportPrint != 0) {
		if (pause == 1) {
			OSReport(sRedCommandSePauseOnFmt, sRedCommandLogPrefix, seId);
		} else {
			OSReport(sRedCommandSePauseOffFmt, sRedCommandLogPrefix, seId);
		}
		fflush(__files + 1);
	}

	trackBasePtr = (unsigned int*)((char*)p_SoundControlBuffer + 0xdbc);
	track = *trackBasePtr;
	voice = (unsigned int)p_VoiceData + 0x1800;
	do {
		if ((*(int*)(track + 0xf8) != 0) && ((seId == -1) || (seId == *(int*)(track + 0xf8)))) {
			if (pause == 1) {
				if (*(void**)(voice + 0x14) != 0) {
					*(unsigned int*)(voice + 0x9c) = 0;
					*(unsigned int*)(voice + 0x90) |= 0x18;
				}
				*(unsigned int*)(track + 0xfc) |= 8;
				*(unsigned int*)(voice + 0x94) |= 8;
			} else {
				*(unsigned int*)(voice + 0xb8) |= 3;
				*(unsigned int*)(track + 0xfc) &= 0xfffffff7;
				*(unsigned int*)(voice + 0x94) &= 0xfffffff7;
			}
		}
		track += 0x154;
		voice += 0xc0;
	} while (track < *trackBasePtr + 0x2a80);
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
	int waveBase = c_RedEntry.SearchWaveBase((int)*(short*)((char*)musicHead + 6));
	if (waveBase == 0) {
		return;
	}

	int* music = (int*)p_SoundControlBuffer;
	if (mode != 0) {
		music += 0x24a;
	}

	m_MusicSkipLine = mode;
	music[0x11c] = musicId;
	music[0x11b] &= 0xfffeffff;
	music[0x122] = 0;

	if (m_CrossTime == 0) {
		music[0x115] = 0x1ff000;
		music[0x117] = 0;
	} else {
		music[0x115] = 0;
		music[0x116] = 0x1ff800;
		music[0x116] = music[0x116] / m_CrossTime;
		music[0x117] = m_CrossTime;
		m_CrossTime = 0;
	}

	int trackBase = RedNew(*(char*)((char*)musicHead + 8) * 0x154);
	if (trackBase == 0) {
		if (m_ReportPrint != 0) {
			OSReport(sRedCommandMusicTrackCreateErrorFmt,
			         sRedCommandLogPrefix, sRedCommandLogErrorColor, sRedCommandLogReset);
			fflush(__files + 1);
			OSReport(sRedCommandMusicNeedMemoryFmt,
			         sRedCommandLogPrefix, sRedCommandLogErrorColor,
			         (int)*(short*)((char*)musicHead + 4), *(char*)((char*)musicHead + 8) * 0x154, sRedCommandLogReset);
			fflush(__files + 1);
		}
		c_RedEntry.DisplayMMemoryInfo();
		return;
	}

	*music = trackBase;

	if (*(char*)((char*)musicHead + 9) != 0) {
		unsigned int reverbKind = ((int)*(char*)((char*)musicHead + 9) - 1U) & 7;
		SetReverb(0, *(int*)((char*)t_ReverbModeData + reverbKind * 0x1c),
		          (int*)((char*)t_ReverbModeData + reverbKind * 0x1c + 4));
	}

	*(int*)p_ReverbDepth = (int)*(short*)((char*)musicHead + 10);
	if (*(int*)p_ReverbDepth != 0) {
		*(int*)p_ReverbDepth = (*(int*)p_ReverbDepth + 1) << 8;
		*(int*)p_ReverbDepth = (*(int*)p_ReverbDepth - 1) << 0xc;
	}
	((int*)p_ReverbDepth)[1] = 0;
	((int*)p_ReverbDepth)[2] = 0;
	music[0x11f] = (int)*(short*)((char*)musicHead + 6);

	unsigned char* current = (unsigned char*)musicHead + 0x20;
	int* track = (int*)*music;
	int count = *(char*)((char*)musicHead + 8);
	char trackNo = 0;
	while (count != 0) {
		unsigned int blockSize = ((unsigned int)current[3] << 24) | ((unsigned int)current[2] << 16) |
		                         ((unsigned int)current[1] << 8) | (unsigned int)current[0];
		*(char*)((char*)track + 0x14e) = trackNo - 1;
		track[6] = (int)waveHead;
		*(unsigned char**)track = current + 4;
		current = current + 4 + blockSize;
		track[0x42] = DeltaTimeSumup((unsigned char**)track) + 1;
		track[0x3d] = 0;
		track[8] = (m_MusicKeySignature == 0) ? 0 : (int)(t_KeySignatureData + 0xb);
		track[0x13] = 0x7f000;
		track[0x15] = 0;
		track[10] = 0x7fff000;
		track[0xd] = 0x7f000;
		track[0x10] = 0x40000;
		track[0x1a] = *(int*)p_ReverbDepth;
		track[0x1c] = 0;
		track[0x12] = 0;
		track[0xf] = 0;
		track[0xc] = 0;
		track[0x45] = 0;
		track[0x44] = 0;
		track[0x46] = 0;
		*(short*)(track + 0x4f) = 0;
		*(short*)((char*)track + 0x142) = 0;
		*(unsigned char*)((char*)track + 0x14b) = 2;
		*(short*)((char*)track + 0x13e) = 0;
		*(short*)(track + 0x50) = 0;
		*(unsigned char*)(track + 0x52) = 0;
		track[0x2d] = 0;
		track[0x25] = 0;
		track[0x1d] = 0;
		track[0x33] = 0;
		*(short*)(track + 0x2c) = 0;
		*(short*)(track + 0x24) = 0;
		*(short*)((char*)track + 0xb2) = 0;
		*(short*)((char*)track + 0x92) = 0;
		track[7] = 0;
		track[0x41] = ((*(unsigned int*)((char*)musicHead + 0x14) & 0x40000) == 0) ? 0x200000 : 0;
		*(short*)((char*)track + 0x13a) = 0;
		*(short*)(track + 0x4e) = 0;
		track[0x3c] = 0;
		track[0x3b] = 0;
		track[0x3a] = 0;
		track[0x39] = 0;
		track[0x38] = 0;
		track[0x48] = 0xffffffff;
		*(unsigned char*)((char*)track + 0x26) = 0;
		track[0x3f] = 0xc02;
		memset(track + 0x35, 0xff, 0xc);

		count--;
		trackNo++;
		if (count != 0) {
			track += 0x55;
		}
	}

	music[0x11d] = 1;
	*(unsigned char*)((char*)music + 0x490) = 0;
	music[0x120] = 0;
	music[2] = (int)(t_KeySignatureData + 0xb);
	*(unsigned char*)((char*)music + 0x491) = *(unsigned char*)((char*)musicHead + 8);
	*(short*)((char*)music + 0x48e) = (short)*(char*)((char*)musicHead + 8);
	*(unsigned char*)((char*)music + 0x492) = (unsigned char)(*(unsigned short*)((char*)musicHead + 0xc) & 0x7f);
	*(short*)(music + 0x123) = 1;
	music[0x112] = 0x1000;
	music[5] = 10000;
	music[4] = -1;
	music[3] = 1;
	music[0x11e] = 0;
	if (volume != 0) {
		volume = (((volume + 1) * 4) - 1) * 0x1000;
	}
	music[7] = volume;
	music[9] = 0;
	music[0x122] = 0;
	music[0x11b] &= 0x10;
	if ((*(unsigned int*)((char*)musicHead + 0x14) & 0x40000) != 0) {
		music[0x11b] |= 0x40000;
	}

	c_RedEntry.WaveHistoryManager(1, music[0x11f]);
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
	unsigned int* music = (unsigned int*)p_SoundControlBuffer;

	do {
		if ((seId == -1) || (((int)music[0x11c] >= 0) && ((int)music[0x11c] == seId))) {
			unsigned int musicId = music[0x11c];
			music[0x122] = 0;
			music[0x11c] = -1;
			if (*(short*)((char*)music + 0x48e) != 0) {
				unsigned int* seTrack = p_VoiceData;
				do {
					if ((*seTrack >= *music) &&
					    (*seTrack <
					     *music + (unsigned int)*(unsigned char*)((char*)music + 0x491) *
					                   0x154)) {
						seTrack[0x25] &= 0xfffffff3;
						seTrack[0x24] &= 0xfffffffe;
						seTrack[0x24] |= 2;
						*((unsigned char*)seTrack + 0x1a) &= ~4;
						*seTrack = 0;
						seTrack[0x23] = 0;
					}
					seTrack += 0x30;
				} while (seTrack < p_VoiceData + 0xc00);

				int* track = (int*)*music;
				do {
					if ((u32)*track != 0) {
						KeyOnReserveClear((RedKeyOnDATA*)p_KeyOnData, (RedTrackDATA*)track);
						*track = 0;
					}
					track += 0x55;
				} while (track < (int*)(*music +
				                        (unsigned int)*(unsigned char*)((char*)music + 0x491) *
				                            0x154));

				*(short*)((char*)music + 0x48e) = 0;
				*(unsigned char*)((char*)music + 0x491) = 0;
				RedDelete((void*)*music);
				*music = 0;
				c_RedEntry.WaveHistoryManager(0, music[0x11f]);
				c_RedEntry.MusicHistoryManager(0, musicId);
			}
		}
		music += 0x125;
	} while (music < (unsigned int*)p_SoundControlBuffer + 0x24a);

	music = (unsigned int*)p_SoundControlBuffer;
	if (((int)music[0x11c] < 0) && ((int)music[0x241] >= 0)) {
		memcpy((void*)p_SoundControlBuffer, (unsigned int*)p_SoundControlBuffer + 0x125, 0x494);
		*(short*)((char*)music + 0x922) = 0;
		*(unsigned char*)((char*)music + 0x925) = 0;
		music[0x241] = -1;
		music[0x125] = 0;
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
	int* musicBank = c_RedEntry.SearchMusicBank(musicId);

	if (musicBank != 0) {
		RedMusicHEAD* musicHead = (RedMusicHEAD*)musicBank[2];
		RedWaveHeadWD* waveHead =
		    (RedWaveHeadWD*)c_RedEntry.SearchWaveBase(*(short*)((char*)musicHead + 6));

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
	int* music;

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

	music = (int*)p_SoundControlBuffer;
	do {
		if ((seId == -1) || (seId == music[0x11c]) || (music[0x11c] < 0)) {
			if (mode == 1) {
				music[0x116] = -music[0x115] / duration;
				music[0x117] = duration;
			} else {
				music[8] = (volume - music[7]) / duration;
				music[9] = duration;
			}
		}
		music += 0x125;
	} while ((unsigned int)music < (unsigned int)p_SoundControlBuffer + 0xdbc);
}
