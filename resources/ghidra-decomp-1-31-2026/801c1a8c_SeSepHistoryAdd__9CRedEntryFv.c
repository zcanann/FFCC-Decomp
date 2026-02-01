// Function: SeSepHistoryAdd__9CRedEntryFv
// Entry: 801c1a8c
// Size: 68 bytes

void SeSepHistoryAdd__9CRedEntryFv(int param_1)

{
  uint uVar1;
  
  uVar1 = *(uint *)(param_1 + 4);
  do {
    if (*(int *)(uVar1 + 4) != 0) {
      *(int *)(uVar1 + 4) = *(int *)(uVar1 + 4) + 1;
    }
    uVar1 = uVar1 + 0x10;
  } while (uVar1 < *(int *)(param_1 + 4) + 0x1000U);
  return;
}

