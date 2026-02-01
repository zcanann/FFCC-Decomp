// Function: __DVDCheckWaitingQueue
// Entry: 8018b2ac
// Size: 88 bytes

undefined4 __DVDCheckWaitingQueue(void)

{
  undefined4 *puVar1;
  int iVar2;
  
  OSDisableInterrupts();
  iVar2 = 4;
  puVar1 = &DAT_8030cab8;
  do {
    if ((undefined4 *)*puVar1 != puVar1) {
      OSRestoreInterrupts();
      return 1;
    }
    puVar1 = puVar1 + 2;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  OSRestoreInterrupts();
  return 0;
}

