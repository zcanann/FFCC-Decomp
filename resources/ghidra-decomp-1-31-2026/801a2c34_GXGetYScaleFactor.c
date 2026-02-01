// Function: GXGetYScaleFactor
// Entry: 801a2c34
// Size: 568 bytes

double GXGetYScaleFactor(uint param_1,uint param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  double dVar7;
  double dVar8;
  double dVar9;
  double dVar10;
  double dVar11;
  
  uVar6 = param_2 & 0xffff;
  uVar2 = param_1 & 0xffff;
  dVar8 = (double)((float)((double)CONCAT44(0x43300000,uVar6) - DOUBLE_80333858) /
                  (float)((double)CONCAT44(0x43300000,uVar2) - DOUBLE_80333858));
  uVar3 = __cvt_fp2unsigned((double)(float)((double)FLOAT_80333850 / dVar8));
  uVar3 = uVar3 & 0x1ff;
  uVar1 = (uVar2 - 1) * 0x100;
  uVar4 = uVar1 / uVar3;
  uVar5 = uVar4 + 1;
  if ((0x80 < uVar3) && (uVar3 < 0x100)) {
    for (; (uVar3 & 1) == 0; uVar3 = uVar3 >> 1) {
    }
    if (uVar2 == (uVar2 / uVar3) * uVar3) {
      uVar5 = uVar4 + 2;
    }
  }
  if (0x400 < uVar5) {
    uVar5 = 0x400;
  }
  dVar10 = (double)FLOAT_80333850;
  dVar9 = DOUBLE_80333858;
  while ((param_2 & 0xffff) < uVar5) {
    uVar6 = uVar6 - 1;
    dVar8 = (double)((float)((double)CONCAT44(0x43300000,uVar6) - dVar9) /
                    (float)((double)CONCAT44(0x43300000,param_1 & 0xffff) - dVar9));
    uVar3 = __cvt_fp2unsigned((double)(float)(dVar10 / dVar8));
    uVar3 = uVar3 & 0x1ff;
    uVar4 = uVar1 / uVar3;
    uVar5 = uVar4 + 1;
    if ((0x80 < uVar3) && (uVar3 < 0x100)) {
      for (; (uVar3 & 1) == 0; uVar3 = uVar3 >> 1) {
      }
      if (uVar2 == (uVar2 / uVar3) * uVar3) {
        uVar5 = uVar4 + 2;
      }
    }
    if (0x400 < uVar5) {
      uVar5 = 0x400;
    }
  }
  dVar11 = (double)FLOAT_80333850;
  dVar9 = dVar8;
  dVar10 = DOUBLE_80333858;
  while (uVar5 < (param_2 & 0xffff)) {
    uVar6 = uVar6 + 1;
    dVar7 = (double)((float)((double)CONCAT44(0x43300000,uVar6) - dVar10) /
                    (float)((double)CONCAT44(0x43300000,param_1 & 0xffff) - dVar10));
    dVar8 = dVar9;
    uVar3 = __cvt_fp2unsigned((double)(float)(dVar11 / dVar7));
    uVar3 = uVar3 & 0x1ff;
    uVar4 = uVar1 / uVar3;
    uVar5 = uVar4 + 1;
    if ((0x80 < uVar3) && (uVar3 < 0x100)) {
      for (; (uVar3 & 1) == 0; uVar3 = uVar3 >> 1) {
      }
      if (uVar2 == (uVar2 / uVar3) * uVar3) {
        uVar5 = uVar4 + 2;
      }
    }
    dVar9 = dVar7;
    if (0x400 < uVar5) {
      uVar5 = 0x400;
    }
  }
  return dVar8;
}

