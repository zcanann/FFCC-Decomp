// Function: GetTribeStr__8CMenuPcsFi
// Entry: 80145674
// Size: 156 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

undefined * GetTribeStr__8CMenuPcsFi(CMenuPcs *menuPcs,int param_2)

{
  if (Game.game.m_gameWork.m_languageId == '\x03') {
    return (&PTR_s_Clavat_80214110)[param_2];
  }
  if (Game.game.m_gameWork.m_languageId < 3) {
    if ((Game.game.m_gameWork.m_languageId != '\x01') && (Game.game.m_gameWork.m_languageId != '\0')
       ) {
      return (&PTR_s_Clavat_80214100)[param_2];
    }
  }
  else {
    if (Game.game.m_gameWork.m_languageId == '\x05') {
      return (&PTR_s_Clavate_80214130)[param_2];
    }
    if (Game.game.m_gameWork.m_languageId < 5) {
      return (&PTR_s_Clavat_80214120)[param_2];
    }
  }
  return (&PTR_s_Clavat_802140f0)[param_2];
}

