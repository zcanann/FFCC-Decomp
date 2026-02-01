// Function: AddGil__12CCaravanWorkFi
// Entry: 800a1b5c
// Size: 84 bytes

int AddGil__12CCaravanWorkFi(CCaravanWork *caravanWork,int gilToAdd)

{
  int iVar1;
  
  caravanWork->m_gil = caravanWork->m_gil + gilToAdd;
  iVar1 = caravanWork->m_gil;
  if (iVar1 < 100000000) {
    if (iVar1 < 0) {
      gilToAdd = gilToAdd - iVar1;
      caravanWork->m_gil = 0;
    }
  }
  else {
    caravanWork->m_gil = iVar1 - (iVar1 + -99999999);
    gilToAdd = gilToAdd - (iVar1 + -99999999);
  }
  return gilToAdd;
}

