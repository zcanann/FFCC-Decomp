// Function: DVDCancel
// Entry: 8018ae80
// Size: 172 bytes

undefined4 DVDCancel(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = DVDCancelAsync(param_1,cbForCancelSync);
  if (iVar1 == 0) {
    uVar2 = 0xffffffff;
  }
  else {
    uVar2 = OSDisableInterrupts();
    while (((iVar1 = *(int *)(param_1 + 0xc), 1 < iVar1 + 1U && (iVar1 != 10)) &&
           ((iVar1 != 3 ||
            (((iVar1 = *(int *)(param_1 + 8), 1 < iVar1 - 4U && (iVar1 != 0xd)) && (iVar1 != 0xf))))
           ))) {
      OSSleepThread(&DAT_8032f078);
    }
    OSRestoreInterrupts(uVar2);
    uVar2 = 0;
  }
  return uVar2;
}

