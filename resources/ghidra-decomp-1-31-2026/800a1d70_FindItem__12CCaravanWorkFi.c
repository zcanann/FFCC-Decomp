// Function: FindItem__12CCaravanWorkFi
// Entry: 800a1d70
// Size: 284 bytes

int FindItem__12CCaravanWorkFi(CCaravanWork *caravanWork,int param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = 0;
  iVar2 = 8;
  while( true ) {
    if (((short)caravanWork->m_inventoryItems[0] != -1) &&
       ((short)caravanWork->m_inventoryItems[0] == param_2)) {
      return iVar1;
    }
    if (((short)caravanWork->m_inventoryItems[1] != -1) &&
       ((short)caravanWork->m_inventoryItems[1] == param_2)) {
      return iVar1 + 1;
    }
    if (((short)caravanWork->m_inventoryItems[2] != -1) &&
       ((short)caravanWork->m_inventoryItems[2] == param_2)) {
      return iVar1 + 2;
    }
    if (((short)caravanWork->m_inventoryItems[3] != -1) &&
       ((short)caravanWork->m_inventoryItems[3] == param_2)) {
      return iVar1 + 3;
    }
    if (((short)caravanWork->m_inventoryItems[4] != -1) &&
       ((short)caravanWork->m_inventoryItems[4] == param_2)) {
      return iVar1 + 4;
    }
    if (((short)caravanWork->m_inventoryItems[5] != -1) &&
       ((short)caravanWork->m_inventoryItems[5] == param_2)) {
      return iVar1 + 5;
    }
    if (((short)caravanWork->m_inventoryItems[6] != -1) &&
       ((short)caravanWork->m_inventoryItems[6] == param_2)) {
      return iVar1 + 6;
    }
    if (((short)caravanWork->m_inventoryItems[7] != -1) &&
       ((short)caravanWork->m_inventoryItems[7] == param_2)) break;
    caravanWork = (CCaravanWork *)&(caravanWork->gObjWork).m_baseDataIndex;
    iVar1 = iVar1 + 8;
    iVar2 = iVar2 + -1;
    if (iVar2 == 0) {
      return -1;
    }
  }
  return iVar1 + 7;
}

