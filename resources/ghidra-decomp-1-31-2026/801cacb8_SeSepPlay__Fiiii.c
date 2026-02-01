// Function: SeSepPlay__Fiiii
// Entry: 801cacb8
// Size: 192 bytes

undefined4
SeSepPlay__Fiiii(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  byte *pbVar2;
  
  iVar1 = SearchSeSepBank__9CRedEntryFi(&DAT_8032e154);
  if (iVar1 != 0) {
    pbVar2 = (byte *)(*(int *)(iVar1 + 8) + 0x10);
    if ((*(uint *)(*(int *)(iVar1 + 8) + 0xc) & 0x80000000) != 0) {
      *pbVar2 = *pbVar2 | 0x80;
    }
    iVar1 = _SePlayStart__FP9RedSeINFOiiii(pbVar2,param_1,param_2,param_3,param_4);
    if (iVar1 != 0) {
      SeSepHistoryManager__9CRedEntryFii(&DAT_8032e154,1,param_2);
      return param_2;
    }
  }
  return 0xffffffff;
}

