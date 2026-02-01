// Function: MTXGetScale__5CMathFPA4_fP3Vec
// Entry: 8001b544
// Size: 360 bytes

void MTXGetScale__5CMathFPA4_fP3Vec(undefined4 param_1,Mtx *mtx,Vec *vec)

{
  double dVar1;
  Vec VStack_38;
  Vec local_2c;
  Vec local_20;
  Vec local_14;
  
  local_14.x = mtx->value[0][0];
  local_14.y = mtx->value[1][0];
  local_14.z = mtx->value[2][0];
  local_20.x = mtx->value[0][1];
  local_20.y = mtx->value[1][1];
  local_20.z = mtx->value[2][1];
  local_2c.x = mtx->value[0][2];
  local_2c.y = mtx->value[1][2];
  local_2c.z = mtx->value[2][2];
  dVar1 = (double)PSVECMag(&local_14);
  vec->x = (float)dVar1;
  PSVECNormalize(&local_14,&local_14);
  dVar1 = (double)PSVECDotProduct(&local_14,&local_20);
  PSVECScale((float)dVar1,&local_14,&VStack_38);
  PSVECSubtract(&local_20,&VStack_38,&local_20);
  dVar1 = (double)PSVECMag(&local_20);
  vec->y = (float)dVar1;
  PSVECNormalize(&local_20,&local_20);
  dVar1 = (double)PSVECDotProduct(&local_20,&local_2c);
  PSVECScale((float)dVar1,&local_20,&VStack_38);
  PSVECSubtract(&local_2c,&VStack_38,&local_2c);
  dVar1 = (double)PSVECDotProduct(&local_14,&local_2c);
  PSVECScale((float)dVar1,&local_14,&VStack_38);
  PSVECSubtract(&local_2c,&VStack_38,&local_2c);
  dVar1 = (double)PSVECMag(&local_2c);
  vec->z = (float)dVar1;
  PSVECNormalize(&local_2c,&local_2c);
  PSVECCrossProduct(&local_20,&local_2c,&VStack_38);
  dVar1 = (double)PSVECDotProduct(&local_14,&VStack_38);
  if (dVar1 < DOUBLE_8032f778) {
    PSVECScale(FLOAT_8032f744,vec,vec);
  }
  return;
}

