// Function: destroyFullShadow__10CCameraPcsFv
// Entry: 800382f8
// Size: 96 bytes

void destroyFullShadow__10CCameraPcsFv(int param_1)

{
  if (*(int *)(param_1 + 0x31c) != 0) {
    __dl__FPv();
    *(undefined4 *)(param_1 + 0x31c) = 0;
  }
  if (*(int *)(param_1 + 800) != 0) {
    __dl__FPv();
    *(undefined4 *)(param_1 + 800) = 0;
  }
  return;
}

