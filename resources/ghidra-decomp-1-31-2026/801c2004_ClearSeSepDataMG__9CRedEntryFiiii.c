// Function: ClearSeSepDataMG__9CRedEntryFiiii
// Entry: 801c2004
// Size: 212 bytes

undefined4
ClearSeSepDataMG__9CRedEntryFiiii(int param_1,int param_2,int param_3,int param_4,int param_5)

{
  int iVar1;
  int *piVar2;
  
  piVar2 = *(int **)(param_1 + 4);
  do {
    if (piVar2[3] != 0) {
      iVar1 = *piVar2 / 1000 + (*piVar2 >> 0x1f);
      iVar1 = iVar1 - (iVar1 >> 0x1f);
      if ((((param_2 != iVar1) && (param_3 != iVar1)) && (param_4 != iVar1)) && (param_5 != iVar1))
      {
        SeSepMemoryFree__9CRedEntryFP14RedHistoryBANK(param_1,piVar2);
      }
    }
    piVar2 = piVar2 + 4;
  } while (piVar2 < (int *)(*(int *)(param_1 + 4) + 0x1000U));
  return 0;
}

