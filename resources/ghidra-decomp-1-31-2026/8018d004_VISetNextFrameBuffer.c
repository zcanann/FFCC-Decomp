// Function: VISetNextFrameBuffer
// Entry: 8018d004
// Size: 108 bytes

void VISetNextFrameBuffer(undefined4 param_1)

{
  undefined4 uVar1;
  
  uVar1 = OSDisableInterrupts();
  DAT_8032f130 = 1;
  DAT_8030cc68 = param_1;
  setFbbRegs(&DAT_8030cc38,&DAT_8030cc6c,&DAT_8030cc70,&DAT_8030cc84,&DAT_8030cc88);
  OSRestoreInterrupts(uVar1);
  return;
}

