// Function: __MidiCtrl_VibrateDelay__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
// Entry: 801c93b0
// Size: 40 bytes

void __MidiCtrl_VibrateDelay__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
               (undefined4 param_1,undefined4 param_2,int *param_3)

{
  *(ushort *)(param_3 + 0x24) = (ushort)*(byte *)*param_3;
  *(ushort *)((int)param_3 + 0x92) = (ushort)*(byte *)(*param_3 + 1);
  *param_3 = *param_3 + 2;
  return;
}

