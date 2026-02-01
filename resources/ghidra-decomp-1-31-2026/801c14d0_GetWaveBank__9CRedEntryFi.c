// Function: GetWaveBank__9CRedEntryFi
// Entry: 801c14d0
// Size: 40 bytes

int GetWaveBank__9CRedEntryFi(int *param_1,int param_2)

{
  if ((-1 < param_2) && (param_2 < 0x10)) {
    return *param_1 + param_2 * 0x10;
  }
  return 0;
}

