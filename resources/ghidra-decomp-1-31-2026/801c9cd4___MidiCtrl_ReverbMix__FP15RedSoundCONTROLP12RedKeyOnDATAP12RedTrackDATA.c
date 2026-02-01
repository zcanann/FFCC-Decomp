// Function: __MidiCtrl_ReverbMix__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
// Entry: 801c9cd4
// Size: 232 bytes

void __MidiCtrl_ReverbMix__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
               (undefined4 param_1,undefined4 param_2,int *param_3)

{
  byte bVar1;
  
  param_3[0x3f] = param_3[0x3f] & 0xffffc3ff;
  bVar1 = *(byte *)*param_3;
  if (bVar1 == 2) {
    param_3[0x3f] = param_3[0x3f] | 0x1000;
LAB_801c9d30:
    param_3[0x3f] = param_3[0x3f] | 0x400;
  }
  else {
    if ((1 < bVar1) || (bVar1 == 0)) goto LAB_801c9d30;
    param_3[0x3f] = param_3[0x3f] | 0x1000;
  }
  bVar1 = *(byte *)(*param_3 + 1);
  if (bVar1 == 2) {
    param_3[0x3f] = param_3[0x3f] | 0x2000;
  }
  else if ((bVar1 < 2) && (bVar1 != 0)) {
    param_3[0x3f] = param_3[0x3f] | 0x2000;
    goto LAB_801c9d84;
  }
  param_3[0x3f] = param_3[0x3f] | 0x800;
LAB_801c9d84:
  *param_3 = *param_3 + 2;
  SetVoiceSwitch__FP12RedTrackDATAi(param_3,param_3[0x3f]);
  DAT_8032f4b4 = DAT_8032f4b4 | 2;
  return;
}

