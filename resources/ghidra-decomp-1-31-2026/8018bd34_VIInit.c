// Function: VIInit
// Entry: 8018bd34
// Size: 1200 bytes

void VIInit(void)

{
  ushort *puVar1;
  ushort uVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  short sVar8;
  int iVar7;
  short sVar9;
  
  if (DAT_8032f0e0 == 0) {
    OSRegisterVersion(DAT_8032eb08);
    DAT_8032f0e0 = 1;
    DAT_8032f0fc = 1;
    uVar2 = DAT_cc002002;
    if ((uVar2 & 1) == 0) {
      __VIInit(0);
    }
    DAT_8032f0e4 = 0;
    DAT_8032f10c = 0;
    DAT_8032f108 = 0;
    DAT_8032f11c = 0;
    DAT_8032f118 = 0;
    DAT_8032f104 = 0;
    DAT_8032f110 = 0;
    DAT_8032f0e8 = 0;
    DAT_cc00204e = DAT_802179a0 | DAT_802179a2 << 10;
    DAT_cc00204c = (ushort)((int)(uint)DAT_802179a2 >> 6) | DAT_802179a4 << 4;
    DAT_cc002052 = DAT_802179a6 | DAT_802179a8 << 10;
    DAT_cc002050 = (ushort)((int)(uint)DAT_802179a8 >> 6) | DAT_802179aa << 4;
    DAT_cc002056 = DAT_802179ac | DAT_802179ae << 10;
    DAT_cc002054 = (ushort)((int)(uint)DAT_802179ae >> 6) | DAT_802179b0 << 4;
    DAT_cc00205a = DAT_802179b2 | DAT_802179b4 << 8;
    DAT_cc002058 = DAT_802179b6 | DAT_802179b8 << 8;
    DAT_cc00205e = DAT_802179ba | DAT_802179bc << 8;
    DAT_cc00205c = DAT_802179be | DAT_802179c0 << 8;
    DAT_cc002062 = DAT_802179c2 | DAT_802179c4 << 8;
    DAT_cc002060 = DAT_802179c6 | DAT_802179c8 << 8;
    DAT_cc002066 = DAT_802179ca | DAT_802179cc << 8;
    DAT_cc002064 = DAT_802179ce | DAT_802179d0 << 8;
    DAT_cc002070 = 0x280;
    iVar3 = __OSLockSram();
    DAT_8032f102 = 0;
    DAT_8032f100 = (short)*(char *)(iVar3 + 0x10);
    __OSUnlockSram(0);
    uVar2 = DAT_cc002002;
    DAT_8030cc5c = uVar2 >> 2 & 1;
    DAT_8030cc60 = uVar2 >> 8 & 3;
    if ((DAT_800000cc == 1) && ((uVar2 >> 8 & 3) == 0)) {
      DAT_8030cc60 = 5;
    }
    uVar4 = DAT_8030cc60;
    if (DAT_8030cc60 == 3) {
      uVar4 = 0;
    }
    DAT_8030cc8c = getTiming(uVar4 * 4 + DAT_8030cc5c);
    DAT_8032f124 = DAT_8030cc60;
    DAT_8030cc3c = 0x280;
    puVar1 = (ushort *)(DAT_8030cc8c + 2);
    DAT_8030cc3e = *puVar1 * 2;
    DAT_8030cc38 = 0x28;
    DAT_8030cc3a = 0;
    DAT_8030cc40 = 0x50;
    iVar3 = DAT_8032f100 + 0x28;
    if (iVar3 < 0x51) {
      if (iVar3 < 0) {
        iVar3 = 0;
      }
      DAT_8030cc40 = (undefined2)iVar3;
    }
    if (DAT_8030cc58 == 0) {
      iVar3 = 2;
    }
    else {
      iVar3 = 1;
    }
    iVar5 = (int)DAT_8032f102;
    DAT_8030cc42 = 0;
    if (0 < iVar5) {
      DAT_8030cc42 = DAT_8032f102;
    }
    iVar6 = (int)(short)*puVar1;
    if (DAT_8030cc3e + iVar5 + iVar6 * -2 < 1) {
      sVar9 = 0;
    }
    else {
      sVar9 = (short)(DAT_8030cc3e + iVar5) + *puVar1 * -2;
    }
    sVar8 = DAT_8032f102;
    if (-1 < iVar5) {
      sVar8 = 0;
    }
    DAT_8030cc44 = (DAT_8030cc3e + sVar8) - sVar9;
    iVar7 = iVar5;
    if (-1 < iVar5) {
      iVar7 = 0;
    }
    DAT_8030cc46 = DAT_8030cc50 - (short)(iVar7 / iVar3);
    if (DAT_8030cc3e + iVar5 + iVar6 * -2 < 1) {
      iVar6 = 0;
    }
    else {
      iVar6 = DAT_8030cc3e + iVar5 + iVar6 * -2;
    }
    if (-1 < iVar5) {
      iVar5 = 0;
    }
    DAT_8030cc48 = (DAT_8030cc54 + (short)(iVar5 / iVar3)) - (short)(iVar6 / iVar3);
    DAT_8030cc4a = 0x280;
    DAT_8030cc4c = (undefined2)((*puVar1 & 0x7fff) << 1);
    DAT_8030cc4e = 0;
    DAT_8030cc50 = 0;
    DAT_8030cc52 = 0x280;
    DAT_8030cc54 = (short)((*puVar1 & 0x7fff) << 1);
    DAT_8030cc58 = 0;
    DAT_8030cc64 = 0x28;
    DAT_8030cc65 = 0x28;
    DAT_8030cc66 = 0x28;
    DAT_8030cc74 = 0;
    DAT_8030cc78 = 1;
    DAT_8030cc7c = 0;
    DAT_8030cb4a = uVar2;
    DAT_8032f120 = DAT_8030cc8c;
    OSInitThreadQueue(&DAT_8032f0ec);
    uVar2 = DAT_cc002030;
    DAT_cc002030 = uVar2 & 0x7fff;
    uVar2 = DAT_cc002034;
    DAT_cc002034 = uVar2 & 0x7fff;
    DAT_8032f0f4 = 0;
    DAT_8032f0f8 = 0;
    __OSSetInterruptHandler(0x18,__VIRetraceHandler);
    __OSUnmaskInterrupts(0x80);
  }
  return;
}

