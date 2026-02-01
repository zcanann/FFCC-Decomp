// Function: Calc__7CMapObjFv
// Entry: 80029538
// Size: 2016 bytes

void Calc__7CMapObjFv(int param_1)

{
  float *pfVar1;
  int iVar2;
  float *pfVar3;
  char cVar4;
  Vec *pVVar5;
  uint uVar6;
  char cVar7;
  char cVar8;
  Vec *vecA;
  Vec *vecB;
  Vec *pVVar9;
  int iVar10;
  float local_d8;
  int local_d4;
  int local_d0;
  undefined local_cc [2];
  byte bStack_ca;
  char cStack_c9;
  uint local_c8;
  float local_c4;
  int local_c0;
  int local_bc;
  undefined local_b8 [2];
  byte bStack_b6;
  char cStack_b5;
  uint local_b4;
  float local_b0;
  int local_ac;
  int local_a8;
  undefined local_a4 [2];
  byte bStack_a2;
  char cStack_a1;
  uint local_a0;
  float local_9c;
  int local_98;
  int local_94;
  undefined local_90 [2];
  byte bStack_8e;
  char cStack_8d;
  uint local_8c;
  int local_88;
  int local_84;
  float local_80;
  Vec local_7c;
  Vec VStack_70;
  Vec VStack_64;
  Mtx MStack_58;
  longlong local_28;
  
  if (*(short *)(param_1 + 0x2c) != 0) {
    *(short *)(param_1 + 0x28) = *(short *)(param_1 + 0x28) + *(short *)(param_1 + 0x2c);
    if (*(short *)(param_1 + 0x2c) < 1) {
      if (*(short *)(param_1 + 0x28) <= *(short *)(param_1 + 0x2a)) {
        *(short *)(param_1 + 0x28) = *(short *)(param_1 + 0x2a);
        *(undefined2 *)(param_1 + 0x2c) = 0;
      }
    }
    else if (*(short *)(param_1 + 0x2a) <= *(short *)(param_1 + 0x28)) {
      *(short *)(param_1 + 0x28) = *(short *)(param_1 + 0x2a);
      *(undefined2 *)(param_1 + 0x2c) = 0;
    }
    if (*(short *)(param_1 + 0x28) == 0) {
      *(undefined *)(param_1 + 0x15) = *(undefined *)(param_1 + 0x14);
    }
    else {
      *(undefined *)(param_1 + 0x15) = 2;
    }
  }
  if ((((*(char *)(param_1 + 0x1d) == '\x01') && (*(int *)(param_1 + 0xc) != 0)) &&
      (*(char *)(param_1 + 0x1f) == -1)) && ((*(byte *)(param_1 + 0x18) & 1) != 0)) {
    if ((FLOAT_8032f944 <= *(float *)(param_1 + 0x50)) ||
       (*(float *)(param_1 + 0x4c) < FLOAT_8032f948)) {
      local_7c.x = *(float *)(param_1 + 0xc4);
      local_7c.y = *(float *)(param_1 + 0xd4);
      local_7c.z = *(float *)(param_1 + 0xe4);
      PSMTXCopy(&CameraPcs.m_cameraMatrix,&MStack_58);
      PSMTXMultVec(&MStack_58,&local_7c,&VStack_70);
      VStack_70.z = -VStack_70.z;
      *(bool *)(param_1 + 0x25) = *(float *)(param_1 + 0x50) < VStack_70.z;
      if (*(float *)(param_1 + 0x4c) <= VStack_70.z) {
        *(undefined *)(param_1 + 0x26) = 1;
        *(undefined *)(param_1 + 0x15) = *(undefined *)(param_1 + 0x14);
      }
      else {
        *(undefined *)(param_1 + 0x26) = 1;
        *(undefined *)(param_1 + 0x15) = 2;
      }
    }
    else {
      *(undefined *)(param_1 + 0x15) = *(undefined *)(param_1 + 0x14);
      *(undefined *)(param_1 + 0x25) = 1;
      *(undefined *)(param_1 + 0x26) = 0;
    }
  }
  iVar10 = *(int *)(param_1 + 0xec);
  if (iVar10 != 0) {
    iVar2 = *(int *)(iVar10 + 4);
    if (iVar2 == 1) {
      iVar2 = IsRun__12CMapKeyFrameFv((CMapKeyFrame *)(iVar10 + 0xc0));
      if (iVar2 != 0) {
        iVar2 = Get__12CMapKeyFrameFRiRiRf
                          ((CMapKeyFrame *)(iVar10 + 0xc0),&local_c0,&local_bc,&local_c4);
        if (iVar2 == 0) {
          iVar2 = iVar10 + local_c0 * 4;
          *(undefined *)(iVar10 + 8) = *(undefined *)(iVar2 + 0x40);
          *(undefined *)(iVar10 + 9) = *(undefined *)(iVar2 + 0x41);
          *(undefined *)(iVar10 + 10) = *(undefined *)(iVar2 + 0x42);
          *(undefined *)(iVar10 + 0xb) = *(undefined *)(iVar2 + 0x43);
        }
        else {
          iVar2 = (int)(FLOAT_8032f94c * local_c4);
          local_28 = (longlong)iVar2;
          uVar6 = *(uint *)(iVar10 + local_c0 * 4 + 0x40);
          local_b4 = *(uint *)(iVar10 + local_bc * 4 + 0x40);
          local_b8[0] = (byte)(uVar6 >> 0x18);
          local_b8[1] = (byte)(uVar6 >> 0x10);
          bStack_b6 = (byte)(uVar6 >> 8);
          cStack_b5 = (char)uVar6;
          cVar8 = local_b8[0] + (char)(iVar2 * ((local_b4 >> 0x18) - (uint)local_b8[0]) >> 8);
          *(char *)(iVar10 + 8) = cVar8;
          cVar7 = local_b8[1] + (char)(iVar2 * ((local_b4 >> 0x10 & 0xff) - (uint)local_b8[1]) >> 8)
          ;
          *(char *)(iVar10 + 9) = cVar7;
          cVar4 = bStack_b6 + (char)(iVar2 * ((local_b4 >> 8 & 0xff) - (uint)bStack_b6) >> 8);
          *(char *)(iVar10 + 10) = cVar4;
          cStack_b5 = cStack_b5 + (char)(iVar2 * ((local_b4 & 0xff) - (uVar6 & 0xff)) >> 8);
          _local_b8 = CONCAT31(CONCAT21(CONCAT11(cVar8,cVar7),cVar4),cStack_b5);
          *(char *)(iVar10 + 0xb) = cStack_b5;
        }
        Calc__12CMapKeyFrameFv((CMapKeyFrame *)(iVar10 + 0xc0));
        if (*(char *)(iVar10 + 0x2f) != '\0') {
          *(undefined *)(iVar10 + 0xc) = *(undefined *)(iVar10 + 8);
          *(undefined *)(iVar10 + 0xd) = *(undefined *)(iVar10 + 9);
          *(undefined *)(iVar10 + 0xe) = *(undefined *)(iVar10 + 10);
          *(undefined *)(iVar10 + 0xf) = *(undefined *)(iVar10 + 0xb);
        }
      }
      iVar2 = IsRun__12CMapKeyFrameFv((CMapKeyFrame *)(iVar10 + 0xe8));
      if (iVar2 != 0) {
        iVar2 = Get__12CMapKeyFrameFRiRiRf
                          ((CMapKeyFrame *)(iVar10 + 0xe8),&local_d4,&local_d0,&local_d8);
        if (iVar2 == 0) {
          iVar2 = iVar10 + local_d4 * 4;
          *(undefined *)(iVar10 + 8) = *(undefined *)(iVar2 + 0x40);
          *(undefined *)(iVar10 + 9) = *(undefined *)(iVar2 + 0x41);
          *(undefined *)(iVar10 + 10) = *(undefined *)(iVar2 + 0x42);
          *(undefined *)(iVar10 + 0xb) = *(undefined *)(iVar2 + 0x43);
        }
        else {
          iVar2 = (int)(FLOAT_8032f94c * local_d8);
          local_28 = (longlong)iVar2;
          uVar6 = *(uint *)(iVar10 + local_d4 * 4 + 0x40);
          local_c8 = *(uint *)(iVar10 + local_d0 * 4 + 0x40);
          local_cc[0] = (byte)(uVar6 >> 0x18);
          local_cc[1] = (byte)(uVar6 >> 0x10);
          bStack_ca = (byte)(uVar6 >> 8);
          cStack_c9 = (char)uVar6;
          cVar8 = local_cc[0] + (char)(iVar2 * ((local_c8 >> 0x18) - (uint)local_cc[0]) >> 8);
          *(char *)(iVar10 + 8) = cVar8;
          cVar7 = local_cc[1] + (char)(iVar2 * ((local_c8 >> 0x10 & 0xff) - (uint)local_cc[1]) >> 8)
          ;
          *(char *)(iVar10 + 9) = cVar7;
          cVar4 = bStack_ca + (char)(iVar2 * ((local_c8 >> 8 & 0xff) - (uint)bStack_ca) >> 8);
          *(char *)(iVar10 + 10) = cVar4;
          cStack_c9 = cStack_c9 + (char)(iVar2 * ((local_c8 & 0xff) - (uVar6 & 0xff)) >> 8);
          _local_cc = CONCAT31(CONCAT21(CONCAT11(cVar8,cVar7),cVar4),cStack_c9);
          *(char *)(iVar10 + 0xb) = cStack_c9;
        }
        Calc__12CMapKeyFrameFv((CMapKeyFrame *)(iVar10 + 0xe8));
      }
    }
    else if (iVar2 < 1) {
      if (-1 < iVar2) {
        iVar2 = IsRun__12CMapKeyFrameFv((CMapKeyFrame *)(iVar10 + 0xa4));
        if (iVar2 != 0) {
          iVar2 = Get__12CMapKeyFrameFRiRiRf
                            ((CMapKeyFrame *)(iVar10 + 0xa4),&local_98,&local_94,&local_9c);
          if (iVar2 == 0) {
            iVar2 = iVar10 + local_98 * 4;
            *(undefined *)(iVar10 + 8) = *(undefined *)(iVar2 + 0x24);
            *(undefined *)(iVar10 + 9) = *(undefined *)(iVar2 + 0x25);
            *(undefined *)(iVar10 + 10) = *(undefined *)(iVar2 + 0x26);
            *(undefined *)(iVar10 + 0xb) = *(undefined *)(iVar2 + 0x27);
          }
          else {
            iVar2 = (int)(FLOAT_8032f94c * local_9c);
            local_28 = (longlong)iVar2;
            uVar6 = *(uint *)(iVar10 + local_98 * 4 + 0x24);
            local_8c = *(uint *)(iVar10 + local_94 * 4 + 0x24);
            local_90[0] = (byte)(uVar6 >> 0x18);
            local_90[1] = (byte)(uVar6 >> 0x10);
            bStack_8e = (byte)(uVar6 >> 8);
            cStack_8d = (char)uVar6;
            cVar8 = local_90[0] + (char)(iVar2 * ((local_8c >> 0x18) - (uint)local_90[0]) >> 8);
            *(char *)(iVar10 + 8) = cVar8;
            cVar7 = local_90[1] +
                    (char)(iVar2 * ((local_8c >> 0x10 & 0xff) - (uint)local_90[1]) >> 8);
            *(char *)(iVar10 + 9) = cVar7;
            cVar4 = bStack_8e + (char)(iVar2 * ((local_8c >> 8 & 0xff) - (uint)bStack_8e) >> 8);
            *(char *)(iVar10 + 10) = cVar4;
            cStack_8d = cStack_8d + (char)(iVar2 * ((local_8c & 0xff) - (uVar6 & 0xff)) >> 8);
            _local_90 = CONCAT31(CONCAT21(CONCAT11(cVar8,cVar7),cVar4),cStack_8d);
            *(char *)(iVar10 + 0xb) = cStack_8d;
          }
          Calc__12CMapKeyFrameFv((CMapKeyFrame *)(iVar10 + 0xa4));
          if (*(char *)(iVar10 + 0x1f) != '\0') {
            *(undefined *)(iVar10 + 0xc) = *(undefined *)(iVar10 + 8);
            *(undefined *)(iVar10 + 0xd) = *(undefined *)(iVar10 + 9);
            *(undefined *)(iVar10 + 0xe) = *(undefined *)(iVar10 + 10);
            *(undefined *)(iVar10 + 0xf) = *(undefined *)(iVar10 + 0xb);
          }
        }
        iVar2 = IsRun__12CMapKeyFrameFv((CMapKeyFrame *)(iVar10 + 0xcc));
        if (iVar2 != 0) {
          iVar2 = Get__12CMapKeyFrameFRiRiRf
                            ((CMapKeyFrame *)(iVar10 + 0xcc),&local_ac,&local_a8,&local_b0);
          if (iVar2 == 0) {
            iVar2 = iVar10 + local_ac * 4;
            *(undefined *)(iVar10 + 8) = *(undefined *)(iVar2 + 0x24);
            *(undefined *)(iVar10 + 9) = *(undefined *)(iVar2 + 0x25);
            *(undefined *)(iVar10 + 10) = *(undefined *)(iVar2 + 0x26);
            *(undefined *)(iVar10 + 0xb) = *(undefined *)(iVar2 + 0x27);
          }
          else {
            iVar2 = (int)(FLOAT_8032f94c * local_b0);
            local_28 = (longlong)iVar2;
            uVar6 = *(uint *)(iVar10 + local_ac * 4 + 0x24);
            local_a0 = *(uint *)(iVar10 + local_a8 * 4 + 0x24);
            local_a4[0] = (byte)(uVar6 >> 0x18);
            local_a4[1] = (byte)(uVar6 >> 0x10);
            bStack_a2 = (byte)(uVar6 >> 8);
            cStack_a1 = (char)uVar6;
            cVar8 = local_a4[0] + (char)(iVar2 * ((local_a0 >> 0x18) - (uint)local_a4[0]) >> 8);
            *(char *)(iVar10 + 8) = cVar8;
            cVar7 = local_a4[1] +
                    (char)(iVar2 * ((local_a0 >> 0x10 & 0xff) - (uint)local_a4[1]) >> 8);
            *(char *)(iVar10 + 9) = cVar7;
            cVar4 = bStack_a2 + (char)(iVar2 * ((local_a0 >> 8 & 0xff) - (uint)bStack_a2) >> 8);
            *(char *)(iVar10 + 10) = cVar4;
            cStack_a1 = cStack_a1 + (char)(iVar2 * ((local_a0 & 0xff) - (uVar6 & 0xff)) >> 8);
            _local_a4 = CONCAT31(CONCAT21(CONCAT11(cVar8,cVar7),cVar4),cStack_a1);
            *(char *)(iVar10 + 0xb) = cStack_a1;
          }
          Calc__12CMapKeyFrameFv((CMapKeyFrame *)(iVar10 + 0xcc));
        }
      }
    }
    else if ((iVar2 < 3) &&
            (iVar2 = IsRun__12CMapKeyFrameFv((CMapKeyFrame *)(iVar10 + 0x14)), iVar2 != 0)) {
      pVVar9 = *(Vec **)(*(int *)(param_1 + 0xc) + 0x2c);
      iVar2 = Get__12CMapKeyFrameFRiRiRf
                        ((CMapKeyFrame *)(iVar10 + 0x14),&local_84,&local_88,&local_80);
      if (iVar2 == 0) {
        pfVar3 = *(float **)(*(int *)(iVar10 + 0xc) + local_84 * 4);
        pVVar5 = pVVar9;
        for (iVar2 = 0; iVar2 < *(int *)(iVar10 + 0x10); iVar2 = iVar2 + 1) {
          pVVar5->x = *pfVar3;
          pVVar5->y = pfVar3[1];
          pfVar1 = pfVar3 + 2;
          pfVar3 = pfVar3 + 3;
          pVVar5->z = *pfVar1;
          pVVar5 = pVVar5 + 1;
        }
      }
      else {
        vecB = *(Vec **)(*(int *)(iVar10 + 0xc) + local_84 * 4);
        vecA = *(Vec **)(*(int *)(iVar10 + 0xc) + local_88 * 4);
        pVVar5 = pVVar9;
        for (iVar2 = 0; iVar2 < *(int *)(iVar10 + 0x10); iVar2 = iVar2 + 1) {
          PSVECSubtract(vecA,vecB,&VStack_64);
          PSVECScale(local_80,&VStack_64,&VStack_64);
          PSVECAdd(vecB,&VStack_64,pVVar5);
          vecB = vecB + 1;
          vecA = vecA + 1;
          pVVar5 = pVVar5 + 1;
        }
      }
      DCFlushRange(pVVar9,*(int *)(iVar10 + 0x10) * 0xc);
      Calc__12CMapKeyFrameFv((CMapKeyFrame *)(iVar10 + 0x14));
    }
  }
  return;
}

