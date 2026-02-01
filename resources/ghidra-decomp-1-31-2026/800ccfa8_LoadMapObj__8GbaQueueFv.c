// Function: LoadMapObj__8GbaQueueFv
// Entry: 800ccfa8
// Size: 548 bytes

void LoadMapObj__8GbaQueueFv(GbaQueue *gbaQueue)

{
  char cVar1;
  char cVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  longlong lVar7;
  uint uVar8;
  GbaQueue *pGVar9;
  int iVar10;
  char *pcVar11;
  byte local_1b8 [4];
  uint local_1b4;
  char acStack_1b0 [4];
  undefined2 auStack_1ac [190];
  longlong local_30;
  longlong local_28;
  longlong local_20;
  longlong local_18;
  
  if (gbaQueue->scrInitEnd == 0) {
    iVar10 = 0;
    pGVar9 = gbaQueue;
    do {
      OSWaitSemaphore(pGVar9->accessSemaphores);
      iVar10 = iVar10 + 1;
      pGVar9 = (GbaQueue *)(pGVar9->accessSemaphores + 1);
    } while (iVar10 < 4);
    if (gbaQueue->field_0x2b00 != '\0') {
      memset(&gbaQueue->field_0x2b00,0,0x188);
    }
    iVar10 = 0;
    do {
      OSSignalSemaphore(gbaQueue->accessSemaphores);
      iVar10 = iVar10 + 1;
      gbaQueue = (GbaQueue *)(gbaQueue->accessSemaphores + 1);
    } while (iVar10 < 4);
  }
  else {
    memset(local_1b8,0,0x188);
    iVar10 = 0;
    pcVar11 = &CFlat.field_0x134c;
    do {
      cVar1 = *pcVar11;
      if (cVar1 != -1) {
        uVar8 = (uint)local_1b8[0];
        if (cVar1 < '\x19') {
          fVar3 = *(float *)(pcVar11 + 4);
          fVar4 = *(float *)(pcVar11 + 8);
          fVar5 = *(float *)(pcVar11 + 0xc);
          fVar6 = *(float *)(pcVar11 + 0x10);
          cVar2 = pcVar11[1];
          acStack_1b0[uVar8 * 0xc] = cVar1;
          local_30 = (longlong)(int)(fVar3 / FLOAT_80330d54);
          local_28 = (longlong)(int)(fVar4 / FLOAT_80330d54);
          local_20 = (longlong)(int)(fVar5 / FLOAT_80330d54);
          auStack_1ac[uVar8 * 6] = (short)(int)(fVar3 / FLOAT_80330d54);
          lVar7 = local_20;
          auStack_1ac[uVar8 * 6 + 1] = (short)(int)(fVar4 / FLOAT_80330d54);
          local_18 = (longlong)(int)(fVar6 / FLOAT_80330d54);
          auStack_1ac[uVar8 * 6 + 2] = (short)lVar7;
          auStack_1ac[uVar8 * 6 + 3] = (short)local_18;
          local_1b4 = local_1b4 & ~(1 << uVar8) | 1 << uVar8 & (-(int)cVar2 | (int)cVar2) >> 0x1f;
          local_1b8[0] = local_1b8[0] + 1;
        }
        else if (1 < (uint)System.m_execParam) {
          Printf__7CSystemFPce(&System,s_Error_Unknown_mapobj_type__d__801db418);
        }
      }
      iVar10 = iVar10 + 1;
      pcVar11 = pcVar11 + 0x14;
    } while (iVar10 < 0x20);
    iVar10 = 0;
    pGVar9 = gbaQueue;
    do {
      OSWaitSemaphore(pGVar9->accessSemaphores);
      iVar10 = iVar10 + 1;
      pGVar9 = (GbaQueue *)(pGVar9->accessSemaphores + 1);
    } while (iVar10 < 4);
    memcpy(&gbaQueue->field_0x2b00,local_1b8,0x188);
    iVar10 = 0;
    do {
      OSSignalSemaphore(gbaQueue->accessSemaphores);
      iVar10 = iVar10 + 1;
      gbaQueue = (GbaQueue *)(gbaQueue->accessSemaphores + 1);
    } while (iVar10 < 4);
  }
  return;
}

