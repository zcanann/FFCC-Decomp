// Function: OSSuspendThread
// Entry: 801817ec
// Size: 368 bytes

int OSSuspendThread(int param_1)

{
  ushort uVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  uVar2 = OSDisableInterrupts();
  iVar3 = *(int *)(param_1 + 0x2cc);
  *(int *)(param_1 + 0x2cc) = iVar3 + 1;
  if (iVar3 == 0) {
    uVar1 = *(ushort *)(param_1 + 0x2c8);
    if (uVar1 != 3) {
      if (uVar1 < 3) {
        if (uVar1 == 1) {
          UnsetRun(param_1);
        }
        else if (uVar1 != 0) {
          DAT_8032efd4 = 1;
          *(undefined2 *)(param_1 + 0x2c8) = 1;
        }
      }
      else if (uVar1 < 5) {
        iVar4 = *(int *)(param_1 + 0x2e0);
        iVar5 = *(int *)(param_1 + 0x2e4);
        if (iVar4 == 0) {
          *(int *)(*(int *)(param_1 + 0x2dc) + 4) = iVar5;
        }
        else {
          *(int *)(iVar4 + 0x2e4) = iVar5;
        }
        if (iVar5 == 0) {
          **(int **)(param_1 + 0x2dc) = iVar4;
        }
        else {
          *(int *)(iVar5 + 0x2e0) = iVar4;
        }
        *(undefined4 *)(param_1 + 0x2d0) = 0x20;
        iVar4 = (*(int **)(param_1 + 0x2dc))[1];
        if (iVar4 == 0) {
          **(int **)(param_1 + 0x2dc) = param_1;
        }
        else {
          *(int *)(iVar4 + 0x2e0) = param_1;
        }
        *(int *)(param_1 + 0x2e4) = iVar4;
        *(undefined4 *)(param_1 + 0x2e0) = 0;
        *(int *)(*(int *)(param_1 + 0x2dc) + 4) = param_1;
        if (*(int *)(param_1 + 0x2f0) != 0) {
          iVar4 = *(int *)(*(int *)(param_1 + 0x2f0) + 8);
          do {
            if ((0 < *(int *)(iVar4 + 0x2cc)) ||
               (iVar5 = __OSGetEffectivePriority(iVar4), *(int *)(iVar4 + 0x2d0) == iVar5)) break;
            iVar4 = SetEffectivePriority(iVar4);
          } while (iVar4 != 0);
        }
      }
    }
    if (DAT_8032efd4 != 0) {
      SelectThread(0);
    }
  }
  OSRestoreInterrupts(uVar2);
  return iVar3;
}

