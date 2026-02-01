// Function: GXProject
// Entry: 801a6204
// Size: 372 bytes

void GXProject(double param_1,double param_2,double param_3,float *param_4,float *param_5,
              float *param_6,float *param_7,float *param_8,float *param_9)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  
  fVar6 = FLOAT_80333918;
  fVar1 = param_4[3] +
          (float)((double)param_4[2] * param_3) +
          (float)((double)*param_4 * param_1) + (float)((double)param_4[1] * param_2);
  fVar2 = param_4[7] +
          (float)((double)param_4[6] * param_3) +
          (float)((double)param_4[4] * param_1) + (float)((double)param_4[5] * param_2);
  fVar3 = param_4[0xb] +
          (float)((double)param_4[10] * param_3) +
          (float)((double)param_4[8] * param_1) + (float)((double)param_4[9] * param_2);
  if (FLOAT_80333910 == *param_5) {
    fVar5 = fVar1 * param_5[1] + fVar3 * param_5[2];
    fVar4 = param_5[6] + fVar3 * param_5[5];
    fVar2 = fVar2 * param_5[3] + fVar3 * param_5[4];
    fVar1 = FLOAT_80333914 / -fVar3;
  }
  else {
    fVar5 = param_5[2] + fVar1 * param_5[1];
    fVar2 = param_5[4] + fVar2 * param_5[3];
    fVar4 = param_5[6] + fVar3 * param_5[5];
    fVar1 = FLOAT_80333914;
  }
  *param_7 = param_6[2] * FLOAT_80333918 + *param_6 + fVar1 * fVar5 * param_6[2] * FLOAT_80333918;
  *param_8 = param_6[3] * fVar6 + param_6[1] + fVar1 * -fVar2 * param_6[3] * fVar6;
  *param_9 = param_6[5] + fVar1 * fVar4 * (param_6[5] - param_6[4]);
  return;
}

