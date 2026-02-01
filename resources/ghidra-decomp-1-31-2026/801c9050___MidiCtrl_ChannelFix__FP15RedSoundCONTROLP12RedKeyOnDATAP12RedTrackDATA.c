// Function: __MidiCtrl_ChannelFix__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
// Entry: 801c9050
// Size: 72 bytes

void __MidiCtrl_ChannelFix__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
               (undefined4 param_1,undefined4 param_2,undefined4 *param_3)

{
  char *pcVar1;
  
  pcVar1 = (char *)*param_3;
  *param_3 = pcVar1 + 1;
  if (*pcVar1 == '\0') {
    *(byte *)((int)param_3 + 0x26) = *(byte *)((int)param_3 + 0x26) & 0xfb;
  }
  else {
    *(byte *)((int)param_3 + 0x26) = *(byte *)((int)param_3 + 0x26) | 4;
  }
  return;
}

