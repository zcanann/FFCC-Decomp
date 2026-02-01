// Function: __AXDSPResumeCallback
// Entry: 801928b0
// Size: 88 bytes

void __AXDSPResumeCallback(void)

{
  int extraout_r4;
  
  if (DAT_8032f244 == 2) {
    DAT_8032f244 = 0;
    OSGetTime();
    __AXOutNewFrame((uint)(extraout_r4 - DAT_8032f24c) >> 2,extraout_r4,DAT_8032f248);
  }
  else {
    DAT_8032f244 = 1;
  }
  return;
}

