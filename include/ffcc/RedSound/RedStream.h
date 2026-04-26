#ifndef _FFCC_REDSOUND_REDSTREAM_H
#define _FFCC_REDSOUND_REDSTREAM_H

#include "types.h"

struct RedStreamDATA {
    int m_track;
    int m_voiceData;
    int m_fileData;
    void* m_buffer;
    u8 m_header[0x0C];
    int m_loopEnd;
    int m_loopStart;
    int m_pitch;
    u8 m_pad28[0x2A - 0x28];
    s16 m_channelCount;
    u8 m_pad2C[0x30 - 0x2C];
    u8 m_trackData[2][0x60];
    int m_volume;
    int m_volumeStep;
    int m_volumeStepCount;
    int m_padFC;
    int m_pan;
    int m_panStep;
    int m_panStepCount;
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
