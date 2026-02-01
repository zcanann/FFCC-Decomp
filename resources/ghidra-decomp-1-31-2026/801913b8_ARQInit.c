// Function: ARQInit
// Entry: 801913b8
// Size: 112 bytes

void ARQInit(void)

{
  if (DAT_8032f1e4 != 1) {
    OSRegisterVersion(DAT_8032eb48);
    DAT_8032f1c8 = 0;
    DAT_8032f1c0 = 0;
    DAT_8032f1e0 = 0x1000;
    ARRegisterDMACallback(__ARQInterruptServiceRoutine);
    DAT_8032f1d0 = 0;
    DAT_8032f1d4 = 0;
    DAT_8032f1d8 = 0;
    DAT_8032f1dc = 0;
    DAT_8032f1e4 = 1;
  }
  return;
}

