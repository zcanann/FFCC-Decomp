// Function: CheckAndResetCurrentWeaponIdx__12CCaravanWorkFi
// Entry: 8009f178
// Size: 96 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void CheckAndResetCurrentWeaponIdx__12CCaravanWorkFi(CCaravanWork *caravanWork)

{
  int iVar1;
  
  iVar1 = _DelCmdListAndItem__12CCaravanWorkFii();
  if ((iVar1 < 1) || (*(short *)(Game.game.unkCFlatData0[2] + iVar1 * 0x48) != 1)) {
    caravanWork->m_currentCmdListIndex = 0;
    caravanWork->m_weaponIdx = 0;
  }
  return;
}

