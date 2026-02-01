// Function: __kernel_cos
// Entry: 801ba5e8
// Size: 244 bytes

double __kernel_cos(double param_1,double param_2)

{
  double dVar1;
  double dVar2;
  undefined4 local_18;
  undefined8 local_10;
  
  local_18 = (uint)((ulonglong)param_1 >> 0x20);
  local_18 = local_18 & 0x7fffffff;
  if ((0x3e3fffff < local_18) || (dVar1 = DOUBLE_80333b90, (int)param_1 != 0)) {
    dVar2 = param_1 * param_1;
    dVar1 = dVar2 * (dVar2 * (dVar2 * (dVar2 * (dVar2 * (DOUBLE_80333bc0 * dVar2 + DOUBLE_80333bb8)
                                               + DOUBLE_80333bb0) + DOUBLE_80333ba8) +
                             DOUBLE_80333ba0) + DOUBLE_80333b98);
    if (local_18 < 0x3fd33333) {
      dVar1 = DOUBLE_80333b90 - (DOUBLE_80333bc8 * dVar2 - (dVar2 * dVar1 - param_1 * param_2));
    }
    else {
      if (local_18 < 0x3fe90001) {
        local_10 = (double)((ulonglong)(local_18 - 0x200000) << 0x20);
      }
      else {
        local_10 = DOUBLE_80333bd0;
      }
      dVar1 = (DOUBLE_80333b90 - local_10) -
              ((DOUBLE_80333bc8 * dVar2 - local_10) - (dVar2 * dVar1 - param_1 * param_2));
    }
  }
  return dVar1;
}

