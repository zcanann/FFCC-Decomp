// Function: __MidiCtrl_KeyOnVelocity__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
// Entry: 801c83e0
// Size: 80 bytes

void __MidiCtrl_KeyOnVelocity__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
               (undefined4 param_1,undefined4 param_2,undefined4 *param_3)

{
  undefined *puVar1;
  
  puVar1 = (undefined *)*param_3;
  *param_3 = puVar1 + 1;
  *(undefined *)((int)param_3 + 0x25) = *puVar1;
  KeyOnReserve__FP12RedKeyOnDATAP12RedTrackDATA(param_2,param_3);
  return;
}

