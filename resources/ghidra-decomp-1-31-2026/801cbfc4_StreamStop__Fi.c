// Function: StreamStop__Fi
// Entry: 801cbfc4
// Size: 112 bytes

void StreamStop__Fi(int param_1)

{
  uint uVar1;
  
  uVar1 = DAT_8032f438;
  do {
    if ((*(int *)(uVar1 + 0x10c) != 0) && ((param_1 == -1 || (param_1 == *(int *)(uVar1 + 0x10c)))))
    {
      _StreamStop__FP13RedStreamDATA(uVar1);
    }
    uVar1 = uVar1 + 0x130;
  } while (uVar1 < DAT_8032f438 + 0x4c0);
  return;
}

