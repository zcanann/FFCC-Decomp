// Function: SetUSBStreamDataDone__14CUSBStreamDataFv
// Entry: 800503fc
// Size: 16 bytes

void SetUSBStreamDataDone__14CUSBStreamDataFv(CUSBStreamData *usbStreamData)

{
  usbStreamData->m_headerReady = 0;
  usbStreamData->m_dataReady = 0;
  return;
}

