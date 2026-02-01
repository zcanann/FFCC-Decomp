// Function: GetMcWinMessBuff__8CMenuPcsFi
// Entry: 8017b268
// Size: 400 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

undefined ** GetMcWinMessBuff__8CMenuPcsFi(CMenuPcs *menuPcs,int param_2)

{
  if (param_2 != 0) {
    if (param_2 != 1) {
      if (Game.game.m_gameWork.m_languageId == '\x03') {
        return (undefined **)&DAT_802161bc;
      }
      if (Game.game.m_gameWork.m_languageId < 3) {
        if ((Game.game.m_gameWork.m_languageId != '\x01') &&
           (Game.game.m_gameWork.m_languageId != '\0')) {
          return (undefined **)&DAT_80216140;
        }
      }
      else {
        if (Game.game.m_gameWork.m_languageId == '\x05') {
          return (undefined **)&DAT_802162b4;
        }
        if (Game.game.m_gameWork.m_languageId < 5) {
          return (undefined **)&DAT_80216238;
        }
      }
      return (undefined **)&DAT_802160c4;
    }
    if (Game.game.m_gameWork.m_languageId == '\x03') {
      return &PTR_DAT_802163a8;
    }
    if (Game.game.m_gameWork.m_languageId < 3) {
      if ((Game.game.m_gameWork.m_languageId != '\x01') &&
         (Game.game.m_gameWork.m_languageId != '\0')) {
        return &PTR_DAT_8021636c;
      }
    }
    else {
      if (Game.game.m_gameWork.m_languageId == '\x05') {
        return &PTR_DAT_80216420;
      }
      if (Game.game.m_gameWork.m_languageId < 5) {
        return &PTR_DAT_802163e4;
      }
    }
    return &PTR_DAT_80216330;
  }
  if (Game.game.m_gameWork.m_languageId == '\x03') {
    return &PTR_DAT_80215e00;
  }
  if (Game.game.m_gameWork.m_languageId < 3) {
    if ((Game.game.m_gameWork.m_languageId != '\x01') && (Game.game.m_gameWork.m_languageId != '\0')
       ) {
      return &PTR_DAT_80215d14;
    }
  }
  else {
    if (Game.game.m_gameWork.m_languageId == '\x05') {
      return &PTR_DAT_80215fd8;
    }
    if (Game.game.m_gameWork.m_languageId < 5) {
      return &PTR_DAT_80215eec;
    }
  }
  return &PTR_DAT_80215c28;
}

