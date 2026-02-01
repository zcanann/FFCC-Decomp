// Function: GetScreenFadeExecutingBit__11CGraphicPcsFv
// Entry: 80046218
// Size: 160 bytes

uint GetScreenFadeExecutingBit__11CGraphicPcsFv(int param_1)

{
  uint uVar1;
  
  uVar1 = 0;
  if ((*(int *)(param_1 + 0x14) != 0) || (*(int *)(param_1 + 4) != 0)) {
    uVar1 = 1;
  }
  if ((*(int *)(param_1 + 0x40) != 0) || (*(int *)(param_1 + 0x30) != 0)) {
    uVar1 = uVar1 | 2;
  }
  if ((*(int *)(param_1 + 0x6c) != 0) || (*(int *)(param_1 + 0x5c) != 0)) {
    uVar1 = uVar1 | 4;
  }
  if ((*(int *)(param_1 + 0x98) != 0) || (*(int *)(param_1 + 0x88) != 0)) {
    uVar1 = uVar1 | 8;
  }
  return uVar1;
}

