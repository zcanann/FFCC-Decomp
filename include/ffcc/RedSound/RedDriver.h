#ifndef _FFCC_REDSOUND_REDDRIVER_H
#define _FFCC_REDSOUND_REDDRIVER_H

struct OSAlarm;
struct OSContext;

void _SetSoundMode(int*);
void _SetReverbDepth(int*);
void _SetMusicData(int*);
void _MusicStop(int*);
void _MusicPlaySequence(int*);
void _MusicCrossPlaySequence(int*);
void _MusicNextPlaySequence(int*);
void _MusicMasterVolume(int*);
void _MusicVolume(int*);
void _SetMusicPhraseStop(int*);
void _SetSeBlockData(int*);
void _SetSeSepData(int*);
void _ClearSeSepData(int*);
void _ClearSeSepDataMG(int*);
void _SeStop(int*);
void _SeStopMG(int*);
void _SeBlockPlay(int*);
void _SeSepPlay(int*);
void _SeSepPlaySequence(int*);
void _SeMasterVolume(int*);
void _SeVolume(int*);
void _SePan(int*);
void _SePitch(int*);
void _SePause(int*);
void _StreamStop(int*);
void _StreamPlay(int*);
void _StreamVolume(int*);
void _StreamPause(int*);
void _EntryExecCommand(void (*)(int*), int, int, int, int, int, int, int);
void _ExecuteCommand();
unsigned int DeltaTimeSumup(unsigned char**);
unsigned int GetMyEntryID();
void _MyAlarmHandler(OSAlarm*, OSContext*);
void RedSleep(int);
int _MainThread(void*);
int _WaveSettingThread(void*);
void _DMACheckProcess();
void _DmaCallback(unsigned long);
int RedDmaEntry(int, int, int, int, int, void (*)(void*), void*);
int RedDmaSearchID(int);
void _DmaExecute();
void _DmaExecuteThread(void*);
void _MusicSkipThread(void*);
void _RedAXCallback();

class CRedDriver
{
public:
	CRedDriver();
	~CRedDriver();

	void Init();
	void End();
	void GetProgramTime();
	void SetSoundMode(int);
	void GetSoundMode();
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

	void* SetSeBlockData(int, void*);
	void SetSeSepData(void*);
	void ClearSeSepData(int);
	void ClearSeSepDataMG(int, int, int, int);
	void ReentrySeSepData(int);

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
	void GetSeVolume(int, int);
	void ReportSeLoop(int);
	void DisplaySePlayInfo();


	int StreamPlayState(int);
	void GetStreamPlayPoint(int, int*, int*);
	void StreamStop(int);
	void StreamPlay(int, void*, int, int, int);
	void StreamVolume(int, int, int);
	void StreamPause(int, int);

	void ClearWaveData(int);
	void ClearWaveDataM(int, int, int, int);
	void ClearWaveBank(int);
	void SetWaveData(int, int, void*, int);
	void ReentryWaveData(int);
	void DisplayWaveInfo();

	void SetReverb(int, int);
	void SetReverbDepth(int, int, int);
	void TestProcess(int);
};

#endif // _FFCC_REDSOUND_REDDRIVER_H
