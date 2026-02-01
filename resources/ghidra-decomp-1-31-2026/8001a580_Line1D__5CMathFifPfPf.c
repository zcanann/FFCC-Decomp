// Function: Line1D__5CMathFifPfPf
// Entry: 8001a580
// Size: 172 bytes

double Line1D__5CMathFifPfPf(float x,float period,int lastIndex,float *x_arr,float *y_arr)

{
  float fVar1;
  int iVar2;
  int iVar3;
  
  fVar1 = x_arr[lastIndex] - *x_arr;
  for (; x_arr[lastIndex] < x; x = x - fVar1) {
  }
  for (; x < *x_arr; x = x + fVar1) {
  }
  iVar3 = 0;
  while (iVar2 = lastIndex, iVar3 < iVar2) {
    lastIndex = (iVar3 + iVar2) / 2;
    if (x_arr[lastIndex] < x) {
      iVar3 = lastIndex + 1;
      lastIndex = iVar2;
    }
  }
  if (0 < iVar3) {
    iVar3 = iVar3 + -1;
  }
  return (double)(((x - x_arr[iVar3]) / (x_arr[iVar3 + 1] - x_arr[iVar3])) *
                  (y_arr[iVar3 + 1] - y_arr[iVar3]) + y_arr[iVar3]);
}

