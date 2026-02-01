// Function: DeleteItem__12CCaravanWorkFii
// Entry: 800a1c7c
// Size: 144 bytes

undefined4 DeleteItem__12CCaravanWorkFii(CCaravanWork *caravanWork,int itemIndex,int param_3)

{
  CCaravanWork *pCVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = 0;
  iVar3 = 0x40;
  pCVar1 = caravanWork;
  while (((short)pCVar1->m_inventoryItems[0] == -1 ||
         ((short)pCVar1->m_inventoryItems[0] != itemIndex))) {
    pCVar1 = (CCaravanWork *)((int)&(pCVar1->gObjWork).vtable + 2);
    iVar2 = iVar2 + 1;
    iVar3 = iVar3 + -1;
    if (iVar3 == 0) {
      return 0;
    }
  }
  caravanWork->m_inventoryItems[iVar2] = 0xffff;
  caravanWork->m_inventoryItemCount = caravanWork->m_inventoryItemCount + -1;
  if (param_3 != 0) {
    DelItem__6JoyBusFiUc(&Joybus,caravanWork->m_joybusCaravanId,(char)iVar2);
  }
  return 1;
}

