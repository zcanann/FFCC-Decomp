// Function: GXSetFog
// Entry: 801a59bc
// Size: 540 bytes

void GXSetFog(double param_1,double param_2,double param_3,double param_4,uint param_5,
             uint3 *param_6)

{
  float fVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  double dVar6;
  float local_20;
  float local_1c;
  
  uVar3 = 0;
  uVar4 = 0;
  uVar5 = param_5 >> 3 & 1;
  if (uVar5 == 0) {
    fVar1 = FLOAT_803338e0;
    local_1c = FLOAT_803338d8;
    local_20 = FLOAT_803338d8;
    if ((param_4 != param_3) && (param_2 != param_1)) {
      local_20 = (float)(param_1 / (double)(float)(param_2 - param_1));
      fVar1 = (float)(param_4 / (double)(float)(param_4 - param_3));
      local_1c = (float)(param_4 * param_3) /
                 (float)((double)(float)(param_4 - param_3) * (double)(float)(param_2 - param_1));
    }
    iVar2 = 0;
    while (dVar6 = (double)fVar1, DOUBLE_803338e8 < dVar6) {
      iVar2 = iVar2 + 1;
      fVar1 = (float)(dVar6 * (double)FLOAT_803338e0);
    }
    for (; ((double)FLOAT_803338d8 < dVar6 && (dVar6 < DOUBLE_803338f8));
        dVar6 = (double)(float)(dVar6 * (double)FLOAT_803338f0)) {
      iVar2 = iVar2 + -1;
    }
    local_1c = local_1c /
               (float)((double)CONCAT44(0x43300000,1 << iVar2 + 1U ^ 0x80000000) - DOUBLE_80333908);
    uVar3 = __cvt_fp2unsigned((double)(float)((double)FLOAT_80333900 * dVar6));
    uVar3 = uVar3 & 0xffffff | 0xef000000;
    uVar4 = iVar2 + 1U & 0xffffff | 0xf0000000;
  }
  else if ((param_4 == param_3) || (param_2 == param_1)) {
    local_1c = FLOAT_803338d8;
    local_20 = FLOAT_803338d8;
  }
  else {
    local_20 = FLOAT_803338dc / (float)(param_2 - param_1);
    local_1c = local_20 * (float)(param_4 - param_3);
    local_20 = local_20 * (float)(param_1 - param_3);
  }
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = (uint)local_1c >> 0xc & 0x7ff | (uint)local_1c >> 0xc & 0x7f800 |
                 (uint)local_1c >> 0xc & 0x80000 | 0xee000000;
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = uVar3;
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = uVar4;
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = (uint)local_20 >> 0xc & 0x7ff | (uint)local_20 >> 0xc & 0x7f800 |
                 (uint)local_20 >> 0xc & 0x80000 | uVar5 << 0x14 | (param_5 & 7) << 0x15 |
                 0xf1000000;
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = *param_6 | 0xf2000000;
  *(undefined2 *)(DAT_80333828 + 2) = 0;
  return;
}

