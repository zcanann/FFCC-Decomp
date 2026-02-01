// Function: TRKGetNextEvent
// Entry: 801a9218
// Size: 180 bytes

undefined4 TRKGetNextEvent(undefined4 param_1)

{
  undefined4 uVar1;
  
  uVar1 = 0;
  TRKAcquireMutex(&DAT_80328720);
  if (0 < DAT_80328724) {
    TRK_memcpy(param_1,DAT_80328728 * 0xc + -0x7fcd78d4,0xc);
    DAT_80328728 = DAT_80328728 + 1;
    DAT_80328724 = DAT_80328724 + -1;
    if (DAT_80328728 == 2) {
      DAT_80328728 = 0;
    }
    uVar1 = 1;
  }
  TRKReleaseMutex(&DAT_80328720);
  return uVar1;
}

