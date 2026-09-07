#include "global.h"
#include "ffcc/pppLensFlare.h"
#include "ffcc/partMng.h"
#include "ffcc/pppColum.h"
#include "ffcc/pppPart.h"
#include "ffcc/pppShape.h"
#include "ffcc/p_camera.h"

#include <dolphin/gx.h>
#include <dolphin/gx/GXCpu2Efb.h>
#include <dolphin/mtx.h>
#include "PowerPC_EABI_Support/Runtime/runtime.h"

STATIC_ASSERT(offsetof(LensFlareWork, m_projectedX) == 0x10);
STATIC_ASSERT(offsetof(LensFlareWork, m_viewPosition) == 0x20);
STATIC_ASSERT(offsetof(LensFlareWork, m_shapeFrame1) == 0x2E);
STATIC_ASSERT(offsetof(LensFlareWork, m_alpha) == 0x32);
STATIC_ASSERT(offsetof(LensFlareWork, m_dot) == 0x34);
STATIC_ASSERT(sizeof(LensFlareDataOffsets) == 0xC);
STATIC_ASSERT(offsetof(LensFlareDataOffsets, m_colorWorkOffset) == 0x4);
STATIC_ASSERT(offsetof(LensFlareDataOffsets, m_workOffset) == 0x8);

static inline LensFlareDataOffsets* GetLensFlareDataOffsets(_pppCtrlTable* ctrlTable)
{
	return reinterpret_cast<LensFlareDataOffsets*>(ctrlTable->m_serializedDataOffsets);
}

static inline LensFlareWork* GetLensFlareWork(pppColum* obj, _pppCtrlTable* ctrlTable)
{
	return reinterpret_cast<LensFlareWork*>(obj->m_workArea + GetLensFlareDataOffsets(ctrlTable)->m_workOffset);
}

static inline _pppColorWork* GetLensFlareColorWork(pppColum* obj, _pppCtrlTable* ctrlTable)
{
	return reinterpret_cast<_pppColorWork*>(obj->m_workArea + GetLensFlareDataOffsets(ctrlTable)->m_colorWorkOffset);
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
void pppRenderLensFlare(pppColum* obj, pppColumStep* unkB, _pppCtrlTable* ctrlTable)
{
	LensFlareWork* work = GetLensFlareWork(obj, ctrlTable);
	_pppColorWork* colorWork = GetLensFlareColorWork(obj, ctrlTable);
	s32 dataValIndex = unkB->m_dataValIndex;

	if (dataValIndex != 0xFFFF) {
		pppShapeSt* shape = ppvEnv->m_shapeTablePtr[dataValIndex];
		if (work->m_alpha != 0) {
			pppCVECTOR local_70;
			Vec local_60;
			Mtx local_54;
			float scale;

			PSMTXIdentity(local_54);
			scale = *(float*)&unkB->m_stepValue;
			local_54[0][0] = (ppvMng->m_scale.x * obj->m_drawMatrix.value[0][0]) * scale;
			local_54[1][1] = (ppvMng->m_scale.y * obj->m_drawMatrix.value[1][1]) * scale;
			local_54[2][2] = (ppvMng->m_scale.z * obj->m_drawMatrix.value[2][2]) * scale;

			local_60.x = ppvMng->m_matrix.value[0][3];
			local_60.y = ppvMng->m_matrix.value[1][3];
			local_60.z = ppvMng->m_matrix.value[2][3];

			PSMTXMultVec(ppvCameraMatrix, &local_60, &local_60);

			local_54[0][3] = local_60.x;
			local_54[1][3] = local_60.y;
			local_54[2][3] = local_60.z;

			pppCopyVector(work->m_viewPosition, local_60);

			GXLoadPosMtxImm(local_54, 0);

			local_70.rgba[0] = colorWork->result.r;
			local_70.rgba[1] = colorWork->result.g;
			local_70.rgba[2] = colorWork->result.b;
			local_70.rgba[3] = work->m_alpha;

			pppSetDrawEnv(
				&local_70, (pppFMATRIX*)0, 0.0f, unkB->m_lensFlare.m_drawEnvLightTarget, unkB->m_unk13,
				unkB->m_unk12, 0, 1, 1, 0);

			pppSetBlendMode(unkB->m_unk12);
			pppDrawShp(static_cast<long*>(shape->m_animData), work->m_shapeFrame1,
			           ppvEnv->m_materialSetPtr, unkB->m_unk12);
			pppSetBlendMode(3);
		}
	}
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
void pppFrameLensFlare(pppColum* obj, pppColumStep* unkB, _pppCtrlTable* ctrlTable)
{
	if (ppvUserStopPartF == 0) {
		LensFlareWork* work = GetLensFlareWork(obj, ctrlTable);
		_pppColorWork* colorWork = GetLensFlareColorWork(obj, ctrlTable);
		u8 sourceAlpha = colorWork->result.a;
		float projX = ppvMng->m_matrix.value[0][3];
		float projY = ppvMng->m_matrix.value[1][3];
		float projZ = ppvMng->m_matrix.value[2][3];
		u32 zAtPixel;
		Vec cameraPos;
		Vec cameraLookAt;
		Vec lookDir;
		Vec objectPos;
		Vec cameraToObject;
		Mtx cameraMtx;
		float projection[7];
		float viewport[6];
		u8 flareWidth;
		int halfWidth;
		u32 z0;
		int projectedXInt;
		int projectedYInt;
		int x;
		int y;
		int x0;
		int y0;
		s16 stepSize;
		float alphaScale;

		alphaScale = (float)sourceAlpha / 128.0f;
		GXGetViewportv(viewport);
		GXGetProjectionv(projection);
		PSMTXCopy(CameraPcs.m_cameraMatrix, cameraMtx);
		GXProject(projX, projY, projZ, cameraMtx, projection, viewport,
				  &work->m_projectedX, &work->m_projectedY, &work->m_projectedZ);

		work->m_alpha = 0;
		cameraPos.x = CameraPcs.m_positionX;
		cameraPos.y = CameraPcs.m_positionY;
		cameraPos.z = CameraPcs.m_positionZ;
		cameraLookAt.x = CameraPcs.m_targetX;
		cameraLookAt.y = CameraPcs.m_targetY;
		cameraLookAt.z = CameraPcs.m_targetZ;
		PSVECSubtract(&cameraLookAt, &cameraPos, &lookDir);

		objectPos.x = ppvMng->m_matrix.value[0][3];
		objectPos.y = ppvMng->m_matrix.value[1][3];
		objectPos.z = ppvMng->m_matrix.value[2][3];
		PSVECSubtract(&cameraPos, &objectPos, &cameraToObject);
		PSVECScale(&cameraToObject, &cameraToObject, -1.0f);
		PSVECNormalize(&lookDir, &lookDir);
		PSVECNormalize(&cameraToObject, &cameraToObject);
		work->m_dot = PSVECDotProduct(&cameraToObject, &lookDir);

		projectedXInt = (int)work->m_projectedX;
		projectedYInt = (int)work->m_projectedY;
		zAtPixel = 0;
		flareWidth = unkB->m_arg3;
		halfWidth = flareWidth >> 1;
		z0 = __cvt_fp2unsigned((double)(16777215.0f * work->m_projectedZ));
		y0 = (u16)projectedYInt;
		x0 = (u16)projectedXInt;
		stepSize = (s16)((u16)flareWidth / (u16)unkB->m_count);

		for (y = y0 - halfWidth; y <= (y0 + halfWidth); y += stepSize) {
			for (x = x0 - halfWidth; x <= (x0 + halfWidth); x += stepSize) {
				s16 xShort = (s16)x;
				s16 yShort = (s16)y;

				if ((xShort >= 0) && (yShort >= 0) && (xShort <= 0x280) && (yShort <= 0x1C0)) {
					GXPeekZ((u16)xShort, (u16)yShort, &zAtPixel);
					if (z0 <= zAtPixel) {
						work->m_alpha = (u8)(work->m_alpha + 1);
					}
				}
			}
		}

		int sampleCount = unkB->m_count + 1;
		sampleCount *= sampleCount;
		if (work->m_alpha == sampleCount) {
			work->m_alpha = 0xff;
		} else {
			int scaledAlpha = work->m_alpha * (0xFF / sampleCount);
			int scaledAlphaByte = (u8)scaledAlpha;

			work->m_alpha = scaledAlphaByte;
			if (0xFF < scaledAlphaByte) {
				work->m_alpha = 0xff;
			} else {
				work->m_alpha = scaledAlphaByte;
			}
		}

		work->m_alpha = (u8)(int)((float)(u8)work->m_alpha * alphaScale);
		if (unkB->m_dataValIndex != 0xffff) {
			pppShapeSt* shape = ppvEnv->m_shapeTablePtr[unkB->m_dataValIndex];
			pppCalcFrameShape(static_cast<long*>(shape->m_animData), work->m_shapeFrame0, work->m_shapeFrame1,
			                  work->m_shapeFrame2, unkB->m_initWOrk);
		}
	}
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
 * PAL Address: 0x800dec14
 * PAL Size: 72b
 */
void pppConstructLensFlare(pppColum* obj, _pppCtrlTable* ctrlTable)
{
	LensFlareWork* work = GetLensFlareWork(obj, ctrlTable);

	float initValue = 0.0f;

	work->m_projectedZ = initValue;
	work->m_projectedY = initValue;
	work->m_projectedX = initValue;
	work->m_viewPosition.z = initValue;
	work->m_viewPosition.y = initValue;
	work->m_viewPosition.x = initValue;

	work->m_shapeFrame2 = 0;
	work->m_shapeFrame1 = 0;
	work->m_shapeFrame0 = 0;
	work->m_alpha = 0;
	work->m_dot = initValue;
}
