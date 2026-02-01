// Function: AddItem__12CCaravanWorkFiPi
// Entry: 800a1f08
// Size: 180 bytes

undefined4 AddItem__12CCaravanWorkFiPi(CCaravanWork *caravanWork,uint16_t param_2,uint *param_3)

{
  CCaravanWork *pCVar1;
  uint uVar2;
  int iVar3;
  
  if ((ushort)caravanWork->m_inventoryItemCount < 0x40) {
    uVar2 = 0;
    iVar3 = 0x40;
    pCVar1 = caravanWork;
    do {
      if (pCVar1->m_inventoryItems[0] == 0xffff) {
        caravanWork->m_inventoryItems[uVar2] = param_2;
        caravanWork->m_inventoryItemCount = caravanWork->m_inventoryItemCount + 1;
        SetItem__6JoyBusFiUcs(&Joybus,caravanWork->m_joybusCaravanId,uVar2 & 0xff,param_2);
        if (param_3 != (uint *)0x0) {
          *param_3 = uVar2;
        }
        return 1;
      }
      pCVar1 = (CCaravanWork *)((int)&(pCVar1->gObjWork).vtable + 2);
      uVar2 = uVar2 + 1;
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
  }
  return 0;
}

