// Function: GetEnemyPos__8GbaQueueFiPUiPi
// Entry: 800ce76c
// Size: 576 bytes

void GetEnemyPos__8GbaQueueFiPUiPi(GbaQueue *gbaQueue,int param_2,undefined *param_3,int *param_4)

{
  char cVar1;
  short sVar2;
  short sVar3;
  uint uVar4;
  char *pcVar5;
  int iVar6;
  int iVar7;
  char *pcVar8;
  int iVar9;
  char local_528 [1288];
  
  OSWaitSemaphore(gbaQueue->accessSemaphores + param_2);
  uVar4 = countLeadingZeros(1 - (char)gbaQueue->field_0x2d56);
  OSSignalSemaphore(gbaQueue->accessSemaphores + param_2);
  if ((uVar4 >> 5 & 0xff) != 0) {
    param_2 = 0;
  }
  OSWaitSemaphore(gbaQueue->accessSemaphores + param_2);
  sVar2 = *(short *)(gbaQueue->compatibilityStr + param_2 * 0xdc + 0x32);
  sVar3 = *(short *)(gbaQueue->compatibilityStr + param_2 * 0xdc + 0x34);
  memcpy(local_528,&gbaQueue->field_0xb34,0x500);
  cVar1 = (&gbaQueue->field_0x2d32)[param_2];
  pcVar5 = local_528;
  iVar9 = 0x40;
  do {
    *(short *)(pcVar5 + 8) = *(short *)(pcVar5 + 8) - sVar2;
    *(short *)(pcVar5 + 10) = *(short *)(pcVar5 + 10) - sVar3;
    uVar4 = (int)*(short *)(pcVar5 + 8) >> 0x1f;
    if (((int)((uVar4 ^ (int)*(short *)(pcVar5 + 8)) - uVar4) < 0x50) &&
       (uVar4 = (int)*(short *)(pcVar5 + 10) >> 0x1f,
       (int)((uVar4 ^ (int)*(short *)(pcVar5 + 10)) - uVar4) < 0x40)) {
      *pcVar5 = '\x01';
    }
    else {
      pcVar5[8] = -1;
      pcVar5[9] = -1;
      pcVar5[10] = -1;
      pcVar5[0xb] = -1;
      *pcVar5 = '\0';
    }
    if ((*(short *)(pcVar5 + 4) == 0) || (pcVar5[2] == '\0')) {
      *pcVar5 = '\0';
    }
    if ((cVar1 == '\x02') || (cVar1 == '\0')) {
      *pcVar5 = '\0';
    }
    else if ((cVar1 == '\x03') && (pcVar5[1] == '\x01')) {
      *pcVar5 = '\0';
    }
    pcVar5 = pcVar5 + 0x14;
    iVar9 = iVar9 + -1;
  } while (iVar9 != 0);
  iVar9 = 0;
  pcVar8 = local_528;
  iVar7 = 0;
  pcVar5 = &gbaQueue->field_0x1034 + param_2 * 0x500;
  while( true ) {
    if (0x3f < iVar7) break;
    if (((*pcVar8 != '\0') || (*pcVar5 != '\0')) && (iVar6 = memcmp(pcVar8,pcVar5,0x14), iVar6 != 0)
       ) {
      iVar9 = iVar9 + 1;
      *param_3 = 0x12;
      param_3[1] = (byte)iVar7 | (byte)((int)*pcVar8 << 7);
      param_3[2] = (char)*(undefined2 *)(pcVar8 + 8);
      param_3[3] = (char)*(undefined2 *)(pcVar8 + 10);
      param_3 = param_3 + 4;
    }
    pcVar8 = pcVar8 + 0x14;
    pcVar5 = pcVar5 + 0x14;
    iVar7 = iVar7 + 1;
  }
  *param_4 = iVar9;
  memcpy(&gbaQueue->field_0x1034 + param_2 * 0x500,local_528,0x500);
  OSSignalSemaphore(gbaQueue->accessSemaphores + param_2);
  return;
}

