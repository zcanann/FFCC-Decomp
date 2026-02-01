// Function: __MidiCtrl_PitchBend__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
// Entry: 801c9b3c
// Size: 132 bytes

void __MidiCtrl_PitchBend__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
               (undefined4 param_1,undefined4 param_2,int *param_3)

{
  int iVar1;
  
  iVar1 = (uint)*(byte *)*param_3 + (uint)*(byte *)(*param_3 + 1) * 0x80 + -0x2000;
  *(short *)(param_3 + 0x50) = (short)iVar1;
  *(short *)((int)param_3 + 0x13e) = (short)(iVar1 * *(char *)((int)param_3 + 0x14b) >> 5);
  *param_3 = *param_3 + 2;
  _PitchBendCompute__FP12RedTrackDATAi(param_3,(int)*(short *)((int)param_3 + 0x13e));
  return;
}

