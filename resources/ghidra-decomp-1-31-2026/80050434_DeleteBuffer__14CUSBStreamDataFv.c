// Function: DeleteBuffer__14CUSBStreamDataFv
// Entry: 80050434
// Size: 84 bytes

void DeleteBuffer__14CUSBStreamDataFv(CUSBStreamData *usbStreamData)

{
  if (usbStreamData->m_data != (uint8_t *)0x0) {
    __dla__FPv(usbStreamData->m_data);
    usbStreamData->m_data = (uint8_t *)0x0;
  }
  usbStreamData->m_headerReady = 0;
  usbStreamData->m_dataReady = 0;
  usbStreamData->m_sizeBytes = 0;
  usbStreamData->m_packetCode = 0;
  return;
}

