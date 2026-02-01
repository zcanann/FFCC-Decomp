// Function: SetStreamVolume__Fiii
// Entry: 801cc534
// Size: 204 bytes

void SetStreamVolume__Fiii(int param_1,uint param_2,int param_3)

{
  int iVar1;
  uint uVar2;
  
  if (param_3 < 1) {
    iVar1 = 1;
  }
  else {
    iVar1 = (param_3 * 200) / 0x3c + (param_3 * 200 >> 0x1f);
    iVar1 = iVar1 - (iVar1 >> 0x1f);
  }
  param_2 = param_2 & 0x7f;
  uVar2 = DAT_8032f438;
  if (param_2 != 0) {
    param_2 = ((param_2 + 1) * 0x100 + -1) * 0x1000 | 0x800;
  }
  do {
    if ((*(int *)(uVar2 + 0x10c) != 0) && ((param_1 == -1 || (param_1 == *(int *)(uVar2 + 0x10c)))))
    {
      if (iVar1 < 1) {
        *(uint *)(uVar2 + 0xf0) = param_2;
        *(undefined4 *)(uVar2 + 0xf8) = 0;
      }
      else {
        *(int *)(uVar2 + 0xf4) = (int)(param_2 - *(int *)(uVar2 + 0xf0)) / iVar1;
        *(int *)(uVar2 + 0xf8) = iVar1;
      }
    }
    uVar2 = uVar2 + 0x130;
  } while (uVar2 < DAT_8032f438 + 0x4c0);
  return;
}

