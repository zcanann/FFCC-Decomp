// Function: GetTreasurePos__8GbaQueueFiPUiPi
// Entry: 800ce56c
// Size: 512 bytes

void GetTreasurePos__8GbaQueueFiPUiPi
               (GbaQueue *gbaQueue,int param_2,undefined *param_3,int *param_4)

{
  short sVar1;
  short sVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  char *pcVar7;
  char *pcVar8;
  char local_168 [324];
  
  if (gbaQueue->field_0x2d56 != '\0') {
    param_2 = 0;
  }
  OSWaitSemaphore(gbaQueue->accessSemaphores + param_2);
  sVar1 = *(short *)(gbaQueue->compatibilityStr + param_2 * 0xdc + 0x32);
  sVar2 = *(short *)(gbaQueue->compatibilityStr + param_2 * 0xdc + 0x34);
  memcpy(local_168,&gbaQueue->field_0x2434,0x140);
  pcVar7 = local_168;
  iVar4 = 0;
  do {
    if ((char)gbaQueue->field_0x2af4 <= iVar4) {
      iVar4 = 0;
      pcVar8 = local_168;
      iVar6 = 0;
      pcVar7 = &gbaQueue->field_0x2574 + param_2 * 0x140;
      while( true ) {
        if ((char)gbaQueue->field_0x2af4 <= iVar6) break;
        if (((*pcVar8 != '\0') || (*pcVar7 != '\0')) &&
           (iVar3 = memcmp(pcVar8,pcVar7,0x14), iVar3 != 0)) {
          *param_3 = 0x21;
          iVar4 = iVar4 + 1;
          param_3[1] = (char)iVar6 + 0x40U | (byte)((int)*pcVar8 << 7);
          param_3[2] = (char)*(undefined2 *)(pcVar8 + 8);
          param_3[3] = (char)*(undefined2 *)(pcVar8 + 10);
          param_3 = param_3 + 4;
        }
        pcVar8 = pcVar8 + 0x14;
        pcVar7 = pcVar7 + 0x14;
        iVar6 = iVar6 + 1;
      }
      *param_4 = iVar4;
      memcpy(&gbaQueue->field_0x2574 + param_2 * 0x140,local_168,0x140);
      OSSignalSemaphore(gbaQueue->accessSemaphores + param_2);
      return;
    }
    *(short *)(pcVar7 + 8) = *(short *)(pcVar7 + 8) - sVar1;
    *(short *)(pcVar7 + 10) = *(short *)(pcVar7 + 10) - sVar2;
    uVar5 = (int)*(short *)(pcVar7 + 8) >> 0x1f;
    if ((int)((uVar5 ^ (int)*(short *)(pcVar7 + 8)) - uVar5) < 0x50) {
      uVar5 = (int)*(short *)(pcVar7 + 10) >> 0x1f;
      if (0x3f < (int)((uVar5 ^ (int)*(short *)(pcVar7 + 10)) - uVar5)) goto LAB_800ce630;
      *pcVar7 = '\x01';
    }
    else {
LAB_800ce630:
      pcVar7[8] = -1;
      pcVar7[9] = -1;
      pcVar7[10] = -1;
      pcVar7[0xb] = -1;
      *pcVar7 = '\0';
    }
    if (pcVar7[2] == '\0') {
      *pcVar7 = '\0';
    }
    if ((&gbaQueue->field_0x2d32)[param_2] != '\x03') {
      *pcVar7 = '\0';
    }
    pcVar7 = pcVar7 + 0x14;
    iVar4 = iVar4 + 1;
  } while( true );
}

