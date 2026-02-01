// Function: __MidiCtrl_PortamentOff__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
// Entry: 801c89b8
// Size: 20 bytes

void __MidiCtrl_PortamentOff__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
               (undefined4 param_1,undefined4 param_2,int param_3)

{
  *(undefined4 *)(param_3 + 0x118) = 0;
  *(undefined4 *)(param_3 + 0x120) = 0xffffffff;
  return;
}

