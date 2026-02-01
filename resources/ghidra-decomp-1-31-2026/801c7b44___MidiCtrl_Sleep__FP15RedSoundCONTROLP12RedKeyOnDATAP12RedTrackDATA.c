// Function: __MidiCtrl_Sleep__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
// Entry: 801c7b44
// Size: 136 bytes

void __MidiCtrl_Sleep__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
               (int *param_1,undefined4 param_2)

{
  int *piVar1;
  
  if ((DAT_8032f424 == 1) && (param_1 == DAT_8032f3f0)) {
    piVar1 = (int *)*param_1;
    do {
      if (*piVar1 != 0) {
        __MidiCtrl_Stop__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA(param_1,param_2,piVar1);
      }
      piVar1 = piVar1 + 0x55;
    } while (piVar1 < (int *)(*param_1 + (uint)*(byte *)((int)param_1 + 0x491) * 0x154));
  }
  return;
}

