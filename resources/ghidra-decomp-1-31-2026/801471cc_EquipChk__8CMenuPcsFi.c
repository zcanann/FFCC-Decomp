// Function: EquipChk__8CMenuPcsFi
// Entry: 801471cc
// Size: 400 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

undefined4 EquipChk__8CMenuPcsFi(CMenuPcs *menuPcs,int param_2)

{
  if (2 < *(short *)(Game.game.m_scriptFoodBase[0] + 0xbaa)) {
    if ((-1 < *(short *)(Game.game.m_scriptFoodBase[0] + 0x208)) &&
       (*(short *)(Game.game.m_scriptFoodBase[0] + 0x208) == param_2)) {
      return 1;
    }
    if (3 < *(short *)(Game.game.m_scriptFoodBase[0] + 0xbaa)) {
      if ((-1 < *(short *)(Game.game.m_scriptFoodBase[0] + 0x20a)) &&
         (*(short *)(Game.game.m_scriptFoodBase[0] + 0x20a) == param_2)) {
        return 1;
      }
      if (4 < *(short *)(Game.game.m_scriptFoodBase[0] + 0xbaa)) {
        if ((-1 < *(short *)(Game.game.m_scriptFoodBase[0] + 0x20c)) &&
           (*(short *)(Game.game.m_scriptFoodBase[0] + 0x20c) == param_2)) {
          return 1;
        }
        if (5 < *(short *)(Game.game.m_scriptFoodBase[0] + 0xbaa)) {
          if ((-1 < *(short *)(Game.game.m_scriptFoodBase[0] + 0x20e)) &&
             (*(short *)(Game.game.m_scriptFoodBase[0] + 0x20e) == param_2)) {
            return 1;
          }
          if (6 < *(short *)(Game.game.m_scriptFoodBase[0] + 0xbaa)) {
            if ((-1 < *(short *)(Game.game.m_scriptFoodBase[0] + 0x210)) &&
               (*(short *)(Game.game.m_scriptFoodBase[0] + 0x210) == param_2)) {
              return 1;
            }
            if ((7 < *(short *)(Game.game.m_scriptFoodBase[0] + 0xbaa)) &&
               ((-1 < *(short *)(Game.game.m_scriptFoodBase[0] + 0x212) &&
                (*(short *)(Game.game.m_scriptFoodBase[0] + 0x212) == param_2)))) {
              return 1;
            }
          }
        }
      }
    }
  }
  if ((-1 < *(short *)(Game.game.m_scriptFoodBase[0] + 0xac)) &&
     (*(short *)(Game.game.m_scriptFoodBase[0] + 0xac) == param_2)) {
    return 1;
  }
  if ((-1 < *(short *)(Game.game.m_scriptFoodBase[0] + 0xae)) &&
     (*(short *)(Game.game.m_scriptFoodBase[0] + 0xae) == param_2)) {
    return 1;
  }
  if ((-1 < *(short *)(Game.game.m_scriptFoodBase[0] + 0xb0)) &&
     (*(short *)(Game.game.m_scriptFoodBase[0] + 0xb0) == param_2)) {
    return 1;
  }
  if ((-1 < *(short *)(Game.game.m_scriptFoodBase[0] + 0xb2)) &&
     (*(short *)(Game.game.m_scriptFoodBase[0] + 0xb2) == param_2)) {
    return 1;
  }
  return 0;
}

