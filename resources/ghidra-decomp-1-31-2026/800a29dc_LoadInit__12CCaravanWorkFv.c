// Function: LoadInit__12CCaravanWorkFv
// Entry: 800a29dc
// Size: 136 bytes

void LoadInit__12CCaravanWorkFv(CCaravanWork *caravanWork)

{
  caravanWork->m_shopState = 0;
  caravanWork->unk_0x3a8 = 0;
  caravanWork->unk_0x3ac = 0;
  (caravanWork->gObjWork).m_objType = 0;
  caravanWork->m_joybusCaravanId = -1;
  sprintf(caravanWork->unk_0x3ca_0x3dd,&DAT_801d9ff0);
  caravanWork->m_letterMeta[0] = 0xffff;
  caravanWork->m_letterMeta[1] = 0xffff;
  caravanWork->m_letterMeta[2] = 0xffff;
  caravanWork->m_letterMeta[3] = 0xffff;
  caravanWork->m_letterMeta[4] = 0xffff;
  caravanWork->m_letterMeta[5] = 0xffff;
  caravanWork->m_letterMeta[6] = 0xffff;
  caravanWork->m_letterMeta[7] = 0xffff;
  clearCaravanWork__12CCaravanWorkFv(caravanWork);
  return;
}

