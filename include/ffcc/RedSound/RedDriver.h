#ifndef _FFCC_REDSOUND_REDDRIVER_H
#define _FFCC_REDSOUND_REDDRIVER_H

#ifndef FFCC_REDSOUND_DMA_CALLBACK_TYPEDEF
#define FFCC_REDSOUND_DMA_CALLBACK_TYPEDEF
typedef void (*RedDmaCallback)(void* callbackData);
#endif

#define REDSOUND_DMA_CALLBACK_NONE ((RedDmaCallback)0)
#define REDSOUND_DMA_CALLBACK_DATA_NONE ((void*)0)

struct RedReverbDepth;
struct RedReverbModeData;
struct RedReverbSize;
struct RedAdsrDATA;
struct RedStreamDATA;
struct RedTrackDATA;
struct RedWaveHeadWD;

enum RedDmaEntryFlag {
	REDSOUND_DMA_FLAG_MAIN_QUEUE = 1,
	REDSOUND_DMA_FLAG_CHUNKED_TRANSFER = 0x8000,
	REDSOUND_DMA_FLAG_QUEUE_MASK = 0xffff7fff,
	REDSOUND_DMA_FLAGS_WAVE_LOAD = REDSOUND_DMA_FLAG_CHUNKED_TRANSFER,
	REDSOUND_DMA_FLAGS_STREAM_LOAD = REDSOUND_DMA_FLAG_CHUNKED_TRANSFER | REDSOUND_DMA_FLAG_MAIN_QUEUE,
};

enum RedDmaDirection {
	REDSOUND_DMA_DIRECTION_TO_ARAM = 0,
	REDSOUND_DMA_DIRECTION_FROM_ARAM = 1,
};

enum RedDmaId {
	REDSOUND_DMA_ID_NONE = 0,
};

enum RedDmaSearchResult {
	REDSOUND_DMA_SEARCH_NOT_FOUND = 0,
	REDSOUND_DMA_SEARCH_FOUND = 1,
};

#define RedDmaMainMemoryAddress(memory) ((int)(memory))

struct RedDmaRequest {
	int m_id;
	int m_direction;
	void* m_mainMemory;
	int m_aramMemory;
	int m_size;
	RedDmaCallback m_callback;
	void* m_callbackData;
};

enum RedDmaRequestLayout {
	REDSOUND_DMA_REQUEST_ID_OFFSET = (unsigned int)&(((RedDmaRequest*)0)->m_id),
	REDSOUND_DMA_REQUEST_DIRECTION_OFFSET = (unsigned int)&(((RedDmaRequest*)0)->m_direction),
	REDSOUND_DMA_REQUEST_MAIN_MEMORY_OFFSET = (unsigned int)&(((RedDmaRequest*)0)->m_mainMemory),
	REDSOUND_DMA_REQUEST_ARAM_MEMORY_OFFSET = (unsigned int)&(((RedDmaRequest*)0)->m_aramMemory),
	REDSOUND_DMA_REQUEST_SIZE_OFFSET = (unsigned int)&(((RedDmaRequest*)0)->m_size),
	REDSOUND_DMA_REQUEST_CALLBACK_OFFSET = (unsigned int)&(((RedDmaRequest*)0)->m_callback),
	REDSOUND_DMA_REQUEST_CALLBACK_DATA_OFFSET = (unsigned int)&(((RedDmaRequest*)0)->m_callbackData),
	REDSOUND_DMA_MAIN_QUEUE_INDEX = 0,
	REDSOUND_DMA_STREAM_QUEUE_INDEX = 1,
	REDSOUND_DMA_QUEUE_COUNT = 2,
	REDSOUND_DMA_REQUEST_SIZE = sizeof(RedDmaRequest),
	REDSOUND_DMA_QUEUE_ENTRY_SHIFT = 7,
	REDSOUND_DMA_QUEUE_ENTRY_COUNT = 1 << REDSOUND_DMA_QUEUE_ENTRY_SHIFT,
	REDSOUND_DMA_QUEUE_WORD_COUNT = REDSOUND_DMA_REQUEST_SIZE * REDSOUND_DMA_QUEUE_ENTRY_COUNT / sizeof(int),
	REDSOUND_DMA_CONTROL_WORD_COUNT = REDSOUND_DMA_QUEUE_WORD_COUNT * REDSOUND_DMA_QUEUE_COUNT,
	REDSOUND_DMA_CONTROL_ENTRY_COUNT = REDSOUND_DMA_QUEUE_ENTRY_COUNT * 2,
	REDSOUND_DMA_QUEUE_SIZE = REDSOUND_DMA_REQUEST_SIZE * REDSOUND_DMA_QUEUE_ENTRY_COUNT,
	REDSOUND_DMA_CONTROL_SIZE = REDSOUND_DMA_QUEUE_SIZE * REDSOUND_DMA_QUEUE_COUNT,
	REDSOUND_DMA_TRANSFER_ALIGN_SHIFT = 5,
	REDSOUND_DMA_TRANSFER_ALIGN = 1 << REDSOUND_DMA_TRANSFER_ALIGN_SHIFT,
	REDSOUND_DMA_TRANSFER_ALIGN_MASK = ~(REDSOUND_DMA_TRANSFER_ALIGN - 1),
	REDSOUND_DMA_MAX_CHUNK_SHIFT = 18,
	REDSOUND_DMA_MAX_CHUNK_SIZE = 1 << REDSOUND_DMA_MAX_CHUNK_SHIFT,
	REDSOUND_DMA_ARQ_OWNER_ID = 0x469,
	REDSOUND_DMA_ARQ_PRIORITY = 1,
};

unsigned int DeltaTimeSumup(unsigned char** buffer);
#define RedTrackCommandReadDeltaTime(track) DeltaTimeSumup((unsigned char**)&(track)->m_command)
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
	void ClearMusicData(int musicId);
	int MusicPlayState(int musicId);
	void MusicStop(int musicId);
	int MusicPlay(int musicId, int volume, int mode);
	int MusicPlay(void* musicData, int volume, int mode);
	int MusicCrossPlay(int musicId, int volume, int mode);
	int MusicCrossPlay(void* musicData, int volume, int mode);
	int MusicNextPlay(int musicId, int volume, int mode);
	int MusicNextPlay(void* musicData, int volume, int mode);
	void MusicMasterVolume(int volume);
	void MusicFadeOut(int musicId, int frameCount);
	void MusicVolume(int musicId, int volume, int frameCount);
	void MusicTempo(int tempo, int frameCount);
	void MusicPitch(int pitch, int frameCount);
	void MusicPause(int musicId, int pause);
	void DisplayMusicInfo();
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
	void SeStopG(int group);
	void SeStopMG(int bank, int sep, int group, int kind);
	int SePlay(int bank, int sep, int autoId, int pan, int volume, int pitch);
	int SePlay(void* seSepData, int autoId, int pan, int volume, int pitch);
	void SeMasterVolume(int volume);
	void SeFadeOut(int seId, int frameCount);
	void SeVolume(int seId, int volume, int frameCount);
	void SePan(int seId, int pan, int frameCount);
	void SePitch(int seId, int pitch, int frameCount);
	void SePause(int seId, int pause);
	int GetSeVolume(int seId, int mode);
	int ReportSeLoop(int seId);
	void DisplaySePlayInfo();
	void ClearSePlayLine();
	RedTrackDATA* GetSePlayTrack();


	int StreamPlayState(int streamId);
	int GetStreamPlayPoint(int streamId, int* playPoint, int* readPoint);
	RedStreamDATA* GetStreamPlayBlock(int streamId);
	void StreamStop(int streamId);
	int StreamPlay(int streamId, void* streamHeader, int fileSize, int pan, int volume);
	void StreamVolume(int streamId, int volume, int frameCount);
	void StreamPan(int streamId, int pan, int frameCount);
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
	void SetReverb(int kind, int mode, int* reverbParams);
	RedReverbSize* GetReverbInfo();
	RedReverbDepth* GetReverbDepth();
	void SetReverbDepth(int bank, int depth, int frameCount);
	void SetMute(unsigned int voiceNo, unsigned int mute);
	int PlayWaveItem(int waveNo, int itemNo, int key, int pan, int volume);
	void StopWaveItem();
	int WavePitchCompute(int key, int pitch);
	void SetWaveTune(int key, int fineTune);
	void SetWavePitch(int pitch);
	void SetWaveAdsr(int attack, RedAdsrDATA* adsr);
	RedReverbModeData* GetReverbModeTable(int mode);
	void TestProcess(int mode);
};

#endif // _FFCC_REDSOUND_REDDRIVER_H
