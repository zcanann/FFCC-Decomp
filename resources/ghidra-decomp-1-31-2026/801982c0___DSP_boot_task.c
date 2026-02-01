// Function: __DSP_boot_task
// Entry: 801982c0
// Size: 396 bytes

void __DSP_boot_task(int param_1)

{
  int iVar1;
  
  do {
    iVar1 = DSPCheckMailFromDSP();
  } while (iVar1 == 0);
  DSPReadMailFromDSP();
  DSPSendMailToDSP(0x80f3a001);
  do {
    iVar1 = DSPCheckMailToDSP();
  } while (iVar1 != 0);
  DSPSendMailToDSP(*(undefined4 *)(param_1 + 0xc));
  do {
    iVar1 = DSPCheckMailToDSP();
  } while (iVar1 != 0);
  DSPSendMailToDSP(0x80f3c002);
  do {
    iVar1 = DSPCheckMailToDSP();
  } while (iVar1 != 0);
  DSPSendMailToDSP(*(uint *)(param_1 + 0x14) & 0xffff);
  do {
    iVar1 = DSPCheckMailToDSP();
  } while (iVar1 != 0);
  DSPSendMailToDSP(0x80f3a002);
  do {
    iVar1 = DSPCheckMailToDSP();
  } while (iVar1 != 0);
  DSPSendMailToDSP(*(undefined4 *)(param_1 + 0x10));
  do {
    iVar1 = DSPCheckMailToDSP();
  } while (iVar1 != 0);
  DSPSendMailToDSP(0x80f3b002);
  do {
    iVar1 = DSPCheckMailToDSP();
  } while (iVar1 != 0);
  DSPSendMailToDSP(0);
  do {
    iVar1 = DSPCheckMailToDSP();
  } while (iVar1 != 0);
  DSPSendMailToDSP(0x80f3d001);
  do {
    iVar1 = DSPCheckMailToDSP();
  } while (iVar1 != 0);
  DSPSendMailToDSP(*(undefined2 *)(param_1 + 0x24));
  do {
    iVar1 = DSPCheckMailToDSP();
  } while (iVar1 != 0);
  __DSP_debug_printf(s_DSP_is_booting_task__0x_08X_8021c038,param_1);
  __DSP_debug_printf(s___DSP_boot_task_____IRAM_MMEM_AD_8021c058,*(undefined4 *)(param_1 + 0xc));
  __DSP_debug_printf(s___DSP_boot_task_____IRAM_DSP_ADD_8021c088,*(undefined4 *)(param_1 + 0x14));
  __DSP_debug_printf(s___DSP_boot_task_____IRAM_LENGTH___8021c0b8,*(undefined4 *)(param_1 + 0x10));
  __DSP_debug_printf(s___DSP_boot_task_____DRAM_MMEM_AD_8021c0e8,*(undefined4 *)(param_1 + 0x1c));
  __DSP_debug_printf(s___DSP_boot_task_____Start_Vector_8021c118,*(undefined2 *)(param_1 + 0x24));
  return;
}

