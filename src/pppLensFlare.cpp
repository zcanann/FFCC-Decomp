#include "ffcc/pppLensFlare.h"
#include "ffcc/partMng.h"
#include "ffcc/pppColum.h"
#include "ffcc/pppPart.h"
#include "ffcc/pppShape.h"

#include <dolphin/gx.h>
#include <dolphin/mtx.h>

extern float FLOAT_80331060;

/*
 * --INFO--
 * PAL Address: 0x800dec14
 * PAL Size: 72b
 */
void pppConstructLensFlare(void* obj, void* param)
{
	void* dataPtr = *((void**)((char*)param + 0x0c));
	int offset = *((int*)((char*)dataPtr + 0x08));
	
	float initValue = FLOAT_80331060;
	
	// Initialize float fields
	*((float*)((char*)obj + offset + 0x98)) = initValue;
	*((float*)((char*)obj + offset + 0x94)) = initValue;
	*((float*)((char*)obj + offset + 0x90)) = initValue;
	*((float*)((char*)obj + offset + 0xa8)) = initValue;
	*((float*)((char*)obj + offset + 0xa4)) = initValue;
	*((float*)((char*)obj + offset + 0xa0)) = initValue;
	*((float*)((char*)obj + offset + 0xb4)) = initValue;
	
	// Initialize short fields
	*((short*)((char*)obj + offset + 0xb0)) = 0;
	*((short*)((char*)obj + offset + 0xae)) = 0;
	*((short*)((char*)obj + offset + 0xac)) = 0;
	
	// Initialize byte field
	*((char*)obj + offset + 0xb2) = 0;
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
 */
void pppFrameLensFlare(void* obj, void* param2, void* param3)
{
	// TODO: Complex frame logic
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