// Function: ClearWaveData__9CRedEntryFi
// Entry: 801c1190
// Size: 316 bytes

void ClearWaveData__9CRedEntryFi(int *param_1,int param_2)

{
  int iVar1;
  int *piVar2;
  
  if (param_2 < 0) {
    if (param_2 == -1) {
      for (piVar2 = (int *)*param_1; piVar2 < (int *)(*param_1 + 0x400); piVar2 = piVar2 + 4) {
        if (-1 < *piVar2) {
          WaveDelete__9CRedEntryFP14RedHistoryBANK(param_1,piVar2);
        }
      }
    }
    else if (param_2 == -2) {
      for (piVar2 = (int *)(*param_1 + 0x100); piVar2 < (int *)(*param_1 + 0x400);
          piVar2 = piVar2 + 4) {
        if (-1 < *piVar2) {
          WaveDelete__9CRedEntryFP14RedHistoryBANK(param_1,piVar2);
        }
      }
    }
    else if (param_2 == -3) {
      for (piVar2 = (int *)(*param_1 + 0x100); piVar2 < (int *)(*param_1 + 0x400);
          piVar2 = piVar2 + 4) {
        if ((-1 < *piVar2) && (0 < piVar2[1])) {
          WaveDelete__9CRedEntryFP14RedHistoryBANK(param_1,piVar2);
        }
      }
    }
  }
  else {
    iVar1 = SearchWaveSequence__9CRedEntryFi(param_1,param_2);
    if (-1 < iVar1) {
      WaveDelete__9CRedEntryFP14RedHistoryBANK(param_1,*param_1 + iVar1 * 0x10);
    }
  }
  return;
}

