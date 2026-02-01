// Function: SearchSeSepBank__9CRedEntryFi
// Entry: 801c20d8
// Size: 68 bytes

int * SearchSeSepBank__9CRedEntryFi(int param_1,int param_2)

{
  int *piVar1;
  
  piVar1 = *(int **)(param_1 + 4);
  do {
    if (*piVar1 == param_2) {
      return piVar1;
    }
    piVar1 = piVar1 + 4;
  } while (piVar1 < (int *)(*(int *)(param_1 + 4) + 0x1000));
  return (int *)0x0;
}

