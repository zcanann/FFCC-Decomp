// Function: FGUseItem__12CCaravanWorkFii
// Entry: 800a2290
// Size: 160 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void FGUseItem__12CCaravanWorkFii(CCaravanWork *caravanWork,int param_2,int param_3)

{
  int iVar1;
  
  iVar1 = useItem__10CGPartyObjFi
                    ((CGPartyObj *)(caravanWork->gObjWork).m_ownerObj,
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

