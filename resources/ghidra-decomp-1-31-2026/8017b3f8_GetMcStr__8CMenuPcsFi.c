// Function: GetMcStr__8CMenuPcsFi
// Entry: 8017b3f8
// Size: 156 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

undefined * GetMcStr__8CMenuPcsFi(CMenuPcs *menuPcs,int param_2)

{
  if (Game.game.m_gameWork.m_languageId == '\x03') {
    return (&PTR_s_I_dati_sono_danneggiati__80215bf8)[param_2];
  }
  if (Game.game.m_gameWork.m_languageId < 3) {
    if ((Game.game.m_gameWork.m_languageId != '\x01') && (Game.game.m_gameWork.m_languageId != '\0')
       ) {
      return (&PTR_s_Der_Spielstand_ist_fehlerhaft__80215be8)[param_2];
    }
  }
  else {
    if (Game.game.m_gameWork.m_languageId == '\x05') {
      return (&PTR_DAT_80215c18)[param_2];
    }
    if (Game.game.m_gameWork.m_languageId < 5) {
      return (&PTR_DAT_80215c08)[param_2];
    }
  }
  return (&PTR_s_The_data_is_corrupt__80215bd8)[param_2];
}

