#include "ffcc/ptrarray.h"
#include "global.h"
#include "ffcc/pppYmLaser.h"
#include "ffcc/pppLaserCommon.h"
#include "ffcc/graphic.h"
#include "ffcc/gxfunc.h"
#include "ffcc/math.h"
#include "ffcc/map.h"
#include "ffcc/maphit.h"
#include "ffcc/linkage.h"
#include "ffcc/util.h"
#include "ffcc/pppPart.h"
#include "ffcc/pppShape.h"
#include "ffcc/pppYmEnv.h"
#include "ffcc/textureman.h"

#include <string.h>

static const f32 kPppYmLaserZero = 0.0f;
static const f32 kPppYmLaserOne = 1.0f;
static const f32 kPppYmLaserDebugPointScale = 2.0f;

static inline f32 LoadLaserFloat(const f32& value)
{
	return value;
}

static const char s_pppYmLaser_cpp[] = "pppYmLaser.cpp";

typedef pppLaserWorkBase pppYmLaserWork;
typedef pppLaserColorBlock pppYmLaserColorData;

STATIC_ASSERT(offsetof(pppLaserDataOffsets, m_colorBlockOffset) == 0x4);
STATIC_ASSERT(offsetof(pppLaserDataOffsets, m_workOffset) == 0x8);
STATIC_ASSERT(offsetof(CMapCylinder, m_bottom) == 0x0);
STATIC_ASSERT(offsetof(CMapCylinder, m_axis) == 0x18);
STATIC_ASSERT(offsetof(CMapCylinder, m_radius) == 0x24);
STATIC_ASSERT(offsetof(CMapCylinder, m_bound) == 0x28);

static inline pppLaserDataOffsets* GetYmLaserDataOffsets(_pppCtrlTable* ctrlTable)
{
	return reinterpret_cast<pppLaserDataOffsets*>(ctrlTable->m_serializedDataOffsets);
}

static inline pppYmLaserWork* GetYmLaserWork(pppYmLaser* laser, _pppCtrlTable* ctrlTable)
{
	return reinterpret_cast<pppYmLaserWork*>(laser->m_workArea + GetYmLaserDataOffsets(ctrlTable)->m_workOffset);
}

static inline pppYmLaserColorData* GetYmLaserColorData(pppYmLaser* laser, _pppCtrlTable* ctrlTable)
{
	return reinterpret_cast<pppYmLaserColorData*>(laser->m_workArea + GetYmLaserDataOffsets(ctrlTable)->m_colorBlockOffset);
}

STATIC_ASSERT(offsetof(pppYmLaser, m_workArea) == 0x80);

/*
 * --INFO--
 * PAL Address: 0x800d2614
 * PAL Size: 3008b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void pppRenderYmLaser(pppYmLaser* laser, pppLaserStep* step, _pppCtrlTable* data)
{
	pppYmLaserWork* work = GetYmLaserWork(laser, data);
	pppYmLaserColorData* colorData = GetYmLaserColorData(laser, data);
	s32 dataValIndex = step->m_dataValIndex;
	u32 count;
	s32 i;
	s32 alphaStep;
	char alphaMax;
	float negHalfWidth;
	float length;
	float halfWidth;
	float u0;
	float u1;
	float uvStep;
	pppFMATRIX mtxOut;
	pppFMATRIX unitMtx;
	Mtx shapeMtx;
	Mtx rotateMtx;
	Mtx debugMtx ATTRIBUTE_ALIGN(8);
	Mtx pointMtx;
	Mtx sphereMtx;
	Vec shapePos;
	Vec spherePos;
	Vec debugSource;
	_GXColor color;
	CTexture* texture;

	if (dataValIndex == 0xFFFF) {
		return;
	}

	texture = GetTextureFromRSD(dataValIndex, ppvEnv);
	pppSetBlendMode(step->m_laser.m_blendMode);
	_GXSetTevSwapMode(GX_TEVSTAGE1, GX_TEV_SWAP0, GX_TEV_SWAP0);
	pppSetDrawEnv(
		&colorData->m_color, &laser->m_localMatrix, LoadLaserFloat(kPppYmLaserZero), step->m_laser.m_drawEnvColor1,
		step->m_laser.m_drawEnvColor0, step->m_laser.m_blendMode, 0, 1, 1, 0);
	GXSetNumTevStages(1);
	GXSetNumTexGens(1);
	GXSetNumChans(1);
	GXSetCullMode(GX_CULL_NONE);
	_GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_OR, GX_ALWAYS, 0);
	color = *(_GXColor*)&colorData->m_color;
	_GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
	GXSetTexCoordGen2((GXTexCoordID)0, (GXTexGenType)1, (GXTexGenSrc)4, 0x3C, GX_FALSE, 0x7D);
	_GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC, GX_CC_ZERO);
	_GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
	_GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_RASA);
	_GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
	gUtil.SetVtxFmt_POS_CLR_TEX();
	GXLoadTexObj(&texture->m_texObj, GX_TEXMAP0);

	halfWidth = work->m_halfWidth;
	length = work->m_length;
	negHalfWidth = -halfWidth;

	pppUnitMatrix(unitMtx);
	pppMulMatrix(mtxOut, ppvMng->m_matrix, laser->m_localMatrix);
	pppMulMatrix(mtxOut, *(pppFMATRIX*)&ppvCameraMatrix, mtxOut);
	GXLoadPosMtxImm(mtxOut.value, 0);

	GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT7, 4);
	GXPosition3f32(negHalfWidth, LoadLaserFloat(kPppYmLaserZero), LoadLaserFloat(kPppYmLaserZero));
	GXColor1u32(*(u32*)&color);
	GXTexCoord2f32(LoadLaserFloat(kPppYmLaserZero), LoadLaserFloat(kPppYmLaserZero));
	GXPosition3f32(negHalfWidth, LoadLaserFloat(kPppYmLaserZero), length);
	GXColor1u32(*(u32*)&color);
	GXTexCoord2f32(LoadLaserFloat(kPppYmLaserZero), work->m_length);
	GXPosition3f32(halfWidth, LoadLaserFloat(kPppYmLaserZero), LoadLaserFloat(kPppYmLaserZero));
	GXColor1u32(*(u32*)&color);
	GXTexCoord2f32(LoadLaserFloat(kPppYmLaserOne), LoadLaserFloat(kPppYmLaserZero));
	GXPosition3f32(halfWidth, LoadLaserFloat(kPppYmLaserZero), length);
	GXColor1u32(*(u32*)&color);
	GXTexCoord2f32(LoadLaserFloat(kPppYmLaserOne), work->m_length);

	GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT7, 4);
	GXPosition3f32(LoadLaserFloat(kPppYmLaserZero), negHalfWidth, LoadLaserFloat(kPppYmLaserZero));
	GXColor1u32(*(u32*)&color);
	GXTexCoord2f32(LoadLaserFloat(kPppYmLaserZero), LoadLaserFloat(kPppYmLaserZero));
	GXPosition3f32(LoadLaserFloat(kPppYmLaserZero), negHalfWidth, length);
	GXColor1u32(*(u32*)&color);
	GXTexCoord2f32(LoadLaserFloat(kPppYmLaserZero), work->m_length);
	GXPosition3f32(LoadLaserFloat(kPppYmLaserZero), halfWidth, LoadLaserFloat(kPppYmLaserZero));
	GXColor1u32(*(u32*)&color);
	GXTexCoord2f32(LoadLaserFloat(kPppYmLaserOne), LoadLaserFloat(kPppYmLaserZero));
	GXPosition3f32(LoadLaserFloat(kPppYmLaserZero), halfWidth, length);
	GXColor1u32(*(u32*)&color);
	GXTexCoord2f32(LoadLaserFloat(kPppYmLaserOne), work->m_length);

	if (step->m_stepValue != 0xFFFF) {
		pppShapeSt* shape = ppvEnv->m_resourceTables.m_shapeTablePtr[step->m_stepValue];
		PSMTXIdentity(shapeMtx);
		shapeMtx[0][0] = step->m_laser.m_shapeScale * ppvMng->m_scale.x;
		shapeMtx[1][1] = step->m_laser.m_shapeScale * ppvMng->m_scale.y;
		shapeMtx[2][2] = shapeMtx[0][0];
		if (LoadLaserFloat(kPppYmLaserZero) != work->m_shapeRotation) {
			PSMTXRotRad(rotateMtx, 'z', work->m_shapeRotation);
			PSMTXConcat(shapeMtx, rotateMtx, shapeMtx);
		}
		PSMTXMultVec(ppvCameraMatrix, work->m_points, &shapePos);
		shapeMtx[0][3] = shapePos.x;
		shapeMtx[1][3] = shapePos.y;
		shapeMtx[2][3] = shapePos.z;
		GXLoadPosMtxImm(shapeMtx, GX_PNMTX0);
		pppDrawShp(static_cast<long*>(shape->m_animData), work->m_shapeArg2, ppvEnv->m_materialSetPtr,
		           step->m_laser.m_blendMode);

		count = step->m_laser.m_pointCount;
		uvStep = LoadLaserFloat(kPppYmLaserOne) / (float)count;
		if (step->m_initWOrk == 0xFFFF) {
			_GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
			_GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
		} else {
			texture = GetTextureFromRSD(step->m_initWOrk, ppvEnv);
			_GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
			GXLoadTexObj(&texture->m_texObj, GX_TEXMAP0);
		}

		GXLoadPosMtxImm(ppvCameraMatrix, GX_PNMTX0);
		alphaMax = step->m_laser.m_trailAlpha;
		alphaStep = (u8)((u8)alphaMax / (s32)step->m_laser.m_pointCount);
		color.r = step->m_laser.m_trailColorR;
		color.g = step->m_laser.m_trailColorG;
		color.b = step->m_laser.m_trailColorB;
		color.a = alphaMax;
		GXBegin(GX_TRIANGLES, GX_VTXFMT7, (u16)((step->m_laser.m_pointCount - 1) * 3));
		u8 trailColorR = color.r;
		u8 trailColorG = color.g;
		u8 trailColorB = color.b;
		for (int j = 0; j < (int)(step->m_laser.m_pointCount - 1); j++) {
			u0 = uvStep * (float)j;
			u1 = uvStep * (float)(j + 1);
			_GXColor trailStartColor;
			trailStartColor.r = trailColorR;
			trailStartColor.g = trailColorG;
			trailStartColor.b = trailColorB;
			trailStartColor.a = (u8)alphaMax - alphaStep * j;
			_GXColor trailEndColor;
			trailEndColor.r = trailColorR;
			trailEndColor.g = trailColorG;
			trailEndColor.b = trailColorB;
			trailEndColor.a = (u8)alphaMax - alphaStep * (j + 1);

			GXPosition3f32(work->m_origin.x, work->m_origin.y, work->m_origin.z);
			GXColor1u32(*(u32*)&trailStartColor);
			GXTexCoord2f32(u0, LoadLaserFloat(kPppYmLaserOne));

			GXPosition3f32(work->m_points[j].x, work->m_points[j].y, work->m_points[j].z);
			GXColor1u32(*(u32*)&trailStartColor);
			GXTexCoord2f32(u0, LoadLaserFloat(kPppYmLaserZero));

			GXPosition3f32(work->m_points[j + 1].x, work->m_points[j + 1].y, work->m_points[j + 1].z);
			GXColor1u32(*(u32*)&trailEndColor);
			GXTexCoord2f32(u1, LoadLaserFloat(kPppYmLaserZero));
		}

		if ((CFlatRuntimeDebugFlags() & CFlatRuntimeDebugFlag_ParticleHitSpheres) != 0) {
			gUtil.SetVtxFmt_POS_CLR();
			_GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
			_GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
			GXSetNumTexGens(0);
			pppSetBlendMode(1);

			color.r = 0x80;
			color.g = 0xFF;
			color.b = 0x80;
			color.a = 0xFF;
			GXSetChanAmbColor(GX_COLOR0A0, color);
			GXSetPointSize(0x28, GX_TO_ZERO);
			GXBegin(GX_POINTS, GX_VTXFMT7, (u16)(step->m_laser.m_pointCount - 1));
			for (int j = 0; j < (int)(step->m_laser.m_pointCount - 1); j++) {
				GXPosition3f32(work->m_points[j].x, work->m_points[j].y, work->m_points[j].z);
				GXColor1u32(*(u32*)&color);
			}

			color.r = 0x80;
			color.g = 0x80;
			color.b = 0xFF;
			color.a = 0xFF;
			GXSetChanAmbColor(GX_COLOR0A0, color);
			GXSetLineWidth(0x14, GX_TO_ZERO);
			GXBegin(GX_LINES, GX_VTXFMT7, (u16)((step->m_laser.m_pointCount - 1) * 4));
			for (int j = 0; j < (int)(step->m_laser.m_pointCount - 1); j++) {
				GXPosition3f32(work->m_points[j].x, work->m_points[j].y, work->m_points[j].z);
				GXColor1u32(*(u32*)&color);
				GXPosition3f32(work->m_points[j + 1].x, work->m_points[j + 1].y, work->m_points[j + 1].z);
				GXColor1u32(*(u32*)&color);
				GXPosition3f32(work->m_points[j].x, work->m_points[j].y, work->m_points[j].z);
				GXColor1u32(*(u32*)&color);
				GXPosition3f32(work->m_origin.x, work->m_origin.y, work->m_origin.z);
				GXColor1u32(*(u32*)&color);
			}

			GXSetLineWidth(8, GX_TO_ZERO);
			GXSetPointSize(8, GX_TO_ZERO);
			GXSetZMode(1, GX_LEQUAL, 0);

			if ((CFlatRuntimeDebugFlags() & CFlatRuntimeDebugFlag_ParticleHitSpheres) != 0) {
				float radius = ppvMng->m_hitScale * step->m_laser.m_hitScale;
				float distance = PSVECDistance(work->m_points, &work->m_origin);
				debugSource.x = LoadLaserFloat(kPppYmLaserZero);
				debugSource.y = LoadLaserFloat(kPppYmLaserZero);
				debugSource.z = LoadLaserFloat(kPppYmLaserOne);
				color.r = 0xFF;
				color.g = 0xFF;
				color.b = 0xFF;
				color.a = 0xFF;
				PSMTXIdentity(debugMtx);
				debugMtx[0][0] = radius;
				debugMtx[1][1] = radius;
				debugMtx[2][2] = distance;
				PSMTXConcat(laser->m_localMatrix.value, debugMtx, debugMtx);
				PSMTXConcat(ppvMng->m_matrix.value, debugMtx, debugMtx);
				PSMTXConcat(ppvCameraMatrix, debugMtx, debugMtx);
				PSMTXMultVec(debugMtx, &debugSource, &spherePos);
				debugMtx[0][3] = spherePos.x;
				debugMtx[1][3] = spherePos.y;
				debugMtx[2][3] = spherePos.z;
				Graphic.DrawSphere(debugMtx, color);
			}

			GXLoadPosMtxImm(laser->m_drawMatrix.value, GX_PNMTX0);
			color.r = 0xFF;
			color.g = 0xFF;
			color.b = 0xFF;
			color.a = 0xFF;
			for (i = 0; (int)i < (int)(u32)step->m_laser.m_pointCount; i++) {
				if ((work->m_points[i].x == LoadLaserFloat(kPppYmLaserZero)) &&
					(work->m_points[i].y == LoadLaserFloat(kPppYmLaserZero)) &&
					(work->m_points[i].z == LoadLaserFloat(kPppYmLaserZero))) {
					continue;
				}
				PSMTXScale(pointMtx, LoadLaserFloat(kPppYmLaserDebugPointScale), LoadLaserFloat(kPppYmLaserDebugPointScale),
				            LoadLaserFloat(kPppYmLaserDebugPointScale));
				pointMtx[0][3] = work->m_points[i].x;
				pointMtx[1][3] = work->m_points[i].y;
				pointMtx[2][3] = work->m_points[i].z;
				PSMTXConcat(ppvCameraMatrix, pointMtx, sphereMtx);
				Graphic.DrawSphere(sphereMtx, color);
			}

			pointMtx[0][3] = work->m_origin.x;
			pointMtx[1][3] = work->m_origin.y;
			pointMtx[2][3] = work->m_origin.z;
			PSMTXConcat(ppvCameraMatrix, pointMtx, sphereMtx);
			Graphic.DrawSphere(sphereMtx, color);
			pppInitBlendMode();
		}
	}
}

static const f32 kPppYmLaserHistoryBackstep = -1.0f;
static const f32 kPppYmLaserHitRayScale = 1.2f;
static const f32 kPppYmLaserCylinderMax = 10000000000.0f;
static const f32 kPppYmLaserCylinderMin = -10000000000.0f;
static const f32 kPppYmLaserFullTurn = 6.2831855f;

/*
 * --INFO--
 * PAL Address: 0x800d31d4
 * PAL Size: 1308b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void pppFrameYmLaser(pppYmLaser* laser, pppLaserStep* step, _pppCtrlTable* data)
{
	pppYmLaserWork* work;
	Vec localB;
	Vec localA;
	Mtx tempMtx;
	Mtx charaMtx;
	int emptyHistory;
	int fillIndex;

	if ((ppvUserStopPartF == 0) && (step->m_stepValue != 0xFFFF)) {
	work = GetYmLaserWork(laser, data);
	emptyHistory = 0;

	if (work->m_points == 0) {
		work->m_points = (Vec*)pppMemAlloc(
			(u32)step->m_laser.m_pointCount * 0xc, ppvEnv->m_stagePtr, const_cast<char*>(s_pppYmLaser_cpp), 0x5d);
		memset(work->m_points, 0, (u32)step->m_laser.m_pointCount * 0xc);
		emptyHistory = 1;
	}

	CalcGraphValue(
		(_pppPObject*)laser, step->m_graphId, work->m_halfWidth, work->m_graphValue2, work->m_graphValue3,
		step->m_laser.m_halfWidthBase,
		step->m_laser.m_halfWidthVelocity, step->m_laser.m_halfWidthAccel);
	CalcGraphValue(
		(_pppPObject*)laser, step->m_graphId, work->m_lengthStep, work->m_graphValue0, work->m_graphValue1,
		step->m_laser.m_lengthStepBase,
		step->m_laser.m_lengthStepVelocity, step->m_laser.m_lengthStepAccel);

	pppCalcFrameShape(
		static_cast<long*>(ppvEnv->m_resourceTables.m_shapeTablePtr[step->m_stepValue]->m_animData), work->m_shapeArg1,
		work->m_shapeArg2, work->m_shapeArg0, step->m_laser.m_shapeFrameStep);

	for (int i = 0; i < (int)((u32)step->m_laser.m_historyFrameCount + 1); i++) {
		int max = (int)step->m_laser.m_pointCount - 2;

		for (int j = max; (int)i <= j; j--) {
			pppCopyVector(work->m_points[j + 1], work->m_points[j]);
		}

		localB.x = LoadLaserFloat(kPppYmLaserZero);
		localB.y = LoadLaserFloat(kPppYmLaserZero);
		localB.z = work->m_length;

		if (i == 0) {
			PSMTXConcat(ppvMng->m_matrix.value, laser->m_localMatrix.value, tempMtx);
			work->m_origin.x = tempMtx[0][3];
			work->m_origin.y = tempMtx[1][3];
			work->m_origin.z = tempMtx[2][3];
			PSMTXMultVec(tempMtx, &localB, work->m_points);
		} else {
			if (emptyHistory) {
				continue;
			}

			s32 frameCount = step->m_laser.m_historyFrameCount + 1;
			float t = LoadLaserFloat(kPppYmLaserHistoryBackstep) / (float)frameCount;
			t *= (float)i;
			if (GetCharaNodeFrameMatrix(ppvMng, t, charaMtx) == 0) {
				emptyHistory = 1;
				continue;
			} else {
				PSMTXConcat(charaMtx, laser->m_localMatrix.value, charaMtx);
				PSMTXMultVec(charaMtx, &localB, &work->m_points[i]);
			}
		}

		pppSubVector(localA, work->m_points[i], work->m_origin);
		PSVECScale(&localA, &localA, LoadLaserFloat(kPppYmLaserHitRayScale));

		CMapCylinder cyl(LoadLaserFloat(kPppYmLaserCylinderMin), LoadLaserFloat(kPppYmLaserCylinderMax));
		cyl.m_bottom = work->m_origin;
		cyl.m_axis = localA;
		cyl.m_radius = LoadLaserFloat(kPppYmLaserZero);

		int check = MapMng.CheckHitCylinderNear(&cyl, &localA, 0xffffffff);
		int hit = 0;
		if (check != 0) {
			hit = 1;
			MapMng.m_hitMapObj->CalcHitPosition(&work->m_points[i]);
			work->m_length = PSVECDistance(&work->m_points[i], &work->m_origin);
		} else {
			if (i == 0) {
				work->m_length += work->m_lengthStep;
			}
		}

		if (i == 0) {
			localB.x = LoadLaserFloat(kPppYmLaserZero);
			localB.y = LoadLaserFloat(kPppYmLaserZero);
			localB.z = work->m_length;
			PSMTXMultVec(tempMtx, &localB, &work->m_points[i]);
		}

		if (step->m_laser.m_disableHitCylinder == 0) {
			pppHitCylinderSendSystem(
				ppvMng, &work->m_origin, &localA,
				ppvMng->m_hitScale * step->m_laser.m_hitScale,
				step->m_laser.m_hitRadius);
		}

		if (step->m_laser.m_disableHitObject == 0) {
			int createHitObject = 0;
			if (step->m_arg3 != -1) {
				createHitObject = 1;
			}
			if (!hit) {
				createHitObject = 0;
			}

			if (work->m_hitFrame < step->m_laser.m_hitInterval) {
				work->m_hitFrame++;
				createHitObject = 0;
			} else {
				work->m_hitFrame = 0;
			}

			if (createHitObject != 0) {
				_pppPDataVal* dataVal = ppvMng->m_pppPDataVals + step->m_arg3;
				_pppPObject* created;
				if (dataVal == 0) {
					created = 0;
				} else {
					created = pppCreatePObject(ppvMng, dataVal);
					created->m_link.m_previous = &laser->m_link;
				}

				Vec* createdPos = (Vec*)(created->m_workArea + step->m_laser.m_spawnPositionOffset);
				createdPos->x = work->m_points[i].x;
				createdPos->y = work->m_points[i].y + step->m_laser.m_spawnYOffset;
				createdPos->z = work->m_points[i].z;
			}
		}
	}

	if (emptyHistory) {
		for (fillIndex = 0; fillIndex < (int)(u32)step->m_laser.m_pointCount; fillIndex++) {
			pppCopyVector(work->m_points[fillIndex], work->m_points[0]);
		}
	}
}
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
	pppYmLaserWork* work = GetYmLaserWork(laser, ctrlTable);
	void* stage = work->m_points;

	if (stage != 0) {
		pppHeapUseRate(reinterpret_cast<CMemory::CStage*>(stage));
		work->m_points = 0;
	}
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
	f32 zero = kPppYmLaserZero;
	pppYmLaserWork* work = GetYmLaserWork(laser, ctrlTable);

	work->m_graphValue3 = zero;
	work->m_graphValue2 = zero;
	work->m_halfWidth = zero;
	work->m_graphValue1 = zero;
	work->m_graphValue0 = zero;
	work->m_lengthStep = zero;
	work->m_origin.z = zero;
	work->m_origin.y = zero;
	work->m_origin.x = zero;
	work->m_shapeReady = 0;
}

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
	f32 zero = kPppYmLaserZero;
	f32 randArg = kPppYmLaserFullTurn;
	pppYmLaserWork* work = GetYmLaserWork(laser, ctrlTable);

	work->m_length = zero;
	work->m_graphValue3 = zero;
	work->m_graphValue2 = zero;
	work->m_halfWidth = zero;
	work->m_graphValue1 = zero;
	work->m_graphValue0 = zero;
	work->m_lengthStep = zero;
	work->m_points = 0;
	work->m_origin.z = zero;
	work->m_origin.y = zero;
	work->m_origin.x = zero;
	work->m_shapeReady = 0;
	work->m_hitFrame = 0;
	work->m_unused2E = 0;
	work->m_shapeArg0 = 0;
	work->m_shapeArg2 = 0;
	work->m_shapeArg1 = 0;
	work->m_shapeRotation = Math.RandF(randArg);
}
