// Function: ClearWaveDataM__9CRedEntryFiiii
// Entry: 801c12cc
// Size: 204 bytes

void ClearWaveDataM__9CRedEntryFiiii(int *param_1,int param_2,int param_3,int param_4,int param_5)

{
  int *piVar1;
  
  if ((((param_2 != -1) || (param_3 != -1)) || (param_4 != -1)) || (param_5 != -1)) {
    for (piVar1 = (int *)(*param_1 + 0x100); piVar1 < (int *)(*param_1 + 0x400); piVar1 = piVar1 + 4
        ) {
      if ((((-1 < *piVar1) && (0 < piVar1[1])) &&
          ((*piVar1 != param_2 && ((*piVar1 != param_3 && (*piVar1 != param_4)))))) &&
         (*piVar1 != param_5)) {
        WaveDelete__9CRedEntryFP14RedHistoryBANK(param_1,piVar1);
      }
    }
  }
  return;
}

