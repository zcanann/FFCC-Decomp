// Function: DSPAssertTask
// Entry: 80197be4
// Size: 200 bytes

int * DSPAssertTask(int *param_1)

{
  ushort uVar1;
  undefined4 uVar2;
  
  uVar2 = OSDisableInterrupts();
  if (DAT_8032f2dc == param_1) {
    DAT_8032f2c8 = 1;
    DAT_8032f2cc = param_1;
    OSRestoreInterrupts(uVar2);
  }
  else if ((uint)param_1[1] < (uint)DAT_8032f2dc[1]) {
    DAT_8032f2c8 = 1;
    DAT_8032f2cc = param_1;
    if (*DAT_8032f2dc == 1) {
      OSDisableInterrupts();
      uVar1 = DAT_cc00500a;
      DAT_cc00500a = uVar1 & 0xff57 | 2;
      OSRestoreInterrupts();
    }
    OSRestoreInterrupts(uVar2);
  }
  else {
    OSRestoreInterrupts(uVar2);
    param_1 = (int *)0x0;
  }
  return param_1;
}

