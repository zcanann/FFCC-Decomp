// Function: __DVDPopWaitingQueue
// Entry: 8018b20c
// Size: 160 bytes

int * __DVDPopWaitingQueue(void)

{
  undefined4 *puVar1;
  int *piVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  
  OSDisableInterrupts();
  iVar5 = 4;
  puVar1 = &DAT_8030cab8;
  iVar3 = 0;
  do {
    if ((undefined4 *)*puVar1 != puVar1) {
      OSRestoreInterrupts();
      OSDisableInterrupts();
      piVar2 = &DAT_8030cab8 + iVar3 * 2;
      piVar4 = (int *)*piVar2;
      *piVar2 = *piVar4;
      *(int **)(*piVar4 + 4) = piVar2;
      OSRestoreInterrupts();
      *piVar4 = 0;
      piVar4[1] = 0;
      return piVar4;
    }
    puVar1 = puVar1 + 2;
    iVar3 = iVar3 + 1;
    iVar5 = iVar5 + -1;
  } while (iVar5 != 0);
  OSRestoreInterrupts();
  return (int *)0x0;
}

