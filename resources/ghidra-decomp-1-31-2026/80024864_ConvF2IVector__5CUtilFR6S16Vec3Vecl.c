// Function: ConvF2IVector__5CUtilFR6S16Vec3Vecl
// Entry: 80024864
// Size: 152 bytes

void ConvF2IVector__5CUtilFR6S16Vec3Vecl(CUtil *util,S16Vec *s16Vec,float *param_3,int param_4)

{
  double dVar1;
  double dVar2;
  float fVar3;
  float fVar4;
  uint uVar5;
  
  uVar5 = 1 << param_4 ^ 0x80000000;
  fVar3 = param_3[1];
  fVar4 = param_3[2];
  dVar1 = (double)CONCAT44(0x43300000,uVar5) - DOUBLE_8032f890;
  dVar2 = (double)CONCAT44(0x43300000,uVar5) - DOUBLE_8032f890;
  s16Vec->x = (short)(int)(*param_3 * (float)((double)CONCAT44(0x43300000,uVar5) - DOUBLE_8032f890))
  ;
  s16Vec->y = (short)(int)(fVar3 * (float)dVar1);
  s16Vec->z = (short)(int)(fVar4 * (float)dVar2);
  return;
}

