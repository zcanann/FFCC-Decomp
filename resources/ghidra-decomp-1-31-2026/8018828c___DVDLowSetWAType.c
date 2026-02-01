// Function: __DVDLowSetWAType
// Entry: 8018828c
// Size: 68 bytes

void __DVDLowSetWAType(undefined4 param_1,undefined4 param_2)

{
  OSDisableInterrupts();
  DAT_8032f03c = param_1;
  DAT_8032f040 = param_2;
  OSRestoreInterrupts();
  return;
}

