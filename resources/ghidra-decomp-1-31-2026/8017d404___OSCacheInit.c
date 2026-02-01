// Function: __OSCacheInit
// Entry: 8017d404
// Size: 244 bytes

void __OSCacheInit(void)

{
  uint uVar1;
  undefined4 uVar2;
  
  uVar1 = PPCMfhid0();
  if ((uVar1 & 0x8000) == 0) {
    ICEnable();
    DBPrintf(s_L1_i_caches_initialized_80216b94);
  }
  uVar1 = PPCMfhid0();
  if ((uVar1 & 0x4000) == 0) {
    DCEnable();
    DBPrintf(s_L1_d_caches_initialized_80216bb0);
  }
  uVar1 = PPCMfl2cr();
  if ((uVar1 & 0x80000000) == 0) {
    uVar2 = PPCMfmsr();
    sync(0);
    PPCMtmsr(0x30);
    sync(0);
    sync(0);
    uVar1 = PPCMfl2cr();
    PPCMtl2cr(uVar1 & 0x7fffffff);
    sync(0);
    L2GlobalInvalidate();
    PPCMtmsr(uVar2);
    uVar1 = PPCMfl2cr();
    PPCMtl2cr(uVar1 & 0xffdfffff | 0x80000000);
    DBPrintf(s_L2_cache_initialized_80216bcc);
  }
  OSSetErrorHandler(1,DMAErrorHandler);
  DBPrintf(s_Locked_cache_machine_check_handl_80216be4);
  return;
}

