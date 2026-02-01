// Function: __init_hardware
// Entry: 80003400
// Size: 36 bytes

void __init_hardware(void)

{
  __OSPSInit();
  __OSFPRInit();
  __OSCacheInit();
  return;
}

