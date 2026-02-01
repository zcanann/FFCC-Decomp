// Function: changeMode__8CMenuPcsFQ28CMenuPcs8MENUMODE
// Entry: 80096800
// Size: 668 bytes

void changeMode__8CMenuPcsFQ28CMenuPcs8MENUMODE(CMenuPcs *menuPcs,int param_2)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  CMenuPcs *pCVar4;
  
  if (*(int *)&menuPcs->field_0x740 != param_2) {
    _WaitDrawDone__8CGraphicFPci(&Graphic,s_p_menu_cpp_801d9d80,0x1b0);
    iVar1 = *(int *)&menuPcs->field_0x740;
    if (iVar1 == 1) {
      destroyWorld__8CMenuPcsFv(menuPcs);
    }
    else if (iVar1 < 1) {
      if ((iVar1 != -1) && (-2 < iVar1)) {
        piVar2 = *(int **)&menuPcs->field_0xfc;
        if (piVar2 != (int *)0x0) {
          iVar1 = piVar2[1];
          piVar2[1] = iVar1 + -1;
          if ((iVar1 + -1 == 0) && (piVar2 != (int *)0x0)) {
            (**(code **)(*piVar2 + 8))(piVar2,1);
          }
          *(undefined4 *)&menuPcs->field_0xfc = 0;
        }
        iVar1 = 0;
        pCVar4 = menuPcs;
        do {
          piVar2 = *(int **)&pCVar4->field_0x1e4;
          if (piVar2 != (int *)0x0) {
            iVar3 = piVar2[1];
            piVar2[1] = iVar3 + -1;
            if ((iVar3 + -1 == 0) && (piVar2 != (int *)0x0)) {
              (**(code **)(*piVar2 + 8))(piVar2,1);
            }
            *(undefined4 *)&pCVar4->field_0x1e4 = 0;
          }
          iVar1 = iVar1 + 1;
          pCVar4 = (CMenuPcs *)&pCVar4->field_0x4;
        } while (iVar1 < 10);
        iVar1 = 0;
        pCVar4 = menuPcs;
        do {
          piVar2 = *(int **)&pCVar4->field_0x154;
          if (piVar2 != (int *)0x0) {
            iVar3 = piVar2[1];
            piVar2[1] = iVar3 + -1;
            if ((iVar3 + -1 == 0) && (piVar2 != (int *)0x0)) {
              (**(code **)(*piVar2 + 8))(piVar2,1);
            }
            *(undefined4 *)&pCVar4->field_0x154 = 0;
          }
          iVar1 = iVar1 + 1;
          pCVar4 = (CMenuPcs *)&pCVar4->field_0x4;
        } while (iVar1 < 2);
        iVar1 = 0;
        pCVar4 = menuPcs;
        do {
          piVar2 = *(int **)&pCVar4->field_0x13c;
          if (piVar2 != (int *)0x0) {
            iVar3 = piVar2[1];
            piVar2[1] = iVar3 + -1;
            if ((iVar3 + -1 == 0) && (piVar2 != (int *)0x0)) {
              (**(code **)(*piVar2 + 8))(piVar2,1);
            }
            *(undefined4 *)&pCVar4->field_0x13c = 0;
          }
          iVar1 = iVar1 + 1;
          pCVar4 = (CMenuPcs *)&pCVar4->field_0x4;
        } while (iVar1 < 4);
        iVar1 = 0;
        pCVar4 = menuPcs;
        do {
          piVar2 = *(int **)&pCVar4->field_0x10c;
          if (piVar2 != (int *)0x0) {
            iVar3 = piVar2[1];
            piVar2[1] = iVar3 + -1;
            if ((iVar3 + -1 == 0) && (piVar2 != (int *)0x0)) {
              (**(code **)(*piVar2 + 8))(piVar2,1);
            }
            *(undefined4 *)&pCVar4->field_0x10c = 0;
          }
          iVar1 = iVar1 + 1;
          pCVar4 = (CMenuPcs *)&pCVar4->field_0x4;
        } while (iVar1 < 0xc);
        destroySingleMenu__8CMenuPcsFv(menuPcs);
        destroyVillageMenu__8CMenuPcsFv(menuPcs);
      }
    }
    else if (iVar1 < 3) {
      destroyBonus__8CMenuPcsFv(menuPcs);
    }
    *(int *)&menuPcs->field_0x740 = param_2;
    iVar1 = *(int *)&menuPcs->field_0x740;
    if (iVar1 == 1) {
      createWorld__8CMenuPcsFv(menuPcs);
    }
    else if (iVar1 < 1) {
      if ((iVar1 != -1) && (-2 < iVar1)) {
        createBattle__8CMenuPcsFv(menuPcs);
        createSingleMenu__8CMenuPcsFv(menuPcs);
      }
    }
    else if (iVar1 < 3) {
      createBonus__8CMenuPcsFv(menuPcs);
    }
  }
  return;
}

