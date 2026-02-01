// Function: __OSGetExceptionHandler
// Entry: 8017bfe4
// Size: 20 bytes

undefined4 __OSGetExceptionHandler(uint param_1)

{
  return *(undefined4 *)(DAT_8032ef44 + (param_1 & 0xff) * 4);
}

