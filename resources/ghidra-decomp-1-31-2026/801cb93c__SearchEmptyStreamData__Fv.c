// Function: _SearchEmptyStreamData__Fv
// Entry: 801cb93c
// Size: 68 bytes

uint _SearchEmptyStreamData__Fv(void)

{
  uint uVar1;
  
  uVar1 = DAT_8032f438;
  do {
    if (*(int *)(uVar1 + 0x10c) == 0) {
      return uVar1;
    }
    uVar1 = uVar1 + 0x130;
  } while (uVar1 < DAT_8032f438 + 0x4c0);
  return 0;
}

