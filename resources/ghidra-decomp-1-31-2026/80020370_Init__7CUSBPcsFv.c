// Function: Init__7CUSBPcsFv
// Entry: 80020370
// Size: 116 bytes

void Init__7CUSBPcsFv(CUSBPcs *usbPcs)

{
  CStage *pCVar1;
  
  pCVar1 = CreateStage__7CMemoryFUlPci(&Memory,0x2000,s_CUSBPcs_8032f810,0);
  usbPcs->m_smallStage = pCVar1;
  usbPcs->m_bigStage = (CStage *)0x0;
  strcpy(usbPcs->m_rootPath,s_plot_kmitsuru__801d6d14);
  usbPcs->m_unk0x104 = 0;
  usbPcs->m_unk0x108 = 0;
  Connect__4CUSBFv(&USB);
  return;
}

