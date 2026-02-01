// Function: __OSContextInit
// Entry: 8017dd20
// Size: 72 bytes

void __OSContextInit(void)

{
  __OSSetExceptionHandler(7,OSSwitchFPUContext);
  DAT_800000d8 = 0;
  DBPrintf(s_FPU_unavailable_handler_installe_80216dcc);
  return;
}

