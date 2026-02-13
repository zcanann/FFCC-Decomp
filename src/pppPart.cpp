#include "ffcc/pppPart.h"

#include "ffcc/map.h"
#include "ffcc/p_game.h"
#include "ffcc/memory.h"
#include "ffcc/sound.h"
#include "ffcc/p_camera.h"
#include "ffcc/pppGetRotMatrixXYZ.h"
#include "ffcc/pppGetRotMatrixXZY.h"
#include "ffcc/pppGetRotMatrixYXZ.h"
#include "ffcc/pppGetRotMatrixYZX.h"
#include "ffcc/pppGetRotMatrixZXY.h"
#include "ffcc/pppGetRotMatrixZYX.h"

static const float kPppZero = 0.0; // FLOAT_8032fddc
static const float kPppOne = 1.0; // FLOAT_8032fdfc
static const double kScaleConstA = 4503601774854144.0; // DOUBLE_803304b0
static const float kScaleConstB = 0.017453292f; // FLOAT_803304a8
extern "C" unsigned char lbl_8032ED85;

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
_pppMngSt* pppStopSe(_pppMngSt* pppMngSt, PPPSEST* pppSest)
{
	if (pppSest->m_soundEffectSlot >= 0 && pppSest->m_soundEffectHandle >= 0)
	{
		pppMngSt = Sound.FadeOutSe3D(pppSest->m_soundEffectHandle, pppSest->m_soundEffectFadeFrames);
		pppSest->m_soundEffectHandle = -1;
	}

	return pppMngSt;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppUnitMatrix(pppFMATRIX& pppFMtx)
{ 
	PSMTXIdentity(pppFMtx.value);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppRotMatrix(pppFMATRIX& dst, pppFMATRIX src, Vec rot)
{
	pppFMATRIX Rx;
	pppFMATRIX Ry;
	pppFMATRIX Rz;
	pppFMATRIX R;

	PSMTXRotRad(Rx.value, 'x', rot.x);
	PSMTXRotRad(Ry.value, 'y', rot.y);
	PSMTXRotRad(Rz.value, 'z', rot.z);
	PSMTXConcat(Ry.value, Rz.value, R.value);
	PSMTXConcat(Rx.value, R.value, R.value);
	PSMTXConcat(R.value, src.value, dst.value);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppApplyMatrix(Vec& destination, pppFMATRIX pppFMatrix, Vec source)
{ 
	PSMTXMultVecSR(pppFMatrix.value, &source, &destination);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppAddVector(Vec& ab, Vec a, Vec b)
{ 
	PSVECAdd(&a, &b, &ab);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppScaleVectorXYZ(Vec& outVec, Vec inVec, float scale)
{ 
	PSVECScale(&inVec, &outVec, scale);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppScaleVector(Vec& outVec, Vec inVec, float scale)
{
	PSVECScale(&inVec, &outVec, scale);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppGetRowVector(pppFMATRIX& pppFMtx, Vec& vecA, Vec& vecB, Vec& vecC, Vec& vecD)
{
	vecA.x = pppFMtx.value[0][0];
	vecA.y = pppFMtx.value[1][0];
	vecA.z = pppFMtx.value[2][0];

	vecB.x = pppFMtx.value[0][1];
	vecB.y = pppFMtx.value[1][1];
	vecB.z = pppFMtx.value[2][1];

	vecC.x = pppFMtx.value[0][2];
	vecC.y = pppFMtx.value[1][2];
	vecC.z = pppFMtx.value[2][2];

	vecD.x = pppFMtx.value[0][3];
	vecD.y = pppFMtx.value[1][3];
	vecD.z = pppFMtx.value[2][3];
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppSetRowVector(pppFMATRIX& pppFMtx, Vec& vecA, Vec& vecB, Vec& vecC, Vec& vecD)
{
	pppFMtx.value[0][0] = vecA.x;
	pppFMtx.value[1][0] = vecA.y;
	pppFMtx.value[2][0] = vecA.z;

	pppFMtx.value[0][1] = vecB.x;
	pppFMtx.value[1][1] = vecB.y;
	pppFMtx.value[2][1] = vecB.z;

	pppFMtx.value[0][2] = vecC.x;
	pppFMtx.value[1][2] = vecC.y;
	pppFMtx.value[2][2] = vecC.z;

	pppFMtx.value[0][3] = vecD.x;
	pppFMtx.value[1][3] = vecD.y;
	pppFMtx.value[2][3] = vecD.z;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppNormalize(Vec& dest, Vec source)
{ 
	if ((source.x != kPppZero || source.y != kPppZero) || source.z != kPppZero)
	{
		PSVECNormalize(&source, &dest);
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppOuterProduct(Vec& ab, Vec a, Vec b)
{ 
	PSVECCrossProduct(&a, &b, &ab);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppCopyMatrix(pppFMATRIX& dest, pppFMATRIX source)
{ 
	PSMTXCopy(source.value, dest.value);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppMulMatrix(pppFMATRIX& ab, pppFMATRIX a, pppFMATRIX b)
{ 
	PSMTXConcat(a.value, b.value, ab.value);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppCopyVector(Vec& dest, Vec source)
{ 
	dest.x = source.x;
	dest.y = source.y;
	dest.z = source.z;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppSubVector(Vec& dest, Vec a, Vec b)
{ 
	PSVECSubtract(&a, &b, &dest);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
float pppVectorLength(Vec vec)
{
	Vec zeroVec;

	zeroVec.x = kPppZero;
	zeroVec.y = kPppZero;
	zeroVec.z = kPppZero;

	return PSVECDistance(&vec, &zeroVec);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppCreateHeap(_pppEnvSt* pppEnvSt, unsigned long param_2)
{ 
	pppEnvSt->m_stagePtr = Memory.CreateStage(param_2, "CPartPcs.heap", 0);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppDestroyHeap(_pppEnvSt* pppEnvSt)
{ 
	Memory.DestroyStage(pppEnvSt->m_stagePtr);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppMemAlloc(unsigned long, CMemory::CStage*, char*, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppMemFree(void*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppHeapUseRate(CMemory::CStage* stage)
{ 
	if (stage != (CMemory::CStage*)0)
	{
		Memory.Free(stage);
	}
}

/*
 * --INFO--
 * PAL Address: 80056c74
 * PAL Size: 44b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppHeapCheckLeak(CMemory::CStage* stage)
{
	stage->heapWalker(2, 0, 0xFFFFFFFF);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
unsigned long pppMngStHeapCheckLeak(CMemory::CStage* stage)
{
	unsigned long heapTotal;
	unsigned long heapUseRate;
	unsigned long heapUnused;

	stage->heapInfo(heapTotal, heapUseRate, heapUnused);
	if (heapTotal == 0) {
		heapTotal = 10000;
	} else {
		heapTotal = (heapUseRate * 10000) / heapTotal;
	}

	return heapTotal;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppMngStHeapCheck(CMemory::CStage* stage)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void callCon2Prog(_pppPObject*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void callConProg(_pppPObject*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppCreatePObject(_pppMngSt*, _pppPDataVal*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppDeletePObject(_pppPObject*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _pppAllFreePObject(_pppMngSt*)
{
	// TODO
}

static void InitOwnerFlagsAndScale(_pppMngSt* pppMngSt)
{
	u8* ownerBytes = (u8*)pppMngSt->m_owner;

	// Owner-facing
	if (!pppMngSt->m_ownerFacing) {
		u8 facing = ownerBytes[0x9A];
		pppMngSt->m_ownerFacing =
			(u8)(((u32)facing << 25) >> 31);
	}

	// Slot visible flags
	if (!pppMngSt->m_ownerFlagsInitialized) {
		u8 visible = 0;
		u32 flags = *(u32*)(ownerBytes + 0x60);

		if ((flags & 0x00000001) != 0 && (flags & 0x00400000) == 0) {
			visible = 1;
		}
		pppMngSt->m_slotVisible = visible;
		// Original code sets m_ownerFlagsInitialized somewhere else.
	}

	// Node scale
	if (!pppMngSt->m_nodeScaleInitialized) {
		bool useModelScale = false;

		int ownerData = *(int*)(ownerBytes + 0xF8);
		if (ownerData != 0 && *(int*)(ownerData + 0x168) != 0) {
			useModelScale = true;
		}

		float scale;
		if (useModelScale) {
			int modelPtr = *(int*)(ownerData + 0x168);
			scale = *(float*)(modelPtr + 0x9C);
		} else {
			scale = *(float*)(ownerBytes + 0x4B0);
		}

		pppMngSt->m_ownerScale = scale;

		// kScaleConstB *

		if (kScaleConstA == (double)pppMngSt->m_ownerScale) {
			pppMngSt->m_useOwnerScaleSign = 1;
		} else if (kScaleConstA == (double)pppMngSt->m_ownerScale) {
			pppMngSt->m_useOwnerScaleSign = 0;
		} else {
			pppMngSt->m_useOwnerScaleSign = 1;
		}

		// m_nodeScaleInitialized likely set somewhere else in original code
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppSetMatrix(_pppMngSt* pppMngSt)
{
	// 1) Build local rotation matrix into pppMngStPtr->m_matrix
	switch (pppMngSt->m_rotationOrder) {
	case 0:
		pppGetRotMatrixXYZ(pppMngStPtr->m_matrix, &pppMngSt->m_rotation);
		break;
	case 1:
		pppGetRotMatrixXZY(pppMngStPtr->m_matrix, &pppMngSt->m_rotation);
		break;
	case 2:
		pppGetRotMatrixYXZ(pppMngStPtr->m_matrix, &pppMngSt->m_rotation);
		break;
	case 3:
		pppGetRotMatrixYZX(pppMngStPtr->m_matrix, &pppMngSt->m_rotation);
		break;
	case 4:
		pppGetRotMatrixZXY(pppMngStPtr->m_matrix, &pppMngSt->m_rotation);
		break;
	case 5:
		pppGetRotMatrixZYX(pppMngStPtr->m_matrix, &pppMngSt->m_rotation);
		break;
	default:
		break;
	}

	u8 mode = pppMngSt->m_matrixMode;

	Mtx nodeMtx = {};
	Vec tmpPos;
	bool attached = false;

	if (mode == 5)
	{
		if (!pppMngSt->m_bindNode)
		{
			goto LocalOnly;
		}

		InitOwnerFlagsAndScale(pppMngSt);

		u8* ownerBytes = (u8*)pppMngSt->m_owner;
		int ownerData = *(int*)(ownerBytes + 0xF8);
		CChara::CModel* model = 0;

		if (ownerData != 0)
		{
			model = *(CChara::CModel**)(ownerData + 0x168);
		}

		// CalcSafeNodeWorldMatrix(model, nodeMtx, pppMngSt->m_bindNode);
		// (call commented if symbol not wired up)

		nodeMtx[0][3] += pppMngStPtr->m_position.x;
		nodeMtx[1][3] += pppMngStPtr->m_position.y;
		nodeMtx[2][3] += pppMngStPtr->m_position.z;

		PSMTXConcat(nodeMtx, pppMngStPtr->m_matrix.value, pppMngStPtr->m_matrix.value);
		attached = true;
	}
	else if (mode < 5)
	{
		if (mode == 3)
		{
			// Attach to character node (like 5) but slightly different flow
			if (!pppMngSt->m_bindNode) {
				goto LocalOnly;
			}

			InitOwnerFlagsAndScale(pppMngSt);

			u8* ownerBytes = (u8*)pppMngSt->m_owner;
			int ownerData = *(int*)(ownerBytes + 0xF8);
			CChara::CModel* model = 0;

			if (ownerData != 0)
			{
				model = *(CChara::CModel**)(ownerData + 0x168);
			}

			// CalcSafeNodeWorldMatrix(model, nodeMtx, pppMngSt->m_bindNode);

			nodeMtx[0][3] += pppMngStPtr->m_position.x;
			nodeMtx[1][3] += pppMngStPtr->m_position.y;
			nodeMtx[2][3] += pppMngStPtr->m_position.z;

			PSMTXConcat(nodeMtx, pppMngStPtr->m_matrix.value, pppMngStPtr->m_matrix.value);
			attached = true;
		}
		else
		{
			// mode == 2 or 4 (map object world matrix)
			if (mode > 2)
			{
				// mode == 4
				// GetMapObjWMtx(&MapMng, pppMngSt->m_mapObjIndex, nodeMtx);
				MapMng.GetMapObjWMtx(pppMngSt->m_mapObjIndex, nodeMtx);

				nodeMtx[0][3] += pppMngStPtr->m_position.x;
				nodeMtx[1][3] += pppMngStPtr->m_position.y;
				nodeMtx[2][3] += pppMngStPtr->m_position.z;

				PSMTXConcat(nodeMtx, pppMngStPtr->m_matrix.value, pppMngStPtr->m_matrix.value);
				attached = true;
			}
			else
			{
				// mode == 2
				if (pppMngSt->m_mapObjIndex == -1)
				{
					goto LocalOnly;
				}

				// GetMapObjWMtx(&MapMng, pppMngSt->m_mapObjIndex, nodeMtx);
				MapMng.GetMapObjWMtx(pppMngSt->m_mapObjIndex, nodeMtx);

				nodeMtx[0][3] += pppMngStPtr->m_position.x;
				nodeMtx[1][3] += pppMngStPtr->m_position.y;
				nodeMtx[2][3] += pppMngStPtr->m_position.z;

				PSMTXConcat(nodeMtx, pppMngStPtr->m_matrix.value, pppMngStPtr->m_matrix.value);
				attached = true;
			}
		}
	}
	else {
		if (mode == 7)
		{
			if (!pppMngSt->m_bindNode)
			{
				goto LocalOnly;
			}

			InitOwnerFlagsAndScale(pppMngSt);

			u8* ownerBytes = (u8*)pppMngSt->m_owner;
			int ownerData = *(int*)(ownerBytes + 0xF8);
			CChara::CModel* model = 0;

			if (ownerData != 0)
			{
				model = *(CChara::CModel**)(ownerData + 0x168);
			}

			// CalcSafeNodeWorldMatrix(model, nodeMtx, pppMngSt->m_bindNode);

			PSMTXMultVecSR(nodeMtx, &pppMngStPtr->m_position, &tmpPos);

			pppMngStPtr->m_matrix.value[0][3] = nodeMtx[0][3] + tmpPos.x;
			pppMngStPtr->m_matrix.value[1][3] = nodeMtx[1][3] + tmpPos.y;
			pppMngStPtr->m_matrix.value[2][3] = nodeMtx[2][3] + tmpPos.z;

			attached = true;
		}
		else
		{
			if (mode > 6 || !pppMngSt->m_bindNode)
			{
				goto LocalOnly;
			}

			InitOwnerFlagsAndScale(pppMngSt);

			u8* ownerBytes = (u8*)pppMngSt->m_owner;
			int ownerData = *(int*)(ownerBytes + 0xF8);
			CChara::CModel* model = 0;

			if (ownerData != 0)
			{
				model = *(CChara::CModel**)(ownerData + 0x168);
			}

			// CalcSafeNodeWorldMatrix(model, nodeMtx, pppMngSt->m_bindNode);

			Vec col0;
			Vec col1;
			Vec col2;

			col0.x = nodeMtx[0][0];
			col0.y = nodeMtx[1][0];
			col0.z = nodeMtx[2][0];

			col1.x = nodeMtx[0][1];
			col1.y = nodeMtx[1][1];
			col1.z = nodeMtx[2][1];

			col2.x = nodeMtx[0][2];
			col2.y = nodeMtx[1][2];
			col2.z = nodeMtx[2][2];

			PSVECNormalize(&col0, &col0);
			PSVECNormalize(&col1, &col1);
			PSVECNormalize(&col2, &col2);

			nodeMtx[0][0] = col0.x; nodeMtx[1][0] = col0.y; nodeMtx[2][0] = col0.z;
			nodeMtx[0][1] = col1.x; nodeMtx[1][1] = col1.y; nodeMtx[2][1] = col1.z;
			nodeMtx[0][2] = col2.x; nodeMtx[1][2] = col2.y; nodeMtx[2][2] = col2.z;

			PSMTXMultVecSR(nodeMtx, &pppMngStPtr->m_position, &tmpPos);

			nodeMtx[0][3] += tmpPos.x;
			nodeMtx[1][3] += tmpPos.y;
			nodeMtx[2][3] += tmpPos.z;

			PSMTXConcat(nodeMtx, pppMngStPtr->m_matrix.value, pppMngStPtr->m_matrix.value);
			attached = true;
		}
	}

	if (!attached)
	{
	LocalOnly:
		Vec col;

		col.x = pppMngStPtr->m_matrix.value[0][0];
		col.y = pppMngStPtr->m_matrix.value[1][0];
		col.z = pppMngStPtr->m_matrix.value[2][0];
		PSVECScale(&col, &col, pppMngSt->m_scale.x);
		pppMngStPtr->m_matrix.value[0][0] = col.x;
		pppMngStPtr->m_matrix.value[1][0] = col.y;
		pppMngStPtr->m_matrix.value[2][0] = col.z;

		col.x = pppMngStPtr->m_matrix.value[0][1];
		col.y = pppMngStPtr->m_matrix.value[1][1];
		col.z = pppMngStPtr->m_matrix.value[2][1];
		PSVECScale(&col, &col, pppMngSt->m_scale.y);
		pppMngStPtr->m_matrix.value[0][1] = col.x;
		pppMngStPtr->m_matrix.value[1][1] = col.y;
		pppMngStPtr->m_matrix.value[2][1] = col.z;

		col.x = pppMngStPtr->m_matrix.value[0][2];
		col.y = pppMngStPtr->m_matrix.value[1][2];
		col.z = pppMngStPtr->m_matrix.value[2][2];
		PSVECScale(&col, &col, pppMngSt->m_scale.z);
		pppMngStPtr->m_matrix.value[0][2] = col.x;
		pppMngStPtr->m_matrix.value[1][2] = col.y;
		pppMngStPtr->m_matrix.value[2][2] = col.z;

		pppMngStPtr->m_matrix.value[0][3] = pppMngSt->m_position.x;
		pppMngStPtr->m_matrix.value[1][3] = pppMngSt->m_position.y;
		pppMngStPtr->m_matrix.value[2][3] = pppMngSt->m_position.z;
		return;
	}

	if (pppMngSt->m_scale.x != kPppOne)
	{
		Vec col;
		col.x = pppMngStPtr->m_matrix.value[0][0];
		col.y = pppMngStPtr->m_matrix.value[1][0];
		col.z = pppMngStPtr->m_matrix.value[2][0];
		PSVECScale(&col, &col, pppMngSt->m_scale.x);
		pppMngStPtr->m_matrix.value[0][0] = col.x;
		pppMngStPtr->m_matrix.value[1][0] = col.y;
		pppMngStPtr->m_matrix.value[2][0] = col.z;
	}

	if (pppMngSt->m_scale.y != kPppOne)
	{
		Vec col;
		col.x = pppMngStPtr->m_matrix.value[0][1];
		col.y = pppMngStPtr->m_matrix.value[1][1];
		col.z = pppMngStPtr->m_matrix.value[2][1];
		PSVECScale(&col, &col, pppMngSt->m_scale.y);
		pppMngStPtr->m_matrix.value[0][1] = col.x;
		pppMngStPtr->m_matrix.value[1][1] = col.y;
		pppMngStPtr->m_matrix.value[2][1] = col.z;
	}

	if (pppMngSt->m_scale.z != kPppOne)
	{
		Vec col;
		col.x = pppMngStPtr->m_matrix.value[0][2];
		col.y = pppMngStPtr->m_matrix.value[1][2];
		col.z = pppMngStPtr->m_matrix.value[2][2];
		PSVECScale(&col, &col, pppMngSt->m_scale.z);
		pppMngStPtr->m_matrix.value[0][2] = col.x;
		pppMngStPtr->m_matrix.value[1][2] = col.y;
		pppMngStPtr->m_matrix.value[2][2] = col.z;
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppSetFpMatrix(_pppMngSt* pppMngSt)
{
	Vec pos;
	Vec up;
	Vec upTmp;
	Vec right;
	Vec rightTmp;
	Vec forward;
	Vec forwardTmp;
	Mtx localMtx = {};

	PSMTXCopy(pppMngStPtr->m_matrix.value, localMtx);

	if (pppMngSt->m_fpBillboard == 0)
	{
		PSMTXConcat(ppvCameraMatrix0, pppMngStPtr->m_matrix.value, ppvWorldMatrix);

		pos.x = localMtx[0][3];
		pos.y = localMtx[1][3];
		pos.z = localMtx[2][3];

		PSMTXMultVec(ppvCameraMatrix0, &pos, &pos);
	}
	else
	{
		PSMTXConcat(ppvCameraMatrix0, pppMngStPtr->m_matrix.value, ppvWorldMatrix);

		pos.x = localMtx[0][3];
		pos.y = localMtx[1][3];
		pos.z = localMtx[2][3];

		PSMTXMultVecSR(ppvCameraMatrix0, &pos, &pos);

		pos.y += CameraPcs._228_4_;
	}

	up.x = ppvWorldMatrix[0][1];
	up.y = ppvWorldMatrix[1][1];
	up.z = ppvWorldMatrix[2][1];

	upTmp = up;

	ppvWorldMatrix[0][3] = pos.x;
	ppvWorldMatrix[1][3] = pos.y;
	ppvWorldMatrix[2][3] = pos.z;

	if (ppvWorldMatrix[0][1] != kPppZero || ppvWorldMatrix[1][1] != kPppZero || ppvWorldMatrix[2][1] != kPppZero)
	{
		PSVECNormalize(&upTmp, &up);
	}

	right.x	= up.y;
	rightTmp.x = up.y;
	rightTmp.y = -up.x;
	right.y	= rightTmp.y;
	right.z	= kPppZero;
	rightTmp.z = kPppZero;

	ppvWorldMatrixWood[0][1] = up.x;
	ppvWorldMatrixWood[1][1] = up.y;
	ppvWorldMatrixWood[2][1] = up.z;

	if (up.y != kPppZero || rightTmp.y != kPppZero)
	{
		PSVECNormalize(&rightTmp, &right);
	}

	ppvWorldMatrixWood[0][0] = right.x;
	ppvWorldMatrixWood[1][0] = right.y;
	ppvWorldMatrixWood[2][0] = right.z;

	PSVECCrossProduct(&right, &up, &forward);
	forwardTmp = forward;

	if (forward.x != kPppZero || forward.y != kPppZero || forward.z != kPppZero)
	{
		PSVECNormalize(&forwardTmp, &forward);
	}

	ppvWorldMatrixWood[0][2] = forward.x;
	ppvWorldMatrixWood[1][2] = forward.y;
	ppvWorldMatrixWood[2][2] = forward.z;

	ppvWorldMatrixWood[0][3] = ppvWorldMatrix[0][3];
	ppvWorldMatrixWood[1][3] = ppvWorldMatrix[1][3];
	ppvWorldMatrixWood[2][3] = ppvWorldMatrix[2][3];
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppCacheLoadModel(short*, _pppDataHead*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppCacheLoadShape(short*, _pppDataHead*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppCacheUnLoadModel(short*, _pppDataHead*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppCacheUnLoadShape(short*, _pppDataHead*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppCacheRefCnt0UpModel(short*, _pppDataHead*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppCacheRefCnt0UpShape(short*, _pppDataHead*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppCacheDumpModel(short*, _pppDataHead*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppCacheDumpShape(short*, _pppDataHead*)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 80055308
 * PAL Size: 1376b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void _pppStartPart(_pppMngSt* pppMngSt, long* pdt, int runControlPrograms)
{
	struct pppProgramSetDefRaw
	{
		pppProgramSetDefRaw* m_next;
		int m_unk4;
		int m_unk8;
		int m_unkC;
		int m_startFrame;
	};

	struct pppPDataValRaw
	{
		pppProgramSetDefRaw* m_programSetDef;
		int m_nextSpawnTime;
		_pppPObjLink* m_objHead;
		short m_activeCount;
		unsigned char m_index;
		unsigned char m_pad;
	};

	pppMngStPtr = pppMngSt;

	unsigned char* mngBytes = (unsigned char*)pppMngSt;
	*(int*)(mngBytes + 0x24) = (int)pdt[0];
	*(unsigned char*)(mngBytes + 0xF4) = (unsigned char)pdt[1];
	*(unsigned char*)(mngBytes + 0xE6) = 0;

	short* modelList = (short*)((unsigned char*)pdt + pdt[4]);
	short* shapeList = (short*)((unsigned char*)pdt + pdt[5]);

	if (Game.game.m_currentSceneId != 7) {
		pppCacheLoadModel(modelList, (_pppDataHead*)pdt);
		pppCacheLoadShape(shapeList, (_pppDataHead*)pdt);
		*(unsigned char*)(mngBytes + 0xF5) = 1;
	}

	int controlOffset = (int)pdt[2];
	int programOffset = (int)pdt[3];
	int controlCount = *(int*)((unsigned char*)pdt + controlOffset);
	int programCount = *(int*)((unsigned char*)pdt + programOffset);

	*(int*)(mngBytes + 0xB4) = controlCount;
	*(int*)(mngBytes + 0xB8) = programCount;
	*(void**)(mngBytes + 0xCC) = (void*)((int*)((unsigned char*)pdt + controlOffset) + 1);
	*(void**)(mngBytes + 0xD0) = (void*)((int*)((unsigned char*)pdt + programOffset) + 1);
	*(int*)(mngBytes + 0x34) = 0;
	*(int*)(mngBytes + 0xAC) = 0;

	pppPDataValRaw* pDataVals = 0;
	if (programCount > 0) {
		pDataVals = (pppPDataValRaw*)new (pppEnvStPtr->m_stagePtr, (char*)"pppPart.cpp", 0x585) unsigned char[programCount * 0x10];
	}
	*(void**)(mngBytes + 0xC8) = pDataVals;

	pppProgramSetDefRaw* programSet = (pppProgramSetDefRaw*)(pdt + 6);
	for (int i = 0; i < programCount && programSet != 0 && pDataVals != 0; i++) {
		pDataVals[i].m_programSetDef = programSet;
		pDataVals[i].m_nextSpawnTime = programSet->m_startFrame;
		pDataVals[i].m_objHead = 0;
		pDataVals[i].m_activeCount = 0;
		pDataVals[i].m_index = (unsigned char)i;
		pDataVals[i].m_pad = 0;
		programSet = programSet->m_next;
	}

	if (runControlPrograms != 0) {
		void** controlTable = (void**)*(void**)(mngBytes + 0xCC);
		for (int i = 0; i < controlCount; i++) {
			unsigned char* controlEntry = (unsigned char*)controlTable[i];
			if (controlEntry != 0) {
				void (*fn)(_pppMngSt*) = *(void (**)(_pppMngSt*))(controlEntry + 0x10);
				if (fn != 0) {
					fn(pppMngSt);
				}
			}
		}
	}
}

/*
 * --INFO--
 * PAL Address: 800550ac
 * PAL Size: 604b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppInitPdt(long* progOffsetReconstructionTable, pppProg* pppProg)
{
	int pppProgRelocCount = *(int*)((int)progOffsetReconstructionTable + progOffsetReconstructionTable[2]);
	int pdtRelocCount = *(int*)((int)progOffsetReconstructionTable + progOffsetReconstructionTable[3]);
	int* pppProgRelocs = (int*)((int)progOffsetReconstructionTable + progOffsetReconstructionTable[2]) + 1;
	int* pdtRelocs = (int*)((int)progOffsetReconstructionTable + progOffsetReconstructionTable[3]) + 1;
	int* table = (int*)(progOffsetReconstructionTable + 6);

	if (progOffsetReconstructionTable[6] == 0) {
		return;
	}

	int* entry = table;
	int* head = 0;
	do {
		head = entry;
		*head = (int)progOffsetReconstructionTable + *head;
		entry = head;

		for (int i = 0; i < *(short*)((int)head + 0x26); i++) {
			entry[10] = (int)(pppProg + entry[10]);
			entry[12] = (int)progOffsetReconstructionTable + entry[12];
			entry[13] = (int)progOffsetReconstructionTable + entry[13];
			entry += 4;
		}

		entry = (int*)*head;
	} while (*(int*)*head != 0);

	int processed = 0;
	*entry = 0;
	if (pppProgRelocCount > 0) {
		if (pppProgRelocCount > 8) {
			unsigned int blocks = (unsigned int)(pppProgRelocCount - 1) >> 3;
			int* reloc = pppProgRelocs;
			if (pppProgRelocCount - 8 > 0) {
				do {
					processed += 8;
					reloc[0] = (int)(pppProg + reloc[0]);
					reloc[1] = (int)(pppProg + reloc[1]);
					reloc[2] = (int)(pppProg + reloc[2]);
					reloc[3] = (int)(pppProg + reloc[3]);
					reloc[4] = (int)(pppProg + reloc[4]);
					reloc[5] = (int)(pppProg + reloc[5]);
					reloc[6] = (int)(pppProg + reloc[6]);
					reloc[7] = (int)(pppProg + reloc[7]);
					reloc += 8;
					blocks--;
				} while (blocks != 0);
			}
		}

		int remain = pppProgRelocCount - processed;
		int* reloc = pppProgRelocs + processed;
		if (processed < pppProgRelocCount) {
			do {
				*reloc = (int)(pppProg + *reloc);
				reloc++;
				remain--;
			} while (remain != 0);
		}
	}

	processed = 0;
	if (pdtRelocCount > 0) {
		if (pdtRelocCount > 8) {
			unsigned int blocks = (unsigned int)(pdtRelocCount - 1) >> 3;
			int* reloc = pdtRelocs;
			if (pdtRelocCount - 8 > 0) {
				do {
					processed += 8;
					reloc[0] += (int)progOffsetReconstructionTable;
					reloc[1] += (int)progOffsetReconstructionTable;
					reloc[2] += (int)progOffsetReconstructionTable;
					reloc[3] += (int)progOffsetReconstructionTable;
					reloc[4] += (int)progOffsetReconstructionTable;
					reloc[5] += (int)progOffsetReconstructionTable;
					reloc[6] += (int)progOffsetReconstructionTable;
					reloc[7] += (int)progOffsetReconstructionTable;
					reloc += 8;
					blocks--;
				} while (blocks != 0);
			}
		}

		int remain = pdtRelocCount - processed;
		int* reloc = pdtRelocs + processed;
		if (processed < pdtRelocCount) {
			do {
				*reloc += (int)progOffsetReconstructionTable;
				reloc++;
				remain--;
			} while (remain != 0);
		}
	}
}

/*
 * --INFO--
 * PAL Address: 80054d88
 * PAL Size: 804b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppInitData(_pppDataHead* pppDataHead, pppProg* pppProg, int param_3)
{
	// Convert relative offsets to absolute addresses
	pppDataHead->m_cacheChunks = (int)&pppDataHead->m_version + pppDataHead->m_cacheChunks;
	pppDataHead->m_modelNames = (int)&pppDataHead->m_version + pppDataHead->m_modelNames;
	pppDataHead->m_shapeNames = (int)&pppDataHead->m_version + pppDataHead->m_shapeNames;
	pppDataHead->m_shapeGroups = (int)&pppDataHead->m_version + pppDataHead->m_shapeGroups;
	
	// Basic cache chunk processing
	int* originalChunks = (int*)pppDataHead->m_cacheChunks;
	for (int i = 0; i < (int)(unsigned int)pppDataHead->m_cacheChunkCount; i++) {
		// Process cache chunks - simplified implementation
	}
	
	// Basic model names processing  
	unsigned int modelNamesOffset = pppDataHead->m_modelNames;
	for (int i = 0; i < (int)(unsigned int)pppDataHead->m_modelCount; i++) {
		// Process model names - simplified implementation
		modelNamesOffset += 0x20;
	}
	
	// Basic shape names processing
	unsigned int shapeNamesOffset = pppDataHead->m_shapeNames;
	for (int i = 0; i < (int)(unsigned int)pppDataHead->m_shapeCount; i++) {
		// Process shape names - simplified implementation
		shapeNamesOffset += 0x20;
	}
	
	// Basic shape groups processing
	unsigned short* originalGroups = (unsigned short*)pppDataHead->m_shapeGroups;
	for (int i = 0; i < (int)(unsigned int)pppDataHead->m_shapeGroupCount; i++) {
		// Process shape groups - simplified implementation
		originalGroups += 4;
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppCalcPartStd(_pppMngSt*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppDrawPartStd(_pppMngSt*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _pppDeadPart(_pppMngSt*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _pppInitPart(_pppMngSt*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void apeaPObject(_pppMngSt*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _pppCalcPart(_pppMngSt*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void _pppDrawPart(_pppMngSt*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppDrawMesh(pppModelSt*, Vec*, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppInitBlendMode()
{
	lbl_8032ED85 = 0xFF;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppSetBlendMode(unsigned char)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppClearDrawEnv()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppSetDrawEnv(pppCVECTOR*, pppFMATRIX*, float, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppInitDrawEnv(unsigned char)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppHitCylinderSendSystem(_pppMngSt*, Vec*, Vec*, float, float)
{
	// TODO
}
