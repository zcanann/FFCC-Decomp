#include "ffcc/pppYmDeformationScreen.h"
#include "ffcc/graphic.h"
#include "ffcc/render_buffers.h"
#include "ffcc/mapmesh.h"
#include "ffcc/p_camera.h"
#include "ffcc/p_game.h"
#include "ffcc/partMng.h"
#include "ffcc/pppYmEnv.h"
#include "ffcc/util.h"
#include "ffcc/math.h"

#include <dolphin/gx.h>
#include <dolphin/mtx.h>
#include "ffcc/ppp_linkage.h"

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
	char pad[0xc];
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
	unsigned char m_rgba[4];
};

struct _pppEnvStYmDeformationScreen {
	void* m_stagePtr;
	CMaterialSet* m_materialSetPtr;
	CMapMesh** m_mapMeshPtr;
};

extern float FLOAT_80330670;
extern float FLOAT_80330674;
extern float FLOAT_80330678;
extern float FLOAT_8033067C;
extern float FLOAT_80330680;
extern float FLOAT_80330684;
extern float FLOAT_80330688;
extern float FLOAT_8033068C;
extern float FLOAT_80330690;

static inline Mtx44& CameraScreenMatrix()
{
    return *reinterpret_cast<Mtx44*>(reinterpret_cast<u8*>(&CameraPcs) + 0x94);
}

static inline float CameraLookAtX()
{
    return *reinterpret_cast<float*>(reinterpret_cast<u8*>(&CameraPcs) + 0xD4);
}

static inline float CameraLookAtY()
{
    return *reinterpret_cast<float*>(reinterpret_cast<u8*>(&CameraPcs) + 0xD8);
}

static inline float CameraLookAtZ()
{
    return *reinterpret_cast<float*>(reinterpret_cast<u8*>(&CameraPcs) + 0xDC);
}

void pppInitBlendMode(void);
void pppSetBlendMode(unsigned char);
void pppSetFpMatrix(_pppMngSt*);

extern "C" {
void CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf(
    void*, int, float*, float*, float*, float, float*, float*);
void MTX44MultVec4__5CMathFPA4_fP5Vec4dP5Vec4d(void*, Mtx44, Vec4d*, Vec4d*);

int GetTexture__8CMapMeshFP12CMaterialSetRi(CMapMesh*, CMaterialSet*, int&);

void pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(
	pppCVECTOR*, pppFMATRIX*, float, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char,
	unsigned char, unsigned char);

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
	float zero = FLOAT_80330670;
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
void pppDestructYmDeformationScreen(pppYmDeformationScreen*, void*)
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
	Vec4d outVec;
	Vec4d inVec;
	Mtx44 screenMtx;
	float* work;
	u8* workBytes;
	int* serializedDataOffsets;
	float cameraX;
	float cameraY;
	float cameraZ;
	YmDeformationScreenStep* step;

	if (gPppCalcDisabled == 0) {
		step = (YmDeformationScreenStep*)param2;
		serializedDataOffsets = ((YmDeformationScreenData*)param3)->m_serializedDataOffsets;
		work = (float*)((char*)param1 + 0x80 + serializedDataOffsets[2]);
		workBytes = (u8*)work;

		CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf(
			param1, step->m_graphId, work + 2, work + 3, work + 4, step->m_initWOrk, &step->m_stepValue, &step->m_arg3);
		CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf(
			param1, step->m_graphId, work + 5, work + 6, work + 7, step->m_payload0, &step->m_payload1, &step->m_payload2);

		if (gPppInConstructor == 0) {
			if (workBytes[6] != 0) {
				*(s16*)(workBytes + 4) += (int)work[5];
				if (*(s16*)(workBytes + 4) > step->m_payload3) {
					workBytes[6] = 0;
				}
			} else {
				*(s16*)(workBytes + 4) -= (int)work[5];
				if (*(s16*)(workBytes + 4) < -step->m_payload3) {
					workBytes[6] = 1;
				}
			}

			if (*(s32*)((u8*)param1 + 0xC) == 0) {
				PSMTX44Copy(CameraScreenMatrix(), screenMtx);
				inVec.x = FLOAT_80330670;
				inVec.y = FLOAT_80330670;
				inVec.z = -*(float*)&step->m_payloadBytes[2];
				inVec.w = FLOAT_8033067C;
				MTX44MultVec4__5CMathFPA4_fP5Vec4dP5Vec4d(&Math, screenMtx, &inVec, &outVec);
				{
					float outW = outVec.w;
					if (outW != FLOAT_80330670) {
						outVec.z /= outW;
					}
				}
				work[0] = outVec.z;
			}

			if ((s32)Game.m_currentSceneId == 7) {
				cameraX = ppvCameraMatrix02[0][3];
				cameraY = ppvCameraMatrix02[1][3];
				cameraZ = ppvCameraMatrix02[2][3];
			} else {
				cameraX = CameraLookAtX();
				cameraY = CameraLookAtY();
				cameraZ = CameraLookAtZ();
			}
			pppMngStPtr->m_matrix.value[0][3] = cameraX;
			pppMngStPtr->m_matrix.value[1][3] = cameraY;
			pppMngStPtr->m_matrix.value[2][3] = cameraZ;
			pppSetFpMatrix(pppMngStPtr);
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x800981a8
 * PAL Size: 1716b
 */
void pppRenderYmDeformationScreen(pppYmDeformationScreen* param1, void* param2, void* param3)
{
	YmDeformationScreenStep* step = (YmDeformationScreenStep*)param2;
	float* work = (float*)((char*)param1 + 0x80 + ((YmDeformationScreenData*)param3)->m_serializedDataOffsets[2]);
	int textureIndex = 0;
	GXTexObj backTexObj;
	Mtx44 savedProjection;
	Mtx44 orthoMtx;
	Mtx identity;
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
		((CMapMesh**)pppEnvStPtr->m_mapMeshPtr)[step->m_dataValIndex], pppEnvStPtr->m_materialSetPtr, textureIndex);

	_GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1, 1, 5, 1);
	GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
	GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX1, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
	color.m_rgba[0] = 0x40;
	color.m_rgba[1] = 0x40;
	color.m_rgba[2] = 0x40;
	color.m_rgba[3] = 0x40;
	pppSetBlendMode(0);
	pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(
		&color, (pppFMATRIX*)0, FLOAT_80330670, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0,
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

	gUtil.BeginQuadEnv();
	gUtil.SetVtxFmt_POS_CLR_TEX0_TEX1();
	GXSetNumTevStages(1);
	GXSetNumTexGens(2);
	GXSetNumChans(1);
	PSMTX44Copy(ppvScreenMatrix, savedProjection);
	PSMTXIdentity(identity);
	GXLoadPosMtxImm(identity, 0);
	GXSetCurrentMtx(0);

	PSMTX44Identity(orthoMtx);
	orthoMtx[0][0] = FLOAT_80330674;
	orthoMtx[1][1] = FLOAT_80330678;
	orthoMtx[2][2] = FLOAT_8033067C;
	orthoMtx[0][3] = FLOAT_80330680;
	orthoMtx[1][3] = FLOAT_8033067C;
	orthoMtx[2][3] = FLOAT_80330670;
	GXSetProjection(orthoMtx, GX_ORTHOGRAPHIC);
	GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
	_GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0, 0, 0, 4);
	_GXSetTevOp__F13_GXTevStageID10_GXTevMode(0, 3);
	GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);

	depth = work[0];
	GXSetNumIndStages(1);
	GXSetIndTexOrder(GX_INDTEXSTAGE0, GX_TEXCOORD0, GX_TEXMAP1);
	GXSetTevIndWarp(GX_TEVSTAGE0, GX_INDTEXSTAGE0, GX_TRUE, GX_FALSE, GX_ITM_0);
	GXSetIndTexCoordScale(GX_INDTEXSTAGE0, GX_ITS_1, GX_ITS_1);

	if ((*(short*)(work + 1) == 0) || (*(short*)(work + 1) == 0x168)) {
		*(short*)(work + 1) = 1;
	}

	PSMTXRotRad(rot, 'z', FLOAT_80330684 * (float)(*(short*)(work + 1)));
	indMtx[0][0] = rot[0][0] * work[2];
	indMtx[0][1] = rot[0][1] * work[2];
	indMtx[0][2] = 0.0f;
	indMtx[1][0] = rot[1][0] * work[2];
	indMtx[1][1] = rot[1][1] * work[2];
	indMtx[1][2] = 0.0f;
	GXSetIndTexMtx(GX_ITM_0, indMtx, 1);

	texU = (float)(0x280 / *(unsigned int*)(textureBase + 100));
	texV = (float)(0x1C0 / *(unsigned int*)(textureBase + 0x68));

	Graphic.GetBackBufferRect2(Graphic.m_scratchTextureBuffer, &backTexObj, 0, 0, 640, 224, 0, GX_LINEAR, GX_TF_RGBA8, 0);
	GXLoadTexObj(&backTexObj, GX_TEXMAP0);
	GXLoadTexObj((GXTexObj*)(textureBase + 0x28), GX_TEXMAP1);
	GXBegin(GX_QUADS, GX_VTXFMT7, 4);
	GXPosition3f32(FLOAT_80330670, FLOAT_80330670, depth);
	GXColor1u32(*(u32*)color.m_rgba);
	GXTexCoord2f32(FLOAT_80330670, FLOAT_80330670);
	GXTexCoord2f32(FLOAT_80330670, FLOAT_80330670);
	GXPosition3f32(FLOAT_80330688, FLOAT_80330670, depth);
	GXColor1u32(*(u32*)color.m_rgba);
	GXTexCoord2f32(texU, FLOAT_80330670);
	GXTexCoord2f32(FLOAT_8033067C, FLOAT_80330670);
	GXPosition3f32(FLOAT_80330688, FLOAT_8033068C, depth);
	GXColor1u32(*(u32*)color.m_rgba);
	GXTexCoord2f32(texU, texV);
	GXTexCoord2f32(FLOAT_8033067C, FLOAT_8033067C);
	GXPosition3f32(FLOAT_80330670, FLOAT_8033068C, depth);
	GXColor1u32(*(u32*)color.m_rgba);
	GXTexCoord2f32(FLOAT_80330670, texV);
	GXTexCoord2f32(FLOAT_80330670, FLOAT_8033067C);

	Graphic.GetBackBufferRect2(Graphic.m_scratchTextureBuffer, &backTexObj, 0, 224, 640, 224, 0, GX_LINEAR, GX_TF_RGBA8, 0);
	GXLoadTexObj(&backTexObj, GX_TEXMAP0);
	depth = work[0];
	GXBegin(GX_QUADS, GX_VTXFMT7, 4);
	GXPosition3f32(FLOAT_80330670, FLOAT_8033068C, depth);
	GXColor1u32(*(u32*)color.m_rgba);
	GXTexCoord2f32(FLOAT_80330670, FLOAT_80330670);
	GXTexCoord2f32(FLOAT_80330670, FLOAT_80330670);
	GXPosition3f32(FLOAT_80330688, FLOAT_8033068C, depth);
	GXColor1u32(*(u32*)color.m_rgba);
	GXTexCoord2f32(texU, FLOAT_80330670);
	GXTexCoord2f32(FLOAT_8033067C, FLOAT_80330670);
	GXPosition3f32(FLOAT_80330688, FLOAT_80330690, depth);
	GXColor1u32(*(u32*)color.m_rgba);
	GXTexCoord2f32(texU, texV);
	GXTexCoord2f32(FLOAT_8033067C, FLOAT_8033067C);
	GXPosition3f32(FLOAT_80330670, FLOAT_80330690, depth);
	GXColor1u32(*(u32*)color.m_rgba);
	GXTexCoord2f32(FLOAT_80330670, texV);
	GXTexCoord2f32(FLOAT_80330670, FLOAT_8033067C);

	gUtil.EndQuadEnv();
	DisableIndWarp(GX_TEVSTAGE1, GX_INDTEXSTAGE0);
	GXSetProjection(savedProjection, GX_PERSPECTIVE);
	pppInitBlendMode();
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
