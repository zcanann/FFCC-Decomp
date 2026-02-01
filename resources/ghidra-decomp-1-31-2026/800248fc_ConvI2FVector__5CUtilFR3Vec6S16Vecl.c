// Function: ConvI2FVector__5CUtilFR3Vec6S16Vecl
// Entry: 800248fc
// Size: 176 bytes

void ConvI2FVector__5CUtilFR3Vec6S16Vecl(CUtil *util,float *param_2,S16Vec *s16Vec,int param_4)

{
  double dVar1;
  double dVar2;
  double dVar3;
  double dVar4;
  uint uVar5;
  
  dVar4 = DOUBLE_8032f890;
  uVar5 = 1 << param_4 ^ 0x80000000;
  dVar1 = (double)CONCAT44(0x43300000,(int)s16Vec->y ^ 0x80000000) - DOUBLE_8032f890;
  dVar2 = (double)CONCAT44(0x43300000,uVar5) - DOUBLE_8032f890;
  dVar3 = (double)CONCAT44(0x43300000,(int)s16Vec->z ^ 0x80000000) - DOUBLE_8032f890;
  *param_2 = (float)((double)CONCAT44(0x43300000,(int)s16Vec->x ^ 0x80000000) - DOUBLE_8032f890) /
             (float)((double)CONCAT44(0x43300000,uVar5) - DOUBLE_8032f890);
  param_2[1] = (float)dVar1 / (float)dVar2;
  param_2[2] = (float)dVar3 / (float)((double)CONCAT44(0x43300000,uVar5) - dVar4);
  return;
}

