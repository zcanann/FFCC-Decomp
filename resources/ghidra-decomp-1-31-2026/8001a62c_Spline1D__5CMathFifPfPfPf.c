// Function: Spline1D__5CMathFifPfPfPf
// Entry: 8001a62c
// Size: 220 bytes

double Spline1D__5CMathFifPfPfPf
                 (float param_1,float period,int lastIndex,float *x_arr,float *y_arr,float *tangents
                 )

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  int iVar5;
  
  fVar1 = x_arr[lastIndex] - *x_arr;
  for (; x_arr[lastIndex] < param_1; param_1 = param_1 - fVar1) {
  }
  for (; param_1 < *x_arr; param_1 = param_1 + fVar1) {
  }
  iVar5 = 0;
  while (iVar4 = lastIndex, iVar5 < iVar4) {
    lastIndex = (iVar5 + iVar4) / 2;
    if (x_arr[lastIndex] < param_1) {
      iVar5 = lastIndex + 1;
      lastIndex = iVar4;
    }
  }
  if (0 < iVar5) {
    iVar5 = iVar5 + -1;
  }
  fVar1 = tangents[iVar5];
  fVar2 = param_1 - x_arr[iVar5];
  fVar3 = x_arr[iVar5 + 1] - x_arr[iVar5];
  return (double)(fVar2 * (fVar2 * (FLOAT_8032f758 * fVar1 +
                                   (fVar2 * (tangents[iVar5 + 1] - fVar1)) / fVar3) +
                          -(fVar3 * (FLOAT_8032f75c * fVar1 + tangents[iVar5 + 1]) -
                           (y_arr[iVar5 + 1] - y_arr[iVar5]) / fVar3)) + y_arr[iVar5]);
}

