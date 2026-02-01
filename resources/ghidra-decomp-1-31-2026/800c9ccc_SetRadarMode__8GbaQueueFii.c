// Function: SetRadarMode__8GbaQueueFii
// Entry: 800c9ccc
// Size: 160 bytes

void SetRadarMode__8GbaQueueFii(GbaQueue *gbaQueue,int param_2,uint param_3)

{
  byte bVar1;
  byte bVar2;
  
  OSWaitSemaphore(gbaQueue->accessSemaphores + param_2);
  bVar1 = gbaQueue->field_0x2d41;
  bVar2 = (byte)(1 << param_2);
  gbaQueue->field_0x2d41 = bVar1 & ~bVar2 | (byte)((param_3 & 1) << param_2);
  if (bVar1 != gbaQueue->field_0x2d41) {
    gbaQueue->chgRadarMode = gbaQueue->chgRadarMode | bVar2;
  }
  OSSignalSemaphore(gbaQueue->accessSemaphores + param_2);
  return;
}

