// Function: mccReadData__7CUSBPcsFv
// Entry: 80020180
// Size: 104 bytes

void mccReadData__7CUSBPcsFv(void)

{
  if (DAT_8032ec6c == '\0') {
    DAT_8032ec68 = 0;
    DAT_8032ec6c = '\x01';
  }
  DAT_8032ec68 = DAT_8032ec68 + 1;
  if (4 < DAT_8032ec68) {
    DAT_8032ec68 = 0;
    IsConnected__4CUSBFv(&USB);
  }
  return;
}

