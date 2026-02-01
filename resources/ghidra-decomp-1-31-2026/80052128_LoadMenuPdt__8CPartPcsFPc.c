// Function: LoadMenuPdt__8CPartPcsFPc
// Entry: 80052128
// Size: 392 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

int LoadMenuPdt__8CPartPcsFPc(CPartPcs *CPartPcs,undefined4 param_2)

{
  char *pcVar1;
  int pdtSlotIndex;
  int iVar2;
  CStage *stage;
  undefined auStack_108 [256];
  
  pcVar1 = GetLangString__5CGameFv(&Game.game);
  sprintf(auStack_108,s_dvd__smenu__s_801d7fb0,pcVar1,param_2);
  stage = (CStage *)MenuPcs._236_4_;
  if (Game.game.m_gameWork.m_menuStageMode != '\0') {
    stage = (CStage *)MenuPcs._244_4_;
  }
  (CPartPcs->m_usbStreamData).m_stageLoad = stage;
  SetRStage__13CAmemCacheSetFPQ27CMemory6CStage((CAmemCacheSet *)CAMemCacheSet,stage);
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
    iVar2 = pppLoadPtx__8CPartMngFPCciiPvi(&PartMng,auStack_108,pdtSlotIndex,0,0,0);
    if (iVar2 == 0) {
      pppReleasePdt__8CPartMngFi(&PartMng,pdtSlotIndex);
      pdtSlotIndex = -1;
    }
    else {
      iVar2 = pppLoadPdt__8CPartMngFPCciiPvi(&PartMng,auStack_108,pdtSlotIndex,0,0,0);
      if (iVar2 == 0) {
        pppReleasePdt__8CPartMngFi(&PartMng,pdtSlotIndex);
        pdtSlotIndex = -1;
      }
      else {
        PartPcs.m_usbStreamData.m_printFreeOnNext = '\x01';
      }
    }
  }
  (CPartPcs->m_usbStreamData).m_stageLoad = (CPartPcs->m_usbStreamData).m_stageDefault;
  SetRStage__13CAmemCacheSetFPQ27CMemory6CStage
            ((CAmemCacheSet *)CAMemCacheSet,(CPartPcs->m_usbStreamData).m_stageDefault);
  return pdtSlotIndex;
}

