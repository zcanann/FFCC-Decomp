// Function: GetAttrStr__8CMenuPcsFi
// Entry: 80145404
// Size: 156 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

undefined * GetAttrStr__8CMenuPcsFi(CMenuPcs *menuPcs,int param_2)

{
  if (Game.game.m_gameWork.m_languageId == '\x03') {
    return (&PTR_DAT_80214960)[param_2];
  }
  if (Game.game.m_gameWork.m_languageId < 3) {
    if ((Game.game.m_gameWork.m_languageId != '\x01') && (Game.game.m_gameWork.m_languageId != '\0')
       ) {
      return (&PTR_DAT_80214910)[param_2];
    }
  }
  else {
    if (Game.game.m_gameWork.m_languageId == '\x05') {
      return (&PTR_DAT_80214a00)[param_2];
    }
    if (Game.game.m_gameWork.m_languageId < 5) {
      return (&PTR_DAT_802149b0)[param_2];
    }
  }
  return (&PTR_DAT_802148c0)[param_2];
}

