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

void CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf(float, pppConstrainCameraDir*, int, float*, float*, float*, float*, float*);
void GetDirectVector__5CUtilFP3VecP3Vec3Vec(void*, Vec*, Vec*, Vec*);
void pppSetFpMatrix__FP9_pppMngSt(_pppMngSt*);

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
	double dVar2;
	double dVar3;
	double dVar4;
	double dVar5;
	Vec local_108;
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
		
		CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf(
			param_2->m_dataValIndex,
			param_1,
			param_2->m_graphId,
			value,
			value + 1,
			value + 2,
			&param_2->m_initWOrk,
			&param_2->m_stepValue);

		if ((DAT_8032ed78 != 1) && (((char*)&param_2->m_arg3)[1] != 0 || param_2->m_arg3 != 0)) {
			
			local_cc = CameraPcs._236_4_;
			local_c8 = CameraPcs._240_4_;
			local_c4 = CameraPcs._244_4_;
			
			PSMTXCopy(CameraPcs.m_cameraMatrix, MStack_84);
			
			dVar5 = (double)CameraPcs._224_4_;
			dVar4 = (double)CameraPcs._228_4_;
			dVar3 = (double)CameraPcs._232_4_;
			dVar2 = (double)(FLOAT_803331e0 + ((CameraPcs._252_4_ - FLOAT_803331e4) / FLOAT_803331e4));
			
			PSMTXIdentity(pppMngStPtr->m_matrix.value);
			fVar1 = FLOAT_803331e0;
			pppMngSt->m_scale.x = (float)((double)FLOAT_803331e8 * dVar2);
			pppMngSt->m_scale.y = (float)dVar2;
			pppMngSt->m_scale.z = fVar1;
			
			PSMTXScale(MStack_b4, pppMngSt->m_scale.x, pppMngSt->m_scale.y, pppMngSt->m_scale.z);
			
			if (((char*)&param_2->m_arg3)[1] != 0) {
				PSMTXInverse(MStack_84, pppMngStPtr->m_matrix.value);
			}
			
			PSMTXConcat(MStack_b4, pppMngStPtr->m_matrix.value, pppMngStPtr->m_matrix.value);
			
			if (param_2->m_arg3 != 0) {
				dVar2 = (double)*value;
				local_c0.x = (float)((double)local_cc * dVar2 + dVar5);
				local_c0.y = (float)((double)local_c8 * dVar2 + dVar4);
				local_c0.z = (float)((double)local_c4 * dVar2 + dVar3);
			}
			
			dVar2 = (double)((_pppPObject*)param_1)->m_localMatrix.value[0][3];
			dVar3 = (double)((_pppPObject*)param_1)->m_localMatrix.value[1][3];
			local_108.x = local_cc;
			local_108.y = local_c8;
			local_108.z = local_c4;
			
			GetDirectVector__5CUtilFP3VecP3Vec3Vec((void*)&DAT_8032ec70, (Vec*)&local_d8, (Vec*)&local_e4, &local_108);
			
			local_f0.x = (float)(dVar2 * (double)local_d8);
			local_f0.y = (float)(dVar2 * (double)local_d4);
			local_f0.z = (float)(dVar2 * (double)local_d0);
			local_fc.x = (float)(dVar3 * (double)local_e4);
			local_fc.y = (float)(dVar3 * (double)local_e0);
			local_fc.z = (float)(dVar3 * (double)local_dc);
			
			PSVECAdd(&local_c0, &local_f0, &local_c0);
			PSVECAdd(&local_c0, &local_fc, &local_c0);
			
			pppMngStPtr->m_matrix.value[0][3] = local_c0.x;
			pppMngStPtr->m_matrix.value[1][3] = local_c0.y;
			pppMngStPtr->m_matrix.value[2][3] = local_c0.z;
			
			pppSetFpMatrix__FP9_pppMngSt(pppMngSt);
		}
	}
}
