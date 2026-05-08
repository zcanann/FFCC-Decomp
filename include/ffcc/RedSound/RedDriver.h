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
void RedSleep(int microseconds);
int RedDmaEntry(int flags, int direction, int mainMemory, int aramMemory, int size, void (*callback)(void*), void* callbackData);
int RedDmaSearchID(int id);

class CRedDriver
{
public:
	CRedDriver();
	~CRedDriver();

	void Init();
	void End();
	int GetProgramTime();
	void SetSoundMode(int soundMode);
	int GetSoundMode();
	int SetMusicData(void* musicData);
	int ReentryMusicData(int musicId);
	void MusicStop(int musicId);
	int MusicPlay(int musicId, int volume, int mode);
	int MusicCrossPlay(int musicId, int volume, int mode);
	int MusicNextPlay(int musicId, int volume, int mode);
	void MusicMasterVolume(int volume);
	void MusicFadeOut(int musicId, int frameCount);
	void MusicVolume(int musicId, int volume, int frameCount);
	void SetMusicPhraseStop(int enable);

	void* SetSeBlockData(int bank, void* data);
	int SetSeSepData(void* data);
	void ClearSeSepData(int sepId);
	void ClearSeSepDataMG(int bank, int sep, int group, int kind);
	int ReentrySeSepData(int sepId);

	int SePlayState(int seId);
	void SeStop(int seId);
	void SeStopMG(int bank, int sep, int group, int kind);
	int SePlay(int bank, int sep, int autoId, int pan, int volume, int pitch);
	void SeMasterVolume(int volume);
	void SeFadeOut(int seId, int frameCount);
	void SeVolume(int seId, int volume, int frameCount);
	void SePan(int seId, int pan, int frameCount);
	void SePitch(int seId, int pitch, int frameCount);
	void SePause(int seId, int pause);
	int GetSeVolume(int seId, int mode);
	int ReportSeLoop(int seId);
	void DisplaySePlayInfo();


	int StreamPlayState(int streamId);
	int GetStreamPlayPoint(int streamId, int* current, int* total);
	void StreamStop(int streamId);
	int StreamPlay(int streamId, void* streamHeader, int fileSize, int pan, int volume);
	void StreamVolume(int streamId, int volume, int frameCount);
	void StreamPause(int streamId, int pause);

	void ClearWaveData(int waveNo);
	void ClearWaveDataM(int waveNo0, int waveNo1, int waveNo2, int waveNo3);
	void ClearWaveBank(int bank);
	void SetWaveData(int slot, int waveID, void* data, int size);
	int ReentryWaveData(int waveNo);
	void DisplayWaveInfo();

	void SetReverb(int kind, int mode);
	void SetReverbDepth(int type, int depth, int frameCount);
	void TestProcess(int mode);
};

#endif // _FFCC_REDSOUND_REDDRIVER_H
