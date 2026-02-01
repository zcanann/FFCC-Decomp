// Function: SetCurrentWeaponIdx__12CCaravanWorkFi
// Entry: 8009f1d8
// Size: 36 bytes

void SetCurrentWeaponIdx__12CCaravanWorkFi(CCaravanWork *caravanWork,int weaponIdx)

{
  caravanWork->m_weaponIdx = (int16_t)weaponIdx;
  CheckAndResetCurrentWeaponIdx__12CCaravanWorkFi(caravanWork);
  return;
}

