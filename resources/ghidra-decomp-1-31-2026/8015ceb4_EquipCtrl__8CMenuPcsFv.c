// Function: EquipCtrl__8CMenuPcsFv
// Entry: 8015ceb4
// Size: 596 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void EquipCtrl__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  short sVar1;
  uint32_t uVar2;
  float fVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  
  iVar4 = 0;
  *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x32) =
       *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x30);
  iVar5 = *(int *)&menuPcs->field_0x82c;
  sVar1 = *(short *)(iVar5 + 0x30);
  if ((sVar1 == 0) || ((sVar1 != 0 && (*(short *)(iVar5 + 0x12) == 1)))) {
    iVar4 = EquipCtrlCur__8CMenuPcsFv(menuPcs);
  }
  else if ((sVar1 == 1) && (*(short *)(iVar5 + 0x12) == 0)) {
    iVar4 = EquipOpen0__8CMenuPcsFv(menuPcs);
    if (iVar4 != 0) {
      iVar4 = 0;
      *(short *)(*(int *)&menuPcs->field_0x82c + 0x12) =
           *(short *)(*(int *)&menuPcs->field_0x82c + 0x12) + 1;
    }
  }
  else if ((sVar1 == 1) &&
          ((*(short *)(iVar5 + 0x12) == 2 && (iVar4 = EquipClose0__8CMenuPcsFv(menuPcs), iVar4 != 0)
           ))) {
    *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x12) = 0;
    *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x30) = 0;
    *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x22) = 0;
    CmdInit1__8CMenuPcsFv(menuPcs);
    iVar4 = 0;
  }
  fVar3 = FLOAT_80332ee0;
  uVar2 = Game.game.m_scriptFoodBase[0];
  if (iVar4 != 0) {
    iVar4 = *(int *)&menuPcs->field_0x850 + 8;
    for (iVar5 = 0; iVar5 < **(short **)&menuPcs->field_0x850; iVar5 = iVar5 + 1) {
      *(float *)(iVar4 + 0x10) = fVar3;
      *(float *)(iVar4 + 0x14) = fVar3;
      iVar4 = iVar4 + 0x40;
    }
    uVar6 = (uint)*(short *)(uVar2 + 0xbaa);
    iVar5 = 0;
    iVar4 = (uVar6 - 1) * 0x40;
    if (-1 < (int)(uVar6 - 1)) {
      uVar8 = uVar6 >> 3;
      if (uVar8 != 0) {
        do {
          iVar7 = *(int *)&menuPcs->field_0x850 + iVar4 + 8;
          *(int *)(iVar7 + 0x24) = iVar5;
          *(undefined4 *)(iVar7 + 0x28) = 3;
          iVar7 = *(int *)&menuPcs->field_0x850 + iVar4 + -0x38;
          *(int *)(iVar7 + 0x24) = iVar5 + 1;
          *(undefined4 *)(iVar7 + 0x28) = 3;
          iVar7 = *(int *)&menuPcs->field_0x850 + iVar4 + -0x78;
          *(int *)(iVar7 + 0x24) = iVar5 + 2;
          *(undefined4 *)(iVar7 + 0x28) = 3;
          iVar7 = *(int *)&menuPcs->field_0x850 + iVar4 + -0xb8;
          *(int *)(iVar7 + 0x24) = iVar5 + 3;
          *(undefined4 *)(iVar7 + 0x28) = 3;
          iVar7 = *(int *)&menuPcs->field_0x850 + iVar4 + -0xf8;
          *(int *)(iVar7 + 0x24) = iVar5 + 4;
          *(undefined4 *)(iVar7 + 0x28) = 3;
          iVar7 = *(int *)&menuPcs->field_0x850 + iVar4 + -0x138;
          *(int *)(iVar7 + 0x24) = iVar5 + 5;
          *(undefined4 *)(iVar7 + 0x28) = 3;
          iVar7 = *(int *)&menuPcs->field_0x850 + iVar4 + -0x178;
          *(int *)(iVar7 + 0x24) = iVar5 + 6;
          *(undefined4 *)(iVar7 + 0x28) = 3;
          iVar7 = iVar4 + -0x1b8;
          iVar4 = iVar4 + -0x200;
          iVar7 = *(int *)&menuPcs->field_0x850 + iVar7;
          *(int *)(iVar7 + 0x24) = iVar5 + 7;
          iVar5 = iVar5 + 8;
          *(undefined4 *)(iVar7 + 0x28) = 3;
          uVar8 = uVar8 - 1;
        } while (uVar8 != 0);
        uVar6 = uVar6 & 7;
        if (uVar6 == 0) {
          return;
        }
      }
      do {
        iVar7 = iVar4 + 8;
        iVar4 = iVar4 + -0x40;
        iVar7 = *(int *)&menuPcs->field_0x850 + iVar7;
        *(int *)(iVar7 + 0x24) = iVar5;
        iVar5 = iVar5 + 1;
        *(undefined4 *)(iVar7 + 0x28) = 3;
        uVar6 = uVar6 - 1;
      } while (uVar6 != 0);
    }
  }
  return;
}

