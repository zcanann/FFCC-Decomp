// Function: GetWinMess__8CMenuPcsFi
// Entry: 8017b220
// Size: 72 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

int GetWinMess__8CMenuPcsFi(CMenuPcs *menuPcs,int param_2)

{
  if (((Game.game.m_gameWork.m_languageId != '\x01') && (Game.game.m_gameWork.m_languageId != '\0'))
     && (Game.game.m_gameWork.m_languageId < 6)) {
    return param_2 * 0x14 + -0x7fde9ba4;
  }
  return param_2 * 0x14 + -0x7fde9ba4;
}

