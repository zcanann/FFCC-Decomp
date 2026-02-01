// Function: __MidiCtrl_KeyOffNote__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
// Entry: 801c84c8
// Size: 84 bytes

void __MidiCtrl_KeyOffNote__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
               (undefined4 param_1,undefined4 param_2,undefined4 *param_3)

{
  undefined *puVar1;
  
  puVar1 = (undefined *)*param_3;
  *param_3 = puVar1 + 1;
  *(undefined *)(param_3 + 9) = *puVar1;
  KeyOffSet__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA(param_1,param_2);
  return;
}

