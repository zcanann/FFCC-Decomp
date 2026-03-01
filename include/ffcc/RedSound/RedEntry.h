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
	void WaveDelete(RedHistoryBANK*);
	int WaveOldClear(int, int);
	int WaveHeadAdd(int, RedWaveHeadWD*, int);
	int SetWaveData(int, void*, int);
	void ClearWaveData(int);
	void ClearWaveDataM(int, int, int, int);
	void ClearWaveBank(int);
	int GetWaveBank(int);
	int SearchWaveBase(int);
	void ReentryWaveData(int);
	void WaveHistoryManager(int, int);
	void DisplayWaveInfo();

	void SeSepHistoryAdd();
	void SeSepHistoryDelete(int);
	void SeSepHistoryChoice(RedHistoryBANK*);
	int SearchSeSepSequence(int);
	void SeSepMemoryFree(RedHistoryBANK*);
	void SeSepOldDelete();
	void SeSepHeadAdd(RedSeSepHEAD*);
	void SetSeSepData(RedSeSepHEAD*);
	void ClearSeSepData(int);
	void ClearSeSepDataMG(int, int, int, int);
	int* SearchSeSepBank(int);
	void ReentrySeSepData(int);
	void SeSepHistoryManager(int, int);
	void DisplaySePlayInfo();

	void MusicHistoryAdd();
	void MusicHistoryDelete(int);
	void MusicHistoryChoice(RedHistoryBANK*);
	int SearchMusicSequence(int);
	void MusicMemoryFree(RedHistoryBANK*);
	void MusicOldClear();
	void MusicOldChoice();
	int* SearchMusicBank(int);
	void ReentryMusicData(int);
	void MusicHistoryManager(int, int);
	void MusicHeadAdd(RedMusicHEAD*);
	void SetMusicData(RedMusicHEAD*);
	void DisplayMMemoryInfo();
};

#endif // _FFCC_REDSOUND_REDENTRY_H
