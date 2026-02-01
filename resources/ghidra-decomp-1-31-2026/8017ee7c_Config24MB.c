// Function: Config24MB
// Entry: 8017ee7c
// Size: 128 bytes

void Config24MB(void)

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

