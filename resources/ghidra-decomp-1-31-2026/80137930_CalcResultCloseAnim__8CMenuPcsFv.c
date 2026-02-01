// Function: CalcResultCloseAnim__8CMenuPcsFv
// Entry: 80137930
// Size: 8676 bytes

void CalcResultCloseAnim__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  double dVar1;
  float fVar2;
  double dVar3;
  double dVar4;
  double dVar5;
  double dVar6;
  double dVar7;
  float fVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  short *psVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  int unaff_r31;
  uint uVar18;
  Mtx MStack_178;
  Mtx MStack_148;
  Mtx MStack_118;
  double local_e8;
  undefined4 local_e0;
  uint uStack_dc;
  double local_d8;
  double local_d0;
  undefined4 local_c8;
  uint uStack_c4;
  double local_c0;
  double local_b8;
  undefined4 local_b0;
  uint uStack_ac;
  double local_a8;
  double local_a0;
  undefined4 local_98;
  uint uStack_94;
  double local_90;
  double local_88;
  undefined4 local_80;
  uint uStack_7c;
  double local_78;
  double local_70;
  double local_68;
  double local_60;
  double local_58;
  double local_50;
  undefined8 local_48;
  undefined8 local_40;
  undefined4 local_38;
  uint uStack_34;
  undefined8 local_30;
  
  fVar2 = FLOAT_80331eac;
  iVar17 = *DAT_8032eea8;
  if (*(char *)(*(int *)&menuPcs->field_0x82c + 0xb) == '\0') {
    iVar10 = 0;
    for (iVar13 = 0; psVar12 = *(short **)&menuPcs->field_0x84c, iVar13 < *psVar12;
        iVar13 = iVar13 + 1) {
      iVar11 = iVar10 + 0x38;
      *(undefined4 *)((int)psVar12 + iVar10 + 0x28) = 0;
      iVar9 = iVar10 + 0x3c;
      iVar10 = iVar10 + 0x40;
      *(float *)(*(int *)&menuPcs->field_0x84c + iVar11) = fVar2;
      *(float *)(*(int *)&menuPcs->field_0x84c + iVar9) = fVar2;
    }
    iVar10 = 0;
    psVar12[0x16] = 0;
    psVar12[0x17] = 9999;
    psVar12[0x1a] = 0;
    psVar12[0x1b] = 3;
    if (0 < iVar17) {
      if ((8 < iVar17) && (uVar18 = iVar17 - 1U >> 3, iVar13 = iVar10, 0 < iVar17 + -8)) {
        do {
          iVar10 = iVar13 + 8;
          *(undefined4 *)(*(int *)&menuPcs->field_0x84c + (iVar13 + 1) * 0x40 + 0x2c) = 0x10;
          *(undefined4 *)(*(int *)&menuPcs->field_0x84c + (iVar13 + 2) * 0x40 + 0x2c) = 0x10;
          *(undefined4 *)(*(int *)&menuPcs->field_0x84c + (iVar13 + 3) * 0x40 + 0x2c) = 0x10;
          *(undefined4 *)(*(int *)&menuPcs->field_0x84c + (iVar13 + 4) * 0x40 + 0x2c) = 0x10;
          *(undefined4 *)(*(int *)&menuPcs->field_0x84c + (iVar13 + 5) * 0x40 + 0x2c) = 0x10;
          *(undefined4 *)(*(int *)&menuPcs->field_0x84c + (iVar13 + 6) * 0x40 + 0x2c) = 0x10;
          *(undefined4 *)(*(int *)&menuPcs->field_0x84c + (iVar13 + 7) * 0x40 + 0x2c) = 0x10;
          *(undefined4 *)(*(int *)&menuPcs->field_0x84c + (iVar13 + 8) * 0x40 + 0x2c) = 0x10;
          uVar18 = uVar18 - 1;
          iVar13 = iVar10;
        } while (uVar18 != 0);
      }
      iVar13 = iVar17 - iVar10;
      if (iVar10 < iVar17) {
        do {
          iVar9 = iVar10 + 1;
          iVar10 = iVar10 + 1;
          *(undefined4 *)(*(int *)&menuPcs->field_0x84c + iVar9 * 0x40 + 0x2c) = 0x10;
          iVar13 = iVar13 + -1;
        } while (iVar13 != 0);
      }
    }
    fVar2 = FLOAT_80331ed0;
    dVar1 = DOUBLE_80331e88;
    iVar10 = iVar17 + 1;
    iVar13 = 0;
    if (0 < iVar17) {
      if ((8 < iVar17) && (uVar18 = iVar17 - 1U >> 3, 0 < iVar17 + -8)) {
        do {
          iVar11 = iVar10 + iVar13;
          psVar12 = (short *)(*(int *)&menuPcs->field_0x84c + iVar11 * 0x40 + 8);
          *(int *)(psVar12 + 0x12) =
               *(int *)(psVar12 + iVar17 * -0x20 + 0x12) + *(int *)(psVar12 + iVar17 * -0x20 + 0x14)
          ;
          psVar12[0x16] = 0;
          psVar12[0x17] = 1;
          local_e0 = 0x43300000;
          local_e8 = (double)(CONCAT44(0x43300000,(int)*psVar12) ^ 0x80000000);
          local_c8 = 0x43300000;
          *(float *)(psVar12 + 0x1c) = (float)(local_e8 - dVar1);
          *(float *)(psVar12 + 0x18) = fVar2;
          uStack_dc = (int)*psVar12 ^ 0x80000000;
          iVar9 = (int)((float)((double)CONCAT44(0x43300000,uStack_dc) - dVar1) -
                       *(float *)(psVar12 + 0x18));
          local_d8 = (double)(longlong)iVar9;
          *psVar12 = (short)iVar9;
          psVar12 = (short *)(*(int *)&menuPcs->field_0x84c + (iVar11 + 1) * 0x40 + 8);
          *(int *)(psVar12 + 0x12) =
               *(int *)(psVar12 + iVar17 * -0x20 + 0x12) + *(int *)(psVar12 + iVar17 * -0x20 + 0x14)
          ;
          psVar12[0x16] = 0;
          psVar12[0x17] = 1;
          local_d0 = (double)(CONCAT44(0x43300000,(int)*psVar12) ^ 0x80000000);
          *(float *)(psVar12 + 0x1c) = (float)(local_d0 - dVar1);
          *(float *)(psVar12 + 0x18) = fVar2;
          uStack_c4 = (int)*psVar12 ^ 0x80000000;
          iVar9 = (int)((float)((double)CONCAT44(0x43300000,uStack_c4) - dVar1) -
                       *(float *)(psVar12 + 0x18));
          local_c0 = (double)(longlong)iVar9;
          *psVar12 = (short)iVar9;
          psVar12 = (short *)(*(int *)&menuPcs->field_0x84c + (iVar11 + 2) * 0x40 + 8);
          *(int *)(psVar12 + 0x12) =
               *(int *)(psVar12 + iVar17 * -0x20 + 0x12) + *(int *)(psVar12 + iVar17 * -0x20 + 0x14)
          ;
          psVar12[0x16] = 0;
          psVar12[0x17] = 1;
          local_b8 = (double)(CONCAT44(0x43300000,(int)*psVar12) ^ 0x80000000);
          *(float *)(psVar12 + 0x1c) = (float)(local_b8 - dVar1);
          *(float *)(psVar12 + 0x18) = fVar2;
          local_b0 = 0x43300000;
          uStack_ac = (int)*psVar12 ^ 0x80000000;
          local_98 = 0x43300000;
          local_80 = 0x43300000;
          iVar9 = (int)((float)((double)CONCAT44(0x43300000,uStack_ac) - dVar1) -
                       *(float *)(psVar12 + 0x18));
          local_a8 = (double)(longlong)iVar9;
          *psVar12 = (short)iVar9;
          psVar12 = (short *)(*(int *)&menuPcs->field_0x84c + (iVar11 + 3) * 0x40 + 8);
          *(int *)(psVar12 + 0x12) =
               *(int *)(psVar12 + iVar17 * -0x20 + 0x12) + *(int *)(psVar12 + iVar17 * -0x20 + 0x14)
          ;
          psVar12[0x16] = 0;
          psVar12[0x17] = 1;
          local_a0 = (double)(CONCAT44(0x43300000,(int)*psVar12) ^ 0x80000000);
          *(float *)(psVar12 + 0x1c) = (float)(local_a0 - dVar1);
          *(float *)(psVar12 + 0x18) = fVar2;
          uStack_94 = (int)*psVar12 ^ 0x80000000;
          iVar9 = (int)((float)((double)CONCAT44(0x43300000,uStack_94) - dVar1) -
                       *(float *)(psVar12 + 0x18));
          local_90 = (double)(longlong)iVar9;
          *psVar12 = (short)iVar9;
          psVar12 = (short *)(*(int *)&menuPcs->field_0x84c + (iVar11 + 4) * 0x40 + 8);
          *(int *)(psVar12 + 0x12) =
               *(int *)(psVar12 + iVar17 * -0x20 + 0x12) + *(int *)(psVar12 + iVar17 * -0x20 + 0x14)
          ;
          psVar12[0x16] = 0;
          psVar12[0x17] = 1;
          local_88 = (double)(CONCAT44(0x43300000,(int)*psVar12) ^ 0x80000000);
          *(float *)(psVar12 + 0x1c) = (float)(local_88 - dVar1);
          *(float *)(psVar12 + 0x18) = fVar2;
          uStack_7c = (int)*psVar12 ^ 0x80000000;
          iVar9 = (int)((float)((double)CONCAT44(0x43300000,uStack_7c) - dVar1) -
                       *(float *)(psVar12 + 0x18));
          local_78 = (double)(longlong)iVar9;
          *psVar12 = (short)iVar9;
          psVar12 = (short *)(*(int *)&menuPcs->field_0x84c + (iVar11 + 5) * 0x40 + 8);
          *(int *)(psVar12 + 0x12) =
               *(int *)(psVar12 + iVar17 * -0x20 + 0x12) + *(int *)(psVar12 + iVar17 * -0x20 + 0x14)
          ;
          iVar13 = iVar13 + 8;
          psVar12[0x16] = 0;
          psVar12[0x17] = 1;
          local_70 = (double)(CONCAT44(0x43300000,(int)*psVar12) ^ 0x80000000);
          *(float *)(psVar12 + 0x1c) = (float)(local_70 - dVar1);
          *(float *)(psVar12 + 0x18) = fVar2;
          local_68 = (double)(CONCAT44(0x43300000,(int)*psVar12) ^ 0x80000000);
          local_38 = 0x43300000;
          iVar9 = (int)((float)(local_68 - dVar1) - *(float *)(psVar12 + 0x18));
          local_60 = (double)(longlong)iVar9;
          *psVar12 = (short)iVar9;
          psVar12 = (short *)(*(int *)&menuPcs->field_0x84c + (iVar11 + 6) * 0x40 + 8);
          *(int *)(psVar12 + 0x12) =
               *(int *)(psVar12 + iVar17 * -0x20 + 0x12) + *(int *)(psVar12 + iVar17 * -0x20 + 0x14)
          ;
          psVar12[0x16] = 0;
          psVar12[0x17] = 1;
          local_58 = (double)(CONCAT44(0x43300000,(int)*psVar12) ^ 0x80000000);
          *(float *)(psVar12 + 0x1c) = (float)(local_58 - dVar1);
          *(float *)(psVar12 + 0x18) = fVar2;
          local_50 = (double)(CONCAT44(0x43300000,(int)*psVar12) ^ 0x80000000);
          iVar9 = (int)((float)(local_50 - dVar1) - *(float *)(psVar12 + 0x18));
          local_48 = (double)(longlong)iVar9;
          *psVar12 = (short)iVar9;
          psVar12 = (short *)(*(int *)&menuPcs->field_0x84c + (iVar11 + 7) * 0x40 + 8);
          *(int *)(psVar12 + 0x12) =
               *(int *)(psVar12 + iVar17 * -0x20 + 0x12) + *(int *)(psVar12 + iVar17 * -0x20 + 0x14)
          ;
          psVar12[0x16] = 0;
          psVar12[0x17] = 1;
          local_40 = (double)(CONCAT44(0x43300000,(int)*psVar12) ^ 0x80000000);
          *(float *)(psVar12 + 0x1c) = (float)(local_40 - dVar1);
          *(float *)(psVar12 + 0x18) = fVar2;
          uStack_34 = (int)*psVar12 ^ 0x80000000;
          iVar9 = (int)((float)((double)CONCAT44(0x43300000,uStack_34) - dVar1) -
                       *(float *)(psVar12 + 0x18));
          local_30 = (double)(longlong)iVar9;
          *psVar12 = (short)iVar9;
          uVar18 = uVar18 - 1;
          unaff_r31 = iVar17;
        } while (uVar18 != 0);
      }
      fVar2 = FLOAT_80331ed0;
      dVar1 = DOUBLE_80331e88;
      iVar9 = iVar17 - iVar13;
      if (iVar13 < iVar17) {
        do {
          psVar12 = (short *)(*(int *)&menuPcs->field_0x84c + (iVar10 + iVar13) * 0x40 + 8);
          local_38 = 0x43300000;
          iVar13 = iVar13 + 1;
          *(int *)(psVar12 + 0x12) =
               *(int *)(psVar12 + iVar17 * -0x20 + 0x12) + *(int *)(psVar12 + iVar17 * -0x20 + 0x14)
          ;
          psVar12[0x16] = 0;
          psVar12[0x17] = 1;
          local_30 = (double)(CONCAT44(0x43300000,(int)*psVar12) ^ 0x80000000);
          *(float *)(psVar12 + 0x1c) = (float)(local_30 - dVar1);
          *(float *)(psVar12 + 0x18) = fVar2;
          uStack_34 = (int)*psVar12 ^ 0x80000000;
          iVar11 = (int)((float)((double)CONCAT44(0x43300000,uStack_34) - dVar1) -
                        *(float *)(psVar12 + 0x18));
          local_40 = (double)(longlong)iVar11;
          *psVar12 = (short)iVar11;
          iVar9 = iVar9 + -1;
          unaff_r31 = iVar17;
        } while (iVar9 != 0);
      }
    }
    iVar10 = iVar10 + iVar17;
    iVar13 = 0;
    if (0 < iVar17) {
      if ((8 < iVar17) && (uVar18 = iVar17 - 1U >> 3, 0 < iVar17 + -8)) {
        do {
          iVar15 = iVar10 + iVar13;
          iVar11 = *(int *)&menuPcs->field_0x84c + iVar15 * 0x40 + 8;
          iVar9 = iVar11 + iVar17 * -0x40;
          *(int *)(iVar11 + 0x24) = *(int *)(iVar9 + 0x24) + *(int *)(iVar9 + 0x28);
          *(undefined4 *)(iVar11 + 0x2c) = 1;
          iVar11 = *(int *)&menuPcs->field_0x84c + (iVar15 + 1) * 0x40 + 8;
          iVar9 = iVar11 + iVar17 * -0x40;
          iVar13 = iVar13 + 8;
          *(int *)(iVar11 + 0x24) = *(int *)(iVar9 + 0x24) + *(int *)(iVar9 + 0x28);
          *(undefined4 *)(iVar11 + 0x2c) = 1;
          iVar9 = *(int *)&menuPcs->field_0x84c + (iVar15 + 2) * 0x40 + 8;
          iVar11 = iVar9 + iVar17 * -0x40;
          *(int *)(iVar9 + 0x24) = *(int *)(iVar11 + 0x24) + *(int *)(iVar11 + 0x28);
          *(undefined4 *)(iVar9 + 0x2c) = 1;
          iVar9 = *(int *)&menuPcs->field_0x84c + (iVar15 + 3) * 0x40 + 8;
          iVar11 = iVar9 + iVar17 * -0x40;
          *(int *)(iVar9 + 0x24) = *(int *)(iVar11 + 0x24) + *(int *)(iVar11 + 0x28);
          *(undefined4 *)(iVar9 + 0x2c) = 1;
          iVar9 = *(int *)&menuPcs->field_0x84c + (iVar15 + 4) * 0x40 + 8;
          iVar11 = iVar9 + iVar17 * -0x40;
          *(int *)(iVar9 + 0x24) = *(int *)(iVar11 + 0x24) + *(int *)(iVar11 + 0x28);
          *(undefined4 *)(iVar9 + 0x2c) = 1;
          iVar9 = *(int *)&menuPcs->field_0x84c + (iVar15 + 5) * 0x40 + 8;
          iVar11 = iVar9 + iVar17 * -0x40;
          *(int *)(iVar9 + 0x24) = *(int *)(iVar11 + 0x24) + *(int *)(iVar11 + 0x28);
          *(undefined4 *)(iVar9 + 0x2c) = 1;
          iVar9 = *(int *)&menuPcs->field_0x84c + (iVar15 + 6) * 0x40 + 8;
          iVar11 = iVar9 + iVar17 * -0x40;
          *(int *)(iVar9 + 0x24) = *(int *)(iVar11 + 0x24) + *(int *)(iVar11 + 0x28);
          *(undefined4 *)(iVar9 + 0x2c) = 1;
          iVar9 = *(int *)&menuPcs->field_0x84c + (iVar15 + 7) * 0x40 + 8;
          iVar11 = iVar9 + iVar17 * -0x40;
          *(int *)(iVar9 + 0x24) = *(int *)(iVar11 + 0x24) + *(int *)(iVar11 + 0x28);
          *(undefined4 *)(iVar9 + 0x2c) = 1;
          uVar18 = uVar18 - 1;
        } while (uVar18 != 0);
      }
      iVar9 = iVar17 - iVar13;
      if (iVar13 < iVar17) {
        do {
          iVar11 = iVar10 + iVar13;
          iVar13 = iVar13 + 1;
          iVar15 = *(int *)&menuPcs->field_0x84c + iVar11 * 0x40 + 8;
          iVar11 = iVar15 + iVar17 * -0x40;
          *(int *)(iVar15 + 0x24) = *(int *)(iVar11 + 0x24) + *(int *)(iVar11 + 0x28);
          *(undefined4 *)(iVar15 + 0x2c) = 1;
          iVar9 = iVar9 + -1;
        } while (iVar9 != 0);
      }
    }
    iVar10 = iVar10 + iVar17;
    iVar13 = 0;
    if (0 < iVar17) {
      if ((8 < iVar17) && (uVar18 = iVar17 - 1U >> 3, 0 < iVar17 + -8)) {
        do {
          iVar9 = iVar10 + iVar13;
          iVar13 = iVar13 + 8;
          *(undefined4 *)(*(int *)&menuPcs->field_0x84c + iVar9 * 0x40 + 0x2c) = 0;
          *(undefined4 *)(*(int *)&menuPcs->field_0x84c + (iVar9 + 1) * 0x40 + 0x2c) = 0;
          *(undefined4 *)(*(int *)&menuPcs->field_0x84c + (iVar9 + 2) * 0x40 + 0x2c) = 0;
          *(undefined4 *)(*(int *)&menuPcs->field_0x84c + (iVar9 + 3) * 0x40 + 0x2c) = 0;
          *(undefined4 *)(*(int *)&menuPcs->field_0x84c + (iVar9 + 4) * 0x40 + 0x2c) = 0;
          *(undefined4 *)(*(int *)&menuPcs->field_0x84c + (iVar9 + 5) * 0x40 + 0x2c) = 0;
          *(undefined4 *)(*(int *)&menuPcs->field_0x84c + (iVar9 + 6) * 0x40 + 0x2c) = 0;
          *(undefined4 *)(*(int *)&menuPcs->field_0x84c + (iVar9 + 7) * 0x40 + 0x2c) = 0;
          uVar18 = uVar18 - 1;
        } while (uVar18 != 0);
      }
      iVar9 = iVar17 - iVar13;
      if (iVar13 < iVar17) {
        do {
          iVar11 = iVar10 + iVar13;
          iVar13 = iVar13 + 1;
          *(undefined4 *)(*(int *)&menuPcs->field_0x84c + iVar11 * 0x40 + 0x2c) = 0;
          iVar9 = iVar9 + -1;
        } while (iVar9 != 0);
      }
    }
    iVar10 = iVar10 + iVar17;
    iVar13 = 0;
    if (0 < iVar17) {
      if ((8 < iVar17) && (uVar18 = iVar17 - 1U >> 3, 0 < iVar17 + -8)) {
        do {
          iVar11 = iVar10 + iVar13;
          iVar9 = *(int *)&menuPcs->field_0x84c + iVar11 * 0x40 + 8;
          *(undefined4 *)(iVar9 + 0x24) = 9999;
          *(undefined4 *)(iVar9 + 0x2c) = 3;
          iVar9 = *(int *)&menuPcs->field_0x84c + (iVar11 + 1) * 0x40 + 8;
          *(undefined4 *)(iVar9 + 0x24) = 9999;
          *(undefined4 *)(iVar9 + 0x2c) = 3;
          iVar9 = *(int *)&menuPcs->field_0x84c + (iVar11 + 2) * 0x40 + 8;
          *(undefined4 *)(iVar9 + 0x24) = 9999;
          iVar13 = iVar13 + 8;
          *(undefined4 *)(iVar9 + 0x2c) = 3;
          iVar9 = *(int *)&menuPcs->field_0x84c + (iVar11 + 3) * 0x40 + 8;
          *(undefined4 *)(iVar9 + 0x24) = 9999;
          *(undefined4 *)(iVar9 + 0x2c) = 3;
          iVar9 = *(int *)&menuPcs->field_0x84c + (iVar11 + 4) * 0x40 + 8;
          *(undefined4 *)(iVar9 + 0x24) = 9999;
          *(undefined4 *)(iVar9 + 0x2c) = 3;
          iVar9 = *(int *)&menuPcs->field_0x84c + (iVar11 + 5) * 0x40 + 8;
          *(undefined4 *)(iVar9 + 0x24) = 9999;
          *(undefined4 *)(iVar9 + 0x2c) = 3;
          iVar9 = *(int *)&menuPcs->field_0x84c + (iVar11 + 6) * 0x40 + 8;
          *(undefined4 *)(iVar9 + 0x24) = 9999;
          *(undefined4 *)(iVar9 + 0x2c) = 3;
          iVar9 = *(int *)&menuPcs->field_0x84c + (iVar11 + 7) * 0x40 + 8;
          *(undefined4 *)(iVar9 + 0x24) = 9999;
          *(undefined4 *)(iVar9 + 0x2c) = 3;
          uVar18 = uVar18 - 1;
        } while (uVar18 != 0);
      }
      iVar9 = iVar17 - iVar13;
      if (iVar13 < iVar17) {
        do {
          iVar11 = iVar10 + iVar13;
          iVar13 = iVar13 + 1;
          iVar11 = *(int *)&menuPcs->field_0x84c + iVar11 * 0x40 + 8;
          *(undefined4 *)(iVar11 + 0x24) = 9999;
          *(undefined4 *)(iVar11 + 0x2c) = 3;
          iVar9 = iVar9 + -1;
        } while (iVar9 != 0);
      }
    }
    fVar2 = FLOAT_80331ed0;
    dVar1 = DOUBLE_80331e88;
    iVar10 = iVar10 + iVar17;
    iVar13 = 0;
    if (0 < iVar17) {
      if (8 < iVar17) {
        iVar9 = iVar10 - (iVar17 + 1);
        uVar18 = iVar17 - 1U >> 3;
        if (0 < iVar17 + -8) {
          do {
            iVar15 = iVar10 + iVar13;
            psVar12 = (short *)(*(int *)&menuPcs->field_0x84c + iVar15 * 0x40 + 8);
            *(undefined4 *)(psVar12 + 0x12) = *(undefined4 *)(psVar12 + iVar9 * -0x20 + 0x12);
            psVar12[0x16] = 0;
            psVar12[0x17] = 1;
            local_38 = 0x43300000;
            local_30 = (double)(CONCAT44(0x43300000,(int)*psVar12) ^ 0x80000000);
            *(float *)(psVar12 + 0x1c) = (float)(local_30 - dVar1);
            *(float *)(psVar12 + 0x18) = fVar2;
            uStack_34 = (int)*psVar12 ^ 0x80000000;
            iVar11 = (int)((float)((double)CONCAT44(0x43300000,uStack_34) - dVar1) -
                          *(float *)(psVar12 + 0x18));
            local_40 = (double)(longlong)iVar11;
            *psVar12 = (short)iVar11;
            psVar12 = (short *)(*(int *)&menuPcs->field_0x84c + (iVar15 + 1) * 0x40 + 8);
            *(undefined4 *)(psVar12 + 0x12) = *(undefined4 *)(psVar12 + iVar9 * -0x20 + 0x12);
            psVar12[0x16] = 0;
            psVar12[0x17] = 1;
            local_48 = (double)(CONCAT44(0x43300000,(int)*psVar12) ^ 0x80000000);
            *(float *)(psVar12 + 0x1c) = (float)(local_48 - dVar1);
            *(float *)(psVar12 + 0x18) = fVar2;
            local_50 = (double)(CONCAT44(0x43300000,(int)*psVar12) ^ 0x80000000);
            iVar11 = (int)((float)(local_50 - dVar1) - *(float *)(psVar12 + 0x18));
            local_58 = (double)(longlong)iVar11;
            *psVar12 = (short)iVar11;
            psVar12 = (short *)(*(int *)&menuPcs->field_0x84c + (iVar15 + 2) * 0x40 + 8);
            *(undefined4 *)(psVar12 + 0x12) = *(undefined4 *)(psVar12 + iVar9 * -0x20 + 0x12);
            psVar12[0x16] = 0;
            psVar12[0x17] = 1;
            local_60 = (double)(CONCAT44(0x43300000,(int)*psVar12) ^ 0x80000000);
            *(float *)(psVar12 + 0x1c) = (float)(local_60 - dVar1);
            *(float *)(psVar12 + 0x18) = fVar2;
            local_68 = (double)(CONCAT44(0x43300000,(int)*psVar12) ^ 0x80000000);
            iVar11 = (int)((float)(local_68 - dVar1) - *(float *)(psVar12 + 0x18));
            local_70 = (double)(longlong)iVar11;
            *psVar12 = (short)iVar11;
            psVar12 = (short *)(*(int *)&menuPcs->field_0x84c + (iVar15 + 3) * 0x40 + 8);
            local_80 = 0x43300000;
            *(undefined4 *)(psVar12 + 0x12) = *(undefined4 *)(psVar12 + iVar9 * -0x20 + 0x12);
            psVar12[0x16] = 0;
            psVar12[0x17] = 1;
            local_78 = (double)(CONCAT44(0x43300000,(int)*psVar12) ^ 0x80000000);
            local_98 = 0x43300000;
            *(float *)(psVar12 + 0x1c) = (float)(local_78 - dVar1);
            *(float *)(psVar12 + 0x18) = fVar2;
            uStack_7c = (int)*psVar12 ^ 0x80000000;
            local_b0 = 0x43300000;
            iVar11 = (int)((float)((double)CONCAT44(0x43300000,uStack_7c) - dVar1) -
                          *(float *)(psVar12 + 0x18));
            local_88 = (double)(longlong)iVar11;
            *psVar12 = (short)iVar11;
            psVar12 = (short *)(*(int *)&menuPcs->field_0x84c + (iVar15 + 4) * 0x40 + 8);
            *(undefined4 *)(psVar12 + 0x12) = *(undefined4 *)(psVar12 + iVar9 * -0x20 + 0x12);
            psVar12[0x16] = 0;
            psVar12[0x17] = 1;
            local_90 = (double)(CONCAT44(0x43300000,(int)*psVar12) ^ 0x80000000);
            *(float *)(psVar12 + 0x1c) = (float)(local_90 - dVar1);
            *(float *)(psVar12 + 0x18) = fVar2;
            uStack_94 = (int)*psVar12 ^ 0x80000000;
            iVar11 = (int)((float)((double)CONCAT44(0x43300000,uStack_94) - dVar1) -
                          *(float *)(psVar12 + 0x18));
            local_a0 = (double)(longlong)iVar11;
            *psVar12 = (short)iVar11;
            psVar12 = (short *)(*(int *)&menuPcs->field_0x84c + (iVar15 + 5) * 0x40 + 8);
            *(undefined4 *)(psVar12 + 0x12) = *(undefined4 *)(psVar12 + iVar9 * -0x20 + 0x12);
            psVar12[0x16] = 0;
            psVar12[0x17] = 1;
            local_a8 = (double)(CONCAT44(0x43300000,(int)*psVar12) ^ 0x80000000);
            *(float *)(psVar12 + 0x1c) = (float)(local_a8 - dVar1);
            *(float *)(psVar12 + 0x18) = fVar2;
            uStack_ac = (int)*psVar12 ^ 0x80000000;
            iVar11 = (int)((float)((double)CONCAT44(0x43300000,uStack_ac) - dVar1) -
                          *(float *)(psVar12 + 0x18));
            local_b8 = (double)(longlong)iVar11;
            *psVar12 = (short)iVar11;
            psVar12 = (short *)(*(int *)&menuPcs->field_0x84c + (iVar15 + 6) * 0x40 + 8);
            iVar13 = iVar13 + 8;
            local_c8 = 0x43300000;
            *(undefined4 *)(psVar12 + 0x12) = *(undefined4 *)(psVar12 + iVar9 * -0x20 + 0x12);
            psVar12[0x16] = 0;
            psVar12[0x17] = 1;
            local_c0 = (double)(CONCAT44(0x43300000,(int)*psVar12) ^ 0x80000000);
            local_e0 = 0x43300000;
            *(float *)(psVar12 + 0x1c) = (float)(local_c0 - dVar1);
            *(float *)(psVar12 + 0x18) = fVar2;
            uStack_c4 = (int)*psVar12 ^ 0x80000000;
            iVar11 = (int)((float)((double)CONCAT44(0x43300000,uStack_c4) - dVar1) -
                          *(float *)(psVar12 + 0x18));
            local_d0 = (double)(longlong)iVar11;
            *psVar12 = (short)iVar11;
            psVar12 = (short *)(*(int *)&menuPcs->field_0x84c + (iVar15 + 7) * 0x40 + 8);
            *(undefined4 *)(psVar12 + 0x12) = *(undefined4 *)(psVar12 + iVar9 * -0x20 + 0x12);
            psVar12[0x16] = 0;
            psVar12[0x17] = 1;
            local_d8 = (double)(CONCAT44(0x43300000,(int)*psVar12) ^ 0x80000000);
            *(float *)(psVar12 + 0x1c) = (float)(local_d8 - dVar1);
            *(float *)(psVar12 + 0x18) = fVar2;
            uStack_dc = (int)*psVar12 ^ 0x80000000;
            iVar11 = (int)((float)((double)CONCAT44(0x43300000,uStack_dc) - dVar1) -
                          *(float *)(psVar12 + 0x18));
            local_e8 = (double)(longlong)iVar11;
            *psVar12 = (short)iVar11;
            uVar18 = uVar18 - 1;
            unaff_r31 = iVar9;
          } while (uVar18 != 0);
        }
      }
      fVar2 = FLOAT_80331ed0;
      dVar1 = DOUBLE_80331e88;
      iVar9 = iVar17 - iVar13;
      iVar11 = iVar10 - (iVar17 + 1);
      if (iVar13 < iVar17) {
        do {
          psVar12 = (short *)(*(int *)&menuPcs->field_0x84c + (iVar10 + iVar13) * 0x40 + 8);
          local_38 = 0x43300000;
          iVar13 = iVar13 + 1;
          *(undefined4 *)(psVar12 + 0x12) = *(undefined4 *)(psVar12 + iVar11 * -0x20 + 0x12);
          psVar12[0x16] = 0;
          psVar12[0x17] = 1;
          local_30 = (double)(CONCAT44(0x43300000,(int)*psVar12) ^ 0x80000000);
          *(float *)(psVar12 + 0x1c) = (float)(local_30 - dVar1);
          *(float *)(psVar12 + 0x18) = fVar2;
          uStack_34 = (int)*psVar12 ^ 0x80000000;
          iVar15 = (int)((float)((double)CONCAT44(0x43300000,uStack_34) - dVar1) -
                        *(float *)(psVar12 + 0x18));
          local_40 = (double)(longlong)iVar15;
          *psVar12 = (short)iVar15;
          iVar9 = iVar9 + -1;
          unaff_r31 = iVar11;
        } while (iVar9 != 0);
      }
    }
    iVar13 = iVar10 + iVar17 + 1;
    *(undefined4 *)(*(int *)&menuPcs->field_0x84c + (iVar10 + iVar17) * 0x40 + 0x2c) =
         *(undefined4 *)(*(int *)&menuPcs->field_0x84c + 0x6c);
    iVar10 = 0;
    DAT_8032eeac = (undefined)iVar13;
    if (0 < iVar17) {
      if ((8 < iVar17) && (uVar18 = iVar17 - 1U >> 3, 0 < iVar17 + -8)) {
        do {
          iVar11 = iVar13 + iVar10;
          iVar10 = iVar10 + 8;
          iVar9 = *(int *)&menuPcs->field_0x84c + iVar11 * 0x40 + 8;
          *(undefined4 *)(iVar9 + 0x24) = 8;
          *(undefined4 *)(iVar9 + 0x28) = 8;
          iVar9 = *(int *)&menuPcs->field_0x84c + (iVar11 + 1) * 0x40 + 8;
          *(undefined4 *)(iVar9 + 0x24) = 8;
          *(undefined4 *)(iVar9 + 0x28) = 8;
          iVar9 = *(int *)&menuPcs->field_0x84c + (iVar11 + 2) * 0x40 + 8;
          *(undefined4 *)(iVar9 + 0x24) = 8;
          *(undefined4 *)(iVar9 + 0x28) = 8;
          iVar9 = *(int *)&menuPcs->field_0x84c + (iVar11 + 3) * 0x40 + 8;
          *(undefined4 *)(iVar9 + 0x24) = 8;
          *(undefined4 *)(iVar9 + 0x28) = 8;
          iVar9 = *(int *)&menuPcs->field_0x84c + (iVar11 + 4) * 0x40 + 8;
          *(undefined4 *)(iVar9 + 0x24) = 8;
          *(undefined4 *)(iVar9 + 0x28) = 8;
          iVar9 = *(int *)&menuPcs->field_0x84c + (iVar11 + 5) * 0x40 + 8;
          *(undefined4 *)(iVar9 + 0x24) = 8;
          *(undefined4 *)(iVar9 + 0x28) = 8;
          iVar9 = *(int *)&menuPcs->field_0x84c + (iVar11 + 6) * 0x40 + 8;
          *(undefined4 *)(iVar9 + 0x24) = 8;
          *(undefined4 *)(iVar9 + 0x28) = 8;
          iVar9 = *(int *)&menuPcs->field_0x84c + (iVar11 + 7) * 0x40 + 8;
          *(undefined4 *)(iVar9 + 0x24) = 8;
          *(undefined4 *)(iVar9 + 0x28) = 8;
          uVar18 = uVar18 - 1;
        } while (uVar18 != 0);
      }
      iVar9 = iVar17 - iVar10;
      if (iVar10 < iVar17) {
        do {
          iVar11 = iVar13 + iVar10;
          iVar10 = iVar10 + 1;
          iVar11 = *(int *)&menuPcs->field_0x84c + iVar11 * 0x40 + 8;
          *(undefined4 *)(iVar11 + 0x24) = 8;
          *(undefined4 *)(iVar11 + 0x28) = 8;
          iVar9 = iVar9 + -1;
        } while (iVar9 != 0);
      }
    }
    fVar2 = FLOAT_80331ed0;
    dVar1 = DOUBLE_80331e88;
    iVar13 = iVar13 + iVar17;
    iVar10 = 0;
    if (0 < iVar17) {
      if (8 < iVar17) {
        iVar9 = iVar13 - (iVar17 + 1);
        uVar18 = iVar17 - 1U >> 3;
        if (0 < iVar17 + -8) {
          do {
            iVar15 = iVar13 + iVar10;
            psVar12 = (short *)(*(int *)&menuPcs->field_0x84c + iVar15 * 0x40 + 8);
            *(undefined4 *)(psVar12 + 0x12) = *(undefined4 *)(psVar12 + iVar9 * -0x20 + 0x12);
            psVar12[0x16] = 0;
            psVar12[0x17] = 1;
            local_38 = 0x43300000;
            local_30 = (double)(CONCAT44(0x43300000,(int)*psVar12) ^ 0x80000000);
            *(float *)(psVar12 + 0x1c) = (float)(local_30 - dVar1);
            *(float *)(psVar12 + 0x18) = fVar2;
            uStack_34 = (int)*psVar12 ^ 0x80000000;
            iVar11 = (int)((float)((double)CONCAT44(0x43300000,uStack_34) - dVar1) -
                          *(float *)(psVar12 + 0x18));
            local_40 = (double)(longlong)iVar11;
            *psVar12 = (short)iVar11;
            psVar12 = (short *)(*(int *)&menuPcs->field_0x84c + (iVar15 + 1) * 0x40 + 8);
            *(undefined4 *)(psVar12 + 0x12) = *(undefined4 *)(psVar12 + iVar9 * -0x20 + 0x12);
            psVar12[0x16] = 0;
            psVar12[0x17] = 1;
            local_48 = (double)(CONCAT44(0x43300000,(int)*psVar12) ^ 0x80000000);
            *(float *)(psVar12 + 0x1c) = (float)(local_48 - dVar1);
            *(float *)(psVar12 + 0x18) = fVar2;
            local_50 = (double)(CONCAT44(0x43300000,(int)*psVar12) ^ 0x80000000);
            iVar11 = (int)((float)(local_50 - dVar1) - *(float *)(psVar12 + 0x18));
            local_58 = (double)(longlong)iVar11;
            *psVar12 = (short)iVar11;
            psVar12 = (short *)(*(int *)&menuPcs->field_0x84c + (iVar15 + 2) * 0x40 + 8);
            *(undefined4 *)(psVar12 + 0x12) = *(undefined4 *)(psVar12 + iVar9 * -0x20 + 0x12);
            psVar12[0x16] = 0;
            psVar12[0x17] = 1;
            local_60 = (double)(CONCAT44(0x43300000,(int)*psVar12) ^ 0x80000000);
            *(float *)(psVar12 + 0x1c) = (float)(local_60 - dVar1);
            *(float *)(psVar12 + 0x18) = fVar2;
            local_68 = (double)(CONCAT44(0x43300000,(int)*psVar12) ^ 0x80000000);
            iVar11 = (int)((float)(local_68 - dVar1) - *(float *)(psVar12 + 0x18));
            local_70 = (double)(longlong)iVar11;
            *psVar12 = (short)iVar11;
            psVar12 = (short *)(*(int *)&menuPcs->field_0x84c + (iVar15 + 3) * 0x40 + 8);
            local_80 = 0x43300000;
            *(undefined4 *)(psVar12 + 0x12) = *(undefined4 *)(psVar12 + iVar9 * -0x20 + 0x12);
            psVar12[0x16] = 0;
            psVar12[0x17] = 1;
            local_78 = (double)(CONCAT44(0x43300000,(int)*psVar12) ^ 0x80000000);
            local_98 = 0x43300000;
            *(float *)(psVar12 + 0x1c) = (float)(local_78 - dVar1);
            *(float *)(psVar12 + 0x18) = fVar2;
            uStack_7c = (int)*psVar12 ^ 0x80000000;
            local_b0 = 0x43300000;
            iVar11 = (int)((float)((double)CONCAT44(0x43300000,uStack_7c) - dVar1) -
                          *(float *)(psVar12 + 0x18));
            local_88 = (double)(longlong)iVar11;
            *psVar12 = (short)iVar11;
            psVar12 = (short *)(*(int *)&menuPcs->field_0x84c + (iVar15 + 4) * 0x40 + 8);
            *(undefined4 *)(psVar12 + 0x12) = *(undefined4 *)(psVar12 + iVar9 * -0x20 + 0x12);
            psVar12[0x16] = 0;
            psVar12[0x17] = 1;
            local_90 = (double)(CONCAT44(0x43300000,(int)*psVar12) ^ 0x80000000);
            *(float *)(psVar12 + 0x1c) = (float)(local_90 - dVar1);
            *(float *)(psVar12 + 0x18) = fVar2;
            uStack_94 = (int)*psVar12 ^ 0x80000000;
            iVar11 = (int)((float)((double)CONCAT44(0x43300000,uStack_94) - dVar1) -
                          *(float *)(psVar12 + 0x18));
            local_a0 = (double)(longlong)iVar11;
            *psVar12 = (short)iVar11;
            psVar12 = (short *)(*(int *)&menuPcs->field_0x84c + (iVar15 + 5) * 0x40 + 8);
            *(undefined4 *)(psVar12 + 0x12) = *(undefined4 *)(psVar12 + iVar9 * -0x20 + 0x12);
            psVar12[0x16] = 0;
            psVar12[0x17] = 1;
            local_a8 = (double)(CONCAT44(0x43300000,(int)*psVar12) ^ 0x80000000);
            *(float *)(psVar12 + 0x1c) = (float)(local_a8 - dVar1);
            *(float *)(psVar12 + 0x18) = fVar2;
            uStack_ac = (int)*psVar12 ^ 0x80000000;
            iVar11 = (int)((float)((double)CONCAT44(0x43300000,uStack_ac) - dVar1) -
                          *(float *)(psVar12 + 0x18));
            local_b8 = (double)(longlong)iVar11;
            *psVar12 = (short)iVar11;
            psVar12 = (short *)(*(int *)&menuPcs->field_0x84c + (iVar15 + 6) * 0x40 + 8);
            iVar10 = iVar10 + 8;
            local_c8 = 0x43300000;
            *(undefined4 *)(psVar12 + 0x12) = *(undefined4 *)(psVar12 + iVar9 * -0x20 + 0x12);
            psVar12[0x16] = 0;
            psVar12[0x17] = 1;
            local_c0 = (double)(CONCAT44(0x43300000,(int)*psVar12) ^ 0x80000000);
            local_e0 = 0x43300000;
            *(float *)(psVar12 + 0x1c) = (float)(local_c0 - dVar1);
            *(float *)(psVar12 + 0x18) = fVar2;
            uStack_c4 = (int)*psVar12 ^ 0x80000000;
            iVar11 = (int)((float)((double)CONCAT44(0x43300000,uStack_c4) - dVar1) -
                          *(float *)(psVar12 + 0x18));
            local_d0 = (double)(longlong)iVar11;
            *psVar12 = (short)iVar11;
            psVar12 = (short *)(*(int *)&menuPcs->field_0x84c + (iVar15 + 7) * 0x40 + 8);
            *(undefined4 *)(psVar12 + 0x12) = *(undefined4 *)(psVar12 + iVar9 * -0x20 + 0x12);
            psVar12[0x16] = 0;
            psVar12[0x17] = 1;
            local_d8 = (double)(CONCAT44(0x43300000,(int)*psVar12) ^ 0x80000000);
            *(float *)(psVar12 + 0x1c) = (float)(local_d8 - dVar1);
            *(float *)(psVar12 + 0x18) = fVar2;
            uStack_dc = (int)*psVar12 ^ 0x80000000;
            iVar11 = (int)((float)((double)CONCAT44(0x43300000,uStack_dc) - dVar1) -
                          *(float *)(psVar12 + 0x18));
            local_e8 = (double)(longlong)iVar11;
            *psVar12 = (short)iVar11;
            uVar18 = uVar18 - 1;
            unaff_r31 = iVar9;
          } while (uVar18 != 0);
        }
      }
      fVar2 = FLOAT_80331ed0;
      dVar1 = DOUBLE_80331e88;
      iVar9 = iVar17 - iVar10;
      iVar11 = iVar13 - (iVar17 + 1);
      if (iVar10 < iVar17) {
        do {
          psVar12 = (short *)(*(int *)&menuPcs->field_0x84c + (iVar13 + iVar10) * 0x40 + 8);
          local_38 = 0x43300000;
          iVar10 = iVar10 + 1;
          *(undefined4 *)(psVar12 + 0x12) = *(undefined4 *)(psVar12 + iVar11 * -0x20 + 0x12);
          psVar12[0x16] = 0;
          psVar12[0x17] = 1;
          local_30 = (double)(CONCAT44(0x43300000,(int)*psVar12) ^ 0x80000000);
          *(float *)(psVar12 + 0x1c) = (float)(local_30 - dVar1);
          *(float *)(psVar12 + 0x18) = fVar2;
          uStack_34 = (int)*psVar12 ^ 0x80000000;
          iVar15 = (int)((float)((double)CONCAT44(0x43300000,uStack_34) - dVar1) -
                        *(float *)(psVar12 + 0x18));
          local_40 = (double)(longlong)iVar15;
          *psVar12 = (short)iVar15;
          iVar9 = iVar9 + -1;
          unaff_r31 = iVar11;
        } while (iVar9 != 0);
      }
    }
    iVar13 = iVar13 + iVar17;
    iVar10 = 0;
    if (0 < iVar17) {
      if ((8 < iVar17) && (uVar18 = iVar17 - 1U >> 3, 0 < iVar17 + -8)) {
        do {
          iVar9 = iVar13 + iVar10;
          iVar10 = iVar10 + 8;
          *(undefined4 *)(*(int *)&menuPcs->field_0x84c + iVar9 * 0x40 + 0x2c) = 0;
          *(undefined4 *)(*(int *)&menuPcs->field_0x84c + (iVar9 + 1) * 0x40 + 0x2c) = 0;
          *(undefined4 *)(*(int *)&menuPcs->field_0x84c + (iVar9 + 2) * 0x40 + 0x2c) = 0;
          *(undefined4 *)(*(int *)&menuPcs->field_0x84c + (iVar9 + 3) * 0x40 + 0x2c) = 0;
          *(undefined4 *)(*(int *)&menuPcs->field_0x84c + (iVar9 + 4) * 0x40 + 0x2c) = 0;
          *(undefined4 *)(*(int *)&menuPcs->field_0x84c + (iVar9 + 5) * 0x40 + 0x2c) = 0;
          *(undefined4 *)(*(int *)&menuPcs->field_0x84c + (iVar9 + 6) * 0x40 + 0x2c) = 0;
          *(undefined4 *)(*(int *)&menuPcs->field_0x84c + (iVar9 + 7) * 0x40 + 0x2c) = 0;
          uVar18 = uVar18 - 1;
        } while (uVar18 != 0);
      }
      iVar9 = iVar17 - iVar10;
      if (iVar10 < iVar17) {
        do {
          iVar11 = iVar13 + iVar10;
          iVar10 = iVar10 + 1;
          *(undefined4 *)(*(int *)&menuPcs->field_0x84c + iVar11 * 0x40 + 0x2c) = 0;
          iVar9 = iVar9 + -1;
        } while (iVar9 != 0);
      }
    }
    fVar2 = FLOAT_80331ed0;
    dVar1 = DOUBLE_80331e88;
    iVar13 = iVar13 + iVar17;
    iVar10 = 0;
    if (0 < iVar17) {
      if (8 < iVar17) {
        iVar9 = iVar13 - (iVar17 + 1);
        uVar18 = iVar17 - 1U >> 3;
        if (0 < iVar17 + -8) {
          do {
            iVar15 = iVar13 + iVar10;
            psVar12 = (short *)(*(int *)&menuPcs->field_0x84c + iVar15 * 0x40 + 8);
            *(undefined4 *)(psVar12 + 0x12) = *(undefined4 *)(psVar12 + iVar9 * -0x20 + 0x12);
            psVar12[0x16] = 0;
            psVar12[0x17] = 1;
            local_38 = 0x43300000;
            local_30 = (double)(CONCAT44(0x43300000,(int)*psVar12) ^ 0x80000000);
            *(float *)(psVar12 + 0x1c) = (float)(local_30 - dVar1);
            *(float *)(psVar12 + 0x18) = fVar2;
            uStack_34 = (int)*psVar12 ^ 0x80000000;
            iVar11 = (int)((float)((double)CONCAT44(0x43300000,uStack_34) - dVar1) -
                          *(float *)(psVar12 + 0x18));
            local_40 = (double)(longlong)iVar11;
            *psVar12 = (short)iVar11;
            psVar12 = (short *)(*(int *)&menuPcs->field_0x84c + (iVar15 + 1) * 0x40 + 8);
            *(undefined4 *)(psVar12 + 0x12) = *(undefined4 *)(psVar12 + iVar9 * -0x20 + 0x12);
            psVar12[0x16] = 0;
            psVar12[0x17] = 1;
            local_48 = (double)(CONCAT44(0x43300000,(int)*psVar12) ^ 0x80000000);
            *(float *)(psVar12 + 0x1c) = (float)(local_48 - dVar1);
            *(float *)(psVar12 + 0x18) = fVar2;
            local_50 = (double)(CONCAT44(0x43300000,(int)*psVar12) ^ 0x80000000);
            iVar11 = (int)((float)(local_50 - dVar1) - *(float *)(psVar12 + 0x18));
            local_58 = (double)(longlong)iVar11;
            *psVar12 = (short)iVar11;
            psVar12 = (short *)(*(int *)&menuPcs->field_0x84c + (iVar15 + 2) * 0x40 + 8);
            *(undefined4 *)(psVar12 + 0x12) = *(undefined4 *)(psVar12 + iVar9 * -0x20 + 0x12);
            psVar12[0x16] = 0;
            psVar12[0x17] = 1;
            local_60 = (double)(CONCAT44(0x43300000,(int)*psVar12) ^ 0x80000000);
            *(float *)(psVar12 + 0x1c) = (float)(local_60 - dVar1);
            *(float *)(psVar12 + 0x18) = fVar2;
            local_68 = (double)(CONCAT44(0x43300000,(int)*psVar12) ^ 0x80000000);
            iVar11 = (int)((float)(local_68 - dVar1) - *(float *)(psVar12 + 0x18));
            local_70 = (double)(longlong)iVar11;
            *psVar12 = (short)iVar11;
            psVar12 = (short *)(*(int *)&menuPcs->field_0x84c + (iVar15 + 3) * 0x40 + 8);
            local_80 = 0x43300000;
            *(undefined4 *)(psVar12 + 0x12) = *(undefined4 *)(psVar12 + iVar9 * -0x20 + 0x12);
            psVar12[0x16] = 0;
            psVar12[0x17] = 1;
            local_78 = (double)(CONCAT44(0x43300000,(int)*psVar12) ^ 0x80000000);
            local_98 = 0x43300000;
            *(float *)(psVar12 + 0x1c) = (float)(local_78 - dVar1);
            *(float *)(psVar12 + 0x18) = fVar2;
            uStack_7c = (int)*psVar12 ^ 0x80000000;
            local_b0 = 0x43300000;
            iVar11 = (int)((float)((double)CONCAT44(0x43300000,uStack_7c) - dVar1) -
                          *(float *)(psVar12 + 0x18));
            local_88 = (double)(longlong)iVar11;
            *psVar12 = (short)iVar11;
            psVar12 = (short *)(*(int *)&menuPcs->field_0x84c + (iVar15 + 4) * 0x40 + 8);
            *(undefined4 *)(psVar12 + 0x12) = *(undefined4 *)(psVar12 + iVar9 * -0x20 + 0x12);
            psVar12[0x16] = 0;
            psVar12[0x17] = 1;
            local_90 = (double)(CONCAT44(0x43300000,(int)*psVar12) ^ 0x80000000);
            *(float *)(psVar12 + 0x1c) = (float)(local_90 - dVar1);
            *(float *)(psVar12 + 0x18) = fVar2;
            uStack_94 = (int)*psVar12 ^ 0x80000000;
            iVar11 = (int)((float)((double)CONCAT44(0x43300000,uStack_94) - dVar1) -
                          *(float *)(psVar12 + 0x18));
            local_a0 = (double)(longlong)iVar11;
            *psVar12 = (short)iVar11;
            psVar12 = (short *)(*(int *)&menuPcs->field_0x84c + (iVar15 + 5) * 0x40 + 8);
            *(undefined4 *)(psVar12 + 0x12) = *(undefined4 *)(psVar12 + iVar9 * -0x20 + 0x12);
            psVar12[0x16] = 0;
            psVar12[0x17] = 1;
            local_a8 = (double)(CONCAT44(0x43300000,(int)*psVar12) ^ 0x80000000);
            *(float *)(psVar12 + 0x1c) = (float)(local_a8 - dVar1);
            *(float *)(psVar12 + 0x18) = fVar2;
            uStack_ac = (int)*psVar12 ^ 0x80000000;
            iVar11 = (int)((float)((double)CONCAT44(0x43300000,uStack_ac) - dVar1) -
                          *(float *)(psVar12 + 0x18));
            local_b8 = (double)(longlong)iVar11;
            *psVar12 = (short)iVar11;
            psVar12 = (short *)(*(int *)&menuPcs->field_0x84c + (iVar15 + 6) * 0x40 + 8);
            iVar10 = iVar10 + 8;
            local_c8 = 0x43300000;
            *(undefined4 *)(psVar12 + 0x12) = *(undefined4 *)(psVar12 + iVar9 * -0x20 + 0x12);
            psVar12[0x16] = 0;
            psVar12[0x17] = 1;
            local_c0 = (double)(CONCAT44(0x43300000,(int)*psVar12) ^ 0x80000000);
            local_e0 = 0x43300000;
            *(float *)(psVar12 + 0x1c) = (float)(local_c0 - dVar1);
            *(float *)(psVar12 + 0x18) = fVar2;
            uStack_c4 = (int)*psVar12 ^ 0x80000000;
            iVar11 = (int)((float)((double)CONCAT44(0x43300000,uStack_c4) - dVar1) -
                          *(float *)(psVar12 + 0x18));
            local_d0 = (double)(longlong)iVar11;
            *psVar12 = (short)iVar11;
            psVar12 = (short *)(*(int *)&menuPcs->field_0x84c + (iVar15 + 7) * 0x40 + 8);
            *(undefined4 *)(psVar12 + 0x12) = *(undefined4 *)(psVar12 + iVar9 * -0x20 + 0x12);
            psVar12[0x16] = 0;
            psVar12[0x17] = 1;
            local_d8 = (double)(CONCAT44(0x43300000,(int)*psVar12) ^ 0x80000000);
            *(float *)(psVar12 + 0x1c) = (float)(local_d8 - dVar1);
            *(float *)(psVar12 + 0x18) = fVar2;
            uStack_dc = (int)*psVar12 ^ 0x80000000;
            iVar11 = (int)((float)((double)CONCAT44(0x43300000,uStack_dc) - dVar1) -
                          *(float *)(psVar12 + 0x18));
            local_e8 = (double)(longlong)iVar11;
            *psVar12 = (short)iVar11;
            uVar18 = uVar18 - 1;
            unaff_r31 = iVar9;
          } while (uVar18 != 0);
        }
      }
      fVar2 = FLOAT_80331ed0;
      dVar1 = DOUBLE_80331e88;
      iVar9 = iVar17 - iVar10;
      iVar11 = iVar13 - (iVar17 + 1);
      if (iVar10 < iVar17) {
        do {
          psVar12 = (short *)(*(int *)&menuPcs->field_0x84c + (iVar13 + iVar10) * 0x40 + 8);
          local_38 = 0x43300000;
          iVar10 = iVar10 + 1;
          *(undefined4 *)(psVar12 + 0x12) = *(undefined4 *)(psVar12 + iVar11 * -0x20 + 0x12);
          psVar12[0x16] = 0;
          psVar12[0x17] = 1;
          local_30 = (double)(CONCAT44(0x43300000,(int)*psVar12) ^ 0x80000000);
          *(float *)(psVar12 + 0x1c) = (float)(local_30 - dVar1);
          *(float *)(psVar12 + 0x18) = fVar2;
          uStack_34 = (int)*psVar12 ^ 0x80000000;
          iVar15 = (int)((float)((double)CONCAT44(0x43300000,uStack_34) - dVar1) -
                        *(float *)(psVar12 + 0x18));
          local_40 = (double)(longlong)iVar15;
          *psVar12 = (short)iVar15;
          iVar9 = iVar9 + -1;
          unaff_r31 = iVar11;
        } while (iVar9 != 0);
      }
    }
    fVar2 = FLOAT_80331eac;
    iVar10 = 0;
    for (iVar13 = 0; psVar12 = *(short **)&menuPcs->field_0x84c, iVar13 < *psVar12;
        iVar13 = iVar13 + 1) {
      if (fVar2 == *(float *)((int)psVar12 + iVar10 + 0x38)) {
        local_30 = (double)(CONCAT44(0x43300000,(int)*(short *)((int)psVar12 + iVar10 + 8)) ^
                           0x80000000);
        *(float *)((int)psVar12 + iVar10 + 0x40) = (float)(local_30 - DOUBLE_80331e88);
      }
      iVar9 = *(int *)&menuPcs->field_0x84c + iVar10;
      if (fVar2 == *(float *)(iVar9 + 0x3c)) {
        local_30 = (double)(CONCAT44(0x43300000,(int)*(short *)(iVar9 + 10)) ^ 0x80000000);
        *(float *)(iVar9 + 0x44) = (float)(local_30 - DOUBLE_80331e88);
      }
      iVar10 = iVar10 + 0x40;
    }
    psVar12[3] = 0;
    *(undefined *)(*(int *)&menuPcs->field_0x82c + 0xb) = 1;
  }
  iVar13 = 0;
  iVar11 = 0;
  *(short *)(*(int *)&menuPcs->field_0x82c + 0x22) =
       *(short *)(*(int *)&menuPcs->field_0x82c + 0x22) + 1;
  iVar10 = (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x22);
  for (iVar9 = 0; fVar8 = FLOAT_80331efc, fVar2 = FLOAT_80331ef8, dVar7 = DOUBLE_80331ef0,
      dVar6 = DOUBLE_80331ee8, dVar5 = DOUBLE_80331ee0, dVar4 = DOUBLE_80331e90,
      dVar3 = DOUBLE_80331e88, dVar1 = DOUBLE_80331e78, iVar9 < **(short **)&menuPcs->field_0x84c;
      iVar9 = iVar9 + 1) {
    psVar12 = (short *)((int)*(short **)&menuPcs->field_0x84c + iVar13 + 8);
    if ((*(uint *)(psVar12 + 0x16) & 1) == 0) {
      if (iVar10 < *(int *)(psVar12 + 0x12)) {
        *(float *)(psVar12 + 8) = FLOAT_80331eb0;
      }
      if (iVar10 < (int)(*(int *)(psVar12 + 0x12) + *(uint *)(psVar12 + 0x14))) {
        local_30 = (double)CONCAT44(0x43300000,*(uint *)(psVar12 + 0x14) ^ 0x80000000);
        uStack_34 = *(uint *)(psVar12 + 0x10) ^ 0x80000000;
        local_38 = 0x43300000;
        *(float *)(psVar12 + 8) =
             (float)-((DOUBLE_80331ed8 / (local_30 - DOUBLE_80331e88)) *
                      ((double)CONCAT44(0x43300000,uStack_34) - DOUBLE_80331e88) - DOUBLE_80331ed8);
      }
      else {
        *(float *)(psVar12 + 8) = FLOAT_80331eac;
      }
    }
    else {
      *(float *)(psVar12 + 8) = FLOAT_80331eb0;
    }
    if (((int)(*(int *)(psVar12 + 0x12) + *(uint *)(psVar12 + 0x14)) <= iVar10) ||
       (0x270e < *(int *)(psVar12 + 0x12))) {
      iVar11 = iVar11 + 1;
    }
    if (((*(uint *)(psVar12 + 0x16) & 2) == 0) &&
       ((*(float *)(psVar12 + 0x18) != FLOAT_80331eac ||
        (*(float *)(psVar12 + 0x1a) != FLOAT_80331eac)))) {
      local_30 = (double)CONCAT44(0x43300000,*(uint *)(psVar12 + 0x14) ^ 0x80000000);
      uStack_34 = *(uint *)(psVar12 + 0x10) ^ 0x80000000;
      local_38 = 0x43300000;
      local_48 = (double)CONCAT44(0x43300000,(int)*psVar12 ^ 0x80000000);
      local_40 = (double)CONCAT44(0x43300000,(int)psVar12[1] ^ 0x80000000);
      fVar2 = (float)-((DOUBLE_80331ed8 / (local_30 - DOUBLE_80331e88)) *
                       ((double)CONCAT44(0x43300000,uStack_34) - DOUBLE_80331e88) - DOUBLE_80331ed8)
      ;
      dVar1 = local_40 - DOUBLE_80331e88;
      *(float *)(psVar12 + 0x18) =
           (*(float *)(psVar12 + 0x1c) - (float)(local_48 - DOUBLE_80331e88)) * fVar2;
      *(float *)(psVar12 + 0x1a) = (*(float *)(psVar12 + 0x1e) - (float)dVar1) * fVar2;
    }
    if ((*(int *)(psVar12 + 0x12) < iVar10) &&
       (iVar10 <= *(int *)(psVar12 + 0x12) + *(int *)(psVar12 + 0x14))) {
      *(int *)(psVar12 + 0x10) = *(int *)(psVar12 + 0x10) + 1;
    }
    iVar13 = iVar13 + 0x40;
  }
  iVar13 = 0;
  iVar10 = 0;
  if (0 < iVar17) {
    unaff_r31 = iVar17 + 1;
    iVar9 = iVar17;
    do {
      local_38 = 0x43300000;
      psVar12 = (short *)(*(int *)&menuPcs->field_0x84c + (unaff_r31 + iVar13) * 0x40 + 8);
      uStack_34 = (int)*psVar12 ^ 0x80000000;
      iVar14 = iVar10 + 0x40;
      local_30 = (double)(CONCAT44(0x43300000,(int)psVar12[2]) ^ 0x80000000);
      local_48 = (double)CONCAT44(0x43300000,(int)psVar12[1] ^ 0x80000000);
      local_40 = (double)CONCAT44(0x43300000,(int)psVar12[3] ^ 0x80000000);
      local_80 = 0x43300000;
      iVar15 = (int)((double)(float)(dVar5 + (local_30 - dVar3) * dVar1 +
                                             (double)((float)((double)CONCAT44(0x43300000,uStack_34)
                                                             - dVar3) + *(float *)(psVar12 + 0x18)))
                    - dVar6);
      local_50 = (double)(longlong)iVar15;
      iVar16 = (int)((double)(float)((local_40 - dVar3) * dVar1 +
                                    (double)((float)(local_48 - dVar3) + *(float *)(psVar12 + 0x1a))
                                    ) - dVar7);
      local_58 = (double)(longlong)iVar16;
      *(short *)(*(int *)&menuPcs->field_0x814 + iVar10 + 8) = (short)iVar15;
      *(short *)(*(int *)&menuPcs->field_0x814 + iVar10 + 10) = (short)iVar16;
      local_60 = (double)(CONCAT44(0x43300000,(int)*psVar12) ^ 0x80000000);
      iVar15 = (int)(fVar2 + (float)(local_60 - dVar3) + *(float *)(psVar12 + 0x18));
      local_68 = (double)(longlong)iVar15;
      *(int *)(*(int *)&menuPcs->field_0x814 + iVar14) = iVar15;
      local_70 = (double)(CONCAT44(0x43300000,(int)psVar12[1]) ^ 0x80000000);
      iVar15 = (int)(((float)(local_70 - dVar3) + *(float *)(psVar12 + 0x1a)) - fVar8);
      local_78 = (double)(longlong)iVar15;
      *(int *)(*(int *)&menuPcs->field_0x814 + iVar10 + 0x44) = iVar15;
      uStack_7c = *(uint *)(*(int *)&menuPcs->field_0x814 + iVar14) ^ 0x80000000;
      if ((double)CONCAT44(0x43300000,uStack_7c) - dVar3 < dVar4) {
        *(undefined4 *)(*(int *)&menuPcs->field_0x814 + iVar14) = 0;
      }
      local_30 = (double)(CONCAT44(0x43300000,
                                   *(undefined4 *)(*(int *)&menuPcs->field_0x814 + iVar10 + 0x44)) ^
                         0x80000000);
      if (local_30 - dVar3 < dVar4) {
        *(undefined4 *)(*(int *)&menuPcs->field_0x814 + iVar10 + 0x44) = 0;
      }
      iVar15 = iVar10 + 0x4c;
      *(undefined4 *)(*(int *)&menuPcs->field_0x814 + iVar10 + 0x48) = 0x48;
      iVar10 = iVar10 + 0x50;
      iVar13 = iVar13 + 1;
      *(undefined4 *)(*(int *)&menuPcs->field_0x814 + iVar15) = 0x58;
      iVar9 = iVar9 + -1;
    } while (iVar9 != 0);
  }
  iVar9 = 0;
  iVar10 = (iVar17 * 2 + 1) * 0x40;
  for (iVar13 = 0; iVar13 < iVar17 * 2; iVar13 = iVar13 + 1) {
    iVar15 = *(int *)&menuPcs->field_0x84c;
    if (iVar13 < iVar17) {
      iVar16 = *(int *)((int)DAT_8032eea8 + iVar9 + 0x20);
      unaff_r31 = *(int *)((int)DAT_8032eea8 + iVar9 + 0x44);
      fVar2 = *(float *)(&DAT_801dd56c + unaff_r31 * 4);
      PSMTXScale(fVar2,fVar2,fVar2,&MStack_118);
    }
    else {
      iVar16 = *(int *)((int)menuPcs + (iVar13 - iVar17) * 4 + 0x774);
      PSMTXScale(FLOAT_80331eb0,FLOAT_80331eb0,FLOAT_80331eb0,&MStack_118);
    }
    if (iVar13 / iVar17 == 1) {
      PSMTXRotRad(FLOAT_80331f94,&MStack_148,0x78);
      PSMTXConcat(&MStack_118,&MStack_148,&MStack_118);
      PSMTXRotRad(FLOAT_80331f04 * **(float **)&menuPcs->field_0x82c,&MStack_178,0x79);
      PSMTXConcat(&MStack_118,&MStack_178,&MStack_118);
    }
    if (iVar13 < iVar17) {
      MStack_118.value[1][3] = *(float *)(&DAT_801dd55c + unaff_r31 * 4);
    }
    else {
      MStack_118.value[1][3] = FLOAT_80331eac;
    }
    MStack_118.value[0][3] = FLOAT_80331eac;
    *(byte *)(*(int *)(iVar16 + 0x168) + 0x10c) =
         *(byte *)(*(int *)(iVar16 + 0x168) + 0x10c) & 0x7f | 0x80;
    MStack_118.value[2][3] = MStack_118.value[0][3];
    SetMatrix__Q26CChara6CModelFPA4_f(*(CModel **)(iVar16 + 0x168),&MStack_118);
    CalcMatrix__Q26CChara6CModelFv(*(undefined4 *)(iVar16 + 0x168));
    CalcSkin__Q26CChara6CModelFv(*(undefined4 *)(iVar16 + 0x168));
    if (iVar13 < iVar17) {
      *(float *)(*(int *)(iVar16 + 0x168) + 0x9c) = FLOAT_80331eb0;
    }
    else {
      *(undefined4 *)(*(int *)(iVar16 + 0x168) + 0x9c) = *(undefined4 *)(iVar15 + iVar10 + 0x18);
    }
    iVar10 = iVar10 + 0x40;
    iVar9 = iVar9 + 0x2c;
  }
  if (**(short **)&menuPcs->field_0x84c == iVar11) {
    (*(short **)&menuPcs->field_0x84c)[3] = 1;
  }
  return;
}

