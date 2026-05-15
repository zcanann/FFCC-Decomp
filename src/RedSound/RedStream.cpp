#include "ffcc/RedSound/RedStream.h"
#include "ffcc/RedSound/RedCommand.h"
#include "ffcc/RedSound/RedDriver.h"
#include "ffcc/RedSound/RedEntry.h"
#include "ffcc/RedSound/RedExecute.h"
#include "ffcc/RedSound/RedMemory.h"
#include "ffcc/RedSound/RedMidiCtrl.h"
#include "ffcc/RedSound/RedGlobals.h"
#include "global.h"
#include <dolphin/os.h>
#include <string.h>

static const char sRedStreamBufferDidntSecureFmt[] = "%s%sStream Buffer didn't secure.%s\n";
static const char sRedStreamLogPrefix[] = "\x1B[7;34mSound\x1B[0m:";
static const char sRedStreamMainMemoryDidntCreateFmt[] = "%s%sM-Memory didn't create.(need:0x%6.6X)%s\n";
static const char sRedStreamAramMemoryDidntCreateFmt[] = "%s%sA-Memory didn't create.(need:0x%6.6X)%s\n";
static const char sRedStreamPauseOnFmt[] = "%sPause : Stream : ON  %d\n";
static const char sRedStreamPauseOffFmt[] = "%sPause : Stream : OFF %d\n";
static const char sRedStreamLogErrorColor[] = "\x1B[7;31m";
static const char sRedStreamLogReset[] = "\x1B[0m";
static const char sRedStreamLogWarnColor[] = "\x1B[4;31m";

enum RedStreamStringLayout {
	REDSOUND_STREAM_BUFFER_DIDNT_SECURE_FMT_SIZE = 0x24,
	REDSOUND_STREAM_LOG_PREFIX_SIZE = 0x12,
	REDSOUND_STREAM_MAIN_MEMORY_DIDNT_CREATE_FMT_SIZE = 0x2d,
	REDSOUND_STREAM_ARAM_MEMORY_DIDNT_CREATE_FMT_SIZE = 0x2d,
	REDSOUND_STREAM_PAUSE_ON_FMT_SIZE = 0x1b,
	REDSOUND_STREAM_PAUSE_OFF_FMT_SIZE = 0x1b,
	REDSOUND_STREAM_LOG_ERROR_COLOR_SIZE = 0x08,
	REDSOUND_STREAM_LOG_RESET_SIZE = 0x05,
	REDSOUND_STREAM_LOG_WARN_COLOR_SIZE = 0x08,
	REDSOUND_STREAM_RODATA_STRING_SIZE = 0xc6,
	REDSOUND_STREAM_SDATA2_STRING_SIZE = 0x15,
};

enum RedStreamLayoutSize {
	REDSOUND_STREAM_STEREO_PLANE_SIZE = 0x2000,
	REDSOUND_STREAM_STEREO_PLANE_PAGE_COUNT = REDSOUND_STREAM_STEREO_PLANE_SIZE / REDSOUND_STREAM_PAGE_SIZE,
	REDSOUND_STREAM_TRANSFER_BUFFER_SIZE = REDSOUND_STREAM_STEREO_PLANE_SIZE * 2,
	REDSOUND_STREAM_TRANSFER_BUFFER_ALLOC_SIZE = 0x4000,
	REDSOUND_STREAM_SAMPLE_ADVANCE = 0x200,
	REDSOUND_STREAM_FILE_HEADER_SIZE = sizeof(RedStreamHEAD),
	REDSOUND_STREAM_INITIAL_LOOP_END = 0x3fff,
	REDSOUND_STREAM_BASE_PITCH = 0x3c00000,
	REDSOUND_STREAM_ARAM_HIGH_THRESHOLD = 0x800000,
	REDSOUND_STREAM_ARAM_LOW_OFFSET = 0,
	REDSOUND_STREAM_ARAM_HIGH_OFFSET = 0x300000,
	REDSOUND_STREAM_ARAM_TO_AX_ADDRESS_SCALE = 2,
	REDSOUND_STREAM_ERASE_TRACK = 0xff,
	REDSOUND_STREAM_STEREO_CHANNEL_COUNT = 2,
	REDSOUND_STREAM_STEREO_FRAME_WORD_COUNT = 2,
	REDSOUND_STREAM_MIN_FRAME_COUNT = 1,
	REDSOUND_STREAM_SILENT_PAN = 0,
	REDSOUND_STREAM_BUFFER_SIDE_A = 0,
	REDSOUND_STREAM_BUFFER_SIDE_B = 1,
	REDSOUND_STREAM_BUFFER_SIDE_MASK = 1,
};

enum RedStreamChannelIndex {
	REDSOUND_STREAM_LEFT_CHANNEL = 0,
	REDSOUND_STREAM_RIGHT_CHANNEL = 1,
};

struct RedStreamStereoFrame {
	unsigned int m_left[REDSOUND_STREAM_STEREO_FRAME_WORD_COUNT];
	unsigned int m_right[REDSOUND_STREAM_STEREO_FRAME_WORD_COUNT];
};

struct RedStreamChannelFrame {
	unsigned int m_word[REDSOUND_STREAM_STEREO_FRAME_WORD_COUNT];
};

enum RedStreamFrameLayoutSize {
	REDSOUND_STREAM_STEREO_LEFT_FRAME_OFFSET = 0x00,
	REDSOUND_STREAM_STEREO_RIGHT_FRAME_OFFSET = sizeof(unsigned int) * REDSOUND_STREAM_STEREO_FRAME_WORD_COUNT,
	REDSOUND_STREAM_STEREO_FRAME_WORD_BYTES = sizeof(unsigned int),
	REDSOUND_STREAM_STEREO_CHANNEL_FRAME_BYTES = sizeof(unsigned int) * REDSOUND_STREAM_STEREO_FRAME_WORD_COUNT,
	REDSOUND_STREAM_STEREO_FRAME_SIZE = 0x10,
	REDSOUND_STREAM_STEREO_FRAMES_PER_PAGE = REDSOUND_STREAM_PAGE_SIZE / REDSOUND_STREAM_STEREO_FRAME_SIZE,
	REDSOUND_STREAM_LEFT_PRED_SCALE_OFFSET = REDSOUND_STREAM_PAGE_SIZE,
	REDSOUND_STREAM_LOOP_START_SAMPLE = 2,
	REDSOUND_STREAM_LOOP_ENABLED_MIN = 0,
	REDSOUND_STREAM_ADSR_RELEASE_TIME = 10,
};

STATIC_ASSERT(offsetof(RedStreamHEAD, m_signature) == REDSOUND_STREAM_HEAD_SIGNATURE_OFFSET);
STATIC_ASSERT(sizeof(((RedStreamHEAD*)0)->m_signature) == REDSOUND_STREAM_SIGNATURE_SIZE);
STATIC_ASSERT(offsetof(RedStreamHEAD, m_reserved04) == REDSOUND_STREAM_HEAD_RESERVED04_OFFSET);
STATIC_ASSERT(sizeof(((RedStreamHEAD*)0)->m_reserved04) == REDSOUND_STREAM_HEAD_RESERVED04_SIZE);
STATIC_ASSERT(offsetof(RedStreamHEAD, m_loopEnd) == REDSOUND_STREAM_HEAD_LOOP_END_OFFSET);
STATIC_ASSERT(offsetof(RedStreamHEAD, m_loopStart) == REDSOUND_STREAM_HEAD_LOOP_START_OFFSET);
STATIC_ASSERT(offsetof(RedStreamHEAD, m_pitch) == REDSOUND_STREAM_HEAD_PITCH_OFFSET);
STATIC_ASSERT(offsetof(RedStreamHEAD, m_reserved18) == REDSOUND_STREAM_HEAD_RESERVED18_OFFSET);
STATIC_ASSERT(sizeof(((RedStreamHEAD*)0)->m_reserved18) == REDSOUND_STREAM_HEAD_RESERVED18_SIZE);
STATIC_ASSERT(offsetof(RedStreamHEAD, m_reserved18) + REDSOUND_STREAM_HEAD_RESERVED18_SIZE ==
              REDSOUND_STREAM_HEAD_CHANNEL_COUNT_OFFSET);
STATIC_ASSERT(offsetof(RedStreamHEAD, m_channelCount) == REDSOUND_STREAM_HEAD_CHANNEL_COUNT_OFFSET);
STATIC_ASSERT(offsetof(RedStreamHEAD, m_flags) == REDSOUND_STREAM_HEAD_FLAGS_OFFSET);
STATIC_ASSERT(offsetof(RedStreamHEAD, m_reserved1E) == REDSOUND_STREAM_HEAD_RESERVED1E_OFFSET);
STATIC_ASSERT(sizeof(((RedStreamHEAD*)0)->m_reserved1E) == REDSOUND_STREAM_HEAD_RESERVED1E_SIZE);
STATIC_ASSERT(offsetof(RedStreamHEAD, m_reserved1E) + REDSOUND_STREAM_HEAD_RESERVED1E_SIZE ==
              REDSOUND_STREAM_HEAD_SIZE);
STATIC_ASSERT(sizeof(RedStreamHEAD) == REDSOUND_STREAM_HEAD_SIZE);
STATIC_ASSERT(offsetof(RedStreamADPCMHeader, m_data) == REDSOUND_STREAM_ADPCM_DATA_OFFSET);
STATIC_ASSERT(offsetof(RedStreamADPCMHeader, m_loop) == REDSOUND_STREAM_ADPCM_LOOP_OFFSET);
STATIC_ASSERT(sizeof(((RedStreamADPCMHeader*)0)->m_data) == REDSOUND_STREAM_ADPCM_DATA_SIZE);
STATIC_ASSERT(sizeof(((RedStreamADPCMHeader*)0)->m_loop) == REDSOUND_STREAM_ADPCM_LOOP_SIZE);
STATIC_ASSERT(sizeof(RedStreamADPCMHeader) == REDSOUND_STREAM_ADPCM_HEADER_SIZE);
STATIC_ASSERT(offsetof(RedStreamFile, m_header) == REDSOUND_STREAM_FILE_HEAD_OFFSET);
STATIC_ASSERT(offsetof(RedStreamFile, m_adpcm) == REDSOUND_STREAM_FILE_ADPCM_OFFSET);
STATIC_ASSERT(sizeof(((RedStreamFile*)0)->m_adpcm) ==
              REDSOUND_STREAM_ADPCM_HEADER_SIZE * REDSOUND_STREAM_FILE_ADPCM_COUNT);
STATIC_ASSERT(offsetof(RedStreamFile, m_adpcm) + sizeof(((RedStreamFile*)0)->m_adpcm) ==
              REDSOUND_STREAM_FILE_ADPCM_END);
STATIC_ASSERT(offsetof(RedStreamFile, m_trailingPadding) == REDSOUND_STREAM_FILE_TRAILING_PAD_OFFSET);
STATIC_ASSERT(sizeof(((RedStreamFile*)0)->m_trailingPadding) == REDSOUND_STREAM_FILE_TRAILING_PAD_SIZE);
STATIC_ASSERT(sizeof(RedStreamFile) == REDSOUND_STREAM_FILE_SIZE);
STATIC_ASSERT(offsetof(RedStreamStereoFrame, m_left) == REDSOUND_STREAM_STEREO_LEFT_FRAME_OFFSET);
STATIC_ASSERT(sizeof(((RedStreamStereoFrame*)0)->m_left) == REDSOUND_STREAM_STEREO_CHANNEL_FRAME_BYTES);
STATIC_ASSERT(offsetof(RedStreamStereoFrame, m_right) == REDSOUND_STREAM_STEREO_RIGHT_FRAME_OFFSET);
STATIC_ASSERT(sizeof(((RedStreamStereoFrame*)0)->m_right) == REDSOUND_STREAM_STEREO_CHANNEL_FRAME_BYTES);
STATIC_ASSERT(sizeof(RedStreamStereoFrame) == REDSOUND_STREAM_STEREO_FRAME_SIZE);
STATIC_ASSERT(sizeof(((RedStreamChannelFrame*)0)->m_word) == REDSOUND_STREAM_STEREO_CHANNEL_FRAME_BYTES);
STATIC_ASSERT(sizeof(RedStreamChannelFrame) == REDSOUND_STREAM_STEREO_CHANNEL_FRAME_BYTES);
STATIC_ASSERT(REDSOUND_STREAM_STEREO_FRAMES_PER_PAGE * REDSOUND_STREAM_STEREO_FRAME_SIZE ==
              REDSOUND_STREAM_PAGE_SIZE);
STATIC_ASSERT(REDSOUND_STREAM_STEREO_PLANE_SIZE * REDSOUND_STREAM_STEREO_CHANNEL_COUNT ==
              REDSOUND_STREAM_TRANSFER_BUFFER_SIZE);
STATIC_ASSERT(REDSOUND_STREAM_TRANSFER_BUFFER_SIZE == REDSOUND_STREAM_TRANSFER_BUFFER_ALLOC_SIZE);
STATIC_ASSERT(offsetof(RedStreamStepData, m_value) == REDSOUND_STREAM_STEP_VALUE_OFFSET);
STATIC_ASSERT(offsetof(RedStreamStepData, m_step) == REDSOUND_STREAM_STEP_STEP_OFFSET);
STATIC_ASSERT(offsetof(RedStreamStepData, m_stepCount) == REDSOUND_STREAM_STEP_COUNT_OFFSET);
STATIC_ASSERT(sizeof(RedStreamStepData) == REDSOUND_STREAM_STEP_DATA_SIZE);
STATIC_ASSERT(offsetof(RedStreamDATA, m_track) == REDSOUND_STREAM_TRACK_OFFSET);
STATIC_ASSERT(offsetof(RedStreamDATA, m_voiceData) == REDSOUND_STREAM_VOICE_DATA_OFFSET);
STATIC_ASSERT(offsetof(RedStreamDATA, m_fileData) == REDSOUND_STREAM_FILE_DATA_OFFSET);
STATIC_ASSERT(offsetof(RedStreamDATA, m_buffer) == REDSOUND_STREAM_BUFFER_OFFSET);
STATIC_ASSERT(offsetof(RedStreamDATA, m_header) == REDSOUND_STREAM_HEADER_OFFSET);
STATIC_ASSERT(offsetof(RedStreamDATA, m_trackData) == REDSOUND_STREAM_TRACK_DATA_OFFSET);
STATIC_ASSERT(offsetof(RedStreamDATA, m_volume.m_value) == REDSOUND_STREAM_VOLUME_OFFSET);
STATIC_ASSERT(offsetof(RedStreamDATA, m_volume.m_step) == REDSOUND_STREAM_VOLUME_STEP_OFFSET);
STATIC_ASSERT(offsetof(RedStreamDATA, m_volume.m_stepCount) == REDSOUND_STREAM_VOLUME_STEP_COUNT_OFFSET);
STATIC_ASSERT(offsetof(RedStreamDATA, m_reservedFC) == REDSOUND_STREAM_RESERVED_FC_OFFSET);
STATIC_ASSERT(sizeof(((RedStreamDATA*)0)->m_reservedFC) == REDSOUND_STREAM_RESERVED_FC_SIZE);
STATIC_ASSERT(offsetof(RedStreamDATA, m_pan.m_value) == REDSOUND_STREAM_PAN_OFFSET);
STATIC_ASSERT(offsetof(RedStreamDATA, m_pan.m_step) == REDSOUND_STREAM_PAN_STEP_OFFSET);
STATIC_ASSERT(offsetof(RedStreamDATA, m_pan.m_stepCount) == REDSOUND_STREAM_PAN_STEP_COUNT_OFFSET);
STATIC_ASSERT(offsetof(RedStreamDATA, m_streamId) == REDSOUND_STREAM_ID_OFFSET);
STATIC_ASSERT(offsetof(RedStreamDATA, m_state) == REDSOUND_STREAM_STATE_OFFSET);
STATIC_ASSERT(offsetof(RedStreamDATA, m_dmaId) == REDSOUND_STREAM_DMA_ID_OFFSET);
STATIC_ASSERT(offsetof(RedStreamDATA, m_fileSize) == REDSOUND_STREAM_FILE_SIZE_OFFSET);
STATIC_ASSERT(offsetof(RedStreamDATA, m_fileCursor) == REDSOUND_STREAM_FILE_CURSOR_OFFSET);
STATIC_ASSERT(offsetof(RedStreamDATA, m_readOffset) == REDSOUND_STREAM_READ_OFFSET);
STATIC_ASSERT(offsetof(RedStreamDATA, m_streamCursor) == REDSOUND_STREAM_CURSOR_OFFSET);
STATIC_ASSERT(offsetof(RedStreamDATA, m_streamCursorBase) == REDSOUND_STREAM_CURSOR_BASE_OFFSET);
STATIC_ASSERT(offsetof(RedStreamDATA, m_aramBuffer) == REDSOUND_STREAM_ARAM_BUFFER_OFFSET);
STATIC_ASSERT(sizeof(RedStreamDATA) == REDSOUND_STREAM_DATA_SIZE);
STATIC_ASSERT(sizeof(sRedStreamBufferDidntSecureFmt) == REDSOUND_STREAM_BUFFER_DIDNT_SECURE_FMT_SIZE);
STATIC_ASSERT(sizeof(sRedStreamLogPrefix) == REDSOUND_STREAM_LOG_PREFIX_SIZE);
STATIC_ASSERT(sizeof(sRedStreamMainMemoryDidntCreateFmt) == REDSOUND_STREAM_MAIN_MEMORY_DIDNT_CREATE_FMT_SIZE);
STATIC_ASSERT(sizeof(sRedStreamAramMemoryDidntCreateFmt) == REDSOUND_STREAM_ARAM_MEMORY_DIDNT_CREATE_FMT_SIZE);
STATIC_ASSERT(sizeof(sRedStreamPauseOnFmt) == REDSOUND_STREAM_PAUSE_ON_FMT_SIZE);
STATIC_ASSERT(sizeof(sRedStreamPauseOffFmt) == REDSOUND_STREAM_PAUSE_OFF_FMT_SIZE);
STATIC_ASSERT(sizeof(sRedStreamLogErrorColor) == REDSOUND_STREAM_LOG_ERROR_COLOR_SIZE);
STATIC_ASSERT(sizeof(sRedStreamLogReset) == REDSOUND_STREAM_LOG_RESET_SIZE);
STATIC_ASSERT(sizeof(sRedStreamLogWarnColor) == REDSOUND_STREAM_LOG_WARN_COLOR_SIZE);
STATIC_ASSERT(sizeof(sRedStreamBufferDidntSecureFmt) + sizeof(sRedStreamLogPrefix) +
                  sizeof(sRedStreamMainMemoryDidntCreateFmt) + sizeof(sRedStreamAramMemoryDidntCreateFmt) +
                  sizeof(sRedStreamPauseOnFmt) + sizeof(sRedStreamPauseOffFmt) ==
              REDSOUND_STREAM_RODATA_STRING_SIZE);
STATIC_ASSERT(sizeof(sRedStreamLogErrorColor) + sizeof(sRedStreamLogReset) + sizeof(sRedStreamLogWarnColor) ==
              REDSOUND_STREAM_SDATA2_STRING_SIZE);

static RedStreamDATA* _SearchEmptyStreamData();
static void _StreamStop(RedStreamDATA* streamData);
static int _ArrangeStreamDataNoLoop(RedStreamDATA* stream, int bufferIndex, int byteCount);
static int _ArrangeStreamDataLoop(RedStreamDATA* stream, int bufferIndex, int byteCount);

/*
 * --INFO--
 * PAL Address: 0x801cbfc4
 * PAL Size: 112b
 * EN Address: 0x8020dee8
 * EN Size: 112b
 * JP Address: TODO
 * JP Size: TODO
 */
void StreamStop(int streamID)
{
	volatile RedStreamDATA* streamData = p_Stream;

	do {
		if ((streamData->m_streamId != REDSOUND_STREAM_ID_NONE) &&
		    ((streamID == REDSOUND_STREAM_ID_ALL) || (streamID == streamData->m_streamId))) {
			_StreamStop((RedStreamDATA*)streamData);
		}
		streamData++;
	} while (streamData < p_Stream + REDSOUND_STREAM_COUNT);
}
/*
 * --INFO--
 * PAL Address: 0x801cc034
 * PAL Size: 1280b
 * EN Address: 0x8020df58
 * EN Size: 1280b
 * JP Address: TODO
 * JP Size: TODO
 */
int StreamPlay(int streamID, void* streamHeader, int fileSize, int pan, int volume)
{
	int amemSize;
	int arOffset;
	int pitch;
	int channel;
	int sampleOffset;
	RedStreamFile* streamFile;
	RedStreamADPCMHeader* headerData;
	RedStreamDATA* streamData;
	RedVoiceDATA* voice;

	streamData = _SearchEmptyStreamData();
	if (streamData != 0) {

	memcpy(&streamData->m_header, streamHeader, REDSOUND_STREAM_FILE_HEADER_SIZE);
	streamData->m_track = SearchSeEmptyTrack(streamData->m_header.m_channelCount, REDSOUND_STREAM_ERASE_TRACK, 0);
	streamData->m_buffer = (u8*)RedNew(REDSOUND_STREAM_TRANSFER_BUFFER_SIZE);
	amemSize = streamData->m_header.m_channelCount * REDSOUND_STREAM_STEREO_PLANE_SIZE;
	if (c_RedMemory.GetABufferSize() < REDSOUND_STREAM_ARAM_HIGH_THRESHOLD) {
		arOffset = REDSOUND_STREAM_ARAM_LOW_OFFSET;
	} else {
		arOffset = REDSOUND_STREAM_ARAM_HIGH_OFFSET;
	}
	streamData->m_aramBuffer = RedNewA(amemSize, 0, arOffset);
	if (streamData->m_aramBuffer == 0) {
		c_RedEntry.WaveOldClear(0, arOffset);
		streamData->m_aramBuffer = RedNewA(amemSize, 0, arOffset);
	}

	if ((streamData->m_track != 0) && (streamData->m_buffer != 0) && (streamData->m_aramBuffer != 0)) {
		sampleOffset = REDSOUND_STREAM_LEFT_PRED_SCALE_OFFSET;
		streamFile = reinterpret_cast<RedStreamFile*>(streamHeader);
		headerData = streamFile->m_adpcm;
		headerData->m_data.pred_scale = (short)((s8*)streamFile)[sampleOffset];
		headerData->m_data.yn1 = headerData->m_data.yn2 = 0;
		if (streamData->m_header.m_channelCount == REDSOUND_STREAM_STEREO_CHANNEL_COUNT) {
			if (streamData->m_header.m_loopStart < REDSOUND_STREAM_LOOP_ENABLED_MIN) {
				sampleOffset += REDSOUND_STREAM_PAGE_SIZE;
			} else {
				sampleOffset += REDSOUND_STREAM_STEREO_RIGHT_FRAME_OFFSET;
			}
			headerData[REDSOUND_STREAM_RIGHT_CHANNEL].m_data.pred_scale = (short)((s8*)streamFile)[sampleOffset];
			headerData[REDSOUND_STREAM_RIGHT_CHANNEL].m_data.yn1 =
			    headerData[REDSOUND_STREAM_RIGHT_CHANNEL].m_data.yn2 = 0;
		}

		streamData->m_streamId = streamID;
		streamData->m_fileCursor = 0;
		streamData->m_readOffset = REDSOUND_STREAM_PAGE_SIZE;
		streamData->m_streamCursor = 0;
		streamData->m_voiceData = p_VoiceData + streamData->m_track->m_trackNo;
		streamData->m_fileData = (u8*)streamHeader;
		streamData->m_fileSize = fileSize;
		if (volume != 0) {
			volume = ((volume + 1) * REDSOUND_VOLUME_BYTE_SCALE - 1) * REDSOUND_FIXED_ONE;
		}
		streamData->m_volume.m_value = volume;
		streamData->m_volume.m_stepCount = 0;
		pitch = PitchCompute(REDSOUND_STREAM_BASE_PITCH, 0, streamData->m_header.m_pitch, 0);
		channel = 0;
		do {
			voice = streamData->m_voiceData + channel;
			voice->m_track = streamData->m_track + channel;
			voice->m_track->m_note.m_allocFlags |= REDSOUND_NOTE_ALLOC_STREAM;
			voice->m_stateFlags |= REDSOUND_VOICE_STATE_STREAM;
			voice->m_voiceSwitch = REDSOUND_VOICE_SWITCH_STREAM_DEFAULT;
			if (streamData->m_header.m_flags != REDSOUND_STREAM_HEADER_REVERB_NONE) {
				voice->m_voiceSwitch |= REDSOUND_VOICE_SWITCH_REVERB_STEREO;
			}
			voice->m_track->m_voiceSwitch = REDSOUND_VOICE_SWITCH_LOOP;
			voice->m_envelopeLevel = REDSOUND_ENVELOPE_LEVEL_FULL;
			voice->m_waveData = &streamData->m_trackData[channel];
			voice->m_targetPitch = pitch;
			voice->m_track->m_reverbDepth = p_ReverbDepth[REDSOUND_REVERB_DEPTH_SE].m_depth;
			voice->m_track->m_reverbDepthDelta = 0;
			if (streamData->m_header.m_channelCount == REDSOUND_STREAM_STEREO_CHANNEL_COUNT) {
				if (channel == REDSOUND_STREAM_LEFT_CHANNEL) {
					streamData->m_pan.m_value = REDSOUND_STREAM_SILENT_PAN;
					streamData->m_pan.m_stepCount = 0;
				} else {
					streamData->m_pan.m_value = REDSOUND_VOLUME_DEFAULT;
					streamData->m_pan.m_stepCount = 0;
				}
			} else {
				streamData->m_pan.m_value = pan << REDSOUND_FIXED_SHIFT;
				streamData->m_pan.m_stepCount = 0;
			}
			SetVoiceVolumeMix(streamData->m_voiceData + channel, streamData->m_pan.m_value >> REDSOUND_FIXED_SHIFT,
			                  streamData->m_volume.m_value >> REDSOUND_FIXED_SHIFT);
			(streamData->m_track + channel)->m_waveBase = streamData->m_aramBuffer + channel * REDSOUND_STREAM_STEREO_PLANE_SIZE;
			memset(&streamData->m_trackData[channel], 0, REDSOUND_WAVE_DATA_SIZE);
			memcpy(&streamData->m_trackData[channel].m_adpcm, &headerData[channel], REDSOUND_STREAM_ADPCM_HEADER_SIZE);
			voice->m_adsr.m_level[REDSOUND_VOICE_ADSR_ATTACK] = voice->m_adsr.m_level[REDSOUND_VOICE_ADSR_DECAY] =
			    voice->m_adsr.m_level[REDSOUND_VOICE_ADSR_SUSTAIN] = 0;
			voice->m_adsr.m_level[REDSOUND_VOICE_ADSR_RELEASE] = REDSOUND_VOLUME_MAX;
			voice->m_adsr.m_time[REDSOUND_VOICE_ADSR_ATTACK] = voice->m_adsr.m_time[REDSOUND_VOICE_ADSR_DECAY] =
			    voice->m_adsr.m_time[REDSOUND_VOICE_ADSR_SUSTAIN] = 0;
			voice->m_adsr.m_time[REDSOUND_VOICE_ADSR_RELEASE] = REDSOUND_STREAM_ADSR_RELEASE_TIME;
			streamData->m_trackData[channel].m_sampleStart = 0;
			streamData->m_trackData[channel].m_loopEnd = REDSOUND_STREAM_INITIAL_LOOP_END;
			streamData->m_trackData[channel].m_loopStart = REDSOUND_STREAM_LOOP_START_SAMPLE;
			channel += 1;
		} while (channel < streamData->m_header.m_channelCount);

		int dmaID;
		if (streamData->m_header.m_loopStart < REDSOUND_STREAM_LOOP_ENABLED_MIN) {
			dmaID = _ArrangeStreamDataNoLoop(streamData, REDSOUND_STREAM_BUFFER_SIDE_A, REDSOUND_STREAM_STEREO_PLANE_SIZE);
		} else {
			dmaID = _ArrangeStreamDataLoop(streamData, REDSOUND_STREAM_BUFFER_SIDE_A, REDSOUND_STREAM_STEREO_PLANE_SIZE);
		}
		streamData->m_dmaId = dmaID;
		streamData->m_streamCursorBase = REDSOUND_STREAM_PAGE_SIZE;
		streamData->m_state = REDSOUND_STREAM_STATE_LOADING;
	} else {
		if (m_ReportPrint != REDSOUND_REPORT_PRINT_OFF) {
			OSReport(sRedStreamBufferDidntSecureFmt, sRedStreamLogPrefix, sRedStreamLogErrorColor, sRedStreamLogReset);
			fflush(__files + 1);
		}
		if (streamData->m_buffer != 0) {
			RedDelete(streamData->m_buffer);
		} else {
			if (m_ReportPrint != REDSOUND_REPORT_PRINT_OFF) {
				OSReport(sRedStreamMainMemoryDidntCreateFmt,
				         sRedStreamLogPrefix, sRedStreamLogWarnColor, REDSOUND_STREAM_TRANSFER_BUFFER_SIZE,
				         sRedStreamLogReset);
				fflush(__files + 1);
			}
		}
		if (streamData->m_aramBuffer != 0) {
			RedDeleteA(streamData->m_aramBuffer);
		} else {
			if (m_ReportPrint != REDSOUND_REPORT_PRINT_OFF) {
				OSReport(sRedStreamAramMemoryDidntCreateFmt,
				         sRedStreamLogPrefix, sRedStreamLogWarnColor,
				         streamData->m_header.m_channelCount * REDSOUND_STREAM_STEREO_PLANE_SIZE,
				         sRedStreamLogReset);
				fflush(__files + 1);
			}
		}
	}
	}
	return streamID;
}
/*
 * --INFO--
 * PAL Address: 0x801cc534
 * PAL Size: 204b
 * EN Address: 0x8020e458
 * EN Size: 204b
 * JP Address: TODO
 * JP Size: TODO
 */
void SetStreamVolume(int streamID, int volume, int frameCount)
{
	volatile RedStreamDATA* streamData;

	if (frameCount < REDSOUND_STREAM_MIN_FRAME_COUNT) {
		frameCount = REDSOUND_STREAM_MIN_FRAME_COUNT;
	} else {
		frameCount *= REDSOUND_STREAM_FADE_TICKS_PER_SECOND;
		frameCount /= REDSOUND_FRAMES_PER_SECOND;
	}

	volume &= REDSOUND_VOLUME_MAX;
	if (volume != 0) {
		volume++;
		volume <<= 8;
		volume--;
		volume <<= REDSOUND_FIXED_SHIFT;
		volume |= REDSOUND_FIXED_HALF;
	}

	streamData = p_Stream;
	do {
		if ((streamData->m_streamId != REDSOUND_STREAM_ID_NONE) &&
		    ((streamID == REDSOUND_STREAM_ID_ALL) || (streamID == streamData->m_streamId))) {
			if (frameCount > 0) {
				int delta = volume - streamData->m_volume.m_value;
				streamData->m_volume.m_step = delta / frameCount;
				streamData->m_volume.m_stepCount = frameCount;
			} else {
				streamData->m_volume.m_value = volume;
				streamData->m_volume.m_stepCount = 0;
			}
		}
		streamData++;
	} while (streamData < p_Stream + REDSOUND_STREAM_COUNT);
}
/*
 * --INFO--
 * PAL Address: 0x801cc600
 * PAL Size: 392b
 * EN Address: 0x8020e524
 * EN Size: 392b
 * JP Address: TODO
 * JP Size: TODO
 */
void StreamPause(int streamID, int pause)
{
	RedVoiceDATA* voiceData;
	RedStreamDATA* streamData;
	int volume;
	int pan;

	if (m_ReportPrint != REDSOUND_REPORT_PRINT_OFF) {
		if (pause == REDSOUND_PAUSE_ON) {
			OSReport(sRedStreamPauseOnFmt, sRedStreamLogPrefix, streamID);
		} else {
			OSReport(sRedStreamPauseOffFmt, sRedStreamLogPrefix, streamID);
		}
		fflush(__files + 1);
	}
	streamData = p_Stream;
	do {
		if ((streamData->m_streamId != REDSOUND_STREAM_ID_NONE) &&
		    ((streamID == REDSOUND_STREAM_ID_ALL) || (streamID == streamData->m_streamId))) {
			voiceData = streamData->m_voiceData;
			if (pause == REDSOUND_PAUSE_ON) {
				if (voiceData->m_axVoice != 0) {
					voiceData->m_targetPitch = 0;
					voiceData->m_flags |= REDSOUND_VOICE_FLAGS_PITCH_DIRTY;
					if (streamData->m_header.m_channelCount == REDSOUND_STREAM_STEREO_CHANNEL_COUNT) {
						voiceData[REDSOUND_STREAM_RIGHT_CHANNEL].m_targetPitch = 0;
						voiceData[REDSOUND_STREAM_RIGHT_CHANNEL].m_flags |= REDSOUND_VOICE_FLAGS_PITCH_DIRTY;
					}
				}
			} else if (voiceData->m_axVoice != 0) {
				unsigned int pitch = PitchCompute(REDSOUND_STREAM_BASE_PITCH, 0, streamData->m_header.m_pitch, 0);
				volume = streamData->m_volume.m_value >> REDSOUND_FIXED_SHIFT;
				if (streamData->m_header.m_channelCount == REDSOUND_STREAM_STEREO_CHANNEL_COUNT) {
					voiceData->m_targetPitch = pitch;
					voiceData->m_flags |= REDSOUND_VOICE_FLAGS_PITCH_DIRTY;
					voiceData[REDSOUND_STREAM_RIGHT_CHANNEL].m_targetPitch = pitch;
					voiceData[REDSOUND_STREAM_RIGHT_CHANNEL].m_flags |= REDSOUND_VOICE_FLAGS_PITCH_DIRTY;
				} else {
					pan = streamData->m_pan.m_value >> REDSOUND_FIXED_SHIFT;
					voiceData->m_targetPitch = pitch;
					voiceData->m_flags |= REDSOUND_VOICE_FLAGS_PITCH_DIRTY;
				}
			}
		}
		streamData++;
	} while (streamData < p_Stream + REDSOUND_STREAM_COUNT);
}
/*
 * --INFO--
 * PAL Address: 0x801cc788
 * PAL Size: 684b
 * EN Address: 0x8020e6ac
 * EN Size: 684b
 * JP Address: TODO
 * JP Size: TODO
 */
void StreamControl()
{
	RedStreamDATA* streamData = p_Stream;
	do {
		RedVoiceDATA* voiceData;
		if (streamData->m_state == REDSOUND_STREAM_STATE_PLAYING) {
			voiceData = streamData->m_voiceData;
			if (voiceData->m_axVoice != 0) {
				if (voiceData->m_axVoice->priority == 0) {
					_StreamStop(streamData);
				} else {
					int samplePos = voiceData->m_axVoice->pb.addr.currentAddressHi;
					int sampleStart =
					    (streamData->m_aramBuffer + streamData->m_streamCursorBase) *
					    REDSOUND_STREAM_ARAM_TO_AX_ADDRESS_SCALE;
					samplePos <<= 16;
					samplePos |= voiceData->m_axVoice->pb.addr.currentAddressLo;
					if ((samplePos >= sampleStart) && (samplePos < sampleStart + REDSOUND_STREAM_STEREO_PLANE_SIZE)) {
						int stopped = 0;
						if (streamData->m_header.m_loopStart < REDSOUND_STREAM_LOOP_ENABLED_MIN) {
							streamData->m_header.m_loopEnd = streamData->m_header.m_loopEnd - REDSOUND_STREAM_SAMPLE_ADVANCE;
							if (streamData->m_header.m_loopEnd < 1) {
								_StreamStop(streamData);
								stopped = 1;
							}
						}
						streamData->m_fileCursor += streamData->m_header.m_channelCount * REDSOUND_STREAM_PAGE_SIZE;
						if (streamData->m_fileCursor >= streamData->m_fileSize) {
							streamData->m_fileCursor -= streamData->m_fileSize;
						}

						if (!stopped) {
							int side;
							int dmaID;
							if (streamData->m_streamCursorBase != 0) {
								side = REDSOUND_STREAM_BUFFER_SIDE_A;
								streamData->m_streamCursorBase = 0;
							} else {
								side = REDSOUND_STREAM_BUFFER_SIDE_B;
								streamData->m_streamCursorBase = REDSOUND_STREAM_PAGE_SIZE;
							}

							if (streamData->m_header.m_loopStart < REDSOUND_STREAM_LOOP_ENABLED_MIN) {
								dmaID = _ArrangeStreamDataNoLoop(streamData, side, REDSOUND_STREAM_PAGE_SIZE);
							} else {
								dmaID = _ArrangeStreamDataLoop(streamData, side, REDSOUND_STREAM_PAGE_SIZE);
							}
							streamData->m_dmaId = dmaID;
						}
					}

					int changed = 0;
					if (streamData->m_pan.m_stepCount != 0) {
						changed += 1;
						streamData->m_pan.m_stepCount -= 1;
						streamData->m_pan.m_value += streamData->m_pan.m_step;
					}
					if (streamData->m_volume.m_stepCount != 0) {
						changed += 1;
						streamData->m_volume.m_stepCount -= 1;
						streamData->m_volume.m_value += streamData->m_volume.m_step;
					}
					if (changed != 0) {
						if (streamData->m_header.m_channelCount == REDSOUND_STREAM_STEREO_CHANNEL_COUNT) {
							SetVoiceVolumeMix(voiceData, REDSOUND_STREAM_SILENT_PAN,
							                  streamData->m_volume.m_value >> REDSOUND_FIXED_SHIFT);
							voiceData += 1;
							SetVoiceVolumeMix(voiceData, REDSOUND_VOLUME_MAX,
							                  streamData->m_volume.m_value >> REDSOUND_FIXED_SHIFT);
						} else {
							SetVoiceVolumeMix(voiceData, streamData->m_pan.m_value >> REDSOUND_FIXED_SHIFT,
							                  streamData->m_volume.m_value >> REDSOUND_FIXED_SHIFT);
						}
					}
				}
			}
		} else if ((streamData->m_state == REDSOUND_STREAM_STATE_LOADING) && (RedDmaSearchID(streamData->m_dmaId) == 0)) {
			voiceData = streamData->m_voiceData;
			streamData->m_state = REDSOUND_STREAM_STATE_PLAYING;
			voiceData->m_flags |= REDSOUND_VOICE_FLAGS_STREAM_START;
			voiceData->m_waveData = streamData->m_trackData;
			voiceData->m_active = REDSOUND_VOICE_ACTIVE_ON;
			if (streamData->m_header.m_channelCount == REDSOUND_STREAM_STEREO_CHANNEL_COUNT) {
				voiceData[REDSOUND_STREAM_RIGHT_CHANNEL].m_flags |= REDSOUND_VOICE_FLAGS_STREAM_START;
				voiceData[REDSOUND_STREAM_RIGHT_CHANNEL].m_waveData =
				    &streamData->m_trackData[REDSOUND_STREAM_RIGHT_CHANNEL];
				voiceData[REDSOUND_STREAM_RIGHT_CHANNEL].m_active = REDSOUND_VOICE_ACTIVE_ON;
			}
		}

		streamData++;
	} while (streamData < p_Stream + REDSOUND_STREAM_COUNT);
}
/*
 * --INFO--
 * PAL Address: 0x801cb93c
 * PAL Size: 68b
 * EN Address: 0x8020d860
 * EN Size: 68b
 * JP Address: TODO
 * JP Size: TODO
 */
static RedStreamDATA* _SearchEmptyStreamData()
{
	RedStreamDATA* streamData = p_Stream;

	for (;;) {
		if (streamData->m_streamId == REDSOUND_STREAM_ID_NONE) {
			return streamData;
		}

		streamData++;

		if (!(streamData < p_Stream + REDSOUND_STREAM_COUNT)) {
			return 0;
		}
	}
}
/*
 * --INFO--
 * PAL Address: 0x801cb980
 * PAL Size: 272b
 * EN Address: 0x8020d8a4
 * EN Size: 272b
 * JP Address: TODO
 * JP Size: TODO
 */
static void _StreamStop(RedStreamDATA* streamData)
{
	fflush(__files + 1);
	if (streamData->m_streamId != REDSOUND_STREAM_ID_NONE) {
		streamData->m_streamId = REDSOUND_STREAM_ID_NONE;
		streamData->m_state = REDSOUND_STREAM_STATE_STOPPED;
		if (streamData->m_buffer != 0) {
			RedDelete(streamData->m_buffer);
			streamData->m_buffer = 0;
		}
		if (streamData->m_aramBuffer != 0) {
			RedDeleteA(streamData->m_aramBuffer);
			streamData->m_aramBuffer = 0;
		}
		streamData->m_voiceData->m_flags |= REDSOUND_VOICE_FLAGS_RELEASED;
		streamData->m_track->m_note.m_allocFlags &= ~REDSOUND_NOTE_ALLOC_STREAM;
		streamData->m_voiceData->m_stateFlags &= REDSOUND_VOICE_STATE_CLEAR_STREAM_MASK;
		streamData->m_voiceData->m_active = REDSOUND_VOICE_ACTIVE_OFF;
		if (streamData->m_header.m_channelCount == REDSOUND_STREAM_STEREO_CHANNEL_COUNT) {
			streamData->m_voiceData[REDSOUND_STREAM_RIGHT_CHANNEL].m_flags |= REDSOUND_VOICE_FLAGS_RELEASED;
			streamData->m_track[REDSOUND_STREAM_RIGHT_CHANNEL].m_note.m_allocFlags &= ~REDSOUND_NOTE_ALLOC_STREAM;
			streamData->m_voiceData[REDSOUND_STREAM_RIGHT_CHANNEL].m_stateFlags &= REDSOUND_VOICE_STATE_CLEAR_STREAM_MASK;
			streamData->m_voiceData[REDSOUND_STREAM_RIGHT_CHANNEL].m_active = REDSOUND_VOICE_ACTIVE_OFF;
		}
	}
}
/*
 * --INFO--
 * PAL Address: 0x801cba90
 * PAL Size: 476b
 * EN Address: 0x8020d9b4
 * EN Size: 476b
 * JP Address: TODO
 * JP Size: TODO
 */
static int _ArrangeStreamDataNoLoop(RedStreamDATA* stream, int bufferIndex, int byteCount)
{
	unsigned char* dstBuffer;
	RedVoiceDATA* voiceData;
	int dmaDstOffset;
	int dmaID;

	bufferIndex &= REDSOUND_STREAM_BUFFER_SIDE_MASK;

	do {
		dstBuffer = stream->m_buffer + bufferIndex * REDSOUND_STREAM_PAGE_SIZE;
		voiceData = stream->m_voiceData;

		memcpy(dstBuffer, stream->m_fileData + stream->m_readOffset, REDSOUND_STREAM_PAGE_SIZE);
		stream->m_readOffset += REDSOUND_STREAM_PAGE_SIZE;
		if (stream->m_readOffset >= stream->m_fileSize) {
			stream->m_readOffset = 0;
		}

		if (stream->m_header.m_channelCount == REDSOUND_STREAM_STEREO_CHANNEL_COUNT) {
			memcpy(dstBuffer + REDSOUND_STREAM_STEREO_PLANE_SIZE, stream->m_fileData + stream->m_readOffset, REDSOUND_STREAM_PAGE_SIZE);
			stream->m_readOffset += REDSOUND_STREAM_PAGE_SIZE;
			if (stream->m_readOffset >= stream->m_fileSize) {
				stream->m_readOffset = 0;
			}
		}

		dmaDstOffset = stream->m_aramBuffer + bufferIndex * REDSOUND_STREAM_PAGE_SIZE;
		dmaID = RedDmaEntry(REDSOUND_DMA_FLAGS_STREAM_LOAD, REDSOUND_DMA_DIRECTION_TO_ARAM,
		                    (int)dstBuffer, dmaDstOffset, REDSOUND_STREAM_PAGE_SIZE, 0, 0);

		if ((bufferIndex == REDSOUND_STREAM_BUFFER_SIDE_A) && (voiceData->m_axVoice != 0)) {
			voiceData->m_axVoice->pb.adpcmLoop.loop_pred_scale = (unsigned short)*dstBuffer;
			voiceData->m_axVoice->pb.adpcmLoop.loop_yn1 = voiceData->m_axVoice->pb.adpcmLoop.loop_yn2 = 0;
			voiceData->m_axVoice->sync |= AX_SYNC_FLAG_COPYADPCMLOOP;
		}

		if (stream->m_header.m_channelCount == REDSOUND_STREAM_STEREO_CHANNEL_COUNT) {
			dstBuffer += REDSOUND_STREAM_STEREO_PLANE_SIZE;
			dmaDstOffset += REDSOUND_STREAM_STEREO_PLANE_SIZE;
			voiceData += 1;
			dmaID = RedDmaEntry(REDSOUND_DMA_FLAGS_STREAM_LOAD, REDSOUND_DMA_DIRECTION_TO_ARAM,
			                    (int)dstBuffer, dmaDstOffset, REDSOUND_STREAM_PAGE_SIZE, 0, 0);
			if ((bufferIndex == REDSOUND_STREAM_BUFFER_SIDE_A) && (voiceData->m_axVoice != 0)) {
				voiceData->m_axVoice->pb.adpcmLoop.loop_pred_scale = (unsigned short)*dstBuffer;
				voiceData->m_axVoice->pb.adpcmLoop.loop_yn1 = voiceData->m_axVoice->pb.adpcmLoop.loop_yn2 = 0;
				voiceData->m_axVoice->sync |= AX_SYNC_FLAG_COPYADPCMLOOP;
			}
		}

		byteCount -= REDSOUND_STREAM_PAGE_SIZE;
		bufferIndex ^= REDSOUND_STREAM_BUFFER_SIDE_MASK;
		stream->m_streamCursor += REDSOUND_STREAM_SAMPLE_ADVANCE;
	} while (0 < byteCount);

	return dmaID;
}
/*
 * --INFO--
 * PAL Address: 0x801cbc6c
 * PAL Size: 856b
 * EN Address: 0x8020db90
 * EN Size: 856b
 * JP Address: TODO
 * JP Size: TODO
 */
static int _ArrangeStreamDataLoop(RedStreamDATA* stream, int bufferIndex, int byteCount)
{
	RedStreamStereoFrame* srcEnd;
	RedStreamChannelFrame* leftDst;
	RedStreamChannelFrame* rightDst;
	unsigned char* dstBase;
	RedStreamStereoFrame* srcFrame;
	RedVoiceDATA* voiceData;
	int dmaID;

	bufferIndex = bufferIndex & REDSOUND_STREAM_BUFFER_SIDE_MASK;
	
	if (stream->m_header.m_channelCount == REDSOUND_STREAM_STEREO_CHANNEL_COUNT) {
		do {
			dstBase = stream->m_buffer + bufferIndex * REDSOUND_STREAM_PAGE_SIZE;
			voiceData = stream->m_voiceData;
			srcFrame = (RedStreamStereoFrame*)(stream->m_fileData + stream->m_readOffset);
			rightDst = (RedStreamChannelFrame*)(dstBase + REDSOUND_STREAM_STEREO_PLANE_SIZE);
			srcEnd = srcFrame + REDSOUND_STREAM_STEREO_FRAMES_PER_PAGE;
			leftDst = (RedStreamChannelFrame*)dstBase;
			
			do {
				leftDst->m_word[0] = srcFrame->m_left[0];
				leftDst->m_word[1] = srcFrame->m_left[1];
				leftDst++;
				rightDst->m_word[0] = srcFrame->m_right[0];
				rightDst->m_word[1] = srcFrame->m_right[1];
				srcFrame = srcFrame + 1;
				rightDst++;
			} while (srcFrame < srcEnd);
			
			stream->m_readOffset = stream->m_readOffset + REDSOUND_STREAM_PAGE_SIZE;
			if (stream->m_readOffset >= stream->m_fileSize) {
				stream->m_readOffset = 0;
			}
			
			srcFrame = (RedStreamStereoFrame*)(stream->m_fileData + stream->m_readOffset);
			srcEnd = srcFrame + REDSOUND_STREAM_STEREO_FRAMES_PER_PAGE;
			
			do {
				leftDst->m_word[0] = srcFrame->m_left[0];
				leftDst->m_word[1] = srcFrame->m_left[1];
				leftDst++;
				rightDst->m_word[0] = srcFrame->m_right[0];
				rightDst->m_word[1] = srcFrame->m_right[1];
				srcFrame = srcFrame + 1;
				rightDst++;
			} while (srcFrame < srcEnd);
			
			stream->m_readOffset = stream->m_readOffset + REDSOUND_STREAM_PAGE_SIZE;
			if (stream->m_readOffset >= stream->m_fileSize) {
				stream->m_readOffset = 0;
			}
			
			dmaID = RedDmaEntry(REDSOUND_DMA_FLAGS_STREAM_LOAD, REDSOUND_DMA_DIRECTION_TO_ARAM,
			                    (int)dstBase, stream->m_aramBuffer + bufferIndex * REDSOUND_STREAM_PAGE_SIZE,
			                    REDSOUND_STREAM_PAGE_SIZE, 0, 0);
			dmaID = RedDmaEntry(REDSOUND_DMA_FLAGS_STREAM_LOAD, REDSOUND_DMA_DIRECTION_TO_ARAM,
			                    (int)(dstBase + REDSOUND_STREAM_STEREO_PLANE_SIZE),
			                    stream->m_aramBuffer + (bufferIndex + REDSOUND_STREAM_STEREO_PLANE_PAGE_COUNT) * REDSOUND_STREAM_PAGE_SIZE,
			                    REDSOUND_STREAM_PAGE_SIZE, 0, 0);
			
			if ((bufferIndex == REDSOUND_STREAM_BUFFER_SIDE_A) && (voiceData->m_axVoice != 0)) {
				voiceData->m_axVoice->pb.adpcmLoop.loop_pred_scale = (unsigned short)*dstBase;
				voiceData->m_axVoice->pb.adpcmLoop.loop_yn1 = voiceData->m_axVoice->pb.adpcmLoop.loop_yn2 = 0;
				voiceData->m_axVoice->sync |= AX_SYNC_FLAG_COPYADPCMLOOP;
				voiceData[REDSOUND_STREAM_RIGHT_CHANNEL].m_axVoice->pb.adpcmLoop.loop_pred_scale =
				    (unsigned short)dstBase[REDSOUND_STREAM_STEREO_PLANE_SIZE];
				voiceData[REDSOUND_STREAM_RIGHT_CHANNEL].m_axVoice->pb.adpcmLoop.loop_yn1 =
				    voiceData[REDSOUND_STREAM_RIGHT_CHANNEL].m_axVoice->pb.adpcmLoop.loop_yn2 = 0;
				voiceData[REDSOUND_STREAM_RIGHT_CHANNEL].m_axVoice->sync |= AX_SYNC_FLAG_COPYADPCMLOOP;
			}
			
			bufferIndex = bufferIndex ^ REDSOUND_STREAM_BUFFER_SIDE_MASK;
			byteCount = byteCount + -REDSOUND_STREAM_PAGE_SIZE;
			stream->m_streamCursor = stream->m_streamCursor + REDSOUND_STREAM_SAMPLE_ADVANCE;
			
			if (stream->m_streamCursor >= stream->m_header.m_loopEnd) {
				stream->m_streamCursor = stream->m_streamCursor - stream->m_header.m_loopEnd;
				stream->m_streamCursor = stream->m_streamCursor + stream->m_header.m_loopStart;
			}
		} while (0 < byteCount);
	} else {
		do {
			dstBase = stream->m_buffer + bufferIndex * REDSOUND_STREAM_PAGE_SIZE;
			voiceData = stream->m_voiceData;
			memcpy(dstBase, stream->m_fileData + stream->m_readOffset, REDSOUND_STREAM_PAGE_SIZE);
			stream->m_readOffset = stream->m_readOffset + REDSOUND_STREAM_PAGE_SIZE;
			
			if (stream->m_readOffset >= stream->m_fileSize) {
				stream->m_readOffset = 0;
			}
			
			dmaID = RedDmaEntry(REDSOUND_DMA_FLAGS_STREAM_LOAD, REDSOUND_DMA_DIRECTION_TO_ARAM,
			                    (int)dstBase, stream->m_aramBuffer + bufferIndex * REDSOUND_STREAM_PAGE_SIZE,
			                    REDSOUND_STREAM_PAGE_SIZE, 0, 0);
			
			if ((bufferIndex == REDSOUND_STREAM_BUFFER_SIDE_A) && (voiceData->m_axVoice != 0)) {
				voiceData->m_axVoice->pb.adpcmLoop.loop_pred_scale = (unsigned short)*dstBase;
				voiceData->m_axVoice->pb.adpcmLoop.loop_yn1 = voiceData->m_axVoice->pb.adpcmLoop.loop_yn2 = 0;
				voiceData->m_axVoice->sync |= AX_SYNC_FLAG_COPYADPCMLOOP;
			}
			
			bufferIndex = bufferIndex ^ REDSOUND_STREAM_BUFFER_SIDE_MASK;
			byteCount = byteCount + -REDSOUND_STREAM_PAGE_SIZE;
			stream->m_streamCursor = stream->m_streamCursor + REDSOUND_STREAM_SAMPLE_ADVANCE;
			
			if (stream->m_streamCursor >= stream->m_header.m_loopEnd) {
				stream->m_streamCursor = stream->m_streamCursor - stream->m_header.m_loopEnd;
				stream->m_streamCursor = stream->m_streamCursor + stream->m_header.m_loopStart;
			}
		} while (0 < byteCount);
	}

	return dmaID;
}
/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 184b
 * EN Address: UNUSED
 * EN Size: 184b
 * JP Address: TODO
 * JP Size: TODO
 */
void SetStreamPan(int streamID, int pan, int frameCount)
{
	volatile RedStreamDATA* streamData;

	if (frameCount < REDSOUND_STREAM_MIN_FRAME_COUNT) {
		frameCount = REDSOUND_STREAM_MIN_FRAME_COUNT;
	} else {
		frameCount *= REDSOUND_STREAM_FADE_TICKS_PER_SECOND;
		frameCount /= REDSOUND_FRAMES_PER_SECOND;
	}

	pan &= REDSOUND_PAN_BYTE_MASK;
	pan <<= REDSOUND_FIXED_SHIFT;
	pan |= REDSOUND_FIXED_HALF;
	streamData = p_Stream;
	do {
		if ((streamData->m_streamId != REDSOUND_STREAM_ID_NONE) &&
		    ((streamID == REDSOUND_STREAM_ID_ALL) || (streamID == streamData->m_streamId))) {
			if (frameCount > 0) {
				int delta = pan - streamData->m_pan.m_value;
				streamData->m_pan.m_step = delta / frameCount;
				streamData->m_pan.m_stepCount = frameCount;
			} else {
				streamData->m_pan.m_value = pan;
				streamData->m_pan.m_stepCount = 0;
			}
		}
		streamData++;
	} while (streamData < p_Stream + REDSOUND_STREAM_COUNT);
}
