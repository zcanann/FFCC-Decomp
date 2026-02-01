// Function: DSPCancelTask
// Entry: 80197ba4
// Size: 64 bytes

int DSPCancelTask(int param_1)

{
  OSDisableInterrupts();
  *(uint *)(param_1 + 8) = *(uint *)(param_1 + 8) | 2;
  OSRestoreInterrupts();
  return param_1;
}

