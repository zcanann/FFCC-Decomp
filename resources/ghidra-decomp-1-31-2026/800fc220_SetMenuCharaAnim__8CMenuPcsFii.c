// Function: SetMenuCharaAnim__8CMenuPcsFii
// Entry: 800fc220
// Size: 20 bytes

void SetMenuCharaAnim__8CMenuPcsFii(CMenuPcs *menuPcs)

{
  int iVar1;
  
  iVar1 = *(int *)&menuPcs->field_0x828;
  *(undefined *)(iVar1 + 10) = 0;
  *(undefined *)(iVar1 + 0xe) = 0;
  return;
}

