// Function: ArtiCtrl__8CMenuPcsFv
// Entry: 801607d4
// Size: 84 bytes

int ArtiCtrl__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  int iVar1;
  
  *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x32) =
       *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x30);
  iVar1 = ArtiCtrlCur__8CMenuPcsFv(menuPcs);
  if (iVar1 != 0) {
    ArtiInit1__8CMenuPcsFv(menuPcs);
  }
  return iVar1;
}

