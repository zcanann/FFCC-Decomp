// Function: GXInitFifoPtrs
// Entry: 801a0468
// Size: 112 bytes

void GXInitFifoPtrs(int param_1,int param_2,int param_3)

{
  OSDisableInterrupts();
  *(int *)(param_1 + 0x14) = param_2;
  *(int *)(param_1 + 0x18) = param_3;
  *(int *)(param_1 + 0x1c) = param_3 - param_2;
  if (*(int *)(param_1 + 0x1c) < 0) {
    *(int *)(param_1 + 0x1c) = *(int *)(param_1 + 0x1c) + *(int *)(param_1 + 8);
  }
  OSRestoreInterrupts();
  return;
}

