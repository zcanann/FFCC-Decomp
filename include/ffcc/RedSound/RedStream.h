#ifndef _FFCC_REDSOUND_REDSTREAM_H
#define _FFCC_REDSOUND_REDSTREAM_H

#include "ffcc/RedSound/RedExecute.h"
#include "types.h"

struct RedTrackDATA;
struct RedVoiceDATA;

struct RedStreamHEAD {
    u8 m_unk00[0x0C];
    int m_loopEnd;
    int m_loopStart;
    int m_pitch;
    s16 m_unk18;
    s16 m_channelCount;
    s16 m_flags;
    s16 m_unk1E;
};

struct RedStreamDATA {
    RedTrackDATA* m_track;
    RedVoiceDATA* m_voiceData;
    u8* m_fileData;
    u8* m_buffer;
    RedStreamHEAD m_header;
    RedWaveDATA m_trackData[2];
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
