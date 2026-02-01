// Function: __MidiCtrl_PanDirect__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
// Entry: 801c8884
// Size: 92 bytes

void __MidiCtrl_PanDirect__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
               (undefined4 param_1,undefined4 param_2,undefined4 *param_3)

{
  byte *pbVar1;
  
  pbVar1 = (byte *)*param_3;
  *param_3 = pbVar1 + 1;
  param_3[0x10] = (uint)*pbVar1 << 0xc;
  param_3[0x11] = 0;
  param_3[0x12] = 0;
  if (param_3[0x2d] == 0) {
    param_3[0x33] = 0;
  }
  DAT_8032f4b4 = DAT_8032f4b4 | 2;
  return;
}

