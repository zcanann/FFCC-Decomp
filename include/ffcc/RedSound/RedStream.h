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

enum RedStreamSignature {
    REDSOUND_STREAM_SIGNATURE_0 = 'S',
    REDSOUND_STREAM_SIGNATURE_1 = 'T',
    REDSOUND_STREAM_SIGNATURE_2 = 'R',
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

enum RedStreamDataLayoutOffset {
    REDSOUND_STREAM_TRACK_OFFSET = 0x00,
    REDSOUND_STREAM_VOICE_DATA_OFFSET = 0x04,
    REDSOUND_STREAM_FILE_DATA_OFFSET = 0x08,
    REDSOUND_STREAM_BUFFER_OFFSET = 0x0C,
    REDSOUND_STREAM_HEADER_OFFSET = 0x10,
    REDSOUND_STREAM_TRACK_DATA_OFFSET = 0x30,
    REDSOUND_STREAM_VOLUME_OFFSET = 0xF0,
    REDSOUND_STREAM_PAN_OFFSET = 0x100,
    REDSOUND_STREAM_ID_OFFSET = 0x10C,
    REDSOUND_STREAM_STATE_OFFSET = 0x110,
    REDSOUND_STREAM_DMA_ID_OFFSET = 0x114,
    REDSOUND_STREAM_FILE_SIZE_OFFSET = 0x118,
    REDSOUND_STREAM_READ_OFFSET = 0x120,
    REDSOUND_STREAM_CURSOR_OFFSET = 0x124,
    REDSOUND_STREAM_CURSOR_BASE_OFFSET = 0x128,
    REDSOUND_STREAM_ARAM_BUFFER_OFFSET = 0x12C,
};

enum RedStreamDataLayoutSize {
    REDSOUND_STREAM_DATA_SIZE = 0x130,
};

void StreamStop(int);
int StreamPlay(int, void*, int, int, int);
void SetStreamVolume(int, int, int);
void StreamPause(int, int);
void StreamControl();

#endif // _FFCC_REDSOUND_REDSTREAM_H
