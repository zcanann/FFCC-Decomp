// Function: __MidiCtrl_FineTuneRelative__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
// Entry: 801c99d8
// Size: 44 bytes

void __MidiCtrl_FineTuneRelative__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
               (undefined4 param_1,undefined4 param_2,undefined4 *param_3)

{
  char *pcVar1;
  
  pcVar1 = (char *)*param_3;
  *param_3 = pcVar1 + 1;
  *(char *)(param_3 + 0x52) = *(char *)(param_3 + 0x52) + *pcVar1;
  DAT_8032f4b4 = DAT_8032f4b4 | 1;
  return;
}

