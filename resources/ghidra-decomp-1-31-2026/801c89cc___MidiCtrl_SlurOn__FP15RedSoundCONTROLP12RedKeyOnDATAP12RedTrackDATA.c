// Function: __MidiCtrl_SlurOn__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
// Entry: 801c89cc
// Size: 28 bytes

void __MidiCtrl_SlurOn__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
               (undefined4 param_1,undefined4 param_2,int param_3)

{
  *(uint *)(param_3 + 0x104) = *(uint *)(param_3 + 0x104) | 0x80000;
  *(uint *)(param_3 + 0x104) = *(uint *)(param_3 + 0x104) & 0xffefffff;
  return;
}

