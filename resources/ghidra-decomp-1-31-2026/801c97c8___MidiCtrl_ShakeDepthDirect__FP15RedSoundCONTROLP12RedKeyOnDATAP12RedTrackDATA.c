// Function: __MidiCtrl_ShakeDepthDirect__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
// Entry: 801c97c8
// Size: 36 bytes

void __MidiCtrl_ShakeDepthDirect__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
               (undefined4 param_1,undefined4 param_2,undefined4 *param_3)

{
  byte *pbVar1;
  
  pbVar1 = (byte *)*param_3;
  *param_3 = pbVar1 + 1;
  param_3[0x30] = (uint)*pbVar1 << 0xc;
  *(undefined2 *)((int)param_3 + 0xd2) = 0;
  return;
}

