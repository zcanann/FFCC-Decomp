// Function: __MidiCtrl_ReverbOff__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
// Entry: 801c9c7c
// Size: 88 bytes

void __MidiCtrl_ReverbOff__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
               (undefined4 param_1,undefined4 param_2,int param_3)

{
  *(uint *)(param_3 + 0xfc) = *(uint *)(param_3 + 0xfc) & 0xffffcfff;
  *(uint *)(param_3 + 0xfc) = *(uint *)(param_3 + 0xfc) | 0xc00;
  SetVoiceSwitch__FP12RedTrackDATAi(param_3,*(undefined4 *)(param_3 + 0xfc));
  DAT_8032f4b4 = DAT_8032f4b4 | 2;
  return;
}

