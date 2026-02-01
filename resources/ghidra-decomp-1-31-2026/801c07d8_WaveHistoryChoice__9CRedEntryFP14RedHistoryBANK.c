// Function: WaveHistoryChoice__9CRedEntryFP14RedHistoryBANK
// Entry: 801c07d8
// Size: 104 bytes

void WaveHistoryChoice__9CRedEntryFP14RedHistoryBANK(uint *param_1,int param_2)

{
  uint uVar1;
  
  if (*(int *)(param_2 + 4) != 0) {
    uVar1 = *param_1;
    do {
      if ((*(int *)(uVar1 + 4) != 0) && (*(int *)(uVar1 + 4) < *(int *)(param_2 + 4))) {
        *(int *)(uVar1 + 4) = *(int *)(uVar1 + 4) + 1;
      }
      uVar1 = uVar1 + 0x10;
    } while (uVar1 < *param_1 + 0x400);
    *(undefined4 *)(param_2 + 4) = 1;
  }
  return;
}

