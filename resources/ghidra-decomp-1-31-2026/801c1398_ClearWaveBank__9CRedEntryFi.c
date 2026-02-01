// Function: ClearWaveBank__9CRedEntryFi
// Entry: 801c1398
// Size: 312 bytes

void ClearWaveBank__9CRedEntryFi(int *param_1,int param_2)

{
  int *piVar1;
  
  if (param_2 < 0) {
    if (param_2 == -1) {
      for (piVar1 = (int *)*param_1; piVar1 < (int *)(*param_1 + 0x400); piVar1 = piVar1 + 4) {
        if (-1 < *piVar1) {
          WaveDelete__9CRedEntryFP14RedHistoryBANK(param_1,piVar1);
        }
      }
    }
    else if (param_2 == -2) {
      for (piVar1 = (int *)(*param_1 + 0x100); piVar1 < (int *)(*param_1 + 0x400);
          piVar1 = piVar1 + 4) {
        if (-1 < *piVar1) {
          WaveDelete__9CRedEntryFP14RedHistoryBANK(param_1,piVar1);
        }
      }
    }
    else if (param_2 == -3) {
      for (piVar1 = (int *)(*param_1 + 0x100); piVar1 < (int *)(*param_1 + 0x400);
          piVar1 = piVar1 + 4) {
        if ((-1 < *piVar1) && (0 < piVar1[1])) {
          WaveDelete__9CRedEntryFP14RedHistoryBANK(param_1,piVar1);
        }
      }
    }
  }
  else if ((-1 < param_2) && (param_2 < 0x10)) {
    WaveDelete__9CRedEntryFP14RedHistoryBANK(param_1,*param_1 + param_2 * 0x10);
  }
  return;
}

