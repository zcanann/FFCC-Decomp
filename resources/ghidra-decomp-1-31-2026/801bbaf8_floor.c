// Function: floor
// Entry: 801bbaf8
// Size: 328 bytes

double floor(double param_1)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  undefined8 local_8;
  
  local_8._0_4_ = (uint)((ulonglong)param_1 >> 0x20);
  local_8._4_4_ = SUB84(param_1,0);
  uVar2 = local_8._0_4_ >> 0x14 & 0x7ff;
  uVar3 = uVar2 - 0x3ff;
  if ((int)uVar3 < 0x14) {
    if ((int)uVar3 < 0) {
      if (DOUBLE_80333cc0 < DOUBLE_80333cb8 + param_1) {
        if ((longlong)param_1 < 0) {
          if (((ulonglong)param_1 & 0x7fffffff00000000) != 0 || local_8._4_4_ != 0) {
            local_8._0_4_ = 0xbff00000;
            local_8._4_4_ = 0;
          }
        }
        else {
          local_8._4_4_ = 0;
          local_8._0_4_ = 0;
        }
      }
    }
    else {
      uVar2 = 0xfffff >> (uVar3 & 0x3f);
      if (local_8._4_4_ == 0 && (local_8._0_4_ & uVar2) == 0) {
        return param_1;
      }
      if (DOUBLE_80333cc0 < DOUBLE_80333cb8 + param_1) {
        if ((longlong)param_1 < 0) {
          local_8._0_4_ = local_8._0_4_ + (0x100000 >> (uVar3 & 0x3f));
        }
        local_8._0_4_ = local_8._0_4_ & ~uVar2;
        local_8._4_4_ = 0;
      }
    }
  }
  else {
    if (0x33 < (int)uVar3) {
      if (uVar3 != 0x400) {
        return param_1;
      }
      return param_1 + param_1;
    }
    uVar2 = 0xffffffff >> uVar2 - 0x413;
    if ((local_8._4_4_ & uVar2) == 0) {
      return param_1;
    }
    if (DOUBLE_80333cc0 < DOUBLE_80333cb8 + param_1) {
      uVar1 = local_8._4_4_;
      if ((longlong)param_1 < 0) {
        if (uVar3 == 0x14) {
          local_8._0_4_ = local_8._0_4_ + 1;
        }
        else {
          uVar1 = local_8._4_4_ + (1 << 0x34 - uVar3);
          if (uVar1 < local_8._4_4_) {
            local_8._0_4_ = local_8._0_4_ + 1;
          }
        }
      }
      local_8._4_4_ = uVar1 & ~uVar2;
    }
  }
  return local_8;
}

