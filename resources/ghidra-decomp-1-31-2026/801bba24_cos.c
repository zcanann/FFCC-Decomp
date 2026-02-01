// Function: cos
// Entry: 801bba24
// Size: 212 bytes

/* WARNING: Removing unreachable block (ram,0x801bba8c) */

double cos(double param_1)

{
  uint uVar1;
  uint local_18;
  undefined8 local_10;
  undefined8 local_8;
  
  local_18 = (uint)((ulonglong)param_1 >> 0x20);
  if ((local_18 & 0x7fffffff) < 0x3fe921fc) {
    param_1 = (double)__kernel_cos(param_1,DOUBLE_80333cb0);
  }
  else if ((local_18 & 0x7fffffff) < 0x7ff00000) {
    uVar1 = __ieee754_rem_pio2(&local_10);
    uVar1 = uVar1 & 3;
    if (uVar1 == 1) {
      param_1 = (double)__kernel_sin(local_10,local_8,1);
      param_1 = -param_1;
    }
    else if (uVar1 == 0) {
      param_1 = (double)__kernel_cos(local_10,local_8);
    }
    else if (uVar1 < 3) {
      param_1 = (double)__kernel_cos(local_10,local_8);
      param_1 = -param_1;
    }
    else {
      param_1 = (double)__kernel_sin(local_10,local_8,1);
    }
  }
  else {
    param_1 = param_1 - param_1;
  }
  return param_1;
}

