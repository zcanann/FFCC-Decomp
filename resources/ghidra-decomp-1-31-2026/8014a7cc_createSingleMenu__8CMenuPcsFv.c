// Function: createSingleMenu__8CMenuPcsFv
// Entry: 8014a7cc
// Size: 372 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void createSingleMenu__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  int *piVar1;
  char *pcVar2;
  int iVar3;
  undefined auStack_88 [128];
  
  *(undefined2 *)&menuPcs->field_0x866 = 0;
  DAT_8032eebc = 0;
  if (Game.game.m_gameWork.m_menuStageMode == '\0') {
    if (menuPcs->field_0x859 != '\0') {
      *(undefined4 *)&menuPcs->field_0xf0 = 0;
      piVar1 = *(int **)&menuPcs->field_0x108;
      if (piVar1 != (int *)0x0) {
        iVar3 = piVar1[1];
        piVar1[1] = iVar3 + -1;
        if ((iVar3 + -1 == 0) && (piVar1 != (int *)0x0)) {
          (**(code **)(*piVar1 + 8))(piVar1,1);
        }
        *(undefined4 *)&menuPcs->field_0x108 = 0;
      }
      menuPcs->field_0x859 = 0;
      menuPcs->field_0x85a = 0;
    }
  }
  else {
    if (menuPcs->field_0x859 == '\0') {
      *(undefined4 *)&menuPcs->field_0xf0 = CharaPcs._212_4_;
      menuPcs->field_0x859 = 1;
    }
    pcVar2 = GetLangString__5CGameFv(&Game.game);
    sprintf(auStack_88,s_dvd__smenu_subfont_fnt_801de8f8,pcVar2);
    loadFont__8CMenuPcsFiPcii(menuPcs,1,auStack_88,4,0xffffffff);
    menuPcs->field_0x85a = 0;
    DAT_8032eec4 = 0xffffffff;
    DAT_8032eeb8 = 0;
    if (Game.game.m_gameWork.m_menuStageMode != '\0') {
      loadTexture__8CMenuPcsFPPciiPQ28CMenuPcs4CTmpiii
                (menuPcs,&PTR_s_solo2_80214a8c,4,1,&DAT_80214ab0,0x20,0xd,1);
      *(undefined4 *)&menuPcs->field_0x814 = 0;
      *(undefined4 *)&menuPcs->field_0x850 = 0;
      *(undefined4 *)&menuPcs->field_0x82c = 0;
      *(undefined4 *)&menuPcs->field_0x848 = 0;
      menuPcs->m_shopMenuPtr = (CShopMenu *)0x0;
    }
  }
  return;
}

