// Function: OSWakeupThread
// Entry: 80181a48
// Size: 260 bytes

void OSWakeupThread(int *param_1)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  
  uVar1 = OSDisableInterrupts();
  while (iVar3 = *param_1, iVar3 != 0) {
    iVar2 = *(int *)(iVar3 + 0x2e0);
    if (iVar2 == 0) {
      param_1[1] = 0;
    }
    else {
      *(undefined4 *)(iVar2 + 0x2e4) = 0;
    }
    *param_1 = iVar2;
    *(undefined2 *)(iVar3 + 0x2c8) = 1;
    if (*(int *)(iVar3 + 0x2cc) < 1) {
      *(int *)(iVar3 + 0x2dc) = *(int *)(iVar3 + 0x2d0) * 8 + -0x7fcf4368;
      iVar2 = (*(int **)(iVar3 + 0x2dc))[1];
      if (iVar2 == 0) {
        **(int **)(iVar3 + 0x2dc) = iVar3;
      }
      else {
        *(int *)(iVar2 + 0x2e0) = iVar3;
      }
      *(int *)(iVar3 + 0x2e4) = iVar2;
      *(undefined4 *)(iVar3 + 0x2e0) = 0;
      *(int *)(*(int *)(iVar3 + 0x2dc) + 4) = iVar3;
      DAT_8032efd0 = DAT_8032efd0 | 1 << 0x1f - *(int *)(iVar3 + 0x2d0);
      DAT_8032efd4 = 1;
    }
  }
  if (DAT_8032efd4 != 0) {
    SelectThread(0);
  }
  OSRestoreInterrupts(uVar1);
  return;
}

