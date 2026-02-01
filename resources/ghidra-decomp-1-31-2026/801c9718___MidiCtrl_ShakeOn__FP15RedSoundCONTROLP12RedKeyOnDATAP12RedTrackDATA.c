// Function: __MidiCtrl_ShakeOn__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
// Entry: 801c9718
// Size: 164 bytes

void __MidiCtrl_ShakeOn__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
               (undefined4 param_1,undefined4 param_2,int *param_3)

{
  uint uVar1;
  
  param_3[0x30] = (uint)*(byte *)*param_3 << 0xc;
  if (*(char *)(*param_3 + 1) == '\0') {
    uVar1 = 0x100;
  }
  else {
    uVar1 = (uint)*(byte *)(*param_3 + 1);
  }
  param_3[0x2e] = 0x100000 / uVar1;
  param_3[0x2d] = (int)(&PTR_SineSwing__Fi_8021e9d0)[*(byte *)(*param_3 + 2) & 0xf];
  *(undefined2 *)((int)param_3 + 0xd2) = 0;
  *(undefined2 *)(param_3 + 0x34) = 0;
  param_3[0x32] = 0;
  param_3[0x33] = 0;
  *param_3 = *param_3 + 3;
  return;
}

