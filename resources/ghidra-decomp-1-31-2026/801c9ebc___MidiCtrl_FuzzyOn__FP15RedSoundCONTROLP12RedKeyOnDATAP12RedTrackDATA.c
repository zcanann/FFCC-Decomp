// Function: __MidiCtrl_FuzzyOn__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
// Entry: 801c9ebc
// Size: 228 bytes

void __MidiCtrl_FuzzyOn__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
               (undefined4 param_1,undefined4 param_2,undefined4 *param_3)

{
  byte bVar1;
  byte *pbVar2;
  byte *pbVar3;
  int iVar4;
  uint uVar5;
  
  pbVar3 = (byte *)*param_3;
  *param_3 = pbVar3 + 1;
  pbVar2 = (byte *)*param_3;
  bVar1 = *pbVar3;
  *param_3 = pbVar2 + 1;
  uVar5 = (uint)*pbVar2;
  if (uVar5 == 0) {
    iVar4 = 0x100;
  }
  else {
    iVar4 = uVar5 + 1;
  }
  if (bVar1 == 3) {
    param_3[0x3b] = iVar4;
    param_3[0x3f] = param_3[0x3f] | 0x20000;
    return;
  }
  if (bVar1 < 3) {
    if (bVar1 == 1) {
      param_3[0x39] = iVar4;
      param_3[0x3f] = param_3[0x3f] | 0x8000;
      return;
    }
    if (bVar1 != 0) {
      param_3[0x3a] = iVar4;
      param_3[0x3f] = param_3[0x3f] | 0x10000;
      return;
    }
  }
  else if (bVar1 < 5) {
    param_3[0x3c] = iVar4;
    param_3[0x3f] = param_3[0x3f] | 0x40000;
    return;
  }
  param_3[0x38] = iVar4;
  param_3[0x3f] = param_3[0x3f] | 0x4000;
  return;
}

