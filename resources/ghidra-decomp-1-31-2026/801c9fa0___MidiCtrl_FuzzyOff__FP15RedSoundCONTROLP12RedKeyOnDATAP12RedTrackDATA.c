// Function: __MidiCtrl_FuzzyOff__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
// Entry: 801c9fa0
// Size: 152 bytes

void __MidiCtrl_FuzzyOff__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
               (undefined4 param_1,undefined4 param_2,undefined4 *param_3)

{
  byte bVar1;
  byte *pbVar2;
  
  pbVar2 = (byte *)*param_3;
  *param_3 = pbVar2 + 1;
  bVar1 = *pbVar2;
  if (bVar1 == 3) {
    param_3[0x3f] = param_3[0x3f] & 0xfffdffff;
    return;
  }
  if (bVar1 < 3) {
    if (bVar1 == 1) {
      param_3[0x3f] = param_3[0x3f] & 0xffff7fff;
      return;
    }
    if (bVar1 != 0) {
      param_3[0x3f] = param_3[0x3f] & 0xfffeffff;
      return;
    }
  }
  else if (bVar1 < 5) {
    param_3[0x3f] = param_3[0x3f] & 0xfffbffff;
    return;
  }
  param_3[0x3f] = param_3[0x3f] & 0xffffbfff;
  return;
}

