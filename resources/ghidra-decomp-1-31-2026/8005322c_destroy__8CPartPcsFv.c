// Function: destroy__8CPartPcsFv
// Entry: 8005322c
// Size: 180 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void destroy__8CPartPcsFv(CPartPcs *partPcs)

{
  CStage *pCVar1;
  
  IsBigAlloc__7CUSBPcsFi(&USBPcs,0);
  Destroy__8CPartMngFv(&PartMng);
  pCVar1 = (partPcs->m_usbStreamData).m_stageAmem;
  if (pCVar1 != (CStage *)0x0) {
    DestroyStage__7CMemoryFPQ27CMemory6CStage(&Memory,pCVar1);
  }
  _AssertCache__13CAmemCacheSetFv((CAmemCacheSet *)CAMemCacheSet);
  Destroy__13CAmemCacheSetFv((CAmemCacheSet *)CAMemCacheSet);
  DestroyStage__7CMemoryFPQ27CMemory6CStage(&Memory,(partPcs->m_usbStreamData).m_stageDefault);
  if ((partPcs->m_usbStreamData).m_freePtr != (void *)0x0) {
    Free__7CMemoryFPv(&Memory);
  }
  pCVar1 = (partPcs->m_usbStreamData).m_stageExtra;
  if (pCVar1 != (CStage *)0x0) {
    DestroyStage__7CMemoryFPQ27CMemory6CStage(&Memory,pCVar1);
  }
  return;
}

