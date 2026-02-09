#include "ffcc/pppYmDeformationScreen.h"

struct pppYmDeformationScreen;
struct YmDeformationScreenOffsetData {
	int unk0;
	int unk1;
	int offset;
};

struct YmDeformationScreenParam {
	char pad[0xc];
	YmDeformationScreenOffsetData* offsetData;
};

/*
 * --INFO--
 * PAL Address: 0x80098a94
 * PAL Size: 64b
 */
void pppConstructYmDeformationScreen(pppYmDeformationScreen* obj, void* param2)
{
	int offset = ((YmDeformationScreenParam*)param2)->offsetData->offset;
	char* basePtr = (char*)obj + offset + 0x80;
	float zero = 0.0f;

	*(short*)(basePtr + 0x4) = 0;
	*(char*)(basePtr + 0x6) = 1;
	*(float*)(basePtr + 0x10) = zero;
	*(float*)(basePtr + 0xc) = zero;
	*(float*)(basePtr + 0x8) = zero;
	*(float*)(basePtr + 0x1c) = zero;
	*(float*)(basePtr + 0x18) = zero;
	*(float*)(basePtr + 0x14) = zero;
}

/*
 * --INFO--
 * PAL Address: 0x80098a64
 * PAL Size: 48b
 */
void pppConstruct2YmDeformationScreen(pppYmDeformationScreen* obj, void* param2)
{
	float zero = 0.0f;
	int offset = ((YmDeformationScreenParam*)param2)->offsetData->offset;
	char* basePtr = (char*)obj + offset + 0x80;

	*(float*)(basePtr + 0x10) = zero;
	*(float*)(basePtr + 0xc) = zero;
	*(float*)(basePtr + 0x8) = zero;
	*(float*)(basePtr + 0x1c) = zero;
	*(float*)(basePtr + 0x18) = zero;
	*(float*)(basePtr + 0x14) = zero;
}

/*
 * --INFO--
 * PAL Address: 0x80098a60
 * PAL Size: 4b
 */
void pppDestructYmDeformationScreen(void)
{
	return;
}

/*
 * --INFO--
 * PAL Address: 0x8009885c
 * PAL Size: 516b
 */
void pppFrameYmDeformationScreen(pppYmDeformationScreen* param1, void* param2, void* param3)
{
	// TODO - implement based on Ghidra decomp
}

/*
 * --INFO--
 * PAL Address: 0x800981a8
 * PAL Size: 1716b
 */
void pppRenderYmDeformationScreen(pppYmDeformationScreen* param1, void* param2, void* param3)
{
	// TODO - implement based on Ghidra decomp
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void SetUpIndWarp(VYmDeformationScreen*)
{
	// TODO
}
