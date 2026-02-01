// Function: pppFrameYmBreath
// Entry: 800c04f8
// Size: 1264 bytes

/* WARNING: Removing unreachable block (ram,0x800c09cc) */
/* WARNING: Removing unreachable block (ram,0x800c0508) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppFrameYmBreath(pppYmBreath *pppYmBreath,int param_2,int param_3)

{
  bool bVar1;
  _pppMngSt *p_Var2;
  int iVar3;
  float fVar4;
  undefined4 uVar5;
  Vec *inVec;
  short sVar6;
  uint uVar7;
  undefined4 *puVar8;
  Mtx *dest;
  int iVar9;
  Mtx *a;
  int iVar10;
  float fVar11;
  double dVar12;
  float local_168;
  float local_164;
  float local_160;
  undefined4 local_15c;
  undefined4 local_158;
  undefined4 local_154;
  float local_150;
  float local_14c;
  float local_148;
  float local_144;
  float local_140;
  float local_13c;
  float local_138;
  float local_134;
  float local_130;
  Vec local_12c;
  undefined4 local_120;
  undefined4 local_11c;
  undefined4 local_118;
  Vec local_114;
  Vec local_108;
  undefined auStack_fc [12];
  pppFMATRIX local_f0;
  pppFMATRIX pStack_c0;
  Mtx MStack_90;
  Mtx local_60;
  
  p_Var2 = pppMngStPtr;
  if (DAT_8032ed70 == 0) {
    iVar3 = (*(int **)(param_3 + 0xc))[1];
    dest = (Mtx *)((int)(&pppYmBreath->field0_0x0 + 2) + **(int **)(param_3 + 0xc));
    if (dest[1].value[0][0] == 0.0) {
      dest[1].value[1][0] = (float)(uint)*(ushort *)(param_2 + 0x1e);
      *(undefined2 *)((int)dest[1].value[2] + 6) = *(undefined2 *)(param_2 + 0x12);
      *(undefined2 *)(dest[1].value[2] + 1) = *(undefined2 *)(param_2 + 0x14);
      fVar4 = (float)pppMemAlloc__FUlPQ27CMemory6CStagePci
                               ((int)dest[1].value[1][0] * 0x60,pppEnvStPtr->m_stagePtr,
                                s_pppYmBreath_cpp_801da9b0,0x243);
      dest[1].value[0][0] = fVar4;
      fVar4 = dest[1].value[0][0];
      if (fVar4 != 0.0) {
        memset(fVar4,0,(int)dest[1].value[1][0] * 0x60);
      }
      fVar4 = (float)pppMemAlloc__FUlPQ27CMemory6CStagePci
                               ((int)dest[1].value[1][0] * 0x30,pppEnvStPtr->m_stagePtr,
                                s_pppYmBreath_cpp_801da9b0,0x249);
      dest[1].value[0][1] = fVar4;
      fVar4 = dest[1].value[0][1];
      if (fVar4 != 0.0) {
        memset(fVar4,0,(int)dest[1].value[1][0] * 0x30);
      }
      fVar4 = (float)pppMemAlloc__FUlPQ27CMemory6CStagePci
                               ((int)dest[1].value[1][0] << 5,pppEnvStPtr->m_stagePtr,
                                s_pppYmBreath_cpp_801da9b0,0x24f);
      dest[1].value[0][2] = fVar4;
      fVar4 = dest[1].value[0][2];
      if (fVar4 != 0.0) {
        memset(fVar4,0,(int)dest[1].value[1][0] << 5);
      }
      fVar4 = (float)pppMemAlloc__FUlPQ27CMemory6CStagePci
                               ((uint)*(ushort *)(param_2 + 0x14) * 0x5c,pppEnvStPtr->m_stagePtr,
                                s_pppYmBreath_cpp_801da9b0,0x255);
      dest[1].value[0][3] = fVar4;
      fVar4 = dest[1].value[0][3];
      if (fVar4 != 0.0) {
        memset(fVar4,0,(uint)*(ushort *)(param_2 + 0x14) * 0x5c);
        puVar8 = (undefined4 *)dest[1].value[0][3];
        for (iVar10 = 0; iVar10 < (int)(uint)*(ushort *)(param_2 + 0x14); iVar10 = iVar10 + 1) {
          uVar5 = pppMemAlloc__FUlPQ27CMemory6CStagePci
                            ((uint)*(ushort *)(param_2 + 0x12),pppEnvStPtr->m_stagePtr,
                             s_pppYmBreath_cpp_801da9b0,0x260);
          puVar8[1] = uVar5;
          memset(puVar8[1],0xffffffff,*(undefined2 *)(param_2 + 0x12));
          uVar5 = pppMemAlloc__FUlPQ27CMemory6CStagePci
                            ((uint)*(ushort *)(param_2 + 0x12),pppEnvStPtr->m_stagePtr,
                             s_pppYmBreath_cpp_801da9b0,0x263);
          puVar8[2] = uVar5;
          memset(puVar8[2],0xffffffff,*(undefined2 *)(param_2 + 0x12));
          *puVar8 = 0;
          puVar8 = puVar8 + 0x17;
        }
      }
      fVar11 = FLOAT_80330c90;
      fVar4 = FLOAT_80330c80;
      inVec = (Vec *)(dest[1].value[1] + 2);
      dest[1].value[1][2] = FLOAT_80330c80;
      dest[1].value[1][3] = fVar4;
      dest[1].value[2][0] = fVar11;
      PSVECNormalize(inVec,inVec);
    }
    PSMTXCopy(&pppMngStPtr->m_matrix,dest);
    UpdateAllParticle__FP11_pppPObjectP9VYmBreathP9PYmBreathP6VColor
              (&pppYmBreath->field0_0x0,dest,param_2,
               (undefined *)((int)(&pppYmBreath->field0_0x0 + 2) + iVar3));
    fVar4 = dest[1].value[0][1];
    fVar11 = dest[1].value[0][3];
    for (iVar3 = 0; iVar3 < (int)(uint)*(ushort *)(param_2 + 0x14); iVar3 = iVar3 + 1) {
      uVar7 = (uint)*(ushort *)(param_2 + 0x12);
      iVar10 = (int)dest[1].value[0][3] + (short)iVar3 * 0x5c;
      for (sVar6 = 0; (int)sVar6 < (int)uVar7; sVar6 = sVar6 + 1) {
        if ((*(char *)(*(int *)(iVar10 + 4) + (int)sVar6) == -1) ||
           (*(char *)(*(int *)(iVar10 + 8) + (int)sVar6) != '\x01')) {
          bVar1 = false;
          goto LAB_800c07a8;
        }
      }
      bVar1 = true;
LAB_800c07a8:
      if (bVar1) {
        iVar9 = -1;
        iVar10 = 0;
        dVar12 = (double)(p_Var2->m_paramD * *(float *)(param_2 + 8));
        for (; uVar7 != 0; uVar7 = uVar7 - 1) {
          if (*(char *)(*(int *)((int)fVar11 + 8) + iVar10) != -1) {
            iVar9 = (int)*(char *)(*(int *)((int)fVar11 + 4) + iVar10);
            break;
          }
          iVar10 = iVar10 + 1;
        }
        PSMTXIdentity(&local_60);
        local_60.value[0][0] = (float)dVar12;
        local_60.value[1][1] = (float)dVar12;
        a = (Mtx *)((int)fVar4 + iVar9 * 0x30);
        local_60.value[2][2] = (float)dVar12;
        PSMTXConcat(a,&(pppYmBreath->field0_0x0).m_localMatrix,&MStack_90);
        PSMTXMultVec(&MStack_90,(Vec *)((int)fVar11 + 0xc),&local_114);
        local_f0.value[0][0] = a->value[0][0];
        local_f0.value[0][1] = a->value[0][1];
        local_f0.value[0][2] = a->value[0][2];
        local_f0.value[0][3] = a->value[0][3];
        local_f0.value[1][0] = a->value[1][0];
        local_f0.value[1][1] = a->value[1][1];
        local_f0.value[1][2] = a->value[1][2];
        local_f0.value[1][3] = a->value[1][3];
        local_f0.value[2][0] = a->value[2][0];
        local_f0.value[2][1] = a->value[2][1];
        local_f0.value[2][2] = a->value[2][2];
        local_f0.value[2][3] = a->value[2][3];
        pppCopyMatrix__FR10pppFMATRIX10pppFMATRIX(&pStack_c0,&local_f0);
        pStack_c0.value[0][3] = FLOAT_80330c80;
        pStack_c0.value[1][3] = FLOAT_80330c80;
        pStack_c0.value[2][3] = FLOAT_80330c80;
        *(float *)((int)fVar11 + 0x28) = (float)dVar12;
        local_12c.x = *(float *)((int)fVar11 + 0x18);
        local_12c.y = *(float *)((int)fVar11 + 0x1c);
        local_12c.z = *(float *)((int)fVar11 + 0x20);
        pppCopyVector__FR3Vec3Vec(&local_108,&local_12c);
        PSMTXMultVec(&pStack_c0,&local_108,&local_108);
        local_138 = local_108.x;
        local_134 = local_108.y;
        local_130 = local_108.z;
        pppNormalize__FR3Vec3Vec(&local_108,&local_138);
        PSVECScale(*(float *)((int)fVar11 + 0x24),&local_108,&local_108);
        local_150 = local_108.x;
        local_14c = local_108.y;
        local_148 = local_108.z;
        local_144 = local_114.x;
        local_140 = local_114.y;
        local_13c = local_114.z;
        pppAddVector__FR3Vec3Vec3Vec(&local_120,&local_144,&local_150);
        local_168 = local_114.x;
        local_164 = local_114.y;
        local_160 = local_114.z;
        local_15c = local_120;
        local_158 = local_11c;
        local_154 = local_118;
        pppSubVector__FR3Vec3Vec3Vec(auStack_fc,&local_15c,&local_168);
        pppHitCylinderSendSystem__FP9_pppMngStP3VecP3Vecff
                  (dVar12,(double)*(float *)(param_2 + 4),p_Var2,&local_114,auStack_fc);
      }
      fVar11 = (float)((int)fVar11 + 0x5c);
    }
  }
  return;
}

