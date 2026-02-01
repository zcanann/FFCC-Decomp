// Function: calc__8CMenuPcsFv
// Entry: 800966e8
// Size: 280 bytes

void calc__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  CMenuPcs *pCVar5;
  
  iVar1 = *(int *)&menuPcs->field_0x740;
  if (iVar1 == 1) {
    CalcDiaryMenu__8CMenuPcsFv();
  }
  else if (iVar1 < 1) {
    if (-1 < iVar1) {
      iVar1 = 0;
      pCVar5 = menuPcs;
      do {
        Calc__5CMenuFv(*(CMenu **)&pCVar5->field_0x13c);
        iVar1 = iVar1 + 1;
        pCVar5 = (CMenuPcs *)&pCVar5->field_0x4;
      } while (iVar1 < 4);
      iVar1 = 0;
      pCVar5 = menuPcs;
      do {
        Calc__5CMenuFv(*(CMenu **)&pCVar5->field_0x10c);
        iVar1 = iVar1 + 1;
        pCVar5 = (CMenuPcs *)&pCVar5->field_0x4;
      } while (iVar1 < 0xc);
      iVar2 = *(int *)&menuPcs->field_0x68;
      iVar1 = *(int *)&menuPcs->field_0x6c + -1;
      if ((iVar1 <= iVar2) &&
         (iVar3 = *(int *)&menuPcs->field_0x6c + 1, iVar1 = iVar2, iVar3 < iVar2)) {
        iVar1 = iVar3;
      }
      *(int *)&menuPcs->field_0x6c = iVar1;
      uVar4 = *(int *)&menuPcs->field_0x58 - 1;
      *(uint *)&menuPcs->field_0x58 = uVar4 & ~((int)uVar4 >> 0x1f);
      uVar4 = *(int *)&menuPcs->field_0x5c - 1;
      *(uint *)&menuPcs->field_0x5c = uVar4 & ~((int)uVar4 >> 0x1f);
      calcVillageMenu__8CMenuPcsFv(menuPcs);
    }
  }
  else if (iVar1 < 3) {
    calcBonus__8CMenuPcsFv(menuPcs);
  }
  return;
}

