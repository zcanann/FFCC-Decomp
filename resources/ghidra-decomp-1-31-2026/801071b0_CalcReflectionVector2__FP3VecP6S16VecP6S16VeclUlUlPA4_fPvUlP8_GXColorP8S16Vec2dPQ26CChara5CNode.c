// Function: CalcReflectionVector2__FP3VecP6S16VecP6S16VeclUlUlPA4_fPvUlP8_GXColorP8S16Vec2dPQ26CChara5CNode
// Entry: 801071b0
// Size: 1428 bytes

/* WARNING: Removing unreachable block (ram,0x80107728) */
/* WARNING: Removing unreachable block (ram,0x8010747c) */
/* WARNING: Removing unreachable block (ram,0x801071c0) */

void CalcReflectionVector2__FP3VecP6S16VecP6S16VeclUlUlPA4_fPvUlP8_GXColorP8S16Vec2dPQ26CChara5CNode
               (int param_1,int param_2,int param_3,int param_4,undefined4 param_5,
               undefined4 param_6,Mtx *param_7,ushort *param_8,int param_9,int param_10,int param_11
               ,int param_12)

{
  byte bVar1;
  ushort uVar2;
  ushort uVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  int iVar7;
  char *pcVar8;
  undefined4 *puVar9;
  uint uVar10;
  ushort *puVar11;
  float *outVec;
  ushort *puVar12;
  byte bVar13;
  double dVar14;
  float local_1a8;
  float local_1a4;
  S16Vec local_1a0;
  S16Vec local_198;
  float local_190;
  float local_18c;
  CVector local_188;
  float local_17c;
  float local_178;
  float local_174;
  Vec VStack_170;
  Vec VStack_164;
  Vec VStack_158;
  Vec local_14c;
  Vec local_140;
  Vec local_134;
  Vec local_128;
  Mtx MStack_11c;
  Mtx MStack_ec;
  Mtx MStack_bc;
  Mtx MStack_8c;
  
  local_128.x = (float)CameraPcs._224_4_;
  local_128.y = (float)CameraPcs._228_4_;
  local_128.z = (float)CameraPcs._232_4_;
  PSMTXCopy(param_7,&MStack_11c);
  local_134.x = *(float *)(param_12 + 0x78);
  local_134.y = *(float *)(param_12 + 0x88);
  local_134.z = *(float *)(param_12 + 0x98);
  local_140.x = MStack_11c.value[0][3];
  local_140.y = MStack_11c.value[1][3];
  local_140.z = MStack_11c.value[2][3];
  PSVECAdd(&local_134,&local_140,&local_14c);
  PSMTXCopy((Mtx *)(param_12 + 0x6c),param_7);
  param_7->value[0][3] = local_14c.x;
  param_7->value[1][3] = local_14c.y;
  param_7->value[2][3] = local_14c.z;
  PSMTXCopy(param_7,&MStack_ec);
  MStack_ec.value[0][3] = FLOAT_80331898;
  MStack_ec.value[1][3] = FLOAT_80331898;
  MStack_ec.value[2][3] = FLOAT_80331898;
  PSMTXCopy(&CameraPcs.m_cameraMatrix,&MStack_bc);
  PSMTXConcat(&MStack_bc,param_7,&MStack_8c);
  dVar14 = (double)FLOAT_803318a4;
  puVar12 = (ushort *)((int)param_8 + param_9);
  while (param_8 < puVar12) {
    bVar1 = *(byte *)param_8;
    uVar2 = *(ushort *)((int)param_8 + 1);
    iVar7 = IsHasDrawFmtDL__5CUtilFUc((CUtil *)&DAT_8032ec70,(uint)bVar1);
    if (iVar7 == 0) break;
    param_8 = (ushort *)((int)param_8 + 3);
    for (iVar7 = 0; iVar7 < (int)(uint)uVar2; iVar7 = iVar7 + 1) {
      uVar10 = (uint)*param_8;
      uVar3 = param_8[1];
      puVar11 = param_8 + 4;
      if ((bVar1 & 7) == 2) {
        puVar11 = param_8 + 5;
      }
      puVar9 = (undefined4 *)(param_2 + uVar10 * 6);
      local_198._0_4_ = *puVar9;
      local_198.z = *(short *)(puVar9 + 1);
      ConvI2FVector__5CUtilFR3Vec6S16Vecl((CUtil *)&DAT_8032ec70,&VStack_164,&local_198,param_5);
      puVar9 = (undefined4 *)(param_3 + (uint)uVar3 * 6);
      local_1a0._0_4_ = *puVar9;
      local_1a0.z = *(short *)(puVar9 + 1);
      ConvI2FVector__5CUtilFR3Vec6S16Vecl((CUtil *)&DAT_8032ec70,&VStack_170,&local_1a0,param_6);
      PSMTXMultVec(param_7,&VStack_164,&VStack_164);
      PSMTXMultVec(&MStack_ec,&VStack_170,&VStack_170);
      PSVECSubtract(&VStack_164,&local_128,&VStack_158);
      PSVECNormalize(&VStack_158,&VStack_158);
      outVec = (float *)(param_1 + uVar10 * 0xc);
      C_VECReflect(&VStack_158,&VStack_170,outVec);
      local_178 = ABS(outVec[1]);
      local_17c = ABS(*outVec);
      local_174 = ABS(outVec[2]);
      bVar13 = local_17c < local_178;
      fVar4 = local_17c;
      if ((bool)bVar13) {
        fVar4 = local_178;
      }
      if (fVar4 < local_174) {
        bVar13 = 2;
      }
      __ct__7CVectorFfff(*outVec,outVec[1],outVec[2],&local_188);
      pcVar8 = (char *)(param_10 + uVar10 * 4);
      *pcVar8 = -0x80;
      pcVar8[1] = -0x80;
      pcVar8[2] = -0x80;
      local_18c = (float)dVar14;
      local_190 = (float)dVar14;
      pcVar8[3] = -1;
      fVar6 = FLOAT_803318c0;
      fVar4 = FLOAT_803318bc;
      if (bVar13 == 1) {
        fVar6 = FLOAT_803318b8 * local_188.y;
        if (outVec[1] < FLOAT_80331898) {
          pcVar8[1] = pcVar8[1] + -0x7f;
          local_190 = (float)(dVar14 - (double)(local_188.x / fVar6)) * fVar4 + fVar4;
          local_18c = (float)((double)((float)(dVar14 + (double)(local_188.z / fVar6)) * fVar4) +
                             dVar14);
        }
        else {
          pcVar8[1] = pcVar8[1] + '\x7f';
          local_18c = (float)(dVar14 + (double)(local_188.z / fVar6)) * fVar4;
          local_190 = (float)((double)((float)(dVar14 + (double)(local_188.x / fVar6)) * fVar4) +
                             dVar14);
        }
      }
      else if (bVar13 == 0) {
        fVar5 = FLOAT_803318b8 * local_188.x;
        if (*outVec < FLOAT_80331898) {
          *pcVar8 = *pcVar8 + -0x7f;
          local_190 = (float)(dVar14 - (double)(local_188.z / fVar5)) * fVar4 + fVar6;
          local_18c = (float)(dVar14 + (double)(local_188.y / fVar5)) * fVar4 + fVar4;
        }
        else {
          *pcVar8 = *pcVar8 + '\x7f';
          local_190 = (float)(dVar14 - (double)(local_188.z / fVar5)) * fVar4 + fVar4;
          local_18c = (float)(dVar14 - (double)(local_188.y / fVar5)) * fVar4 + fVar4;
        }
      }
      else if (bVar13 < 3) {
        fVar6 = FLOAT_803318b8 * local_188.z;
        if (outVec[2] < FLOAT_80331898) {
          pcVar8[2] = pcVar8[2] + -0x7f;
          local_190 = (float)((double)((float)(dVar14 + (double)(local_188.x / fVar6)) * fVar4) +
                             dVar14);
          local_18c = (float)(dVar14 + (double)(local_188.y / fVar6)) * fVar4 + fVar4;
        }
        else {
          pcVar8[2] = pcVar8[2] + '\x7f';
          local_190 = (float)(dVar14 + (double)(local_188.x / fVar6)) * fVar4;
          local_18c = (float)(dVar14 - (double)(local_188.y / fVar6)) * fVar4 + fVar4;
        }
      }
      local_1a8 = local_190;
      local_1a4 = local_18c;
      ConvF2IVector2d__5CUtilFR8S16Vec2d5Vec2dl
                ((CUtil *)&DAT_8032ec70,(S16Vec2d *)(param_11 + (uint)uVar3 * 4),&local_1a8,0xc);
      param_8 = puVar11;
    }
  }
  DCFlushRange(param_1,param_4 * 0xc);
  DCFlushRange(param_11,param_4 << 3);
  return;
}

