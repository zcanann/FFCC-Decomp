// Function: calcBonus__8CMenuPcsFv
// Entry: 8013d2a0
// Size: 368 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void calcBonus__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  int iVar1;
  int iVar2;
  
  **(float **)&menuPcs->field_0x82c =
       (float)((double)**(float **)&menuPcs->field_0x82c - DOUBLE_80331fc0);
  if (*(short *)(*(int *)&menuPcs->field_0x84c + 6) != 0) {
    *(short *)(*(int *)&menuPcs->field_0x82c + 0x1c) =
         *(short *)(*(int *)&menuPcs->field_0x82c + 0x1c) + 1;
    *(undefined2 *)(*(int *)&menuPcs->field_0x84c + 6) = 0;
    *(undefined *)(*(int *)&menuPcs->field_0x82c + 0xb) = 0;
    *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x10) = 0;
    *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x22) = 0;
  }
  switch(*(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x1c)) {
  case 0:
    CalcResultOpenAnim__8CMenuPcsFv(menuPcs);
    break;
  case 1:
    CalcResultCountAnim__8CMenuPcsFv(menuPcs);
    break;
  case 2:
    CalcResultCloseAnim__8CMenuPcsFv(menuPcs);
    break;
  case 3:
    CalcSelectOpenAnim__8CMenuPcsFv(menuPcs);
    break;
  case 4:
    CalcSelectWait__8CMenuPcsFv(menuPcs);
    break;
  case 5:
    CalcSelectCloseAnim__8CMenuPcsFv(menuPcs);
    if (*(short *)(*(int *)&menuPcs->field_0x84c + 6) != 0) {
      CallWorldParam__8CMenuPcsFiii(menuPcs,8,0,0);
    }
    break;
  case 6:
    iVar2 = 0;
    iVar1 = -0x7fde1140;
    do {
      if (*(CCaravanWork **)(iVar1 + 0xc5c0) != (CCaravanWork *)0x0) {
        SafeDeleteTempItem__12CCaravanWorkFv(*(CCaravanWork **)(iVar1 + 0xc5c0));
        SortBeforeReturnWorldMap__12CCaravanWorkFv(*(CCaravanWork **)(iVar1 + 0xc5c0));
      }
      iVar2 = iVar2 + 1;
      iVar1 = iVar1 + 4;
    } while (iVar2 < 4);
    changeMode__8CMenuPcsFQ28CMenuPcs8MENUMODE(menuPcs,0);
  }
  return;
}

