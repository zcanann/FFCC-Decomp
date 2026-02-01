// Function: WaveHistoryAdd__9CRedEntryFi
// Entry: 801c0738
// Size: 72 bytes

void WaveHistoryAdd__9CRedEntryFi(int *param_1,int param_2)

{
  uint uVar1;
  
  uVar1 = *param_1 + 0x100;
  do {
    if (param_2 <= *(int *)(uVar1 + 4)) {
      *(int *)(uVar1 + 4) = *(int *)(uVar1 + 4) + 1;
    }
    uVar1 = uVar1 + 0x10;
  } while (uVar1 < *param_1 + 0x400U);
  return;
}

