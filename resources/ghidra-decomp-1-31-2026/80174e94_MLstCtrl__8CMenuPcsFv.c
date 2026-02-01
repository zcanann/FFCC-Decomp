// Function: MLstCtrl__8CMenuPcsFv
// Entry: 80174e94
// Size: 892 bytes

void MLstCtrl__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  bool bVar1;
  float fVar2;
  ushort uVar3;
  ushort uVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  
  bVar1 = false;
  if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
    bVar1 = true;
  }
  if (bVar1) {
    uVar3 = 0;
  }
  else {
    countLeadingZeros(Pad._448_4_);
    uVar3 = Pad._8_2_;
  }
  bVar1 = false;
  if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
    bVar1 = true;
  }
  if (bVar1) {
    uVar4 = 0;
  }
  else {
    countLeadingZeros(Pad._448_4_);
    uVar4 = Pad._20_2_;
  }
  if (uVar4 == 0) {
    bVar1 = false;
  }
  else {
    if ((uVar4 & 0x48) == 0) {
      if ((uVar4 & 0x24) != 0) {
        iVar6 = *(int *)&menuPcs->field_0x82c;
        if (*(short *)(iVar6 + 0x26) < 8) {
          *(short *)(iVar6 + 0x26) = *(short *)(iVar6 + 0x26) + 1;
        }
        else {
          *(undefined2 *)(iVar6 + 0x26) = 0;
        }
        PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
      }
    }
    else {
      iVar6 = *(int *)&menuPcs->field_0x82c;
      if (*(short *)(iVar6 + 0x26) == 0) {
        *(undefined2 *)(iVar6 + 0x26) = 8;
      }
      else {
        *(short *)(iVar6 + 0x26) = *(short *)(iVar6 + 0x26) + -1;
      }
      PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
    }
    if ((uVar4 & 0x6c) == 0) {
      if ((uVar3 & 0x100) == 0) {
        if ((uVar3 & 0x200) == 0) goto LAB_80175090;
        *(undefined *)(*(int *)&menuPcs->field_0x82c + 0xd) = 0xff;
        PlaySe__6CSoundFiiii(&Sound,3,0x40,0x7f,0);
        bVar1 = true;
      }
      else {
        PlaySe__6CSoundFiiii(&Sound,2,0x40,0x7f,0);
        bVar1 = true;
      }
    }
    else {
LAB_80175090:
      bVar1 = false;
    }
  }
  fVar2 = FLOAT_803333f0;
  if (!bVar1) {
    return;
  }
  iVar6 = *(int *)&menuPcs->field_0x850 + 8;
  for (iVar7 = 0; uVar5 = (uint)**(short **)&menuPcs->field_0x850, iVar7 < (int)uVar5;
      iVar7 = iVar7 + 1) {
    *(float *)(iVar6 + 0x10) = fVar2;
    *(float *)(iVar6 + 0x14) = fVar2;
    iVar6 = iVar6 + 0x40;
  }
  iVar7 = 0;
  iVar6 = (uVar5 - 1) * 0x40;
  if (-1 < (int)(uVar5 - 1)) {
    uVar9 = uVar5 >> 3;
    if (uVar9 != 0) {
      do {
        iVar8 = *(int *)&menuPcs->field_0x850 + iVar6 + 8;
        *(int *)(iVar8 + 0x24) = iVar7;
        *(undefined4 *)(iVar8 + 0x28) = 4;
        iVar8 = *(int *)&menuPcs->field_0x850 + iVar6 + -0x38;
        *(int *)(iVar8 + 0x24) = iVar7 + 1;
        *(undefined4 *)(iVar8 + 0x28) = 4;
        iVar8 = *(int *)&menuPcs->field_0x850 + iVar6 + -0x78;
        *(int *)(iVar8 + 0x24) = iVar7 + 2;
        *(undefined4 *)(iVar8 + 0x28) = 4;
        iVar8 = *(int *)&menuPcs->field_0x850 + iVar6 + -0xb8;
        *(int *)(iVar8 + 0x24) = iVar7 + 3;
        *(undefined4 *)(iVar8 + 0x28) = 4;
        iVar8 = *(int *)&menuPcs->field_0x850 + iVar6 + -0xf8;
        *(int *)(iVar8 + 0x24) = iVar7 + 4;
        *(undefined4 *)(iVar8 + 0x28) = 4;
        iVar8 = *(int *)&menuPcs->field_0x850 + iVar6 + -0x138;
        *(int *)(iVar8 + 0x24) = iVar7 + 5;
        *(undefined4 *)(iVar8 + 0x28) = 4;
        iVar8 = *(int *)&menuPcs->field_0x850 + iVar6 + -0x178;
        *(int *)(iVar8 + 0x24) = iVar7 + 6;
        *(undefined4 *)(iVar8 + 0x28) = 4;
        iVar8 = iVar6 + -0x1b8;
        iVar6 = iVar6 + -0x200;
        iVar8 = *(int *)&menuPcs->field_0x850 + iVar8;
        *(int *)(iVar8 + 0x24) = iVar7 + 7;
        iVar7 = iVar7 + 8;
        *(undefined4 *)(iVar8 + 0x28) = 4;
        uVar9 = uVar9 - 1;
      } while (uVar9 != 0);
      uVar5 = uVar5 & 7;
      if (uVar5 == 0) goto LAB_801751e8;
    }
    do {
      iVar8 = iVar6 + 8;
      iVar6 = iVar6 + -0x40;
      iVar8 = *(int *)&menuPcs->field_0x850 + iVar8;
      *(int *)(iVar8 + 0x24) = iVar7;
      iVar7 = iVar7 + 1;
      *(undefined4 *)(iVar8 + 0x28) = 4;
      uVar5 = uVar5 - 1;
    } while (uVar5 != 0);
  }
LAB_801751e8:
  *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x22) = 0;
  return;
}

