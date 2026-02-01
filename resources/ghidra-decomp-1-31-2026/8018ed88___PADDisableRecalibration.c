// Function: __PADDisableRecalibration
// Entry: 8018ed88
// Size: 124 bytes

bool __PADDisableRecalibration(int param_1)

{
  byte bVar1;
  
  OSDisableInterrupts();
  bVar1 = DAT_800030e3 & 0x40;
  DAT_800030e3 = DAT_800030e3 & 0xbf;
  if (param_1 != 0) {
    DAT_800030e3 = DAT_800030e3 | 0x40;
  }
  OSRestoreInterrupts();
  return bVar1 != 0;
}

