// Function: ICInvalidateRange
// Entry: 8017cfa4
// Size: 52 bytes

uint ICInvalidateRange(uint param_1,int param_2)

{
  uint uVar1;
  
  if (param_2 == 0) {
    return param_1;
  }
  uVar1 = param_2 + (param_1 & 0x1f) + 0x1f >> 5;
  do {
    instructionCacheBlockInvalidate(param_1);
    param_1 = param_1 + 0x20;
    uVar1 = uVar1 - 1;
  } while (uVar1 != 0);
  sync(0);
  instructionSynchronize();
  return param_1;
}

