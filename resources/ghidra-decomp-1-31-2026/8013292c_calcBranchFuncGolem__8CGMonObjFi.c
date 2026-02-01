// Function: calcBranchFuncGolem__8CGMonObjFi
// Entry: 8013292c
// Size: 64 bytes

uint calcBranchFuncGolem__8CGMonObjFi(int param_1)

{
  uint uVar1;
  
  if (*(int *)(param_1 + 0x6d0) == 1) {
    return 2;
  }
  uVar1 = countLeadingZeros((uint)(*(ushort *)(*(int *)(param_1 + 0x58) + 0x1a) >> 1 <=
                                  *(ushort *)(*(int *)(param_1 + 0x58) + 0x1c)));
  return uVar1 >> 5;
}

