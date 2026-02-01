// Function: IsBigAlloc__7CUSBPcsFi
// Entry: 8002027c
// Size: 132 bytes

void IsBigAlloc__7CUSBPcsFi(CUSBPcs *usbPcs,int param_2)

{
  CStage *pCVar1;
  
  if ((param_2 == 0) || (usbPcs->m_bigStage != (CStage *)0x0)) {
    if ((param_2 == 0) && (usbPcs->m_bigStage != (CStage *)0x0)) {
      DestroyStage__7CMemoryFPQ27CMemory6CStage(&Memory,usbPcs->m_bigStage);
      usbPcs->m_bigStage = (CStage *)0x0;
    }
  }
  else {
    pCVar1 = CreateStage__7CMemoryFUlPci(&Memory,0x100000,s_CUSBPcs_8032f810,0);
    usbPcs->m_bigStage = pCVar1;
  }
  return;
}

