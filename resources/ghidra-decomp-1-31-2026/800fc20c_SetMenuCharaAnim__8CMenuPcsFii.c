// Function: SetMenuCharaAnim__8CMenuPcsFii
// Entry: 800fc20c
// Size: 20 bytes

void SetMenuCharaAnim__8CMenuPcsFii(CMenuPcs *menuPcs,int param_2,undefined4 param_3)

{
  *(undefined4 *)(*(int *)&menuPcs->field_0x844 + param_2 * 0x14 + 4) = param_3;
  return;
}

