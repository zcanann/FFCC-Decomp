// Function: CmdInit2__8CMenuPcsFv
// Entry: 8014fc50
// Size: 700 bytes

void CmdInit2__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  short sVar1;
  float fVar2;
  int iVar3;
  undefined4 uVar4;
  uint uVar5;
  int iVar6;
  short *psVar7;
  uint uVar8;
  
  uVar4 = 0x2f;
  psVar7 = *(short **)&menuPcs->field_0x850;
  sVar1 = *psVar7;
  iVar3 = (int)sVar1;
  (psVar7 + iVar3 * 0x20 + 0x12)[0] = 0;
  (psVar7 + iVar3 * 0x20 + 0x12)[1] = 0x2e;
  (psVar7 + iVar3 * 0x20 + 0x16)[0] = 0;
  (psVar7 + iVar3 * 0x20 + 0x16)[1] = 2;
  (psVar7 + iVar3 * 0x20 + 0x18)[0] = 0;
  (psVar7 + iVar3 * 0x20 + 0x18)[1] = 5;
  iVar6 = *(int *)&menuPcs->field_0x850 + (iVar3 + 1) * 0x40 + 8;
  if (*(short *)&menuPcs->field_0x864 == 0) {
    uVar4 = 0x46;
  }
  *(undefined4 *)(iVar6 + 0x1c) = uVar4;
  *(undefined4 *)(iVar6 + 0x24) = 7;
  uVar4 = 0x2f;
  *(undefined4 *)(iVar6 + 0x28) = 5;
  iVar6 = *(int *)&menuPcs->field_0x850 + (iVar3 + 2) * 0x40 + 8;
  if (*(short *)&menuPcs->field_0x864 == 0) {
    uVar4 = 0x46;
  }
  *(undefined4 *)(iVar6 + 0x1c) = uVar4;
  *(undefined4 *)(iVar6 + 0x24) = 7;
  *(undefined4 *)(iVar6 + 0x28) = 5;
  iVar6 = *(int *)&menuPcs->field_0x850 + (iVar3 + 3) * 0x40 + 8;
  *(undefined4 *)(iVar6 + 0x2c) = 2;
  *(undefined4 *)(iVar6 + 0x1c) = 0x2e;
  *(undefined4 *)(iVar6 + 0x24) = 7;
  *(undefined4 *)(iVar6 + 0x28) = 5;
  iVar6 = *(int *)&menuPcs->field_0x850 + (iVar3 + 4) * 0x40 + 8;
  *(undefined4 *)(iVar6 + 0x2c) = 2;
  *(undefined4 *)(iVar6 + 0x1c) = 0x37;
  *(undefined4 *)(iVar6 + 0x24) = 0;
  *(undefined4 *)(iVar6 + 0x28) = 5;
  iVar6 = *(int *)&menuPcs->field_0x850 + (iVar3 + 5) * 0x40 + 8;
  *(undefined4 *)(iVar6 + 0x2c) = 2;
  *(undefined4 *)(iVar6 + 0x1c) = 0x37;
  *(undefined4 *)(iVar6 + 0x24) = 0;
  *(undefined4 *)(iVar6 + 0x28) = 5;
  iVar6 = *(int *)&menuPcs->field_0x850 + (iVar3 + 6) * 0x40 + 8;
  *(undefined4 *)(iVar6 + 0x2c) = 2;
  *(undefined4 *)(iVar6 + 0x1c) = 0x37;
  *(undefined4 *)(iVar6 + 0x24) = 0;
  *(undefined4 *)(iVar6 + 0x28) = 5;
  iVar6 = *(int *)&menuPcs->field_0x850 + (iVar3 + 7) * 0x40 + 8;
  *(undefined4 *)(iVar6 + 0x2c) = 2;
  *(undefined4 *)(iVar6 + 0x1c) = 0x37;
  *(undefined4 *)(iVar6 + 0x24) = 0;
  *(undefined4 *)(iVar6 + 0x28) = 5;
  iVar6 = *(int *)&menuPcs->field_0x850 + (iVar3 + 8) * 0x40 + 8;
  *(undefined4 *)(iVar6 + 0x2c) = 2;
  *(undefined4 *)(iVar6 + 0x1c) = 0x37;
  *(undefined4 *)(iVar6 + 0x24) = 0;
  *(undefined4 *)(iVar6 + 0x28) = 5;
  iVar6 = *(int *)&menuPcs->field_0x850 + (iVar3 + 9) * 0x40 + 8;
  *(undefined4 *)(iVar6 + 0x2c) = 2;
  *(undefined4 *)(iVar6 + 0x1c) = 0x37;
  *(undefined4 *)(iVar6 + 0x24) = 0;
  *(undefined4 *)(iVar6 + 0x28) = 5;
  fVar2 = FLOAT_80332a70;
  iVar6 = *(int *)&menuPcs->field_0x850 + (iVar3 + 10) * 0x40 + 8;
  *(undefined4 *)(iVar6 + 0x2c) = 2;
  *(undefined4 *)(iVar6 + 0x1c) = 0x37;
  *(undefined4 *)(iVar6 + 0x24) = 0;
  *(undefined4 *)(iVar6 + 0x28) = 5;
  iVar3 = *(int *)&menuPcs->field_0x850 + (iVar3 + 0xb) * 0x40 + 8;
  *(undefined4 *)(iVar3 + 0x2c) = 2;
  *(undefined4 *)(iVar3 + 0x1c) = 0x37;
  *(undefined4 *)(iVar3 + 0x24) = 0;
  *(undefined4 *)(iVar3 + 0x28) = 5;
  *(short *)(*(int *)&menuPcs->field_0x850 + 2) = sVar1 + 0xc;
  psVar7 = *(short **)&menuPcs->field_0x850;
  uVar5 = (int)psVar7[1] - (int)*psVar7;
  psVar7 = psVar7 + *psVar7 * 0x20 + 4;
  if (0 < (int)uVar5) {
    uVar8 = uVar5 >> 3;
    if (uVar8 != 0) {
      do {
        psVar7[0x10] = 0;
        psVar7[0x11] = 0;
        *(float *)(psVar7 + 8) = fVar2;
        psVar7[0x30] = 0;
        psVar7[0x31] = 0;
        *(float *)(psVar7 + 0x28) = fVar2;
        psVar7[0x50] = 0;
        psVar7[0x51] = 0;
        *(float *)(psVar7 + 0x48) = fVar2;
        psVar7[0x70] = 0;
        psVar7[0x71] = 0;
        *(float *)(psVar7 + 0x68) = fVar2;
        psVar7[0x90] = 0;
        psVar7[0x91] = 0;
        *(float *)(psVar7 + 0x88) = fVar2;
        psVar7[0xb0] = 0;
        psVar7[0xb1] = 0;
        *(float *)(psVar7 + 0xa8) = fVar2;
        psVar7[0xd0] = 0;
        psVar7[0xd1] = 0;
        *(float *)(psVar7 + 200) = fVar2;
        psVar7[0xf0] = 0;
        psVar7[0xf1] = 0;
        *(float *)(psVar7 + 0xe8) = fVar2;
        psVar7 = psVar7 + 0x100;
        uVar8 = uVar8 - 1;
      } while (uVar8 != 0);
      uVar5 = uVar5 & 7;
      if (uVar5 == 0) {
        return;
      }
    }
    do {
      psVar7[0x10] = 0;
      psVar7[0x11] = 0;
      *(float *)(psVar7 + 8) = fVar2;
      psVar7 = psVar7 + 0x20;
      uVar5 = uVar5 - 1;
    } while (uVar5 != 0);
  }
  return;
}

