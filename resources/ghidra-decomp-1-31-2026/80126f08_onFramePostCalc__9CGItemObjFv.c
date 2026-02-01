// Function: onFramePostCalc__9CGItemObjFv
// Entry: 80126f08
// Size: 48 bytes

void onFramePostCalc__9CGItemObjFv(int param_1)

{
  if (-1 < (int)((uint)*(byte *)(param_1 + 0x50) << 0x1c | (uint)(*(byte *)(param_1 + 0x50) >> 4)))
  {
    return;
  }
  if (*(int *)(param_1 + 0x550) != 0) {
    return;
  }
  *(int *)(param_1 + 0x94) = *(int *)(param_1 + 0x94) + -1;
  return;
}

