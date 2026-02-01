// Function: MusicHistoryChoice__9CRedEntryFP14RedHistoryBANK
// Entry: 801c25a8
// Size: 104 bytes

void MusicHistoryChoice__9CRedEntryFP14RedHistoryBANK(int param_1,int param_2)

{
  uint uVar1;
  
  if (*(int *)(param_2 + 4) != 0) {
    uVar1 = *(uint *)(param_1 + 8);
    do {
      if ((*(int *)(uVar1 + 4) != 0) && (*(int *)(uVar1 + 4) < *(int *)(param_2 + 4))) {
        *(int *)(uVar1 + 4) = *(int *)(uVar1 + 4) + 1;
      }
      uVar1 = uVar1 + 0x10;
    } while (uVar1 < *(int *)(param_1 + 8) + 0x40U);
    *(undefined4 *)(param_2 + 4) = 1;
  }
  return;
}

