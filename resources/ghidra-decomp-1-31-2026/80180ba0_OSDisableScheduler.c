// Function: OSDisableScheduler
// Entry: 80180ba0
// Size: 64 bytes

int OSDisableScheduler(void)

{
  int iVar1;
  
  OSDisableInterrupts();
  iVar1 = DAT_8032efd8;
  DAT_8032efd8 = DAT_8032efd8 + 1;
  OSRestoreInterrupts();
  return iVar1;
}

