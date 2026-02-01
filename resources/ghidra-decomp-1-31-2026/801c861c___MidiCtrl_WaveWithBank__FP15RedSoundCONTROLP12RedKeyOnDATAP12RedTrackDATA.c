// Function: __MidiCtrl_WaveWithBank__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
// Entry: 801c861c
// Size: 168 bytes

void __MidiCtrl_WaveWithBank__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
               (undefined4 param_1,undefined4 param_2,undefined4 *param_3)

{
  undefined uVar1;
  int iVar2;
  byte *pbVar3;
  undefined *puVar4;
  uint uVar5;
  
  puVar4 = (undefined *)*param_3;
  *param_3 = puVar4 + 1;
  pbVar3 = (byte *)*param_3;
  uVar1 = *puVar4;
  *param_3 = pbVar3 + 1;
  uVar5 = (uint)*pbVar3;
  param_3[7] = 0;
  param_3[0x47] = 0;
  iVar2 = GetWaveBank__9CRedEntryFi(&DAT_8032e154,uVar1);
  if (iVar2 != 0) {
    iVar2 = *(int *)(iVar2 + 8);
    param_3[7] = iVar2 + *(int *)(iVar2 + 0x20 + uVar5 * 4);
    param_3[0x47] = *(undefined4 *)(iVar2 + 0x10);
    memset(param_3 + 0x35,0xffffffff,0xc);
  }
  *(undefined *)((int)param_3 + 0x14d) = uVar1;
  param_3[0x49] = uVar5;
  return;
}

