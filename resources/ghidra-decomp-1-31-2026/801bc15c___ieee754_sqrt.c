// Function: __ieee754_sqrt
// Entry: 801bc15c
// Size: 548 bytes

double __ieee754_sqrt(double param_1)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  uint uVar9;
  uint local_18;
  uint uStack_14;
  undefined8 local_10;
  
  local_18 = (uint)((ulonglong)param_1 >> 0x20);
  uStack_14 = SUB84(param_1,0);
  if ((local_18 & 0x7ff00000) == 0x7ff00000) {
    DAT_8032f390 = 0x21;
    return param_1 * param_1 + param_1;
  }
  if ((int)local_18 < 1) {
    if (uStack_14 == 0 && ((ulonglong)param_1 & 0x7fffffff00000000) == 0) {
      return param_1;
    }
    if ((longlong)param_1 < 0) {
      DAT_8032f390 = 0x21;
      return (double)DAT_8032ec20;
    }
  }
  iVar1 = (int)local_18 >> 0x14;
  if (iVar1 == 0) {
    iVar1 = 0;
    uVar3 = uStack_14;
    while (local_18 == 0) {
      iVar1 = iVar1 + -0x15;
      local_18 = uVar3 >> 0xb;
      uVar3 = uVar3 << 0x15;
    }
    iVar4 = 0;
    for (; (local_18 & 0x100000) == 0; local_18 = local_18 << 1) {
      iVar4 = iVar4 + 1;
    }
    uStack_14 = uVar3 << iVar4;
    iVar1 = iVar1 - (iVar4 + -1);
    local_18 = local_18 | uVar3 >> 0x20 - iVar4;
  }
  uVar3 = local_18 & 0xfffff | 0x100000;
  if ((iVar1 - 0x3ffU & 1) != 0) {
    iVar4 = (int)uStack_14 >> 0x1f;
    uStack_14 = uStack_14 * 2;
    uVar3 = uVar3 * 2 - iVar4;
  }
  iVar2 = uVar3 * 2 - ((int)uStack_14 >> 0x1f);
  uVar6 = 0;
  iVar4 = 0;
  uVar7 = 0;
  uVar9 = 0;
  for (uVar3 = 0x200000; uStack_14 = uStack_14 * 2, uVar3 != 0; uVar3 = uVar3 >> 1) {
    iVar8 = iVar4 + uVar3;
    if (iVar8 <= iVar2) {
      iVar4 = iVar8 + uVar3;
      iVar2 = iVar2 - iVar8;
      uVar9 = uVar9 + uVar3;
    }
    iVar2 = iVar2 * 2 - ((int)uStack_14 >> 0x1f);
  }
  for (uVar3 = 0x80000000; uVar3 != 0; uVar3 = uVar3 >> 1) {
    uVar5 = uVar6 + uVar3;
    iVar8 = iVar4;
    if ((iVar4 < iVar2) || ((iVar4 == iVar2 && (uVar5 <= uStack_14)))) {
      uVar6 = uVar5 + uVar3;
      if (((uVar5 & 0x80000000) == 0x80000000) && ((uVar6 & 0x80000000) == 0)) {
        iVar8 = iVar4 + 1;
      }
      iVar2 = iVar2 - iVar4;
      if (uStack_14 < uVar5) {
        iVar2 = iVar2 + -1;
      }
      uStack_14 = uStack_14 - uVar5;
      uVar7 = uVar7 + uVar3;
    }
    iVar4 = (int)uStack_14 >> 0x1f;
    uStack_14 = uStack_14 * 2;
    iVar2 = iVar2 * 2 - iVar4;
    iVar4 = iVar8;
  }
  if (iVar2 != 0 || uStack_14 != 0) {
    if (uVar7 == 0xffffffff) {
      uVar7 = 0;
      uVar9 = uVar9 + 1;
    }
    else {
      uVar7 = uVar7 + (uVar7 & 1);
    }
  }
  uVar7 = uVar7 >> 1;
  if ((uVar9 & 1) == 1) {
    uVar7 = uVar7 | 0x80000000;
  }
  local_10 = (double)CONCAT44(((int)uVar9 >> 1) + 0x3fe00000 + (iVar1 + -0x3ff >> 1) * 0x100000,
                              uVar7);
  return local_10;
}

