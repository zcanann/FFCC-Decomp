// Function: ClearAll__5CWindFv
// Entry: 800da05c
// Size: 88 bytes

void ClearAll__5CWindFv(int param_1)

{
  memset(param_1,0,0xc80);
  *(undefined4 *)(param_1 + 0xc80) = 1;
  memset(param_1 + 0xc84,0,0x7000);
  *(undefined4 *)(param_1 + 0x7c84) = 10000000;
  return;
}

