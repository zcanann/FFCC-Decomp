#include "ffcc/pppConstrainCameraDir2.h"
#include "ffcc/partMng.h"
#include "ffcc/pppConstrainCameraDir.h"
#include <dolphin/mtx.h>

extern int DAT_8032ed70;
extern char DAT_8032ed78;
extern _pppMngSt* pppMngStPtr;
extern struct {
    float _224_4_, _228_4_, _232_4_, _236_4_, _240_4_, _244_4_, _252_4_;
    Mtx m_cameraMatrix;
} CameraPcs;
extern float FLOAT_803331e0;
extern float FLOAT_803331e4;
extern float FLOAT_803331e8;
extern int DAT_8032ec70;

extern "C" void CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf(float, pppConstrainCameraDir*, int, float*, float*, float*, float*, float*);
extern "C" void GetDirectVector__5CUtilFP3VecP3Vec3Vec(void*, Vec*, Vec*, Vec*);
extern "C" void pppSetFpMatrix__FP9_pppMngSt(_pppMngSt*);

/*
 * --INFO--
 * PAL Address: 0x8016ca80
 * PAL Size: 688b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppFrameConstrainCameraDir2(pppConstrainCameraDir* param_1, UnkB* param_2, UnkC* param_3)
{
	_pppMngSt* pppMngSt;
	float fVar1;
	float* value;
	float fVar2;
	float fVar3;
	float fVar4;
	float fVar5;
	unsigned char* flags;
	float local_108;
	float local_104;
	float local_100;
	Vec local_fc;
	Vec local_f0;
	float local_e4;
	float local_e0;
	float local_dc;
	float local_d8;
	float local_d4;
	float local_d0;
	float local_cc;
	float local_c8;
	float local_c4;
	Vec local_c0;
	Mtx MStack_b4;
	Mtx MStack_84;

	pppMngSt = pppMngStPtr;
	if (DAT_8032ed70 == 0) {
		value = (float*)((char*)param_1 + *param_3->m_serializedDataOffsets + 0x80);
		flags = (unsigned char*)&param_2->m_arg3;
		
		CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf(
			param_2->m_dataValIndex,
			param_1,
			param_2->m_graphId,
			value,
			value + 1,
			value + 2,
			&param_2->m_initWOrk,
			&param_2->m_stepValue);

		if ((DAT_8032ed78 != 1) && ((flags[1] != 0 || flags[0] != 0))) {
			
			local_cc = CameraPcs._236_4_;
			local_c8 = CameraPcs._240_4_;
			local_c4 = CameraPcs._244_4_;
			
			PSMTXCopy(CameraPcs.m_cameraMatrix, MStack_84);
			
			fVar5 = CameraPcs._224_4_;
			fVar4 = CameraPcs._228_4_;
			fVar3 = CameraPcs._232_4_;
			fVar2 = FLOAT_803331e0 + ((CameraPcs._252_4_ - FLOAT_803331e4) / FLOAT_803331e4);
			
			PSMTXIdentity(pppMngStPtr->m_matrix.value);
			fVar1 = FLOAT_803331e0;
			pppMngSt->m_scale.x = FLOAT_803331e8 * fVar2;
			pppMngSt->m_scale.y = fVar2;
			pppMngSt->m_scale.z = fVar1;
			
			PSMTXScale(MStack_b4, pppMngSt->m_scale.x, pppMngSt->m_scale.y, pppMngSt->m_scale.z);
			
			if (flags[1] != 0) {
				PSMTXInverse(MStack_84, pppMngStPtr->m_matrix.value);
			}
			
			PSMTXConcat(MStack_b4, pppMngStPtr->m_matrix.value, pppMngStPtr->m_matrix.value);
			
			if (flags[0] != 0) {
				fVar2 = *value;
				local_c0.x = local_cc * fVar2 + fVar5;
				local_c0.y = local_c8 * fVar2 + fVar4;
				local_c0.z = local_c4 * fVar2 + fVar3;
			}
			
			fVar2 = ((_pppPObject*)param_1)->m_localMatrix.value[0][3];
			fVar3 = ((_pppPObject*)param_1)->m_localMatrix.value[1][3];
			local_108 = local_cc;
			local_104 = local_c8;
			local_100 = local_c4;
			
			GetDirectVector__5CUtilFP3VecP3Vec3Vec((void*)&DAT_8032ec70, (Vec*)&local_d8, (Vec*)&local_e4, (Vec*)&local_108);
			
			local_f0.x = fVar2 * local_d8;
			local_f0.y = fVar2 * local_d4;
			local_f0.z = fVar2 * local_d0;
			local_fc.x = fVar3 * local_e4;
			local_fc.y = fVar3 * local_e0;
			local_fc.z = fVar3 * local_dc;
			
			PSVECAdd(&local_c0, &local_f0, &local_c0);
			PSVECAdd(&local_c0, &local_fc, &local_c0);
			
			pppMngStPtr->m_matrix.value[0][3] = local_c0.x;
			pppMngStPtr->m_matrix.value[1][3] = local_c0.y;
			pppMngStPtr->m_matrix.value[2][3] = local_c0.z;
			
			pppSetFpMatrix__FP9_pppMngSt(pppMngSt);
		}
	}
}
