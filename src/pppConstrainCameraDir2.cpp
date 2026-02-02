#include "ffcc/pppConstrainCameraDir2.h"
#include <dolphin/mtx.h>

extern int DAT_8032ed70;
extern int DAT_8032ed78;
extern void* pppMngStPtr;
extern void* CameraPcs;
extern float FLOAT_803331e0;
extern float FLOAT_803331e4;
extern float FLOAT_803331e8;
extern int DAT_8032ec70;

void CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf(float, void*, int, float*, float*, float*, float*, float*);
void GetDirectVector__5CUtilFP3VecP3Vec3Vec(void*, float*, float*, float*);
void pppSetFpMatrix__FP9_pppMngSt(void*);

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
	void* pppMngSt;
	float fVar1;
	float* value;
	double dVar2;
	double dVar3;
	double dVar4;
	double dVar5;
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
		value = (float*)((char*)param_1 + 0x80 + *((int*)((char*)param_3 + 0x0c)));
		
		CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf(
			*((float*)((char*)param_2 + 0x00)),
			param_1,
			*((int*)((char*)param_2 + 0x04)),
			value,
			value + 1,
			value + 2,
			(float*)((char*)param_2 + 0x08),
			(float*)((char*)param_2 + 0x0c));

		if ((DAT_8032ed78 != 1) &&
			((*((char*)param_2 + 0x11) != 0) || (*((char*)param_2 + 0x10) != 0))) {
			
			local_cc = *((float*)((char*)&CameraPcs + 0xec));
			local_c8 = *((float*)((char*)&CameraPcs + 0xf0));
			local_c4 = *((float*)((char*)&CameraPcs + 0xf4));
			
			PSMTXCopy(*((Mtx*)((char*)&CameraPcs + 0x70)), MStack_84);
			
			dVar5 = (double)*((float*)((char*)&CameraPcs + 0xe0));
			dVar4 = (double)*((float*)((char*)&CameraPcs + 0xe4));
			dVar3 = (double)*((float*)((char*)&CameraPcs + 0xe8));
			dVar2 = (double)(FLOAT_803331e0 + ((*((float*)((char*)&CameraPcs + 0xfc)) - FLOAT_803331e4) / FLOAT_803331e4));
			
			PSMTXIdentity(*((Mtx*)((char*)pppMngStPtr + 0x10)));
			fVar1 = FLOAT_803331e0;
			*((float*)((char*)pppMngSt + 0x70)) = (float)((double)FLOAT_803331e8 * dVar2);
			*((float*)((char*)pppMngSt + 0x74)) = (float)dVar2;
			*((float*)((char*)pppMngSt + 0x78)) = fVar1;
			
			PSMTXScale(MStack_b4, *((float*)((char*)pppMngSt + 0x70)), *((float*)((char*)pppMngSt + 0x74)), *((float*)((char*)pppMngSt + 0x78)));
			
			if (*((char*)param_2 + 0x11) != 0) {
				PSMTXInverse(MStack_84, *((Mtx*)((char*)pppMngStPtr + 0x10)));
			}
			
			PSMTXConcat(MStack_b4, *((Mtx*)((char*)pppMngStPtr + 0x10)), *((Mtx*)((char*)pppMngStPtr + 0x10)));
			
			if (*((char*)param_2 + 0x10) != 0) {
				dVar2 = (double)*value;
				local_c0.x = (float)((double)local_cc * dVar2 + dVar5);
				local_c0.y = (float)((double)local_c8 * dVar2 + dVar4);
				local_c0.z = (float)((double)local_c4 * dVar2 + dVar3);
			}
			
			dVar2 = (double)*((float*)((char*)param_1 + 0x40));
			dVar3 = (double)*((float*)((char*)param_1 + 0x50));
			local_108 = local_cc;
			local_104 = local_c8;
			local_100 = local_c4;
			
			GetDirectVector__5CUtilFP3VecP3Vec3Vec((void*)&DAT_8032ec70, &local_d8, &local_e4, &local_108);
			
			local_f0.x = (float)(dVar2 * (double)local_d8);
			local_f0.y = (float)(dVar2 * (double)local_d4);
			local_f0.z = (float)(dVar2 * (double)local_d0);
			local_fc.x = (float)(dVar3 * (double)local_e4);
			local_fc.y = (float)(dVar3 * (double)local_e0);
			local_fc.z = (float)(dVar3 * (double)local_dc);
			
			PSVECAdd(&local_c0, &local_f0, &local_c0);
			PSVECAdd(&local_c0, &local_fc, &local_c0);
			
			*((float*)((char*)pppMngStPtr + 0x1c)) = local_c0.x;
			*((float*)((char*)pppMngStPtr + 0x2c)) = local_c0.y;
			*((float*)((char*)pppMngStPtr + 0x3c)) = local_c0.z;
			
			pppSetFpMatrix__FP9_pppMngSt(pppMngSt);
		}
	}
}