// Function: __MidiCtrl_ReverbOn__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
// Entry: 801c9c30
// Size: 76 bytes

void __MidiCtrl_ReverbOn__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
               (undefined4 param_1,undefined4 param_2,int param_3)

{
  *(uint *)(param_3 + 0xfc) = *(uint *)(param_3 + 0xfc) | 0x3c00;
  SetVoiceSwitch__FP12RedTrackDATAi(param_3,*(undefined4 *)(param_3 + 0xfc));
  DAT_8032f4b4 = DAT_8032f4b4 | 2;
  return;
}

