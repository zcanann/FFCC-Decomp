#include "ffcc/RedSound/RedEntry.h"
#include "ffcc/RedSound/RedCommand.h"
#include "ffcc/RedSound/RedDriver.h"
#include "ffcc/RedSound/RedMidiCtrl.h"
#include "ffcc/RedSound/RedGlobals.h"
#include "ffcc/RedSound/RedMemory.h"
#include <dolphin/os.h>
#include <string.h>

static const char sRedEntryColoredBlankLineFmt[] = "%s%s                                     %s\n";
static const char sRedEntryLogPrefix[] = "\x1B[7;34mSound\x1B[0m:";
static const char s__s_s__________ERROR___________s_801e7917[] = "%s%s ********       ERROR       ******** %s\n";
static const char s__s_s_Erase_Using_Wave_Data_____W_801e7944[] =
    "%s%s Erase Using Wave Data !! (WAVE%4.4d) %s\n";
static const char s__s_sWave_Header_was_broken__s_801e7972[] = "%s%sWave-Header was broken.%s\n";
static const char s__s_sNOT_HAVE_A_MEMORY_FREE_AREA___801e7991[] =
    "%s%sNOT HAVE A-MEMORY FREE AREA (WAVE%4.4u:0x%6.6X need).%s\n";
static const char s__s_sWave_Entry___wave_4_4u__s_801e79ce[] = "%s%sWave Entry. (wave%4.4u)%s\n";
static const char s__s_____AMemory_Information______801e79ed[] = "%s==== AMemory Information ====\n";
static const char s__s_Bank___Name___Start___Size___F_801e7a0e[] =
    "%s Bank : Name     : Start      : Size       : Free       : History\n";
static const char s__s__2d___WAVE_4_4d___0x_8_8X___0_801e7a53[] =
    "%s  %2d  : WAVE%4.4d : 0x%8.8X : 0x%8.8X : 0x%8.8X :   %3d\n";
static const char s__s______WAVE_4_4d___0x_8_8X___0x_801e7a8f[] =
    "%s  --  : WAVE%4.4d : 0x%8.8X : 0x%8.8X : 0x%8.8X :   %3d\n";
static const char s__s______________0x_8_8X___0x_8_8_801e7aca[] =
    "%s      : -------- : 0x%8.8X : 0x%8.8X : 0x%8.8X : %d\n";
static const char s__s_Entry_Wave____d_801e7b01[] = "%s    Entry Wave = %d\n";
static const char s__s_Total_Size___0x_8_8X_801e7b18[] = "%s    Total Size = 0x%8.8X\n";
static const char s__s_Max_Free_Size___0x_8_8X_801e7b34[] = "%s Max Free Size = 0x%8.8X\n";
static const char s__s_sSE_Sep_Header_was_broken__s_801e7b50[] = "%s%sSE-Sep-Header was broken.%s\n";
static const char s__s_____SE_Play_Information______801e7b71[] = "%s==== SE Play Information ====\n";
static const char s__s_Track___Name___Wave_801e7b92[] = "%s Track : Name         : Wave\n";
static const char s__s__2d____3_3u__3_3u___WAVE_4_4u_801e7bb2[] =
    "%s    %2d : %3.3u:%3.3u      : WAVE%4.4u\n";
static const char s__s__2d___se_6_6u_sep___WAVE_4_4u_801e7bdc[] =
    "%s    %2d : se%6.6u.sep : WAVE%4.4u\n";
static const char s__s__2d_____801e7c01[] = "%s    %2d :              :\n";
static const char s__s_sMusic_Header_was_broken__s_801e7c1d[] = "%s%sMusic-Header was broken.%s\n";
static const char sRedEntryMusicInformationHeaderFmt[] = "%s==== MUSIC Information ====\n";
static const char sRedEntryMusicInfoColumnFmt[] = "%s BGM      : Wave : Size     : \n";
static const char sRedEntryMusicInfoPlayFmt[] = "%s music%3.3u : %4.4u : 0x%6.6X : Play\n";
static const char sRedEntryMusicInfoStopFmt[] = "%s music%3.3u : %4.4u : 0x%6.6X : Stop\n";
static const char s__s_____MMemory_Information______801e7cce[] = "%s==== MMemory Information ====\n";
static const char s__s_Name___Start___Size___Free_801e7cef[] = "%s Name     : Start      : Size       : Free       \n";
static const char s__s_MUSIC_3_3d___0x_8_8X___0x_8_8_801e7d24[] =
    "%s MUSIC%3.3d : 0x%8.8X : 0x%8.8X : 0x%8.8X\n";
static const char s__s_SE_BLOCK___0x_8_8X___0x_8_8X___801e7d51[] =
    "%s SE-BLOCK : 0x%8.8X : 0x%8.8X : 0x%8.8X\n";
static const char s__s_WAVE_4_4d___0x_8_8X___0x_8_8X_801e7d7c[] =
    "%s WAVE%4.4d : 0x%8.8X : 0x%8.8X : 0x%8.8X\n";
static const char s__s_SE_6_6d___0x_8_8X___0x_8_8X___801e7da8[] =
    "%s SE%6.6d : 0x%8.8X : 0x%8.8X : 0x%8.8X\n";
static const char s__s____________0x_8_8X___0x_8_8X___801e7dd2[] =
    "%s -------- : 0x%8.8X : 0x%8.8X : 0x%8.8X\n";
static const char s__s_Entry_Items____d_801e7dfd[] = "%s   Entry Items = %d\n";
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
	int iVar2;

	m_waveBankBase = RedNew(0x400);
	m_seSepBankBase = RedNew(0x1000);
	m_musicBankBase = RedNew(0x40);

	memset((void*)m_waveBankBase, 0, 0x400);
	iVar2 = 0;
	do {
		*(int*)(m_waveBankBase + iVar2 * 0x10) = -1;
		iVar2 = iVar2 + 1;
	} while (iVar2 < 0x40);

	memset((void*)m_seSepBankBase, 0, 0x1000);
	iVar2 = 0;
	do {
		*(int*)(m_seSepBankBase + iVar2 * 0x10) = -1;
		iVar2 = iVar2 + 1;
	} while (iVar2 < 0x100);

	memset((void*)m_musicBankBase, 0, 0x40);
	iVar2 = 0;
	do {
		*(int*)(m_musicBankBase + iVar2 * 0x10) = -1;
		iVar2 = iVar2 + 1;
	} while (iVar2 < 4);

	m_waveLoadNo = -1;
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
	RedHistoryBANK* history = reinterpret_cast<RedHistoryBANK*>(m_waveBankBase + 0x100);

	do {
		if (history->m_historyNo >= historyNo) {
			history->m_historyNo = history->m_historyNo + 1;
		}
		history += 1;
	} while (history < reinterpret_cast<RedHistoryBANK*>(m_waveBankBase + 0x400));
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
		RedHistoryBANK* history = reinterpret_cast<RedHistoryBANK*>(m_waveBankBase);
		do {
			if ((history->m_historyNo != 0) && (history->m_historyNo > historyNo)) {
				history->m_historyNo = history->m_historyNo - 1;
			}
			history += 1;
		} while (history < reinterpret_cast<RedHistoryBANK*>(m_waveBankBase + 0x400));
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
	if (bank->m_historyNo != 0) {
		RedHistoryBANK* history = reinterpret_cast<RedHistoryBANK*>(m_waveBankBase);
		do {
			if ((history->m_historyNo != 0) &&
			    (history->m_historyNo < bank->m_historyNo)) {
				history->m_historyNo = history->m_historyNo + 1;
			}
			history += 1;
		} while (history < reinterpret_cast<RedHistoryBANK*>(m_waveBankBase + 0x400));

		bank->m_historyNo = 1;
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CRedEntry::SearchWaveSequence(int waveNo)
{
	RedHistoryBANK* waveBank = reinterpret_cast<RedHistoryBANK*>(m_waveBankBase);

	while (waveBank < reinterpret_cast<RedHistoryBANK*>(m_waveBankBase + 0x400)) {
		if ((waveBank->m_size != 0) && (waveBank->m_id == waveNo)) {
			return (reinterpret_cast<int>(waveBank) - m_waveBankBase) / 0x10;
		}
		waveBank += 1;
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
	int soundBase = (int)(p_SoundControlBuffer + REDSOUND_CONTROL_MUSIC_SECONDARY);

	do {
		if ((*(int*)(soundBase + 0x470) >= 0) && (*(int*)(soundBase + 0x47c) == waveNo)) {
			found = 1;
			MusicStop(*(int*)(soundBase + 0x470));
		}
		soundBase -= REDSOUND_CONTROL_SIZE;
	} while ((unsigned int)soundBase >= (unsigned int)p_SoundControlBuffer);

	soundBase = (int)(p_SoundControlBuffer + REDSOUND_CONTROL_SE);
	RedTrackDATA* track = *(RedTrackDATA**)soundBase;
	do {
		if (((u32)track->m_command != 0) && ((u32)track->m_waveBankData != 0) &&
		    (reinterpret_cast<RedWaveHeadWD*>(track->m_waveBankData)->m_waveNo == waveNo)) {
			found = 1;
			SeStopID(track->m_seId);
		}
		track += 1;
	} while (track < reinterpret_cast<RedTrackDATA*>(*(int*)soundBase + REDSOUND_SE_TRACK_ARENA_SIZE));

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
	int sequenceNo = -1;
	int iVar2;

	if (bank->m_id >= 0) {
		WaveHistoryDelete(bank->m_historyNo);
		iVar2 = bank->m_id;

		bank->m_id = -1;
		bank->m_size = 0;

		sequenceNo = SearchWaveSequence(iVar2);
		if (sequenceNo < 0) {
			if ((SearchUseWave(iVar2) != 0) && (m_ReportPrint != 0)) {
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
			RedDeleteA(reinterpret_cast<RedWaveHeadWD*>(bank->m_data)->m_aramAddress);
			RedDelete(bank->m_data);
		}

		bank->m_data = 0;
		bank->m_historyNo = 0;
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
	RedHistoryBANK* selected = 0;
	int arAddress = c_RedMemory.GetABufferAddress();
	int maxBankSize = 0;
	offset += arAddress;
	maxSize += arAddress;
	RedHistoryBANK* history = reinterpret_cast<RedHistoryBANK*>(m_waveBankBase + 0x100);

	do {
		if (history->m_historyNo > maxBankSize) {
			arAddress = reinterpret_cast<RedWaveHeadWD*>(history->m_data)->m_aramAddress;
			if ((arAddress >= offset) && (arAddress < maxSize)) {
				maxBankSize = history->m_historyNo;
				selected = history;
			}
		}
		history += 1;
	} while (history < reinterpret_cast<RedHistoryBANK*>(m_waveBankBase + 0x400));

	if (maxBankSize != 0) {
		WaveDelete(selected);
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
	if ((waveHead->m_signature[0] != 'W') || (waveHead->m_signature[1] != 'D')) {
		if (m_ReportPrint != 0) {
			OSReport(s__s_sWave_Header_was_broken__s_801e7972, sRedEntryLogPrefix, sRedEntryHeaderErrorColor, sRedEntryResetColor);
			fflush(__files + 1);
		}

		return -1;
	}

	if (waveHead->m_loadSize < waveHead->m_waveSize) {
		waveHead->m_loadSize = waveHead->m_waveSize;
	}

	if ((waveNo >= 100) && (waveNo < 300)) {
		if (waveHead->m_loadSize <= 0x200000) {
			waveHead->m_loadSize = 0x200000;
		} else if (waveHead->m_loadSize <= 0x400000) {
			waveHead->m_loadSize = 0x400000;
		}
	} else if ((waveNo >= 10) && (waveNo < 70)) {
		waveHead->m_loadSize += 0x27FFF;
		int blocks = waveHead->m_loadSize / 0x28000;
		blocks += blocks >> 0x1F;
		waveHead->m_loadSize = blocks * 0x28000;
	} else if (((waveNo >= 0x154) && (waveNo < 0x17a)) || ((waveNo >= 0x17f) && (waveNo < 0x182)) ||
	           (waveNo == 0x183)) {
		waveHead->m_loadSize = 0x100000;
	}

	int minOffset;
	int maxOffset;
	if ((waveNo >= 100) && (waveNo < 300)) {
		minOffset = 0x400000;
		maxOffset = minOffset + 0x400000;
	} else if (((waveNo >= 0x154) && (waveNo < 0x17a)) || ((waveNo >= 0x17f) && (waveNo < 0x182)) ||
	           (waveNo == 0x183)) {
		minOffset = 0x300000;
		maxOffset = minOffset + 0x100000;
	} else {
		minOffset = 0;
		maxOffset = minOffset + 0x300000;
	}

	do {
		RedHistoryBANK* historyBank;
		if (waveBankNo < 0) {
			historyBank = reinterpret_cast<RedHistoryBANK*>(m_waveBankBase + 0x100);
			while ((historyBank->m_size != 0) &&
			       (historyBank < reinterpret_cast<RedHistoryBANK*>(m_waveBankBase + 0x400U))) {
				historyBank += 1;
			}
		} else {
			waveBankNo &= 0xF;
			historyBank = reinterpret_cast<RedHistoryBANK*>(m_waveBankBase + waveBankNo * 0x10);
			if (historyBank->m_size != 0) {
				WaveDelete(historyBank);
			}
		}

		int arAddress;
		if ((historyBank < reinterpret_cast<RedHistoryBANK*>(m_waveBankBase + 0x400U)) &&
		    ((arAddress = RedNewA(waveHead->m_loadSize, minOffset, maxOffset)) != 0)) {
			int copySize = waveHead->m_toneCount * 0x60 + 0x20;
			copySize += ((waveHead->m_tableCount * 4) + 0x1F) & 0xFFFFFFE0;
			void* copied = (void*)RedNew(copySize);
			if (copied != 0) {
				historyBank->m_data = (int)copied;
				historyBank->m_size = copySize;
				waveHead->m_aramAddress = arAddress;
				historyBank->m_id = waveNo;
				waveHead->m_waveNo = (short)waveNo;
				if (waveBankNo < 0) {
					WaveHistoryAdd(1);
					historyBank->m_historyNo = 1;
				} else {
					historyBank->m_historyNo = 0;
				}
				memcpy(copied, waveHead, copySize);
				return arAddress;
			}
			RedDeleteA((void*)arAddress);
		}
	} while (WaveOldClear(minOffset, maxOffset) != 0);

	if (m_ReportPrint != 0) {
		OSReport(s__s_sNOT_HAVE_A_MEMORY_FREE_AREA___801e7991, sRedEntryLogPrefix, sRedEntryErrorColor, (int)waveHead->m_waveNo,
		         waveHead->m_waveSize, sRedEntryResetColor);
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
	int waveNo;
	int waveAddress;
	int waveSize;
	void* waveDataTop;

	if (waveDataSize == 0) {
		if ((m_waveLoadNo >= 0) && ((waveNo = SearchWaveSequence(m_waveLoadNo)) >= 0)) {
			WaveDelete(&reinterpret_cast<RedHistoryBANK*>(m_waveBankBase)[waveNo]);
		}

		m_waveLoadNo = -1;
		return -1;
	}

	waveAddress = 0;
	if (m_waveLoadNo < 0) {
		RedWaveHeadWD* waveHead = (RedWaveHeadWD*)waveData;
		waveNo = waveHead->m_waveNo;

		if ((waveBankNo >= 0) && (waveNo != reinterpret_cast<RedHistoryBANK*>(m_waveBankBase)[waveBankNo].m_id)) {
			WaveDelete(&reinterpret_cast<RedHistoryBANK*>(m_waveBankBase)[waveBankNo]);
		}

		int historyNo = SearchWaveSequence(waveNo);
		if (historyNo >= 0) {
			if ((waveBankNo >= 0) && (historyNo != waveBankNo)) {
				*(int*)(m_waveBankBase + waveBankNo * 0x10 + 0x0) = *(int*)(m_waveBankBase + historyNo * 0x10 + 0x0);
				*(int*)(m_waveBankBase + waveBankNo * 0x10 + 0x4) = *(int*)(m_waveBankBase + historyNo * 0x10 + 0x4);
				*(int*)(m_waveBankBase + waveBankNo * 0x10 + 0x8) = *(int*)(m_waveBankBase + historyNo * 0x10 + 0x8);
				*(int*)(m_waveBankBase + waveBankNo * 0x10 + 0xC) = *(int*)(m_waveBankBase + historyNo * 0x10 + 0xC);
				historyNo = waveBankNo;
			}

			WaveHistoryChoice(&reinterpret_cast<RedHistoryBANK*>(m_waveBankBase)[historyNo]);
		} else {
			m_waveLoadNo = waveHead->m_waveNo;
			waveAddress = WaveHeadAdd(waveBankNo, waveHead, waveNo);
			if (waveAddress < 0) {
				m_waveLoadSize = 0;
				m_waveLoadNo = -1;
				return -1;
			}

			int waveHeadSize =
			    ((((waveHead->m_tableCount * 4) + 0x1F) & 0xFFFFFFE0) +
			     waveHead->m_toneCount * 0x60) +
			    0x20;
			waveSize = waveHead->m_waveSize;
			waveDataSize -= waveHeadSize;
			waveDataTop = (void*)((unsigned char*)waveData + waveHeadSize);
		}
	} else {
		waveAddress = m_waveLoadAddress;
		waveDataTop = waveData;
		waveSize = m_waveLoadSize;
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
		m_waveLoadSize = waveSize;
		m_waveLoadAddress = waveAddress;

		while (RedDmaSearchID(dmaID) > 0) {
			RedSleep(1000);
		}

		if (m_waveLoadSize < 1) {
			if (m_ReportPrint != 0) {
				OSReport(s__s_sWave_Entry___wave_4_4u__s_801e79ce, sRedEntryLogPrefix, sRedEntryInfoColor, m_waveLoadNo, sRedEntryResetColor);
				fflush(__files + 1);
			}

			m_waveLoadNo = -1;
			return 0;
		}
	}

	return m_waveLoadNo;
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
	RedHistoryBANK* historyBank;

	if (waveNo < 0) {
		if (waveNo == -1) {
			for (historyBank = reinterpret_cast<RedHistoryBANK*>(m_waveBankBase);
			     historyBank < reinterpret_cast<RedHistoryBANK*>(m_waveBankBase + 0x400); historyBank += 1) {
				if (historyBank->m_id >= 0) {
					WaveDelete(historyBank);
				}
			}
		} else if (waveNo == -2) {
			for (historyBank = reinterpret_cast<RedHistoryBANK*>(m_waveBankBase + 0x100);
			     historyBank < reinterpret_cast<RedHistoryBANK*>(m_waveBankBase + 0x400); historyBank += 1) {
				if (historyBank->m_id >= 0) {
					WaveDelete(historyBank);
				}
			}
		} else if (waveNo == -3) {
			for (historyBank = reinterpret_cast<RedHistoryBANK*>(m_waveBankBase + 0x100);
			     historyBank < reinterpret_cast<RedHistoryBANK*>(m_waveBankBase + 0x400); historyBank += 1) {
				if ((historyBank->m_id >= 0) && (0 < historyBank->m_historyNo)) {
					WaveDelete(historyBank);
				}
			}
		}
	} else {
		waveNo = SearchWaveSequence(waveNo);
		if (waveNo >= 0) {
			WaveDelete(reinterpret_cast<RedHistoryBANK*>(m_waveBankBase + waveNo * 0x10));
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
	RedHistoryBANK* historyBank;

	if (((waveNo0 == -1) && (waveNo1 == -1) && (waveNo2 == -1)) && (waveNo3 == -1)) {
		return;
	}

	for (historyBank = reinterpret_cast<RedHistoryBANK*>(m_waveBankBase + 0x100);
	     historyBank < reinterpret_cast<RedHistoryBANK*>(m_waveBankBase + 0x400); historyBank += 1) {
		if (((historyBank->m_id >= 0) && (0 < historyBank->m_historyNo)) &&
		    (historyBank->m_id != waveNo0) && (historyBank->m_id != waveNo1) &&
		    (historyBank->m_id != waveNo2) && (historyBank->m_id != waveNo3)) {
			WaveDelete(historyBank);
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
	RedHistoryBANK* historyBank;

	if (waveBankNo < 0) {
		if (waveBankNo == -1) {
			for (historyBank = reinterpret_cast<RedHistoryBANK*>(m_waveBankBase);
			     historyBank < reinterpret_cast<RedHistoryBANK*>(m_waveBankBase + 0x400); historyBank += 1) {
				if (!(historyBank->m_id < 0)) {
					WaveDelete(historyBank);
				}
			}
		} else if (waveBankNo == -2) {
			for (historyBank = reinterpret_cast<RedHistoryBANK*>(m_waveBankBase + 0x100);
			     historyBank < reinterpret_cast<RedHistoryBANK*>(m_waveBankBase + 0x400); historyBank += 1) {
				if (!(historyBank->m_id < 0)) {
					WaveDelete(historyBank);
				}
			}
		} else if (waveBankNo == -3) {
			for (historyBank = reinterpret_cast<RedHistoryBANK*>(m_waveBankBase + 0x100);
			     historyBank < reinterpret_cast<RedHistoryBANK*>(m_waveBankBase + 0x400); historyBank += 1) {
				if (!(historyBank->m_id < 0) && (0 < historyBank->m_historyNo)) {
					WaveDelete(historyBank);
				}
			}
		}
	} else if ((waveBankNo >= 0) && (waveBankNo < 0x10)) {
		WaveDelete(reinterpret_cast<RedHistoryBANK*>(m_waveBankBase + waveBankNo * 0x10));
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
RedWaveHeadWD* CRedEntry::SearchWaveBase(int waveNo)
{
	RedHistoryBANK* waveBank = reinterpret_cast<RedHistoryBANK*>(m_waveBankBase);

	do {
		if (waveNo == waveBank->m_id) {
			return reinterpret_cast<RedWaveHeadWD*>(waveBank->m_data);
		}
		waveBank += 1;
	} while (waveBank < reinterpret_cast<RedHistoryBANK*>(m_waveBankBase + 0x400));

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
		WaveHistoryChoice(reinterpret_cast<RedHistoryBANK*>(m_waveBankBase + waveNo * 0x10));
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
	int* track;

	if (mode == 0) {
		used = 0;
		if ((p_SoundControlBuffer[REDSOUND_CONTROL_MUSIC_PRIMARY].m_activeTrackCount != 0) &&
		    (p_SoundControlBuffer[REDSOUND_CONTROL_MUSIC_PRIMARY].m_waveNo == waveNo)) {
			used |= 1;
		}
		if ((p_SoundControlBuffer[REDSOUND_CONTROL_MUSIC_SECONDARY].m_activeTrackCount != 0) &&
		    (p_SoundControlBuffer[REDSOUND_CONTROL_MUSIC_SECONDARY].m_waveNo == waveNo)) {
			used |= 1;
		}
		if (used == 0) {
			int* trackHead = (int*)&p_SoundControlBuffer[REDSOUND_CONTROL_SE].m_tracks;
			track = (int*)*trackHead;
			do {
				if (((*reinterpret_cast<unsigned int*>(track) != 0) && (*reinterpret_cast<unsigned int*>(track + 6) != 0)) &&
				    (reinterpret_cast<RedWaveHeadWD*>(track[6])->m_waveNo == waveNo)) {
					used++;
					break;
				}
				track += REDSOUND_TRACK_SIZE / sizeof(*track);
			} while (track < (int*)(*trackHead + REDSOUND_SE_TRACK_ARENA_SIZE));
		}
		if (used == 0) {
			used = SearchWaveSequence(waveNo);
			if ((used >= 0x10) && (*(int*)(*(int*)this + used * 0x10 + 4) == 0)) {
				WaveHistoryAdd(0x14);
				*(int*)(*(int*)this + used * 0x10 + 4) = 0x14;
			}
		}
	} else {
		used = SearchWaveSequence(waveNo);
		if ((used >= 0x10) && (*(int*)(*(int*)this + used * 0x10 + 4) != 0)) {
			WaveHistoryDelete(*(int*)(*(int*)this + used * 0x10 + 4));
			*(int*)(*(int*)this + used * 0x10 + 4) = 0;
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
        RedMemoryBlock* aBankAddress = c_RedMemory.GetABankAddress();
        int aBufferEnd = aBufferAddress + c_RedMemory.GetABufferSize();

		RedMemoryBlock* bank = aBankAddress;
		do {
			if (bank->m_size != 0) {
				int freeSize;
				if (bank[1].m_size < 1) {
					freeSize = aBufferEnd - (bank->m_address + bank->m_size);
				} else {
					freeSize = bank[1].m_address - (bank->m_address + bank->m_size);
				}

				RedHistoryBANK* history = reinterpret_cast<RedHistoryBANK*>(m_waveBankBase);
				do {
					if ((history->m_size != 0) && (((RedWaveHeadWD*)history->m_data)->m_aramAddress == bank->m_address)) {
						break;
					}
					history += 1;
				} while (history < reinterpret_cast<RedHistoryBANK*>(m_waveBankBase + 0x400));

				if (history < reinterpret_cast<RedHistoryBANK*>(m_waveBankBase + 0x400)) {
					if (history < reinterpret_cast<RedHistoryBANK*>(m_waveBankBase + 0x100)) {
						unsigned int index = reinterpret_cast<unsigned int>(history) - (unsigned int)m_waveBankBase;
						OSReport(s__s__2d___WAVE_4_4d___0x_8_8X___0_801e7a53, sRedEntryLogPrefix, (int)(index >> 4),
						         (int)((RedWaveHeadWD*)history->m_data)->m_waveNo, ((RedWaveHeadWD*)history->m_data)->m_aramAddress, bank->m_size,
						         freeSize, history->m_historyNo);
						fflush(__files + 1);
					} else {
						OSReport(s__s______WAVE_4_4d___0x_8_8X___0x_801e7a8f, sRedEntryLogPrefix,
						         (int)((RedWaveHeadWD*)history->m_data)->m_waveNo, ((RedWaveHeadWD*)history->m_data)->m_aramAddress, bank->m_size,
						         freeSize, history->m_historyNo);
						fflush(__files + 1);
					}
					entryWave += 1;
				} else {
					unsigned int bankIndex = (unsigned int)((int)bank - (int)aBankAddress);
					OSReport(s__s______________0x_8_8X___0x_8_8_801e7aca, sRedEntryLogPrefix, bank->m_address, bank->m_size, freeSize,
					         (int)(bankIndex >> 3));
					fflush(__files + 1);
				}

				if (maxFreeSize < bank->m_address - aBufferAddress) {
					maxFreeSize = bank->m_address - aBufferAddress;
				}
				totalSize += bank->m_size;
				aBufferAddress = bank->m_address + bank->m_size;
			}
			bank++;
		} while (bank < aBankAddress + 0x400);

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
	RedHistoryBANK* history = reinterpret_cast<RedHistoryBANK*>(m_seSepBankBase);
	do {
		if (history->m_historyNo != 0) {
			history->m_historyNo = history->m_historyNo + 1;
		}
		history += 1;
	} while (history < reinterpret_cast<RedHistoryBANK*>(m_seSepBankBase + 0x1000));
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
		RedHistoryBANK* history = reinterpret_cast<RedHistoryBANK*>(m_seSepBankBase);
		do {
			if (history->m_historyNo > historyNo) {
				history->m_historyNo = history->m_historyNo - 1;
			}
			history += 1;
		} while (history < reinterpret_cast<RedHistoryBANK*>(m_seSepBankBase + 0x1000));
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
	if (bank->m_historyNo != 0) {
		RedHistoryBANK* history = reinterpret_cast<RedHistoryBANK*>(m_seSepBankBase);
		do {
			if ((history->m_historyNo != 0) && (history->m_historyNo < bank->m_historyNo)) {
				history->m_historyNo = history->m_historyNo + 1;
			}
			history += 1;
		} while (history < reinterpret_cast<RedHistoryBANK*>(m_seSepBankBase + 0x1000));
		bank->m_historyNo = 1;
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
	RedHistoryBANK* seSepBank = reinterpret_cast<RedHistoryBANK*>(m_seSepBankBase);

	if (seNo == -1) {
		do {
			if (seSepBank->m_size != 0) {
				return (reinterpret_cast<int>(seSepBank) - m_seSepBankBase) / 0x10;
			}
			seSepBank += 1;
		} while (seSepBank < reinterpret_cast<RedHistoryBANK*>(m_seSepBankBase + 0x1000));
	} else {
		do {
			if ((seSepBank->m_size != 0) && (seSepBank->m_id == seNo)) {
				return (reinterpret_cast<int>(seSepBank) - m_seSepBankBase) / 0x10;
			}
			seSepBank += 1;
		} while (seSepBank < reinterpret_cast<RedHistoryBANK*>(m_seSepBankBase + 0x1000));
	}

	return -1;
}

/*
 * --INFO--
 * PAL Address: 0x801c1c20
 * PAL Size: 156b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedEntry::SeSepMemoryFree(RedHistoryBANK* bank)
{
	int freedSize;
	int waveNo = static_cast<unsigned int>(reinterpret_cast<RedSeSepHEAD*>(bank->m_data)->m_waveNoLo) +
	             static_cast<unsigned int>(reinterpret_cast<RedSeSepHEAD*>(bank->m_data)->m_waveNoHi) * 0x100;

	RedDelete(bank->m_data);
	SeSepHistoryDelete(bank->m_historyNo);

	freedSize = bank->m_size;
	bank->m_data = bank->m_size = 0;
	bank->m_id = -1;

	WaveHistoryManager(0, waveNo);
	return freedSize;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
RedHistoryBANK* CRedEntry::SeSepOldDelete()
{
	unsigned int selected = 0;
	int historyNo = 0;
	unsigned int history = static_cast<unsigned int>(m_seSepBankBase);

	do {
		if ((*reinterpret_cast<int*>(history + 0xC) != 0) && (historyNo < *reinterpret_cast<int*>(history + 4))) {
			historyNo = *reinterpret_cast<int*>(history + 4);
			selected = history;
		}
		history += 0x10;
	} while (history < static_cast<unsigned int>(m_seSepBankBase) + 0x1000);

	if (selected != 0) {
		SeSepMemoryFree(reinterpret_cast<RedHistoryBANK*>(selected));
	}

	return reinterpret_cast<RedHistoryBANK*>(selected);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CRedEntry::SeSepHeadAdd(RedSeSepHEAD* seSepHead)
{
	RedHistoryBANK* bank = reinterpret_cast<RedHistoryBANK*>(m_seSepBankBase);
	int result = 0;

	while ((bank->m_size != 0) &&
	       (bank < reinterpret_cast<RedHistoryBANK*>(m_seSepBankBase + 0x1000U))) {
		bank += 1;
	}
	if (bank < reinterpret_cast<RedHistoryBANK*>(m_seSepBankBase + 0x1000U)) {
	} else {
		bank = SeSepOldDelete();
	}

	if ((bank != 0) &&
	    (bank < reinterpret_cast<RedHistoryBANK*>(m_seSepBankBase + 0x1000U))) {
		bank->m_data = reinterpret_cast<int>(seSepHead);
		result = reinterpret_cast<int>(seSepHead);
		bank->m_size = seSepHead->m_sizeAndFlags & 0x7FFFFFFF;
		bank->m_id = seSepHead->m_seNo;
		SeSepHistoryAdd();
		bank->m_historyNo = 1;
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

	if ((seSepHead->m_signature[0] != 'S') || (seSepHead->m_signature[1] != 'e') ||
	    (seSepHead->m_signature[2] != 'S') || (seSepHead->m_signature[3] != 'e') ||
	    (seSepHead->m_signature[4] != 'p')) {
		RedDelete(seSepHead);
		if (m_ReportPrint != 0) {
			OSReport(s__s_sSE_Sep_Header_was_broken__s_801e7b50, sRedEntryLogPrefix, sRedEntryHeaderErrorColor, sRedEntryResetColor);
			fflush(__files + 1);
		}
		return 0;
	}

	result = SearchSeSepSequence(seSepHead->m_seNo);
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
		RedHistoryBANK* history = reinterpret_cast<RedHistoryBANK*>(m_seSepBankBase);
		do {
			if (history->m_size != 0) {
				SeSepMemoryFree(history);
			}
			history += 1;
		} while (history < reinterpret_cast<RedHistoryBANK*>(m_seSepBankBase + 0x1000));
	} else {
		result = SearchSeSepSequence(seNo);
		if (result >= 0) {
			result = SeSepMemoryFree(reinterpret_cast<RedHistoryBANK*>(m_seSepBankBase + result * 0x10));
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
	int result = 0;
	RedHistoryBANK* bank = reinterpret_cast<RedHistoryBANK*>(m_seSepBankBase);

	do {
		if (bank->m_size != 0) {
			int seNo = bank->m_id / 1000;
			if ((bankNo != seNo) && (sepNo != seNo) && (groupNo != seNo) && (kindNo != seNo)) {
				SeSepMemoryFree(bank);
			}
		}
		bank += 1;
	} while (bank < reinterpret_cast<RedHistoryBANK*>(m_seSepBankBase + 0x1000));

	return result;
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
RedHistoryBANK* CRedEntry::SearchSeSepBank(int seNo)
{
	RedHistoryBANK* seSepBank = reinterpret_cast<RedHistoryBANK*>(m_seSepBankBase);
	do {
		if (seSepBank->m_id == seNo) {
			return seSepBank;
		}
		seSepBank += 1;
	} while (seSepBank < reinterpret_cast<RedHistoryBANK*>(m_seSepBankBase + 0x1000));

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
		SeSepHistoryChoice(reinterpret_cast<RedHistoryBANK*>(m_seSepBankBase + seNo * 0x10));
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
	RedTrackDATA* track;
	int sequenceNo;

	if (mode == 0) {
		sequenceNo = 0;
		track = p_SoundControlBuffer[REDSOUND_CONTROL_SE].m_tracks;

		do {
			if (((unsigned int)track->m_command != 0) && (track->m_seSepId == seNo)) {
				sequenceNo |= 1;
				break;
			}
			track += 1;
		} while (track < p_SoundControlBuffer[REDSOUND_CONTROL_SE].m_tracks + REDSOUND_SE_TRACK_COUNT);

		if (sequenceNo == 0) {
			sequenceNo = SearchSeSepSequence(seNo);
			if ((sequenceNo >= 0) && (reinterpret_cast<RedHistoryBANK*>(m_seSepBankBase)[sequenceNo].m_historyNo == 0)) {
				SeSepHistoryAdd();
				reinterpret_cast<RedHistoryBANK*>(m_seSepBankBase)[sequenceNo].m_historyNo = 1;
			}
		}
	} else {
		sequenceNo = SearchSeSepSequence(seNo);
		if (reinterpret_cast<RedHistoryBANK*>(m_seSepBankBase)[sequenceNo].m_historyNo != 0) {
			SeSepHistoryDelete(reinterpret_cast<RedHistoryBANK*>(m_seSepBankBase)[sequenceNo].m_historyNo);
			reinterpret_cast<RedHistoryBANK*>(m_seSepBankBase)[sequenceNo].m_historyNo = 0;
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

		int* trackHead = (int*)&p_SoundControlBuffer[REDSOUND_CONTROL_SE].m_tracks;
		int* track = (int*)*trackHead;
		do {
			int trackOffset = (int)track - *trackHead;
			int trackIndex = trackOffset / REDSOUND_TRACK_SIZE + (trackOffset >> 0x1F);
			trackIndex = (trackIndex - (trackIndex >> 0x1F)) + 0x20;
			int trackCommand = track[0];
			if (trackCommand != 0) {
				if ((track[0x3D] & 0x80000000) != 0) {
					unsigned int seDataNo = (unsigned int)track[0x3D];
					int songNo = (int)(seDataNo & 0x7FFFFFFF) >> 9;
					int seqBase = ((int*)p_SeBlockData)[songNo] + 0x10;
					int seqInfo = seqBase + *(short*)(((int*)p_SeBlockData)[songNo] + 10) * 4;
					seqInfo += (*(unsigned int*)(seqBase + (seDataNo & 0x1FF) * 4) & 0x7FFFFFFF);
					int waveNo = static_cast<unsigned int>(reinterpret_cast<RedSeINFO*>(seqInfo)->m_waveNoLo) +
					             static_cast<unsigned int>(reinterpret_cast<RedSeINFO*>(seqInfo)->m_waveNoHi) *
					                 0x100;

					OSReport(s__s__2d____3_3u__3_3u___WAVE_4_4u_801e7bb2, sRedEntryLogPrefix,
					         trackIndex, songNo, seDataNo & 0x1FF, waveNo);
					fflush(__files + 1);
				} else {
					RedHistoryBANK* seSepBank = SearchSeSepBank(track[0x3D]);
					int waveNo =
					    static_cast<unsigned int>(reinterpret_cast<RedSeSepHEAD*>(seSepBank->m_data)->m_waveNoLo) +
					    static_cast<unsigned int>(reinterpret_cast<RedSeSepHEAD*>(seSepBank->m_data)->m_waveNoHi) *
					        0x100;
					OSReport(s__s__2d___se_6_6u_sep___WAVE_4_4u_801e7bdc, sRedEntryLogPrefix,
					         trackIndex, track[0x3D], waveNo);
					fflush(__files + 1);
				}
			} else {
				OSReport(s__s__2d_____801e7c01, sRedEntryLogPrefix, trackIndex);
				fflush(__files + 1);
			}
			track += REDSOUND_TRACK_SIZE / sizeof(*track);
		} while (track < (int*)(*trackHead + REDSOUND_SE_TRACK_ARENA_SIZE));

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
	RedHistoryBANK* history = reinterpret_cast<RedHistoryBANK*>(m_musicBankBase);

	do {
		if (history->m_historyNo != 0) {
			history->m_historyNo = history->m_historyNo + 1;
		}
		history += 1;
	} while (history < reinterpret_cast<RedHistoryBANK*>(m_musicBankBase + 0x40));
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedEntry::MusicHistoryDelete(int historyNo)
{
	if (historyNo != 0) {
		RedHistoryBANK* history = reinterpret_cast<RedHistoryBANK*>(m_musicBankBase);
		do {
			if (history->m_historyNo > historyNo) {
				history->m_historyNo = history->m_historyNo - 1;
			}
			history += 1;
		} while (history < reinterpret_cast<RedHistoryBANK*>(m_musicBankBase + 0x40));
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRedEntry::MusicHistoryChoice(RedHistoryBANK* bank)
{
	if (bank->m_historyNo != 0) {
		RedHistoryBANK* history = reinterpret_cast<RedHistoryBANK*>(m_musicBankBase);
		do {
			if ((history->m_historyNo != 0) && (history->m_historyNo < bank->m_historyNo)) {
				history->m_historyNo = history->m_historyNo + 1;
			}
			history += 1;
		} while (history < reinterpret_cast<RedHistoryBANK*>(m_musicBankBase + 0x40));
		bank->m_historyNo = 1;
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
	RedHistoryBANK* musicBank = reinterpret_cast<RedHistoryBANK*>(m_musicBankBase);

	do {
		if ((musicBank->m_size != 0) && (musicBank->m_id == musicNo)) {
			return (reinterpret_cast<int>(musicBank) - m_musicBankBase) / 0x10;
		}
		musicBank += 1;
	} while (musicBank < reinterpret_cast<RedHistoryBANK*>(m_musicBankBase + 0x40));

	return -1;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CRedEntry::MusicMemoryFree(RedHistoryBANK* bank)
{
	WaveHistoryManager(0, reinterpret_cast<RedMusicHEAD*>(bank->m_data)->m_waveNo);
	RedDelete(bank->m_data);
	int freedSize = bank->m_size;
	bank->m_data = bank->m_size = 0;
	bank->m_historyNo = 0;
	bank->m_id = -1;
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
	RedHistoryBANK* selected = 0;
	RedHistoryBANK* history = reinterpret_cast<RedHistoryBANK*>(m_musicBankBase);

	do {
		if (history->m_historyNo > historyNo) {
			historyNo = history->m_historyNo;
			selected = history;
		}
		history += 1;
	} while (history < reinterpret_cast<RedHistoryBANK*>(m_musicBankBase + 0x40));

	if (historyNo != 0) {
		MusicMemoryFree(selected);
	}

	return historyNo;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
RedHistoryBANK* CRedEntry::MusicOldChoice()
{
	RedHistoryBANK* selected = 0;
	int historyNo = 0;
	RedHistoryBANK* history = reinterpret_cast<RedHistoryBANK*>(m_musicBankBase);

	do {
		if (history->m_size == 0) {
			return history;
		}
		if (history->m_historyNo > historyNo) {
			historyNo = history->m_historyNo;
			selected = history;
		}
		history += 1;
	} while (history < reinterpret_cast<RedHistoryBANK*>(m_musicBankBase + 0x40));

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
RedHistoryBANK* CRedEntry::SearchMusicBank(int musicNo)
{
	RedHistoryBANK* musicBank = reinterpret_cast<RedHistoryBANK*>(m_musicBankBase);
	do {
		if (musicBank->m_id == musicNo) {
			return musicBank;
		}
		musicBank += 1;
	} while (musicBank < reinterpret_cast<RedHistoryBANK*>(m_musicBankBase + 0x40));

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
		MusicHistoryChoice(reinterpret_cast<RedHistoryBANK*>(m_musicBankBase + musicNo * 0x10));
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
	int musicSeq;

	if (mode == 0) {
		musicSeq = 0;
		if ((p_SoundControlBuffer[REDSOUND_CONTROL_MUSIC_PRIMARY].m_activeTrackCount != 0)
		    && (p_SoundControlBuffer[REDSOUND_CONTROL_MUSIC_PRIMARY].m_musicId == musicNo)) {
			musicSeq |= 1;
		}
		if ((p_SoundControlBuffer[REDSOUND_CONTROL_MUSIC_SECONDARY].m_activeTrackCount != 0)
		    && (p_SoundControlBuffer[REDSOUND_CONTROL_MUSIC_SECONDARY].m_musicId == musicNo)) {
			musicSeq |= 1;
		}

		if (musicSeq == 0) {
			musicSeq = SearchMusicSequence(musicNo);
			if (musicSeq >= 0) {
				if (*reinterpret_cast<int*>(*reinterpret_cast<int*>(reinterpret_cast<int>(this) + 8) + musicSeq * 0x10 + 4) == 0) {
					MusicHistoryAdd();
					*reinterpret_cast<int*>(*reinterpret_cast<int*>(reinterpret_cast<int>(this) + 8) + musicSeq * 0x10 + 4) = 1;
				}
			}
		}
	} else {
		musicSeq = SearchMusicSequence(musicNo);
		if (musicSeq >= 0) {
			if (*reinterpret_cast<int*>(*reinterpret_cast<int*>(reinterpret_cast<int>(this) + 8) + musicSeq * 0x10 + 4) != 0) {
				MusicHistoryDelete(*reinterpret_cast<int*>(*reinterpret_cast<int*>(reinterpret_cast<int>(this) + 8) + musicSeq * 0x10 + 4));
				*reinterpret_cast<int*>(*reinterpret_cast<int*>(reinterpret_cast<int>(this) + 8) + musicSeq * 0x10 + 4) = 0;
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
	int result = 0;
	RedHistoryBANK* bank = MusicOldChoice();
	if ((bank != 0) && (bank->m_size != 0)) {
		MusicOldClear();
		bank = MusicOldChoice();
	}

	if (bank != 0) {
		bank->m_data = reinterpret_cast<int>(musicHead);
		result = reinterpret_cast<int>(musicHead);
		bank->m_size = musicHead->m_size;
		bank->m_id = static_cast<int>(musicHead->m_musicNo);
		MusicHistoryAdd();
		bank->m_historyNo = 1;
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

	if ((musicHead->m_signature[0] != 'B') || (musicHead->m_signature[1] != 'G') ||
	    (musicHead->m_signature[2] != 'M')) {
		RedDelete(musicHead);
		if (m_ReportPrint != 0) {
			OSReport(s__s_sMusic_Header_was_broken__s_801e7c1d, sRedEntryLogPrefix, sRedEntryHeaderErrorColor, sRedEntryResetColor);
			fflush(__files + 1);
		}
		return 0;
	}

	result = SearchMusicSequence(static_cast<int>(musicHead->m_musicNo));
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
	RedMemoryBlock* memoryBank;
	RedMemoryBlock* bankEntry;
	unsigned int history;
	int* seBlockBase;

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
		if (bankEntry->m_size != 0) {
			int matched = 0;

			if (bankEntry[1].m_size < 1) {
				freeSize = bufferTop - (bankEntry->m_address + bankEntry->m_size);
			} else {
				freeSize = bankEntry[1].m_address - (bankEntry->m_address + bankEntry->m_size);
			}

			history = (unsigned int)m_musicBankBase;
			do {
				if ((*(int*)(history + 0xC) != 0) && (*(int*)(history + 8) == bankEntry->m_address)) {
					OSReport(s__s_MUSIC_3_3d___0x_8_8X___0x_8_8_801e7d24, sRedEntryLogPrefix,
					         (int)*(short*)(bankEntry->m_address + 4), bankEntry->m_address, bankEntry->m_size, freeSize);
					fflush(__files + 1);
					matched = 1;
					break;
				}
				history += 0x10;
			} while (history < (unsigned int)m_musicBankBase + 0x40);

			if (matched == 0) {
				i = 0;
				do {
					if ((seBlockBase[i] != 0) && (bankEntry->m_address == seBlockBase[i])) {
						OSReport(s__s_SE_BLOCK___0x_8_8X___0x_8_8X___801e7d51, sRedEntryLogPrefix, bankEntry->m_address,
						         bankEntry->m_size, freeSize);
						fflush(__files + 1);
						matched = 1;
						break;
					}
					i++;
				} while (i < 4);
			}

			if (matched == 0) {
				history = (unsigned int)m_waveBankBase;
				do {
					if ((*(int*)(history + 0xC) != 0) && (*(int*)(history + 8) == bankEntry->m_address)) {
						OSReport(s__s_WAVE_4_4d___0x_8_8X___0x_8_8X_801e7d7c, sRedEntryLogPrefix,
						         (int)*(short*)(bankEntry->m_address + 2), bankEntry->m_address, bankEntry->m_size, freeSize);
						fflush(__files + 1);
						matched = 1;
						break;
					}
					history += 0x10;
				} while (history < (unsigned int)m_waveBankBase + 0x400);
			}

			if (matched == 0) {
				history = (unsigned int)m_seSepBankBase;
				do {
					if ((*(int*)(history + 0xC) != 0) && (*(int*)(history + 8) == bankEntry->m_address)) {
						OSReport(s__s_SE_6_6d___0x_8_8X___0x_8_8X___801e7da8, sRedEntryLogPrefix,
						         *(int*)(bankEntry->m_address + 8), bankEntry->m_address, bankEntry->m_size, freeSize);
						fflush(__files + 1);
						matched = 1;
						break;
					}
					history += 0x10;
				} while (history < (unsigned int)m_seSepBankBase + 0x1000);
			}

			if (matched == 0) {
				OSReport(s__s____________0x_8_8X___0x_8_8X___801e7dd2, sRedEntryLogPrefix, bankEntry->m_address, bankEntry->m_size,
				         freeSize);
				fflush(__files + 1);
			}

			if (maxFreeSize < (bankEntry->m_address - nextAddress)) {
				maxFreeSize = bankEntry->m_address - nextAddress;
			}

			entryCount++;
			totalSize += bankEntry->m_size;
			nextAddress = bankEntry->m_address + bankEntry->m_size;
		}

		bankEntry++;
	} while (bankEntry < memoryBank + 0x400);

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
