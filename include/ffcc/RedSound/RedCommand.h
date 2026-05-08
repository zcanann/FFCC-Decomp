#ifndef _FFCC_REDSOUND_REDCOMMAND_H
#define _FFCC_REDSOUND_REDCOMMAND_H

struct RedMusicHEAD;
struct RedSeINFO;
struct RedTrackDATA;
struct RedWaveHeadWD;

enum RedReverbModeLayout {
	REDSOUND_REVERB_MODE_PARAM_COUNT = 6,
	REDSOUND_REVERB_MODE_COUNT = 8,
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

RedTrackDATA* SearchSeEmptyTrack(int trackCount, int eraseTrack, int attrMask);
int SeStopID(int seId);
int SeStopMG(int bank, int sep, int group, int kind);
int SeBlockPlay(int seId, int bank, int no, int pan, int volume);
int SeSepPlay(int seId, int sepId, int pan, int volume);
void SetSeVolume(int seId, int volume, int frameCount, int mode);
void SetSePan(int seId, int pan, int frameCount);
void SetSePitch(int seId, int pitch, int frameCount);
void SePause(int seId, int pause);
int MusicStop(int musicId);
int MusicPlay(int musicId, int volume, int mode);
void SetMusicVolume(int musicId, int volume, int frameCount, int mode);

extern RedReverbModeData t_ReverbModeData[REDSOUND_REVERB_MODE_COUNT];

#endif // _FFCC_REDSOUND_REDCOMMAND_H
