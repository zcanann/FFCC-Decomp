// Function: wakeup__FP7OSAlarmP9OSContext
// Entry: 80019694
// Size: 36 bytes

void wakeup__FP7OSAlarmP9OSContext(int param_1)

{
  OSResumeThread(*(undefined4 *)(param_1 + 0x28));
  return;
}

