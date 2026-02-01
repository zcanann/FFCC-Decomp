// Function: __MidiCtrl_KeyOffNoteVelocity__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
// Entry: 801c8468
// Size: 96 bytes

void __MidiCtrl_KeyOffNoteVelocity__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
               (undefined4 param_1,undefined4 param_2,int *param_3)

{
  undefined *puVar1;
  
  puVar1 = (undefined *)*param_3;
  *param_3 = (int)(puVar1 + 1);
  *(undefined *)(param_3 + 9) = *puVar1;
  *param_3 = *param_3 + 1;
  KeyOffSet__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA(param_1,param_2);
  return;
}

