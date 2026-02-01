// Function: VerifyID
// Entry: 8019b5e0
// Size: 644 bytes

undefined4 VerifyID(int param_1)

{
  ushort uVar1;
  ushort *puVar2;
  undefined4 uVar3;
  int iVar4;
  ushort uVar5;
  uint extraout_r4;
  ushort uVar6;
  ushort *puVar7;
  uint uVar8;
  byte *pbVar9;
  int iVar10;
  int iVar11;
  ulonglong uVar12;
  
  puVar2 = *(ushort **)(param_1 + 0x80);
  if ((puVar2[0x10] == 0) && (puVar2[0x11] == *(ushort *)(param_1 + 8))) {
    uVar6 = 0;
    uVar5 = 0;
    iVar11 = 0x1f;
    puVar7 = puVar2;
    do {
      uVar5 = uVar5 + *puVar7 + puVar7[1] + puVar7[2] + puVar7[3] + puVar7[4] + puVar7[5] +
              puVar7[6] + puVar7[7];
      uVar6 = uVar6 + ~*puVar7 + ~puVar7[1] + ~puVar7[2] + ~puVar7[3] + ~puVar7[4] + ~puVar7[5] +
              ~puVar7[6] + ~puVar7[7];
      puVar7 = puVar7 + 8;
      iVar11 = iVar11 + -1;
    } while (iVar11 != 0);
    iVar11 = 6;
    do {
      uVar1 = *puVar7;
      puVar7 = puVar7 + 1;
      uVar5 = uVar5 + uVar1;
      uVar6 = uVar6 + ~uVar1;
      iVar11 = iVar11 + -1;
    } while (iVar11 != 0);
    if (uVar5 == 0xffff) {
      uVar5 = 0;
    }
    if (uVar6 == 0xffff) {
      uVar6 = 0;
    }
    if ((puVar2[0xfe] == uVar5) && (puVar2[0xff] == uVar6)) {
      iVar10 = *(int *)(puVar2 + 6);
      uVar8 = *(uint *)(puVar2 + 8);
      iVar4 = __OSLockSramEx();
      iVar11 = (param_1 + 0x7fcd8ac0) / 0x110 + (param_1 + 0x7fcd8ac0 >> 0x1f);
      pbVar9 = (byte *)(iVar4 + (iVar11 - (iVar11 >> 0x1f)) * 0xc);
      iVar11 = 0;
      puVar7 = puVar2;
      do {
        uVar12 = __shr2i(iVar10 * 0x41c64e6d + (int)((ulonglong)uVar8 * 0x41c64e6d >> 0x20) +
                         (uint)(0xffffcfc6 < uVar8 * 0x41c64e6d),uVar8 * 0x41c64e6d + 0x3039,0x10);
        if ((uint)*(byte *)puVar7 != ((int)uVar12 + (uint)*pbVar9 & 0xff)) {
          __OSUnlockSramEx(0);
          return 0xfffffffa;
        }
        uVar8 = (int)uVar12 * 0x41c64e6d;
        __shr2i((int)(uVar12 >> 0x20) * 0x41c64e6d +
                (int)((uVar12 & 0xffffffff) * 0x41c64e6d >> 0x20) + (uint)(0xffffcfc6 < uVar8),
                uVar8 + 0x3039,0x10);
        iVar11 = iVar11 + 1;
        uVar8 = extraout_r4 & 0x7fff;
        iVar10 = 0;
        pbVar9 = pbVar9 + 1;
        puVar7 = (ushort *)((int)puVar7 + 1);
      } while (iVar11 < 0xc);
      __OSUnlockSramEx(0);
      uVar5 = __CARDGetFontEncode();
      if (puVar2[0x12] == uVar5) {
        uVar3 = 0;
      }
      else {
        uVar3 = 0xfffffff3;
      }
    }
    else {
      uVar3 = 0xfffffffa;
    }
  }
  else {
    uVar3 = 0xfffffffa;
  }
  return uVar3;
}

