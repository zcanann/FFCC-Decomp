// Function: SetSingWinInfo__8CMenuPcsFiiii
// Entry: 80146490
// Size: 60 bytes

void SetSingWinInfo__8CMenuPcsFiiii
               (CMenuPcs *menuPcs,undefined2 param_2,undefined2 param_3,undefined2 param_4,
               undefined2 param_5)

{
  **(undefined2 **)&menuPcs->field_0x848 = param_2;
  *(undefined2 *)(*(int *)&menuPcs->field_0x848 + 2) = param_3;
  *(undefined2 *)(*(int *)&menuPcs->field_0x848 + 4) = param_4;
  *(undefined2 *)(*(int *)&menuPcs->field_0x848 + 6) = param_5;
  *(undefined2 *)(*(int *)&menuPcs->field_0x848 + 8) = 0;
  *(undefined2 *)(*(int *)&menuPcs->field_0x848 + 10) = 3;
  return;
}

