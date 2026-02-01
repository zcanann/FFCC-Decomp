// Function: __MidiCtrl_FineTuneAbsolute__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
// Entry: 801c99b4
// Size: 36 bytes

void __MidiCtrl_FineTuneAbsolute__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
               (undefined4 param_1,undefined4 param_2,undefined4 *param_3)

{
  undefined *puVar1;
  
  puVar1 = (undefined *)*param_3;
  *param_3 = puVar1 + 1;
  *(undefined *)(param_3 + 0x52) = *puVar1;
  DAT_8032f4b4 = DAT_8032f4b4 | 1;
  return;
}

