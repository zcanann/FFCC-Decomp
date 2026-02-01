// Function: __AXOutQuit
// Entry: 80192d40
// Size: 88 bytes

void __AXOutQuit(void)

{
  undefined4 uVar1;
  
  uVar1 = OSDisableInterrupts();
  DAT_8032f250 = 0;
  DSPCancelTask(&DAT_80310860);
  OSSleepThread(&DAT_8032f260);
  AIStopDMA();
  OSRestoreInterrupts(uVar1);
  return;
}

