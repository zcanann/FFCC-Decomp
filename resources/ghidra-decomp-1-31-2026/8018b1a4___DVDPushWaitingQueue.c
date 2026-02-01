// Function: __DVDPushWaitingQueue
// Entry: 8018b1a4
// Size: 104 bytes

undefined4 __DVDPushWaitingQueue(int param_1,undefined4 *param_2)

{
  OSDisableInterrupts();
  *(undefined4 **)(&DAT_8030cabc)[param_1 * 2] = param_2;
  param_2[1] = (&DAT_8030cabc)[param_1 * 2];
  *param_2 = &DAT_8030cab8 + param_1 * 2;
  (&DAT_8030cabc)[param_1 * 2] = param_2;
  OSRestoreInterrupts();
  return 1;
}

