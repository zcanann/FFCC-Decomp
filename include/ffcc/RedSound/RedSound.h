#ifndef _FFCC_REDSOUND_REDSOUND_H
#define _FFCC_REDSOUND_REDSOUND_H

#ifndef FFCC_REDSOUND_DMA_CALLBACK_TYPEDEF
#define FFCC_REDSOUND_DMA_CALLBACK_TYPEDEF
typedef void (*RedDmaCallback)(void* callbackData);
#endif

struct RedAdsrDATA;
struct RedMemoryBlock;
struct RedSoundCONTROL;
struct RedWaveHeadWD;
struct RedReverbDepth;
struct RedReverbModeData;
struct RedReverbSize;
struct RedStreamDATA;
struct RedTrackDATA;
struct RedVoiceDATA;

class CRedSound
{
public:
	CRedSound();
	~CRedSound();

	unsigned int GetAutoID();
	int* EntryStandbyID(int entryId);
	int Init(void* memory, int memorySize, int aramMemory, int aramMemorySize);
	void Start();
	void End();
	int GetProgramTime();
	int GetMasterTime();
	void Sleep(int microseconds);
	void ReportPrint(int enable);
	int ReportStandby(int entryId);

	int DMAEntry(int flags, int direction, int mainMemory, int aramMemory, int size,
	             RedDmaCallback callback, void* callbackData);
	int DMACheck(int id);
	void SetDMAMode(int mode);

	void SetSoundMode(int soundMode);
	int GetSoundMode();

	void SetReverb(int kind, int mode);
	void SetReverb(int kind, int mode, int* params);
	RedReverbSize* GetReverbInfo();
	RedReverbDepth* GetReverbDepth();
	void SetReverbDepth(int type, int depth, int frameCount);
	void SetMute(unsigned int voiceNo, unsigned int mute);
	RedReverbModeData* GetReverbModeTable(int mode);

	void SetMusicData(void* musicData);
	int ReentryMusicData(int musicId);
	void ClearMusicData(int musicId);
	int MusicPlayState(int musicId);
	int CheckMusicEntry(int musicId);
	void MusicStop(int musicId);
	void MusicPlay(int musicId, int volume, int mode);
	void MusicPlay(void* musicData, int volume, int mode);
	void MusicCrossPlay(int musicId, int volume, int mode);
	void MusicCrossPlay(void* musicData, int volume, int mode);
	void MusicNextPlay(int musicId, int volume, int mode);
	void MusicNextPlay(void* musicData, int volume, int mode);
	void MusicMasterVolume(int volume);
	void MusicFadeOut(int musicId, int frameCount);
	void MusicVolume(int musicId, int volume, int frameCount);
	void MusicTempo(int tempo, int frameCount);
	void MusicPitch(int pitch, int frameCount);
	void MusicPause(int musicId, int pause);
	void SetMusicPhraseStop(int enable);
	void SetMusicFastSpeed(int speed);
	int CheckMusicPhraseStop();
	void DisplayMusicInfo();

	void SetSeBlockData(int bank, void* blockData);
	void SetSeSepData(void* seSepData);
	void ClearSeSepData(int sepId);
	void ClearSeSepDataMG(int bank, int sep, int group, int kind);
	int ReentrySeSepData(int sepId);

	int SePlayState(int seId);
	void SeStop(int seId);
	void SeStopG(int group);
	void SeStopMG(int bank, int sep, int group, int kind);
	int SePlay(int bank, int sep, int pan, int volume, int pitch);
	int SePlay(void* seSepData, int pan, int volume, int pitch);
	int CheckSeSepEntry(int sepId);
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
	void GetStreamPlayPoint(int streamId, int* current, int* total);
	RedStreamDATA* GetStreamPlayBlock(int streamId);
	void StreamStop(int streamId);
	int StreamPlay(void* streamHeader, int fileSize, int pan, int volume);
	void StreamVolume(int streamId, int volume, int frameCount);
	void StreamPan(int streamId, int pan, int frameCount);
	void StreamPause(int streamId, int pause);

	unsigned int SetWaveData(int waveID, void* waveData, int waveSize);
	void ClearWaveData(int waveNo);
	void ClearWaveDataM(int waveNo0, int waveNo1, int waveNo2, int waveNo3);
	void ClearWaveBank(int bank);
	int ReentryWaveData(int waveNo);
	RedWaveHeadWD* GetWaveInfo(int waveNo);
	int CheckWaveEntry(int waveNo);
	void DisplayWaveInfo();
	void DisplayMMemoryInfo();
	void GetMakeTime(char** date, char** time);
	int GetMainBufferAddress();
	int GetMainBufferSize();
	RedMemoryBlock* GetMainBankAddress();
	int GetABufferAddress();
	RedMemoryBlock* GetABankAddress();
	RedSoundCONTROL* GetControlAddress();
	RedVoiceDATA* GetVoiceAddress();

	void TestProcess(int mode);
};

#endif // _FFCC_REDSOUND_REDSOUND_H
