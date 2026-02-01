// Function: ClrArtifactFlg__8GbaQueueFi
// Entry: 800ca7a8
// Size: 104 bytes

void ClrArtifactFlg__8GbaQueueFi(GbaQueue *gbaQueue,int param_2)

{
  OSWaitSemaphore(gbaQueue->accessSemaphores + param_2);
  gbaQueue->artifactFlg = gbaQueue->artifactFlg & ~(byte)(1 << param_2);
  OSSignalSemaphore(gbaQueue->accessSemaphores + param_2);
  return;
}

