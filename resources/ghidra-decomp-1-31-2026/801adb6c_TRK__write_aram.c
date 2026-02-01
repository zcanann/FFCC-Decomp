// Function: TRK__write_aram
// Entry: 801adb6c
// Size: 492 bytes

void TRK__write_aram(int param_1,uint param_2,int *param_3)

{
  uint uVar1;
  uint uVar2;
  short sVar3;
  short sVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  undefined auStack_60 [60];
  
  if (param_2 < 0x4000) {
    return;
  }
  if (0x8000000 < param_2 + *param_3) {
    return;
  }
  uVar1 = param_2 & 0xffffffe0;
  iVar5 = 0;
  uVar2 = *param_3 + (param_2 & 0x1f) + 0x1f & 0xffffffe0;
  uVar7 = uVar2 + 0x1f >> 5;
  if (uVar2 != 0) {
    uVar6 = uVar2 + 0x1f >> 8;
    if (uVar6 != 0) {
      do {
        dataCacheBlockFlush(iVar5 + param_1);
        dataCacheBlockFlush(iVar5 + 0x20 + param_1);
        dataCacheBlockFlush(iVar5 + 0x40 + param_1);
        dataCacheBlockFlush(iVar5 + 0x60 + param_1);
        dataCacheBlockFlush(iVar5 + 0x80 + param_1);
        dataCacheBlockFlush(iVar5 + 0xa0 + param_1);
        dataCacheBlockFlush(iVar5 + 0xc0 + param_1);
        dataCacheBlockFlush(iVar5 + 0xe0 + param_1);
        iVar5 = iVar5 + 0x100;
        uVar6 = uVar6 - 1;
      } while (uVar6 != 0);
      uVar7 = uVar7 & 7;
      if (uVar7 == 0) goto LAB_801adc44;
    }
    do {
      dataCacheBlockFlush(iVar5 + param_1);
      iVar5 = iVar5 + 0x20;
      uVar7 = uVar7 - 1;
    } while (uVar7 != 0);
  }
LAB_801adc44:
  do {
    iVar5 = ARGetDMAStatus();
  } while (iVar5 != 0);
  sVar3 = __ARGetInterruptStatus();
  uVar7 = 0x8000000;
  if ((param_2 & 0x1f) != 0) {
    dataCacheBlockInvalidate(auStack_60);
    __ARClearInterrupt();
    ARStartDMA(1,auStack_60,uVar1,0x20);
    do {
      sVar4 = __ARGetInterruptStatus();
    } while (sVar4 == 0);
    TRK_memcpy(param_1,auStack_60,param_2 & 0x1f);
    dataCacheBlockFlush(param_1);
    uVar7 = uVar1;
  }
  param_2 = param_2 + *param_3;
  uVar6 = param_2 & 0x1f;
  if (uVar6 != 0) {
    if ((param_2 & 0xffffffe0) != uVar7) {
      dataCacheBlockInvalidate(auStack_60);
      __ARClearInterrupt();
      ARStartDMA(1,auStack_60,param_2 & 0xffffffe0,0x20);
      do {
        sVar4 = __ARGetInterruptStatus();
      } while (sVar4 == 0);
    }
    TRK_memcpy(param_1 + param_2,auStack_60 + uVar6,0x20 - uVar6);
    dataCacheBlockFlush(param_1 + param_2);
  }
  sync(0);
  __ARClearInterrupt();
  ARStartDMA(0,param_1,uVar1,uVar2);
  if (sVar3 == 0) {
    do {
      sVar3 = __ARGetInterruptStatus();
    } while (sVar3 == 0);
    __ARClearInterrupt();
  }
  return;
}

