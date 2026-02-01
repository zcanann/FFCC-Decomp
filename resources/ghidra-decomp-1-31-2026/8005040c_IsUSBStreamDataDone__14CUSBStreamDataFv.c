// Function: IsUSBStreamDataDone__14CUSBStreamDataFv
// Entry: 8005040c
// Size: 40 bytes

undefined4 IsUSBStreamDataDone__14CUSBStreamDataFv(CUSBStreamData *usbStreamData)

{
  if ((usbStreamData->m_dataReady != 0) && (usbStreamData->m_headerReady != 0)) {
    return 1;
  }
  return 0;
}

