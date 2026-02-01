// Function: __MidiCtrl_ADSR_DR__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
// Entry: 801c8cd8
// Size: 124 bytes

void __MidiCtrl_ADSR_DR__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
               (undefined4 param_1,undefined4 param_2,int param_3)

{
  undefined2 uVar1;
  int *piVar2;
  
  uVar1 = DeltaTimeSumup__FPPUc(param_3);
  *(undefined2 *)(param_3 + 0xd6) = uVar1;
  piVar2 = DAT_8032f444;
  do {
    if (*piVar2 == param_3) {
      *(undefined2 *)((int)piVar2 + 0x52) = uVar1;
      piVar2[0x24] = piVar2[0x24] | 0x3c0;
    }
    piVar2 = piVar2 + 0x30;
  } while (piVar2 < DAT_8032f444 + 0xc00);
  return;
}

