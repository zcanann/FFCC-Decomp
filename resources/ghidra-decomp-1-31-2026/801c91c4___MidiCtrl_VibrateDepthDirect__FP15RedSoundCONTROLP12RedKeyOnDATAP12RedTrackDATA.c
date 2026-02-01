// Function: __MidiCtrl_VibrateDepthDirect__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
// Entry: 801c91c4
// Size: 36 bytes

void __MidiCtrl_VibrateDepthDirect__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
               (undefined4 param_1,undefined4 param_2,undefined4 *param_3)

{
  byte *pbVar1;
  
  pbVar1 = (byte *)*param_3;
  *param_3 = pbVar1 + 1;
  param_3[0x20] = (uint)*pbVar1 << 0xc;
  *(undefined2 *)((int)param_3 + 0x8e) = 0;
  return;
}

