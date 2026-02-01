// Function: ChgPlayModeFromScript__8CMenuPcsFb
// Entry: 80093e78
// Size: 76 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void ChgPlayModeFromScript__8CMenuPcsFb(CMenuPcs *menuPcs,uint8_t param_2)

{
  if ((*(int *)&menuPcs->field_0x740 != 2) && (*(int *)&menuPcs->field_0x740 != 1)) {
    destroySingleMenu__8CMenuPcsFv(menuPcs);
  }
  Game.game.m_gameWork.m_menuStageMode = param_2;
  return;
}

