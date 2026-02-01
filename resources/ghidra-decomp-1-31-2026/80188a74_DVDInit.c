// Function: DVDInit
// Entry: 80188a74
// Size: 204 bytes

void DVDInit(void)

{
  if (DAT_8032f0c0 == 0) {
    OSRegisterVersion(DAT_8032eae0);
    DAT_8032f0c0 = 1;
    __DVDFSInit();
    __DVDClearWaitingQueue();
    __DVDInitWA();
    DAT_8032f088 = -0x80000000;
    DAT_8032f084 = 0x80000000;
    __OSSetInterruptHandler(0x15,__DVDInterruptHandler);
    __OSUnmaskInterrupts(0x400);
    OSInitThreadQueue(&DAT_8032f078);
    DAT_cc006000 = 0x2a;
    DAT_cc006004 = 0;
    if (*(int *)(DAT_8032f088 + 0x20) == -0x1adf83de) {
      OSReport(s_load_fst_802175f0);
      __fstLoad();
    }
    else if (*(int *)(DAT_8032f088 + 0x20) != 0xd15ea5e) {
      DAT_8032f0bc = 1;
    }
  }
  return;
}

