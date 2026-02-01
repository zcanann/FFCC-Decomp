// Function: __AXOutAiCallback
// Entry: 8019283c
// Size: 104 bytes

void __AXOutAiCallback(void)

{
  undefined8 uVar1;
  
  uVar1 = CONCAT44(DAT_8032f248,DAT_8032f24c);
  if (DAT_8032f244 == 0) {
    uVar1 = OSGetTime();
  }
  DAT_8032f248 = (undefined4)((ulonglong)uVar1 >> 0x20);
  DAT_8032f24c = (undefined4)uVar1;
  if (DAT_8032f244 == 1) {
    DAT_8032f244 = 0;
    __AXOutNewFrame(0);
  }
  else {
    DAT_8032f244 = 2;
    DSPAssertTask(&DAT_80310860);
  }
  return;
}

