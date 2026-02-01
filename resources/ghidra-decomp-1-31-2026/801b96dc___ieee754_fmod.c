// Function: __ieee754_fmod
// Entry: 801b96dc
// Size: 828 bytes

double __ieee754_fmod(double param_1,double param_2)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  undefined8 local_18;
  uint local_10;
  uint uStack_c;
  
  local_10 = (uint)((ulonglong)param_2 >> 0x20);
  local_18._0_4_ = (uint)((ulonglong)param_1 >> 0x20);
  uStack_c = SUB84(param_2,0);
  uVar7 = local_10 & 0x7fffffff;
  uVar1 = local_18._0_4_ & 0x80000000;
  local_18._4_4_ = SUB84(param_1,0);
  uVar4 = local_18._0_4_ ^ uVar1;
  if (((((ulonglong)param_2 & 0x7fffffff00000000) == 0 && uStack_c == 0) ||
      (0x7fefffff < (int)uVar4)) || (0x7ff00000 < (uVar7 | (uStack_c | -uStack_c) >> 0x1f))) {
    return (param_1 * param_2) / (param_1 * param_2);
  }
  if ((int)uVar4 <= (int)uVar7) {
    if ((int)uVar4 < (int)uVar7) {
      return param_1;
    }
    if (local_18._4_4_ < uStack_c) {
      return param_1;
    }
    if (local_18._4_4_ == uStack_c) {
      return *(double *)(&DAT_801e7470 + (uVar1 >> 0x1c));
    }
  }
  if ((int)uVar4 < 0x100000) {
    if (uVar4 == 0) {
      iVar8 = -0x413;
      for (uVar6 = local_18._4_4_; 0 < (int)uVar6; uVar6 = uVar6 << 1) {
        iVar8 = iVar8 + -1;
      }
    }
    else {
      iVar8 = -0x3fe;
      for (iVar2 = local_18._0_4_ << 0xb; 0 < iVar2; iVar2 = iVar2 << 1) {
        iVar8 = iVar8 + -1;
      }
    }
  }
  else {
    iVar8 = ((int)uVar4 >> 0x14) + -0x3ff;
  }
  if (uVar7 < 0x100000) {
    if (((ulonglong)param_2 & 0x7fffffff00000000) == 0) {
      iVar2 = -0x413;
      for (uVar6 = uStack_c; 0 < (int)uVar6; uVar6 = uVar6 << 1) {
        iVar2 = iVar2 + -1;
      }
    }
    else {
      iVar2 = -0x3fe;
      for (iVar5 = uVar7 << 0xb; 0 < iVar5; iVar5 = iVar5 << 1) {
        iVar2 = iVar2 + -1;
      }
    }
  }
  else {
    iVar2 = ((int)uVar7 >> 0x14) + -0x3ff;
  }
  if (iVar8 < -0x3fe) {
    iVar5 = -iVar8 + -0x3fe;
    if (iVar5 < 0x20) {
      uVar6 = local_18._4_4_ >> 0x20 - iVar5;
      local_18._4_4_ = local_18._4_4_ << iVar5;
      uVar6 = uVar4 << iVar5 | uVar6;
    }
    else {
      uVar6 = local_18._4_4_ << -iVar8 + -0x41e;
      local_18._4_4_ = 0;
    }
  }
  else {
    uVar6 = uVar4 & 0xfffff | 0x100000;
  }
  if (iVar2 < -0x3fe) {
    iVar5 = -iVar2 + -0x3fe;
    if (iVar5 < 0x20) {
      uVar4 = uStack_c >> 0x20 - iVar5;
      uStack_c = uStack_c << iVar5;
      uVar4 = uVar7 << iVar5 | uVar4;
    }
    else {
      uVar4 = uStack_c << -iVar2 + -0x41e;
      uStack_c = 0;
    }
  }
  else {
    uVar4 = local_10 & 0xfffff | 0x100000;
  }
  iVar8 = iVar8 - iVar2;
  do {
    if (iVar8 == 0) {
      uVar4 = uVar6 - uVar4;
      if (local_18._4_4_ < uStack_c) {
        uVar4 = uVar4 - 1;
      }
      if (-1 < (int)uVar4) {
        local_18._4_4_ = local_18._4_4_ - uStack_c;
        uVar6 = uVar4;
      }
      if (uVar6 == 0 && local_18._4_4_ == 0) {
        local_18 = *(double *)(&DAT_801e7470 + (uVar1 >> 0x1c));
      }
      else {
        for (; (int)uVar6 < 0x100000; uVar6 = uVar6 * 2 - iVar8) {
          iVar8 = (int)local_18._4_4_ >> 0x1f;
          local_18._4_4_ = local_18._4_4_ * 2;
          iVar2 = iVar2 + -1;
        }
        if (iVar2 < -0x3fe) {
          uVar7 = -iVar2 - 0x3fe;
          if ((int)uVar7 < 0x15) {
            uVar3 = local_18._4_4_ >> uVar7 | uVar6 << 0x20 - uVar7;
            uVar4 = (int)uVar6 >> (uVar7 & 0x3f);
          }
          else {
            uVar4 = uVar1;
            if ((int)uVar7 < 0x20) {
              uVar3 = uVar6 << 0x20 - uVar7 | local_18._4_4_ >> uVar7;
            }
            else {
              uVar3 = (int)uVar6 >> (-iVar2 - 0x41eU & 0x3f);
            }
          }
          local_18 = (double)CONCAT44(uVar4 | uVar1,uVar3);
        }
        else {
          local_18 = (double)CONCAT44(uVar6 - 0x100000 | (iVar2 + 0x3ff) * 0x100000 | uVar1,
                                      local_18._4_4_);
        }
      }
      return local_18;
    }
    iVar5 = uVar6 - uVar4;
    uVar7 = local_18._4_4_ - uStack_c;
    if (local_18._4_4_ < uStack_c) {
      iVar5 = iVar5 + -1;
    }
    if (iVar5 < 0) {
      uVar6 = uVar6 * 2 - ((int)local_18._4_4_ >> 0x1f);
      uVar7 = local_18._4_4_;
    }
    else {
      if (iVar5 == 0 && uVar7 == 0) {
        return *(double *)(&DAT_801e7470 + (uVar1 >> 0x1c));
      }
      uVar6 = iVar5 * 2 - ((int)uVar7 >> 0x1f);
    }
    local_18._4_4_ = uVar7 * 2;
    iVar8 = iVar8 + -1;
  } while( true );
}

