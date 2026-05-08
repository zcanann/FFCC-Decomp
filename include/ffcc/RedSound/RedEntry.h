#ifndef _FFCC_REDSOUND_REDENTRY_H
#define _FFCC_REDSOUND_REDENTRY_H

struct RedMusicHEAD;
struct RedSeSepHEAD;
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
	REDSOUND_HISTORY_BANK_ENTRY_SIZE = sizeof(RedHistoryBANK),
	REDSOUND_WAVE_BANK_ENTRY_COUNT = 0x40,
	REDSOUND_WAVE_PRIMARY_BANK_ENTRY_COUNT = 0x10,
	REDSOUND_WAVE_PRIMARY_BANK_MASK = REDSOUND_WAVE_PRIMARY_BANK_ENTRY_COUNT - 1,
	REDSOUND_WAVE_RELEASE_HISTORY_NO = REDSOUND_WAVE_PRIMARY_BANK_ENTRY_COUNT + 4,
	REDSOUND_SESEP_BANK_ENTRY_COUNT = 0x100,
	REDSOUND_MUSIC_BANK_ENTRY_COUNT = 0x04,
	REDSOUND_WAVE_BANK_SIZE = REDSOUND_HISTORY_BANK_ENTRY_SIZE * REDSOUND_WAVE_BANK_ENTRY_COUNT,
	REDSOUND_WAVE_HISTORY_BANK_OFFSET = REDSOUND_HISTORY_BANK_ENTRY_SIZE * REDSOUND_WAVE_PRIMARY_BANK_ENTRY_COUNT,
	REDSOUND_SESEP_BANK_SIZE = REDSOUND_HISTORY_BANK_ENTRY_SIZE * REDSOUND_SESEP_BANK_ENTRY_COUNT,
	REDSOUND_MUSIC_BANK_SIZE = REDSOUND_HISTORY_BANK_ENTRY_SIZE * REDSOUND_MUSIC_BANK_ENTRY_COUNT,
};

enum RedEntryFileLayoutSize {
	REDSOUND_MUSIC_SIGNATURE_SIZE = 4,
	REDSOUND_SESEP_SIGNATURE_SIZE = 8,
	REDSOUND_SE_INFO_SEQUENCE_MIN_COUNT = 1,
	REDSOUND_SE_BLOCK_SIGNATURE_SIZE = 8,
	REDSOUND_SE_BLOCK_ENTRY_MIN_COUNT = 1,
	REDSOUND_WAVE_SIGNATURE_SIZE = 2,
	REDSOUND_WAVE_SIGNATURE_MAGIC0 = 'W',
	REDSOUND_WAVE_SIGNATURE_MAGIC1 = 'D',
	REDSOUND_WAVE_OFFSET_MIN_COUNT = 1,
};

enum RedEntryWaveAramLayout {
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
	REDSOUND_WAVE_FIXED_REGION_OFFSET = 0x300000,
	REDSOUND_WAVE_FIXED_REGION_SIZE = 0x100000,
	REDSOUND_WAVE_LARGE_REGION_OFFSET = 0x400000,
	REDSOUND_WAVE_LARGE_REGION_SIZE = 0x400000,
};

enum RedMusicSignature {
	REDSOUND_MUSIC_SIGNATURE_0 = 'B',
	REDSOUND_MUSIC_SIGNATURE_1 = 'G',
	REDSOUND_MUSIC_SIGNATURE_2 = 'M',
};

enum RedSeSepSignature {
	REDSOUND_SESEP_SIGNATURE_0 = 'S',
	REDSOUND_SESEP_SIGNATURE_1 = 'e',
	REDSOUND_SESEP_SIGNATURE_2 = 'S',
	REDSOUND_SESEP_SIGNATURE_3 = 'e',
	REDSOUND_SESEP_SIGNATURE_4 = 'p',
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
	unsigned char m_command[1];
};

enum RedMusicHeaderFlag {
	REDSOUND_MUSIC_HEADER_SIZE = sizeof(RedMusicHEAD),
	REDSOUND_MUSIC_HEADER_SIGNATURE_OFFSET = 0x00,
	REDSOUND_MUSIC_HEADER_MUSIC_NO_OFFSET = 0x04,
	REDSOUND_MUSIC_HEADER_WAVE_NO_OFFSET = 0x06,
	REDSOUND_MUSIC_HEADER_TRACK_COUNT_OFFSET = 0x08,
	REDSOUND_MUSIC_HEADER_REVERB_KIND_OFFSET = 0x09,
	REDSOUND_MUSIC_HEADER_REVERB_DEPTH_OFFSET = 0x0A,
	REDSOUND_MUSIC_HEADER_FLAGS_OFFSET = 0x0C,
	REDSOUND_MUSIC_HEADER_RESERVED0E_OFFSET = 0x0E,
	REDSOUND_MUSIC_HEADER_DATA_SIZE_OFFSET = 0x10,
	REDSOUND_MUSIC_HEADER_PLAY_FLAGS_OFFSET = 0x14,
	REDSOUND_MUSIC_HEADER_RESERVED18_OFFSET = 0x18,
	REDSOUND_MUSIC_HEADER_RESERVED1C_OFFSET = 0x1C,
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
	REDSOUND_SESEP_HEADER_SIZE = 0x10,
	REDSOUND_SESEP_STRUCT_SIZE = 0x14,
	REDSOUND_SESEP_SIGNATURE_OFFSET = 0x00,
	REDSOUND_SESEP_SE_NO_OFFSET = 0x08,
	REDSOUND_SESEP_SIZE_AND_FLAGS_OFFSET = 0x0C,
	REDSOUND_SESEP_INFO_OFFSET = 0x10,
	REDSOUND_SESEP_WAVE_NO_LO_OFFSET = 0x11,
	REDSOUND_SESEP_WAVE_NO_HI_OFFSET = 0x12,
	REDSOUND_SESEP_RESERVED13_OFFSET = 0x13,
	REDSOUND_SESEP_WAVE_NO_HIGH_SCALE = 0x100,
	REDSOUND_SESEP_SIZE_MASK = 0x7FFFFFFF,
	REDSOUND_SESEP_FLAGS_MASK = 0x80000000,
};

struct RedSeInfoSequence
{
	unsigned char m_offsetLo;
	unsigned char m_offsetHiAndFlags;
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
	REDSOUND_SE_INFO_FLAGS_AND_COUNT_OFFSET = 0,
	REDSOUND_SE_INFO_WAVE_NO_LO_OFFSET = 1,
	REDSOUND_SE_INFO_WAVE_NO_HI_OFFSET = 2,
	REDSOUND_SE_INFO_ERASE_TRACK_OFFSET = 3,
	REDSOUND_SE_INFO_ATTR_MASK_OFFSET = 4,
	REDSOUND_SE_INFO_SEQUENCE_OFFSET = 5,
	REDSOUND_SE_INFO_MIN_SIZE = 7,
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
	unsigned char m_reserved08[0x0A - 0x08];
	short m_seCount;
	int m_size;
	int m_entries[REDSOUND_SE_BLOCK_ENTRY_MIN_COUNT];
};

enum RedSeBlockEntryLayout {
	REDSOUND_SE_BLOCK_HEADER_SIZE = 0x10,
	REDSOUND_SE_BLOCK_STRUCT_SIZE = 0x14,
	REDSOUND_SE_BLOCK_SIGNATURE_OFFSET = 0x00,
	REDSOUND_SE_BLOCK_SE_COUNT_OFFSET = 0x0A,
	REDSOUND_SE_BLOCK_SIZE_OFFSET = 0x0C,
	REDSOUND_SE_BLOCK_ENTRIES_OFFSET = 0x10,
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

struct RedWaveHeadWD
{
	char m_signature[REDSOUND_WAVE_SIGNATURE_SIZE];
	short m_waveNo;
	int m_waveSize;
	int m_tableCount;
	int m_toneCount;
	int m_aramAddress;
	int m_loadSize;
	unsigned char m_reserved18[0x20 - 0x18];
	int m_waveOffsets[REDSOUND_WAVE_OFFSET_MIN_COUNT];
};

enum RedWaveHeadLayout {
	REDSOUND_WAVE_HEAD_WAVE_NO_OFFSET = 0x02,
	REDSOUND_WAVE_HEAD_WAVE_SIZE_OFFSET = 0x04,
	REDSOUND_WAVE_HEAD_TABLE_COUNT_OFFSET = 0x08,
	REDSOUND_WAVE_HEAD_TONE_COUNT_OFFSET = 0x0C,
	REDSOUND_WAVE_HEAD_ARAM_ADDRESS_OFFSET = 0x10,
	REDSOUND_WAVE_HEAD_LOAD_SIZE_OFFSET = 0x14,
	REDSOUND_WAVE_HEAD_OFFSETS_OFFSET = 0x20,
};

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
	int GetWaveBank(int waveNo);
	RedWaveHeadWD* SearchWaveBase(int waveNo);
	int ReentryWaveData(int waveNo);
	void WaveHistoryManager(int waveNo, int count);
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
	void SeSepHistoryManager(int seNo, int count);
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
	void MusicHistoryManager(int musicNo, int count);
	RedMusicHEAD* MusicHeadAdd(RedMusicHEAD* musicHead);
	RedMusicHEAD* SetMusicData(RedMusicHEAD* musicHead);
	void DisplayMMemoryInfo();

	RedHistoryBANK* m_waveBankBase;
	RedHistoryBANK* m_seSepBankBase;
	RedHistoryBANK* m_musicBankBase;
	int m_waveLoadNo;
	int m_waveLoadSize;
	int m_waveLoadAddress;
};

#endif // _FFCC_REDSOUND_REDENTRY_H
