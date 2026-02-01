// Function: __MidiCtrl_VibrateType__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
// Entry: 801c9370
// Size: 64 bytes

void __MidiCtrl_VibrateType__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
               (undefined4 param_1,undefined4 param_2,undefined4 *param_3)

{
  byte *pbVar1;
  
  pbVar1 = (byte *)*param_3;
  *param_3 = pbVar1 + 1;
  param_3[0x1d] = (&PTR_SineSwing__Fi_8021e9d0)[*pbVar1 & 0xf];
  return;
}

