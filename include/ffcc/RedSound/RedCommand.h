#ifndef _FFCC_REDSOUND_REDCOMMAND_H
#define _FFCC_REDSOUND_REDCOMMAND_H

struct RedMusicHEAD;
struct RedSeINFO;
struct RedWaveHeadWD;

void _EraseAttribute(int, int);
int _EraseTime(int);
void SearchSeEmptyTrack(int, int, int);
int SeStopID(int);
int SeStopMG(int, int, int, int);
int _SePlayStart(RedSeINFO*, int, int, int, int);
int SeBlockPlay(int, int, int, int, int);
void SeSepPlay(int, int, int, int);
void SetSeVolume(int, int, int, int);
void SetSePan(int, int, int);
void SetSePitch(int, int, int);
void SePause(int, int);
void _MusicPlayStart(RedMusicHEAD*, RedWaveHeadWD*, int, int, int);
void MusicStop(int);
void MusicPlay(int, int, int);
void SetMusicVolume(int, int, int, int);

#endif // _FFCC_REDSOUND_REDCOMMAND_H
