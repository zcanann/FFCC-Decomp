// Function: FUN_801b52a0
// Entry: 801b52a0
// Size: 36 bytes

uint FUN_801b52a0(uint param_1)

{
  if (param_1 == 0xffffffff) {
    return 0xffffffff;
  }
  return (uint)(byte)(&DAT_8021d4c0)[param_1 & 0xff];
}

