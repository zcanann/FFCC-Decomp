// Function: __MidiCtrl_PitchBendRange__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
// Entry: 801c9bc0
// Size: 112 bytes

void __MidiCtrl_PitchBendRange__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
               (undefined4 param_1,undefined4 param_2,undefined4 *param_3)

{
  undefined *puVar1;
  
  puVar1 = (undefined *)*param_3;
  *param_3 = puVar1 + 1;
  *(undefined *)((int)param_3 + 0x14b) = *puVar1;
  *(short *)((int)param_3 + 0x13e) =
       (short)((int)*(short *)(param_3 + 0x50) * (int)*(char *)((int)param_3 + 0x14b) >> 5);
  _PitchBendCompute__FP12RedTrackDATAi(param_3,(int)*(short *)((int)param_3 + 0x13e));
  return;
}

