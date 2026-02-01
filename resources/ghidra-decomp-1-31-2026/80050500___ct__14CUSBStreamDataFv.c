// Function: __ct__14CUSBStreamDataFv
// Entry: 80050500
// Size: 28 bytes

void __ct__14CUSBStreamDataFv(CUSBStreamData *usbStreamData)

{
  usbStreamData->m_data = (uint8_t *)0x0;
  usbStreamData->m_headerReady = 0;
  usbStreamData->m_dataReady = 0;
  usbStreamData->m_sizeBytes = 0;
  usbStreamData->m_packetCode = 0;
  return;
}

