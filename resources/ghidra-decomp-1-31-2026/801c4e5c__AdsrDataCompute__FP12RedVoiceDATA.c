// Function: _AdsrDataCompute__FP12RedVoiceDATA
// Entry: 801c4e5c
// Size: 164 bytes

void _AdsrDataCompute__FP12RedVoiceDATA(int param_1)

{
  uint unaff_r27;
  uint uVar1;
  int *piVar2;
  uint uVar3;
  uint uVar4;
  
  piVar2 = (int *)(param_1 + 0x5c);
  uVar1 = 0;
  uVar4 = *(uint *)(param_1 + 0xac);
  while (uVar3 = uVar4, *piVar2 < 3) {
    uVar3 = (uint)*(byte *)(param_1 + 0x50 + *piVar2 + 9);
    uVar1 = (uint)*(ushort *)(param_1 + 0x50 + *piVar2 * 2);
    if (uVar3 != 0) {
      uVar3 = ((uVar3 + 1) * 0x100 + -1) * 0x1000;
    }
    unaff_r27 = uVar4;
    if (uVar1 != 0) break;
    *piVar2 = *piVar2 + 1;
    uVar4 = uVar3;
  }
  *(uint *)(param_1 + 0x60) = uVar1;
  if (uVar1 == 0) {
    *(uint *)(param_1 + 0xac) = uVar3;
  }
  else {
    *(uint *)(param_1 + 0xac) = unaff_r27;
    *(int *)(param_1 + 100) = (int)((uVar3 | 0x800) - unaff_r27) / (int)uVar1;
  }
  return;
}

