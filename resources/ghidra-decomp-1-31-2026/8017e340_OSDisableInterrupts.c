// Function: OSDisableInterrupts
// Entry: 8017e340
// Size: 20 bytes

ulonglong OSDisableInterrupts(void)

{
  uint in_MSR;
  
  return CONCAT44(in_MSR >> 0xf,in_MSR) & 0x1ffff7fff;
}

