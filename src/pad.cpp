#include "ffcc/pad.h"

#include "ffcc/memory.h"
#include "ffcc/system.h"
#include "ffcc/joybus.h"
#include "ffcc/p_dbgmenu.h"

#include "dolphin/pad.h"
#include "dolphin/si.h"

#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/file_io.h"
#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/FILE_POS.h"
#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/direct_io.h"

#include <string.h>

CPad Pad;

void* operator new[](unsigned long, CMemory::CStage*, char*, int);

static const char s_CPad[] = "CPad";
extern const float kPadAnalogZero = 0.0f;
extern const float kPadAnalogScale = 0.0078125f;
extern const float kPadTriggerMax = 255.0f;
extern const double kPadS32ToDoubleBias = 4503601774854144.0;
extern const double kPadU32ToDoubleBias = 4503599627370496.0;
static const char s_pad_cpp[] = { 'p', 'a', 'd', '.', 'c', 'p', 'p', 0 };
static const char s_rb[] = { 'r', 'b', 0 };
static const char s_replay_dat[] = "/replay.dat";
static const char s_replay_host_msg[] = {
    0x43, 0x50, 0x61, 0x64, 0x2E, 0x49, 0x6E, 0x69, 0x74, 0x3A, 0x20, 0x68, 0x6F,
    0x73, 0x74, 0x82, 0xA9, 0x82, 0xE7, 0x96, 0xF1, 0x25, 0x64, 0x95, 0x62, 0x82,
    0xCC, 0x83, 0x8A, 0x83, 0x76, 0x83, 0x8C, 0x83, 0x43, 0x83, 0x66, 0x81, 0x5B,
    0x83, 0x5E, 0x82, 0xF0, 0x93, 0xC7, 0x82, 0xDD, 0x8D, 0x9E, 0x82, 0xDD, 0x82,
    0xDC, 0x82, 0xB5, 0x82, 0xBD, 0x81, 0x42, 0x0A, 0x00, 0x00, 0x00, 0x00,
};

extern "C" {
PADStatus g_pad[4];
}

namespace {
struct ReplayFrame
{
    PADStatus pad[4];
    CPad::Gba gba[4];
};

struct ReplayBuffer
{
    u32 cursor;
    u32 recordMode;
    s32 frameCount;
    ReplayFrame frames[0x1A5E0];
};

typedef char ReplayFrame_size_check[(sizeof(ReplayFrame) == 0x40) ? 1 : -1];
typedef char ReplayBuffer_size_check[(sizeof(ReplayBuffer) == 0x69780C) ? 1 : -1];
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 156b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CPad::SaveReplayData()
{
    ReplayBuffer* replay = reinterpret_cast<ReplayBuffer*>(_1b0_4_);

    if ((replay != 0) && (replay->recordMode != 0) && (replay->cursor <= sizeof(ReplayBuffer)) &&
        (replay->frameCount != 0)) {
        FILE* fp = fopen(s_replay_dat, "wb");
        if (fp != 0) {
            fwrite(replay, 1, replay->cursor, fp);
            fclose(fp);
        }
    }
}

#pragma always_inline on
#pragma inline_max_size 100000
#pragma inline_max_total_size 100000
static inline void MergePadInputs(CPad* pad, u16* puVar13, u16* puVar18, u16* puVar10)
{
	int iVar14;
	u8* p12;
	u32 uVar17;
	int iVar6;
	u16* puVar7;
	u16* puVar12;
	u16 uVar8;
	u32 uVar15;
	s8 cVar9;
	u32 uVar16;
	float fVar2;
	float fVar3;

	fVar2 = kPadAnalogZero;
	CPad::PadInput* merged = reinterpret_cast<CPad::PadInput*>(puVar10);
	merged->buttonPrev[0] = merged->button[0];
	uVar17 = 0;
	merged->buttonDown[0] = 0;
	merged->button[0] = 0;
	merged->buttonPrev[1] = merged->button[1];
	merged->buttonDown[1] = 0;
	merged->button[1] = 0;
	merged->stickBitsPrev = merged->stickBits;
	merged->holdOverride = 0;
	merged->digitalStickOverride = 0;
	merged->stickBits = 0;
	merged->stickBitsDown = 0;
	merged->repeatButton = 0;
	merged->buttonUp = 0;
	merged->substickY = 0;
	merged->substickX = 0;
	merged->stickY = 0;
	merged->stickX = 0;
	merged->triggerRight = 0;
	merged->triggerLeft = 0;
	merged->substickYF = fVar2;
	merged->substickXF = fVar2;
	merged->stickYF = fVar2;
	merged->stickXF = fVar2;
	merged->triggerRightF = fVar2;
	merged->triggerLeftF = fVar2;
	merged->lockedButton[2] = 0;
	merged->lockedButton[1] = 0;
	merged->lockedButton[0] = 0;
	merged->activeMask = 0;
	iVar6 = reinterpret_cast<int>(pad);
	do
	{
		p12 = reinterpret_cast<u8*>(iVar6 + 4);
		puVar12 = reinterpret_cast<u16*>(p12);
		puVar7 = puVar10;
		for (iVar14 = 0; iVar14 < 2; iVar14++)
		{
			if ((iVar14 != 0) || (*reinterpret_cast<s8*>(puVar13 + 5) != -3))
			{
				puVar12[0x26] = static_cast<u16>(*reinterpret_cast<u16*>(p12 + 0x30) | *puVar12);
				if (iVar14 == 0)
				{
					uVar8 = *puVar18;
					*reinterpret_cast<u16*>(p12 + 0x08) = *reinterpret_cast<u16*>(p12 + 0x0A);
					uVar16 = (__cntlzw(1 - (uVar8 & 0x3FFF)) >> 5) & 0xFF;
					*reinterpret_cast<s8*>(p12 + 0x40) = *reinterpret_cast<s8*>(puVar13 + 5);
					*reinterpret_cast<u32*>(p12 + 0x50) = uVar16;
					*reinterpret_cast<u32*>(p12 + 0x44) = 0;
					*reinterpret_cast<u32*>(p12 + 0x38) = 0;
					*reinterpret_cast<u32*>(p12 + 0x3C) = 0;
					if ((*reinterpret_cast<s8*>(p12 + 0x40) == 0) || reinterpret_cast<CPad::Gba*>(puVar18)->noController)
					{
						if (reinterpret_cast<CPad::Gba*>(puVar18)->noController)
						{
							*puVar12 = puVar18[1];
						}
						else
						{
							*puVar12 = *puVar13;
						}
						if (*reinterpret_cast<u8*>(puVar13 + 3) >= 100)
						{
							*puVar12 = static_cast<u16>(*puVar12 | PAD_TRIGGER_L);
						}
						if (*reinterpret_cast<u8*>(reinterpret_cast<u8*>(puVar13) + 7) >= 100)
						{
							*puVar12 = static_cast<u16>(*puVar12 | PAD_TRIGGER_R);
						}
						if ((DbgMenuPcs.GetDbgFlagsRaw() & 0x100) != 0)
						{
							uVar16 = static_cast<int>(*reinterpret_cast<s8*>(p12 + 0x14)) >> 0x1F;
							if ((static_cast<int>((uVar16 ^ static_cast<int>(*reinterpret_cast<u8*>(p12 + 0x14))) - uVar16) >= pad->m_stickDigitalThreshold) ||
								((uVar16 = static_cast<int>(*reinterpret_cast<s8*>(p12 + 0x15)) >> 0x1F),
								 (static_cast<int>((uVar16 ^ static_cast<int>(*reinterpret_cast<s8*>(p12 + 0x15))) - uVar16) >= pad->m_stickDigitalThreshold)))
							{
								*puVar12 = static_cast<u16>(*puVar12 & 0xFFF0);
								*reinterpret_cast<u32*>(p12 + 0x3C) = 1;
								if (pad->m_stickDigitalThreshold <= static_cast<int>(*reinterpret_cast<s8*>(p12 + 0x14)))
								{
									*puVar12 = static_cast<u16>(*puVar12 | PAD_BUTTON_RIGHT);
								}
								if (-static_cast<int>(pad->m_stickDigitalThreshold) >= static_cast<int>(*reinterpret_cast<s8*>(p12 + 0x14)))
								{
									*puVar12 = static_cast<u16>(*puVar12 | PAD_BUTTON_LEFT);
								}
								if (pad->m_stickDigitalThreshold <= static_cast<int>(*reinterpret_cast<s8*>(p12 + 0x15)))
								{
									*puVar12 = static_cast<u16>(*puVar12 | PAD_BUTTON_UP);
								}
								if (-static_cast<int>(pad->m_stickDigitalThreshold) >= static_cast<int>(*reinterpret_cast<s8*>(p12 + 0x15)))
								{
									*puVar12 = static_cast<u16>(*puVar12 | PAD_BUTTON_DOWN);
								}
							}
						}
						*reinterpret_cast<u32*>(p12 + 0x44) = *reinterpret_cast<u32*>(p12 + 0x44) | 1;
						*reinterpret_cast<u8*>(p12 + 0x14) = *reinterpret_cast<u8*>(puVar13 + 1);
						*reinterpret_cast<u16*>(p12 + 0x0A) = 0;
						if (*reinterpret_cast<s8*>(p12 + 0x14) < 0)
						{
							*reinterpret_cast<u16*>(p12 + 0x0A) = *reinterpret_cast<u16*>(p12 + 0x0A) | 1;
						}
						if (0 < *reinterpret_cast<s8*>(p12 + 0x14))
						{
							*reinterpret_cast<u16*>(p12 + 0x0A) = *reinterpret_cast<u16*>(p12 + 0x0A) | 2;
						}
						*reinterpret_cast<u8*>(p12 + 0x15) = *reinterpret_cast<u8*>(reinterpret_cast<u8*>(puVar13) + 3);
						if (*reinterpret_cast<s8*>(p12 + 0x15) < 0)
						{
							*reinterpret_cast<u16*>(p12 + 0x0A) = *reinterpret_cast<u16*>(p12 + 0x0A) | 4;
						}
						if (0 < *reinterpret_cast<s8*>(p12 + 0x15))
						{
							*reinterpret_cast<u16*>(p12 + 0x0A) = *reinterpret_cast<u16*>(p12 + 0x0A) | 8;
						}
						fVar2 = kPadAnalogScale;
						fVar3 = kPadTriggerMax;
						*reinterpret_cast<u8*>(p12 + 0x16) = *reinterpret_cast<u8*>(puVar13 + 2);
						*reinterpret_cast<u8*>(p12 + 0x17) = *reinterpret_cast<u8*>(reinterpret_cast<u8*>(puVar13) + 5);
						*reinterpret_cast<u8*>(p12 + 0x12) = *reinterpret_cast<u8*>(puVar13 + 3);
						*reinterpret_cast<u8*>(p12 + 0x13) = *reinterpret_cast<u8*>(reinterpret_cast<u8*>(puVar13) + 7);
						*reinterpret_cast<float*>(p12 + 0x20) =
							static_cast<float>(*reinterpret_cast<s8*>(p12 + 0x14)) * fVar2;
						*reinterpret_cast<float*>(p12 + 0x24) =
							static_cast<float>(*reinterpret_cast<s8*>(p12 + 0x15)) * fVar2;
						*reinterpret_cast<float*>(p12 + 0x28) =
							static_cast<float>(*reinterpret_cast<s8*>(p12 + 0x16)) * fVar2;
						*reinterpret_cast<float*>(p12 + 0x2C) =
							static_cast<float>(*reinterpret_cast<s8*>(p12 + 0x17)) * fVar2;
						*reinterpret_cast<float*>(p12 + 0x18) =
							static_cast<float>(*reinterpret_cast<u8*>(p12 + 0x12)) / fVar3;
						*reinterpret_cast<float*>(p12 + 0x1C) =
							static_cast<float>(*reinterpret_cast<u8*>(p12 + 0x13)) / fVar3;
					}
					else
					{
						*puVar12 = 0;
						fVar2 = kPadAnalogZero;
						*reinterpret_cast<u8*>(p12 + 0x14) = 0;
						*reinterpret_cast<u8*>(p12 + 0x15) = 0;
						*reinterpret_cast<u8*>(p12 + 0x16) = 0;
						*reinterpret_cast<u8*>(p12 + 0x17) = 0;
						*reinterpret_cast<u8*>(p12 + 0x12) = 0;
						*reinterpret_cast<u8*>(p12 + 0x13) = 0;
						*reinterpret_cast<float*>(p12 + 0x20) = fVar2;
						*reinterpret_cast<float*>(p12 + 0x24) = fVar2;
						*reinterpret_cast<float*>(p12 + 0x28) = fVar2;
						*reinterpret_cast<float*>(p12 + 0x2C) = fVar2;
						*reinterpret_cast<float*>(p12 + 0x18) = fVar2;
						*reinterpret_cast<float*>(p12 + 0x1C) = fVar2;
					}
				}
				else if (reinterpret_cast<CPad::Gba*>(puVar18)->connected)
				{
					uVar8 = puVar18[1];
					*reinterpret_cast<u32*>(p12 + 0x44) = *reinterpret_cast<u32*>(p12 + 0x44) | 1;
					*puVar12 = uVar8;
				}
				puVar12[2] = static_cast<u16>(*puVar12 & (puVar12[0x26] ^ *puVar12));
				if (iVar14 == 0)
				{
					*reinterpret_cast<u16*>(p12 + 0x0E) =
						static_cast<u16>(puVar12[0x26] & (puVar12[0x26] ^ *puVar12));
					*reinterpret_cast<u16*>(p12 + 0x0C) =
						static_cast<u16>(*reinterpret_cast<u16*>(p12 + 0x0A) &
						                 (*reinterpret_cast<u16*>(p12 + 0x08) ^ *reinterpret_cast<u16*>(p12 + 0x0A)));
					*reinterpret_cast<u16*>(p12 + 0x10) = static_cast<u16>(puVar12[0x26] & *puVar12 & 0x1F7F);
					if (*reinterpret_cast<u16*>(p12 + 0x10) != 0)
					{
						*reinterpret_cast<int*>(p12 + 0x48) = *reinterpret_cast<int*>(p12 + 0x48) + 1;
						if (*reinterpret_cast<u32*>(p12 + 0x48) < 0x10)
						{
							*reinterpret_cast<u16*>(p12 + 0x10) = 0;
						}
						else if ((*reinterpret_cast<u32*>(p12 + 0x48) & 1) != 0)
						{
							*reinterpret_cast<u16*>(p12 + 0x10) = 0;
						}
					}
					else
					{
						*reinterpret_cast<u32*>(p12 + 0x48) = 0;
					}
					*reinterpret_cast<u16*>(p12 + 0x10) =
						static_cast<u16>(*reinterpret_cast<u16*>(p12 + 0x10) | puVar12[2]);
					if (*reinterpret_cast<int*>(p12 + 0x38) != 0)
					{
						*reinterpret_cast<u16*>(p12 + 0x30) = *puVar12;
						*reinterpret_cast<u16*>(p12 + 0x32) = puVar12[2];
						*reinterpret_cast<u16*>(p12 + 0x34) = *reinterpret_cast<u16*>(p12 + 0x10);
						*reinterpret_cast<u16*>(p12 + 0x0A) = 0;
						*reinterpret_cast<u16*>(p12 + 0x0C) = 0;
						*reinterpret_cast<u16*>(p12 + 0x10) = 0;
						puVar12[2] = 0;
						*reinterpret_cast<u16*>(p12 + 0x0E) = 0;
						*puVar12 = 0;
					}
					else
					{
						*reinterpret_cast<u16*>(p12 + 0x34) = 0;
						*reinterpret_cast<u16*>(p12 + 0x32) = 0;
						*reinterpret_cast<u16*>(p12 + 0x30) = 0;
					}
				}
				puVar7[2] = static_cast<u16>(puVar7[2] | puVar12[2]);
				*puVar7 = static_cast<u16>(*puVar7 | *puVar12);
				if (iVar14 == 0)
				{
					u8* p10 = reinterpret_cast<u8*>(puVar10);
					*reinterpret_cast<u32*>(p10 + 0x38) =
						*reinterpret_cast<u32*>(p10 + 0x38) | *reinterpret_cast<u32*>(p12 + 0x38);
					*reinterpret_cast<u32*>(p10 + 0x3C) =
						*reinterpret_cast<u32*>(p10 + 0x3C) | *reinterpret_cast<u32*>(p12 + 0x3C);
					*reinterpret_cast<u16*>(p10 + 0x0E) =
						static_cast<u16>(*reinterpret_cast<u16*>(p10 + 0x0E) | *reinterpret_cast<u16*>(p12 + 0x0E));
					*reinterpret_cast<u16*>(p10 + 0x0A) =
						static_cast<u16>(*reinterpret_cast<u16*>(p10 + 0x0A) | *reinterpret_cast<u16*>(p12 + 0x0A));
					*reinterpret_cast<u16*>(p10 + 0x0C) =
						static_cast<u16>(*reinterpret_cast<u16*>(p10 + 0x0C) | *reinterpret_cast<u16*>(p12 + 0x0C));
					*reinterpret_cast<s16*>(p10 + 0x10) =
						static_cast<u16>(*reinterpret_cast<u16*>(p10 + 0x10) | *reinterpret_cast<u16*>(p12 + 0x10));
					*reinterpret_cast<u16*>(p10 + 0x32) =
						static_cast<u16>(*reinterpret_cast<u16*>(p10 + 0x32) | *reinterpret_cast<u16*>(p12 + 0x32));
					*reinterpret_cast<u16*>(p10 + 0x30) =
						static_cast<u16>(*reinterpret_cast<u16*>(p10 + 0x30) | *reinterpret_cast<u16*>(p12 + 0x30));
					*reinterpret_cast<u16*>(p10 + 0x34) =
						static_cast<u16>(*reinterpret_cast<u16*>(p10 + 0x34) | *reinterpret_cast<u16*>(p12 + 0x34));
					cVar9 = *reinterpret_cast<s8*>(p12 + 0x14);
					uVar15 = static_cast<int>(*reinterpret_cast<s8*>(p10 + 0x14)) >> 0x1F;
					uVar16 = static_cast<int>(cVar9) >> 0x1F;
					if (static_cast<int>((uVar15 ^ static_cast<int>(*reinterpret_cast<s8*>(p10 + 0x14))) - uVar15) <
					    static_cast<int>((uVar16 ^ static_cast<int>(cVar9)) - uVar16))
					{
						*reinterpret_cast<s8*>(p10 + 0x14) = cVar9;
						*reinterpret_cast<float*>(p10 + 0x20) = *reinterpret_cast<float*>(p12 + 0x20);
					}
					cVar9 = *reinterpret_cast<s8*>(p12 + 0x15);
					uVar15 = static_cast<int>(*reinterpret_cast<s8*>(p10 + 0x15)) >> 0x1F;
					uVar16 = static_cast<int>(cVar9) >> 0x1F;
					if (static_cast<int>((uVar15 ^ static_cast<int>(*reinterpret_cast<s8*>(p10 + 0x15))) - uVar15) <
					    static_cast<int>((uVar16 ^ static_cast<int>(cVar9)) - uVar16))
					{
						*reinterpret_cast<s8*>(p10 + 0x15) = cVar9;
						*reinterpret_cast<float*>(p10 + 0x24) = *reinterpret_cast<float*>(p12 + 0x24);
					}
					cVar9 = *reinterpret_cast<s8*>(p12 + 0x16);
					uVar15 = static_cast<int>(*reinterpret_cast<s8*>(p10 + 0x16)) >> 0x1F;
					uVar16 = static_cast<int>(cVar9) >> 0x1F;
					if (static_cast<int>((uVar15 ^ static_cast<int>(*reinterpret_cast<s8*>(p10 + 0x16))) - uVar15) <
					    static_cast<int>((uVar16 ^ static_cast<int>(cVar9)) - uVar16))
					{
						*reinterpret_cast<s8*>(p10 + 0x16) = cVar9;
						*reinterpret_cast<float*>(p10 + 0x28) = *reinterpret_cast<float*>(p12 + 0x28);
					}
					cVar9 = *reinterpret_cast<s8*>(p12 + 0x17);
					uVar15 = static_cast<int>(*reinterpret_cast<s8*>(p10 + 0x17)) >> 0x1F;
					uVar16 = static_cast<int>(cVar9) >> 0x1F;
					if (static_cast<int>((uVar15 ^ static_cast<int>(*reinterpret_cast<s8*>(p10 + 0x17))) - uVar15) <
					    static_cast<int>((uVar16 ^ static_cast<int>(cVar9)) - uVar16))
					{
						*reinterpret_cast<s8*>(p10 + 0x17) = cVar9;
						*reinterpret_cast<float*>(p10 + 0x2C) = *reinterpret_cast<float*>(p12 + 0x2C);
					}
					if (*reinterpret_cast<u8*>(p10 + 0x12) < *reinterpret_cast<u8*>(p12 + 0x12))
					{
						*reinterpret_cast<u8*>(p10 + 0x12) = *reinterpret_cast<u8*>(p12 + 0x12);
						*reinterpret_cast<float*>(p10 + 0x18) = *reinterpret_cast<float*>(p12 + 0x18);
					}
					if (*reinterpret_cast<u8*>(p10 + 0x13) < *reinterpret_cast<u8*>(p12 + 0x13))
					{
						*reinterpret_cast<u8*>(p10 + 0x13) = *reinterpret_cast<u8*>(p12 + 0x13);
						*reinterpret_cast<float*>(p10 + 0x1C) = *reinterpret_cast<float*>(p12 + 0x1C);
					}
				}
			}
			puVar12 = puVar12 + 1;
			puVar7 = puVar7 + 1;
		}
		uVar17 = uVar17 + 1;
		puVar13 = puVar13 + 6;
		puVar18 = puVar18 + 2;
		iVar6 = iVar6 + 0x54;
	} while (uVar17 < 4);
}

/*
 * --INFO--
 * PAL Address: 0x80022168
 * PAL Size: 2876b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CPad::Frame()
{
	float fVar2;
	float fVar3;
	int iVar6;
	u16 uVar1;
	u16 uVar8;
	u16* puVar7;
	s8 cVar9;
	u16* puVar10;
	int iVar11;
	u16* puVar12;
	u16* puVar13;
	int iVar14;
	u32 port;
	u32 uVar15;
	u32 gbaIdx;
	u32 uVar16;
	u32 uVar17;
	u16* puVar18;
	int iVar19;
	CPad::Gba local_98[4];
	PADStatus local_88[4];
	u8* self = reinterpret_cast<u8*>(this);

	PADRead(local_88);
	PADClamp(local_88);
	memcpy(g_pad, local_88, sizeof(g_pad));
	*reinterpret_cast<u32*>(self + 0x1C4) = 0;
	port = 0;
	puVar18 = reinterpret_cast<u16*>(local_98);
	do
	{
		CPad::Gba* gba = &local_98[port];
		iVar6 = SIProbe(port);
		gba->connected = (0x40000 - iVar6) == 0;
		gba->ctrlMode = Joybus.GetCtrlMode(port);
		gba->noController = gba->connected && (gba->ctrlMode == 0);
		gba->button = 0;
		if (gba->connected)
		{
			gba->button = Joybus.GetPadData(port);
		}
		port = port + 1;
	} while (port < 4);

	if ((_1b0_4_ != 0) && ((iVar14 = _1bc_4_), iVar14 >= 0))
	{
		if (*reinterpret_cast<int*>(_1b0_4_ + 4) != 0)
		{
			if (*reinterpret_cast<int*>(_1b0_4_ + 8) < 0x1A5E0)
			{
				iVar6 = 0;
				iVar14 = 0;
				puVar7 = reinterpret_cast<u16*>(local_88);
				puVar13 = reinterpret_cast<u16*>(local_98);
				for (iVar19 = 0; iVar19 < 4; iVar19++)
				{
					uVar8 = *puVar13;
					uVar1 = puVar13[1];
					iVar11 = *reinterpret_cast<int*>(reinterpret_cast<int>(_1b0_4_) + 8) * 0x40 + iVar6;
					iVar6 = iVar6 + 0x0C;
					puVar13 = puVar13 + 2;
					puVar12 = reinterpret_cast<u16*>(reinterpret_cast<int>(_1b0_4_) + iVar11 + 0x0C);
					*puVar12 = *puVar7;
					*reinterpret_cast<u8*>(puVar12 + 1) = *reinterpret_cast<u8*>(puVar7 + 1);
					*reinterpret_cast<u8*>(reinterpret_cast<u8*>(puVar12) + 3) =
						*reinterpret_cast<u8*>(reinterpret_cast<u8*>(puVar7) + 3);
					*reinterpret_cast<u8*>(puVar12 + 2) = *reinterpret_cast<u8*>(puVar7 + 2);
					*reinterpret_cast<u8*>(reinterpret_cast<u8*>(puVar12) + 5) =
						*reinterpret_cast<u8*>(reinterpret_cast<u8*>(puVar7) + 5);
					*reinterpret_cast<u8*>(puVar12 + 3) = *reinterpret_cast<u8*>(puVar7 + 3);
					*reinterpret_cast<u8*>(reinterpret_cast<u8*>(puVar12) + 7) =
						*reinterpret_cast<u8*>(reinterpret_cast<u8*>(puVar7) + 7);
					*reinterpret_cast<u8*>(puVar12 + 4) = *reinterpret_cast<u8*>(puVar7 + 4);
					*reinterpret_cast<u8*>(reinterpret_cast<u8*>(puVar12) + 9) =
						*reinterpret_cast<u8*>(reinterpret_cast<u8*>(puVar7) + 9);
					puVar10 = puVar7 + 5;
					puVar7 = puVar7 + 6;
					*reinterpret_cast<u8*>(puVar12 + 5) = *reinterpret_cast<u8*>(puVar10);
					iVar11 = *reinterpret_cast<int*>(reinterpret_cast<int>(_1b0_4_) + 8) * 0x40 + iVar14;
					iVar14 = iVar14 + 4;
					puVar10 = reinterpret_cast<u16*>(reinterpret_cast<int>(_1b0_4_) + iVar11 + 0x3C);
					*puVar10 = uVar8;
					puVar10[1] = uVar1;
				}
				*reinterpret_cast<int*>(reinterpret_cast<int>(_1b0_4_) + 8) =
					*reinterpret_cast<int*>(reinterpret_cast<int>(_1b0_4_) + 8) + 1;
				*reinterpret_cast<int*>(_1b0_4_) = *reinterpret_cast<int*>(_1b0_4_) + 0x40;
			}
		}
		else if (iVar14 < 0x1A5E0)
		{
			iVar6 = 0;
			iVar19 = 0;
			puVar7 = reinterpret_cast<u16*>(local_88);
			puVar13 = reinterpret_cast<u16*>(local_98);
			for (iVar11 = 0; iVar11 < 4; iVar11++)
			{
				uVar8 = *puVar7;
				puVar10 = reinterpret_cast<u16*>(reinterpret_cast<int>(_1b0_4_) + iVar14 * 0x40 + iVar6 + 0x0C);
				*puVar7 = *puVar10;
				*reinterpret_cast<u8*>(puVar7 + 1) = *reinterpret_cast<u8*>(puVar10 + 1);
				*reinterpret_cast<u8*>(reinterpret_cast<u8*>(puVar7) + 3) =
					*reinterpret_cast<u8*>(reinterpret_cast<u8*>(puVar10) + 3);
				*reinterpret_cast<u8*>(puVar7 + 2) = *reinterpret_cast<u8*>(puVar10 + 2);
				*reinterpret_cast<u8*>(reinterpret_cast<u8*>(puVar7) + 5) =
					*reinterpret_cast<u8*>(reinterpret_cast<u8*>(puVar10) + 5);
				*reinterpret_cast<u8*>(puVar7 + 3) = *reinterpret_cast<u8*>(puVar10 + 3);
				*reinterpret_cast<u8*>(reinterpret_cast<u8*>(puVar7) + 7) =
					*reinterpret_cast<u8*>(reinterpret_cast<u8*>(puVar10) + 7);
				*reinterpret_cast<u8*>(puVar7 + 4) = *reinterpret_cast<u8*>(puVar10 + 4);
				*reinterpret_cast<u8*>(reinterpret_cast<u8*>(puVar7) + 9) =
					*reinterpret_cast<u8*>(reinterpret_cast<u8*>(puVar10) + 9);
				*reinterpret_cast<u8*>(puVar7 + 5) = *reinterpret_cast<u8*>(puVar10 + 5);
				puVar10 = reinterpret_cast<u16*>(reinterpret_cast<int>(_1b0_4_) + iVar14 * 0x40 + iVar19 + 0x3C);
				uVar1 = puVar10[1];
				*puVar13 = *puVar10;
				puVar13[1] = uVar1;
				if ((uVar8 & PAD_TRIGGER_Z) != 0)
				{
					*puVar7 = static_cast<u16>(*puVar7 | uVar8);
				}
				puVar7 = puVar7 + 6;
				iVar6 = iVar6 + 0x0C;
				iVar19 = iVar19 + 4;
				puVar13 = puVar13 + 2;
			}
		}
	}

	puVar13 = reinterpret_cast<u16*>(local_88);
	puVar10 = reinterpret_cast<u16*>(self + 0x154);
	uVar16 = 0;
	gbaIdx = 0;
	puVar7 = puVar13;
	do
	{
		cVar9 = *reinterpret_cast<s8*>(puVar7 + 5);
		uVar15 = 0x80000000 >> gbaIdx;
		if (cVar9 == -1)
		{
			goto gba_ready;
		}
		if (cVar9 >= -1)
		{
			goto flag_set_low;
		}
		if (cVar9 == -3)
		{
			goto flag_set_neg3;
		}
		if (cVar9 >= -3)
		{
			goto flag_clear;
		}
		goto flag_done;
	flag_set_low:
		if (cVar9 < 1)
		{
			_1a8_4_ = _1a8_4_ | uVar15;
		}
		goto flag_done;
	flag_set_neg3:
		_1a8_4_ = _1a8_4_ | uVar15;
		goto flag_done;
	gba_ready:
		if (static_cast<u8>(Joybus.GBAReady(gbaIdx)) == 0)
		{
			uVar16 = uVar16 | uVar15;
		}
		_1a8_4_ = _1a8_4_ & ~uVar15;
		goto flag_done;
	flag_clear:
		_1a8_4_ = _1a8_4_ & ~uVar15;
	flag_done:
		gbaIdx = gbaIdx + 1;
		puVar7 = puVar7 + 6;
	} while (gbaIdx < 4);

	if ((uVar16 & 0xF0000000) != 0)
	{
		PADReset(uVar16 & 0xF0000000);
	}

	MergePadInputs(this, puVar13, puVar18, puVar10);

	if (_1bc_4_ >= 0)
	{
		_1bc_4_ = _1bc_4_ + 1;
	}
}

#pragma always_inline off

/*
 * --INFO--
 * PAL Address: 0x80020fb0
 * PAL Size: 88b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CPad::Quit()
{
	if (_1b0_4_ != 0)
	{
		delete[] _1b0_4_;
		_1b0_4_ = 0;
	}

	CMemory::CStage* stage = reinterpret_cast<CMemory::CStage*>(_1ac_4_);
	if (stage != 0)
	{
		Memory.DestroyStage(stage);
	}
}

/*
 * --INFO--
 * PAL Address: 0x80021008
 * PAL Size: 416b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CPad::Init()
{
	FILE* fp;
	int frames;
	int size;

	PADInit();
	memset(m_padInputs, 0, sizeof(m_padInputs));
	_1a8_4_ = 0;
	_1ac_4_ = 0;
	_1b0_4_ = 0;
	_1bc_4_ = 0;
	m_debugPadPort = 0xFFFFFFFF;
	m_stickDigitalThreshold = 1;

	if (System.IsGdev())
	{
		_1ac_4_ = Memory.CreateStage(0x800000, const_cast<char*>(s_CPad), 1);
		if (_1ac_4_ != 0)
		{
			_1b0_4_ = new (reinterpret_cast<CMemory::CStage*>(_1ac_4_), const_cast<char*>(s_pad_cpp), 0x54)
				unsigned char[0x69780C];
			if ((_1b4_4_ != 0) && ((fp = fopen(s_replay_dat, s_rb)) != 0))
			{
				fseek(fp, 0, 2);
				size = ftell(fp);
				fseek(fp, 0, 0);
				fread(_1b0_4_, 1, size, fp);
				fclose(fp);
				*reinterpret_cast<unsigned int*>(_1b0_4_ + 4) = 0;
				frames = *reinterpret_cast<int*>(_1b0_4_ + 8);
				System.Printf(const_cast<char*>(s_replay_host_msg), frames / 30);
			}
			else
			{
				*reinterpret_cast<unsigned int*>(_1b0_4_) = 0xC;
				*reinterpret_cast<unsigned int*>(_1b0_4_ + 8) = 0;
				*reinterpret_cast<unsigned int*>(_1b0_4_ + 4) = 1;
			}
		}
	}
}
