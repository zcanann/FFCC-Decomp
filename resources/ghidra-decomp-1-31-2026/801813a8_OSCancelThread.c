// Function: OSCancelThread
// Entry: 801813a8
// Size: 444 bytes

void OSCancelThread(int param_1)

{
  ushort uVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  uVar2 = OSDisableInterrupts();
  uVar1 = *(ushort *)(param_1 + 0x2c8);
  if (uVar1 == 3) {
LAB_801814b0:
    OSRestoreInterrupts(uVar2);
  }
  else {
    if (uVar1 < 3) {
      if (uVar1 == 1) {
        if (*(int *)(param_1 + 0x2cc) < 1) {
          UnsetRun(param_1);
        }
      }
      else {
        if (uVar1 == 0) goto LAB_801814b0;
        DAT_8032efd4 = 1;
      }
    }
    else {
      if (4 < uVar1) goto LAB_801814b0;
      iVar3 = *(int *)(param_1 + 0x2e0);
      iVar4 = *(int *)(param_1 + 0x2e4);
      if (iVar3 == 0) {
        *(int *)(*(int *)(param_1 + 0x2dc) + 4) = iVar4;
      }
      else {
        *(int *)(iVar3 + 0x2e4) = iVar4;
      }
      if (iVar4 == 0) {
        **(int **)(param_1 + 0x2dc) = iVar3;
      }
      else {
        *(int *)(iVar4 + 0x2e0) = iVar3;
      }
      *(undefined4 *)(param_1 + 0x2dc) = 0;
      if ((*(int *)(param_1 + 0x2cc) < 1) && (*(int *)(param_1 + 0x2f0) != 0)) {
        iVar3 = *(int *)(*(int *)(param_1 + 0x2f0) + 8);
        do {
          if ((0 < *(int *)(iVar3 + 0x2cc)) ||
             (iVar4 = __OSGetEffectivePriority(iVar3), *(int *)(iVar3 + 0x2d0) == iVar4)) break;
          iVar3 = SetEffectivePriority(iVar3);
        } while (iVar3 != 0);
      }
    }
    OSClearContext(param_1);
    if ((*(ushort *)(param_1 + 0x2ca) & 1) == 0) {
      *(undefined2 *)(param_1 + 0x2c8) = 8;
    }
    else {
      iVar3 = *(int *)(param_1 + 0x2fc);
      iVar5 = *(int *)(param_1 + 0x300);
      iVar4 = iVar5;
      if (iVar3 != 0) {
        *(int *)(iVar3 + 0x300) = iVar5;
        iVar4 = DAT_800000e0;
      }
      DAT_800000e0 = iVar4;
      if (iVar5 != 0) {
        *(int *)(iVar5 + 0x2fc) = iVar3;
        iVar3 = DAT_800000dc;
      }
      DAT_800000dc = iVar3;
      *(undefined2 *)(param_1 + 0x2c8) = 0;
    }
    __OSUnlockAllMutex(param_1);
    OSWakeupThread(param_1 + 0x2e8);
    if (DAT_8032efd4 != 0) {
      SelectThread(0);
    }
    OSRestoreInterrupts(uVar2);
  }
  return;
}

