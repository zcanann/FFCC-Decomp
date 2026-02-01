// Function: GetMapObj__8GbaQueueFPUc
// Entry: 800cce38
// Size: 368 bytes

void GetMapObj__8GbaQueueFPUc(GbaQueue *gbaQueue,char *param_2)

{
  byte *pbVar1;
  byte *pbVar2;
  int iVar3;
  int iVar4;
  GbaQueue *pGVar5;
  byte local_198 [392];
  
  iVar4 = 0;
  pGVar5 = gbaQueue;
  do {
    OSWaitSemaphore(pGVar5->accessSemaphores);
    iVar4 = iVar4 + 1;
    pGVar5 = (GbaQueue *)(pGVar5->accessSemaphores + 1);
  } while (iVar4 < 4);
  memcpy(local_198,&gbaQueue->field_0x2b00,0x188);
  iVar4 = 0;
  pGVar5 = gbaQueue;
  do {
    OSSignalSemaphore(pGVar5->accessSemaphores);
    iVar4 = iVar4 + 1;
    pGVar5 = (GbaQueue *)(pGVar5->accessSemaphores + 1);
  } while (iVar4 < 4);
  pbVar2 = local_198;
  iVar4 = 5;
  *param_2 = local_198[0];
  param_2[1] = (char)local_198._4_4_;
  param_2[2] = SUB41(local_198._4_4_,1);
  param_2[3] = SUB41(local_198._4_4_,2);
  param_2[4] = SUB41(local_198._4_4_,3);
  for (iVar3 = 0; iVar3 < (int)(uint)local_198[0]; iVar3 = iVar3 + 1) {
    param_2[iVar4] = pbVar2[8];
    param_2[iVar4 + 1] = (char)*(undefined2 *)(pbVar2 + 0xc);
    param_2[iVar4 + 2] = (char)((ushort)*(undefined2 *)(pbVar2 + 0xc) >> 8);
    param_2[iVar4 + 3] = (char)*(undefined2 *)(pbVar2 + 0xe);
    param_2[iVar4 + 4] = (char)((ushort)*(undefined2 *)(pbVar2 + 0xe) >> 8);
    param_2[iVar4 + 5] = (char)*(undefined2 *)(pbVar2 + 0x10);
    param_2[iVar4 + 6] = (char)((ushort)*(undefined2 *)(pbVar2 + 0x10) >> 8);
    param_2[iVar4 + 7] = (char)*(undefined2 *)(pbVar2 + 0x12);
    pbVar1 = pbVar2 + 0x12;
    pbVar2 = pbVar2 + 0xc;
    param_2[iVar4 + 8] = (char)((ushort)*(undefined2 *)pbVar1 >> 8);
    iVar4 = iVar4 + 9;
  }
  gbaQueue->field_0x2c88 = 1;
  return;
}

