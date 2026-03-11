#include "ffcc/pppLight.h"
#include "ffcc/p_light.h"
#include "ffcc/ppp_default_buffer.h"
#include "ffcc/ppp_linkage.h"
#include "ffcc/partMng.h"
#include "ffcc/symbols_shared.h"
#include "dolphin/mtx.h"

extern unsigned char gPppInSubFrameCalc;

struct pppLightTarget {
	int unk0;
	unsigned char* obj;
	int unk8;
	int unkC;
};

extern "C" {
void __ct__Q29CLightPcs6CLightFv(void*);
void Add__9CLightPcsFPQ29CLightPcs6CLight(void*, void*);
}

/*
 * --INFO--
 * PAL Address: 0x800dab00
 * PAL Size: 52b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppLightCon3(void* param1, void* param2)
{
	// Based on assembly: accesses param2+0xc, then deref twice, then +0x80
	// Stores zeros and a float constant to various offsets
	void** ptr1 = (void**)((char*)param2 + 0xc);
	void** ptr2 = (void**)*ptr1;
	void* ptr3 = *ptr2;
	char* base = (char*)param1 + (int)ptr3 + 0x80;
	float zero = kPppLightZero;
	
	// Clear some integer values
	*(int*)((char*)base + 0x10) = 0;
	*(int*)((char*)base + 0x14) = 0;
	
	// Set float values to 0.0f
	*(float*)((char*)base + 0x20) = zero;
	*(float*)((char*)base + 0x2c) = zero;
	*(float*)((char*)base + 0x38) = zero;
	*(float*)((char*)base + 0x44) = zero;
}

/*
 * --INFO--
 * PAL Address: 0x800dab34
 * PAL Size: 100b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppLightCon(void* param1, void* param2)
{
	// Similar pattern to pppLightCon3 but clears more values
	void** ptr1 = (void**)((char*)param2 + 0xc);
	void** ptr2 = (void**)*ptr1;
	void* ptr3 = *ptr2;
	char* base = (char*)param1 + (int)ptr3 + 0x80;
	float zero = kPppLightZero;
	
	// Clear integer values
	*(int*)((char*)base + 0x0) = 0;
	*(int*)((char*)base + 0x4) = 0;
	*(int*)((char*)base + 0x8) = 0;
	*(int*)((char*)base + 0xc) = 0;
	*(int*)((char*)base + 0x10) = 0;
	*(int*)((char*)base + 0x14) = 0;
	
	// Clear float values
	*(float*)((char*)base + 0x20) = zero;
	*(float*)((char*)base + 0x1c) = zero;
	*(float*)((char*)base + 0x18) = zero;
	*(float*)((char*)base + 0x2c) = zero;
	*(float*)((char*)base + 0x28) = zero;
	*(float*)((char*)base + 0x24) = zero;
	*(float*)((char*)base + 0x38) = zero;
	*(float*)((char*)base + 0x34) = zero;
	*(float*)((char*)base + 0x30) = zero;
	*(float*)((char*)base + 0x44) = zero;
	*(float*)((char*)base + 0x40) = zero;
	*(float*)((char*)base + 0x3c) = zero;
}

/*
 * --INFO--
 * PAL Address: 0x800dab98
 * PAL Size: 1276b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppLight(void* param1, void* param2, void* param3)
{
	unsigned char* lightParam = (unsigned char*)param2;
	_pppMngSt* pppMng = (_pppMngSt*)param1;

	if (gPppCalcDisabled != 0) {
		return;
	}

	{
		unsigned char* pppMngBytes = (unsigned char*)pppMng;
		unsigned char* work = (unsigned char*)pppMng + *(int*)(*(unsigned char**)((unsigned char*)param3 + 0xc)) + 0x80;
		CLightPcs::CLight lightData;
		Vec* sourcePos = (Vec*)&lightData.m_position;

		*(float*)(work + 0x1c) = *(float*)(work + 0x1c) + *(float*)(work + 0x20);
		*(float*)(work + 0x18) = *(float*)(work + 0x18) + *(float*)(work + 0x1c);
		*(float*)(work + 0x28) = *(float*)(work + 0x28) + *(float*)(work + 0x2c);
		*(float*)(work + 0x24) = *(float*)(work + 0x24) + *(float*)(work + 0x28);
		*(float*)(work + 0x34) = *(float*)(work + 0x34) + *(float*)(work + 0x38);
		*(float*)(work + 0x30) = *(float*)(work + 0x30) + *(float*)(work + 0x34);
		*(float*)(work + 0x40) = *(float*)(work + 0x40) + *(float*)(work + 0x44);
		*(float*)(work + 0x3c) = *(float*)(work + 0x3c) + *(float*)(work + 0x40);

		*(short*)(work + 0x8) = *(short*)(work + 0x8) + *(short*)(work + 0x10);
		*(short*)(work + 0xa) = *(short*)(work + 0xa) + *(short*)(work + 0x12);
		*(short*)(work + 0xc) = *(short*)(work + 0xc) + *(short*)(work + 0x14);
		*(short*)(work + 0xe) = *(short*)(work + 0xe) + *(short*)(work + 0x16);

		*(short*)(work + 0x0) = *(short*)(work + 0x0) + *(short*)(work + 0x8);
		*(short*)(work + 0x2) = *(short*)(work + 0x2) + *(short*)(work + 0xa);
		*(short*)(work + 0x4) = *(short*)(work + 0x4) + *(short*)(work + 0xc);
		*(short*)(work + 0x6) = *(short*)(work + 0x6) + *(short*)(work + 0xe);

		if (*(int*)lightParam == *(int*)(pppMngBytes + 0xc)) {
			*(short*)(work + 0x0) = *(short*)(work + 0x0) + *(short*)(lightParam + 0x8);
			*(short*)(work + 0x2) = *(short*)(work + 0x2) + *(short*)(lightParam + 0xa);
			*(short*)(work + 0x4) = *(short*)(work + 0x4) + *(short*)(lightParam + 0xc);
			*(short*)(work + 0x6) = *(short*)(work + 0x6) + *(short*)(lightParam + 0xe);
			*(short*)(work + 0x8) = *(short*)(work + 0x8) + *(short*)(lightParam + 0x10);
			*(short*)(work + 0xa) = *(short*)(work + 0xa) + *(short*)(lightParam + 0x12);
			*(short*)(work + 0xc) = *(short*)(work + 0xc) + *(short*)(lightParam + 0x14);
			*(short*)(work + 0xe) = *(short*)(work + 0xe) + *(short*)(lightParam + 0x16);
			*(short*)(work + 0x10) = *(short*)(work + 0x10) + *(short*)(lightParam + 0x18);
			*(short*)(work + 0x12) = *(short*)(work + 0x12) + *(short*)(lightParam + 0x1a);
			*(short*)(work + 0x14) = *(short*)(work + 0x14) + *(short*)(lightParam + 0x1c);
			*(short*)(work + 0x16) = *(short*)(work + 0x16) + *(short*)(lightParam + 0x1e);
			*(float*)(work + 0x18) = *(float*)(work + 0x18) + *(float*)(lightParam + 0x20);
			*(float*)(work + 0x1c) = *(float*)(work + 0x1c) + *(float*)(lightParam + 0x24);
			*(float*)(work + 0x20) = *(float*)(work + 0x20) + *(float*)(lightParam + 0x28);
			*(float*)(work + 0x24) = *(float*)(work + 0x24) + *(float*)(lightParam + 0x2c);
			*(float*)(work + 0x28) = *(float*)(work + 0x28) + *(float*)(lightParam + 0x30);
			*(float*)(work + 0x2c) = *(float*)(work + 0x2c) + *(float*)(lightParam + 0x34);
			*(float*)(work + 0x30) = *(float*)(work + 0x30) + *(float*)(lightParam + 0x38);
			*(float*)(work + 0x34) = *(float*)(work + 0x34) + *(float*)(lightParam + 0x3c);
			*(float*)(work + 0x38) = *(float*)(work + 0x38) + *(float*)(lightParam + 0x40);
			*(float*)(work + 0x3c) = *(float*)(work + 0x3c) + *(float*)(lightParam + 0x4c);
			*(float*)(work + 0x40) = *(float*)(work + 0x40) + *(float*)(lightParam + 0x50);
			*(float*)(work + 0x44) = *(float*)(work + 0x44) + *(float*)(lightParam + 0x54);
		}

		__ct__Q29CLightPcs6CLightFv(&lightData);

		sourcePos->x = *(float*)(pppMngBytes + 0x1c);
		sourcePos->y = *(float*)(pppMngBytes + 0x2c);
		sourcePos->z = *(float*)(pppMngBytes + 0x3c);
		PSMTXMultVec(pppMngStPtr->m_matrix.value, sourcePos, sourcePos);

		lightData.m_attenRadius = *(float*)(work + 0x24);
		lightData.m_attenFalloff = *(float*)(work + 0x18);

		lightData.m_targetColor[0].r = (unsigned char)(*(short*)(work + 0x0) >> 7);
		lightData.m_targetColor[0].g = (unsigned char)(*(short*)(work + 0x2) >> 7);
		lightData.m_targetColor[0].b = (unsigned char)(*(short*)(work + 0x4) >> 7);
		lightData.m_targetColor[0].a = (unsigned char)(*(short*)(work + 0x6) >> 7);

		if (lightParam[0x5a] != 0) {
			lightData.m_targetColor[1] = lightData.m_targetColor[0];
		} else {
			*(u32*)&lightData.m_targetColor[1] = 0;
		}

		if (lightParam[0x5b] != 0) {
			lightData.m_targetColor[2] = lightData.m_targetColor[0];
		} else {
			*(u32*)&lightData.m_targetColor[2] = 0;
		}

		if (lightParam[0x59] == 0) {
			*(u32*)&lightData.m_targetColor[0] = 0;
		}

		if (gPppInConstructor == 0 && gPppInSubFrameCalc == 0) {
			if (lightParam[0x58] == 0) {
				lightData.m_type = 0;
				lightData.m_direction.x = kPppLightZero;
				lightData.m_direction.y = kPppLightZero;
				lightData.m_direction.z = kPppLightOne;
				lightData.m_spotScale = kPppLightDefaultCosAtten;
				Add__9CLightPcsFPQ29CLightPcs6CLight(&LightPcs, &lightData);
			} else {
				unsigned char* obj;
				Vec* direction;

				lightData.m_type = 1;
				if (*(int*)(lightParam + 0x44) == -1) {
					obj = gPppDefaultValueBuffer;
				} else {
					pppLightTarget* targetTable = (pppLightTarget*)pppMngStPtr->m_programInfoTable;
					obj = targetTable[*(int*)(lightParam + 0x44)].obj;
				}

				direction = (Vec*)&lightData.m_direction;
				direction->x = *(float*)(obj + 0x1c);
				direction->y = *(float*)(obj + 0x2c);
				direction->z = *(float*)(obj + 0x3c);
				PSMTXMultVec(pppMngStPtr->m_matrix.value, direction, direction);

				PSVECSubtract(direction, sourcePos, direction);
				PSVECNormalize(direction, direction);
				lightData.m_spotScale = kPppLightSpotScale * *(float*)(work + 0x30);

				if (lightParam[0x58] == 2) {
					lightData.m_specularScale = *(float*)(work + 0x3c);
					lightData.m_specularMode = 1;
				}

				Add__9CLightPcsFPQ29CLightPcs6CLight(&LightPcs, &lightData);
			}
		}
	}
}
