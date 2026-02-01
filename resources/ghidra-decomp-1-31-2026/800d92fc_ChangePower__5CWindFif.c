// Function: ChangePower__5CWindFif
// Entry: 800d92fc
// Size: 192 bytes

void ChangePower__5CWindFif(double param_1,byte *param_2,int param_3)

{
  byte *pbVar1;
  int iVar2;
  
  iVar2 = 8;
  do {
    if ((((((int)((uint)*param_2 << 0x18) < 0) &&
          (pbVar1 = param_2, param_3 == *(int *)(param_2 + 0x20))) ||
         ((pbVar1 = param_2 + 100, (int)((uint)*pbVar1 << 0x18) < 0 &&
          (param_3 == *(int *)(param_2 + 0x84))))) ||
        ((pbVar1 = param_2 + 200, (int)((uint)*pbVar1 << 0x18) < 0 &&
         (param_3 == *(int *)(param_2 + 0xe8))))) ||
       (((int)((uint)param_2[300] << 0x18) < 0 &&
        (pbVar1 = param_2 + 300, param_3 == *(int *)(param_2 + 0x14c))))) goto LAB_800d93a8;
    param_2 = param_2 + 400;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  pbVar1 = (byte *)0x0;
LAB_800d93a8:
  if (pbVar1 != (byte *)0x0) {
    *(float *)(pbVar1 + 0x54) = (float)param_1;
    *(float *)(pbVar1 + 0x4c) = (float)param_1;
    return;
  }
  return;
}

