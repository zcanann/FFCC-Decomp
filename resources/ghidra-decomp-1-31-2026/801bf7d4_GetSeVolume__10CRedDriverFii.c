// Function: GetSeVolume__10CRedDriverFii
// Entry: 801bf7d4
// Size: 128 bytes

int GetSeVolume__10CRedDriverFii(CRedDriver *redDriver,int param_2,int param_3)

{
  int *piVar1;
  
  piVar1 = *(int **)(DAT_8032f3f0 + 0xdbc);
  while ((*piVar1 == 0 || (((param_2 != -1 && (param_2 != piVar1[0x3e])) || (*piVar1 == 0))))) {
    piVar1 = piVar1 + 0x55;
    if ((int *)(*(int *)(DAT_8032f3f0 + 0xdbc) + 0x2a80) <= piVar1) {
      return 0;
    }
  }
  if (param_3 == 1) {
    return piVar1[0x15];
  }
  return piVar1[0x13] >> 0xc;
}

