// Function: AXInit
// Entry: 801915a4
// Size: 60 bytes

void AXInit(void)

{
  OSRegisterVersion(DAT_8032eb50);
  __AXAllocInit();
  __AXVPBInit();
  __AXSPBInit();
  __AXAuxInit();
  __AXClInit();
  __AXOutInit();
  return;
}

