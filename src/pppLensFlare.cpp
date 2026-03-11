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

static inline float CameraWorldX()
{
    return CameraPcs._224_4_;
}

static inline float CameraWorldY()
{
    return CameraPcs._228_4_;
}

static inline float CameraWorldZ()
{
    return CameraPcs._232_4_;
}

static inline Mtx& CameraMatrix()
{
    return *reinterpret_cast<Mtx*>(reinterpret_cast<u8*>(&CameraPcs) + 0x4);
}

extern "C" unsigned int __cvt_fp2unsigned(double);
extern "C" void pppCopyVector__FR3Vec3Vec(Vec*, const Vec*);

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
		int shapeOffset = ctrlTable->m_serializedDataOffsets[2];
		int colorOffset = ctrlTable->m_serializedDataOffsets[1];
		u8* objBytes = (u8*)obj;
		u8* shapeBase = objBytes + shapeOffset + 0x80;
		u8* alphaPtr = shapeBase + 0x32;
		u8 sourceAlpha = objBytes[colorOffset + 0x8B];
		double projX = (double)pppMngStPtr->m_matrix.value[0][3];
		double projY = (double)pppMngStPtr->m_matrix.value[1][3];
		double projZ = (double)pppMngStPtr->m_matrix.value[2][3];
		double alphaScale = (double)((float)sourceAlpha * kPppLensFlareAlphaScale);
		u32 zAtPixel = 0;
		float viewport[6];
		float projection[7];
		Mtx cameraMtx;
		Vec cameraPos;
		Vec cameraLookAt;
		Vec lookDir;
		Vec objectPos;
		Vec cameraToObject;

		GXGetViewportv(viewport);
		GXGetProjectionv(projection);
		PSMTXCopy(CameraMatrix(), cameraMtx);
		GXProject(projX, projY, projZ, cameraMtx, projection, viewport,
				  (float*)(shapeBase + 0x10), (float*)(shapeBase + 0x14), (float*)(shapeBase + 0x18));

		*alphaPtr = 0;
		cameraPos.x = CameraWorldX();
		cameraPos.y = CameraWorldY();
		cameraPos.z = CameraWorldZ();
		cameraLookAt.x = CameraLookAtX();
		cameraLookAt.y = CameraLookAtY();
		cameraLookAt.z = CameraLookAtZ();
		PSVECSubtract(&cameraLookAt, &cameraPos, &lookDir);

		objectPos.x = pppMngStPtr->m_matrix.value[0][3];
		objectPos.y = pppMngStPtr->m_matrix.value[1][3];
		objectPos.z = pppMngStPtr->m_matrix.value[2][3];
		PSVECSubtract(&cameraPos, &objectPos, &cameraToObject);
		PSVECScale(&cameraToObject, &cameraToObject, kPppLensFlareCameraToObjectScale);
		PSVECNormalize(&lookDir, &lookDir);
		PSVECNormalize(&cameraToObject, &cameraToObject);
		*(float*)(shapeBase + 0x34) = PSVECDotProduct(&cameraToObject, &lookDir);

		float xProjected = *(float*)(shapeBase + 0x10);
		float yProjected = *(float*)(shapeBase + 0x14);
		u8* arg3Bytes = (u8*)&unkB->m_arg3;
		u8 argA = arg3Bytes[0];
		u32 halfWidth = (u32)(argA >> 1);
		u32 y0 = (u32)((int)yProjected & 0xFFFF);
		u32 x0 = (u32)((int)xProjected & 0xFFFF);
		u32 z0 = __cvt_fp2unsigned((double)(kPppLensFlareDepthToZScale * *(float*)(shapeBase + 0x18)));
		int step = (short)((u16)argA / (u16)arg3Bytes[1]);
		for (u32 y = y0 - halfWidth; (int)y <= (int)(y0 + halfWidth); y += step) {
			for (u32 x = x0 - halfWidth; (int)x <= (int)(x0 + halfWidth); x += step) {
				if (((-1 < (short)x) && (-1 < (short)y)) && ((short)x < 0x281) && ((short)y < 0x1c1)) {
					GXPeekZ((u16)(x & 0xFFFF), (u16)(y & 0xFFFF), &zAtPixel);
					if (z0 <= zAtPixel) {
						*alphaPtr = (u8)(*alphaPtr + 1);
					}
				}
			}
		}

		step = arg3Bytes[1] + 1;
		u32 sampleCount = (u32)(step * step);
		if ((u8)*alphaPtr == sampleCount) {
			*alphaPtr = 0xff;
		} else {
			sampleCount = (u8)*alphaPtr * (0xff / sampleCount);
			*alphaPtr = (u8)sampleCount;
			if ((sampleCount & 0xff) < 0x100) {
				*alphaPtr = (u8)sampleCount;
			} else {
				*alphaPtr = 0xff;
			}
		}

		*alphaPtr = (u8)(int)((double)(float)(u8)(*alphaPtr) * alphaScale);
		if (unkB->m_dataValIndex != 0xffff) {
			long** shapeTable = *(long***)(*(int*)&pppEnvStPtr->m_particleColors[0] + unkB->m_dataValIndex * 4);
			pppCalcFrameShape(*shapeTable, *(short*)(shapeBase + 0x2c), *(short*)(shapeBase + 0x2e),
							  *(short*)(shapeBase + 0x30),
							  (short)unkB->m_initWOrk);
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
	int shapeOffset;
	int colorOffset;
	long** shapeTable;
	u16 dataValIndex;
	u8* objBytes;
	u8* shapeBase;
	u8* colorBase;
	u8* arg3Bytes;

	shapeOffset = ctrlTable->m_serializedDataOffsets[2];
	colorOffset = ctrlTable->m_serializedDataOffsets[1];
	objBytes = (u8*)obj;
	shapeBase = objBytes + shapeOffset + 0x80;
	colorBase = objBytes + colorOffset + 0x80;
	arg3Bytes = (u8*)&unkB->m_arg3;
	dataValIndex = (u16)unkB->m_dataValIndex;

	if ((dataValIndex != 0xFFFF) &&
		(shapeTable = *(long***)(*(int*)&pppEnvStPtr->m_particleColors[0] + dataValIndex * 4),
		 shapeBase[0x32] != 0)) {
		pppCVECTOR local_70;
		Vec local_6c;
		Vec local_60;
		Mtx local_54;

		PSMTXIdentity(local_54);
		local_54[2][2] = *(float*)&unkB->m_stepValue;
		local_54[0][0] = local_54[2][2] * pppMngStPtr->m_scale.x * *(float*)(objBytes + 0x40);
		local_54[1][1] = local_54[2][2] * pppMngStPtr->m_scale.y * *(float*)(objBytes + 0x54);
		local_54[2][2] = local_54[2][2] * pppMngStPtr->m_scale.z * *(float*)(objBytes + 0x68);

		local_60.x = pppMngStPtr->m_matrix.value[0][3];
		local_60.y = pppMngStPtr->m_matrix.value[1][3];
		local_60.z = pppMngStPtr->m_matrix.value[2][3];

		PSMTXMultVec(ppvCameraMatrix02, &local_60, &local_60);

		local_54[0][3] = local_60.x;
		local_54[1][3] = local_60.y;
		local_54[2][3] = local_60.z;

		local_6c.x = local_60.x;
		local_6c.y = local_60.y;
		local_6c.z = local_60.z;

		pppCopyVector__FR3Vec3Vec((Vec*)(shapeBase + 0x20), &local_6c);

		GXLoadPosMtxImm(local_54, 0);

		local_70.rgba[0] = colorBase[8];
		local_70.rgba[1] = colorBase[9];
		local_70.rgba[2] = colorBase[10];
		local_70.rgba[3] = shapeBase[0x32];

		pppSetDrawEnv(&local_70, (pppFMATRIX*)0, kPppLensFlareZero, (u8)unkB->m_payload[0], arg3Bytes[3],
					  arg3Bytes[2], (u8)0, (u8)1, (u8)1, (u8)0);

		pppSetBlendMode(arg3Bytes[2]);
		pppDrawShp(*shapeTable, *(s16*)(shapeBase + 0x2e), pppEnvStPtr->m_materialSetPtr, arg3Bytes[2]);
		pppSetBlendMode(3);
	}
}
