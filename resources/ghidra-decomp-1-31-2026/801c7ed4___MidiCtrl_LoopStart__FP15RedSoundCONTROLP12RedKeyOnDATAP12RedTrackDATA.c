// Function: __MidiCtrl_LoopStart__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
// Entry: 801c7ed4
// Size: 88 bytes

void __MidiCtrl_LoopStart__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
               (undefined4 param_1,undefined4 param_2,undefined4 *param_3)

{
  *(short *)(param_3 + 0x4f) = *(short *)(param_3 + 0x4f) + 1;
  *(ushort *)(param_3 + 0x4f) = *(ushort *)(param_3 + 0x4f) & 3;
  param_3[*(short *)(param_3 + 0x4f) + 2] = *param_3;
  *(undefined2 *)((int)param_3 + *(short *)(param_3 + 0x4f) * 2 + 0x130) =
       *(undefined2 *)(param_3 + 0x51);
  *(undefined2 *)((int)param_3 + *(short *)(param_3 + 0x4f) * 2 + 0x128) = 0;
  return;
}

