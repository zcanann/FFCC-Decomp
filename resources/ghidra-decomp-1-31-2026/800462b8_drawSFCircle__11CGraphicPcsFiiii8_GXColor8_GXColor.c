// Function: drawSFCircle__11CGraphicPcsFiiii8_GXColor8_GXColor
// Entry: 800462b8
// Size: 596 bytes

/* WARNING: Removing unreachable block (ram,0x800464f0) */
/* WARNING: Removing unreachable block (ram,0x800464e8) */
/* WARNING: Removing unreachable block (ram,0x800464e0) */
/* WARNING: Removing unreachable block (ram,0x800464d8) */
/* WARNING: Removing unreachable block (ram,0x800462e0) */
/* WARNING: Removing unreachable block (ram,0x800462d8) */
/* WARNING: Removing unreachable block (ram,0x800462d0) */
/* WARNING: Removing unreachable block (ram,0x800462c8) */

void drawSFCircle__11CGraphicPcsFiiii8_GXColor8_GXColor
               (undefined4 param_1,uint param_2,uint param_3,uint param_4,uint param_5,
               undefined4 *param_6,undefined4 *param_7)

{
  float *pfVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  float *pfVar5;
  float *pfVar6;
  int iVar7;
  double dVar8;
  double dVar9;
  double dVar10;
  double dVar11;
  double dVar12;
  float local_2b8 [128];
  undefined4 local_b8;
  uint uStack_b4;
  undefined4 local_b0;
  uint uStack_ac;
  undefined4 local_a8;
  uint uStack_a4;
  undefined4 local_a0;
  uint uStack_9c;
  undefined4 local_98;
  uint uStack_94;
  undefined4 local_90;
  uint uStack_8c;
  undefined4 local_88;
  uint uStack_84;
  undefined4 local_80;
  uint uStack_7c;
  undefined4 local_78;
  uint uStack_74;
  
  pfVar6 = local_2b8;
  dVar11 = (double)FLOAT_8032fbc0;
  param_2 = param_2 ^ 0x80000000;
  param_4 = param_4 ^ 0x80000000;
  param_5 = param_5 ^ 0x80000000;
  param_3 = param_3 ^ 0x80000000;
  uVar4 = 0;
  pfVar5 = pfVar6;
  dVar12 = DOUBLE_8032fbb0;
  do {
    uStack_b4 = uVar4 ^ 0x80000000;
    local_b8 = 0x43300000;
    dVar9 = (double)(float)(dVar11 * (double)(float)((double)CONCAT44(0x43300000,uStack_b4) - dVar12
                                                    ));
    dVar8 = (double)sin(dVar9);
    dVar10 = (double)(float)dVar8;
    dVar8 = (double)cos(dVar9);
    uVar4 = uVar4 + 1;
    local_b0 = 0x43300000;
    local_a8 = 0x43300000;
    local_a0 = 0x43300000;
    local_98 = 0x43300000;
    local_90 = 0x43300000;
    uStack_ac = param_2;
    uStack_a4 = param_4;
    uStack_9c = param_2;
    uStack_94 = param_5;
    uStack_8c = param_3;
    *pfVar5 = (float)(dVar10 * (double)(float)((double)CONCAT44(0x43300000,param_2) - dVar12) +
                     (double)(float)((double)CONCAT44(0x43300000,param_4) - dVar12));
    local_88 = 0x43300000;
    local_80 = 0x43300000;
    uStack_84 = param_4;
    uStack_7c = param_3;
    pfVar5[1] = (float)dVar8 * (float)((double)CONCAT44(0x43300000,param_2) - dVar12) +
                (float)((double)CONCAT44(0x43300000,param_5) - dVar12);
    local_78 = 0x43300000;
    uStack_74 = param_5;
    pfVar5[2] = (float)(dVar10 * (double)(float)((double)CONCAT44(0x43300000,param_3) - dVar12) +
                       (double)(float)((double)CONCAT44(0x43300000,param_4) - dVar12));
    pfVar5[3] = (float)dVar8 * (float)((double)CONCAT44(0x43300000,param_3) - dVar12) +
                (float)((double)CONCAT44(0x43300000,param_5) - dVar12);
    pfVar5 = pfVar5 + 4;
  } while ((int)uVar4 < 0x20);
  GXBegin(0x80,0,0x80);
  iVar3 = 0;
  iVar7 = 0x20;
  do {
    DAT_cc008000 = *pfVar6;
    iVar2 = iVar3 + 1 >> 0x1f;
    DAT_cc008000 = pfVar6[1];
    iVar2 = (iVar2 * 0x20 | (uint)((iVar3 + 1) * 0x8000000 + iVar2) >> 0x1b) - iVar2;
    DAT_cc008000 = FLOAT_8032fb78;
    pfVar5 = pfVar6 + 2;
    DAT_cc008000 = *param_6;
    iVar3 = iVar3 + 1;
    pfVar1 = pfVar6 + 3;
    pfVar6 = pfVar6 + 4;
    DAT_cc008000._0_2_ = 0;
    DAT_cc008000._0_2_ = 0;
    DAT_cc008000 = local_2b8[iVar2 * 4];
    DAT_cc008000 = local_2b8[iVar2 * 4 + 1];
    DAT_cc008000 = FLOAT_8032fb78;
    DAT_cc008000 = *param_6;
    DAT_cc008000._0_2_ = 0;
    DAT_cc008000._0_2_ = 0;
    DAT_cc008000 = local_2b8[iVar2 * 4 + 2];
    DAT_cc008000 = local_2b8[iVar2 * 4 + 3];
    DAT_cc008000 = FLOAT_8032fb78;
    DAT_cc008000 = *param_7;
    DAT_cc008000._0_2_ = 0;
    DAT_cc008000._0_2_ = 0;
    DAT_cc008000 = *pfVar5;
    DAT_cc008000 = *pfVar1;
    DAT_cc008000 = FLOAT_8032fb78;
    DAT_cc008000 = *param_7;
    DAT_cc008000._0_2_ = 0;
    DAT_cc008000._0_2_ = 0;
    iVar7 = iVar7 + -1;
  } while (iVar7 != 0);
  return;
}

