#include "ffcc/RedSound/RedEntry.h"
#include "ffcc/RedSound/RedCommand.h"
#include "ffcc/RedSound/RedDriver.h"
#include "ffcc/RedSound/RedMidiCtrl.h"
#include "ffcc/RedSound/RedGlobals.h"
#include "ffcc/RedSound/RedMemory.h"
#include "global.h"
#include <dolphin/os.h>
#include <string.h>

STATIC_ASSERT(offsetof(RedHistoryBANK, m_id) == REDSOUND_HISTORY_BANK_ID_OFFSET);
STATIC_ASSERT(offsetof(RedHistoryBANK, m_historyNo) == REDSOUND_HISTORY_BANK_HISTORY_NO_OFFSET);
STATIC_ASSERT(offsetof(RedHistoryBANK, m_data) == REDSOUND_HISTORY_BANK_DATA_OFFSET);
STATIC_ASSERT(offsetof(RedHistoryBANK, m_size) == REDSOUND_HISTORY_BANK_SIZE_OFFSET);
STATIC_ASSERT(sizeof(RedHistoryBANK) == REDSOUND_HISTORY_BANK_ENTRY_SIZE);
STATIC_ASSERT(REDSOUND_WAVE_PRIMARY_BANK_SIZE == REDSOUND_WAVE_PRIMARY_BANK_ALLOC_SIZE);
STATIC_ASSERT(REDSOUND_WAVE_HISTORY_BANK_SIZE == REDSOUND_WAVE_HISTORY_BANK_ALLOC_SIZE);
STATIC_ASSERT(REDSOUND_WAVE_HISTORY_BANK_OFFSET == REDSOUND_WAVE_PRIMARY_BANK_ALLOC_SIZE);
STATIC_ASSERT(REDSOUND_WAVE_PRIMARY_BANK_SIZE + REDSOUND_WAVE_HISTORY_BANK_SIZE == REDSOUND_WAVE_BANK_SIZE);
STATIC_ASSERT(REDSOUND_WAVE_BANK_SIZE == REDSOUND_WAVE_BANK_ALLOC_SIZE);
STATIC_ASSERT(REDSOUND_SESEP_BANK_SIZE == REDSOUND_SESEP_BANK_ALLOC_SIZE);
STATIC_ASSERT(REDSOUND_MUSIC_BANK_SIZE == REDSOUND_MUSIC_BANK_ALLOC_SIZE);
STATIC_ASSERT(REDSOUND_WAVE_BANK_SIZE + REDSOUND_SESEP_BANK_SIZE + REDSOUND_MUSIC_BANK_SIZE ==
              REDSOUND_ENTRY_BANK_ARENA_SIZE);
STATIC_ASSERT(REDSOUND_ENTRY_BANK_ARENA_SIZE == REDSOUND_ENTRY_BANK_ARENA_ALLOC_SIZE);
STATIC_ASSERT(sizeof(RedMusicHEAD) == REDSOUND_MUSIC_HEADER_SIZE);
STATIC_ASSERT(offsetof(RedMusicHEAD, m_signature) == REDSOUND_MUSIC_HEADER_SIGNATURE_OFFSET);
STATIC_ASSERT(sizeof(((RedMusicHEAD*)0)->m_signature) == REDSOUND_MUSIC_SIGNATURE_SIZE);
STATIC_ASSERT(offsetof(RedMusicHEAD, m_musicNo) == REDSOUND_MUSIC_HEADER_MUSIC_NO_OFFSET);
STATIC_ASSERT(offsetof(RedMusicHEAD, m_waveNo) == REDSOUND_MUSIC_HEADER_WAVE_NO_OFFSET);
STATIC_ASSERT(offsetof(RedMusicHEAD, m_trackCount) == REDSOUND_MUSIC_HEADER_TRACK_COUNT_OFFSET);
STATIC_ASSERT(offsetof(RedMusicHEAD, m_reverbKind) == REDSOUND_MUSIC_HEADER_REVERB_KIND_OFFSET);
STATIC_ASSERT(offsetof(RedMusicHEAD, m_reverbDepth) == REDSOUND_MUSIC_HEADER_REVERB_DEPTH_OFFSET);
STATIC_ASSERT(offsetof(RedMusicHEAD, m_flags) == REDSOUND_MUSIC_HEADER_FLAGS_OFFSET);
STATIC_ASSERT(offsetof(RedMusicHEAD, m_reserved0E) == REDSOUND_MUSIC_HEADER_RESERVED0E_OFFSET);
STATIC_ASSERT(sizeof(((RedMusicHEAD*)0)->m_reserved0E) == REDSOUND_MUSIC_HEADER_RESERVED0E_SIZE);
STATIC_ASSERT(offsetof(RedMusicHEAD, m_size) == REDSOUND_MUSIC_HEADER_DATA_SIZE_OFFSET);
STATIC_ASSERT(offsetof(RedMusicHEAD, m_playFlags) == REDSOUND_MUSIC_HEADER_PLAY_FLAGS_OFFSET);
STATIC_ASSERT(offsetof(RedMusicHEAD, m_reserved18) == REDSOUND_MUSIC_HEADER_RESERVED18_OFFSET);
STATIC_ASSERT(sizeof(((RedMusicHEAD*)0)->m_reserved18) == REDSOUND_MUSIC_HEADER_RESERVED18_SIZE);
STATIC_ASSERT(offsetof(RedMusicHEAD, m_reserved1C) == REDSOUND_MUSIC_HEADER_RESERVED1C_OFFSET);
STATIC_ASSERT(sizeof(((RedMusicHEAD*)0)->m_reserved1C) == REDSOUND_MUSIC_HEADER_RESERVED1C_SIZE);
STATIC_ASSERT(offsetof(RedMusicTrackBlock, m_sizeLo) == REDSOUND_MUSIC_TRACK_BLOCK_SIZE_LO_OFFSET);
STATIC_ASSERT(offsetof(RedMusicTrackBlock, m_sizeHi0) == REDSOUND_MUSIC_TRACK_BLOCK_SIZE_HI0_OFFSET);
STATIC_ASSERT(offsetof(RedMusicTrackBlock, m_sizeHi1) == REDSOUND_MUSIC_TRACK_BLOCK_SIZE_HI1_OFFSET);
STATIC_ASSERT(offsetof(RedMusicTrackBlock, m_sizeHi2) == REDSOUND_MUSIC_TRACK_BLOCK_SIZE_HI2_OFFSET);
STATIC_ASSERT(offsetof(RedMusicTrackBlock, m_command) == REDSOUND_MUSIC_TRACK_BLOCK_COMMAND_OFFSET);
STATIC_ASSERT(sizeof(RedMusicTrackBlock) == REDSOUND_MUSIC_TRACK_BLOCK_MIN_SIZE);
STATIC_ASSERT(REDSOUND_MUSIC_TRACK_BLOCK_COMMAND_OFFSET + sizeof(((RedMusicTrackBlock*)0)->m_command) ==
              REDSOUND_MUSIC_TRACK_BLOCK_MIN_SIZE);
STATIC_ASSERT(offsetof(RedSeSepHEAD, m_signature) == REDSOUND_SESEP_SIGNATURE_OFFSET);
STATIC_ASSERT(sizeof(((RedSeSepHEAD*)0)->m_signature) == REDSOUND_SESEP_SIGNATURE_SIZE);
STATIC_ASSERT(offsetof(RedSeSepHEAD, m_seNo) == REDSOUND_SESEP_SE_NO_OFFSET);
STATIC_ASSERT(offsetof(RedSeSepHEAD, m_sizeAndFlags) == REDSOUND_SESEP_SIZE_AND_FLAGS_OFFSET);
STATIC_ASSERT(offsetof(RedSeSepHEAD, m_seInfoFlags) == REDSOUND_SESEP_INFO_OFFSET);
STATIC_ASSERT(offsetof(RedSeSepHEAD, m_waveNoLo) == REDSOUND_SESEP_WAVE_NO_LO_OFFSET);
STATIC_ASSERT(offsetof(RedSeSepHEAD, m_waveNoHi) == REDSOUND_SESEP_WAVE_NO_HI_OFFSET);
STATIC_ASSERT(offsetof(RedSeSepHEAD, m_reserved13) == REDSOUND_SESEP_RESERVED13_OFFSET);
STATIC_ASSERT(sizeof(((RedSeSepHEAD*)0)->m_reserved13) == REDSOUND_SESEP_RESERVED13_SIZE);
STATIC_ASSERT(sizeof(RedSeSepHEAD) == REDSOUND_SESEP_STRUCT_SIZE);
STATIC_ASSERT(REDSOUND_SESEP_INFO_OFFSET == REDSOUND_SESEP_HEADER_SIZE);
STATIC_ASSERT(REDSOUND_SESEP_RESERVED13_OFFSET + REDSOUND_SESEP_RESERVED13_SIZE == REDSOUND_SESEP_STRUCT_SIZE);
STATIC_ASSERT(offsetof(RedSeInfoSequence, m_offsetLo) == REDSOUND_SE_INFO_SEQUENCE_OFFSET_LO_OFFSET);
STATIC_ASSERT(offsetof(RedSeInfoSequence, m_offsetHiAndFlags) == REDSOUND_SE_INFO_SEQUENCE_OFFSET_HI_AND_FLAGS_OFFSET);
STATIC_ASSERT(sizeof(RedSeInfoSequence) == REDSOUND_SE_INFO_SEQUENCE_ENTRY_SIZE);
STATIC_ASSERT(offsetof(RedSeINFO, m_flagsAndCount) == REDSOUND_SE_INFO_FLAGS_AND_COUNT_OFFSET);
STATIC_ASSERT(offsetof(RedSeINFO, m_waveNoLo) == REDSOUND_SE_INFO_WAVE_NO_LO_OFFSET);
STATIC_ASSERT(offsetof(RedSeINFO, m_waveNoHi) == REDSOUND_SE_INFO_WAVE_NO_HI_OFFSET);
STATIC_ASSERT(offsetof(RedSeINFO, m_eraseTrack) == REDSOUND_SE_INFO_ERASE_TRACK_OFFSET);
STATIC_ASSERT(offsetof(RedSeINFO, m_attrMask) == REDSOUND_SE_INFO_ATTR_MASK_OFFSET);
STATIC_ASSERT(offsetof(RedSeINFO, m_sequence) == REDSOUND_SE_INFO_SEQUENCE_OFFSET);
STATIC_ASSERT(sizeof(RedSeINFO) == REDSOUND_SE_INFO_MIN_SIZE);
STATIC_ASSERT(REDSOUND_SE_INFO_SEQUENCE_OFFSET + REDSOUND_SE_INFO_SEQUENCE_ENTRY_SIZE ==
              REDSOUND_SE_INFO_MIN_SIZE);
STATIC_ASSERT(offsetof(RedSeBlockHEAD, m_signature) == REDSOUND_SE_BLOCK_SIGNATURE_OFFSET);
STATIC_ASSERT(sizeof(((RedSeBlockHEAD*)0)->m_signature) == REDSOUND_SE_BLOCK_SIGNATURE_SIZE);
STATIC_ASSERT(offsetof(RedSeBlockHEAD, m_reserved08) == REDSOUND_SE_BLOCK_RESERVED08_OFFSET);
STATIC_ASSERT(sizeof(((RedSeBlockHEAD*)0)->m_reserved08) == REDSOUND_SE_BLOCK_RESERVED08_SIZE);
STATIC_ASSERT(offsetof(RedSeBlockHEAD, m_seCount) == REDSOUND_SE_BLOCK_SE_COUNT_OFFSET);
STATIC_ASSERT(offsetof(RedSeBlockHEAD, m_size) == REDSOUND_SE_BLOCK_SIZE_OFFSET);
STATIC_ASSERT(offsetof(RedSeBlockHEAD, m_entries) == REDSOUND_SE_BLOCK_ENTRIES_OFFSET);
STATIC_ASSERT(sizeof(RedSeBlockHEAD) == REDSOUND_SE_BLOCK_STRUCT_SIZE);
STATIC_ASSERT(REDSOUND_SE_BLOCK_ENTRIES_OFFSET == REDSOUND_SE_BLOCK_HEADER_SIZE);
STATIC_ASSERT(REDSOUND_SE_BLOCK_RESERVED08_OFFSET + REDSOUND_SE_BLOCK_RESERVED08_SIZE ==
              REDSOUND_SE_BLOCK_SE_COUNT_OFFSET);
STATIC_ASSERT(REDSOUND_SE_BLOCK_ENTRIES_OFFSET + REDSOUND_SE_BLOCK_ENTRY_SIZE ==
              REDSOUND_SE_BLOCK_STRUCT_SIZE);
STATIC_ASSERT(offsetof(RedWaveHeadWD, m_signature) == REDSOUND_WAVE_HEAD_SIGNATURE_OFFSET);
STATIC_ASSERT(sizeof(((RedWaveHeadWD*)0)->m_signature) == REDSOUND_WAVE_SIGNATURE_SIZE);
STATIC_ASSERT(offsetof(RedWaveHeadWD, m_waveNo) == REDSOUND_WAVE_HEAD_WAVE_NO_OFFSET);
STATIC_ASSERT(offsetof(RedWaveHeadWD, m_waveSize) == REDSOUND_WAVE_HEAD_WAVE_SIZE_OFFSET);
STATIC_ASSERT(offsetof(RedWaveHeadWD, m_tableCount) == REDSOUND_WAVE_HEAD_TABLE_COUNT_OFFSET);
STATIC_ASSERT(offsetof(RedWaveHeadWD, m_toneCount) == REDSOUND_WAVE_HEAD_TONE_COUNT_OFFSET);
STATIC_ASSERT(offsetof(RedWaveHeadWD, m_aramAddress) == REDSOUND_WAVE_HEAD_ARAM_ADDRESS_OFFSET);
STATIC_ASSERT(offsetof(RedWaveHeadWD, m_loadSize) == REDSOUND_WAVE_HEAD_LOAD_SIZE_OFFSET);
STATIC_ASSERT(offsetof(RedWaveHeadWD, m_reserved18) == REDSOUND_WAVE_HEAD_RESERVED18_OFFSET);
STATIC_ASSERT(sizeof(((RedWaveHeadWD*)0)->m_reserved18) == REDSOUND_WAVE_HEAD_RESERVED18_SIZE);
STATIC_ASSERT(offsetof(RedWaveHeadWD, m_waveOffsets) == REDSOUND_WAVE_HEAD_OFFSETS_OFFSET);
STATIC_ASSERT(sizeof(RedWaveHeadWD) == REDSOUND_WAVE_HEAD_MIN_SIZE);
STATIC_ASSERT(REDSOUND_WAVE_HEADER_COPY_BASE_SIZE == REDSOUND_WAVE_HEAD_OFFSETS_OFFSET);
STATIC_ASSERT(REDSOUND_WAVE_HEAD_RESERVED18_OFFSET + REDSOUND_WAVE_HEAD_RESERVED18_SIZE ==
              REDSOUND_WAVE_HEAD_OFFSETS_OFFSET);
STATIC_ASSERT(REDSOUND_WAVE_HEAD_OFFSETS_OFFSET + REDSOUND_WAVE_TABLE_ENTRY_SIZE ==
              REDSOUND_WAVE_HEAD_MIN_SIZE);
STATIC_ASSERT(REDSOUND_WAVE_TONE_ENTRY_SIZE == REDSOUND_WAVE_DATA_SIZE);
STATIC_ASSERT(offsetof(RedWaveAramLayout, m_defaultRegion) == REDSOUND_WAVE_DEFAULT_REGION_OFFSET);
STATIC_ASSERT(sizeof(((RedWaveAramLayout*)0)->m_defaultRegion) == REDSOUND_WAVE_DEFAULT_REGION_SIZE);
STATIC_ASSERT(offsetof(RedWaveAramLayout, m_fixedRegion) == REDSOUND_WAVE_FIXED_REGION_OFFSET);
STATIC_ASSERT(sizeof(((RedWaveAramLayout*)0)->m_fixedRegion) == REDSOUND_WAVE_FIXED_REGION_SIZE);
STATIC_ASSERT(offsetof(RedWaveAramLayout, m_largeRegion) == REDSOUND_WAVE_LARGE_REGION_OFFSET);
STATIC_ASSERT(sizeof(((RedWaveAramLayout*)0)->m_largeRegion) == REDSOUND_WAVE_LARGE_REGION_SIZE);
STATIC_ASSERT(offsetof(CRedEntry, m_waveBankBase) == REDSOUND_ENTRY_WAVE_BANK_BASE_OFFSET);
STATIC_ASSERT(offsetof(CRedEntry, m_seSepBankBase) == REDSOUND_ENTRY_SESEP_BANK_BASE_OFFSET);
STATIC_ASSERT(offsetof(CRedEntry, m_musicBankBase) == REDSOUND_ENTRY_MUSIC_BANK_BASE_OFFSET);
STATIC_ASSERT(offsetof(CRedEntry, m_waveLoadNo) == REDSOUND_ENTRY_WAVE_LOAD_NO_OFFSET);
STATIC_ASSERT(offsetof(CRedEntry, m_waveLoadSize) == REDSOUND_ENTRY_WAVE_LOAD_SIZE_OFFSET);
STATIC_ASSERT(offsetof(CRedEntry, m_waveLoadAddress) == REDSOUND_ENTRY_WAVE_LOAD_ADDRESS_OFFSET);
STATIC_ASSERT(sizeof(CRedEntry) == REDSOUND_ENTRY_SIZE);

static const char sRedEntryColoredBlankLineFmt[] = "%s%s                                     %s\n";
static const char sRedEntryLogPrefix[] = "\x1B[7;34mSound\x1B[0m:";
static const char sRedEntryErrorBannerFmt[] = "%s%s ********       ERROR       ******** %s\n";
static const char sRedEntryEraseUsingWaveDataFmt[] =
    "%s%s Erase Using Wave Data !! (WAVE%4.4d) %s\n";
static const char sRedEntryWaveHeaderBrokenFmt[] = "%s%sWave-Header was broken.%s\n";
static const char sRedEntryNoWaveMemoryFreeAreaFmt[] =
    "%s%sNOT HAVE A-MEMORY FREE AREA (WAVE%4.4u:0x%6.6X need).%s\n";
static const char sRedEntryWaveEntryFmt[] = "%s%sWave Entry. (wave%4.4u)%s\n";
static const char sRedEntryAMemoryInfoHeaderFmt[] = "%s==== AMemory Information ====\n";
static const char sRedEntryAMemoryInfoColumnFmt[] =
    "%s Bank : Name     : Start      : Size       : Free       : History\n";
static const char sRedEntryAMemoryWaveBankInfoFmt[] =
    "%s  %2d  : WAVE%4.4d : 0x%8.8X : 0x%8.8X : 0x%8.8X :   %3d\n";
static const char sRedEntryAMemoryUnbankedWaveInfoFmt[] =
    "%s  --  : WAVE%4.4d : 0x%8.8X : 0x%8.8X : 0x%8.8X :   %3d\n";
static const char sRedEntryAMemoryFreeBlockInfoFmt[] =
    "%s      : -------- : 0x%8.8X : 0x%8.8X : 0x%8.8X : %d\n";
static const char sRedEntryEntryWaveCountFmt[] = "%s    Entry Wave = %d\n";
static const char sRedEntryTotalSizeFmt[] = "%s    Total Size = 0x%8.8X\n";
static const char sRedEntryMaxFreeSizeFmt[] = "%s Max Free Size = 0x%8.8X\n";
static const char sRedEntrySeSepHeaderBrokenFmt[] = "%s%sSE-Sep-Header was broken.%s\n";
static const char sRedEntrySePlayInfoHeaderFmt[] = "%s==== SE Play Information ====\n";
static const char sRedEntrySePlayInfoColumnFmt[] = "%s Track : Name         : Wave\n";
static const char sRedEntrySeBlockPlayInfoFmt[] =
    "%s    %2d : %3.3u:%3.3u      : WAVE%4.4u\n";
static const char sRedEntrySeSepPlayInfoFmt[] =
    "%s    %2d : se%6.6u.sep : WAVE%4.4u\n";
static const char sRedEntrySeEmptyPlayInfoFmt[] = "%s    %2d :              :\n";
static const char sRedEntryMusicHeaderBrokenFmt[] = "%s%sMusic-Header was broken.%s\n";
static const char sRedEntryMusicInformationHeaderFmt[] = "%s==== MUSIC Information ====\n";
static const char sRedEntryMusicInfoColumnFmt[] = "%s BGM      : Wave : Size     : \n";
static const char sRedEntryMusicInfoPlayFmt[] = "%s music%3.3u : %4.4u : 0x%6.6X : Play\n";
static const char sRedEntryMusicInfoStopFmt[] = "%s music%3.3u : %4.4u : 0x%6.6X : Stop\n";
static const char sRedEntryMMemoryInfoHeaderFmt[] = "%s==== MMemory Information ====\n";
static const char sRedEntryMMemoryInfoColumnFmt[] = "%s Name     : Start      : Size       : Free       \n";
static const char sRedEntryMMemoryMusicInfoFmt[] =
    "%s MUSIC%3.3d : 0x%8.8X : 0x%8.8X : 0x%8.8X\n";
static const char sRedEntryMMemorySeBlockInfoFmt[] =
    "%s SE-BLOCK : 0x%8.8X : 0x%8.8X : 0x%8.8X\n";
static const char sRedEntryMMemoryWaveInfoFmt[] =
    "%s WAVE%4.4d : 0x%8.8X : 0x%8.8X : 0x%8.8X\n";
static const char sRedEntryMMemorySeInfoFmt[] =
    "%s SE%6.6d : 0x%8.8X : 0x%8.8X : 0x%8.8X\n";
static const char sRedEntryMMemoryFreeBlockInfoFmt[] =
    "%s -------- : 0x%8.8X : 0x%8.8X : 0x%8.8X\n";
static const char sRedEntryEntryItemsFmt[] = "%s   Entry Items = %d\n";
static const char sRedEntryErrorColor[] = "\x1B[7;31m";
static const char sRedEntryResetColor[] = "\x1B[0m";
static const char sRedEntryHeaderErrorColor[] = "\x1B[4;31m";
static const char sRedEntryInfoColor[] = "\x1B[4;34m";
static const char sRedEntryNewline[] = "\n";
static const char sRedEntryPrefixedNewlineFmt[] = "%s\n";

enum RedEntryStringLayout {
	REDSOUND_ENTRY_COLORED_BLANK_LINE_FMT_SIZE = 0x2d,
	REDSOUND_ENTRY_LOG_PREFIX_SIZE = 0x12,
	REDSOUND_ENTRY_ERROR_BANNER_FMT_SIZE = 0x2d,
	REDSOUND_ENTRY_ERASE_USING_WAVE_DATA_FMT_SIZE = 0x2e,
	REDSOUND_ENTRY_WAVE_HEADER_BROKEN_FMT_SIZE = 0x1f,
	REDSOUND_ENTRY_NO_WAVE_MEMORY_FREE_AREA_FMT_SIZE = 0x3d,
	REDSOUND_ENTRY_WAVE_ENTRY_FMT_SIZE = 0x1f,
	REDSOUND_ENTRY_AMEMORY_INFO_HEADER_FMT_SIZE = 0x21,
	REDSOUND_ENTRY_AMEMORY_INFO_COLUMN_FMT_SIZE = 0x45,
	REDSOUND_ENTRY_AMEMORY_WAVE_BANK_INFO_FMT_SIZE = 0x3c,
	REDSOUND_ENTRY_AMEMORY_UNBANKED_WAVE_INFO_FMT_SIZE = 0x3b,
	REDSOUND_ENTRY_AMEMORY_FREE_BLOCK_INFO_FMT_SIZE = 0x37,
	REDSOUND_ENTRY_ENTRY_WAVE_COUNT_FMT_SIZE = 0x17,
	REDSOUND_ENTRY_TOTAL_SIZE_FMT_SIZE = 0x1c,
	REDSOUND_ENTRY_MAX_FREE_SIZE_FMT_SIZE = 0x1c,
	REDSOUND_ENTRY_SESEP_HEADER_BROKEN_FMT_SIZE = 0x21,
	REDSOUND_ENTRY_SE_PLAY_INFO_HEADER_FMT_SIZE = 0x21,
	REDSOUND_ENTRY_SE_PLAY_INFO_COLUMN_FMT_SIZE = 0x20,
	REDSOUND_ENTRY_SE_BLOCK_PLAY_INFO_FMT_SIZE = 0x2a,
	REDSOUND_ENTRY_SESEP_PLAY_INFO_FMT_SIZE = 0x25,
	REDSOUND_ENTRY_SE_EMPTY_PLAY_INFO_FMT_SIZE = 0x1c,
	REDSOUND_ENTRY_MUSIC_HEADER_BROKEN_FMT_SIZE = 0x20,
	REDSOUND_ENTRY_MUSIC_INFORMATION_HEADER_FMT_SIZE = 0x1f,
	REDSOUND_ENTRY_MUSIC_INFO_COLUMN_FMT_SIZE = 0x22,
	REDSOUND_ENTRY_MUSIC_INFO_PLAY_FMT_SIZE = 0x28,
	REDSOUND_ENTRY_MUSIC_INFO_STOP_FMT_SIZE = 0x28,
	REDSOUND_ENTRY_MMEMORY_INFO_HEADER_FMT_SIZE = 0x21,
	REDSOUND_ENTRY_MMEMORY_INFO_COLUMN_FMT_SIZE = 0x35,
	REDSOUND_ENTRY_MMEMORY_MUSIC_INFO_FMT_SIZE = 0x2d,
	REDSOUND_ENTRY_MMEMORY_SE_BLOCK_INFO_FMT_SIZE = 0x2b,
	REDSOUND_ENTRY_MMEMORY_WAVE_INFO_FMT_SIZE = 0x2c,
	REDSOUND_ENTRY_MMEMORY_SE_INFO_FMT_SIZE = 0x2a,
	REDSOUND_ENTRY_MMEMORY_FREE_BLOCK_INFO_FMT_SIZE = 0x2b,
	REDSOUND_ENTRY_ENTRY_ITEMS_FMT_SIZE = 0x17,
	REDSOUND_ENTRY_ERROR_COLOR_SIZE = 0x08,
	REDSOUND_ENTRY_RESET_COLOR_SIZE = 0x05,
	REDSOUND_ENTRY_HEADER_ERROR_COLOR_SIZE = 0x08,
	REDSOUND_ENTRY_INFO_COLOR_SIZE = 0x08,
	REDSOUND_ENTRY_NEWLINE_SIZE = 0x02,
	REDSOUND_ENTRY_PREFIXED_NEWLINE_FMT_SIZE = 0x04,
	REDSOUND_ENTRY_RODATA_STRING_SIZE = 0x53c,
	REDSOUND_ENTRY_SDATA2_STRING_SIZE = 0x23,
};

enum RedEntryMapLayout {
	REDSOUND_ENTRY_MAP_RODATA_STRING_OFFSET = 0x00,
	REDSOUND_ENTRY_MAP_RODATA_STRING_SIZE = 0x53C,
	REDSOUND_ENTRY_MAP_SDATA2_STRING_OFFSET = 0x00,
	REDSOUND_ENTRY_MAP_SDATA2_STRING_SIZE = 0x23,
};

enum RedEntryTiming {
	REDSOUND_WAVE_LOAD_DMA_POLL_SLEEP_US = 1000,
};

STATIC_ASSERT(sizeof(sRedEntryColoredBlankLineFmt) == REDSOUND_ENTRY_COLORED_BLANK_LINE_FMT_SIZE);
STATIC_ASSERT(sizeof(sRedEntryLogPrefix) == REDSOUND_ENTRY_LOG_PREFIX_SIZE);
STATIC_ASSERT(sizeof(sRedEntryErrorBannerFmt) == REDSOUND_ENTRY_ERROR_BANNER_FMT_SIZE);
STATIC_ASSERT(sizeof(sRedEntryEraseUsingWaveDataFmt) == REDSOUND_ENTRY_ERASE_USING_WAVE_DATA_FMT_SIZE);
STATIC_ASSERT(sizeof(sRedEntryWaveHeaderBrokenFmt) == REDSOUND_ENTRY_WAVE_HEADER_BROKEN_FMT_SIZE);
STATIC_ASSERT(sizeof(sRedEntryNoWaveMemoryFreeAreaFmt) == REDSOUND_ENTRY_NO_WAVE_MEMORY_FREE_AREA_FMT_SIZE);
STATIC_ASSERT(sizeof(sRedEntryWaveEntryFmt) == REDSOUND_ENTRY_WAVE_ENTRY_FMT_SIZE);
STATIC_ASSERT(sizeof(sRedEntryAMemoryInfoHeaderFmt) == REDSOUND_ENTRY_AMEMORY_INFO_HEADER_FMT_SIZE);
STATIC_ASSERT(sizeof(sRedEntryAMemoryInfoColumnFmt) == REDSOUND_ENTRY_AMEMORY_INFO_COLUMN_FMT_SIZE);
STATIC_ASSERT(sizeof(sRedEntryAMemoryWaveBankInfoFmt) == REDSOUND_ENTRY_AMEMORY_WAVE_BANK_INFO_FMT_SIZE);
STATIC_ASSERT(sizeof(sRedEntryAMemoryUnbankedWaveInfoFmt) == REDSOUND_ENTRY_AMEMORY_UNBANKED_WAVE_INFO_FMT_SIZE);
STATIC_ASSERT(sizeof(sRedEntryAMemoryFreeBlockInfoFmt) == REDSOUND_ENTRY_AMEMORY_FREE_BLOCK_INFO_FMT_SIZE);
STATIC_ASSERT(sizeof(sRedEntryEntryWaveCountFmt) == REDSOUND_ENTRY_ENTRY_WAVE_COUNT_FMT_SIZE);
STATIC_ASSERT(sizeof(sRedEntryTotalSizeFmt) == REDSOUND_ENTRY_TOTAL_SIZE_FMT_SIZE);
STATIC_ASSERT(sizeof(sRedEntryMaxFreeSizeFmt) == REDSOUND_ENTRY_MAX_FREE_SIZE_FMT_SIZE);
STATIC_ASSERT(sizeof(sRedEntrySeSepHeaderBrokenFmt) == REDSOUND_ENTRY_SESEP_HEADER_BROKEN_FMT_SIZE);
STATIC_ASSERT(sizeof(sRedEntrySePlayInfoHeaderFmt) == REDSOUND_ENTRY_SE_PLAY_INFO_HEADER_FMT_SIZE);
STATIC_ASSERT(sizeof(sRedEntrySePlayInfoColumnFmt) == REDSOUND_ENTRY_SE_PLAY_INFO_COLUMN_FMT_SIZE);
STATIC_ASSERT(sizeof(sRedEntrySeBlockPlayInfoFmt) == REDSOUND_ENTRY_SE_BLOCK_PLAY_INFO_FMT_SIZE);
STATIC_ASSERT(sizeof(sRedEntrySeSepPlayInfoFmt) == REDSOUND_ENTRY_SESEP_PLAY_INFO_FMT_SIZE);
STATIC_ASSERT(sizeof(sRedEntrySeEmptyPlayInfoFmt) == REDSOUND_ENTRY_SE_EMPTY_PLAY_INFO_FMT_SIZE);
STATIC_ASSERT(sizeof(sRedEntryMusicHeaderBrokenFmt) == REDSOUND_ENTRY_MUSIC_HEADER_BROKEN_FMT_SIZE);
STATIC_ASSERT(sizeof(sRedEntryMusicInformationHeaderFmt) == REDSOUND_ENTRY_MUSIC_INFORMATION_HEADER_FMT_SIZE);
STATIC_ASSERT(sizeof(sRedEntryMusicInfoColumnFmt) == REDSOUND_ENTRY_MUSIC_INFO_COLUMN_FMT_SIZE);
STATIC_ASSERT(sizeof(sRedEntryMusicInfoPlayFmt) == REDSOUND_ENTRY_MUSIC_INFO_PLAY_FMT_SIZE);
STATIC_ASSERT(sizeof(sRedEntryMusicInfoStopFmt) == REDSOUND_ENTRY_MUSIC_INFO_STOP_FMT_SIZE);
STATIC_ASSERT(sizeof(sRedEntryMMemoryInfoHeaderFmt) == REDSOUND_ENTRY_MMEMORY_INFO_HEADER_FMT_SIZE);
STATIC_ASSERT(sizeof(sRedEntryMMemoryInfoColumnFmt) == REDSOUND_ENTRY_MMEMORY_INFO_COLUMN_FMT_SIZE);
STATIC_ASSERT(sizeof(sRedEntryMMemoryMusicInfoFmt) == REDSOUND_ENTRY_MMEMORY_MUSIC_INFO_FMT_SIZE);
STATIC_ASSERT(sizeof(sRedEntryMMemorySeBlockInfoFmt) == REDSOUND_ENTRY_MMEMORY_SE_BLOCK_INFO_FMT_SIZE);
STATIC_ASSERT(sizeof(sRedEntryMMemoryWaveInfoFmt) == REDSOUND_ENTRY_MMEMORY_WAVE_INFO_FMT_SIZE);
STATIC_ASSERT(sizeof(sRedEntryMMemorySeInfoFmt) == REDSOUND_ENTRY_MMEMORY_SE_INFO_FMT_SIZE);
STATIC_ASSERT(sizeof(sRedEntryMMemoryFreeBlockInfoFmt) == REDSOUND_ENTRY_MMEMORY_FREE_BLOCK_INFO_FMT_SIZE);
STATIC_ASSERT(sizeof(sRedEntryEntryItemsFmt) == REDSOUND_ENTRY_ENTRY_ITEMS_FMT_SIZE);
STATIC_ASSERT(sizeof(sRedEntryErrorColor) == REDSOUND_ENTRY_ERROR_COLOR_SIZE);
STATIC_ASSERT(sizeof(sRedEntryResetColor) == REDSOUND_ENTRY_RESET_COLOR_SIZE);
STATIC_ASSERT(sizeof(sRedEntryHeaderErrorColor) == REDSOUND_ENTRY_HEADER_ERROR_COLOR_SIZE);
STATIC_ASSERT(sizeof(sRedEntryInfoColor) == REDSOUND_ENTRY_INFO_COLOR_SIZE);
STATIC_ASSERT(sizeof(sRedEntryNewline) == REDSOUND_ENTRY_NEWLINE_SIZE);
STATIC_ASSERT(sizeof(sRedEntryPrefixedNewlineFmt) == REDSOUND_ENTRY_PREFIXED_NEWLINE_FMT_SIZE);
STATIC_ASSERT(sizeof(sRedEntryColoredBlankLineFmt) + sizeof(sRedEntryLogPrefix) + sizeof(sRedEntryErrorBannerFmt) +
                  sizeof(sRedEntryEraseUsingWaveDataFmt) + sizeof(sRedEntryWaveHeaderBrokenFmt) +
                  sizeof(sRedEntryNoWaveMemoryFreeAreaFmt) + sizeof(sRedEntryWaveEntryFmt) +
                  sizeof(sRedEntryAMemoryInfoHeaderFmt) + sizeof(sRedEntryAMemoryInfoColumnFmt) +
                  sizeof(sRedEntryAMemoryWaveBankInfoFmt) + sizeof(sRedEntryAMemoryUnbankedWaveInfoFmt) +
                  sizeof(sRedEntryAMemoryFreeBlockInfoFmt) + sizeof(sRedEntryEntryWaveCountFmt) +
                  sizeof(sRedEntryTotalSizeFmt) + sizeof(sRedEntryMaxFreeSizeFmt) +
                  sizeof(sRedEntrySeSepHeaderBrokenFmt) + sizeof(sRedEntrySePlayInfoHeaderFmt) +
                  sizeof(sRedEntrySePlayInfoColumnFmt) + sizeof(sRedEntrySeBlockPlayInfoFmt) +
                  sizeof(sRedEntrySeSepPlayInfoFmt) + sizeof(sRedEntrySeEmptyPlayInfoFmt) +
                  sizeof(sRedEntryMusicHeaderBrokenFmt) + sizeof(sRedEntryMusicInformationHeaderFmt) +
                  sizeof(sRedEntryMusicInfoColumnFmt) + sizeof(sRedEntryMusicInfoPlayFmt) +
                  sizeof(sRedEntryMusicInfoStopFmt) + sizeof(sRedEntryMMemoryInfoHeaderFmt) +
                  sizeof(sRedEntryMMemoryInfoColumnFmt) + sizeof(sRedEntryMMemoryMusicInfoFmt) +
                  sizeof(sRedEntryMMemorySeBlockInfoFmt) + sizeof(sRedEntryMMemoryWaveInfoFmt) +
                  sizeof(sRedEntryMMemorySeInfoFmt) + sizeof(sRedEntryMMemoryFreeBlockInfoFmt) +
                  sizeof(sRedEntryEntryItemsFmt) ==
              REDSOUND_ENTRY_RODATA_STRING_SIZE);
STATIC_ASSERT(REDSOUND_ENTRY_MAP_RODATA_STRING_OFFSET == 0);
STATIC_ASSERT(REDSOUND_ENTRY_RODATA_STRING_SIZE == REDSOUND_ENTRY_MAP_RODATA_STRING_SIZE);
STATIC_ASSERT(sizeof(sRedEntryErrorColor) + sizeof(sRedEntryResetColor) + sizeof(sRedEntryHeaderErrorColor) +
                  sizeof(sRedEntryInfoColor) + sizeof(sRedEntryNewline) + sizeof(sRedEntryPrefixedNewlineFmt) ==
              REDSOUND_ENTRY_SDATA2_STRING_SIZE);
STATIC_ASSERT(REDSOUND_ENTRY_MAP_SDATA2_STRING_OFFSET == 0);
STATIC_ASSERT(REDSOUND_ENTRY_SDATA2_STRING_SIZE == REDSOUND_ENTRY_MAP_SDATA2_STRING_SIZE);

/*
 * --INFO--
 * PAL Address: 0x801c05f8
 * PAL Size: 4b
 * EN Address: 0x8020251c
 * EN Size: 4b
 * JP Address: TODO
 * JP Size: TODO
 */
CRedEntry::CRedEntry()
{
}
/*
 * --INFO--
 * PAL Address: 0x801c05fc
 * PAL Size: 72b
 * EN Address: 0x80202520
 * EN Size: 72b
 * JP Address: TODO
 * JP Size: TODO
 */
CRedEntry::~CRedEntry()
{
}
/*
 * --INFO--
 * PAL Address: 0x801c0644
 * PAL Size: 244b
 * EN Address: 0x80202568
 * EN Size: 244b
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedEntry::Init()
{
	int bankIndex;

	m_waveBankBase = (RedHistoryBANK*)RedNew(REDSOUND_WAVE_BANK_ALLOC_SIZE);
	m_seSepBankBase = (RedHistoryBANK*)RedNew(REDSOUND_SESEP_BANK_ALLOC_SIZE);
	m_musicBankBase = (RedHistoryBANK*)RedNew(REDSOUND_MUSIC_BANK_ALLOC_SIZE);

	memset(m_waveBankBase, 0, REDSOUND_WAVE_BANK_SIZE);
	bankIndex = 0;
	do {
		RedEntryWaveBankGet(this, bankIndex)->m_id = REDSOUND_HISTORY_BANK_EMPTY_ID;
		bankIndex = bankIndex + 1;
	} while (bankIndex < REDSOUND_WAVE_BANK_ENTRY_COUNT);

	memset(m_seSepBankBase, 0, REDSOUND_SESEP_BANK_SIZE);
	bankIndex = 0;
	do {
		RedEntrySeSepBankGet(this, bankIndex)->m_id = REDSOUND_HISTORY_BANK_EMPTY_ID;
		bankIndex = bankIndex + 1;
	} while (bankIndex < REDSOUND_SESEP_BANK_ENTRY_COUNT);

	memset(m_musicBankBase, 0, REDSOUND_MUSIC_BANK_SIZE);
	bankIndex = 0;
	do {
		RedEntryMusicBankGet(this, bankIndex)->m_id = REDSOUND_HISTORY_BANK_EMPTY_ID;
		bankIndex = bankIndex + 1;
	} while (bankIndex < REDSOUND_MUSIC_BANK_ENTRY_COUNT);

	m_waveLoadNo = REDSOUND_WAVE_NO_NONE;
}
/*
 * --INFO--
 * PAL Address: 0x801c0738
 * PAL Size: 72b
 * EN Address: 0x8020265c
 * EN Size: 72b
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedEntry::WaveHistoryAdd(int historyNo)
{
	RedHistoryBANK* history = RedEntryWaveHistoryGetBegin(this);

	do {
		if (history->m_historyNo >= historyNo) {
			history->m_historyNo = history->m_historyNo + 1;
		}
		history += 1;
	} while (history < RedEntryWaveBankGetEnd(this));
}
/*
 * --INFO--
 * PAL Address: 0x801c0780
 * PAL Size: 88b
 * EN Address: 0x802026a4
 * EN Size: 88b
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedEntry::WaveHistoryDelete(int historyNo)
{
	if (historyNo != REDSOUND_HISTORY_UNUSED) {
		RedHistoryBANK* history = m_waveBankBase;
		do {
			if ((history->m_historyNo != REDSOUND_HISTORY_UNUSED) && (history->m_historyNo > historyNo)) {
				history->m_historyNo = history->m_historyNo - 1;
			}
			history += 1;
		} while (history < RedEntryWaveBankGetEnd(this));
	}
}
/*
 * --INFO--
 * PAL Address: 0x801c07d8
 * PAL Size: 104b
 * EN Address: 0x802026fc
 * EN Size: 104b
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedEntry::WaveHistoryChoice(RedHistoryBANK* bank)
{
	if (bank->m_historyNo != REDSOUND_HISTORY_UNUSED) {
		RedHistoryBANK* history = m_waveBankBase;
		do {
			if ((history->m_historyNo != REDSOUND_HISTORY_UNUSED) &&
			    (history->m_historyNo < bank->m_historyNo)) {
				history->m_historyNo = history->m_historyNo + 1;
			}
			history += 1;
		} while (history < RedEntryWaveBankGetEnd(this));

		bank->m_historyNo = REDSOUND_HISTORY_MOST_RECENT;
	}
}
/*
 * --INFO--
 * PAL Address: 0x801c0840
 * PAL Size: 96b
 * EN Address: 0x80202764
 * EN Size: 96b
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedEntry::SearchWaveSequence(int waveNo)
{
	RedHistoryBANK* waveBank = m_waveBankBase;

	while (waveBank < RedEntryWaveBankGetEnd(this)) {
		if ((waveBank->m_size != REDSOUND_HISTORY_BANK_EMPTY_SIZE) && (waveBank->m_id == waveNo)) {
			return waveBank - m_waveBankBase;
		}
		waveBank += 1;
	}

	return REDSOUND_HISTORY_BANK_NOT_FOUND;
}
/*
 * --INFO--
 * PAL Address: 0x801c08a0
 * PAL Size: 208b
 * EN Address: 0x802027c4
 * EN Size: 208b
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedEntry::SearchUseWave(int waveNo)
{
	unsigned int interruptLevel = OSDisableInterrupts();
	int found = REDSOUND_ENTRY_SEARCH_NOT_FOUND;
	RedSoundCONTROL* control = RedSoundControlGet(REDSOUND_CONTROL_MUSIC_SECONDARY);

	do {
		if ((control->m_musicId >= REDSOUND_MUSIC_ID_MIN) && (control->m_waveNo == waveNo)) {
			found = REDSOUND_ENTRY_SEARCH_FOUND;
			MusicStop(control->m_musicId);
		}
		control--;
	} while ((u32)control >= (u32)RedSoundControlGetBegin());

	control = RedSoundControlGet(REDSOUND_CONTROL_SE);
	RedTrackDATA* track = control->m_tracks;
	do {
		if (((u32)track->m_command != REDSOUND_TRACK_COMMAND_NONE) && (track->m_waveBankData != REDSOUND_WAVE_BANK_DATA_NONE) &&
		    (track->m_waveBankData->m_waveNo == waveNo)) {
			found = REDSOUND_ENTRY_SEARCH_FOUND;
			SeStopID(track->m_seId);
		}
		track += 1;
	} while (track < RedSoundControlGetSeTrackEnd(control));

	OSRestoreInterrupts(interruptLevel);
	return found;
}
/*
 * --INFO--
 * PAL Address: 0x801c0970
 * PAL Size: 356b
 * EN Address: 0x80202894
 * EN Size: 356b
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedEntry::WaveDelete(RedHistoryBANK* bank)
{
	int sequenceNo = REDSOUND_HISTORY_BANK_NOT_FOUND;
	int waveNo;

	if (bank->m_id >= 0) {
		WaveHistoryDelete(bank->m_historyNo);
		waveNo = bank->m_id;

		bank->m_id = REDSOUND_HISTORY_BANK_EMPTY_ID;
		bank->m_size = REDSOUND_HISTORY_BANK_EMPTY_SIZE;

		sequenceNo = SearchWaveSequence(waveNo);
		if (sequenceNo < 0) {
			if ((SearchUseWave(waveNo) != 0) && (RedReportPrintIsEnabled())) {
				OSReport(sRedEntryColoredBlankLineFmt, sRedEntryLogPrefix, sRedEntryErrorColor, sRedEntryResetColor);
				fflush(__files + 1);
				OSReport(sRedEntryErrorBannerFmt, sRedEntryLogPrefix, sRedEntryErrorColor, sRedEntryResetColor);
				fflush(__files + 1);
				OSReport(sRedEntryEraseUsingWaveDataFmt, sRedEntryLogPrefix, sRedEntryErrorColor, waveNo,
				         sRedEntryResetColor);
				fflush(__files + 1);
				OSReport(sRedEntryColoredBlankLineFmt, sRedEntryLogPrefix, sRedEntryErrorColor, sRedEntryResetColor);
				fflush(__files + 1);
			}
			RedDeleteA(bank->m_waveHead->m_aramAddress);
			RedDelete(bank->m_address);
		}

		bank->m_data = REDSOUND_MEMORY_ADDRESS_NONE;
		bank->m_historyNo = REDSOUND_HISTORY_UNUSED;
	}

	return sequenceNo;
}
/*
 * --INFO--
 * PAL Address: 0x801c0ad4
 * PAL Size: 172b
 * EN Address: 0x802029f8
 * EN Size: 172b
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
	RedHistoryBANK* history = RedEntryWaveHistoryGetBegin(this);

	do {
		if (history->m_historyNo > maxBankSize) {
			arAddress = history->m_waveHead->m_aramAddress;
			if ((arAddress >= offset) && (arAddress < maxSize)) {
				maxBankSize = history->m_historyNo;
				selected = history;
			}
		}
		history += 1;
	} while (history < RedEntryWaveBankGetEnd(this));

	if (maxBankSize != REDSOUND_HISTORY_UNUSED) {
		WaveDelete(selected);
	}

	return maxBankSize;
}
/*
 * --INFO--
 * PAL Address: 0x801c0b80
 * PAL Size: 832b
 * EN Address: 0x80202aa4
 * EN Size: 832b
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedEntry::WaveHeadAdd(int waveBankNo, RedWaveHeadWD* waveHead, int waveNo)
{
	if (!RedWaveHeadHasValidSignature(waveHead)) {
		if (RedReportPrintIsEnabled()) {
			OSReport(sRedEntryWaveHeaderBrokenFmt, sRedEntryLogPrefix, sRedEntryHeaderErrorColor, sRedEntryResetColor);
			fflush(__files + 1);
		}

		return REDSOUND_WAVE_ADD_FAILED;
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
		waveHead->m_loadSize /= REDSOUND_WAVE_STAGE_LOAD_BLOCK_SIZE;
		waveHead->m_loadSize *= REDSOUND_WAVE_STAGE_LOAD_BLOCK_SIZE;
	} else if (((waveNo >= REDSOUND_WAVE_FIXED_RANGE0_BEGIN) && (waveNo < REDSOUND_WAVE_FIXED_RANGE0_END)) ||
	           ((waveNo >= REDSOUND_WAVE_FIXED_RANGE1_BEGIN) && (waveNo < REDSOUND_WAVE_FIXED_RANGE1_END)) ||
	           (waveNo == REDSOUND_WAVE_FIXED_SINGLE)) {
		waveHead->m_loadSize = REDSOUND_WAVE_FIXED_REGION_SIZE;
	}

	int aramRangeStart;
	int aramRangeEnd;
	int aramAddress;
	if ((waveNo >= REDSOUND_WAVE_LARGE_RANGE_BEGIN) && (waveNo < REDSOUND_WAVE_LARGE_RANGE_END)) {
		aramRangeStart = REDSOUND_WAVE_LARGE_REGION_OFFSET;
		aramRangeEnd = aramRangeStart + REDSOUND_WAVE_LARGE_REGION_SIZE;
	} else if (((waveNo >= REDSOUND_WAVE_FIXED_RANGE0_BEGIN) && (waveNo < REDSOUND_WAVE_FIXED_RANGE0_END)) ||
	           ((waveNo >= REDSOUND_WAVE_FIXED_RANGE1_BEGIN) && (waveNo < REDSOUND_WAVE_FIXED_RANGE1_END)) ||
	           (waveNo == REDSOUND_WAVE_FIXED_SINGLE)) {
		aramRangeStart = REDSOUND_WAVE_FIXED_REGION_OFFSET;
		aramRangeEnd = aramRangeStart + REDSOUND_WAVE_FIXED_REGION_SIZE;
	} else {
		aramRangeStart = REDSOUND_WAVE_DEFAULT_REGION_OFFSET;
		aramRangeEnd = aramRangeStart + REDSOUND_WAVE_DEFAULT_REGION_SIZE;
	}

	do {
		RedHistoryBANK* allocatedWaveBank;
		if (waveBankNo < 0) {
			allocatedWaveBank = RedEntryWaveHistoryGetBegin(this);
			while ((allocatedWaveBank->m_size != REDSOUND_HISTORY_BANK_EMPTY_SIZE) &&
			       (allocatedWaveBank < RedEntryWaveBankGetEnd(this))) {
				allocatedWaveBank += 1;
			}
		} else {
			waveBankNo &= REDSOUND_WAVE_PRIMARY_BANK_MASK;
			allocatedWaveBank = RedEntryWaveBankGet(this, waveBankNo);
			if (allocatedWaveBank->m_size != REDSOUND_HISTORY_BANK_EMPTY_SIZE) {
				WaveDelete(allocatedWaveBank);
			}
		}

		if ((allocatedWaveBank < RedEntryWaveBankGetEnd(this)) &&
		    ((aramAddress = RedNewA(waveHead->m_loadSize, aramRangeStart, aramRangeEnd)) != 0)) {
			int waveCopySize = RedWaveHeadGetTableSize(waveHead);
			waveCopySize += RedWaveHeadGetToneSize(waveHead) + REDSOUND_WAVE_HEADER_COPY_BASE_SIZE;
			RedWaveHeadWD* copiedWaveHead = (RedWaveHeadWD*)RedNew(waveCopySize);
			if (copiedWaveHead != 0) {
				allocatedWaveBank->m_waveHead = copiedWaveHead;
				allocatedWaveBank->m_size = waveCopySize;
				waveHead->m_aramAddress = aramAddress;
				allocatedWaveBank->m_id = waveNo;
				waveHead->m_waveNo = (short)waveNo;
				if (waveBankNo < 0) {
					WaveHistoryAdd(REDSOUND_HISTORY_MOST_RECENT);
					allocatedWaveBank->m_historyNo = REDSOUND_HISTORY_MOST_RECENT;
				} else {
					allocatedWaveBank->m_historyNo = REDSOUND_HISTORY_UNUSED;
				}
				memcpy(copiedWaveHead, waveHead, waveCopySize);
				goto success;
			}
			RedDeleteA((void*)aramAddress);
		}
	} while (WaveOldClear(aramRangeStart, aramRangeEnd) != 0);

	if (RedReportPrintIsEnabled()) {
		OSReport(sRedEntryNoWaveMemoryFreeAreaFmt, sRedEntryLogPrefix, sRedEntryErrorColor, (int)waveHead->m_waveNo,
		         waveHead->m_waveSize, sRedEntryResetColor);
		fflush(__files + 1);
	}

	return REDSOUND_WAVE_ADD_FAILED;

success:
	return aramAddress;
}
/*
 * --INFO--
 * PAL Address: 0x801c0ec0
 * PAL Size: 720b
 * EN Address: 0x80202de4
 * EN Size: 720b
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedEntry::SetWaveData(int waveBankNo, void* waveData, int waveDataSize)
{
	int waveNo;
	int existingWaveBankIndex;
	int waveAramAddress;
	int remainingWaveSize;
	u8* waveBodyData;

	waveNo = 0;
	if (waveDataSize == 0) {
		if ((m_waveLoadNo >= 0) && ((waveNo = SearchWaveSequence(m_waveLoadNo)) >= 0)) {
			WaveDelete(RedEntryWaveBankGet(this, waveNo));
		}

		m_waveLoadNo = REDSOUND_WAVE_NO_NONE;
		return REDSOUND_WAVE_NO_NONE;
	}

	waveAramAddress = 0;
	if (m_waveLoadNo < 0) {
		waveNo = RedWaveHeadFromData(waveData)->m_waveNo;

		if ((waveBankNo >= 0) && (waveNo != RedEntryWaveBankGet(this, waveBankNo)->m_id)) {
			WaveDelete(RedEntryWaveBankGet(this, waveBankNo));
		}

		existingWaveBankIndex = SearchWaveSequence(waveNo);
		if (existingWaveBankIndex >= 0) {
			if ((waveBankNo >= 0) && (existingWaveBankIndex != waveBankNo)) {
				RedEntryWaveBankGet(this, waveBankNo)->m_id =
				    RedEntryWaveBankGet(this, existingWaveBankIndex)->m_id;
				RedEntryWaveBankGet(this, waveBankNo)->m_historyNo =
				    RedEntryWaveBankGet(this, existingWaveBankIndex)->m_historyNo;
				RedEntryWaveBankGet(this, waveBankNo)->m_address =
				    RedEntryWaveBankGet(this, existingWaveBankIndex)->m_address;
				RedEntryWaveBankGet(this, waveBankNo)->m_size =
				    RedEntryWaveBankGet(this, existingWaveBankIndex)->m_size;
				existingWaveBankIndex = waveBankNo;
			}

			WaveHistoryChoice(RedEntryWaveBankGet(this, existingWaveBankIndex));
		} else {
			m_waveLoadNo = RedWaveHeadFromData(waveData)->m_waveNo;
			waveAramAddress = WaveHeadAdd(waveBankNo, RedWaveHeadFromData(waveData), waveNo);
			if (waveAramAddress < 0) {
				m_waveLoadSize = 0;
				m_waveLoadNo = REDSOUND_WAVE_NO_NONE;
				return REDSOUND_WAVE_NO_NONE;
			}

			int waveHeaderCopySize = RedWaveHeadGetToneSize(RedWaveHeadFromData(waveData));
			waveHeaderCopySize +=
			    RedWaveHeadGetTableSize(RedWaveHeadFromData(waveData)) + REDSOUND_WAVE_HEADER_COPY_BASE_SIZE;
			remainingWaveSize = RedWaveHeadFromData(waveData)->m_waveSize;
			waveDataSize -= waveHeaderCopySize;
			waveBodyData = RedWaveHeadGetBodyData(waveData, waveHeaderCopySize);
		}
	} else {
		waveAramAddress = m_waveLoadAddress;
		waveBodyData = (u8*)waveData;
		remainingWaveSize = m_waveLoadSize;
	}

	if ((waveAramAddress != 0) && (waveDataSize > 0)) {
		int waveTransferSize;
		if (remainingWaveSize > waveDataSize) {
			waveTransferSize = waveDataSize;
		} else {
			waveTransferSize = remainingWaveSize;
		}

		int dmaId = RedDmaEntry(REDSOUND_DMA_FLAGS_WAVE_LOAD, REDSOUND_DMA_DIRECTION_TO_ARAM,
		                        RedDmaMainMemoryAddress(waveBodyData), waveAramAddress, waveTransferSize, REDSOUND_DMA_CALLBACK_NONE,
		                        REDSOUND_DMA_CALLBACK_DATA_NONE);
		remainingWaveSize -= waveTransferSize;
		waveAramAddress += waveTransferSize;
		m_waveLoadSize = remainingWaveSize;
		m_waveLoadAddress = waveAramAddress;

		while (RedDmaSearchID(dmaId) > REDSOUND_DMA_SEARCH_NOT_FOUND) {
			RedSleep(REDSOUND_WAVE_LOAD_DMA_POLL_SLEEP_US);
		}

		if (m_waveLoadSize < 1) {
			if (RedReportPrintIsEnabled()) {
				OSReport(sRedEntryWaveEntryFmt, sRedEntryLogPrefix, sRedEntryInfoColor, m_waveLoadNo, sRedEntryResetColor);
				fflush(__files + 1);
			}

			m_waveLoadNo = REDSOUND_WAVE_NO_NONE;
			return 0;
		}
	}

	return m_waveLoadNo;
}
/*
 * --INFO--
 * PAL Address: 0x801c1190
 * PAL Size: 316b
 * EN Address: 0x802030b4
 * EN Size: 316b
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedEntry::ClearWaveData(int waveNo)
{
	RedHistoryBANK* historyBank;

	if (waveNo < 0) {
		if (waveNo == REDSOUND_WAVE_CLEAR_ALL) {
			for (historyBank = m_waveBankBase;
			     historyBank < RedEntryWaveBankGetEnd(this); historyBank += 1) {
				if (historyBank->m_id >= 0) {
					WaveDelete(historyBank);
				}
			}
		} else if (waveNo == REDSOUND_WAVE_CLEAR_UNBANKED) {
			for (historyBank = RedEntryWaveHistoryGetBegin(this);
			     historyBank < RedEntryWaveBankGetEnd(this); historyBank += 1) {
				if (historyBank->m_id >= 0) {
					WaveDelete(historyBank);
				}
			}
		} else if (waveNo == REDSOUND_WAVE_CLEAR_UNBANKED_USED) {
			for (historyBank = RedEntryWaveHistoryGetBegin(this);
			     historyBank < RedEntryWaveBankGetEnd(this); historyBank += 1) {
				if ((historyBank->m_id >= 0) && (REDSOUND_HISTORY_UNUSED < historyBank->m_historyNo)) {
					WaveDelete(historyBank);
				}
			}
		}
	} else {
		waveNo = SearchWaveSequence(waveNo);
		if (waveNo >= 0) {
			WaveDelete(RedEntryWaveBankGet(this, waveNo));
		}
	}
}
/*
 * --INFO--
 * PAL Address: 0x801c12cc
 * PAL Size: 204b
 * EN Address: 0x802031f0
 * EN Size: 204b
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedEntry::ClearWaveDataM(int waveNo0, int waveNo1, int waveNo2, int waveNo3)
{
	RedHistoryBANK* historyBank;

	if (((waveNo0 == REDSOUND_WAVE_NO_NONE) && (waveNo1 == REDSOUND_WAVE_NO_NONE) &&
	     (waveNo2 == REDSOUND_WAVE_NO_NONE)) &&
	    (waveNo3 == REDSOUND_WAVE_NO_NONE)) {
		return;
	}

	for (historyBank = RedEntryWaveHistoryGetBegin(this);
	     historyBank < RedEntryWaveBankGetEnd(this); historyBank += 1) {
		if (((historyBank->m_id >= 0) && (REDSOUND_HISTORY_UNUSED < historyBank->m_historyNo)) &&
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
 * EN Address: 0x802032bc
 * EN Size: 312b
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedEntry::ClearWaveBank(int waveBankNo)
{
	RedHistoryBANK* historyBank;

	if (waveBankNo < 0) {
		if (waveBankNo == REDSOUND_WAVE_CLEAR_ALL) {
			for (historyBank = m_waveBankBase;
			     historyBank < RedEntryWaveBankGetEnd(this); historyBank += 1) {
				if (!(historyBank->m_id < 0)) {
					WaveDelete(historyBank);
				}
			}
		} else if (waveBankNo == REDSOUND_WAVE_CLEAR_UNBANKED) {
			for (historyBank = RedEntryWaveHistoryGetBegin(this);
			     historyBank < RedEntryWaveBankGetEnd(this); historyBank += 1) {
				if (!(historyBank->m_id < 0)) {
					WaveDelete(historyBank);
				}
			}
		} else if (waveBankNo == REDSOUND_WAVE_CLEAR_UNBANKED_USED) {
			for (historyBank = RedEntryWaveHistoryGetBegin(this);
			     historyBank < RedEntryWaveBankGetEnd(this); historyBank += 1) {
				if (!(historyBank->m_id < 0) && (REDSOUND_HISTORY_UNUSED < historyBank->m_historyNo)) {
					WaveDelete(historyBank);
				}
			}
		}
	} else if (RedEntryWavePrimaryBankNoIsValid(waveBankNo)) {
		WaveDelete(RedEntryWaveBankGet(this, waveBankNo));
	}
}
/*
 * --INFO--
 * PAL Address: 0x801c14d0
 * PAL Size: 40b
 * EN Address: 0x802033f4
 * EN Size: 40b
 * JP Address: TODO
 * JP Size: TODO
 */
RedHistoryBANK* CRedEntry::GetWaveBank(int waveNo)
{
	if (RedEntryWavePrimaryBankNoIsValid(waveNo))
	{
		return RedEntryWaveBankGet(this, waveNo);
	}

	return 0;
}
/*
 * --INFO--
 * PAL Address: 0x801c14f8
 * PAL Size: 68b
 * EN Address: 0x8020341c
 * EN Size: 68b
 * JP Address: TODO
 * JP Size: TODO
 */
RedWaveHeadWD* CRedEntry::SearchWaveBase(int waveNo)
{
	RedHistoryBANK* waveBank = m_waveBankBase;

	do {
		if (waveNo == waveBank->m_id) {
			return waveBank->m_waveHead;
		}
		waveBank += 1;
	} while (waveBank < RedEntryWaveBankGetEnd(this));

	return 0;
}
/*
 * --INFO--
 * PAL Address: 0x801c153c
 * PAL Size: 88b
 * EN Address: 0x80203460
 * EN Size: 88b
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedEntry::ReentryWaveData(int waveNo)
{
	waveNo = SearchWaveSequence(waveNo);
	if (waveNo >= 0) {
		WaveHistoryChoice(RedEntryWaveBankGet(this, waveNo));
	}
	return waveNo;
}
/*
 * --INFO--
 * PAL Address: 0x801c1594
 * PAL Size: 408b
 * EN Address: 0x802034b8
 * EN Size: 408b
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedEntry::WaveHistoryManager(int mode, int waveNo)
{
	int used;
	RedTrackDATA* track;

	if (mode == REDSOUND_HISTORY_MODE_RELEASE) {
		used = 0;
		if ((RedSoundControlGetBegin()->m_activeTrackCount != 0) &&
		    (RedSoundControlGetBegin()->m_waveNo == waveNo)) {
			used |= 1;
		}
		if ((RedSoundControlGet(REDSOUND_CONTROL_MUSIC_SECONDARY)->m_activeTrackCount != 0) &&
		    (RedSoundControlGet(REDSOUND_CONTROL_MUSIC_SECONDARY)->m_waveNo == waveNo)) {
			used |= 1;
		}
		if (used == 0) {
			RedTrackDATA** trackHead = &RedSoundControlGet(REDSOUND_CONTROL_SE)->m_tracks;
			track = *trackHead;
			do {
				if (((u32)track->m_command != REDSOUND_TRACK_COMMAND_NONE) && (track->m_waveBankData != REDSOUND_WAVE_BANK_DATA_NONE) &&
				    (track->m_waveBankData->m_waveNo == waveNo)) {
					used++;
					break;
				}
				track++;
			} while (track < RedSeTrackGetEnd(*trackHead));
		}
		if (used == 0) {
			used = SearchWaveSequence(waveNo);
			if (RedEntryWaveBankNoIsHistory(used) &&
			    (RedEntryWaveBankGet(this, used)->m_historyNo == REDSOUND_HISTORY_UNUSED)) {
				WaveHistoryAdd(REDSOUND_WAVE_RELEASE_HISTORY_NO);
				RedEntryWaveBankGet(this, used)->m_historyNo = REDSOUND_WAVE_RELEASE_HISTORY_NO;
			}
		}
	} else {
		used = SearchWaveSequence(waveNo);
		if (RedEntryWaveBankNoIsHistory(used) &&
		    (RedEntryWaveBankGet(this, used)->m_historyNo != REDSOUND_HISTORY_UNUSED)) {
			WaveHistoryDelete(RedEntryWaveBankGet(this, used)->m_historyNo);
			RedEntryWaveBankGet(this, used)->m_historyNo = REDSOUND_HISTORY_UNUSED;
		}
	}
}
/*
 * --INFO--
 * PAL Address: 0x801c172c
 * PAL Size: 864b
 * EN Address: 0x80203650
 * EN Size: 864b
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedEntry::DisplayWaveInfo()
{
	if (RedReportPrintIsEnabled()) {
		OSReport(sRedEntryNewline);
		fflush(__files + 1);
		OSReport(sRedEntryAMemoryInfoHeaderFmt, sRedEntryLogPrefix);
		fflush(__files + 1);
		OSReport(sRedEntryAMemoryInfoColumnFmt, sRedEntryLogPrefix);
		fflush(__files + 1);

		RedMemoryBlock* aMemoryBlocks;
		RedMemoryBlock* aMemoryBlock;
		int maxFreeSize = 0;
		int totalAllocatedSize = 0;
		int entryWaveCount = 0;
		int previousBlockEnd;
		int aBufferEnd;

		previousBlockEnd = c_RedMemory.GetABufferAddress();
		aMemoryBlocks = c_RedMemory.GetABankAddress();
		aMemoryBlock = aMemoryBlocks;
		aBufferEnd = previousBlockEnd + c_RedMemory.GetABufferSize();
		do {
			if (aMemoryBlock->m_size != REDSOUND_MEMORY_BLOCK_SIZE_EMPTY) {
				int nextFreeSize = RedMemoryBlockGetEndAddress(aMemoryBlock);
				if (RedMemoryBlockGetNext(aMemoryBlock)->m_size > 0) {
					nextFreeSize = RedMemoryBlockGetNext(aMemoryBlock)->m_address - nextFreeSize;
				} else {
					nextFreeSize = aBufferEnd - nextFreeSize;
				}
				int reportFreeSize = nextFreeSize;

				RedHistoryBANK* waveBank = m_waveBankBase;
				do {
					if ((waveBank->m_size != REDSOUND_HISTORY_BANK_EMPTY_SIZE) &&
					    (waveBank->m_waveHead->m_aramAddress == aMemoryBlock->m_address)) {
						break;
					}
					waveBank += 1;
				} while (waveBank < RedEntryWaveBankGetEnd(this));

				if (waveBank < RedEntryWaveBankGetEnd(this)) {
					if (waveBank < RedEntryWavePrimaryBankGetEnd(this)) {
						OSReport(sRedEntryAMemoryWaveBankInfoFmt, sRedEntryLogPrefix,
						         waveBank - m_waveBankBase,
						         (int)waveBank->m_waveHead->m_waveNo, waveBank->m_waveHead->m_aramAddress, aMemoryBlock->m_size,
						         reportFreeSize, waveBank->m_historyNo);
						fflush(__files + 1);
					} else {
						OSReport(sRedEntryAMemoryUnbankedWaveInfoFmt, sRedEntryLogPrefix,
						         (int)waveBank->m_waveHead->m_waveNo, waveBank->m_waveHead->m_aramAddress, aMemoryBlock->m_size,
						         reportFreeSize, waveBank->m_historyNo);
						fflush(__files + 1);
					}
					entryWaveCount += 1;
				} else {
					OSReport(sRedEntryAMemoryFreeBlockInfoFmt, sRedEntryLogPrefix, aMemoryBlock->m_address,
					         aMemoryBlock->m_size, reportFreeSize,
					         aMemoryBlock - aMemoryBlocks);
					fflush(__files + 1);
				}

				if (maxFreeSize < aMemoryBlock->m_address - previousBlockEnd) {
					maxFreeSize = aMemoryBlock->m_address - previousBlockEnd;
				}
				totalAllocatedSize += aMemoryBlock->m_size;
				previousBlockEnd = RedMemoryBlockGetEndAddress(aMemoryBlock);
			}
			aMemoryBlock++;
		} while (aMemoryBlock < RedMemoryBankGetEnd(aMemoryBlocks));

		int aBufferBase = c_RedMemory.GetABufferAddress();
		if (maxFreeSize < (aBufferBase + c_RedMemory.GetABufferSize()) - previousBlockEnd) {
			maxFreeSize = (aBufferBase + c_RedMemory.GetABufferSize()) - previousBlockEnd;
		}

		OSReport(sRedEntryPrefixedNewlineFmt, sRedEntryLogPrefix);
		fflush(__files + 1);
		OSReport(sRedEntryEntryWaveCountFmt, sRedEntryLogPrefix, entryWaveCount);
		fflush(__files + 1);
		OSReport(sRedEntryTotalSizeFmt, sRedEntryLogPrefix, totalAllocatedSize);
		fflush(__files + 1);
		OSReport(sRedEntryMaxFreeSizeFmt, sRedEntryLogPrefix, maxFreeSize);
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
 * EN Address: 0x802039b0
 * EN Size: 68b
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedEntry::SeSepHistoryAdd()
{
	RedHistoryBANK* history = m_seSepBankBase;
	do {
		if (history->m_historyNo != REDSOUND_HISTORY_UNUSED) {
			history->m_historyNo = history->m_historyNo + 1;
		}
		history += 1;
	} while (history < RedEntrySeSepBankGetEnd(this));
}
/*
 * --INFO--
 * PAL Address: 0x801c1ad0
 * PAL Size: 76b
 * EN Address: 0x802039f4
 * EN Size: 76b
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedEntry::SeSepHistoryDelete(int historyNo)
{
	if (historyNo != REDSOUND_HISTORY_UNUSED) {
		RedHistoryBANK* history = m_seSepBankBase;
		do {
			if (history->m_historyNo > historyNo) {
				history->m_historyNo = history->m_historyNo - 1;
			}
			history += 1;
		} while (history < RedEntrySeSepBankGetEnd(this));
	}
}
/*
 * --INFO--
 * PAL Address: 0x801c1b1c
 * PAL Size: 104b
 * EN Address: 0x80203a40
 * EN Size: 104b
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedEntry::SeSepHistoryChoice(RedHistoryBANK* bank)
{
	if (bank->m_historyNo != REDSOUND_HISTORY_UNUSED) {
		RedHistoryBANK* history = m_seSepBankBase;
		do {
			if ((history->m_historyNo != REDSOUND_HISTORY_UNUSED) && (history->m_historyNo < bank->m_historyNo)) {
				history->m_historyNo = history->m_historyNo + 1;
			}
			history += 1;
		} while (history < RedEntrySeSepBankGetEnd(this));
		bank->m_historyNo = REDSOUND_HISTORY_MOST_RECENT;
	}
}
/*
 * --INFO--
 * PAL Address: 0x801c1b84
 * PAL Size: 156b
 * EN Address: 0x80203aa8
 * EN Size: 156b
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedEntry::SearchSeSepSequence(int seNo)
{
	RedHistoryBANK* seSepBank = m_seSepBankBase;

	if (seNo == REDSOUND_SESEP_SEARCH_FIRST) {
		do {
			if (seSepBank->m_size != REDSOUND_HISTORY_BANK_EMPTY_SIZE) {
				return seSepBank - m_seSepBankBase;
			}
			seSepBank += 1;
		} while (seSepBank < RedEntrySeSepBankGetEnd(this));
	} else {
		do {
			if ((seSepBank->m_size != REDSOUND_HISTORY_BANK_EMPTY_SIZE) && (seSepBank->m_id == seNo)) {
				return seSepBank - m_seSepBankBase;
			}
			seSepBank += 1;
		} while (seSepBank < RedEntrySeSepBankGetEnd(this));
	}

	return REDSOUND_HISTORY_BANK_NOT_FOUND;
}
/*
 * --INFO--
 * PAL Address: 0x801c1c20
 * PAL Size: 156b
 * EN Address: 0x80203b44
 * EN Size: 156b
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedEntry::SeSepMemoryFree(RedHistoryBANK* bank)
{
	int freedSize;
	int waveNo = static_cast<unsigned int>(bank->m_seSepHead->m_waveNoLo) +
	             static_cast<unsigned int>(bank->m_seSepHead->m_waveNoHi) * REDSOUND_SESEP_WAVE_NO_HIGH_SCALE;

	RedDelete(bank->m_address);
	SeSepHistoryDelete(bank->m_historyNo);

	freedSize = bank->m_size;
	bank->m_data = bank->m_size = REDSOUND_HISTORY_BANK_EMPTY_SIZE;
	bank->m_id = REDSOUND_HISTORY_BANK_EMPTY_ID;

	WaveHistoryManager(REDSOUND_HISTORY_MODE_RELEASE, waveNo);
	return freedSize;
}
/*
 * --INFO--
 * PAL Address: 0x801c1cbc
 * PAL Size: 152b
 * EN Address: 0x80203be0
 * EN Size: 152b
 * JP Address: TODO
 * JP Size: TODO
 */
RedHistoryBANK* CRedEntry::SeSepOldDelete()
{
	RedHistoryBANK* selected = 0;
	int historyNo = 0;
	RedHistoryBANK* history = m_seSepBankBase;

	do {
		if ((history->m_size != REDSOUND_HISTORY_BANK_EMPTY_SIZE) && (historyNo < history->m_historyNo)) {
			historyNo = history->m_historyNo;
			selected = history;
		}
		history++;
	} while (history < RedEntrySeSepBankGetEnd(this));

	if (selected != 0) {
		SeSepMemoryFree(selected);
	}

	return selected;
}
/*
 * --INFO--
 * PAL Address: 0x801c1d54
 * PAL Size: 212b
 * EN Address: 0x80203c78
 * EN Size: 212b
 * JP Address: TODO
 * JP Size: TODO
 */
RedSeSepHEAD* CRedEntry::SeSepHeadAdd(RedSeSepHEAD* seSepHead)
{
	RedHistoryBANK* bank = m_seSepBankBase;
	RedSeSepHEAD* addedHead = 0;

	while ((bank->m_size != REDSOUND_HISTORY_BANK_EMPTY_SIZE) &&
	       (bank < RedEntrySeSepBankGetEnd(this))) {
		bank += 1;
	}
	if (bank < RedEntrySeSepBankGetEnd(this)) {
	} else {
		bank = SeSepOldDelete();
	}

	if ((bank != 0) &&
	    (bank < RedEntrySeSepBankGetEnd(this))) {
		bank->m_seSepHead = seSepHead;
		addedHead = seSepHead;
		bank->m_size = RedSeSepGetSize(seSepHead);
		bank->m_id = seSepHead->m_seNo;
		SeSepHistoryAdd();
		bank->m_historyNo = REDSOUND_HISTORY_MOST_RECENT;
	}

	return addedHead;
}
/*
 * --INFO--
 * PAL Address: 0x801c1e28
 * PAL Size: 296b
 * EN Address: 0x80203d4c
 * EN Size: 296b
 * JP Address: TODO
 * JP Size: TODO
 */
RedSeSepHEAD* CRedEntry::SetSeSepData(RedSeSepHEAD* seSepHead)
{
	int entryAddress;

	if ((seSepHead->m_signature[REDSOUND_SESEP_SIGNATURE_0_INDEX] != REDSOUND_SESEP_SIGNATURE_0) ||
	    (seSepHead->m_signature[REDSOUND_SESEP_SIGNATURE_1_INDEX] != REDSOUND_SESEP_SIGNATURE_1) ||
	    (seSepHead->m_signature[REDSOUND_SESEP_SIGNATURE_2_INDEX] != REDSOUND_SESEP_SIGNATURE_2) ||
	    (seSepHead->m_signature[REDSOUND_SESEP_SIGNATURE_3_INDEX] != REDSOUND_SESEP_SIGNATURE_3) ||
	    (seSepHead->m_signature[REDSOUND_SESEP_SIGNATURE_4_INDEX] != REDSOUND_SESEP_SIGNATURE_4)) {
		RedDelete(seSepHead);
		if (RedReportPrintIsEnabled()) {
			OSReport(sRedEntrySeSepHeaderBrokenFmt, sRedEntryLogPrefix, sRedEntryHeaderErrorColor, sRedEntryResetColor);
			fflush(__files + 1);
		}
		return 0;
	}

	entryAddress = SearchSeSepSequence(seSepHead->m_seNo);
	if (entryAddress >= 0) {
		RedDelete(seSepHead);
		SeSepHistoryChoice(RedEntrySeSepBankGet(this, entryAddress));
		entryAddress = RedEntrySeSepBankGet(this, entryAddress)->m_address;
	} else {
		entryAddress = reinterpret_cast<int>(SeSepHeadAdd(seSepHead));
		if (entryAddress == 0) {
			RedDelete(seSepHead);
		}
	}

	return RedSeSepHeadFromBankAddress(entryAddress);
}
/*
 * --INFO--
 * PAL Address: 0x801c1f50
 * PAL Size: 180b
 * EN Address: 0x80203e74
 * EN Size: 180b
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedEntry::ClearSeSepData(int seNo)
{
	int clearResult = 0;

	if (seNo == REDSOUND_SESEP_CLEAR_ALL) {
		RedHistoryBANK* history = m_seSepBankBase;
		do {
			if (history->m_size != REDSOUND_HISTORY_BANK_EMPTY_SIZE) {
				SeSepMemoryFree(history);
			}
			history += 1;
		} while (history < RedEntrySeSepBankGetEnd(this));
	} else {
		clearResult = SearchSeSepSequence(seNo);
		if (clearResult >= 0) {
			clearResult = SeSepMemoryFree(RedEntrySeSepBankGet(this, clearResult));
		}
	}

	return clearResult;
}
/*
 * --INFO--
 * PAL Address: 0x801c2004
 * PAL Size: 212b
 * EN Address: 0x80203f28
 * EN Size: 212b
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedEntry::ClearSeSepDataMG(int bankNo, int sepNo, int groupNo, int kindNo)
{
	int clearResult = 0;
	RedHistoryBANK* bank = m_seSepBankBase;

	do {
		if (bank->m_size != REDSOUND_HISTORY_BANK_EMPTY_SIZE) {
			int seNo = bank->m_id / REDSOUND_SE_MG_ID_DIVISOR;
			if ((bankNo != seNo) && (sepNo != seNo) && (groupNo != seNo) && (kindNo != seNo)) {
				SeSepMemoryFree(bank);
			}
		}
		bank += 1;
	} while (bank < RedEntrySeSepBankGetEnd(this));

	return clearResult;
}
/*
 * --INFO--
 * PAL Address: 0x801c20d8
 * PAL Size: 68b
 * EN Address: 0x80203ffc
 * EN Size: 68b
 * JP Address: TODO
 * JP Size: TODO
 */
RedHistoryBANK* CRedEntry::SearchSeSepBank(int seNo)
{
	RedHistoryBANK* seSepBank = m_seSepBankBase;
	do {
		if (seSepBank->m_id == seNo) {
			return seSepBank;
		}
		seSepBank += 1;
	} while (seSepBank < RedEntrySeSepBankGetEnd(this));

	return 0;
}
/*
 * --INFO--
 * PAL Address: 0x801c211c
 * PAL Size: 88b
 * EN Address: 0x80204040
 * EN Size: 88b
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedEntry::ReentrySeSepData(int seNo)
{
	seNo = SearchSeSepSequence(seNo);
	if (seNo >= 0) {
		SeSepHistoryChoice(RedEntrySeSepBankGet(this, seNo));
	}
	return seNo;
}
/*
 * --INFO--
 * PAL Address: 0x801c2174
 * PAL Size: 320b
 * EN Address: 0x80204098
 * EN Size: 320b
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedEntry::SeSepHistoryManager(int mode, int seNo)
{
	RedTrackDATA* track;
	int sequenceNo;

	if (mode == REDSOUND_HISTORY_MODE_RELEASE) {
		sequenceNo = 0;
		track = RedSoundControlGet(REDSOUND_CONTROL_SE)->m_tracks;

		do {
			if (((unsigned int)track->m_command != REDSOUND_TRACK_COMMAND_NONE) && (track->m_seSepId == seNo)) {
				sequenceNo |= 1;
				break;
			}
			track += 1;
		} while (track < RedSoundControlGetSeTrackEnd(RedSoundControlGet(REDSOUND_CONTROL_SE)));

		if (sequenceNo == 0) {
			sequenceNo = SearchSeSepSequence(seNo);
			if ((sequenceNo >= 0) && (RedEntrySeSepBankGet(this, sequenceNo)->m_historyNo == REDSOUND_HISTORY_UNUSED)) {
				SeSepHistoryAdd();
				RedEntrySeSepBankGet(this, sequenceNo)->m_historyNo = REDSOUND_HISTORY_MOST_RECENT;
			}
		}
	} else {
		sequenceNo = SearchSeSepSequence(seNo);
		if (RedEntrySeSepBankGet(this, sequenceNo)->m_historyNo != REDSOUND_HISTORY_UNUSED) {
			SeSepHistoryDelete(RedEntrySeSepBankGet(this, sequenceNo)->m_historyNo);
			RedEntrySeSepBankGet(this, sequenceNo)->m_historyNo = REDSOUND_HISTORY_UNUSED;
		}
	}
}
/*
 * --INFO--
 * PAL Address: 0x801c22b4
 * PAL Size: 612b
 * EN Address: 0x802041d8
 * EN Size: 612b
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedEntry::DisplaySePlayInfo()
{
	if (RedReportPrintIsEnabled()) {
		OSReport(sRedEntryNewline);
		fflush(__files + 1);
		OSReport(sRedEntrySePlayInfoHeaderFmt, sRedEntryLogPrefix);
		fflush(__files + 1);
		OSReport(sRedEntrySePlayInfoColumnFmt, sRedEntryLogPrefix);
		fflush(__files + 1);

		RedTrackDATA** seTrackBasePtr = &RedSoundControlGet(REDSOUND_CONTROL_SE)->m_tracks;
		RedTrackDATA* seTrack = *seTrackBasePtr;
		int displayWaveNo;
		do {
			if (seTrack->m_command != REDSOUND_TRACK_COMMAND_NONE) {
				if (RedSeBlockIdIsBlockData(seTrack->m_seSepId)) {
					unsigned int seBlockId = (unsigned int)seTrack->m_seSepId;
					seBlockId &= REDSOUND_SE_BLOCK_ENTRY_MASK;
					int seBlockBankNo = RedSeBlockIdGetBankNo(seBlockId);
					int seBlockSequenceNo = RedSeBlockIdGetSequenceNo(seBlockId);
					RedSeBlockHEAD* seBlockHead = RedSeBlockDataGet(seBlockBankNo);
					int* seBlockEntries = seBlockHead->m_entries;
					RedSeINFO* blockSeInfo = RedSeBlockGetInfoFromEntries(seBlockHead, seBlockEntries, seBlockSequenceNo);
					displayWaveNo = RedSeInfoGetWaveNo(blockSeInfo);

					OSReport(sRedEntrySeBlockPlayInfoFmt, sRedEntryLogPrefix,
					         (seTrack - *seTrackBasePtr) + REDSOUND_SE_VOICE_BASE_INDEX, seBlockBankNo,
					         seBlockSequenceNo, displayWaveNo);
					fflush(__files + 1);
				} else {
					RedHistoryBANK* seSepBank = SearchSeSepBank(seTrack->m_seSepId);
					RedSeSepHEAD* seSepHead = seSepBank->m_seSepHead;
					displayWaveNo = RedSeSepGetWaveNo(seSepHead);
					OSReport(sRedEntrySeSepPlayInfoFmt, sRedEntryLogPrefix,
					         (seTrack - *seTrackBasePtr) + REDSOUND_SE_VOICE_BASE_INDEX, seTrack->m_seSepId, displayWaveNo);
					fflush(__files + 1);
				}
			} else {
				OSReport(sRedEntrySeEmptyPlayInfoFmt, sRedEntryLogPrefix,
				         (seTrack - *seTrackBasePtr) + REDSOUND_SE_VOICE_BASE_INDEX);
				fflush(__files + 1);
			}
			seTrack += 1;
		} while (seTrack < RedSeTrackGetEnd(*seTrackBasePtr));

		OSReport(sRedEntryPrefixedNewlineFmt, sRedEntryLogPrefix);
		fflush(__files + 1);
		OSReport(sRedEntryNewline);
		fflush(__files + 1);
	}
}
/*
 * --INFO--
 * PAL Address: 0x801c2518
 * PAL Size: 68b
 * EN Address: 0x8020443c
 * EN Size: 68b
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedEntry::MusicHistoryAdd()
{
	RedHistoryBANK* history = m_musicBankBase;

	do {
		if (history->m_historyNo != REDSOUND_HISTORY_UNUSED) {
			history->m_historyNo = history->m_historyNo + 1;
		}
		history += 1;
	} while (history < RedEntryMusicBankGetEnd(this));
}
/*
 * --INFO--
 * PAL Address: 0x801c255c
 * PAL Size: 76b
 * EN Address: 0x80204480
 * EN Size: 76b
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedEntry::MusicHistoryDelete(int historyNo)
{
	if (historyNo != REDSOUND_HISTORY_UNUSED) {
		RedHistoryBANK* history = m_musicBankBase;
		do {
			if (history->m_historyNo > historyNo) {
				history->m_historyNo = history->m_historyNo - 1;
			}
			history += 1;
		} while (history < RedEntryMusicBankGetEnd(this));
	}
}
/*
 * --INFO--
 * PAL Address: 0x801c25a8
 * PAL Size: 104b
 * EN Address: 0x802044cc
 * EN Size: 104b
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedEntry::MusicHistoryChoice(RedHistoryBANK* bank)
{
	if (bank->m_historyNo != REDSOUND_HISTORY_UNUSED) {
		RedHistoryBANK* history = m_musicBankBase;
		do {
			if ((history->m_historyNo != REDSOUND_HISTORY_UNUSED) && (history->m_historyNo < bank->m_historyNo)) {
				history->m_historyNo = history->m_historyNo + 1;
			}
			history += 1;
		} while (history < RedEntryMusicBankGetEnd(this));
		bank->m_historyNo = REDSOUND_HISTORY_MOST_RECENT;
	}
}
/*
 * --INFO--
 * PAL Address: 0x801c2610
 * PAL Size: 92b
 * EN Address: 0x80204534
 * EN Size: 92b
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedEntry::SearchMusicSequence(int musicNo)
{
	RedHistoryBANK* musicBank = m_musicBankBase;

	do {
		if ((musicBank->m_size != REDSOUND_HISTORY_BANK_EMPTY_SIZE) && (musicBank->m_id == musicNo)) {
			return musicBank - m_musicBankBase;
		}
		musicBank += 1;
	} while (musicBank < RedEntryMusicBankGetEnd(this));

	return REDSOUND_HISTORY_BANK_NOT_FOUND;
}
/*
 * --INFO--
 * PAL Address: 0x801c266c
 * PAL Size: 112b
 * EN Address: 0x80204590
 * EN Size: 112b
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedEntry::MusicMemoryFree(RedHistoryBANK* bank)
{
	WaveHistoryManager(REDSOUND_HISTORY_MODE_RELEASE, bank->m_musicHead->m_waveNo);
	RedDelete(bank->m_address);
	int freedSize = bank->m_size;
	bank->m_data = bank->m_size = REDSOUND_HISTORY_BANK_EMPTY_SIZE;
	bank->m_historyNo = REDSOUND_HISTORY_UNUSED;
	bank->m_id = REDSOUND_HISTORY_BANK_EMPTY_ID;
	return freedSize;
}
/*
 * --INFO--
 * PAL Address: 0x801c26dc
 * PAL Size: 140b
 * EN Address: 0x80204600
 * EN Size: 140b
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedEntry::MusicOldClear()
{
	int historyNo = 0;
	RedHistoryBANK* selected = 0;
	RedHistoryBANK* history = m_musicBankBase;

	do {
		if (history->m_historyNo > historyNo) {
			historyNo = history->m_historyNo;
			selected = history;
		}
		history += 1;
	} while (history < RedEntryMusicBankGetEnd(this));

	if (historyNo != REDSOUND_HISTORY_UNUSED) {
		MusicMemoryFree(selected);
	}

	return historyNo;
}
/*
 * --INFO--
 * PAL Address: 0x801c2768
 * PAL Size: 112b
 * EN Address: 0x8020468c
 * EN Size: 112b
 * JP Address: TODO
 * JP Size: TODO
 */
RedHistoryBANK* CRedEntry::MusicOldChoice()
{
	RedHistoryBANK* selected = 0;
	int historyNo = 0;
	RedHistoryBANK* history = m_musicBankBase;

	do {
		if (history->m_size == REDSOUND_HISTORY_BANK_EMPTY_SIZE) {
			return history;
		}
		if (history->m_historyNo > historyNo) {
			historyNo = history->m_historyNo;
			selected = history;
		}
		history += 1;
	} while (history < RedEntryMusicBankGetEnd(this));

	return selected;
}
/*
 * --INFO--
 * PAL Address: 0x801c27d8
 * PAL Size: 68b
 * EN Address: 0x802046fc
 * EN Size: 68b
 * JP Address: TODO
 * JP Size: TODO
 */
RedHistoryBANK* CRedEntry::SearchMusicBank(int musicNo)
{
	RedHistoryBANK* musicBank = m_musicBankBase;
	do {
		if (musicBank->m_id == musicNo) {
			return musicBank;
		}
		musicBank += 1;
	} while (musicBank < RedEntryMusicBankGetEnd(this));

	return 0;
}
/*
 * --INFO--
 * PAL Address: 0x801c281c
 * PAL Size: 88b
 * EN Address: 0x80204740
 * EN Size: 88b
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedEntry::ReentryMusicData(int musicNo)
{
	musicNo = SearchMusicSequence(musicNo);
	if (musicNo >= 0) {
		MusicHistoryChoice(RedEntryMusicBankGet(this, musicNo));
	}
	return musicNo;
}
/*
 * --INFO--
 * PAL Address: 0x801c2874
 * PAL Size: 324b
 * EN Address: 0x80204798
 * EN Size: 324b
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedEntry::MusicHistoryManager(int mode, int musicNo)
{
	int musicSeq;

	if (mode == REDSOUND_HISTORY_MODE_RELEASE) {
		musicSeq = 0;
		if ((RedSoundControlGetBegin()->m_activeTrackCount != 0)
		    && (RedSoundControlGetBegin()->m_musicId == musicNo)) {
			musicSeq |= 1;
		}
		if ((RedSoundControlGet(REDSOUND_CONTROL_MUSIC_SECONDARY)->m_activeTrackCount != 0)
		    && (RedSoundControlGet(REDSOUND_CONTROL_MUSIC_SECONDARY)->m_musicId == musicNo)) {
			musicSeq |= 1;
		}

		if (musicSeq == 0) {
			musicSeq = SearchMusicSequence(musicNo);
			if (musicSeq >= 0) {
				if (RedEntryMusicBankGet(this, musicSeq)->m_historyNo == REDSOUND_HISTORY_UNUSED) {
					MusicHistoryAdd();
					RedEntryMusicBankGet(this, musicSeq)->m_historyNo = REDSOUND_HISTORY_MOST_RECENT;
				}
			}
		}
	} else {
		musicSeq = SearchMusicSequence(musicNo);
		if (musicSeq >= 0) {
			if (RedEntryMusicBankGet(this, musicSeq)->m_historyNo != REDSOUND_HISTORY_UNUSED) {
				MusicHistoryDelete(RedEntryMusicBankGet(this, musicSeq)->m_historyNo);
				RedEntryMusicBankGet(this, musicSeq)->m_historyNo = REDSOUND_HISTORY_UNUSED;
			}
		}
	}
}
/*
 * --INFO--
 * PAL Address: 0x801c29b8
 * PAL Size: 168b
 * EN Address: 0x802048dc
 * EN Size: 168b
 * JP Address: TODO
 * JP Size: TODO
 */
RedMusicHEAD* CRedEntry::MusicHeadAdd(RedMusicHEAD* musicHead)
{
	RedMusicHEAD* addedHead = 0;
	RedHistoryBANK* bank = MusicOldChoice();
	if ((bank != 0) && (bank->m_size != REDSOUND_HISTORY_BANK_EMPTY_SIZE)) {
		MusicOldClear();
		bank = MusicOldChoice();
	}

	if (bank != 0) {
		bank->m_musicHead = musicHead;
		addedHead = musicHead;
		bank->m_size = musicHead->m_size;
		bank->m_id = static_cast<int>(musicHead->m_musicNo);
		MusicHistoryAdd();
		bank->m_historyNo = REDSOUND_HISTORY_MOST_RECENT;
	}

	return addedHead;
}
/*
 * --INFO--
 * PAL Address: 0x801c2a60
 * PAL Size: 272b
 * EN Address: 0x80204984
 * EN Size: 272b
 * JP Address: TODO
 * JP Size: TODO
 */
RedMusicHEAD* CRedEntry::SetMusicData(RedMusicHEAD* musicHead)
{
	int entryAddress;

	if (!RedMusicHeadHasValidSignature(musicHead)) {
		RedDelete(musicHead);
		if (RedReportPrintIsEnabled()) {
			OSReport(sRedEntryMusicHeaderBrokenFmt, sRedEntryLogPrefix, sRedEntryHeaderErrorColor, sRedEntryResetColor);
			fflush(__files + 1);
		}
		return 0;
	}

	entryAddress = SearchMusicSequence(static_cast<int>(musicHead->m_musicNo));
	if (entryAddress >= 0) {
		RedDelete(musicHead);
		MusicHistoryChoice(RedEntryMusicBankGet(this, entryAddress));
		entryAddress = RedEntryMusicBankGet(this, entryAddress)->m_address;
	} else {
		entryAddress = reinterpret_cast<int>(MusicHeadAdd(musicHead));
		if (entryAddress == 0) {
			RedDelete(musicHead);
		}
	}

	return RedMusicHeadFromBankAddress(entryAddress);
}
/*
 * --INFO--
 * PAL Address: 0x801c2b70
 * PAL Size: 1108b
 * EN Address: 0x80204a94
 * EN Size: 1108b
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedEntry::DisplayMMemoryInfo()
{
	int seBlockBank;
	int totalSize;
	int entryCount;
	int maxFreeSize;
	int bufferTop;
	int nextAddress;
	int freeSize;
	RedMemoryBlock* memoryBank;
	RedMemoryBlock* bankEntry;
	RedHistoryBANK* history;

	if (RedReportPrintIsDisabled()) {
		return;
	}

	OSReport(sRedEntryNewline);
	fflush(__files + 1);
	OSReport(sRedEntryMMemoryInfoHeaderFmt, sRedEntryLogPrefix);
	fflush(__files + 1);
	OSReport(sRedEntryMMemoryInfoColumnFmt, sRedEntryLogPrefix);
	fflush(__files + 1);

	maxFreeSize = 0;
	totalSize = 0;
	entryCount = 0;
    nextAddress = c_RedMemory.GetMainBufferAddress();
    memoryBank = c_RedMemory.GetMainBankAddress();
	bankEntry = memoryBank;
    bufferTop = nextAddress + c_RedMemory.GetMainBufferSize();

	do {
		if (bankEntry->m_size != REDSOUND_MEMORY_BLOCK_SIZE_EMPTY) {
			int matched = REDSOUND_ENTRY_SEARCH_NOT_FOUND;
			int blockEnd = RedMemoryBlockGetEndAddress(bankEntry);

			if (RedMemoryBlockGetNext(bankEntry)->m_size > 0) {
				freeSize = RedMemoryBlockGetNext(bankEntry)->m_address - blockEnd;
			} else {
				freeSize = bufferTop - blockEnd;
			}

			history = m_musicBankBase;
			do {
				if ((history->m_size != REDSOUND_HISTORY_BANK_EMPTY_SIZE) &&
				    (history->m_address == bankEntry->m_address)) {
					OSReport(sRedEntryMMemoryMusicInfoFmt, sRedEntryLogPrefix,
					         RedMusicHeadFromBankAddress(bankEntry->m_address)->m_musicNo, bankEntry->m_address,
					         bankEntry->m_size, freeSize);
					fflush(__files + 1);
					matched = REDSOUND_ENTRY_SEARCH_FOUND;
					break;
				}
				history += 1;
			} while (history < RedEntryMusicBankGetEnd(this));

			if (matched == REDSOUND_ENTRY_SEARCH_NOT_FOUND) {
				seBlockBank = 0;
				do {
					if ((RedSeBlockDataGet(seBlockBank) != REDSOUND_SE_BLOCK_DATA_NONE) &&
					    (bankEntry->m_address == RedSeBlockHeadAddress(RedSeBlockDataGet(seBlockBank)))) {
						OSReport(sRedEntryMMemorySeBlockInfoFmt, sRedEntryLogPrefix, bankEntry->m_address,
						         bankEntry->m_size, freeSize);
						fflush(__files + 1);
						matched = REDSOUND_ENTRY_SEARCH_FOUND;
						break;
					}
					seBlockBank++;
				} while (seBlockBank < REDSOUND_SE_BLOCK_BANK_COUNT);
			}

			if (matched == REDSOUND_ENTRY_SEARCH_NOT_FOUND) {
				history = m_waveBankBase;
				do {
					if ((history->m_size != REDSOUND_HISTORY_BANK_EMPTY_SIZE) &&
					    (history->m_address == bankEntry->m_address)) {
						OSReport(sRedEntryMMemoryWaveInfoFmt, sRedEntryLogPrefix,
						         RedWaveHeadFromBankAddress(bankEntry->m_address)->m_waveNo, bankEntry->m_address,
						         bankEntry->m_size, freeSize);
						fflush(__files + 1);
						matched = REDSOUND_ENTRY_SEARCH_FOUND;
						break;
					}
					history += 1;
				} while (history < RedEntryWaveBankGetEnd(this));
			}

			if (matched == REDSOUND_ENTRY_SEARCH_NOT_FOUND) {
				history = m_seSepBankBase;
				do {
					if ((history->m_size != REDSOUND_HISTORY_BANK_EMPTY_SIZE) &&
					    (history->m_address == bankEntry->m_address)) {
						OSReport(sRedEntryMMemorySeInfoFmt, sRedEntryLogPrefix,
						         RedSeSepHeadFromBankAddress(bankEntry->m_address)->m_seNo, bankEntry->m_address,
						         bankEntry->m_size, freeSize);
						fflush(__files + 1);
						matched = REDSOUND_ENTRY_SEARCH_FOUND;
						break;
					}
					history += 1;
				} while (history < RedEntrySeSepBankGetEnd(this));
			}

			if (matched == REDSOUND_ENTRY_SEARCH_NOT_FOUND) {
				OSReport(sRedEntryMMemoryFreeBlockInfoFmt, sRedEntryLogPrefix, bankEntry->m_address, bankEntry->m_size,
				         freeSize);
				fflush(__files + 1);
			}

			if (maxFreeSize < (bankEntry->m_address - nextAddress)) {
				maxFreeSize = bankEntry->m_address - nextAddress;
			}

			entryCount++;
			totalSize += bankEntry->m_size;
			nextAddress = RedMemoryBlockGetEndAddress(bankEntry);
		}

		bankEntry++;
	} while (bankEntry < RedMemoryBankGetEnd(memoryBank));

    freeSize = (c_RedMemory.GetMainBufferAddress() + c_RedMemory.GetMainBufferSize()) - nextAddress;
	if (maxFreeSize < freeSize) {
		maxFreeSize = freeSize;
	}

	OSReport(sRedEntryPrefixedNewlineFmt, sRedEntryLogPrefix);
	fflush(__files + 1);
	OSReport(sRedEntryEntryItemsFmt, sRedEntryLogPrefix, entryCount);
	fflush(__files + 1);
	OSReport(sRedEntryTotalSizeFmt, sRedEntryLogPrefix, totalSize);
	fflush(__files + 1);
	OSReport(sRedEntryMaxFreeSizeFmt, sRedEntryLogPrefix, maxFreeSize);
	fflush(__files + 1);
	OSReport(sRedEntryPrefixedNewlineFmt, sRedEntryLogPrefix);
	fflush(__files + 1);
	OSReport(sRedEntryNewline);
	fflush(__files + 1);
}
/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 204b
 * EN Address: UNUSED
 * EN Size: 204b
 * JP Address: TODO
 * JP Size: TODO
 */
int CRedEntry::ClearMusicData(int musicNo)
{
	int clearResult = 0;

	if (musicNo == REDSOUND_MUSIC_CLEAR_ALL) {
		RedHistoryBANK* history = m_musicBankBase;
		do {
			if (history->m_size != REDSOUND_HISTORY_BANK_EMPTY_SIZE) {
				if (history->m_historyNo != REDSOUND_HISTORY_UNUSED) {
					MusicHistoryDelete(history->m_historyNo);
				}
				clearResult += MusicMemoryFree(history);
			}
			history += 1;
		} while (history < RedEntryMusicBankGetEnd(this));
	} else {
		clearResult = SearchMusicSequence(musicNo);
		if (clearResult >= 0) {
			clearResult = MusicMemoryFree(RedEntryMusicBankGet(this, clearResult));
		}
	}

	return clearResult;
}
/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 428b
 * EN Address: UNUSED
 * EN Size: 428b
 * JP Address: TODO
 * JP Size: TODO
 */
void CRedEntry::DisplayMusicInfo()
{
	if (RedReportPrintIsEnabled()) {
		OSReport(sRedEntryNewline);
		fflush(__files + 1);
		OSReport(sRedEntryMusicInformationHeaderFmt, sRedEntryLogPrefix);
		fflush(__files + 1);
		OSReport(sRedEntryMusicInfoColumnFmt, sRedEntryLogPrefix);
		fflush(__files + 1);

		RedHistoryBANK* history = m_musicBankBase;
		do {
			if (history->m_size != REDSOUND_HISTORY_BANK_EMPTY_SIZE) {
				int playing = REDSOUND_ENTRY_SEARCH_NOT_FOUND;
				if ((RedSoundControlGetBegin()->m_activeTrackCount != 0) &&
				    (RedSoundControlGetBegin()->m_musicId == history->m_id)) {
					playing = REDSOUND_ENTRY_SEARCH_FOUND;
				}
				if ((RedSoundControlGet(REDSOUND_CONTROL_MUSIC_SECONDARY)->m_activeTrackCount != 0) &&
				    (RedSoundControlGet(REDSOUND_CONTROL_MUSIC_SECONDARY)->m_musicId == history->m_id)) {
					playing = REDSOUND_ENTRY_SEARCH_FOUND;
				}

				if (playing != REDSOUND_ENTRY_SEARCH_NOT_FOUND) {
					OSReport(sRedEntryMusicInfoPlayFmt, sRedEntryLogPrefix, history->m_id,
					         history->m_musicHead->m_waveNo, history->m_size);
					fflush(__files + 1);
				} else {
					OSReport(sRedEntryMusicInfoStopFmt, sRedEntryLogPrefix, history->m_id,
					         history->m_musicHead->m_waveNo, history->m_size);
					fflush(__files + 1);
				}
			}
			history += 1;
		} while (history < RedEntryMusicBankGetEnd(this));

		OSReport(sRedEntryNewline);
		fflush(__files + 1);
	}
}
