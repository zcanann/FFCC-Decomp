#include "ffcc/pppCrystal.h"
#include "ffcc/memory.h"

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
	int iVar1;
	
	iVar1 = param_2->m_serializedDataOffsets[2];
	*(unsigned int*)((char*)pppCrystal + 8 + iVar1) = 0;
	*(unsigned int*)((char*)pppCrystal + 8 + iVar1 + 4) = 0;
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
	void* stage;
	void** puVar1;
	
	puVar1 = (void**)((char*)(pppCrystal) + 8 + param_2->m_serializedDataOffsets[2]);
	stage = puVar1[0];
	if ((stage != 0) && (*(void**)stage != 0)) {
		// TODO: pppHeapUseRate((CMemory::CStage*)*(void**)stage);
		*(void**)stage = 0;
	}
	if (stage != 0) {
		// TODO: pppHeapUseRate((CMemory::CStage*)stage);
	}
	if (puVar1[1] != 0) {
		// TODO: pppHeapUseRate((CMemory::CStage*)puVar1[1]);
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
	float fVar1;
	unsigned int uVar2;
	float fVar3;
	int iVar4;
	int iVar5;
	unsigned char uVar6;
	unsigned char* puVar7;
	int* piVar8;
	int* piVar9;
	unsigned int uVar10;
	unsigned int uVar11;
	double dVar12;
	unsigned int local_e4;
	
	if (*(int*)0x8032ed70 == 0) {
		piVar9 = (int*)((char*)pppCrystal + 8 + param_3->m_serializedDataOffsets[2]);
		if (param_2->m_dataValIndex != 0xffff) {
			local_e4 = 0;
			// GetTexture call - placeholder for now
			// GetTexture__8CMapMeshFP12CMaterialSetRi(...);
			
			if (param_2->m_payload[0] == '\0') {
				if (param_2->m_initWOrk == 0xffff) {
					return;
				}
				// GetTexture call - placeholder for now
			}
			
			if ((param_2->m_payload[0] == '\x01') && (*piVar9 == 0)) {
				// Memory allocation and texture setup
				// iVar4 = pppMemAlloc__FUlPQ27CMemory6CStagePci(...);
				// *piVar9 = iVar4;
				// ... complex texture generation code follows
				// DCFlushRange, GXInitTexObj calls
			}
		}
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
