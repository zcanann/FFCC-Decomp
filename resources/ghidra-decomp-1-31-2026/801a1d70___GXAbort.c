// Function: __GXAbort
// Entry: 801a1d70
// Size: 364 bytes

void __GXAbort(void)

{
  bool bVar1;
  short sVar2;
  int iVar3;
  int iVar4;
  short sVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  
  if ((*(char *)(DAT_80333828 + 0x4f2) != '\0') && (iVar4 = GXGetGPFifo(), iVar4 != 0)) {
    sVar5 = *(short *)(DAT_8032f2f4 + 0x4e);
    do {
      sVar2 = *(short *)(DAT_8032f2f4 + 0x4e);
      iVar4 = *(int *)(DAT_8032f2f4 + 0x4e);
      bVar1 = sVar2 != sVar5;
      sVar5 = sVar2;
    } while (bVar1);
    do {
      uVar6 = OSGetTime();
      do {
        uVar7 = OSGetTime();
      } while ((uint)(8 < (uint)uVar7 - (uint)uVar6) +
               ((int)((ulonglong)uVar7 >> 0x20) -
                ((uint)((uint)uVar7 < (uint)uVar6) + (int)((ulonglong)uVar6 >> 0x20)) ^ 0x80000000)
               < 0x80000001);
      sVar5 = *(short *)(DAT_8032f2f4 + 0x4e);
      do {
        sVar2 = *(short *)(DAT_8032f2f4 + 0x4e);
        iVar3 = *(int *)(DAT_8032f2f4 + 0x4e);
        bVar1 = sVar2 != sVar5;
        sVar5 = sVar2;
      } while (bVar1);
      bVar1 = iVar3 != iVar4;
      iVar4 = iVar3;
    } while (bVar1);
  }
  DAT_cc003018 = 1;
  uVar6 = OSGetTime();
  do {
    uVar7 = OSGetTime();
  } while ((uint)(0x32 < (uint)uVar7 - (uint)uVar6) +
           ((int)((ulonglong)uVar7 >> 0x20) -
            ((uint)((uint)uVar7 < (uint)uVar6) + (int)((ulonglong)uVar6 >> 0x20)) ^ 0x80000000) <
           0x80000001);
  DAT_cc003018 = 0;
  uVar6 = OSGetTime();
  do {
    uVar7 = OSGetTime();
  } while ((uint)(5 < (uint)uVar7 - (uint)uVar6) +
           ((int)((ulonglong)uVar7 >> 0x20) -
            ((uint)((uint)uVar7 < (uint)uVar6) + (int)((ulonglong)uVar6 >> 0x20)) ^ 0x80000000) <
           0x80000001);
  return;
}

