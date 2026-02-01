// Function: OSRestoreInterrupts
// Entry: 8017e368
// Size: 36 bytes

uint OSRestoreInterrupts(void)

{
  uint in_MSR;
  
  return in_MSR >> 0xf & 1;
}

