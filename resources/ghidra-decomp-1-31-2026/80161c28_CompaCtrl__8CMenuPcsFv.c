// Function: CompaCtrl__8CMenuPcsFv
// Entry: 80161c28
// Size: 800 bytes

void CompaCtrl__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  bool bVar1;
  float fVar2;
  ushort uVar4;
  short sVar5;
  int iVar3;
  short *psVar6;
  uint uVar7;
  uint uVar8;
  
  bVar1 = false;
  if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
    bVar1 = true;
  }
  if (bVar1) {
    uVar4 = 0;
  }
  else {
    countLeadingZeros(Pad._448_4_);
    uVar4 = Pad._8_2_;
  }
  bVar1 = false;
  if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
    bVar1 = true;
  }
  if (bVar1) {
    sVar5 = 0;
  }
  else {
    countLeadingZeros(Pad._448_4_);
    sVar5 = Pad._20_2_;
  }
  if (sVar5 == 0) {
    bVar1 = false;
  }
  else if ((uVar4 & 0x20) == 0) {
    if ((uVar4 & 0x40) == 0) {
      if ((uVar4 & 0x100) == 0) {
        if ((uVar4 & 0x200) != 0) {
          *(undefined *)(*(int *)&menuPcs->field_0x82c + 0xd) = 1;
          PlaySe__6CSoundFiiii(&Sound,3,0x40,0x7f,0);
          bVar1 = true;
          goto LAB_80161df0;
        }
      }
      else {
        PlaySe__6CSoundFiiii(&Sound,4,0x40,0x7f,0);
      }
      bVar1 = false;
    }
    else {
      *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x1e) = 0xffff;
      PlaySe__6CSoundFiiii(&Sound,0x5a,0x40,0x7f,0);
      bVar1 = true;
    }
  }
  else {
    *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x1e) = 1;
    PlaySe__6CSoundFiiii(&Sound,0x5a,0x40,0x7f,0);
    bVar1 = true;
  }
LAB_80161df0:
  if (bVar1) {
    iVar3 = *(int *)&menuPcs->field_0x850;
    *(undefined4 *)(iVar3 + 0x2c) = 2;
    *(undefined4 *)(iVar3 + 0x30) = 5;
    iVar3 = *(int *)&menuPcs->field_0x850;
    *(undefined4 *)(iVar3 + 0x6c) = 2;
    fVar2 = FLOAT_80333000;
    *(undefined4 *)(iVar3 + 0x70) = 5;
    iVar3 = *(int *)&menuPcs->field_0x850;
    *(undefined4 *)(iVar3 + 0xac) = 2;
    *(undefined4 *)(iVar3 + 0xb0) = 5;
    iVar3 = *(int *)&menuPcs->field_0x850;
    *(undefined4 *)(iVar3 + 0xec) = 7;
    *(undefined4 *)(iVar3 + 0xf0) = 5;
    iVar3 = *(int *)&menuPcs->field_0x850;
    *(undefined4 *)(iVar3 + 300) = 7;
    *(undefined4 *)(iVar3 + 0x130) = 5;
    iVar3 = *(int *)&menuPcs->field_0x850;
    *(undefined4 *)(iVar3 + 0x174) = 2;
    *(undefined4 *)(iVar3 + 0x16c) = 7;
    *(undefined4 *)(iVar3 + 0x170) = 5;
    uVar7 = (uint)**(short **)&menuPcs->field_0x850;
    psVar6 = *(short **)&menuPcs->field_0x850 + 4;
    if (0 < (int)uVar7) {
      uVar8 = uVar7 >> 3;
      if (uVar8 != 0) {
        do {
          psVar6[0x10] = 0;
          psVar6[0x11] = 0;
          *(float *)(psVar6 + 8) = fVar2;
          psVar6[0x30] = 0;
          psVar6[0x31] = 0;
          *(float *)(psVar6 + 0x28) = fVar2;
          psVar6[0x50] = 0;
          psVar6[0x51] = 0;
          *(float *)(psVar6 + 0x48) = fVar2;
          psVar6[0x70] = 0;
          psVar6[0x71] = 0;
          *(float *)(psVar6 + 0x68) = fVar2;
          psVar6[0x90] = 0;
          psVar6[0x91] = 0;
          *(float *)(psVar6 + 0x88) = fVar2;
          psVar6[0xb0] = 0;
          psVar6[0xb1] = 0;
          *(float *)(psVar6 + 0xa8) = fVar2;
          psVar6[0xd0] = 0;
          psVar6[0xd1] = 0;
          *(float *)(psVar6 + 200) = fVar2;
          psVar6[0xf0] = 0;
          psVar6[0xf1] = 0;
          *(float *)(psVar6 + 0xe8) = fVar2;
          psVar6 = psVar6 + 0x100;
          uVar8 = uVar8 - 1;
        } while (uVar8 != 0);
        uVar7 = uVar7 & 7;
        if (uVar7 == 0) {
          return;
        }
      }
      do {
        psVar6[0x10] = 0;
        psVar6[0x11] = 0;
        *(float *)(psVar6 + 8) = fVar2;
        psVar6 = psVar6 + 0x20;
        uVar7 = uVar7 - 1;
      } while (uVar7 != 0);
    }
  }
  return;
}

