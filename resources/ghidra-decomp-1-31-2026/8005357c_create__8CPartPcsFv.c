// Function: create__8CPartPcsFv
// Entry: 8005357c
// Size: 328 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void create__8CPartPcsFv(CPartPcs *partPcs)

{
  CStage *pCVar1;
  
  (partPcs->m_usbStreamData).m_freePtr = (void *)0x0;
  (partPcs->m_usbStreamData).m_stageExtra = (CStage *)0x0;
  (partPcs->m_usbStreamData).m_blockOnFrame = '\0';
  (partPcs->m_usbStreamData).m_miruraEventActive = '\0';
  (partPcs->m_usbStreamData).m_disableShokiDraw = '\0';
  if (Game.game.m_currentSceneId == 7) {
    pCVar1 = CreateStage__7CMemoryFUlPci(&Memory,0x180000,s_CPartPcs_dat_801d810c,0);
    (partPcs->m_usbStreamData).m_stageLoad = pCVar1;
    (partPcs->m_usbStreamData).m_stageDefault = pCVar1;
    (partPcs->m_usbStreamData).m_stageAmem = (CStage *)0x0;
  }
  else {
    pCVar1 = CreateStage__7CMemoryFUlPci(&Memory,0x180000,s_CPartPcs_dat_801d810c,0);
    (partPcs->m_usbStreamData).m_stageLoad = pCVar1;
    (partPcs->m_usbStreamData).m_stageDefault = pCVar1;
    pCVar1 = CreateStage__7CMemoryFUlPci(&Memory,0x400000,s_CPartPcs_amem_801d811c,2);
    (partPcs->m_usbStreamData).m_stageAmem = pCVar1;
  }
  Init__13CAmemCacheSetFPcPQ27CMemory6CStagePQ27CMemory6CStageiPFUl_UcUlPFUl_UcUlPFUl_UcUl
            ((CAmemCacheSet *)CAMemCacheSet,s_CPartPcs_801d7f54,PartPcs.m_usbStreamData.m_stageLoad,
             PartPcs.m_usbStreamData.m_stageAmem,0x400,pppNotAllocAmemCacheRmem__FUl,0,
             pppAmemDeletePmng__FUl,0,pppAmemRefCntError__FUl,0);
  memset(&PartMng,0,0x23fd8);
  Create__8CPartMngFv(&PartMng);
  return;
}

