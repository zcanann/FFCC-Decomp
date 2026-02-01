// Function: DoUnmount
// Entry: 8019cce4
// Size: 156 bytes

void DoUnmount(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  
  uVar1 = OSDisableInterrupts();
  if ((&DAT_80327540)[param_1 * 0x44] != 0) {
    EXISetExiCallback(param_1,0);
    EXIDetach(param_1);
    OSCancelAlarm(&DAT_80327620 + param_1 * 0x110);
    (&DAT_80327540)[param_1 * 0x44] = 0;
    (&DAT_80327544)[param_1 * 0x44] = param_2;
    *(undefined4 *)(&DAT_80327564 + param_1 * 0x110) = 0;
  }
  OSRestoreInterrupts(uVar1);
  return;
}

