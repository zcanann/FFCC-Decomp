#include "ffcc/RedSound/RedEntry.h"
#include "ffcc/RedSound/RedCommand.h"
#include "ffcc/RedSound/RedDriver.h"
#include "ffcc/RedSound/RedMemory.h"
#include <dolphin/os.h>
#include <string.h>

extern CRedMemory DAT_8032f480;
extern int DAT_8032f408;
extern void* DAT_8032f3f0;
extern int DAT_8032e12c;
extern int DAT_8021d1a8;
extern char DAT_801e7905;
extern char DAT_80333d30;
extern char DAT_80333d38;
extern char DAT_80333d3d;
extern char DAT_80333d45;
extern char DAT_80333d4d;
extern char DAT_80333d4f;
extern char s__s_sNOT_HAVE_A_MEMORY_FREE_AREA___801e7991[];
extern char s__s_sWave_Header_was_broken__s_801e7972[];
extern char s__s_____SE_Play_Information______801e7b71[];
extern char s__s_Track___Name___Wave_801e7b92[];
extern char s__s__2d____3_3u__3_3u___WAVE_4_4u_801e7bb2[];
extern char s__s__2d___se_6_6u_sep___WAVE_4_4u_801e7bdc[];
extern char s__s__2d_____801e7c01[];
extern char s__s_____AMemory_Information______801e79ed[];
extern char s__s_Bank___Name___Start___Size___F_801e7a0e[];
extern char s__s__2d___WAVE_4_4d___0x_8_8X___0_801e7a53[];
extern char s__s______WAVE_4_4d___0x_8_8X___0x_801e7a8f[];
extern char s__s______________0x_8_8X___0x_8_8_801e7aca[];
extern char s__s_Entry_Wave____d_801e7b01[];
extern char s__s_Total_Size___0x_8_8X_801e7b18[];
extern char s__s_Max_Free_Size___0x_8_8X_801e7b34[];
extern char s__s_sWave_Entry___wave_4_4u__s_801e79ce[];
extern char s__s_____MMemory_Information______801e7cce[];
extern char s__s_Name___Start___Size___Free_801e7cef[];
extern char s__s_MUSIC_3_3d___0x_8_8X___0x_8_8_801e7d24[];
extern char s__s_SE_BLOCK___0x_8_8X___0x_8_8X___801e7d51[];
extern char s__s_WAVE_4_4d___0x_8_8X___0x_8_8X_801e7d7c[];
extern char s__s_SE_6_6d___0x_8_8X___0x_8_8X___801e7da8[];
extern char s__s____________0x_8_8X___0x_8_8X___801e7dd2[];
extern char s__s_Entry_Items____d_801e7dfd[];

extern "C" {
	void* RedNew__Fi(int);
	int fflush(void*);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CRedEntry::CRedEntry()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CRedEntry::~CRedEntry()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x801c0644
 * PAL Size: 244b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedEntry::Init()
{
	int iVar1;
	int iVar2;
	int* entry = (int*)this;

	iVar2 = (int)RedNew__Fi(0x400);
	entry[0] = iVar2;
	iVar2 = (int)RedNew__Fi(0x1000);
	entry[1] = iVar2;
	iVar2 = (int)RedNew__Fi(0x40);
	entry[2] = iVar2;

	memset((void*)entry[0], 0, 0x400);
	iVar2 = 0;
	do {
		iVar1 = iVar2 * 0x10;
		iVar2 = iVar2 + 1;
		*(int*)(entry[0] + iVar1) = -1;
	} while (iVar2 < 0x40);

	memset((void*)entry[1], 0, 0x1000);
	iVar2 = 0;
	do {
		iVar1 = iVar2 * 0x10;
		iVar2 = iVar2 + 1;
		*(int*)(entry[1] + iVar1) = -1;
	} while (iVar2 < 0x100);

	memset((void*)entry[2], 0, 0x40);
	iVar2 = 0;
	do {
		iVar1 = iVar2 * 0x10;
		iVar2 = iVar2 + 1;
		*(int*)(entry[2] + iVar1) = -1;
	} while (iVar2 < 4);

	entry[3] = -1;
}

/*
 * --INFO--
 * PAL Address: 0x801c0738
 * PAL Size: 72b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedEntry::WaveHistoryAdd(int historyNo)
{
	int* const entry = reinterpret_cast<int*>(this);
	unsigned int history = static_cast<unsigned int>(entry[0] + 0x100);

	do {
		if (historyNo <= *reinterpret_cast<int*>(history + 4)) {
			*reinterpret_cast<int*>(history + 4) = *reinterpret_cast<int*>(history + 4) + 1;
		}
		history += 0x10;
	} while (history < static_cast<unsigned int>(entry[0] + 0x400));
}

/*
 * --INFO--
 * PAL Address: 0x801c0780
 * PAL Size: 88b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedEntry::WaveHistoryDelete(int historyNo)
{
	if (historyNo != 0) {
		unsigned int history = static_cast<unsigned int>(*reinterpret_cast<int*>(this));
		do {
			int* const priority = reinterpret_cast<int*>(history + 4);
			if ((*priority != 0) && (historyNo < *priority)) {
				*priority = *priority - 1;
			}
			history += 0x10;
		} while (history < static_cast<unsigned int>(*reinterpret_cast<int*>(this)) + 0x400);
	}
}

/*
 * --INFO--
 * PAL Address: 0x801c07d8
 * PAL Size: 104b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedEntry::WaveHistoryChoice(RedHistoryBANK* bank)
{
	if (reinterpret_cast<int*>(bank)[1] != 0) {
		unsigned int history = static_cast<unsigned int>(*reinterpret_cast<int*>(this));
		do {
			int* const priority = reinterpret_cast<int*>(history + 4);
			if ((*priority != 0) && (*priority < reinterpret_cast<int*>(bank)[1])) {
				*priority = *priority + 1;
			}
			history += 0x10;
		} while (history < static_cast<unsigned int>(*reinterpret_cast<int*>(this)) + 0x400);

		reinterpret_cast<int*>(bank)[1] = 1;
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CRedEntry::SearchWaveSequence(int waveNo)
{
	int* entry = (int*)this;
	int* const waveBankBase = (int*)entry[0];
	int* waveBank = waveBankBase;
	int i;

	for (i = 0x40; i > 0; i--) {
		if ((waveBank[3] != 0) && (waveBank[0] == waveNo)) {
			int offset = (int)waveBank - (int)waveBankBase;
			return (offset >> 4) + (int)((offset < 0) && ((offset & 0xF) != 0));
		}
		waveBank += 4;
	}

	return -1;
}

/*
 * --INFO--
 * PAL Address: 0x801c08a0
 * PAL Size: 208b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedEntry::SearchUseWave(int waveNo)
{
	unsigned int interruptLevel = OSDisableInterrupts();
	int found = 0;
	int soundBase = (int)DAT_8032f3f0 + 0x494;

	do {
		if ((-1 < *(int*)(soundBase + 0x470)) && (*(int*)(soundBase + 0x47c) == waveNo)) {
			found = 1;
			MusicStop(*(int*)(soundBase + 0x470));
		}
		soundBase -= 0x494;
	} while ((int)DAT_8032f3f0 <= soundBase);

	int* trackBasePtr = (int*)((char*)DAT_8032f3f0 + 0xdbc);
	int* track = (int*)*trackBasePtr;
	do {
		if ((*track != 0) && (track[6] != 0) && (*(short*)(track[6] + 2) == waveNo)) {
			found = 1;
			SeStopID(track[0x3e]);
		}
		track += 0x55;
	} while (track < (int*)(*trackBasePtr + 0x2a80));

	OSRestoreInterrupts(interruptLevel);
	return found;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedEntry::WaveDelete(RedHistoryBANK*)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x801c0ad4
 * PAL Size: 172b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedEntry::WaveOldClear(int offset, int maxSize)
{
	unsigned int selected = 0;
	int maxBankSize = 0;
	int* entry = (int*)this;
	int aBase = DAT_8032f480.GetABufferAddress();
	unsigned int history = (unsigned int)entry[0] + 0x100;

	do {
		int bankSize = *(int*)(history + 4);
		if (maxBankSize < bankSize) {
			int arAddress = *(int*)(*(int*)(history + 8) + 0x10);
			if ((offset + aBase <= arAddress) && (arAddress < maxSize + aBase)) {
				maxBankSize = bankSize;
				selected = history;
			}
		}
		history += 0x10;
	} while (history < (unsigned int)entry[0] + 0x400);

	if (maxBankSize != 0) {
		WaveDelete((RedHistoryBANK*)selected);
	}

	return maxBankSize;
}

/*
 * --INFO--
 * PAL Address: 0x801c0b80
 * PAL Size: 832b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedEntry::WaveHeadAdd(int waveBankNo, RedWaveHeadWD* waveHead, int waveNo)
{
	unsigned char* head = (unsigned char*)waveHead;
	int* entry = (int*)this;

	if ((head[0] == 'W') && (head[1] == 'D')) {
		if (*(int*)(head + 0x14) < *(int*)(head + 4)) {
			*(int*)(head + 0x14) = *(int*)(head + 4);
		}

		if ((waveNo < 100) || (299 < waveNo)) {
			if ((waveNo < 10) || (0x45 < waveNo)) {
				if (((0x153 < waveNo) && (waveNo < 0x17a)) || ((0x17e < waveNo) && (waveNo < 0x182)) ||
				    (waveNo == 0x183)) {
					*(int*)(head + 0x14) = 0x1000;
				}
			} else {
				*(int*)(head + 0x14) += 0x27FFF;
				int blocks = *(int*)(head + 0x14) / 0x28000 + (*(int*)(head + 0x14) >> 0x1F);
				blocks = blocks - (blocks >> 0x1F);
				*(int*)(head + 0x14) = blocks * 0x28000;
			}
		} else if (*(int*)(head + 0x14) < 0x200001) {
			*(int*)(head + 0x14) = 0x2000;
		} else if (*(int*)(head + 0x14) < 0x400001) {
			*(int*)(head + 0x14) = 0x4000;
		}

		int minOffset;
		int maxOffset;
		if ((waveNo < 100) || (299 < waveNo)) {
			if (((waveNo < 0x154) || (0x179 < waveNo)) &&
			    (((waveNo < 0x17f) || (0x181 < waveNo)) && (waveNo != 0x183))) {
				minOffset = 0;
				maxOffset = 0x300000;
			} else {
				minOffset = 0x300000;
				maxOffset = 0x400000;
			}
		} else {
			minOffset = 0x400000;
			maxOffset = 0x800000;
		}

		do {
			int* historyBank;
			if (waveBankNo < 0) {
				historyBank = (int*)(entry[0] + 0x100);
				while ((historyBank[3] != 0) && (historyBank < (int*)(entry[0] + 0x400U))) {
					historyBank += 4;
				}
			} else {
				waveBankNo &= 0xF;
				historyBank = (int*)(entry[0] + waveBankNo * 0x10);
				if (historyBank[3] != 0) {
					WaveDelete((RedHistoryBANK*)historyBank);
				}
			}

			int arAddress;
			if ((historyBank < (int*)(entry[0] + 0x400U)) &&
			    ((arAddress = RedNewA(*(int*)(head + 0x14), minOffset, maxOffset)) != 0)) {
				int copySize = (((*(int*)(head + 8) * 4) + 0x1F) & 0xFFFFFFE0) + *(int*)(head + 0xC) * 0x60 +
				               0x20;
				void* copied = RedNew__Fi(copySize);
				if (copied != 0) {
					historyBank[2] = (int)copied;
					historyBank[3] = copySize;
					*(int*)(head + 0x10) = arAddress;
					historyBank[0] = waveNo;
					*(short*)(head + 2) = (short)waveNo;
					if (waveBankNo < 0) {
						WaveHistoryAdd(1);
						historyBank[1] = 1;
					} else {
						historyBank[1] = 0;
					}
					memcpy(copied, head, copySize);
					return arAddress;
				}
				RedDeleteA(arAddress);
			}
		} while (WaveOldClear(minOffset, maxOffset) != 0);

		if (DAT_8032f408 != 0) {
			OSReport(s__s_sNOT_HAVE_A_MEMORY_FREE_AREA___801e7991, &DAT_801e7905, &DAT_80333d30, (int)*(short*)(head + 2),
			         *(int*)(head + 4), &DAT_80333d38);
			fflush(&DAT_8021d1a8);
		}
	} else if (DAT_8032f408 != 0) {
		OSReport(s__s_sWave_Header_was_broken__s_801e7972, &DAT_801e7905, &DAT_80333d3d, &DAT_80333d38);
		fflush(&DAT_8021d1a8);
	}

	return -1;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CRedEntry::SetWaveData(int waveBankNo, void* waveData, int waveDataSize)
{
	int* entry = (int*)this;
	int waveNo;
	int waveAddress;

	if (waveDataSize == 0) {
		if ((-1 < entry[3]) && ((waveNo = SearchWaveSequence(entry[3])) > -1)) {
			WaveDelete((RedHistoryBANK*)(entry[0] + waveNo * 0x10));
		}

		entry[3] = -1;
		return -1;
	}

	waveAddress = 0;
	if (entry[3] < 0) {
		RedWaveHeadWD* waveHead = (RedWaveHeadWD*)waveData;
		waveNo = *(short*)((unsigned char*)waveHead + 2);

		if ((waveBankNo > -1) && (waveNo != *(int*)(entry[0] + waveBankNo * 0x10))) {
			WaveDelete((RedHistoryBANK*)(entry[0] + waveBankNo * 0x10));
		}

		int historyNo = SearchWaveSequence(waveNo);
		if (historyNo < 0) {
			entry[3] = waveNo;
			waveAddress = WaveHeadAdd(waveBankNo, waveHead, waveNo);
			if (waveAddress < 0) {
				entry[4] = 0;
				entry[3] = -1;
				return -1;
			}

			int waveHeadSize =
			    ((((*(int*)((unsigned char*)waveHead + 8) * 4) + 0x1F) & 0xFFFFFFE0) +
			     *(int*)((unsigned char*)waveHead + 0xC) * 0x60) +
			    0x20;
			entry[4] = *(int*)((unsigned char*)waveHead + 4);
			entry[5] = waveAddress;
			waveDataSize -= waveHeadSize;
			waveData = (void*)((unsigned char*)waveData + waveHeadSize);
		} else {
			if ((waveBankNo > -1) && (historyNo != waveBankNo)) {
				int src = entry[0] + historyNo * 0x10;
				int dst = entry[0] + waveBankNo * 0x10;
				*(int*)(dst + 0x0) = *(int*)(src + 0x0);
				*(int*)(dst + 0x4) = *(int*)(src + 0x4);
				*(int*)(dst + 0x8) = *(int*)(src + 0x8);
				*(int*)(dst + 0xC) = *(int*)(src + 0xC);
				historyNo = waveBankNo;
			}

			WaveHistoryChoice((RedHistoryBANK*)(entry[0] + historyNo * 0x10));
		}
	} else {
		waveAddress = entry[5];
	}

	if ((waveAddress != 0) && (waveDataSize > 0)) {
		int transferSize = entry[4];
		if (waveDataSize < transferSize) {
			transferSize = waveDataSize;
		}

		int dmaID = RedDmaEntry(0x8000, 0, (int)waveData, waveAddress, transferSize, 0, 0);
		entry[4] -= transferSize;
		entry[5] += transferSize;

		while (RedDmaSearchID(dmaID) > 0) {
			RedSleep(1000);
		}

		if (entry[4] < 1) {
			if (DAT_8032f408 != 0) {
				OSReport(s__s_sWave_Entry___wave_4_4u__s_801e79ce, &DAT_801e7905, &DAT_80333d45, entry[3], &DAT_80333d38);
				fflush(&DAT_8021d1a8);
			}

			entry[3] = -1;
			return 0;
		}
	}

	return entry[3];
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedEntry::ClearWaveData(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedEntry::ClearWaveDataM(int, int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedEntry::ClearWaveBank(int)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x801c14d0
 * PAL Size: 40b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedEntry::GetWaveBank(int waveNo)
{
	int* entry = (int*)this;

	if ((-1 < waveNo) && (waveNo < 0x10))
	{
		return *entry + (waveNo * 0x10);
	}

	return 0;
}

/*
 * --INFO--
 * PAL Address: 0x801c14f8
 * PAL Size: 68b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedEntry::SearchWaveBase(int waveNo)
{
	int* entry = (int*)this;
	int* waveBank = (int*)*entry;

	do
	{
		if (*waveBank == waveNo)
		{
			return waveBank[2];
		}
		waveBank += 4;
	} while (waveBank < (int*)(*entry + 0x400));

	return 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedEntry::ReentryWaveData(int)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x801c1594
 * PAL Size: 408b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedEntry::WaveHistoryManager(int mode, int waveNo)
{
	if (mode == 0) {
		bool used = false;

		if ((*(short*)((char*)DAT_8032f3f0 + 0x48e) != 0) && (*(int*)((char*)DAT_8032f3f0 + 0x47c) == waveNo)) {
			used = true;
		}

		if ((*(short*)((char*)DAT_8032f3f0 + 0x922) != 0) && (*(int*)((char*)DAT_8032f3f0 + 0x910) == waveNo)) {
			used = true;
		}

		if (!used) {
			int* track = *(int**)((char*)DAT_8032f3f0 + 0xdbc);
			do {
				if ((*track != 0) && (track[6] != 0) && (*(short*)(track[6] + 2) == waveNo)) {
					used = true;
					break;
				}
				track += 0x55;
			} while (track < (int*)(*(int*)((char*)DAT_8032f3f0 + 0xdbc) + 0x2a80));
		}

		int seq = SearchWaveSequence(waveNo);
		if ((!used) && (0xf < seq)) {
			int* history = (int*)(*(int*)this + seq * 0x10);
			if (history[1] == 0) {
				WaveHistoryAdd(0x14);
				history[1] = 0x14;
			}
		}
	} else {
		int seq = SearchWaveSequence(waveNo);
		if (0xf < seq) {
			int* history = (int*)(*(int*)this + seq * 0x10);
			if (history[1] != 0) {
				WaveHistoryDelete(history[1]);
				history[1] = 0;
			}
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x801c172c
 * PAL Size: 864b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedEntry::DisplayWaveInfo()
{
	int* entry = (int*)this;

	if (DAT_8032f408 != 0) {
		OSReport(&DAT_80333d4d);
		fflush(&DAT_8021d1a8);
		OSReport(s__s_____AMemory_Information______801e79ed, &DAT_801e7905);
		fflush(&DAT_8021d1a8);
		OSReport(s__s_Bank___Name___Start___Size___F_801e7a0e, &DAT_801e7905);
		fflush(&DAT_8021d1a8);

		int maxFreeSize = 0;
		int totalSize = 0;
		int entryWave = 0;
		int aBufferAddress = DAT_8032f480.GetABufferAddress();
		int* aBankAddress = (int*)DAT_8032f480.GetABankAddress();
		int aBufferEnd = aBufferAddress + DAT_8032f480.GetABufferSize();

		int* bank = aBankAddress;
		do {
			if (bank[1] != 0) {
				int freeSize;
				if (bank[3] < 1) {
					freeSize = aBufferEnd - (bank[0] + bank[1]);
				} else {
					freeSize = bank[2] - (bank[0] + bank[1]);
				}

				unsigned int history = (unsigned int)entry[0];
				do {
					if ((*(int*)(history + 0xC) != 0) && (*(int*)(*(int*)(history + 8) + 0x10) == bank[0])) {
						break;
					}
					history += 0x10;
				} while (history < (unsigned int)entry[0] + 0x400);

				if (history < (unsigned int)entry[0] + 0x400) {
					if (history < (unsigned int)entry[0] + 0x100) {
						unsigned int index = history - (unsigned int)entry[0];
						OSReport(s__s__2d___WAVE_4_4d___0x_8_8X___0_801e7a53, &DAT_801e7905, (int)(index >> 4),
						         (int)*(short*)(*(int*)(history + 8) + 2), *(int*)(*(int*)(history + 8) + 0x10), bank[1],
						         freeSize, *(int*)(history + 4));
						fflush(&DAT_8021d1a8);
					} else {
						OSReport(s__s______WAVE_4_4d___0x_8_8X___0x_801e7a8f, &DAT_801e7905,
						         (int)*(short*)(*(int*)(history + 8) + 2), *(int*)(*(int*)(history + 8) + 0x10), bank[1],
						         freeSize, *(int*)(history + 4));
						fflush(&DAT_8021d1a8);
					}
					entryWave += 1;
				} else {
					unsigned int bankIndex = (unsigned int)((int)bank - (int)aBankAddress);
					OSReport(s__s______________0x_8_8X___0x_8_8_801e7aca, &DAT_801e7905, bank[0], bank[1], freeSize,
					         (int)(bankIndex >> 3));
					fflush(&DAT_8021d1a8);
				}

				if (maxFreeSize < bank[0] - aBufferAddress) {
					maxFreeSize = bank[0] - aBufferAddress;
				}
				totalSize += bank[1];
				aBufferAddress = bank[0] + bank[1];
			}
			bank += 2;
		} while (bank < aBankAddress + 0x800);

		int aBase = DAT_8032f480.GetABufferAddress();
		int aSize = DAT_8032f480.GetABufferSize();
		if (maxFreeSize < (aBase + aSize) - aBufferAddress) {
			maxFreeSize = (aBase + DAT_8032f480.GetABufferSize()) - aBufferAddress;
		}

		OSReport(&DAT_80333d4f, &DAT_801e7905);
		fflush(&DAT_8021d1a8);
		OSReport(s__s_Entry_Wave____d_801e7b01, &DAT_801e7905, entryWave);
		fflush(&DAT_8021d1a8);
		OSReport(s__s_Total_Size___0x_8_8X_801e7b18, &DAT_801e7905, totalSize);
		fflush(&DAT_8021d1a8);
		OSReport(s__s_Max_Free_Size___0x_8_8X_801e7b34, &DAT_801e7905, maxFreeSize);
		fflush(&DAT_8021d1a8);
		OSReport(&DAT_80333d4f, &DAT_801e7905);
		fflush(&DAT_8021d1a8);
		OSReport(&DAT_80333d4d);
		fflush(&DAT_8021d1a8);
	}
}

/*
 * --INFO--
 * PAL Address: 0x801c1a8c
 * PAL Size: 68b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedEntry::SeSepHistoryAdd()
{
	int* const entry = (int*)this;
	unsigned int history = (unsigned int)entry[1];
	do {
		if (*(int*)(history + 4) != 0) {
			*(int*)(history + 4) = *(int*)(history + 4) + 1;
		}
		history += 0x10;
	} while (history < (unsigned int)(entry[1] + 0x1000));
}

/*
 * --INFO--
 * PAL Address: 0x801c1ad0
 * PAL Size: 76b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedEntry::SeSepHistoryDelete(int historyNo)
{
	if (historyNo != 0) {
		int* const entry = (int*)this;
		unsigned int history = (unsigned int)entry[1];
		do {
			if (historyNo < *(int*)(history + 4)) {
				*(int*)(history + 4) = *(int*)(history + 4) - 1;
			}
			history += 0x10;
		} while (history < (unsigned int)(entry[1] + 0x1000));
	}
}

/*
 * --INFO--
 * PAL Address: 0x801c1b1c
 * PAL Size: 104b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedEntry::SeSepHistoryChoice(RedHistoryBANK* bank)
{
	if (((int*)bank)[1] != 0) {
		int* const entry = (int*)this;
		unsigned int history = (unsigned int)entry[1];
		do {
			if ((*(int*)(history + 4) != 0) && (*(int*)(history + 4) < ((int*)bank)[1])) {
				*(int*)(history + 4) = *(int*)(history + 4) + 1;
			}
			history += 0x10;
		} while (history < (unsigned int)(entry[1] + 0x1000));
		((int*)bank)[1] = 1;
	}
}

/*
 * --INFO--
 * PAL Address: 0x801c1b84
 * PAL Size: 156b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedEntry::SearchSeSepSequence(int seNo)
{
	int* const base = reinterpret_cast<int*>(*reinterpret_cast<int*>(reinterpret_cast<int>(this) + 4));
	int* seSepBank = base;

	if (seNo == -1) {
		do {
			if (seSepBank[3] != 0) {
				int offset = reinterpret_cast<int>(seSepBank) - reinterpret_cast<int>(base);
				return (offset >> 4) + ((offset < 0) && ((offset & 0xF) != 0));
			}
			seSepBank += 4;
		} while ((unsigned int)seSepBank < (unsigned int)base + 0x1000);
	} else {
		do {
			if ((seSepBank[3] != 0) && (seSepBank[0] == seNo)) {
				int offset = reinterpret_cast<int>(seSepBank) - reinterpret_cast<int>(base);
				return (offset >> 4) + ((offset < 0) && ((offset & 0xF) != 0));
			}
			seSepBank += 4;
		} while ((unsigned int)seSepBank < (unsigned int)base + 0x1000);
	}

	return -1;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedEntry::SeSepMemoryFree(RedHistoryBANK*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedEntry::SeSepOldDelete()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedEntry::SeSepHeadAdd(RedSeSepHEAD*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedEntry::SetSeSepData(RedSeSepHEAD*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedEntry::ClearSeSepData(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedEntry::ClearSeSepDataMG(int, int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x801c20d8
 * PAL Size: 68b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int* CRedEntry::SearchSeSepBank(int seNo)
{
	int* seSepBank = (int*)*(int*)((int)this + 4);
	do {
		if (seSepBank[0] == seNo) {
			return seSepBank;
		}
		seSepBank += 4;
	} while ((unsigned int)seSepBank < (unsigned int)*(int*)((int)this + 4) + 0x1000);

	return 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedEntry::ReentrySeSepData(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedEntry::SeSepHistoryManager(int, int)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x801c22b4
 * PAL Size: 612b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedEntry::DisplaySePlayInfo()
{
	if (DAT_8032f408 != 0) {
		OSReport(&DAT_80333d4d);
		fflush(&DAT_8021d1a8);
		OSReport(s__s_____SE_Play_Information______801e7b71, &DAT_801e7905);
		fflush(&DAT_8021d1a8);
		OSReport(s__s_Track___Name___Wave_801e7b92, &DAT_801e7905);
		fflush(&DAT_8021d1a8);

		int* trackHead = (int*)((int)DAT_8032f3f0 + 0xdbc);
		int* track = (int*)*trackHead;
		do {
			int trackIndex = ((int)track - *trackHead) / 0x154 + (((int)track - *trackHead) >> 0x1F);
			if (track[0] == 0) {
				OSReport(s__s__2d_____801e7c01, &DAT_801e7905, (trackIndex - (trackIndex >> 0x1F)) + 0x20);
				fflush(&DAT_8021d1a8);
			} else if ((track[0x3D] & 0x80000000) == 0) {
				int* seSepBank = SearchSeSepBank(track[0x3D]);
				OSReport(s__s__2d___se_6_6u_sep___WAVE_4_4u_801e7bdc, &DAT_801e7905,
				         (trackIndex - (trackIndex >> 0x1F)) + 0x20, track[0x3D],
				         ((int)*(unsigned char*)(seSepBank[2] + 0x12) << 8) | *(unsigned char*)(seSepBank[2] + 0x11));
				fflush(&DAT_8021d1a8);
			} else {
				unsigned int seDataNo = (unsigned int)track[0x3D];
				int songNo = (int)(seDataNo & 0x7FFFFFFF) >> 9;
				int seqBase = ((int*)&DAT_8032e12c)[songNo] + 0x10;
				seqBase += *(short*)(((int*)&DAT_8032e12c)[songNo] + 10) * 4;
				seqBase += (*(unsigned int*)(seqBase + (seDataNo & 0x1FF) * 4) & 0x7FFFFFFF);

				OSReport(s__s__2d____3_3u__3_3u___WAVE_4_4u_801e7bb2, &DAT_801e7905,
				         (trackIndex - (trackIndex >> 0x1F)) + 0x20, songNo, seDataNo & 0x1FF,
				         ((int)*(unsigned char*)(seqBase + 2) << 8) | *(unsigned char*)(seqBase + 1));
				fflush(&DAT_8021d1a8);
			}
			track += 0x55;
		} while (track < (int*)(*trackHead + 0x2A80));

		OSReport(&DAT_80333d4f, &DAT_801e7905);
		fflush(&DAT_8021d1a8);
		OSReport(&DAT_80333d4d);
		fflush(&DAT_8021d1a8);
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedEntry::MusicHistoryAdd()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedEntry::MusicHistoryDelete(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedEntry::MusicHistoryChoice(RedHistoryBANK*)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x801c2610
 * PAL Size: 92b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedEntry::SearchMusicSequence(int musicNo)
{
	int* const base = reinterpret_cast<int*>(*reinterpret_cast<int*>(reinterpret_cast<int>(this) + 8));
	int* musicBank = base;

	while ((musicBank[3] == 0) || (musicBank[0] != musicNo)) {
		musicBank += 4;
		if (musicBank >= reinterpret_cast<int*>(reinterpret_cast<int>(base) + 0x40)) {
			return -1;
		}
	}

	int offset = reinterpret_cast<int>(musicBank) - reinterpret_cast<int>(base);
	return (offset >> 4) + ((offset < 0) && ((offset & 0xF) != 0));
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedEntry::MusicMemoryFree(RedHistoryBANK*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedEntry::MusicOldClear()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedEntry::MusicOldChoice()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x801c27d8
 * PAL Size: 68b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int* CRedEntry::SearchMusicBank(int musicNo)
{
	int* musicBank = reinterpret_cast<int*>(*reinterpret_cast<int*>(reinterpret_cast<int>(this) + 8));
	do {
		if (musicBank[0] == musicNo) {
			return musicBank;
		}
		musicBank += 4;
	} while (musicBank < reinterpret_cast<int*>(*reinterpret_cast<int*>(reinterpret_cast<int>(this) + 8) + 0x40));

	return 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedEntry::ReentryMusicData(int)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x801c2874
 * PAL Size: 324b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedEntry::MusicHistoryManager(int mode, int musicNo)
{
	if (mode == 0) {
		bool inUse = false;
		if ((*reinterpret_cast<short*>((int)DAT_8032f3f0 + 0x48E) != 0)
		    && (*reinterpret_cast<int*>((int)DAT_8032f3f0 + 0x470) == musicNo)) {
			inUse = true;
		}
		if ((*reinterpret_cast<short*>((int)DAT_8032f3f0 + 0x922) != 0)
		    && (*reinterpret_cast<int*>((int)DAT_8032f3f0 + 0x904) == musicNo)) {
			inUse = true;
		}

		int musicSeq = SearchMusicSequence(musicNo);
		if ((!inUse) && (musicSeq >= 0)) {
			int* const musicBank = reinterpret_cast<int*>(*reinterpret_cast<int*>(reinterpret_cast<int>(this) + 8));
			if (musicBank[musicSeq * 4 + 1] == 0) {
				MusicHistoryAdd();
				musicBank[musicSeq * 4 + 1] = 1;
			}
		}
	} else {
		int musicSeq = SearchMusicSequence(musicNo);
		if (musicSeq >= 0) {
			int* const musicBank = reinterpret_cast<int*>(*reinterpret_cast<int*>(reinterpret_cast<int>(this) + 8));
			if (musicBank[musicSeq * 4 + 1] != 0) {
				MusicHistoryDelete(musicBank[musicSeq * 4 + 1]);
				musicBank[musicSeq * 4 + 1] = 0;
			}
		}
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedEntry::MusicHeadAdd(RedMusicHEAD*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedEntry::SetMusicData(RedMusicHEAD*)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x801c2b70
 * PAL Size: 1108b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedEntry::DisplayMMemoryInfo()
{
	int i;
	int entryCount;
	int totalSize;
	int maxFreeSize;
	int bufferTop;
	int nextAddress;
	int freeSize;
	int* memoryBank;
	int* bankEntry;
	unsigned int history;
	int* seBlockBase;
	int* entry = (int*)this;

	if (DAT_8032f408 == 0) {
		return;
	}

	OSReport(&DAT_80333d4d);
	fflush(&DAT_8021d1a8);
	OSReport(s__s_____MMemory_Information______801e7cce, &DAT_801e7905);
	fflush(&DAT_8021d1a8);
	OSReport(s__s_Name___Start___Size___Free_801e7cef, &DAT_801e7905);
	fflush(&DAT_8021d1a8);

	maxFreeSize = 0;
	totalSize = 0;
	entryCount = 0;
	nextAddress = DAT_8032f480.GetMainBufferAddress();
	memoryBank = DAT_8032f480.GetMainBankAddress();
	bufferTop = nextAddress + DAT_8032f480.GetMainBufferSize();
	bankEntry = memoryBank;
	seBlockBase = &DAT_8032e12c;

	do {
		if (bankEntry[1] != 0) {
			int matched = 0;

			if (bankEntry[3] < 1) {
				freeSize = bufferTop - (bankEntry[0] + bankEntry[1]);
			} else {
				freeSize = bankEntry[2] - (bankEntry[0] + bankEntry[1]);
			}

			history = (unsigned int)entry[2];
			do {
				if ((*(int*)(history + 0xC) != 0) && (*(int*)(history + 8) == bankEntry[0])) {
					OSReport(s__s_MUSIC_3_3d___0x_8_8X___0x_8_8_801e7d24, &DAT_801e7905,
					         (int)*(short*)(bankEntry[0] + 4), bankEntry[0], bankEntry[1], freeSize);
					fflush(&DAT_8021d1a8);
					matched = 1;
					break;
				}
				history += 0x10;
			} while (history < (unsigned int)entry[2] + 0x40);

			if (matched == 0) {
				i = 0;
				do {
					if ((seBlockBase[i] != 0) && (bankEntry[0] == seBlockBase[i])) {
						OSReport(s__s_SE_BLOCK___0x_8_8X___0x_8_8X___801e7d51, &DAT_801e7905, bankEntry[0],
						         bankEntry[1], freeSize);
						fflush(&DAT_8021d1a8);
						matched = 1;
						break;
					}
					i++;
				} while (i < 4);
			}

			if (matched == 0) {
				history = (unsigned int)entry[0];
				do {
					if ((*(int*)(history + 0xC) != 0) && (*(int*)(history + 8) == bankEntry[0])) {
						OSReport(s__s_WAVE_4_4d___0x_8_8X___0x_8_8X_801e7d7c, &DAT_801e7905,
						         (int)*(short*)(bankEntry[0] + 2), bankEntry[0], bankEntry[1], freeSize);
						fflush(&DAT_8021d1a8);
						matched = 1;
						break;
					}
					history += 0x10;
				} while (history < (unsigned int)entry[0] + 0x400);
			}

			if (matched == 0) {
				history = (unsigned int)entry[1];
				do {
					if ((*(int*)(history + 0xC) != 0) && (*(int*)(history + 8) == bankEntry[0])) {
						OSReport(s__s_SE_6_6d___0x_8_8X___0x_8_8X___801e7da8, &DAT_801e7905,
						         *(int*)(bankEntry[0] + 8), bankEntry[0], bankEntry[1], freeSize);
						fflush(&DAT_8021d1a8);
						matched = 1;
						break;
					}
					history += 0x10;
				} while (history < (unsigned int)entry[1] + 0x1000);
			}

			if (matched == 0) {
				OSReport(s__s____________0x_8_8X___0x_8_8X___801e7dd2, &DAT_801e7905, bankEntry[0], bankEntry[1],
				         freeSize);
				fflush(&DAT_8021d1a8);
			}

			if (maxFreeSize < (bankEntry[0] - nextAddress)) {
				maxFreeSize = bankEntry[0] - nextAddress;
			}

			entryCount++;
			totalSize += bankEntry[1];
			nextAddress = bankEntry[0] + bankEntry[1];
		}

		bankEntry += 2;
	} while (bankEntry < memoryBank + 0x800);

	freeSize = (DAT_8032f480.GetMainBufferAddress() + DAT_8032f480.GetMainBufferSize()) - nextAddress;
	if (maxFreeSize < freeSize) {
		maxFreeSize = freeSize;
	}

	OSReport(&DAT_80333d4f, &DAT_801e7905);
	fflush(&DAT_8021d1a8);
	OSReport(s__s_Entry_Items____d_801e7dfd, &DAT_801e7905, entryCount);
	fflush(&DAT_8021d1a8);
	OSReport(s__s_Total_Size___0x_8_8X_801e7b18, &DAT_801e7905, totalSize);
	fflush(&DAT_8021d1a8);
	OSReport(s__s_Max_Free_Size___0x_8_8X_801e7b34, &DAT_801e7905, maxFreeSize);
	fflush(&DAT_8021d1a8);
	OSReport(&DAT_80333d4f, &DAT_801e7905);
	fflush(&DAT_8021d1a8);
	OSReport(&DAT_80333d4d);
	fflush(&DAT_8021d1a8);
}
