#include "ffcc/pppYmLaser.h"
#include "ffcc/graphic.h"
#include "ffcc/math.h"
#include "ffcc/map.h"
#include "ffcc/p_game.h"
#include "ffcc/partMng.h"

#include <string.h>

extern CMath math;
extern "C" float RandF__5CMathFf(float param, CMath* math);
extern "C" void pppHeapUseRate__FPQ27CMemory6CStage(void* stage);
extern struct _pppMngSt* pppMngStPtr;
extern s32 DAT_8032ed70;
extern void* DAT_8032ec70;
extern u32 CFlatFlags;
extern CMapMng MapMng;
extern Mtx ppvCameraMatrix0;
extern CGraphic Graphic;
extern f32 FLOAT_80330dc0;
extern f32 FLOAT_80330de0;
extern f32 FLOAT_80330de4;
extern f32 FLOAT_80330de8;
extern f32 FLOAT_80330dec;
extern f64 DOUBLE_80330dd8;

extern "C" {
void* pppMemAlloc__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);
void CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf(float, void*, int, float*, float*, float*, float*, float*);
void pppCalcFrameShape__FPlRsRsRss(long*, short&, short&, short&, short);
void pppCopyVector__FR3Vec3Vec(Vec*, const Vec*);
void pppSubVector__FR3Vec3Vec3Vec(Vec*, const Vec*, const Vec*);
int CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl(CMapMng*, void*, void*, u32);
void CalcHitPosition__7CMapObjFP3Vec(void*, Vec*);
int GetCharaNodeFrameMatrix__FP9_pppMngStfPA4_f(float, _pppMngSt*, Mtx);
int pppCreatePObject__FP9_pppMngStP12_pppPDataVal(_pppMngSt*, void*);
void pppHitCylinderSendSystem__FP9_pppMngStP3VecP3Vecff(_pppMngSt*, Vec*, Vec*, float, float);
int GetTextureFromRSD__FiP9_pppEnvSt(int, _pppEnvSt*);
void pppSetBlendMode__FUc(u8);
void pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(void*, void*, float, u8, u8, u8, u8, u8, u8, u8);
void SetVtxFmt_POS_CLR_TEX__5CUtilFv(void*);
void SetVtxFmt_POS_CLR__5CUtilFv(void*);
void _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(int, int, int);
void _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(int, int, int, int, int);
void _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(int, int, int, int);
void _GXSetTevOp__F13_GXTevStageID10_GXTevMode(int, int);
void _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg(
	int, int, int, int, int);
void _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(
	int, int, int, int, int, int);
void _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg(
	int, int, int, int, int);
void _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(
	int, int, int, int, int, int);
void pppMulMatrix__FR10pppFMATRIX10pppFMATRIX10pppFMATRIX(pppFMATRIX*, pppFMATRIX*, pppFMATRIX*);
void pppUnitMatrix__FR10pppFMATRIX(pppFMATRIX*);
void pppDrawShp__FPlsP12CMaterialSetUc(long*, short, CMaterialSet*, u8);
void pppInitBlendMode__Fv(void);
}

static char s_pppYmLaser_cpp[] = "pppYmLaser.cpp";

struct YmLaserOffsets {
	int m_serializedDataOffsets[3];
};

struct YmLaserParam {
	unsigned char pad[0xc];
	YmLaserOffsets* offsets;
};

struct YmLaserStep {
	s32 m_graphId;
	s32 m_dataValIndex;
	u16 m_initWOrk;
	u16 m_stepValue;
	s32 m_arg3;
	u8* m_payload;
};

struct CMapCylinderRaw {
	Vec m_bottom;
	Vec m_direction;
	float m_radius;
	float m_height;
	Vec m_top;
	Vec m_direction2;
	float m_radius2;
	float m_height2;
};

struct pppYmLaser {
	u8 field_0x0[0x84];
	f32 field_0x84;
	f32 field_0x88;
	f32 field_0x8c;
	f32 field_0x90;
	f32 field_0x94;
	f32 field_0x98;
	f32 field_0x9c;
	f32 field_0xa0;
	f32 field_0xa4;
	f32 field_0xa8;
	u8 field_0xac;
};

/*
 * --INFO--
 * PAL Address: 0x800d3780
 * PAL Size: 152b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void pppConstructYmLaser(void* pppYmLaser_, void* param_2_)
{
	pppYmLaser* pppYmLaser = (struct pppYmLaser*)pppYmLaser_;
	YmLaserParam* param_2 = (YmLaserParam*)param_2_;
	f32* work = (f32*)((u8*)pppYmLaser + 0x80 + param_2->offsets->m_serializedDataOffsets[2]);
	f32 one = FLOAT_80330dc0;

	*work = one;
	work[6] = one;
	work[5] = one;
	work[4] = one;
	work[3] = one;
	work[2] = one;
	work[1] = one;
	*(u32*)((u8*)work + 0x1c) = 0;
	work[10] = one;
	work[9] = one;
	work[8] = one;
	*((u8*)work + 0x2c) = 0;
	*((u8*)work + 0x2d) = 0;
	*((u8*)work + 0x2e) = 0;
	*((u16*)((u8*)work + 0x30)) = 0;
	*((u16*)((u8*)work + 0x34)) = 0;
	*((u16*)((u8*)work + 0x32)) = 0;
	work[14] = RandF__5CMathFf(FLOAT_80330dc0, &math);
}

/*
 * --INFO--
 * PAL Address: 0x800d373c
 * PAL Size: 68b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void pppConstruct2YmLaser(void* pppYmLaser_, void* param_2_)
{
	pppYmLaser* pppYmLaser = (struct pppYmLaser*)pppYmLaser_;
	YmLaserParam* param_2 = (YmLaserParam*)param_2_;
	f32 one = FLOAT_80330dc0;
	f32* work = (f32*)((u8*)pppYmLaser + 0x80 + param_2->offsets->m_serializedDataOffsets[2]);

	work[6] = one;
	work[5] = one;
	work[4] = one;
	work[3] = one;
	work[2] = one;
	work[1] = one;
	work[10] = one;
	work[9] = one;
	work[8] = one;
	*((u8*)work + 0x2c) = 0;
}

/*
 * --INFO--
 * PAL Address: 0x800d36f0
 * PAL Size: 76b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void pppDestructYmLaser(void* pppYmLaser_, void* param_2_)
{
	pppYmLaser* pppYmLaser = (struct pppYmLaser*)pppYmLaser_;
	YmLaserParam* param_2 = (YmLaserParam*)param_2_;
	f32* work = (f32*)((u8*)pppYmLaser + 0x80 + param_2->offsets->m_serializedDataOffsets[2]);
	void* stage = *(void**)(work + 7);

	if (stage != 0) {
		pppHeapUseRate__FPQ27CMemory6CStage(stage);
		*(void**)(work + 7) = 0;
	}
}

/*
 * --INFO--
 * PAL Address: 0x800d31d4
 * PAL Size: 1308b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void pppFrameYmLaser(void* pppYmLaser, void* param_2, void* param_3)
{
	YmLaserStep* step = (YmLaserStep*)param_2;
	YmLaserParam* data = (YmLaserParam*)param_3;
	_pppPObject* baseObj = (_pppPObject*)pppYmLaser;
	float* work = (float*)((unsigned char*)pppYmLaser + 0x88 + data->offsets->m_serializedDataOffsets[2]);
	Vec localA;
	Vec localB;
	Vec localPos;
	CMapCylinderRaw cyl;
	Mtx charaMtx;
	Mtx tempMtx;
	bool emptyHistory = (work[7] == 0.0f);

	if ((DAT_8032ed70 != 0) || (step->m_stepValue == 1)) {
		return;
	}

	if (emptyHistory) {
		work[7] = (float)(u32)pppMemAlloc__FUlPQ27CMemory6CStagePci(
			(u32)step->m_payload[0x1e] * 0xc, pppEnvStPtr->m_stagePtr, s_pppYmLaser_cpp, 0x5d);
		memset((void*)(u32)work[7], 0, (u32)step->m_payload[0x1e] * 0xc);
	}

	CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf(
		*(float*)(step->m_payload + 0x10), baseObj, step->m_graphId, work + 4, work + 5, work + 6,
		(float*)(step->m_payload + 0x14), (float*)(step->m_payload + 0x18));
	CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf(
		*(float*)(step->m_payload + 4), baseObj, step->m_graphId, work + 1, work + 2, work + 3,
		(float*)(step->m_payload + 8), (float*)(step->m_payload + 0xc));

	pppCalcFrameShape__FPlRsRsRss(
		*(long**)(*(u32*)&pppEnvStPtr->m_particleColors[0] + (u32)step->m_stepValue * 4), *(short*)((u8*)work + 0x32),
		*(short*)(work + 0xd), *(short*)(work + 0xc), *(short*)(step->m_payload + 0x2c));

	for (u32 i = 0; i < (u32)step->m_payload[0x3a] + 1; i++) {
		Vec* points = (Vec*)(u32)work[7];
		int max = (int)step->m_payload[0x1e] - 2;

		for (int j = max; (int)i <= j; j--) {
			localA = points[j];
			pppCopyVector__FR3Vec3Vec(&points[j + 1], &localA);
		}

		localB.x = FLOAT_80330dc0;
		localB.y = FLOAT_80330dc0;
		localB.z = work[0];

		if (i == 0) {
			PSMTXConcat(pppMngStPtr->m_matrix.value, baseObj->m_localMatrix.value, tempMtx);
			work[8] = tempMtx[0][3];
			work[9] = tempMtx[1][3];
			work[10] = tempMtx[2][3];
			PSMTXMultVec(tempMtx, &localB, points);
		} else if (!emptyHistory) {
			double t = (FLOAT_80330de0 / (float)((double)(int)(step->m_payload[0x3a] + 1) - DOUBLE_80330dd8)) *
				(float)((double)(int)i - DOUBLE_80330dd8);
			if (GetCharaNodeFrameMatrix__FP9_pppMngStfPA4_f((float)t, pppMngStPtr, charaMtx) == 0) {
				emptyHistory = true;
			} else {
				PSMTXConcat(charaMtx, baseObj->m_localMatrix.value, charaMtx);
				PSMTXMultVec(charaMtx, &localB, &points[i]);
			}
		}

		localPos.x = work[8];
		localPos.y = work[9];
		localPos.z = work[10];
		pppSubVector__FR3Vec3Vec3Vec(&localA, &points[i], &localPos);
		PSVECScale(&localA, &localA, FLOAT_80330de4);

		cyl.m_bottom = localPos;
		cyl.m_direction = localA;
		cyl.m_radius = FLOAT_80330de8;
		cyl.m_height = FLOAT_80330dec;
		cyl.m_radius2 = FLOAT_80330dec;
		cyl.m_height2 = FLOAT_80330dec;

		bool hit = CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl(
					   &MapMng, &cyl, &cyl.m_direction, 0xffffffff) != 0;
		if (hit) {
			CalcHitPosition__7CMapObjFP3Vec(*(void**)((u8*)&MapMng + 0x22A88), &points[i]);
			work[0] = PSVECDistance(&points[i], (Vec*)(work + 8));
		} else if (i == 0) {
			work[0] += work[1];
		}

		if (i == 0) {
			localB.z = work[0];
			PSMTXMultVec(tempMtx, &localB, &points[0]);
		}

		if (step->m_payload[0x3b] == 0) {
			pppHitCylinderSendSystem__FP9_pppMngStP3VecP3Vecff(
				pppMngStPtr, (Vec*)(work + 8), &localA, pppMngStPtr->m_ownerScale * *(float*)(step->m_payload + 0x24),
				*(float*)(step->m_payload + 0x20));
		}

		if (step->m_payload[0x3c] == 0) {
			u8* hitFrame = (u8*)work + 0x2d;
			bool canCreate = (u8)step->m_payload[0x1d] <= *hitFrame;
			if (canCreate) {
				*hitFrame = 0;
			} else {
				(*hitFrame)++;
			}

			if (canCreate && hit && step->m_arg3 != -1) {
				u8* dataVals = *(u8**)((u8*)pppMngStPtr + 0xc8);
				int created = 0;
				if (dataVals != 0) {
					created = pppCreatePObject__FP9_pppMngStP12_pppPDataVal(pppMngStPtr, dataVals + step->m_arg3 * 0x10);
					*(void**)(created + 4) = pppYmLaser;
				}

				if (created != 0) {
					*(Vec*)(created + *(int*)step->m_payload + 0x80) = points[i];
					*(float*)(created + *(int*)step->m_payload + 0x84) += *(float*)(step->m_payload + 0x34);
				}
			}
		}
	}

	if (emptyHistory) {
		Vec* points = (Vec*)(u32)work[7];
		for (int i = 0; i < (int)(u32)step->m_payload[0x1e]; i++) {
			points[i] = points[0];
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x800d2614
 * PAL Size: 3008b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void pppRenderYmLaser(void* pppYmLaser, void* param_2, void* param_3)
{
	YmLaserStep* step = (YmLaserStep*)param_2;
	YmLaserParam* data = (YmLaserParam*)param_3;
	_pppPObject* baseObj = (_pppPObject*)pppYmLaser;
	int colorOffset = data->offsets->m_serializedDataOffsets[1];
	float* work = (float*)((u8*)pppYmLaser + 0x88 + data->offsets->m_serializedDataOffsets[2]);
	Vec* points;
	u32 count;
	u32 i;
	u32 color;
	u32 colorBase;
	u32 color0;
	u32 color1;
	u8 alpha0;
	u8 alphaStep;
	u8 alphaMax;
	float halfWidth;
	float length;
	float u0;
	float u1;
	float uvStep;
	pppFMATRIX localMtx;
	pppFMATRIX worldMtx;
	pppFMATRIX viewMtx;
	pppFMATRIX modelView;
	pppFMATRIX mtxOut;
	pppFMATRIX shapeMtx;
	Mtx tempMtx;
	Vec shapePos;
	_GXColor debugColor;
	int tex;

	if (step->m_dataValIndex == 0xFFFF) {
		return;
	}

	tex = GetTextureFromRSD__FiP9_pppEnvSt(step->m_dataValIndex, pppEnvStPtr);
	pppSetBlendMode__FUc(step->m_payload[0x1c]);
	_GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(1, 0, 0);
	pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(
		(u8*)pppYmLaser + 0x88 + colorOffset, &baseObj->m_localMatrix, FLOAT_80330dc0, step->m_payload[0x39],
		step->m_payload[0x38], step->m_payload[0x1c], 0, 1, 1, 0);
	GXSetNumTevStages(1);
	GXSetNumTexGens(1);
	GXSetNumChans(1);
	GXSetCullMode(GX_CULL_NONE);
	_GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(7, 0, 1, 7, 0);
	_GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0, 0, 0, 4);
	GXSetTexCoordGen2((GXTexCoordID)0, (GXTexGenType)1, (GXTexGenSrc)4, 0x3C, GX_FALSE, 0x7D);
	_GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg(
		0, 0xF, 8, 0xA, 0xF);
	_GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(0, 0, 0, 0, 1, 0);
	_GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg(
		0, 7, 7, 7, 5);
	_GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(0, 0, 0, 0, 1, 0);
	SetVtxFmt_POS_CLR_TEX__5CUtilFv(&DAT_8032ec70);
	GXLoadTexObj((GXTexObj*)(tex + 0x28), GX_TEXMAP0);

	color = *(u32*)((u8*)pppYmLaser + 0x88 + colorOffset);
	halfWidth = work[4];
	length = work[0];

	localMtx = baseObj->m_localMatrix;
	worldMtx = pppMngStPtr->m_matrix;
	pppMulMatrix__FR10pppFMATRIX10pppFMATRIX10pppFMATRIX(&modelView, &worldMtx, &localMtx);
	viewMtx = *(pppFMATRIX*)&ppvCameraMatrix0;
	pppMulMatrix__FR10pppFMATRIX10pppFMATRIX10pppFMATRIX(&mtxOut, &viewMtx, &modelView);
	GXLoadPosMtxImm(mtxOut.value, 0);

	GXBegin(GX_QUADS, GX_VTXFMT7, 4);
	GXPosition3f32(-halfWidth, FLOAT_80330dc0, FLOAT_80330dc0);
	GXColor1u32(color);
	GXTexCoord2f32(FLOAT_80330dc0, FLOAT_80330dc0);
	GXPosition3f32(-halfWidth, FLOAT_80330dc0, length);
	GXColor1u32(color);
	GXTexCoord2f32(FLOAT_80330dc0, work[0]);
	GXPosition3f32(halfWidth, FLOAT_80330dc0, FLOAT_80330dc0);
	GXColor1u32(color);
	GXTexCoord2f32(FLOAT_80330de0, FLOAT_80330dc0);
	GXPosition3f32(halfWidth, FLOAT_80330dc0, length);
	GXColor1u32(color);
	GXTexCoord2f32(FLOAT_80330de0, work[0]);

	GXBegin(GX_QUADS, GX_VTXFMT7, 4);
	GXPosition3f32(FLOAT_80330dc0, -halfWidth, FLOAT_80330dc0);
	GXColor1u32(color);
	GXTexCoord2f32(FLOAT_80330dc0, FLOAT_80330dc0);
	GXPosition3f32(FLOAT_80330dc0, -halfWidth, length);
	GXColor1u32(color);
	GXTexCoord2f32(FLOAT_80330dc0, work[0]);
	GXPosition3f32(FLOAT_80330dc0, halfWidth, FLOAT_80330dc0);
	GXColor1u32(color);
	GXTexCoord2f32(FLOAT_80330de0, FLOAT_80330dc0);
	GXPosition3f32(FLOAT_80330dc0, halfWidth, length);
	GXColor1u32(color);
	GXTexCoord2f32(FLOAT_80330de0, work[0]);

	if (step->m_stepValue != 0) {
		long* shape = *(long**)(*(u32*)&pppEnvStPtr->m_particleColors[0] + (u32)step->m_stepValue * 4);
		pppUnitMatrix__FR10pppFMATRIX(&shapeMtx);
		shapeMtx.value[0][0] = *(float*)(step->m_payload + 0x30) * pppMngStPtr->m_scale.x;
		shapeMtx.value[1][1] = *(float*)(step->m_payload + 0x30) * pppMngStPtr->m_scale.y;
		shapeMtx.value[2][2] = shapeMtx.value[0][0];
		if (work[0xe] != FLOAT_80330dc0) {
			PSMTXRotRad(tempMtx, 'z', work[0xe]);
			PSMTXConcat(shapeMtx.value, tempMtx, shapeMtx.value);
		}
		PSMTXMultVec(ppvCameraMatrix0, (Vec*)(u32)work[7], &shapePos);
		shapeMtx.value[0][3] = shapePos.x;
		shapeMtx.value[1][3] = shapePos.y;
		shapeMtx.value[2][3] = shapePos.z;
		GXLoadPosMtxImm(shapeMtx.value, GX_PNMTX0);
		pppDrawShp__FPlsP12CMaterialSetUc(
			shape, *(s16*)(work + 0xd), pppEnvStPtr->m_materialSetPtr, step->m_payload[0x1c]);

		count = (u32)step->m_payload[0x1e];
		if (count > 1) {
			uvStep = FLOAT_80330de0 / ((float)(double)count - (float)DOUBLE_80330dd8);
			if (step->m_initWOrk == 0xFFFF) {
				_GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0, 0xFF, 0xFF, 4);
				_GXSetTevOp__F13_GXTevStageID10_GXTevMode(0, 4);
			} else {
				tex = GetTextureFromRSD__FiP9_pppEnvSt(step->m_initWOrk, pppEnvStPtr);
				_GXSetTevOp__F13_GXTevStageID10_GXTevMode(0, 0);
				GXLoadTexObj((GXTexObj*)(tex + 0x28), GX_TEXMAP0);
			}

			GXLoadPosMtxImm(ppvCameraMatrix0, GX_PNMTX0);
			alphaMax = step->m_payload[0x2b];
			alphaStep = (u8)((u32)alphaMax / count);
			colorBase = *(u32*)(step->m_payload + 0x28) & 0xFFFFFF00;
			points = (Vec*)(u32)work[7];

			GXBegin(GX_TRIANGLES, GX_VTXFMT7, (u16)((count - 1) * 3));
			for (i = 0; i < count - 1; i++) {
				alpha0 = (u8)(alphaMax - (u8)(alphaStep * i));
				color0 = colorBase | alpha0;
				color1 = colorBase | (u8)(alphaMax - (u8)(alphaStep * (i + 1)));
				u0 = (float)i * uvStep;
				u1 = (float)(i + 1) * uvStep;

				GXPosition3f32(work[8], work[9], work[10]);
				GXColor1u32(color0);
				GXTexCoord2f32(u0, FLOAT_80330de0);

				GXPosition3f32(points[i].x, points[i].y, points[i].z);
				GXColor1u32(color0);
				GXTexCoord2f32(u0, FLOAT_80330dc0);

				GXPosition3f32(points[i + 1].x, points[i + 1].y, points[i + 1].z);
				GXColor1u32(color1);
				GXTexCoord2f32(u1, FLOAT_80330dc0);
			}
		}

		if ((CFlatFlags & 0x200000) != 0) {
			SetVtxFmt_POS_CLR__5CUtilFv(&DAT_8032ec70);
			_GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0, 0xFF, 0xFF, 4);
			_GXSetTevOp__F13_GXTevStageID10_GXTevMode(0, 4);
			GXSetNumTexGens(0);
			pppSetBlendMode__FUc(1);

			debugColor.r = 0x80;
			debugColor.g = 0xFF;
			debugColor.b = 0x80;
			debugColor.a = 0xFF;
			GXSetChanAmbColor(GX_COLOR0A0, debugColor);
			GXSetPointSize(0x28, GX_TO_ZERO);
			GXBegin(GX_POINTS, GX_VTXFMT7, (u16)(count - 1));
			for (i = 0; i < count - 1; i++) {
				GXPosition3f32(points[i].x, points[i].y, points[i].z);
				GXColor1u32(*(u32*)&debugColor);
			}

			debugColor.r = 0x80;
			debugColor.g = 0x80;
			debugColor.b = 0xFF;
			debugColor.a = 0xFF;
			GXSetChanAmbColor(GX_COLOR0A0, debugColor);
			GXSetLineWidth(0x14, GX_TO_ZERO);
			GXBegin(GX_LINES, GX_VTXFMT7, (u16)((count - 1) * 4));
			for (i = 0; i < count - 1; i++) {
				GXPosition3f32(points[i].x, points[i].y, points[i].z);
				GXColor1u32(*(u32*)&debugColor);
				GXPosition3f32(points[i + 1].x, points[i + 1].y, points[i + 1].z);
				GXColor1u32(*(u32*)&debugColor);
				GXPosition3f32(points[i].x, points[i].y, points[i].z);
				GXColor1u32(*(u32*)&debugColor);
				GXPosition3f32(work[8], work[9], work[10]);
				GXColor1u32(*(u32*)&debugColor);
			}

			GXSetLineWidth(8, GX_TO_ZERO);
			GXSetPointSize(8, GX_TO_ZERO);
			GXSetZMode(1, GX_LEQUAL, 0);

			PSMTXIdentity(tempMtx);
			tempMtx[0][0] = *(float*)((u8*)pppMngStPtr + 0x64) * *(float*)(step->m_payload + 0x24);
			tempMtx[1][1] = tempMtx[0][0];
			tempMtx[2][2] = PSVECDistance((Vec*)(u32)work[7], (Vec*)(work + 8));
			PSMTXConcat(baseObj->m_localMatrix.value, tempMtx, tempMtx);
			PSMTXConcat(pppMngStPtr->m_matrix.value, tempMtx, tempMtx);
			PSMTXConcat(ppvCameraMatrix0, tempMtx, tempMtx);
			shapePos.x = FLOAT_80330dc0;
			shapePos.y = FLOAT_80330dc0;
			shapePos.z = FLOAT_80330de0;
			PSMTXMultVec(tempMtx, &shapePos, &shapePos);
			tempMtx[0][3] = shapePos.x;
			tempMtx[1][3] = shapePos.y;
			tempMtx[2][3] = shapePos.z;
			debugColor.r = 0xFF;
			debugColor.g = 0xFF;
			debugColor.b = 0xFF;
			debugColor.a = 0xFF;
			Graphic.DrawSphere(tempMtx, debugColor);

			for (i = 0; i < count; i++) {
				if ((points[i].x == FLOAT_80330dc0) && (points[i].y == FLOAT_80330dc0) &&
					(points[i].z == FLOAT_80330dc0)) {
					continue;
				}
				PSMTXIdentity(tempMtx);
				tempMtx[0][0] = FLOAT_80330de8;
				tempMtx[1][1] = FLOAT_80330de8;
				tempMtx[2][2] = FLOAT_80330de8;
				tempMtx[0][3] = points[i].x;
				tempMtx[1][3] = points[i].y;
				tempMtx[2][3] = points[i].z;
				PSMTXConcat(ppvCameraMatrix0, tempMtx, tempMtx);
				Graphic.DrawSphere(tempMtx, debugColor);
			}

			PSMTXIdentity(tempMtx);
			tempMtx[0][0] = FLOAT_80330de8;
			tempMtx[1][1] = FLOAT_80330de8;
			tempMtx[2][2] = FLOAT_80330de8;
			tempMtx[0][3] = work[8];
			tempMtx[1][3] = work[9];
			tempMtx[2][3] = work[10];
			PSMTXConcat(ppvCameraMatrix0, tempMtx, tempMtx);
			Graphic.DrawSphere(tempMtx, debugColor);
			pppInitBlendMode__Fv();
		}
	}
}
