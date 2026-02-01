// Function: OSSignalSemaphore
// Entry: 801807ac
// Size: 96 bytes

int OSSignalSemaphore(OSSemaphore *semaphore)

{
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = OSDisableInterrupts();
  iVar2 = semaphore->count;
  semaphore->count = iVar2 + 1;
  OSWakeupThread(&semaphore->queue);
  OSRestoreInterrupts(uVar1);
  return iVar2;
}

