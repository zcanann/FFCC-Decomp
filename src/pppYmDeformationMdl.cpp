#include "ffcc/pppYmDeformationMdl.h"

extern int DAT_8032ed70;
extern u8 DAT_8032ed78;

extern void CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf(float, void*, int, float*, float*, float*, float*, float*);

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
void pppConstruct2YmDeformationMdl(pppYmDeformationMdl* pppYmDeformationMdl_, UnkC* param_2)
{
    float fVar1;
    int iVar2;

    fVar1 = 1.0f;
    iVar2 = param_2->m_serializedDataOffsets[2];
    *(float*)((u8*)pppYmDeformationMdl_ + 0x8C + iVar2) = 1.0f;
    *(float*)((u8*)pppYmDeformationMdl_ + 0x88 + iVar2) = fVar1;
    *(float*)((u8*)pppYmDeformationMdl_ + 0x84 + iVar2) = fVar1;
    *(float*)((u8*)pppYmDeformationMdl_ + 0x98 + iVar2) = fVar1;
    *(float*)((u8*)pppYmDeformationMdl_ + 0x94 + iVar2) = fVar1;
    *(float*)((u8*)pppYmDeformationMdl_ + 0x90 + iVar2) = fVar1;
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
void pppFrameYmDeformationMdl(pppYmDeformationMdl* pppYmDeformationMdl, UnkB* param_2, UnkC* param_3)
{
    s16* psVar1;

    if ((DAT_8032ed70 == 0) && (param_2->m_dataValIndex != 0xFFFF)) {
        psVar1 = (s16*)((u8*)pppYmDeformationMdl + 0x80 + param_3->m_serializedDataOffsets[2]);

        CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf(
            (float)param_2->m_initWOrk, pppYmDeformationMdl, param_2->m_graphId, (float*)(psVar1 + 2),
            (float*)(psVar1 + 4), (float*)(psVar1 + 6), &param_2->m_stepValue, &param_2->m_arg3);
        CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf(
            *param_2->m_payload, pppYmDeformationMdl, param_2->m_graphId, (float*)(psVar1 + 8),
            (float*)(psVar1 + 10), (float*)(psVar1 + 0xC), param_2->m_payload + 1, param_2->m_payload + 2);

        if (DAT_8032ed78 == 0) {
            if (*(u8*)(psVar1 + 1) == 0) {
                *psVar1 = *psVar1 - (s16)(int)*(float*)(psVar1 + 8);
                if ((int)*psVar1 < -(int)(s16)param_2->m_payload[3]) {
                    *(u8*)(psVar1 + 1) = 1;
                }
            } else {
                *psVar1 = *psVar1 + (s16)(int)*(float*)(psVar1 + 8);
                if ((s16)param_2->m_payload[3] < *psVar1) {
                    *(u8*)(psVar1 + 1) = 0;
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
