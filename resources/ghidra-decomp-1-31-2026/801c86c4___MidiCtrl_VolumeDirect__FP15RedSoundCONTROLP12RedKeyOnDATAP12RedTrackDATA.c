// Function: __MidiCtrl_VolumeDirect__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
// Entry: 801c86c4
// Size: 92 bytes

void __MidiCtrl_VolumeDirect__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
               (undefined4 param_1,undefined4 param_2,undefined4 *param_3)

{
  byte *pbVar1;
  uint uVar2;
  
  pbVar1 = (byte *)*param_3;
  *param_3 = pbVar1 + 1;
  uVar2 = (uint)*pbVar1;
  if (uVar2 != 0) {
    uVar2 = ((uVar2 + 1) * 0x100 + -1) * 0x1000;
  }
  param_3[10] = uVar2;
  param_3[0xb] = 0;
  param_3[0xc] = 0;
  DAT_8032f4b4 = DAT_8032f4b4 | 2;
  return;
}

