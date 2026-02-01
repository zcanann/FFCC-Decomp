// Function: THPSimpleCalcNeedMemory
// Entry: 80105174
// Size: 128 bytes

int THPSimpleCalcNeedMemory(void)

{
  int iVar1;
  
  if (SimpleControl._160_4_ != 0) {
    iVar1 = ((SimpleControl._68_4_ + 0x1f) * 8 & 0xffffff00U) +
            (SimpleControl._128_4_ * SimpleControl._132_4_ + 0x1f & 0xffffffe0) +
            (((uint)(SimpleControl._128_4_ * SimpleControl._132_4_) >> 2) + 0x1f & 0xffffffe0) * 2;
    if (SimpleControl._167_1_ != '\0') {
      iVar1 = iVar1 + (SimpleControl._72_4_ * 4 + 0x1fU & 0xffffffe0) * 3;
    }
    return iVar1 + 0x1000;
  }
  return 0;
}

