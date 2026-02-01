// Function: DVDGetDriveStatus
// Entry: 8018aaf8
// Size: 172 bytes

int DVDGetDriveStatus(void)

{
  undefined *puVar1;
  undefined4 uVar2;
  int iVar3;
  
  uVar2 = OSDisableInterrupts();
  puVar1 = DAT_8032f080;
  if (DAT_8032f098 == 0) {
    if (DAT_8032f090 == 0) {
      if (DAT_8032f080 == (undefined *)0x0) {
        iVar3 = 0;
      }
      else if (DAT_8032f080 == &DAT_8030ca60) {
        iVar3 = 0;
      }
      else {
        OSDisableInterrupts();
        iVar3 = *(int *)(puVar1 + 0xc);
        if (iVar3 == 3) {
          iVar3 = 1;
        }
        OSRestoreInterrupts();
      }
    }
    else {
      iVar3 = 8;
    }
  }
  else {
    iVar3 = -1;
  }
  OSRestoreInterrupts(uVar2);
  return iVar3;
}

