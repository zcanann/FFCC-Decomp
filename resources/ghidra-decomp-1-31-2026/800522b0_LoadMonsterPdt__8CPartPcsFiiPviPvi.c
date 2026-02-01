// Function: LoadMonsterPdt__8CPartPcsFiiPviPvi
// Entry: 800522b0
// Size: 328 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

int LoadMonsterPdt__8CPartPcsFiiPviPvi
              (CPartPcs *partPcs,undefined4 param_2,int param_3,undefined4 param_4,
              undefined4 param_5,undefined4 param_6,undefined4 param_7)

{
  int pdtSlotIndex;
  int iVar1;
  undefined auStack_118 [260];
  
  if (param_3 == 0) {
    sprintf(auStack_118,s_dvd_tina_mon_m_03d_801d7fc0,param_2);
  }
  else {
    sprintf(auStack_118,s_dvd_tina_mon_m_03d__c_801d7fd4,param_2,param_3 + 0x61);
  }
  PartMng.m_partAMemBase = 0;
  PartMng.m_partAMemCursor = 0;
  PartMng.m_partLoadCacheParam = 0;
  PartMng.m_partChunkIndex = 0;
  PartMng.m_asyncHandleCount = 0;
  PartMng.m_partLoadMode = 0;
  pdtSlotIndex = pppGetFreeDataMng__8CPartMngFv(&PartMng);
  if (pdtSlotIndex == -1) {
    pdtSlotIndex = -1;
  }
  else {
    iVar1 = pppLoadPtx__8CPartMngFPCciiPvi(&PartMng,auStack_118,pdtSlotIndex,1,param_6,param_7);
    if (iVar1 == 0) {
      pppReleasePdt__8CPartMngFi(&PartMng,pdtSlotIndex);
      pdtSlotIndex = -1;
    }
    else {
      iVar1 = pppLoadPdt__8CPartMngFPCciiPvi(&PartMng,auStack_118,pdtSlotIndex,1,param_4,param_5);
      if (iVar1 == 0) {
        pppReleasePdt__8CPartMngFi(&PartMng,pdtSlotIndex);
        pdtSlotIndex = -1;
      }
      else {
        PartPcs.m_usbStreamData.m_printFreeOnNext = '\x01';
      }
    }
  }
  return pdtSlotIndex;
}

