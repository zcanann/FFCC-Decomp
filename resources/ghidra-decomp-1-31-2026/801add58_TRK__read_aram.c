// Function: TRK__read_aram
// Entry: 801add58
// Size: 308 bytes

void TRK__read_aram(int param_1,uint param_2,int *param_3)

{
  uint uVar1;
  uint uVar2;
  short sVar3;
  short sVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  ulonglong uVar8;
  
  if (param_2 < 0x4000) {
    return;
  }
  if (0x8000000 < param_2 + *param_3) {
    return;
  }
  iVar5 = 0;
  uVar1 = *param_3 + (param_2 & 0x1f) + 0x1f & 0xffffffe0;
  uVar2 = uVar1 + 0x1f >> 5;
  uVar8 = (ulonglong)uVar2 << 0x20;
  if (uVar1 != 0) {
    uVar6 = uVar1 + 0x1f >> 8;
    uVar7 = uVar2;
    if (uVar6 != 0) {
      do {
        dataCacheBlockInvalidate(iVar5 + param_1);
        dataCacheBlockInvalidate(iVar5 + 0x20 + param_1);
        dataCacheBlockInvalidate(iVar5 + 0x40 + param_1);
        dataCacheBlockInvalidate(iVar5 + 0x60 + param_1);
        dataCacheBlockInvalidate(iVar5 + 0x80 + param_1);
        dataCacheBlockInvalidate(iVar5 + 0xa0 + param_1);
        dataCacheBlockInvalidate(iVar5 + 0xc0 + param_1);
        dataCacheBlockInvalidate(iVar5 + 0xe0 + param_1);
        iVar5 = iVar5 + 0x100;
        uVar6 = uVar6 - 1;
      } while (uVar6 != 0);
      uVar7 = uVar2 & 7;
      uVar8 = CONCAT44(uVar2,iVar5) & 0x7ffffffff;
      uVar2 = uVar7;
      if (uVar7 == 0) goto LAB_801ade28;
    }
    do {
      dataCacheBlockInvalidate(iVar5 + param_1);
      iVar5 = iVar5 + 0x20;
      uVar8 = CONCAT44(uVar2,iVar5);
      uVar7 = uVar7 - 1;
    } while (uVar7 != 0);
  }
LAB_801ade28:
  do {
    uVar8 = ARGetDMAStatus((int)(uVar8 >> 0x20),(int)uVar8);
  } while ((int)(uVar8 >> 0x20) != 0);
  sVar3 = __ARGetInterruptStatus();
  __ARClearInterrupt();
  ARStartDMA(1,param_1,param_2 & 0xffffffe0,uVar1);
  do {
    sVar4 = __ARGetInterruptStatus();
  } while (sVar4 == 0);
  if (sVar3 == 0) {
    __ARClearInterrupt();
  }
  return;
}

