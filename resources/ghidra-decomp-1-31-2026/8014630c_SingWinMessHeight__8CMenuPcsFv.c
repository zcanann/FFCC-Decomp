// Function: SingWinMessHeight__8CMenuPcsFv
// Entry: 8014630c
// Size: 88 bytes

int SingWinMessHeight__8CMenuPcsFv(void)

{
  uint uVar1;
  
  uVar1 = (uint)(FLOAT_80332960 * FLOAT_8032ea78);
  if (FLOAT_8033294c <
      FLOAT_80332960 * FLOAT_8032ea78 -
      (float)((double)CONCAT44(0x43300000,uVar1 ^ 0x80000000) - DOUBLE_80332938)) {
    uVar1 = uVar1 + 1;
  }
  return uVar1 + 3;
}

