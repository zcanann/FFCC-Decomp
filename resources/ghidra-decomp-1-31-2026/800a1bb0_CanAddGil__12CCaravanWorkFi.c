// Function: CanAddGil__12CCaravanWorkFi
// Entry: 800a1bb0
// Size: 56 bytes

uint CanAddGil__12CCaravanWorkFi(CCaravanWork *caravanWork,int gilAmount)

{
  int iVar1;
  int iVar2;
  
  iVar2 = 0;
  iVar1 = caravanWork->m_gil + gilAmount;
  if ((-1 < iVar1) && (iVar1 < 100000000)) {
    iVar2 = 1;
  }
  return (uint)-iVar2 >> 0x1f;
}

