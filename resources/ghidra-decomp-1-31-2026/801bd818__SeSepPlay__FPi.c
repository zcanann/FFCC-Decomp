// Function: _SeSepPlay__FPi
// Entry: 801bd818
// Size: 108 bytes

void _SeSepPlay__FPi(undefined4 *param_1)

{
  int iVar1;
  
  iVar1 = SetSeSepData__9CRedEntryFP12RedSeSepHEAD(&DAT_8032e154,param_1[1]);
  if (iVar1 != 0) {
    DAT_8032f440 = param_1[4];
    SeSepPlay__Fiiii(*param_1,*(undefined4 *)(iVar1 + 8),param_1[2],param_1[3]);
  }
  return;
}

