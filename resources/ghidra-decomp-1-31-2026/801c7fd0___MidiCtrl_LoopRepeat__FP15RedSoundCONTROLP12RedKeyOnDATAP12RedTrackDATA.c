// Function: __MidiCtrl_LoopRepeat__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
// Entry: 801c7fd0
// Size: 44 bytes

void __MidiCtrl_LoopRepeat__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
               (undefined4 param_1,undefined4 param_2,undefined4 *param_3)

{
  *param_3 = param_3[*(short *)(param_3 + 0x4f) + 2];
  *(undefined2 *)(param_3 + 0x51) =
       *(undefined2 *)((int)param_3 + *(short *)(param_3 + 0x4f) * 2 + 0x130);
  return;
}

