// Function: ARGetDMAStatus
// Entry: 8018f754
// Size: 60 bytes

ushort ARGetDMAStatus(void)

{
  ushort uVar1;
  
  OSDisableInterrupts();
  uVar1 = DAT_cc00500a;
  OSRestoreInterrupts();
  return uVar1 & 0x200;
}

