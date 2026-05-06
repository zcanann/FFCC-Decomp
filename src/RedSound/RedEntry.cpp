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

enum RedEntryHeaderSignature {
	REDSOUND_ENTRY_MUSIC_SIGNATURE_0 = 'B',
	REDSOUND_ENTRY_MUSIC_SIGNATURE_1 = 'G',
	REDSOUND_ENTRY_MUSIC_SIGNATURE_2 = 'M',
	REDSOUND_ENTRY_SESEP_SIGNATURE_0 = 'S',
	REDSOUND_ENTRY_SESEP_SIGNATURE_1 = 'e',
	REDSOUND_ENTRY_SESEP_SIGNATURE_2 = 'S',
	REDSOUND_ENTRY_SESEP_SIGNATURE_3 = 'e',
	REDSOUND_ENTRY_SESEP_SIGNATURE_4 = 'p',
};

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

	m_waveBankBase = RedNew(REDSOUND_WAVE_BANK_SIZE);
	m_seSepBankBase = RedNew(REDSOUND_SESEP_BANK_SIZE);
	m_musicBankBase = RedNew(REDSOUND_MUSIC_BANK_SIZE);

	memset((void*)m_waveBankBase, 0, REDSOUND_WAVE_BANK_SIZE);
	iVar2 = 0;
	do {
		reinterpret_cast<RedHistoryBANK*>(m_waveBankBase)[iVar2].m_id = REDSOUND_HISTORY_BANK_EMPTY_ID;
		iVar2 = iVar2 + 1;
	} while (iVar2 < REDSOUND_WAVE_BANK_ENTRY_COUNT);

	memset((void*)m_seSepBankBase, 0, REDSOUND_SESEP_BANK_SIZE);
	iVar2 = 0;
	do {
		reinterpret_cast<RedHistoryBANK*>(m_seSepBankBase)[iVar2].m_id = REDSOUND_HISTORY_BANK_EMPTY_ID;
		iVar2 = iVar2 + 1;
	} while (iVar2 < REDSOUND_SESEP_BANK_ENTRY_COUNT);

	memset((void*)m_musicBankBase, 0, REDSOUND_MUSIC_BANK_SIZE);
	iVar2 = 0;
	do {
		reinterpret_cast<RedHistoryBANK*>(m_musicBankBase)[iVar2].m_id = REDSOUND_HISTORY_BANK_EMPTY_ID;
		iVar2 = iVar2 + 1;
	} while (iVar2 < REDSOUND_MUSIC_BANK_ENTRY_COUNT);

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
	RedHistoryBANK* history = &reinterpret_cast<RedHistoryBANK*>(m_waveBankBase)[REDSOUND_WAVE_PRIMARY_BANK_ENTRY_COUNT];

	do {
		if (history->m_historyNo >= historyNo) {
			history->m_historyNo = history->m_historyNo + 1;
		}
		history += 1;
	} while (history < reinterpret_cast<RedHistoryBANK*>(m_waveBankBase) + REDSOUND_WAVE_BANK_ENTRY_COUNT);
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
		} while (history < reinterpret_cast<RedHistoryBANK*>(m_waveBankBase) + REDSOUND_WAVE_BANK_ENTRY_COUNT);
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
		} while (history < reinterpret_cast<RedHistoryBANK*>(m_waveBankBase) + REDSOUND_WAVE_BANK_ENTRY_COUNT);

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

	while (waveBank < reinterpret_cast<RedHistoryBANK*>(m_waveBankBase) + REDSOUND_WAVE_BANK_ENTRY_COUNT) {
		if ((waveBank->m_size != 0) && (waveBank->m_id == waveNo)) {
			return waveBank - reinterpret_cast<RedHistoryBANK*>(m_waveBankBase);
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
	RedSoundCONTROL* control = p_SoundControlBuffer + REDSOUND_CONTROL_MUSIC_SECONDARY;

	do {
		if ((control->m_musicId >= 0) && (control->m_waveNo == waveNo)) {
			found = 1;
			MusicStop(control->m_musicId);
		}
		control--;
	} while ((u32)control >= (u32)p_SoundControlBuffer);

	control = p_SoundControlBuffer + REDSOUND_CONTROL_SE;
	RedTrackDATA* track = control->m_tracks;
	do {
		if (((u32)track->m_command != 0) && (track->m_waveBankData != 0) &&
		    (track->m_waveBankData->m_waveNo == waveNo)) {
			found = 1;
			SeStopID(track->m_seId);
		}
		track += 1;
	} while (track < control->m_tracks + REDSOUND_SE_TRACK_COUNT);

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
	RedHistoryBANK* history = &reinterpret_cast<RedHistoryBANK*>(m_waveBankBase)[REDSOUND_WAVE_PRIMARY_BANK_ENTRY_COUNT];

	do {
		if (history->m_historyNo > maxBankSize) {
			arAddress = reinterpret_cast<RedWaveHeadWD*>(history->m_data)->m_aramAddress;
			if ((arAddress >= offset) && (arAddress < maxSize)) {
				maxBankSize = history->m_historyNo;
				selected = history;
			}
		}
		history += 1;
	} while (history < reinterpret_cast<RedHistoryBANK*>(m_waveBankBase) + REDSOUND_WAVE_BANK_ENTRY_COUNT);

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

	if ((waveNo >= REDSOUND_WAVE_LARGE_RANGE_BEGIN) && (waveNo < REDSOUND_WAVE_LARGE_RANGE_END)) {
		if (waveHead->m_loadSize <= REDSOUND_WAVE_LARGE_LOAD_STEP) {
			waveHead->m_loadSize = REDSOUND_WAVE_LARGE_LOAD_STEP;
		} else if (waveHead->m_loadSize <= REDSOUND_WAVE_LARGE_REGION_SIZE) {
			waveHead->m_loadSize = REDSOUND_WAVE_LARGE_REGION_SIZE;
		}
	} else if ((waveNo >= REDSOUND_WAVE_STAGE_RANGE_BEGIN) && (waveNo < REDSOUND_WAVE_STAGE_RANGE_END)) {
		waveHead->m_loadSize += REDSOUND_WAVE_STAGE_LOAD_BLOCK_ROUND;
		int blocks = waveHead->m_loadSize / REDSOUND_WAVE_STAGE_LOAD_BLOCK_SIZE;
		blocks += blocks >> 0x1F;
		waveHead->m_loadSize = blocks * REDSOUND_WAVE_STAGE_LOAD_BLOCK_SIZE;
	} else if (((waveNo >= REDSOUND_WAVE_FIXED_RANGE0_BEGIN) && (waveNo < REDSOUND_WAVE_FIXED_RANGE0_END)) ||
	           ((waveNo >= REDSOUND_WAVE_FIXED_RANGE1_BEGIN) && (waveNo < REDSOUND_WAVE_FIXED_RANGE1_END)) ||
	           (waveNo == REDSOUND_WAVE_FIXED_SINGLE)) {
		waveHead->m_loadSize = REDSOUND_WAVE_FIXED_REGION_SIZE;
	}

	int minOffset;
	int maxOffset;
	if ((waveNo >= REDSOUND_WAVE_LARGE_RANGE_BEGIN) && (waveNo < REDSOUND_WAVE_LARGE_RANGE_END)) {
		minOffset = REDSOUND_WAVE_LARGE_REGION_OFFSET;
		maxOffset = minOffset + REDSOUND_WAVE_LARGE_REGION_SIZE;
	} else if (((waveNo >= REDSOUND_WAVE_FIXED_RANGE0_BEGIN) && (waveNo < REDSOUND_WAVE_FIXED_RANGE0_END)) ||
	           ((waveNo >= REDSOUND_WAVE_FIXED_RANGE1_BEGIN) && (waveNo < REDSOUND_WAVE_FIXED_RANGE1_END)) ||
	           (waveNo == REDSOUND_WAVE_FIXED_SINGLE)) {
		minOffset = REDSOUND_WAVE_FIXED_REGION_OFFSET;
		maxOffset = minOffset + REDSOUND_WAVE_FIXED_REGION_SIZE;
	} else {
		minOffset = 0;
		maxOffset = minOffset + REDSOUND_WAVE_DEFAULT_REGION_SIZE;
	}

	do {
		RedHistoryBANK* historyBank;
		if (waveBankNo < 0) {
			historyBank = &reinterpret_cast<RedHistoryBANK*>(m_waveBankBase)[REDSOUND_WAVE_PRIMARY_BANK_ENTRY_COUNT];
			while ((historyBank->m_size != 0) &&
			       (historyBank < reinterpret_cast<RedHistoryBANK*>(m_waveBankBase) + REDSOUND_WAVE_BANK_ENTRY_COUNT)) {
				historyBank += 1;
			}
		} else {
			waveBankNo &= REDSOUND_WAVE_PRIMARY_BANK_MASK;
			historyBank = &reinterpret_cast<RedHistoryBANK*>(m_waveBankBase)[waveBankNo];
			if (historyBank->m_size != 0) {
				WaveDelete(historyBank);
			}
		}

		int arAddress;
		if ((historyBank < reinterpret_cast<RedHistoryBANK*>(m_waveBankBase) + REDSOUND_WAVE_BANK_ENTRY_COUNT) &&
		    ((arAddress = RedNewA(waveHead->m_loadSize, minOffset, maxOffset)) != 0)) {
			int copySize = ((waveHead->m_tableCount * REDSOUND_WAVE_TABLE_ENTRY_SIZE) +
			                (REDSOUND_WAVE_TABLE_ALIGN - 1)) &
			               REDSOUND_WAVE_TABLE_ALIGN_MASK;
			copySize += waveHead->m_toneCount * REDSOUND_WAVE_TONE_ENTRY_SIZE + REDSOUND_WAVE_HEADER_COPY_BASE_SIZE;
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
				*(int*)(m_waveBankBase + waveBankNo * REDSOUND_HISTORY_BANK_ENTRY_SIZE + REDSOUND_HISTORY_BANK_ID_OFFSET) =
				    *(int*)(m_waveBankBase + historyNo * REDSOUND_HISTORY_BANK_ENTRY_SIZE + REDSOUND_HISTORY_BANK_ID_OFFSET);
				*(int*)(m_waveBankBase + waveBankNo * REDSOUND_HISTORY_BANK_ENTRY_SIZE + REDSOUND_HISTORY_BANK_HISTORY_NO_OFFSET) =
				    *(int*)(m_waveBankBase + historyNo * REDSOUND_HISTORY_BANK_ENTRY_SIZE + REDSOUND_HISTORY_BANK_HISTORY_NO_OFFSET);
				*(int*)(m_waveBankBase + waveBankNo * REDSOUND_HISTORY_BANK_ENTRY_SIZE + REDSOUND_HISTORY_BANK_DATA_OFFSET) =
				    *(int*)(m_waveBankBase + historyNo * REDSOUND_HISTORY_BANK_ENTRY_SIZE + REDSOUND_HISTORY_BANK_DATA_OFFSET);
				*(int*)(m_waveBankBase + waveBankNo * REDSOUND_HISTORY_BANK_ENTRY_SIZE + REDSOUND_HISTORY_BANK_SIZE_OFFSET) =
				    *(int*)(m_waveBankBase + historyNo * REDSOUND_HISTORY_BANK_ENTRY_SIZE + REDSOUND_HISTORY_BANK_SIZE_OFFSET);
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
			    ((((waveHead->m_tableCount * REDSOUND_WAVE_TABLE_ENTRY_SIZE) + (REDSOUND_WAVE_TABLE_ALIGN - 1)) &
			      REDSOUND_WAVE_TABLE_ALIGN_MASK) +
			     waveHead->m_toneCount * REDSOUND_WAVE_TONE_ENTRY_SIZE) +
			    REDSOUND_WAVE_HEADER_COPY_BASE_SIZE;
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

		int dmaID = RedDmaEntry(REDSOUND_DMA_FLAGS_WAVE_LOAD, 0, (int)waveDataTop, waveAddress, transferSize, 0, 0);
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
			     historyBank < reinterpret_cast<RedHistoryBANK*>(m_waveBankBase) + REDSOUND_WAVE_BANK_ENTRY_COUNT; historyBank += 1) {
				if (historyBank->m_id >= 0) {
					WaveDelete(historyBank);
				}
			}
		} else if (waveNo == -2) {
			for (historyBank = &reinterpret_cast<RedHistoryBANK*>(m_waveBankBase)[REDSOUND_WAVE_PRIMARY_BANK_ENTRY_COUNT];
			     historyBank < reinterpret_cast<RedHistoryBANK*>(m_waveBankBase) + REDSOUND_WAVE_BANK_ENTRY_COUNT; historyBank += 1) {
				if (historyBank->m_id >= 0) {
					WaveDelete(historyBank);
				}
			}
		} else if (waveNo == -3) {
			for (historyBank = &reinterpret_cast<RedHistoryBANK*>(m_waveBankBase)[REDSOUND_WAVE_PRIMARY_BANK_ENTRY_COUNT];
			     historyBank < reinterpret_cast<RedHistoryBANK*>(m_waveBankBase) + REDSOUND_WAVE_BANK_ENTRY_COUNT; historyBank += 1) {
				if ((historyBank->m_id >= 0) && (0 < historyBank->m_historyNo)) {
					WaveDelete(historyBank);
				}
			}
		}
	} else {
		waveNo = SearchWaveSequence(waveNo);
		if (waveNo >= 0) {
			WaveDelete(&reinterpret_cast<RedHistoryBANK*>(m_waveBankBase)[waveNo]);
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

	for (historyBank = &reinterpret_cast<RedHistoryBANK*>(m_waveBankBase)[REDSOUND_WAVE_PRIMARY_BANK_ENTRY_COUNT];
	     historyBank < reinterpret_cast<RedHistoryBANK*>(m_waveBankBase) + REDSOUND_WAVE_BANK_ENTRY_COUNT; historyBank += 1) {
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
			     historyBank < reinterpret_cast<RedHistoryBANK*>(m_waveBankBase) + REDSOUND_WAVE_BANK_ENTRY_COUNT; historyBank += 1) {
				if (!(historyBank->m_id < 0)) {
					WaveDelete(historyBank);
				}
			}
		} else if (waveBankNo == -2) {
			for (historyBank = &reinterpret_cast<RedHistoryBANK*>(m_waveBankBase)[REDSOUND_WAVE_PRIMARY_BANK_ENTRY_COUNT];
			     historyBank < reinterpret_cast<RedHistoryBANK*>(m_waveBankBase) + REDSOUND_WAVE_BANK_ENTRY_COUNT; historyBank += 1) {
				if (!(historyBank->m_id < 0)) {
					WaveDelete(historyBank);
				}
			}
		} else if (waveBankNo == -3) {
			for (historyBank = &reinterpret_cast<RedHistoryBANK*>(m_waveBankBase)[REDSOUND_WAVE_PRIMARY_BANK_ENTRY_COUNT];
			     historyBank < reinterpret_cast<RedHistoryBANK*>(m_waveBankBase) + REDSOUND_WAVE_BANK_ENTRY_COUNT; historyBank += 1) {
				if (!(historyBank->m_id < 0) && (0 < historyBank->m_historyNo)) {
					WaveDelete(historyBank);
				}
			}
		}
	} else if ((waveBankNo >= 0) && (waveBankNo < REDSOUND_WAVE_PRIMARY_BANK_ENTRY_COUNT)) {
		WaveDelete(&reinterpret_cast<RedHistoryBANK*>(m_waveBankBase)[waveBankNo]);
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
	if ((waveNo >= 0) && (waveNo < REDSOUND_WAVE_PRIMARY_BANK_ENTRY_COUNT))
	{
		return reinterpret_cast<int>(&reinterpret_cast<RedHistoryBANK*>(m_waveBankBase)[waveNo]);
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
	} while (waveBank < reinterpret_cast<RedHistoryBANK*>(m_waveBankBase) + REDSOUND_WAVE_BANK_ENTRY_COUNT);

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
		WaveHistoryChoice(&reinterpret_cast<RedHistoryBANK*>(m_waveBankBase)[waveNo]);
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
	RedTrackDATA* track;

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
			RedTrackDATA** trackHead = &p_SoundControlBuffer[REDSOUND_CONTROL_SE].m_tracks;
			track = *trackHead;
			do {
				if (((u32)track->m_command != 0) && (track->m_waveBankData != 0) &&
				    (track->m_waveBankData->m_waveNo == waveNo)) {
					used++;
					break;
				}
				track++;
			} while (track < *trackHead + REDSOUND_SE_TRACK_COUNT);
		}
		if (used == 0) {
			used = SearchWaveSequence(waveNo);
			if ((used >= REDSOUND_WAVE_PRIMARY_BANK_ENTRY_COUNT) &&
			    (reinterpret_cast<RedHistoryBANK*>(m_waveBankBase)[used].m_historyNo == 0)) {
				WaveHistoryAdd(REDSOUND_WAVE_RELEASE_HISTORY_NO);
				reinterpret_cast<RedHistoryBANK*>(m_waveBankBase)[used].m_historyNo = REDSOUND_WAVE_RELEASE_HISTORY_NO;
			}
		}
	} else {
		used = SearchWaveSequence(waveNo);
		if ((used >= REDSOUND_WAVE_PRIMARY_BANK_ENTRY_COUNT) &&
		    (reinterpret_cast<RedHistoryBANK*>(m_waveBankBase)[used].m_historyNo != 0)) {
			WaveHistoryDelete(reinterpret_cast<RedHistoryBANK*>(m_waveBankBase)[used].m_historyNo);
			reinterpret_cast<RedHistoryBANK*>(m_waveBankBase)[used].m_historyNo = 0;
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
				int blockEnd = bank->m_address + bank->m_size;
				if (bank[REDSOUND_MEMORY_NEXT_BLOCK_INDEX].m_size > 0) {
					freeSize = bank[REDSOUND_MEMORY_NEXT_BLOCK_INDEX].m_address - blockEnd;
				} else {
					freeSize = aBufferEnd - blockEnd;
				}

				RedHistoryBANK* history = reinterpret_cast<RedHistoryBANK*>(m_waveBankBase);
				do {
					if ((history->m_size != 0) && (((RedWaveHeadWD*)history->m_data)->m_aramAddress == bank->m_address)) {
						break;
					}
					history += 1;
				} while (history < reinterpret_cast<RedHistoryBANK*>(m_waveBankBase) + REDSOUND_WAVE_BANK_ENTRY_COUNT);

				if (history < reinterpret_cast<RedHistoryBANK*>(m_waveBankBase) + REDSOUND_WAVE_BANK_ENTRY_COUNT) {
					if (history < reinterpret_cast<RedHistoryBANK*>(m_waveBankBase) + REDSOUND_WAVE_PRIMARY_BANK_ENTRY_COUNT) {
						int index = reinterpret_cast<int>(history) - m_waveBankBase;
						OSReport(s__s__2d___WAVE_4_4d___0x_8_8X___0_801e7a53, sRedEntryLogPrefix,
						         index / REDSOUND_HISTORY_BANK_ENTRY_SIZE,
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
					int bankIndex = (int)bank - (int)aBankAddress;
					OSReport(s__s______________0x_8_8X___0x_8_8_801e7aca, sRedEntryLogPrefix, bank->m_address, bank->m_size, freeSize,
					         bankIndex / REDSOUND_MEMORY_BLOCK_SIZE);
					fflush(__files + 1);
				}

				if (maxFreeSize < bank->m_address - aBufferAddress) {
					maxFreeSize = bank->m_address - aBufferAddress;
				}
				totalSize += bank->m_size;
				aBufferAddress = bank->m_address + bank->m_size;
			}
			bank++;
		} while (bank < aBankAddress + REDSOUND_MEMORY_BANK_BLOCK_COUNT);

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
	} while (history < reinterpret_cast<RedHistoryBANK*>(m_seSepBankBase) + REDSOUND_SESEP_BANK_ENTRY_COUNT);
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
		} while (history < reinterpret_cast<RedHistoryBANK*>(m_seSepBankBase) + REDSOUND_SESEP_BANK_ENTRY_COUNT);
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
		} while (history < reinterpret_cast<RedHistoryBANK*>(m_seSepBankBase) + REDSOUND_SESEP_BANK_ENTRY_COUNT);
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
				return seSepBank - reinterpret_cast<RedHistoryBANK*>(m_seSepBankBase);
			}
			seSepBank += 1;
		} while (seSepBank < reinterpret_cast<RedHistoryBANK*>(m_seSepBankBase) + REDSOUND_SESEP_BANK_ENTRY_COUNT);
	} else {
		do {
			if ((seSepBank->m_size != 0) && (seSepBank->m_id == seNo)) {
				return seSepBank - reinterpret_cast<RedHistoryBANK*>(m_seSepBankBase);
			}
			seSepBank += 1;
		} while (seSepBank < reinterpret_cast<RedHistoryBANK*>(m_seSepBankBase) + REDSOUND_SESEP_BANK_ENTRY_COUNT);
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
	             static_cast<unsigned int>(reinterpret_cast<RedSeSepHEAD*>(bank->m_data)->m_waveNoHi) * REDSOUND_SESEP_WAVE_NO_HIGH_SCALE;

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
	RedHistoryBANK* selected = 0;
	int historyNo = 0;
	RedHistoryBANK* history = reinterpret_cast<RedHistoryBANK*>(m_seSepBankBase);

	do {
		if ((history->m_size != 0) && (historyNo < history->m_historyNo)) {
			historyNo = history->m_historyNo;
			selected = history;
		}
		history++;
	} while (history < reinterpret_cast<RedHistoryBANK*>(m_seSepBankBase) + REDSOUND_SESEP_BANK_ENTRY_COUNT);

	if (selected != 0) {
		SeSepMemoryFree(selected);
	}

	return selected;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
RedSeSepHEAD* CRedEntry::SeSepHeadAdd(RedSeSepHEAD* seSepHead)
{
	RedHistoryBANK* bank = reinterpret_cast<RedHistoryBANK*>(m_seSepBankBase);
	int result = 0;

	while ((bank->m_size != 0) &&
	       (bank < reinterpret_cast<RedHistoryBANK*>(m_seSepBankBase) + REDSOUND_SESEP_BANK_ENTRY_COUNT)) {
		bank += 1;
	}
	if (bank < reinterpret_cast<RedHistoryBANK*>(m_seSepBankBase) + REDSOUND_SESEP_BANK_ENTRY_COUNT) {
	} else {
		bank = SeSepOldDelete();
	}

	if ((bank != 0) &&
	    (bank < reinterpret_cast<RedHistoryBANK*>(m_seSepBankBase) + REDSOUND_SESEP_BANK_ENTRY_COUNT)) {
		bank->m_data = reinterpret_cast<int>(seSepHead);
		result = reinterpret_cast<int>(seSepHead);
		bank->m_size = seSepHead->m_sizeAndFlags & REDSOUND_SESEP_SIZE_MASK;
		bank->m_id = seSepHead->m_seNo;
		SeSepHistoryAdd();
		bank->m_historyNo = 1;
	}

	return reinterpret_cast<RedSeSepHEAD*>(result);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
RedSeSepHEAD* CRedEntry::SetSeSepData(RedSeSepHEAD* seSepHead)
{
	int result;

	if ((seSepHead->m_signature[0] != REDSOUND_ENTRY_SESEP_SIGNATURE_0) ||
	    (seSepHead->m_signature[1] != REDSOUND_ENTRY_SESEP_SIGNATURE_1) ||
	    (seSepHead->m_signature[2] != REDSOUND_ENTRY_SESEP_SIGNATURE_2) ||
	    (seSepHead->m_signature[3] != REDSOUND_ENTRY_SESEP_SIGNATURE_3) ||
	    (seSepHead->m_signature[4] != REDSOUND_ENTRY_SESEP_SIGNATURE_4)) {
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
		SeSepHistoryChoice(&reinterpret_cast<RedHistoryBANK*>(m_seSepBankBase)[result]);
		result = reinterpret_cast<RedHistoryBANK*>(m_seSepBankBase)[result].m_data;
	} else {
		result = reinterpret_cast<int>(SeSepHeadAdd(seSepHead));
		if (result == 0) {
			RedDelete(seSepHead);
		}
	}

	return reinterpret_cast<RedSeSepHEAD*>(result);
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
		} while (history < reinterpret_cast<RedHistoryBANK*>(m_seSepBankBase) + REDSOUND_SESEP_BANK_ENTRY_COUNT);
	} else {
		result = SearchSeSepSequence(seNo);
		if (result >= 0) {
			result = SeSepMemoryFree(&reinterpret_cast<RedHistoryBANK*>(m_seSepBankBase)[result]);
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
	} while (bank < reinterpret_cast<RedHistoryBANK*>(m_seSepBankBase) + REDSOUND_SESEP_BANK_ENTRY_COUNT);

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
	} while (seSepBank < reinterpret_cast<RedHistoryBANK*>(m_seSepBankBase) + REDSOUND_SESEP_BANK_ENTRY_COUNT);

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
		SeSepHistoryChoice(&reinterpret_cast<RedHistoryBANK*>(m_seSepBankBase)[seNo]);
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

		RedTrackDATA** trackHead = &p_SoundControlBuffer[REDSOUND_CONTROL_SE].m_tracks;
		RedTrackDATA* track = *trackHead;
		do {
			if (track->m_command != 0) {
				if ((track->m_seSepId & REDSOUND_SE_BLOCK_DATA_FLAG) != 0) {
					unsigned int seDataNo = (unsigned int)track->m_seSepId;
					int songNo = (int)(seDataNo & REDSOUND_SE_BLOCK_ENTRY_MASK) >> REDSOUND_SE_BLOCK_BANK_SHIFT;
					RedSeBlockHEAD* seBlock = p_SeBlockData[songNo];
					int seqBase = reinterpret_cast<int>(seBlock->m_entries);
					int seqInfo = seqBase + seBlock->m_seCount * REDSOUND_SE_BLOCK_ENTRY_SIZE;
					seqInfo += (*(unsigned int*)(seqBase + (seDataNo & REDSOUND_SE_BLOCK_SEQUENCE_MASK) * REDSOUND_SE_BLOCK_ENTRY_SIZE) &
					            REDSOUND_SE_BLOCK_ENTRY_MASK);
					int waveNo = reinterpret_cast<RedSeINFO*>(seqInfo)->m_waveNoHi * REDSOUND_SE_INFO_U16_HIGH_SCALE +
					             reinterpret_cast<RedSeINFO*>(seqInfo)->m_waveNoLo;
					int trackIndex =
					    (reinterpret_cast<int>(track) - reinterpret_cast<int>(*trackHead)) / REDSOUND_TRACK_SIZE;

					OSReport(s__s__2d____3_3u__3_3u___WAVE_4_4u_801e7bb2, sRedEntryLogPrefix,
					         trackIndex + REDSOUND_SE_VOICE_BASE_INDEX, songNo,
					         seDataNo & REDSOUND_SE_BLOCK_SEQUENCE_MASK, waveNo);
					fflush(__files + 1);
				} else {
					RedHistoryBANK* seSepBank = SearchSeSepBank(track->m_seSepId);
					int trackIndex =
					    (reinterpret_cast<int>(track) - reinterpret_cast<int>(*trackHead)) / REDSOUND_TRACK_SIZE;
					int waveNo = reinterpret_cast<RedSeSepHEAD*>(seSepBank->m_data)->m_waveNoHi * REDSOUND_SE_INFO_U16_HIGH_SCALE +
					             reinterpret_cast<RedSeSepHEAD*>(seSepBank->m_data)->m_waveNoLo;
					OSReport(s__s__2d___se_6_6u_sep___WAVE_4_4u_801e7bdc, sRedEntryLogPrefix,
					         trackIndex + REDSOUND_SE_VOICE_BASE_INDEX, track->m_seSepId, waveNo);
					fflush(__files + 1);
				}
			} else {
				int trackIndex =
				    (reinterpret_cast<int>(track) - reinterpret_cast<int>(*trackHead)) / REDSOUND_TRACK_SIZE;
				OSReport(s__s__2d_____801e7c01, sRedEntryLogPrefix,
				         trackIndex + REDSOUND_SE_VOICE_BASE_INDEX);
				fflush(__files + 1);
			}
			track += 1;
		} while (track < *trackHead + REDSOUND_SE_TRACK_COUNT);

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
	} while (history < reinterpret_cast<RedHistoryBANK*>(m_musicBankBase) + REDSOUND_MUSIC_BANK_ENTRY_COUNT);
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
		} while (history < reinterpret_cast<RedHistoryBANK*>(m_musicBankBase) + REDSOUND_MUSIC_BANK_ENTRY_COUNT);
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
		} while (history < reinterpret_cast<RedHistoryBANK*>(m_musicBankBase) + REDSOUND_MUSIC_BANK_ENTRY_COUNT);
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
			return musicBank - reinterpret_cast<RedHistoryBANK*>(m_musicBankBase);
		}
		musicBank += 1;
	} while (musicBank < reinterpret_cast<RedHistoryBANK*>(m_musicBankBase) + REDSOUND_MUSIC_BANK_ENTRY_COUNT);

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
	} while (history < reinterpret_cast<RedHistoryBANK*>(m_musicBankBase) + REDSOUND_MUSIC_BANK_ENTRY_COUNT);

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
	} while (history < reinterpret_cast<RedHistoryBANK*>(m_musicBankBase) + REDSOUND_MUSIC_BANK_ENTRY_COUNT);

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
	} while (musicBank < reinterpret_cast<RedHistoryBANK*>(m_musicBankBase) + REDSOUND_MUSIC_BANK_ENTRY_COUNT);

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
		MusicHistoryChoice(&reinterpret_cast<RedHistoryBANK*>(m_musicBankBase)[musicNo]);
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
				if (reinterpret_cast<RedHistoryBANK*>(m_musicBankBase)[musicSeq].m_historyNo == 0) {
					MusicHistoryAdd();
					reinterpret_cast<RedHistoryBANK*>(m_musicBankBase)[musicSeq].m_historyNo = 1;
				}
			}
		}
	} else {
		musicSeq = SearchMusicSequence(musicNo);
		if (musicSeq >= 0) {
			if (reinterpret_cast<RedHistoryBANK*>(m_musicBankBase)[musicSeq].m_historyNo != 0) {
				MusicHistoryDelete(reinterpret_cast<RedHistoryBANK*>(m_musicBankBase)[musicSeq].m_historyNo);
				reinterpret_cast<RedHistoryBANK*>(m_musicBankBase)[musicSeq].m_historyNo = 0;
			}
		}
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
RedMusicHEAD* CRedEntry::MusicHeadAdd(RedMusicHEAD* musicHead)
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

	return reinterpret_cast<RedMusicHEAD*>(result);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
RedMusicHEAD* CRedEntry::SetMusicData(RedMusicHEAD* musicHead)
{
	int result;

	if ((musicHead->m_signature[0] != REDSOUND_ENTRY_MUSIC_SIGNATURE_0) ||
	    (musicHead->m_signature[1] != REDSOUND_ENTRY_MUSIC_SIGNATURE_1) ||
	    (musicHead->m_signature[2] != REDSOUND_ENTRY_MUSIC_SIGNATURE_2)) {
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
		MusicHistoryChoice(&reinterpret_cast<RedHistoryBANK*>(m_musicBankBase)[result]);
		result = reinterpret_cast<RedHistoryBANK*>(m_musicBankBase)[result].m_data;
	} else {
		result = reinterpret_cast<int>(MusicHeadAdd(musicHead));
		if (result == 0) {
			RedDelete(musicHead);
		}
	}

	return reinterpret_cast<RedMusicHEAD*>(result);
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
	RedHistoryBANK* history;

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

	do {
		if (bankEntry->m_size != 0) {
			int matched = 0;
			int blockEnd = bankEntry->m_address + bankEntry->m_size;

			if (bankEntry[REDSOUND_MEMORY_NEXT_BLOCK_INDEX].m_size > 0) {
				freeSize = bankEntry[REDSOUND_MEMORY_NEXT_BLOCK_INDEX].m_address - blockEnd;
			} else {
				freeSize = bufferTop - blockEnd;
			}

			history = reinterpret_cast<RedHistoryBANK*>(m_musicBankBase);
			do {
				if ((history->m_size != 0) && (history->m_data == bankEntry->m_address)) {
					OSReport(s__s_MUSIC_3_3d___0x_8_8X___0x_8_8_801e7d24, sRedEntryLogPrefix,
					         reinterpret_cast<RedMusicHEAD*>(bankEntry->m_address)->m_musicNo, bankEntry->m_address,
					         bankEntry->m_size, freeSize);
					fflush(__files + 1);
					matched = 1;
					break;
				}
				history += 1;
			} while (history < reinterpret_cast<RedHistoryBANK*>(m_musicBankBase) + REDSOUND_MUSIC_BANK_ENTRY_COUNT);

			if (matched == 0) {
				i = 0;
				do {
					if ((p_SeBlockData[i] != 0) && (bankEntry->m_address == reinterpret_cast<int>(p_SeBlockData[i]))) {
						OSReport(s__s_SE_BLOCK___0x_8_8X___0x_8_8X___801e7d51, sRedEntryLogPrefix, bankEntry->m_address,
						         bankEntry->m_size, freeSize);
						fflush(__files + 1);
						matched = 1;
						break;
					}
					i++;
				} while (i < REDSOUND_SE_BLOCK_BANK_COUNT);
			}

			if (matched == 0) {
				history = reinterpret_cast<RedHistoryBANK*>(m_waveBankBase);
				do {
					if ((history->m_size != 0) && (history->m_data == bankEntry->m_address)) {
						OSReport(s__s_WAVE_4_4d___0x_8_8X___0x_8_8X_801e7d7c, sRedEntryLogPrefix,
						         reinterpret_cast<RedWaveHeadWD*>(bankEntry->m_address)->m_waveNo, bankEntry->m_address,
						         bankEntry->m_size, freeSize);
						fflush(__files + 1);
						matched = 1;
						break;
					}
					history += 1;
				} while (history < reinterpret_cast<RedHistoryBANK*>(m_waveBankBase) + REDSOUND_WAVE_BANK_ENTRY_COUNT);
			}

			if (matched == 0) {
				history = reinterpret_cast<RedHistoryBANK*>(m_seSepBankBase);
				do {
					if ((history->m_size != 0) && (history->m_data == bankEntry->m_address)) {
						OSReport(s__s_SE_6_6d___0x_8_8X___0x_8_8X___801e7da8, sRedEntryLogPrefix,
						         reinterpret_cast<RedSeSepHEAD*>(bankEntry->m_address)->m_seNo, bankEntry->m_address,
						         bankEntry->m_size, freeSize);
						fflush(__files + 1);
						matched = 1;
						break;
					}
					history += 1;
				} while (history < reinterpret_cast<RedHistoryBANK*>(m_seSepBankBase) + REDSOUND_SESEP_BANK_ENTRY_COUNT);
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
	} while (bankEntry < memoryBank + REDSOUND_MEMORY_BANK_BLOCK_COUNT);

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
