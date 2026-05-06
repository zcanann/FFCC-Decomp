#ifndef _FFCC_REDSOUND_REDSTREAM_H
#define _FFCC_REDSOUND_REDSTREAM_H

#include "ffcc/RedSound/RedExecute.h"
#include "types.h"

struct RedTrackDATA;
struct RedVoiceDATA;

enum RedStreamFileLayoutSize {
    REDSOUND_STREAM_SIGNATURE_SIZE = 4,
    REDSOUND_STREAM_HEADER_PAD_SIZE = 0x0C - 0x04,
    REDSOUND_STREAM_TRACK_DATA_COUNT = 2,
};

struct RedStreamHEAD {
    char m_signature[REDSOUND_STREAM_SIGNATURE_SIZE];
    u8 m_reserved04[REDSOUND_STREAM_HEADER_PAD_SIZE];
    int m_loopEnd;
    int m_loopStart;
    int m_pitch;
    s16 m_reserved18;
    s16 m_channelCount;
    s16 m_flags;
    s16 m_reserved1E;
};

enum RedStreamState {
    REDSOUND_STREAM_STATE_STOPPED = 0,
    REDSOUND_STREAM_STATE_PLAYING = 1,
    REDSOUND_STREAM_STATE_LOADING = 3,
};

enum RedStreamHeaderFlag {
    REDSOUND_STREAM_HEADER_REVERB_NONE = 0,
};

struct RedStreamDATA {
    RedTrackDATA* m_track;
    RedVoiceDATA* m_voiceData;
    u8* m_fileData;
    u8* m_buffer;
    RedStreamHEAD m_header;
    RedWaveDATA m_trackData[REDSOUND_STREAM_TRACK_DATA_COUNT];
    int m_volume;
    int m_volumeStep;
    int m_volumeStepCount;
    int m_reservedFC;
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

void StreamStop(int);
int StreamPlay(int, void*, int, int, int);
void SetStreamVolume(int, int, int);
void StreamPause(int, int);
void StreamControl();

#endif // _FFCC_REDSOUND_REDSTREAM_H
