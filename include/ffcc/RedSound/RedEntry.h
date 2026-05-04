#ifndef _FFCC_REDSOUND_REDENTRY_H
#define _FFCC_REDSOUND_REDENTRY_H

struct RedHistoryBANK
{
	int m_id;
	int m_historyNo;
	int m_data;
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

struct RedMusicHEAD
{
	char m_signature[4];
	short m_musicNo;
	short m_waveNo;
	char m_trackCount;
	char m_reverbKind;
	short m_reverbDepth;
	unsigned short m_flags;
	unsigned short m_unk0e;
	int m_size;
	unsigned int m_playFlags;
	int m_unk18;
	int m_unk1c;
};

enum RedMusicHeaderFlag {
	REDSOUND_MUSIC_HEADER_SIZE = sizeof(RedMusicHEAD),
	REDSOUND_MUSIC_HEADER_VOLUME_SCALE_MASK = 0x7F,
	REDSOUND_MUSIC_PLAY_FLAG_RELEASE_NOTES = 0x40000,
};

struct RedSeSepHEAD
{
	char m_signature[8];
	int m_seNo;
	unsigned int m_sizeAndFlags;
	unsigned char m_unk10;
	unsigned char m_waveNoLo;
	unsigned char m_waveNoHi;
	unsigned char m_unk13;
};

enum RedSeSepHeadLayout {
	REDSOUND_SESEP_HEADER_SIZE = 0x10,
	REDSOUND_SESEP_WAVE_NO_HIGH_SCALE = 0x100,
	REDSOUND_SESEP_SIZE_MASK = 0x7FFFFFFF,
	REDSOUND_SESEP_FLAGS_MASK = 0x80000000,
};

struct RedSeINFO
{
	unsigned char m_flagsAndCount;
	unsigned char m_waveNoLo;
	unsigned char m_waveNoHi;
	unsigned char m_eraseTrack;
	unsigned char m_attrMask;
	unsigned char m_sequence[1];
};

enum RedSeInfoLayout {
	REDSOUND_SE_INFO_U16_HIGH_SCALE = 0x100,
	REDSOUND_SE_INFO_MULTI_FLAG = 0x80,
	REDSOUND_SE_INFO_COUNT_MASK = 0x7F,
	REDSOUND_SE_INFO_SEQUENCE_CONTINUE_FLAG = 0x80,
	REDSOUND_SE_INFO_SEQUENCE_OFFSET_MASK = 0x7FFF,
	REDSOUND_SE_INFO_SEQUENCE_ENTRY_SIZE = 2,
};

struct RedSeBlockHEAD
{
	unsigned char m_unk00[0x0A];
	short m_seCount;
	int m_size;
	int m_entries[1];
};

enum RedSeBlockEntryLayout {
	REDSOUND_SE_BLOCK_DATA_FLAG = 0x80000000,
	REDSOUND_SE_BLOCK_ENTRY_MASK = 0x7FFFFFFF,
	REDSOUND_SE_BLOCK_ENTRY_EMPTY = -1,
	REDSOUND_SE_BLOCK_BANK_MASK = 3,
	REDSOUND_SE_BLOCK_BANK_COUNT = REDSOUND_SE_BLOCK_BANK_MASK + 1,
	REDSOUND_SE_BLOCK_BANK_SHIFT = 9,
	REDSOUND_SE_BLOCK_SEQUENCE_MASK = 0x1FF,
	REDSOUND_SE_BLOCK_SEQUENCE_COUNT = REDSOUND_SE_BLOCK_SEQUENCE_MASK + 1,
};

struct RedWaveHeadWD
{
	char m_signature[2];
	short m_waveNo;
	int m_waveSize;
	int m_tableCount;
	int m_toneCount;
	int m_aramAddress;
	int m_loadSize;
};

class CRedEntry
{
public:
	CRedEntry();
	~CRedEntry();

	void Init();

	void WaveHistoryAdd(int);
	void WaveHistoryDelete(int);
	void WaveHistoryChoice(RedHistoryBANK*);
	int SearchWaveSequence(int);
	int SearchUseWave(int);
	int WaveDelete(RedHistoryBANK*);
	int WaveOldClear(int, int);
	int WaveHeadAdd(int, RedWaveHeadWD*, int);
	int SetWaveData(int, void*, int);
	void ClearWaveData(int);
	void ClearWaveDataM(int, int, int, int);
	void ClearWaveBank(int);
	int GetWaveBank(int);
	RedWaveHeadWD* SearchWaveBase(int);
	int ReentryWaveData(int);
	void WaveHistoryManager(int, int);
	void DisplayWaveInfo();

	void SeSepHistoryAdd();
	void SeSepHistoryDelete(int);
	void SeSepHistoryChoice(RedHistoryBANK*);
	int SearchSeSepSequence(int);
	int SeSepMemoryFree(RedHistoryBANK*);
	RedHistoryBANK* SeSepOldDelete();
	RedSeSepHEAD* SeSepHeadAdd(RedSeSepHEAD*);
	RedSeSepHEAD* SetSeSepData(RedSeSepHEAD*);
	int ClearSeSepData(int);
	int ClearSeSepDataMG(int, int, int, int);
	RedHistoryBANK* SearchSeSepBank(int);
	int ReentrySeSepData(int);
	void SeSepHistoryManager(int, int);
	void DisplaySePlayInfo();

	void MusicHistoryAdd();
	void MusicHistoryDelete(int);
	void MusicHistoryChoice(RedHistoryBANK*);
	int SearchMusicSequence(int);
	int MusicMemoryFree(RedHistoryBANK*);
	int MusicOldClear();
	RedHistoryBANK* MusicOldChoice();
	RedHistoryBANK* SearchMusicBank(int);
	int ReentryMusicData(int);
	void MusicHistoryManager(int, int);
	RedMusicHEAD* MusicHeadAdd(RedMusicHEAD*);
	RedMusicHEAD* SetMusicData(RedMusicHEAD*);
	void DisplayMMemoryInfo();

	int m_waveBankBase;
	int m_seSepBankBase;
	int m_musicBankBase;
	int m_waveLoadNo;
	int m_waveLoadSize;
	int m_waveLoadAddress;
};

#endif // _FFCC_REDSOUND_REDENTRY_H
