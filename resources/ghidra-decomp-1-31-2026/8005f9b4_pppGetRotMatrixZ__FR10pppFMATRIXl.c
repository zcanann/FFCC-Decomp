// Function: pppGetRotMatrixZ__FR10pppFMATRIXl
// Entry: 8005f9b4
// Size: 92 bytes

void pppGetRotMatrixZ__FR10pppFMATRIXl(pppFMATRIX *pppFMtx,uint angle)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  
  fVar4 = FLOAT_8032fec4;
  fVar3 = FLOAT_8032fec0;
  fVar1 = *(float *)((int)ppvSinTbl + (angle & 0xfffc));
  fVar2 = *(float *)((int)ppvSinTbl + (angle + 0x4000 & 0xfffc));
  pppFMtx->value[0][0] = fVar2;
  pppFMtx->value[0][1] = -fVar1;
  pppFMtx->value[0][2] = fVar3;
  pppFMtx->value[0][3] = fVar3;
  pppFMtx->value[1][0] = fVar1;
  pppFMtx->value[1][1] = fVar2;
  pppFMtx->value[1][2] = fVar3;
  pppFMtx->value[1][3] = fVar3;
  pppFMtx->value[2][0] = fVar3;
  pppFMtx->value[2][1] = fVar3;
  pppFMtx->value[2][2] = fVar4;
  pppFMtx->value[2][3] = fVar3;
  return;
}

