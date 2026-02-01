// Function: Quit__6CCharaFv
// Entry: 800739a4
// Size: 104 bytes

void Quit__6CCharaFv(int param_1)

{
  if (*(void **)(param_1 + 0x2068) != (void *)0x0) {
    __dla__FPv(*(void **)(param_1 + 0x2068));
    *(undefined4 *)(param_1 + 0x2068) = 0;
  }
  if (*(void **)(param_1 + 0x2070) != (void *)0x0) {
    __dla__FPv(*(void **)(param_1 + 0x2070));
    *(undefined4 *)(param_1 + 0x2070) = 0;
  }
  DestroyStage__7CMemoryFPQ27CMemory6CStage(&Memory,*(undefined4 *)(param_1 + 0x2058));
  return;
}

