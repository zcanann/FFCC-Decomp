// Function: GetMapObjInfo__8GbaQueueFiPUc
// Entry: 800ce3f8
// Size: 372 bytes

undefined4 GetMapObjInfo__8GbaQueueFiPUc(GbaQueue *gbaQueue,int param_2,undefined *param_3)

{
  undefined *puVar1;
  GbaQueue *pGVar2;
  undefined *puVar3;
  int iVar4;
  
  OSWaitSemaphore(gbaQueue->accessSemaphores + param_2);
  iVar4 = 4;
  pGVar2 = gbaQueue;
  do {
    puVar3 = param_3;
    *puVar3 = pGVar2->field_0xb35;
    puVar3[1] = pGVar2->field_0xb49;
    puVar3[2] = pGVar2->field_0xb5d;
    puVar3[3] = pGVar2->field_0xb71;
    puVar3[4] = pGVar2->field_0xb85;
    puVar3[5] = pGVar2->field_0xb99;
    puVar3[6] = pGVar2->field_0xbad;
    puVar3[7] = pGVar2->field_0xbc1;
    puVar3[8] = pGVar2->field_0xbd5;
    puVar3[9] = pGVar2->field_0xbe9;
    puVar3[10] = pGVar2->field_0xbfd;
    puVar3[0xb] = pGVar2->field_0xc11;
    puVar3[0xc] = pGVar2->field_0xc25;
    puVar3[0xd] = pGVar2->field_0xc39;
    puVar3[0xe] = pGVar2->field_0xc4d;
    puVar1 = &pGVar2->field_0xc61;
    pGVar2 = (GbaQueue *)&pGVar2->field_0x140;
    puVar3[0xf] = *puVar1;
    iVar4 = iVar4 + -1;
    param_3 = puVar3 + 0x10;
  } while (iVar4 != 0);
  puVar3[0x10] = gbaQueue->field_0x2435;
  puVar3[0x11] = gbaQueue->field_0x2449;
  puVar3[0x12] = gbaQueue->field_0x245d;
  puVar3[0x13] = gbaQueue->field_0x2471;
  puVar3[0x14] = gbaQueue->field_0x2485;
  puVar3[0x15] = gbaQueue->field_0x2499;
  puVar3[0x16] = gbaQueue->field_0x24ad;
  puVar3[0x17] = gbaQueue->field_0x24c1;
  puVar3[0x18] = gbaQueue->field_0x24d5;
  puVar3[0x19] = gbaQueue->field_0x24e9;
  puVar3[0x1a] = gbaQueue->field_0x24fd;
  puVar3[0x1b] = gbaQueue->field_0x2511;
  puVar3[0x1c] = gbaQueue->field_0x2525;
  puVar3[0x1d] = gbaQueue->field_0x2539;
  puVar3[0x1e] = gbaQueue->field_0x254d;
  puVar3[0x1f] = gbaQueue->field_0x2561;
  OSSignalSemaphore(gbaQueue->accessSemaphores + param_2);
  return 0x50;
}

