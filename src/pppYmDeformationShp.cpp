#include "ffcc/pppYmDeformationShp.h"

extern int DAT_8032ed70;
extern u8 DAT_8032ed78;
extern float FLOAT_803305f4;
extern "C" void CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf(float, void*, int, float*, float*, float*, float*, float*);

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void SetUpIndWarp(VYmDeformationShp*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void calcBoundaryBox(Vec&, Vec&, Vec4d*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void setVertexPos(Vec&, Vec&, Vec&, Vec&, float, char)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void setVertexPos(Vec*, char, float, float, float, float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void setVertexUV(Vec2d*, float, float, float, float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void calcScreenPos(Vec4d&, Vec&, float (*)[4], float (*)[4])
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void oddToEven(float&)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80090590
 * PAL Size: 76b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstructYmDeformationShp(pppYmDeformationShp* pppYmDeformationShp_, UnkC* param_2)
{
	float fVar1 = FLOAT_803305f4;
	u32* work = (u32*)((u8*)pppYmDeformationShp_ + 0x80 + param_2->m_serializedDataOffsets[2]);

	work[0] = 0;
	work[1] = 0;
	work[2] = 0;
	*(u16*)(work + 3) = 0;
	*(u8*)((u8*)(work + 3) + 2) = 1;
	((float*)work)[6] = fVar1;
	((float*)work)[5] = fVar1;
	((float*)work)[4] = fVar1;
	((float*)work)[9] = fVar1;
	((float*)work)[8] = fVar1;
	((float*)work)[7] = fVar1;
}

/*
 * --INFO--
 * PAL Address: 0x80090560
 * PAL Size: 48b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstruct2YmDeformationShp(pppYmDeformationShp* pppYmDeformationShp_, UnkC* param_2)
{
	int offset = param_2->m_serializedDataOffsets[2];
	float fVar1 = FLOAT_803305f4;

	*(float*)((u8*)pppYmDeformationShp_ + 0x98 + offset) = FLOAT_803305f4;
	*(float*)((u8*)pppYmDeformationShp_ + 0x94 + offset) = fVar1;
	*(float*)((u8*)pppYmDeformationShp_ + 0x90 + offset) = fVar1;
	*(float*)((u8*)pppYmDeformationShp_ + 0xa4 + offset) = fVar1;
	*(float*)((u8*)pppYmDeformationShp_ + 0xa0 + offset) = fVar1;
	*(float*)((u8*)pppYmDeformationShp_ + 0x9c + offset) = fVar1;
}

/*
 * --INFO--
 * PAL Address: 0x8009055c
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDestructYmDeformationShp(void)
{
	return;
}

/*
 * --INFO--
 * PAL Address: 0x80090438
 * PAL Size: 292b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppFrameYmDeformationShp(pppYmDeformationShp* pppYmDeformationShp_, UnkB* param_2, UnkC* param_3)
{
	s16* angle;

	if (DAT_8032ed70 != 0) {
		return;
	}

	angle = (s16*)((u8*)pppYmDeformationShp_ + 0x8c + param_3->m_serializedDataOffsets[2]);

	CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf(
		param_2->m_payload[0], pppYmDeformationShp_, param_2->m_graphId, (float*)(angle + 2), (float*)(angle + 4),
		(float*)(angle + 6), &param_2->m_payload[1], &param_2->m_payload[2]);
	CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf(
		param_2->m_payload[3], pppYmDeformationShp_, param_2->m_graphId, (float*)(angle + 8), (float*)(angle + 10),
		(float*)(angle + 12), &param_2->m_payload[4], &param_2->m_payload[5]);

	if (DAT_8032ed78 != 0) {
		return;
	}

	if (*(u8*)(angle + 1) == 0) {
		*angle = *angle - (s16)(int)*(float*)(angle + 8);
		if ((int)*angle < -(int)param_2->m_payload3) {
			*(u8*)(angle + 1) = 1;
		}
	} else {
		*angle = *angle + (s16)(int)*(float*)(angle + 8);
		if (param_2->m_payload3 < *angle) {
			*(u8*)(angle + 1) = 0;
		}
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void RenderDeformationShape(_pppPObject*, VYmDeformationShp*, Vec*, Vec2d*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppRenderYmDeformationShp(pppYmDeformationShp*, UnkB*, UnkC*)
{
	// TODO
}
