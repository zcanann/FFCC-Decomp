#include "ffcc/pppYmLaser.h"
#include "ffcc/graphic.h"
#include "ffcc/math.h"
#include "ffcc/map.h"
#include "ffcc/p_game.h"
#include "ffcc/linkage.h"
#include "ffcc/symbols_shared.h"
#include "ffcc/util.h"
#include "ffcc/pppPart.h"
#include "ffcc/pppShape.h"

#include <string.h>

extern "C" void pppHeapUseRate__FPQ27CMemory6CStage(void* stage);

extern const f32 FLOAT_80330df0;
extern const f32 FLOAT_80330dc0;
extern f32 FLOAT_80330de0;
extern f32 FLOAT_80330de4;
extern f32 FLOAT_80330de8;
extern f32 FLOAT_80330dec;
extern f64 DOUBLE_80330dd8;

void pppInitBlendMode(void);
void pppSetBlendMode(unsigned char);

extern "C" {
void* pppMemAlloc__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);
void CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf(float, void*, int, float*, float*, float*, float*, float*);
int CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl(CMapMng*, void*, void*, u32);
void CalcHitPosition__7CMapObjFP3Vec(void*, Vec*);
int GetCharaNodeFrameMatrix__FP9_pppMngStfPA4_f(float, _pppMngSt*, Mtx);
int pppCreatePObject__FP9_pppMngStP12_pppPDataVal(_pppMngSt*, void*);
int GetTextureFromRSD__FiP9_pppEnvSt(int, _pppEnvSt*);

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
void pppDrawShp__FPlsP12CMaterialSetUc(long*, short, CMaterialSet*, u8);
}

static char s_pppYmLaser_cpp[] = "pppYmLaser.cpp";

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

struct pppYmLaserWork {
	float m_length;
	float m_speed;
	float _unk8;
	float _unkC;
	float m_halfWidth;
	float _unk14;
	float _unk18;
	Vec* m_points;
	Vec m_origin;
	u8 _unk2c;
	u8 m_hitFrame;
	u8 _unk2e;
	u8 _unk2f;
	s16 m_shapeA;
	s16 m_shapeB;
	s16 m_shapeC;
	s16 _pad36;
	float m_shapeRotZ;
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
extern "C" void pppConstructYmLaser(pppYmLaser* laser, _pppCtrlTable* ctrlTable)
{
	f32 one = kPppYmLaserOne;
	f32 randArg = FLOAT_80330df0;
	pppYmLaserWork* work = (pppYmLaserWork*)((u8*)laser + 0x80 + ctrlTable->m_serializedDataOffsets[2]);

	work->m_length = one;
	work->_unk18 = one;
	work->_unk14 = one;
	work->m_halfWidth = one;
	work->_unkC = one;
	work->_unk8 = one;
	work->m_speed = one;
	work->m_points = 0;
	work->m_origin.z = one;
	work->m_origin.y = one;
	work->m_origin.x = one;
	work->_unk2c = 0;
	work->m_hitFrame = 0;
	work->_unk2e = 0;
	work->m_shapeA = 0;
	work->m_shapeC = 0;
	work->m_shapeB = 0;
	work->m_shapeRotZ = Math.RandF(randArg);
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
extern "C" void pppConstruct2YmLaser(pppYmLaser* laser, _pppCtrlTable* ctrlTable)
{
	f32 one = kPppYmLaserOne;
	pppYmLaserWork* work = (pppYmLaserWork*)((u8*)laser + 0x80 + ctrlTable->m_serializedDataOffsets[2]);

	work->_unk18 = one;
	work->_unk14 = one;
	work->m_halfWidth = one;
	work->_unkC = one;
	work->_unk8 = one;
	work->m_speed = one;
	work->m_origin.z = one;
	work->m_origin.y = one;
	work->m_origin.x = one;
	work->_unk2c = 0;
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
extern "C" void pppDestructYmLaser(pppYmLaser* laser, _pppCtrlTable* ctrlTable)
{
	pppYmLaserWork* work = (pppYmLaserWork*)((u8*)laser + 0x80 + ctrlTable->m_serializedDataOffsets[2]);
	void* stage = work->m_points;

	if (stage != 0) {
		pppHeapUseRate__FPQ27CMemory6CStage(stage);
		work->m_points = 0;
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
extern "C" void pppFrameYmLaser(pppYmLaser* laser, pppYmLaserUnkB* step, _pppCtrlTable* data)
{
	_pppPObject* baseObj = (_pppPObject*)laser;
	pppYmLaserWork* work;
	Vec localA;
	Vec localB;
	Vec localPos;
	CMapCylinderRaw cyl;
	Mtx charaMtx;
	Mtx tempMtx;
	bool emptyHistory;

	if ((gPppCalcDisabled != 0) || (step->m_stepValue == 0xFFFF)) {
		return;
	}

	work = (pppYmLaserWork*)((u8*)laser + 0x80 + data->m_serializedDataOffsets[2]);
	emptyHistory = false;

	if (work->m_points == 0) {
		work->m_points = (Vec*)pppMemAlloc__FUlPQ27CMemory6CStagePci(
			(u32)step->m_payload[0x1e] * 0xc, pppEnvStPtr->m_stagePtr, s_pppYmLaser_cpp, 0x5d);
		memset(work->m_points, 0, (u32)step->m_payload[0x1e] * 0xc);
		emptyHistory = true;
	}

	CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf(
		*(float*)(step->m_payload + 0x10), baseObj, step->m_graphId, &work->m_halfWidth, &work->_unk14, &work->_unk18,
		(float*)(step->m_payload + 0x14), (float*)(step->m_payload + 0x18));
	CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf(
		*(float*)(step->m_payload + 4), baseObj, step->m_graphId, &work->m_speed, &work->_unk8, &work->_unkC,
		(float*)(step->m_payload + 8), (float*)(step->m_payload + 0xc));

	pppCalcFrameShape(
		*(long**)(*(u32*)&pppEnvStPtr->m_particleColors[0] + (u32)step->m_stepValue * 4), work->m_shapeB,
		work->m_shapeC, work->m_shapeA, *(short*)(step->m_payload + 0x2c));

	for (u32 i = 0; i < (u32)step->m_payload[0x3a] + 1; i++) {
		Vec* points = work->m_points;
		int max = (int)step->m_payload[0x1e] - 2;

		for (int j = max; (int)i <= j; j--) {
			localA = points[j];
			pppCopyVector(points[j + 1], localA);
		}

		localB.x = kPppYmLaserOne;
		localB.y = kPppYmLaserOne;
		localB.z = work->m_length;

		if (i == 0) {
			PSMTXConcat(pppMngStPtr->m_matrix.value, baseObj->m_localMatrix.value, tempMtx);
			work->m_origin.x = tempMtx[0][3];
			work->m_origin.y = tempMtx[1][3];
			work->m_origin.z = tempMtx[2][3];
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

		localPos = work->m_origin;
		pppSubVector(localA, points[i], localPos);
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
			work->m_length = PSVECDistance(&points[i], &work->m_origin);
		} else if (i == 0) {
			work->m_length += work->m_speed;
		}

		if (i == 0) {
			localB.z = work->m_length;
			PSMTXMultVec(tempMtx, &localB, &points[0]);
		}

		if (step->m_payload[0x3b] == 0) {
			pppHitCylinderSendSystem(
				pppMngStPtr, &work->m_origin, &localA, pppMngStPtr->m_ownerScale * *(float*)(step->m_payload + 0x24),
				*(float*)(step->m_payload + 0x20));
		}

		if (step->m_payload[0x3c] == 0) {
			u8* hitFrame = &work->m_hitFrame;
			if (*hitFrame >= step->m_payload[0x1d]) {
				*hitFrame = 0;
				if (hit && step->m_arg3 != -1) {
					u8* dataVals = *(u8**)((u8*)pppMngStPtr + 0xc8);
					if (dataVals != 0) {
						int created =
							pppCreatePObject__FP9_pppMngStP12_pppPDataVal(pppMngStPtr, dataVals + step->m_arg3 * 0x10);
						*(void**)(created + 4) = laser;
						Vec* createdPos = (Vec*)(created + *(int*)step->m_payload + 0x80);
						createdPos->x = points[i].x;
						createdPos->y = points[i].y + *(float*)(step->m_payload + 0x34);
						createdPos->z = points[i].z;
					}
				}
			} else {
				(*hitFrame)++;
			}
		}
	}

	if (emptyHistory) {
		Vec* points = work->m_points;
		for (int i = 0; i < (int)(u32)step->m_payload[0x1e]; i++) {
			pppCopyVector(points[i], points[0]);
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
extern "C" void pppRenderYmLaser(pppYmLaser* laser, pppYmLaserUnkB* step, _pppCtrlTable* data)
{
	_pppPObject* baseObj = (_pppPObject*)laser;
	int colorOffset = data->m_serializedDataOffsets[1];
	pppYmLaserWork* work = (pppYmLaserWork*)((u8*)laser + 0x80 + data->m_serializedDataOffsets[2]);
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
	pppSetBlendMode(step->m_payload[0x1c]);
	_GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(1, 0, 0);
	pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(
		(u8*)laser + 0x88 + colorOffset, &baseObj->m_localMatrix, kPppYmLaserOne, step->m_payload[0x39],
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
	SetVtxFmt_POS_CLR_TEX__5CUtilFv(&gUtil);
	GXLoadTexObj((GXTexObj*)(tex + 0x28), GX_TEXMAP0);

	color = *(u32*)((u8*)laser + 0x88 + colorOffset);
	halfWidth = work->m_halfWidth;
	length = work->m_length;

	pppMulMatrix(modelView, pppMngStPtr->m_matrix, baseObj->m_localMatrix);
	pppMulMatrix(mtxOut, *(pppFMATRIX*)&ppvCameraMatrix0, modelView);
	GXLoadPosMtxImm(mtxOut.value, 0);

	GXBegin(GX_QUADS, GX_VTXFMT7, 4);
	GXPosition3f32(-halfWidth, kPppYmLaserOne, kPppYmLaserOne);
	GXColor1u32(color);
	GXTexCoord2f32(kPppYmLaserOne, kPppYmLaserOne);
	GXPosition3f32(-halfWidth, kPppYmLaserOne, length);
	GXColor1u32(color);
	GXTexCoord2f32(kPppYmLaserOne, work->m_length);
	GXPosition3f32(halfWidth, kPppYmLaserOne, kPppYmLaserOne);
	GXColor1u32(color);
	GXTexCoord2f32(FLOAT_80330de0, kPppYmLaserOne);
	GXPosition3f32(halfWidth, kPppYmLaserOne, length);
	GXColor1u32(color);
	GXTexCoord2f32(FLOAT_80330de0, work->m_length);

	GXBegin(GX_QUADS, GX_VTXFMT7, 4);
	GXPosition3f32(kPppYmLaserOne, -halfWidth, kPppYmLaserOne);
	GXColor1u32(color);
	GXTexCoord2f32(kPppYmLaserOne, kPppYmLaserOne);
	GXPosition3f32(kPppYmLaserOne, -halfWidth, length);
	GXColor1u32(color);
	GXTexCoord2f32(kPppYmLaserOne, work->m_length);
	GXPosition3f32(kPppYmLaserOne, halfWidth, kPppYmLaserOne);
	GXColor1u32(color);
	GXTexCoord2f32(FLOAT_80330de0, kPppYmLaserOne);
	GXPosition3f32(kPppYmLaserOne, halfWidth, length);
	GXColor1u32(color);
	GXTexCoord2f32(FLOAT_80330de0, work->m_length);

	if (step->m_stepValue != 0xFFFF) {
		long* shape = *(long**)(*(u32*)&pppEnvStPtr->m_particleColors[0] + (u32)step->m_stepValue * 4);
		pppUnitMatrix(shapeMtx);
		shapeMtx.value[0][0] = *(float*)(step->m_payload + 0x30) * pppMngStPtr->m_scale.x;
		shapeMtx.value[1][1] = *(float*)(step->m_payload + 0x30) * pppMngStPtr->m_scale.y;
		shapeMtx.value[2][2] = shapeMtx.value[0][0];
		if (work->m_shapeRotZ != kPppYmLaserOne) {
			PSMTXRotRad(tempMtx, 'z', work->m_shapeRotZ);
			PSMTXConcat(shapeMtx.value, tempMtx, shapeMtx.value);
		}
		PSMTXMultVec(ppvCameraMatrix0, work->m_points, &shapePos);
		shapeMtx.value[0][3] = shapePos.x;
		shapeMtx.value[1][3] = shapePos.y;
		shapeMtx.value[2][3] = shapePos.z;
		GXLoadPosMtxImm(shapeMtx.value, GX_PNMTX0);
		pppDrawShp__FPlsP12CMaterialSetUc(shape, work->m_shapeC, pppEnvStPtr->m_materialSetPtr, step->m_payload[0x1c]);

		count = (u32)step->m_payload[0x1e];
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
		points = work->m_points;

		GXBegin(GX_TRIANGLES, GX_VTXFMT7, (u16)((count - 1) * 3));
		for (i = 0; i < count - 1; i++) {
			alpha0 = (u8)(alphaMax - (u8)(alphaStep * i));
			color0 = colorBase | alpha0;
			color1 = colorBase | (u8)(alphaMax - (u8)(alphaStep * (i + 1)));
			u0 = (float)i * uvStep;
			u1 = (float)(i + 1) * uvStep;

			GXPosition3f32(work->m_origin.x, work->m_origin.y, work->m_origin.z);
			GXColor1u32(color0);
			GXTexCoord2f32(u0, FLOAT_80330de0);

			GXPosition3f32(points[i].x, points[i].y, points[i].z);
			GXColor1u32(color0);
			GXTexCoord2f32(u0, kPppYmLaserOne);

			GXPosition3f32(points[i + 1].x, points[i + 1].y, points[i + 1].z);
			GXColor1u32(color1);
			GXTexCoord2f32(u1, kPppYmLaserOne);
		}

		if ((CFlatFlags & 0x200000) != 0) {
			SetVtxFmt_POS_CLR__5CUtilFv(&gUtil);
			_GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0, 0xFF, 0xFF, 4);
			_GXSetTevOp__F13_GXTevStageID10_GXTevMode(0, 4);
			GXSetNumTexGens(0);
			pppSetBlendMode(1);

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
				GXPosition3f32(work->m_origin.x, work->m_origin.y, work->m_origin.z);
				GXColor1u32(*(u32*)&debugColor);
			}

			GXSetLineWidth(8, GX_TO_ZERO);
			GXSetPointSize(8, GX_TO_ZERO);
			GXSetZMode(1, GX_LEQUAL, 0);

			PSMTXIdentity(tempMtx);
			tempMtx[0][0] = *(float*)((u8*)pppMngStPtr + 0x64) * *(float*)(step->m_payload + 0x24);
			tempMtx[1][1] = tempMtx[0][0];
			tempMtx[2][2] = PSVECDistance(work->m_points, &work->m_origin);
			PSMTXConcat(baseObj->m_localMatrix.value, tempMtx, tempMtx);
			PSMTXConcat(pppMngStPtr->m_matrix.value, tempMtx, tempMtx);
			PSMTXConcat(ppvCameraMatrix0, tempMtx, tempMtx);
			shapePos.x = kPppYmLaserOne;
			shapePos.y = kPppYmLaserOne;
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
				if ((points[i].x == kPppYmLaserOne) && (points[i].y == kPppYmLaserOne) &&
					(points[i].z == kPppYmLaserOne)) {
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
			tempMtx[0][3] = work->m_origin.x;
			tempMtx[1][3] = work->m_origin.y;
			tempMtx[2][3] = work->m_origin.z;
			PSMTXConcat(ppvCameraMatrix0, tempMtx, tempMtx);
			Graphic.DrawSphere(tempMtx, debugColor);
			pppInitBlendMode();
		}
	}
}
