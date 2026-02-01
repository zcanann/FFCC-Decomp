// Function: __MidiCtrl_PortamentOn__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
// Entry: 801c8984
// Size: 52 bytes

void __MidiCtrl_PortamentOn__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
               (undefined4 param_1,undefined4 param_2,int param_3)

{
  undefined4 uVar1;
  
  uVar1 = DeltaTimeSumup__FPPUc(param_3);
  *(undefined4 *)(param_3 + 0x118) = uVar1;
  return;
}

