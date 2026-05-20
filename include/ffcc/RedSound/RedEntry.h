#ifndef _FFCC_REDSOUND_REDENTRY_H
#define _FFCC_REDSOUND_REDENTRY_H

struct RedMusicHEAD;
struct RedSeSepHEAD;
struct RedWaveDATA;
struct RedWaveHeadWD;

struct RedHistoryBANK
{
	int m_id;
	int m_historyNo;
	union {
		int m_data;
		int m_address;
		void* m_pointer;
		RedWaveHeadWD* m_waveHead;
		RedSeSepHEAD* m_seSepHead;
		RedMusicHEAD* m_musicHead;
	};
	int m_size;
};

enum RedEntryBankLayoutSize {
	REDSOUND_HISTORY_BANK_EMPTY_ID = -1,
	REDSOUND_HISTORY_BANK_EMPTY_SIZE = 0,
	REDSOUND_HISTORY_BANK_NOT_FOUND = -1,
	REDSOUND_WAVE_NO_NONE = -1,
	REDSOUND_WAVE_ADD_FAILED = -1,
	REDSOUND_WAVE_SIZE_AUTO = -1,
	REDSOUND_WAVE_CLEAR_ALL = -1,
	REDSOUND_WAVE_CLEAR_UNBANKED = -2,
	REDSOUND_WAVE_CLEAR_UNBANKED_USED = -3,
	REDSOUND_SESEP_SEARCH_FIRST = -1,
	REDSOUND_SESEP_CLEAR_ALL = -1,
	REDSOUND_MUSIC_CLEAR_ALL = -1,
	REDSOUND_HISTORY_BANK_ENTRY_SIZE = sizeof(RedHistoryBANK),
	REDSOUND_HISTORY_BANK_ID_OFFSET = (unsigned int)&(((RedHistoryBANK*)0)->m_id),
	REDSOUND_HISTORY_BANK_HISTORY_NO_OFFSET = (unsigned int)&(((RedHistoryBANK*)0)->m_historyNo),
	REDSOUND_HISTORY_BANK_DATA_OFFSET = (unsigned int)&(((RedHistoryBANK*)0)->m_data),
	REDSOUND_HISTORY_BANK_SIZE_OFFSET = (unsigned int)&(((RedHistoryBANK*)0)->m_size),
	REDSOUND_WAVE_BANK_ENTRY_COUNT = 0x40,
	REDSOUND_WAVE_PRIMARY_BANK_ENTRY_COUNT = 0x10,
	REDSOUND_WAVE_PRIMARY_BANK_MASK = REDSOUND_WAVE_PRIMARY_BANK_ENTRY_COUNT - 1,
	REDSOUND_WAVE_RELEASE_HISTORY_NO = REDSOUND_WAVE_PRIMARY_BANK_ENTRY_COUNT + 4,
	REDSOUND_SESEP_BANK_ENTRY_COUNT = 0x100,
	REDSOUND_MUSIC_BANK_ENTRY_COUNT = 0x04,
	REDSOUND_WAVE_PRIMARY_BANK_SIZE = REDSOUND_HISTORY_BANK_ENTRY_SIZE * REDSOUND_WAVE_PRIMARY_BANK_ENTRY_COUNT,
	REDSOUND_WAVE_HISTORY_BANK_SIZE =
	    REDSOUND_HISTORY_BANK_ENTRY_SIZE * (REDSOUND_WAVE_BANK_ENTRY_COUNT - REDSOUND_WAVE_PRIMARY_BANK_ENTRY_COUNT),
	REDSOUND_WAVE_BANK_SIZE = REDSOUND_HISTORY_BANK_ENTRY_SIZE * REDSOUND_WAVE_BANK_ENTRY_COUNT,
	REDSOUND_WAVE_HISTORY_BANK_OFFSET = REDSOUND_HISTORY_BANK_ENTRY_SIZE * REDSOUND_WAVE_PRIMARY_BANK_ENTRY_COUNT,
	REDSOUND_SESEP_BANK_SIZE = REDSOUND_HISTORY_BANK_ENTRY_SIZE * REDSOUND_SESEP_BANK_ENTRY_COUNT,
	REDSOUND_MUSIC_BANK_SIZE = REDSOUND_HISTORY_BANK_ENTRY_SIZE * REDSOUND_MUSIC_BANK_ENTRY_COUNT,
	REDSOUND_WAVE_PRIMARY_BANK_ALLOC_SIZE = REDSOUND_WAVE_PRIMARY_BANK_SIZE,
	REDSOUND_WAVE_HISTORY_BANK_ALLOC_SIZE = REDSOUND_WAVE_HISTORY_BANK_SIZE,
	REDSOUND_WAVE_BANK_ALLOC_SIZE = REDSOUND_WAVE_BANK_SIZE,
	REDSOUND_SESEP_BANK_ALLOC_SIZE = REDSOUND_SESEP_BANK_SIZE,
	REDSOUND_MUSIC_BANK_ALLOC_SIZE = REDSOUND_MUSIC_BANK_SIZE,
	REDSOUND_ENTRY_BANK_ARENA_SIZE = REDSOUND_WAVE_BANK_SIZE + REDSOUND_SESEP_BANK_SIZE + REDSOUND_MUSIC_BANK_SIZE,
	REDSOUND_ENTRY_BANK_ARENA_ALLOC_SIZE = REDSOUND_ENTRY_BANK_ARENA_SIZE,
};

enum RedHistoryMode {
	REDSOUND_HISTORY_MODE_RELEASE = 0,
	REDSOUND_HISTORY_MODE_USE = 1,
};

#define RedHistoryBankHasData(bank) ((bank)->m_size != REDSOUND_HISTORY_BANK_EMPTY_SIZE)
#define RedHistoryBankIsEmpty(bank) ((bank)->m_size == REDSOUND_HISTORY_BANK_EMPTY_SIZE)

enum RedHistoryNumber {
	REDSOUND_HISTORY_UNUSED = 0,
	REDSOUND_HISTORY_MOST_RECENT = 1,
};

enum RedEntrySearchResult {
	REDSOUND_ENTRY_SEARCH_NOT_FOUND = 0,
	REDSOUND_ENTRY_SEARCH_FOUND = 1,
};

enum RedEntryFileLayoutSize {
	REDSOUND_MUSIC_SIGNATURE_SIZE = 4,
	REDSOUND_MUSIC_TRACK_BLOCK_COMMAND_MIN_COUNT = 1,
	REDSOUND_SESEP_SIGNATURE_SIZE = 8,
	REDSOUND_SESEP_RESERVED13_SIZE = 0x01,
	REDSOUND_SE_INFO_SEQUENCE_MIN_COUNT = 1,
	REDSOUND_SE_BLOCK_SIGNATURE_SIZE = 8,
	REDSOUND_SE_BLOCK_RESERVED08_SIZE = 0x02,
	REDSOUND_SE_BLOCK_ENTRY_MIN_COUNT = 1,
	REDSOUND_WAVE_SIGNATURE_SIZE = 2,
	REDSOUND_WAVE_SIGNATURE_MAGIC0 = 'W',
	REDSOUND_WAVE_SIGNATURE_MAGIC1 = 'D',
	REDSOUND_WAVE_HEAD_RESERVED18_SIZE = 0x08,
	REDSOUND_WAVE_OFFSET_MIN_COUNT = 1,
};

enum RedEntryWaveAramRange {
	REDSOUND_WAVE_STAGE_RANGE_BEGIN = 10,
	REDSOUND_WAVE_STAGE_RANGE_END = 70,
	REDSOUND_WAVE_LARGE_RANGE_BEGIN = 100,
	REDSOUND_WAVE_LARGE_RANGE_END = 300,
	REDSOUND_WAVE_FIXED_RANGE0_BEGIN = 0x154,
	REDSOUND_WAVE_FIXED_RANGE0_END = 0x17A,
	REDSOUND_WAVE_FIXED_RANGE1_BEGIN = 0x17F,
	REDSOUND_WAVE_FIXED_RANGE1_END = 0x182,
	REDSOUND_WAVE_FIXED_SINGLE = 0x183,
	REDSOUND_WAVE_STAGE_LOAD_BLOCK_SIZE = 0x28000,
	REDSOUND_WAVE_STAGE_LOAD_BLOCK_ROUND = REDSOUND_WAVE_STAGE_LOAD_BLOCK_SIZE - 1,
	REDSOUND_WAVE_TABLE_ENTRY_SIZE = sizeof(int),
	REDSOUND_WAVE_TABLE_ALIGN = 0x20,
	REDSOUND_WAVE_TABLE_ALIGN_MASK = ~(REDSOUND_WAVE_TABLE_ALIGN - 1),
	REDSOUND_WAVE_TONE_ENTRY_SIZE = 0x60,
	REDSOUND_WAVE_HEADER_COPY_BASE_SIZE = 0x20,
	REDSOUND_WAVE_LARGE_LOAD_STEP = 0x200000,
	REDSOUND_WAVE_DEFAULT_REGION_SIZE = 0x300000,
	REDSOUND_WAVE_FIXED_REGION_SIZE = 0x100000,
	REDSOUND_WAVE_LARGE_REGION_SIZE = REDSOUND_WAVE_LARGE_LOAD_STEP * 2,
};

struct RedWaveAramLayout {
	char m_defaultRegion[REDSOUND_WAVE_DEFAULT_REGION_SIZE];
	char m_fixedRegion[REDSOUND_WAVE_FIXED_REGION_SIZE];
	char m_largeRegion[REDSOUND_WAVE_LARGE_REGION_SIZE];
};

enum RedEntryWaveAramLayout {
	REDSOUND_WAVE_DEFAULT_REGION_OFFSET = (unsigned int)&(((RedWaveAramLayout*)0)->m_defaultRegion),
	REDSOUND_WAVE_FIXED_REGION_OFFSET = (unsigned int)&(((RedWaveAramLayout*)0)->m_fixedRegion),
	REDSOUND_WAVE_LARGE_REGION_OFFSET = (unsigned int)&(((RedWaveAramLayout*)0)->m_largeRegion),
	REDSOUND_WAVE_DEFAULT_REGION_END = REDSOUND_WAVE_DEFAULT_REGION_OFFSET + REDSOUND_WAVE_DEFAULT_REGION_SIZE,
	REDSOUND_WAVE_FIXED_REGION_END = REDSOUND_WAVE_FIXED_REGION_OFFSET + REDSOUND_WAVE_FIXED_REGION_SIZE,
	REDSOUND_WAVE_LARGE_REGION_END = REDSOUND_WAVE_LARGE_REGION_OFFSET + REDSOUND_WAVE_LARGE_REGION_SIZE,
	REDSOUND_WAVE_ARAM_LAYOUT_SIZE = sizeof(RedWaveAramLayout),
};

enum RedMusicSignature {
	REDSOUND_MUSIC_SIGNATURE_0 = 'B',
	REDSOUND_MUSIC_SIGNATURE_1 = 'G',
	REDSOUND_MUSIC_SIGNATURE_2 = 'M',
};

enum RedMusicSignatureIndex {
	REDSOUND_MUSIC_SIGNATURE_0_INDEX = 0,
	REDSOUND_MUSIC_SIGNATURE_1_INDEX = 1,
	REDSOUND_MUSIC_SIGNATURE_2_INDEX = 2,
};

enum RedSeSepSignature {
	REDSOUND_SESEP_SIGNATURE_0 = 'S',
	REDSOUND_SESEP_SIGNATURE_1 = 'e',
	REDSOUND_SESEP_SIGNATURE_2 = 'S',
	REDSOUND_SESEP_SIGNATURE_3 = 'e',
	REDSOUND_SESEP_SIGNATURE_4 = 'p',
};

enum RedSeSepSignatureIndex {
	REDSOUND_SESEP_SIGNATURE_0_INDEX = 0,
	REDSOUND_SESEP_SIGNATURE_1_INDEX = 1,
	REDSOUND_SESEP_SIGNATURE_2_INDEX = 2,
	REDSOUND_SESEP_SIGNATURE_3_INDEX = 3,
	REDSOUND_SESEP_SIGNATURE_4_INDEX = 4,
};

enum RedSeBlockSignature {
	REDSOUND_SE_BLOCK_SIGNATURE_0 = 'S',
	REDSOUND_SE_BLOCK_SIGNATURE_1 = 'e',
	REDSOUND_SE_BLOCK_SIGNATURE_2 = 'B',
	REDSOUND_SE_BLOCK_SIGNATURE_3 = 'l',
	REDSOUND_SE_BLOCK_SIGNATURE_4 = 'o',
	REDSOUND_SE_BLOCK_SIGNATURE_5 = 'c',
	REDSOUND_SE_BLOCK_SIGNATURE_6 = 'k',
};

enum RedSeBlockSignatureIndex {
	REDSOUND_SE_BLOCK_SIGNATURE_0_INDEX = 0,
	REDSOUND_SE_BLOCK_SIGNATURE_1_INDEX = 1,
	REDSOUND_SE_BLOCK_SIGNATURE_2_INDEX = 2,
	REDSOUND_SE_BLOCK_SIGNATURE_3_INDEX = 3,
	REDSOUND_SE_BLOCK_SIGNATURE_4_INDEX = 4,
	REDSOUND_SE_BLOCK_SIGNATURE_5_INDEX = 5,
	REDSOUND_SE_BLOCK_SIGNATURE_6_INDEX = 6,
};

enum RedWaveSignatureIndex {
	REDSOUND_WAVE_SIGNATURE_MAGIC0_INDEX = 0,
	REDSOUND_WAVE_SIGNATURE_MAGIC1_INDEX = 1,
};

struct RedMusicHEAD
{
	char m_signature[REDSOUND_MUSIC_SIGNATURE_SIZE];
	short m_musicNo;
	short m_waveNo;
	char m_trackCount;
	char m_reverbKind;
	short m_reverbDepth;
	short m_flags;
	unsigned short m_reserved0E;
	int m_size;
	unsigned int m_playFlags;
	int m_reserved18;
	int m_reserved1C;
};

struct RedMusicTrackBlock
{
	unsigned char m_sizeLo;
	unsigned char m_sizeHi0;
	unsigned char m_sizeHi1;
	unsigned char m_sizeHi2;
	unsigned char m_command[REDSOUND_MUSIC_TRACK_BLOCK_COMMAND_MIN_COUNT];
};

enum RedMusicTrackBlockLayout {
	REDSOUND_MUSIC_TRACK_BLOCK_SIZE_LO_OFFSET = (unsigned int)&(((RedMusicTrackBlock*)0)->m_sizeLo),
	REDSOUND_MUSIC_TRACK_BLOCK_SIZE_HI0_OFFSET = (unsigned int)&(((RedMusicTrackBlock*)0)->m_sizeHi0),
	REDSOUND_MUSIC_TRACK_BLOCK_SIZE_HI1_OFFSET = (unsigned int)&(((RedMusicTrackBlock*)0)->m_sizeHi1),
	REDSOUND_MUSIC_TRACK_BLOCK_SIZE_HI2_OFFSET = (unsigned int)&(((RedMusicTrackBlock*)0)->m_sizeHi2),
	REDSOUND_MUSIC_TRACK_BLOCK_COMMAND_OFFSET = (unsigned int)&(((RedMusicTrackBlock*)0)->m_command),
	REDSOUND_MUSIC_TRACK_BLOCK_MIN_SIZE = sizeof(RedMusicTrackBlock),
	REDSOUND_MUSIC_TRACK_BLOCK_SIZE_HI0_SHIFT = 8,
	REDSOUND_MUSIC_TRACK_BLOCK_SIZE_HI1_SHIFT = 16,
	REDSOUND_MUSIC_TRACK_BLOCK_SIZE_HI2_SHIFT = 24,
};

#define RedMusicTrackBlockGetSize(block)                                                          \
	((unsigned int)(block)->m_sizeLo |                                                             \
	 ((unsigned int)(block)->m_sizeHi0 << REDSOUND_MUSIC_TRACK_BLOCK_SIZE_HI0_SHIFT) |             \
	 ((unsigned int)(block)->m_sizeHi1 << REDSOUND_MUSIC_TRACK_BLOCK_SIZE_HI1_SHIFT) |             \
	 ((unsigned int)(block)->m_sizeHi2 << REDSOUND_MUSIC_TRACK_BLOCK_SIZE_HI2_SHIFT))

#define RedMusicTrackBlockGetCommandBlock(block) ((RedMusicTrackBlock*)(block)->m_command)
#define RedMusicTrackBlockGetNext(block, blockSize)                                                \
	((RedMusicTrackBlock*)((unsigned char*)(block) + (blockSize)))
#define RedMusicGetTrackBlocks(musicHead) reinterpret_cast<RedMusicTrackBlock*>((musicHead) + 1)
#define RedMusicHeadGetTrackArenaSize(musicHead) ((musicHead)->m_trackCount * REDSOUND_TRACK_SIZE)
#define RedMusicHeadGetSize(musicHead) ((musicHead)->m_size)
#define RedMusicHeadHasValidSignature(musicHead)                                                   \
	((musicHead)->m_signature[REDSOUND_MUSIC_SIGNATURE_0_INDEX] == REDSOUND_MUSIC_SIGNATURE_0 &&  \
	 (musicHead)->m_signature[REDSOUND_MUSIC_SIGNATURE_1_INDEX] == REDSOUND_MUSIC_SIGNATURE_1 &&  \
	 (musicHead)->m_signature[REDSOUND_MUSIC_SIGNATURE_2_INDEX] == REDSOUND_MUSIC_SIGNATURE_2)

enum RedMusicHeaderFlag {
	REDSOUND_MUSIC_HEADER_SIZE = sizeof(RedMusicHEAD),
	REDSOUND_MUSIC_HEADER_SIGNATURE_OFFSET = (unsigned int)&(((RedMusicHEAD*)0)->m_signature),
	REDSOUND_MUSIC_HEADER_MUSIC_NO_OFFSET = (unsigned int)&(((RedMusicHEAD*)0)->m_musicNo),
	REDSOUND_MUSIC_HEADER_WAVE_NO_OFFSET = (unsigned int)&(((RedMusicHEAD*)0)->m_waveNo),
	REDSOUND_MUSIC_HEADER_TRACK_COUNT_OFFSET = (unsigned int)&(((RedMusicHEAD*)0)->m_trackCount),
	REDSOUND_MUSIC_HEADER_REVERB_KIND_OFFSET = (unsigned int)&(((RedMusicHEAD*)0)->m_reverbKind),
	REDSOUND_MUSIC_HEADER_REVERB_DEPTH_OFFSET = (unsigned int)&(((RedMusicHEAD*)0)->m_reverbDepth),
	REDSOUND_MUSIC_HEADER_FLAGS_OFFSET = (unsigned int)&(((RedMusicHEAD*)0)->m_flags),
	REDSOUND_MUSIC_HEADER_RESERVED0E_OFFSET = (unsigned int)&(((RedMusicHEAD*)0)->m_reserved0E),
	REDSOUND_MUSIC_HEADER_DATA_SIZE_OFFSET = (unsigned int)&(((RedMusicHEAD*)0)->m_size),
	REDSOUND_MUSIC_HEADER_PLAY_FLAGS_OFFSET = (unsigned int)&(((RedMusicHEAD*)0)->m_playFlags),
	REDSOUND_MUSIC_HEADER_RESERVED18_OFFSET = (unsigned int)&(((RedMusicHEAD*)0)->m_reserved18),
	REDSOUND_MUSIC_HEADER_RESERVED1C_OFFSET = (unsigned int)&(((RedMusicHEAD*)0)->m_reserved1C),
	REDSOUND_MUSIC_HEADER_RESERVED0E_SIZE =
	    REDSOUND_MUSIC_HEADER_DATA_SIZE_OFFSET - REDSOUND_MUSIC_HEADER_RESERVED0E_OFFSET,
	REDSOUND_MUSIC_HEADER_RESERVED18_SIZE =
	    REDSOUND_MUSIC_HEADER_RESERVED1C_OFFSET - REDSOUND_MUSIC_HEADER_RESERVED18_OFFSET,
	REDSOUND_MUSIC_HEADER_RESERVED1C_SIZE = REDSOUND_MUSIC_HEADER_SIZE - REDSOUND_MUSIC_HEADER_RESERVED1C_OFFSET,
	REDSOUND_MUSIC_HEADER_VOLUME_SCALE_MASK = 0x7F,
	REDSOUND_MUSIC_PLAY_FLAG_RELEASE_NOTES = 0x40000,
};

struct RedSeINFO;

struct RedSeSepHEAD
{
	char m_signature[REDSOUND_SESEP_SIGNATURE_SIZE];
	int m_seNo;
	unsigned int m_sizeAndFlags;
	unsigned char m_seInfoFlags;
	unsigned char m_waveNoLo;
	unsigned char m_waveNoHi;
	unsigned char m_reserved13;
};

enum RedSeSepHeadLayout {
	REDSOUND_SESEP_STRUCT_SIZE = sizeof(RedSeSepHEAD),
	REDSOUND_SESEP_SIGNATURE_OFFSET = (unsigned int)&(((RedSeSepHEAD*)0)->m_signature),
	REDSOUND_SESEP_SE_NO_OFFSET = (unsigned int)&(((RedSeSepHEAD*)0)->m_seNo),
	REDSOUND_SESEP_SIZE_AND_FLAGS_OFFSET = (unsigned int)&(((RedSeSepHEAD*)0)->m_sizeAndFlags),
	REDSOUND_SESEP_INFO_OFFSET = (unsigned int)&(((RedSeSepHEAD*)0)->m_seInfoFlags),
	REDSOUND_SESEP_HEADER_SIZE = REDSOUND_SESEP_INFO_OFFSET,
	REDSOUND_SESEP_WAVE_NO_LO_OFFSET = (unsigned int)&(((RedSeSepHEAD*)0)->m_waveNoLo),
	REDSOUND_SESEP_WAVE_NO_HI_OFFSET = (unsigned int)&(((RedSeSepHEAD*)0)->m_waveNoHi),
	REDSOUND_SESEP_RESERVED13_OFFSET = (unsigned int)&(((RedSeSepHEAD*)0)->m_reserved13),
	REDSOUND_SESEP_WAVE_NO_HIGH_SCALE = 0x100,
	REDSOUND_SESEP_SIZE_MASK = 0x7FFFFFFF,
	REDSOUND_SESEP_FLAGS_MASK = 0x80000000,
};

#define RedSeSepGetInfo(seSepHead) reinterpret_cast<RedSeINFO*>(&(seSepHead)->m_seInfoFlags)
#define RedSeSepGetSize(seSepHead) ((seSepHead)->m_sizeAndFlags & REDSOUND_SESEP_SIZE_MASK)
#define RedSeSepHasFlags(seSepHead) (((seSepHead)->m_sizeAndFlags & REDSOUND_SESEP_FLAGS_MASK) != 0)
#define RedSeSepGetWaveNo(seSepHead)                                                                  \
	(((seSepHead)->m_waveNoHi * REDSOUND_SESEP_WAVE_NO_HIGH_SCALE) | (seSepHead)->m_waveNoLo)
#define RedSeSepHeadHasValidSignature(seSepHead)                                                   \
	((seSepHead)->m_signature[REDSOUND_SESEP_SIGNATURE_0_INDEX] == REDSOUND_SESEP_SIGNATURE_0 &&  \
	 (seSepHead)->m_signature[REDSOUND_SESEP_SIGNATURE_1_INDEX] == REDSOUND_SESEP_SIGNATURE_1 &&  \
	 (seSepHead)->m_signature[REDSOUND_SESEP_SIGNATURE_2_INDEX] == REDSOUND_SESEP_SIGNATURE_2 &&  \
	 (seSepHead)->m_signature[REDSOUND_SESEP_SIGNATURE_3_INDEX] == REDSOUND_SESEP_SIGNATURE_3 &&  \
	 (seSepHead)->m_signature[REDSOUND_SESEP_SIGNATURE_4_INDEX] == REDSOUND_SESEP_SIGNATURE_4)

struct RedSeInfoSequence
{
	unsigned char m_offsetLo;
	unsigned char m_offsetHiAndFlags;
};

#define RedSeInfoSequenceGetOffset(sequence)                                                       \
	(((sequence)->m_offsetHiAndFlags * REDSOUND_SE_INFO_U16_HIGH_SCALE + (sequence)->m_offsetLo) & \
	 REDSOUND_SE_INFO_SEQUENCE_OFFSET_MASK)

#define RedSeInfoGetCommandData(sequence, count) reinterpret_cast<unsigned char*>((sequence) + (count))
#define RedSeInfoCommandGetNext(command, sequence) ((command) + RedSeInfoSequenceGetOffset(sequence))

#define RedSeInfoSequenceHasContinue(sequence, index)                                               \
	((reinterpret_cast<unsigned char*>(sequence)[(index) * sizeof(RedSeInfoSequence) +             \
	                                             REDSOUND_SE_INFO_SEQUENCE_OFFSET_HI_AND_FLAGS_OFFSET] & \
	  REDSOUND_SE_INFO_SEQUENCE_CONTINUE_FLAG) != 0)

enum RedSeInfoSequenceLayout {
	REDSOUND_SE_INFO_SEQUENCE_OFFSET_LO_OFFSET = (unsigned int)&(((RedSeInfoSequence*)0)->m_offsetLo),
	REDSOUND_SE_INFO_SEQUENCE_OFFSET_HI_AND_FLAGS_OFFSET =
	    (unsigned int)&(((RedSeInfoSequence*)0)->m_offsetHiAndFlags),
};

struct RedSeINFO
{
	unsigned char m_flagsAndCount;
	unsigned char m_waveNoLo;
	unsigned char m_waveNoHi;
	unsigned char m_eraseTrack;
	unsigned char m_attrMask;
	RedSeInfoSequence m_sequence[REDSOUND_SE_INFO_SEQUENCE_MIN_COUNT];
};

enum RedSeInfoLayout {
	REDSOUND_SE_INFO_FLAGS_AND_COUNT_OFFSET = (unsigned int)&(((RedSeINFO*)0)->m_flagsAndCount),
	REDSOUND_SE_INFO_WAVE_NO_LO_OFFSET = (unsigned int)&(((RedSeINFO*)0)->m_waveNoLo),
	REDSOUND_SE_INFO_WAVE_NO_HI_OFFSET = (unsigned int)&(((RedSeINFO*)0)->m_waveNoHi),
	REDSOUND_SE_INFO_ERASE_TRACK_OFFSET = (unsigned int)&(((RedSeINFO*)0)->m_eraseTrack),
	REDSOUND_SE_INFO_ATTR_MASK_OFFSET = (unsigned int)&(((RedSeINFO*)0)->m_attrMask),
	REDSOUND_SE_INFO_SEQUENCE_OFFSET = (unsigned int)&(((RedSeINFO*)0)->m_sequence),
	REDSOUND_SE_INFO_MIN_SIZE = sizeof(RedSeINFO),
	REDSOUND_SE_INFO_U16_HIGH_SCALE = 0x100,
	REDSOUND_SE_INFO_MULTI_FLAG = 0x80,
	REDSOUND_SE_INFO_COUNT_MASK = 0x7F,
	REDSOUND_SE_INFO_SEQUENCE_CONTINUE_FLAG = 0x80,
	REDSOUND_SE_INFO_SEQUENCE_OFFSET_MASK = 0x7FFF,
	REDSOUND_SE_INFO_SEQUENCE_ENTRY_SIZE = sizeof(RedSeInfoSequence),
};

struct RedSeBlockHEAD
{
	char m_signature[REDSOUND_SE_BLOCK_SIGNATURE_SIZE];
	unsigned char m_reserved08[REDSOUND_SE_BLOCK_RESERVED08_SIZE];
	short m_seCount;
	int m_size;
	int m_entries[REDSOUND_SE_BLOCK_ENTRY_MIN_COUNT];
};

enum RedSeBlockEntryLayout {
	REDSOUND_SE_BLOCK_STRUCT_SIZE = sizeof(RedSeBlockHEAD),
	REDSOUND_SE_BLOCK_SIGNATURE_OFFSET = (unsigned int)&(((RedSeBlockHEAD*)0)->m_signature),
	REDSOUND_SE_BLOCK_RESERVED08_OFFSET = (unsigned int)&(((RedSeBlockHEAD*)0)->m_reserved08),
	REDSOUND_SE_BLOCK_SE_COUNT_OFFSET = (unsigned int)&(((RedSeBlockHEAD*)0)->m_seCount),
	REDSOUND_SE_BLOCK_SIZE_OFFSET = (unsigned int)&(((RedSeBlockHEAD*)0)->m_size),
	REDSOUND_SE_BLOCK_ENTRIES_OFFSET = (unsigned int)&(((RedSeBlockHEAD*)0)->m_entries),
	REDSOUND_SE_BLOCK_HEADER_SIZE = REDSOUND_SE_BLOCK_ENTRIES_OFFSET,
	REDSOUND_SE_BLOCK_DATA_FLAG = 0x80000000,
	REDSOUND_SE_BLOCK_ENTRY_MASK = 0x7FFFFFFF,
	REDSOUND_SE_BLOCK_ENTRY_EMPTY = -1,
	REDSOUND_SE_BLOCK_ENTRY_SIZE = sizeof(int),
	REDSOUND_SE_BLOCK_BANK_MASK = 3,
	REDSOUND_SE_BLOCK_BANK_COUNT = REDSOUND_SE_BLOCK_BANK_MASK + 1,
	REDSOUND_SE_BLOCK_BANK_SHIFT = 9,
	REDSOUND_SE_BLOCK_SEQUENCE_MASK = 0x1FF,
	REDSOUND_SE_BLOCK_SEQUENCE_COUNT = REDSOUND_SE_BLOCK_SEQUENCE_MASK + 1,
};

#define REDSOUND_SE_BLOCK_DATA_NONE 0

#define RedSeBlockIdGetBankNo(seBlockId) ((int)(seBlockId) / REDSOUND_SE_BLOCK_SEQUENCE_COUNT)
#define RedSeBlockIdGetSequenceNo(seBlockId) ((seBlockId) & REDSOUND_SE_BLOCK_SEQUENCE_MASK)
#define RedSeBlockIdAddBank(seBlockId, bank) ((seBlockId) += (bank) << REDSOUND_SE_BLOCK_BANK_SHIFT)
#define RedSeBlockIdSetDataFlag(seBlockId) ((seBlockId) |= REDSOUND_SE_BLOCK_DATA_FLAG)
#define RedSeBlockIdIsBlockData(seBlockId) (((seBlockId) & REDSOUND_SE_BLOCK_DATA_FLAG) != 0)
#define RedSeBlockIdIsSeSepData(seBlockId) (((seBlockId) & REDSOUND_SE_BLOCK_DATA_FLAG) == 0)

#define RedSeBlockGetSize(seBlock) ((seBlock)->m_size)
#define RedSeBlockGetSeCount(seBlock) ((seBlock)->m_seCount)
#define RedSeBlockGetInfoBase(seBlock) RedSeBlockGetInfoBaseFromEntries(seBlock, (seBlock)->m_entries)

#define RedSeBlockGetInfoBaseFromEntries(seBlock, entries)                                       \
	(reinterpret_cast<unsigned char*>(entries) +                                                  \
	 (seBlock)->m_seCount * REDSOUND_SE_BLOCK_ENTRY_SIZE)

#define RedSeBlockGetInfo(seBlock, seIndex)                                                       \
	reinterpret_cast<RedSeINFO*>(RedSeBlockGetInfoBase(seBlock) +                                  \
	                             ((seBlock)->m_entries[(seIndex)] & REDSOUND_SE_BLOCK_ENTRY_MASK))

#define RedSeBlockGetInfoFromEntries(seBlock, entries, seIndex)                                   \
	reinterpret_cast<RedSeINFO*>(RedSeBlockGetInfoBaseFromEntries(seBlock, entries) +              \
	                             ((entries)[(seIndex)] & REDSOUND_SE_BLOCK_ENTRY_MASK))

#define RedSeBlockGetInfoFromEntry(seBlock, entries, seIndex)                                      \
	reinterpret_cast<RedSeINFO*>(reinterpret_cast<unsigned char*>(entries) +                        \
	                             ((entries)[(seIndex)] & REDSOUND_SE_BLOCK_ENTRY_MASK) +            \
	                             (seBlock)->m_seCount * REDSOUND_SE_BLOCK_ENTRY_SIZE)

#define RedSeBlockGetInfoFromOffset(entries, infoOffset)                                          \
	reinterpret_cast<RedSeINFO*>(reinterpret_cast<unsigned char*>(entries) + (infoOffset))

#define RedSeInfoGetWaveNo(info)                                                                  \
	(((info)->m_waveNoHi * REDSOUND_SE_INFO_U16_HIGH_SCALE) | (info)->m_waveNoLo)
#define RedSeInfoGetSequences(info) ((info)->m_sequence)
#define RedSeInfoFlagsHasMulti(flags) (((flags) & REDSOUND_SE_INFO_MULTI_FLAG) != 0)
#define RedSeInfoGetSequenceCount(info) ((info)->m_flagsAndCount & ~REDSOUND_SE_INFO_MULTI_FLAG)

struct RedWaveHeadWD
{
	char m_signature[REDSOUND_WAVE_SIGNATURE_SIZE];
	short m_waveNo;
	int m_waveSize;
	int m_tableCount;
	int m_toneCount;
	int m_aramAddress;
	int m_loadSize;
	unsigned char m_reserved18[REDSOUND_WAVE_HEAD_RESERVED18_SIZE];
	int m_waveOffsets[REDSOUND_WAVE_OFFSET_MIN_COUNT];
};

enum RedWaveHeadLayout {
	REDSOUND_WAVE_HEAD_MIN_SIZE = sizeof(RedWaveHeadWD),
	REDSOUND_WAVE_HEAD_SIGNATURE_OFFSET = (unsigned int)&(((RedWaveHeadWD*)0)->m_signature),
	REDSOUND_WAVE_HEAD_WAVE_NO_OFFSET = (unsigned int)&(((RedWaveHeadWD*)0)->m_waveNo),
	REDSOUND_WAVE_HEAD_WAVE_SIZE_OFFSET = (unsigned int)&(((RedWaveHeadWD*)0)->m_waveSize),
	REDSOUND_WAVE_HEAD_TABLE_COUNT_OFFSET = (unsigned int)&(((RedWaveHeadWD*)0)->m_tableCount),
	REDSOUND_WAVE_HEAD_TONE_COUNT_OFFSET = (unsigned int)&(((RedWaveHeadWD*)0)->m_toneCount),
	REDSOUND_WAVE_HEAD_ARAM_ADDRESS_OFFSET = (unsigned int)&(((RedWaveHeadWD*)0)->m_aramAddress),
	REDSOUND_WAVE_HEAD_LOAD_SIZE_OFFSET = (unsigned int)&(((RedWaveHeadWD*)0)->m_loadSize),
	REDSOUND_WAVE_HEAD_RESERVED18_OFFSET = (unsigned int)&(((RedWaveHeadWD*)0)->m_reserved18),
	REDSOUND_WAVE_HEAD_OFFSETS_OFFSET = (unsigned int)&(((RedWaveHeadWD*)0)->m_waveOffsets),
};

#define RedWaveHeadGetTableSize(waveHead)                                                         \
	((((waveHead)->m_tableCount * REDSOUND_WAVE_TABLE_ENTRY_SIZE) + (REDSOUND_WAVE_TABLE_ALIGN - 1)) & \
	 REDSOUND_WAVE_TABLE_ALIGN_MASK)

#define RedWaveHeadGetToneSize(waveHead) ((waveHead)->m_toneCount * REDSOUND_WAVE_TONE_ENTRY_SIZE)

#define RedWaveHeadGetWaveData(waveHead, waveIndex)                                               \
	((RedWaveDATA*)((unsigned char*)(waveHead) + (waveHead)->m_waveOffsets[(waveIndex)]))

#define RedWaveHeadGetBodyData(waveData, waveHeaderSize) ((u8*)(waveData) + (waveHeaderSize))
#define RedWaveHeadHasValidSignature(waveHead)                                                     \
	((waveHead)->m_signature[REDSOUND_WAVE_SIGNATURE_MAGIC0_INDEX] == REDSOUND_WAVE_SIGNATURE_MAGIC0 && \
	 (waveHead)->m_signature[REDSOUND_WAVE_SIGNATURE_MAGIC1_INDEX] == REDSOUND_WAVE_SIGNATURE_MAGIC1)

#define RedMusicHeadFromBankAddress(address) reinterpret_cast<RedMusicHEAD*>(address)
#define RedMusicHeadFromData(musicData) reinterpret_cast<RedMusicHEAD*>(musicData)

#define RedSeBlockHeadAddress(seBlockHead) ((int)(seBlockHead))
#define RedSeBlockHeadFromData(seBlockData) reinterpret_cast<RedSeBlockHEAD*>(seBlockData)

#define RedWaveHeadFromBankAddress(address) reinterpret_cast<RedWaveHeadWD*>(address)
#define RedWaveHeadFromData(waveData) reinterpret_cast<RedWaveHeadWD*>(waveData)

#define RedSeSepHeadFromBankAddress(address) reinterpret_cast<RedSeSepHEAD*>(address)
#define RedSeSepHeadFromData(seSepData) reinterpret_cast<RedSeSepHEAD*>(seSepData)

class CRedEntry
{
public:
	CRedEntry();
	~CRedEntry();

	void Init();

	void WaveHistoryAdd(int waveNo);
	void WaveHistoryDelete(int historyNo);
	void WaveHistoryChoice(RedHistoryBANK* bank);
	int SearchWaveSequence(int waveNo);
	int SearchUseWave(int waveNo);
	int WaveDelete(RedHistoryBANK* bank);
	int WaveOldClear(int waveNo, int aramOffset);
	int WaveHeadAdd(int waveBankNo, RedWaveHeadWD* waveHead, int waveNo);
	int SetWaveData(int waveBankNo, void* waveData, int waveDataSize);
	void ClearWaveData(int waveNo);
	void ClearWaveDataM(int waveNo0, int waveNo1, int waveNo2, int waveNo3);
	void ClearWaveBank(int waveBankNo);
	RedHistoryBANK* GetWaveBank(int waveNo);
	RedWaveHeadWD* SearchWaveBase(int waveNo);
	int ReentryWaveData(int waveNo);
	void WaveHistoryManager(int mode, int waveNo);
	void DisplayWaveInfo();

	void SeSepHistoryAdd();
	void SeSepHistoryDelete(int historyNo);
	void SeSepHistoryChoice(RedHistoryBANK* bank);
	int SearchSeSepSequence(int seNo);
	int SeSepMemoryFree(RedHistoryBANK* bank);
	RedHistoryBANK* SeSepOldDelete();
	RedSeSepHEAD* SeSepHeadAdd(RedSeSepHEAD* seSepHead);
	RedSeSepHEAD* SetSeSepData(RedSeSepHEAD* seSepHead);
	int ClearSeSepData(int seNo);
	int ClearSeSepDataMG(int bank, int sep, int group, int kind);
	RedHistoryBANK* SearchSeSepBank(int seNo);
	int ReentrySeSepData(int seNo);
	void SeSepHistoryManager(int mode, int seNo);
	void DisplaySePlayInfo();

	void MusicHistoryAdd();
	void MusicHistoryDelete(int historyNo);
	void MusicHistoryChoice(RedHistoryBANK* bank);
	int SearchMusicSequence(int musicNo);
	int MusicMemoryFree(RedHistoryBANK* bank);
	int MusicOldClear();
	RedHistoryBANK* MusicOldChoice();
	RedHistoryBANK* SearchMusicBank(int musicNo);
	int ReentryMusicData(int musicNo);
	void MusicHistoryManager(int mode, int musicNo);
	RedMusicHEAD* MusicHeadAdd(RedMusicHEAD* musicHead);
	RedMusicHEAD* SetMusicData(RedMusicHEAD* musicHead);
	int ClearMusicData(int musicNo);
	void DisplayMusicInfo();
	void DisplayMMemoryInfo();

	RedHistoryBANK* m_waveBankBase;
	RedHistoryBANK* m_seSepBankBase;
	RedHistoryBANK* m_musicBankBase;
	int m_waveLoadNo;
	int m_waveLoadSize;
	int m_waveLoadAddress;
};

#define RedEntryWaveBankGet(entry, index) ((entry)->m_waveBankBase + (index))
#define RedEntryWaveBankGetEnd(entry) RedEntryWaveBankGet(entry, REDSOUND_WAVE_BANK_ENTRY_COUNT)
#define RedEntryWavePrimaryBankGetEnd(entry) RedEntryWaveBankGet(entry, REDSOUND_WAVE_PRIMARY_BANK_ENTRY_COUNT)
#define RedEntryWaveHistoryGetBegin(entry) RedEntryWaveBankGet(entry, REDSOUND_WAVE_PRIMARY_BANK_ENTRY_COUNT)
#define RedEntryWavePrimaryBankNoIsValid(bankNo) ((bankNo) >= 0 && (bankNo) < REDSOUND_WAVE_PRIMARY_BANK_ENTRY_COUNT)
#define RedEntryWaveBankNoIsHistory(bankNo) ((bankNo) >= REDSOUND_WAVE_PRIMARY_BANK_ENTRY_COUNT)
#define RedEntrySeSepBankGet(entry, index) ((entry)->m_seSepBankBase + (index))
#define RedEntrySeSepBankGetEnd(entry) RedEntrySeSepBankGet(entry, REDSOUND_SESEP_BANK_ENTRY_COUNT)
#define RedEntryMusicBankGet(entry, index) ((entry)->m_musicBankBase + (index))
#define RedEntryMusicBankGetEnd(entry) RedEntryMusicBankGet(entry, REDSOUND_MUSIC_BANK_ENTRY_COUNT)

enum RedEntryLayout {
	REDSOUND_ENTRY_WAVE_BANK_BASE_OFFSET = (unsigned int)&(((CRedEntry*)0)->m_waveBankBase),
	REDSOUND_ENTRY_SESEP_BANK_BASE_OFFSET = (unsigned int)&(((CRedEntry*)0)->m_seSepBankBase),
	REDSOUND_ENTRY_MUSIC_BANK_BASE_OFFSET = (unsigned int)&(((CRedEntry*)0)->m_musicBankBase),
	REDSOUND_ENTRY_WAVE_LOAD_NO_OFFSET = (unsigned int)&(((CRedEntry*)0)->m_waveLoadNo),
	REDSOUND_ENTRY_WAVE_LOAD_SIZE_OFFSET = (unsigned int)&(((CRedEntry*)0)->m_waveLoadSize),
	REDSOUND_ENTRY_WAVE_LOAD_ADDRESS_OFFSET = (unsigned int)&(((CRedEntry*)0)->m_waveLoadAddress),
	REDSOUND_ENTRY_SIZE = sizeof(CRedEntry),
};

#endif // _FFCC_REDSOUND_REDENTRY_H
