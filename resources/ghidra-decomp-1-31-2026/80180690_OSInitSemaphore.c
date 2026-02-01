// Function: OSInitSemaphore
// Entry: 80180690
// Size: 88 bytes

void OSInitSemaphore(OSSemaphore *osSemaphore,int count)

{
  undefined4 uVar1;
  
  uVar1 = OSDisableInterrupts();
  OSInitThreadQueue(&osSemaphore->queue);
  osSemaphore->count = count;
  OSRestoreInterrupts(uVar1);
  return;
}

