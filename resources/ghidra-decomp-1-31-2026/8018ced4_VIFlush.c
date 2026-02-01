// Function: VIFlush
// Entry: 8018ced4
// Size: 304 bytes

void VIFlush(void)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 extraout_r4;
  int iVar3;
  undefined8 uVar4;
  
  uVar2 = OSDisableInterrupts();
  DAT_8032f110 = DAT_8032f110 | DAT_8032f104;
  DAT_8032f104 = 0;
  DAT_8032f118 = DAT_8032f118 | DAT_8032f108;
  DAT_8032f11c = DAT_8032f11c | DAT_8032f10c;
  for (; uVar1 = DAT_8032f10c, DAT_8032f10c != 0 || DAT_8032f108 != 0;
      DAT_8032f10c = DAT_8032f10c & ~(uint)uVar4) {
    __shr2u(DAT_8032f108,DAT_8032f10c,0x20);
    iVar3 = countLeadingZeros(extraout_r4);
    if (0x1f < iVar3) {
      iVar3 = countLeadingZeros(uVar1);
      iVar3 = iVar3 + 0x20;
    }
    *(undefined2 *)(&DAT_8030cbc0 + iVar3 * 2) = (&DAT_8030cb48)[iVar3];
    uVar4 = __shl2i(0,1,0x3f - iVar3);
    DAT_8032f108 = DAT_8032f108 & ~(uint)((ulonglong)uVar4 >> 0x20);
  }
  DAT_8032f0e8 = 1;
  DAT_8032f128 = DAT_8030cc68;
  OSRestoreInterrupts(uVar2);
  return;
}

