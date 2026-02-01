// Function: SetEvtWord__12CCaravanWorkFis
// Entry: 800b9244
// Size: 16 bytes

void SetEvtWord__12CCaravanWorkFis(CCaravanWork *caravanWork,int evtWordIndex,short evtWord)

{
  caravanWork->m_evtWordArr[evtWordIndex] = evtWord;
  return;
}

