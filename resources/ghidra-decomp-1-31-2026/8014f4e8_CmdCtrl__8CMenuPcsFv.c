// Function: CmdCtrl__8CMenuPcsFv
// Entry: 8014f4e8
// Size: 1424 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void CmdCtrl__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  short sVar1;
  uint32_t uVar2;
  double dVar3;
  float fVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  short *psVar9;
  int iVar10;
  uint uVar11;
  
  CalcStatus__12CCaravanWorkFv(Game.game.m_scriptFoodBase[0]);
  uVar5 = 0;
  *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x32) =
       *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x30);
  uVar2 = Game.game.m_scriptFoodBase[0];
  iVar6 = *(int *)&menuPcs->field_0x82c;
  sVar1 = *(short *)(iVar6 + 0x30);
  if ((sVar1 == 0) || ((sVar1 != 0 && (*(short *)(iVar6 + 0x12) == 1)))) {
    uVar5 = CmdCtrlCur__8CMenuPcsFv(menuPcs);
  }
  else if ((sVar1 == 1) && (*(short *)(iVar6 + 0x12) == 0)) {
    uVar5 = CmdOpen0__8CMenuPcsFv(menuPcs);
    if (uVar5 != 0) {
      uVar5 = 0;
      *(short *)(*(int *)&menuPcs->field_0x82c + 0x12) =
           *(short *)(*(int *)&menuPcs->field_0x82c + 0x12) + 1;
    }
  }
  else if ((sVar1 == 1) && (*(short *)(iVar6 + 0x12) == 2)) {
    uVar5 = CmdClose0__8CMenuPcsFv(menuPcs);
    if (uVar5 != 0) {
      iVar6 = *(int *)&menuPcs->field_0x82c;
      if (*(char *)(iVar6 + 8) == '\0') {
        *(short *)(iVar6 + 0x12) = *(short *)(iVar6 + 0x12) + 1;
      }
      else {
        *(undefined2 *)(iVar6 + 0x12) = 0;
        *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x30) = 3;
        *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x22) = 0;
        *(undefined *)(*(int *)&menuPcs->field_0x82c + 8) = 0;
        CmdInit1__8CMenuPcsFv(menuPcs);
      }
      uVar5 = 0;
    }
  }
  else if ((sVar1 == 1) && (*(short *)(iVar6 + 0x12) == 3)) {
    uVar5 = UniteOpenAnim__8CMenuPcsFi(menuPcs,0xffffffff);
    if (uVar5 != 0) {
      *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x12) = 0;
      *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x30) = 0;
      *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x22) = 0;
      CmdInit1__8CMenuPcsFv(menuPcs);
      uVar5 = 0;
    }
  }
  else if ((sVar1 == 2) && (*(short *)(iVar6 + 0x12) == 0)) {
    uVar5 = CmdOpen1__8CMenuPcsFv(menuPcs);
    if (uVar5 != 0) {
      uVar5 = 0;
      *(short *)(*(int *)&menuPcs->field_0x82c + 0x12) =
           *(short *)(*(int *)&menuPcs->field_0x82c + 0x12) + 1;
    }
  }
  else if ((sVar1 == 2) && (*(short *)(iVar6 + 0x12) == 2)) {
    uVar5 = CmdClose1__8CMenuPcsFv(menuPcs);
    if (uVar5 != 0) {
      iVar6 = *(int *)&menuPcs->field_0x82c;
      if (*(char *)(iVar6 + 8) == '\0') {
        *(undefined2 *)(iVar6 + 0x30) = 0;
      }
      else {
        *(undefined2 *)(iVar6 + 0x14) = 0;
        *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x30) = 3;
      }
      uVar5 = 0;
      *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x12) = 0;
      *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x22) = 0;
    }
  }
  else if ((sVar1 == 3) && (*(short *)(iVar6 + 0x12) == 0)) {
    *(short *)(iVar6 + 0x22) = *(short *)(iVar6 + 0x22) + 1;
    iVar10 = (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x26);
    iVar7 = iVar10 + -1;
    iVar6 = iVar10 + -3;
    iVar8 = uVar2 + iVar7 * 2;
    if (2 < iVar7) {
      do {
        if (-1 < *(short *)(iVar8 + 0x214)) break;
        iVar8 = iVar8 + -2;
        iVar7 = iVar7 + -1;
        iVar6 = iVar6 + -1;
      } while (iVar6 != 0);
    }
    iVar10 = iVar10 + 1;
    iVar6 = *(short *)(uVar2 + 0xbaa) - iVar10;
    iVar8 = uVar2 + iVar10 * 2;
    if (iVar10 < *(short *)(uVar2 + 0xbaa)) {
      do {
        if (-1 < *(short *)(iVar8 + 0x214)) break;
        iVar8 = iVar8 + 2;
        iVar10 = iVar10 + 1;
        iVar6 = iVar6 + -1;
      } while (iVar6 != 0);
    }
    iVar8 = 0;
    for (iVar6 = 0; dVar3 = DOUBLE_80332a60, psVar9 = *(short **)&menuPcs->field_0x850,
        iVar6 < *psVar9; iVar6 = iVar6 + 1) {
      if (((iVar6 < iVar7) || (iVar10 < iVar6)) &&
         (*(float *)((int)psVar9 + iVar8 + 0x18) =
               (float)-(DOUBLE_80332a68 *
                        ((double)CONCAT44(0x43300000,
                                          (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x22) ^
                                          0x80000000) - DOUBLE_80332a80) - DOUBLE_80332a58),
         (double)*(float *)((int)psVar9 + iVar8 + 0x18) < dVar3)) {
        *(float *)((int)psVar9 + iVar8 + 0x18) = FLOAT_80332a88;
      }
      iVar8 = iVar8 + 0x40;
    }
    iVar6 = *(int *)&menuPcs->field_0x82c;
    uVar5 = (uint)(DOUBLE_80332a78 <=
                  (double)CONCAT44(0x43300000,(int)*(short *)(iVar6 + 0x22) ^ 0x80000000) -
                  DOUBLE_80332a80);
    if (uVar5 != 0) {
      *(short *)(iVar6 + *(short *)(iVar6 + 0x30) * 2 + 0x26) = (short)iVar7;
      uVar5 = 0;
      *(short *)(*(int *)&menuPcs->field_0x82c + 0x12) =
           *(short *)(*(int *)&menuPcs->field_0x82c + 0x12) + 1;
    }
  }
  else if (((sVar1 == 3) && (*(short *)(iVar6 + 0x12) == 2)) &&
          (uVar5 = CmdClose2__8CMenuPcsFv(menuPcs), uVar5 != 0)) {
    uVar5 = 0;
    *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x12) = 0;
    *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x30) = 0;
    *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x22) = 0;
    *(undefined *)(*(int *)&menuPcs->field_0x82c + 8) = 0;
  }
  fVar4 = FLOAT_80332a70;
  uVar2 = Game.game.m_scriptFoodBase[0];
  if (uVar5 == 0) {
    return;
  }
  iVar6 = *(int *)&menuPcs->field_0x850 + 8;
  for (iVar8 = 0; iVar8 < **(short **)&menuPcs->field_0x850; iVar8 = iVar8 + 1) {
    *(float *)(iVar6 + 0x10) = fVar4;
    *(float *)(iVar6 + 0x14) = fVar4;
    iVar6 = iVar6 + 0x40;
  }
  uVar5 = (uint)*(short *)(uVar2 + 0xbaa);
  iVar8 = 0;
  iVar6 = (uVar5 - 1) * 0x40;
  if (-1 < (int)(uVar5 - 1)) {
    uVar11 = uVar5 >> 3;
    if (uVar11 != 0) {
      do {
        iVar10 = *(int *)&menuPcs->field_0x850 + iVar6 + 8;
        *(int *)(iVar10 + 0x24) = iVar8;
        *(undefined4 *)(iVar10 + 0x28) = 3;
        iVar10 = *(int *)&menuPcs->field_0x850 + iVar6 + -0x38;
        *(int *)(iVar10 + 0x24) = iVar8 + 1;
        *(undefined4 *)(iVar10 + 0x28) = 3;
        iVar10 = *(int *)&menuPcs->field_0x850 + iVar6 + -0x78;
        *(int *)(iVar10 + 0x24) = iVar8 + 2;
        *(undefined4 *)(iVar10 + 0x28) = 3;
        iVar10 = *(int *)&menuPcs->field_0x850 + iVar6 + -0xb8;
        *(int *)(iVar10 + 0x24) = iVar8 + 3;
        *(undefined4 *)(iVar10 + 0x28) = 3;
        iVar10 = *(int *)&menuPcs->field_0x850 + iVar6 + -0xf8;
        *(int *)(iVar10 + 0x24) = iVar8 + 4;
        *(undefined4 *)(iVar10 + 0x28) = 3;
        iVar10 = *(int *)&menuPcs->field_0x850 + iVar6 + -0x138;
        *(int *)(iVar10 + 0x24) = iVar8 + 5;
        *(undefined4 *)(iVar10 + 0x28) = 3;
        iVar10 = *(int *)&menuPcs->field_0x850 + iVar6 + -0x178;
        *(int *)(iVar10 + 0x24) = iVar8 + 6;
        *(undefined4 *)(iVar10 + 0x28) = 3;
        iVar10 = iVar6 + -0x1b8;
        iVar6 = iVar6 + -0x200;
        iVar10 = *(int *)&menuPcs->field_0x850 + iVar10;
        *(int *)(iVar10 + 0x24) = iVar8 + 7;
        iVar8 = iVar8 + 8;
        *(undefined4 *)(iVar10 + 0x28) = 3;
        uVar11 = uVar11 - 1;
      } while (uVar11 != 0);
      uVar5 = uVar5 & 7;
      if (uVar5 == 0) goto LAB_8014fa50;
    }
    do {
      iVar10 = iVar6 + 8;
      iVar6 = iVar6 + -0x40;
      iVar10 = *(int *)&menuPcs->field_0x850 + iVar10;
      *(int *)(iVar10 + 0x24) = iVar8;
      iVar8 = iVar8 + 1;
      *(undefined4 *)(iVar10 + 0x28) = 3;
      uVar5 = uVar5 - 1;
    } while (uVar5 != 0);
  }
LAB_8014fa50:
  *(undefined *)(*(int *)&menuPcs->field_0x82c + 8) = 0;
  return;
}

