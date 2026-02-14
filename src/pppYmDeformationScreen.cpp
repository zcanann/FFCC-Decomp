#include "ffcc/pppYmDeformationScreen.h"
#include "ffcc/graphic.h"
#include "ffcc/mapmesh.h"
#include "ffcc/p_game.h"
#include "ffcc/partMng.h"
#include "ffcc/pppYmEnv.h"
#include "ffcc/util.h"

#include <dolphin/gx.h>
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

struct pppCVECTOR {
	unsigned int m_rgba;
};

struct _pppEnvStYmDeformationScreen {
	void* m_stagePtr;
	CMaterialSet* m_materialSetPtr;
	CMapMesh** m_mapMeshPtr;
};

extern int DAT_8032ed70;
extern char DAT_8032ed78;
extern void* DAT_80238030;
extern CUtil DAT_8032ec70;
extern float ppvScreenMatrix[4][4];

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
int GetTexture__8CMapMeshFP12CMaterialSetRi(CMapMesh*, CMaterialSet*, int&);
void pppInitBlendMode__Fv(void);
void pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(
	pppCVECTOR*, pppFMATRIX*, float, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char,
	unsigned char, unsigned char);
void pppSetBlendMode__FUc(unsigned char);
void _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(int, int, int, int);
void _GXSetTevSwapModeTable__F13_GXTevSwapSel15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan(int, int, int, int, int);
void _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(int, int, int);
void _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg(int, int, int, int, int);
void _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(int, int, int, int, int, int);
void _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg(int, int, int, int, int);
void _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(int, int, int, int, int, int);
void _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(int, int, int, int);
void _GXSetTevOp__F13_GXTevStageID10_GXTevMode(int, int);
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
	YmDeformationScreenStep* step = (YmDeformationScreenStep*)param2;
	_pppEnvStYmDeformationScreen* env = (_pppEnvStYmDeformationScreen*)pppEnvStPtr;
	float* work = (float*)((char*)param1 + 0x80 + ((YmDeformationScreenData*)param3)->m_serializedDataOffsets[2]);
	int textureIndex = 0;
	GXTexObj backTexObj;
	Mtx identity;
	Mtx44 orthoMtx;
	Mtx rot;
	float indMtx[2][3];
	float depth;
	float texU;
	float texV;
	pppCVECTOR color;
	int textureBase;

	if (step->m_dataValIndex == 0xFFFF) {
		return;
	}

	textureBase = GetTexture__8CMapMeshFP12CMaterialSetRi(
		env->m_mapMeshPtr[step->m_dataValIndex], env->m_materialSetPtr, textureIndex);

	_GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1, 1, 5, 1);
	GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
	GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX1, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
	color.m_rgba = 0x40404040;
	pppSetBlendMode__FUc(0);
	pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(
		&color, (pppFMATRIX*)0, 0.0f, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0,
		(unsigned char)1, (unsigned char)1, (unsigned char)0);
	_GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0, 0, 0);
	GXSetNumTexGens(2);
	GXSetNumChans(1);
	_GXSetTevSwapModeTable__F13_GXTevSwapSel15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan(1, 0, 1, 2, 0);
	_GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0, 0, 1);
	_GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg(0, 0xF, 8, 9, 0xF);
	_GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(0, 0, 0, 0, 1, 0);
	_GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg(0, 7, 7, 7, 4);
	_GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(0, 0, 0, 0, 1, 0);
	_GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(1, 0, 1, 0xFF);
	_GXSetTevOp__F13_GXTevStageID10_GXTevMode(1, 0);

	DAT_8032ec70.BeginQuadEnv();
	DAT_8032ec70.SetVtxFmt_POS_CLR_TEX0_TEX1();
	GXSetNumTevStages(1);
	GXSetNumTexGens(2);
	GXSetNumChans(1);
	PSMTXIdentity(identity);
	GXLoadPosMtxImm(identity, 0);
	GXSetCurrentMtx(0);

	PSMTX44Identity(orthoMtx);
	orthoMtx[0][0] = 2.0f / 640.0f;
	orthoMtx[1][1] = -2.0f / 480.0f;
	orthoMtx[2][2] = 1.0f;
	orthoMtx[0][3] = -1.0f;
	orthoMtx[1][3] = 1.0f;
	GXSetProjection(orthoMtx, GX_ORTHOGRAPHIC);
	GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
	_GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0, 0, 0, 4);
	_GXSetTevOp__F13_GXTevStageID10_GXTevMode(0, 3);
	GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);

	depth = work[0];
	GXSetNumIndStages(1);
	GXSetIndTexOrder(GX_INDTEXSTAGE0, GX_TEXCOORD0, GX_TEXMAP1);
	GXSetTevIndWarp(GX_TEVSTAGE0, GX_INDTEXSTAGE0, GX_TRUE, GX_ITW_0, GX_ITM_1);
	GXSetIndTexCoordScale(GX_INDTEXSTAGE0, GX_ITS_1, GX_ITS_1);

	if ((*(short*)(work + 1) == 0) || (*(short*)(work + 1) == 0x168)) {
		*(short*)(work + 1) = 1;
	}

	PSMTXRotRad(rot, 'z', 0.017453292f * (float)(*(short*)(work + 1)));
	indMtx[0][0] = rot[0][0] * work[2];
	indMtx[0][1] = rot[0][1] * work[2];
	indMtx[0][2] = 0.0f;
	indMtx[1][0] = rot[1][0] * work[2];
	indMtx[1][1] = rot[1][1] * work[2];
	indMtx[1][2] = 0.0f;
	GXSetIndTexMtx(GX_ITM_1, indMtx, 1);

	texU = 640.0f / (float)*(unsigned int*)(textureBase + 100);
	texV = 448.0f / (float)*(unsigned int*)(textureBase + 0x68);

	Graphic.GetBackBufferRect2(DAT_80238030, &backTexObj, 0, 0, 640, 224, 0, GX_LINEAR, GX_TF_RGBA8, 0);
	GXLoadTexObj(&backTexObj, GX_TEXMAP0);
	GXLoadTexObj((GXTexObj*)(textureBase + 0x28), GX_TEXMAP1);
	GXBegin(GX_QUADS, GX_VTXFMT7, 4);
	GXPosition3f32(0.0f, 0.0f, depth);
	GXColor1u32(color.m_rgba);
	GXTexCoord2f32(0.0f, 0.0f);
	GXTexCoord2f32(0.0f, 0.0f);
	GXPosition3f32(640.0f, 0.0f, depth);
	GXColor1u32(color.m_rgba);
	GXTexCoord2f32(texU, 0.0f);
	GXTexCoord2f32(1.0f, 0.0f);
	GXPosition3f32(640.0f, 224.0f, depth);
	GXColor1u32(color.m_rgba);
	GXTexCoord2f32(texU, texV);
	GXTexCoord2f32(1.0f, 1.0f);
	GXPosition3f32(0.0f, 224.0f, depth);
	GXColor1u32(color.m_rgba);
	GXTexCoord2f32(0.0f, texV);
	GXTexCoord2f32(0.0f, 1.0f);

	Graphic.GetBackBufferRect2(DAT_80238030, &backTexObj, 0, 224, 640, 224, 0, GX_LINEAR, GX_TF_RGBA8, 0);
	GXLoadTexObj(&backTexObj, GX_TEXMAP0);
	depth = work[0];
	GXBegin(GX_QUADS, GX_VTXFMT7, 4);
	GXPosition3f32(0.0f, 224.0f, depth);
	GXColor1u32(color.m_rgba);
	GXTexCoord2f32(0.0f, 0.0f);
	GXTexCoord2f32(0.0f, 0.0f);
	GXPosition3f32(640.0f, 224.0f, depth);
	GXColor1u32(color.m_rgba);
	GXTexCoord2f32(texU, 0.0f);
	GXTexCoord2f32(1.0f, 0.0f);
	GXPosition3f32(640.0f, 448.0f, depth);
	GXColor1u32(color.m_rgba);
	GXTexCoord2f32(texU, texV);
	GXTexCoord2f32(1.0f, 1.0f);
	GXPosition3f32(0.0f, 448.0f, depth);
	GXColor1u32(color.m_rgba);
	GXTexCoord2f32(0.0f, texV);
	GXTexCoord2f32(0.0f, 1.0f);

	DAT_8032ec70.EndQuadEnv();
	DisableIndWarp(GX_TEVSTAGE1, GX_INDTEXSTAGE0);
	GXSetProjection(ppvScreenMatrix, GX_PERSPECTIVE);
	pppInitBlendMode__Fv();
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
