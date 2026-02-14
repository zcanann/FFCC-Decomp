#include "ffcc/RedSound/RedCommand.h"
#include "ffcc/RedSound/RedEntry.h"
#include "ffcc/RedSound/RedMidiCtrl.h"

extern CRedEntry DAT_8032e154;
extern void* DAT_8032f3f0;
extern void* DAT_8032f3fc;
extern unsigned int* DAT_8032f444;

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _EraseAttribute(int, int)
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void SeStopID(int)
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void MusicStop(int)
{
	// TODO
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
