#include "ffcc/RedSound/RedStream.h"
#include "ffcc/RedSound/RedCommand.h"
#include "ffcc/RedSound/RedDriver.h"
#include "ffcc/RedSound/RedEntry.h"
#include "ffcc/RedSound/RedExecute.h"
#include "ffcc/RedSound/RedMemory.h"
#include "ffcc/RedSound/RedGlobals.h"
#include <dolphin/os.h>
#include <string.h>

struct RedStreamDebugStrings {
    char bufferDidntSecure[sizeof("%s%sStream Buffer didn't secure.%s\n")];
    char logPrefix[sizeof("\x1B[7;34mSound\x1B[0m:")];
    char mainMemoryDidntCreate[sizeof("%s%sM-Memory didn't create.(need:0x%6.6X)%s\n")];
    char aramMemoryDidntCreate[sizeof("%s%sA-Memory didn't create.(need:0x%6.6X)%s\n")];
    char pauseOn[sizeof("%sPause : Stream : ON  %d\n")];
    char pauseOff[sizeof("%sPause : Stream : OFF %d\n")];
    char pad[2];
};

static const RedStreamDebugStrings sRedStreamDebugStrings = {
    "%s%sStream Buffer didn't secure.%s\n",
    "\x1B[7;34mSound\x1B[0m:",
    "%s%sM-Memory didn't create.(need:0x%6.6X)%s\n",
    "%s%sA-Memory didn't create.(need:0x%6.6X)%s\n",
    "%sPause : Stream : ON  %d\n",
    "%sPause : Stream : OFF %d\n",
    { 0, 0 },
};

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
	RedStreamDATA* result;

	for (;;) {
		if (streamData->m_streamId == 0) {
			result = streamData;
			break;
		}

		streamData = (RedStreamDATA*)((u8*)streamData + 0x130);

		if (!((u8*)streamData < (u8*)p_Stream + 0x4C0)) {
			result = 0;
			break;
		}
	}

	return result;
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
int _ArrangeStreamDataNoLoop(RedStreamDATA* param_1, int param_2, int param_3)
{
	unsigned char* dstBuffer;
	int streamStruct;
	int dmaDstOffset;
	int dmaID = 0;

	param_2 &= 1;

	do {
		dstBuffer = (unsigned char*)(*(int*)((int)param_1 + 0xc) + param_2 * 0x1000);
		streamStruct = *(int*)((int)param_1 + 4);

		memcpy(dstBuffer, (void*)(*(int*)((int)param_1 + 8) + *(int*)((int)param_1 + 0x120)), 0x1000);
		*(int*)((int)param_1 + 0x120) += 0x1000;
		if (*(int*)((int)param_1 + 0x120) >= *(int*)((int)param_1 + 0x118)) {
			*(int*)((int)param_1 + 0x120) = 0;
		}

		if (*(short*)((int)param_1 + 0x2a) == 2) {
			memcpy(dstBuffer + 0x2000, (void*)(*(int*)((int)param_1 + 8) + *(int*)((int)param_1 + 0x120)), 0x1000);
			*(int*)((int)param_1 + 0x120) += 0x1000;
			if (*(int*)((int)param_1 + 0x120) >= *(int*)((int)param_1 + 0x118)) {
				*(int*)((int)param_1 + 0x120) = 0;
			}
		}

		dmaDstOffset = *(int*)((int)param_1 + 0x12c) + param_2 * 0x1000;
		dmaID = RedDmaEntry(0x8001, 0, (int)dstBuffer, dmaDstOffset, 0x1000, 0, 0);

		if ((param_2 == 0) && (*(void**)(streamStruct + 0x14) != 0)) {
			int zero = 0;
			*(unsigned short*)(*(int*)(streamStruct + 0x14) + 0x1ec) = (unsigned short)*dstBuffer;
			*(unsigned short*)(*(int*)(streamStruct + 0x14) + 0x1f0) = zero;
			*(unsigned short*)(*(int*)(streamStruct + 0x14) + 0x1ee) = zero;
			*(unsigned int*)(*(int*)(streamStruct + 0x14) + 0x1c) |= 0x100000;
		}

		if (*(short*)((int)param_1 + 0x2a) == 2) {
			dstBuffer += 0x2000;
			dmaDstOffset += 0x2000;
			dmaID = RedDmaEntry(0x8001, 0, (int)dstBuffer, dmaDstOffset, 0x1000, 0, 0);
			streamStruct += 0xc0;
			if ((param_2 == 0) && (*(void**)(streamStruct + 0x14) != 0)) {
				int zero = 0;
				*(unsigned short*)(*(int*)(streamStruct + 0x14) + 0x1ec) = (unsigned short)*dstBuffer;
				*(unsigned short*)(*(int*)(streamStruct + 0x14) + 0x1f0) = zero;
				*(unsigned short*)(*(int*)(streamStruct + 0x14) + 0x1ee) = zero;
				*(unsigned int*)(*(int*)(streamStruct + 0x14) + 0x1c) |= 0x100000;
			}
		}

		param_3 -= 0x1000;
		param_2 ^= 1;
		*(int*)((int)param_1 + 0x124) += 0x200;
	} while (0 < param_3);

	return dmaID;
}

/*
 * --INFO--
 * Address:	801cbc6c
 * Size:	856b
 */
int _ArrangeStreamDataLoop(RedStreamDATA* param_1, int param_2, int param_3)
{
	unsigned int* puVar3;
	unsigned char* pbVar4;
	unsigned char* pbVar5;
	unsigned char* pbVar6;
	unsigned int* puVar7;
	int iVar8;
	int dmaID = 0;

	param_2 = param_2 & 1;
	
	if (*(short*)((int)param_1 + 0x2a) == 2) {
		do {
			pbVar6 = (unsigned char*)(*(int*)((int)param_1 + 0xc) + param_2 * 0x1000);
			iVar8 = *(int*)((int)param_1 + 4);
			puVar7 = (unsigned int*)(*(int*)((int)param_1 + 8) + *(int*)((int)param_1 + 0x120));
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
			
			*(int*)((int)param_1 + 0x120) = *(int*)((int)param_1 + 0x120) + 0x1000;
			if (*(int*)((int)param_1 + 0x120) >= *(int*)((int)param_1 + 0x118)) {
				*(int*)((int)param_1 + 0x120) = 0;
			}
			
			puVar7 = (unsigned int*)(*(int*)((int)param_1 + 8) + *(int*)((int)param_1 + 0x120));
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
			
			*(int*)((int)param_1 + 0x120) = *(int*)((int)param_1 + 0x120) + 0x1000;
			if (*(int*)((int)param_1 + 0x120) >= *(int*)((int)param_1 + 0x118)) {
				*(int*)((int)param_1 + 0x120) = 0;
			}
			
			dmaID = RedDmaEntry(0x8001, 0, (int)pbVar6, *(int*)((int)param_1 + 300) + param_2 * 0x1000, 0x1000, 0, 0);
			dmaID = RedDmaEntry(0x8001, 0, (int)(pbVar6 + 0x2000), *(int*)((int)param_1 + 300) + (param_2 + 2) * 0x1000, 0x1000, 0, 0);
			
			if ((param_2 == 0) && (*(void**)(iVar8 + 0x14) != 0)) {
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
			
			param_2 = param_2 ^ 1;
			param_3 = param_3 + -0x1000;
			*(int*)((int)param_1 + 0x124) = *(int*)((int)param_1 + 0x124) + 0x200;
			
			if (*(int*)((int)param_1 + 0x124) >= *(int*)((int)param_1 + 0x1c)) {
				*(int*)((int)param_1 + 0x124) = *(int*)((int)param_1 + 0x124) - *(int*)((int)param_1 + 0x1c);
				*(int*)((int)param_1 + 0x124) = *(int*)((int)param_1 + 0x124) + *(int*)((int)param_1 + 0x20);
			}
		} while (0 < param_3);
	} else {
		do {
			pbVar5 = (unsigned char*)(*(int*)((int)param_1 + 0xc) + param_2 * 0x1000);
			iVar8 = *(int*)((int)param_1 + 4);
			memcpy(pbVar5, (void*)(*(int*)((int)param_1 + 8) + *(int*)((int)param_1 + 0x120)), 0x1000);
			*(int*)((int)param_1 + 0x120) = *(int*)((int)param_1 + 0x120) + 0x1000;
			
			if (*(int*)((int)param_1 + 0x120) >= *(int*)((int)param_1 + 0x118)) {
				*(int*)((int)param_1 + 0x120) = 0;
			}
			
			dmaID = RedDmaEntry(0x8001, 0, (int)pbVar5, *(int*)((int)param_1 + 300) + param_2 * 0x1000, 0x1000, 0, 0);
			
			if ((param_2 == 0) && (*(void**)(iVar8 + 0x14) != 0)) {
				int zero = 0;
				*(unsigned short*)(*(int*)(iVar8 + 0x14) + 0x1ec) = (unsigned short)*pbVar5;
				*(unsigned short*)(*(int*)(iVar8 + 0x14) + 0x1f0) = zero;
				*(unsigned short*)(*(int*)(iVar8 + 0x14) + 0x1ee) = zero;
				*(unsigned int*)(*(int*)(iVar8 + 0x14) + 0x1c) = *(unsigned int*)(*(int*)(iVar8 + 0x14) + 0x1c) | 0x100000;
			}
			
			param_2 = param_2 ^ 1;
			param_3 = param_3 + -0x1000;
			*(int*)((int)param_1 + 0x124) = *(int*)((int)param_1 + 0x124) + 0x200;
			
			if (*(int*)((int)param_1 + 0x124) >= *(int*)((int)param_1 + 0x1c)) {
				*(int*)((int)param_1 + 0x124) = *(int*)((int)param_1 + 0x124) - *(int*)((int)param_1 + 0x1c);
				*(int*)((int)param_1 + 0x124) = *(int*)((int)param_1 + 0x124) + *(int*)((int)param_1 + 0x20);
			}
		} while (0 < param_3);
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
void StreamStop(int param_1)
{
	volatile RedStreamDATA* streamData = p_Stream;

	do {
		if ((streamData->m_streamId != 0) && ((param_1 == -1) || (param_1 == streamData->m_streamId))) {
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
int StreamPlay(int param_1, void* param_2, int param_3, int param_4, int param_5)
{
	const RedStreamDebugStrings* debugStrings = &sRedStreamDebugStrings;
	int amemSize;
	int arOffset;
	int pitch;
	int iVar2;
	int* streamData;
	int* voice;

	streamData = (int*)_SearchEmptyStreamData();
	if (streamData == (int*)0) {
		return param_1;
	}

	memcpy(streamData + 4, param_2, 0x20);
	*streamData = (int)SearchSeEmptyTrack(*(short*)((int)streamData + 0x2a), 0xff, 0);
	streamData[3] = RedNew(0x4000);
	amemSize = *(short*)((int)streamData + 0x2a) << 0xd;
	arOffset = 0;
	if (c_RedMemory.GetABufferSize() >= 0x800000) {
		arOffset = 0x300000;
	}
	streamData[0x4b] = RedNewA(amemSize, 0, arOffset);
	if (streamData[0x4b] == 0) {
		c_RedEntry.WaveOldClear(0, arOffset);
		streamData[0x4b] = RedNewA(amemSize, 0, arOffset);
	}

	if ((*streamData != 0) && (streamData[3] != 0) && (streamData[0x4b] != 0)) {
		*(short*)((int)param_2 + 0x42) = (short)*(char*)((int)param_2 + 0x1000);
		*(unsigned short*)((int)param_2 + 0x46) = 0;
		*(unsigned short*)((int)param_2 + 0x44) = 0;
		if (*(short*)((int)streamData + 0x2a) == 2) {
			if (streamData[8] < 0) {
				iVar2 = 0x2000;
			} else {
				iVar2 = 0x1008;
			}
			*(short*)((int)param_2 + 0x70) = (short)*(char*)((int)param_2 + iVar2);
			*(unsigned short*)((int)param_2 + 0x74) = 0;
			*(unsigned short*)((int)param_2 + 0x72) = 0;
		}

		streamData[0x43] = param_1;
		streamData[0x47] = 0;
		streamData[0x48] = 0x1000;
		streamData[0x49] = 0;
		streamData[1] = (int)p_VoiceData + *(char*)(*streamData + 0x14e) * 0xc0;
		streamData[2] = (int)param_2;
		streamData[0x46] = param_3;
		if (param_5 != 0) {
			param_5 = ((param_5 + 1) * 0x100 - 1) * 0x1000;
		}
		streamData[0x3c] = param_5;
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
			voice[1] = (int)(streamData + iVar2 * 0x18 + 0xc);
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
				streamData[0x40] = param_4 << 0xc;
				streamData[0x42] = 0;
			}
			SetVoiceVolumeMix((RedVoiceDATA*)(streamData[1] + iVar2 * 0xc0), streamData[0x40] >> 0xc, streamData[0x3c] >> 0xc);
			*(int*)(*streamData + iVar2 * 0x154 + 0x11c) = streamData[0x4b] + iVar2 * 0x2000;
			memset(streamData + iVar2 * 0x18 + 0xc, 0, 0x60);
			memcpy((void*)((int)streamData + iVar2 * 0x60 + 0x52), (void*)((int)param_2 + 0x20 + iVar2 * 0x2e), 0x2e);
			*(unsigned char*)((int)voice + 0x5a) = 0;
			*(unsigned char*)((int)voice + 0x59) = 0;
			*(unsigned char*)(voice + 0x16) = 0;
			*(unsigned char*)((int)voice + 0x5b) = 0x7f;
			*(unsigned short*)(voice + 0x15) = 0;
			*(unsigned short*)((int)voice + 0x52) = 0;
			*(unsigned short*)(voice + 0x14) = 0;
			*(unsigned short*)((int)voice + 0x56) = 10;
			streamData[iVar2 * 0x18 + 0xd] = 0;
			streamData[iVar2 * 0x18 + 0xf] = 0x3fff;
			streamData[iVar2 * 0x18 + 0xe] = 2;
			iVar2 += 1;
		} while (iVar2 < *(short*)((int)streamData + 0x2a));

		if (streamData[8] < 0) {
			streamData[0x45] = _ArrangeStreamDataNoLoop((RedStreamDATA*)streamData, 0, 0x2000);
		} else {
			streamData[0x45] = _ArrangeStreamDataLoop((RedStreamDATA*)streamData, 0, 0x2000);
		}
		streamData[0x4a] = 0x1000;
		streamData[0x44] = 3;
	} else {
		if (m_ReportPrint != 0) {
			OSReport(debugStrings->bufferDidntSecure, debugStrings->logPrefix, sRedStreamLogErrorColor,
			         sRedStreamLogReset);
			fflush(__files + 1);
		}
		if (streamData[3] == 0) {
			if (m_ReportPrint != 0) {
				OSReport(debugStrings->mainMemoryDidntCreate,
				         debugStrings->logPrefix, sRedStreamLogWarnColor, 0x4000,
				         sRedStreamLogReset);
				fflush(__files + 1);
			}
		} else {
			RedDelete((void*)streamData[3]);
		}
		if (streamData[0x4b] == 0) {
			if (m_ReportPrint != 0) {
				OSReport(debugStrings->aramMemoryDidntCreate,
				         debugStrings->logPrefix, sRedStreamLogWarnColor, amemSize,
				         sRedStreamLogReset);
				fflush(__files + 1);
			}
		} else {
			RedDeleteA(streamData[0x4b]);
		}
	}
	return param_1;
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
void SetStreamVolume(int param_1, int param_2, int param_3)
{
	volatile RedStreamDATA* streamData;

	if (param_3 < 1) {
		param_3 = 1;
	} else {
		param_3 = (param_3 * 200) / 60;
	}

	param_2 &= 0x7f;
	if (param_2 != 0) {
		param_2 = ((param_2 + 1) * 0x100 - 1) * 0x1000 | 0x800;
	}

	streamData = p_Stream;
	do {
		if ((streamData->m_streamId != 0) && ((param_1 == -1) || (param_1 == streamData->m_streamId))) {
			if (param_3 > 0) {
				int delta = param_2 - streamData->m_volume;
				streamData->m_volumeStep = delta / param_3;
				streamData->m_volumeStepCount = param_3;
			} else {
				streamData->m_volume = param_2;
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
void StreamPause(int param_1, int param_2)
{
	const RedStreamDebugStrings* debugStrings = &sRedStreamDebugStrings;
	RedStreamDATA* streamData;
	RedStreamDATA* streamEnd;

	if (m_ReportPrint != 0) {
		if (param_2 == 1) {
			OSReport(debugStrings->pauseOn, debugStrings->logPrefix, param_1);
		} else {
			OSReport(debugStrings->pauseOff, debugStrings->logPrefix, param_1);
		}
		fflush(__files + 1);
	}
	streamData = p_Stream;
	streamEnd = p_Stream + 4;
	while (streamData < streamEnd) {
		if ((streamData->m_streamId != 0) && ((param_1 == -1) || (param_1 == streamData->m_streamId))) {
			unsigned int voiceData = (unsigned int)streamData->m_voiceData;
			if (param_2 == 1) {
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
				if (streamData->m_channelCount == 2) {
					*(int*)(voiceData + 0x9c) = pitch;
					*(unsigned int*)(voiceData + 0x90) |= 0x10;
					*(int*)(voiceData + 0x15c) = pitch;
					*(unsigned int*)(voiceData + 0x150) |= 0x10;
				} else {
					*(int*)(voiceData + 0x9c) = pitch;
					*(unsigned int*)(voiceData + 0x90) |= 0x10;
				}
			}
		}
		streamData++;
	}
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
		if (*(int*)(streamData + 0x110) == 1) {
			int voiceData = *(int*)(streamData + 4);
			if (*(void**)(voiceData + 0x14) != 0) {
				if (*(int*)(*(int*)(voiceData + 0x14) + 0xc) == 0) {
					_StreamStop((RedStreamDATA*)streamData);
				} else {
					int sampleStart = (*(int*)(streamData + 0x12c) + *(int*)(streamData + 0x128)) * 2;
					int samplePos = (*(unsigned short*)(*(int*)(voiceData + 0x14) + 0x1b2) << 16) |
						*(unsigned short*)(*(int*)(voiceData + 0x14) + 0x1b4);
					if ((samplePos >= sampleStart) && (samplePos < sampleStart + 0x2000)) {
						int stopped = 0;
						if ((*(int*)(streamData + 0x20) < 0) &&
							((*(int*)(streamData + 0x1c) = *(int*)(streamData + 0x1c) - 0x200), *(int*)(streamData + 0x1c) < 1)) {
							_StreamStop((RedStreamDATA*)streamData);
							stopped = 1;
						}
						*(int*)(streamData + 0x11c) += *(short*)(streamData + 0x2a) * 0x1000;
						if (*(int*)(streamData + 0x118) <= *(int*)(streamData + 0x11c)) {
							*(int*)(streamData + 0x11c) -= *(int*)(streamData + 0x118);
						}

						if (!stopped) {
							int side;
							if (*(int*)(streamData + 0x128) != 0) {
								side = 0;
								*(int*)(streamData + 0x128) = 0;
							} else {
								side = 1;
								*(int*)(streamData + 0x128) = 0x1000;
							}

							if (*(int*)(streamData + 0x20) < 0) {
								*(int*)(streamData + 0x114) = _ArrangeStreamDataNoLoop((RedStreamDATA*)streamData, side, 0x1000);
							} else {
								*(int*)(streamData + 0x114) = _ArrangeStreamDataLoop((RedStreamDATA*)streamData, side, 0x1000);
							}
						}
					}

					RedStreamDATA* stream = (RedStreamDATA*)streamData;
					int changed = stream->m_panStepCount != 0;
					if (changed) {
						stream->m_panStepCount -= 1;
						stream->m_pan += stream->m_panStep;
					}
					if (stream->m_volumeStepCount != 0) {
						changed += 1;
						stream->m_volumeStepCount -= 1;
						stream->m_volume += stream->m_volumeStep;
					}
					if (changed != 0) {
						if (*(short*)(streamData + 0x2a) == 2) {
							SetVoiceVolumeMix((RedVoiceDATA*)voiceData, 0, stream->m_volume >> 0xc);
							SetVoiceVolumeMix((RedVoiceDATA*)(voiceData + 0xc0), 0x7f, stream->m_volume >> 0xc);
						} else {
							SetVoiceVolumeMix((RedVoiceDATA*)voiceData, stream->m_pan >> 0xc,
								stream->m_volume >> 0xc);
						}
					}
				}
			}
		} else if ((*(int*)(streamData + 0x110) == 3) && (RedDmaSearchID(*(int*)(streamData + 0x114)) == 0)) {
			int voiceData = *(int*)(streamData + 4);
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
