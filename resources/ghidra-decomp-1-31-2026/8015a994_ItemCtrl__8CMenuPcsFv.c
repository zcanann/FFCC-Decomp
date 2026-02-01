// Function: ItemCtrl__8CMenuPcsFv
// Entry: 8015a994
// Size: 260 bytes

int ItemCtrl__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  short sVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = 0;
  *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x32) =
       *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x30);
  iVar2 = *(int *)&menuPcs->field_0x82c;
  sVar1 = *(short *)(iVar2 + 0x30);
  if ((sVar1 == 0) || ((sVar1 != 0 && (*(short *)(iVar2 + 0x12) == 1)))) {
    iVar3 = ItemCtrlCur__8CMenuPcsFv(menuPcs);
  }
  else if ((sVar1 == 1) && (*(short *)(iVar2 + 0x12) == 0)) {
    if (*(short *)(*(int *)&menuPcs->field_0x848 + 10) == 1) {
      iVar3 = 0;
      *(undefined2 *)(iVar2 + 0x12) = 1;
    }
  }
  else if (((sVar1 == 1) && (*(short *)(iVar2 + 0x12) == 2)) &&
          (*(short *)(*(int *)&menuPcs->field_0x848 + 10) == 3)) {
    iVar3 = 0;
    *(undefined2 *)(iVar2 + 0x12) = 0;
    *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x30) = 0;
    *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x22) = 0;
  }
  if (iVar3 != 0) {
    SingLifeInit__8CMenuPcsFi(menuPcs,0xffffffff);
    ItemInit1__8CMenuPcsFv(menuPcs);
  }
  return iVar3;
}

