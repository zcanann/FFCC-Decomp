// Function: CalcResultOpenAnim__8CMenuPcsFv
// Entry: 8013b14c
// Size: 8316 bytes

/* WARNING: Removing unreachable block (ram,0x8013d1ac) */
/* WARNING: Removing unreachable block (ram,0x8013b15c) */

void CalcResultOpenAnim__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  float fVar1;
  short sVar2;
  bool bVar3;
  double dVar4;
  float fVar5;
  double dVar6;
  double dVar7;
  double dVar8;
  float fVar9;
  float fVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  short *psVar15;
  CMenuPcs *pCVar16;
  int iVar17;
  int iVar18;
  int iVar19;
  short sVar21;
  undefined2 *puVar20;
  undefined2 *puVar22;
  int iVar23;
  int iVar24;
  short *psVar25;
  int iVar26;
  int iVar27;
  int iVar28;
  undefined2 uVar29;
  uint uVar30;
  int unaff_r31;
  uint uVar31;
  uint uVar32;
  double dVar33;
  undefined4 local_1e8;
  undefined4 local_1e4;
  undefined4 local_1e0;
  undefined4 local_1dc;
  Mtx MStack_1d8;
  Mtx MStack_1a8;
  Mtx MStack_178;
  double local_148;
  double local_140;
  undefined8 local_138;
  undefined8 local_130;
  undefined8 local_128;
  double local_120;
  double local_68;
  double local_60;
  undefined8 local_58;
  double local_50;
  
  iVar11 = *(int *)&menuPcs->field_0x82c;
  uVar30 = *DAT_8032eea8;
  if (*(char *)(iVar11 + 0xb) != '\0') {
    iVar26 = 0;
    iVar23 = 0;
    *(short *)(iVar11 + 0x22) = *(short *)(iVar11 + 0x22) + 1;
    iVar24 = (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x22);
    for (iVar11 = 0; dVar33 = DOUBLE_80331e88, iVar11 < **(short **)&menuPcs->field_0x84c;
        iVar11 = iVar11 + 1) {
      iVar12 = (int)*(short **)&menuPcs->field_0x84c + iVar26 + 8;
      if (*(int *)(iVar12 + 0x24) <= iVar24) {
        if (iVar24 < *(int *)(iVar12 + 0x24) + *(int *)(iVar12 + 0x28)) {
          *(int *)(iVar12 + 0x20) = *(int *)(iVar12 + 0x20) + 1;
          local_50 = (double)(CONCAT44(0x43300000,*(undefined4 *)(iVar12 + 0x28)) ^ 0x80000000);
          local_58 = (double)(CONCAT44(0x43300000,*(undefined4 *)(iVar12 + 0x20)) ^ 0x80000000);
          *(float *)(iVar12 + 0x10) =
               (float)((DOUBLE_80331ed8 / (local_50 - dVar33)) * (local_58 - dVar33));
        }
        else {
          iVar23 = iVar23 + 1;
          *(float *)(iVar12 + 0x10) = FLOAT_80331eb0;
        }
        if (*(int *)(iVar12 + 0x1c) == 0x17) {
          for (iVar17 = 0; iVar17 < (int)*DAT_8032eea8; iVar17 = iVar17 + 1) {
            if (*(int *)(iVar12 + 0x20) == 1) {
              PlaySe__6CSoundFiiii(&Sound,0x49,0x40,0x7f,0);
            }
            iVar12 = iVar12 + 0x40;
          }
        }
      }
      iVar26 = iVar26 + 0x40;
    }
    iVar11 = uVar30 * 2;
    iVar12 = 0;
    iVar24 = (iVar11 + 1) * 0x40;
    for (iVar26 = 0; iVar26 < (int)(uVar30 * 3); iVar26 = iVar26 + 1) {
      iVar17 = *(int *)&menuPcs->field_0x84c + iVar24 + 8;
      if (iVar26 < (int)uVar30) {
        iVar13 = *(int *)((int)DAT_8032eea8 + iVar12 + 0x20);
        unaff_r31 = *(int *)((int)DAT_8032eea8 + iVar12 + 0x44);
        fVar1 = *(float *)(&DAT_801dd56c + unaff_r31 * 4);
        PSMTXScale(fVar1,fVar1,fVar1,&MStack_178);
      }
      else {
        iVar13 = *(int *)((int)menuPcs + (iVar26 - uVar30) * 4 + 0x774);
        if (iVar26 < iVar11) {
          PSMTXScale(FLOAT_80331eb0,FLOAT_80331eb0,FLOAT_80331eb0,&MStack_178);
        }
        else {
          dVar33 = (double)FLOAT_80331fa8;
          if ((*(int *)(iVar17 + 0x20) == 0x18) && (menuPcs->field_0x8c == '\0')) {
            PlaySe__6CSoundFiiii(&Sound,0x48,0x40,0x7f,0);
            menuPcs->field_0x8c = 1;
          }
          if (0x17 < *(int *)(iVar17 + 0x20)) {
            unaff_r31 = *(int *)(iVar17 + 0x20) + -0x18;
            local_50 = (double)(CONCAT44(0x43300000,unaff_r31) ^ 0x80000000);
            local_58 = (double)(CONCAT44(0x43300000,*(int *)(iVar17 + 0x28) + -0x18) ^ 0x80000000);
            dVar33 = (double)(float)(DOUBLE_80331e78 *
                                     (double)((float)(local_50 - DOUBLE_80331e88) /
                                             (float)(local_58 - DOUBLE_80331e88)) + dVar33);
          }
          PSMTXScale((float)dVar33,(float)dVar33,(float)dVar33,&MStack_178);
        }
      }
      if (iVar26 / (int)uVar30 == 1) {
        PSMTXRotRad(FLOAT_80331f94,&MStack_1a8,0x78);
        PSMTXConcat(&MStack_178,&MStack_1a8,&MStack_178);
        PSMTXRotRad(FLOAT_80331f04 * **(float **)&menuPcs->field_0x82c,&MStack_1d8,0x79);
        PSMTXConcat(&MStack_178,&MStack_1d8,&MStack_178);
      }
      if (iVar26 < (int)uVar30) {
        MStack_178.value[0][3] = FLOAT_80331eac;
        MStack_178.value[1][3] = *(float *)(&DAT_801dd55c + unaff_r31 * 4);
        MStack_178.value[2][3] = FLOAT_80331eac;
      }
      else if (iVar26 < iVar11) {
        MStack_178.value[0][3] = FLOAT_80331eac;
        MStack_178.value[1][3] = FLOAT_80331eac;
        MStack_178.value[2][3] = FLOAT_80331eac;
      }
      else {
        local_1e0 = DAT_8032ea68;
        local_1dc = DAT_8032ea6c;
        local_50 = (double)(CONCAT44(0x43300000,*(int *)(iVar17 + 0x20) + -1) ^ 0x80000000);
        dVar33 = (double)GetFcvValue__8CMenuPcsFQ28CMenuPcs3FCVf
                                   ((double)(float)(local_50 - DOUBLE_80331e88),menuPcs,&local_1e0);
        MStack_178.value[0][3] = (float)dVar33;
        if (*(int *)(iVar17 + 0x20) == 8) {
          PlaySe__6CSoundFiiii(&Sound,0x47,0x40,0x7f,0);
        }
        local_1e8 = DAT_8032ea70;
        local_1e4 = DAT_8032ea74;
        local_50 = (double)(CONCAT44(0x43300000,*(int *)(iVar17 + 0x20) + -1) ^ 0x80000000);
        dVar33 = (double)GetFcvValue__8CMenuPcsFQ28CMenuPcs3FCVf
                                   ((double)(float)(local_50 - DOUBLE_80331e88),menuPcs,&local_1e8);
        unaff_r31 = iVar26 + uVar30 * -2;
        MStack_178.value[1][3] = (float)dVar33;
        MStack_178.value[2][3] = FLOAT_80331eac;
        if ((0 < unaff_r31) && (unaff_r31 < 3)) {
          MStack_178.value[1][3] = (float)((double)(float)dVar33 - DOUBLE_80331fb0);
        }
      }
      FLOAT_80331eac = MStack_178.value[2][3];
      *(byte *)(*(int *)(iVar13 + 0x168) + 0x10c) =
           *(byte *)(*(int *)(iVar13 + 0x168) + 0x10c) & 0x7f | 0x80;
      SetMatrix__Q26CChara6CModelFPA4_f(*(CModel **)(iVar13 + 0x168),&MStack_178);
      CalcMatrix__Q26CChara6CModelFv(*(undefined4 *)(iVar13 + 0x168));
      CalcSkin__Q26CChara6CModelFv(*(undefined4 *)(iVar13 + 0x168));
      dVar33 = DOUBLE_80331e90;
      if (iVar11 <= iVar26) {
        if (*(int *)(iVar17 + 0x20) < 0x18) {
          *(float *)(iVar17 + 0x10) = FLOAT_80331eb0;
        }
        else {
          unaff_r31 = *(int *)(iVar17 + 0x20) + -0x18;
          local_50 = (double)(CONCAT44(0x43300000,unaff_r31) ^ 0x80000000);
          local_58 = (double)(CONCAT44(0x43300000,*(int *)(iVar17 + 0x28) + -0x18) ^ 0x80000000);
          *(float *)(iVar17 + 0x10) =
               (float)(DOUBLE_80331ed8 -
                      (double)((float)(local_50 - DOUBLE_80331e88) /
                              (float)(local_58 - DOUBLE_80331e88)));
          if ((double)*(float *)(iVar17 + 0x10) < dVar33) {
            *(float *)(iVar17 + 0x10) = FLOAT_80331eac;
          }
        }
      }
      iVar24 = iVar24 + 0x40;
      iVar12 = iVar12 + 0x2c;
      *(undefined4 *)(*(int *)(iVar13 + 0x168) + 0x9c) = *(undefined4 *)(iVar17 + 0x10);
    }
    if (**(short **)&menuPcs->field_0x84c != iVar23) {
      return;
    }
    (*(short **)&menuPcs->field_0x84c)[3] = 1;
    return;
  }
  menuPcs->field_0x8c = 0;
  PlaySe__6CSoundFiiii(&Sound,0x46,0x40,0x7f,0);
  memset(*(undefined4 *)&menuPcs->field_0x84c,0,0x1008);
  iVar11 = *(int *)&menuPcs->field_0x84c;
  *(undefined4 *)(iVar11 + 0x24) = 0x16;
  fVar1 = FLOAT_80331eac;
  *(undefined2 *)(iVar11 + 10) = 0;
  fVar5 = FLOAT_80331eb0;
  iVar23 = 0;
  *(undefined2 *)(iVar11 + 8) = 0;
  *(undefined2 *)(iVar11 + 0xc) = 0x280;
  *(undefined2 *)(iVar11 + 0xe) = 0x1c0;
  *(float *)(iVar11 + 0x14) = fVar1;
  *(float *)(iVar11 + 0x10) = fVar1;
  *(undefined4 *)(iVar11 + 0x2c) = 0;
  *(undefined4 *)(iVar11 + 0x30) = 8;
  *(float *)(iVar11 + 0x1c) = fVar5;
  *(float *)(iVar11 + 0x18) = fVar1;
  if (0 < (int)uVar30) {
    if (8 < (int)uVar30) {
      sVar21 = 0x38;
      uVar32 = uVar30 - 1 >> 3;
      if (0 < (int)(uVar30 - 8)) {
        do {
          sVar2 = (short)iVar23;
          puVar22 = (undefined2 *)(*(int *)&menuPcs->field_0x84c + (iVar23 + 1) * 0x40 + 8);
          *(undefined4 *)(puVar22 + 0xe) = 0x17;
          *puVar22 = 0x80;
          puVar22[1] = sVar21;
          puVar22[2] = 0x1a0;
          puVar22[3] = 0x40;
          *(float *)(puVar22 + 4) = fVar1;
          *(float *)(puVar22 + 6) = fVar1;
          *(undefined4 *)(puVar22 + 0x14) = 8;
          *(float *)(puVar22 + 10) = fVar5;
          puVar22 = (undefined2 *)(*(int *)&menuPcs->field_0x84c + (iVar23 + 2) * 0x40 + 8);
          *(undefined4 *)(puVar22 + 0xe) = 0x17;
          *puVar22 = 0x80;
          puVar22[1] = (sVar2 + 1) * 0x60 + 0x38;
          puVar22[2] = 0x1a0;
          puVar22[3] = 0x40;
          *(float *)(puVar22 + 4) = fVar1;
          *(float *)(puVar22 + 6) = fVar1;
          *(undefined4 *)(puVar22 + 0x14) = 8;
          *(float *)(puVar22 + 10) = fVar5;
          puVar22 = (undefined2 *)(*(int *)&menuPcs->field_0x84c + (iVar23 + 3) * 0x40 + 8);
          *(undefined4 *)(puVar22 + 0xe) = 0x17;
          *puVar22 = 0x80;
          puVar22[1] = (sVar2 + 2) * 0x60 + 0x38;
          puVar22[2] = 0x1a0;
          puVar22[3] = 0x40;
          *(float *)(puVar22 + 4) = fVar1;
          *(float *)(puVar22 + 6) = fVar1;
          *(undefined4 *)(puVar22 + 0x14) = 8;
          *(float *)(puVar22 + 10) = fVar5;
          puVar22 = (undefined2 *)(*(int *)&menuPcs->field_0x84c + (iVar23 + 4) * 0x40 + 8);
          *(undefined4 *)(puVar22 + 0xe) = 0x17;
          *puVar22 = 0x80;
          puVar22[1] = (sVar2 + 3) * 0x60 + 0x38;
          puVar22[2] = 0x1a0;
          puVar22[3] = 0x40;
          *(float *)(puVar22 + 4) = fVar1;
          *(float *)(puVar22 + 6) = fVar1;
          *(undefined4 *)(puVar22 + 0x14) = 8;
          *(float *)(puVar22 + 10) = fVar5;
          iVar24 = iVar23 + 6;
          puVar22 = (undefined2 *)(*(int *)&menuPcs->field_0x84c + (iVar23 + 5) * 0x40 + 8);
          iVar26 = iVar23 + 7;
          *(undefined4 *)(puVar22 + 0xe) = 0x17;
          *puVar22 = 0x80;
          puVar22[1] = (sVar2 + 4) * 0x60 + 0x38;
          puVar22[2] = 0x1a0;
          iVar11 = iVar23 + 8;
          puVar22[3] = 0x40;
          sVar21 = sVar21 + 0x300;
          *(float *)(puVar22 + 4) = fVar1;
          *(float *)(puVar22 + 6) = fVar1;
          *(undefined4 *)(puVar22 + 0x14) = 8;
          iVar23 = iVar23 + 8;
          *(float *)(puVar22 + 10) = fVar5;
          puVar22 = (undefined2 *)(*(int *)&menuPcs->field_0x84c + iVar24 * 0x40 + 8);
          *(undefined4 *)(puVar22 + 0xe) = 0x17;
          *puVar22 = 0x80;
          puVar22[1] = (sVar2 + 5) * 0x60 + 0x38;
          puVar22[2] = 0x1a0;
          puVar22[3] = 0x40;
          *(float *)(puVar22 + 4) = fVar1;
          *(float *)(puVar22 + 6) = fVar1;
          *(undefined4 *)(puVar22 + 0x14) = 8;
          *(float *)(puVar22 + 10) = fVar5;
          puVar22 = (undefined2 *)(*(int *)&menuPcs->field_0x84c + iVar26 * 0x40 + 8);
          *(undefined4 *)(puVar22 + 0xe) = 0x17;
          *puVar22 = 0x80;
          puVar22[1] = (sVar2 + 6) * 0x60 + 0x38;
          puVar22[2] = 0x1a0;
          puVar22[3] = 0x40;
          *(float *)(puVar22 + 4) = fVar1;
          *(float *)(puVar22 + 6) = fVar1;
          *(undefined4 *)(puVar22 + 0x14) = 8;
          *(float *)(puVar22 + 10) = fVar5;
          puVar22 = (undefined2 *)(*(int *)&menuPcs->field_0x84c + iVar11 * 0x40 + 8);
          *(undefined4 *)(puVar22 + 0xe) = 0x17;
          *puVar22 = 0x80;
          puVar22[1] = (sVar2 + 7) * 0x60 + 0x38;
          puVar22[2] = 0x1a0;
          puVar22[3] = 0x40;
          *(float *)(puVar22 + 4) = fVar1;
          *(float *)(puVar22 + 6) = fVar1;
          *(undefined4 *)(puVar22 + 0x14) = 8;
          *(float *)(puVar22 + 10) = fVar5;
          uVar32 = uVar32 - 1;
        } while (uVar32 != 0);
      }
    }
    fVar5 = FLOAT_80331eb0;
    fVar1 = FLOAT_80331eac;
    iVar11 = uVar30 - iVar23;
    iVar24 = iVar23 * 0x60 + 0x38;
    if (iVar23 < (int)uVar30) {
      do {
        iVar26 = iVar23 + 1;
        iVar23 = iVar23 + 1;
        puVar22 = (undefined2 *)(*(int *)&menuPcs->field_0x84c + iVar26 * 0x40 + 8);
        *(undefined4 *)(puVar22 + 0xe) = 0x17;
        *puVar22 = 0x80;
        puVar22[1] = (short)iVar24;
        iVar24 = iVar24 + 0x60;
        puVar22[2] = 0x1a0;
        puVar22[3] = 0x40;
        *(float *)(puVar22 + 4) = fVar1;
        *(float *)(puVar22 + 6) = fVar1;
        *(undefined4 *)(puVar22 + 0x14) = 8;
        *(float *)(puVar22 + 10) = fVar5;
        iVar11 = iVar11 + -1;
      } while (iVar11 != 0);
    }
  }
  fVar1 = FLOAT_80331eb0;
  dVar33 = DOUBLE_80331e88;
  iVar11 = uVar30 + 1;
  iVar24 = 0;
  iVar23 = 0;
  sVar21 = 0x28;
  uVar32 = uVar30;
  if (0 < (int)uVar30) {
    do {
      uVar31 = *(uint *)((int)DAT_8032eea8 + iVar23 + 0x1c);
      puVar22 = (undefined2 *)(*(int *)&menuPcs->field_0x84c + (iVar11 + iVar24) * 0x40 + 8);
      *(undefined4 *)(puVar22 + 0xe) = 0x18;
      bVar3 = false;
      if ((0 < iVar24) && (iVar24 < 3)) {
        bVar3 = true;
      }
      uVar29 = 0x48;
      if (bVar3) {
        uVar29 = 0x30;
      }
      *puVar22 = uVar29;
      puVar22[1] = sVar21;
      puVar22[2] = 0x60;
      puVar22[3] = 0x58;
      if ((uVar31 & 1) == 0) {
        iVar26 = 0;
      }
      else {
        iVar26 = (int)(short)puVar22[2];
      }
      local_148 = (double)(CONCAT44(0x43300000,iVar26) ^ 0x80000000);
      *(float *)(puVar22 + 4) = (float)(local_148 - dVar33);
      if ((int)uVar31 >> 1 == 0) {
        iVar26 = 0;
      }
      else {
        iVar26 = (int)(short)puVar22[3];
      }
      local_140 = (double)(CONCAT44(0x43300000,iVar26) ^ 0x80000000);
      *(float *)(puVar22 + 6) = (float)(local_140 - dVar33);
      if (iVar24 == 0) {
        *(int *)(puVar22 + 0x12) =
             *(int *)(puVar22 + iVar11 * -0x20 + 0x12) + *(int *)(puVar22 + iVar11 * -0x20 + 0x14);
        *(int *)(puVar22 + 0x12) = *(int *)(puVar22 + 0x12) + 0x18;
      }
      else {
        *(int *)(puVar22 + 0x12) = *(int *)(puVar22 + -0xe) + 3;
      }
      iVar23 = iVar23 + 0x2c;
      *(undefined4 *)(puVar22 + 0x14) = 8;
      sVar21 = sVar21 + 0x60;
      iVar24 = iVar24 + 1;
      *(float *)(puVar22 + 10) = fVar1;
      uVar32 = uVar32 - 1;
    } while (uVar32 != 0);
  }
  fVar5 = FLOAT_80331eb0;
  fVar1 = FLOAT_80331eac;
  iVar11 = iVar11 + uVar30;
  iVar23 = iVar11 - (uVar30 + 1);
  iVar24 = 0;
  if (0 < (int)uVar30) {
    uVar32 = uVar30 >> 1;
    uVar31 = uVar30;
    if (uVar32 != 0) {
      do {
        iVar26 = iVar24 + 1;
        puVar22 = (undefined2 *)(*(int *)&menuPcs->field_0x84c + (iVar11 + iVar24) * 0x40 + 8);
        *(undefined4 *)(puVar22 + 0xe) = 0xfffffffe;
        *puVar22 = 0;
        iVar24 = iVar24 + 2;
        puVar22[1] = 0;
        puVar22[2] = 0;
        puVar22[3] = 0;
        *(float *)(puVar22 + 4) = fVar1;
        *(float *)(puVar22 + 6) = fVar1;
        *(int *)(puVar22 + 0x12) =
             *(int *)(puVar22 + iVar23 * -0x20 + 0x12) + *(int *)(puVar22 + iVar23 * -0x20 + 0x14);
        *(undefined4 *)(puVar22 + 0x14) = 8;
        *(float *)(puVar22 + 10) = fVar5;
        puVar22 = (undefined2 *)(*(int *)&menuPcs->field_0x84c + (iVar11 + iVar26) * 0x40 + 8);
        *(undefined4 *)(puVar22 + 0xe) = 0xfffffffe;
        *puVar22 = 0;
        puVar22[1] = 0;
        puVar22[2] = 0;
        puVar22[3] = 0;
        *(float *)(puVar22 + 4) = fVar1;
        *(float *)(puVar22 + 6) = fVar1;
        *(int *)(puVar22 + 0x12) =
             *(int *)(puVar22 + iVar23 * -0x20 + 0x12) + *(int *)(puVar22 + iVar23 * -0x20 + 0x14);
        *(undefined4 *)(puVar22 + 0x14) = 8;
        *(float *)(puVar22 + 10) = fVar5;
        uVar32 = uVar32 - 1;
      } while (uVar32 != 0);
      uVar31 = uVar30 & 1;
      if (uVar31 == 0) goto LAB_8013b77c;
    }
    do {
      iVar26 = iVar11 + iVar24;
      iVar24 = iVar24 + 1;
      puVar22 = (undefined2 *)(*(int *)&menuPcs->field_0x84c + iVar26 * 0x40 + 8);
      *(undefined4 *)(puVar22 + 0xe) = 0xfffffffe;
      *puVar22 = 0;
      puVar22[1] = 0;
      puVar22[2] = 0;
      puVar22[3] = 0;
      *(float *)(puVar22 + 4) = fVar1;
      *(float *)(puVar22 + 6) = fVar1;
      *(int *)(puVar22 + 0x12) =
           *(int *)(puVar22 + iVar23 * -0x20 + 0x12) + *(int *)(puVar22 + iVar23 * -0x20 + 0x14);
      *(undefined4 *)(puVar22 + 0x14) = 8;
      *(float *)(puVar22 + 10) = fVar5;
      uVar31 = uVar31 - 1;
    } while (uVar31 != 0);
  }
LAB_8013b77c:
  fVar5 = FLOAT_80331eb0;
  fVar1 = FLOAT_80331eac;
  iVar11 = iVar11 + uVar30;
  iVar23 = 0;
  if (0 < (int)uVar30) {
    if ((8 < (int)uVar30) && (uVar32 = uVar30 - 1 >> 3, 0 < (int)(uVar30 - 8))) {
      do {
        iVar24 = iVar11 + iVar23;
        puVar22 = (undefined2 *)(*(int *)&menuPcs->field_0x84c + iVar24 * 0x40 + 8);
        *(undefined4 *)(puVar22 + 0xe) = 0xfffffffe;
        *puVar22 = 0;
        puVar22[1] = 0;
        puVar22[2] = 0;
        puVar22[3] = 0;
        *(float *)(puVar22 + 4) = fVar1;
        *(float *)(puVar22 + 6) = fVar1;
        *(undefined4 *)(puVar22 + 0x14) = 8;
        *(float *)(puVar22 + 10) = fVar5;
        puVar22 = (undefined2 *)(*(int *)&menuPcs->field_0x84c + (iVar24 + 1) * 0x40 + 8);
        *(undefined4 *)(puVar22 + 0xe) = 0xfffffffe;
        *puVar22 = 0;
        puVar22[1] = 0;
        puVar22[2] = 0;
        puVar22[3] = 0;
        *(float *)(puVar22 + 4) = fVar1;
        *(float *)(puVar22 + 6) = fVar1;
        *(undefined4 *)(puVar22 + 0x14) = 8;
        *(float *)(puVar22 + 10) = fVar5;
        puVar22 = (undefined2 *)(*(int *)&menuPcs->field_0x84c + (iVar24 + 2) * 0x40 + 8);
        *(undefined4 *)(puVar22 + 0xe) = 0xfffffffe;
        *puVar22 = 0;
        puVar22[1] = 0;
        puVar22[2] = 0;
        puVar22[3] = 0;
        *(float *)(puVar22 + 4) = fVar1;
        *(float *)(puVar22 + 6) = fVar1;
        *(undefined4 *)(puVar22 + 0x14) = 8;
        *(float *)(puVar22 + 10) = fVar5;
        puVar22 = (undefined2 *)(*(int *)&menuPcs->field_0x84c + (iVar24 + 3) * 0x40 + 8);
        *(undefined4 *)(puVar22 + 0xe) = 0xfffffffe;
        *puVar22 = 0;
        puVar22[1] = 0;
        puVar22[2] = 0;
        puVar22[3] = 0;
        *(float *)(puVar22 + 4) = fVar1;
        *(float *)(puVar22 + 6) = fVar1;
        *(undefined4 *)(puVar22 + 0x14) = 8;
        *(float *)(puVar22 + 10) = fVar5;
        puVar22 = (undefined2 *)(*(int *)&menuPcs->field_0x84c + (iVar24 + 4) * 0x40 + 8);
        *(undefined4 *)(puVar22 + 0xe) = 0xfffffffe;
        iVar23 = iVar23 + 8;
        *puVar22 = 0;
        puVar22[1] = 0;
        puVar22[2] = 0;
        puVar22[3] = 0;
        *(float *)(puVar22 + 4) = fVar1;
        *(float *)(puVar22 + 6) = fVar1;
        *(undefined4 *)(puVar22 + 0x14) = 8;
        *(float *)(puVar22 + 10) = fVar5;
        puVar22 = (undefined2 *)(*(int *)&menuPcs->field_0x84c + (iVar24 + 5) * 0x40 + 8);
        *(undefined4 *)(puVar22 + 0xe) = 0xfffffffe;
        *puVar22 = 0;
        puVar22[1] = 0;
        puVar22[2] = 0;
        puVar22[3] = 0;
        *(float *)(puVar22 + 4) = fVar1;
        *(float *)(puVar22 + 6) = fVar1;
        *(undefined4 *)(puVar22 + 0x14) = 8;
        *(float *)(puVar22 + 10) = fVar5;
        puVar22 = (undefined2 *)(*(int *)&menuPcs->field_0x84c + (iVar24 + 6) * 0x40 + 8);
        *(undefined4 *)(puVar22 + 0xe) = 0xfffffffe;
        *puVar22 = 0;
        puVar22[1] = 0;
        puVar22[2] = 0;
        puVar22[3] = 0;
        *(float *)(puVar22 + 4) = fVar1;
        *(float *)(puVar22 + 6) = fVar1;
        *(undefined4 *)(puVar22 + 0x14) = 8;
        *(float *)(puVar22 + 10) = fVar5;
        puVar22 = (undefined2 *)(*(int *)&menuPcs->field_0x84c + (iVar24 + 7) * 0x40 + 8);
        *(undefined4 *)(puVar22 + 0xe) = 0xfffffffe;
        *puVar22 = 0;
        puVar22[1] = 0;
        puVar22[2] = 0;
        puVar22[3] = 0;
        *(float *)(puVar22 + 4) = fVar1;
        *(float *)(puVar22 + 6) = fVar1;
        *(undefined4 *)(puVar22 + 0x14) = 8;
        *(float *)(puVar22 + 10) = fVar5;
        uVar32 = uVar32 - 1;
      } while (uVar32 != 0);
    }
    fVar5 = FLOAT_80331eb0;
    fVar1 = FLOAT_80331eac;
    iVar24 = uVar30 - iVar23;
    if (iVar23 < (int)uVar30) {
      do {
        iVar26 = iVar11 + iVar23;
        iVar23 = iVar23 + 1;
        puVar22 = (undefined2 *)(*(int *)&menuPcs->field_0x84c + iVar26 * 0x40 + 8);
        *(undefined4 *)(puVar22 + 0xe) = 0xfffffffe;
        *puVar22 = 0;
        puVar22[1] = 0;
        puVar22[2] = 0;
        puVar22[3] = 0;
        *(float *)(puVar22 + 4) = fVar1;
        *(float *)(puVar22 + 6) = fVar1;
        *(undefined4 *)(puVar22 + 0x14) = 8;
        *(float *)(puVar22 + 10) = fVar5;
        iVar24 = iVar24 + -1;
      } while (iVar24 != 0);
    }
  }
  fVar5 = FLOAT_80331eb0;
  fVar1 = FLOAT_80331eac;
  iVar23 = iVar11 + uVar30;
  iVar26 = 0;
  iVar24 = 0;
  uVar32 = uVar30;
  if (0 < (int)uVar30) {
    do {
      puVar22 = (undefined2 *)(*(int *)&menuPcs->field_0x84c + (iVar23 + iVar26) * 0x40 + 8);
      *(undefined4 *)(puVar22 + 0xe) = 0xfffffffe;
      *puVar22 = 0;
      puVar22[1] = 0;
      puVar22[2] = 0;
      puVar22[3] = 0;
      *(float *)(puVar22 + 4) = fVar1;
      *(float *)(puVar22 + 6) = fVar1;
      *(int *)(puVar22 + 0x12) =
           *(int *)(puVar22 + iVar23 * -0x20 + 0x12) + *(int *)(puVar22 + iVar23 * -0x20 + 0x14);
      if (iVar26 != 0) {
        *(int *)(puVar22 + 0x12) = *(int *)(puVar22 + 0x12) + iVar24;
      }
      iVar24 = iVar24 + 3;
      *(undefined4 *)(puVar22 + 0x14) = 0x20;
      iVar26 = iVar26 + 1;
      *(float *)(puVar22 + 10) = fVar5;
      uVar32 = uVar32 - 1;
    } while (uVar32 != 0);
  }
  fVar5 = FLOAT_80331f68;
  fVar1 = FLOAT_80331eac;
  iVar23 = iVar23 + uVar30;
  iVar24 = 0;
  uVar32 = uVar30;
  if (0 < (int)uVar30) {
    do {
      puVar20 = (undefined2 *)(*(int *)&menuPcs->field_0x84c + (iVar23 + iVar24) * 0x40 + 8);
      iVar24 = iVar24 + 1;
      puVar22 = puVar20 + (iVar23 - (uVar30 + 1)) * -0x20;
      *puVar20 = *puVar22;
      puVar20[1] = puVar22[1];
      puVar20[2] = puVar22[2];
      puVar20[3] = puVar22[3];
      *(undefined4 *)(puVar20 + 4) = *(undefined4 *)(puVar22 + 4);
      *(undefined4 *)(puVar20 + 6) = *(undefined4 *)(puVar22 + 6);
      *(undefined4 *)(puVar20 + 8) = *(undefined4 *)(puVar22 + 8);
      *(undefined4 *)(puVar20 + 10) = *(undefined4 *)(puVar22 + 10);
      *(undefined4 *)(puVar20 + 0xc) = *(undefined4 *)(puVar22 + 0xc);
      *(undefined4 *)(puVar20 + 0xe) = *(undefined4 *)(puVar22 + 0xe);
      *(undefined4 *)(puVar20 + 0x10) = *(undefined4 *)(puVar22 + 0x10);
      *(undefined4 *)(puVar20 + 0x12) = *(undefined4 *)(puVar22 + 0x12);
      *(undefined4 *)(puVar20 + 0x14) = *(undefined4 *)(puVar22 + 0x14);
      *(undefined4 *)(puVar20 + 0x16) = *(undefined4 *)(puVar22 + 0x16);
      *(undefined4 *)(puVar20 + 0x18) = *(undefined4 *)(puVar22 + 0x18);
      *(undefined4 *)(puVar20 + 0x1a) = *(undefined4 *)(puVar22 + 0x1a);
      *(undefined4 *)(puVar20 + 0x1c) = *(undefined4 *)(puVar22 + 0x1c);
      *(undefined4 *)(puVar20 + 0x1e) = *(undefined4 *)(puVar22 + 0x1e);
      puVar20[1] = puVar20[1] + 0x20;
      puVar20[2] = 0xa8;
      puVar20[3] = 0x38;
      *(float *)(puVar20 + 4) = fVar1;
      *(float *)(puVar20 + 6) = fVar5;
      uVar32 = uVar32 - 1;
    } while (uVar32 != 0);
  }
  iVar23 = iVar23 + uVar30;
  iVar24 = 0;
  if (0 < (int)uVar30) {
    if (8 < (int)uVar30) {
      iVar26 = uVar30 * 0x40;
      uVar32 = uVar30 - 1 >> 3;
      if (0 < (int)(uVar30 - 8)) {
        do {
          iVar27 = *(int *)&menuPcs->field_0x84c + (iVar24 + 1) * 0x40 + 8;
          iVar13 = iVar24 + 3;
          iVar17 = iVar26 + iVar27;
          iVar12 = iVar24 + 4;
          iVar19 = iVar24 + 5;
          iVar18 = iVar24 + 6;
          iVar14 = iVar24 + 7;
          *(int *)(iVar27 + 0x24) = *(int *)(iVar17 + 0x24) + *(int *)(iVar17 + 0x28);
          iVar17 = iVar24 + 8;
          iVar28 = *(int *)&menuPcs->field_0x84c + (iVar24 + 2) * 0x40 + 8;
          iVar27 = iVar26 + iVar28;
          iVar24 = iVar24 + 8;
          *(int *)(iVar28 + 0x24) = *(int *)(iVar27 + 0x24) + *(int *)(iVar27 + 0x28);
          iVar27 = *(int *)&menuPcs->field_0x84c + iVar13 * 0x40 + 8;
          iVar13 = iVar26 + iVar27;
          *(int *)(iVar27 + 0x24) = *(int *)(iVar13 + 0x24) + *(int *)(iVar13 + 0x28);
          iVar12 = *(int *)&menuPcs->field_0x84c + iVar12 * 0x40 + 8;
          iVar13 = iVar26 + iVar12;
          *(int *)(iVar12 + 0x24) = *(int *)(iVar13 + 0x24) + *(int *)(iVar13 + 0x28);
          iVar12 = *(int *)&menuPcs->field_0x84c + iVar19 * 0x40 + 8;
          iVar13 = iVar26 + iVar12;
          *(int *)(iVar12 + 0x24) = *(int *)(iVar13 + 0x24) + *(int *)(iVar13 + 0x28);
          iVar12 = *(int *)&menuPcs->field_0x84c + iVar18 * 0x40 + 8;
          iVar13 = iVar26 + iVar12;
          *(int *)(iVar12 + 0x24) = *(int *)(iVar13 + 0x24) + *(int *)(iVar13 + 0x28);
          iVar12 = *(int *)&menuPcs->field_0x84c + iVar14 * 0x40 + 8;
          iVar13 = iVar26 + iVar12;
          *(int *)(iVar12 + 0x24) = *(int *)(iVar13 + 0x24) + *(int *)(iVar13 + 0x28);
          iVar12 = *(int *)&menuPcs->field_0x84c + iVar17 * 0x40 + 8;
          iVar17 = iVar26 + iVar12;
          *(int *)(iVar12 + 0x24) = *(int *)(iVar17 + 0x24) + *(int *)(iVar17 + 0x28);
          uVar32 = uVar32 - 1;
        } while (uVar32 != 0);
      }
    }
    iVar26 = uVar30 - iVar24;
    if (iVar24 < (int)uVar30) {
      do {
        iVar12 = iVar24 + 1;
        iVar24 = iVar24 + 1;
        iVar17 = *(int *)&menuPcs->field_0x84c + iVar12 * 0x40 + 8;
        iVar12 = uVar30 * 0x40 + iVar17;
        *(int *)(iVar17 + 0x24) = *(int *)(iVar12 + 0x24) + *(int *)(iVar12 + 0x28);
        iVar26 = iVar26 + -1;
      } while (iVar26 != 0);
    }
  }
  iVar24 = 0;
  if (0 < (int)uVar30) {
    if (8 < (int)uVar30) {
      iVar26 = iVar11 + -1;
      uVar32 = uVar30 - 1 >> 3;
      if (0 < (int)(uVar30 - 8)) {
        do {
          iVar13 = iVar11 + iVar24;
          iVar24 = iVar24 + 8;
          iVar17 = *(int *)&menuPcs->field_0x84c + iVar13 * 0x40 + 8;
          iVar12 = iVar17 + iVar26 * -0x40;
          *(int *)(iVar17 + 0x24) = *(int *)(iVar12 + 0x24) + *(int *)(iVar12 + 0x28);
          iVar17 = *(int *)&menuPcs->field_0x84c + (iVar13 + 1) * 0x40 + 8;
          iVar12 = iVar17 + iVar26 * -0x40;
          *(int *)(iVar17 + 0x24) = *(int *)(iVar12 + 0x24) + *(int *)(iVar12 + 0x28);
          iVar17 = *(int *)&menuPcs->field_0x84c + (iVar13 + 2) * 0x40 + 8;
          iVar12 = iVar17 + iVar26 * -0x40;
          *(int *)(iVar17 + 0x24) = *(int *)(iVar12 + 0x24) + *(int *)(iVar12 + 0x28);
          iVar12 = *(int *)&menuPcs->field_0x84c + (iVar13 + 3) * 0x40 + 8;
          iVar17 = iVar12 + iVar26 * -0x40;
          *(int *)(iVar12 + 0x24) = *(int *)(iVar17 + 0x24) + *(int *)(iVar17 + 0x28);
          iVar12 = *(int *)&menuPcs->field_0x84c + (iVar13 + 4) * 0x40 + 8;
          iVar17 = iVar12 + iVar26 * -0x40;
          *(int *)(iVar12 + 0x24) = *(int *)(iVar17 + 0x24) + *(int *)(iVar17 + 0x28);
          iVar12 = *(int *)&menuPcs->field_0x84c + (iVar13 + 5) * 0x40 + 8;
          iVar17 = iVar12 + iVar26 * -0x40;
          *(int *)(iVar12 + 0x24) = *(int *)(iVar17 + 0x24) + *(int *)(iVar17 + 0x28);
          iVar12 = *(int *)&menuPcs->field_0x84c + (iVar13 + 6) * 0x40 + 8;
          iVar17 = iVar12 + iVar26 * -0x40;
          *(int *)(iVar12 + 0x24) = *(int *)(iVar17 + 0x24) + *(int *)(iVar17 + 0x28);
          iVar12 = *(int *)&menuPcs->field_0x84c + (iVar13 + 7) * 0x40 + 8;
          iVar17 = iVar12 + iVar26 * -0x40;
          *(int *)(iVar12 + 0x24) = *(int *)(iVar17 + 0x24) + *(int *)(iVar17 + 0x28);
          uVar32 = uVar32 - 1;
        } while (uVar32 != 0);
      }
    }
    iVar26 = uVar30 - iVar24;
    if (iVar24 < (int)uVar30) {
      do {
        iVar12 = iVar11 + iVar24;
        iVar24 = iVar24 + 1;
        iVar17 = *(int *)&menuPcs->field_0x84c + iVar12 * 0x40 + 8;
        iVar12 = iVar17 + (iVar11 + -1) * -0x40;
        *(int *)(iVar17 + 0x24) = *(int *)(iVar12 + 0x24) + *(int *)(iVar12 + 0x28);
        iVar26 = iVar26 + -1;
      } while (iVar26 != 0);
    }
  }
  puVar22 = (undefined2 *)(*(int *)&menuPcs->field_0x84c + iVar23 * 0x40 + 8);
  *(undefined4 *)(puVar22 + 0xe) = 0x19;
  puVar22[1] = 0x10;
  fVar1 = FLOAT_80331eac;
  puVar22[2] = 0x140;
  fVar10 = FLOAT_80331fa4;
  fVar9 = FLOAT_80331fa0;
  fVar5 = FLOAT_80331eb0;
  iVar11 = iVar23 + 1;
  *puVar22 = (short)(0x280 - (short)puVar22[2] >> 1);
  iVar24 = 0;
  puVar22[3] = 0x28;
  *(float *)(puVar22 + 4) = fVar1;
  *(float *)(puVar22 + 6) = fVar9;
  *(undefined4 *)(puVar22 + 0x12) = *(undefined4 *)(*(int *)&menuPcs->field_0x84c + 0x6c);
  *(undefined4 *)(puVar22 + 0x14) = 8;
  *(undefined4 *)(puVar22 + 0x14) = 10;
  *(float *)(puVar22 + 10) = fVar5;
  DAT_8032eeac = (char)iVar11;
  if (0 < (int)uVar30) {
    uVar32 = uVar30 >> 1;
    uVar31 = uVar30;
    if (uVar32 != 0) {
      do {
        iVar26 = iVar24 + 1;
        puVar22 = (undefined2 *)(*(int *)&menuPcs->field_0x84c + (iVar11 + iVar24) * 0x40 + 8);
        *(undefined4 *)(puVar22 + 0xe) = 0x19;
        *puVar22 = 0x200;
        iVar24 = iVar24 + 2;
        puVar22[1] = puVar22[iVar23 * -0x20 + 1] + 0xc;
        puVar22[2] = 0x20;
        puVar22[3] = 0x28;
        *(float *)(puVar22 + 4) = fVar1;
        *(float *)(puVar22 + 6) = fVar10;
        *(int *)(puVar22 + 0x12) =
             *(int *)(puVar22 + iVar23 * -0x20 + 0x12) + *(int *)(puVar22 + iVar23 * -0x20 + 0x14);
        *(undefined4 *)(puVar22 + 0x14) = 8;
        *(float *)(puVar22 + 10) = fVar5;
        puVar22 = (undefined2 *)(*(int *)&menuPcs->field_0x84c + (iVar11 + iVar26) * 0x40 + 8);
        *(undefined4 *)(puVar22 + 0xe) = 0x19;
        *puVar22 = 0x200;
        puVar22[1] = puVar22[iVar23 * -0x20 + 1] + 0xc;
        puVar22[2] = 0x20;
        puVar22[3] = 0x28;
        *(float *)(puVar22 + 4) = fVar1;
        *(float *)(puVar22 + 6) = fVar10;
        *(int *)(puVar22 + 0x12) =
             *(int *)(puVar22 + iVar23 * -0x20 + 0x12) + *(int *)(puVar22 + iVar23 * -0x20 + 0x14);
        *(undefined4 *)(puVar22 + 0x14) = 8;
        *(float *)(puVar22 + 10) = fVar5;
        uVar32 = uVar32 - 1;
      } while (uVar32 != 0);
      uVar31 = uVar30 & 1;
      if (uVar31 == 0) goto LAB_8013c0f4;
    }
    do {
      puVar22 = (undefined2 *)(*(int *)&menuPcs->field_0x84c + (iVar11 + iVar24) * 0x40 + 8);
      *(undefined4 *)(puVar22 + 0xe) = 0x19;
      *puVar22 = 0x200;
      iVar24 = iVar24 + 1;
      puVar22[1] = puVar22[iVar23 * -0x20 + 1] + 0xc;
      puVar22[2] = 0x20;
      puVar22[3] = 0x28;
      *(float *)(puVar22 + 4) = fVar1;
      *(float *)(puVar22 + 6) = fVar10;
      *(int *)(puVar22 + 0x12) =
           *(int *)(puVar22 + iVar23 * -0x20 + 0x12) + *(int *)(puVar22 + iVar23 * -0x20 + 0x14);
      *(undefined4 *)(puVar22 + 0x14) = 8;
      *(float *)(puVar22 + 10) = fVar5;
      uVar31 = uVar31 - 1;
    } while (uVar31 != 0);
  }
LAB_8013c0f4:
  fVar5 = FLOAT_80331eb0;
  fVar1 = FLOAT_80331eac;
  iVar11 = iVar11 + uVar30;
  iVar23 = iVar11 - (uVar30 + 1);
  iVar24 = 0;
  if (0 < (int)uVar30) {
    uVar32 = uVar30 >> 1;
    uVar31 = uVar30;
    if (uVar32 != 0) {
      do {
        iVar26 = iVar24 + 1;
        psVar25 = (short *)(*(int *)&menuPcs->field_0x84c + (iVar11 + iVar24) * 0x40 + 8);
        psVar25[0xe] = -1;
        psVar25[0xf] = -1;
        psVar15 = psVar25 + iVar23 * -0x20;
        iVar24 = iVar24 + 2;
        *psVar25 = *psVar15 + 0x50;
        psVar25[1] = psVar15[1] + 0x48;
        psVar25[2] = 0;
        psVar25[3] = 0;
        *(float *)(psVar25 + 4) = fVar1;
        *(float *)(psVar25 + 6) = fVar1;
        *(undefined4 *)(psVar25 + 0x12) = *(undefined4 *)(psVar15 + 0x12);
        psVar25[0x14] = 0;
        psVar25[0x15] = 8;
        *(float *)(psVar25 + 10) = fVar5;
        psVar25 = (short *)(*(int *)&menuPcs->field_0x84c + (iVar11 + iVar26) * 0x40 + 8);
        psVar25[0xe] = -1;
        psVar25[0xf] = -1;
        psVar15 = psVar25 + iVar23 * -0x20;
        *psVar25 = *psVar15 + 0x50;
        psVar25[1] = psVar15[1] + 0x48;
        psVar25[2] = 0;
        psVar25[3] = 0;
        *(float *)(psVar25 + 4) = fVar1;
        *(float *)(psVar25 + 6) = fVar1;
        *(undefined4 *)(psVar25 + 0x12) = *(undefined4 *)(psVar15 + 0x12);
        psVar25[0x14] = 0;
        psVar25[0x15] = 8;
        *(float *)(psVar25 + 10) = fVar5;
        uVar32 = uVar32 - 1;
      } while (uVar32 != 0);
      uVar31 = uVar30 & 1;
      if (uVar31 == 0) goto LAB_8013c25c;
    }
    do {
      psVar25 = (short *)(*(int *)&menuPcs->field_0x84c + (iVar11 + iVar24) * 0x40 + 8);
      psVar25[0xe] = -1;
      psVar25[0xf] = -1;
      psVar15 = psVar25 + iVar23 * -0x20;
      iVar24 = iVar24 + 1;
      *psVar25 = *psVar15 + 0x50;
      psVar25[1] = psVar15[1] + 0x48;
      psVar25[2] = 0;
      psVar25[3] = 0;
      *(float *)(psVar25 + 4) = fVar1;
      *(float *)(psVar25 + 6) = fVar1;
      *(undefined4 *)(psVar25 + 0x12) = *(undefined4 *)(psVar15 + 0x12);
      psVar25[0x14] = 0;
      psVar25[0x15] = 8;
      *(float *)(psVar25 + 10) = fVar5;
      uVar31 = uVar31 - 1;
    } while (uVar31 != 0);
  }
LAB_8013c25c:
  fVar5 = FLOAT_80331eb0;
  fVar1 = FLOAT_80331eac;
  iVar11 = iVar11 + uVar30;
  iVar23 = iVar11 + -1;
  iVar24 = 0;
  if (0 < (int)uVar30) {
    uVar32 = uVar30 >> 1;
    uVar31 = uVar30;
    if (uVar32 != 0) {
      do {
        iVar26 = iVar24 + 1;
        puVar22 = (undefined2 *)(*(int *)&menuPcs->field_0x84c + (iVar11 + iVar24) * 0x40 + 8);
        *(undefined4 *)(puVar22 + 0xe) = 0xffffffff;
        *puVar22 = 0xb8;
        iVar24 = iVar24 + 2;
        puVar22[1] = puVar22[iVar23 * -0x20 + 1] + 0x15;
        puVar22[2] = 0;
        puVar22[3] = 0;
        *(float *)(puVar22 + 4) = fVar1;
        *(float *)(puVar22 + 6) = fVar1;
        *(int *)(puVar22 + 0x12) =
             *(int *)(puVar22 + iVar23 * -0x20 + 0x12) + *(int *)(puVar22 + iVar23 * -0x20 + 0x14);
        *(undefined4 *)(puVar22 + 0x14) = 8;
        *(float *)(puVar22 + 10) = fVar5;
        puVar22 = (undefined2 *)(*(int *)&menuPcs->field_0x84c + (iVar11 + iVar26) * 0x40 + 8);
        *(undefined4 *)(puVar22 + 0xe) = 0xffffffff;
        *puVar22 = 0xb8;
        puVar22[1] = puVar22[iVar23 * -0x20 + 1] + 0x15;
        puVar22[2] = 0;
        puVar22[3] = 0;
        *(float *)(puVar22 + 4) = fVar1;
        *(float *)(puVar22 + 6) = fVar1;
        *(int *)(puVar22 + 0x12) =
             *(int *)(puVar22 + iVar23 * -0x20 + 0x12) + *(int *)(puVar22 + iVar23 * -0x20 + 0x14);
        *(undefined4 *)(puVar22 + 0x14) = 8;
        *(float *)(puVar22 + 10) = fVar5;
        uVar32 = uVar32 - 1;
      } while (uVar32 != 0);
      uVar31 = uVar30 & 1;
      if (uVar31 == 0) goto LAB_8013c3c8;
    }
    do {
      puVar22 = (undefined2 *)(*(int *)&menuPcs->field_0x84c + (iVar11 + iVar24) * 0x40 + 8);
      *(undefined4 *)(puVar22 + 0xe) = 0xffffffff;
      iVar24 = iVar24 + 1;
      *puVar22 = 0xb8;
      puVar22[1] = puVar22[iVar23 * -0x20 + 1] + 0x15;
      puVar22[2] = 0;
      puVar22[3] = 0;
      *(float *)(puVar22 + 4) = fVar1;
      *(float *)(puVar22 + 6) = fVar1;
      *(int *)(puVar22 + 0x12) =
           *(int *)(puVar22 + iVar23 * -0x20 + 0x12) + *(int *)(puVar22 + iVar23 * -0x20 + 0x14);
      *(undefined4 *)(puVar22 + 0x14) = 8;
      *(float *)(puVar22 + 10) = fVar5;
      uVar31 = uVar31 - 1;
    } while (uVar31 != 0);
  }
LAB_8013c3c8:
  dVar8 = DOUBLE_80331ef0;
  dVar7 = DOUBLE_80331ee8;
  dVar6 = DOUBLE_80331ee0;
  dVar4 = DOUBLE_80331e88;
  dVar33 = DOUBLE_80331e78;
  iVar24 = 0;
  iVar23 = 0;
  uVar32 = uVar30;
  if (0 < (int)uVar30) {
    do {
      psVar15 = (short *)(*(int *)&menuPcs->field_0x84c + (uVar30 + iVar24 + 1) * 0x40 + 8);
      iVar18 = iVar23 + 8;
      iVar14 = iVar23 + 10;
      iVar13 = iVar23 + 0x40;
      local_140 = (double)(CONCAT44(0x43300000,(int)psVar15[2]) ^ 0x80000000);
      local_148 = (double)(CONCAT44(0x43300000,(int)*psVar15) ^ 0x80000000);
      iVar17 = iVar23 + 0x44;
      iVar12 = iVar23 + 0x48;
      iVar26 = iVar23 + 0x4c;
      local_138 = (double)CONCAT44(0x43300000,(int)psVar15[3] ^ 0x80000000);
      iVar23 = iVar23 + 0x50;
      iVar24 = iVar24 + 1;
      local_130 = (double)CONCAT44(0x43300000,(int)psVar15[1] ^ 0x80000000);
      *(short *)(*(int *)&menuPcs->field_0x814 + iVar18) =
           (short)(int)((double)(float)(dVar6 + (local_140 - dVar4) * dVar33 + (local_148 - dVar4))
                       - dVar7);
      *(short *)(*(int *)&menuPcs->field_0x814 + iVar14) =
           (short)(int)((double)(float)((local_138 - dVar4) * dVar33 + (local_130 - dVar4)) - dVar8)
      ;
      *(int *)(*(int *)&menuPcs->field_0x814 + iVar13) = *psVar15 + 0xc;
      *(int *)(*(int *)&menuPcs->field_0x814 + iVar17) = psVar15[1] + -8;
      *(undefined4 *)(*(int *)&menuPcs->field_0x814 + iVar12) = 0x48;
      *(undefined4 *)(*(int *)&menuPcs->field_0x814 + iVar26) = 0x58;
      uVar32 = uVar32 - 1;
    } while (uVar32 != 0);
  }
  dVar7 = DOUBLE_80331ef0;
  dVar6 = DOUBLE_80331ee8;
  dVar4 = DOUBLE_80331e88;
  dVar33 = DOUBLE_80331e78;
  iVar26 = 0;
  iVar23 = 0;
  iVar24 = uVar30 * 0x50;
  uVar32 = uVar30;
  if (0 < (int)uVar30) {
    do {
      iVar12 = DAT_8032eeac + iVar26;
      iVar26 = iVar26 + 1;
      psVar15 = (short *)(*(int *)&menuPcs->field_0x84c + iVar12 * 0x40 + 8);
      local_128 = (double)(CONCAT44(0x43300000,(int)*psVar15) ^ 0x80000000);
      local_120 = (double)(CONCAT44(0x43300000,psVar15[2] * 3) ^ 0x80000000);
      iVar17 = psVar15[2] * 3 + 0x20;
      local_130 = (double)(CONCAT44(0x43300000,(int)psVar15[3]) ^ 0x80000000);
      local_138 = (double)CONCAT44(0x43300000,(int)psVar15[1] ^ 0x80000000);
      *(short *)(iVar24 + *(int *)&menuPcs->field_0x814 + iVar23 + 8) =
           (short)(int)((double)(float)((local_120 - dVar4) * dVar33 + (local_128 - dVar4)) - dVar6)
      ;
      *(short *)(iVar24 + *(int *)&menuPcs->field_0x814 + iVar23 + 10) =
           (short)(int)((double)(float)((local_130 - dVar4) * dVar33 + (local_138 - dVar4)) - dVar7)
      ;
      *(int *)(iVar24 + *(int *)&menuPcs->field_0x814 + iVar23 + 0x40) = *psVar15 + -0x10;
      *(int *)(iVar24 + *(int *)&menuPcs->field_0x814 + iVar23 + 0x44) = psVar15[1] + -0x10;
      *(int *)(iVar24 + *(int *)&menuPcs->field_0x814 + iVar23 + 0x48) = iVar17;
      iVar12 = *(int *)&menuPcs->field_0x814 + iVar23;
      iVar23 = iVar23 + 0x50;
      *(int *)(iVar24 + iVar12 + 0x4c) = iVar17;
      uVar32 = uVar32 - 1;
    } while (uVar32 != 0);
  }
  dVar6 = DOUBLE_80331ef0;
  dVar4 = DOUBLE_80331e88;
  dVar33 = DOUBLE_80331e78;
  iVar23 = 0;
  if (0 < (int)uVar30) {
    if (8 < (int)uVar30) {
      iVar26 = uVar30 * 2;
      uVar32 = uVar30 - 1 >> 3;
      iVar24 = (int)FLOAT_80331eac;
      iVar12 = uVar30 * 0xa0;
      if (0 < (int)(uVar30 - 8)) {
        do {
          iVar17 = *(int *)&menuPcs->field_0x84c + (iVar23 + 1) * 0x40 + 8;
          local_120 = (double)(CONCAT44(0x43300000,(int)*(short *)(iVar17 + 6)) ^ 0x80000000);
          iVar13 = (iVar23 + iVar26 + 1) * 0x50;
          local_128 = (double)CONCAT44(0x43300000,(int)*(short *)(iVar17 + 2) ^ 0x80000000);
          uVar29 = (undefined2)iVar24;
          *(undefined2 *)(*(int *)&menuPcs->field_0x814 + iVar12 + 8) = uVar29;
          *(short *)(*(int *)&menuPcs->field_0x814 + iVar12 + 10) =
               (short)(int)((double)(float)((local_120 - dVar4) * dVar33 + (local_128 - dVar4)) -
                           dVar6);
          iVar17 = *(int *)&menuPcs->field_0x84c + (iVar23 + 2) * 0x40 + 8;
          local_140 = (double)(CONCAT44(0x43300000,(int)*(short *)(iVar17 + 6)) ^ 0x80000000);
          local_148 = (double)(CONCAT44(0x43300000,(int)*(short *)(iVar17 + 2)) ^ 0x80000000);
          *(undefined2 *)(*(int *)&menuPcs->field_0x814 + iVar13 + 8) = uVar29;
          *(short *)(*(int *)&menuPcs->field_0x814 + iVar13 + 10) =
               (short)(int)((double)(float)((local_140 - dVar4) * dVar33 + (local_148 - dVar4)) -
                           dVar6);
          iVar17 = *(int *)&menuPcs->field_0x84c + (iVar23 + 3) * 0x40 + 8;
          sVar21 = *(short *)(iVar17 + 6);
          sVar2 = *(short *)(iVar17 + 2);
          iVar17 = (iVar23 + iVar26 + 2) * 0x50;
          *(undefined2 *)(*(int *)&menuPcs->field_0x814 + iVar17 + 8) = uVar29;
          iVar13 = (iVar23 + iVar26 + 4) * 0x50;
          *(short *)(*(int *)&menuPcs->field_0x814 + iVar17 + 10) =
               (short)(int)((double)(float)(((double)CONCAT44(0x43300000,(int)sVar21 ^ 0x80000000) -
                                            dVar4) * dVar33 +
                                           ((double)CONCAT44(0x43300000,(int)sVar2 ^ 0x80000000) -
                                           dVar4)) - dVar6);
          iVar14 = *(int *)&menuPcs->field_0x84c + (iVar23 + 4) * 0x40 + 8;
          sVar21 = *(short *)(iVar14 + 6);
          iVar17 = (iVar23 + iVar26 + 3) * 0x50;
          sVar2 = *(short *)(iVar14 + 2);
          *(undefined2 *)(*(int *)&menuPcs->field_0x814 + iVar17 + 8) = uVar29;
          *(short *)(*(int *)&menuPcs->field_0x814 + iVar17 + 10) =
               (short)(int)((double)(float)(((double)CONCAT44(0x43300000,(int)sVar21 ^ 0x80000000) -
                                            dVar4) * dVar33 +
                                           ((double)CONCAT44(0x43300000,(int)sVar2 ^ 0x80000000) -
                                           dVar4)) - dVar6);
          iVar17 = *(int *)&menuPcs->field_0x84c + (iVar23 + 5) * 0x40 + 8;
          sVar21 = *(short *)(iVar17 + 6);
          sVar2 = *(short *)(iVar17 + 2);
          *(undefined2 *)(*(int *)&menuPcs->field_0x814 + iVar13 + 8) = uVar29;
          *(short *)(*(int *)&menuPcs->field_0x814 + iVar13 + 10) =
               (short)(int)((double)(float)(((double)CONCAT44(0x43300000,(int)sVar21 ^ 0x80000000) -
                                            dVar4) * dVar33 +
                                           ((double)CONCAT44(0x43300000,(int)sVar2 ^ 0x80000000) -
                                           dVar4)) - dVar6);
          iVar17 = *(int *)&menuPcs->field_0x84c + (iVar23 + 6) * 0x40 + 8;
          sVar21 = *(short *)(iVar17 + 6);
          iVar13 = (iVar23 + iVar26 + 5) * 0x50;
          sVar2 = *(short *)(iVar17 + 2);
          iVar17 = (iVar23 + iVar26 + 6) * 0x50;
          *(undefined2 *)(*(int *)&menuPcs->field_0x814 + iVar13 + 8) = uVar29;
          *(short *)(*(int *)&menuPcs->field_0x814 + iVar13 + 10) =
               (short)(int)((double)(float)(((double)CONCAT44(0x43300000,(int)sVar21 ^ 0x80000000) -
                                            dVar4) * dVar33 +
                                           ((double)CONCAT44(0x43300000,(int)sVar2 ^ 0x80000000) -
                                           dVar4)) - dVar6);
          iVar13 = *(int *)&menuPcs->field_0x84c + (iVar23 + 7) * 0x40 + 8;
          sVar21 = *(short *)(iVar13 + 6);
          sVar2 = *(short *)(iVar13 + 2);
          *(undefined2 *)(*(int *)&menuPcs->field_0x814 + iVar17 + 8) = uVar29;
          *(short *)(*(int *)&menuPcs->field_0x814 + iVar17 + 10) =
               (short)(int)((double)(float)(((double)CONCAT44(0x43300000,(int)sVar21 ^ 0x80000000) -
                                            dVar4) * dVar33 +
                                           ((double)CONCAT44(0x43300000,(int)sVar2 ^ 0x80000000) -
                                           dVar4)) - dVar6);
          iVar17 = *(int *)&menuPcs->field_0x84c + (iVar23 + 8) * 0x40 + 8;
          local_68 = (double)(CONCAT44(0x43300000,(int)*(short *)(iVar17 + 6)) ^ 0x80000000);
          local_60 = (double)(CONCAT44(0x43300000,(int)*(short *)(iVar17 + 2)) ^ 0x80000000);
          iVar17 = (iVar23 + iVar26 + 7) * 0x50;
          iVar12 = iVar12 + 0x280;
          *(undefined2 *)(*(int *)&menuPcs->field_0x814 + iVar17 + 8) = uVar29;
          iVar23 = iVar23 + 8;
          *(short *)(*(int *)&menuPcs->field_0x814 + iVar17 + 10) =
               (short)(int)((double)(float)((local_68 - dVar4) * dVar33 + (local_60 - dVar4)) -
                           dVar6);
          uVar32 = uVar32 - 1;
        } while (uVar32 != 0);
      }
    }
    dVar6 = DOUBLE_80331ef0;
    dVar4 = DOUBLE_80331e88;
    dVar33 = DOUBLE_80331e78;
    iVar26 = uVar30 - iVar23;
    iVar24 = (int)FLOAT_80331eac;
    iVar12 = (uVar30 * 2 + iVar23) * 0x50;
    if (iVar23 < (int)uVar30) {
      do {
        iVar14 = *(int *)&menuPcs->field_0x84c + (iVar23 + 1) * 0x40 + 8;
        iVar13 = iVar12 + 8;
        iVar17 = iVar12 + 10;
        local_50 = (double)(CONCAT44(0x43300000,(int)*(short *)(iVar14 + 6)) ^ 0x80000000);
        iVar12 = iVar12 + 0x50;
        iVar23 = iVar23 + 1;
        local_58 = (double)CONCAT44(0x43300000,(int)*(short *)(iVar14 + 2) ^ 0x80000000);
        *(short *)(*(int *)&menuPcs->field_0x814 + iVar13) = (short)iVar24;
        *(short *)(*(int *)&menuPcs->field_0x814 + iVar17) =
             (short)(int)((double)(float)((local_50 - dVar4) * dVar33 + (local_58 - dVar4)) - dVar6)
        ;
        iVar26 = iVar26 + -1;
      } while (iVar26 != 0);
    }
  }
  fVar1 = FLOAT_80331eac;
  iVar23 = 3;
  pCVar16 = menuPcs;
  do {
    if (*(int *)&pCVar16->field_0x774 != 0) {
      *(float *)(*(int *)(*(int *)&pCVar16->field_0x774 + 0x168) + 0x9c) = fVar1;
    }
    if (*(int *)&pCVar16->field_0x778 != 0) {
      *(float *)(*(int *)(*(int *)&pCVar16->field_0x778 + 0x168) + 0x9c) = fVar1;
    }
    if (*(int *)&pCVar16->field_0x77c != 0) {
      *(float *)(*(int *)(*(int *)&pCVar16->field_0x77c + 0x168) + 0x9c) = fVar1;
    }
    if (*(int *)&pCVar16->field_0x780 != 0) {
      *(float *)(*(int *)(*(int *)&pCVar16->field_0x780 + 0x168) + 0x9c) = fVar1;
    }
    if (*(int *)&pCVar16->field_0x784 != 0) {
      *(float *)(*(int *)(*(int *)&pCVar16->field_0x784 + 0x168) + 0x9c) = fVar1;
    }
    if (*(int *)&pCVar16->field_0x788 != 0) {
      *(float *)(*(int *)(*(int *)&pCVar16->field_0x788 + 0x168) + 0x9c) = fVar1;
    }
    if (*(int *)&pCVar16->field_0x78c != 0) {
      *(float *)(*(int *)(*(int *)&pCVar16->field_0x78c + 0x168) + 0x9c) = fVar1;
    }
    if (*(int *)&pCVar16->field_0x790 != 0) {
      *(float *)(*(int *)(*(int *)&pCVar16->field_0x790 + 0x168) + 0x9c) = fVar1;
    }
    pCVar16 = (CMenuPcs *)&pCVar16->m_mcCtrl;
    iVar23 = iVar23 + -1;
  } while (iVar23 != 0);
  **(short **)&menuPcs->field_0x84c = (short)iVar11 + (short)uVar30;
  *(undefined2 *)(*(int *)&menuPcs->field_0x84c + 6) = 0;
  *(undefined *)(*(int *)&menuPcs->field_0x82c + 0xb) = 1;
  return;
}

