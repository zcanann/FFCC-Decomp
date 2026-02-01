// Function: GetPlayerHP__8GbaQueueFiPUc
// Entry: 800cddec
// Size: 332 bytes

uint GetPlayerHP__8GbaQueueFiPUc(GbaQueue *gbaQueue,int param_2,undefined *param_3)

{
  byte bVar1;
  byte bVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  char unaff_r26;
  char unaff_r27;
  GbaQueue *pGVar6;
  GbaQueue *osSemaphore;
  
  bVar2 = 0;
  bVar1 = 0;
  iVar5 = 0;
  pGVar6 = gbaQueue;
  osSemaphore = gbaQueue;
  do {
    OSWaitSemaphore(osSemaphore->accessSemaphores);
    if (iVar5 == param_2) {
      unaff_r26 = pGVar6->field_0x46b;
      unaff_r27 = pGVar6->field_0x7db;
    }
    if (pGVar6->field_0x46b != '\0') {
      bVar1 = bVar1 | (byte)(1 << iVar5);
    }
    if (pGVar6->field_0x7db != '\0') {
      bVar2 = bVar2 | (byte)(1 << iVar5);
    }
    OSSignalSemaphore(osSemaphore->accessSemaphores);
    iVar5 = iVar5 + 1;
    pGVar6 = (GbaQueue *)&pGVar6->field_0xdc;
    osSemaphore = (GbaQueue *)(osSemaphore->accessSemaphores + 1);
  } while (iVar5 < 4);
  uVar4 = (uint)((int)(char)bVar2 - (int)(char)bVar1 | (int)(char)bVar1 - (int)(char)bVar2) >> 0x1f;
  if (unaff_r26 != unaff_r27) {
    uVar4 = 1;
  }
  bVar2 = (byte)(1 << param_2);
  if (unaff_r26 != unaff_r27) {
    uVar4 = 1;
  }
  if ((gbaQueue->field_0x2d5a & bVar2) != (gbaQueue->field_0x2d59 & bVar2)) {
    uVar4 = 1;
  }
  *param_3 = 0x13;
  param_3[1] = bVar1;
  param_3[2] = unaff_r26;
  uVar3 = (int)(char)gbaQueue->field_0x2d5a & 1 << param_2;
  param_3[3] = (byte)((byte)(-uVar3 >> 0x18) | (byte)(uVar3 >> 0x18)) >> 7;
  return uVar4;
}

