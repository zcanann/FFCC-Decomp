// Function: _SetReverbDepth__FPi
// Entry: 801bcf88
// Size: 192 bytes

void _SetReverbDepth__FPi(uint *param_1)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  int *piVar4;
  uint uVar5;
  
  uVar2 = *param_1;
  uVar5 = param_1[1] & 0x7f;
  uVar3 = param_1[2];
  if (uVar5 != 0) {
    uVar5 = ((uVar5 + 1) * 0x100 + -1) * 0x1000;
  }
  *(uint *)(DAT_8032f474 + (uVar2 & 1) * 0xc) = uVar5;
  if ((uVar2 & 1) != 0) {
    iVar1 = (int)(uVar3 * 0x60) / 0x3c + ((int)(uVar3 * 0x60) >> 0x1f);
    iVar1 = iVar1 - (iVar1 >> 0x1f);
    if (iVar1 == 0) {
      iVar1 = 1;
    }
    piVar4 = *(int **)(DAT_8032f3f0 + 0xdbc);
    do {
      if (*piVar4 != 0) {
        piVar4[0x1b] = (int)((uVar5 | 0x800) - (piVar4[0x1a] & 0xfffff000U)) / iVar1;
        piVar4[0x1c] = iVar1;
      }
      piVar4 = piVar4 + 0x55;
    } while (piVar4 < (int *)(*(int *)(DAT_8032f3f0 + 0xdbc) + 0x2a80));
  }
  return;
}

