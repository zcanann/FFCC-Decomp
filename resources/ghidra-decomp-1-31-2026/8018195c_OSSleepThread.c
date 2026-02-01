// Function: OSSleepThread
// Entry: 8018195c
// Size: 236 bytes

void OSSleepThread(int *param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  
  uVar2 = OSDisableInterrupts();
  iVar1 = DAT_800000e4;
  *(undefined2 *)(DAT_800000e4 + 0x2c8) = 4;
  *(int **)(iVar1 + 0x2dc) = param_1;
  for (iVar4 = *param_1; (iVar4 != 0 && (*(int *)(iVar4 + 0x2d0) <= *(int *)(iVar1 + 0x2d0)));
      iVar4 = *(int *)(iVar4 + 0x2e0)) {
  }
  if (iVar4 == 0) {
    iVar4 = param_1[1];
    if (iVar4 == 0) {
      *param_1 = iVar1;
    }
    else {
      *(int *)(iVar4 + 0x2e0) = iVar1;
    }
    *(int *)(iVar1 + 0x2e4) = iVar4;
    *(undefined4 *)(iVar1 + 0x2e0) = 0;
    param_1[1] = iVar1;
  }
  else {
    *(int *)(iVar1 + 0x2e0) = iVar4;
    iVar3 = *(int *)(iVar4 + 0x2e4);
    *(int *)(iVar4 + 0x2e4) = iVar1;
    *(int *)(iVar1 + 0x2e4) = iVar3;
    if (iVar3 == 0) {
      *param_1 = iVar1;
    }
    else {
      *(int *)(iVar3 + 0x2e0) = iVar1;
    }
  }
  DAT_8032efd4 = 1;
  SelectThread(0);
  OSRestoreInterrupts(uVar2);
  return;
}

