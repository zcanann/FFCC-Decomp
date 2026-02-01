// Function: MusicHistoryDelete__9CRedEntryFi
// Entry: 801c255c
// Size: 76 bytes

void MusicHistoryDelete__9CRedEntryFi(int param_1,int param_2)

{
  uint uVar1;
  
  if (param_2 != 0) {
    uVar1 = *(uint *)(param_1 + 8);
    do {
      if (param_2 < *(int *)(uVar1 + 4)) {
        *(int *)(uVar1 + 4) = *(int *)(uVar1 + 4) + -1;
      }
      uVar1 = uVar1 + 0x10;
    } while (uVar1 < *(int *)(param_1 + 8) + 0x40U);
  }
  return;
}

