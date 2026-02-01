// Function: __OSSetExceptionHandler
// Entry: 8017bfc8
// Size: 28 bytes

undefined4 __OSSetExceptionHandler(uint param_1,undefined4 param_2)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  
  puVar2 = (undefined4 *)(DAT_8032ef44 + (param_1 & 0xff) * 4);
  uVar1 = *puVar2;
  *puVar2 = param_2;
  return uVar1;
}

