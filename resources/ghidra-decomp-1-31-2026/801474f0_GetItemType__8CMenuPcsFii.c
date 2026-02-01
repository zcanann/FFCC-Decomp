// Function: GetItemType__8CMenuPcsFii
// Entry: 801474f0
// Size: 204 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

undefined4 GetItemType__8CMenuPcsFii(CMenuPcs *menuPcs,int itemId,int param_3)

{
  if (param_3 == 0) {
    itemId = (int)*(short *)(Game.game.m_scriptFoodBase[0] + itemId * 2 + 0xb6);
  }
  if (itemId < 1) {
    return 0;
  }
  if (itemId < 0x9f) {
    return 1;
  }
  if (itemId < 0x100) {
    return 2;
  }
  if (itemId < 0x125) {
    return 3;
  }
  if (itemId == 0x125) {
    return 4;
  }
  if (itemId < 0x12a) {
    return 5;
  }
  if (itemId >= 0x17d) {
    if (itemId < 0x17d) {
      return 6;
    }
    if (0x188 < itemId) {
      if (400 < itemId) {
        return 9;
      }
      return 8;
    }
    return 7;
  }
  return 6;
}

