// Function: createLoad__8CPartPcsFv
// Entry: 80053444
// Size: 312 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void createLoad__8CPartPcsFv(void)

{
  PartMng.m_partAMemBase = 0;
  PartMng.m_partAMemCursor = 0;
  PartMng.m_partLoadCacheParam = 0;
  PartMng.m_partChunkIndex = 0;
  PartMng.m_asyncHandleCount = 0;
  PartMng.m_partLoadMode = 0;
  pppLoadPtx__8CPartMngFPCciiPvi(&PartMng,s_dvd_tina_chobit_801d812c,1,1,0,0);
  pppLoadPmd__8CPartMngFPCc(&PartMng,s_dvd_tina_chobit_801d812c);
  pppLoadPan__8CPartMngFPCc(&PartMng,s_dvd_tina_chobit_801d812c);
  pppLoadPdt__8CPartMngFPCciiPvi(&PartMng,s_dvd_tina_chobit_0_801d813c,1,1,0,0);
  pppLoadPdt__8CPartMngFPCciiPvi(&PartMng,s_dvd_tina_chobit_1_801d8150,2,1,0,0);
  pppLoadPdt__8CPartMngFPCciiPvi(&PartMng,s_dvd_tina_chobit_2_801d8164,3,1,0,0);
  pppLoadPdt__8CPartMngFPCciiPvi(&PartMng,s_dvd_tina_chobit_3_801d8178,4,1,0,0);
  pppLoadPdt__8CPartMngFPCciiPvi(&PartMng,s_dvd_tina_chobit_4_801d818c,5,1,0,0);
  AmemSetLock__13CAmemCacheSetFv((CAmemCacheSet *)CAMemCacheSet);
  return;
}

