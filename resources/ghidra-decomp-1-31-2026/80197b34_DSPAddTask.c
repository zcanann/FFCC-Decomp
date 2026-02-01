// Function: DSPAddTask
// Entry: 80197b34
// Size: 112 bytes

undefined4 * DSPAddTask(undefined4 *param_1)

{
  undefined4 uVar1;
  
  uVar1 = OSDisableInterrupts();
  __DSP_insert_task(param_1);
  *param_1 = 0;
  param_1[2] = 1;
  OSRestoreInterrupts(uVar1);
  if (param_1 == DAT_8032f2d8) {
    __DSP_boot_task(param_1);
  }
  return param_1;
}

