// Function: DCEnable
// Entry: 8017ceac
// Size: 20 bytes

uint DCEnable(void)

{
  uint in_HID0;
  
  sync(0);
  return in_HID0 | 0x4000;
}

