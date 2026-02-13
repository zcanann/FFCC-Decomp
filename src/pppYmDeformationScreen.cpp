#include "ffcc/pppYmDeformationScreen.h"
#include "ffcc/p_game.h"
#include "ffcc/partMng.h"

#include <dolphin/mtx.h>

struct pppYmDeformationScreen;
struct YmDeformationScreenOffsetData {
	int unk0;
	int unk1;
	int offset;
};

struct YmDeformationScreenParam {
	char pad[0xc];
	YmDeformationScreenOffsetData* offsetData;
};

struct Vec4d {
	float x;
	float y;
	float z;
	float w;
};

struct YmDeformationScreenData {
	int* m_serializedDataOffsets;
};

struct YmDeformationScreenStep {
	int m_graphId;
	int m_dataValIndex;
	float m_initWOrk;
	float m_stepValue;
	float m_arg3;
	float m_payload0;
	float m_payload1;
	float m_payload2;
	short m_payload3;
	char m_payloadBytes[0x1a];
};

extern int DAT_8032ed70;
extern char DAT_8032ed78;

extern struct {
	float _212_4_;
	float _216_4_;
	float _220_4_;
	float _224_4_;
	float _228_4_;
	float _232_4_;
	Mtx m_cameraMatrix;
	Mtx44 m_screenMatrix;
} CameraPcs;

extern "C" {
void CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf(float, void*, int, float*, float*, float*, float*, float*);
void MTX44MultVec4__5CMathFPA4_fP5Vec4dP5Vec4d(void*, Mtx44, Vec4d*, Vec4d*);
void pppSetFpMatrix__FP9_pppMngSt(_pppMngSt*);
}

/*
 * --INFO--
 * PAL Address: 0x80098a94
 * PAL Size: 64b
 */
void pppConstructYmDeformationScreen(pppYmDeformationScreen* obj, void* param2)
{
	int offset = ((YmDeformationScreenParam*)param2)->offsetData->offset;
	char* basePtr = (char*)obj + offset + 0x80;
	float zero = 0.0f;

	*(short*)(basePtr + 0x4) = 0;
	*(char*)(basePtr + 0x6) = 1;
	*(float*)(basePtr + 0x10) = zero;
	*(float*)(basePtr + 0xc) = zero;
	*(float*)(basePtr + 0x8) = zero;
	*(float*)(basePtr + 0x1c) = zero;
	*(float*)(basePtr + 0x18) = zero;
	*(float*)(basePtr + 0x14) = zero;
}

/*
 * --INFO--
 * PAL Address: 0x80098a64
 * PAL Size: 48b
 */
void pppConstruct2YmDeformationScreen(pppYmDeformationScreen* obj, void* param2)
{
	float zero = 0.0f;
	int offset = ((YmDeformationScreenParam*)param2)->offsetData->offset;
	char* basePtr = (char*)obj + offset + 0x80;

	*(float*)(basePtr + 0x10) = zero;
	*(float*)(basePtr + 0xc) = zero;
	*(float*)(basePtr + 0x8) = zero;
	*(float*)(basePtr + 0x1c) = zero;
	*(float*)(basePtr + 0x18) = zero;
	*(float*)(basePtr + 0x14) = zero;
}

/*
 * --INFO--
 * PAL Address: 0x80098a60
 * PAL Size: 4b
 */
void pppDestructYmDeformationScreen(void)
{
	return;
}

/*
 * --INFO--
 * PAL Address: 0x8009885c
 * PAL Size: 516b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppFrameYmDeformationScreen(pppYmDeformationScreen* param1, void* param2, void* param3)
{
	Vec4d inVec;
	Vec4d outVec;
	Mtx44 screenMtx;
	float* work;
	short* angle;
	float cameraX;
	float cameraY;
	float cameraZ;
	YmDeformationScreenStep* step;

	if (DAT_8032ed70 != 0) {
		return;
	}

	step = (YmDeformationScreenStep*)param2;
	work = (float*)((char*)param1 + 0x80 + ((YmDeformationScreenData*)param3)->m_serializedDataOffsets[2]);
	angle = (short*)(work + 1);

	CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf(
		step->m_initWOrk, param1, step->m_graphId, work + 2, work + 3, work + 4, &step->m_stepValue, &step->m_arg3);
	CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf(
		step->m_payload0, param1, step->m_graphId, work + 5, work + 6, work + 7, &step->m_payload1, &step->m_payload2);

	if (DAT_8032ed78 != 0) {
		return;
	}

	if (*((char*)work + 6) == 0) {
		*angle = *angle - (short)(int)work[5];
		if ((int)*angle < -(int)step->m_payload3) {
			*((char*)work + 6) = 1;
		}
	} else {
		*angle = *angle + (short)(int)work[5];
		if (step->m_payload3 < *angle) {
			*((char*)work + 6) = 0;
		}
	}

	if (((_pppPObject*)param1)->m_graphId == 0) {
		PSMTX44Copy(CameraPcs.m_screenMatrix, screenMtx);
		inVec.x = 0.0f;
		inVec.y = 0.0f;
		inVec.z = -*(float*)((char*)&step->m_payload0 + 0x10);
		inVec.w = 1.0f;
		MTX44MultVec4__5CMathFPA4_fP5Vec4dP5Vec4d(0, screenMtx, &inVec, &outVec);
		if (outVec.w != 0.0f) {
			outVec.z /= outVec.w;
		}
		work[0] = outVec.z;
	}

	cameraX = CameraPcs._212_4_;
	cameraY = CameraPcs._216_4_;
	cameraZ = CameraPcs._220_4_;
	if (Game.game.m_currentSceneId == 7) {
		cameraX = ppvCameraMatrix0[0][3];
		cameraY = ppvCameraMatrix0[1][3];
		cameraZ = ppvCameraMatrix0[2][3];
	}
	pppMngStPtr->m_matrix.value[0][3] = cameraX;
	pppMngStPtr->m_matrix.value[1][3] = cameraY;
	pppMngStPtr->m_matrix.value[2][3] = cameraZ;
	pppSetFpMatrix__FP9_pppMngSt(pppMngStPtr);
}

/*
 * --INFO--
 * PAL Address: 0x800981a8
 * PAL Size: 1716b
 */
void pppRenderYmDeformationScreen(pppYmDeformationScreen* param1, void* param2, void* param3)
{
	// TODO - implement based on Ghidra decomp
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void SetUpIndWarp(VYmDeformationScreen*)
{
	// TODO
}
