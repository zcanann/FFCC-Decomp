// Function: DeleteItemIdx__12CCaravanWorkFii
// Entry: 800a1d0c
// Size: 100 bytes

void DeleteItemIdx__12CCaravanWorkFii(CCaravanWork *caravanWork,int param_2,int param_3)

{
  if (caravanWork->m_inventoryItems[param_2] != 0xffff) {
    caravanWork->m_inventoryItems[param_2] = 0xffff;
    caravanWork->m_inventoryItemCount = caravanWork->m_inventoryItemCount + -1;
    if (param_3 != 0) {
      DelItem__6JoyBusFiUc(&Joybus,caravanWork->m_joybusCaravanId,(char)param_2);
    }
  }
  return;
}

