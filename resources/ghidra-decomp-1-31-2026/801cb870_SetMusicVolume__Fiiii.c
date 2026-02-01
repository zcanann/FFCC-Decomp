// Function: SetMusicVolume__Fiiii
// Entry: 801cb870
// Size: 204 bytes

void SetMusicVolume__Fiiii(int param_1,uint param_2,int param_3,int param_4)

{
  int iVar1;
  uint uVar2;
  
  if (param_2 != 0) {
    param_2 = ((param_2 + 1) * 4 + -1) * 0x1000;
  }
  uVar2 = DAT_8032f3f0;
  if (param_3 < 1) {
    iVar1 = 1;
  }
  else {
    iVar1 = (param_3 * 200) / 0x3c + (param_3 * 200 >> 0x1f);
    iVar1 = iVar1 - (iVar1 >> 0x1f);
  }
  do {
    if (((param_1 == -1) || (param_1 == *(int *)(uVar2 + 0x470))) || (*(int *)(uVar2 + 0x470) < 0))
    {
      if (param_4 == 1) {
        *(int *)(uVar2 + 0x458) = -*(int *)(uVar2 + 0x454) / iVar1;
        *(int *)(uVar2 + 0x45c) = iVar1;
      }
      else {
        *(int *)(uVar2 + 0x20) = (int)((param_2 | 0x800) - *(int *)(uVar2 + 0x1c)) / iVar1;
        *(int *)(uVar2 + 0x24) = iVar1;
      }
    }
    uVar2 = uVar2 + 0x494;
  } while (uVar2 < DAT_8032f3f0 + 0xdbc);
  return;
}

