// Function: GetJobStr__8CMenuPcsFi
// Entry: 801455d8
// Size: 156 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

undefined * GetJobStr__8CMenuPcsFi(CMenuPcs *menuPcs,int param_2)

{
  if (Game.game.m_gameWork.m_languageId == '\x03') {
    return (&PTR_s_Fabbri_80214180)[param_2];
  }
  if (Game.game.m_gameWork.m_languageId < 3) {
    if ((Game.game.m_gameWork.m_languageId != '\x01') && (Game.game.m_gameWork.m_languageId != '\0')
       ) {
      return (&PTR_s_Schmied_80214160)[param_2];
    }
  }
  else {
    if (Game.game.m_gameWork.m_languageId == '\x05') {
      return (&PTR_s_Herrero_802141c0)[param_2];
    }
    if (Game.game.m_gameWork.m_languageId < 5) {
      return (&PTR_s_Forgeron_802141a0)[param_2];
    }
  }
  return (&PTR_s_Blacksmith_80214140)[param_2];
}

