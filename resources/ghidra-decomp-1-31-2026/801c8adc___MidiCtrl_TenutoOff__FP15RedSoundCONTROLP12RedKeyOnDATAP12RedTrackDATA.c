// Function: __MidiCtrl_TenutoOff__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
// Entry: 801c8adc
// Size: 16 bytes

void __MidiCtrl_TenutoOff__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
               (undefined4 param_1,undefined4 param_2,int param_3)

{
  *(uint *)(param_3 + 0x104) = *(uint *)(param_3 + 0x104) & 0xffdfffff;
  return;
}

