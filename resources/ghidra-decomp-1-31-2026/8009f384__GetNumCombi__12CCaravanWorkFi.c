// Function: ?GetNumCombi__12CCaravanWorkFi
// Entry: 8009f384
// Size: 212 bytes

void _GetNumCombi__12CCaravanWorkFi(CCaravanWork *caravanWork,int param_2,int param_3)

{
  uint16_t uVar1;
  uint16_t uVar2;
  
  uVar2 = 0;
  if ((short)caravanWork->m_currentCmdListIndex == param_2) {
    uVar2 = GetNextCmdListIdx__12CCaravanWorkFii(caravanWork,param_2,1);
  }
  uVar1 = caravanWork->m_commandListInventorySlotRef[param_2];
  if (caravanWork->m_inventoryItems[(short)uVar1] != 0xffff) {
    caravanWork->m_inventoryItems[(short)uVar1] = 0xffff;
    caravanWork->m_inventoryItemCount = caravanWork->m_inventoryItemCount + -1;
    if (param_3 != 0) {
      DelItem__6JoyBusFiUc(&Joybus,caravanWork->m_joybusCaravanId,(char)uVar1);
    }
  }
  caravanWork->m_commandListInventorySlotRef[param_2] = 0xffff;
  if (param_3 != 0) {
    SetCmdLst__6JoyBusFiis(&Joybus,caravanWork->m_joybusCaravanId,param_2,-1);
  }
  if ((short)caravanWork->m_currentCmdListIndex == param_2) {
    caravanWork->m_currentCmdListIndex = uVar2;
  }
  return;
}

