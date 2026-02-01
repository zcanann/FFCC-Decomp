// Function: destroy__8CMenuPcsFv
// Entry: 800970e0
// Size: 352 bytes

void destroy__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  int *piVar1;
  int iVar2;
  CMenuPcs *pCVar3;
  int iVar4;
  
  changeMode__8CMenuPcsFQ28CMenuPcs8MENUMODE(menuPcs,0xffffffff);
  iVar4 = 0;
  pCVar3 = menuPcs;
  do {
    piVar1 = *(int **)&pCVar3->field_0x18c;
    if (piVar1 != (int *)0x0) {
      iVar2 = piVar1[1];
      piVar1[1] = iVar2 + -1;
      if ((iVar2 + -1 == 0) && (piVar1 != (int *)0x0)) {
        (**(code **)(*piVar1 + 8))(piVar1,1);
      }
      *(undefined4 *)&pCVar3->field_0x18c = 0;
    }
    iVar4 = iVar4 + 1;
    pCVar3 = (CMenuPcs *)&pCVar3->field_0x4;
  } while (iVar4 < 0x16);
  iVar4 = 0;
  pCVar3 = menuPcs;
  do {
    piVar1 = *(int **)&pCVar3->field_0x14c;
    if (piVar1 != (int *)0x0) {
      iVar2 = piVar1[1];
      piVar1[1] = iVar2 + -1;
      if ((iVar2 + -1 == 0) && (piVar1 != (int *)0x0)) {
        (**(code **)(*piVar1 + 8))(piVar1,1);
      }
      *(undefined4 *)&pCVar3->field_0x14c = 0;
    }
    iVar4 = iVar4 + 1;
    pCVar3 = (CMenuPcs *)&pCVar3->field_0x4;
  } while (iVar4 < 2);
  piVar1 = *(int **)&menuPcs->field_0xf8;
  if (piVar1 != (int *)0x0) {
    iVar4 = piVar1[1];
    piVar1[1] = iVar4 + -1;
    if ((iVar4 + -1 == 0) && (piVar1 != (int *)0x0)) {
      (**(code **)(*piVar1 + 8))(piVar1,1);
    }
    *(undefined4 *)&menuPcs->field_0xf8 = 0;
  }
  DestroyStage__7CMemoryFPQ27CMemory6CStage(&Memory,*(undefined4 *)&menuPcs->field_0xec);
  if (menuPcs->field_0x859 != '\0') {
    *(undefined4 *)&menuPcs->field_0xf0 = 0;
    menuPcs->field_0x859 = 0;
  }
  return;
}

