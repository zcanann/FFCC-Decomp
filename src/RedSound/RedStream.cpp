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

		streamData = (RedStreamDATA*)((u8*)streamData + 0x130);

		if (!((u8*)streamData < (u8*)p_Stream + 0x4C0)) {
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
		dstBuffer = (unsigned char*)(*(int*)((int)stream + 0xc) + bufferIndex * 0x1000);
		streamStruct = *(int*)((int)stream + 4);

		memcpy(dstBuffer, (void*)(*(int*)((int)stream + 8) + *(int*)((int)stream + 0x120)), 0x1000);
		*(int*)((int)stream + 0x120) += 0x1000;
		if (*(int*)((int)stream + 0x120) >= *(int*)((int)stream + 0x118)) {
			*(int*)((int)stream + 0x120) = 0;
		}

		if (*(short*)((int)stream + 0x2a) == 2) {
			memcpy(dstBuffer + 0x2000, (void*)(*(int*)((int)stream + 8) + *(int*)((int)stream + 0x120)), 0x1000);
			*(int*)((int)stream + 0x120) += 0x1000;
			if (*(int*)((int)stream + 0x120) >= *(int*)((int)stream + 0x118)) {
				*(int*)((int)stream + 0x120) = 0;
			}
		}

		dmaDstOffset = *(int*)((int)stream + 0x12c) + bufferIndex * 0x1000;
		dmaID = RedDmaEntry(0x8001, 0, (int)dstBuffer, dmaDstOffset, 0x1000, 0, 0);

		if ((bufferIndex == 0) && (*(void**)(streamStruct + 0x14) != 0)) {
			*(unsigned short*)(*(int*)(streamStruct + 0x14) + 0x1ec) = (unsigned short)*dstBuffer;
			*(unsigned short*)(*(int*)(streamStruct + 0x14) + 0x1ee) =
			    *(unsigned short*)(*(int*)(streamStruct + 0x14) + 0x1f0) = 0;
			*(unsigned int*)(*(int*)(streamStruct + 0x14) + 0x1c) |= 0x100000;
		}

		if (*(short*)((int)stream + 0x2a) == 2) {
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
		*(int*)((int)stream + 0x124) += 0x200;
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
	
	if (*(short*)((int)stream + 0x2a) == 2) {
		do {
			pbVar6 = (unsigned char*)(*(int*)((int)stream + 0xc) + bufferIndex * 0x1000);
			iVar8 = *(int*)((int)stream + 4);
			puVar7 = (unsigned int*)(*(int*)((int)stream + 8) + *(int*)((int)stream + 0x120));
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
			
			*(int*)((int)stream + 0x120) = *(int*)((int)stream + 0x120) + 0x1000;
			if (*(int*)((int)stream + 0x120) >= *(int*)((int)stream + 0x118)) {
				*(int*)((int)stream + 0x120) = 0;
			}
			
			puVar7 = (unsigned int*)(*(int*)((int)stream + 8) + *(int*)((int)stream + 0x120));
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
			
			*(int*)((int)stream + 0x120) = *(int*)((int)stream + 0x120) + 0x1000;
			if (*(int*)((int)stream + 0x120) >= *(int*)((int)stream + 0x118)) {
				*(int*)((int)stream + 0x120) = 0;
			}
			
			dmaID = RedDmaEntry(0x8001, 0, (int)pbVar6, *(int*)((int)stream + 300) + bufferIndex * 0x1000, 0x1000, 0, 0);
			dmaID = RedDmaEntry(0x8001, 0, (int)(pbVar6 + 0x2000), *(int*)((int)stream + 300) + (bufferIndex + 2) * 0x1000, 0x1000, 0, 0);
			
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
			*(int*)((int)stream + 0x124) = *(int*)((int)stream + 0x124) + 0x200;
			
			if (*(int*)((int)stream + 0x124) >= *(int*)((int)stream + 0x1c)) {
				*(int*)((int)stream + 0x124) = *(int*)((int)stream + 0x124) - *(int*)((int)stream + 0x1c);
				*(int*)((int)stream + 0x124) = *(int*)((int)stream + 0x124) + *(int*)((int)stream + 0x20);
			}
		} while (0 < byteCount);
	} else {
		do {
			pbVar5 = (unsigned char*)(*(int*)((int)stream + 0xc) + bufferIndex * 0x1000);
			iVar8 = *(int*)((int)stream + 4);
			memcpy(pbVar5, (void*)(*(int*)((int)stream + 8) + *(int*)((int)stream + 0x120)), 0x1000);
			*(int*)((int)stream + 0x120) = *(int*)((int)stream + 0x120) + 0x1000;
			
			if (*(int*)((int)stream + 0x120) >= *(int*)((int)stream + 0x118)) {
				*(int*)((int)stream + 0x120) = 0;
			}
			
			dmaID = RedDmaEntry(0x8001, 0, (int)pbVar5, *(int*)((int)stream + 300) + bufferIndex * 0x1000, 0x1000, 0, 0);
			
			if ((bufferIndex == 0) && (*(void**)(iVar8 + 0x14) != 0)) {
				int zero = 0;
				*(unsigned short*)(*(int*)(iVar8 + 0x14) + 0x1ec) = (unsigned short)*pbVar5;
				*(unsigned short*)(*(int*)(iVar8 + 0x14) + 0x1f0) = zero;
				*(unsigned short*)(*(int*)(iVar8 + 0x14) + 0x1ee) = zero;
				*(unsigned int*)(*(int*)(iVar8 + 0x14) + 0x1c) = *(unsigned int*)(*(int*)(iVar8 + 0x14) + 0x1c) | 0x100000;
			}
			
			bufferIndex = bufferIndex ^ 1;
			byteCount = byteCount + -0x1000;
			*(int*)((int)stream + 0x124) = *(int*)((int)stream + 0x124) + 0x200;
			
			if (*(int*)((int)stream + 0x124) >= *(int*)((int)stream + 0x1c)) {
				*(int*)((int)stream + 0x124) = *(int*)((int)stream + 0x124) - *(int*)((int)stream + 0x1c);
				*(int*)((int)stream + 0x124) = *(int*)((int)stream + 0x124) + *(int*)((int)stream + 0x20);
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
int StreamPlay(int streamID, void* streamHeader, int volume, int pan, int loopMode)
{
	int amemSize;
	int arOffset;
	int pitch;
	int iVar2;
	int sampleOffset;
	u8* headerData;
	int* streamData;
	int* voice;

	streamData = (int*)_SearchEmptyStreamData();
	if (streamData != (int*)0) {

	memcpy(streamData + 4, streamHeader, 0x20);
	*streamData = (int)SearchSeEmptyTrack(*(short*)((int)streamData + 0x2a), 0xff, 0);
	streamData[3] = RedNew(0x4000);
	amemSize = *(short*)((int)streamData + 0x2a) << 0xd;
	if (c_RedMemory.GetABufferSize() < 0x800000) {
		arOffset = 0;
	} else {
		arOffset = 0x300000;
	}
	streamData[0x4b] = RedNewA(amemSize, 0, arOffset);
	if (streamData[0x4b] == 0) {
		c_RedEntry.WaveOldClear(0, arOffset);
		streamData[0x4b] = RedNewA(amemSize, 0, arOffset);
	}

	if ((*streamData != 0) && (streamData[3] != 0) && (streamData[0x4b] != 0)) {
		sampleOffset = 0x1000;
		*(short*)((int)streamHeader + 0x42) = (short)*(char*)((int)streamHeader + sampleOffset);
		*(unsigned short*)((int)streamHeader + 0x46) = 0;
		*(unsigned short*)((int)streamHeader + 0x44) = 0;
		headerData = (u8*)streamHeader + 0x20;
		if (*(short*)((int)streamData + 0x2a) == 2) {
			if (streamData[8] < 0) {
				sampleOffset += 0x1000;
			} else {
				sampleOffset += 8;
			}
			*(short*)(headerData + 0x50) = (short)*(char*)((int)streamHeader + sampleOffset);
			*(unsigned short*)(headerData + 0x54) = 0;
			*(unsigned short*)(headerData + 0x52) = 0;
		}

		streamData[0x43] = streamID;
		streamData[0x47] = 0;
		streamData[0x48] = 0x1000;
		streamData[0x49] = 0;
		streamData[1] = (int)p_VoiceData + *(char*)(*streamData + 0x14e) * 0xc0;
		streamData[2] = (int)streamHeader;
		streamData[0x46] = volume;
		if (loopMode != 0) {
			loopMode = ((loopMode + 1) * 0x100 - 1) * 0x1000;
		}
		streamData[0x3c] = loopMode;
		streamData[0x3e] = 0;
		pitch = PitchCompute(0x3c00000, 0, streamData[9], 0);
		iVar2 = 0;
		do {
			voice = (int*)(streamData[1] + iVar2 * 0xc0);
			*voice = *streamData + iVar2 * 0x154;
			*(unsigned char*)(*voice + 0x26) |= 2;
			*(unsigned char*)((int)voice + 0x1a) |= 2;
			voice[0x25] = 0xc01;
			if (*(short*)(streamData + 0xb) != 0) {
				voice[0x25] |= 0x3000;
			}
			*(int*)(*voice + 0xfc) = 1;
			voice[0x2c] = 0x8000;
			voice[1] = (int)streamData + iVar2 * 0x60 + 0x30;
			voice[0x27] = pitch;
			*(int*)(*voice + 0x68) = *(int*)((int)p_ReverbDepth + 0xc);
			*(int*)(*voice + 0x70) = 0;
			if (*(short*)((int)streamData + 0x2a) == 2) {
				if (iVar2 == 0) {
					streamData[0x40] = 0;
					streamData[0x42] = 0;
				} else {
					streamData[0x40] = 0x7f000;
					streamData[0x42] = 0;
				}
			} else {
				streamData[0x40] = pan << 0xc;
				streamData[0x42] = 0;
			}
			SetVoiceVolumeMix((RedVoiceDATA*)(streamData[1] + iVar2 * 0xc0), streamData[0x40] >> 0xc, streamData[0x3c] >> 0xc);
			*(int*)(*streamData + iVar2 * 0x154 + 0x11c) = streamData[0x4b] + iVar2 * 0x2000;
			memset((void*)((int)streamData + iVar2 * 0x60 + 0x30), 0, 0x60);
			memcpy((void*)((int)streamData + iVar2 * 0x60 + 0x52), headerData + iVar2 * 0x2e, 0x2e);
			*(unsigned char*)((int)voice + 0x5a) = 0;
			*(unsigned char*)((int)voice + 0x59) = 0;
			*(unsigned char*)(voice + 0x16) = 0;
			*(unsigned char*)((int)voice + 0x5b) = 0x7f;
			*(unsigned short*)(voice + 0x15) = 0;
			*(unsigned short*)((int)voice + 0x52) = 0;
			*(unsigned short*)(voice + 0x14) = 0;
			*(unsigned short*)((int)voice + 0x56) = 10;
			*(int*)((int)streamData + iVar2 * 0x60 + 0x34) = 0;
			*(int*)((int)streamData + iVar2 * 0x60 + 0x3c) = 0x3fff;
			*(int*)((int)streamData + iVar2 * 0x60 + 0x38) = 2;
			iVar2 += 1;
		} while (iVar2 < *(short*)((int)streamData + 0x2a));

		int dmaID;
		if (streamData[8] < 0) {
			dmaID = _ArrangeStreamDataNoLoop((RedStreamDATA*)streamData, 0, 0x2000);
		} else {
			dmaID = _ArrangeStreamDataLoop((RedStreamDATA*)streamData, 0, 0x2000);
		}
		streamData[0x45] = dmaID;
		streamData[0x4a] = 0x1000;
		streamData[0x44] = 3;
	} else {
		if (m_ReportPrint != 0) {
			OSReport(sRedStreamBufferDidntSecureFmt, sRedStreamLogPrefix, sRedStreamLogErrorColor, sRedStreamLogReset);
			fflush(__files + 1);
		}
		if (streamData[3] != 0) {
			RedDelete((void*)streamData[3]);
		} else {
			if (m_ReportPrint != 0) {
				OSReport(sRedStreamMainMemoryDidntCreateFmt,
				         sRedStreamLogPrefix, sRedStreamLogWarnColor, 0x4000,
				         sRedStreamLogReset);
				fflush(__files + 1);
			}
		}
		if (streamData[0x4b] != 0) {
			RedDeleteA(streamData[0x4b]);
		} else {
			if (m_ReportPrint != 0) {
				OSReport(sRedStreamAramMemoryDidntCreateFmt,
				         sRedStreamLogPrefix, sRedStreamLogWarnColor, *(short*)((int)streamData + 0x2a) << 0xd,
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
			unsigned int voiceData = (unsigned int)streamData->m_voiceData;
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
				unsigned int pitch = PitchCompute(0x3c00000, 0, *(int*)((u8*)streamData + 0x24), 0);
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
	unsigned int streamData = (unsigned int)p_Stream;
	do {
		int voiceData;
		if (*(int*)(streamData + 0x110) == 1) {
			voiceData = *(int*)(streamData + 4);
			if (*(void**)(voiceData + 0x14) != 0) {
				if (*(int*)(*(int*)(voiceData + 0x14) + 0xc) == 0) {
					_StreamStop((RedStreamDATA*)streamData);
				} else {
					int samplePos = *(unsigned short*)(*(int*)(voiceData + 0x14) + 0x1b2);
					int sampleStart = (*(int*)(streamData + 0x12c) + *(int*)(streamData + 0x128)) * 2;
					samplePos <<= 16;
					samplePos |= *(unsigned short*)(*(int*)(voiceData + 0x14) + 0x1b4);
					if ((samplePos >= sampleStart) && (samplePos < sampleStart + 0x2000)) {
						int stopped = 0;
						if (*(int*)(streamData + 0x20) < 0) {
							*(int*)(streamData + 0x1c) = *(int*)(streamData + 0x1c) - 0x200;
							if (*(int*)(streamData + 0x1c) < 1) {
								_StreamStop((RedStreamDATA*)streamData);
								stopped = 1;
							}
						}
						*(int*)(streamData + 0x11c) += *(short*)(streamData + 0x2a) * 0x1000;
						if (*(int*)(streamData + 0x11c) >= *(int*)(streamData + 0x118)) {
							*(int*)(streamData + 0x11c) -= *(int*)(streamData + 0x118);
						}

						if (!stopped) {
							int side;
							int dmaID;
							if (*(int*)(streamData + 0x128) != 0) {
								side = 0;
								*(int*)(streamData + 0x128) = 0;
							} else {
								side = 1;
								*(int*)(streamData + 0x128) = 0x1000;
							}

							if (*(int*)(streamData + 0x20) < 0) {
								dmaID = _ArrangeStreamDataNoLoop((RedStreamDATA*)streamData, side, 0x1000);
							} else {
								dmaID = _ArrangeStreamDataLoop((RedStreamDATA*)streamData, side, 0x1000);
							}
							*(int*)(streamData + 0x114) = dmaID;
						}
					}

					int changed = 0;
					if (*(int*)(streamData + 0x108) != 0) {
						changed += 1;
						*(int*)(streamData + 0x108) -= 1;
						*(int*)(streamData + 0x100) += *(int*)(streamData + 0x104);
					}
					if (*(int*)(streamData + 0xf8) != 0) {
						changed += 1;
						*(int*)(streamData + 0xf8) -= 1;
						*(int*)(streamData + 0xf0) += *(int*)(streamData + 0xf4);
					}
					if (changed != 0) {
						if (*(short*)(streamData + 0x2a) == 2) {
							SetVoiceVolumeMix((RedVoiceDATA*)voiceData, 0, *(int*)(streamData + 0xf0) >> 0xc);
							voiceData += 0xc0;
							SetVoiceVolumeMix((RedVoiceDATA*)voiceData, 0x7f, *(int*)(streamData + 0xf0) >> 0xc);
						} else {
							SetVoiceVolumeMix((RedVoiceDATA*)voiceData, *(int*)(streamData + 0x100) >> 0xc,
								*(int*)(streamData + 0xf0) >> 0xc);
						}
					}
				}
			}
		} else if ((*(int*)(streamData + 0x110) == 3) && (RedDmaSearchID(*(int*)(streamData + 0x114)) == 0)) {
			voiceData = *(int*)(streamData + 4);
			*(int*)(streamData + 0x110) = 1;
			*(unsigned int*)(voiceData + 0x90) |= 0x19;
			*(unsigned int*)(voiceData + 4) = streamData + 0x30;
			*(int*)(voiceData + 0x8c) = 1;
			if (*(short*)(streamData + 0x2a) == 2) {
				*(unsigned int*)(voiceData + 0x150) |= 0x19;
				*(unsigned int*)(voiceData + 0xc4) = streamData + 0x90;
				*(int*)(voiceData + 0x14c) = 1;
			}
		}

		streamData += 0x130;
	} while (streamData < (unsigned int)p_Stream + 0x4c0);
}
