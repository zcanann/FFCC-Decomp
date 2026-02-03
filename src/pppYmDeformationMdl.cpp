#include "ffcc/pppYmDeformationMdl.h"
#include "ffcc/pppYmEnv.h"
#include <dolphin/gx.h>
#include <dolphin/mtx.h>

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void SetUpIndWarp(VYmDeformationMdl*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void DisableIndWarp()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x800d20c0
 * PAL Size: 64b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstructYmDeformationMdl(void* pppYmDeformationMdl_, void* param_2)
{
	float fVar1 = 1.0f; // FLOAT_80330dac
	unsigned short* puVar2 = (unsigned short*)((char*)pppYmDeformationMdl_ + 0x80 + *((int*)param_2 + 2));
	
	*puVar2 = 0;
	*((unsigned char*)(puVar2 + 1)) = 1;
	*((float*)(puVar2 + 6)) = fVar1;
	*((float*)(puVar2 + 4)) = fVar1;
	*((float*)(puVar2 + 2)) = fVar1;
	*((float*)(puVar2 + 0xc)) = fVar1;
	*((float*)(puVar2 + 10)) = fVar1;
	*((float*)(puVar2 + 8)) = fVar1;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppConstruct2YmDeformationMdl(void)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x800d208c
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDestructYmDeformationMdl(void)
{
	return;
}

/*
 * --INFO--
 * PAL Address: 0x800d1f58
 * PAL Size: 308b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppFrameYmDeformationMdl(void* pppYmDeformationMdl, void* param_2, void* param_3)
{
	// Global variables - may need to be declared properly
	static int DAT_8032ed70 = 0;
	static char DAT_8032ed78 = '\0';
	
	short* psVar1;
	
	if ((DAT_8032ed70 == 0) &&
		(psVar1 = (short*)((char*)pppYmDeformationMdl + 0x80 + *((int*)param_3 + 2)),
		*((unsigned short*)param_2 + 1) != 0xffff)) {
		
		CalcGraphValue((_pppPObject*)pppYmDeformationMdl, *((long*)param_2),
			*(float*)(psVar1 + 2), *(float*)(psVar1 + 4), *(float*)(psVar1 + 6),
			*((float*)param_2 + 2), *((float*)param_2 + 3), *((float*)param_2 + 4));
			
		CalcGraphValue((_pppPObject*)pppYmDeformationMdl, *((long*)param_2),
			*(float*)(psVar1 + 8), *(float*)(psVar1 + 10), *(float*)(psVar1 + 0xc),
			*((float*)param_2 + 5), *((float*)param_2 + 6), *((float*)param_2 + 7));
			
		if (DAT_8032ed78 == '\0') {
			if (*((char*)(psVar1 + 1)) == '\0') {
				*psVar1 = *psVar1 - (short)(int)*(float*)(psVar1 + 8);
				if ((int)*psVar1 < -(int)*((short*)param_2 + 12)) {
					*((unsigned char*)(psVar1 + 1)) = 1;
				}
			} else {
				*psVar1 = *psVar1 + (short)(int)*(float*)(psVar1 + 8);
				if (*((short*)param_2 + 12) < *psVar1) {
					*((unsigned char*)(psVar1 + 1)) = 0;
				}
			}
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x800d19f0
 * PAL Size: 1384b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRenderYmDeformationMdl(void* pppYmDeformationMdl, void* param_2, void* param_3)
{
	unsigned int local_19c[4];
	float local_18c, local_188, local_184, local_180;
	float local_17c, local_178, local_174, local_170;
	float local_16c, local_168, local_164, local_160;
	float local_12c, local_128, local_11c, local_118;
	Mtx local_fc, MStack_cc, MStack_5c;
	unsigned int local_28, uStack_24, local_20, uStack_1c;
	
	// Initialize arrays
	local_19c[3] = 0;
	
	short* psVar4 = (short*)((char*)pppYmDeformationMdl + 0x80 + *((int*)param_3 + 2));
	
	if (*((unsigned short*)param_2 + 1) != 0xffff) {
		int iVar2 = *((int*)param_3 + 1);
		
		// TODO: Get pppModelSt from pppEnvStPtr->m_mapMeshPtr[param_2->m_dataValIndex]
		// TODO: GetTexture call
		
		PSMTXIdentity(MStack_5c);
		
		// TODO: Matrix calculations and transformations
		
		// GX setup calls
		GXSetNumTevStages(1);
		GXSetNumTexGens(2);
		GXSetNumChans(1);
		
		// TODO: Additional GX configuration calls
		// GXSetTevOrder, GXSetTevColorIn, GXSetTevColorOp, etc.
		
		// TODO: Texture binding and rendering logic
		// TODO: Model rendering with deformation
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
