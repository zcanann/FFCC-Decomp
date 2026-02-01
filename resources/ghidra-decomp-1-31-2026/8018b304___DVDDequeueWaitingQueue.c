// Function: __DVDDequeueWaitingQueue
// Entry: 8018b304
// Size: 96 bytes

undefined4 __DVDDequeueWaitingQueue(int *param_1)

{
  undefined4 uVar1;
  int *piVar2;
  int iVar3;
  
  OSDisableInterrupts();
  piVar2 = (int *)param_1[1];
  iVar3 = *param_1;
  if ((piVar2 == (int *)0x0) || (iVar3 == 0)) {
    OSRestoreInterrupts();
    uVar1 = 0;
  }
  else {
    *piVar2 = iVar3;
    *(int **)(iVar3 + 4) = piVar2;
    OSRestoreInterrupts();
    uVar1 = 1;
  }
  return uVar1;
}

