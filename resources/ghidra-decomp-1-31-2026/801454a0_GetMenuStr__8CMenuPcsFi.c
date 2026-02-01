// Function: GetMenuStr__8CMenuPcsFi
// Entry: 801454a0
// Size: 156 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

undefined * GetMenuStr__8CMenuPcsFi(CMenuPcs *menuPcs,int param_2)

{
  if (Game.game.m_gameWork.m_languageId == '\x03') {
    return (&PTR_DAT_802143a0)[param_2];
  }
  if (Game.game.m_gameWork.m_languageId < 3) {
    if ((Game.game.m_gameWork.m_languageId != '\x01') && (Game.game.m_gameWork.m_languageId != '\0')
       ) {
      return (&PTR_DAT_802142c0)[param_2];
    }
  }
  else {
    if (Game.game.m_gameWork.m_languageId == '\x05') {
      return (&PTR_DAT_80214560)[param_2];
    }
    if (Game.game.m_gameWork.m_languageId < 5) {
      return (&PTR_DAT_80214480)[param_2];
    }
  }
  return (&PTR_DAT_802141e0)[param_2];
}

