// Function: RealMode
// Entry: 8017ef7c
// Size: 24 bytes

uint RealMode(void)

{
  uint in_MSR;
  
  returnFromInterrupt(in_MSR,in_MSR & 0xffffffcf);
  return in_MSR & 0xffffffcf;
}

