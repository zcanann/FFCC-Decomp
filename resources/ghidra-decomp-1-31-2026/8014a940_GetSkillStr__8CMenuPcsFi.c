// Function: GetSkillStr__8CMenuPcsFi
// Entry: 8014a940
// Size: 156 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

undefined * GetSkillStr__8CMenuPcsFi(CMenuPcs *menuPcs,int param_2)

{
  if (Game.game.m_gameWork.m_languageId == '\x03') {
    return (&PTR_s_Colpo_Fire_80214d50)[param_2];
  }
  if (Game.game.m_gameWork.m_languageId < 3) {
    if ((Game.game.m_gameWork.m_languageId != '\x01') && (Game.game.m_gameWork.m_languageId != '\0')
       ) {
      return (&PTR_s_Feuer_Hieb_80214d3c)[param_2];
    }
  }
  else {
    if (Game.game.m_gameWork.m_languageId == '\x05') {
      return (&PTR_s_Efecto_Fuego_80214d78)[param_2];
    }
    if (Game.game.m_gameWork.m_languageId < 5) {
      return (&PTR_s_Pyro_Frappe_80214d64)[param_2];
    }
  }
  return (&PTR_s_Flamestrike_80214d28)[param_2];
}

