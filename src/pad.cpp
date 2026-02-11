#include "ffcc/pad.h"

#include "ffcc/memory.h"
#include "ffcc/system.h"

#include "dolphin/pad.h"

#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/file_io.h"
#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/FILE_POS.h"
#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/direct_io.h"

#include <string.h>

CPad Pad;

void* operator new[](unsigned long, CMemory::CStage*, char*, int);
extern void* lbl_801E8864;

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
	Pad._0_4_ = &lbl_801E8864;
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
		operator delete(replayBuf);
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
	// Frame update for controller input
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
