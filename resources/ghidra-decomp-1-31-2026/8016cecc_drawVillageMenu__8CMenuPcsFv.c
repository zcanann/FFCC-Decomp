// Function: drawVillageMenu__8CMenuPcsFv
// Entry: 8016cecc
// Size: 140 bytes

void drawVillageMenu__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  int iVar1;
  
  if (*(short *)&menuPcs->field_0x86c != 0) {
    iVar1 = *(int *)&menuPcs->field_0x830;
    CmakeVillageDraw__8CMenuPcsFv(menuPcs);
    if (*(short *)(iVar1 + 0x2e) != 0) {
      if (*(short *)(iVar1 + 0x10) < 2) {
        *(short *)(iVar1 + 0x10) = *(short *)(iVar1 + 0x10) + 1;
      }
      else {
        menuPcs->field_0x16 = 0;
        CallWorldParam__8CMenuPcsFiii(menuPcs,10,0,0);
      }
      *(undefined2 *)(iVar1 + 0x22) = 0;
    }
  }
  return;
}

