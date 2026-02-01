// Function: tan
// Entry: 801bc064
// Size: 120 bytes

double tan(double param_1)

{
  uint uVar1;
  uint local_18;
  undefined8 local_10;
  undefined8 local_8;
  
  local_18 = (uint)((ulonglong)param_1 >> 0x20);
  if ((local_18 & 0x7fffffff) < 0x3fe921fc) {
    param_1 = (double)__kernel_tan(param_1,DOUBLE_80333d00,1);
  }
  else if ((local_18 & 0x7fffffff) < 0x7ff00000) {
    uVar1 = __ieee754_rem_pio2(&local_10);
    param_1 = (double)__kernel_tan(local_10,local_8,(uVar1 & 1) * -2 + 1);
  }
  else {
    param_1 = param_1 - param_1;
  }
  return param_1;
}

