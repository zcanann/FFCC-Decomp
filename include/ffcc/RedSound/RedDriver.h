#ifndef _FFCC_REDSOUND_REDDRIVER_H
#define _FFCC_REDSOUND_REDDRIVER_H

#ifndef FFCC_REDSOUND_DMA_CALLBACK_TYPEDEF
#define FFCC_REDSOUND_DMA_CALLBACK_TYPEDEF
typedef void (*RedDmaCallback)(void* callbackData);
#endif

struct RedReverbDepth;
struct RedReverbModeData;
struct RedReverbSize;
struct RedWaveHeadWD;

enum RedDmaEntryFlag {
	REDSOUND_DMA_FLAG_MAIN_QUEUE = 1,
	REDSOUND_DMA_FLAG_CHUNKED_TRANSFER = 0x8000,
	REDSOUND_DMA_FLAG_QUEUE_MASK = 0xffff7fff,
	REDSOUND_DMA_FLAGS_WAVE_LOAD = REDSOUND_DMA_FLAG_CHUNKED_TRANSFER,
	REDSOUND_DMA_FLAGS_STREAM_LOAD = REDSOUND_DMA_FLAG_CHUNKED_TRANSFER | REDSOUND_DMA_FLAG_MAIN_QUEUE,
};

unsigned int DeltaTimeSumup(unsigned char** buffer);
unsigned int GetMyEntryID();
void RedSleep(int microseconds);
int RedDmaEntry(int flags, int direction, int mainMemory, int aramMemory, int size,
                RedDmaCallback callback, void* callbackData);
int RedDmaSearchID(int id);
void RedDmaClearID(int id);
void RedSetDMAMode(int mode);

class CRedDriver
{
public:
	CRedDriver();
	~CRedDriver();

	void Init();
	void End();
	int GetProgramTime();
	int GetMasterTime();
	void SetSoundMode(int soundMode);
	int GetSoundMode();
	int SetMusicData(void* musicData);
	int ReentryMusicData(int musicId);
	int CheckMusicEntry(int musicId);
	void MusicStop(int musicId);
	int MusicPlay(int musicId, int volume, int mode);
	int MusicCrossPlay(int musicId, int volume, int mode);
	int MusicNextPlay(int musicId, int volume, int mode);
	void MusicMasterVolume(int volume);
	void MusicFadeOut(int musicId, int frameCount);
	void MusicVolume(int musicId, int volume, int frameCount);
	void SetMusicPhraseStop(int enable);
	void SetMusicFastSpeed(int speed);
	int CheckMusicPhraseStop();

	void* SetSeBlockData(int bank, void* blockData);
	int SetSeSepData(void* seSepData);
	void ClearSeSepData(int sepId);
	void ClearSeSepDataMG(int bank, int sep, int group, int kind);
	int ReentrySeSepData(int sepId);
	int CheckSeSepEntry(int sepId);

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
	void SetWaveData(int slot, int waveID, void* waveData, int waveSize);
	int ReentryWaveData(int waveNo);
	RedWaveHeadWD* GetWaveInfo(int waveNo);
	int CheckWaveEntry(int waveNo);
	void DisplayWaveInfo();
	void DisplayMMemoryInfo();

	void SetReverb(int kind, int mode);
	RedReverbSize* GetReverbInfo();
	RedReverbDepth* GetReverbDepth();
	void SetReverbDepth(int type, int depth, int frameCount);
	void SetMute(unsigned int voiceNo, unsigned int mute);
	RedReverbModeData* GetReverbModeTable(int mode);
	void TestProcess(int mode);
};

#endif // _FFCC_REDSOUND_REDDRIVER_H
