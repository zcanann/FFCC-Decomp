#ifndef _FFCC_REDSOUND_REDSTREAM_H
#define _FFCC_REDSOUND_REDSTREAM_H

struct RedStreamDATA;

void _SearchEmptyStreamData();
void _StreamStop(RedStreamDATA*);
void _ArrangeStreamDataNoLoop(RedStreamDATA*, int, int);
void _ArrangeStreamDataLoop(RedStreamDATA*, int, int);

void StreamStop(int);
void StreamPlay(int, void*, int, int, int);
void SetStreamVolume(int, int, int);
void StreamPause(int, int);
void StreamControl();

#endif // _FFCC_REDSOUND_REDSTREAM_H
