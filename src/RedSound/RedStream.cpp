#include "ffcc/RedSound/RedStream.h"
#include "ffcc/RedSound/RedDriver.h"
#include "ffcc/RedSound/RedExecute.h"
#include <string.h>

extern void* DAT_8032f438;
extern int DAT_8021d1a8;

extern "C" {
void RedDelete__FPv(void*);
void RedDeleteA__Fi(int);
int PitchCompute__Fiiii(int, int, int, int);
int fflush(void*);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
unsigned int _SearchEmptyStreamData()
{
	unsigned int streamData;

	streamData = (unsigned int)DAT_8032f438;
	do {
		if (*(int*)(streamData + 0x10c) == 0) {
			return streamData;
		}
		streamData += 0x130;
	} while (streamData < (unsigned int)DAT_8032f438 + 0x4c0);

	return 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _StreamStop(RedStreamDATA* streamData)
{
	fflush(&DAT_8021d1a8);
	if (*(int*)((int)streamData + 0x10c) != 0) {
		*(int*)((int)streamData + 0x10c) = 0;
		*(int*)((int)streamData + 0x110) = 0;
		if (*(int*)((int)streamData + 0xc) != 0) {
			RedDelete__FPv((void*)*(int*)((int)streamData + 0xc));
			*(int*)((int)streamData + 0xc) = 0;
		}
		if (*(int*)((int)streamData + 0x12c) != 0) {
			RedDeleteA__Fi(*(int*)((int)streamData + 0x12c));
			*(int*)((int)streamData + 0x12c) = 0;
		}
		*(unsigned int*)(*(int*)((int)streamData + 4) + 0x90) |= 2;
		*(unsigned char*)(*(int*)((int)streamData + 0) + 0x26) &= 0xfd;
		*(unsigned char*)(*(int*)((int)streamData + 4) + 0x1a) &= 0xfd;
		*(int*)(*(int*)((int)streamData + 4) + 0x8c) = 0;
		if (*(short*)((int)streamData + 0x2a) == 2) {
			*(unsigned int*)(*(int*)((int)streamData + 4) + 0x150) |= 2;
			*(unsigned char*)(*(int*)((int)streamData + 0) + 0x17a) &= 0xfd;
			*(unsigned char*)(*(int*)((int)streamData + 4) + 0xda) &= 0xfd;
			*(int*)(*(int*)((int)streamData + 4) + 0x14c) = 0;
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
		if (*(int*)((int)param_1 + 0x118) <= *(int*)((int)param_1 + 0x120)) {
			*(int*)((int)param_1 + 0x120) = 0;
		}

		if (*(short*)((int)param_1 + 0x2a) == 2) {
			memcpy(dstBuffer + 0x2000, (void*)(*(int*)((int)param_1 + 8) + *(int*)((int)param_1 + 0x120)), 0x1000);
			*(int*)((int)param_1 + 0x120) += 0x1000;
			if (*(int*)((int)param_1 + 0x118) <= *(int*)((int)param_1 + 0x120)) {
				*(int*)((int)param_1 + 0x120) = 0;
			}
		}

		dmaDstOffset = *(int*)((int)param_1 + 0x12c) + param_2 * 0x1000;
		dmaID = RedDmaEntry(0x8001, 0, (int)dstBuffer, dmaDstOffset, 0x1000, 0, 0);

		if ((param_2 == 0) && (*(int*)(streamStruct + 0x14) != 0)) {
			*(unsigned short*)(*(int*)(streamStruct + 0x14) + 0x1ec) = (unsigned short)*dstBuffer;
			*(unsigned short*)(*(int*)(streamStruct + 0x14) + 0x1f0) = 0;
			*(unsigned short*)(*(int*)(streamStruct + 0x14) + 0x1ee) = 0;
			*(unsigned int*)(*(int*)(streamStruct + 0x14) + 0x1c) |= 0x100000;
		}

		if (*(short*)((int)param_1 + 0x2a) == 2) {
			dmaID = RedDmaEntry(0x8001, 0, (int)(dstBuffer + 0x2000), dmaDstOffset + 0x2000, 0x1000, 0, 0);
			if ((param_2 == 0) && (*(int*)(streamStruct + 0xd4) != 0)) {
				*(unsigned short*)(*(int*)(streamStruct + 0xd4) + 0x1ec) = (unsigned short)dstBuffer[0x2000];
				*(unsigned short*)(*(int*)(streamStruct + 0xd4) + 0x1f0) = 0;
				*(unsigned short*)(*(int*)(streamStruct + 0xd4) + 0x1ee) = 0;
				*(unsigned int*)(*(int*)(streamStruct + 0xd4) + 0x1c) |= 0x100000;
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
	unsigned int* puVar1;
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
				puVar1 = puVar7 + 3;
				puVar7 = puVar7 + 4;
				*(unsigned int*)(pbVar4 + 4) = *puVar1;
				pbVar4 = pbVar4 + 8;
			} while (puVar7 < puVar3);
			
			*(int*)((int)param_1 + 0x120) = *(int*)((int)param_1 + 0x120) + 0x1000;
			if (*(int*)((int)param_1 + 0x118) <= *(int*)((int)param_1 + 0x120)) {
				*(int*)((int)param_1 + 0x120) = 0;
			}
			
			puVar7 = (unsigned int*)(*(int*)((int)param_1 + 8) + *(int*)((int)param_1 + 0x120));
			puVar3 = puVar7 + 0x400;
			
			do {
				*(unsigned int*)pbVar5 = *puVar7;
				*(unsigned int*)(pbVar5 + 4) = puVar7[1];
				pbVar5 = pbVar5 + 8;
				*(unsigned int*)pbVar4 = puVar7[2];
				puVar1 = puVar7 + 3;
				puVar7 = puVar7 + 4;
				*(unsigned int*)(pbVar4 + 4) = *puVar1;
				pbVar4 = pbVar4 + 8;
			} while (puVar7 < puVar3);
			
			*(int*)((int)param_1 + 0x120) = *(int*)((int)param_1 + 0x120) + 0x1000;
			if (*(int*)((int)param_1 + 0x118) <= *(int*)((int)param_1 + 0x120)) {
				*(int*)((int)param_1 + 0x120) = 0;
			}
			
			dmaID = RedDmaEntry(0x8001, 0, (int)pbVar6, *(int*)((int)param_1 + 300) + param_2 * 0x1000, 0x1000, 0, 0);
			dmaID = RedDmaEntry(0x8001, 0, (int)(pbVar6 + 0x2000), *(int*)((int)param_1 + 300) + (param_2 + 2) * 0x1000, 0x1000, 0, 0);
			
			if ((param_2 == 0) && (*(int*)(iVar8 + 0x14) != 0)) {
				*(unsigned short*)(*(int*)(iVar8 + 0x14) + 0x1ec) = (unsigned short)*pbVar6;
				*(unsigned short*)(*(int*)(iVar8 + 0x14) + 0x1f0) = 0;
				*(unsigned short*)(*(int*)(iVar8 + 0x14) + 0x1ee) = 0;
				*(unsigned int*)(*(int*)(iVar8 + 0x14) + 0x1c) = *(unsigned int*)(*(int*)(iVar8 + 0x14) + 0x1c) | 0x100000;
				*(unsigned short*)(*(int*)(iVar8 + 0xd4) + 0x1ec) = (unsigned short)pbVar6[0x2000];
				*(unsigned short*)(*(int*)(iVar8 + 0xd4) + 0x1f0) = 0;
				*(unsigned short*)(*(int*)(iVar8 + 0xd4) + 0x1ee) = 0;
				*(unsigned int*)(*(int*)(iVar8 + 0xd4) + 0x1c) = *(unsigned int*)(*(int*)(iVar8 + 0xd4) + 0x1c) | 0x100000;
			}
			
			param_2 = param_2 ^ 1;
			param_3 = param_3 + -0x1000;
			*(int*)((int)param_1 + 0x124) = *(int*)((int)param_1 + 0x124) + 0x200;
			
			if (*(int*)((int)param_1 + 0x1c) <= *(int*)((int)param_1 + 0x124)) {
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
			
			if (*(int*)((int)param_1 + 0x118) <= *(int*)((int)param_1 + 0x120)) {
				*(int*)((int)param_1 + 0x120) = 0;
			}
			
			dmaID = RedDmaEntry(0x8001, 0, (int)pbVar5, *(int*)((int)param_1 + 300) + param_2 * 0x1000, 0x1000, 0, 0);
			
			if ((param_2 == 0) && (*(int*)(iVar8 + 0x14) != 0)) {
				*(unsigned short*)(*(int*)(iVar8 + 0x14) + 0x1ec) = (unsigned short)*pbVar5;
				*(unsigned short*)(*(int*)(iVar8 + 0x14) + 0x1f0) = 0;
				*(unsigned short*)(*(int*)(iVar8 + 0x14) + 0x1ee) = 0;
				*(unsigned int*)(*(int*)(iVar8 + 0x14) + 0x1c) = *(unsigned int*)(*(int*)(iVar8 + 0x14) + 0x1c) | 0x100000;
			}
			
			param_2 = param_2 ^ 1;
			param_3 = param_3 + -0x1000;
			*(int*)((int)param_1 + 0x124) = *(int*)((int)param_1 + 0x124) + 0x200;
			
			if (*(int*)((int)param_1 + 0x1c) <= *(int*)((int)param_1 + 0x124)) {
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
	void (*stopFn)(RedStreamDATA*);
	unsigned int streamData;

	stopFn = _StreamStop;
	streamData = (unsigned int)DAT_8032f438;
	do {
		if ((*(int*)(streamData + 0x10c) != 0) &&
		    ((param_1 == -1) || (param_1 == *(int*)(streamData + 0x10c)))) {
			stopFn((RedStreamDATA*)streamData);
		}
		streamData += 0x130;
	} while (streamData < (unsigned int)DAT_8032f438 + 0x4c0);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void StreamPlay(int, void*, int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void SetStreamVolume(int param_1, int param_2, int param_3)
{
	int iVar1;
	unsigned int streamData;

	if (param_3 < 1) {
		iVar1 = 1;
	} else {
		iVar1 = (param_3 * 200) / 0x3c + (param_3 * 200 >> 0x1f);
		iVar1 -= (iVar1 >> 0x1f);
	}
	param_2 &= 0x7f;
	streamData = (unsigned int)DAT_8032f438;
	if (param_2 != 0) {
		param_2 = ((param_2 + 1) * 0x100 - 1) * 0x1000 | 0x800;
	}

	do {
		if ((*(int*)(streamData + 0x10c) != 0) &&
		    ((param_1 == -1) || (param_1 == *(int*)(streamData + 0x10c)))) {
			if (iVar1 < 1) {
				*(unsigned int*)(streamData + 0xf0) = (unsigned int)param_2;
				*(int*)(streamData + 0xf8) = 0;
			} else {
				*(int*)(streamData + 0xf4) =
				    (int)((unsigned int)param_2 - *(int*)(streamData + 0xf0)) / iVar1;
				*(int*)(streamData + 0xf8) = iVar1;
			}
		}
		streamData += 0x130;
	} while (streamData < (unsigned int)DAT_8032f438 + 0x4c0);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void StreamPause(int param_1, int param_2)
{
	unsigned int streamData;

	streamData = (unsigned int)DAT_8032f438;
	do {
		if ((*(int*)(streamData + 0x10c) != 0) &&
		    ((param_1 == -1) || (param_1 == *(int*)(streamData + 0x10c)))) {
			int voiceData = *(int*)(streamData + 4);
			if (param_2 == 1) {
				if (*(int*)(voiceData + 0x14) != 0) {
					*(int*)(voiceData + 0x9c) = 0;
					*(unsigned int*)(voiceData + 0x90) |= 0x10;
					if (*(short*)(streamData + 0x2a) == 2) {
						*(int*)(voiceData + 0x15c) = 0;
						*(unsigned int*)(voiceData + 0x150) |= 0x10;
					}
				}
			} else if (*(int*)(voiceData + 0x14) != 0) {
				int pitch = PitchCompute__Fiiii(0x3c00000, 0, *(int*)(streamData + 0x24), 0);
				if (*(short*)(streamData + 0x2a) == 2) {
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
		streamData += 0x130;
	} while (streamData < (unsigned int)DAT_8032f438 + 0x4c0);
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
	extern void* DAT_8032f438;

	unsigned int streamData = (unsigned int)DAT_8032f438;
	do {
		if (*(int*)(streamData + 0x110) == 1) {
			int voiceData = *(int*)(streamData + 4);
			if (*(int*)(voiceData + 0x14) != 0) {
				if (*(int*)(*(int*)(voiceData + 0x14) + 0xc) == 0) {
					_StreamStop((RedStreamDATA*)streamData);
				} else {
					int sampleStart = (*(int*)(streamData + 0x12c) + *(int*)(streamData + 0x128)) * 2;
					int samplePos = (*(unsigned short*)(*(int*)(voiceData + 0x14) + 0x1b2) << 16) |
						*(unsigned short*)(*(int*)(voiceData + 0x14) + 0x1b4);
					if ((sampleStart <= samplePos) && (samplePos < sampleStart + 0x2000)) {
						bool stopped = false;
						if ((*(int*)(streamData + 0x20) < 0) &&
							((*(int*)(streamData + 0x1c) = *(int*)(streamData + 0x1c) - 0x200), *(int*)(streamData + 0x1c) < 1)) {
							_StreamStop((RedStreamDATA*)streamData);
							stopped = true;
						}
						*(int*)(streamData + 0x11c) += *(short*)(streamData + 0x2a) * 0x1000;
						if (*(int*)(streamData + 0x118) <= *(int*)(streamData + 0x11c)) {
							*(int*)(streamData + 0x11c) -= *(int*)(streamData + 0x118);
						}

						if (!stopped) {
							int side = *(int*)(streamData + 0x128) == 0;
							if (side) {
								*(int*)(streamData + 0x128) = 0x1000;
							} else {
								*(int*)(streamData + 0x128) = 0;
							}

							if (*(int*)(streamData + 0x20) < 0) {
								*(int*)(streamData + 0x114) = _ArrangeStreamDataNoLoop((RedStreamDATA*)streamData, side, 0x1000);
							} else {
								*(int*)(streamData + 0x114) = _ArrangeStreamDataLoop((RedStreamDATA*)streamData, side, 0x1000);
							}
						}
					}
				}

				int changed = *(int*)(streamData + 0x108) != 0;
				if (changed) {
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
						SetVoiceVolumeMix((RedVoiceDATA*)(voiceData + 0xc0), 0x7f, *(int*)(streamData + 0xf0) >> 0xc);
					} else {
						SetVoiceVolumeMix((RedVoiceDATA*)voiceData, *(int*)(streamData + 0x100) >> 0xc,
							*(int*)(streamData + 0xf0) >> 0xc);
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
	} while (streamData < (unsigned int)DAT_8032f438 + 0x4c0);
}
