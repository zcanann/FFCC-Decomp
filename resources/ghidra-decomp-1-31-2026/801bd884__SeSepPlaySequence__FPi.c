// Function: _SeSepPlaySequence__FPi
// Entry: 801bd884
// Size: 92 bytes

void _SeSepPlaySequence__FPi(undefined4 *param_1)

{
  int iVar1;
  
  iVar1 = SearchSeSepSequence__9CRedEntryFi(&DAT_8032e154,param_1[1]);
  if (-1 < iVar1) {
    DAT_8032f440 = param_1[4];
    SeSepPlay__Fiiii(*param_1,param_1[1],param_1[2],param_1[3]);
  }
  return;
}

