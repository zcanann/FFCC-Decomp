// Function: Config48MB
// Entry: 8017eefc
// Size: 128 bytes

void Config48MB(void)

{
  uint in_MSR;
  
  instructionSynchronize();
  instructionSynchronize();
  instructionSynchronize();
  instructionSynchronize();
  instructionSynchronize();
  returnFromInterrupt(in_MSR,in_MSR | 0x30);
  return;
}

