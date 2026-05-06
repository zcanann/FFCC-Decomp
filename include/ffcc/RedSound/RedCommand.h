#ifndef _FFCC_REDSOUND_REDCOMMAND_H
#define _FFCC_REDSOUND_REDCOMMAND_H

struct RedMusicHEAD;
struct RedSeINFO;
struct RedTrackDATA;
struct RedWaveHeadWD;

enum RedReverbModeLayout {
	REDSOUND_REVERB_MODE_PARAM_COUNT = 6,
};

enum RedReverbParamIndex {
	REDSOUND_REVERB_PARAM_PRE_DELAY = 0,
	REDSOUND_REVERB_PARAM_TIME = 1,
	REDSOUND_REVERB_PARAM_COLORATION = 2,
	REDSOUND_REVERB_PARAM_DAMPING = 3,
	REDSOUND_REVERB_PARAM_MIX = 4,
	REDSOUND_REVERB_PARAM_CROSSTALK = 5,
	REDSOUND_REVERB_PARAM_DELAY = 0,
	REDSOUND_REVERB_PARAM_FEEDBACK = 1,
	REDSOUND_REVERB_PARAM_OUTPUT = 2,
	REDSOUND_REVERB_PARAM_CHORUS_BASE_DELAY = 0,
	REDSOUND_REVERB_PARAM_CHORUS_VARIATION = 1,
	REDSOUND_REVERB_PARAM_CHORUS_PERIOD = 2,
};

struct RedReverbModeData {
	int m_kind;
	int m_params[REDSOUND_REVERB_MODE_PARAM_COUNT];
};

RedTrackDATA* SearchSeEmptyTrack(int, int, int);
int SeStopID(int);
int SeStopMG(int, int, int, int);
int SeBlockPlay(int, int, int, int, int);
int SeSepPlay(int, int, int, int);
void SetSeVolume(int, int, int, int);
void SetSePan(int, int, int);
void SetSePitch(int, int, int);
void SePause(int, int);
int MusicStop(int);
int MusicPlay(int, int, int);
void SetMusicVolume(int, int, int, int);

extern RedReverbModeData t_ReverbModeData[];

#endif // _FFCC_REDSOUND_REDCOMMAND_H
