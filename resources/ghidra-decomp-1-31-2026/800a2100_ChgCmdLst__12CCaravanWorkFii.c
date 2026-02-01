// Function: ChgCmdLst__12CCaravanWorkFii
// Entry: 800a2100
// Size: 100 bytes

void ChgCmdLst__12CCaravanWorkFii(CCaravanWork *caravanWork,int commandListIndex,int param_3)

{
  uint16_t uVar1;
  
  caravanWork->m_commandListInventorySlotRef[commandListIndex] = (uint16_t)param_3;
  if ((param_3 < 0) && ((short)caravanWork->m_currentCmdListIndex == commandListIndex)) {
    uVar1 = GetNextCmdListIdx__12CCaravanWorkFii
                      (caravanWork,(int)(short)caravanWork->m_currentCmdListIndex,0xffffffff);
    caravanWork->m_currentCmdListIndex = uVar1;
  }
  CheckAndResetCurrentWeaponIdx__12CCaravanWorkFi(caravanWork);
  return;
}

