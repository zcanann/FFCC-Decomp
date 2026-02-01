// Function: SetSeVolume__Fiiii
// Entry: 801cad78
// Size: 168 bytes

void SetSeVolume__Fiiii(int param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  int *piVar2;
  
  if (param_3 < 1) {
    param_3 = 1;
  }
  piVar2 = *(int **)(DAT_8032f3f0 + 0xdbc);
  iVar1 = (param_3 * 0x60) / 0x3c + (param_3 * 0x60 >> 0x1f);
  iVar1 = iVar1 - (iVar1 >> 0x1f);
  do {
    if ((*piVar2 != 0) && ((param_1 < 0 || (piVar2[0x3e] == param_1)))) {
      piVar2[0x14] = (int)((param_2 << 0xc | 0x800U) - piVar2[0x13]) / iVar1;
      piVar2[0x15] = iVar1;
      piVar2[0x16] = param_4;
    }
    piVar2 = piVar2 + 0x55;
  } while (piVar2 < (int *)(*(int *)(DAT_8032f3f0 + 0xdbc) + 0x2a80));
  return;
}

