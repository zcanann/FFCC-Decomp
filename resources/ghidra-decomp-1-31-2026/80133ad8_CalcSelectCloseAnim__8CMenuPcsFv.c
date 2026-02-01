// Function: CalcSelectCloseAnim__8CMenuPcsFv
// Entry: 80133ad8
// Size: 3172 bytes

void CalcSelectCloseAnim__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  double dVar1;
  float fVar2;
  double dVar3;
  double dVar4;
  float fVar5;
  float fVar6;
  double dVar7;
  double dVar8;
  double dVar9;
  short *psVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  short *psVar16;
  int iVar17;
  int iVar18;
  int iVar19;
  Vec local_168;
  Vec local_15c;
  Mtx MStack_150;
  Mtx MStack_120;
  Mtx MStack_f0;
  Mtx MStack_c0;
  undefined8 local_90;
  undefined8 local_88;
  undefined8 local_80;
  undefined8 local_78;
  longlong local_70;
  longlong local_68;
  undefined4 local_60;
  uint uStack_5c;
  longlong local_58;
  undefined4 local_50;
  uint uStack_4c;
  longlong local_48;
  undefined4 local_40;
  uint uStack_3c;
  
  fVar2 = FLOAT_80331eb0;
  iVar19 = *DAT_8032eea8;
  if (*(char *)(*(int *)&menuPcs->field_0x82c + 0xb) == '\0') {
    **(short **)&menuPcs->field_0x84c = **(short **)&menuPcs->field_0x84c + -1;
    iVar12 = 0;
    for (iVar13 = 0; psVar10 = *(short **)&menuPcs->field_0x84c, iVar13 < *psVar10;
        iVar13 = iVar13 + 1) {
      *(float *)((int)psVar10 + iVar12 + 0x18) = fVar2;
      *(undefined4 *)((int)psVar10 + iVar12 + 0x28) = 0;
      *(undefined4 *)((int)psVar10 + iVar12 + 0x34) = 0;
      iVar12 = iVar12 + 0x40;
    }
    iVar13 = 0;
    psVar10[0x12] = 0;
    psVar10[0x13] = 0x16;
    psVar10[0x16] = 0;
    psVar10[0x17] = 8;
    psVar10[0x18] = 0;
    fVar5 = FLOAT_80331eb0;
    psVar10[0x19] = 8;
    iVar12 = *(int *)&menuPcs->field_0x84c;
    *(undefined4 *)(iVar12 + 0x6c) = 0;
    fVar6 = FLOAT_80331ed0;
    *(undefined4 *)(iVar12 + 0x70) = 8;
    fVar2 = FLOAT_80331eac;
    *(undefined4 *)(iVar12 + 0x74) = 2;
    dVar1 = DOUBLE_80331e88;
    iVar12 = *(int *)&menuPcs->field_0x84c;
    *(undefined4 *)(iVar12 + 0xa4) = 0x1f;
    *(undefined4 *)(iVar12 + 0xac) = 0;
    *(undefined4 *)(iVar12 + 0xb0) = 0;
    *(undefined4 *)(iVar12 + 0xb4) = 2;
    iVar12 = *(int *)&menuPcs->field_0x84c;
    *(undefined4 *)(iVar12 + 0xe4) = 0xfffffffc;
    *(undefined4 *)(iVar12 + 0xec) = 0;
    *(undefined4 *)(iVar12 + 0xf0) = 8;
    iVar12 = iVar19;
    if (0 < iVar19) {
      do {
        psVar10 = (short *)(*(int *)&menuPcs->field_0x84c + (iVar13 + 4) * 0x40 + 8);
        iVar13 = iVar13 + 1;
        psVar10[0x12] = 0;
        psVar10[0x13] = 0;
        psVar10[0x14] = 0;
        psVar10[0x15] = 8;
        *(float *)(psVar10 + 10) = fVar5;
        local_90 = (double)(longlong)(int)*(float *)(psVar10 + 0x1c);
        *psVar10 = (short)(int)*(float *)(psVar10 + 0x1c);
        local_88 = (double)(longlong)(int)*(float *)(psVar10 + 0x1e);
        psVar10[1] = (short)(int)*(float *)(psVar10 + 0x1e);
        *(float *)(psVar10 + 0x18) = fVar6;
        *(float *)(psVar10 + 0x1a) = fVar2;
        local_80 = (double)(CONCAT44(0x43300000,(int)*psVar10) ^ 0x80000000);
        *(float *)(psVar10 + 0x1c) = (float)(local_80 - dVar1) + *(float *)(psVar10 + 0x18);
        local_78 = (double)(CONCAT44(0x43300000,(int)psVar10[1]) ^ 0x80000000);
        *(float *)(psVar10 + 0x1e) = (float)(local_78 - dVar1) + *(float *)(psVar10 + 0x1a);
        iVar12 = iVar12 + -1;
      } while (iVar12 != 0);
    }
    fVar5 = FLOAT_80331ed0;
    fVar2 = FLOAT_80331eac;
    dVar1 = DOUBLE_80331e88;
    iVar13 = iVar19 + 4;
    DAT_8032eeae = (char)iVar13;
    iVar14 = 0;
    iVar12 = iVar19;
    if (0 < iVar19) {
      do {
        psVar10 = (short *)(*(int *)&menuPcs->field_0x84c + (iVar13 + iVar14) * 0x40 + 8);
        iVar14 = iVar14 + 1;
        psVar10[0x12] = 0;
        psVar10[0x13] = 0;
        psVar10[0x14] = 0;
        psVar10[0x15] = 8;
        local_78 = (double)(longlong)(int)*(float *)(psVar10 + 0x1c);
        *psVar10 = (short)(int)*(float *)(psVar10 + 0x1c);
        local_80 = (double)(longlong)(int)*(float *)(psVar10 + 0x1e);
        psVar10[1] = (short)(int)*(float *)(psVar10 + 0x1e);
        *(float *)(psVar10 + 0x18) = fVar5;
        *(float *)(psVar10 + 0x1a) = fVar2;
        local_88 = (double)(CONCAT44(0x43300000,(int)*psVar10) ^ 0x80000000);
        *(float *)(psVar10 + 0x1c) = (float)(local_88 - dVar1) + *(float *)(psVar10 + 0x18);
        local_90 = (double)(CONCAT44(0x43300000,(int)psVar10[1]) ^ 0x80000000);
        *(float *)(psVar10 + 0x1e) = (float)(local_90 - dVar1) + *(float *)(psVar10 + 0x1a);
        iVar12 = iVar12 + -1;
      } while (iVar12 != 0);
    }
    iVar13 = iVar13 + iVar19;
    iVar14 = 0;
    DAT_8032eead = (undefined)iVar13;
    iVar12 = *(int *)&menuPcs->field_0x84c + iVar13 * 0x40 + 8;
    *(undefined4 *)(iVar12 + 0x24) = 0;
    *(undefined4 *)(iVar12 + 0x28) = 8;
    *(undefined4 *)(iVar12 + 0x2c) = 0;
    iVar12 = *(int *)&menuPcs->field_0x84c + (iVar13 + 1) * 0x40 + 8;
    *(undefined4 *)(iVar12 + 0x24) = 0;
    *(undefined4 *)(iVar12 + 0x28) = 8;
    fVar5 = FLOAT_80331ed0;
    *(undefined4 *)(iVar12 + 0x2c) = 0;
    fVar2 = FLOAT_80331eac;
    dVar1 = DOUBLE_80331e88;
    iVar12 = *(int *)&menuPcs->field_0x84c + (iVar13 + 2) * 0x40 + 8;
    *(undefined4 *)(iVar12 + 0x24) = 0;
    *(undefined4 *)(iVar12 + 0x28) = 8;
    *(undefined4 *)(iVar12 + 0x2c) = 0;
    iVar12 = *(int *)&menuPcs->field_0x84c + (iVar13 + 3) * 0x40 + 8;
    *(undefined4 *)(iVar12 + 0x24) = 0;
    *(undefined4 *)(iVar12 + 0x28) = 8;
    *(undefined4 *)(iVar12 + 0x2c) = 0;
    iVar12 = *(int *)&menuPcs->field_0x84c + (iVar13 + 4) * 0x40 + 8;
    *(undefined4 *)(iVar12 + 0x24) = 0;
    *(undefined4 *)(iVar12 + 0x28) = 8;
    *(undefined4 *)(iVar12 + 0x2c) = 0;
    iVar12 = *(int *)&menuPcs->field_0x84c + (iVar13 + 5) * 0x40 + 8;
    *(undefined4 *)(iVar12 + 0x24) = 0;
    *(undefined4 *)(iVar12 + 0x28) = 8;
    *(undefined4 *)(iVar12 + 0x2c) = 0;
    iVar12 = *(int *)&menuPcs->field_0x84c + (iVar13 + 6) * 0x40 + 8;
    *(undefined4 *)(iVar12 + 0x24) = 0;
    *(undefined4 *)(iVar12 + 0x28) = 8;
    *(undefined4 *)(iVar12 + 0x2c) = 0;
    iVar12 = *(int *)&menuPcs->field_0x84c + (iVar13 + 7) * 0x40 + 8;
    *(undefined4 *)(iVar12 + 0x24) = 0;
    *(undefined4 *)(iVar12 + 0x28) = 8;
    *(undefined4 *)(iVar12 + 0x2c) = 0;
    iVar12 = iVar19;
    if (0 < iVar19) {
      do {
        psVar10 = (short *)(*(int *)&menuPcs->field_0x84c + (iVar13 + 8 + iVar14) * 0x40 + 8);
        iVar14 = iVar14 + 1;
        psVar10[0x12] = 0;
        psVar10[0x13] = 0;
        psVar10[0x14] = 0;
        psVar10[0x15] = 8;
        local_78 = (double)(longlong)(int)*(float *)(psVar10 + 0x1c);
        *psVar10 = (short)(int)*(float *)(psVar10 + 0x1c);
        local_80 = (double)(longlong)(int)*(float *)(psVar10 + 0x1e);
        psVar10[1] = (short)(int)*(float *)(psVar10 + 0x1e);
        *(float *)(psVar10 + 0x18) = fVar5;
        *(float *)(psVar10 + 0x1a) = fVar2;
        local_88 = (double)(CONCAT44(0x43300000,(int)*psVar10) ^ 0x80000000);
        *(float *)(psVar10 + 0x1c) = (float)(local_88 - dVar1) + *(float *)(psVar10 + 0x18);
        local_90 = (double)(CONCAT44(0x43300000,(int)psVar10[1]) ^ 0x80000000);
        *(float *)(psVar10 + 0x1e) = (float)(local_90 - dVar1) + *(float *)(psVar10 + 0x1a);
        iVar12 = iVar12 + -1;
      } while (iVar12 != 0);
    }
    fVar5 = FLOAT_80331ed0;
    fVar2 = FLOAT_80331eac;
    dVar1 = DOUBLE_80331e88;
    iVar13 = iVar13 + 8 + iVar19;
    iVar14 = 0;
    iVar12 = iVar19;
    if (0 < iVar19) {
      do {
        psVar10 = (short *)(*(int *)&menuPcs->field_0x84c + (iVar13 + iVar14) * 0x40 + 8);
        iVar14 = iVar14 + 1;
        psVar10[0x12] = 0;
        psVar10[0x13] = 0;
        psVar10[0x14] = 0;
        psVar10[0x15] = 8;
        local_78 = (double)(longlong)(int)*(float *)(psVar10 + 0x1c);
        *psVar10 = (short)(int)*(float *)(psVar10 + 0x1c);
        local_80 = (double)(longlong)(int)*(float *)(psVar10 + 0x1e);
        psVar10[1] = (short)(int)*(float *)(psVar10 + 0x1e);
        *(float *)(psVar10 + 0x18) = fVar5;
        *(float *)(psVar10 + 0x1a) = fVar2;
        local_88 = (double)(CONCAT44(0x43300000,(int)*psVar10) ^ 0x80000000);
        *(float *)(psVar10 + 0x1c) = (float)(local_88 - dVar1) + *(float *)(psVar10 + 0x18);
        local_90 = (double)(CONCAT44(0x43300000,(int)psVar10[1]) ^ 0x80000000);
        *(float *)(psVar10 + 0x1e) = (float)(local_90 - dVar1) + *(float *)(psVar10 + 0x1a);
        iVar12 = iVar12 + -1;
      } while (iVar12 != 0);
    }
    fVar5 = FLOAT_80331ed0;
    fVar2 = FLOAT_80331eac;
    dVar1 = DOUBLE_80331e88;
    iVar13 = iVar13 + iVar19;
    iVar14 = 0;
    iVar12 = iVar19;
    if (0 < iVar19) {
      do {
        psVar16 = (short *)(*(int *)&menuPcs->field_0x84c + (iVar13 + iVar14) * 0x40 + 8);
        psVar10 = psVar16 + (iVar13 + -4) * -0x20;
        iVar14 = iVar14 + 1;
        psVar16[0xe] = -1;
        psVar16[0xf] = -1;
        *psVar16 = *psVar10 + 0x50;
        psVar16[1] = psVar10[1] + 0x48;
        *(undefined4 *)(psVar16 + 0x12) = *(undefined4 *)(psVar10 + 0x12);
        psVar16[0x14] = 0;
        psVar16[0x15] = 8;
        *(float *)(psVar16 + 0x18) = fVar5;
        *(float *)(psVar16 + 0x1a) = fVar2;
        local_78 = (double)(CONCAT44(0x43300000,(int)*psVar16) ^ 0x80000000);
        *(float *)(psVar16 + 0x1c) = (float)(local_78 - dVar1) + *(float *)(psVar16 + 0x18);
        local_80 = (double)(CONCAT44(0x43300000,(int)psVar16[1]) ^ 0x80000000);
        *(float *)(psVar16 + 0x1e) = (float)(local_80 - dVar1) + *(float *)(psVar16 + 0x1a);
        iVar12 = iVar12 + -1;
      } while (iVar12 != 0);
    }
    *(undefined2 *)(*(int *)&menuPcs->field_0x84c + 6) = 0;
    *(undefined *)(*(int *)&menuPcs->field_0x82c + 0xb) = 1;
  }
  iVar13 = 0;
  iVar18 = 0;
  *(short *)(*(int *)&menuPcs->field_0x82c + 0x22) =
       *(short *)(*(int *)&menuPcs->field_0x82c + 0x22) + 1;
  iVar12 = (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x22);
  for (iVar14 = 0; fVar5 = FLOAT_80331efc, fVar2 = FLOAT_80331ef8, dVar9 = DOUBLE_80331ef0,
      dVar8 = DOUBLE_80331ee8, dVar7 = DOUBLE_80331ee0, dVar4 = DOUBLE_80331e90,
      dVar3 = DOUBLE_80331e88, dVar1 = DOUBLE_80331e78, iVar14 < **(short **)&menuPcs->field_0x84c;
      iVar14 = iVar14 + 1) {
    psVar10 = (short *)((int)*(short **)&menuPcs->field_0x84c + iVar13 + 8);
    if ((*(uint *)(psVar10 + 0x16) & 1) == 0) {
      if (iVar12 < *(int *)(psVar10 + 0x12)) {
        *(float *)(psVar10 + 8) = FLOAT_80331eb0;
      }
      if (iVar12 < (int)(*(int *)(psVar10 + 0x12) + *(uint *)(psVar10 + 0x14))) {
        local_78 = (double)CONCAT44(0x43300000,*(uint *)(psVar10 + 0x14) ^ 0x80000000);
        local_80 = (double)CONCAT44(0x43300000,*(uint *)(psVar10 + 0x10) ^ 0x80000000);
        *(float *)(psVar10 + 8) =
             (float)-((DOUBLE_80331ed8 / (local_78 - DOUBLE_80331e88)) *
                      (local_80 - DOUBLE_80331e88) - DOUBLE_80331ed8);
      }
      else {
        *(float *)(psVar10 + 8) = FLOAT_80331eac;
      }
    }
    else {
      *(float *)(psVar10 + 8) = FLOAT_80331eb0;
    }
    if (((int)(*(int *)(psVar10 + 0x12) + *(uint *)(psVar10 + 0x14)) <= iVar12) ||
       (0x270e < *(int *)(psVar10 + 0x12))) {
      iVar18 = iVar18 + 1;
    }
    if (((*(uint *)(psVar10 + 0x16) & 2) == 0) &&
       ((*(float *)(psVar10 + 0x18) != FLOAT_80331eac ||
        (*(float *)(psVar10 + 0x1a) != FLOAT_80331eac)))) {
      local_78 = (double)CONCAT44(0x43300000,*(uint *)(psVar10 + 0x14) ^ 0x80000000);
      local_80 = (double)CONCAT44(0x43300000,*(uint *)(psVar10 + 0x10) ^ 0x80000000);
      local_90 = (double)CONCAT44(0x43300000,(int)*psVar10 ^ 0x80000000);
      local_88 = (double)CONCAT44(0x43300000,(int)psVar10[1] ^ 0x80000000);
      fVar2 = (float)-((DOUBLE_80331ed8 / (local_78 - DOUBLE_80331e88)) *
                       (local_80 - DOUBLE_80331e88) - DOUBLE_80331ed8);
      dVar1 = local_88 - DOUBLE_80331e88;
      *(float *)(psVar10 + 0x18) =
           (*(float *)(psVar10 + 0x1c) - (float)(local_90 - DOUBLE_80331e88)) * fVar2;
      *(float *)(psVar10 + 0x1a) = (*(float *)(psVar10 + 0x1e) - (float)dVar1) * fVar2;
    }
    if ((*(int *)(psVar10 + 0x12) < iVar12) &&
       (iVar12 <= *(int *)(psVar10 + 0x12) + *(int *)(psVar10 + 0x14))) {
      *(int *)(psVar10 + 0x10) = *(int *)(psVar10 + 0x10) + 1;
    }
    iVar13 = iVar13 + 0x40;
  }
  iVar14 = 0;
  iVar13 = 0;
  iVar12 = iVar19;
  if (0 < iVar19) {
    do {
      psVar10 = (short *)(*(int *)&menuPcs->field_0x84c + (iVar14 + 4) * 0x40 + 8);
      local_80 = (double)(CONCAT44(0x43300000,(int)*psVar10) ^ 0x80000000);
      iVar15 = iVar13 + 0x40;
      local_78 = (double)(CONCAT44(0x43300000,(int)psVar10[2]) ^ 0x80000000);
      local_90 = (double)CONCAT44(0x43300000,(int)psVar10[1] ^ 0x80000000);
      local_88 = (double)CONCAT44(0x43300000,(int)psVar10[3] ^ 0x80000000);
      local_60 = 0x43300000;
      local_50 = 0x43300000;
      iVar11 = (int)((double)(float)(dVar7 + (local_78 - dVar3) * dVar1 +
                                             (double)((float)(local_80 - dVar3) +
                                                     *(float *)(psVar10 + 0x18))) - dVar8);
      local_70 = (longlong)iVar11;
      iVar17 = (int)((double)(float)((local_88 - dVar3) * dVar1 +
                                    (double)((float)(local_90 - dVar3) + *(float *)(psVar10 + 0x1a))
                                    ) - dVar9);
      local_68 = (longlong)iVar17;
      *(short *)(*(int *)&menuPcs->field_0x814 + iVar13 + 8) = (short)iVar11;
      *(short *)(*(int *)&menuPcs->field_0x814 + iVar13 + 10) = (short)iVar17;
      uStack_5c = (int)*psVar10 ^ 0x80000000;
      iVar11 = (int)(fVar2 + (float)((double)CONCAT44(0x43300000,uStack_5c) - dVar3) +
                             *(float *)(psVar10 + 0x18));
      local_58 = (longlong)iVar11;
      *(int *)(*(int *)&menuPcs->field_0x814 + iVar15) = iVar11;
      uStack_4c = (int)psVar10[1] ^ 0x80000000;
      iVar11 = (int)(((float)((double)CONCAT44(0x43300000,uStack_4c) - dVar3) +
                     *(float *)(psVar10 + 0x1a)) - fVar5);
      local_48 = (longlong)iVar11;
      *(int *)(*(int *)&menuPcs->field_0x814 + iVar13 + 0x44) = iVar11;
      if ((double)CONCAT44(0x43300000,*(uint *)(*(int *)&menuPcs->field_0x814 + iVar15) ^ 0x80000000
                          ) - dVar3 < dVar4) {
        *(undefined4 *)(*(int *)&menuPcs->field_0x814 + iVar15) = 0;
      }
      local_40 = 0x43300000;
      uStack_3c = *(uint *)(*(int *)&menuPcs->field_0x814 + iVar13 + 0x44) ^ 0x80000000;
      if ((double)CONCAT44(0x43300000,uStack_3c) - dVar3 < dVar4) {
        *(undefined4 *)(*(int *)&menuPcs->field_0x814 + iVar13 + 0x44) = 0;
      }
      iVar11 = iVar13 + 0x4c;
      *(undefined4 *)(*(int *)&menuPcs->field_0x814 + iVar13 + 0x48) = 0x48;
      iVar13 = iVar13 + 0x50;
      iVar14 = iVar14 + 1;
      *(undefined4 *)(*(int *)&menuPcs->field_0x814 + iVar11) = 0x58;
      iVar12 = iVar12 + -1;
    } while (iVar12 != 0);
  }
  iVar12 = 0;
  iVar13 = 0;
  do {
    if (iVar19 + 8 <= iVar12) {
      if (**(short **)&menuPcs->field_0x84c == iVar18) {
        (*(short **)&menuPcs->field_0x84c)[3] = 1;
      }
      return;
    }
    iVar11 = *(int *)&menuPcs->field_0x84c;
    iVar14 = (int)DAT_8032eeae;
    if (iVar12 < iVar19) {
      iVar17 = *(int *)((int)DAT_8032eea8 + iVar13 + 0x44);
      iVar15 = *(int *)((int)DAT_8032eea8 + iVar13 + 0x20);
      fVar2 = *(float *)(&DAT_801dd56c + iVar17 * 4);
      PSMTXScale(fVar2,fVar2,fVar2,&MStack_c0);
LAB_80134590:
      if (iVar12 < iVar19) {
        MStack_c0.value[1][3] = *(float *)(&DAT_801dd55c + iVar17 * 4);
        MStack_c0.value[0][3] = FLOAT_80331eac;
      }
      else {
        uStack_3c = iVar12 - iVar19 ^ 0x80000000;
        local_40 = 0x43300000;
        local_15c.x = DAT_801dd57c;
        local_15c.y = FLOAT_80331eac;
        local_15c.z = FLOAT_80331eac;
        PSMTXRotRad(FLOAT_80331f04 *
                    (float)(DOUBLE_80331f08 *
                           ((double)CONCAT44(0x43300000,uStack_3c) - DOUBLE_80331e88)),&MStack_f0,
                    0x7a);
        PSMTXMultVecSR(&MStack_f0,&local_15c,&local_168);
        if (*(int *)(iVar15 + 4) == 0x44) {
          PSMTXRotRad(FLOAT_80331f10,&MStack_120,0x79);
          PSMTXConcat(&MStack_c0,&MStack_120,&MStack_c0);
          PSMTXRotRad(FLOAT_80331f14,&MStack_150,0x78);
          PSMTXConcat(&MStack_c0,&MStack_150,&MStack_c0);
        }
        MStack_c0.value[0][3] = local_168.x;
        iVar17 = *(int *)(iVar15 + 4);
        MStack_c0.value[1][3] = (float)((double)(FLOAT_80331f18 * local_168.y) - DOUBLE_80331f20);
        if ((iVar17 == 0x41) || (iVar17 == 0x37)) {
          MStack_c0.value[1][3] = MStack_c0.value[1][3] + FLOAT_80331f28;
        }
        else if (iVar17 == 0x44) {
          MStack_c0.value[1][3] = MStack_c0.value[1][3] + FLOAT_80331f2c;
        }
      }
      MStack_c0.value[2][3] = FLOAT_80331eac;
      *(byte *)(*(int *)(iVar15 + 0x168) + 0x10c) =
           *(byte *)(*(int *)(iVar15 + 0x168) + 0x10c) & 0x7f | 0x80;
      SetMatrix__Q26CChara6CModelFPA4_f(*(CModel **)(iVar15 + 0x168),&MStack_c0);
      CalcMatrix__Q26CChara6CModelFv(*(undefined4 *)(iVar15 + 0x168));
      CalcSkin__Q26CChara6CModelFv(*(undefined4 *)(iVar15 + 0x168));
      *(undefined4 *)(*(int *)(iVar15 + 0x168) + 0x9c) =
           *(undefined4 *)(iVar11 + (iVar14 + iVar12) * 0x40 + 0x18);
    }
    else {
      iVar17 = iVar12 + iVar19;
      iVar15 = *(int *)((int)(&menuPcs->m_cameraMatrix + 1) + iVar17 * 4);
      if (iVar15 != 0) {
        PSMTXScale(FLOAT_80331f00,FLOAT_80331f00,FLOAT_80331f00,&MStack_c0);
        goto LAB_80134590;
      }
    }
    iVar13 = iVar13 + 0x2c;
    iVar12 = iVar12 + 1;
  } while( true );
}

