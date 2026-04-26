#include "ffcc/RedSound/RedEntry.h"
#include "ffcc/RedSound/RedCommand.h"
#include "ffcc/RedSound/RedDriver.h"
#include "ffcc/RedSound/RedGlobals.h"
#include "ffcc/RedSound/RedMemory.h"
#include <dolphin/os.h>
#include <string.h>

static const char sRedEntryLogBlob[0x540] =
    "%s%s                                     %s\n\0"
    "\x1B[7;34mSound\x1B[0m:\0"
    "%s%s ********       ERROR       ******** %s\n\0"
    "%s%s Erase Using Wave Data !! (WAVE%4.4d) %s\n\0"
    "%s%sWave-Header was broken.%s\n\0"
    "%s%sNOT HAVE A-MEMORY FREE AREA (WAVE%4.4u:0x%6.6X need).%s\n\0"
    "%s%sWave Entry. (wave%4.4u)%s\n\0"
    "%s==== AMemory Information ====\n\0"
    "%s Bank : Name     : Start      : Size       : Free       : History\n\0"
    "%s  %2d  : WAVE%4.4d : 0x%8.8X : 0x%8.8X : 0x%8.8X :   %3d\n\0"
    "%s  --  : WAVE%4.4d : 0x%8.8X : 0x%8.8X : 0x%8.8X :   %3d\n\0"
    "%s      : -------- : 0x%8.8X : 0x%8.8X : 0x%8.8X : %d\n\0"
    "%s    Entry Wave = %d\n\0"
    "%s    Total Size = 0x%8.8X\n\0"
    "%s Max Free Size = 0x%8.8X\n\0"
    "%s%sSE-Sep-Header was broken.%s\n\0"
    "%s==== SE Play Information ====\n\0"
    "%s Track : Name         : Wave\n\0"
    "%s    %2d : %3.3u:%3.3u      : WAVE%4.4u\n\0"
    "%s    %2d : se%6.6u.sep : WAVE%4.4u\n\0"
    "%s    %2d :              :\n\0"
    "%s%sMusic-Header was broken.%s\n\0"
    "%s==== MUSIC Information ====\n\0"
    "%s BGM      : Wave : Size     : \n\0"
    "%s music%3.3u : %4.4u : 0x%6.6X : Play\n\0"
    "%s music%3.3u : %4.4u : 0x%6.6X : Stop\n\0"
    "%s==== MMemory Information ====\n\0"
    "%s Name     : Start      : Size       : Free       \n\0"
    "%s MUSIC%3.3d : 0x%8.8X : 0x%8.8X : 0x%8.8X\n\0"
    "%s SE-BLOCK : 0x%8.8X : 0x%8.8X : 0x%8.8X\n\0"
    "%s WAVE%4.4d : 0x%8.8X : 0x%8.8X : 0x%8.8X\n\0"
    "%s SE%6.6d : 0x%8.8X : 0x%8.8X : 0x%8.8X\n\0"
    "%s -------- : 0x%8.8X : 0x%8.8X : 0x%8.8X\n\0"
    "%s   Entry Items = %d\n";
#define sRedEntryColoredBlankLineFmt (sRedEntryLogBlob + 0x000)
#define sRedEntryLogPrefix (sRedEntryLogBlob + 0x02D)
#define s__s_s__________ERROR___________s_801e7917 (sRedEntryLogBlob + 0x03F)
#define s__s_s_Erase_Using_Wave_Data_____W_801e7944 (sRedEntryLogBlob + 0x06C)
#define s__s_sWave_Header_was_broken__s_801e7972 (sRedEntryLogBlob + 0x09A)
#define s__s_sNOT_HAVE_A_MEMORY_FREE_AREA___801e7991 (sRedEntryLogBlob + 0x0B9)
#define s__s_sWave_Entry___wave_4_4u__s_801e79ce (sRedEntryLogBlob + 0x0F6)
#define s__s_____AMemory_Information______801e79ed (sRedEntryLogBlob + 0x115)
#define s__s_Bank___Name___Start___Size___F_801e7a0e (sRedEntryLogBlob + 0x136)
#define s__s__2d___WAVE_4_4d___0x_8_8X___0_801e7a53 (sRedEntryLogBlob + 0x17B)
#define s__s______WAVE_4_4d___0x_8_8X___0x_801e7a8f (sRedEntryLogBlob + 0x1B7)
#define s__s______________0x_8_8X___0x_8_8_801e7aca (sRedEntryLogBlob + 0x1F2)
#define s__s_Entry_Wave____d_801e7b01 (sRedEntryLogBlob + 0x229)
#define s__s_Total_Size___0x_8_8X_801e7b18 (sRedEntryLogBlob + 0x240)
#define s__s_Max_Free_Size___0x_8_8X_801e7b34 (sRedEntryLogBlob + 0x25C)
#define s__s_sSE_Sep_Header_was_broken__s_801e7b50 (sRedEntryLogBlob + 0x278)
#define s__s_____SE_Play_Information______801e7b71 (sRedEntryLogBlob + 0x299)
#define s__s_Track___Name___Wave_801e7b92 (sRedEntryLogBlob + 0x2BA)
#define s__s__2d____3_3u__3_3u___WAVE_4_4u_801e7bb2 (sRedEntryLogBlob + 0x2DA)
#define s__s__2d___se_6_6u_sep___WAVE_4_4u_801e7bdc (sRedEntryLogBlob + 0x304)
#define s__s__2d_____801e7c01 (sRedEntryLogBlob + 0x329)
#define s__s_sMusic_Header_was_broken__s_801e7c1d (sRedEntryLogBlob + 0x345)
#define s__s_____MMemory_Information______801e7cce (sRedEntryLogBlob + 0x3F6)
#define s__s_Name___Start___Size___Free_801e7cef (sRedEntryLogBlob + 0x417)
#define s__s_MUSIC_3_3d___0x_8_8X___0x_8_8_801e7d24 (sRedEntryLogBlob + 0x44C)
#define s__s_SE_BLOCK___0x_8_8X___0x_8_8X___801e7d51 (sRedEntryLogBlob + 0x479)
#define s__s_WAVE_4_4d___0x_8_8X___0x_8_8X_801e7d7c (sRedEntryLogBlob + 0x4A4)
#define s__s_SE_6_6d___0x_8_8X___0x_8_8X___801e7da8 (sRedEntryLogBlob + 0x4D0)
#define s__s____________0x_8_8X___0x_8_8X___801e7dd2 (sRedEntryLogBlob + 0x4FA)
#define s__s_Entry_Items____d_801e7dfd (sRedEntryLogBlob + 0x525)
static const char sRedEntryErrorColor[] = "\x1B[7;31m";
static const char sRedEntryResetColor[] = "\x1B[0m";
static const char sRedEntryHeaderErrorColor[] = "\x1B[4;31m";
static const char sRedEntryInfoColor[] = "\x1B[4;34m";
static const char sRedEntryNewline[] = "\n";
static const char sRedEntryPrefixedNewlineFmt[] = "%s\n";

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

	iVar2 = RedNew(0x400);
	entry[0] = iVar2;
	iVar2 = RedNew(0x1000);
	entry[1] = iVar2;
	iVar2 = RedNew(0x40);
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
	int* waveBank = (int*)entry[0];
	int* end = (int*)(entry[0] + 0x400);

	do {
		if ((waveBank[3] != 0) && (*waveBank == waveNo)) {
			int offset = (int)waveBank - entry[0];
			return offset / 0x10;
		}
		waveBank += 4;
	} while (waveBank < end);

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
	int soundBase = (int)p_SoundControlBuffer + 0x494;

	do {
		if ((*(int*)(soundBase + 0x470) >= 0) && (*(int*)(soundBase + 0x47c) == waveNo)) {
			found = 1;
			MusicStop(*(int*)(soundBase + 0x470));
		}
		soundBase -= 0x494;
	} while ((int)p_SoundControlBuffer <= soundBase);

	int* trackBasePtr = (int*)((char*)p_SoundControlBuffer + 0xdbc);
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
 * PAL Address: 0x801c0970
 * PAL Size: 356b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedEntry::WaveDelete(RedHistoryBANK* bank)
{
	int iVar1;
	int iVar2;
	int sequenceNo = -1;
	int* bankEntry = reinterpret_cast<int*>(bank);

	if (-1 < bankEntry[0]) {
		WaveHistoryDelete(bankEntry[1]);
		iVar2 = bankEntry[0];

		bankEntry[0] = -1;
		bankEntry[3] = 0;

		sequenceNo = SearchWaveSequence(iVar2);
		if (sequenceNo < 0) {
			iVar1 = SearchUseWave(iVar2);
			if ((iVar1 != 0) && (m_ReportPrint != 0)) {
				OSReport(sRedEntryColoredBlankLineFmt, sRedEntryLogPrefix, sRedEntryErrorColor, sRedEntryResetColor);
				fflush(__files + 1);
				OSReport(s__s_s__________ERROR___________s_801e7917, sRedEntryLogPrefix, sRedEntryErrorColor, sRedEntryResetColor);
				fflush(__files + 1);
				OSReport(s__s_s_Erase_Using_Wave_Data_____W_801e7944, sRedEntryLogPrefix, sRedEntryErrorColor, iVar2,
				         sRedEntryResetColor);
				fflush(__files + 1);
				OSReport(sRedEntryColoredBlankLineFmt, sRedEntryLogPrefix, sRedEntryErrorColor, sRedEntryResetColor);
				fflush(__files + 1);
			}
			RedDeleteA(*reinterpret_cast<int*>(bankEntry[2] + 0x10));
			RedDelete(bankEntry[2]);
		}

		bankEntry[2] = 0;
		bankEntry[1] = 0;
	}

	return sequenceNo;
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
    int aBase = c_RedMemory.GetABufferAddress();
	offset += aBase;
	maxSize += aBase;
	unsigned int history = (unsigned int)entry[0] + 0x100;

	do {
		int bankSize = *(int*)(history + 4);
		if (maxBankSize < bankSize) {
			int arAddress = *(int*)(*(int*)(history + 8) + 0x10);
			if ((offset <= arAddress) && (arAddress < maxSize)) {
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

	if ((head[0] != 'W') || (head[1] != 'D')) {
		if (m_ReportPrint != 0) {
			OSReport(s__s_sWave_Header_was_broken__s_801e7972, sRedEntryLogPrefix, sRedEntryHeaderErrorColor, sRedEntryResetColor);
			fflush(__files + 1);
		}

		return -1;
	}

	if (*(int*)(head + 0x14) < *(int*)(head + 4)) {
		*(int*)(head + 0x14) = *(int*)(head + 4);
	}

	if ((waveNo >= 100) && (waveNo < 300)) {
		if (*(int*)(head + 0x14) <= 0x200000) {
			*(int*)(head + 0x14) = 0x200000;
		} else if (*(int*)(head + 0x14) <= 0x400000) {
			*(int*)(head + 0x14) = 0x400000;
		}
	} else if ((waveNo >= 10) && (waveNo < 70)) {
		*(int*)(head + 0x14) += 0x27FFF;
		int blocks = *(int*)(head + 0x14) / 0x28000 + (*(int*)(head + 0x14) >> 0x1F);
		blocks = blocks - (blocks >> 0x1F);
		*(int*)(head + 0x14) = blocks * 0x28000;
	} else if (((waveNo >= 0x154) && (waveNo < 0x17a)) || ((waveNo >= 0x17f) && (waveNo < 0x182)) ||
	           (waveNo == 0x183)) {
		*(int*)(head + 0x14) = 0x100000;
	}

	int minOffset;
	int maxOffset;
	if ((waveNo >= 100) && (waveNo < 300)) {
		minOffset = 0x400000;
		maxOffset = 0x800000;
	} else if (((waveNo >= 0x154) && (waveNo < 0x17a)) || ((waveNo >= 0x17f) && (waveNo < 0x182)) ||
	           (waveNo == 0x183)) {
		minOffset = 0x300000;
		maxOffset = 0x400000;
	} else {
		minOffset = 0;
		maxOffset = 0x300000;
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
			void* copied = (void*)RedNew(copySize);
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
			RedDeleteA((void*)arAddress);
		}
	} while (WaveOldClear(minOffset, maxOffset) != 0);

	if (m_ReportPrint != 0) {
		OSReport(s__s_sNOT_HAVE_A_MEMORY_FREE_AREA___801e7991, sRedEntryLogPrefix, sRedEntryErrorColor, (int)*(short*)(head + 2),
		         *(int*)(head + 4), sRedEntryResetColor);
		fflush(__files + 1);
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
	int waveSize;
	void* waveDataTop;

	if (waveDataSize == 0) {
		if ((entry[3] >= 0) && ((waveNo = SearchWaveSequence(entry[3])) >= 0)) {
			WaveDelete((RedHistoryBANK*)(entry[0] + waveNo * 0x10));
		}

		entry[3] = -1;
		return -1;
	}

	waveAddress = 0;
	if (entry[3] < 0) {
		RedWaveHeadWD* waveHead = (RedWaveHeadWD*)waveData;
		waveNo = *(short*)((unsigned char*)waveHead + 2);

		if ((waveBankNo >= 0) && (waveNo != *(int*)(entry[0] + waveBankNo * 0x10))) {
			WaveDelete((RedHistoryBANK*)(entry[0] + waveBankNo * 0x10));
		}

		int historyNo = SearchWaveSequence(waveNo);
		if (historyNo >= 0) {
			if ((waveBankNo >= 0) && (historyNo != waveBankNo)) {
				*(int*)(entry[0] + waveBankNo * 0x10 + 0x0) = *(int*)(entry[0] + historyNo * 0x10 + 0x0);
				*(int*)(entry[0] + waveBankNo * 0x10 + 0x4) = *(int*)(entry[0] + historyNo * 0x10 + 0x4);
				*(int*)(entry[0] + waveBankNo * 0x10 + 0x8) = *(int*)(entry[0] + historyNo * 0x10 + 0x8);
				*(int*)(entry[0] + waveBankNo * 0x10 + 0xC) = *(int*)(entry[0] + historyNo * 0x10 + 0xC);
				historyNo = waveBankNo;
			}

			WaveHistoryChoice((RedHistoryBANK*)(entry[0] + historyNo * 0x10));
		} else {
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
			waveSize = *(int*)((unsigned char*)waveHead + 4);
			waveDataSize -= waveHeadSize;
			waveDataTop = (void*)((unsigned char*)waveData + waveHeadSize);
		}
	} else {
		waveAddress = entry[5];
		waveDataTop = waveData;
		waveSize = entry[4];
	}

	if ((waveAddress != 0) && (waveDataSize > 0)) {
		int transferSize;
		if (waveSize > waveDataSize) {
			transferSize = waveDataSize;
		} else {
			transferSize = waveSize;
		}

		int dmaID = RedDmaEntry(0x8000, 0, (int)waveDataTop, waveAddress, transferSize, 0, 0);
		waveSize -= transferSize;
		waveAddress += transferSize;
		entry[4] = waveSize;
		entry[5] = waveAddress;

		while (RedDmaSearchID(dmaID) > 0) {
			RedSleep(1000);
		}

		if (entry[4] < 1) {
			if (m_ReportPrint != 0) {
				OSReport(s__s_sWave_Entry___wave_4_4u__s_801e79ce, sRedEntryLogPrefix, sRedEntryInfoColor, entry[3], sRedEntryResetColor);
				fflush(__files + 1);
			}

			entry[3] = -1;
			return 0;
		}
	}

	return entry[3];
}

/*
 * --INFO--
 * PAL Address: 0x801c1190
 * PAL Size: 316b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedEntry::ClearWaveData(int waveNo)
{
	int historyNo;
	int* historyBank;
	int* entry = (int*)this;

	if (waveNo < 0) {
		if (waveNo == -1) {
			for (historyBank = (int*)entry[0]; historyBank < (int*)(entry[0] + 0x400); historyBank += 4) {
				if (historyBank[0] >= 0) {
					WaveDelete((RedHistoryBANK*)historyBank);
				}
			}
		} else if (waveNo == -2) {
			for (historyBank = (int*)(entry[0] + 0x100); historyBank < (int*)(entry[0] + 0x400); historyBank += 4) {
				if (historyBank[0] >= 0) {
					WaveDelete((RedHistoryBANK*)historyBank);
				}
			}
		} else if (waveNo == -3) {
			for (historyBank = (int*)(entry[0] + 0x100); historyBank < (int*)(entry[0] + 0x400); historyBank += 4) {
				if ((historyBank[0] >= 0) && (0 < historyBank[1])) {
					WaveDelete((RedHistoryBANK*)historyBank);
				}
			}
		}
	} else {
		historyNo = SearchWaveSequence(waveNo);
		if (historyNo >= 0) {
			WaveDelete((RedHistoryBANK*)(entry[0] + historyNo * 0x10));
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x801c12cc
 * PAL Size: 204b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedEntry::ClearWaveDataM(int waveNo0, int waveNo1, int waveNo2, int waveNo3)
{
	int* entry = (int*)this;
	int* historyBank;

	if (((waveNo0 == -1) && (waveNo1 == -1) && (waveNo2 == -1)) && (waveNo3 == -1)) {
		return;
	}

	for (historyBank = (int*)(entry[0] + 0x100); historyBank < (int*)(entry[0] + 0x400); historyBank += 4) {
		if (((historyBank[0] >= 0) && (0 < historyBank[1])) &&
		    (historyBank[0] != waveNo0) && (historyBank[0] != waveNo1) &&
		    (historyBank[0] != waveNo2) && (historyBank[0] != waveNo3)) {
			WaveDelete((RedHistoryBANK*)historyBank);
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x801c1398
 * PAL Size: 312b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedEntry::ClearWaveBank(int waveBankNo)
{
	int* const entry = (int*)this;

	if (waveBankNo < 0) {
		if (waveBankNo == -1) {
			for (int* historyBank = (int*)entry[0]; historyBank < (int*)(entry[0] + 0x400); historyBank += 4) {
				if (!(historyBank[0] < 0)) {
					WaveDelete((RedHistoryBANK*)historyBank);
				}
			}
		} else if (waveBankNo == -2) {
			for (int* historyBank = (int*)(entry[0] + 0x100); historyBank < (int*)(entry[0] + 0x400); historyBank += 4) {
				if (!(historyBank[0] < 0)) {
					WaveDelete((RedHistoryBANK*)historyBank);
				}
			}
		} else if (waveBankNo == -3) {
			for (int* historyBank = (int*)(entry[0] + 0x100); historyBank < (int*)(entry[0] + 0x400); historyBank += 4) {
				if (!(historyBank[0] < 0) && (0 < historyBank[1])) {
					WaveDelete((RedHistoryBANK*)historyBank);
				}
			}
		}
	} else if (waveBankNo < 0x10) {
		WaveDelete((RedHistoryBANK*)(entry[0] + waveBankNo * 0x10));
	}
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
	if ((waveNo >= 0) && (waveNo < 0x10))
	{
		return m_waveBankBase + (waveNo * 0x10);
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
	int* waveBase = (int*)*(int*)this;
	int* waveBank = waveBase;
	int* waveBankEnd = waveBase + 0x100;

	do {
		if (waveNo == *waveBank) {
			return waveBank[2];
		}
		waveBank += 4;
	} while (waveBank < waveBankEnd);

	return 0;
}

/*
 * --INFO--
 * PAL Address: 0x801c153c
 * PAL Size: 88b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedEntry::ReentryWaveData(int waveNo)
{
	waveNo = SearchWaveSequence(waveNo);
	if (waveNo >= 0) {
		WaveHistoryChoice((RedHistoryBANK*)(((int*)this)[0] + waveNo * 0x10));
	}
	return waveNo;
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
	int used;
	int seq;
	int* track;

	if (mode == 0) {
		used = 0;
		if ((*(short*)((char*)p_SoundControlBuffer + 0x48e) != 0) && (*(int*)((char*)p_SoundControlBuffer + 0x47c) == waveNo)) {
			used |= 1;
		}
		if ((*(short*)((char*)p_SoundControlBuffer + 0x922) != 0) && (*(int*)((char*)p_SoundControlBuffer + 0x910) == waveNo)) {
			used |= 1;
		}
		if (used == 0) {
			track = *(int**)((char*)p_SoundControlBuffer + 0xdbc);
			do {
				if (((*track != 0) && (track[6] != 0)) && (*(short*)(track[6] + 2) == waveNo)) {
					used++;
					break;
				}
				track += 0x55;
			} while (track < (int*)(*(int*)((char*)p_SoundControlBuffer + 0xdbc) + 0x2a80));
		}
		if (used == 0) {
			seq = SearchWaveSequence(waveNo);
			if ((seq >= 0x10) && (*(int*)(*(int*)this + seq * 0x10 + 4) == 0)) {
				WaveHistoryAdd(0x14);
				*(int*)(*(int*)this + seq * 0x10 + 4) = 0x14;
			}
		}
	} else {
		seq = SearchWaveSequence(waveNo);
		if ((seq >= 0x10) && (*(int*)(*(int*)this + seq * 0x10 + 4) != 0)) {
			WaveHistoryDelete(*(int*)(*(int*)this + seq * 0x10 + 4));
			*(int*)(*(int*)this + seq * 0x10 + 4) = 0;
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

	if (m_ReportPrint != 0) {
		OSReport(sRedEntryNewline);
		fflush(__files + 1);
		OSReport(s__s_____AMemory_Information______801e79ed, sRedEntryLogPrefix);
		fflush(__files + 1);
		OSReport(s__s_Bank___Name___Start___Size___F_801e7a0e, sRedEntryLogPrefix);
		fflush(__files + 1);

		int maxFreeSize = 0;
		int totalSize = 0;
		int entryWave = 0;
        int aBufferAddress = c_RedMemory.GetABufferAddress();
        int* aBankAddress = (int*)c_RedMemory.GetABankAddress();
        int aBufferEnd = aBufferAddress + c_RedMemory.GetABufferSize();

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
						OSReport(s__s__2d___WAVE_4_4d___0x_8_8X___0_801e7a53, sRedEntryLogPrefix, (int)(index >> 4),
						         (int)*(short*)(*(int*)(history + 8) + 2), *(int*)(*(int*)(history + 8) + 0x10), bank[1],
						         freeSize, *(int*)(history + 4));
						fflush(__files + 1);
					} else {
						OSReport(s__s______WAVE_4_4d___0x_8_8X___0x_801e7a8f, sRedEntryLogPrefix,
						         (int)*(short*)(*(int*)(history + 8) + 2), *(int*)(*(int*)(history + 8) + 0x10), bank[1],
						         freeSize, *(int*)(history + 4));
						fflush(__files + 1);
					}
					entryWave += 1;
				} else {
					unsigned int bankIndex = (unsigned int)((int)bank - (int)aBankAddress);
					OSReport(s__s______________0x_8_8X___0x_8_8_801e7aca, sRedEntryLogPrefix, bank[0], bank[1], freeSize,
					         (int)(bankIndex >> 3));
					fflush(__files + 1);
				}

				if (maxFreeSize < bank[0] - aBufferAddress) {
					maxFreeSize = bank[0] - aBufferAddress;
				}
				totalSize += bank[1];
				aBufferAddress = bank[0] + bank[1];
			}
			bank += 2;
		} while (bank < aBankAddress + 0x800);

        int aBase = c_RedMemory.GetABufferAddress();
        int aSize = c_RedMemory.GetABufferSize();
		if (maxFreeSize < (aBase + aSize) - aBufferAddress) {
            maxFreeSize = (aBase + c_RedMemory.GetABufferSize()) - aBufferAddress;
		}

		OSReport(sRedEntryPrefixedNewlineFmt, sRedEntryLogPrefix);
		fflush(__files + 1);
		OSReport(s__s_Entry_Wave____d_801e7b01, sRedEntryLogPrefix, entryWave);
		fflush(__files + 1);
		OSReport(s__s_Total_Size___0x_8_8X_801e7b18, sRedEntryLogPrefix, totalSize);
		fflush(__files + 1);
		OSReport(s__s_Max_Free_Size___0x_8_8X_801e7b34, sRedEntryLogPrefix, maxFreeSize);
		fflush(__files + 1);
		OSReport(sRedEntryPrefixedNewlineFmt, sRedEntryLogPrefix);
		fflush(__files + 1);
		OSReport(sRedEntryNewline);
		fflush(__files + 1);
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
	unsigned int offset;
	int* seSepBank = *(int**)((int)this + 4);

	if (seNo == -1) {
		do {
			if (seSepBank[3] != 0) {
				offset = (int)seSepBank - *(int*)((int)this + 4);
				return (int)offset / 0x10;
			}
			seSepBank += 4;
		} while (seSepBank < (int*)(*(int*)((int)this + 4) + 0x1000));
	} else {
		do {
			if ((seSepBank[3] != 0) && (seSepBank[0] == seNo)) {
				offset = (int)seSepBank - *(int*)((int)this + 4);
				return (int)offset / 0x10;
			}
			seSepBank += 4;
		} while (seSepBank < (int*)(*(int*)((int)this + 4) + 0x1000));
	}

	return -1;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CRedEntry::SeSepMemoryFree(RedHistoryBANK* bank)
{
	int* bankData = reinterpret_cast<int*>(bank);
	int waveNo = static_cast<unsigned int>(*reinterpret_cast<unsigned char*>(bankData[2] + 0x11)) +
	             static_cast<unsigned int>(*reinterpret_cast<unsigned char*>(bankData[2] + 0x12)) * 0x100;

	RedDelete(bankData[2]);
	SeSepHistoryDelete(bankData[1]);

	int freedSize = bankData[3];
	bankData[3] = 0;
	bankData[2] = 0;
	bankData[0] = -1;

	WaveHistoryManager(0, waveNo);
	return freedSize;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
unsigned int CRedEntry::SeSepOldDelete()
{
	int historyNo = 0;
	unsigned int selected = 0;
	unsigned int history = *reinterpret_cast<unsigned int*>(reinterpret_cast<int>(this) + 4);

	do {
		if ((*reinterpret_cast<int*>(history + 0xC) != 0) && (historyNo < *reinterpret_cast<int*>(history + 4))) {
			historyNo = *reinterpret_cast<int*>(history + 4);
			selected = history;
		}
		history += 0x10;
	} while (history < *reinterpret_cast<unsigned int*>(reinterpret_cast<int>(this) + 4) + 0x1000);

	if (selected != 0) {
		SeSepMemoryFree(reinterpret_cast<RedHistoryBANK*>(selected));
	}

	return selected;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CRedEntry::SeSepHeadAdd(RedSeSepHEAD* seSepHead)
{
	unsigned int base = *reinterpret_cast<unsigned int*>(reinterpret_cast<int>(this) + 4);
	int* bank = reinterpret_cast<int*>(base);

	while ((bank[3] != 0) && (reinterpret_cast<unsigned int>(bank) < base + 0x1000)) {
		bank += 4;
	}
	if (base + 0x1000 <= reinterpret_cast<unsigned int>(bank)) {
		bank = reinterpret_cast<int*>(SeSepOldDelete());
	}

	int result = 0;
	if ((bank != 0) && (reinterpret_cast<unsigned int>(bank) < base + 0x1000)) {
		bank[2] = reinterpret_cast<int>(seSepHead);
		bank[3] = *reinterpret_cast<unsigned int*>(reinterpret_cast<int>(seSepHead) + 0xC) & 0x7FFFFFFF;
		bank[0] = *reinterpret_cast<int*>(reinterpret_cast<int>(seSepHead) + 8);
		SeSepHistoryAdd();
		bank[1] = 1;
		result = reinterpret_cast<int>(seSepHead);
	}

	return result;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CRedEntry::SetSeSepData(RedSeSepHEAD* seSepHead)
{
	int result;
	char* data = reinterpret_cast<char*>(seSepHead);

	if ((data[0] != 'S') || (data[1] != 'e') || (data[2] != 'S') || (data[3] != 'e') || (data[4] != 'p')) {
		RedDelete(seSepHead);
		if (m_ReportPrint != 0) {
			OSReport(s__s_sSE_Sep_Header_was_broken__s_801e7b50, sRedEntryLogPrefix, sRedEntryHeaderErrorColor, sRedEntryResetColor);
			fflush(__files + 1);
		}
		return 0;
	}

	result = SearchSeSepSequence(*reinterpret_cast<int*>(data + 8));
	if (result >= 0) {
		RedDelete(seSepHead);
		SeSepHistoryChoice(reinterpret_cast<RedHistoryBANK*>(*reinterpret_cast<int*>(reinterpret_cast<int>(this) + 4) +
		                                                   result * 0x10));
		result = *reinterpret_cast<int*>(*reinterpret_cast<int*>(reinterpret_cast<int>(this) + 4) + result * 0x10 + 8);
	} else {
		result = SeSepHeadAdd(seSepHead);
		if (result == 0) {
			RedDelete(seSepHead);
		}
	}

	return result;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CRedEntry::ClearSeSepData(int seNo)
{
	int result = 0;

	if (seNo == -1) {
		unsigned int history = *reinterpret_cast<unsigned int*>(reinterpret_cast<int>(this) + 4);
		do {
			if (*reinterpret_cast<int*>(history + 0xC) != 0) {
				SeSepMemoryFree(reinterpret_cast<RedHistoryBANK*>(history));
			}
			history += 0x10;
		} while (history < *reinterpret_cast<unsigned int*>(reinterpret_cast<int>(this) + 4) + 0x1000);
	} else {
		result = SearchSeSepSequence(seNo);
		if (result >= 0) {
			result = SeSepMemoryFree(reinterpret_cast<RedHistoryBANK*>(
			    *reinterpret_cast<int*>(reinterpret_cast<int>(this) + 4) + result * 0x10));
		}
	}

	return result;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CRedEntry::ClearSeSepDataMG(int bankNo, int sepNo, int groupNo, int kindNo)
{
	int* bank = reinterpret_cast<int*>(*reinterpret_cast<int*>(reinterpret_cast<int>(this) + 4));

	do {
		if (bank[3] != 0) {
			int seNo = bank[0] / 1000;
			if ((bankNo != seNo) && (sepNo != seNo) && (groupNo != seNo) && (kindNo != seNo)) {
				SeSepMemoryFree(reinterpret_cast<RedHistoryBANK*>(bank));
			}
		}
		bank += 4;
	} while (bank < reinterpret_cast<int*>(*reinterpret_cast<int*>(reinterpret_cast<int>(this) + 4) + 0x1000));

	return 0;
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
 * PAL Address: 0x801c211c
 * PAL Size: 88b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedEntry::ReentrySeSepData(int seNo)
{
	seNo = SearchSeSepSequence(seNo);
	if (seNo >= 0) {
		SeSepHistoryChoice((RedHistoryBANK*)(((int*)this)[1] + seNo * 0x10));
	}
	return seNo;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedEntry::SeSepHistoryManager(int mode, int seNo)
{
	if (mode == 0) {
		int inUse = 0;
		int* track = *(int**)((int)p_SoundControlBuffer + 0xdbc);

		do {
			if ((*track != 0) && (track[0x3D] == seNo)) {
				inUse |= 1;
				break;
			}
			track += 0x55;
		} while (track < (int*)(*(int*)((int)p_SoundControlBuffer + 0xdbc) + 0x2a80));

		if (inUse == 0) {
			int sequenceNo = SearchSeSepSequence(seNo);
			if ((sequenceNo >= 0) &&
			    (*reinterpret_cast<int*>(*reinterpret_cast<int*>((int)this + 4) + sequenceNo * 0x10 + 4) == 0)) {
				SeSepHistoryAdd();
				*reinterpret_cast<int*>(*reinterpret_cast<int*>((int)this + 4) + sequenceNo * 0x10 + 4) = 1;
			}
		}
	} else {
		int sequenceNo = SearchSeSepSequence(seNo);
		if (sequenceNo >= 0) {
			if (*reinterpret_cast<int*>(*reinterpret_cast<int*>((int)this + 4) + sequenceNo * 0x10 + 4) != 0) {
				SeSepHistoryDelete(*reinterpret_cast<int*>(*reinterpret_cast<int*>((int)this + 4) + sequenceNo * 0x10 + 4));
				*reinterpret_cast<int*>(*reinterpret_cast<int*>((int)this + 4) + sequenceNo * 0x10 + 4) = 0;
			}
		}
	}
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
	if (m_ReportPrint != 0) {
		OSReport(sRedEntryNewline);
		fflush(__files + 1);
		OSReport(s__s_____SE_Play_Information______801e7b71, sRedEntryLogPrefix);
		fflush(__files + 1);
		OSReport(s__s_Track___Name___Wave_801e7b92, sRedEntryLogPrefix);
		fflush(__files + 1);

		int* trackHead = (int*)((int)p_SoundControlBuffer + 0xdbc);
		int* track = (int*)*trackHead;
		do {
			int trackIndex = ((int)track - *trackHead) / 0x154 + (((int)track - *trackHead) >> 0x1F);
			if (track[0] == 0) {
				OSReport(s__s__2d_____801e7c01, sRedEntryLogPrefix, (trackIndex - (trackIndex >> 0x1F)) + 0x20);
				fflush(__files + 1);
			} else if ((track[0x3D] & 0x80000000) == 0) {
				int* seSepBank = SearchSeSepBank(track[0x3D]);
				OSReport(s__s__2d___se_6_6u_sep___WAVE_4_4u_801e7bdc, sRedEntryLogPrefix,
				         (trackIndex - (trackIndex >> 0x1F)) + 0x20, track[0x3D],
				         ((int)*(unsigned char*)(seSepBank[2] + 0x12) << 8) | *(unsigned char*)(seSepBank[2] + 0x11));
				fflush(__files + 1);
			} else {
				unsigned int seDataNo = (unsigned int)track[0x3D];
				int songNo = (int)(seDataNo & 0x7FFFFFFF) >> 9;
				int seqBase = ((int*)&p_SeBlockData)[songNo] + 0x10;
				seqBase += *(short*)(((int*)&p_SeBlockData)[songNo] + 10) * 4;
				seqBase += (*(unsigned int*)(seqBase + (seDataNo & 0x1FF) * 4) & 0x7FFFFFFF);

				OSReport(s__s__2d____3_3u__3_3u___WAVE_4_4u_801e7bb2, sRedEntryLogPrefix,
				         (trackIndex - (trackIndex >> 0x1F)) + 0x20, songNo, seDataNo & 0x1FF,
				         ((int)*(unsigned char*)(seqBase + 2) << 8) | *(unsigned char*)(seqBase + 1));
				fflush(__files + 1);
			}
			track += 0x55;
		} while (track < (int*)(*trackHead + 0x2A80));

		OSReport(sRedEntryPrefixedNewlineFmt, sRedEntryLogPrefix);
		fflush(__files + 1);
		OSReport(sRedEntryNewline);
		fflush(__files + 1);
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedEntry::MusicHistoryAdd()
{
	unsigned int history = static_cast<unsigned int>(*reinterpret_cast<int*>(reinterpret_cast<int>(this) + 8));

	do {
		if (*reinterpret_cast<int*>(history + 4) != 0) {
			*reinterpret_cast<int*>(history + 4) = *reinterpret_cast<int*>(history + 4) + 1;
		}
		history += 0x10;
	} while (history < static_cast<unsigned int>(*reinterpret_cast<int*>(reinterpret_cast<int>(this) + 8)) + 0x40);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedEntry::MusicHistoryDelete(int historyNo)
{
	if (historyNo != 0) {
		unsigned int history = (unsigned int)*(int*)((int)this + 8);
		do {
			if (historyNo < *(int*)(history + 4)) {
				*(int*)(history + 4) = *(int*)(history + 4) - 1;
			}
			history += 0x10;
		} while (history < (unsigned int)*(int*)((int)this + 8) + 0x40);
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedEntry::MusicHistoryChoice(RedHistoryBANK* bank)
{
	int* bankData = (int*)bank;
	if (bankData[1] != 0) {
		unsigned int history = (unsigned int)*(int*)((int)this + 8);
		do {
			if ((*(int*)(history + 4) != 0) && (*(int*)(history + 4) < bankData[1])) {
				*(int*)(history + 4) = *(int*)(history + 4) + 1;
			}
			history += 0x10;
		} while (history < (unsigned int)*(int*)((int)this + 8) + 0x40);
		bankData[1] = 1;
	}
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
	int* musicBank = *(int**)((int)this + 8);
	int* end = (int*)(*(int*)((int)this + 8) + 0x40);

	do {
		if ((musicBank[3] != 0) && (*musicBank == musicNo)) {
			int offset = (int)musicBank - *(int*)((int)this + 8);
			return offset / 0x10;
		}
		musicBank += 4;
	} while (musicBank < end);

	return -1;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CRedEntry::MusicMemoryFree(RedHistoryBANK* bank)
{
	int* bankData = (int*)bank;

	WaveHistoryManager(0, (int)*(short*)(bankData[2] + 6));
	RedDelete(bankData[2]);
	int freedSize = bankData[3];
	bankData[3] = 0;
	bankData[2] = 0;
	bankData[1] = 0;
	bankData[0] = -1;
	return freedSize;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CRedEntry::MusicOldClear()
{
	int historyNo = 0;
	unsigned int selected = 0;
	unsigned int history = (unsigned int)*(int*)((int)this + 8);

	do {
		if (*(int*)(history + 4) > historyNo) {
			historyNo = *(int*)(history + 4);
			selected = history;
		}
		history += 0x10;
	} while (history < (unsigned int)*(int*)((int)this + 8) + 0x40);

	if (historyNo != 0) {
		MusicMemoryFree((RedHistoryBANK*)selected);
	}

	return historyNo;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
unsigned int CRedEntry::MusicOldChoice()
{
	unsigned int selected = 0;
	int historyNo = 0;
	unsigned int history = (unsigned int)*(int*)((int)this + 8);

	do {
		if (*(int*)(history + 0xc) == 0) {
			return history;
		}
		if (*(int*)(history + 4) > historyNo) {
			historyNo = *(int*)(history + 4);
			selected = history;
		}
		history += 0x10;
	} while (history < (unsigned int)*(int*)((int)this + 8) + 0x40);

	return selected;
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
 * PAL Address: 0x801c281c
 * PAL Size: 88b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedEntry::ReentryMusicData(int musicNo)
{
	musicNo = SearchMusicSequence(musicNo);
	if (musicNo >= 0) {
		MusicHistoryChoice((RedHistoryBANK*)(((int*)this)[2] + musicNo * 0x10));
	}
	return musicNo;
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
		int inUse = 0;
		if ((*reinterpret_cast<short*>((int)p_SoundControlBuffer + 0x48E) != 0)
		    && (*reinterpret_cast<int*>((int)p_SoundControlBuffer + 0x470) == musicNo)) {
			inUse |= 1;
		}
		if ((*reinterpret_cast<short*>((int)p_SoundControlBuffer + 0x922) != 0)
		    && (*reinterpret_cast<int*>((int)p_SoundControlBuffer + 0x904) == musicNo)) {
			inUse |= 1;
		}

		if (inUse == 0) {
			int musicSeq = SearchMusicSequence(musicNo);
			if (musicSeq >= 0) {
				if (reinterpret_cast<int*>(*reinterpret_cast<int*>(reinterpret_cast<int>(this) + 8))[musicSeq * 4 + 1] == 0) {
					MusicHistoryAdd();
					reinterpret_cast<int*>(*reinterpret_cast<int*>(reinterpret_cast<int>(this) + 8))[musicSeq * 4 + 1] = 1;
				}
			}
		}
	} else {
		int musicSeq = SearchMusicSequence(musicNo);
		if (musicSeq >= 0) {
			if (reinterpret_cast<int*>(*reinterpret_cast<int*>(reinterpret_cast<int>(this) + 8))[musicSeq * 4 + 1] != 0) {
				MusicHistoryDelete(reinterpret_cast<int*>(*reinterpret_cast<int*>(reinterpret_cast<int>(this) + 8))[musicSeq * 4 + 1]);
				reinterpret_cast<int*>(*reinterpret_cast<int*>(reinterpret_cast<int>(this) + 8))[musicSeq * 4 + 1] = 0;
			}
		}
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CRedEntry::MusicHeadAdd(RedMusicHEAD* musicHead)
{
	int* bank = reinterpret_cast<int*>(MusicOldChoice());
	if ((bank != 0) && (bank[3] != 0)) {
		MusicOldClear();
		bank = reinterpret_cast<int*>(MusicOldChoice());
	}

	int result = 0;
	if (bank != 0) {
		bank[2] = reinterpret_cast<int>(musicHead);
		bank[3] = *reinterpret_cast<int*>(reinterpret_cast<int>(musicHead) + 0x10);
		bank[0] = static_cast<int>(*reinterpret_cast<short*>(reinterpret_cast<int>(musicHead) + 4));
		MusicHistoryAdd();
		bank[1] = 1;
		result = reinterpret_cast<int>(musicHead);
	}

	return result;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CRedEntry::SetMusicData(RedMusicHEAD* musicHead)
{
	int result;
	char* data = reinterpret_cast<char*>(musicHead);

	if ((data[0] != 'B') || (data[1] != 'G') || (data[2] != 'M')) {
		RedDelete(musicHead);
		if (m_ReportPrint != 0) {
			OSReport(s__s_sMusic_Header_was_broken__s_801e7c1d, sRedEntryLogPrefix, sRedEntryHeaderErrorColor, sRedEntryResetColor);
			fflush(__files + 1);
		}
		return 0;
	}

	result = SearchMusicSequence(static_cast<int>(*reinterpret_cast<short*>(data + 4)));
	if (result >= 0) {
		RedDelete(musicHead);
		MusicHistoryChoice(reinterpret_cast<RedHistoryBANK*>(*reinterpret_cast<int*>(reinterpret_cast<int>(this) + 8) +
		                                                    result * 0x10));
		result = *reinterpret_cast<int*>(*reinterpret_cast<int*>(reinterpret_cast<int>(this) + 8) + result * 0x10 + 8);
	} else {
		result = MusicHeadAdd(musicHead);
		if (result == 0) {
			RedDelete(musicHead);
		}
	}

	return result;
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

	if (m_ReportPrint == 0) {
		return;
	}

	OSReport(sRedEntryNewline);
	fflush(__files + 1);
	OSReport(s__s_____MMemory_Information______801e7cce, sRedEntryLogPrefix);
	fflush(__files + 1);
	OSReport(s__s_Name___Start___Size___Free_801e7cef, sRedEntryLogPrefix);
	fflush(__files + 1);

	maxFreeSize = 0;
	totalSize = 0;
	entryCount = 0;
    nextAddress = c_RedMemory.GetMainBufferAddress();
    memoryBank = c_RedMemory.GetMainBankAddress();
    bufferTop = nextAddress + c_RedMemory.GetMainBufferSize();
	bankEntry = memoryBank;
	seBlockBase = (int*)p_SeBlockData;

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
					OSReport(s__s_MUSIC_3_3d___0x_8_8X___0x_8_8_801e7d24, sRedEntryLogPrefix,
					         (int)*(short*)(bankEntry[0] + 4), bankEntry[0], bankEntry[1], freeSize);
					fflush(__files + 1);
					matched = 1;
					break;
				}
				history += 0x10;
			} while (history < (unsigned int)entry[2] + 0x40);

			if (matched == 0) {
				i = 0;
				do {
					if ((seBlockBase[i] != 0) && (bankEntry[0] == seBlockBase[i])) {
						OSReport(s__s_SE_BLOCK___0x_8_8X___0x_8_8X___801e7d51, sRedEntryLogPrefix, bankEntry[0],
						         bankEntry[1], freeSize);
						fflush(__files + 1);
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
						OSReport(s__s_WAVE_4_4d___0x_8_8X___0x_8_8X_801e7d7c, sRedEntryLogPrefix,
						         (int)*(short*)(bankEntry[0] + 2), bankEntry[0], bankEntry[1], freeSize);
						fflush(__files + 1);
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
						OSReport(s__s_SE_6_6d___0x_8_8X___0x_8_8X___801e7da8, sRedEntryLogPrefix,
						         *(int*)(bankEntry[0] + 8), bankEntry[0], bankEntry[1], freeSize);
						fflush(__files + 1);
						matched = 1;
						break;
					}
					history += 0x10;
				} while (history < (unsigned int)entry[1] + 0x1000);
			}

			if (matched == 0) {
				OSReport(s__s____________0x_8_8X___0x_8_8X___801e7dd2, sRedEntryLogPrefix, bankEntry[0], bankEntry[1],
				         freeSize);
				fflush(__files + 1);
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

    freeSize = (c_RedMemory.GetMainBufferAddress() + c_RedMemory.GetMainBufferSize()) - nextAddress;
	if (maxFreeSize < freeSize) {
		maxFreeSize = freeSize;
	}

	OSReport(sRedEntryPrefixedNewlineFmt, sRedEntryLogPrefix);
	fflush(__files + 1);
	OSReport(s__s_Entry_Items____d_801e7dfd, sRedEntryLogPrefix, entryCount);
	fflush(__files + 1);
	OSReport(s__s_Total_Size___0x_8_8X_801e7b18, sRedEntryLogPrefix, totalSize);
	fflush(__files + 1);
	OSReport(s__s_Max_Free_Size___0x_8_8X_801e7b34, sRedEntryLogPrefix, maxFreeSize);
	fflush(__files + 1);
	OSReport(sRedEntryPrefixedNewlineFmt, sRedEntryLogPrefix);
	fflush(__files + 1);
	OSReport(sRedEntryNewline);
	fflush(__files + 1);
}
