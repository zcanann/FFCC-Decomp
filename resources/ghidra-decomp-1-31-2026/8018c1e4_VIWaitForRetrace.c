// Function: VIWaitForRetrace
// Entry: 8018c1e4
// Size: 84 bytes

void VIWaitForRetrace(void)

{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = OSDisableInterrupts();
  iVar1 = DAT_8032f0e4;
  do {
    OSSleepThread(&DAT_8032f0ec);
  } while (iVar1 == DAT_8032f0e4);
  OSRestoreInterrupts(uVar2);
  return;
}

