// Function: WriteProc
// Entry: 801a88dc
// Size: 48 bytes

void WriteProc(int param_1)

{
  param_1 = param_1 * 0x100;
  if (*(int *)(&DAT_80328340 + param_1) != 0) {
    return;
  }
  **(byte **)(&DAT_80328334 + param_1) = (&DAT_80328325)[param_1] & 0x3a;
  return;
}

