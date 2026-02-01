// Function: __MidiCtrl_Wave__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
// Entry: 801c8564
// Size: 184 bytes

void __MidiCtrl_Wave__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
               (undefined4 param_1,undefined4 param_2,undefined4 *param_3)

{
  byte *pbVar1;
  uint uVar2;
  
  param_3[7] = 0;
  param_3[0x47] = 0;
  pbVar1 = (byte *)*param_3;
  *param_3 = pbVar1 + 1;
  uVar2 = (uint)*pbVar1;
  if ((param_3[6] != 0) && ((int)uVar2 < *(int *)(param_3[6] + 8))) {
    param_3[7] = param_3[6] + *(int *)(param_3[6] + 0x20 + uVar2 * 4);
    param_3[0x47] = *(undefined4 *)(param_3[6] + 0x10);
    memset(param_3 + 0x35,0xffffffff,0xc);
  }
  *(undefined *)((int)param_3 + 0x14d) = 0x10;
  param_3[0x49] = uVar2;
  return;
}

