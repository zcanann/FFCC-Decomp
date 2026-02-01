// Function: onScriptChanging__8CMenuPcsFPc
// Entry: 80095d44
// Size: 300 bytes

void onScriptChanging__8CMenuPcsFPc(CMenuPcs *menuPcs,undefined4 param_2)

{
  int *piVar1;
  int iVar2;
  CMenuPcs *pCVar3;
  
  if (*(int *)&menuPcs->field_0x740 == 0) {
    iVar2 = 0;
    pCVar3 = menuPcs;
    do {
      ScriptChanging__5CMenuFPc(*(CMenuPcs **)&pCVar3->field_0x13c);
      iVar2 = iVar2 + 1;
      pCVar3 = (CMenuPcs *)&pCVar3->field_0x4;
    } while (iVar2 < 4);
    iVar2 = 0;
    pCVar3 = menuPcs;
    do {
      ScriptChanging__5CMenuFPc(*(CMenuPcs **)&pCVar3->field_0x10c);
      iVar2 = iVar2 + 1;
      pCVar3 = (CMenuPcs *)&pCVar3->field_0x4;
    } while (iVar2 < 0xc);
  }
  memset(&menuPcs->field_0x48,0,0x28);
  piVar1 = *(int **)&menuPcs->field_0x100;
  if (piVar1 != (int *)0x0) {
    iVar2 = piVar1[1];
    piVar1[1] = iVar2 + -1;
    if ((iVar2 + -1 == 0) && (piVar1 != (int *)0x0)) {
      (**(code **)(*piVar1 + 8))(piVar1,1);
    }
    *(undefined4 *)&menuPcs->field_0x100 = 0;
  }
  piVar1 = *(int **)&menuPcs->field_0x104;
  if (piVar1 != (int *)0x0) {
    iVar2 = piVar1[1];
    piVar1[1] = iVar2 + -1;
    if ((iVar2 + -1 == 0) && (piVar1 != (int *)0x0)) {
      (**(code **)(*piVar1 + 8))(piVar1,1);
    }
    *(undefined4 *)&menuPcs->field_0x104 = 0;
  }
  return;
}

