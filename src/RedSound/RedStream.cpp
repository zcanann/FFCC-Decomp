#include "ffcc/RedSound/RedStream.h"
#include "ffcc/RedSound/RedCommand.h"
#include "ffcc/RedSound/RedDriver.h"
#include "ffcc/RedSound/RedEntry.h"
#include "ffcc/RedSound/RedExecute.h"
#include "ffcc/RedSound/RedMemory.h"
#include "ffcc/RedSound/RedMidiCtrl.h"
#include "ffcc/RedSound/RedGlobals.h"
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

enum RedStreamLayoutSize {
	REDSOUND_STREAM_PAGE_SIZE = 0x1000,
	REDSOUND_STREAM_STEREO_PLANE_SIZE = 0x2000,
	REDSOUND_STREAM_TRANSFER_BUFFER_SIZE = 0x4000,
	REDSOUND_STREAM_SAMPLE_ADVANCE = 0x200,
	REDSOUND_STREAM_ADPCM_HEADER_SIZE = 0x2e,
	REDSOUND_STREAM_INITIAL_LOOP_END = 0x3fff,
};

/*
 * --INFO--
 * PAL Address: 0x801cb93c
 * PAL Size: 68b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
RedStreamDATA* _SearchEmptyStreamData()
{
	RedStreamDATA* streamData = p_Stream;

	for (;;) {
		if (streamData->m_streamId == 0) {
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
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void _StreamStop(RedStreamDATA* streamData)
{
	fflush(__files + 1);
	if (streamData->m_streamId != 0) {
		streamData->m_streamId = 0;
		streamData->m_state = 0;
		if (streamData->m_buffer != 0) {
			RedDelete(streamData->m_buffer);
			streamData->m_buffer = 0;
		}
		if (streamData->m_aramBuffer != 0) {
			RedDeleteA(streamData->m_aramBuffer);
			streamData->m_aramBuffer = 0;
		}
		streamData->m_voiceData->m_flags |= 2;
		streamData->m_track->m_note.m_allocFlags &= -3;
		streamData->m_voiceData->m_stateFlags &= -3;
		streamData->m_voiceData->m_active = 0;
		if (streamData->m_header.m_channelCount == 2) {
			streamData->m_voiceData[1].m_flags |= 2;
			streamData->m_track[1].m_note.m_allocFlags &= -3;
			streamData->m_voiceData[1].m_stateFlags &= -3;
			streamData->m_voiceData[1].m_active = 0;
		}
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int _ArrangeStreamDataNoLoop(RedStreamDATA* stream, int bufferIndex, int byteCount)
{
	unsigned char* dstBuffer;
	RedVoiceDATA* voiceData;
	int dmaDstOffset;
	int dmaID;

	bufferIndex &= 1;

	do {
		dstBuffer = stream->m_buffer + bufferIndex * REDSOUND_STREAM_PAGE_SIZE;
		voiceData = stream->m_voiceData;

		memcpy(dstBuffer, stream->m_fileData + stream->m_readOffset, REDSOUND_STREAM_PAGE_SIZE);
		stream->m_readOffset += REDSOUND_STREAM_PAGE_SIZE;
		if (stream->m_readOffset >= stream->m_fileSize) {
			stream->m_readOffset = 0;
		}

		if (stream->m_header.m_channelCount == 2) {
			memcpy(dstBuffer + REDSOUND_STREAM_STEREO_PLANE_SIZE, stream->m_fileData + stream->m_readOffset, REDSOUND_STREAM_PAGE_SIZE);
			stream->m_readOffset += REDSOUND_STREAM_PAGE_SIZE;
			if (stream->m_readOffset >= stream->m_fileSize) {
				stream->m_readOffset = 0;
			}
		}

		dmaDstOffset = stream->m_aramBuffer + bufferIndex * REDSOUND_STREAM_PAGE_SIZE;
		dmaID = RedDmaEntry(0x8001, 0, (int)dstBuffer, dmaDstOffset, REDSOUND_STREAM_PAGE_SIZE, 0, 0);

		if ((bufferIndex == 0) && (voiceData->m_axVoice != 0)) {
			voiceData->m_axVoice->pb.adpcmLoop.loop_pred_scale = (unsigned short)*dstBuffer;
			voiceData->m_axVoice->pb.adpcmLoop.loop_yn1 = voiceData->m_axVoice->pb.adpcmLoop.loop_yn2 = 0;
			voiceData->m_axVoice->sync |= 0x100000;
		}

		if (stream->m_header.m_channelCount == 2) {
			dstBuffer += REDSOUND_STREAM_STEREO_PLANE_SIZE;
			dmaDstOffset += REDSOUND_STREAM_STEREO_PLANE_SIZE;
			voiceData += 1;
			dmaID = RedDmaEntry(0x8001, 0, (int)dstBuffer, dmaDstOffset, REDSOUND_STREAM_PAGE_SIZE, 0, 0);
			if ((bufferIndex == 0) && (voiceData->m_axVoice != 0)) {
				voiceData->m_axVoice->pb.adpcmLoop.loop_pred_scale = (unsigned short)*dstBuffer;
				voiceData->m_axVoice->pb.adpcmLoop.loop_yn1 = voiceData->m_axVoice->pb.adpcmLoop.loop_yn2 = 0;
				voiceData->m_axVoice->sync |= 0x100000;
			}
		}

		byteCount -= REDSOUND_STREAM_PAGE_SIZE;
		bufferIndex ^= 1;
		stream->m_streamCursor += REDSOUND_STREAM_SAMPLE_ADVANCE;
	} while (0 < byteCount);

	return dmaID;
}

/*
 * --INFO--
 * Address:	801cbc6c
 * Size:	856b
 */
int _ArrangeStreamDataLoop(RedStreamDATA* stream, int bufferIndex, int byteCount)
{
	unsigned int* puVar3;
	unsigned char* pbVar4;
	unsigned char* pbVar5;
	unsigned char* pbVar6;
	unsigned int* puVar7;
	RedVoiceDATA* voiceData;
	int dmaID;

	bufferIndex = bufferIndex & 1;
	
	if (stream->m_header.m_channelCount == 2) {
		do {
			pbVar6 = stream->m_buffer + bufferIndex * REDSOUND_STREAM_PAGE_SIZE;
			voiceData = stream->m_voiceData;
			puVar7 = (unsigned int*)(stream->m_fileData + stream->m_readOffset);
			pbVar4 = pbVar6 + REDSOUND_STREAM_STEREO_PLANE_SIZE;
			puVar3 = puVar7 + 0x400;
			pbVar5 = pbVar6;
			
			do {
				*(unsigned int*)pbVar5 = *puVar7;
				*(unsigned int*)(pbVar5 + 4) = puVar7[1];
				pbVar5 = pbVar5 + 8;
				*(unsigned int*)pbVar4 = puVar7[2];
				*(unsigned int*)(pbVar4 + 4) = puVar7[3];
				puVar7 = puVar7 + 4;
				pbVar4 = pbVar4 + 8;
			} while (puVar7 < puVar3);
			
			stream->m_readOffset = stream->m_readOffset + REDSOUND_STREAM_PAGE_SIZE;
			if (stream->m_readOffset >= stream->m_fileSize) {
				stream->m_readOffset = 0;
			}
			
			puVar7 = (unsigned int*)(stream->m_fileData + stream->m_readOffset);
			puVar3 = puVar7 + 0x400;
			
			do {
				*(unsigned int*)pbVar5 = *puVar7;
				*(unsigned int*)(pbVar5 + 4) = puVar7[1];
				pbVar5 = pbVar5 + 8;
				*(unsigned int*)pbVar4 = puVar7[2];
				*(unsigned int*)(pbVar4 + 4) = puVar7[3];
				puVar7 = puVar7 + 4;
				pbVar4 = pbVar4 + 8;
			} while (puVar7 < puVar3);
			
			stream->m_readOffset = stream->m_readOffset + REDSOUND_STREAM_PAGE_SIZE;
			if (stream->m_readOffset >= stream->m_fileSize) {
				stream->m_readOffset = 0;
			}
			
			dmaID = RedDmaEntry(0x8001, 0, (int)pbVar6, stream->m_aramBuffer + bufferIndex * REDSOUND_STREAM_PAGE_SIZE, REDSOUND_STREAM_PAGE_SIZE, 0, 0);
			dmaID = RedDmaEntry(0x8001, 0, (int)(pbVar6 + REDSOUND_STREAM_STEREO_PLANE_SIZE), stream->m_aramBuffer + (bufferIndex + 2) * REDSOUND_STREAM_PAGE_SIZE, REDSOUND_STREAM_PAGE_SIZE, 0, 0);
			
			if ((bufferIndex == 0) && (voiceData->m_axVoice != 0)) {
				voiceData->m_axVoice->pb.adpcmLoop.loop_pred_scale = (unsigned short)*pbVar6;
				voiceData->m_axVoice->pb.adpcmLoop.loop_yn1 = voiceData->m_axVoice->pb.adpcmLoop.loop_yn2 = 0;
				voiceData->m_axVoice->sync |= 0x100000;
				voiceData[1].m_axVoice->pb.adpcmLoop.loop_pred_scale = (unsigned short)pbVar6[REDSOUND_STREAM_STEREO_PLANE_SIZE];
				voiceData[1].m_axVoice->pb.adpcmLoop.loop_yn1 = voiceData[1].m_axVoice->pb.adpcmLoop.loop_yn2 = 0;
				voiceData[1].m_axVoice->sync |= 0x100000;
			}
			
			bufferIndex = bufferIndex ^ 1;
			byteCount = byteCount + -REDSOUND_STREAM_PAGE_SIZE;
			stream->m_streamCursor = stream->m_streamCursor + REDSOUND_STREAM_SAMPLE_ADVANCE;
			
			if (stream->m_streamCursor >= stream->m_header.m_loopEnd) {
				stream->m_streamCursor = stream->m_streamCursor - stream->m_header.m_loopEnd;
				stream->m_streamCursor = stream->m_streamCursor + stream->m_header.m_loopStart;
			}
		} while (0 < byteCount);
	} else {
		do {
			pbVar5 = stream->m_buffer + bufferIndex * REDSOUND_STREAM_PAGE_SIZE;
			voiceData = stream->m_voiceData;
			memcpy(pbVar5, stream->m_fileData + stream->m_readOffset, REDSOUND_STREAM_PAGE_SIZE);
			stream->m_readOffset = stream->m_readOffset + REDSOUND_STREAM_PAGE_SIZE;
			
			if (stream->m_readOffset >= stream->m_fileSize) {
				stream->m_readOffset = 0;
			}
			
			dmaID = RedDmaEntry(0x8001, 0, (int)pbVar5, stream->m_aramBuffer + bufferIndex * REDSOUND_STREAM_PAGE_SIZE, REDSOUND_STREAM_PAGE_SIZE, 0, 0);
			
			if ((bufferIndex == 0) && (voiceData->m_axVoice != 0)) {
				voiceData->m_axVoice->pb.adpcmLoop.loop_pred_scale = (unsigned short)*pbVar5;
				voiceData->m_axVoice->pb.adpcmLoop.loop_yn1 = voiceData->m_axVoice->pb.adpcmLoop.loop_yn2 = 0;
				voiceData->m_axVoice->sync |= 0x100000;
			}
			
			bufferIndex = bufferIndex ^ 1;
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
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void StreamStop(int streamID)
{
	volatile RedStreamDATA* streamData = p_Stream;

	do {
		if ((streamData->m_streamId != 0) && ((streamID == -1) || (streamID == streamData->m_streamId))) {
			_StreamStop((RedStreamDATA*)streamData);
		}
		streamData++;
	} while (streamData < p_Stream + REDSOUND_STREAM_COUNT);
}

/*
 * --INFO--
 * PAL Address: 0x801cc034
 * PAL Size: 1280b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int StreamPlay(int streamID, void* streamHeader, int fileSize, int pan, int volume)
{
	u32 amemSize;
	u32 arOffset;
	int pitch;
	int iVar2;
	int sampleOffset;
	u8* headerData;
	RedStreamDATA* streamData;
	RedVoiceDATA* voice;

	streamData = _SearchEmptyStreamData();
	if (streamData != 0) {

	memcpy(&streamData->m_header, streamHeader, 0x20);
	streamData->m_track = SearchSeEmptyTrack(streamData->m_header.m_channelCount, 0xff, 0);
	streamData->m_buffer = (u8*)RedNew(REDSOUND_STREAM_TRANSFER_BUFFER_SIZE);
	amemSize = streamData->m_header.m_channelCount << 0xd;
	if (c_RedMemory.GetABufferSize() < 0x800000) {
		arOffset = 0;
	} else {
		arOffset = 0x300000;
	}
	streamData->m_aramBuffer = RedNewA(amemSize, 0, arOffset);
	if (streamData->m_aramBuffer == 0) {
		c_RedEntry.WaveOldClear(0, arOffset);
		streamData->m_aramBuffer = RedNewA(amemSize, 0, arOffset);
	}

	if ((streamData->m_track != 0) && (streamData->m_buffer != 0) && (streamData->m_aramBuffer != 0)) {
		sampleOffset = REDSOUND_STREAM_PAGE_SIZE;
		headerData = (u8*)streamHeader + 0x20;
		*(short*)((int)streamHeader + 0x42) = (short)*(char*)((int)streamHeader + sampleOffset);
		*(unsigned short*)((int)streamHeader + 0x44) = *(unsigned short*)((int)streamHeader + 0x46) = 0;
		if (streamData->m_header.m_channelCount == 2) {
			if (streamData->m_header.m_loopStart < 0) {
				sampleOffset += REDSOUND_STREAM_PAGE_SIZE;
			} else {
				sampleOffset += 8;
			}
			*(short*)(headerData + 0x50) = (short)*(char*)((int)streamHeader + sampleOffset);
			*(unsigned short*)(headerData + 0x52) = *(unsigned short*)(headerData + 0x54) = 0;
		}

		streamData->m_streamId = streamID;
		streamData->m_fileCursor = 0;
		streamData->m_readOffset = REDSOUND_STREAM_PAGE_SIZE;
		streamData->m_streamCursor = 0;
		streamData->m_voiceData = p_VoiceData + streamData->m_track->m_trackNo;
		streamData->m_fileData = (u8*)streamHeader;
		streamData->m_fileSize = fileSize;
		if (volume != 0) {
			volume = ((volume + 1) * 0x100 - 1) * 0x1000;
		}
		streamData->m_volume = volume;
		streamData->m_volumeStepCount = 0;
		pitch = PitchCompute(0x3c00000, 0, streamData->m_header.m_pitch, 0);
		iVar2 = 0;
		do {
			voice = streamData->m_voiceData + iVar2;
			voice->m_track = streamData->m_track + iVar2;
			voice->m_track->m_note.m_allocFlags |= 2;
			voice->m_stateFlags |= 2;
			voice->m_voiceSwitch = 0xc01;
			if (streamData->m_header.m_flags != 0) {
				voice->m_voiceSwitch |= 0x3000;
			}
			voice->m_track->m_voiceSwitch = 1;
			voice->m_envelopeLevel = 0x8000;
			voice->m_waveData = &streamData->m_trackData[iVar2];
			voice->m_targetPitch = pitch;
			voice->m_track->m_reverbDepth = p_ReverbDepth[1].m_depth;
			voice->m_track->m_reverbDepthDelta = 0;
			if (streamData->m_header.m_channelCount == 2) {
				if (iVar2 == 0) {
					streamData->m_pan = 0;
					streamData->m_panStepCount = 0;
				} else {
					streamData->m_pan = 0x7f000;
					streamData->m_panStepCount = 0;
				}
			} else {
				streamData->m_pan = pan << 0xc;
				streamData->m_panStepCount = 0;
			}
			SetVoiceVolumeMix(streamData->m_voiceData + iVar2, streamData->m_pan >> 0xc, streamData->m_volume >> 0xc);
			(streamData->m_track + iVar2)->m_waveBase = streamData->m_aramBuffer + iVar2 * REDSOUND_STREAM_STEREO_PLANE_SIZE;
			memset(&streamData->m_trackData[iVar2], 0, sizeof(RedWaveDATA));
			memcpy(streamData->m_trackData[iVar2].m_adpcmData, headerData + iVar2 * REDSOUND_STREAM_ADPCM_HEADER_SIZE, REDSOUND_STREAM_ADPCM_HEADER_SIZE);
			voice->m_adsrLevel[0] = voice->m_adsrLevel[1] = voice->m_adsrLevel[2] = 0;
			voice->m_adsrLevel[3] = 0x7f;
			voice->m_adsrTime[0] = voice->m_adsrTime[1] = voice->m_adsrTime[2] = 0;
			voice->m_adsrTime[3] = 10;
			streamData->m_trackData[iVar2].m_sampleStart = 0;
			streamData->m_trackData[iVar2].m_loopEnd = REDSOUND_STREAM_INITIAL_LOOP_END;
			streamData->m_trackData[iVar2].m_loopStart = 2;
			iVar2 += 1;
		} while (iVar2 < streamData->m_header.m_channelCount);

		int dmaID;
		if (streamData->m_header.m_loopStart < 0) {
			dmaID = _ArrangeStreamDataNoLoop(streamData, 0, REDSOUND_STREAM_STEREO_PLANE_SIZE);
		} else {
			dmaID = _ArrangeStreamDataLoop(streamData, 0, REDSOUND_STREAM_STEREO_PLANE_SIZE);
		}
		streamData->m_dmaId = dmaID;
		streamData->m_streamCursorBase = REDSOUND_STREAM_PAGE_SIZE;
		streamData->m_state = 3;
	} else {
		if (m_ReportPrint != 0) {
			OSReport(sRedStreamBufferDidntSecureFmt, sRedStreamLogPrefix, sRedStreamLogErrorColor, sRedStreamLogReset);
			fflush(__files + 1);
		}
		if (streamData->m_buffer != 0) {
			RedDelete(streamData->m_buffer);
		} else {
			if (m_ReportPrint != 0) {
				OSReport(sRedStreamMainMemoryDidntCreateFmt,
				         sRedStreamLogPrefix, sRedStreamLogWarnColor, REDSOUND_STREAM_TRANSFER_BUFFER_SIZE,
				         sRedStreamLogReset);
				fflush(__files + 1);
			}
		}
		if (streamData->m_aramBuffer != 0) {
			RedDeleteA(streamData->m_aramBuffer);
		} else {
			if (m_ReportPrint != 0) {
				OSReport(sRedStreamAramMemoryDidntCreateFmt,
				         sRedStreamLogPrefix, sRedStreamLogWarnColor, streamData->m_header.m_channelCount << 0xd,
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
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void SetStreamVolume(int streamID, int volume, int frameCount)
{
	volatile RedStreamDATA* streamData;

	if (frameCount < 1) {
		frameCount = 1;
	} else {
		frameCount *= 200;
		frameCount /= 60;
	}

	volume &= 0x7f;
	if (volume != 0) {
		volume++;
		volume <<= 8;
		volume--;
		volume <<= 12;
		volume |= 0x800;
	}

	streamData = p_Stream;
	do {
		if ((streamData->m_streamId != 0) && ((streamID == -1) || (streamID == streamData->m_streamId))) {
			if (frameCount > 0) {
				int delta = volume - streamData->m_volume;
				streamData->m_volumeStep = delta / frameCount;
				streamData->m_volumeStepCount = frameCount;
			} else {
				streamData->m_volume = volume;
				streamData->m_volumeStepCount = 0;
			}
		}
		streamData++;
	} while (streamData < p_Stream + REDSOUND_STREAM_COUNT);
}

/*
 * --INFO--
 * PAL Address: 0x801cc600
 * PAL Size: 392b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void StreamPause(int streamID, int pause)
{
	RedVoiceDATA* voiceData;
	RedStreamDATA* streamData;
	int volume;
	int pan;

	if (m_ReportPrint != 0) {
		if (pause == 1) {
			OSReport(sRedStreamPauseOnFmt, sRedStreamLogPrefix, streamID);
		} else {
			OSReport(sRedStreamPauseOffFmt, sRedStreamLogPrefix, streamID);
		}
		fflush(__files + 1);
	}
	streamData = p_Stream;
	do {
		if ((streamData->m_streamId != 0) && ((streamID == -1) || (streamID == streamData->m_streamId))) {
			voiceData = streamData->m_voiceData;
			if (pause == 1) {
				if (voiceData->m_axVoice != 0) {
					voiceData->m_targetPitch = 0;
					voiceData->m_flags |= 0x10;
					if (streamData->m_header.m_channelCount == 2) {
						voiceData[1].m_targetPitch = 0;
						voiceData[1].m_flags |= 0x10;
					}
				}
			} else if (voiceData->m_axVoice != 0) {
				unsigned int pitch = PitchCompute(0x3c00000, 0, streamData->m_header.m_pitch, 0);
				short channelCount = streamData->m_header.m_channelCount;
				volume = streamData->m_volume >> 0xc;
				if (channelCount == 2) {
					voiceData->m_targetPitch = pitch;
					voiceData->m_flags |= 0x10;
					voiceData[1].m_targetPitch = pitch;
					voiceData[1].m_flags |= 0x10;
				} else {
					pan = streamData->m_pan >> 0xc;
					voiceData->m_targetPitch = pitch;
					voiceData->m_flags |= 0x10;
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
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void StreamControl()
{
	RedStreamDATA* streamData = p_Stream;
	do {
		RedVoiceDATA* voiceData;
		if (streamData->m_state == 1) {
			voiceData = streamData->m_voiceData;
			if (voiceData->m_axVoice != 0) {
				if (voiceData->m_axVoice->priority == 0) {
					_StreamStop(streamData);
				} else {
					int samplePos = voiceData->m_axVoice->pb.addr.currentAddressHi;
					int sampleStart = (streamData->m_aramBuffer + streamData->m_streamCursorBase) * 2;
					samplePos <<= 16;
					samplePos |= voiceData->m_axVoice->pb.addr.currentAddressLo;
					if ((samplePos >= sampleStart) && (samplePos < sampleStart + REDSOUND_STREAM_STEREO_PLANE_SIZE)) {
						int stopped = 0;
						if (streamData->m_header.m_loopStart < 0) {
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
								side = 0;
								streamData->m_streamCursorBase = 0;
							} else {
								side = 1;
								streamData->m_streamCursorBase = REDSOUND_STREAM_PAGE_SIZE;
							}

							if (streamData->m_header.m_loopStart < 0) {
								dmaID = _ArrangeStreamDataNoLoop(streamData, side, REDSOUND_STREAM_PAGE_SIZE);
							} else {
								dmaID = _ArrangeStreamDataLoop(streamData, side, REDSOUND_STREAM_PAGE_SIZE);
							}
							streamData->m_dmaId = dmaID;
						}
					}

					int changed = 0;
					if (streamData->m_panStepCount != 0) {
						changed += 1;
						streamData->m_panStepCount -= 1;
						streamData->m_pan += streamData->m_panStep;
					}
					if (streamData->m_volumeStepCount != 0) {
						changed += 1;
						streamData->m_volumeStepCount -= 1;
						streamData->m_volume += streamData->m_volumeStep;
					}
					if (changed != 0) {
						if (streamData->m_header.m_channelCount == 2) {
							SetVoiceVolumeMix(voiceData, 0, streamData->m_volume >> 0xc);
							voiceData += 1;
							SetVoiceVolumeMix(voiceData, 0x7f, streamData->m_volume >> 0xc);
						} else {
							SetVoiceVolumeMix(voiceData, streamData->m_pan >> 0xc, streamData->m_volume >> 0xc);
						}
					}
				}
			}
		} else if ((streamData->m_state == 3) && (RedDmaSearchID(streamData->m_dmaId) == 0)) {
			voiceData = streamData->m_voiceData;
			streamData->m_state = 1;
			voiceData->m_flags |= 0x19;
			voiceData->m_waveData = streamData->m_trackData;
			voiceData->m_active = 1;
			if (streamData->m_header.m_channelCount == 2) {
				voiceData[1].m_flags |= 0x19;
				voiceData[1].m_waveData = &streamData->m_trackData[1];
				voiceData[1].m_active = 1;
			}
		}

		streamData++;
	} while (streamData < p_Stream + REDSOUND_STREAM_COUNT);
}
