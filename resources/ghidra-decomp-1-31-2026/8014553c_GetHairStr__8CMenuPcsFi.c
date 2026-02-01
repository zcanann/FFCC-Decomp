// Function: GetHairStr__8CMenuPcsFi
// Entry: 8014553c
// Size: 156 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

undefined * GetHairStr__8CMenuPcsFi(CMenuPcs *menuPcs,int param_2)

{
  if (Game.game.m_gameWork.m_languageId == '\x03') {
    return (&PTR_s_Ciuffo_ribelle_80214740)[param_2];
  }
  if (Game.game.m_gameWork.m_languageId < 3) {
    if ((Game.game.m_gameWork.m_languageId != '\x01') && (Game.game.m_gameWork.m_languageId != '\0')
       ) {
      return (&PTR_s_Spitzschopf_802146c0)[param_2];
    }
  }
  else {
    if (Game.game.m_gameWork.m_languageId == '\x05') {
      return (&PTR_s_Remolino_80214840)[param_2];
    }
    if (Game.game.m_gameWork.m_languageId < 5) {
      return (&PTR_DAT_802147c0)[param_2];
    }
  }
  return (&PTR_s_Cowlick_80214640)[param_2];
}

