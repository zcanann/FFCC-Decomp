// Function: __MidiCtrl_ShakeRateDirect__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
// Entry: 801c9864
// Size: 96 bytes

void __MidiCtrl_ShakeRateDirect__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
               (undefined4 param_1,undefined4 param_2,int *param_3)

{
  uint uVar1;
  
  if (*(char *)*param_3 == '\0') {
    uVar1 = 0x100;
  }
  else {
    uVar1 = (uint)*(byte *)*param_3;
  }
  param_3[0x2e] = 0x100000 / uVar1;
  *(undefined2 *)(param_3 + 0x34) = 0;
  *param_3 = *param_3 + 1;
  return;
}

