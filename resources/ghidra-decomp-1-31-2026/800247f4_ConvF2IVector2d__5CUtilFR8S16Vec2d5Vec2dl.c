// Function: ConvF2IVector2d__5CUtilFR8S16Vec2d5Vec2dl
// Entry: 800247f4
// Size: 112 bytes

void ConvF2IVector2d__5CUtilFR8S16Vec2d5Vec2dl
               (CUtil *util,S16Vec2d *s16Vec2d,float *param_3,int param_4)

{
  double dVar1;
  float fVar2;
  uint uVar3;
  
  uVar3 = 1 << param_4 ^ 0x80000000;
  fVar2 = param_3[1];
  dVar1 = (double)CONCAT44(0x43300000,uVar3) - DOUBLE_8032f890;
  s16Vec2d->x = (short)(int)(*param_3 *
                            (float)((double)CONCAT44(0x43300000,uVar3) - DOUBLE_8032f890));
  s16Vec2d->y = (short)(int)(fVar2 * (float)dVar1);
  return;
}

