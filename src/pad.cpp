#include "ffcc/pad.h"

#include "ffcc/memory.h"
#include "ffcc/system.h"
#include "ffcc/joybus.h"
#include "ffcc/p_minigame.h"

#include "dolphin/pad.h"
#include "dolphin/si.h"

#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/file_io.h"
#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/FILE_POS.h"
#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/direct_io.h"

#include <string.h>

CPad Pad;

void* operator new[](unsigned long, CMemory::CStage*, char*, int);
extern "C" char __vt__8CManager[];
extern "C" char lbl_801E8864[];
extern CMiniGamePcs MiniGamePcs;
extern "C" unsigned char BYTE_ARRAY_8024430c[];
extern "C" float FLOAT_8032f820;
extern "C" float FLOAT_8032f824;
extern "C" float FLOAT_8032f828;
extern "C" double DOUBLE_8032f830;
extern "C" double DOUBLE_8032f838;

/*
 * --INFO--
 * PAL Address: 0x800211a8
 * PAL Size: 44b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void __sinit_pad_cpp()
{
	void* vtbl = __vt__8CManager;
	*reinterpret_cast<void**>(&Pad) = vtbl;
	*reinterpret_cast<void**>(&Pad) = lbl_801E8864;
	Pad._1b4_4_ = 0;
	Pad._1b8_4_ = 0;
}

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: TODO
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CPad::CPad()
{
	// TODO
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
	memset(reinterpret_cast<char*>(this) + 4, 0, 0x1A4);
	_1a8_4_ = 0;
	_1ac_4_ = 0;
	_1b0_4_ = 0;
	_1bc_4_ = 0;
	_1c0_4_ = 0xFFFFFFFF;
	_1c8_4_ = 1;

	if (System.IsGdev() != 0)
	{
		_1ac_4_ = Memory.CreateStage(0x800000, (char*)"pad.cpp", 1);
		if (_1ac_4_ != 0)
		{
			_1b0_4_ = new (reinterpret_cast<CMemory::CStage*>(_1ac_4_), (char*)"pad.cpp", 0x54) unsigned char[0x69780C];
			if ((_1b4_4_ != 0) && ((fp = fopen("replay.dat", "rb")) != 0))
			{
				fseek(fp, 0, 2);
				size = ftell(fp);
				fseek(fp, 0, 0);
				fread(_1b0_4_, 1, size, fp);
				fclose(fp);
				*reinterpret_cast<unsigned int*>(_1b0_4_ + 4) = 0;
				frames = *reinterpret_cast<int*>(_1b0_4_ + 8);
				System.Printf((char*)"replay frames=%d\n", frames / 30);
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
	char* const base = reinterpret_cast<char*>(this);
	void* replayBuf = *reinterpret_cast<void**>(base + 0x1B0);
	if (replayBuf != nullptr)
	{
		operator delete[](replayBuf);
		*reinterpret_cast<void**>(base + 0x1B0) = nullptr;
	}

	CMemory::CStage* stage = *reinterpret_cast<CMemory::CStage**>(base + 0x1AC);
	if (stage != nullptr)
	{
		Memory.DestroyStage(stage);
	}
}

/*
 * --INFO--
 * PAL Address: 0x80020494
 * PAL Size: 2844b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CPad::Frame()
{
	PADStatus status[4];
	u16 joyBusData[8];
	u16* joyBusDataPtr;
	u16* statusAsU16;
	u16* padStateBase;
	u16* padStateCursor;
	u16* statusCursor;
	u16* joyBusCursor;
	char* self = reinterpret_cast<char*>(this);

	PADRead(status);
	PADClamp(status);
	memcpy(BYTE_ARRAY_8024430c, status, 0x30);

	*reinterpret_cast<u32*>(self + 0x1C4) = 0;
	joyBusDataPtr = joyBusData;
	for (int i = 0; i < 4; i++)
	{
		int probe = SIProbe(i);
		int leading = __cntlzw(0x40000 - probe);
		*reinterpret_cast<u8*>(joyBusDataPtr) =
			static_cast<u8>(((leading << 2) & 0x80) | (*reinterpret_cast<u8*>(joyBusDataPtr) & 0x7F));

		u16 ctrlMode = static_cast<u16>(Joybus.GetCtrlMode(i));
		joyBusDataPtr[0] = static_cast<u16>((ctrlMode & 0x3FFF) | (joyBusDataPtr[0] & 0xC000));

		int setBit = 0;
		if ((static_cast<s8>(*reinterpret_cast<u8*>(joyBusDataPtr)) < 0) && ((joyBusDataPtr[0] & 0x3FFF) == 0))
		{
			setBit = 1;
		}
		*reinterpret_cast<u8*>(joyBusDataPtr) =
			static_cast<u8>((setBit << 6) | (*reinterpret_cast<u8*>(joyBusDataPtr) & 0xBF));

		joyBusDataPtr[1] = 0;
		if (static_cast<s8>(*reinterpret_cast<u8*>(joyBusDataPtr)) < 0)
		{
			joyBusDataPtr[1] = static_cast<u16>(Joybus.GetPadData(i));
		}
		joyBusDataPtr += 2;
	}

	if ((*reinterpret_cast<u32*>(self + 0x1B0) != 0) && (*reinterpret_cast<s32*>(self + 0x1BC) >= 0))
	{
		u8* replay = *reinterpret_cast<u8**>(self + 0x1B0);
		s32 frameIndex = *reinterpret_cast<s32*>(self + 0x1BC);
		int* replayFlags = reinterpret_cast<int*>(replay + 4);
		if (*replayFlags == 0)
		{
			if (frameIndex < 0x1A5E0)
			{
				for (int i = 0; i < 4; i++)
				{
					u16 originalButtons = status[i].button;
					const u8* src = replay + frameIndex * 0x40 + i * 0x0C + 0x0C;
					const u16* replayJoyBus = reinterpret_cast<const u16*>(replay + frameIndex * 0x40 + i * 4 + 0x3C);
					status[i] = *reinterpret_cast<const PADStatus*>(src);
					joyBusData[i * 2] = replayJoyBus[0];
					joyBusData[i * 2 + 1] = replayJoyBus[1];
					if ((originalButtons & PAD_TRIGGER_Z) != 0)
					{
						status[i].button = static_cast<u16>(status[i].button | originalButtons);
					}
				}
			}
		}
		else
		{
			int* replayFrames = reinterpret_cast<int*>(replay + 8);
			if (*replayFrames < 0x1A5E0)
			{
				for (int i = 0; i < 4; i++)
				{
					u8* dst = replay + *replayFrames * 0x40 + i * 0x0C + 0x0C;
					u16* dstJoyBus = reinterpret_cast<u16*>(replay + *replayFrames * 0x40 + i * 4 + 0x3C);
					*reinterpret_cast<PADStatus*>(dst) = status[i];
					dstJoyBus[0] = joyBusData[i * 2];
					dstJoyBus[1] = joyBusData[i * 2 + 1];
				}

				(*replayFrames)++;
				*reinterpret_cast<int*>(_1b0_4_) += 0x40;
			}
		}
	}

	u32 missingGbaMask = 0;
	statusAsU16 = reinterpret_cast<u16*>(status);
	for (u32 i = 0; i < 4; i++)
	{
		s8 err = *reinterpret_cast<s8*>(statusAsU16 + 5);
		u32 padMask = 0x80000000u >> i;

		if (err == -1)
		{
			if (Joybus.GBAReady(i) == 0)
			{
				missingGbaMask |= padMask;
			}
			*reinterpret_cast<u32*>(self + 0x1A8) &= ~padMask;
		}
		else if (err < -1)
		{
			if (err == -3)
			{
				*reinterpret_cast<u32*>(self + 0x1A8) |= padMask;
			}
			else if (err > -4)
			{
				*reinterpret_cast<u32*>(self + 0x1A8) &= ~padMask;
			}
		}
		else if (err < 1)
		{
			*reinterpret_cast<u32*>(self + 0x1A8) |= padMask;
		}
		statusAsU16 += 6;
	}

	if ((missingGbaMask & 0xF0000000) != 0)
	{
		PADReset(0);
	}

	padStateBase = reinterpret_cast<u16*>(self + 0x154);
	*reinterpret_cast<u16*>(self + 0x1A0) = *reinterpret_cast<u16*>(self + 0x154);
	*reinterpret_cast<u16*>(self + 0x158) = 0;
	*reinterpret_cast<u16*>(self + 0x154) = 0;
	*reinterpret_cast<u16*>(self + 0x1A2) = *reinterpret_cast<u16*>(self + 0x156);
	*reinterpret_cast<u16*>(self + 0x15A) = 0;
	*reinterpret_cast<u16*>(self + 0x156) = 0;
	*reinterpret_cast<u16*>(self + 0x15C) = *reinterpret_cast<u16*>(self + 0x15E);
	*reinterpret_cast<u32*>(self + 0x18C) = 0;
	*reinterpret_cast<u32*>(self + 0x190) = 0;
	*reinterpret_cast<u16*>(self + 0x15E) = 0;
	*reinterpret_cast<u16*>(self + 0x160) = 0;
	*reinterpret_cast<u16*>(self + 0x164) = 0;
	*reinterpret_cast<u16*>(self + 0x162) = 0;
	*reinterpret_cast<s8*>(self + 0x16B) = 0;
	*reinterpret_cast<s8*>(self + 0x16A) = 0;
	*reinterpret_cast<s8*>(self + 0x169) = 0;
	*reinterpret_cast<s8*>(self + 0x168) = 0;
	*reinterpret_cast<u8*>(self + 0x167) = 0;
	*reinterpret_cast<u8*>(self + 0x166) = 0;
	*reinterpret_cast<float*>(self + 0x180) = FLOAT_8032f820;
	*reinterpret_cast<float*>(self + 0x17C) = FLOAT_8032f820;
	*reinterpret_cast<float*>(self + 0x178) = FLOAT_8032f820;
	*reinterpret_cast<float*>(self + 0x174) = FLOAT_8032f820;
	*reinterpret_cast<float*>(self + 0x170) = FLOAT_8032f820;
	*reinterpret_cast<float*>(self + 0x16C) = FLOAT_8032f820;
	*reinterpret_cast<u16*>(self + 0x188) = 0;
	*reinterpret_cast<u16*>(self + 0x186) = 0;
	*reinterpret_cast<u16*>(self + 0x184) = 0;
	*reinterpret_cast<u32*>(self + 0x198) = 0;

	statusCursor = reinterpret_cast<u16*>(status);
	joyBusCursor = joyBusData;
	char* padInfo = self;
	for (u32 pad = 0; pad < 4; pad++)
	{
		padStateCursor = padStateBase;
		u16* playerButtons = reinterpret_cast<u16*>(padInfo + 4);
		for (int pass = 0; pass < 2; pass++)
		{
			if ((pass != 0) || (*reinterpret_cast<s8*>(statusCursor + 5) != -3))
			{
				playerButtons[0x26] = *reinterpret_cast<u16*>(padInfo + 0x34) | *playerButtons;

				if (pass == 0)
				{
					u16 ctrlPacked = *joyBusCursor;
					*reinterpret_cast<u16*>(padInfo + 0xC) = *reinterpret_cast<u16*>(padInfo + 0xE);
					*reinterpret_cast<s8*>(padInfo + 0x44) = *reinterpret_cast<s8*>(statusCursor + 5);
					*reinterpret_cast<u32*>(padInfo + 0x54) = (__cntlzw(1 - (ctrlPacked & 0x3FFF)) >> 5) & 0xFF;
					*reinterpret_cast<u32*>(padInfo + 0x48) = 0;
					*reinterpret_cast<u32*>(padInfo + 0x3C) = 0;
					*reinterpret_cast<u32*>(padInfo + 0x40) = 0;

					if ((*reinterpret_cast<s8*>(padInfo + 0x44) == 0) || ((ctrlPacked & 0x4000) != 0))
					{
						if ((ctrlPacked & 0x4000) == 0)
						{
							*playerButtons = *statusCursor;
						}
						else
						{
							*playerButtons = joyBusCursor[1];
						}

						if (*reinterpret_cast<u8*>(statusCursor + 3) > 99)
						{
							*playerButtons |= 0x40;
						}
						if (*reinterpret_cast<u8*>(reinterpret_cast<u8*>(statusCursor) + 7) > 99)
						{
							*playerButtons |= 0x20;
						}

						if ((*reinterpret_cast<u32*>(reinterpret_cast<u8*>(&MiniGamePcs) + 0x6484) & 0x100) != 0)
						{
							s8 stickX = *reinterpret_cast<s8*>(padInfo + 0x18);
							s8 stickY = *reinterpret_cast<s8*>(padInfo + 0x19);
							int absX = stickX < 0 ? -stickX : stickX;
							int absY = stickY < 0 ? -stickY : stickY;
							if ((*reinterpret_cast<s32*>(self + 0x1C8) <= absX) || (*reinterpret_cast<s32*>(self + 0x1C8) <= absY))
							{
								*playerButtons &= 0xFFF0;
								*reinterpret_cast<u32*>(padInfo + 0x40) = 1;
								if (*reinterpret_cast<s32*>(self + 0x1C8) <= stickX)
								{
									*playerButtons |= 2;
								}
								if (stickX <= -*reinterpret_cast<s32*>(self + 0x1C8))
								{
									*playerButtons |= 1;
								}
								if (*reinterpret_cast<s32*>(self + 0x1C8) <= stickY)
								{
									*playerButtons |= 8;
								}
								if (stickY <= -*reinterpret_cast<s32*>(self + 0x1C8))
								{
									*playerButtons |= 4;
								}
							}
						}

						*reinterpret_cast<u32*>(padInfo + 0x48) |= 1;
						*reinterpret_cast<s8*>(padInfo + 0x18) = *reinterpret_cast<s8*>(statusCursor + 1);
						*reinterpret_cast<u16*>(padInfo + 0xE) = 0;
						if (*reinterpret_cast<s8*>(padInfo + 0x18) < 0)
						{
							*reinterpret_cast<u16*>(padInfo + 0xE) |= 1;
						}
						if (*reinterpret_cast<s8*>(padInfo + 0x18) > 0)
						{
							*reinterpret_cast<u16*>(padInfo + 0xE) |= 2;
						}

						*reinterpret_cast<s8*>(padInfo + 0x19) = *reinterpret_cast<s8*>(reinterpret_cast<u8*>(statusCursor) + 3);
						if (*reinterpret_cast<s8*>(padInfo + 0x19) < 0)
						{
							*reinterpret_cast<u16*>(padInfo + 0xE) |= 4;
						}
						if (*reinterpret_cast<s8*>(padInfo + 0x19) > 0)
						{
							*reinterpret_cast<u16*>(padInfo + 0xE) |= 8;
						}

						*reinterpret_cast<s8*>(padInfo + 0x1A) = *reinterpret_cast<s8*>(statusCursor + 2);
						*reinterpret_cast<s8*>(padInfo + 0x1B) = *reinterpret_cast<s8*>(reinterpret_cast<u8*>(statusCursor) + 5);
						*reinterpret_cast<u8*>(padInfo + 0x16) = *reinterpret_cast<u8*>(statusCursor + 3);
						*reinterpret_cast<u8*>(padInfo + 0x17) = *reinterpret_cast<u8*>(reinterpret_cast<u8*>(statusCursor) + 7);

						*reinterpret_cast<float*>(padInfo + 0x24) =
							static_cast<float>((static_cast<double>(*reinterpret_cast<s8*>(padInfo + 0x18)) + DOUBLE_8032f830) - DOUBLE_8032f830) * FLOAT_8032f824;
						*reinterpret_cast<float*>(padInfo + 0x28) =
							static_cast<float>((static_cast<double>(*reinterpret_cast<s8*>(padInfo + 0x19)) + DOUBLE_8032f830) - DOUBLE_8032f830) * FLOAT_8032f824;
						*reinterpret_cast<float*>(padInfo + 0x2C) =
							static_cast<float>((static_cast<double>(*reinterpret_cast<s8*>(padInfo + 0x1A)) + DOUBLE_8032f830) - DOUBLE_8032f830) * FLOAT_8032f824;
						*reinterpret_cast<float*>(padInfo + 0x30) =
							static_cast<float>((static_cast<double>(*reinterpret_cast<s8*>(padInfo + 0x1B)) + DOUBLE_8032f830) - DOUBLE_8032f830) * FLOAT_8032f824;
						*reinterpret_cast<float*>(padInfo + 0x1C) =
							static_cast<float>((static_cast<double>(*reinterpret_cast<u8*>(padInfo + 0x16)) + DOUBLE_8032f838) - DOUBLE_8032f838) / FLOAT_8032f828;
						*reinterpret_cast<float*>(padInfo + 0x20) =
							static_cast<float>((static_cast<double>(*reinterpret_cast<u8*>(padInfo + 0x17)) + DOUBLE_8032f838) - DOUBLE_8032f838) / FLOAT_8032f828;
					}
					else
					{
						*playerButtons = 0;
						*reinterpret_cast<s8*>(padInfo + 0x18) = 0;
						*reinterpret_cast<s8*>(padInfo + 0x19) = 0;
						*reinterpret_cast<s8*>(padInfo + 0x1A) = 0;
						*reinterpret_cast<s8*>(padInfo + 0x1B) = 0;
						*reinterpret_cast<u8*>(padInfo + 0x16) = 0;
						*reinterpret_cast<u8*>(padInfo + 0x17) = 0;
						*reinterpret_cast<float*>(padInfo + 0x24) = FLOAT_8032f820;
						*reinterpret_cast<float*>(padInfo + 0x28) = FLOAT_8032f820;
						*reinterpret_cast<float*>(padInfo + 0x2C) = FLOAT_8032f820;
						*reinterpret_cast<float*>(padInfo + 0x30) = FLOAT_8032f820;
						*reinterpret_cast<float*>(padInfo + 0x1C) = FLOAT_8032f820;
						*reinterpret_cast<float*>(padInfo + 0x20) = FLOAT_8032f820;
					}
				}
				else if ((*joyBusCursor & 0x8000) != 0)
				{
					*reinterpret_cast<u32*>(padInfo + 0x48) |= 1;
					*playerButtons = joyBusCursor[1];
				}

				playerButtons[2] = *playerButtons & (playerButtons[0x26] ^ *playerButtons);
				if (pass == 0)
				{
					*reinterpret_cast<u16*>(padInfo + 0x12) = playerButtons[0x26] & (playerButtons[0x26] ^ *playerButtons);
					*reinterpret_cast<u16*>(padInfo + 0x10) = *reinterpret_cast<u16*>(padInfo + 0xE) &
						(*reinterpret_cast<u16*>(padInfo + 0xC) ^ *reinterpret_cast<u16*>(padInfo + 0xE));
					*reinterpret_cast<u16*>(padInfo + 0x14) = playerButtons[0x26] & *playerButtons & 0x1F7F;
					if (*reinterpret_cast<s16*>(padInfo + 0x14) == 0)
					{
						*reinterpret_cast<u32*>(padInfo + 0x4C) = 0;
					}
					else
					{
						(*reinterpret_cast<u32*>(padInfo + 0x4C))++;
						if ((*reinterpret_cast<u32*>(padInfo + 0x4C) < 0x10) ||
							((*reinterpret_cast<u32*>(padInfo + 0x4C) & 1) != 0))
						{
							*reinterpret_cast<u16*>(padInfo + 0x14) = 0;
						}
					}

					*reinterpret_cast<u16*>(padInfo + 0x14) |= playerButtons[2];
					if (*reinterpret_cast<u32*>(padInfo + 0x3C) == 0)
					{
						*reinterpret_cast<u16*>(padInfo + 0x38) = 0;
						*reinterpret_cast<u16*>(padInfo + 0x36) = 0;
						*reinterpret_cast<u16*>(padInfo + 0x34) = 0;
					}
					else
					{
						*reinterpret_cast<u16*>(padInfo + 0x34) = *playerButtons;
						*reinterpret_cast<u16*>(padInfo + 0x36) = playerButtons[2];
						*reinterpret_cast<u16*>(padInfo + 0x38) = *reinterpret_cast<u16*>(padInfo + 0x14);
						*reinterpret_cast<u16*>(padInfo + 0xE) = 0;
						*reinterpret_cast<u16*>(padInfo + 0x10) = 0;
						*reinterpret_cast<u16*>(padInfo + 0x14) = 0;
						playerButtons[2] = 0;
						*reinterpret_cast<u16*>(padInfo + 0x12) = 0;
						*playerButtons = 0;
					}
				}

				padStateCursor[2] |= playerButtons[2];
				padStateCursor[0] |= *playerButtons;
				if (pass == 0)
				{
					*reinterpret_cast<u32*>(self + 0x18C) |= *reinterpret_cast<u32*>(padInfo + 0x3C);
					*reinterpret_cast<u32*>(self + 0x190) |= *reinterpret_cast<u32*>(padInfo + 0x40);
					*reinterpret_cast<u16*>(self + 0x162) |= *reinterpret_cast<u16*>(padInfo + 0x12);
					*reinterpret_cast<u16*>(self + 0x15E) |= *reinterpret_cast<u16*>(padInfo + 0xE);
					*reinterpret_cast<u16*>(self + 0x160) |= *reinterpret_cast<u16*>(padInfo + 0x10);
					*reinterpret_cast<u16*>(self + 0x164) |= *reinterpret_cast<u16*>(padInfo + 0x14);
					*reinterpret_cast<u16*>(self + 0x186) |= *reinterpret_cast<u16*>(padInfo + 0x36);
					*reinterpret_cast<u16*>(self + 0x184) |= *reinterpret_cast<u16*>(padInfo + 0x34);
					*reinterpret_cast<u16*>(self + 0x188) |= *reinterpret_cast<u16*>(padInfo + 0x38);

					s8 lx = *reinterpret_cast<s8*>(padInfo + 0x18);
					s8 curLx = *reinterpret_cast<s8*>(self + 0x168);
					s32 absCurLx = curLx < 0 ? -curLx : curLx;
					s32 absLx = lx < 0 ? -lx : lx;
					if (absCurLx < absLx)
					{
						*reinterpret_cast<s8*>(self + 0x168) = lx;
						*reinterpret_cast<float*>(self + 0x174) = *reinterpret_cast<float*>(padInfo + 0x24);
					}

					s8 ly = *reinterpret_cast<s8*>(padInfo + 0x19);
					s8 curLy = *reinterpret_cast<s8*>(self + 0x169);
					s32 absCurLy = curLy < 0 ? -curLy : curLy;
					s32 absLy = ly < 0 ? -ly : ly;
					if (absCurLy < absLy)
					{
						*reinterpret_cast<s8*>(self + 0x169) = ly;
						*reinterpret_cast<float*>(self + 0x178) = *reinterpret_cast<float*>(padInfo + 0x28);
					}

					s8 rx = *reinterpret_cast<s8*>(padInfo + 0x1A);
					s8 curRx = *reinterpret_cast<s8*>(self + 0x16A);
					s32 absCurRx = curRx < 0 ? -curRx : curRx;
					s32 absRx = rx < 0 ? -rx : rx;
					if (absCurRx < absRx)
					{
						*reinterpret_cast<s8*>(self + 0x16A) = rx;
						*reinterpret_cast<float*>(self + 0x17C) = *reinterpret_cast<float*>(padInfo + 0x2C);
					}

					s8 ry = *reinterpret_cast<s8*>(padInfo + 0x1B);
					s8 curRy = *reinterpret_cast<s8*>(self + 0x16B);
					s32 absCurRy = curRy < 0 ? -curRy : curRy;
					s32 absRy = ry < 0 ? -ry : ry;
					if (absCurRy < absRy)
					{
						*reinterpret_cast<s8*>(self + 0x16B) = ry;
						*reinterpret_cast<float*>(self + 0x180) = *reinterpret_cast<float*>(padInfo + 0x30);
					}

					if (*reinterpret_cast<u8*>(self + 0x166) < *reinterpret_cast<u8*>(padInfo + 0x16))
					{
						*reinterpret_cast<u8*>(self + 0x166) = *reinterpret_cast<u8*>(padInfo + 0x16);
						*reinterpret_cast<float*>(self + 0x16C) = *reinterpret_cast<float*>(padInfo + 0x1C);
					}

					if (*reinterpret_cast<u8*>(self + 0x167) < *reinterpret_cast<u8*>(padInfo + 0x17))
					{
						*reinterpret_cast<u8*>(self + 0x167) = *reinterpret_cast<u8*>(padInfo + 0x17);
						*reinterpret_cast<float*>(self + 0x170) = *reinterpret_cast<float*>(padInfo + 0x20);
					}
				}
			}

			playerButtons++;
			padStateCursor++;
		}

		statusCursor += 6;
		joyBusCursor += 2;
		padInfo += 0x54;
		padStateBase += 2;
	}

	if (*reinterpret_cast<s32*>(self + 0x1BC) >= 0)
	{
		(*reinterpret_cast<s32*>(self + 0x1BC))++;
	}
}

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: TODO
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CPad::SaveReplayData()
{
	// TODO
}
