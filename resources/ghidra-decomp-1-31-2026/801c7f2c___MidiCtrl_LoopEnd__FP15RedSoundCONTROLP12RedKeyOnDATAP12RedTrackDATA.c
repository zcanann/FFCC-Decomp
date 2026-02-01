// Function: __MidiCtrl_LoopEnd__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
// Entry: 801c7f2c
// Size: 164 bytes

void __MidiCtrl_LoopEnd__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
               (undefined4 param_1,undefined4 param_2,undefined4 *param_3)

{
  byte *pbVar1;
  int iVar2;
  ushort uVar3;
  
  pbVar1 = (byte *)*param_3;
  *param_3 = pbVar1 + 1;
  uVar3 = (ushort)*pbVar1;
  if (uVar3 == 0) {
    uVar3 = 0x100;
  }
  iVar2 = *(short *)(param_3 + 0x4f) * 2 + 0x128;
  *(short *)((int)param_3 + iVar2) = *(short *)((int)param_3 + iVar2) + 1;
  if (*(ushort *)((int)param_3 + *(short *)(param_3 + 0x4f) * 2 + 0x128) == uVar3) {
    *(short *)(param_3 + 0x4f) = *(short *)(param_3 + 0x4f) + -1;
    *(ushort *)(param_3 + 0x4f) = *(ushort *)(param_3 + 0x4f) & 3;
  }
  else {
    *param_3 = param_3[*(short *)(param_3 + 0x4f) + 2];
    *(undefined2 *)(param_3 + 0x51) =
         *(undefined2 *)((int)param_3 + *(short *)(param_3 + 0x4f) * 2 + 0x130);
  }
  return;
}

