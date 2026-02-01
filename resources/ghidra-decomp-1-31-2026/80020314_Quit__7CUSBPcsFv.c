// Function: Quit__7CUSBPcsFv
// Entry: 80020314
// Size: 92 bytes

void Quit__7CUSBPcsFv(CUSBPcs *usbPcs)

{
  if (usbPcs->m_bigStage != (CStage *)0x0) {
    DestroyStage__7CMemoryFPQ27CMemory6CStage(&Memory,usbPcs->m_bigStage);
  }
  DestroyStage__7CMemoryFPQ27CMemory6CStage(&Memory,usbPcs->m_smallStage);
  Disconnect__4CUSBFv(&USB);
  return;
}

