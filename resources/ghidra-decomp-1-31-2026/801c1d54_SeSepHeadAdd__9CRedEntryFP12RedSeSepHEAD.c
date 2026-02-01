// Function: SeSepHeadAdd__9CRedEntryFP12RedSeSepHEAD
// Entry: 801c1d54
// Size: 212 bytes

int SeSepHeadAdd__9CRedEntryFP12RedSeSepHEAD(int param_1,int param_2)

{
  int iVar1;
  undefined4 *puVar2;
  
  for (puVar2 = *(undefined4 **)(param_1 + 4);
      (puVar2[3] != 0 && (puVar2 < (undefined4 *)(*(int *)(param_1 + 4) + 0x1000U)));
      puVar2 = puVar2 + 4) {
  }
  if ((undefined4 *)(*(int *)(param_1 + 4) + 0x1000U) <= puVar2) {
    puVar2 = (undefined4 *)SeSepOldDelete__9CRedEntryFv(param_1);
  }
  iVar1 = 0;
  if ((puVar2 != (undefined4 *)0x0) && (puVar2 < (undefined4 *)(*(int *)(param_1 + 4) + 0x1000U))) {
    puVar2[2] = param_2;
    puVar2[3] = *(uint *)(param_2 + 0xc) & 0x7fffffff;
    *puVar2 = *(undefined4 *)(param_2 + 8);
    SeSepHistoryAdd__9CRedEntryFv(param_1);
    puVar2[1] = 1;
    iVar1 = param_2;
  }
  return iVar1;
}

