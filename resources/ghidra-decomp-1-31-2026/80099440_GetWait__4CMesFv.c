// Function: GetWait__4CMesFv
// Entry: 80099440
// Size: 32 bytes

undefined4 GetWait__4CMesFv(int param_1)

{
  if (*(int *)(param_1 + 0x3c7c) < *(int *)(param_1 + 0x3c80)) {
    return *(undefined4 *)(param_1 + 0x3c78);
  }
  return 0;
}

