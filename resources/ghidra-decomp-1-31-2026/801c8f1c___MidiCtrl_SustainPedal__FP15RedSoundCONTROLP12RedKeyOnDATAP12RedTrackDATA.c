// Function: __MidiCtrl_SustainPedal__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
// Entry: 801c8f1c
// Size: 212 bytes

void __MidiCtrl_SustainPedal__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
               (undefined4 param_1,undefined4 param_2,int *param_3)

{
  undefined4 *puVar1;
  
  if (*(char *)*param_3 == '\0') {
    param_3[0x3f] = param_3[0x3f] & 0xfffffffb;
    puVar1 = DAT_8032f444;
    do {
      if ((int *)*puVar1 == param_3) {
        puVar1[0x25] = puVar1[0x25] & 0xfffffffb;
      }
      puVar1 = puVar1 + 0x30;
    } while (puVar1 < DAT_8032f444 + 0xc00);
  }
  else {
    param_3[0x3f] = param_3[0x3f] | 4;
    puVar1 = DAT_8032f444;
    do {
      if ((int *)*puVar1 == param_3) {
        puVar1[0x25] = puVar1[0x25] | 4;
      }
      puVar1 = puVar1 + 0x30;
    } while (puVar1 < DAT_8032f444 + 0xc00);
  }
  *param_3 = *param_3 + 1;
  SetVoiceSwitch__FP12RedTrackDATAi(param_3,param_3[0x3f]);
  return;
}

