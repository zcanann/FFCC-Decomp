// Function: DataAddCompute__FPiiPi
// Entry: 801c7478
// Size: 80 bytes

int DataAddCompute__FPiiPi(int *param_1,int param_2,int *param_3)

{
  int iVar1;
  
  iVar1 = 0;
  if (param_2 == *param_1 >> 0xc) {
    *param_3 = 0;
  }
  else {
    iVar1 = (int)((param_2 << 0xc | 0x800U) - *param_1) / *param_3;
  }
  return iVar1;
}

