// Function: MakeLightMap__Q29CLightPcs10CBumpLightFv
// Entry: 80048644
// Size: 1656 bytes

/* WARNING: Removing unreachable block (ram,0x80048ca0) */
/* WARNING: Removing unreachable block (ram,0x80048c98) */
/* WARNING: Removing unreachable block (ram,0x80048c90) */
/* WARNING: Removing unreachable block (ram,0x80048c88) */
/* WARNING: Removing unreachable block (ram,0x80048c80) */
/* WARNING: Removing unreachable block (ram,0x80048c78) */
/* WARNING: Removing unreachable block (ram,0x8004867c) */
/* WARNING: Removing unreachable block (ram,0x80048674) */
/* WARNING: Removing unreachable block (ram,0x8004866c) */
/* WARNING: Removing unreachable block (ram,0x80048664) */
/* WARNING: Removing unreachable block (ram,0x8004865c) */
/* WARNING: Removing unreachable block (ram,0x80048654) */

void MakeLightMap__Q29CLightPcs10CBumpLightFv(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  undefined uVar5;
  undefined uVar6;
  undefined uVar7;
  undefined uVar8;
  undefined4 uVar9;
  uint uVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  uint uVar14;
  int iVar15;
  float *pfVar16;
  int iVar17;
  int iVar18;
  double dVar19;
  double dVar20;
  double dVar21;
  double dVar22;
  double dVar23;
  double dVar24;
  double dVar25;
  double dVar26;
  double dVar27;
  double dVar28;
  double dVar29;
  undefined4 local_1f0;
  undefined4 local_1ec;
  undefined4 local_1e8;
  undefined4 local_1e4;
  undefined4 local_1e0;
  undefined4 local_1dc;
  undefined4 local_1d8;
  undefined4 local_1d4;
  undefined4 local_1d0;
  undefined4 local_1cc;
  Vec VStack_1c8;
  Vec VStack_1bc;
  Vec VStack_1b0;
  Vec local_1a4;
  float local_198;
  float local_194;
  float local_190;
  Vec local_18c;
  Vec local_180;
  undefined auStack_174 [64];
  Mtx MStack_134;
  Mtx MStack_104;
  Mtx MStack_d4;
  undefined4 local_a0;
  uint uStack_9c;
  undefined4 local_98;
  int iStack_94;
  
  if (*(int *)(param_1 + 0xb4) != 0) {
    uVar5 = *(undefined *)(param_1 + 0x68);
    uVar6 = *(undefined *)(param_1 + 0x69);
    uVar7 = *(undefined *)(param_1 + 0x6a);
    uVar8 = *(undefined *)(param_1 + 0x6b);
    local_1d0 = CONCAT13(uVar5,CONCAT12(uVar5,CONCAT11(uVar5,uVar5)));
    local_1cc = DAT_8032fc0c;
    local_1d4 = CONCAT13(uVar6,CONCAT12(uVar6,CONCAT11(uVar6,uVar6)));
    local_1d8 = CONCAT13(uVar7,CONCAT12(uVar7,CONCAT11(uVar7,uVar7)));
    local_1dc = CONCAT13(uVar8,CONCAT12(uVar8,CONCAT11(uVar8,uVar8)));
    local_1e0 = local_1d0;
    GXSetChanAmbColor(0,&local_1e0);
    local_1e4 = local_1d4;
    GXSetChanMatColor(0,&local_1e4);
    local_1e8 = local_1d8;
    GXSetChanAmbColor(2,&local_1e8);
    local_1ec = local_1dc;
    GXSetChanMatColor(2,&local_1ec);
    if (*(char *)(param_1 + 0xb1) == '\x01') {
      PSMTXIdentity(&MStack_d4);
      PSMTXTrans(FLOAT_8032fc14,FLOAT_8032fc14,FLOAT_8032fc34,&MStack_d4);
      GXLoadPosMtxImm(&MStack_d4,0);
      PSMTXIdentity(&MStack_d4);
      GXLoadNrmMtxImm(&MStack_d4,0);
      local_18c.z = FLOAT_8032fc14;
      local_18c.y = FLOAT_8032fc14;
      local_18c.x = FLOAT_8032fc14;
      local_198 = FLOAT_8032fc14;
      local_194 = FLOAT_8032fc1c;
      local_190 = FLOAT_8032fc14;
      C_MTXLookAt(&MStack_104,&local_18c,&local_198,(Vec *)(param_1 + 0x38));
      local_1a4.x = (float)CameraPcs._224_4_;
      local_1a4.y = (float)CameraPcs._228_4_;
      local_1a4.z = (float)CameraPcs._232_4_;
      PSVECSubtract((Vec *)(param_1 + 0x10),&local_1a4,&VStack_1b0);
      PSVECNormalize(&VStack_1b0,&VStack_1b0);
      PSVECNormalize((Vec *)(param_1 + 0x38),&VStack_1bc);
      PSVECSubtract(&VStack_1b0,&VStack_1bc,&VStack_1c8);
      fVar1 = FLOAT_8032fc1c;
      if (*(char *)(param_1 + 0xb2) == '\x01') {
        fVar1 = FLOAT_8032fc38;
      }
      PSVECScale(fVar1,&VStack_1c8,&VStack_1c8);
      PSVECAdd(&VStack_1bc,&VStack_1c8,&VStack_1bc);
      PSVECNormalize(&VStack_1bc,&VStack_1bc);
      PSMTXMultVecSR(&MStack_104,&VStack_1bc,&local_180);
    }
    else {
      PSMTXIdentity(&MStack_134);
      GXLoadPosMtxImm(&MStack_134,0);
      GXLoadNrmMtxImm(&MStack_134,0);
      local_180.x = *(float *)(param_1 + 0x38);
      local_180.y = *(float *)(param_1 + 0x3c);
      local_180.z = *(float *)(param_1 + 0x40);
    }
    iVar13 = GXGetTexBufferSize(0x40,0x40,3,0,0);
    uVar9 = local_1cc;
    dVar24 = (double)FLOAT_8032fc40;
    dVar25 = (double)FLOAT_8032fc1c;
    pfVar16 = (float *)&DAT_801ea430;
    dVar26 = (double)FLOAT_8032fc3c;
    dVar28 = (double)FLOAT_8032fc44;
    iVar17 = 0;
    dVar29 = (double)FLOAT_8032fc60;
    dVar27 = DOUBLE_8032fc68;
    for (iVar15 = 0; iVar15 < (int)(uint)*(byte *)(param_1 + 0xb3); iVar15 = iVar15 + 1) {
      iVar11 = *(int *)(param_1 + 0xb4);
      GXInitSpecularDir((double)local_180.x,(double)local_180.y,(double)local_180.z,auStack_174);
      local_1f0 = uVar9;
      GXInitLightColor(auStack_174,&local_1f0);
      if (*(char *)(param_1 + 0xb2) == '\x01') {
        dVar19 = (double)FLOAT_8032fc14;
        dVar21 = (double)(*(float *)(param_1 + 0x48) * FLOAT_8032fc18);
        GXInitLightAttn(dVar19,dVar19,(double)FLOAT_8032fc1c,dVar21,dVar19,
                        (double)(float)((double)FLOAT_8032fc1c - dVar21),auStack_174);
      }
      else {
        dVar19 = (double)FLOAT_8032fc14;
        GXInitLightAttn(dVar19,dVar19,(double)FLOAT_8032fc1c,(double)(*pfVar16 * FLOAT_8032fc18),
                        dVar19,(double)(float)((double)FLOAT_8032fc1c -
                                              (double)(*pfVar16 * FLOAT_8032fc18)),auStack_174);
      }
      GXLoadLightObjImm(auStack_174,1);
      uVar10 = 0;
      do {
        uVar14 = uVar10;
        GXBegin(0x98,0,0x42);
        local_a0 = 0x43300000;
        fVar1 = (float)((double)(float)(dVar26 * (double)(float)((double)CONCAT44(0x43300000,uVar14)
                                                                - dVar27)) * dVar24 - dVar25);
        dVar19 = (double)fVar1;
        fVar2 = (float)((double)(float)(dVar26 * (double)(float)((double)CONCAT44(0x43300000,
                                                                                  uVar14 + 1) -
                                                                dVar27)) * dVar24 - dVar25);
        dVar21 = (double)fVar2;
        iVar18 = 0x21;
        iVar12 = 0;
        do {
          iStack_94 = iVar12;
          local_98 = 0x43300000;
          fVar3 = (float)((double)(float)(dVar26 * (double)(float)((double)CONCAT44(0x43300000,
                                                                                    iStack_94) -
                                                                  dVar27)) * dVar24 - dVar25);
          dVar20 = (double)fVar3;
          dVar22 = (double)(float)(dVar19 * dVar19 + (double)(float)(dVar20 * dVar20));
          if (dVar25 <= dVar22) {
            dVar22 = (double)FLOAT_8032fc14;
          }
          else {
            fVar4 = (float)(dVar25 - dVar22);
            dVar22 = (double)fVar4;
            if (dVar22 <= (double)FLOAT_8032fc14) {
              if (DOUBLE_8032fc58 <= dVar22) {
                uVar10 = (uint)fVar4 & 0x7f800000;
                if (uVar10 == 0x7f800000) {
                  if (((uint)fVar4 & 0x7fffff) == 0) {
                    iVar12 = 2;
                  }
                  else {
                    iVar12 = 1;
                  }
                }
                else if ((uVar10 < 0x7f800000) && (uVar10 == 0)) {
                  if (((uint)fVar4 & 0x7fffff) == 0) {
                    iVar12 = 3;
                  }
                  else {
                    iVar12 = 5;
                  }
                }
                else {
                  iVar12 = 4;
                }
                if (iVar12 == 1) {
                  dVar22 = (double)DAT_8032ec20;
                }
              }
              else {
                dVar22 = (double)DAT_8032ec20;
              }
            }
            else {
              dVar23 = 1.0 / SQRT(dVar22);
              dVar23 = DOUBLE_8032fc48 * dVar23 * -(dVar22 * dVar23 * dVar23 - DOUBLE_8032fc50);
              dVar23 = DOUBLE_8032fc48 * dVar23 * -(dVar22 * dVar23 * dVar23 - DOUBLE_8032fc50);
              dVar22 = (double)(float)(dVar22 * DOUBLE_8032fc48 * dVar23 *
                                                -(dVar22 * dVar23 * dVar23 - DOUBLE_8032fc50));
            }
          }
          DAT_cc008000 = fVar1;
          dVar23 = (double)(float)(dVar21 * dVar21 + (double)(float)(dVar20 * dVar20));
          DAT_cc008000 = fVar3;
          DAT_cc008000 = (float)dVar29;
          DAT_cc008000 = (float)(dVar19 / dVar28);
          DAT_cc008000 = (float)(dVar20 / dVar28);
          DAT_cc008000 = (float)dVar22;
          if (dVar25 <= dVar23) {
            dVar22 = (double)FLOAT_8032fc14;
          }
          else {
            fVar4 = (float)(dVar25 - dVar23);
            dVar22 = (double)fVar4;
            if (dVar22 <= (double)FLOAT_8032fc14) {
              if (DOUBLE_8032fc58 <= dVar22) {
                uVar10 = (uint)fVar4 & 0x7f800000;
                if (uVar10 == 0x7f800000) {
                  if (((uint)fVar4 & 0x7fffff) == 0) {
                    iVar12 = 2;
                  }
                  else {
                    iVar12 = 1;
                  }
                }
                else if ((uVar10 < 0x7f800000) && (uVar10 == 0)) {
                  if (((uint)fVar4 & 0x7fffff) == 0) {
                    iVar12 = 3;
                  }
                  else {
                    iVar12 = 5;
                  }
                }
                else {
                  iVar12 = 4;
                }
                if (iVar12 == 1) {
                  dVar22 = (double)DAT_8032ec20;
                }
              }
              else {
                dVar22 = (double)DAT_8032ec20;
              }
            }
            else {
              dVar23 = 1.0 / SQRT(dVar22);
              dVar23 = DOUBLE_8032fc48 * dVar23 * -(dVar22 * dVar23 * dVar23 - DOUBLE_8032fc50);
              dVar23 = DOUBLE_8032fc48 * dVar23 * -(dVar22 * dVar23 * dVar23 - DOUBLE_8032fc50);
              dVar22 = (double)(float)(dVar22 * DOUBLE_8032fc48 * dVar23 *
                                                -(dVar22 * dVar23 * dVar23 - DOUBLE_8032fc50));
            }
          }
          DAT_cc008000 = fVar2;
          DAT_cc008000 = fVar3;
          DAT_cc008000 = (float)dVar29;
          DAT_cc008000 = (float)(dVar21 / dVar28);
          DAT_cc008000 = (float)(dVar20 / dVar28);
          DAT_cc008000 = (float)dVar22;
          iVar18 = iVar18 + -1;
          iVar12 = iStack_94 + 1;
        } while (iVar18 != 0);
        uVar10 = uVar14 + 1;
        uStack_9c = uVar14;
      } while (uVar14 + 1 < 0x20);
      GXSetTexCopySrc(0,0,0x40,0x40);
      GXSetTexCopyDst(0x40,0x40,3,0);
      GXCopyTex(iVar11 + iVar17,1);
      GXPixModeSync();
      iVar17 = iVar17 + iVar13;
      pfVar16 = pfVar16 + 1;
    }
  }
  return;
}

