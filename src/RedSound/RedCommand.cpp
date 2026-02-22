#include "ffcc/RedSound/RedCommand.h"
#include "ffcc/RedSound/RedEntry.h"
#include "ffcc/RedSound/RedDriver.h"
#include "ffcc/RedSound/RedMemory.h"
#include "ffcc/RedSound/RedMidiCtrl.h"
#include <dolphin/os.h>
#include <string.h>

extern CRedEntry DAT_8032e154;
extern int DAT_8032e12c;
extern void* DAT_8032f3f0;
extern void* DAT_8032f3fc;
extern unsigned int* DAT_8032f444;
extern int DAT_8032f408;
extern int DAT_8032f440;
extern int DAT_8021d1a8;
extern void* DAT_8032f474;
extern char DAT_801e7e3e;
extern char DAT_80333d68;
extern char DAT_80333d70;
extern char s__sPause___SE___ON__d_801e7e50[];
extern char s__sPause___SE___OFF__d_801e7e6b[];
extern char s__s_sWave_is_not_Entry___wave_4_4_801e7e18[];

extern "C" {
int fflush(void*);
int SearchMusicBank__9CRedEntryFi(CRedEntry*, int);
int SearchWaveBase__9CRedEntryFi(void*, int);
void WaveHistoryManager__9CRedEntryFii(void*, int, int);
}

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
	int* trackBasePtr = (int*)((char*)DAT_8032f3f0 + 0xdbc);
	int* track = (int*)*trackBasePtr;

	do {
		if ((*track != 0) && ((int)*(unsigned char*)((char*)track + 0x14f) <= eraseTrack) &&
		    ((((unsigned int)*(unsigned char*)(track + 0x54)) & (unsigned int)attrMask) != 0)) {
			unsigned char trackNo;
			unsigned int* seTrack;

			KeyOnReserveClear((RedKeyOnDATA*)DAT_8032f3fc, (RedTrackDATA*)track);
			track[0x3e] = 0;
			track[0x41] = 0;
			*track = 0;
			track[0x16] = 0;

			trackNo = *(unsigned char*)((char*)track + 0x14e);
			((unsigned char*)DAT_8032f444)[trackNo * 0xc0 + 0x1a] &= (unsigned char)0xfa;
			seTrack = (unsigned int*)((unsigned char*)DAT_8032f444 + trackNo * 0xc0);
			seTrack[0x25] &= 0xfffffff7;
			seTrack[0x24] &= 0xfffffffe;
			seTrack[0x24] |= 2;
			seTrack[0x23] = 0;

			DAT_8032e154.SeSepHistoryManager(0, track[0x3d]);
			if (track[6] != 0) {
				DAT_8032e154.WaveHistoryManager(0, *(short*)(track[6] + 2));
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
	int* trackBasePtr = (int*)((char*)DAT_8032f3f0 + 0xdbc);
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

			KeyOnReserveClear((RedKeyOnDATA*)DAT_8032f3fc, (RedTrackDATA*)track);
			track[0x3e] = 0;
			track[0x41] = 0;
			*track = 0;
			track[0x16] = 0;

			trackNo = *(unsigned char*)((char*)track + 0x14e);
			((unsigned char*)DAT_8032f444)[trackNo * 0xc0 + 0x1a] &=
			    (unsigned char)0xfa;
			seTrack = (unsigned int*)((unsigned char*)DAT_8032f444 + trackNo * 0xc0);
			seTrack[0x25] &= 0xfffffff7;
			seTrack[0x24] &= 0xfffffffe;
			seTrack[0x24] |= 2;
			seTrack[0x23] = 0;

			if (track[6] != 0) {
				DAT_8032e154.WaveHistoryManager(0, *(short*)(track[6] + 2));
			}
			erasedCount++;
		}
		track += 0x55;
	} while (track < (int*)(*trackBasePtr + 0x2a80));

	if (erasedCount != 0) {
		DAT_8032e154.SeSepHistoryManager(0, sepId);
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
	int* trackBasePtr;
	int* scan;
	int* track;
	int remaining;

	trackBasePtr = (int*)((char*)DAT_8032f3f0 + 0xdbc);
	if (attrMask != 0) {
		_EraseAttribute(eraseTrack, attrMask);
	}

	do {
		track = (int*)(*trackBasePtr + 0x292c);
		scan = track;
		remaining = trackCount;
		do {
			while (((track = scan, remaining = remaining - 1, remaining != 0) && (*track == 0)) &&
			       ((((unsigned char*)track)[0x26] & 2) == 0)) {
				scan = track - 0x55;
			}
			if ((*track != 0) || ((((unsigned char*)track)[0x26] & 2) != 0)) {
				remaining = 1;
				scan = track;
			}
			scan = scan - 0x55;
		} while ((remaining != 0) && ((int*)*trackBasePtr <= track));
	} while ((track < (int*)*trackBasePtr) && (_EraseTime(eraseTrack) != 0));

	if (track < (int*)*trackBasePtr) {
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
	int* trackBasePtr = (int*)((char*)DAT_8032f3f0 + 0xdbc);
	int* track;

	*(unsigned int*)((char*)DAT_8032f3f0 + 0x1244) = 0;
	track = (int*)*trackBasePtr;
	do {
		if ((*track != 0) && ((seId == -1) || (track[0x3e] == seId))) {
			unsigned char trackNo;
			unsigned int* seTrack;

			KeyOnReserveClear((RedKeyOnDATA*)DAT_8032f3fc, (RedTrackDATA*)track);
			track[0x3e] = 0;
			track[0x41] = 0;
			*track = 0;
			track[0x16] = 0;

			trackNo = *(unsigned char*)((char*)track + 0x14e);
			((unsigned char*)DAT_8032f444)[trackNo * 0xc0 + 0x1a] &= (unsigned char)0xfa;
			seTrack = (unsigned int*)((unsigned char*)DAT_8032f444 + trackNo * 0xc0);
			seTrack[0x25] &= 0xfffffff7;
			seTrack[0x24] &= 0xfffffffe;
			seTrack[0x24] |= 2;
			seTrack[0] = 0;
			seTrack[0x23] = 0;

			if (track[6] != 0) {
				DAT_8032e154.WaveHistoryManager(0, *(short*)(track[6] + 2));
			}
			DAT_8032e154.SeSepHistoryManager(0, track[0x3d]);
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

	soundBase = (int)DAT_8032f3f0;
	trackBasePtr = (int*)(soundBase + 0xdbc);
	*(unsigned int*)(soundBase + 0x1244) = 0;
	track = *(int**)(soundBase + 0xdbc);
	do {
		if ((*track != 0) && ((track[0x3d] & 0x80000000U) == 0)) {
			int id = track[0x3d] / 1000 + (track[0x3d] >> 0x1f);
			id = id - (id >> 0x1f);
			if ((bank != id) && (sep != id) && (group != id) && (kind != id)) {
				unsigned char trackNo;
				unsigned int* seTrack;

				KeyOnReserveClear((RedKeyOnDATA*)DAT_8032f3fc, (RedTrackDATA*)track);
				track[0x3e] = 0;
				track[0x41] = 0;
				*track = 0;
				track[0x16] = 0;

				trackNo = *(unsigned char*)((char*)track + 0x14e);
				((unsigned char*)DAT_8032f444)[trackNo * 0xc0 + 0x1a] &= (unsigned char)0xfa;
				seTrack = (unsigned int*)((unsigned char*)DAT_8032f444 + trackNo * 0xc0);
				seTrack[0x25] &= 0xfffffff7;
				seTrack[0x24] &= 0xfffffffe;
				seTrack[0x24] |= 2;
				seTrack[0] = 0;
				seTrack[0x23] = 0;

				if (track[6] != 0) {
					DAT_8032e154.WaveHistoryManager(0, *(short*)(track[6] + 2));
				}
				DAT_8032e154.SeSepHistoryManager(0, track[0x3d]);
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

	*(unsigned int*)((char*)DAT_8032f3f0 + 0x1244) = 0;
	deltaTime = (unsigned int)((unsigned char*)info)[2] * 0x100 + (unsigned int)((unsigned char*)info)[1];
	waveBase = SearchWaveBase__9CRedEntryFi(&DAT_8032e154, deltaTime);
	if (waveBase == 0) {
		if (DAT_8032f408 != 0) {
			OSReport(s__s_sWave_is_not_Entry___wave_4_4_801e7e18, &DAT_801e7e3e, &DAT_80333d68,
			         deltaTime, &DAT_80333d70);
			fflush(&DAT_8021d1a8);
		}
	} else {
		WaveHistoryManager__9CRedEntryFii(&DAT_8032e154, 1, *(short*)(waveBase + 2));
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

		seTrack = (int*)((unsigned char*)DAT_8032f444 + *(char*)((char*)track + 0x14e) * 0xc0);
		while (true) {
			track[6] = waveBase;
			*(unsigned char**)track = current;
			current = current +
			          (((unsigned int)seq[1] * 0x100 + (unsigned int)*seq) & 0x7fff);
			deltaTime = (int)DeltaTimeSumup((unsigned char**)track);
			track[0x42] = deltaTime + 1;
			if (DAT_8032f440 != 0) {
				track[0x42] = track[0x42] - DAT_8032f440;
			}

			track[0x3d] = sepId;
			track[0x3e] = seId;
			*(short*)(track + 0x51) = 0;
			if (DAT_8032f440 == 0) {
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
				track[0x1a] = *(int*)((char*)DAT_8032f474 + 0xc);
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
	int bankData;
	int seOffset;
	unsigned char* seInfo;

	bank &= 3;
	no &= 0x1ff;
	bankData = (&DAT_8032e12c)[bank];
	if (bankData != 0) {
		if ((no < *(short*)(bankData + 10)) &&
		    (*(int*)((bankData + 0x10) + no * 4) != -1)) {
			seOffset = *(int*)((bankData + 0x10) + no * 4);
			seInfo = (unsigned char*)((bankData + 0x10) + *(short*)(bankData + 10) * 4 +
			                          (seOffset & 0x7fffffff));
			if ((seOffset & 0x80000000) != 0) {
				*seInfo |= 0x80;
			}
			if (_SePlayStart((RedSeINFO*)seInfo, seId, no + bank * 0x200 | 0x80000000, pan, volume) !=
			    0) {
				return no;
			}
		}
	}
	return -1;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void SeSepPlay(int, int, int, int)
{
	// TODO
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
	int step;

	if (frameCount < 1) {
		frameCount = 1;
	}

	track = *(int**)((char*)DAT_8032f3f0 + 0xdbc);
	step = (frameCount * 0x60) / 0x3c + ((frameCount * 0x60) >> 0x1f);
	step = step - (step >> 0x1f);

	do {
		if ((*track != 0) && ((seId < 0) || (track[0x3e] == seId))) {
			track[0x14] = ((volume << 0xc) | 0x800) - track[0x13];
			track[0x14] /= step;
			track[0x15] = step;
			track[0x16] = mode;
		}
		track += 0x55;
	} while (track < (int*)(*(int*)((char*)DAT_8032f3f0 + 0xdbc) + 0x2a80));
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
	int step;

	if (frameCount < 1) {
		frameCount = 1;
	}

	track = *(int**)((char*)DAT_8032f3f0 + 0xdbc);
	step = (frameCount * 0x60) / 0x3c + ((frameCount * 0x60) >> 0x1f);
	step = step - (step >> 0x1f);

	do {
		if ((*track != 0) && ((seId < 0) || (track[0x3e] == seId))) {
			track[0x11] = (((pan << 0xc) | 0x800) - track[0x10]) / step;
			track[0x12] = step;
		}
		track += 0x55;
	} while (track < (int*)(*(int*)((char*)DAT_8032f3f0 + 0xdbc) + 0x2a80));
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
	int step;

	if (frameCount < 1) {
		frameCount = 1;
	}

	track = *(int**)((char*)DAT_8032f3f0 + 0xdbc);
	step = (frameCount * 0x60) / 0x3c + ((frameCount * 0x60) >> 0x1f);
	step = step - (step >> 0x1f);

	do {
		if ((*track != 0) && ((seId < 0) || (track[0x3e] == seId))) {
			track[0x18] = (((pitch << 0xc) | 0x800) - track[0x17]) / step;
			track[0x19] = step;
		}
		track += 0x55;
	} while (track < (int*)(*(int*)((char*)DAT_8032f3f0 + 0xdbc) + 0x2a80));
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

	if (DAT_8032f408 != 0) {
		if (pause == 1) {
			OSReport(s__sPause___SE___ON__d_801e7e50, &DAT_801e7e3e, seId);
		} else {
			OSReport(s__sPause___SE___OFF__d_801e7e6b, &DAT_801e7e3e, seId);
		}
		fflush(&DAT_8021d1a8);
	}

	trackBasePtr = (unsigned int*)((char*)DAT_8032f3f0 + 0xdbc);
	track = *trackBasePtr;
	voice = (unsigned int)DAT_8032f444 + 0x1800;
	do {
		if ((*(int*)(track + 0xf8) != 0) && ((seId == -1) || (seId == *(int*)(track + 0xf8)))) {
			if (pause == 1) {
				if (*(int*)(voice + 0x14) != 0) {
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
 * Address:	TODO
 * Size:	TODO
 */
void _MusicPlayStart(RedMusicHEAD*, RedWaveHeadWD*, int, int, int)
{
	// TODO
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
void MusicStop(int seId)
{
	unsigned int* musicBase = (unsigned int*)DAT_8032f3f0;
	unsigned int* music = musicBase;

	do {
		if ((seId == -1) || (((int)music[0x11c] >= 0) && (music[0x11c] == (unsigned int)seId))) {
			unsigned int musicId = music[0x11c];
			music[0x122] = 0;
			music[0x11c] = -1;
			if (*(short*)((char*)music + 0x48e) != 0) {
				unsigned int* seTrack = DAT_8032f444;
				do {
					if ((*music <= *seTrack) &&
					    (*seTrack <
					     *music + (unsigned int)*(unsigned char*)((char*)music + 0x491) *
					                   0x154)) {
						seTrack[0x25] &= 0xfffffff3;
						seTrack[0x24] &= 0xfffffffe;
						seTrack[0x24] |= 2;
						*((unsigned char*)seTrack + 0x1a) &= 0xfb;
						*seTrack = 0;
						seTrack[0x23] = 0;
					}
					seTrack += 0x30;
				} while (seTrack < DAT_8032f444 + 0xc00);

				int* track = (int*)*music;
				do {
					if (*track != 0) {
						KeyOnReserveClear((RedKeyOnDATA*)DAT_8032f3fc, (RedTrackDATA*)track);
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
				DAT_8032e154.WaveHistoryManager(0, music[0x11f]);
				DAT_8032e154.MusicHistoryManager(0, musicId);
			}
		}
		music += 0x125;
	} while (music < musicBase + 0x24a);

	if (((int)musicBase[0x11c] < 0) && ((int)musicBase[0x241] >= 0)) {
		memcpy(musicBase, musicBase + 0x125, 0x494);
		*(short*)((char*)musicBase + 0x922) = 0;
		*(unsigned char*)((char*)musicBase + 0x925) = 0;
		musicBase[0x241] = -1;
		musicBase[0x125] = 0;
	}
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
	int musicBank = SearchMusicBank__9CRedEntryFi(&DAT_8032e154, musicId);

	if (musicBank != 0) {
		int musicHead = *(int*)(musicBank + 8);
		int waveHead = SearchWaveBase__9CRedEntryFi(&DAT_8032e154, (int)*(short*)(musicHead + 6));
		if (waveHead == 0) {
			return -1;
		}

		_MusicPlayStart((RedMusicHEAD*)musicHead, (RedWaveHeadWD*)waveHead, musicId, volume, mode);
	}

	return 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void SetMusicVolume(int, int, int, int)
{
	// TODO
}
