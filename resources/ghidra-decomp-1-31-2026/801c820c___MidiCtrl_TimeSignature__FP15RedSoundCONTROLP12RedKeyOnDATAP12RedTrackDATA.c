// Function: __MidiCtrl_TimeSignature__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
// Entry: 801c820c
// Size: 64 bytes

void __MidiCtrl_TimeSignature__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
               (int param_1,undefined4 param_2,int *param_3)

{
  *(ushort *)(param_1 + 0x18) = (ushort)*(byte *)*param_3;
  *(ushort *)(param_1 + 0x1a) = (ushort)*(byte *)(*param_3 + 1);
  *(int *)(param_1 + 0x14) =
       (0xc0 / (int)*(short *)(param_1 + 0x1a)) * (int)*(short *)(param_1 + 0x18);
  *param_3 = *param_3 + 2;
  return;
}

