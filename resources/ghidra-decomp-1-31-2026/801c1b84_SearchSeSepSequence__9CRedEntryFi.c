// Function: SearchSeSepSequence__9CRedEntryFi
// Entry: 801c1b84
// Size: 156 bytes

int SearchSeSepSequence__9CRedEntryFi(int param_1,int param_2)

{
  uint uVar1;
  int *piVar2;
  
  piVar2 = *(int **)(param_1 + 4);
  if (param_2 == -1) {
    do {
      if (piVar2[3] != 0) {
        uVar1 = (int)piVar2 - *(int *)(param_1 + 4);
        return ((int)uVar1 >> 4) + (uint)((int)uVar1 < 0 && (uVar1 & 0xf) != 0);
      }
      piVar2 = piVar2 + 4;
    } while (piVar2 < (int *)(*(int *)(param_1 + 4) + 0x1000U));
  }
  else {
    do {
      if ((piVar2[3] != 0) && (*piVar2 == param_2)) {
        uVar1 = (int)piVar2 - *(int *)(param_1 + 4);
        return ((int)uVar1 >> 4) + (uint)((int)uVar1 < 0 && (uVar1 & 0xf) != 0);
      }
      piVar2 = piVar2 + 4;
    } while (piVar2 < (int *)(*(int *)(param_1 + 4) + 0x1000));
  }
  return -1;
}

