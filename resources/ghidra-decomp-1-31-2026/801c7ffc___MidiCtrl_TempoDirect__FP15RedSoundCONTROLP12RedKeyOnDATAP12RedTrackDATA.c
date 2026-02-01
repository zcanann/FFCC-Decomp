// Function: __MidiCtrl_TempoDirect__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
// Entry: 801c7ffc
// Size: 44 bytes

void __MidiCtrl_TempoDirect__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
               (int param_1,undefined4 param_2,undefined4 *param_3)

{
  byte *pbVar1;
  
  pbVar1 = (byte *)*param_3;
  *param_3 = pbVar1 + 1;
  *(uint *)(param_1 + 0x448) = (uint)*pbVar1 << 0xc;
  *(undefined4 *)(param_1 + 0x44c) = 0;
  *(undefined4 *)(param_1 + 0x450) = 0;
  return;
}

