// Function: __MidiCtrl_ExpressionDirect__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
// Entry: 801c87b4
// Size: 76 bytes

void __MidiCtrl_ExpressionDirect__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
               (undefined4 param_1,undefined4 param_2,undefined4 *param_3)

{
  char *pcVar1;
  
  pcVar1 = (char *)*param_3;
  *param_3 = pcVar1 + 1;
  param_3[0xd] = (int)*pcVar1 << 0xc;
  param_3[0xe] = 0;
  param_3[0xf] = 0;
  DAT_8032f4b4 = DAT_8032f4b4 | 2;
  return;
}

