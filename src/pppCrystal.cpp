#include "ffcc/pppCrystal.h"
#include "ffcc/memory.h"
#include "ffcc/pppPart.h"

#include <dolphin/gx.h>
#include <math.h>

extern int DAT_8032ed70;
extern "C" unsigned int __cvt_fp2unsigned(double);
extern "C" void* pppMemAlloc__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);

int GetTexture__8CMapMeshFP12CMaterialSetRi(CMapMesh* mapMesh, CMaterialSet* materialSet, int& textureIndex);

static char s_pppCrystalCpp[] = "pppCrystal.cpp";

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void ImageBufferSetPixel_IA8(HSD_ImageBuffer*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void MakeRefractionMap(HSD_ImageBuffer*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	800dd404
 * Size:	32b
 */
void pppConstructCrystal(struct pppCrystal* pppCrystal, struct UnkC* param_2)
{
	s32 iVar1 = param_2->m_serializedDataOffsets[2];
	u32* data = (u32*)((char*)pppCrystal + iVar1 + 8);

	data[0] = 0;
	data[1] = 0;
}

/*
 * --INFO--
 * PAL Address: 0x800dd37c
 * PAL Size: 136b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDestructCrystal(struct pppCrystal* pppCrystal, struct UnkC* param_2)
{
	CMemory::CStage* stage;
	u32* puVar1;
	
	puVar1 = (u32*)((char*)pppCrystal + 8 + param_2->m_serializedDataOffsets[2]);
	stage = (CMemory::CStage*)puVar1[0];
	if ((stage != 0) && (*(CMemory::CStage**)stage != 0)) {
		pppHeapUseRate(*(CMemory::CStage**)stage);
		*(u32*)stage = 0;
	}
	if (stage != 0) {
		pppHeapUseRate(stage);
	}
	if ((CMemory::CStage*)puVar1[1] != 0) {
		pppHeapUseRate((CMemory::CStage*)puVar1[1]);
		puVar1[1] = 0;
	}
}

/*
 * --INFO--
 * Address:	800dcf44
 * Size:	1080b
 */
void pppFrameCrystal(struct pppCrystal* pppCrystal, struct UnkB* param_2, struct UnkC* param_3)
{
	int* refractionData;
	int* textureInfo;
	u16 dataValIndex;
	u16 initWork;
	u8* payload;
	int textureIndex;
	int textureBase;
	int textureSize;
	u32 y;
	u32 x;

	if (DAT_8032ed70 != 0) {
		return;
	}

	refractionData = (int*)((u8*)pppCrystal + param_3->m_serializedDataOffsets[2] + 8);
	dataValIndex = *(u16*)((u8*)param_2 + 4);
	if (dataValIndex == 0xFFFF) {
		return;
	}

	payload = (u8*)param_2 + 0x14;
	textureIndex = 0;
	textureBase = GetTexture__8CMapMeshFP12CMaterialSetRi(
		&pppEnvStPtr->m_mapMeshPtr[dataValIndex], pppEnvStPtr->m_materialSetPtr, textureIndex);
	(void)textureBase;

	if (payload[0] == 0) {
		initWork = *(u16*)((u8*)param_2 + 8);
		if (initWork == 0xFFFF) {
			return;
		}
		GetTexture__8CMapMeshFP12CMaterialSetRi(
			&pppEnvStPtr->m_mapMeshPtr[initWork], pppEnvStPtr->m_materialSetPtr, textureIndex);
	}

	if ((payload[0] != 1) || (refractionData[0] != 0)) {
		return;
	}

	refractionData[0] = (int)pppMemAlloc__FUlPQ27CMemory6CStagePci(
		0x18, pppEnvStPtr->m_stagePtr, s_pppCrystalCpp, 0xA7);
	if (refractionData[0] == 0) {
		return;
	}

	textureInfo = (int*)refractionData[0];
	textureSize = (int)GXGetTexBufferSize(0x20, 0x20, GX_TF_IA8, GX_FALSE, 0);
	textureInfo[0] = (int)pppMemAlloc__FUlPQ27CMemory6CStagePci(
		textureSize, pppEnvStPtr->m_stagePtr, s_pppCrystalCpp, 0xAC);
	textureInfo[1] = GX_TF_IA8;
	textureInfo[2] = 0x20;
	textureInfo[3] = 0x20;
	textureInfo[4] = 0x100;
	textureInfo[5] = textureSize;

	if (textureInfo[0] == 0) {
		return;
	}

	{
		const float start = -1.0f;
		const float step = 2.0f / (float)(textureInfo[2] - 1);
		float yy = start;

		for (y = 0; y < (u32)textureInfo[3]; ++y) {
			float xx = start;
			const float y2 = yy * yy;

			for (x = 0; x < (u32)textureInfo[2]; ++x) {
				float magnitude = xx * xx + y2;
				float normal = 0.0f;

				if (magnitude > 1.0f) {
					normal = 1.0f / sqrtf(magnitude);
				} else if (magnitude > 0.0f) {
					normal = sqrtf(magnitude);
				}

				if (normal > 0.8f) {
					normal = 0.8f;
				}

				{
					const u8 nx =
						(u8)__cvt_fp2unsigned((double)(xx * normal * 127.0f + 128.0f));
					const u8 ny =
						(u8)__cvt_fp2unsigned((double)(yy * normal * 127.0f + 128.0f));
					u8* pixel = (u8*)(textureInfo[0] +
						(y >> 2) * (textureInfo[2] & 0x1FFFFFFCU) * 8 +
						(x & 0x1FFFFFFC) * 8 +
						((x & 3) + (y & 3) * 4) * 2);

					pixel[0] = nx;
					pixel[1] = ny;
				}
				xx += step;
			}
			yy += step;
		}
	}

	DCFlushRange((void*)textureInfo[0], textureInfo[5]);
	refractionData[1] = (int)pppMemAlloc__FUlPQ27CMemory6CStagePci(
		0x20, pppEnvStPtr->m_stagePtr, s_pppCrystalCpp, 0xB4);
	if (refractionData[1] != 0) {
		GXInitTexObj((GXTexObj*)refractionData[1], (void*)textureInfo[0], (u16)textureInfo[2],
			(u16)textureInfo[3], GX_TF_IA8, GX_CLAMP, GX_CLAMP, GX_FALSE);
	}
}

/*
 * --INFO--
 * Address:	800dc9a0
 * Size:	1444b
 */
void pppRenderCrystal(struct pppCrystal* pppCrystal, struct UnkB* param_2, struct UnkC* param_3)
{
	float fVar1;
	float fVar2;
	int iVar3;
	int iVar4;
	int iVar5;
	int iVar6;
	int iVar7;
	void* pppModelSt;
	unsigned int local_c0;
	
	iVar6 = param_3->m_serializedDataOffsets[2];
	iVar3 = param_3->m_serializedDataOffsets[1];
	
	if (param_2->m_dataValIndex != 0xffff) {
		iVar7 = 0;
		// pppModelSt = (pppModelSt*)pppEnvStPtr->m_mapMeshPtr[param_2->m_dataValIndex];
		local_c0 = 0;
		// iVar4 = GetTexture__8CMapMeshFP12CMaterialSetRi(...);
		
		if (param_2->m_payload[0] == '\0') {
			if (param_2->m_initWOrk == 0xffff) {
				return;
			}
			// iVar7 = GetTexture__8CMapMeshFP12CMaterialSetRi(...);
		}
		
		// Graphics setup and rendering calls would go here
		// pppSetBlendMode, pppSetDrawEnv, texture operations, etc.
	}
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
