// Function: __dt__14CUSBStreamDataFv
// Entry: 8005049c
// Size: 100 bytes

CUSBStreamData * __dt__14CUSBStreamDataFv(CUSBStreamData *usbStreamData,short param_2)

{
  if (usbStreamData != (CUSBStreamData *)0x0) {
    if (usbStreamData->m_data != (uint8_t *)0x0) {
      __dla__FPv(usbStreamData->m_data);
      usbStreamData->m_data = (uint8_t *)0x0;
    }
    if (0 < param_2) {
      __dl__FPv(usbStreamData);
    }
  }
  return usbStreamData;
}

