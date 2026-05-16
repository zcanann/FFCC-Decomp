#ifndef _FFCC_REDSOUND_REDSTREAM_H
#define _FFCC_REDSOUND_REDSTREAM_H

#include "ffcc/RedSound/RedExecute.h"
#include "types.h"

struct RedTrackDATA;
struct RedVoiceDATA;

enum RedStreamFileLayoutSize {
    REDSOUND_STREAM_SIGNATURE_SIZE = 4,
    REDSOUND_STREAM_PAGE_SIZE = 0x1000,
    REDSOUND_STREAM_TRACK_DATA_COUNT = 2,
    REDSOUND_STREAM_STEREO_CHANNEL_COUNT = 2,
    REDSOUND_STREAM_STEREO_PLANE_PAGE_COUNT = 2,
    REDSOUND_STREAM_STEREO_PLANE_SIZE = REDSOUND_STREAM_PAGE_SIZE * REDSOUND_STREAM_STEREO_PLANE_PAGE_COUNT,
    REDSOUND_STREAM_TRANSFER_BUFFER_SIZE = REDSOUND_STREAM_STEREO_PLANE_SIZE * REDSOUND_STREAM_STEREO_CHANNEL_COUNT,
    REDSOUND_STREAM_TRANSFER_BUFFER_ALLOC_SIZE = REDSOUND_STREAM_TRANSFER_BUFFER_SIZE,
};

enum RedStreamSignature {
    REDSOUND_STREAM_SIGNATURE_0 = 'S',
    REDSOUND_STREAM_SIGNATURE_1 = 'T',
    REDSOUND_STREAM_SIGNATURE_2 = 'R',
};

enum RedStreamSignatureIndex {
    REDSOUND_STREAM_SIGNATURE_0_INDEX = 0,
    REDSOUND_STREAM_SIGNATURE_1_INDEX = 1,
    REDSOUND_STREAM_SIGNATURE_2_INDEX = 2,
};

enum RedStreamHeadLayoutSize {
    REDSOUND_STREAM_HEAD_RESERVED04_SIZE = 0x08,
    REDSOUND_STREAM_HEAD_RESERVED18_SIZE = sizeof(s16),
    REDSOUND_STREAM_HEAD_RESERVED1E_SIZE = sizeof(s16),
};

struct RedStreamHEAD {
    char m_signature[REDSOUND_STREAM_SIGNATURE_SIZE];
    u8 m_reserved04[REDSOUND_STREAM_HEAD_RESERVED04_SIZE];
    int m_loopEnd;
    int m_loopStart;
    int m_pitch;
    s16 m_reserved18;
    s16 m_channelCount;
    s16 m_flags;
    s16 m_reserved1E;
};

enum RedStreamHeadLayoutOffset {
    REDSOUND_STREAM_HEAD_SIGNATURE_OFFSET = (unsigned int)&(((RedStreamHEAD*)0)->m_signature),
    REDSOUND_STREAM_HEAD_RESERVED04_OFFSET = (unsigned int)&(((RedStreamHEAD*)0)->m_reserved04),
    REDSOUND_STREAM_HEAD_LOOP_END_OFFSET = (unsigned int)&(((RedStreamHEAD*)0)->m_loopEnd),
    REDSOUND_STREAM_HEAD_LOOP_START_OFFSET = (unsigned int)&(((RedStreamHEAD*)0)->m_loopStart),
    REDSOUND_STREAM_HEAD_PITCH_OFFSET = (unsigned int)&(((RedStreamHEAD*)0)->m_pitch),
    REDSOUND_STREAM_HEAD_RESERVED18_OFFSET = (unsigned int)&(((RedStreamHEAD*)0)->m_reserved18),
    REDSOUND_STREAM_HEAD_CHANNEL_COUNT_OFFSET = (unsigned int)&(((RedStreamHEAD*)0)->m_channelCount),
    REDSOUND_STREAM_HEAD_FLAGS_OFFSET = (unsigned int)&(((RedStreamHEAD*)0)->m_flags),
    REDSOUND_STREAM_HEAD_RESERVED1E_OFFSET = (unsigned int)&(((RedStreamHEAD*)0)->m_reserved1E),
    REDSOUND_STREAM_HEAD_SIZE = sizeof(RedStreamHEAD),
};

struct RedStreamADPCMHeader {
    AXPBADPCM m_data;
    AXPBADPCMLOOP m_loop;
};

enum RedStreamAdpcmHeaderLayoutOffset {
    REDSOUND_STREAM_ADPCM_DATA_OFFSET = (unsigned int)&(((RedStreamADPCMHeader*)0)->m_data),
    REDSOUND_STREAM_ADPCM_LOOP_OFFSET = (unsigned int)&(((RedStreamADPCMHeader*)0)->m_loop),
    REDSOUND_STREAM_ADPCM_HEADER_SIZE = sizeof(RedStreamADPCMHeader),
    REDSOUND_STREAM_ADPCM_DATA_SIZE = REDSOUND_STREAM_ADPCM_LOOP_OFFSET - REDSOUND_STREAM_ADPCM_DATA_OFFSET,
    REDSOUND_STREAM_ADPCM_LOOP_SIZE = REDSOUND_STREAM_ADPCM_HEADER_SIZE - REDSOUND_STREAM_ADPCM_LOOP_OFFSET,
};

enum RedStreamFilePayloadLayout {
    REDSOUND_STREAM_FILE_ADPCM_COUNT = REDSOUND_STREAM_TRACK_DATA_COUNT,
    REDSOUND_STREAM_FILE_AUDIO_OFFSET = REDSOUND_STREAM_PAGE_SIZE,
    REDSOUND_STREAM_FILE_TRAILING_PAD_SIZE =
        REDSOUND_STREAM_FILE_AUDIO_OFFSET -
        (REDSOUND_STREAM_HEAD_SIZE + REDSOUND_STREAM_ADPCM_HEADER_SIZE * REDSOUND_STREAM_FILE_ADPCM_COUNT),
    REDSOUND_STREAM_FILE_SIZE = REDSOUND_STREAM_FILE_AUDIO_OFFSET,
};

struct RedStreamFile {
    RedStreamHEAD m_header;
    RedStreamADPCMHeader m_adpcm[REDSOUND_STREAM_FILE_ADPCM_COUNT];
    u8 m_trailingPadding[REDSOUND_STREAM_FILE_TRAILING_PAD_SIZE];
};

#define RedStreamFileGetSampleByte(streamFile, offset) ((s8*)(streamFile))[(offset)]

#define RedStreamBufferGetPage(buffer, pageIndex) ((buffer) + (pageIndex) * REDSOUND_STREAM_PAGE_SIZE)

#define RedStreamBufferGetRightPlane(buffer) ((buffer) + REDSOUND_STREAM_STEREO_PLANE_SIZE)

#define RedStreamAramGetPage(buffer, pageIndex) ((buffer) + (pageIndex) * REDSOUND_STREAM_PAGE_SIZE)

#define RedStreamAramGetRightPlane(buffer) ((buffer) + REDSOUND_STREAM_STEREO_PLANE_SIZE)

#define RedStreamAramGetChannelPlane(buffer, channel) ((buffer) + (channel) * REDSOUND_STREAM_STEREO_PLANE_SIZE)

#define RedStreamGetReadCursor(stream) ((stream)->m_fileData + (stream)->m_readOffset)

enum RedStreamFileLayoutOffset {
    REDSOUND_STREAM_FILE_HEAD_OFFSET = (unsigned int)&(((RedStreamFile*)0)->m_header),
    REDSOUND_STREAM_FILE_ADPCM_OFFSET = (unsigned int)&(((RedStreamFile*)0)->m_adpcm),
    REDSOUND_STREAM_FILE_ADPCM_END =
        REDSOUND_STREAM_FILE_ADPCM_OFFSET + REDSOUND_STREAM_ADPCM_HEADER_SIZE * REDSOUND_STREAM_FILE_ADPCM_COUNT,
    REDSOUND_STREAM_FILE_TRAILING_PAD_OFFSET = (unsigned int)&(((RedStreamFile*)0)->m_trailingPadding),
};

enum RedStreamChannelIndex {
    REDSOUND_STREAM_LEFT_CHANNEL = 0,
    REDSOUND_STREAM_RIGHT_CHANNEL = 1,
};

enum RedStreamFrameWordIndex {
    REDSOUND_STREAM_FRAME_WORD_0 = 0,
    REDSOUND_STREAM_FRAME_WORD_1 = 1,
    REDSOUND_STREAM_STEREO_FRAME_WORD_COUNT = 2,
};

struct RedStreamStereoFrame {
    unsigned int m_left[REDSOUND_STREAM_STEREO_FRAME_WORD_COUNT];
    unsigned int m_right[REDSOUND_STREAM_STEREO_FRAME_WORD_COUNT];
};

struct RedStreamChannelFrame {
    unsigned int m_word[REDSOUND_STREAM_STEREO_FRAME_WORD_COUNT];
};

enum RedStreamFrameLayoutSize {
    REDSOUND_STREAM_STEREO_LEFT_FRAME_OFFSET = (unsigned int)&(((RedStreamStereoFrame*)0)->m_left),
    REDSOUND_STREAM_STEREO_RIGHT_FRAME_OFFSET = (unsigned int)&(((RedStreamStereoFrame*)0)->m_right),
    REDSOUND_STREAM_STEREO_FRAME_WORD_BYTES = sizeof(unsigned int),
    REDSOUND_STREAM_STEREO_CHANNEL_FRAME_BYTES = sizeof(RedStreamChannelFrame),
    REDSOUND_STREAM_STEREO_FRAME_SIZE = sizeof(RedStreamStereoFrame),
    REDSOUND_STREAM_STEREO_FRAMES_PER_PAGE = REDSOUND_STREAM_PAGE_SIZE / REDSOUND_STREAM_STEREO_FRAME_SIZE,
    REDSOUND_STREAM_AX_CURRENT_ADDRESS_HI_SHIFT = 16,
    REDSOUND_STREAM_LOOP_START_SAMPLE = 2,
    REDSOUND_STREAM_LOOP_ENABLED_MIN = 0,
    REDSOUND_STREAM_ADSR_RELEASE_TIME = 10,
};

struct RedStreamStepData {
    int m_value;
    int m_step;
    int m_stepCount;
};

enum RedStreamStepDataLayoutOffset {
    REDSOUND_STREAM_STEP_VALUE_OFFSET = (unsigned int)&(((RedStreamStepData*)0)->m_value),
    REDSOUND_STREAM_STEP_STEP_OFFSET = (unsigned int)&(((RedStreamStepData*)0)->m_step),
    REDSOUND_STREAM_STEP_COUNT_OFFSET = (unsigned int)&(((RedStreamStepData*)0)->m_stepCount),
};

enum RedStreamStepDataLayoutSize {
    REDSOUND_STREAM_STEP_DATA_SIZE = sizeof(RedStreamStepData),
};

enum RedStreamState {
    REDSOUND_STREAM_STATE_STOPPED = 0,
    REDSOUND_STREAM_STATE_PLAYING = 1,
    REDSOUND_STREAM_STATE_LOADING = 3,
};

enum RedStreamId {
    REDSOUND_STREAM_ID_NONE = 0,
    REDSOUND_STREAM_ID_ALL = -1,
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
    RedStreamStepData m_volume;
    int m_reservedFC;
    RedStreamStepData m_pan;
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

#define REDSOUND_STREAM_DATA_NONE 0
#define REDSOUND_STREAM_TRACK_NONE 0
#define REDSOUND_STREAM_BUFFER_NONE 0
#define REDSOUND_STREAM_ARAM_BUFFER_NONE 0

#define RedStreamGetTrack(stream, channel) ((stream)->m_track + (channel))
#define RedStreamGetVoiceData(stream, channel) ((stream)->m_voiceData + (channel))
#define RedStreamGetTrackData(stream, channel) (&(stream)->m_trackData[(channel)])
#define RedStreamVoiceDataGetChannel(voiceData, channel) ((voiceData) + (channel))

enum RedStreamDataLayoutOffset {
    REDSOUND_STREAM_TRACK_OFFSET = (unsigned int)&(((RedStreamDATA*)0)->m_track),
    REDSOUND_STREAM_VOICE_DATA_OFFSET = (unsigned int)&(((RedStreamDATA*)0)->m_voiceData),
    REDSOUND_STREAM_FILE_DATA_OFFSET = (unsigned int)&(((RedStreamDATA*)0)->m_fileData),
    REDSOUND_STREAM_BUFFER_OFFSET = (unsigned int)&(((RedStreamDATA*)0)->m_buffer),
    REDSOUND_STREAM_HEADER_OFFSET = (unsigned int)&(((RedStreamDATA*)0)->m_header),
    REDSOUND_STREAM_TRACK_DATA_OFFSET = (unsigned int)&(((RedStreamDATA*)0)->m_trackData),
    REDSOUND_STREAM_VOLUME_OFFSET = (unsigned int)&(((RedStreamDATA*)0)->m_volume.m_value),
    REDSOUND_STREAM_VOLUME_STEP_OFFSET = (unsigned int)&(((RedStreamDATA*)0)->m_volume.m_step),
    REDSOUND_STREAM_VOLUME_STEP_COUNT_OFFSET = (unsigned int)&(((RedStreamDATA*)0)->m_volume.m_stepCount),
    REDSOUND_STREAM_RESERVED_FC_OFFSET = (unsigned int)&(((RedStreamDATA*)0)->m_reservedFC),
    REDSOUND_STREAM_PAN_OFFSET = (unsigned int)&(((RedStreamDATA*)0)->m_pan.m_value),
    REDSOUND_STREAM_PAN_STEP_OFFSET = (unsigned int)&(((RedStreamDATA*)0)->m_pan.m_step),
    REDSOUND_STREAM_PAN_STEP_COUNT_OFFSET = (unsigned int)&(((RedStreamDATA*)0)->m_pan.m_stepCount),
    REDSOUND_STREAM_ID_OFFSET = (unsigned int)&(((RedStreamDATA*)0)->m_streamId),
    REDSOUND_STREAM_STATE_OFFSET = (unsigned int)&(((RedStreamDATA*)0)->m_state),
    REDSOUND_STREAM_DMA_ID_OFFSET = (unsigned int)&(((RedStreamDATA*)0)->m_dmaId),
    REDSOUND_STREAM_FILE_SIZE_OFFSET = (unsigned int)&(((RedStreamDATA*)0)->m_fileSize),
    REDSOUND_STREAM_FILE_CURSOR_OFFSET = (unsigned int)&(((RedStreamDATA*)0)->m_fileCursor),
    REDSOUND_STREAM_READ_OFFSET = (unsigned int)&(((RedStreamDATA*)0)->m_readOffset),
    REDSOUND_STREAM_CURSOR_OFFSET = (unsigned int)&(((RedStreamDATA*)0)->m_streamCursor),
    REDSOUND_STREAM_CURSOR_BASE_OFFSET = (unsigned int)&(((RedStreamDATA*)0)->m_streamCursorBase),
    REDSOUND_STREAM_ARAM_BUFFER_OFFSET = (unsigned int)&(((RedStreamDATA*)0)->m_aramBuffer),
};

enum RedStreamDataLayoutSize {
    REDSOUND_STREAM_RESERVED_FC_SIZE = REDSOUND_STREAM_PAN_OFFSET - REDSOUND_STREAM_RESERVED_FC_OFFSET,
    REDSOUND_STREAM_DATA_SIZE = sizeof(RedStreamDATA),
};

void StreamStop(int streamId);
int StreamPlay(int streamId, void* streamHeader, int fileSize, int pan, int volume);
void SetStreamVolume(int streamId, int volume, int frameCount);
void SetStreamPan(int streamId, int pan, int frameCount);
void StreamPause(int streamId, int pause);
void StreamControl();

#endif // _FFCC_REDSOUND_REDSTREAM_H
