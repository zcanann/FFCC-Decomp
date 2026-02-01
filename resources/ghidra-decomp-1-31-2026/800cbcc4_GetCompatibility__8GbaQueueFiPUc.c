// Function: GetCompatibility__8GbaQueueFiPUc
// Entry: 800cbcc4
// Size: 480 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

int GetCompatibility__8GbaQueueFiPUc(GbaQueue *gbaQueue,int param_2,char *outCompatibilityStr)

{
  byte *pbVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  byte *pbVar5;
  int32_t srcBuffer;
  int iVar6;
  uint uVar7;
  char *dstBuffer;
  undefined uStack_38;
  byte local_37 [4];
  char local_33;
  char local_32;
  char local_31;
  byte local_2f [11];
  
  OSWaitSemaphore(gbaQueue->accessSemaphores + param_2);
  memcpy(&uStack_38,gbaQueue->compatibilityStr + param_2 * 0xdc,0x10);
  OSSignalSemaphore(gbaQueue->accessSemaphores + param_2);
  uVar7 = 2;
  *outCompatibilityStr = (&gbaQueue->field_0x529)[param_2 * 0xdc];
  if (local_37[2] != '\0') {
    uVar7 = 3;
  }
  if (local_37[3] != '\0') {
    uVar7 = uVar7 + 1;
  }
  if (local_33 != '\0') {
    uVar7 = uVar7 + 1;
  }
  if (local_32 != '\0') {
    uVar7 = uVar7 + 1;
  }
  if (local_31 != '\0') {
    uVar7 = uVar7 + 1;
  }
  if ((4 < uVar7) && (System.m_execParam != 0)) {
    Printf__7CSystemFPce(&System,s_compatibility_data_error___801db3a4);
  }
  pbVar5 = local_37;
  outCompatibilityStr[1] = (char)uVar7;
  dstBuffer = outCompatibilityStr + 2;
  iVar3 = 0;
  iVar6 = 2;
  pbVar1 = pbVar5;
  for (iVar4 = 1; (iVar3 < (int)uVar7 && (iVar4 < 8)); iVar4 = iVar4 + 1) {
    if ((iVar3 < 2) || ((iVar3 >= 2 && (*pbVar1 != 0)))) {
      *dstBuffer = (char)iVar4;
      iVar6 = iVar6 + 2;
      iVar3 = iVar3 + 1;
      dstBuffer[1] = pbVar1[8];
      dstBuffer = dstBuffer + 2;
    }
    pbVar1 = pbVar1 + 1;
  }
  iVar4 = 0;
  for (iVar3 = 1; (iVar4 < (int)uVar7 && (iVar3 < 8)); iVar3 = iVar3 + 1) {
    if ((iVar4 < 2) || ((iVar4 >= 2 && (*pbVar5 != 0)))) {
      srcBuffer = Game.game.m_cFlatDataArr[1].m_table[2].index[*pbVar5];
      iVar2 = strlen(srcBuffer);
      memcpy(dstBuffer,srcBuffer,iVar2 + 1);
      iVar6 = iVar2 + iVar6 + 1;
      iVar4 = iVar4 + 1;
      dstBuffer = dstBuffer + iVar2 + 1;
    }
    pbVar5 = pbVar5 + 1;
  }
  return iVar6;
}

