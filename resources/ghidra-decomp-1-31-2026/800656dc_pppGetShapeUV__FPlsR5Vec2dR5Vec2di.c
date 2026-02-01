// Function: pppGetShapeUV__FPlsR5Vec2dR5Vec2di
// Entry: 800656dc
// Size: 184 bytes

void pppGetShapeUV__FPlsR5Vec2dR5Vec2di
               (int param_1,short param_2,float *param_3,float *param_4,int param_5)

{
  float fVar1;
  double dVar2;
  int iVar3;
  
  dVar2 = DOUBLE_80330110;
  fVar1 = FLOAT_80330108;
  iVar3 = *(int *)(param_1 + *(short *)(param_1 + param_2 * 8 + 0x10) + 0xc + param_5 * 8);
  *param_3 = (float)((double)CONCAT44(0x43300000,(int)*(short *)(iVar3 + 0x13) ^ 0x80000000) -
                    DOUBLE_80330110) * FLOAT_80330108;
  param_3[1] = (float)((double)CONCAT44(0x43300000,(int)*(short *)(iVar3 + 0x15) ^ 0x80000000) -
                      dVar2) * fVar1;
  *param_4 = (float)((double)CONCAT44(0x43300000,(int)*(short *)(iVar3 + 0x3b) ^ 0x80000000) - dVar2
                    ) * fVar1;
  param_4[1] = (float)((double)CONCAT44(0x43300000,(int)*(short *)(iVar3 + 0x3d) ^ 0x80000000) -
                      dVar2) * fVar1;
  return;
}

