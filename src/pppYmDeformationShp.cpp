#include "ffcc/pppYmDeformationShp.h"
#include "ffcc/graphic.h"
#include "ffcc/mapmesh.h"

#include <dolphin/gx.h>
#include <dolphin/mtx.h>

extern int DAT_8032ed70;
extern u8 DAT_8032ed78;
extern void* DAT_8032ec70;
extern float FLOAT_803305f0;
extern float FLOAT_803305f4;
extern float FLOAT_803305f8;
extern CGraphic Graphic;

struct _pppEnvStYmDeformationShp {
	void* m_stagePtr;
	CMaterialSet* m_materialSetPtr;
	CMapMesh** m_mapMeshPtr;
};

extern _pppEnvStYmDeformationShp* pppEnvStPtr;

extern "C" void CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf(float, void*, int, float*, float*, float*, float*, float*);

extern "C" {
int GetTexture__8CMapMeshFP12CMaterialSetRi(CMapMesh* mapMesh, CMaterialSet* materialSet, int& textureIndex);
void pppSetBlendMode__FUc(unsigned char mode);
void pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(
	void* color, void* matrix, float z, unsigned char a3, unsigned char a4, unsigned char a5, unsigned char a6,
	unsigned char a7, unsigned char a8, unsigned char a9);
void _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(int stage, int rasSel, int texSel);
void _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(int comp0, int ref0, int op, int comp1, int ref1);
void _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(int stage, int texCoord, int texMap, int chan);
void _GXSetTevOp__F13_GXTevStageID10_GXTevMode(int stage, int mode);
void SetVtxFmt_POS_TEX0_TEX1__5CUtilFv(void* util);
int GetBackBufferRect__8CGraphicFRiRiRiRii(CGraphic* graphic, int& left, int& top, int& width, int& height, int copy);
void DisableIndWarp__F13_GXTevStageID16_GXIndTexStageID(int stage, int indStage);
}

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
 * PAL Address: 0x8008eec8
 * PAL Size: 2904b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRenderYmDeformationShp(pppYmDeformationShp* pppYmDeformationShp_, UnkB* param_2, UnkC* param_3)
{
	int textureIndex = 0;
	u8* work = (u8*)pppYmDeformationShp_ + 0x80 + param_3->m_serializedDataOffsets[2];
	u8* params = (u8*)param_2;
	float local_134;
	float local_130;
	float local_12c;
	float local_128;
	float local_124;
	float local_120;
	float local_11c;
	float local_118;
	float local_e4;
	float local_e0;
	float local_dc;
	float local_d8;
	float local_d4;
	float local_d0;
	float local_cc;
	float local_c8;
	float local_c4;
	float local_c0;
	float local_bc;
	float local_b8;
	Mtx rotMtx;
	float indMtx[2][3];

	if (param_2->m_dataValIndex == 0xFFFF) {
		return;
	}

	int colorOffset = param_3->m_serializedDataOffsets[1];
	int textureBase = GetTexture__8CMapMeshFP12CMaterialSetRi(
		pppEnvStPtr->m_mapMeshPtr[param_2->m_dataValIndex], pppEnvStPtr->m_materialSetPtr, textureIndex);

	pppSetBlendMode__FUc(1);
	_GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0, 0, 0);
	pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(
		(u8*)pppYmDeformationShp_ + 0x88 + colorOffset, (u8*)pppYmDeformationShp_ + 0x40, *(float*)(params + 0x2c), params[0x31], 0, 0, 0, 1,
		1, 0);

	GXSetNumTevStages(1);
	GXSetNumTexGens(2);
	GXSetNumChans(1);
	_GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(7, 0, 1, 7, 0);
	_GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0, 0, 0, 4);
	_GXSetTevOp__F13_GXTevStageID10_GXTevMode(0, 3);
	SetVtxFmt_POS_TEX0_TEX1__5CUtilFv(&DAT_8032ec70);
	GXLoadTexObj((GXTexObj*)(textureBase + 0x28), GX_TEXMAP1);
	GXSetNumIndStages(1);
	GXSetIndTexOrder(GX_INDTEXSTAGE0, GX_TEXCOORD1, GX_TEXMAP1);
	GXSetTevIndWarp(GX_TEVSTAGE0, GX_INDTEXSTAGE0, GX_TRUE, GX_ITW_0, GX_ITM_1);

	s16* angle = (s16*)(work + 0xc);
	if ((*angle == 0) || (*angle == 0x168)) {
		*angle = 1;
	}

	PSMTXRotRad(rotMtx, 'z', FLOAT_803305f0 * (float)*angle);
	float scale = *(float*)(work + 0x10);
	indMtx[0][0] = rotMtx[0][0] * scale;
	indMtx[0][1] = rotMtx[0][1] * scale;
	indMtx[1][0] = rotMtx[1][0] * scale;
	indMtx[1][1] = rotMtx[1][1] * scale;
	indMtx[0][2] = FLOAT_803305f4;
	indMtx[1][2] = FLOAT_803305f4;
	GXSetIndTexMtx(GX_ITM_1, indMtx, 1);

	if (params[0x26] == 0) {
		float quadSize = (float)params[8];
		if (params[0x28] == 0) {
			local_e4 = -quadSize;
			local_dc = FLOAT_803305f4;
			local_d0 = FLOAT_803305f4;
			local_c4 = FLOAT_803305f4;
			local_b8 = FLOAT_803305f4;
			local_e0 = quadSize;
			local_d8 = quadSize;
			local_d4 = quadSize;
			local_cc = quadSize;
			local_c8 = -quadSize;
			local_c0 = -quadSize;
			local_bc = -quadSize;
		} else if (params[0x28] == 1) {
			local_e4 = -quadSize;
			local_e0 = FLOAT_803305f4;
			local_d4 = FLOAT_803305f4;
			local_c8 = FLOAT_803305f4;
			local_bc = FLOAT_803305f4;
			local_dc = -quadSize;
			local_d8 = quadSize;
			local_d0 = -quadSize;
			local_cc = quadSize;
			local_c4 = quadSize;
			local_c0 = -quadSize;
			local_b8 = quadSize;
		} else {
			DisableIndWarp__F13_GXTevStageID16_GXIndTexStageID(1, 0);
			return;
		}

		local_134 = FLOAT_803305f4;
		local_130 = FLOAT_803305f4;
		local_12c = FLOAT_803305f8;
		local_128 = FLOAT_803305f4;
		local_124 = FLOAT_803305f8;
		local_120 = FLOAT_803305f8;
		local_11c = FLOAT_803305f4;
		local_118 = FLOAT_803305f8;
		RenderDeformationShape(
			(_pppPObject*)pppYmDeformationShp_, (VYmDeformationShp*)work, (Vec*)&local_e4, (Vec2d*)&local_134);
	} else {
		float size = (float)params[8];
		float split = (float)params[0x27];
		float uvSplit = (FLOAT_803305f8 / (size + size)) * (size - split);
		float uvRemainder = FLOAT_803305f8 - uvSplit;

		if (params[0x28] == 0) {
			local_e4 = -size;
			local_e0 = -split;
			local_d8 = -split;
			local_d4 = -split;
			local_cc = -split;
			local_c8 = split;
			local_c0 = -size;
			local_bc = split;
			local_dc = FLOAT_803305f4;
			local_d0 = FLOAT_803305f4;
			local_c4 = FLOAT_803305f4;
			local_b8 = FLOAT_803305f4;
		} else if (params[0x28] == 1) {
			local_e4 = -size;
			local_dc = -split;
			local_d8 = -split;
			local_d0 = -split;
			local_cc = -split;
			local_c4 = split;
			local_c0 = -size;
			local_b8 = split;
			local_e0 = FLOAT_803305f4;
			local_d4 = FLOAT_803305f4;
			local_c8 = FLOAT_803305f4;
			local_bc = FLOAT_803305f4;
		} else {
			DisableIndWarp__F13_GXTevStageID16_GXIndTexStageID(1, 0);
			return;
		}

		local_134 = FLOAT_803305f4;
		local_11c = FLOAT_803305f4;
		local_12c = uvSplit;
		local_128 = uvSplit;
		local_124 = uvSplit;
		local_118 = uvRemainder;
		local_130 = FLOAT_803305f4;
		local_120 = uvRemainder;
		RenderDeformationShape(
			(_pppPObject*)pppYmDeformationShp_, (VYmDeformationShp*)work, (Vec*)&local_e4, (Vec2d*)&local_134);

		if (params[0x28] == 0) {
			local_e4 = split;
			local_e0 = -split;
			local_d8 = size;
			local_d4 = -split;
			local_cc = size;
			local_c8 = split;
			local_c0 = split;
			local_bc = split;
			local_dc = FLOAT_803305f4;
			local_d0 = FLOAT_803305f4;
			local_c4 = FLOAT_803305f4;
			local_b8 = FLOAT_803305f4;
		} else {
			local_e4 = split;
			local_dc = -split;
			local_d8 = size;
			local_d0 = -split;
			local_cc = size;
			local_c4 = split;
			local_c0 = split;
			local_b8 = split;
			local_e0 = FLOAT_803305f4;
			local_d4 = FLOAT_803305f4;
			local_c8 = FLOAT_803305f4;
			local_bc = FLOAT_803305f4;
		}

		local_130 = uvSplit;
		local_134 = FLOAT_803305f8;
		local_12c = uvRemainder;
		local_128 = uvSplit;
		local_124 = uvRemainder;
		local_120 = uvRemainder;
		local_11c = FLOAT_803305f8;
		local_118 = uvRemainder;
		RenderDeformationShape(
			(_pppPObject*)pppYmDeformationShp_, (VYmDeformationShp*)work, (Vec*)&local_e4, (Vec2d*)&local_134);

		if (params[0x26] == 1) {
			if (params[0x28] == 0) {
				local_e4 = -size;
				local_e0 = -size;
				local_d8 = size;
				local_d4 = -size;
				local_cc = size;
				local_c8 = -split;
				local_c0 = -size;
				local_bc = -split;
				local_dc = FLOAT_803305f4;
				local_d0 = FLOAT_803305f4;
				local_c4 = FLOAT_803305f4;
				local_b8 = FLOAT_803305f4;
			} else if (params[0x28] == 1) {
				local_e4 = -size;
				local_dc = -size;
				local_d8 = size;
				local_d0 = -size;
				local_cc = size;
				local_c4 = -split;
				local_c0 = -size;
				local_b8 = -split;
				local_e0 = FLOAT_803305f4;
				local_d4 = FLOAT_803305f4;
				local_c8 = FLOAT_803305f4;
				local_bc = FLOAT_803305f4;
			}

			local_134 = FLOAT_803305f4;
			local_130 = FLOAT_803305f4;
			local_12c = FLOAT_803305f8;
			local_128 = FLOAT_803305f4;
			local_124 = FLOAT_803305f8;
			local_120 = uvSplit;
			local_11c = FLOAT_803305f4;
			local_118 = uvSplit;
			RenderDeformationShape(
				(_pppPObject*)pppYmDeformationShp_, (VYmDeformationShp*)work, (Vec*)&local_e4, (Vec2d*)&local_134);

			if (params[0x28] == 0) {
				local_e4 = split;
				local_e0 = -size;
				local_d8 = size;
				local_d4 = -size;
				local_cc = size;
				local_c8 = size;
				local_c0 = split;
				local_bc = size;
				local_dc = FLOAT_803305f4;
				local_d0 = FLOAT_803305f4;
				local_c4 = FLOAT_803305f4;
				local_b8 = FLOAT_803305f4;
			} else if (params[0x28] == 1) {
				local_e4 = split;
				local_dc = -size;
				local_d8 = size;
				local_d0 = -size;
				local_cc = size;
				local_c4 = size;
				local_c0 = split;
				local_b8 = size;
				local_e0 = FLOAT_803305f4;
				local_d4 = FLOAT_803305f4;
				local_c8 = FLOAT_803305f4;
				local_bc = FLOAT_803305f4;
			}

			local_134 = FLOAT_803305f4;
			local_130 = uvRemainder;
			local_12c = FLOAT_803305f8;
			local_128 = uvRemainder;
			local_124 = FLOAT_803305f8;
			local_120 = FLOAT_803305f8;
			local_11c = FLOAT_803305f4;
			local_118 = FLOAT_803305f8;
			RenderDeformationShape(
				(_pppPObject*)pppYmDeformationShp_, (VYmDeformationShp*)work, (Vec*)&local_e4, (Vec2d*)&local_134);
		}
	}

	DisableIndWarp__F13_GXTevStageID16_GXIndTexStageID(1, 0);
}
