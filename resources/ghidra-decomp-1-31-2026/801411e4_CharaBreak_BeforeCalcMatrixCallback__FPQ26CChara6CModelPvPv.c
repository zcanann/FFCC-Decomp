// Function: CharaBreak_BeforeCalcMatrixCallback__FPQ26CChara6CModelPvPv
// Entry: 801411e4
// Size: 32 bytes

uint CharaBreak_BeforeCalcMatrixCallback__FPQ26CChara6CModelPvPv
               (uint param_1,int param_2,int param_3)

{
  uint uVar1;
  
  if (*(int *)(param_2 + 0x44) == 0) {
    return param_1;
  }
  uVar1 = countLeadingZeros(1 - (uint)*(byte *)(param_3 + 0x42));
  return uVar1 >> 5;
}

