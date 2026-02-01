// Function: __MidiCtrl_TremoloDelay__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
// Entry: 801c96f0
// Size: 40 bytes

void __MidiCtrl_TremoloDelay__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
               (undefined4 param_1,undefined4 param_2,int *param_3)

{
  *(ushort *)(param_3 + 0x2c) = (ushort)*(byte *)*param_3;
  *(ushort *)((int)param_3 + 0xb2) = (ushort)*(byte *)(*param_3 + 1);
  *param_3 = *param_3 + 2;
  return;
}

