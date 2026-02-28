#include "ffcc/RedSound/RedEntry.h"
#include "ffcc/RedSound/RedMemory.h"
#include <dolphin/os.h>
#include <string.h>

extern CRedMemory DAT_8032f480;
extern int DAT_8032f408;
extern int DAT_8032e12c;
extern int DAT_8021d1a8;
extern char DAT_801e7905;
extern char DAT_80333d30;
extern char DAT_80333d38;
extern char DAT_80333d3d;
extern char DAT_80333d4d;
extern char DAT_80333d4f;
extern char s__s_sNOT_HAVE_A_MEMORY_FREE_AREA___801e7991[];
extern char s__s_sWave_Header_was_broken__s_801e7972[];
extern char s__s_____AMemory_Information______801e79ed[];
extern char s__s_Bank___Name___Start___Size___F_801e7a0e[];
extern char s__s__2d___WAVE_4_4d___0x_8_8X___0_801e7a53[];
extern char s__s______WAVE_4_4d___0x_8_8X___0x_801e7a8f[];
extern char s__s______________0x_8_8X___0x_8_8_801e7aca[];
extern char s__s_Entry_Wave____d_801e7b01[];
extern char s__s_Total_Size___0x_8_8X_801e7b18[];
extern char s__s_Max_Free_Size___0x_8_8X_801e7b34[];
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
 * Address:	TODO
 * Size:	TODO
 */
void CRedEntry::WaveHistoryAdd(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedEntry::WaveHistoryDelete(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedEntry::WaveHistoryChoice(RedHistoryBANK*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedEntry::SearchWaveSequence(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedEntry::SearchUseWave(int)
{
	// TODO
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
void CRedEntry::SetWaveData(int, void*, int)
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CRedEntry::WaveHistoryManager(int, int)
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CRedEntry::SeSepHistoryAdd()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedEntry::SeSepHistoryDelete(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedEntry::SeSepHistoryChoice(RedHistoryBANK*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedEntry::SearchSeSepSequence(int)
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CRedEntry::SearchSeSepBank(int)
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CRedEntry::DisplaySePlayInfo()
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CRedEntry::SearchMusicSequence(int)
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CRedEntry::SearchMusicBank(int)
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CRedEntry::MusicHistoryManager(int, int)
{
	// TODO
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
