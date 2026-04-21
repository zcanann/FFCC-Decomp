#ifndef _FFCC_REDSOUND_REDSTREAM_H
#define _FFCC_REDSOUND_REDSTREAM_H

#include "types.h"

struct RedStreamDATA {
    int m_track;
    int m_voiceData;
    int m_fileData;
    void* m_buffer;
    u8 m_pad10[0x2A - 0x10];
    s16 m_channelCount;
    u8 m_pad2C[0xF0 - 0x2C];
    int m_volume;
    int m_volumeStep;
    int m_volumeStepCount;
    u8 m_padFC[0x10C - 0xFC];
    int m_streamId;
    int m_state;
    int m_dmaId;
    int m_fileSize;
    int m_fileCursor;
    int m_readOffset;
    int m_streamCursor;
    int m_streamCursorBase;
    int m_aramBuffer;
};

RedStreamDATA* _SearchEmptyStreamData();
void _StreamStop(RedStreamDATA*);
int _ArrangeStreamDataNoLoop(RedStreamDATA*, int, int);
int _ArrangeStreamDataLoop(RedStreamDATA*, int, int);

void StreamStop(int);
int StreamPlay(int, void*, int, int, int);
void SetStreamVolume(int, int, int);
void StreamPause(int, int);
void StreamControl();

#endif // _FFCC_REDSOUND_REDSTREAM_H
