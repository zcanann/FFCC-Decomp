#include "ffcc/pppYmLaser.h"
#include "ffcc/math.h"
#include "ffcc/map.h"
#include "ffcc/partMng.h"

#include <string.h>

extern CMath Math;
extern "C" float RandF__5CMathFf(float param, CMath* math);
extern "C" void pppHeapUseRate__FPQ27CMemory6CStage(void* stage);
extern struct _pppMngSt* pppMngStPtr;
extern s32 DAT_8032ed70;
extern CMapMng MapMng;
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

/*
 * --INFO--
 * PAL Address: 0x800d3780
 * PAL Size: 152b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void pppConstructYmLaser(void* pppYmLaser, void* param_2)
{
	YmLaserParam* data = (YmLaserParam*)param_2;
	float one = 1.0f;
	float* work = (float*)((unsigned char*)pppYmLaser + 0x88 + data->offsets->m_serializedDataOffsets[2]);

	*work = 1.0f;
	work[6] = one;
	work[5] = one;
	work[4] = one;
	work[3] = one;
	work[2] = one;
	work[1] = one;
	work[7] = 0.0f;
	work[10] = one;
	work[9] = one;
	work[8] = one;
	*((unsigned char*)work + 0x2c) = 0;
	*((unsigned char*)work + 0x2d) = 0;
	*((unsigned char*)work + 0x2e) = 0;
	*((unsigned short*)((unsigned char*)work + 0x30)) = 0;
	*((unsigned short*)((unsigned char*)work + 0x34)) = 0;
	*((unsigned short*)((unsigned char*)work + 0x32)) = 0;
	work[14] = RandF__5CMathFf(1.0f, &Math);
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
extern "C" void pppConstruct2YmLaser(void* pppYmLaser, void* param_2)
{
	YmLaserParam* data = (YmLaserParam*)param_2;
	float one = 1.0f;
	int dataOffset = data->offsets->m_serializedDataOffsets[2];

	*(float*)((unsigned char*)pppYmLaser + 0x98 + dataOffset) = one;
	*(float*)((unsigned char*)pppYmLaser + 0x94 + dataOffset) = one;
	*(float*)((unsigned char*)pppYmLaser + 0x90 + dataOffset) = one;
	*(float*)((unsigned char*)pppYmLaser + 0x8c + dataOffset) = one;
	*(float*)((unsigned char*)pppYmLaser + 0x88 + dataOffset) = one;
	*(float*)((unsigned char*)pppYmLaser + 0x84 + dataOffset) = one;
	*(float*)((unsigned char*)pppYmLaser + 0xa8 + dataOffset) = one;
	*(float*)((unsigned char*)pppYmLaser + 0xa4 + dataOffset) = one;
	*(float*)((unsigned char*)pppYmLaser + 0xa0 + dataOffset) = one;
	*((unsigned char*)pppYmLaser + 0xac + dataOffset) = 0;
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
extern "C" void pppDestructYmLaser(void* pppYmLaser, void* param_2)
{
	YmLaserOffsets* offsets = (YmLaserOffsets*)param_2;
	int dataOffset = offsets->m_serializedDataOffsets[2];
	void* stage = *(void**)((unsigned char*)pppYmLaser + 0x9c + dataOffset);

	if (stage != 0) {
		pppHeapUseRate__FPQ27CMemory6CStage(stage);
		*(void**)((unsigned char*)pppYmLaser + 0x9c + dataOffset) = 0;
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
	// TODO - Complex rendering logic with GX calls
}
