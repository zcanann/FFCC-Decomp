// Function: FavoInit__8CMenuPcsFv
// Entry: 8016343c
// Size: 1296 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void FavoInit__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  undefined uVar1;
  undefined uVar2;
  uint32_t uVar3;
  float fVar4;
  float fVar5;
  double dVar6;
  float fVar7;
  int iVar8;
  short sVar9;
  short sVar10;
  short sVar11;
  undefined *puVar12;
  undefined *puVar13;
  short *psVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  
  uVar3 = Game.game.m_scriptFoodBase[0];
  memset(*(undefined4 *)&menuPcs->field_0x850,0,0x1008);
  fVar4 = FLOAT_80333048;
  iVar8 = *(int *)&menuPcs->field_0x850 + 8;
  iVar16 = 8;
  do {
    *(float *)(iVar8 + 0x14) = fVar4;
    *(float *)(iVar8 + 0x54) = fVar4;
    *(float *)(iVar8 + 0x94) = fVar4;
    *(float *)(iVar8 + 0xd4) = fVar4;
    *(float *)(iVar8 + 0x114) = fVar4;
    *(float *)(iVar8 + 0x154) = fVar4;
    *(float *)(iVar8 + 0x194) = fVar4;
    *(float *)(iVar8 + 0x1d4) = fVar4;
    iVar8 = iVar8 + 0x200;
    iVar16 = iVar16 + -1;
  } while (iVar16 != 0);
  iVar8 = *(int *)&menuPcs->field_0x850;
  *(undefined4 *)(iVar8 + 0x24) = 0x33;
  *(undefined4 *)(iVar8 + 0x20) = 4;
  *(undefined2 *)(iVar8 + 8) = 0x30;
  fVar4 = FLOAT_80333040;
  *(undefined2 *)(iVar8 + 10) = 0x28;
  dVar6 = DOUBLE_80333078;
  *(undefined2 *)(iVar8 + 0xc) = 0x158;
  fVar5 = FLOAT_80333080;
  *(undefined2 *)(iVar8 + 0xe) = 0x20;
  *(float *)(iVar8 + 0x10) = fVar4;
  *(float *)(iVar8 + 0x14) = fVar4;
  *(float *)(iVar8 + 0x1c) =
       fVar5 / (float)((double)CONCAT44(0x43300000,(int)*(short *)(iVar8 + 0xc) ^ 0x80000000) -
                      dVar6);
  *(undefined4 *)(iVar8 + 0x2c) = 5;
  *(undefined4 *)(iVar8 + 0x30) = 5;
  iVar8 = *(int *)&menuPcs->field_0x850;
  *(undefined4 *)(iVar8 + 100) = 0x32;
  *(undefined2 *)(iVar8 + 0x48) = 0x30;
  *(undefined2 *)(iVar8 + 0x4a) = 0x48;
  *(undefined2 *)(iVar8 + 0x4c) = 0x158;
  *(undefined2 *)(iVar8 + 0x4e) = 200;
  *(float *)(iVar8 + 0x50) = fVar4;
  *(float *)(iVar8 + 0x54) = fVar4;
  *(float *)(iVar8 + 0x5c) =
       fVar5 / (float)((double)CONCAT44(0x43300000,(int)*(short *)(iVar8 + 0x4c) ^ 0x80000000) -
                      dVar6);
  *(undefined4 *)(iVar8 + 0x6c) = 5;
  *(undefined4 *)(iVar8 + 0x70) = 5;
  iVar8 = *(int *)&menuPcs->field_0x850;
  *(undefined4 *)(iVar8 + 0xa4) = 0x33;
  *(undefined2 *)(iVar8 + 0x88) = 0x30;
  *(undefined2 *)(iVar8 + 0x8a) = 0x110;
  *(undefined2 *)(iVar8 + 0x8c) = 0x158;
  *(undefined2 *)(iVar8 + 0x8e) = 0x20;
  *(float *)(iVar8 + 0x90) = fVar4;
  *(float *)(iVar8 + 0x94) = fVar4;
  *(float *)(iVar8 + 0x9c) =
       fVar5 / (float)((double)CONCAT44(0x43300000,(int)*(short *)(iVar8 + 0x8c) ^ 0x80000000) -
                      dVar6);
  *(undefined4 *)(iVar8 + 0xac) = 5;
  *(undefined4 *)(iVar8 + 0xb0) = 5;
  iVar8 = *(int *)&menuPcs->field_0x850;
  *(undefined4 *)(iVar8 + 0xe4) = 0x45;
  fVar5 = FLOAT_80333048;
  sVar9 = 0;
  *(undefined2 *)(iVar8 + 200) = 0x18;
  fVar7 = FLOAT_80333084;
  sVar11 = 6;
  *(undefined2 *)(iVar8 + 0xca) = 0xe;
  *(undefined2 *)(iVar8 + 0xcc) = 0x30;
  iVar16 = 0x180;
  *(undefined2 *)(iVar8 + 0xce) = 0x30;
  *(float *)(iVar8 + 0xd0) = fVar4;
  *(float *)(iVar8 + 0xd4) = fVar4;
  *(float *)(iVar8 + 0xdc) = fVar5;
  *(undefined4 *)(iVar8 + 0xec) = 0;
  *(undefined4 *)(iVar8 + 0xf0) = 5;
  iVar8 = *(int *)&menuPcs->field_0x850;
  *(undefined4 *)(iVar8 + 0x124) = 0x45;
  *(undefined2 *)(iVar8 + 0x108) = 0x1d;
  *(undefined2 *)(iVar8 + 0x10c) = 0x30;
  *(undefined2 *)(iVar8 + 0x10e) = 0x30;
  *(short *)(iVar8 + 0x10a) = 0x150 - *(short *)(iVar8 + 0x10e);
  *(float *)(iVar8 + 0x110) = fVar4;
  *(float *)(iVar8 + 0x114) = fVar4;
  *(float *)(iVar8 + 0x11c) = fVar7;
  *(undefined4 *)(iVar8 + 300) = 0;
  *(undefined4 *)(iVar8 + 0x130) = 5;
  iVar8 = *(int *)&menuPcs->field_0x850;
  *(undefined4 *)(iVar8 + 0x174) = 2;
  *(undefined4 *)(iVar8 + 0x164) = 0x2e;
  *(undefined2 *)(iVar8 + 0x148) = 0x18;
  *(undefined2 *)(iVar8 + 0x14a) = 8;
  *(undefined2 *)(iVar8 + 0x14c) = 0x48;
  *(undefined2 *)(iVar8 + 0x14e) = 0x140;
  *(float *)(iVar8 + 0x150) = fVar4;
  *(float *)(iVar8 + 0x154) = fVar4;
  *(undefined4 *)(iVar8 + 0x16c) = 0;
  *(undefined4 *)(iVar8 + 0x170) = 5;
  iVar8 = *(int *)&menuPcs->field_0x850;
  iVar17 = 4;
  do {
    psVar14 = (short *)(*(int *)&menuPcs->field_0x850 + iVar16 + 8);
    psVar14[0x16] = 0;
    psVar14[0x17] = 2;
    psVar14[0xe] = 0;
    psVar14[0xf] = 0x37;
    sVar11 = sVar11 + 2;
    *psVar14 = *(short *)(iVar8 + 8) + 0x28;
    sVar10 = sVar9 + 0x20;
    psVar14[1] = *(short *)(iVar8 + 10) + sVar9;
    psVar14[2] = 200;
    psVar14[3] = 0x28;
    *(float *)(psVar14 + 4) = fVar4;
    *(float *)(psVar14 + 6) = fVar4;
    psVar14[0x12] = 0;
    psVar14[0x13] = 7;
    psVar14[0x14] = 0;
    psVar14[0x15] = 5;
    iVar15 = iVar16 + 0x48;
    iVar16 = iVar16 + 0x80;
    psVar14 = (short *)(*(int *)&menuPcs->field_0x850 + iVar15);
    psVar14[0x16] = 0;
    psVar14[0x17] = 2;
    psVar14[0xe] = 0;
    psVar14[0xf] = 0x37;
    *psVar14 = *(short *)(iVar8 + 8) + 0x28;
    sVar9 = sVar9 + 0x40;
    psVar14[1] = *(short *)(iVar8 + 10) + sVar10;
    psVar14[2] = 200;
    psVar14[3] = 0x28;
    *(float *)(psVar14 + 4) = fVar4;
    *(float *)(psVar14 + 6) = fVar4;
    psVar14[0x12] = 0;
    psVar14[0x13] = 7;
    psVar14[0x14] = 0;
    psVar14[0x15] = 5;
    iVar17 = iVar17 + -1;
  } while (iVar17 != 0);
  **(short **)&menuPcs->field_0x850 = sVar11;
  memset(s_rank,0,0x20);
  iVar8 = 0;
  puVar13 = s_rank;
  s_rank[1] = 0;
  s_rank._2_2_ = *(undefined2 *)(uVar3 + 0x3b8);
  s_rank[5] = 1;
  s_rank._6_2_ = *(undefined2 *)(uVar3 + 0x3ba);
  s_rank[9] = 2;
  s_rank._10_2_ = *(undefined2 *)(uVar3 + 0x3bc);
  s_rank[0xd] = 3;
  s_rank._14_2_ = *(undefined2 *)(uVar3 + 0x3be);
  s_rank[0x11] = 4;
  s_rank._18_2_ = *(undefined2 *)(uVar3 + 0x3c0);
  s_rank[0x15] = 5;
  s_rank._22_2_ = *(undefined2 *)(uVar3 + 0x3c2);
  s_rank[0x19] = 6;
  s_rank._26_2_ = *(undefined2 *)(uVar3 + 0x3c4);
  s_rank[0x1d] = 7;
  s_rank._30_2_ = *(undefined2 *)(uVar3 + 0x3c6);
  do {
    iVar17 = iVar8 + 1;
    iVar16 = 8 - iVar17;
    puVar12 = s_rank + iVar17 * 4;
    if (iVar17 < 8) {
      do {
        sVar9 = *(short *)(puVar13 + 2);
        if (sVar9 < *(short *)(puVar12 + 2)) {
          uVar1 = *puVar13;
          uVar2 = puVar13[1];
          *puVar13 = *puVar12;
          puVar13[1] = puVar12[1];
          *(short *)(puVar13 + 2) = *(short *)(puVar12 + 2);
          *puVar12 = uVar1;
          puVar12[1] = uVar2;
          *(short *)(puVar12 + 2) = sVar9;
        }
        puVar12 = puVar12 + 4;
        iVar16 = iVar16 + -1;
      } while (iVar16 != 0);
    }
    iVar8 = iVar8 + 1;
    puVar13 = puVar13 + 4;
  } while (iVar8 < 8);
  iVar8 = 0;
  iVar17 = 0;
  iVar16 = 8;
  puVar13 = s_rank;
  do {
    if ((iVar17 != 0) && (*(short *)(puVar13 + -2) != *(short *)(puVar13 + 2))) {
      iVar8 = iVar17;
    }
    iVar17 = iVar17 + 1;
    *puVar13 = (char)iVar8 + '\x01';
    puVar13 = puVar13 + 4;
    iVar16 = iVar16 + -1;
  } while (iVar16 != 0);
  *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x26) = 0;
  *(undefined *)(*(int *)&menuPcs->field_0x82c + 0xb) = 1;
  return;
}

