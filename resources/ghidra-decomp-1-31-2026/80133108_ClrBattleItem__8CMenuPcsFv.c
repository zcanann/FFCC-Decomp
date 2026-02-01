// Function: ClrBattleItem__8CMenuPcsFv
// Entry: 80133108
// Size: 104 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void ClrBattleItem__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  int iVar1;
  int iVar2;
  
  iVar2 = -0x7fde1140;
  iVar1 = 0;
  do {
    if (*(CCaravanWork **)(iVar2 + 0xc5c0) != (CCaravanWork *)0x0) {
      SafeDeleteTempItem__12CCaravanWorkFv(*(CCaravanWork **)(iVar2 + 0xc5c0));
      SortBeforeReturnWorldMap__12CCaravanWorkFv(*(CCaravanWork **)(iVar2 + 0xc5c0));
    }
    iVar1 = iVar1 + 1;
    iVar2 = iVar2 + 4;
  } while (iVar1 < 4);
  return;
}

