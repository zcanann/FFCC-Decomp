// Function: OSEnableScheduler
// Entry: 80180be0
// Size: 64 bytes

int OSEnableScheduler(void)

{
  int iVar1;
  
  OSDisableInterrupts();
  iVar1 = DAT_8032efd8;
  DAT_8032efd8 = DAT_8032efd8 + -1;
  OSRestoreInterrupts();
  return iVar1;
}

