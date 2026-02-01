// Function: DVDGetCommandBlockStatus
// Entry: 8018aaac
// Size: 76 bytes

int DVDGetCommandBlockStatus(int param_1)

{
  int iVar1;
  
  OSDisableInterrupts();
  iVar1 = *(int *)(param_1 + 0xc);
  if (iVar1 == 3) {
    iVar1 = 1;
  }
  OSRestoreInterrupts();
  return iVar1;
}

