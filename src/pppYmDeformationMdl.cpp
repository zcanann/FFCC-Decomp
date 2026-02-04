#include "ffcc/pppYmDeformationMdl.h"

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
void pppConstructYmDeformationMdl(pppYmDeformationMdl* pppYmDeformationMdl_, struct UnkC* param_2)
{
    float fVar1 = 1.0f; // FLOAT_80330dac equivalent 
    u16* puVar2 = (u16*)((u8*)pppYmDeformationMdl_ + 0x80 + param_2->m_serializedDataOffsets[2]);
    
    *puVar2 = 0;
    *(u8*)(puVar2 + 1) = 1;
    *(float*)(puVar2 + 6) = fVar1;
    *(float*)(puVar2 + 4) = fVar1;
    *(float*)(puVar2 + 2) = fVar1;
    *(float*)(puVar2 + 0xc) = fVar1;
    *(float*)(puVar2 + 10) = fVar1;
    *(float*)(puVar2 + 8) = fVar1;
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
	// TODO
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
