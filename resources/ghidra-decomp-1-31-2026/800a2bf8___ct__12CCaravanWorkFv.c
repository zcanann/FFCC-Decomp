// Function: __ct__12CCaravanWorkFv
// Entry: 800a2bf8
// Size: 176 bytes

CCaravanWork * __ct__12CCaravanWorkFv(CCaravanWork *caravanWork)

{
  (caravanWork->gObjWork).vtable = &PTR_PTR_s_CGObjWork_8020faa8;
  (caravanWork->gObjWork).m_objType = -1;
  (caravanWork->gObjWork).m_saveSlot = 0xff;
  (caravanWork->gObjWork).m_partyIndex = 0xff;
  (caravanWork->gObjWork).m_isLoadingFlag = 0xff;
  (caravanWork->gObjWork).m_miscFlags = 0xff;
  (caravanWork->gObjWork).m_ownerObj = (void *)0x0;
  (caravanWork->gObjWork).vtable = &PTR_PTR_s_CCaravanWork_8020fa98;
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
  return caravanWork;
}

