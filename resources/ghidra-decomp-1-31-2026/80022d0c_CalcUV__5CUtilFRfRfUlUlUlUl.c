// Function: CalcUV__5CUtilFRfRfUlUlUlUl
// Entry: 80022d0c
// Size: 100 bytes

void CalcUV__5CUtilFRfRfUlUlUlUl
               (CUtil *util,float *param_2,float *param_3,undefined4 param_4,undefined4 param_5,
               undefined4 param_6,undefined4 param_7)

{
  double dVar1;
  double dVar2;
  
  dVar2 = DOUBLE_8032f898;
  dVar1 = (double)CONCAT44(0x43300000,param_5) - DOUBLE_8032f898;
  *param_2 = (float)((double)CONCAT44(0x43300000,param_4) - DOUBLE_8032f898) /
             (float)((double)CONCAT44(0x43300000,param_6) - DOUBLE_8032f898);
  *param_3 = (float)dVar1 / (float)((double)CONCAT44(0x43300000,param_7) - dVar2);
  return;
}

