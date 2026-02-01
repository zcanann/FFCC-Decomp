// Function: SystemCallVector
// Entry: 80180970
// Size: 28 bytes

void SystemCallVector(void)

{
  undefined4 in_MSR;
  undefined4 in_SRR1;
  
  instructionSynchronize();
  sync(0);
  returnFromInterrupt(in_MSR,in_SRR1);
  return;
}

