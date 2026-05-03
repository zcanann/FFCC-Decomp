#ifndef _FFCC_REDSOUND_REDDRIVER_H
#define _FFCC_REDSOUND_REDDRIVER_H

enum RedDmaEntryFlag {
	REDSOUND_DMA_FLAG_MAIN_QUEUE = 1,
	REDSOUND_DMA_FLAG_CHUNKED_TRANSFER = 0x8000,
	REDSOUND_DMA_FLAG_QUEUE_MASK = 0xffff7fff,
	REDSOUND_DMA_FLAGS_WAVE_LOAD = REDSOUND_DMA_FLAG_CHUNKED_TRANSFER,
	REDSOUND_DMA_FLAGS_STREAM_LOAD = REDSOUND_DMA_FLAG_CHUNKED_TRANSFER | REDSOUND_DMA_FLAG_MAIN_QUEUE,
};

unsigned int DeltaTimeSumup(unsigned char**);
unsigned int GetMyEntryID();
void RedSleep(int);
int RedDmaEntry(int, int, int, int, int, void (*)(void*), void*);
int RedDmaSearchID(int);

class CRedDriver
{
public:
	CRedDriver();
	~CRedDriver();

	void Init();
	void End();
	int GetProgramTime();
	void SetSoundMode(int);
	int GetSoundMode();
	int SetMusicData(void*);
	int ReentryMusicData(int);
	void MusicStop(int);
	int MusicPlay(int, int, int);
	int MusicCrossPlay(int, int, int);
	int MusicNextPlay(int, int, int);
	void MusicMasterVolume(int);
	void MusicFadeOut(int, int);
	void MusicVolume(int, int, int);
	void SetMusicPhraseStop(int);

	void* SetSeBlockData(int, void*);
	int SetSeSepData(void*);
	void ClearSeSepData(int);
	void ClearSeSepDataMG(int, int, int, int);
	int ReentrySeSepData(int);

	int SePlayState(int);
	void SeStop(int);
	void SeStopMG(int, int, int, int);
	int SePlay(int, int, int, int, int, int);
	void SeMasterVolume(int);
	void SeFadeOut(int, int);
	void SeVolume(int, int, int);
	void SePan(int, int, int);
	void SePitch(int, int, int);
	void SePause(int, int);
	int GetSeVolume(int, int);
	int ReportSeLoop(int);
	void DisplaySePlayInfo();


	int StreamPlayState(int);
	int GetStreamPlayPoint(int, int*, int*);
	void StreamStop(int);
	int StreamPlay(int, void*, int, int, int);
	void StreamVolume(int, int, int);
	void StreamPause(int, int);

	void ClearWaveData(int);
	void ClearWaveDataM(int, int, int, int);
	void ClearWaveBank(int);
	void SetWaveData(int, int, void*, int);
	int ReentryWaveData(int);
	void DisplayWaveInfo();

	void SetReverb(int, int);
	void SetReverbDepth(int, int, int);
	void TestProcess(int);
};

#endif // _FFCC_REDSOUND_REDDRIVER_H
