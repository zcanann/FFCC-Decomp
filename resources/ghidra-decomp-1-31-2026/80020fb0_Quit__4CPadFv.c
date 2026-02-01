// Function: Quit__4CPadFv
// Entry: 80020fb0
// Size: 88 bytes

void Quit__4CPadFv(int param_1)

{
  if (*(void **)(param_1 + 0x1b0) != (void *)0x0) {
    __dla__FPv(*(void **)(param_1 + 0x1b0));
    *(undefined4 *)(param_1 + 0x1b0) = 0;
  }
  if (*(int *)(param_1 + 0x1ac) != 0) {
    DestroyStage__7CMemoryFPQ27CMemory6CStage(&Memory,*(int *)(param_1 + 0x1ac));
  }
  return;
}

