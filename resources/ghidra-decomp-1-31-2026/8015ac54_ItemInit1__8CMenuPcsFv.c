// Function: ItemInit1__8CMenuPcsFv
// Entry: 8015ac54
// Size: 604 bytes

void ItemInit1__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  float fVar1;
  int iVar2;
  short *psVar3;
  uint uVar4;
  uint uVar5;
  
  iVar2 = *(int *)&menuPcs->field_0x850;
  *(undefined4 *)(iVar2 + 0x24) = 0x2e;
  *(undefined4 *)(iVar2 + 0x2c) = 2;
  *(undefined4 *)(iVar2 + 0x30) = 5;
  iVar2 = *(int *)&menuPcs->field_0x850;
  *(undefined4 *)(iVar2 + 100) = 0x47;
  *(undefined4 *)(iVar2 + 0x6c) = 7;
  *(undefined4 *)(iVar2 + 0x70) = 5;
  iVar2 = *(int *)&menuPcs->field_0x850;
  *(undefined4 *)(iVar2 + 0xa4) = 0x47;
  *(undefined4 *)(iVar2 + 0xac) = 7;
  *(undefined4 *)(iVar2 + 0xb0) = 5;
  iVar2 = *(int *)&menuPcs->field_0x850;
  *(undefined4 *)(iVar2 + 0xf4) = 2;
  *(undefined4 *)(iVar2 + 0xe4) = 0x2e;
  *(undefined4 *)(iVar2 + 0xec) = 7;
  *(undefined4 *)(iVar2 + 0xf0) = 5;
  iVar2 = *(int *)&menuPcs->field_0x850;
  *(undefined4 *)(iVar2 + 0x134) = 2;
  *(undefined4 *)(iVar2 + 0x124) = 0x37;
  *(undefined4 *)(iVar2 + 300) = 0;
  *(undefined4 *)(iVar2 + 0x130) = 5;
  iVar2 = *(int *)&menuPcs->field_0x850;
  *(undefined4 *)(iVar2 + 0x174) = 2;
  *(undefined4 *)(iVar2 + 0x164) = 0x37;
  *(undefined4 *)(iVar2 + 0x16c) = 0;
  *(undefined4 *)(iVar2 + 0x170) = 5;
  iVar2 = *(int *)&menuPcs->field_0x850;
  *(undefined4 *)(iVar2 + 0x1b4) = 2;
  *(undefined4 *)(iVar2 + 0x1a4) = 0x37;
  *(undefined4 *)(iVar2 + 0x1ac) = 0;
  *(undefined4 *)(iVar2 + 0x1b0) = 5;
  iVar2 = *(int *)&menuPcs->field_0x850;
  *(undefined4 *)(iVar2 + 500) = 2;
  *(undefined4 *)(iVar2 + 0x1e4) = 0x37;
  fVar1 = FLOAT_80332e64;
  *(undefined4 *)(iVar2 + 0x1ec) = 0;
  *(undefined4 *)(iVar2 + 0x1f0) = 5;
  iVar2 = *(int *)&menuPcs->field_0x850;
  *(undefined4 *)(iVar2 + 0x234) = 2;
  *(undefined4 *)(iVar2 + 0x224) = 0x37;
  *(undefined4 *)(iVar2 + 0x22c) = 0;
  *(undefined4 *)(iVar2 + 0x230) = 5;
  iVar2 = *(int *)&menuPcs->field_0x850;
  *(undefined4 *)(iVar2 + 0x274) = 2;
  *(undefined4 *)(iVar2 + 0x264) = 0x37;
  *(undefined4 *)(iVar2 + 0x26c) = 0;
  *(undefined4 *)(iVar2 + 0x270) = 5;
  iVar2 = *(int *)&menuPcs->field_0x850;
  *(undefined4 *)(iVar2 + 0x2b4) = 2;
  *(undefined4 *)(iVar2 + 0x2a4) = 0x37;
  *(undefined4 *)(iVar2 + 0x2ac) = 0;
  *(undefined4 *)(iVar2 + 0x2b0) = 5;
  iVar2 = *(int *)&menuPcs->field_0x850;
  *(undefined4 *)(iVar2 + 0x2f4) = 2;
  *(undefined4 *)(iVar2 + 0x2e4) = 0x37;
  *(undefined4 *)(iVar2 + 0x2ec) = 0;
  *(undefined4 *)(iVar2 + 0x2f0) = 5;
  uVar4 = (uint)**(short **)&menuPcs->field_0x850;
  psVar3 = *(short **)&menuPcs->field_0x850 + 4;
  if (0 < (int)uVar4) {
    uVar5 = uVar4 >> 3;
    if (uVar5 != 0) {
      do {
        psVar3[0x10] = 0;
        psVar3[0x11] = 0;
        *(float *)(psVar3 + 8) = fVar1;
        psVar3[0x30] = 0;
        psVar3[0x31] = 0;
        *(float *)(psVar3 + 0x28) = fVar1;
        psVar3[0x50] = 0;
        psVar3[0x51] = 0;
        *(float *)(psVar3 + 0x48) = fVar1;
        psVar3[0x70] = 0;
        psVar3[0x71] = 0;
        *(float *)(psVar3 + 0x68) = fVar1;
        psVar3[0x90] = 0;
        psVar3[0x91] = 0;
        *(float *)(psVar3 + 0x88) = fVar1;
        psVar3[0xb0] = 0;
        psVar3[0xb1] = 0;
        *(float *)(psVar3 + 0xa8) = fVar1;
        psVar3[0xd0] = 0;
        psVar3[0xd1] = 0;
        *(float *)(psVar3 + 200) = fVar1;
        psVar3[0xf0] = 0;
        psVar3[0xf1] = 0;
        *(float *)(psVar3 + 0xe8) = fVar1;
        psVar3 = psVar3 + 0x100;
        uVar5 = uVar5 - 1;
      } while (uVar5 != 0);
      uVar4 = uVar4 & 7;
      if (uVar4 == 0) {
        return;
      }
    }
    do {
      psVar3[0x10] = 0;
      psVar3[0x11] = 0;
      *(float *)(psVar3 + 8) = fVar1;
      psVar3 = psVar3 + 0x20;
      uVar4 = uVar4 - 1;
    } while (uVar4 != 0);
  }
  return;
}

