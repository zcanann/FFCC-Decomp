#ifndef _FFCC_REDSOUND_REDSOUND_H
#define _FFCC_REDSOUND_REDSOUND_H

class CRedSound
{
public:
	CRedSound();
	~CRedSound();

	unsigned int GetAutoID();
	int* EntryStandbyID(int);
	void Init(void*, int, int, int);
	void Start();
	void End();
	void GetProgramTime();
	void ReportPrint(int);
	void ReportStandby(int);

	void DMAEntry(int, int, int, int, int, void (*)(void*), void*);
	void DMACheck(int);

	void SetSoundMode(int);
	void GetSoundMode();

	void SetReverb(int, int);
	void SetReverbDepth(int, int, int);

	void SetMusicData(void*);
	void ReentryMusicData(int);
	void MusicStop(int);
	void MusicPlay(int, int, int);
	void MusicCrossPlay(int, int, int);
	void MusicNextPlay(int, int, int);
	void MusicMasterVolume(int);
	void MusicFadeOut(int, int);
	void MusicVolume(int, int, int);
	void SetMusicPhraseStop(int);

	void SetSeBlockData(int, void*);
	void SetSeSepData(void*);
	void ClearSeSepData(int);
	void ClearSeSepDataMG(int, int, int, int);
	void ReentrySeSepData(int);

	void SePlayState(int);
	void SeStop(int);
	void SeStopMG(int, int, int, int);
	void SePlay(int, int, int, int, int);
	void SeMasterVolume(int);
	void SeFadeOut(int, int);
	void SeVolume(int, int, int);
	void SePan(int, int, int);
	void SePitch(int, int, int);
	void SePause(int, int);
	void GetSeVolume(int, int);
	void ReportSeLoop(int);
	void DisplaySePlayInfo();

	void StreamPlayState(int);
	void GetStreamPlayPoint(int, int*, int*);
	void StreamStop(int);
	void StreamPlay(void*, int, int, int);
	void StreamVolume(int, int, int);
	void StreamPause(int, int);

	void SetWaveData(int, void*, int);
	void ClearWaveData(int);
	void ClearWaveDataM(int, int, int, int);
	void ClearWaveBank(int);
	void ReentryWaveData(int);
	void DisplayWaveInfo();

	void TestProcess(int);
};

#endif // _FFCC_REDSOUND_REDSOUND_H
