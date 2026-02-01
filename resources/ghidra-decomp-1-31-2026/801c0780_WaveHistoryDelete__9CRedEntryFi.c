// Function: WaveHistoryDelete__9CRedEntryFi
// Entry: 801c0780
// Size: 88 bytes

void WaveHistoryDelete__9CRedEntryFi(uint *param_1,int param_2)

{
  uint uVar1;
  
  if (param_2 != 0) {
    uVar1 = *param_1;
    do {
      if ((*(int *)(uVar1 + 4) != 0) && (param_2 < *(int *)(uVar1 + 4))) {
        *(int *)(uVar1 + 4) = *(int *)(uVar1 + 4) + -1;
      }
      uVar1 = uVar1 + 0x10;
    } while (uVar1 < *param_1 + 0x400);
  }
  return;
}

