// Function: isRideTarget__10CGPartyObjFv
// Entry: 8011f520
// Size: 84 bytes

undefined4 isRideTarget__10CGPartyObjFv(int param_1)

{
  bool bVar1;
  undefined4 uVar2;
  
  uVar2 = 0;
  bVar1 = false;
  if ((*(int *)(param_1 + 0x520) == 2) || (*(int *)(param_1 + 0x520) == 6)) {
    if (*(int *)(param_1 + 0x668) != 0) {
      bVar1 = true;
    }
  }
  if ((bVar1) &&
     ((int)((uint)*(byte *)(param_1 + 0x6b8) << 0x19 | (uint)(*(byte *)(param_1 + 0x6b8) >> 7)) < 0)
     ) {
    uVar2 = 1;
  }
  return uVar2;
}

