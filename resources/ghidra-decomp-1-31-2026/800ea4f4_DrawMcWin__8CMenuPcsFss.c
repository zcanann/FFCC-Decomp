// Function: DrawMcWin__8CMenuPcsFss
// Entry: 800ea4f4
// Size: 1528 bytes

/* WARNING: Removing unreachable block (ram,0x800eaad0) */
/* WARNING: Removing unreachable block (ram,0x800eaac8) */
/* WARNING: Removing unreachable block (ram,0x800eaac0) */
/* WARNING: Removing unreachable block (ram,0x800eaab8) */
/* WARNING: Removing unreachable block (ram,0x800eaab0) */
/* WARNING: Removing unreachable block (ram,0x800eaaa8) */
/* WARNING: Removing unreachable block (ram,0x800eaaa0) */
/* WARNING: Removing unreachable block (ram,0x800eaa98) */
/* WARNING: Removing unreachable block (ram,0x800eaa90) */
/* WARNING: Removing unreachable block (ram,0x800eaa88) */
/* WARNING: Removing unreachable block (ram,0x800ea54c) */
/* WARNING: Removing unreachable block (ram,0x800ea544) */
/* WARNING: Removing unreachable block (ram,0x800ea53c) */
/* WARNING: Removing unreachable block (ram,0x800ea534) */
/* WARNING: Removing unreachable block (ram,0x800ea52c) */
/* WARNING: Removing unreachable block (ram,0x800ea524) */
/* WARNING: Removing unreachable block (ram,0x800ea51c) */
/* WARNING: Removing unreachable block (ram,0x800ea514) */
/* WARNING: Removing unreachable block (ram,0x800ea50c) */
/* WARNING: Removing unreachable block (ram,0x800ea504) */

void DrawMcWin__8CMenuPcsFss(CMenuPcs *menuPcs,short param_2,short param_3)

{
  float fVar1;
  float fVar2;
  short sVar3;
  float fVar4;
  float fVar5;
  uint uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  uint uVar9;
  short *psVar10;
  int iVar11;
  double dVar12;
  double dVar13;
  double dVar14;
  double dVar15;
  double dVar16;
  double dVar17;
  double dVar18;
  double dVar19;
  double dVar20;
  double dVar21;
  undefined4 local_100;
  undefined4 local_fc;
  undefined4 local_f8;
  uint uStack_f4;
  undefined8 local_f0;
  undefined4 local_e8;
  uint uStack_e4;
  undefined8 local_e0;
  longlong local_d8;
  undefined4 local_d0;
  uint uStack_cc;
  longlong local_c8;
  undefined4 local_c0;
  uint uStack_bc;
  
  if ((-1 < param_2) && (*(short *)(*(int *)&menuPcs->field_0x848 + 10) != param_2)) {
    *(short *)(*(int *)&menuPcs->field_0x848 + 10) = param_2;
  }
  psVar10 = *(short **)&menuPcs->field_0x848;
  if (psVar10[5] != 3) {
    uVar9 = (int)*psVar10 ^ 0x80000000;
    local_f0 = (double)CONCAT44(0x43300000,(int)psVar10[2] ^ 0x80000000U);
    uVar6 = (int)psVar10[1] ^ 0x80000000;
    local_e0 = (double)CONCAT44(0x43300000,(int)psVar10[3] ^ 0x80000000U);
    fVar1 = (float)((double)CONCAT44(0x43300000,uVar9) - DOUBLE_80331408) +
            (float)((local_f0 - DOUBLE_80331408) * DOUBLE_803313f8);
    fVar4 = (float)((double)CONCAT44(0x43300000,uVar6) - DOUBLE_80331408) +
            (float)((local_e0 - DOUBLE_80331408) * DOUBLE_803313f8);
    if (psVar10[5] == 1) {
      local_e0 = (double)CONCAT44(0x43300000,uVar9);
      fVar1 = (float)(local_e0 - DOUBLE_80331408);
      fVar2 = (float)((double)CONCAT44(0x43300000,uVar6) - DOUBLE_80331408);
      local_f0 = (double)CONCAT44(0x43300000,(int)psVar10[2] ^ 0x80000000U);
      dVar13 = local_f0 - DOUBLE_80331408;
      dVar12 = (double)CONCAT44(0x43300000,(int)psVar10[3] ^ 0x80000000U) - DOUBLE_80331408;
    }
    else {
      local_e0 = (double)CONCAT44(0x43300000,uVar9);
      local_f0 = (double)CONCAT44(0x43300000,uVar6);
      fVar5 = (((fVar1 - (float)(local_e0 - DOUBLE_80331408)) - FLOAT_80331410) / FLOAT_80331414) *
              (float)((double)CONCAT44(0x43300000,(int)psVar10[4] ^ 0x80000000U) - DOUBLE_80331408);
      fVar2 = (((fVar4 - (float)(local_f0 - DOUBLE_80331408)) - FLOAT_80331410) / FLOAT_80331414) *
              (float)((double)CONCAT44(0x43300000,(int)psVar10[4] ^ 0x80000000U) - DOUBLE_80331408);
      fVar1 = (fVar1 - FLOAT_80331410) - fVar5;
      dVar13 = DOUBLE_80331418 * (double)(FLOAT_80331410 + fVar5);
      dVar12 = DOUBLE_80331418 * (double)(FLOAT_80331410 + fVar2);
      fVar2 = (fVar4 - FLOAT_80331410) - fVar2;
    }
    local_e8 = 0x43300000;
    local_d0 = 0x43300000;
    local_e0 = (double)(longlong)(int)((double)fVar1 - DOUBLE_803313f8);
    local_f8 = 0x43300000;
    local_f0 = (double)(longlong)(int)((double)fVar2 - DOUBLE_803313f8);
    local_c0 = 0x43300000;
    local_d8 = (longlong)(int)((double)(float)dVar13 - DOUBLE_80331420);
    local_c8 = (longlong)(int)((double)(float)dVar12 - DOUBLE_80331420);
    uStack_e4 = (int)((double)fVar1 - DOUBLE_803313f8) ^ 0x80000000;
    uStack_f4 = (int)((double)fVar2 - DOUBLE_803313f8) ^ 0x80000000;
    uStack_cc = (int)((double)(float)dVar13 - DOUBLE_80331420) ^ 0x80000000;
    uStack_bc = (int)((double)(float)dVar12 - DOUBLE_80331420) ^ 0x80000000;
    dVar12 = (double)(float)((double)CONCAT44(0x43300000,uStack_e4) - DOUBLE_80331408);
    dVar13 = (double)(float)((double)CONCAT44(0x43300000,uStack_f4) - DOUBLE_80331408);
    dVar20 = (double)(float)((double)CONCAT44(0x43300000,uStack_cc) - DOUBLE_80331408);
    dVar19 = (double)(float)((double)CONCAT44(0x43300000,uStack_bc) - DOUBLE_80331408);
    SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
    local_fc = 0xffffffff;
    local_100 = 0xffffffff;
    GXSetChanMatColor(4,&local_100);
    uVar7 = 0x2c;
    if (param_3 != 0) {
      uVar7 = 0x24;
    }
    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,uVar7);
    dVar16 = (double)FLOAT_803313dc;
    dVar21 = (double)((float)(dVar12 + dVar20) - FLOAT_80331410);
    uVar6 = 0;
    dVar15 = (double)((float)(dVar13 + dVar19) - FLOAT_80331410);
    do {
      uVar9 = 0;
      dVar14 = dVar12;
      if ((uVar6 & 1) != 0) {
        uVar9 = 8;
        dVar14 = dVar21;
      }
      dVar17 = dVar13;
      if ((uVar6 & 2) != 0) {
        uVar9 = uVar9 | 4;
        dVar17 = dVar15;
      }
      DrawRect__8CMenuPcsFUlfffffffff
                (dVar14,dVar17,(double)FLOAT_80331410,(double)FLOAT_80331410,dVar16,dVar16,
                 (double)FLOAT_803313e8,(double)FLOAT_803313e8,&MenuPcs,uVar9);
      uVar6 = uVar6 + 1;
    } while ((int)uVar6 < 4);
    uVar7 = 0x2d;
    if (param_3 != 0) {
      uVar7 = 0x26;
    }
    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,uVar7);
    dVar20 = dVar20 - DOUBLE_80331428;
    dVar17 = (double)FLOAT_803313dc;
    dVar18 = (double)(float)((double)FLOAT_80331410 + dVar12);
    iVar11 = 0;
    dVar14 = (double)(float)dVar20;
    dVar16 = dVar13;
    do {
      uVar7 = 0;
      if (iVar11 != 0) {
        uVar7 = 4;
        dVar13 = dVar15;
      }
      DrawRect__8CMenuPcsFUlfffffffff
                (dVar18,dVar13,dVar14,(double)FLOAT_80331410,dVar17,dVar17,(double)FLOAT_803313e8,
                 (double)FLOAT_803313e8,&MenuPcs,uVar7);
      iVar11 = iVar11 + 1;
    } while (iVar11 < 2);
    uVar7 = 0x2e;
    if (param_3 != 0) {
      uVar7 = 0x25;
    }
    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,uVar7);
    dVar19 = dVar19 - DOUBLE_80331428;
    iVar11 = 0;
    dVar15 = (double)(float)((double)FLOAT_80331410 + dVar16);
    dVar16 = (double)FLOAT_803313dc;
    dVar13 = (double)(float)dVar19;
    do {
      uVar7 = 0;
      if (iVar11 != 0) {
        uVar7 = 8;
        dVar12 = dVar21;
      }
      DrawRect__8CMenuPcsFUlfffffffff
                (dVar12,dVar15,(double)FLOAT_80331410,dVar13,dVar16,dVar16,(double)FLOAT_803313e8,
                 (double)FLOAT_803313e8,&MenuPcs,uVar7);
      iVar11 = iVar11 + 1;
    } while (iVar11 < 2);
    uVar8 = 0x2f;
    if (param_3 != 0) {
      uVar8 = 0x27;
    }
    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,uVar8);
    DrawRect__8CMenuPcsFUlfffffffff
              (dVar18,dVar15,(double)(float)dVar20,(double)(float)dVar19,(double)FLOAT_803313dc,
               (double)FLOAT_803313dc,(double)FLOAT_803313e8,(double)FLOAT_803313e8,&MenuPcs,uVar7);
    iVar11 = *(int *)&menuPcs->field_0x848;
    sVar3 = *(short *)(iVar11 + 10);
    if (sVar3 == 0) {
      *(short *)(iVar11 + 8) = *(short *)(iVar11 + 8) + 1;
      if (5 < *(short *)(*(int *)&menuPcs->field_0x848 + 8)) {
        *(undefined2 *)(*(int *)&menuPcs->field_0x848 + 8) = 6;
        *(undefined2 *)(*(int *)&menuPcs->field_0x848 + 10) = 1;
      }
    }
    else if (sVar3 == 1) {
      if (*(short *)(iVar11 + 8) != 6) {
        *(undefined2 *)(iVar11 + 8) = 6;
      }
    }
    else if (sVar3 == 2) {
      *(short *)(iVar11 + 8) = *(short *)(iVar11 + 8) + -1;
      if (*(short *)(*(int *)&menuPcs->field_0x848 + 8) < 1) {
        *(undefined2 *)(*(int *)&menuPcs->field_0x848 + 8) = 0;
        *(undefined2 *)(*(int *)&menuPcs->field_0x848 + 10) = 3;
      }
    }
  }
  return;
}

