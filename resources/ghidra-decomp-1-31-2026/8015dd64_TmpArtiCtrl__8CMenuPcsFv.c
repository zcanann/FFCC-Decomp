// Function: TmpArtiCtrl__8CMenuPcsFv
// Entry: 8015dd64
// Size: 744 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void TmpArtiCtrl__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  bool bVar1;
  uint32_t uVar2;
  float fVar3;
  ushort uVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  
  bVar1 = false;
  *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x32) =
       *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x30);
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
  if (uVar4 == 0) {
    bVar1 = false;
  }
  else if ((uVar4 & 0x20) == 0) {
    if ((uVar4 & 0x40) == 0) {
      if ((uVar4 & 0x100) == 0) {
        if ((uVar4 & 0x200) != 0) {
          *(undefined *)(*(int *)&menuPcs->field_0x82c + 0xd) = 1;
          PlaySe__6CSoundFiiii(&Sound,3,0x40,0x7f,0);
          bVar1 = true;
          goto LAB_8015ded0;
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
LAB_8015ded0:
  fVar3 = FLOAT_80332f30;
  uVar2 = Game.game.m_scriptFoodBase[0];
  if (bVar1) {
    iVar6 = *(int *)&menuPcs->field_0x850 + 8;
    for (iVar7 = 0; iVar7 < **(short **)&menuPcs->field_0x850; iVar7 = iVar7 + 1) {
      *(float *)(iVar6 + 0x10) = fVar3;
      *(float *)(iVar6 + 0x14) = fVar3;
      iVar6 = iVar6 + 0x40;
    }
    uVar5 = (uint)*(short *)(uVar2 + 0xbaa);
    iVar7 = 0;
    iVar6 = (uVar5 - 1) * 0x40;
    if (-1 < (int)(uVar5 - 1)) {
      uVar9 = uVar5 >> 3;
      if (uVar9 != 0) {
        do {
          iVar8 = *(int *)&menuPcs->field_0x850 + iVar6 + 8;
          *(int *)(iVar8 + 0x24) = iVar7;
          *(undefined4 *)(iVar8 + 0x28) = 3;
          iVar8 = *(int *)&menuPcs->field_0x850 + iVar6 + -0x38;
          *(int *)(iVar8 + 0x24) = iVar7 + 1;
          *(undefined4 *)(iVar8 + 0x28) = 3;
          iVar8 = *(int *)&menuPcs->field_0x850 + iVar6 + -0x78;
          *(int *)(iVar8 + 0x24) = iVar7 + 2;
          *(undefined4 *)(iVar8 + 0x28) = 3;
          iVar8 = *(int *)&menuPcs->field_0x850 + iVar6 + -0xb8;
          *(int *)(iVar8 + 0x24) = iVar7 + 3;
          *(undefined4 *)(iVar8 + 0x28) = 3;
          iVar8 = *(int *)&menuPcs->field_0x850 + iVar6 + -0xf8;
          *(int *)(iVar8 + 0x24) = iVar7 + 4;
          *(undefined4 *)(iVar8 + 0x28) = 3;
          iVar8 = *(int *)&menuPcs->field_0x850 + iVar6 + -0x138;
          *(int *)(iVar8 + 0x24) = iVar7 + 5;
          *(undefined4 *)(iVar8 + 0x28) = 3;
          iVar8 = *(int *)&menuPcs->field_0x850 + iVar6 + -0x178;
          *(int *)(iVar8 + 0x24) = iVar7 + 6;
          *(undefined4 *)(iVar8 + 0x28) = 3;
          iVar8 = iVar6 + -0x1b8;
          iVar6 = iVar6 + -0x200;
          iVar8 = *(int *)&menuPcs->field_0x850 + iVar8;
          *(int *)(iVar8 + 0x24) = iVar7 + 7;
          iVar7 = iVar7 + 8;
          *(undefined4 *)(iVar8 + 0x28) = 3;
          uVar9 = uVar9 - 1;
        } while (uVar9 != 0);
        uVar5 = uVar5 & 7;
        if (uVar5 == 0) {
          return;
        }
      }
      do {
        iVar8 = iVar6 + 8;
        iVar6 = iVar6 + -0x40;
        iVar8 = *(int *)&menuPcs->field_0x850 + iVar8;
        *(int *)(iVar8 + 0x24) = iVar7;
        iVar7 = iVar7 + 1;
        *(undefined4 *)(iVar8 + 0x28) = 3;
        uVar5 = uVar5 - 1;
      } while (uVar5 != 0);
    }
  }
  return;
}

