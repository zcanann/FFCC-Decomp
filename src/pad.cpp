#include "ffcc/pad.h"

#include "ffcc/memory.h"
#include "ffcc/system.h"
#include "ffcc/joybus.h"

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
	unsigned int size;

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
			if ((_1b4_4_ == 0) || ((fp = fopen("replay.dat", "rb")) == 0))
			{
				*reinterpret_cast<unsigned int*>(_1b0_4_) = 0xC;
				*reinterpret_cast<unsigned int*>(_1b0_4_ + 8) = 0;
				*reinterpret_cast<unsigned int*>(_1b0_4_ + 4) = 1;
			}
			else
			{
				fseek(fp, 0, 2);
				size = ftell(fp);
				fseek(fp, 0, 0);
				fread(_1b0_4_, 1, size, fp);
				fclose(fp);
				*reinterpret_cast<unsigned int*>(_1b0_4_ + 4) = 0;
				frames = *reinterpret_cast<int*>(_1b0_4_ + 8);
				frames = frames / 0x1E + (frames >> 0x1F);
				System.Printf((char*)"replay frames=%d\n", frames - (frames >> 0x1F));
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
 * PAL Address: TODO
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

	PADRead(status);
	PADClamp(status);

	_1c4_4_ = 0;
	for (int i = 0; i < 4; i++)
	{
		u16 ctrlMode = static_cast<u16>(Joybus.GetCtrlMode(i)) & 0x3FFF;
		u16 flags = static_cast<u16>((__cntlzw(0x40000 - SIProbe(i)) << 10) & 0x8000);
		u16 packedMode = static_cast<u16>(flags | ctrlMode);
		if (((packedMode & 0x8000) != 0) && ((packedMode & 0x3FFF) == 0))
		{
			packedMode = static_cast<u16>(packedMode | 0x4000);
		}

		joyBusData[i * 2] = packedMode;
		joyBusData[i * 2 + 1] = 0;
		if ((packedMode & 0x8000) != 0)
		{
			joyBusData[i * 2 + 1] = static_cast<u16>(Joybus.GetPadData(i));
		}
	}

	if ((_1b0_4_ != 0) && (_1bc_4_ >= 0))
	{
		int* replayFlags = reinterpret_cast<int*>(_1b0_4_ + 4);
		if (*replayFlags == 0)
		{
			if (_1bc_4_ < 0x1A5E0)
			{
				for (int i = 0; i < 4; i++)
				{
					u16 originalButtons = status[i].button;
					const u8* src = _1b0_4_ + _1bc_4_ * 0x40 + i * 0x0C + 0x0C;
					const u16* replayJoyBus = reinterpret_cast<const u16*>(_1b0_4_ + _1bc_4_ * 0x40 + i * 4 + 0x3C);
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
			int* replayFrames = reinterpret_cast<int*>(_1b0_4_ + 8);
			if (*replayFrames < 0x1A5E0)
			{
				for (int i = 0; i < 4; i++)
				{
					u8* dst = _1b0_4_ + *replayFrames * 0x40 + i * 0x0C + 0x0C;
					u16* dstJoyBus = reinterpret_cast<u16*>(_1b0_4_ + *replayFrames * 0x40 + i * 4 + 0x3C);
					*reinterpret_cast<PADStatus*>(dst) = status[i];
					dstJoyBus[0] = joyBusData[i * 2];
					dstJoyBus[1] = joyBusData[i * 2 + 1];
				}

				(*replayFrames)++;
				*reinterpret_cast<int*>(_1b0_4_) += 0x40;
			}
		}
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
