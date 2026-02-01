// Function: ClearEvtWork__12CCaravanWorkFv
// Entry: 800a2994
// Size: 72 bytes

void ClearEvtWork__12CCaravanWorkFv(CCaravanWork *caravanWork)

{
  memset(caravanWork->m_evtWorkArr,0,0x100);
  memset(caravanWork->m_evtWordArr,0,0x200);
  return;
}

