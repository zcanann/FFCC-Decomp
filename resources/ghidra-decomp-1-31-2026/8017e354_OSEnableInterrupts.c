// Function: OSEnableInterrupts
// Entry: 8017e354
// Size: 20 bytes

ulonglong OSEnableInterrupts(void)

{
  uint in_MSR;
  
  return CONCAT44(in_MSR >> 0xf,in_MSR) & 0x1ffffffff | 0x8000;
}

