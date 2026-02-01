// Function: pppFrameYmMiasma
// Entry: 80090aa4
// Size: 748 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppFrameYmMiasma(pppYmMiasma *pppYmMiasma,int *param_2,int param_3)

{
  uint uVar1;
  float fVar2;
  short sVar3;
  int iVar4;
  _PARTICLE_DATA *particleData;
  int iVar5;
  int *piVar6;
  double dVar7;
  Vec local_68;
  int local_5c;
  int local_58;
  int local_54;
  float local_50;
  float local_4c;
  float local_48;
  Vec local_44;
  undefined auStack_38 [16];
  undefined4 local_28;
  uint uStack_24;
  longlong local_20;
  
  if (DAT_8032ed70 == 0) {
    piVar6 = (int *)((int)(&pppYmMiasma->field0_0x0 + 2) + *(int *)(*(int *)(param_3 + 0xc) + 8));
    if (*param_2 == (pppYmMiasma->field0_0x0).m_graphId) {
      piVar6[7] = (int)((float)piVar6[7] + (float)param_2[0x16]);
      piVar6[8] = (int)((float)piVar6[8] + (float)param_2[0x17]);
      piVar6[9] = (int)((float)piVar6[9] + (float)param_2[0x18]);
    }
    if (*piVar6 == 0) {
      iVar4 = pppMemAlloc__FUlPQ27CMemory6CStagePci
                        ((uint)*(ushort *)(param_2 + 3) * 0x50,pppEnvStPtr->m_stagePtr,
                         s_pppYmMiasma_cpp_801d9ca8,0x18d);
      *piVar6 = iVar4;
      particleData = (_PARTICLE_DATA *)*piVar6;
      for (iVar4 = 0; iVar4 < (int)(uint)*(ushort *)(param_2 + 3); iVar4 = iVar4 + 1) {
        InitParticleData__FP9VYmMiasmaP11_pppPObjectP9PYmMiasmaP13PARTICLE_DATA
                  (piVar6,&pppYmMiasma->field0_0x0,param_2,particleData);
        particleData = (_PARTICLE_DATA *)&particleData->m_sizeVal;
      }
    }
    fVar2 = FLOAT_80330644;
    *(char *)(piVar6 + 2) = *(char *)(piVar6 + 2) + '\x01';
    piVar6[1] = (int)((float)piVar6[1] - (float)param_2[0x1b]);
    if ((float)piVar6[1] < fVar2) {
      piVar6[1] = (int)fVar2;
    }
    if (*(byte *)(param_2 + 0x19) < *(byte *)(piVar6 + 2)) {
      *(undefined *)(piVar6 + 2) = 0;
      piVar6[1] = param_2[6];
      iVar4 = rand();
      fVar2 = FLOAT_80330644;
      sVar3 = (short)iVar4 -
              (short)(iVar4 / (int)*(short *)(param_2 + 0x1a)) * *(short *)(param_2 + 0x1a);
      uVar1 = (uint)(int)sVar3 >> 0x1f;
      if (((int)sVar3 & 1U ^ uVar1) == uVar1) {
        sVar3 = -sVar3;
      }
      local_28 = 0x43300000;
      uStack_24 = (int)(short)(sVar3 + *(short *)((int)param_2 + 0x66)) ^ 0x80000000;
      uVar1 = (uint)((FLOAT_80330650 *
                     FLOAT_80330640 *
                     (float)((double)CONCAT44(0x43300000,uStack_24) - DOUBLE_80330648)) /
                    FLOAT_80330654);
      local_20 = (longlong)(int)uVar1;
      iVar4 = *(int *)((int)ppvSinTbl + (uVar1 & 0xfffc));
      piVar6[4] = *(int *)((int)ppvSinTbl + (uVar1 + 0x4000 & 0xfffc));
      piVar6[5] = (int)fVar2;
      piVar6[6] = iVar4;
    }
    piVar6[8] = (int)((float)piVar6[8] + (float)piVar6[9]);
    piVar6[7] = (int)((float)piVar6[7] + (float)piVar6[8]);
    iVar4 = *piVar6;
    for (iVar5 = 0; iVar5 < (int)(uint)*(ushort *)(param_2 + 3); iVar5 = iVar5 + 1) {
      UpdateParticleData__FP11_pppPObjectP13_pppCtrlTableP9PYmMiasmaP13PARTICLE_DATA
                (&pppYmMiasma->field0_0x0,param_3,param_2,iVar4);
      iVar4 = iVar4 + 0x50;
    }
    local_50 = (pppMngStPtr->m_matrix).value[0][3];
    local_4c = (pppMngStPtr->m_matrix).value[1][3];
    local_48 = (pppMngStPtr->m_matrix).value[2][3];
    local_5c = piVar6[10];
    local_58 = piVar6[0xb];
    local_54 = piVar6[0xc];
    local_44.x = local_50;
    local_44.y = local_4c;
    local_44.z = local_48;
    pppSubVector__FR3Vec3Vec3Vec(auStack_38,&local_50,&local_5c);
    dVar7 = (double)PSVECDistance(&local_44,(Vec *)(piVar6 + 10));
    if (dVar7 == (double)FLOAT_80330644) {
      *(undefined *)(piVar6 + 0xd) = 0;
    }
    else {
      *(undefined *)(piVar6 + 0xd) = 0xff;
    }
    local_68.x = local_44.x;
    local_68.y = local_44.y;
    local_68.z = local_44.z;
    pppCopyVector__FR3Vec3Vec((Vec *)(piVar6 + 10),&local_68);
  }
  return;
}

