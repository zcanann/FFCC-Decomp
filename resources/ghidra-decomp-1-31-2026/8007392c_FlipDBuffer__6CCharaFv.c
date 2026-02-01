// Function: FlipDBuffer__6CCharaFv
// Entry: 8007392c
// Size: 36 bytes

void FlipDBuffer__6CCharaFv(int param_1)

{
  *(int *)(param_1 + 0x2060) = 1 - *(int *)(param_1 + 0x2060);
  *(undefined4 *)(param_1 + *(int *)(param_1 + 0x2060) * 8 + 0x2064) = 0;
  return;
}

