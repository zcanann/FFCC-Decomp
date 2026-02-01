// Function: GXSetDispCopyYScale
// Entry: 801a2e6c
// Size: 200 bytes

uint GXSetDispCopyYScale(double param_1)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  
  uVar2 = __cvt_fp2unsigned((double)(float)((double)FLOAT_80333850 / param_1));
  iVar1 = DAT_80333828;
  uVar2 = uVar2 & 0x1ff;
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = uVar2 | 0x4e000000;
  iVar3 = -uVar2 + 0x100;
  *(undefined2 *)(DAT_80333828 + 2) = 0;
  *(uint *)(iVar1 + 0x1ec) =
       *(uint *)(iVar1 + 0x1ec) & 0xfffffbff |
       (iVar3 - ((uint)(iVar3 == 0) + -uVar2 + 0xff)) * 0x400 & 0x3fc00;
  uVar4 = (*(uint *)(iVar1 + 0x1e4) >> 2 & 0x3ff00) / uVar2;
  uVar6 = (*(uint *)(iVar1 + 0x1e4) >> 10 & 0x3ff) + 1;
  uVar5 = uVar4 + 1;
  if ((0x80 < uVar2) && (uVar2 < 0x100)) {
    for (; (uVar2 & 1) == 0; uVar2 = uVar2 >> 1) {
    }
    if (uVar6 == (uVar6 / uVar2) * uVar2) {
      uVar5 = uVar4 + 2;
    }
  }
  if (0x400 < uVar5) {
    uVar5 = 0x400;
  }
  return uVar5;
}

