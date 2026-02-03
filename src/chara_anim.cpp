#include "ffcc/chara_anim.h"
#include "ffcc/chunkfile.h"


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
 * Address:	TODO
 * Size:	TODO
 */
CChara::CAnim::CAnim()
{
	// Initialize base CRef
	
	// Set member variables to default values
	*(unsigned short*)((char*)this + 0xe) = 0;
	*(int*)((char*)this + 0x14) = 0;
	*(void**)((char*)this + 0x20) = 0;
	
	// Set various flags and values
	*(unsigned char*)((char*)this + 0x9) = 0x80 | 0x0; // Set bit 7, clear bit 6
	*(unsigned char*)((char*)this + 0xa) = 5;
	*(unsigned char*)((char*)this + 0xb) = 0xb;
	*(unsigned char*)((char*)this + 0xc) = 10;
	*(unsigned char*)((char*)this + 0xd) = 0;
	
	*(void**)((char*)this + 0x18) = 0;
	*(void**)((char*)this + 0x28) = 0;
	*(int*)((char*)this + 0x1c) = 0;
	*(void**)((char*)this + 0x2c) = 0;
	*(int*)((char*)this + 0x24) = 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CChara::CAnim::~CAnim()
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CChara::CAnim::InitQuantize()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CChara::CAnimNode::CAnimNode()
{
	// TODO
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
