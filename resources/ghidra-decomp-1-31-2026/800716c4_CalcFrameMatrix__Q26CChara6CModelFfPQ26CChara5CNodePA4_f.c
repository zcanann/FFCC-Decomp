// Function: CalcFrameMatrix__Q26CChara6CModelFfPQ26CChara5CNodePA4_f
// Entry: 800716c4
// Size: 1184 bytes

/* WARNING: Removing unreachable block (ram,0x80071b48) */
/* WARNING: Removing unreachable block (ram,0x80071b40) */
/* WARNING: Removing unreachable block (ram,0x800716dc) */
/* WARNING: Removing unreachable block (ram,0x800716d4) */

void CalcFrameMatrix__Q26CChara6CModelFfPQ26CChara5CNodePA4_f
               (undefined8 param_1,int param_2,int *param_3,Mtx *param_4)

{
  float xS;
  short sVar1;
  bool bVar2;
  bool bVar3;
  int iVar4;
  uint uVar5;
  Mtx *source;
  int *piVar6;
  double alpha;
  Vec VStack_1a8;
  Vec VStack_19c;
  Vec VStack_190;
  Vec VStack_184;
  Vec local_178;
  Vec local_16c;
  Quat QStack_160;
  Mtx MStack_150;
  Mtx MStack_120;
  Mtx MStack_f0;
  undefined4 local_c0;
  undefined4 local_bc;
  undefined4 local_b8;
  undefined4 local_b4;
  undefined4 local_b0;
  undefined4 local_ac;
  float local_a8;
  float local_a4;
  float local_a0;
  undefined4 local_9c;
  undefined4 local_98;
  undefined4 local_94;
  undefined4 local_90;
  undefined4 local_8c;
  undefined4 local_88;
  float local_84;
  float local_80;
  float local_7c;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  float local_60;
  float local_5c;
  float local_58;
  undefined4 local_50;
  uint uStack_4c;
  undefined4 local_48;
  uint uStack_44;
  
  if (*(int *)(param_2 + 0xd0) != 0) {
    InitQuantize__Q26CChara5CAnimFv();
  }
  PSMTXIdentity(param_4);
  bVar2 = false;
  while (param_3 != (int *)0x0) {
    source = (Mtx *)*param_3;
    sVar1 = *(short *)(source[2].value[0] + 2);
    if (sVar1 < 0) {
      piVar6 = (int *)0x0;
    }
    else {
      piVar6 = (int *)(*(int *)(param_2 + 0xa8) + sVar1 * 0xc0);
    }
    bVar3 = false;
    local_9c = local_78;
    local_98 = local_74;
    local_94 = local_70;
    local_90 = local_6c;
    local_8c = local_68;
    local_88 = local_64;
    local_84 = local_60;
    local_80 = local_5c;
    local_7c = local_58;
    if ((param_3[0x27] == 0) && (param_3[0x28] == 0)) {
      PSMTXCopy(source,&MStack_120);
    }
    else {
      if ((piVar6 == (int *)0x0) ||
         ((iVar4 = piVar6[0x27], iVar4 == 0 || (-1 < *(char *)(iVar4 + 0x14))))) {
        if ((piVar6 == (int *)0x0) &&
           (xS = *(float *)(*(int *)(param_2 + 0xa4) + 0x28), FLOAT_803301bc != xS)) {
          PSMTXScale(xS,xS,xS,&MStack_120);
        }
        else {
          PSMTXIdentity(&MStack_120);
        }
      }
      else {
        Interp__Q26CChara9CAnimNodeFPQ26CChara5CAnimP3SRTf
                  (param_1,iVar4,*(undefined4 *)(param_2 + 0xd0),&local_78);
        bVar3 = true;
        PSMTXScale(FLOAT_803301bc / local_60,FLOAT_803301bc / local_5c,FLOAT_803301bc / local_58,
                   &MStack_120);
      }
      if (*(char *)((int)source[2].value[2] + 0xf) != '\0') {
        MStack_120.value[0][3] = *(float *)(*piVar6 + 0x60);
      }
      if (param_3[0x28] != 0) {
        Interp__Q26CChara9CAnimNodeFPQ26CChara5CAnimP3SRTf
                  (param_1,param_3[0x28],*(undefined4 *)(param_2 + 0xd0),&local_c0);
        if (*(char *)(param_3[0x28] + 0x14) < '\0') {
          SRTToMatrix__5CMathFPA4_fP3SRT(&Math,&MStack_f0,&local_c0);
        }
        else {
          SRTToMatrixRT__5CMathFPA4_fP3SRT(&Math,&MStack_f0,&local_c0);
        }
        PSMTXConcat(&MStack_120,&MStack_f0,&MStack_120);
        PSMTXScale(FLOAT_803301bc / local_a8,FLOAT_803301bc / local_a4,FLOAT_803301bc / local_a0,
                   &MStack_f0);
        PSMTXConcat(&MStack_120,&MStack_f0,&MStack_120);
      }
      if (param_3[0x27] != 0) {
        if (bVar2) {
          local_c0 = local_9c;
          local_bc = local_98;
          local_b8 = local_94;
          local_b4 = local_90;
          local_b0 = local_8c;
          local_ac = local_88;
          local_a8 = local_84;
          local_a4 = local_80;
          local_a0 = local_7c;
        }
        else {
          Interp__Q26CChara9CAnimNodeFPQ26CChara5CAnimP3SRTf
                    (param_1,param_3[0x27],*(undefined4 *)(param_2 + 0xd0),&local_c0);
        }
        if (*(char *)(param_3[0x27] + 0x14) < '\0') {
          SRTToMatrix__5CMathFPA4_fP3SRT(&Math,&MStack_f0,&local_c0);
        }
        else {
          SRTToMatrixRT__5CMathFPA4_fP3SRT(&Math,&MStack_f0,&local_c0);
        }
        PSMTXConcat(&MStack_120,&MStack_f0,&MStack_120);
      }
    }
    bVar2 = bVar3;
    uVar5 = (uint)*(ushort *)(param_2 + 0xd8);
    if (uVar5 != 0) {
      uStack_44 = (uint)*(ushort *)(param_2 + 0xda);
      local_48 = 0x43300000;
      local_50 = 0x43300000;
      local_16c.z = MStack_120.value[2][3];
      local_16c.x = MStack_120.value[0][3];
      local_16c.y = MStack_120.value[1][3];
      alpha = -(double)((float)((double)CONCAT44(0x43300000,uVar5) - DOUBLE_803301f0) *
                        (FLOAT_803301bc /
                        (float)((double)CONCAT44(0x43300000,uStack_44) - DOUBLE_803301f0)) -
                       FLOAT_803301bc);
      uStack_4c = uVar5;
      MTXGetScale__5CMathFPA4_fP3Vec(&Math,&MStack_120,&local_178);
      if (FLOAT_803301e4 <= local_178.x) {
        PSVECScale((float)((double)FLOAT_803301bc - alpha),(Vec *)(param_3 + 0x18),&VStack_190);
        PSVECScale((float)alpha,&local_178,&VStack_184);
        PSVECAdd(&VStack_190,&VStack_184,&local_178);
      }
      else {
        local_178.y = FLOAT_803301e8;
        local_178.z = FLOAT_803301e8;
      }
      PSVECScale((float)((double)FLOAT_803301bc - alpha),(Vec *)(param_3 + 0x15),&VStack_1a8);
      PSVECScale((float)alpha,&local_16c,&VStack_19c);
      PSVECAdd(&VStack_1a8,&VStack_19c,&local_16c);
      C_QUATMtx(&QStack_160,&MStack_120);
      C_QUATSlerp(alpha,(Quat *)(param_3 + 0x11),&QStack_160,&QStack_160);
      PSMTXScale(local_178.x,local_178.y,local_178.z,&MStack_150);
      PSMTXQuat(&MStack_120,&QStack_160);
      PSMTXConcat(&MStack_120,&MStack_150,&MStack_120);
      MStack_120.value[0][3] = local_16c.x;
      MStack_120.value[1][3] = local_16c.y;
      MStack_120.value[2][3] = local_16c.z;
    }
    PSMTXConcat(&MStack_120,param_4,param_4);
    param_3 = piVar6;
  }
  PSMTXConcat((Mtx *)(param_2 + 8),param_4,param_4);
  return;
}

