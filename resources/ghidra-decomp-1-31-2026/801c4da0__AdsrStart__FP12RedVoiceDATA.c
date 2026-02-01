// Function: _AdsrStart__FP12RedVoiceDATA
// Entry: 801c4da0
// Size: 188 bytes

void _AdsrStart__FP12RedVoiceDATA(int param_1)

{
  uint uVar1;
  uint uVar2;
  int *piVar3;
  uint uVar4;
  
  piVar3 = (int *)(param_1 + 0x5c);
  *(undefined4 *)(param_1 + 0x5c) = 0;
  uVar4 = (uint)*(byte *)(param_1 + 0x58);
  do {
    uVar2 = uVar4;
    uVar1 = (uint)*(ushort *)(param_1 + 0x50 + *piVar3 * 2);
    uVar4 = (uint)*(byte *)(param_1 + 0x50 + *piVar3 + 9);
    if (uVar1 != 0) break;
    *piVar3 = *piVar3 + 1;
  } while (*piVar3 < 3);
  *(uint *)(param_1 + 0x60) = uVar1;
  if (uVar4 != 0) {
    uVar4 = ((uVar4 + 1) * 0x100 + -1) * 0x1000;
  }
  if (uVar1 == 0) {
    *(uint *)(param_1 + 0xac) = uVar4;
  }
  else {
    if (uVar2 != 0) {
      uVar2 = ((uVar2 + 1) * 0x100 + -1) * 0x1000;
    }
    *(uint *)(param_1 + 0xac) = uVar2;
    *(int *)(param_1 + 100) = (int)((uVar4 | 0x800) - uVar2) / (int)uVar1;
  }
  return;
}

