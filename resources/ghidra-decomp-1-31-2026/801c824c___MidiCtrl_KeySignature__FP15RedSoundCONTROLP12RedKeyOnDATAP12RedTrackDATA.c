// Function: __MidiCtrl_KeySignature__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
// Entry: 801c824c
// Size: 140 bytes

void __MidiCtrl_KeySignature__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
               (uint *param_1,undefined4 param_2,undefined4 *param_3)

{
  byte *pbVar1;
  uint uVar2;
  
  pbVar1 = (byte *)*param_3;
  *param_3 = pbVar1 + 1;
  uVar2 = *pbVar1 & 0x1f;
  param_1[0x120] = uVar2;
  param_1[2] = *(int *)(&DAT_8021dc20 + uVar2 * 4) + 0x8021dca0;
  if (DAT_8032f414 != 0) {
    uVar2 = *param_1;
    do {
      *(uint *)(uVar2 + 0x20) = param_1[2];
      uVar2 = uVar2 + 0x154;
    } while (uVar2 < *param_1 + (uint)*(byte *)((int)param_1 + 0x491) * 0x154);
  }
  return;
}

