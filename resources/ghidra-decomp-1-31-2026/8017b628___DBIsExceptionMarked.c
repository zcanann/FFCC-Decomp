// Function: __DBIsExceptionMarked
// Entry: 8017b628
// Size: 28 bytes

uint __DBIsExceptionMarked(uint param_1)

{
  return *(uint *)(DAT_8032ef18 + 4) & 1 << (param_1 & 0xff);
}

