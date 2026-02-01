// Function: VIGetDTVStatus
// Entry: 8018d25c
// Size: 60 bytes

ushort VIGetDTVStatus(void)

{
  ushort uVar1;
  
  OSDisableInterrupts();
  uVar1 = DAT_cc00206e;
  OSRestoreInterrupts();
  return uVar1 & 1;
}

