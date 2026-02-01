// Function: WaveOldClear__9CRedEntryFii
// Entry: 801c0ad4
// Size: 172 bytes

int WaveOldClear__9CRedEntryFii(int *param_1,int param_2,int param_3)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  
  uVar2 = 0;
  iVar1 = GetABufferAddress__10CRedMemoryFv(&DAT_8032f480);
  iVar3 = 0;
  uVar5 = *param_1 + 0x100;
  do {
    if (((iVar3 < *(int *)(uVar5 + 4)) &&
        (iVar4 = *(int *)(*(int *)(uVar5 + 8) + 0x10), param_2 + iVar1 <= iVar4)) &&
       (iVar4 < param_3 + iVar1)) {
      iVar3 = *(int *)(uVar5 + 4);
      uVar2 = uVar5;
    }
    uVar5 = uVar5 + 0x10;
  } while (uVar5 < *param_1 + 0x400U);
  if (iVar3 != 0) {
    WaveDelete__9CRedEntryFP14RedHistoryBANK(param_1,uVar2);
  }
  return iVar3;
}

