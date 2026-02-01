// Function: OSGetSemaphoreCount
// Entry: 8018080c
// Size: 8 bytes

int OSGetSemaphoreCount(OSSemaphore *osSemaphore)

{
  return osSemaphore->count;
}

