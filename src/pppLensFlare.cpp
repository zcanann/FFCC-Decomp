#include "ffcc/pppLensFlare.h"
#include "ffcc/partMng.h"
#include "ffcc/pppColum.h"
#include "ffcc/pppPart.h"
#include "ffcc/pppShape.h"
#include "ffcc/p_camera.h"
#include "ffcc/symbols_shared.h"

#include <dolphin/gx.h>
#include <dolphin/gx/GXCpu2Efb.h>
#include <dolphin/mtx.h>

struct LensFlareStep {
    s32 m_graphId;
    s32 m_dataValIndex;
    s16 m_initWOrk;
    s16 _pad0A;
    f32 m_stepValue;
    u32 m_arg3;
    u8 m_payload[0x19];
};

struct LensFlareWork {
    u8 _pad00[0x10];
    f32 m_projectedX;
    f32 m_projectedY;
    f32 m_projectedZ;
    f32 _pad1C;
    Vec m_viewPosition;
    s16 m_shapeFrame0;
    s16 m_shapeFrame1;
    s16 m_shapeFrame2;
    u8 m_alpha;
    u8 _pad33;
    f32 m_dot;
};

extern "C" unsigned int __cvt_fp2unsigned(double);
extern "C" void pppCopyVector__FR3Vec3Vec(Vec*, const Vec*);
extern "C" void pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(
    pppCVECTOR*, pppFMATRIX*, float, u8, u8, u8, u8, u8, u8, u8);

/*
 * --INFO--
 * PAL Address: 0x800dec14
 * PAL Size: 72b
 */
void pppConstructLensFlare(pppColum* obj, _pppCtrlTable* ctrlTable)
{
	char* work = (char*)obj + ctrlTable->m_serializedDataOffsets[2] + 0x80;

	float initValue = kPppLensFlareZero;

	*((float*)(work + 0x18)) = initValue;
	*((float*)(work + 0x14)) = initValue;
	*((float*)(work + 0x10)) = initValue;
	*((float*)(work + 0x28)) = initValue;
	*((float*)(work + 0x24)) = initValue;
	*((float*)(work + 0x20)) = initValue;

	*((short*)(work + 0x30)) = 0;
	*((short*)(work + 0x2e)) = 0;
	*((short*)(work + 0x2c)) = 0;
	*(work + 0x32) = 0;
	*((float*)(work + 0x34)) = initValue;
}

/*
 * --INFO--
 * PAL Address: 0x800dec10
 * PAL Size: 4b
 */
void pppDestructLensFlare(pppColum*, _pppCtrlTable*)
{
	return;
}

/*
 * --INFO--
 * PAL Address: 0x800de8c4
 * PAL Size: 844b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppFrameLensFlare(pppColum* obj, pppColumUnkB* unkB, _pppCtrlTable* ctrlTable)
{
	if (gPppCalcDisabled == 0) {
		LensFlareStep* step = (LensFlareStep*)unkB;
		int shapeOffset = ctrlTable->m_serializedDataOffsets[2];
		int colorOffset = ctrlTable->m_serializedDataOffsets[1];
		u8* objBytes = (u8*)obj;
		LensFlareWork* work = (LensFlareWork*)(objBytes + shapeOffset + 0x80);
		u8 sourceAlpha = objBytes[colorOffset + 0x8B];
		double projX = (double)pppMngStPtr->m_matrix.value[0][3];
		double projY = (double)pppMngStPtr->m_matrix.value[1][3];
		double projZ = (double)pppMngStPtr->m_matrix.value[2][3];
		double alphaScale = (double)((float)sourceAlpha * kPppLensFlareAlphaScale);
		u32 zAtPixel;
		float viewport[6];
		float projection[7];
		Mtx cameraMtx;
		Vec cameraPos;
		Vec cameraLookAt;
		Vec lookDir;
		Vec objectPos;
		Vec cameraToObject;
		u8* stepArgBytes = (u8*)&step->m_arg3;

		GXGetViewportv(viewport);
		GXGetProjectionv(projection);
		PSMTXCopy(CameraPcs.m_cameraMatrix, cameraMtx);
		GXProject(projX, projY, projZ, cameraMtx, projection, viewport,
				  &work->m_projectedX, &work->m_projectedY, &work->m_projectedZ);

		work->m_alpha = 0;
		cameraPos.x = CameraPcs._224_4_;
		cameraPos.y = CameraPcs._228_4_;
		cameraPos.z = CameraPcs._232_4_;
		cameraLookAt.x = CameraPcs._212_4_;
		cameraLookAt.y = CameraPcs._216_4_;
		cameraLookAt.z = CameraPcs._220_4_;
		PSVECSubtract(&cameraLookAt, &cameraPos, &lookDir);

		objectPos.x = pppMngStPtr->m_matrix.value[0][3];
		objectPos.y = pppMngStPtr->m_matrix.value[1][3];
		objectPos.z = pppMngStPtr->m_matrix.value[2][3];
		PSVECSubtract(&cameraPos, &objectPos, &cameraToObject);
		PSVECScale(&cameraToObject, &cameraToObject, kPppLensFlareCameraToObjectScale);
		PSVECNormalize(&lookDir, &lookDir);
		PSVECNormalize(&cameraToObject, &cameraToObject);
		work->m_dot = PSVECDotProduct(&cameraToObject, &lookDir);

		float xProjected = work->m_projectedX;
		float yProjected = work->m_projectedY;
		u8 argA = stepArgBytes[0];
		u32 halfWidth = (u32)(argA >> 1);
		u32 y0 = (u32)((int)yProjected & 0xFFFF);
		u32 x0 = (u32)((int)xProjected & 0xFFFF);
		u32 z0 = __cvt_fp2unsigned((double)(kPppLensFlareDepthToZScale * work->m_projectedZ));
		int stepSize = (short)((u16)argA / (u16)stepArgBytes[1]);
		for (u32 y = y0 - halfWidth; (int)y <= (int)(y0 + halfWidth); y += stepSize) {
			for (u32 x = x0 - halfWidth; (int)x <= (int)(x0 + halfWidth); x += stepSize) {
				if (((-1 < (short)x) && (-1 < (short)y)) && ((short)x < 0x281) && ((short)y < 0x1c1)) {
					GXPeekZ((u16)(x & 0xFFFF), (u16)(y & 0xFFFF), &zAtPixel);
					if (z0 <= zAtPixel) {
						work->m_alpha = (u8)(work->m_alpha + 1);
					}
				}
			}
		}

		stepSize = stepArgBytes[1] + 1;
		u32 sampleCount = (u32)(stepSize * stepSize);
		if (work->m_alpha == sampleCount) {
			work->m_alpha = 0xff;
		} else {
			sampleCount = work->m_alpha * (0xff / sampleCount);
			work->m_alpha = (u8)sampleCount;
			if ((sampleCount & 0xff) < 0x100) {
				work->m_alpha = (u8)sampleCount;
			} else {
				work->m_alpha = 0xff;
			}
		}

		work->m_alpha = (u8)(int)((double)(float)work->m_alpha * alphaScale);
		if (step->m_dataValIndex != 0xffff) {
			long** shapeTable = *(long***)(*(int*)&pppEnvStPtr->m_particleColors[0] + step->m_dataValIndex * 4);
			pppCalcFrameShape(*shapeTable, work->m_shapeFrame0, work->m_shapeFrame1, work->m_shapeFrame2,
							  step->m_initWOrk);
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x800de718
 * PAL Size: 428b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRenderLensFlare(pppColum* obj, pppColumUnkB* unkB, _pppCtrlTable* ctrlTable)
{
	LensFlareStep* step;
	int shapeOffset;
	int colorOffset;
	long** shapeTable;
	s32 dataValIndex;
	u8* objBytes;
	LensFlareWork* work;
	pppCVECTOR* color;
	u8* stepArgBytes;

	step = (LensFlareStep*)unkB;
	shapeOffset = ctrlTable->m_serializedDataOffsets[2];
	colorOffset = ctrlTable->m_serializedDataOffsets[1];
	objBytes = (u8*)obj;
	work = (LensFlareWork*)(objBytes + shapeOffset + 0x80);
	color = (pppCVECTOR*)(objBytes + colorOffset + 0x80);
	stepArgBytes = (u8*)&step->m_arg3;
	dataValIndex = step->m_dataValIndex;

	if ((dataValIndex != 0xFFFF) &&
		(shapeTable = *(long***)(*(int*)&pppEnvStPtr->m_particleColors[0] + dataValIndex * 4),
		 work->m_alpha != 0)) {
		pppCVECTOR local_70;
		Vec local_60;
		Mtx local_54;

		PSMTXIdentity(local_54);
		stepValue = step->m_stepValue;
		local_54[0][0] = stepValue * pppMngStPtr->m_scale.x * *(float*)(objBytes + 0x40);
		local_54[1][1] = stepValue * pppMngStPtr->m_scale.y * *(float*)(objBytes + 0x54);
		local_54[2][2] = stepValue * pppMngStPtr->m_scale.z * *(float*)(objBytes + 0x68);

		local_60.x = pppMngStPtr->m_matrix.value[0][3];
		local_60.y = pppMngStPtr->m_matrix.value[1][3];
		local_60.z = pppMngStPtr->m_matrix.value[2][3];

		PSMTXMultVec(ppvCameraMatrix02, &local_60, &local_60);

		local_54[0][3] = local_60.x;
		local_54[1][3] = local_60.y;
		local_54[2][3] = local_60.z;
		pppCopyVector__FR3Vec3Vec(&work->m_viewPosition, &local_60);

		GXLoadPosMtxImm(local_54, 0);

		local_70.rgba[0] = color->rgba[0];
		local_70.rgba[1] = color->rgba[1];
		local_70.rgba[2] = color->rgba[2];
		local_70.rgba[3] = work->m_alpha;

		pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(
			&local_70, (pppFMATRIX*)0, kPppLensFlareZero, step->m_payload[0], stepArgBytes[3], stepArgBytes[2], 0, 1, 1,
			0);

		pppSetBlendMode(stepArgBytes[2]);
		pppDrawShp(*shapeTable, work->m_shapeFrame1, pppEnvStPtr->m_materialSetPtr, stepArgBytes[2]);
		pppSetBlendMode(3);
	}
}
