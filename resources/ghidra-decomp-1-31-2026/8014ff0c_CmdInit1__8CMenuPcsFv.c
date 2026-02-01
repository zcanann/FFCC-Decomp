// Function: CmdInit1__8CMenuPcsFv
// Entry: 8014ff0c
// Size: 816 bytes

void CmdInit1__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  short sVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  uint uVar5;
  undefined4 uVar6;
  short sVar7;
  int iVar8;
  int iVar9;
  short *psVar10;
  int iVar11;
  undefined2 *puVar12;
  short *psVar13;
  int iVar14;
  uint uVar15;
  
  fVar4 = FLOAT_80332b38;
  fVar3 = FLOAT_80332ad0;
  fVar2 = FLOAT_80332a70;
  iVar8 = (int)**(short **)&menuPcs->field_0x850;
  psVar10 = *(short **)&menuPcs->field_0x850 + iVar8 * 0x20 + 4;
  psVar10[0xe] = 0;
  psVar10[0xf] = 0x2e;
  uVar6 = 0x2f;
  *psVar10 = 0xb8;
  psVar10[1] = 0x28;
  psVar10[2] = 0x78;
  psVar10[3] = 0x108;
  *(float *)(psVar10 + 4) = fVar4;
  *(float *)(psVar10 + 6) = fVar3;
  *(float *)(psVar10 + 10) = fVar2;
  psVar10[0x12] = 0;
  psVar10[0x13] = 5;
  psVar10[0x14] = 0;
  psVar10[0x15] = 5;
  puVar12 = (undefined2 *)(*(int *)&menuPcs->field_0x850 + (iVar8 + 1) * 0x40 + 8);
  if (*(short *)&menuPcs->field_0x864 == 0) {
    uVar6 = 0x46;
  }
  *(undefined4 *)(puVar12 + 0xe) = uVar6;
  *puVar12 = 0xa0;
  fVar3 = FLOAT_80332ab0;
  puVar12[1] = 0xe;
  fVar2 = FLOAT_80332a70;
  puVar12[2] = 0x30;
  uVar6 = 0x2f;
  puVar12[3] = 0x30;
  *(float *)(puVar12 + 4) = fVar3;
  *(float *)(puVar12 + 6) = fVar3;
  *(float *)(puVar12 + 10) = fVar2;
  *(undefined4 *)(puVar12 + 0x12) = 0;
  *(undefined4 *)(puVar12 + 0x14) = 5;
  puVar12 = (undefined2 *)(*(int *)&menuPcs->field_0x850 + (iVar8 + 2) * 0x40 + 8);
  if (*(short *)&menuPcs->field_0x864 == 0) {
    uVar6 = 0x46;
  }
  *(undefined4 *)(puVar12 + 0xe) = uVar6;
  puVar12[2] = 0x30;
  fVar2 = FLOAT_80332ab0;
  sVar7 = 0;
  puVar12[3] = 0x30;
  fVar3 = FLOAT_80332b3c;
  *puVar12 = 0xa5;
  iVar9 = iVar8 + 4;
  puVar12[1] = 0x150 - puVar12[3];
  iVar11 = iVar9 * 0x40;
  *(float *)(puVar12 + 4) = fVar2;
  *(float *)(puVar12 + 6) = fVar2;
  *(float *)(puVar12 + 10) = fVar3;
  *(undefined4 *)(puVar12 + 0x12) = 0;
  *(undefined4 *)(puVar12 + 0x14) = 5;
  puVar12 = (undefined2 *)(*(int *)&menuPcs->field_0x850 + (iVar8 + 3) * 0x40 + 8);
  *(undefined4 *)(puVar12 + 0x16) = 2;
  *(undefined4 *)(puVar12 + 0xe) = 0x2e;
  *puVar12 = 0xa0;
  puVar12[1] = 8;
  puVar12[2] = 0x48;
  puVar12[3] = 0x140;
  *(float *)(puVar12 + 4) = fVar2;
  *(float *)(puVar12 + 6) = fVar2;
  *(undefined4 *)(puVar12 + 0x12) = 0;
  *(undefined4 *)(puVar12 + 0x14) = 5;
  psVar10 = *(short **)&menuPcs->field_0x850 + **(short **)&menuPcs->field_0x850 * 0x20 + 4;
  iVar8 = 4;
  do {
    psVar13 = (short *)(*(int *)&menuPcs->field_0x850 + iVar11 + 8);
    psVar13[0x16] = 0;
    psVar13[0x17] = 2;
    psVar13[0xe] = 0;
    psVar13[0xf] = 0x37;
    iVar9 = iVar9 + 2;
    *psVar13 = *psVar10 + 0x24;
    sVar1 = sVar7 + 0x20;
    psVar13[1] = psVar10[1] + sVar7;
    psVar13[2] = 200;
    psVar13[3] = 0x28;
    *(float *)(psVar13 + 4) = fVar2;
    *(float *)(psVar13 + 6) = fVar2;
    psVar13[0x12] = 0;
    psVar13[0x13] = 7;
    psVar13[0x14] = 0;
    psVar13[0x15] = 5;
    iVar14 = iVar11 + 0x48;
    iVar11 = iVar11 + 0x80;
    psVar13 = (short *)(*(int *)&menuPcs->field_0x850 + iVar14);
    psVar13[0x16] = 0;
    psVar13[0x17] = 2;
    psVar13[0xe] = 0;
    psVar13[0xf] = 0x37;
    *psVar13 = *psVar10 + 0x24;
    sVar7 = sVar7 + 0x40;
    psVar13[1] = psVar10[1] + sVar1;
    psVar13[2] = 200;
    psVar13[3] = 0x28;
    *(float *)(psVar13 + 4) = fVar2;
    *(float *)(psVar13 + 6) = fVar2;
    psVar13[0x12] = 0;
    psVar13[0x13] = 7;
    psVar13[0x14] = 0;
    fVar3 = FLOAT_80332ab0;
    psVar13[0x15] = 5;
    iVar8 = iVar8 + -1;
  } while (iVar8 != 0);
  *(short *)(*(int *)&menuPcs->field_0x850 + 2) = (short)iVar9;
  psVar10 = *(short **)&menuPcs->field_0x850;
  uVar5 = (int)psVar10[1] - (int)*psVar10;
  psVar10 = psVar10 + *psVar10 * 0x20 + 4;
  if (0 < (int)uVar5) {
    uVar15 = uVar5 >> 3;
    if (uVar15 != 0) {
      do {
        psVar10[0x10] = 0;
        psVar10[0x11] = 0;
        *(float *)(psVar10 + 8) = fVar3;
        psVar10[0x30] = 0;
        psVar10[0x31] = 0;
        *(float *)(psVar10 + 0x28) = fVar3;
        psVar10[0x50] = 0;
        psVar10[0x51] = 0;
        *(float *)(psVar10 + 0x48) = fVar3;
        psVar10[0x70] = 0;
        psVar10[0x71] = 0;
        *(float *)(psVar10 + 0x68) = fVar3;
        psVar10[0x90] = 0;
        psVar10[0x91] = 0;
        *(float *)(psVar10 + 0x88) = fVar3;
        psVar10[0xb0] = 0;
        psVar10[0xb1] = 0;
        *(float *)(psVar10 + 0xa8) = fVar3;
        psVar10[0xd0] = 0;
        psVar10[0xd1] = 0;
        *(float *)(psVar10 + 200) = fVar3;
        psVar10[0xf0] = 0;
        psVar10[0xf1] = 0;
        *(float *)(psVar10 + 0xe8) = fVar3;
        psVar10 = psVar10 + 0x100;
        uVar15 = uVar15 - 1;
      } while (uVar15 != 0);
      uVar5 = uVar5 & 7;
      if (uVar5 == 0) {
        return;
      }
    }
    do {
      psVar10[0x10] = 0;
      psVar10[0x11] = 0;
      *(float *)(psVar10 + 8) = fVar3;
      psVar10 = psVar10 + 0x20;
      uVar5 = uVar5 - 1;
    } while (uVar5 != 0);
  }
  return;
}

