#include "ffcc/pppBlurChara.h"
#include "ffcc/partMng.h"
#include <dolphin/gx.h>

extern unsigned int DAT_8032ed70;
extern unsigned char MaterialMan[];
extern _pppEnvSt* pppEnvStPtr;
extern _pppMngSt* pppMngStPtr;

extern "C" {
void* GetCharaHandlePtr__FP8CGObjectl(void*, long);
int GetCharaModelPtr__FPQ29CCharaPcs7CHandle(void*);
void* pppMemAlloc__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);
void pppHeapUseRate__FPQ27CMemory6CStage(void*);
}

/*
 * --INFO--
 * PAL Address: 0x800de6d8
 * PAL Size: 64b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void BlurChara_SetBeforeMeshLockEnvCallback(CChara::CModel*, void*, void*, int)
{
	GXSetZMode(0, GX_LEQUAL, 0);
	*(unsigned int*)(MaterialMan + 0x48) |= 0x10000;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void BlurChara_AfterDrawModelCallback(CChara::CModel*, void*, void*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GXSetTexCoordGen(void)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x800de22c
 * PAL Size: 112b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstructBlurChara(pppBlurChara* blurChara, UnkC* data)
{
	int dataOffset = data->m_serializedDataOffsets[2];
	unsigned int* state = (unsigned int*)((char*)blurChara + dataOffset + 0x80);
	void* charaObj = *(void**)((char*)pppMngStPtr + 0x8);
	void* handle = GetCharaHandlePtr__FP8CGObjectl(charaObj, 0);
	int model = GetCharaModelPtr__FPQ29CCharaPcs7CHandle(handle);

	state[1] = (unsigned int)charaObj;
	*(void**)(model + 0x108) = (void*)BlurChara_AfterDrawModelCallback;
	state[0] = 0;
	state[2] = 0;
	state[3] = *(unsigned int*)(model + 0x9c);
}

/*
 * --INFO--
 * PAL Address: 0x800de194
 * PAL Size: 152b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDestructBlurChara(pppBlurChara* blurChara, UnkC* data)
{
	int dataOffset = data->m_serializedDataOffsets[2];
	unsigned int* state = (unsigned int*)((char*)blurChara + dataOffset + 0x80);
	void* handle = GetCharaHandlePtr__FP8CGObjectl((void*)state[1], 0);
	int model = GetCharaModelPtr__FPQ29CCharaPcs7CHandle(handle);

	*(void**)(model + 0x108) = 0;
	*(void**)(model + 0xe4) = 0;
	*(void**)(model + 0xe8) = 0;

	if (state[0] != 0) {
		pppHeapUseRate__FPQ27CMemory6CStage((void*)state[0]);
		state[0] = 0;
	}
	if (state[2] != 0) {
		pppHeapUseRate__FPQ27CMemory6CStage((void*)state[2]);
		state[2] = 0;
	}

	*(unsigned int*)(model + 0x9c) = state[3];
}

/*
 * --INFO--
 * PAL Address: 0x800de0ac
 * PAL Size: 232b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppFrameBlurChara(pppBlurChara* blurChara, UnkB* stepData, UnkC* data)
{
	if (DAT_8032ed70 != 0) {
		return;
	}

	int dataOffset = data->m_serializedDataOffsets[2];
	unsigned int* state = (unsigned int*)((char*)blurChara + dataOffset + 0x80);
	void* handle = GetCharaHandlePtr__FP8CGObjectl(*(void**)((char*)pppMngStPtr + 0x8), 0);
	int model = GetCharaModelPtr__FPQ29CCharaPcs7CHandle(handle);

	*(void**)(model + 0xe4) = state;
	*(UnkB**)(model + 0xe8) = stepData;

	if (state[0] == 0) {
		unsigned int size = GXGetTexBufferSize(0x140, 0xe0, GX_TF_RGBA8, GX_FALSE, 0);
		state[0] = (unsigned int)pppMemAlloc__FUlPQ27CMemory6CStagePci(
		    size, pppEnvStPtr->m_stagePtr, (char*)"pppBlurChara.cpp", 0xd5);
		state[2] = (unsigned int)pppMemAlloc__FUlPQ27CMemory6CStagePci(
		    0x20, pppEnvStPtr->m_stagePtr, (char*)"pppBlurChara.cpp", 0xd7);

		*(void**)(model + 0xe4) = state;
		*(UnkB**)(model + 0xe8) = stepData;
		*(void (**)(CChara::CModel*, void*, void*, int))(model + 0xf4) = BlurChara_SetBeforeMeshLockEnvCallback;
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppRenderBlurChara(pppBlurChara*, UnkB*, UnkC*)
{
	// TODO
}
