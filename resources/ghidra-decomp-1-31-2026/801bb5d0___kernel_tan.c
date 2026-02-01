// Function: __kernel_tan
// Entry: 801bb5d0
// Size: 532 bytes

/* WARNING: Removing unreachable block (ram,0x801bb7d4) */
/* WARNING: Removing unreachable block (ram,0x801bb5d8) */

double __kernel_tan(double param_1,double param_2,uint param_3)

{
  uint uVar1;
  uint uVar2;
  double dVar3;
  double dVar4;
  undefined8 local_38;
  undefined8 local_30;
  undefined8 local_28;
  undefined8 local_20;
  
  local_38._0_4_ = (uint)((ulonglong)param_1 >> 0x20);
  uVar2 = local_38._0_4_;
  uVar1 = local_38._0_4_ & 0x7fffffff;
  if ((uVar1 < 0x3e300000) && ((int)param_1 == 0)) {
    local_38._4_4_ = SUB84(param_1,0);
    if (param_3 == 0xffffffff &&
        (((ulonglong)param_1 & 0x7fffffff00000000) == 0 && local_38._4_4_ == 0)) {
      param_1 = DOUBLE_80333c50 / ABS(param_1);
    }
    else if (param_3 != 1) {
      param_1 = DOUBLE_80333c58 / param_1;
    }
  }
  else {
    local_38 = param_1;
    if (0x3fe59427 < uVar1) {
      if ((longlong)param_1 < 0) {
        param_2 = -param_2;
        local_38 = -param_1;
      }
      local_38 = (DOUBLE_80333c60 - local_38) + (DOUBLE_80333c68 - param_2);
      param_2 = DOUBLE_80333c70;
    }
    dVar3 = local_38 * local_38;
    dVar4 = dVar3 * dVar3;
    dVar3 = DAT_801e7688 * dVar3 * local_38 +
            dVar3 * (dVar3 * local_38 *
                     (dVar4 * (dVar4 * (dVar4 * (dVar4 * (dVar4 * DAT_801e76e0 + DAT_801e76d0) +
                                                DAT_801e76c0) + DAT_801e76b0) + DAT_801e76a0) +
                      DAT_801e7690 +
                     dVar3 * (dVar4 * (dVar4 * (dVar4 * (dVar4 * (dVar4 * DAT_801e76e8 +
                                                                 DAT_801e76d8) + DAT_801e76c8) +
                                               DAT_801e76b8) + DAT_801e76a8) + DAT_801e7698)) +
                    param_2) + param_2;
    param_1 = local_38 + dVar3;
    if (uVar1 < 0x3fe59428) {
      if (param_3 != 1) {
        local_28 = (double)((ulonglong)param_1 & 0xffffffff00000000);
        local_30 = (double)((ulonglong)(DOUBLE_80333c58 / param_1) & 0xffffffff00000000);
        param_1 = (DOUBLE_80333c58 / param_1) *
                  (local_30 * (dVar3 - (local_28 - local_38)) +
                  local_30 * local_28 + DOUBLE_80333c50) + local_30;
      }
    }
    else {
      local_20 = (double)CONCAT44(0x43300000,param_3 ^ 0x80000000);
      param_1 = ((double)CONCAT44(0x43300000,1 - (uVar2 >> 0x1e & 2) ^ 0x80000000) - DOUBLE_80333c80
                ) * -(DOUBLE_80333c78 *
                      (local_38 -
                      ((param_1 * param_1) / (param_1 + (local_20 - DOUBLE_80333c80)) - dVar3)) -
                     (local_20 - DOUBLE_80333c80));
    }
  }
  return param_1;
}

