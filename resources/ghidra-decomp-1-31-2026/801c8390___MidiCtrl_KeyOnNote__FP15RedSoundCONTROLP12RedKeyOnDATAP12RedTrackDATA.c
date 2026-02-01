// Function: __MidiCtrl_KeyOnNote__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
// Entry: 801c8390
// Size: 80 bytes

void __MidiCtrl_KeyOnNote__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
               (undefined4 param_1,undefined4 param_2,undefined4 *param_3)

{
  undefined *puVar1;
  
  puVar1 = (undefined *)*param_3;
  *param_3 = puVar1 + 1;
  *(undefined *)(param_3 + 9) = *puVar1;
  KeyOnReserve__FP12RedKeyOnDATAP12RedTrackDATA(param_2,param_3);
  return;
}

