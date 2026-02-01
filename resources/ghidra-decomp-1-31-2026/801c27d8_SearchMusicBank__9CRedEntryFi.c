// Function: SearchMusicBank__9CRedEntryFi
// Entry: 801c27d8
// Size: 68 bytes

int * SearchMusicBank__9CRedEntryFi(int param_1,int param_2)

{
  int *piVar1;
  
  piVar1 = *(int **)(param_1 + 8);
  do {
    if (*piVar1 == param_2) {
      return piVar1;
    }
    piVar1 = piVar1 + 4;
  } while (piVar1 < (int *)(*(int *)(param_1 + 8) + 0x40));
  return (int *)0x0;
}

