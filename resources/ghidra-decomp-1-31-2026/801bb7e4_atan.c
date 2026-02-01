// Function: atan
// Entry: 801bb7e4
// Size: 536 bytes

double atan(double param_1)

{
  uint uVar1;
  int iVar2;
  double dVar3;
  double dVar4;
  double dVar5;
  undefined8 local_8;
  
  local_8._0_4_ = (uint)((ulonglong)param_1 >> 0x20);
  uVar1 = local_8._0_4_ & 0x7fffffff;
  if (uVar1 < 0x44100000) {
    if (uVar1 < 0x3fdc0000) {
      if ((uVar1 < 0x3e200000) && (DOUBLE_80333c90 < DOUBLE_80333c88 + param_1)) {
        return param_1;
      }
      iVar2 = -1;
      local_8 = param_1;
    }
    else {
      local_8 = ABS(param_1);
      if (uVar1 < 0x3ff30000) {
        if (uVar1 < 0x3fe60000) {
          iVar2 = 0;
          local_8 = (DOUBLE_80333c98 * local_8 - DOUBLE_80333c90) / (DOUBLE_80333c98 + local_8);
        }
        else {
          iVar2 = 1;
          local_8 = (local_8 - DOUBLE_80333c90) / (DOUBLE_80333c90 + local_8);
        }
      }
      else if (uVar1 < 0x40038000) {
        iVar2 = 2;
        local_8 = (local_8 - DOUBLE_80333ca0) / (DOUBLE_80333ca0 * local_8 + DOUBLE_80333c90);
      }
      else {
        iVar2 = 3;
        local_8 = DOUBLE_80333ca8 / local_8;
      }
    }
    dVar3 = local_8 * local_8;
    dVar5 = dVar3 * dVar3;
    dVar4 = dVar5 * (dVar5 * (dVar5 * (dVar5 * (dVar5 * DAT_801e7778 + DAT_801e7768) + DAT_801e7758)
                             + DAT_801e7748) + DAT_801e7738);
    dVar3 = dVar3 * (dVar5 * (dVar5 * (dVar5 * (dVar5 * (dVar5 * DAT_801e7780 + DAT_801e7770) +
                                               DAT_801e7760) + DAT_801e7750) + DAT_801e7740) +
                    DAT_801e7730);
    if (iVar2 < 0) {
      dVar3 = -(local_8 * (dVar3 + dVar4) - local_8);
    }
    else {
      dVar3 = *(double *)(&DAT_801e76f0 + iVar2 * 8) -
              ((local_8 * (dVar3 + dVar4) - *(double *)(&DAT_801e7710 + iVar2 * 8)) - local_8);
      if ((longlong)param_1 < 0) {
        dVar3 = -dVar3;
      }
    }
  }
  else if ((uVar1 < 0x7ff00001) &&
          ((uVar1 != 0x7ff00000 || (local_8._4_4_ = SUB84(param_1,0), local_8._4_4_ == 0)))) {
    if ((int)local_8._0_4_ < 1) {
      dVar3 = -DAT_801e7708 - DAT_801e7728;
    }
    else {
      dVar3 = DAT_801e7708 + DAT_801e7728;
    }
  }
  else {
    dVar3 = param_1 + param_1;
  }
  return dVar3;
}

