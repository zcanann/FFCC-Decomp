#include "ffcc/RedSound/RedCommand.h"
#include "ffcc/RedSound/RedEntry.h"
#include "ffcc/RedSound/RedMemory.h"
#include "ffcc/RedSound/RedMidiCtrl.h"
#include <string.h>

extern CRedEntry DAT_8032e154;
extern void* DAT_8032f3f0;
extern void* DAT_8032f3fc;
extern unsigned int* DAT_8032f444;

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
 * Address:	TODO
 * Size:	TODO
 */
void SearchSeEmptyTrack(int, int, int)
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void SeStopMG(int, int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _SePlayStart(RedSeINFO*, int, int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void SeBlockPlay(int, int, int, int, int)
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void SetSeVolume(int, int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void SetSePan(int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void SetSePitch(int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void SePause(int, int)
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void MusicPlay(int, int, int)
{
	// TODO
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
