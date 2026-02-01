// Function: CreateBuffer__14CUSBStreamDataFv
// Entry: 80050488
// Size: 20 bytes

void CreateBuffer__14CUSBStreamDataFv(CUSBStreamData *usbStreamData)

{
  usbStreamData->m_data = (uint8_t *)File.m_readBuffer;
  return;
}

