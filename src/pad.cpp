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
extern void* __vt__8CManager;
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
	char* const base = reinterpret_cast<char*>(&Pad);
	*reinterpret_cast<void**>(base) = &__vt__8CManager;
	*reinterpret_cast<void**>(base) = &lbl_801E8864;
	Pad._448_4_ = 0;
	Pad._452_4_ = 0;
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
	char* const base = reinterpret_cast<char*>(this);
	PADInit();
	memset(base + 4, 0, 0x1A4);

	*reinterpret_cast<unsigned int*>(base + 0x1A8) = 0;
	*reinterpret_cast<unsigned int*>(base + 0x1AC) = 0;
	*reinterpret_cast<unsigned int*>(base + 0x1B0) = 0;
	*reinterpret_cast<unsigned int*>(base + 0x1BC) = 0;
	*reinterpret_cast<unsigned int*>(base + 0x1C0) = 0xFFFFFFFF;
	*reinterpret_cast<unsigned int*>(base + 0x1C8) = 1;

	if (!System.IsGdev())
	{
		return;
	}

	CMemory::CStage* stage = Memory.CreateStage(0x800000, (char*)"pad.cpp", 1);
	*reinterpret_cast<CMemory::CStage**>(base + 0x1AC) = stage;
	if (stage == nullptr)
	{
		return;
	}

	unsigned char* replayBuf = new (stage, (char*)"pad.cpp", 0x54) unsigned char[0x69780C];
	*reinterpret_cast<unsigned char**>(base + 0x1B0) = replayBuf;
	if (replayBuf == nullptr)
	{
		return;
	}

	if ((*reinterpret_cast<int*>(base + 0x1B4) == 0))
	{
		reinterpret_cast<int*>(replayBuf)[0] = 0xC;
		reinterpret_cast<int*>(replayBuf)[1] = 1;
		reinterpret_cast<int*>(replayBuf)[2] = 0;
		return;
	}

	FILE* fp = fopen("replay.dat", "rb");
	if (fp == nullptr)
	{
		reinterpret_cast<int*>(replayBuf)[0] = 0xC;
		reinterpret_cast<int*>(replayBuf)[1] = 1;
		reinterpret_cast<int*>(replayBuf)[2] = 0;
		return;
	}

	fseek(fp, 0, 2);
	unsigned int size = ftell(fp);
	fseek(fp, 0, 0);
	fread(replayBuf, 1, size, fp);
	fclose(fp);

	reinterpret_cast<unsigned int*>(replayBuf)[1] = 0;
	int frames = reinterpret_cast<int*>(replayBuf)[2];
	frames = frames / 0x1E + (frames >> 0x1F);
	System.Printf((char*)"replay frames=%d\n", frames - (frames >> 0x1F));
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
