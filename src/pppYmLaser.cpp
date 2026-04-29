#include "ffcc/pppYmLaser.h"
#include "ffcc/graphic.h"
#include "ffcc/math.h"
#include "ffcc/map.h"
#include "ffcc/linkage.h"
extern "C" {
extern const f32 kPppYmLaserOne;
extern int gPppCalcDisabled;
}
#include "ffcc/util.h"
#include "ffcc/pppPart.h"
#include "ffcc/pppShape.h"

#include <string.h>

extern "C" void pppHeapUseRate__FPQ27CMemory6CStage(void* stage);

extern const f32 FLOAT_80330df0;
extern const f32 FLOAT_80330DC4;
extern const f32 FLOAT_80330DC8;
extern f32 FLOAT_80330de0;
extern f32 FLOAT_80330de4;
extern f32 FLOAT_80330de8;
extern f32 FLOAT_80330dec;
extern "C" const f64 DOUBLE_80330DD0;

void pppInitBlendMode(void);
void pppSetBlendMode(unsigned char);

extern "C" {
void* pppMemAlloc__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);
void CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf(
    void*, long, float&, float&, float&, float, float&, float&);
int CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl(CMapMng*, void*, void*, u32);
void CalcHitPosition__7CMapObjFP3Vec(void*, Vec*);
int GetCharaNodeFrameMatrix__FP9_pppMngStfPA4_f(_pppMngSt*, float, Mtx);
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
void pppMulMatrix__FR10pppFMATRIX10pppFMATRIX10pppFMATRIX(pppFMATRIX*, pppFMATRIX*, pppFMATRIX*);
void pppUnitMatrix__FR10pppFMATRIX(pppFMATRIX*);
void pppDrawShp__FPlsP12CMaterialSetUc(long*, short, CMaterialSet*, u8);
}

extern "C" const char s_pppYmLaser_cpp_801DB4B0[] = "pppYmLaser.cpp";

struct CMapCylinderRaw {
	Vec m_bottom;
	u8 m_pad0C[0x0C];
	Vec m_direction;
	float m_radius;
	Vec m_top;
	Vec m_direction2;
};

struct pppYmLaserWork {
	float m_length;
	float m_lengthStep;
	float m_graphValue0;
	float m_graphValue1;
	float m_halfWidth;
	float m_graphValue2;
	float m_graphValue3;
	Vec* m_points;
	Vec m_origin;
	u8 m_shapeReady;
	u8 m_hitFrame;
	u8 m_unused2E;
	u8 m_unused2F;
	s16 m_shapeArg0;
	s16 m_shapeArg1;
	s16 m_shapeArg2;
	s16 m_unused36;
	float m_shapeRotation;
};

struct pppYmLaserColorData {
	u8 m_pad0[8];
	pppCVECTOR m_color;
};

union pppYmLaserDoubleBits {
	double d;
	u32 u[2];
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
	work->m_graphValue3 = one;
	work->m_graphValue2 = one;
	work->m_halfWidth = one;
	work->m_graphValue1 = one;
	work->m_graphValue0 = one;
	work->m_lengthStep = one;
	work->m_points = 0;
	work->m_origin.z = one;
	work->m_origin.y = one;
	work->m_origin.x = one;
	work->m_shapeReady = 0;
	work->m_hitFrame = 0;
	work->m_unused2E = 0;
	work->m_shapeArg0 = 0;
	work->m_shapeArg2 = 0;
	work->m_shapeArg1 = 0;
	work->m_shapeRotation = Math.RandF(randArg);
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

	work->m_graphValue3 = one;
	work->m_graphValue2 = one;
	work->m_halfWidth = one;
	work->m_graphValue1 = one;
	work->m_graphValue0 = one;
	work->m_lengthStep = one;
	work->m_origin.z = one;
	work->m_origin.y = one;
	work->m_origin.x = one;
	work->m_shapeReady = 0;
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
	pppYmLaserWork* work;
	Vec localA;
	Vec localB;
	CMapCylinderRaw cyl;
	Mtx charaMtx;
	Mtx tempMtx;
	int emptyHistory;

	if ((gPppCalcDisabled == 0) && (step->m_stepValue != 0xFFFF)) {
	work = (pppYmLaserWork*)((u8*)laser + 0x80 + data->m_serializedDataOffsets[2]);
	emptyHistory = 0;

	if (work->m_points == 0) {
		work->m_points = (Vec*)pppMemAlloc__FUlPQ27CMemory6CStagePci(
			(u32)step->m_payload[0x1e] * 0xc, pppEnvStPtr->m_stagePtr, const_cast<char*>(s_pppYmLaser_cpp_801DB4B0), 0x5d);
		memset(work->m_points, 0, (u32)step->m_payload[0x1e] * 0xc);
		emptyHistory = 1;
	}

	CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf(
		(_pppPObject*)laser, step->m_graphId, work->m_halfWidth, work->m_graphValue2, work->m_graphValue3,
		*(float*)(step->m_payload + 0x10),
		*(float*)(step->m_payload + 0x14), *(float*)(step->m_payload + 0x18));
	CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf(
		(_pppPObject*)laser, step->m_graphId, work->m_lengthStep, work->m_graphValue0, work->m_graphValue1,
		*(float*)(step->m_payload + 4),
		*(float*)(step->m_payload + 8), *(float*)(step->m_payload + 0xc));

	pppCalcFrameShape(
		**(long***)(*(u32*)&pppEnvStPtr->m_particleColors[0] + (u32)step->m_stepValue * 4), work->m_shapeArg1,
		work->m_shapeArg2, work->m_shapeArg0, *(short*)(step->m_payload + 0x2c));

	for (int i = 0; i < (int)((u32)step->m_payload[0x3a] + 1); i++) {
		int max = (int)step->m_payload[0x1e] - 2;

		for (int j = max; (int)i <= j; j--) {
			pppCopyVector(work->m_points[j + 1], work->m_points[j]);
		}

		localB.x = kPppYmLaserOne;
		localB.y = kPppYmLaserOne;
		localB.z = work->m_length;

		if (i == 0) {
			PSMTXConcat(pppMngStPtr->m_matrix.value, laser->m_localMatrix.value, tempMtx);
			work->m_origin.x = tempMtx[0][3];
			work->m_origin.y = tempMtx[1][3];
			work->m_origin.z = tempMtx[2][3];
			PSMTXMultVec(tempMtx, &localB, work->m_points);
		} else {
			if (emptyHistory) {
				continue;
			}

			float t = (FLOAT_80330de0 / (float)(s32)(step->m_payload[0x3a] + 1)) * (float)i;
			if (GetCharaNodeFrameMatrix__FP9_pppMngStfPA4_f(pppMngStPtr, t, charaMtx) == 0) {
				emptyHistory = 1;
				continue;
			} else {
				PSMTXConcat(charaMtx, laser->m_localMatrix.value, charaMtx);
				PSMTXMultVec(charaMtx, &localB, &work->m_points[i]);
			}
		}

		pppSubVector(localA, work->m_points[i], work->m_origin);
		PSVECScale(&localA, &localA, FLOAT_80330de4);

		cyl.m_top.x = FLOAT_80330de8;
		cyl.m_top.y = FLOAT_80330de8;
		cyl.m_top.z = FLOAT_80330de8;
		cyl.m_direction2.x = FLOAT_80330dec;
		cyl.m_direction2.y = FLOAT_80330dec;
		cyl.m_direction2.z = FLOAT_80330dec;
		cyl.m_bottom = work->m_origin;
		cyl.m_direction = localA;
		cyl.m_radius = kPppYmLaserOne;

		int hit = 0;
		if (CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl(&MapMng, &cyl, &localA, 0xffffffff) != 0) {
			hit = 1;
			CalcHitPosition__7CMapObjFP3Vec(*(void**)((u8*)&MapMng + 0x22A78), &work->m_points[i]);
			work->m_length = PSVECDistance(&work->m_points[i], &work->m_origin);
		} else if (i == 0) {
			work->m_length += work->m_lengthStep;
		}

		if (i == 0) {
			localB.x = kPppYmLaserOne;
			localB.y = kPppYmLaserOne;
			localB.z = work->m_length;
			PSMTXMultVec(tempMtx, &localB, &work->m_points[i]);
		}

		if (step->m_payload[0x3b] == 0) {
			pppHitCylinderSendSystem(
				pppMngStPtr, &work->m_origin, &localA,
				pppMngStPtr->m_previousPosition.z * *(float*)(step->m_payload + 0x24),
				*(float*)(step->m_payload + 0x20));
		}

		if (step->m_payload[0x3c] == 0) {
			int createHitObject = 0;
			if (step->m_arg3 != -1) {
				createHitObject = 1;
			}
			if (!hit) {
				createHitObject = 0;
			}

			if (work->m_hitFrame < step->m_payload[0x1d]) {
				work->m_hitFrame++;
				createHitObject = 0;
			} else {
				work->m_hitFrame = 0;
			}

			if (createHitObject != 0) {
				_pppPDataVal* dataVal = pppMngStPtr->m_pppPDataVals + step->m_arg3;
				_pppPObject* created;
				if (dataVal == 0) {
					created = 0;
				} else {
					created = pppCreatePObject(pppMngStPtr, dataVal);
					*(_pppPObject**)((u8*)created + 4) = (_pppPObject*)laser;
				}

				Vec* createdPos = (Vec*)((u8*)created + *(int*)step->m_payload + 0x80);
				createdPos->x = work->m_points[i].x;
				createdPos->y = work->m_points[i].y + *(float*)(step->m_payload + 0x34);
				createdPos->z = work->m_points[i].z;
			}
		}
	}

	if (emptyHistory) {
		for (int i = 0; i < (int)(u32)step->m_payload[0x1e]; i++) {
			pppCopyVector(work->m_points[i], work->m_points[0]);
		}
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
	int colorOffset = data->m_serializedDataOffsets[1];
	pppYmLaserColorData* colorData = (pppYmLaserColorData*)((u8*)laser + 0x80 + colorOffset);
	pppYmLaserWork* work = (pppYmLaserWork*)((u8*)laser + 0x80 + data->m_serializedDataOffsets[2]);
	Vec* points;
	u32 count;
	u32 i;
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
	Mtx sphereMtx;
	Vec shapePos;
	Vec spherePos;
	_GXColor color;
	_GXColor debugColor;
	int tex;

	if (step->m_dataValIndex == 0xFFFF) {
		return;
	}

	tex = GetTextureFromRSD__FiP9_pppEnvSt(step->m_dataValIndex, pppEnvStPtr);
	pppSetBlendMode(step->m_payload[0x1c]);
	_GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(1, 0, 0);
	pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(
		&colorData->m_color, &laser->m_localMatrix, kPppYmLaserOne, step->m_payload[0x39],
		step->m_payload[0x38], step->m_payload[0x1c], 0, 1, 1, 0);
	GXSetNumTevStages(1);
	GXSetNumTexGens(1);
	GXSetNumChans(1);
	GXSetCullMode(GX_CULL_NONE);
	_GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(7, 0, 1, 7, 0);
	color = *(_GXColor*)&colorData->m_color;
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

	length = work->m_length;
	halfWidth = work->m_halfWidth;

	pppMulMatrix__FR10pppFMATRIX10pppFMATRIX10pppFMATRIX(&modelView, &pppMngStPtr->m_matrix, &laser->m_localMatrix);
	pppMulMatrix__FR10pppFMATRIX10pppFMATRIX10pppFMATRIX(&mtxOut, (pppFMATRIX*)&ppvCameraMatrix0, &modelView);
	GXLoadPosMtxImm(mtxOut.value, 0);

	GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT7, 4);
	GXPosition3f32(-halfWidth, kPppYmLaserOne, kPppYmLaserOne);
	GXColor1u32(*(u32*)&color);
	GXTexCoord2f32(kPppYmLaserOne, kPppYmLaserOne);
	GXPosition3f32(-halfWidth, kPppYmLaserOne, length);
	GXColor1u32(*(u32*)&color);
	GXTexCoord2f32(kPppYmLaserOne, work->m_length);
	GXPosition3f32(halfWidth, kPppYmLaserOne, kPppYmLaserOne);
	GXColor1u32(*(u32*)&color);
	GXTexCoord2f32(FLOAT_80330DC4, kPppYmLaserOne);
	GXPosition3f32(halfWidth, kPppYmLaserOne, length);
	GXColor1u32(*(u32*)&color);
	GXTexCoord2f32(FLOAT_80330DC4, work->m_length);

	GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT7, 4);
	GXPosition3f32(kPppYmLaserOne, -halfWidth, kPppYmLaserOne);
	GXColor1u32(*(u32*)&color);
	GXTexCoord2f32(kPppYmLaserOne, kPppYmLaserOne);
	GXPosition3f32(kPppYmLaserOne, -halfWidth, length);
	GXColor1u32(*(u32*)&color);
	GXTexCoord2f32(kPppYmLaserOne, work->m_length);
	GXPosition3f32(kPppYmLaserOne, halfWidth, kPppYmLaserOne);
	GXColor1u32(*(u32*)&color);
	GXTexCoord2f32(FLOAT_80330DC4, kPppYmLaserOne);
	GXPosition3f32(kPppYmLaserOne, halfWidth, length);
	GXColor1u32(*(u32*)&color);
	GXTexCoord2f32(FLOAT_80330DC4, work->m_length);

	if (step->m_stepValue != 0xFFFF) {
		long** shapeTable = *(long***)(*(u32*)&pppEnvStPtr->m_particleColors[0] + (u32)step->m_stepValue * 4);
		PSMTXIdentity(shapeMtx.value);
		shapeMtx.value[0][0] = *(float*)(step->m_payload + 0x30) * pppMngStPtr->m_scale.x;
		shapeMtx.value[1][1] = *(float*)(step->m_payload + 0x30) * pppMngStPtr->m_scale.y;
		shapeMtx.value[2][2] = shapeMtx.value[0][0];
		if (kPppYmLaserOne != work->m_shapeRotation) {
			PSMTXRotRad(tempMtx, 'z', work->m_shapeRotation);
			PSMTXConcat(shapeMtx.value, tempMtx, shapeMtx.value);
		}
		PSMTXMultVec(ppvCameraMatrix02, work->m_points, &shapePos);
		shapeMtx.value[0][3] = shapePos.x;
		shapeMtx.value[1][3] = shapePos.y;
		shapeMtx.value[2][3] = shapePos.z;
		GXLoadPosMtxImm(shapeMtx.value, GX_PNMTX0);
		pppDrawShp__FPlsP12CMaterialSetUc(*shapeTable, work->m_shapeArg2, pppEnvStPtr->m_materialSetPtr, step->m_payload[0x1c]);

		count = (u32)step->m_payload[0x1e];
		pppYmLaserDoubleBits countDouble;

		countDouble.u[0] = 0x43300000;
		countDouble.u[1] = count;
		uvStep = FLOAT_80330DC4 / (float)(countDouble.d - DOUBLE_80330DD0);
		if (step->m_initWOrk == 0xFFFF) {
			_GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0, 0xFF, 0xFF, 4);
			_GXSetTevOp__F13_GXTevStageID10_GXTevMode(0, 4);
		} else {
			tex = GetTextureFromRSD__FiP9_pppEnvSt(step->m_initWOrk, pppEnvStPtr);
			_GXSetTevOp__F13_GXTevStageID10_GXTevMode(0, 0);
			GXLoadTexObj((GXTexObj*)(tex + 0x28), GX_TEXMAP0);
		}

		GXLoadPosMtxImm(ppvCameraMatrix02, GX_PNMTX0);
		alphaMax = step->m_payload[0x2b];
		alphaStep = (u8)((u32)alphaMax / step->m_payload[0x1e]);
		colorBase = *(u32*)(step->m_payload + 0x28) & 0xFFFFFF00;
		points = work->m_points;

		GXBegin(GX_TRIANGLES, GX_VTXFMT7, (u16)((step->m_payload[0x1e] - 1) * 3));
		for (i = 0; (int)i < (int)(step->m_payload[0x1e] - 1); i++) {
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
			GXBegin(GX_POINTS, GX_VTXFMT7, (u16)(step->m_payload[0x1e] - 1));
			for (int j = 0; j < (int)(step->m_payload[0x1e] - 1); j++) {
				GXPosition3f32(points[j].x, points[j].y, points[j].z);
				GXColor1u32(*(u32*)&debugColor);
			}

			debugColor.r = 0x80;
			debugColor.g = 0x80;
			debugColor.b = 0xFF;
			debugColor.a = 0xFF;
			GXSetChanAmbColor(GX_COLOR0A0, debugColor);
			GXSetLineWidth(0x14, GX_TO_ZERO);
			GXBegin(GX_LINES, GX_VTXFMT7, (u16)((step->m_payload[0x1e] - 1) * 4));
			for (int j = 0; j < (int)(step->m_payload[0x1e] - 1); j++) {
				GXPosition3f32(points[j].x, points[j].y, points[j].z);
				GXColor1u32(*(u32*)&debugColor);
				GXPosition3f32(points[j + 1].x, points[j + 1].y, points[j + 1].z);
				GXColor1u32(*(u32*)&debugColor);
				GXPosition3f32(points[j].x, points[j].y, points[j].z);
				GXColor1u32(*(u32*)&debugColor);
				GXPosition3f32(work->m_origin.x, work->m_origin.y, work->m_origin.z);
				GXColor1u32(*(u32*)&debugColor);
			}

			GXSetLineWidth(8, GX_TO_ZERO);
			GXSetPointSize(8, GX_TO_ZERO);
			GXSetZMode(1, GX_LEQUAL, 0);

			PSMTXIdentity(tempMtx);
			tempMtx[0][0] = pppMngStPtr->m_previousPosition.z * *(float*)(step->m_payload + 0x24);
			tempMtx[1][1] = tempMtx[0][0];
			tempMtx[2][2] = PSVECDistance(work->m_points, &work->m_origin);
			PSMTXConcat(laser->m_localMatrix.value, tempMtx, tempMtx);
			PSMTXConcat(pppMngStPtr->m_matrix.value, tempMtx, tempMtx);
			PSMTXConcat(ppvCameraMatrix02, tempMtx, tempMtx);
			shapePos.x = kPppYmLaserOne;
			shapePos.y = kPppYmLaserOne;
			shapePos.z = FLOAT_80330DC4;
			PSMTXMultVec(tempMtx, &shapePos, &spherePos);
			tempMtx[0][3] = spherePos.x;
			tempMtx[1][3] = spherePos.y;
			tempMtx[2][3] = spherePos.z;
			debugColor.r = 0xFF;
			debugColor.g = 0xFF;
			debugColor.b = 0xFF;
			debugColor.a = 0xFF;
			Graphic.DrawSphere(tempMtx, debugColor);

			GXLoadPosMtxImm(laser->m_drawMatrix.value, GX_PNMTX0);
			for (i = 0; (int)i < (int)(u32)step->m_payload[0x1e]; i++) {
				if ((points[i].x == kPppYmLaserOne) && (points[i].y == kPppYmLaserOne) &&
					(points[i].z == kPppYmLaserOne)) {
					continue;
				}
				PSMTXScale(tempMtx, FLOAT_80330DC8, FLOAT_80330DC8, FLOAT_80330DC8);
				tempMtx[0][3] = points[i].x;
				tempMtx[1][3] = points[i].y;
				tempMtx[2][3] = points[i].z;
				PSMTXConcat(ppvCameraMatrix02, tempMtx, sphereMtx);
				Graphic.DrawSphere(sphereMtx, debugColor);
			}

			tempMtx[0][3] = work->m_origin.x;
			tempMtx[1][3] = work->m_origin.y;
			tempMtx[2][3] = work->m_origin.z;
			PSMTXConcat(ppvCameraMatrix02, tempMtx, sphereMtx);
			Graphic.DrawSphere(sphereMtx, debugColor);
			pppInitBlendMode();
		}
	}
}
