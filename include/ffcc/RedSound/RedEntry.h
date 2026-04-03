#ifndef _FFCC_REDSOUND_REDENTRY_H
#define _FFCC_REDSOUND_REDENTRY_H

struct RedHistoryBANK;
struct RedMusicHEAD;
struct RedSeSepHEAD;
struct RedWaveHeadWD;

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
	int SearchWaveBase(int);
	int ReentryWaveData(int);
	void WaveHistoryManager(int, int);
	void DisplayWaveInfo();

	void SeSepHistoryAdd();
	void SeSepHistoryDelete(int);
	void SeSepHistoryChoice(RedHistoryBANK*);
	int SearchSeSepSequence(int);
	int SeSepMemoryFree(RedHistoryBANK*);
	unsigned int SeSepOldDelete();
	int SeSepHeadAdd(RedSeSepHEAD*);
	int SetSeSepData(RedSeSepHEAD*);
	int ClearSeSepData(int);
	int ClearSeSepDataMG(int, int, int, int);
	int* SearchSeSepBank(int);
	int ReentrySeSepData(int);
	void SeSepHistoryManager(int, int);
	void DisplaySePlayInfo();

	void MusicHistoryAdd();
	void MusicHistoryDelete(int);
	void MusicHistoryChoice(RedHistoryBANK*);
	int SearchMusicSequence(int);
	int MusicMemoryFree(RedHistoryBANK*);
	int MusicOldClear();
	unsigned int MusicOldChoice();
	int* SearchMusicBank(int);
	int ReentryMusicData(int);
	void MusicHistoryManager(int, int);
	int MusicHeadAdd(RedMusicHEAD*);
	int SetMusicData(RedMusicHEAD*);
	void DisplayMMemoryInfo();

	int m_waveBankBase;
	int m_seSepBankBase;
	int m_musicBankBase;
	int m_waveHistoryIndex;
	int m_seSepHistoryIndex;
	int m_musicHistoryIndex;
	int m_reserved;
};

#endif // _FFCC_REDSOUND_REDENTRY_H
