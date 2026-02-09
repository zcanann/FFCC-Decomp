#include "ffcc/chara_anim.h"
#include "ffcc/chunkfile.h"

#include <PowerPC_EABI_Support/Runtime/MWCPlusLib.h>

extern "C" void __ct__4CRefFv(void*);
extern "C" void __dt__4CRefFv(void*, int);
extern "C" void __dt__Q26CChara9CAnimNodeFv(void*, int);
extern "C" void __dla__FPv(void*);
extern "C" void gqrInit__6CCharaFUlUlUl(void*, unsigned long, unsigned long, unsigned long);

extern "C" unsigned char Chara[];
extern "C" void* PTR_PTR_s_CChara_CAnim_80210534;

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void i2f2_7(float*, unsigned short*, float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void i2f_7(float*, unsigned short*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void i2f2_6(float*, unsigned short*, float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void i2f_6(float*, unsigned short*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void i2f2_5(float*, unsigned short*, float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void i2f_5(float*, unsigned short*)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x800BFDE0
 * PAL Size: 152b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CChara::CAnim::CAnim()
{
	unsigned char* const p = (unsigned char*)this;

	__ct__4CRefFv(this);
	*(void**)p = &PTR_PTR_s_CChara_CAnim_80210534;
	*(unsigned short*)(p + 0xE) = 0;
	*(int*)(p + 0x14) = 0;
	*(void**)(p + 0x20) = 0;
	p[9] = (unsigned char)((p[9] & 0x7F) | 0x80);
	p[9] = (unsigned char)(p[9] & 0xBF);
	p[0xA] = 5;
	p[0xB] = 0xB;
	p[0xC] = 10;
	p[0xD] = 0;
	*(void**)(p + 0x18) = 0;
	*(void**)(p + 0x28) = 0;
	*(int*)(p + 0x1C) = 0;
	*(int*)(p + 0x24) = 0;
	*(void**)(p + 0x2C) = 0;
}

/*
 * --INFO--
 * PAL Address: 0x800BFD44
 * PAL Size: 156b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CChara::CAnim::~CAnim()
{
	unsigned char* const p = (unsigned char*)this;
	void* nodeArray;
	void* bank;

	*(void**)p = &PTR_PTR_s_CChara_CAnim_80210534;

	nodeArray = *(void**)(p + 0x14);
	if (nodeArray != 0) {
		__destroy_new_array(nodeArray, (ConstructorDestructor)__dt__Q26CChara9CAnimNodeFv);
		*(void**)(p + 0x14) = 0;
	}

	bank = *(void**)(p + 0x20);
	if (bank != 0) {
		__dla__FPv(bank);
		*(void**)(p + 0x20) = 0;
	}

	__dt__4CRefFv(this, 0);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CChara::CAnim::Create(void* data, CMemory::CStage* stage)
{
	// Store stage pointer
	*(CMemory::CStage**)((char*)this + 0x2c) = stage;
	
	// Initialize basic member variables
	*(short*)((char*)this + 0xe) = 0;
	*(void**)((char*)this + 0x14) = 0;
	*(void**)((char*)this + 0x20) = 0;
	*(int*)((char*)this + 0x1c) = 0;
	*(short*)((char*)this + 0x10) = 0;
	*(char*)((char*)this + 9) = 0;
	*(unsigned int*)((char*)this + 0x18) = 0;
	
	// TODO: Parse chunk file data when CChunkFile interface is available
}

/*
 * --INFO--
 * PAL Address: 0x800BF910
 * PAL Size: 116b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CChara::CAnim::InitQuantize()
{
	unsigned char* const p = (unsigned char*)this;
	unsigned long qx = ((unsigned long)p[0xA] << 0x18) | 0x70000 | ((unsigned long)p[0xA] << 8) | 7;
	unsigned long qy = ((unsigned long)p[0xB] << 0x18) | 0x70000 | ((unsigned long)p[0xB] << 8) | 7;
	unsigned long qz = ((unsigned long)p[0xC] << 0x18) | 0x70000 | ((unsigned long)p[0xC] << 8) | 7;

	gqrInit__6CCharaFUlUlUl(Chara, qx, qy, qz);
}

/*
 * --INFO--
 * PAL Address: 0x800BF8F0
 * PAL Size: 32b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CChara::CAnimNode::CAnimNode()
{
	unsigned char* const p = (unsigned char*)this;
	p[0x14] = (unsigned char)(p[0x14] & 0x7F);
	*(unsigned int*)(p + 0x14) &= 0x80001FFF;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CChara::CAnimNode::~CAnimNode()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CChara::CAnimNode::Create(CChunkFile&)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CChara::CAnimNode::Interp(CChara::CAnim* anim, SRT* srt, float frame)
{
	// Memory management for animation data
	if (*(int*)((char*)anim + 0x20) == 0) {
		// TODO: Allocate memory for animation data if needed
		return;
	}
	
	*(int*)((char*)anim + 0x24) = 0;
	
	float frameFloat = frame;
	unsigned int frameInt = (unsigned int)frameFloat;
	float frameFrac = frameFloat - (float)frameInt;
	
	if (frameInt == *(unsigned short*)((char*)anim + 0x10) - 1) {
		frameFrac = 0.0f;
	}
	
	unsigned int animFlags = *(unsigned int*)((char*)this + 0x14) >> 0xd & 0x3ffff;
	int frameIndex = frameInt * 2;
	float* animData = (float*)(*(int*)((char*)this + 0x10) + *(int*)((char*)anim + 0x20));
	float* outData = (float*)srt;
	
	// Process 3 components (likely translation)
	for (int i = 0; i < 3; i++) {
		unsigned int componentType = animFlags & 3;
		if (componentType == 0) {
			*outData = 0.0f;
		} else if (componentType == 1) {
			*outData = *animData;
			animData = (float*)((char*)animData + 2);
		} else {
			float value1 = *(float*)((char*)animData + frameIndex);
			float value2 = *(float*)((char*)animData + frameIndex + 2);
			*outData = (value2 - value1) * frameFrac + value1;
			animData = (float*)((char*)animData + (*(unsigned short*)((char*)anim + 0x10) + 1) * 2);
		}
		animFlags = animFlags >> 2;
		outData++;
	}
	
	// Process next 3 components (likely rotation)
	for (int i = 0; i < 3; i++) {
		unsigned int componentType = animFlags & 3;
		if (componentType == 0) {
			*outData = 0.0f;
		} else if (componentType == 1) {
			*outData = *animData;
			animData = (float*)((char*)animData + 2);
		} else {
			float value1 = *(float*)((char*)animData + frameIndex);
			float value2 = *(float*)((char*)animData + frameIndex + 2);
			*outData = (value2 - value1) * frameFrac + value1;
			animData = (float*)((char*)animData + (*(unsigned short*)((char*)anim + 0x10) + 1) * 2);
		}
		animFlags = animFlags >> 2;
		outData++;
	}
	
	// Process final 3 components (likely scale)  
	for (int i = 0; i < 3; i++) {
		unsigned int componentType = animFlags & 3;
		if (componentType == 0) {
			*outData = 1.0f;
		} else if (componentType == 1) {
			*outData = *animData;
			animData = (float*)((char*)animData + 2);
		} else {
			float value1 = *(float*)((char*)animData + frameIndex);
			float value2 = *(float*)((char*)animData + frameIndex + 2);
			*outData = (value2 - value1) * frameFrac + value1;
			animData = (float*)((char*)animData + (*(unsigned short*)((char*)anim + 0x10) + 1) * 2);
		}
		animFlags = animFlags >> 2;
		outData++;
	}
}
