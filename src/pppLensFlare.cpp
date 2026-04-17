#include "ffcc/pppLensFlare.h"
#include "ffcc/partMng.h"
#include "ffcc/pppColum.h"
#include "ffcc/pppPart.h"
#include "ffcc/pppShape.h"
#include "ffcc/p_camera.h"
extern "C" {
extern const float kPppLensFlareZero;
extern const float kPppLensFlareAlphaScale;
extern const float kPppLensFlareCameraToObjectScale;
extern const float kPppLensFlareDepthToZScale;
extern int gPppCalcDisabled;
}

#include <dolphin/gx.h>
#include <dolphin/gx/GXCpu2Efb.h>
#include <dolphin/mtx.h>

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
	int shapeOffset = ctrlTable->m_serializedDataOffsets[2];
	int colorOffset = ctrlTable->m_serializedDataOffsets[1];
	u8* objBytes = (u8*)obj;
	u8* shapeBase = objBytes + shapeOffset + 0x80;
	u8* colorBase = objBytes + colorOffset + 0x80;
	s32 dataValIndex = unkB->m_dataValIndex;

	if (dataValIndex != 0xFFFF) {
		long** shapeTable = *(long***)(*(int*)&pppEnvStPtr->m_particleColors[0] + dataValIndex * 4);
		if (shapeBase[0x32] != 0) {
			pppCVECTOR local_70;
			Vec local_60;
			Mtx local_54;
			float scale;

			PSMTXIdentity(local_54);
			scale = *(float*)&unkB->m_stepValue;
			local_54[0][0] = (pppMngStPtr->m_scale.x * *(float*)(objBytes + 0x40)) * scale;
			local_54[1][1] = (pppMngStPtr->m_scale.y * *(float*)(objBytes + 0x54)) * scale;
			local_54[2][2] = (pppMngStPtr->m_scale.z * *(float*)(objBytes + 0x68)) * scale;

			local_60.x = pppMngStPtr->m_matrix.value[0][3];
			local_60.y = pppMngStPtr->m_matrix.value[1][3];
			local_60.z = pppMngStPtr->m_matrix.value[2][3];

			PSMTXMultVec(ppvCameraMatrix02, &local_60, &local_60);

			local_54[0][3] = local_60.x;
			local_54[1][3] = local_60.y;
			local_54[2][3] = local_60.z;

			pppCopyVector(*(Vec*)(shapeBase + 0x20), local_60);

			GXLoadPosMtxImm(local_54, 0);

			local_70.rgba[0] = colorBase[8];
			local_70.rgba[1] = colorBase[9];
			local_70.rgba[2] = colorBase[10];
			local_70.rgba[3] = shapeBase[0x32];

			pppSetDrawEnv(&local_70, (pppFMATRIX*)0, kPppLensFlareZero, unkB->m_payload[0], unkB->m_unk13, unkB->m_unk12, 0,
						  1, 1, 0);

			pppSetBlendMode(unkB->m_unk12);
			pppDrawShp(*shapeTable, *(s16*)(shapeBase + 0x2e), pppEnvStPtr->m_materialSetPtr, unkB->m_unk12);
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
void pppFrameLensFlare(pppColum* obj, pppColumUnkB* unkB, _pppCtrlTable* ctrlTable)
{
	if (gPppCalcDisabled == 0) {
		int shapeOffset = ctrlTable->m_serializedDataOffsets[2];
		int colorOffset = ctrlTable->m_serializedDataOffsets[1];
		u8* objBytes = (u8*)obj;
		u8* colorBase = objBytes + colorOffset;
		LensFlareWork* work = (LensFlareWork*)(objBytes + shapeOffset + 0x80);
		u8 sourceAlpha = colorBase[0x8B];
		float projX = pppMngStPtr->m_matrix.value[0][3];
		float projY = pppMngStPtr->m_matrix.value[1][3];
		float projZ = pppMngStPtr->m_matrix.value[2][3];
		u32 zAtPixel;
		Vec cameraPos;
		Vec cameraLookAt;
		Vec lookDir;
		Vec objectPos;
		Vec cameraToObject;
		Mtx cameraMtx;
		float projection[7];
		float viewport[6];
		int projectedYInt;
		int projectedXInt;
		float alphaScale;

		alphaScale = (float)sourceAlpha * kPppLensFlareAlphaScale;

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

		projectedYInt = (int)work->m_projectedY;
		projectedXInt = (int)work->m_projectedX;
		zAtPixel = 0;
		u8 flareWidth = unkB->m_arg3;
		u32 halfWidth = (u32)(flareWidth >> 1);
		u32 z0 = __cvt_fp2unsigned((double)(kPppLensFlareDepthToZScale * work->m_projectedZ));
		u32 x0 = (u32)(projectedXInt & 0xFFFF);
		u32 y0 = (u32)(projectedYInt & 0xFFFF);
		s16 stepSize = (s16)((u16)flareWidth / (u16)unkB->m_count);

		for (u32 y = y0 - halfWidth; (int)y <= (int)(y0 + halfWidth); y += stepSize) {
			for (u32 x = x0 - halfWidth; (int)x <= (int)(x0 + halfWidth); x += stepSize) {
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

		int sampleCount = (int)unkB->m_count + 1;
		sampleCount *= sampleCount;
		if ((u8)work->m_alpha == sampleCount) {
			work->m_alpha = 0xff;
		} else {
			u8 alpha = (u8)work->m_alpha;
			int scaledAlpha = alpha * (0xFF / sampleCount);

			work->m_alpha = (u8)scaledAlpha;
			if (0xFF < (int)(u8)scaledAlpha) {
				work->m_alpha = 0xff;
			} else {
				work->m_alpha = (u8)scaledAlpha;
			}
		}

		work->m_alpha = (u8)(int)((float)(u8)work->m_alpha * alphaScale);
		if (unkB->m_dataValIndex != 0xffff) {
			long** shapeTable = *(long***)(*(int*)&pppEnvStPtr->m_particleColors[0] + unkB->m_dataValIndex * 4);
			pppCalcFrameShape(*shapeTable, work->m_shapeFrame0, work->m_shapeFrame1, work->m_shapeFrame2,
							  unkB->m_initWOrk);
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
