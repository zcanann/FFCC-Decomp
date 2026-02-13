#include "ffcc/pppLensFlare.h"
#include "ffcc/partMng.h"
#include "ffcc/pppColum.h"
#include "ffcc/pppPart.h"
#include "ffcc/pppShape.h"

#include <dolphin/gx.h>
#include <dolphin/mtx.h>

extern int DAT_8032ed70;
extern float FLOAT_80331060;
extern float FLOAT_80331064;
extern float FLOAT_80331068;
extern float FLOAT_8033106c;
extern double DOUBLE_80331070;

extern struct {
	float _212_4_;
	float _216_4_;
	float _220_4_;
	float _224_4_;
	float _228_4_;
	float _232_4_;
	Mtx m_cameraMatrix;
} CameraPcs;

extern "C" unsigned int __cvt_fp2unsigned(double);
extern "C" void GXPeekZ(unsigned short, unsigned short, unsigned int*);

/*
 * --INFO--
 * PAL Address: 0x800dec14
 * PAL Size: 72b
 */
void pppConstructLensFlare(void* obj, void* param)
{
	void* dataPtr = *((void**)((char*)param + 0x0c));
	char* work = (char*)obj + *((int*)((char*)dataPtr + 0x08)) + 0x80;

	float initValue = FLOAT_80331060;

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
void pppDestructLensFlare(void)
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
void pppFrameLensFlare(void* obj, void* param2, void* param3)
{
	UnkB* unkB = (UnkB*)param2;
	UnkC* unkC = (UnkC*)param3;
	int offset2;
	int offset1;
	unsigned char* alphaPtr;
	float viewport[6];
	float projection[7];
	Mtx cameraMtx;
	Vec cameraPos;
	Vec cameraLookAt;
	Vec lookDir;
	Vec objectPos;
	Vec cameraToObject;
	unsigned int zAtPixel;
	unsigned int x;
	unsigned int y;

	if (DAT_8032ed70 == 0) {
		offset2 = unkC->m_serializedDataOffsets[2];
		offset1 = unkC->m_serializedDataOffsets[1];
		alphaPtr = (unsigned char*)((char*)obj + offset2 + 0xb2);

		GXGetViewportv(viewport);
		GXGetProjectionv(projection);
		PSMTXCopy(CameraPcs.m_cameraMatrix, cameraMtx);

		GXProject(pppMngStPtr->m_matrix.value[0][3], pppMngStPtr->m_matrix.value[1][3],
				  pppMngStPtr->m_matrix.value[2][3], cameraMtx, projection, viewport,
				  (float*)((char*)obj + offset2 + 0x90), (float*)((char*)obj + offset2 + 0x94),
				  (float*)((char*)obj + offset2 + 0x98));

		*alphaPtr = 0;

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
		PSVECScale(&cameraToObject, &cameraToObject, FLOAT_80331068);
		PSVECNormalize(&lookDir, &lookDir);
		PSVECNormalize(&cameraToObject, &cameraToObject);

		*(float*)((char*)obj + offset2 + 0xb4) = PSVECDotProduct(&cameraToObject, &lookDir);

		unsigned int halfWidth = ((unsigned char)unkB->m_arg3) >> 1;
		unsigned int x0 = ((int)*(float*)((char*)obj + offset2 + 0x90)) & 0xffff;
		unsigned int y0 = ((int)*(float*)((char*)obj + offset2 + 0x94)) & 0xffff;
		unsigned int z0 = __cvt_fp2unsigned((double)(FLOAT_8033106c * *(float*)((char*)obj + offset2 + 0x98)));
		int stride = (short)((unsigned short)(unsigned char)unkB->m_arg3 /
							 (unsigned short)*((unsigned char*)(&unkB->m_arg3) + 1));

		for (y = y0 - halfWidth; (int)y <= (int)(y0 + halfWidth); y += stride) {
			for (x = x0 - halfWidth; (int)x <= (int)(x0 + halfWidth); x += stride) {
				if (((-1 < (short)x) && (-1 < (short)y)) && ((short)x < 0x281) && ((short)y < 0x1c1)) {
					GXPeekZ(x & 0xffff, y & 0xffff, &zAtPixel);
					if (z0 <= zAtPixel) {
						*alphaPtr = *alphaPtr + 1;
					}
				}
			}
		}

		int sampleDiv = *((unsigned char*)(&unkB->m_arg3) + 1) + 1;
		unsigned int totalSamples = sampleDiv * sampleDiv;

		if (*alphaPtr == totalSamples) {
			*alphaPtr = 0xff;
		} else {
			unsigned int scaledAlpha = *alphaPtr * (0xff / totalSamples);
			if (scaledAlpha < 0x100) {
				*alphaPtr = (unsigned char)scaledAlpha;
			} else {
				*alphaPtr = 0xff;
			}
		}

		*alphaPtr = (unsigned char)(int)((double)(float)*alphaPtr *
										 (double)((float)((double)(unsigned char)*((unsigned char*)obj + offset1 + 0x88) - DOUBLE_80331070) *
												  FLOAT_80331064));

		if (unkB->m_dataValIndex != 0xffff) {
			long* shapeTable = *(long**)(*(int*)&pppEnvStPtr->m_particleColors[0] + unkB->m_dataValIndex * 4);
			pppCalcFrameShape(shapeTable, *(short*)((char*)obj + offset2 + 0xac),
							  *(short*)((char*)obj + offset2 + 0xae),
							  *(short*)((char*)obj + offset2 + 0xb0),
							  (short)unkB->m_initWOrk);
		}
	}
	return;
}

/*
 * --INFO--
 * PAL Address: 0x800de718
 * PAL Size: 428b
 */
void pppRenderLensFlare(void* obj, void* param2, void* param3)
{
	UnkB* unkB = (UnkB*)param2;
	UnkC* unkC = (UnkC*)param3;
	
	int iVar2 = unkC->m_serializedDataOffsets[2];
	int iVar1 = unkC->m_serializedDataOffsets[1];
	
	if ((unkB->m_dataValIndex != 0xffff) &&
		(*(((char*)obj) + iVar2 + 0xb2) != 0)) {
		
		unsigned int* puVar3 = *(unsigned int**)
			(*(int*)&pppEnvStPtr->m_particleColors[0] + unkB->m_dataValIndex * 4);
		
		pppCVECTOR local_70;
		Vec local_6c;
		Vec local_60;
		Mtx local_54;
		
		PSMTXIdentity(local_54);
		local_54[2][2] = (float)unkB->m_stepValue;
		local_54[0][0] = local_54[2][2] * pppMngStPtr->m_scale.x * *(float*)(((char*)obj) + 0x40);
		local_54[1][1] = local_54[2][2] * pppMngStPtr->m_scale.y * *(float*)(((char*)obj) + 0x54);
		local_54[2][2] = local_54[2][2] * pppMngStPtr->m_scale.z * *(float*)(((char*)obj) + 0x68);
		
		local_60.x = pppMngStPtr->m_matrix.value[0][3];
		local_60.y = pppMngStPtr->m_matrix.value[1][3];
		local_60.z = pppMngStPtr->m_matrix.value[2][3];
		
		PSMTXMultVec(ppvCameraMatrix0, &local_60, &local_60);
		
		local_54[0][3] = local_60.x;
		local_54[1][3] = local_60.y;
		local_54[2][3] = local_60.z;
		
		local_6c.x = local_60.x;
		local_6c.y = local_60.y;
		local_6c.z = local_60.z;
		
		Vec* targetVec = (Vec*)(((char*)obj) + iVar2 + 0xa0);
		pppCopyVector(*targetVec, local_6c);
		
		GXLoadPosMtxImm(local_54, 0);
		
		local_70.rgba[0] = *(((unsigned char*)obj) + iVar1 + 0x88);
		local_70.rgba[1] = *(((unsigned char*)obj) + iVar1 + 0x89);
		local_70.rgba[2] = *(((unsigned char*)obj) + iVar1 + 0x8a);
		local_70.rgba[3] = *(((unsigned char*)obj) + iVar2 + 0xb2);
		
		pppSetDrawEnv(&local_70, (pppFMATRIX*)0, FLOAT_80331060,
			(unsigned char)unkB->m_payload[0],
			*((unsigned char*)(&unkB->m_arg3) + 3),
			*((unsigned char*)(&unkB->m_arg3) + 2),
			(unsigned char)0, (unsigned char)1, (unsigned char)1, (unsigned char)0);
		
		pppSetBlendMode(*((unsigned char*)(&unkB->m_arg3) + 2));
		
		pppDrawShp((long*)puVar3, *(short*)(((char*)obj) + iVar2 + 0xae),
			pppEnvStPtr->m_materialSetPtr, *((unsigned char*)(&unkB->m_arg3) + 2));
		
		pppSetBlendMode(3);
	}
	return;
}
