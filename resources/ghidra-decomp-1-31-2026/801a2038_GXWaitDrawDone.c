// Function: GXWaitDrawDone
// Entry: 801a2038
// Size: 76 bytes

void GXWaitDrawDone(void)

{
  undefined4 uVar1;
  
  uVar1 = OSDisableInterrupts();
  while (DAT_8032f338 == '\0') {
    OSSleepThread(&DAT_8032f33c);
  }
  OSRestoreInterrupts(uVar1);
  return;
}

