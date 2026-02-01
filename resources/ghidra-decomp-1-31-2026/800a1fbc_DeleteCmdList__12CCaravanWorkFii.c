// Function: DeleteCmdList__12CCaravanWorkFii
// Entry: 800a1fbc
// Size: 80 bytes

void DeleteCmdList__12CCaravanWorkFii(CCaravanWork *caravanWork,int param_2,int param_3)

{
  caravanWork->m_commandListInventorySlotRef[param_2] = 0xffff;
  if (param_3 != 0) {
    SetCmdLst__6JoyBusFiis(&Joybus,caravanWork->m_joybusCaravanId,param_2,-1);
  }
  return;
}

