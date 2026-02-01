// Function: MoneyCtrl__8CMenuPcsFv
// Entry: 8015f588
// Size: 256 bytes

void MoneyCtrl__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  short sVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = 0;
  *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x32) =
       *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x30);
  iVar3 = *(int *)&menuPcs->field_0x82c;
  sVar1 = *(short *)(iVar3 + 0x30);
  if ((sVar1 == 0) || ((sVar1 != 0 && (*(short *)(iVar3 + 0x12) == 1)))) {
    iVar2 = MoneyCtrlCur__8CMenuPcsFv(menuPcs);
  }
  else if ((sVar1 == 1) && (*(short *)(iVar3 + 0x12) == 0)) {
    if (*(short *)(*(int *)&menuPcs->field_0x848 + 10) == 1) {
      iVar2 = 0;
      *(undefined2 *)(iVar3 + 0x12) = 1;
    }
  }
  else if (((sVar1 == 1) && (*(short *)(iVar3 + 0x12) == 2)) &&
          (*(short *)(*(int *)&menuPcs->field_0x848 + 10) == 3)) {
    iVar2 = 0;
    *(undefined2 *)(iVar3 + 0x12) = 0;
    *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x30) = 0;
    *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x22) = 0;
  }
  if (iVar2 != 0) {
    iVar2 = *(int *)&menuPcs->field_0x850;
    *(float *)(iVar2 + 0x18) = FLOAT_80332f70;
    *(undefined4 *)(iVar2 + 0x2c) = 0;
    *(undefined4 *)(iVar2 + 0x30) = 10;
    *(undefined4 *)(iVar2 + 0x28) = 0;
  }
  return;
}

