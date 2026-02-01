// Function: GXInitLightSpot
// Entry: 801a352c
// Size: 400 bytes

void GXInitLightSpot(double param_1,int param_2,undefined4 param_3)

{
  float fVar1;
  double dVar2;
  double dVar3;
  double dVar4;
  double dVar5;
  
  if ((param_1 <= (double)FLOAT_80333860) || ((double)FLOAT_80333864 < param_1)) {
    param_3 = 0;
  }
  dVar2 = (double)cosf((double)((float)((double)FLOAT_80333868 * param_1) / FLOAT_8033386c));
  switch(param_3) {
  default:
    dVar3 = (double)FLOAT_80333860;
    dVar5 = dVar3;
    fVar1 = FLOAT_80333878;
    break;
  case 1:
    dVar3 = (double)FLOAT_80333874;
    fVar1 = (float)((double)FLOAT_80333870 * dVar2);
    dVar5 = (double)FLOAT_80333860;
    break;
  case 2:
    dVar5 = (double)FLOAT_80333860;
    dVar3 = (double)(float)((double)FLOAT_80333878 / (double)(float)((double)FLOAT_80333878 - dVar2)
                           );
    fVar1 = (float)(-dVar2 * dVar3);
    break;
  case 3:
    dVar5 = (double)(float)((double)FLOAT_80333878 / (double)(float)((double)FLOAT_80333878 - dVar2)
                           );
    dVar3 = (double)(float)(-dVar2 * dVar5);
    fVar1 = FLOAT_80333860;
    break;
  case 4:
    fVar1 = (float)((double)FLOAT_80333878 - dVar2);
    dVar5 = (double)(float)((double)FLOAT_80333878 / (double)(fVar1 * fVar1));
    fVar1 = (float)(dVar5 * (double)(float)(dVar2 * (double)(float)(dVar2 - (double)FLOAT_8033387c))
                   );
    dVar3 = (double)(float)((double)FLOAT_8033387c * dVar5);
    dVar5 = -dVar5;
    break;
  case 5:
    dVar3 = (double)FLOAT_80333878;
    fVar1 = (float)(dVar3 / (double)((float)(dVar3 - dVar2) * (float)(dVar3 - dVar2)));
    dVar5 = (double)(FLOAT_80333880 * fVar1);
    dVar3 = (double)(FLOAT_80333884 * (float)(dVar3 + dVar2) * fVar1);
    fVar1 = (float)(dVar5 * dVar2);
    break;
  case 6:
    dVar4 = (double)FLOAT_80333878;
    fVar1 = (float)(dVar4 / (double)((float)(dVar4 - dVar2) * (float)(dVar4 - dVar2)));
    dVar3 = (double)((float)((double)FLOAT_80333884 * dVar2) * fVar1);
    dVar5 = (double)(FLOAT_80333888 * fVar1);
    fVar1 = (float)(dVar4 - (double)(fVar1 * (float)((double)(float)((double)FLOAT_8033387c * dVar2)
                                                    * dVar2)));
  }
  *(float *)(param_2 + 0x10) = fVar1;
  *(float *)(param_2 + 0x14) = (float)dVar3;
  *(float *)(param_2 + 0x18) = (float)dVar5;
  return;
}

