#include "ffcc/RedSound/RedStream.h"
#include "ffcc/RedSound/RedCommand.h"
#include "ffcc/RedSound/RedDriver.h"
#include "ffcc/RedSound/RedEntry.h"
#include "ffcc/RedSound/RedExecute.h"
#include "ffcc/RedSound/RedMemory.h"
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

		if (!(streamData < p_Stream + 4)) {
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
		*(unsigned int*)(streamData->m_voiceData + 0x90) |= 2;
		*(unsigned char*)(streamData->m_track + 0x26) &= -3;
		*(unsigned char*)(streamData->m_voiceData + 0x1a) &= -3;
		*(int*)(streamData->m_voiceData + 0x8c) = 0;
		if (streamData->m_channelCount == 2) {
			*(unsigned int*)(streamData->m_voiceData + 0x150) |= 2;
			*(unsigned char*)(streamData->m_track + 0x17a) &= -3;
			*(unsigned char*)(streamData->m_voiceData + 0xda) &= -3;
			*(int*)(streamData->m_voiceData + 0x14c) = 0;
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
	int streamStruct;
	int dmaDstOffset;
	int dmaID;

	bufferIndex &= 1;

	do {
		dstBuffer = (unsigned char*)((int)stream->m_buffer + bufferIndex * 0x1000);
		streamStruct = stream->m_voiceData;

		memcpy(dstBuffer, (void*)(stream->m_fileData + stream->m_readOffset), 0x1000);
		stream->m_readOffset += 0x1000;
		if (stream->m_readOffset >= stream->m_fileSize) {
			stream->m_readOffset = 0;
		}

		if (stream->m_channelCount == 2) {
			memcpy(dstBuffer + 0x2000, (void*)(stream->m_fileData + stream->m_readOffset), 0x1000);
			stream->m_readOffset += 0x1000;
			if (stream->m_readOffset >= stream->m_fileSize) {
				stream->m_readOffset = 0;
			}
		}

		dmaDstOffset = stream->m_aramBuffer + bufferIndex * 0x1000;
		dmaID = RedDmaEntry(0x8001, 0, (int)dstBuffer, dmaDstOffset, 0x1000, 0, 0);

		if ((bufferIndex == 0) && (*(void**)(streamStruct + 0x14) != 0)) {
			*(unsigned short*)(*(int*)(streamStruct + 0x14) + 0x1ec) = (unsigned short)*dstBuffer;
			*(unsigned short*)(*(int*)(streamStruct + 0x14) + 0x1ee) =
			    *(unsigned short*)(*(int*)(streamStruct + 0x14) + 0x1f0) = 0;
			*(unsigned int*)(*(int*)(streamStruct + 0x14) + 0x1c) |= 0x100000;
		}

		if (stream->m_channelCount == 2) {
			dstBuffer += 0x2000;
			dmaDstOffset += 0x2000;
			streamStruct += 0xc0;
			dmaID = RedDmaEntry(0x8001, 0, (int)dstBuffer, dmaDstOffset, 0x1000, 0, 0);
			if ((bufferIndex == 0) && (*(void**)(streamStruct + 0x14) != 0)) {
				*(unsigned short*)(*(int*)(streamStruct + 0x14) + 0x1ec) = (unsigned short)*dstBuffer;
				*(unsigned short*)(*(int*)(streamStruct + 0x14) + 0x1ee) =
				    *(unsigned short*)(*(int*)(streamStruct + 0x14) + 0x1f0) = 0;
				*(unsigned int*)(*(int*)(streamStruct + 0x14) + 0x1c) |= 0x100000;
			}
		}

		byteCount -= 0x1000;
		bufferIndex ^= 1;
		stream->m_streamCursor += 0x200;
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
	int iVar8;
	int dmaID;

	bufferIndex = bufferIndex & 1;
	
	if (stream->m_channelCount == 2) {
		do {
			pbVar6 = (unsigned char*)((int)stream->m_buffer + bufferIndex * 0x1000);
			iVar8 = stream->m_voiceData;
			puVar7 = (unsigned int*)(stream->m_fileData + stream->m_readOffset);
			pbVar4 = pbVar6 + 0x2000;
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
			
			stream->m_readOffset = stream->m_readOffset + 0x1000;
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
			
			stream->m_readOffset = stream->m_readOffset + 0x1000;
			if (stream->m_readOffset >= stream->m_fileSize) {
				stream->m_readOffset = 0;
			}
			
			dmaID = RedDmaEntry(0x8001, 0, (int)pbVar6, stream->m_aramBuffer + bufferIndex * 0x1000, 0x1000, 0, 0);
			dmaID = RedDmaEntry(0x8001, 0, (int)(pbVar6 + 0x2000), stream->m_aramBuffer + (bufferIndex + 2) * 0x1000, 0x1000, 0, 0);
			
			if ((bufferIndex == 0) && (*(void**)(iVar8 + 0x14) != 0)) {
				int zero = 0;
				*(unsigned short*)(*(int*)(iVar8 + 0x14) + 0x1ec) = (unsigned short)*pbVar6;
				*(unsigned short*)(*(int*)(iVar8 + 0x14) + 0x1f0) = zero;
				*(unsigned short*)(*(int*)(iVar8 + 0x14) + 0x1ee) = zero;
				*(unsigned int*)(*(int*)(iVar8 + 0x14) + 0x1c) = *(unsigned int*)(*(int*)(iVar8 + 0x14) + 0x1c) | 0x100000;
				*(unsigned short*)(*(int*)(iVar8 + 0xd4) + 0x1ec) = (unsigned short)pbVar6[0x2000];
				*(unsigned short*)(*(int*)(iVar8 + 0xd4) + 0x1f0) = zero;
				*(unsigned short*)(*(int*)(iVar8 + 0xd4) + 0x1ee) = zero;
				*(unsigned int*)(*(int*)(iVar8 + 0xd4) + 0x1c) = *(unsigned int*)(*(int*)(iVar8 + 0xd4) + 0x1c) | 0x100000;
			}
			
			bufferIndex = bufferIndex ^ 1;
			byteCount = byteCount + -0x1000;
			stream->m_streamCursor = stream->m_streamCursor + 0x200;
			
			if (stream->m_streamCursor >= stream->m_loopEnd) {
				stream->m_streamCursor = stream->m_streamCursor - stream->m_loopEnd;
				stream->m_streamCursor = stream->m_streamCursor + stream->m_loopStart;
			}
		} while (0 < byteCount);
	} else {
		do {
			pbVar5 = (unsigned char*)((int)stream->m_buffer + bufferIndex * 0x1000);
			iVar8 = stream->m_voiceData;
			memcpy(pbVar5, (void*)(stream->m_fileData + stream->m_readOffset), 0x1000);
			stream->m_readOffset = stream->m_readOffset + 0x1000;
			
			if (stream->m_readOffset >= stream->m_fileSize) {
				stream->m_readOffset = 0;
			}
			
			dmaID = RedDmaEntry(0x8001, 0, (int)pbVar5, stream->m_aramBuffer + bufferIndex * 0x1000, 0x1000, 0, 0);
			
			if ((bufferIndex == 0) && (*(void**)(iVar8 + 0x14) != 0)) {
				int zero = 0;
				*(unsigned short*)(*(int*)(iVar8 + 0x14) + 0x1ec) = (unsigned short)*pbVar5;
				*(unsigned short*)(*(int*)(iVar8 + 0x14) + 0x1f0) = zero;
				*(unsigned short*)(*(int*)(iVar8 + 0x14) + 0x1ee) = zero;
				*(unsigned int*)(*(int*)(iVar8 + 0x14) + 0x1c) = *(unsigned int*)(*(int*)(iVar8 + 0x14) + 0x1c) | 0x100000;
			}
			
			bufferIndex = bufferIndex ^ 1;
			byteCount = byteCount + -0x1000;
			stream->m_streamCursor = stream->m_streamCursor + 0x200;
			
			if (stream->m_streamCursor >= stream->m_loopEnd) {
				stream->m_streamCursor = stream->m_streamCursor - stream->m_loopEnd;
				stream->m_streamCursor = stream->m_streamCursor + stream->m_loopStart;
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
	} while (streamData < p_Stream + 4);
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
	int amemSize;
	int arOffset;
	int pitch;
	int iVar2;
	int sampleOffset;
	u8* headerData;
	RedStreamDATA* streamData;
	int* voice;

	streamData = _SearchEmptyStreamData();
	if (streamData != 0) {

	memcpy(streamData->m_header, streamHeader, 0x20);
	streamData->m_track = (int)SearchSeEmptyTrack(streamData->m_channelCount, 0xff, 0);
	streamData->m_buffer = (void*)RedNew(0x4000);
	amemSize = streamData->m_channelCount << 0xd;
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
		sampleOffset = 0x1000;
		*(short*)((int)streamHeader + 0x42) = (short)*(char*)((int)streamHeader + sampleOffset);
		*(unsigned short*)((int)streamHeader + 0x46) = 0;
		*(unsigned short*)((int)streamHeader + 0x44) = 0;
		headerData = (u8*)streamHeader + 0x20;
		if (streamData->m_channelCount == 2) {
			if (streamData->m_loopStart < 0) {
				sampleOffset += 0x1000;
			} else {
				sampleOffset += 8;
			}
			*(short*)(headerData + 0x50) = (short)*(char*)((int)streamHeader + sampleOffset);
			*(unsigned short*)(headerData + 0x54) = 0;
			*(unsigned short*)(headerData + 0x52) = 0;
		}

		streamData->m_streamId = streamID;
		streamData->m_fileCursor = 0;
		streamData->m_readOffset = 0x1000;
		streamData->m_streamCursor = 0;
		streamData->m_voiceData = (int)p_VoiceData + *(char*)(streamData->m_track + 0x14e) * 0xc0;
		streamData->m_fileData = (int)streamHeader;
		streamData->m_fileSize = fileSize;
		if (volume != 0) {
			volume = ((volume + 1) * 0x100 - 1) * 0x1000;
		}
		streamData->m_volume = volume;
		streamData->m_volumeStepCount = 0;
		pitch = PitchCompute(0x3c00000, 0, streamData->m_pitch, 0);
		iVar2 = 0;
		do {
			voice = (int*)(streamData->m_voiceData + iVar2 * 0xc0);
			*voice = streamData->m_track + iVar2 * 0x154;
			*(unsigned char*)(*voice + 0x26) |= 2;
			*(unsigned char*)((int)voice + 0x1a) |= 2;
			voice[0x25] = 0xc01;
			if (*(short*)(streamData + 0xb) != 0) {
				voice[0x25] |= 0x3000;
			}
			*(int*)(*voice + 0xfc) = 1;
			voice[0x2c] = 0x8000;
			voice[1] = (int)streamData->m_trackData[iVar2];
			voice[0x27] = pitch;
			*(int*)(*voice + 0x68) = *(int*)((int)p_ReverbDepth + 0xc);
			*(int*)(*voice + 0x70) = 0;
			if (streamData->m_channelCount == 2) {
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
			SetVoiceVolumeMix((RedVoiceDATA*)(streamData->m_voiceData + iVar2 * 0xc0), streamData->m_pan >> 0xc, streamData->m_volume >> 0xc);
			*(int*)(streamData->m_track + iVar2 * 0x154 + 0x11c) = streamData->m_aramBuffer + iVar2 * 0x2000;
			memset(streamData->m_trackData[iVar2], 0, 0x60);
			memcpy(streamData->m_trackData[iVar2] + 0x22, headerData + iVar2 * 0x2e, 0x2e);
			*(unsigned char*)((int)voice + 0x5a) = 0;
			*(unsigned char*)((int)voice + 0x59) = 0;
			*(unsigned char*)(voice + 0x16) = 0;
			*(unsigned char*)((int)voice + 0x5b) = 0x7f;
			*(unsigned short*)(voice + 0x15) = 0;
			*(unsigned short*)((int)voice + 0x52) = 0;
			*(unsigned short*)(voice + 0x14) = 0;
			*(unsigned short*)((int)voice + 0x56) = 10;
			*(int*)(streamData->m_trackData[iVar2] + 4) = 0;
			*(int*)(streamData->m_trackData[iVar2] + 0xc) = 0x3fff;
			*(int*)(streamData->m_trackData[iVar2] + 8) = 2;
			iVar2 += 1;
		} while (iVar2 < streamData->m_channelCount);

		int dmaID;
		if (streamData->m_loopStart < 0) {
			dmaID = _ArrangeStreamDataNoLoop(streamData, 0, 0x2000);
		} else {
			dmaID = _ArrangeStreamDataLoop(streamData, 0, 0x2000);
		}
		streamData->m_dmaId = dmaID;
		streamData->m_streamCursorBase = 0x1000;
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
				         sRedStreamLogPrefix, sRedStreamLogWarnColor, 0x4000,
				         sRedStreamLogReset);
				fflush(__files + 1);
			}
		}
		if (streamData->m_aramBuffer != 0) {
			RedDeleteA(streamData->m_aramBuffer);
		} else {
			if (m_ReportPrint != 0) {
				OSReport(sRedStreamAramMemoryDidntCreateFmt,
				         sRedStreamLogPrefix, sRedStreamLogWarnColor, streamData->m_channelCount << 0xd,
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
	} while (streamData < p_Stream + 4);
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
	unsigned int voiceData;
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
			voiceData = (unsigned int)streamData->m_voiceData;
			if (pause == 1) {
				if (*(void**)(voiceData + 0x14) != 0) {
					*(int*)(voiceData + 0x9c) = 0;
					*(unsigned int*)(voiceData + 0x90) |= 0x10;
					if (streamData->m_channelCount == 2) {
						*(int*)(voiceData + 0x15c) = 0;
						*(unsigned int*)(voiceData + 0x150) |= 0x10;
					}
				}
			} else if (*(void**)(voiceData + 0x14) != 0) {
				unsigned int pitch = PitchCompute(0x3c00000, 0, streamData->m_pitch, 0);
				short channelCount = streamData->m_channelCount;
				volume = streamData->m_volume >> 0xc;
				if (channelCount == 2) {
					*(int*)(voiceData + 0x9c) = pitch;
					*(unsigned int*)(voiceData + 0x90) |= 0x10;
					*(int*)(voiceData + 0x15c) = pitch;
					*(unsigned int*)(voiceData + 0x150) |= 0x10;
				} else {
					pan = streamData->m_pan >> 0xc;
					*(int*)(voiceData + 0x9c) = pitch;
					*(unsigned int*)(voiceData + 0x90) |= 0x10;
				}
			}
		}
		streamData++;
	} while (streamData < p_Stream + 4);
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
		int voiceData;
		if (streamData->m_state == 1) {
			voiceData = streamData->m_voiceData;
			if (*(void**)(voiceData + 0x14) != 0) {
				if (*(int*)(*(int*)(voiceData + 0x14) + 0xc) == 0) {
					_StreamStop(streamData);
				} else {
					int samplePos = *(unsigned short*)(*(int*)(voiceData + 0x14) + 0x1b2);
					int sampleStart = (streamData->m_aramBuffer + streamData->m_streamCursorBase) * 2;
					samplePos <<= 16;
					samplePos |= *(unsigned short*)(*(int*)(voiceData + 0x14) + 0x1b4);
					if ((samplePos >= sampleStart) && (samplePos < sampleStart + 0x2000)) {
						int stopped = 0;
						if (streamData->m_loopStart < 0) {
							streamData->m_loopEnd = streamData->m_loopEnd - 0x200;
							if (streamData->m_loopEnd < 1) {
								_StreamStop(streamData);
								stopped = 1;
							}
						}
						streamData->m_fileCursor += streamData->m_channelCount * 0x1000;
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
								streamData->m_streamCursorBase = 0x1000;
							}

							if (streamData->m_loopStart < 0) {
								dmaID = _ArrangeStreamDataNoLoop(streamData, side, 0x1000);
							} else {
								dmaID = _ArrangeStreamDataLoop(streamData, side, 0x1000);
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
						if (streamData->m_channelCount == 2) {
							SetVoiceVolumeMix((RedVoiceDATA*)voiceData, 0, streamData->m_volume >> 0xc);
							voiceData += 0xc0;
							SetVoiceVolumeMix((RedVoiceDATA*)voiceData, 0x7f, streamData->m_volume >> 0xc);
						} else {
							SetVoiceVolumeMix((RedVoiceDATA*)voiceData, streamData->m_pan >> 0xc,
								streamData->m_volume >> 0xc);
						}
					}
				}
			}
		} else if ((streamData->m_state == 3) && (RedDmaSearchID(streamData->m_dmaId) == 0)) {
			voiceData = streamData->m_voiceData;
			streamData->m_state = 1;
			*(unsigned int*)(voiceData + 0x90) |= 0x19;
			*(unsigned int*)(voiceData + 4) = (unsigned int)streamData->m_trackData;
			*(int*)(voiceData + 0x8c) = 1;
			if (streamData->m_channelCount == 2) {
				*(unsigned int*)(voiceData + 0x150) |= 0x19;
				*(unsigned int*)(voiceData + 0xc4) = (unsigned int)streamData->m_trackData[1];
				*(int*)(voiceData + 0x14c) = 1;
			}
		}

		streamData++;
	} while (streamData < p_Stream + 4);
}
