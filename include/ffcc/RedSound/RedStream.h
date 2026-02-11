#ifndef _FFCC_REDSOUND_REDSTREAM_H
#define _FFCC_REDSOUND_REDSTREAM_H

struct RedStreamDATA;

unsigned int _SearchEmptyStreamData();
void _StreamStop(RedStreamDATA*);
int _ArrangeStreamDataNoLoop(RedStreamDATA*, int, int);
int _ArrangeStreamDataLoop(RedStreamDATA*, int, int);

void StreamStop(int);
void StreamPlay(int, void*, int, int, int);
void SetStreamVolume(int, int, int);
void StreamPause(int, int);
void StreamControl();

#endif // _FFCC_REDSOUND_REDSTREAM_H
