// Function: FGPutItem__12CCaravanWorkFii
// Entry: 800a21f0
// Size: 160 bytes

void FGPutItem__12CCaravanWorkFii(CCaravanWork *caravanWork,int param_2,int param_3)

{
  int iVar1;
  
  iVar1 = putItem__10CGPartyObjFi
                    ((caravanWork->gObjWork).m_ownerObj,
                     (int)(short)caravanWork->m_inventoryItems[param_2]);
  if ((iVar1 != 0) && (caravanWork->m_inventoryItems[param_2] != 0xffff)) {
    caravanWork->m_inventoryItems[param_2] = 0xffff;
    caravanWork->m_inventoryItemCount = caravanWork->m_inventoryItemCount + -1;
    if (param_3 != 0) {
      DelItem__6JoyBusFiUc(&Joybus,caravanWork->m_joybusCaravanId,(char)param_2);
    }
  }
  return;
}

