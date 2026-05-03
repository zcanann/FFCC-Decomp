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
	REDSOUND_HISTORY_BANK_ENTRY_SIZE = sizeof(RedHistoryBANK),
	REDSOUND_WAVE_BANK_ENTRY_COUNT = 0x40,
	REDSOUND_WAVE_PRIMARY_BANK_ENTRY_COUNT = 0x10,
	REDSOUND_SESEP_BANK_ENTRY_COUNT = 0x100,
	REDSOUND_MUSIC_BANK_ENTRY_COUNT = 0x04,
	REDSOUND_WAVE_BANK_SIZE = REDSOUND_HISTORY_BANK_ENTRY_SIZE * REDSOUND_WAVE_BANK_ENTRY_COUNT,
	REDSOUND_WAVE_HISTORY_BANK_OFFSET = REDSOUND_HISTORY_BANK_ENTRY_SIZE * REDSOUND_WAVE_PRIMARY_BANK_ENTRY_COUNT,
	REDSOUND_SESEP_BANK_SIZE = REDSOUND_HISTORY_BANK_ENTRY_SIZE * REDSOUND_SESEP_BANK_ENTRY_COUNT,
	REDSOUND_MUSIC_BANK_SIZE = REDSOUND_HISTORY_BANK_ENTRY_SIZE * REDSOUND_MUSIC_BANK_ENTRY_COUNT,
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

struct RedSeINFO
{
	unsigned char m_flagsAndCount;
	unsigned char m_waveNoLo;
	unsigned char m_waveNoHi;
	unsigned char m_eraseTrack;
	unsigned char m_attrMask;
	unsigned char m_sequence[1];
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
	REDSOUND_SE_BLOCK_BANK_SHIFT = 9,
	REDSOUND_SE_BLOCK_SEQUENCE_MASK = 0x1FF,
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
	int SeSepHeadAdd(RedSeSepHEAD*);
	int SetSeSepData(RedSeSepHEAD*);
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
	int MusicHeadAdd(RedMusicHEAD*);
	int SetMusicData(RedMusicHEAD*);
	void DisplayMMemoryInfo();

	int m_waveBankBase;
	int m_seSepBankBase;
	int m_musicBankBase;
	int m_waveLoadNo;
	int m_waveLoadSize;
	int m_waveLoadAddress;
};

#endif // _FFCC_REDSOUND_REDENTRY_H
