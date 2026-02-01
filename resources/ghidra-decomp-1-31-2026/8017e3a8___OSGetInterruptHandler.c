// Function: __OSGetInterruptHandler
// Entry: 8017e3a8
// Size: 20 bytes

undefined4 __OSGetInterruptHandler(short param_1)

{
  return *(undefined4 *)(OSAlarm_8032ef60.start._0_4_ + param_1 * 4);
}

