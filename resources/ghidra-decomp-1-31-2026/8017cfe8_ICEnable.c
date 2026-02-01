// Function: ICEnable
// Entry: 8017cfe8
// Size: 20 bytes

uint ICEnable(void)

{
  uint in_HID0;
  
  instructionSynchronize();
  return in_HID0 | 0x8000;
}

