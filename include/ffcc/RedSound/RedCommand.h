#ifndef _FFCC_REDSOUND_REDCOMMAND_H
#define _FFCC_REDSOUND_REDCOMMAND_H

struct RedMusicHEAD;
struct RedSeINFO;
struct RedTrackDATA;
struct RedWaveHeadWD;

struct RedReverbModeData {
	int kind;
	int params[6];
};

void _EraseAttribute(int, int);
int _EraseTime(int);
RedTrackDATA* SearchSeEmptyTrack(int, int, int);
int SeStopID(int);
int SeStopMG(int, int, int, int);
int _SePlayStart(RedSeINFO*, int, int, int, int);
int SeBlockPlay(int, int, int, int, int);
int SeSepPlay(int, int, int, int);
void SetSeVolume(int, int, int, int);
void SetSePan(int, int, int);
void SetSePitch(int, int, int);
void SePause(int, int);
void _MusicPlayStart(RedMusicHEAD*, RedWaveHeadWD*, int, int, int);
int MusicStop(int);
int MusicPlay(int, int, int);
void SetMusicVolume(int, int, int, int);

extern RedReverbModeData t_ReverbModeData[];

#endif // _FFCC_REDSOUND_REDCOMMAND_H
