// Function: __MidiCtrl_ChannelAlloc__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
// Entry: 801c8ff0
// Size: 24 bytes

void __MidiCtrl_ChannelAlloc__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
               (int param_1,undefined4 param_2,undefined4 *param_3)

{
  undefined *puVar1;
  
  puVar1 = (undefined *)*param_3;
  *param_3 = puVar1 + 1;
  *(undefined *)(param_1 + 0x490) = *puVar1;
  return;
}

