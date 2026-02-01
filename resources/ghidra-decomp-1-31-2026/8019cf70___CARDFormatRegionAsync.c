// Function: __CARDFormatRegionAsync
// Entry: 8019cf70
// Size: 1624 bytes

int __CARDFormatRegionAsync(int chan,short encode,code *callback)

{
  ushort uVar1;
  uint uVar2;
  int iVar3;
  uint extraout_r4;
  uint extraout_r4_00;
  uint extraout_r4_01;
  uint extraout_r4_02;
  uint extraout_r4_03;
  uint extraout_r4_04;
  uint extraout_r4_05;
  uint extraout_r4_06;
  uint extraout_r4_07;
  char *pcVar4;
  char *pcVar5;
  void *pvVar6;
  short sVar7;
  ulonglong uVar8;
  ulonglong uVar9;
  CARDControl *local_40 [2];
  
  iVar3 = __CARDGetControlBlock(chan,local_40);
  if (-1 < iVar3) {
    pvVar6 = local_40[0]->workArea;
    memset(pvVar6,0xff,0x2000);
    uVar1 = DAT_cc00206e;
    *(short *)((int)pvVar6 + 0x24) = encode;
    iVar3 = __OSLockSram();
    *(undefined4 *)((int)pvVar6 + 0x14) = *(undefined4 *)(iVar3 + 0xc);
    *(uint *)((int)pvVar6 + 0x18) = (uint)*(byte *)(iVar3 + 0x12);
    __OSUnlockSram(0);
    uVar8 = OSGetTime();
    iVar3 = __OSLockSramEx();
    pcVar5 = (char *)(iVar3 + chan * 0xc);
    sVar7 = 0;
    pcVar4 = pcVar5;
    uVar9 = uVar8;
    while( true ) {
      if (3 < sVar7) break;
      uVar2 = (int)uVar9 * 0x41c64e6d;
      uVar9 = __shr2i((int)(uVar9 >> 0x20) * 0x41c64e6d +
                      (int)((uVar9 & 0xffffffff) * 0x41c64e6d >> 0x20) + (uint)(0xffffcfc6 < uVar2),
                      uVar2 + 0x3039,0x10);
      *(char *)((int)pvVar6 + (int)sVar7) = (char)uVar9 + *pcVar4;
      uVar2 = (int)uVar9 * 0x41c64e6d;
      __shr2i((int)(uVar9 >> 0x20) * 0x41c64e6d + (int)((uVar9 & 0xffffffff) * 0x41c64e6d >> 0x20) +
              (uint)(0xffffcfc6 < uVar2),uVar2 + 0x3039,0x10);
      uVar2 = (extraout_r4 & 0x7fff) * 0x41c64e6d;
      uVar9 = __shr2i((int)((ulonglong)(extraout_r4 & 0x7fff) * 0x41c64e6d >> 0x20) +
                      (uint)(0xffffcfc6 < uVar2),uVar2 + 0x3039,0x10);
      uVar2 = (int)uVar9 * 0x41c64e6d;
      *(char *)((int)pvVar6 + (int)(short)(sVar7 + 1)) = (char)uVar9 + pcVar5[(short)(sVar7 + 1)];
      __shr2i((int)(uVar9 >> 0x20) * 0x41c64e6d + (int)((uVar9 & 0xffffffff) * 0x41c64e6d >> 0x20) +
              (uint)(0xffffcfc6 < uVar2),uVar2 + 0x3039,0x10);
      uVar2 = (extraout_r4_00 & 0x7fff) * 0x41c64e6d;
      uVar9 = __shr2i((int)((ulonglong)(extraout_r4_00 & 0x7fff) * 0x41c64e6d >> 0x20) +
                      (uint)(0xffffcfc6 < uVar2),uVar2 + 0x3039,0x10);
      uVar2 = (int)uVar9 * 0x41c64e6d;
      *(char *)((int)pvVar6 + (int)(short)(sVar7 + 2)) = (char)uVar9 + pcVar5[(short)(sVar7 + 2)];
      __shr2i((int)(uVar9 >> 0x20) * 0x41c64e6d + (int)((uVar9 & 0xffffffff) * 0x41c64e6d >> 0x20) +
              (uint)(0xffffcfc6 < uVar2),uVar2 + 0x3039,0x10);
      uVar2 = (extraout_r4_01 & 0x7fff) * 0x41c64e6d;
      uVar9 = __shr2i((int)((ulonglong)(extraout_r4_01 & 0x7fff) * 0x41c64e6d >> 0x20) +
                      (uint)(0xffffcfc6 < uVar2),uVar2 + 0x3039,0x10);
      uVar2 = (int)uVar9 * 0x41c64e6d;
      *(char *)((int)pvVar6 + (int)(short)(sVar7 + 3)) = (char)uVar9 + pcVar5[(short)(sVar7 + 3)];
      __shr2i((int)(uVar9 >> 0x20) * 0x41c64e6d + (int)((uVar9 & 0xffffffff) * 0x41c64e6d >> 0x20) +
              (uint)(0xffffcfc6 < uVar2),uVar2 + 0x3039,0x10);
      uVar2 = (extraout_r4_02 & 0x7fff) * 0x41c64e6d;
      uVar9 = __shr2i((int)((ulonglong)(extraout_r4_02 & 0x7fff) * 0x41c64e6d >> 0x20) +
                      (uint)(0xffffcfc6 < uVar2),uVar2 + 0x3039,0x10);
      uVar2 = (int)uVar9 * 0x41c64e6d;
      *(char *)((int)pvVar6 + (int)(short)(sVar7 + 4)) = (char)uVar9 + pcVar5[(short)(sVar7 + 4)];
      __shr2i((int)(uVar9 >> 0x20) * 0x41c64e6d + (int)((uVar9 & 0xffffffff) * 0x41c64e6d >> 0x20) +
              (uint)(0xffffcfc6 < uVar2),uVar2 + 0x3039,0x10);
      uVar2 = (extraout_r4_03 & 0x7fff) * 0x41c64e6d;
      uVar9 = __shr2i((int)((ulonglong)(extraout_r4_03 & 0x7fff) * 0x41c64e6d >> 0x20) +
                      (uint)(0xffffcfc6 < uVar2),uVar2 + 0x3039,0x10);
      uVar2 = (int)uVar9 * 0x41c64e6d;
      *(char *)((int)pvVar6 + (int)(short)(sVar7 + 5)) = (char)uVar9 + pcVar5[(short)(sVar7 + 5)];
      __shr2i((int)(uVar9 >> 0x20) * 0x41c64e6d + (int)((uVar9 & 0xffffffff) * 0x41c64e6d >> 0x20) +
              (uint)(0xffffcfc6 < uVar2),uVar2 + 0x3039,0x10);
      uVar2 = (extraout_r4_04 & 0x7fff) * 0x41c64e6d;
      uVar9 = __shr2i((int)((ulonglong)(extraout_r4_04 & 0x7fff) * 0x41c64e6d >> 0x20) +
                      (uint)(0xffffcfc6 < uVar2),uVar2 + 0x3039,0x10);
      uVar2 = (int)uVar9 * 0x41c64e6d;
      *(char *)((int)pvVar6 + (int)(short)(sVar7 + 6)) = (char)uVar9 + pcVar5[(short)(sVar7 + 6)];
      __shr2i((int)(uVar9 >> 0x20) * 0x41c64e6d + (int)((uVar9 & 0xffffffff) * 0x41c64e6d >> 0x20) +
              (uint)(0xffffcfc6 < uVar2),uVar2 + 0x3039,0x10);
      uVar2 = (extraout_r4_05 & 0x7fff) * 0x41c64e6d;
      uVar9 = __shr2i((int)((ulonglong)(extraout_r4_05 & 0x7fff) * 0x41c64e6d >> 0x20) +
                      (uint)(0xffffcfc6 < uVar2),uVar2 + 0x3039,0x10);
      uVar2 = (int)uVar9 * 0x41c64e6d;
      *(char *)((int)pvVar6 + (int)(short)(sVar7 + 7)) = (char)uVar9 + pcVar5[(short)(sVar7 + 7)];
      __shr2i((int)(uVar9 >> 0x20) * 0x41c64e6d + (int)((uVar9 & 0xffffffff) * 0x41c64e6d >> 0x20) +
              (uint)(0xffffcfc6 < uVar2),uVar2 + 0x3039,0x10);
      uVar9 = (ulonglong)(extraout_r4_06 & 0x7fff);
      pcVar4 = pcVar4 + 8;
      sVar7 = sVar7 + 8;
    }
    pcVar5 = pcVar5 + sVar7;
    while( true ) {
      if (0xb < sVar7) break;
      uVar2 = (int)uVar9 * 0x41c64e6d;
      uVar9 = __shr2i((int)(uVar9 >> 0x20) * 0x41c64e6d +
                      (int)((uVar9 & 0xffffffff) * 0x41c64e6d >> 0x20) + (uint)(0xffffcfc6 < uVar2),
                      uVar2 + 0x3039,0x10);
      *(char *)((int)pvVar6 + (int)sVar7) = (char)uVar9 + *pcVar5;
      uVar2 = (int)uVar9 * 0x41c64e6d;
      __shr2i((int)(uVar9 >> 0x20) * 0x41c64e6d + (int)((uVar9 & 0xffffffff) * 0x41c64e6d >> 0x20) +
              (uint)(0xffffcfc6 < uVar2),uVar2 + 0x3039,0x10);
      uVar9 = (ulonglong)(extraout_r4_07 & 0x7fff);
      pcVar5 = pcVar5 + 1;
      sVar7 = sVar7 + 1;
    }
    __OSUnlockSramEx(0);
    *(uint *)((int)pvVar6 + 0x1c) = (uint)uVar1;
    *(ulonglong *)((int)pvVar6 + 0xc) = uVar8;
    *(undefined2 *)((int)pvVar6 + 0x20) = 0;
    *(uint16_t *)((int)pvVar6 + 0x22) = local_40[0]->size;
    __CARDCheckSum(pvVar6,0x1fc,(int)pvVar6 + 0x1fc,(int)pvVar6 + 0x1fe);
    for (sVar7 = 0; sVar7 < 2; sVar7 = sVar7 + 1) {
      pvVar6 = (void *)((int)local_40[0]->workArea + (sVar7 + 1) * 0x2000);
      memset(pvVar6,0xff,0x2000);
      *(short *)((int)pvVar6 + 0x1ffa) = sVar7;
      __CARDCheckSum(pvVar6,0x1ffc,(int)pvVar6 + 0x1ffc,(int)pvVar6 + 0x1ffe);
    }
    for (sVar7 = 0; sVar7 < 2; sVar7 = sVar7 + 1) {
      pvVar6 = (void *)((int)local_40[0]->workArea + (sVar7 + 3) * 0x2000);
      memset(pvVar6,0,0x2000);
      *(short *)((int)pvVar6 + 4) = sVar7;
      *(uint16_t *)((int)pvVar6 + 6) = local_40[0]->cBlock - 5;
      *(undefined2 *)((int)pvVar6 + 8) = 4;
      __CARDCheckSum((int)pvVar6 + 4,0x1ffc,pvVar6,(int)pvVar6 + 2);
    }
    if (callback == (code *)0x0) {
      callback = __CARDDefaultApiCallback;
    }
    local_40[0]->apiCallback = callback;
    DCStoreRange(local_40[0]->workArea,0xa000);
    local_40[0]->formatStep = 0;
    iVar3 = __CARDEraseSector(chan,local_40[0]->sectorSize * local_40[0]->formatStep,FormatCallback)
    ;
    if (iVar3 < 0) {
      __CARDPutControlBlock(local_40[0],iVar3);
    }
  }
  return iVar3;
}

