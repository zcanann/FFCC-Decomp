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

enum RedStreamMapLayout {
	REDSOUND_STREAM_MAP_RODATA_STRING_OFFSET = 0x00,
	REDSOUND_STREAM_MAP_RODATA_STRING_SIZE = 0xC6,
	REDSOUND_STREAM_MAP_SDATA2_STRING_OFFSET = 0x00,
	REDSOUND_STREAM_MAP_SDATA2_STRING_SIZE = 0x15,
};

enum RedStreamLayoutSize {
	REDSOUND_STREAM_SAMPLE_ADVANCE = REDSOUND_STREAM_PAGE_SIZE / REDSOUND_STREAM_STEREO_CHANNEL_FRAME_BYTES,
	REDSOUND_STREAM_FILE_HEADER_SIZE = sizeof(RedStreamHEAD),
	REDSOUND_STREAM_INITIAL_LOOP_END = REDSOUND_STREAM_TRANSFER_BUFFER_SIZE - 1,
	REDSOUND_STREAM_BASE_PITCH = 0x3c00000,
	REDSOUND_STREAM_ARAM_HIGH_THRESHOLD = REDSOUND_WAVE_ARAM_LAYOUT_SIZE,
	REDSOUND_STREAM_ARAM_LOW_OFFSET = REDSOUND_WAVE_DEFAULT_REGION_OFFSET,
	REDSOUND_STREAM_ARAM_HIGH_OFFSET = REDSOUND_WAVE_FIXED_REGION_OFFSET,
	REDSOUND_STREAM_ARAM_TO_AX_ADDRESS_SCALE = 2,
	REDSOUND_STREAM_ERASE_TRACK = 0xff,
	REDSOUND_STREAM_MIN_FRAME_COUNT = 1,
	REDSOUND_STREAM_SILENT_PAN = 0,
	REDSOUND_STREAM_BUFFER_SIDE_A = 0,
	REDSOUND_STREAM_BUFFER_SIDE_B = 1,
	REDSOUND_STREAM_BUFFER_SIDE_MASK = 1,
	REDSOUND_STREAM_VOLUME_INPUT_SCALE_SHIFT = 8,
};

#define RedStreamVolumeFromInput(volume) (((volume + 1) * REDSOUND_VOLUME_BYTE_SCALE - 1) * REDSOUND_FIXED_ONE)
#define RedStreamGetCurrentAramSampleStart(stream)                                                \
	(((stream)->m_aramBuffer + (stream)->m_streamCursorBase) * REDSOUND_STREAM_ARAM_TO_AX_ADDRESS_SCALE)

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
STATIC_ASSERT(REDSOUND_STREAM_ARAM_LOW_OFFSET == REDSOUND_WAVE_DEFAULT_REGION_OFFSET);
STATIC_ASSERT(REDSOUND_STREAM_ARAM_HIGH_OFFSET == REDSOUND_WAVE_FIXED_REGION_OFFSET);
STATIC_ASSERT(REDSOUND_STREAM_ARAM_HIGH_THRESHOLD == REDSOUND_WAVE_ARAM_LAYOUT_SIZE);
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
STATIC_ASSERT(REDSOUND_STREAM_MAP_RODATA_STRING_OFFSET == 0);
STATIC_ASSERT(REDSOUND_STREAM_RODATA_STRING_SIZE == REDSOUND_STREAM_MAP_RODATA_STRING_SIZE);
STATIC_ASSERT(sizeof(sRedStreamLogErrorColor) + sizeof(sRedStreamLogReset) + sizeof(sRedStreamLogWarnColor) ==
              REDSOUND_STREAM_SDATA2_STRING_SIZE);
STATIC_ASSERT(REDSOUND_STREAM_MAP_SDATA2_STRING_OFFSET == 0);
STATIC_ASSERT(REDSOUND_STREAM_SDATA2_STRING_SIZE == REDSOUND_STREAM_MAP_SDATA2_STRING_SIZE);

static RedStreamDATA* _SearchEmptyStreamData();
static void _StreamStop(RedStreamDATA* streamData);
static int _ArrangeStreamDataNoLoop(RedStreamDATA* stream, int bufferIndex, int byteCount);
static int _ArrangeStreamDataLoop(RedStreamDATA* stream, int bufferIndex, int byteCount);

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
	RedStreamDATA* streamData = RedStreamDataGetBegin();

	for (;;) {
		if (streamData->m_streamId == REDSOUND_STREAM_ID_NONE) {
			return streamData;
		}

		streamData++;

		if (!(streamData < RedStreamDataGetEnd())) {
			return REDSOUND_STREAM_DATA_NONE;
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
		if (streamData->m_buffer != REDSOUND_STREAM_BUFFER_NONE) {
			RedDelete(streamData->m_buffer);
			streamData->m_buffer = REDSOUND_STREAM_BUFFER_NONE;
		}
		if (streamData->m_aramBuffer != REDSOUND_STREAM_ARAM_BUFFER_NONE) {
			RedDeleteA(streamData->m_aramBuffer);
			streamData->m_aramBuffer = REDSOUND_STREAM_ARAM_BUFFER_NONE;
		}
		streamData->m_voiceData->m_flags |= REDSOUND_VOICE_FLAGS_RELEASED;
		RedNoteAllocClearStream(streamData->m_track->m_note.m_allocFlags);
		streamData->m_voiceData->m_stateFlags &= REDSOUND_VOICE_STATE_CLEAR_STREAM_MASK;
		streamData->m_voiceData->m_active = REDSOUND_VOICE_ACTIVE_OFF;
		if (streamData->m_header.m_channelCount == REDSOUND_STREAM_STEREO_CHANNEL_COUNT) {
			RedStreamGetVoiceData(streamData, REDSOUND_STREAM_RIGHT_CHANNEL)->m_flags |= REDSOUND_VOICE_FLAGS_RELEASED;
			RedNoteAllocClearStream(RedStreamGetTrack(streamData, REDSOUND_STREAM_RIGHT_CHANNEL)->m_note.m_allocFlags);
			RedStreamGetVoiceData(streamData, REDSOUND_STREAM_RIGHT_CHANNEL)->m_stateFlags &= REDSOUND_VOICE_STATE_CLEAR_STREAM_MASK;
			RedStreamGetVoiceData(streamData, REDSOUND_STREAM_RIGHT_CHANNEL)->m_active = REDSOUND_VOICE_ACTIVE_OFF;
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
		dstBuffer = RedStreamBufferGetPage(stream->m_buffer, bufferIndex);
		voiceData = stream->m_voiceData;

		memcpy(dstBuffer, RedStreamGetReadCursor(stream), REDSOUND_STREAM_PAGE_SIZE);
		stream->m_readOffset += REDSOUND_STREAM_PAGE_SIZE;
		if (stream->m_readOffset >= stream->m_fileSize) {
			stream->m_readOffset = 0;
		}

		if (stream->m_header.m_channelCount == REDSOUND_STREAM_STEREO_CHANNEL_COUNT) {
			memcpy(RedStreamBufferGetRightPlane(dstBuffer), RedStreamGetReadCursor(stream), REDSOUND_STREAM_PAGE_SIZE);
			stream->m_readOffset += REDSOUND_STREAM_PAGE_SIZE;
			if (stream->m_readOffset >= stream->m_fileSize) {
				stream->m_readOffset = 0;
			}
		}

		dmaDstOffset = RedStreamAramGetPage(stream->m_aramBuffer, bufferIndex);
		dmaID = RedDmaEntry(REDSOUND_DMA_FLAGS_STREAM_LOAD, REDSOUND_DMA_DIRECTION_TO_ARAM,
		                    RedDmaMainMemoryAddress(dstBuffer), dmaDstOffset, REDSOUND_STREAM_PAGE_SIZE,
		                    REDSOUND_DMA_CALLBACK_NONE, REDSOUND_DMA_CALLBACK_DATA_NONE);

		if ((bufferIndex == REDSOUND_STREAM_BUFFER_SIDE_A) && (voiceData->m_axVoice != REDSOUND_AX_VOICE_NONE)) {
			voiceData->m_axVoice->pb.adpcmLoop.loop_pred_scale = (unsigned short)*dstBuffer;
			voiceData->m_axVoice->pb.adpcmLoop.loop_yn1 = voiceData->m_axVoice->pb.adpcmLoop.loop_yn2 = 0;
			voiceData->m_axVoice->sync |= AX_SYNC_FLAG_COPYADPCMLOOP;
		}

		if (stream->m_header.m_channelCount == REDSOUND_STREAM_STEREO_CHANNEL_COUNT) {
			dstBuffer = RedStreamBufferGetRightPlane(dstBuffer);
			dmaDstOffset = RedStreamAramGetRightPlane(dmaDstOffset);
			voiceData += 1;
			dmaID = RedDmaEntry(REDSOUND_DMA_FLAGS_STREAM_LOAD, REDSOUND_DMA_DIRECTION_TO_ARAM,
			                    RedDmaMainMemoryAddress(dstBuffer), dmaDstOffset, REDSOUND_STREAM_PAGE_SIZE,
			                    REDSOUND_DMA_CALLBACK_NONE, REDSOUND_DMA_CALLBACK_DATA_NONE);
			if ((bufferIndex == REDSOUND_STREAM_BUFFER_SIDE_A) && (voiceData->m_axVoice != REDSOUND_AX_VOICE_NONE)) {
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
			dstBase = RedStreamBufferGetPage(stream->m_buffer, bufferIndex);
			voiceData = stream->m_voiceData;
			srcFrame = (RedStreamStereoFrame*)RedStreamGetReadCursor(stream);
			rightDst = (RedStreamChannelFrame*)RedStreamBufferGetRightPlane(dstBase);
			srcEnd = srcFrame + REDSOUND_STREAM_STEREO_FRAMES_PER_PAGE;
			leftDst = (RedStreamChannelFrame*)dstBase;
			
			do {
				RedStreamChannelFrameGetWord(leftDst, REDSOUND_STREAM_FRAME_WORD_0) =
				    RedStreamStereoFrameGetLeftWord(srcFrame, REDSOUND_STREAM_FRAME_WORD_0);
				RedStreamChannelFrameGetWord(leftDst, REDSOUND_STREAM_FRAME_WORD_1) =
				    RedStreamStereoFrameGetLeftWord(srcFrame, REDSOUND_STREAM_FRAME_WORD_1);
				leftDst++;
				RedStreamChannelFrameGetWord(rightDst, REDSOUND_STREAM_FRAME_WORD_0) =
				    RedStreamStereoFrameGetRightWord(srcFrame, REDSOUND_STREAM_FRAME_WORD_0);
				RedStreamChannelFrameGetWord(rightDst, REDSOUND_STREAM_FRAME_WORD_1) =
				    RedStreamStereoFrameGetRightWord(srcFrame, REDSOUND_STREAM_FRAME_WORD_1);
				srcFrame = srcFrame + 1;
				rightDst++;
			} while (srcFrame < srcEnd);
			
			stream->m_readOffset = stream->m_readOffset + REDSOUND_STREAM_PAGE_SIZE;
			if (stream->m_readOffset >= stream->m_fileSize) {
				stream->m_readOffset = 0;
			}
			
			srcFrame = (RedStreamStereoFrame*)RedStreamGetReadCursor(stream);
			srcEnd = srcFrame + REDSOUND_STREAM_STEREO_FRAMES_PER_PAGE;
			
			do {
				RedStreamChannelFrameGetWord(leftDst, REDSOUND_STREAM_FRAME_WORD_0) =
				    RedStreamStereoFrameGetLeftWord(srcFrame, REDSOUND_STREAM_FRAME_WORD_0);
				RedStreamChannelFrameGetWord(leftDst, REDSOUND_STREAM_FRAME_WORD_1) =
				    RedStreamStereoFrameGetLeftWord(srcFrame, REDSOUND_STREAM_FRAME_WORD_1);
				leftDst++;
				RedStreamChannelFrameGetWord(rightDst, REDSOUND_STREAM_FRAME_WORD_0) =
				    RedStreamStereoFrameGetRightWord(srcFrame, REDSOUND_STREAM_FRAME_WORD_0);
				RedStreamChannelFrameGetWord(rightDst, REDSOUND_STREAM_FRAME_WORD_1) =
				    RedStreamStereoFrameGetRightWord(srcFrame, REDSOUND_STREAM_FRAME_WORD_1);
				srcFrame = srcFrame + 1;
				rightDst++;
			} while (srcFrame < srcEnd);
			
			stream->m_readOffset = stream->m_readOffset + REDSOUND_STREAM_PAGE_SIZE;
			if (stream->m_readOffset >= stream->m_fileSize) {
				stream->m_readOffset = 0;
			}
			
			dmaID = RedDmaEntry(REDSOUND_DMA_FLAGS_STREAM_LOAD, REDSOUND_DMA_DIRECTION_TO_ARAM,
			                    RedDmaMainMemoryAddress(dstBase), RedStreamAramGetPage(stream->m_aramBuffer, bufferIndex),
			                    REDSOUND_STREAM_PAGE_SIZE, REDSOUND_DMA_CALLBACK_NONE,
			                    REDSOUND_DMA_CALLBACK_DATA_NONE);
			dmaID = RedDmaEntry(REDSOUND_DMA_FLAGS_STREAM_LOAD, REDSOUND_DMA_DIRECTION_TO_ARAM,
			                    RedDmaMainMemoryAddress(RedStreamBufferGetRightPlane(dstBase)),
			                    RedStreamAramGetPage(stream->m_aramBuffer,
			                                         bufferIndex + REDSOUND_STREAM_STEREO_PLANE_PAGE_COUNT),
			                    REDSOUND_STREAM_PAGE_SIZE, REDSOUND_DMA_CALLBACK_NONE,
			                    REDSOUND_DMA_CALLBACK_DATA_NONE);
			
			if ((bufferIndex == REDSOUND_STREAM_BUFFER_SIDE_A) && (voiceData->m_axVoice != REDSOUND_AX_VOICE_NONE)) {
				voiceData->m_axVoice->pb.adpcmLoop.loop_pred_scale = (unsigned short)*dstBase;
				voiceData->m_axVoice->pb.adpcmLoop.loop_yn1 = voiceData->m_axVoice->pb.adpcmLoop.loop_yn2 = 0;
				voiceData->m_axVoice->sync |= AX_SYNC_FLAG_COPYADPCMLOOP;
				RedStreamVoiceDataGetChannel(voiceData, REDSOUND_STREAM_RIGHT_CHANNEL)->m_axVoice->pb.adpcmLoop.loop_pred_scale =
				    (unsigned short)*RedStreamBufferGetRightPlane(dstBase);
				RedStreamVoiceDataGetChannel(voiceData, REDSOUND_STREAM_RIGHT_CHANNEL)->m_axVoice->pb.adpcmLoop.loop_yn1 =
				    RedStreamVoiceDataGetChannel(voiceData, REDSOUND_STREAM_RIGHT_CHANNEL)->m_axVoice->pb.adpcmLoop.loop_yn2 = 0;
				RedStreamVoiceDataGetChannel(voiceData, REDSOUND_STREAM_RIGHT_CHANNEL)->m_axVoice->sync |= AX_SYNC_FLAG_COPYADPCMLOOP;
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
			dstBase = RedStreamBufferGetPage(stream->m_buffer, bufferIndex);
			voiceData = stream->m_voiceData;
			memcpy(dstBase, RedStreamGetReadCursor(stream), REDSOUND_STREAM_PAGE_SIZE);
			stream->m_readOffset = stream->m_readOffset + REDSOUND_STREAM_PAGE_SIZE;
			
			if (stream->m_readOffset >= stream->m_fileSize) {
				stream->m_readOffset = 0;
			}
			
			dmaID = RedDmaEntry(REDSOUND_DMA_FLAGS_STREAM_LOAD, REDSOUND_DMA_DIRECTION_TO_ARAM,
			                    RedDmaMainMemoryAddress(dstBase), RedStreamAramGetPage(stream->m_aramBuffer, bufferIndex),
			                    REDSOUND_STREAM_PAGE_SIZE, REDSOUND_DMA_CALLBACK_NONE,
			                    REDSOUND_DMA_CALLBACK_DATA_NONE);
			
			if ((bufferIndex == REDSOUND_STREAM_BUFFER_SIDE_A) && (voiceData->m_axVoice != REDSOUND_AX_VOICE_NONE)) {
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
 * PAL Address: 0x801cbfc4
 * PAL Size: 112b
 * EN Address: 0x8020dee8
 * EN Size: 112b
 * JP Address: TODO
 * JP Size: TODO
 */
void StreamStop(int streamID)
{
	volatile RedStreamDATA* streamData = RedStreamDataGetBegin();

	do {
		if ((streamData->m_streamId != REDSOUND_STREAM_ID_NONE) &&
		    ((streamID == REDSOUND_STREAM_ID_ALL) || (streamID == streamData->m_streamId))) {
			_StreamStop((RedStreamDATA*)streamData);
		}
		streamData++;
	} while (streamData < RedStreamDataGetEnd());
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
	int aramSize;
	unsigned int aramOffset;
	RedStreamADPCMHeader* adpcmHeader;
	RedStreamDATA* streamData;

	streamData = _SearchEmptyStreamData();
	if (streamData != REDSOUND_STREAM_DATA_NONE) {

	memcpy(&streamData->m_header, streamHeader, REDSOUND_STREAM_HEAD_SIZE);
	streamData->m_track = SearchSeEmptyTrack(streamData->m_header.m_channelCount, REDSOUND_STREAM_ERASE_TRACK, 0);
	streamData->m_buffer = (u8*)RedNew(REDSOUND_STREAM_TRANSFER_BUFFER_ALLOC_SIZE);
	aramSize = streamData->m_header.m_channelCount * REDSOUND_STREAM_STEREO_PLANE_SIZE;
	if (c_RedMemory.GetABufferSize() < REDSOUND_STREAM_ARAM_HIGH_THRESHOLD) {
		aramOffset = REDSOUND_STREAM_ARAM_LOW_OFFSET;
	} else {
		aramOffset = REDSOUND_STREAM_ARAM_HIGH_OFFSET;
	}
	streamData->m_aramBuffer = RedNewA(aramSize, 0, aramOffset);
	if (streamData->m_aramBuffer == REDSOUND_STREAM_ARAM_BUFFER_NONE) {
		c_RedEntry.WaveOldClear(0, aramOffset);
		streamData->m_aramBuffer = RedNewA(aramSize, 0, aramOffset);
	}

	if ((streamData->m_track != REDSOUND_STREAM_TRACK_NONE) &&
	    (streamData->m_buffer != REDSOUND_STREAM_BUFFER_NONE) &&
	    (streamData->m_aramBuffer != REDSOUND_STREAM_ARAM_BUFFER_NONE)) {
		{
			int adpcmSampleOffset;
			RedStreamFile* streamFile;

			adpcmSampleOffset = REDSOUND_STREAM_FILE_AUDIO_OFFSET;
			streamFile = RedStreamFileFromHeader(streamHeader);
			adpcmHeader = RedStreamFileGetAdpcm(streamFile, REDSOUND_STREAM_LEFT_CHANNEL);
			adpcmHeader->m_data.pred_scale = RedStreamFileGetSampleByte(streamFile, adpcmSampleOffset);
			adpcmHeader->m_data.yn1 = adpcmHeader->m_data.yn2 = 0;
			if (streamData->m_header.m_channelCount == REDSOUND_STREAM_STEREO_CHANNEL_COUNT) {
				if (RedStreamHeaderHasNoLoop(&streamData->m_header)) {
					adpcmSampleOffset += REDSOUND_STREAM_PAGE_SIZE;
				} else {
					adpcmSampleOffset += REDSOUND_STREAM_STEREO_RIGHT_FRAME_OFFSET;
				}
				RedStreamAdpcmHeaderGetChannel(adpcmHeader, REDSOUND_STREAM_RIGHT_CHANNEL)->m_data.pred_scale =
				    RedStreamFileGetSampleByte(streamFile, adpcmSampleOffset);
				RedStreamAdpcmHeaderGetChannel(adpcmHeader, REDSOUND_STREAM_RIGHT_CHANNEL)->m_data.yn1 =
				    RedStreamAdpcmHeaderGetChannel(adpcmHeader, REDSOUND_STREAM_RIGHT_CHANNEL)->m_data.yn2 = 0;
			}
		}

		streamData->m_streamId = streamID;
		streamData->m_fileCursor = 0;
		streamData->m_readOffset = REDSOUND_STREAM_PAGE_SIZE;
		streamData->m_streamCursor = 0;
		streamData->m_voiceData = RedVoiceDataGet(streamData->m_track->m_trackNo);
		streamData->m_fileData = RedStreamFileFromHeader(streamHeader);
		streamData->m_fileSize = fileSize;
		if (volume != 0) {
			volume = RedStreamVolumeFromInput(volume);
		}
		streamData->m_volume.m_value = volume;
		streamData->m_volume.m_stepCount = 0;
		int streamPitch = PitchCompute(REDSOUND_STREAM_BASE_PITCH, 0, streamData->m_header.m_pitch, 0);
		int channelIndex = 0;
		do {
			RedVoiceDATA* voice = RedStreamGetVoiceData(streamData, channelIndex);
			voice->m_track = RedStreamGetTrack(streamData, channelIndex);
			RedNoteAllocSetStream(voice->m_track->m_note.m_allocFlags);
			voice->m_stateFlags |= REDSOUND_VOICE_STATE_STREAM;
			voice->m_voiceSwitch = REDSOUND_VOICE_SWITCH_STREAM_DEFAULT;
			if (streamData->m_header.m_flags != REDSOUND_STREAM_HEADER_REVERB_NONE) {
				voice->m_voiceSwitch |= REDSOUND_VOICE_SWITCH_REVERB_STEREO;
			}
			voice->m_track->m_voiceSwitch = REDSOUND_VOICE_SWITCH_LOOP;
			voice->m_envelopeLevel = REDSOUND_ENVELOPE_LEVEL_FULL;
			voice->m_waveData = RedStreamGetTrackData(streamData, channelIndex);
			voice->m_targetPitch = streamPitch;
			voice->m_track->m_reverbDepth = RedReverbDepthGetDepth(REDSOUND_REVERB_DEPTH_SE);
			voice->m_track->m_reverbDepthDelta = 0;
			if (streamData->m_header.m_channelCount == REDSOUND_STREAM_STEREO_CHANNEL_COUNT) {
				if (channelIndex == REDSOUND_STREAM_LEFT_CHANNEL) {
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
			SetVoiceVolumeMix(RedStreamGetVoiceData(streamData, channelIndex), streamData->m_pan.m_value >> REDSOUND_FIXED_SHIFT,
			                  streamData->m_volume.m_value >> REDSOUND_FIXED_SHIFT);
			RedStreamGetTrack(streamData, channelIndex)->m_waveBase =
			    RedStreamAramGetChannelPlane(streamData->m_aramBuffer, channelIndex);
			memset(RedStreamGetTrackData(streamData, channelIndex), 0, REDSOUND_WAVE_DATA_SIZE);
			memcpy(&RedStreamGetTrackData(streamData, channelIndex)->m_adpcm, RedStreamAdpcmHeaderGetChannel(adpcmHeader, channelIndex),
			       REDSOUND_STREAM_ADPCM_HEADER_SIZE);
			voice->m_adsr.m_level[REDSOUND_VOICE_ADSR_ATTACK] = voice->m_adsr.m_level[REDSOUND_VOICE_ADSR_DECAY] =
			    voice->m_adsr.m_level[REDSOUND_VOICE_ADSR_SUSTAIN] = 0;
			voice->m_adsr.m_level[REDSOUND_VOICE_ADSR_RELEASE] = REDSOUND_VOLUME_MAX;
			voice->m_adsr.m_time[REDSOUND_VOICE_ADSR_ATTACK] = voice->m_adsr.m_time[REDSOUND_VOICE_ADSR_DECAY] =
			    voice->m_adsr.m_time[REDSOUND_VOICE_ADSR_SUSTAIN] = 0;
			voice->m_adsr.m_time[REDSOUND_VOICE_ADSR_RELEASE] = REDSOUND_STREAM_ADSR_RELEASE_TIME;
			RedStreamGetTrackData(streamData, channelIndex)->m_sampleStart = 0;
			RedStreamGetTrackData(streamData, channelIndex)->m_loopEnd = REDSOUND_STREAM_INITIAL_LOOP_END;
			RedStreamGetTrackData(streamData, channelIndex)->m_loopStart = REDSOUND_STREAM_LOOP_START_SAMPLE;
			channelIndex += 1;
		} while (channelIndex < streamData->m_header.m_channelCount);

		if (RedStreamHeaderHasNoLoop(&streamData->m_header)) {
			channelIndex = _ArrangeStreamDataNoLoop(streamData, REDSOUND_STREAM_BUFFER_SIDE_A, REDSOUND_STREAM_STEREO_PLANE_SIZE);
		} else {
			channelIndex = _ArrangeStreamDataLoop(streamData, REDSOUND_STREAM_BUFFER_SIDE_A, REDSOUND_STREAM_STEREO_PLANE_SIZE);
		}
		streamData->m_dmaId = channelIndex;
		streamData->m_streamCursorBase = REDSOUND_STREAM_PAGE_SIZE;
		streamData->m_state = REDSOUND_STREAM_STATE_LOADING;
	} else {
		if (RedReportPrintIsEnabled()) {
			OSReport(sRedStreamBufferDidntSecureFmt, sRedStreamLogPrefix, sRedStreamLogErrorColor, sRedStreamLogReset);
			fflush(__files + 1);
		}
		if (streamData->m_buffer != REDSOUND_STREAM_BUFFER_NONE) {
			RedDelete(streamData->m_buffer);
		} else {
			if (RedReportPrintIsEnabled()) {
				OSReport(sRedStreamMainMemoryDidntCreateFmt,
				         sRedStreamLogPrefix, sRedStreamLogWarnColor, REDSOUND_STREAM_TRANSFER_BUFFER_SIZE,
				         sRedStreamLogReset);
				fflush(__files + 1);
			}
		}
		if (streamData->m_aramBuffer != REDSOUND_STREAM_ARAM_BUFFER_NONE) {
			RedDeleteA(streamData->m_aramBuffer);
		} else {
			if (RedReportPrintIsEnabled()) {
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
		volume <<= REDSOUND_STREAM_VOLUME_INPUT_SCALE_SHIFT;
		volume--;
		volume <<= REDSOUND_FIXED_SHIFT;
		volume |= REDSOUND_FIXED_HALF;
	}

	streamData = RedStreamDataGetBegin();
	do {
		if ((streamData->m_streamId != REDSOUND_STREAM_ID_NONE) &&
		    ((streamID == REDSOUND_STREAM_ID_ALL) || (streamID == streamData->m_streamId))) {
			if (frameCount > 0) {
				int volumeDelta = volume - streamData->m_volume.m_value;
				streamData->m_volume.m_step = volumeDelta / frameCount;
				streamData->m_volume.m_stepCount = frameCount;
			} else {
				streamData->m_volume.m_value = volume;
				streamData->m_volume.m_stepCount = 0;
			}
		}
		streamData++;
	} while (streamData < RedStreamDataGetEnd());
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
	streamData = RedStreamDataGetBegin();
	do {
		if ((streamData->m_streamId != REDSOUND_STREAM_ID_NONE) &&
		    ((streamID == REDSOUND_STREAM_ID_ALL) || (streamID == streamData->m_streamId))) {
			if (frameCount > 0) {
				int panDelta = pan - streamData->m_pan.m_value;
				streamData->m_pan.m_step = panDelta / frameCount;
				streamData->m_pan.m_stepCount = frameCount;
			} else {
				streamData->m_pan.m_value = pan;
				streamData->m_pan.m_stepCount = 0;
			}
		}
		streamData++;
	} while (streamData < RedStreamDataGetEnd());
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

	if (RedReportPrintIsEnabled()) {
		if (pause == REDSOUND_PAUSE_ON) {
			OSReport(sRedStreamPauseOnFmt, sRedStreamLogPrefix, streamID);
		} else {
			OSReport(sRedStreamPauseOffFmt, sRedStreamLogPrefix, streamID);
		}
		fflush(__files + 1);
	}
	streamData = RedStreamDataGetBegin();
	do {
		if ((streamData->m_streamId != REDSOUND_STREAM_ID_NONE) &&
		    ((streamID == REDSOUND_STREAM_ID_ALL) || (streamID == streamData->m_streamId))) {
			voiceData = streamData->m_voiceData;
			if (pause == REDSOUND_PAUSE_ON) {
				if (voiceData->m_axVoice != REDSOUND_AX_VOICE_NONE) {
					voiceData->m_targetPitch = 0;
					voiceData->m_flags |= REDSOUND_VOICE_FLAGS_PITCH_DIRTY;
					if (streamData->m_header.m_channelCount == REDSOUND_STREAM_STEREO_CHANNEL_COUNT) {
						RedStreamVoiceDataGetChannel(voiceData, REDSOUND_STREAM_RIGHT_CHANNEL)->m_targetPitch = 0;
						RedStreamVoiceDataGetChannel(voiceData, REDSOUND_STREAM_RIGHT_CHANNEL)->m_flags |= REDSOUND_VOICE_FLAGS_PITCH_DIRTY;
					}
				}
			} else if (voiceData->m_axVoice != REDSOUND_AX_VOICE_NONE) {
				unsigned int resumePitch = PitchCompute(REDSOUND_STREAM_BASE_PITCH, 0, streamData->m_header.m_pitch, 0);
				volume = streamData->m_volume.m_value >> REDSOUND_FIXED_SHIFT;
				if (streamData->m_header.m_channelCount == REDSOUND_STREAM_STEREO_CHANNEL_COUNT) {
					voiceData->m_targetPitch = resumePitch;
					voiceData->m_flags |= REDSOUND_VOICE_FLAGS_PITCH_DIRTY;
					RedStreamVoiceDataGetChannel(voiceData, REDSOUND_STREAM_RIGHT_CHANNEL)->m_targetPitch = resumePitch;
					RedStreamVoiceDataGetChannel(voiceData, REDSOUND_STREAM_RIGHT_CHANNEL)->m_flags |= REDSOUND_VOICE_FLAGS_PITCH_DIRTY;
				} else {
					pan = streamData->m_pan.m_value >> REDSOUND_FIXED_SHIFT;
					voiceData->m_targetPitch = resumePitch;
					voiceData->m_flags |= REDSOUND_VOICE_FLAGS_PITCH_DIRTY;
				}
			}
		}
		streamData++;
	} while (streamData < RedStreamDataGetEnd());
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
	RedStreamDATA* streamData = RedStreamDataGetBegin();
	do {
		RedVoiceDATA* voiceData;
		int streamResult;
		if (streamData->m_state == REDSOUND_STREAM_STATE_PLAYING) {
			voiceData = streamData->m_voiceData;
			if (voiceData->m_axVoice != REDSOUND_AX_VOICE_NONE) {
				if (voiceData->m_axVoice->priority == 0) {
					_StreamStop(streamData);
				} else {
					int currentBufferSampleStart = RedStreamGetCurrentAramSampleStart(streamData);
					int axSamplePosition = voiceData->m_axVoice->pb.addr.currentAddressHi;
					axSamplePosition <<= REDSOUND_STREAM_AX_CURRENT_ADDRESS_HI_SHIFT;
					axSamplePosition |= voiceData->m_axVoice->pb.addr.currentAddressLo;
					if ((axSamplePosition >= currentBufferSampleStart) &&
					    (axSamplePosition < RedStreamAramSampleGetEnd(currentBufferSampleStart))) {
						streamResult = 0;
						if (RedStreamHeaderHasNoLoop(&streamData->m_header)) {
							streamData->m_header.m_loopEnd = streamData->m_header.m_loopEnd - REDSOUND_STREAM_SAMPLE_ADVANCE;
							if (streamData->m_header.m_loopEnd < 1) {
								_StreamStop(streamData);
								streamResult = 1;
							}
						}
						streamData->m_fileCursor += streamData->m_header.m_channelCount * REDSOUND_STREAM_PAGE_SIZE;
						if (streamData->m_fileCursor >= streamData->m_fileSize) {
							streamData->m_fileCursor -= streamData->m_fileSize;
						}

						if (streamResult == 0) {
							if (streamData->m_streamCursorBase != 0) {
								streamResult = REDSOUND_STREAM_BUFFER_SIDE_A;
								streamData->m_streamCursorBase = 0;
							} else {
								streamResult = REDSOUND_STREAM_BUFFER_SIDE_B;
								streamData->m_streamCursorBase = REDSOUND_STREAM_PAGE_SIZE;
							}

							if (RedStreamHeaderHasNoLoop(&streamData->m_header)) {
								streamResult = _ArrangeStreamDataNoLoop(streamData, streamResult, REDSOUND_STREAM_PAGE_SIZE);
							} else {
								streamResult = _ArrangeStreamDataLoop(streamData, streamResult, REDSOUND_STREAM_PAGE_SIZE);
							}
							streamData->m_dmaId = streamResult;
						}
					}

					streamResult = 0;
					if (streamData->m_pan.m_stepCount != 0) {
						streamResult += 1;
						streamData->m_pan.m_stepCount -= 1;
						streamData->m_pan.m_value += streamData->m_pan.m_step;
					}
					if (streamData->m_volume.m_stepCount != 0) {
						streamResult += 1;
						streamData->m_volume.m_stepCount -= 1;
						streamData->m_volume.m_value += streamData->m_volume.m_step;
					}
					if (streamResult != 0) {
						if (streamData->m_header.m_channelCount == REDSOUND_STREAM_STEREO_CHANNEL_COUNT) {
							SetVoiceVolumeMix(voiceData, REDSOUND_STREAM_SILENT_PAN,
							                  streamData->m_volume.m_value >> REDSOUND_FIXED_SHIFT);
							voiceData += REDSOUND_STREAM_RIGHT_CHANNEL;
							SetVoiceVolumeMix(voiceData, REDSOUND_VOLUME_MAX,
							                  streamData->m_volume.m_value >> REDSOUND_FIXED_SHIFT);
						} else {
							SetVoiceVolumeMix(voiceData, streamData->m_pan.m_value >> REDSOUND_FIXED_SHIFT,
							                  streamData->m_volume.m_value >> REDSOUND_FIXED_SHIFT);
						}
					}
				}
			}
		} else if ((streamData->m_state == REDSOUND_STREAM_STATE_LOADING) &&
		           (RedDmaSearchID(streamData->m_dmaId) == REDSOUND_DMA_SEARCH_NOT_FOUND)) {
			voiceData = streamData->m_voiceData;
			streamData->m_state = REDSOUND_STREAM_STATE_PLAYING;
			voiceData->m_flags |= REDSOUND_VOICE_FLAGS_STREAM_START;
			voiceData->m_waveData = RedStreamGetTrackData(streamData, REDSOUND_STREAM_LEFT_CHANNEL);
			voiceData->m_active = REDSOUND_VOICE_ACTIVE_ON;
			if (streamData->m_header.m_channelCount == REDSOUND_STREAM_STEREO_CHANNEL_COUNT) {
				RedStreamVoiceDataGetChannel(voiceData, REDSOUND_STREAM_RIGHT_CHANNEL)->m_flags |= REDSOUND_VOICE_FLAGS_STREAM_START;
				RedStreamVoiceDataGetChannel(voiceData, REDSOUND_STREAM_RIGHT_CHANNEL)->m_waveData =
				    RedStreamGetTrackData(streamData, REDSOUND_STREAM_RIGHT_CHANNEL);
				RedStreamVoiceDataGetChannel(voiceData, REDSOUND_STREAM_RIGHT_CHANNEL)->m_active = REDSOUND_VOICE_ACTIVE_ON;
			}
		}

		streamData++;
	} while (streamData < RedStreamDataGetEnd());
}
