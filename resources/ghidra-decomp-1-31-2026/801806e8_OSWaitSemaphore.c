// Function: OSWaitSemaphore
// Entry: 801806e8
// Size: 112 bytes

int OSWaitSemaphore(OSSemaphore *osSemaphore)

{
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = OSDisableInterrupts();
  while (iVar2 = osSemaphore->count, iVar2 < 1) {
    OSSleepThread(&osSemaphore->queue);
  }
  osSemaphore->count = osSemaphore->count + -1;
  OSRestoreInterrupts(uVar1);
  return iVar2;
}

