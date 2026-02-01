// Function: __AXOutInitDSP
// Entry: 80192934
// Size: 204 bytes

void __AXOutInitDSP(void)

{
  int iVar1;
  
  DAT_8031086c = &DAT_80219840;
  DAT_80310870 = (uint)DAT_8032eb58;
  DAT_80310874 = 0;
  DAT_80310878 = &DAT_803108b0;
  DAT_8031087c = 0x2000;
  DAT_80310880 = 0;
  DAT_80310884 = 0x10;
  DAT_80310886 = 0x30;
  DAT_80310888 = __AXDSPInitCallback;
  DAT_8031088c = __AXDSPResumeCallback;
  DAT_80310890 = __AXDSPDoneCallback;
  DAT_80310894 = 0;
  DAT_80310864 = 0;
  DAT_8032f254 = 0;
  DAT_8032f258 = 0;
  OSInitThreadQueue(&DAT_8032f260);
  iVar1 = DSPCheckInit();
  if (iVar1 == 0) {
    DSPInit();
  }
  DSPAddTask(&DAT_80310860);
  do {
  } while (DAT_8032f254 == 0);
  return;
}

