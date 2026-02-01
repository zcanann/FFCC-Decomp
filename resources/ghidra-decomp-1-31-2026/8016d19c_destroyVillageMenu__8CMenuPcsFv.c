// Function: destroyVillageMenu__8CMenuPcsFv
// Entry: 8016d19c
// Size: 192 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void destroyVillageMenu__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  int *piVar1;
  int iVar2;
  
  if (*(short *)&menuPcs->field_0x86c != 0) {
    if (Game.game.m_gameWork.m_menuStageMode == '\0') {
      piVar1 = *(int **)&menuPcs->field_0x108;
      if (piVar1 != (int *)0x0) {
        iVar2 = piVar1[1];
        piVar1[1] = iVar2 + -1;
        if ((iVar2 + -1 == 0) && (piVar1 != (int *)0x0)) {
          (**(code **)(*piVar1 + 8))(piVar1,1);
        }
        *(undefined4 *)&menuPcs->field_0x108 = 0;
      }
    }
    freeTexture__8CMenuPcsFiiii(menuPcs,8,1,0x60,9);
    if (*(int *)&menuPcs->field_0x830 != 0) {
      __dl__FPv();
      *(undefined4 *)&menuPcs->field_0x830 = 0;
    }
    *(undefined2 *)&menuPcs->field_0x86c = 0;
  }
  return;
}

