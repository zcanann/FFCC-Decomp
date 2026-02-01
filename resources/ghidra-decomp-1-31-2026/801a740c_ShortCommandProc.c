// Function: ShortCommandProc
// Entry: 801a740c
// Size: 84 bytes

void ShortCommandProc(int param_1)

{
  param_1 = param_1 * 0x100;
  if (*(int *)(&DAT_80328340 + param_1) != 0) {
    return;
  }
  if (((&DAT_80328325)[param_1] == '\0') && ((&DAT_80328326)[param_1] == '\x04')) {
    **(byte **)(&DAT_80328334 + param_1) = (&DAT_80328327)[param_1] & 0x3a;
    return;
  }
  *(undefined4 *)(&DAT_80328340 + param_1) = 1;
  return;
}

