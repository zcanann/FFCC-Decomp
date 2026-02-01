// Function: OSInitAlarm
// Entry: 8017c180
// Size: 76 bytes

void OSInitAlarm(void)

{
  code *pcVar1;
  
  pcVar1 = (code *)__OSGetExceptionHandler(8);
  if (pcVar1 != DecrementerExceptionHandler) {
    OSAlarm_8032ef60.tag = 0;
    OSAlarm_8032ef60.handler = (void *)0x0;
    __OSSetExceptionHandler(8);
  }
  return;
}

