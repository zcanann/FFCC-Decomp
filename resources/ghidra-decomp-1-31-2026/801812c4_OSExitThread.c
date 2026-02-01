// Function: OSExitThread
// Entry: 801812c4
// Size: 228 bytes

void OSExitThread(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  
  uVar3 = OSDisableInterrupts();
  iVar1 = DAT_800000e4;
  OSClearContext(DAT_800000e4);
  if ((*(ushort *)(iVar1 + 0x2ca) & 1) == 0) {
    *(undefined2 *)(iVar1 + 0x2c8) = 8;
    *(undefined4 *)(iVar1 + 0x2d8) = param_1;
  }
  else {
    iVar4 = *(int *)(iVar1 + 0x2fc);
    iVar5 = *(int *)(iVar1 + 0x300);
    iVar2 = iVar5;
    if (iVar4 != 0) {
      *(int *)(iVar4 + 0x300) = iVar5;
      iVar2 = DAT_800000e0;
    }
    DAT_800000e0 = iVar2;
    if (iVar5 != 0) {
      *(int *)(iVar5 + 0x2fc) = iVar4;
      iVar4 = DAT_800000dc;
    }
    DAT_800000dc = iVar4;
    *(undefined2 *)(iVar1 + 0x2c8) = 0;
  }
  __OSUnlockAllMutex(iVar1);
  OSWakeupThread(iVar1 + 0x2e8);
  DAT_8032efd4 = 1;
  SelectThread(0);
  OSRestoreInterrupts(uVar3);
  return;
}

