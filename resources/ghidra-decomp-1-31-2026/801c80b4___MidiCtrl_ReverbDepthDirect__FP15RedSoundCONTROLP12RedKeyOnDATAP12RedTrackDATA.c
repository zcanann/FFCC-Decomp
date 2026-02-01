// Function: __MidiCtrl_ReverbDepthDirect__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
// Entry: 801c80b4
// Size: 164 bytes

void __MidiCtrl_ReverbDepthDirect__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
               (undefined4 param_1,undefined4 param_2,undefined4 *param_3)

{
  char *pcVar1;
  int *piVar2;
  
  piVar2 = param_3 + 0x1a;
  pcVar1 = (char *)*param_3;
  *param_3 = pcVar1 + 1;
  param_3[0x1a] = (int)*pcVar1;
  if (param_3[0x1a] != 0) {
    *piVar2 = *piVar2 + 1;
    *piVar2 = *piVar2 << 8;
    *piVar2 = *piVar2 + -1;
    *piVar2 = *piVar2 << 0xc;
  }
  param_3[0x1b] = 0;
  param_3[0x1c] = 0;
  SetVoiceAccess__FP12RedTrackDATAi(param_3,8);
  return;
}

