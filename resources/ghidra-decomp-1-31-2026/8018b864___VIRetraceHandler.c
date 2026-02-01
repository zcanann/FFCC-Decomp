// Function: __VIRetraceHandler
// Entry: 8018b864
// Size: 560 bytes

void __VIRetraceHandler(undefined4 param_1,undefined4 param_2)

{
  bool bVar1;
  ushort uVar2;
  uint uVar3;
  int iVar4;
  undefined4 extraout_r4;
  bool bVar5;
  undefined8 uVar6;
  undefined auStack_2e0 [716];
  
  uVar2 = DAT_cc002030;
  if ((uVar2 & 0x8000) != 0) {
    DAT_cc002030 = uVar2 & 0x7fff;
  }
  uVar2 = DAT_cc002034;
  if ((uVar2 & 0x8000) != 0) {
    DAT_cc002034 = uVar2 & 0x7fff;
  }
  uVar2 = DAT_cc002038;
  bVar5 = (uVar2 & 0x8000) != 0;
  if (bVar5) {
    DAT_cc002038 = uVar2 & 0x7fff;
  }
  uVar2 = DAT_cc00203c;
  bVar1 = (uVar2 & 0x8000) != 0;
  if (bVar1) {
    DAT_cc00203c = uVar2 & 0x7fff;
  }
  if ((bVar5) || (bVar1)) {
    OSSetCurrentContext(param_2);
  }
  else {
    DAT_8032f0e4 = DAT_8032f0e4 + 1;
    OSClearContext(auStack_2e0);
    OSSetCurrentContext(auStack_2e0);
    if (DAT_8032f0f4 != (code *)0x0) {
      (*DAT_8032f0f4)(DAT_8032f0e4);
    }
    if (DAT_8032f0e8 != 0) {
      if ((DAT_8032f110 == 1) && (iVar4 = getCurrentFieldEvenOdd(), iVar4 == 0)) {
        bVar5 = false;
      }
      else {
        for (; uVar3 = DAT_8032f11c, DAT_8032f11c != 0 || DAT_8032f118 != 0;
            DAT_8032f11c = DAT_8032f11c & ~(uint)uVar6) {
          __shr2u(DAT_8032f118,DAT_8032f11c,0x20);
          iVar4 = countLeadingZeros(extraout_r4);
          if (0x1f < iVar4) {
            iVar4 = countLeadingZeros(uVar3);
            iVar4 = iVar4 + 0x20;
          }
          (&DAT_cc002000)[iVar4] = *(undefined2 *)(&DAT_8030cbc0 + iVar4 * 2);
          uVar6 = __shl2i(0,1,0x3f - iVar4);
          DAT_8032f118 = DAT_8032f118 & ~(uint)((ulonglong)uVar6 >> 0x20);
        }
        DAT_8032f110 = 0;
        bVar5 = true;
        DAT_8032f120 = DAT_8030cc8c;
        DAT_8032f124 = DAT_8030cc60;
        DAT_8032f12c = DAT_8032f128;
      }
      if (bVar5) {
        DAT_8032f0e8 = 0;
        SIRefreshSamplingRate();
      }
    }
    if (DAT_8032f0f8 != (code *)0x0) {
      OSClearContext(auStack_2e0);
      (*DAT_8032f0f8)(DAT_8032f0e4);
    }
    OSWakeupThread(&DAT_8032f0ec);
    OSClearContext(auStack_2e0);
    OSSetCurrentContext(param_2);
  }
  return;
}

