// Function: __kernel_sin
// Entry: 801bb530
// Size: 160 bytes

double __kernel_sin(double param_1,double param_2,int param_3)

{
  double dVar1;
  double dVar2;
  double dVar3;
  undefined4 local_18;
  
  local_18 = (uint)((ulonglong)param_1 >> 0x20);
  if ((0x3e3fffff < (local_18 & 0x7fffffff)) || ((int)param_1 != 0)) {
    dVar3 = param_1 * param_1;
    dVar2 = dVar3 * param_1;
    dVar1 = dVar3 * (dVar3 * (dVar3 * (DOUBLE_80333c38 * dVar3 + DOUBLE_80333c30) + DOUBLE_80333c28)
                    + DOUBLE_80333c20) + DOUBLE_80333c18;
    if (param_3 == 0) {
      param_1 = dVar2 * (dVar3 * dVar1 + DOUBLE_80333c40) + param_1;
    }
    else {
      param_1 = param_1 - -(DOUBLE_80333c40 * dVar2 -
                           (dVar3 * (DOUBLE_80333c48 * param_2 - dVar2 * dVar1) - param_2));
    }
  }
  return param_1;
}

