// Function: FGPutGil__12CCaravanWorkFi
// Entry: 800a2164
// Size: 140 bytes

void FGPutGil__12CCaravanWorkFi(CCaravanWork *caravanWork,int gilToRemove)

{
  int iVar1;
  
  iVar1 = putGil__10CGPartyObjFi((caravanWork->gObjWork).m_ownerObj);
  if (iVar1 != 0) {
    caravanWork->m_gil = caravanWork->m_gil - gilToRemove;
    if (caravanWork->m_gil < 100000000) {
      if (caravanWork->m_gil < 0) {
        caravanWork->m_gil = 0;
      }
    }
    else {
      caravanWork->m_gil = 99999999;
    }
  }
  return;
}

