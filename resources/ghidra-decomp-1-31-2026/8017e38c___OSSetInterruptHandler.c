// Function: __OSSetInterruptHandler
// Entry: 8017e38c
// Size: 28 bytes

undefined4 __OSSetInterruptHandler(short param_1,undefined4 param_2)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  
  puVar2 = (undefined4 *)(OSAlarm_8032ef60.start._0_4_ + param_1 * 4);
  uVar1 = *puVar2;
  *puVar2 = param_2;
  return uVar1;
}

