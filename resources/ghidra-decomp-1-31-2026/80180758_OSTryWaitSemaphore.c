// Function: OSTryWaitSemaphore
// Entry: 80180758
// Size: 84 bytes

int OSTryWaitSemaphore(OSSemaphore *semaphore)

{
  int iVar1;
  
  OSDisableInterrupts();
  iVar1 = semaphore->count;
  if (0 < iVar1) {
    semaphore->count = iVar1 + -1;
  }
  OSRestoreInterrupts();
  return iVar1;
}

