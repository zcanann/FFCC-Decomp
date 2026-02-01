// Function: GXInitSpecularDir
// Entry: 801a36e8
// Size: 228 bytes

void GXInitSpecularDir(double param_1,double param_2,double param_3,int param_4)

{
  double dVar1;
  double dVar2;
  double dVar3;
  double dVar4;
  double dVar5;
  
  dVar1 = -param_1;
  dVar2 = -param_2;
  dVar3 = (double)(float)((double)FLOAT_80333878 - param_3);
  dVar4 = (double)((float)(dVar3 * dVar3) + (float)(dVar1 * dVar1) + (float)(dVar2 * dVar2));
  if ((double)FLOAT_80333860 != dVar4) {
    if ((double)FLOAT_80333860 < dVar4) {
      dVar5 = 1.0 / SQRT(dVar4);
      dVar5 = DOUBLE_80333890 * dVar5 * (DOUBLE_80333898 - dVar4 * dVar5 * dVar5);
      dVar5 = DOUBLE_80333890 * dVar5 * (DOUBLE_80333898 - dVar4 * dVar5 * dVar5);
      dVar4 = (double)(float)(dVar4 * DOUBLE_80333890 * dVar5 *
                                      (DOUBLE_80333898 - dVar4 * dVar5 * dVar5));
    }
    dVar4 = (double)(float)((double)FLOAT_80333878 / dVar4);
  }
  *(float *)(param_4 + 0x34) = (float)(dVar1 * dVar4);
  *(float *)(param_4 + 0x38) = (float)(dVar2 * dVar4);
  *(float *)(param_4 + 0x3c) = (float)(dVar3 * dVar4);
  dVar1 = (double)FLOAT_803338a0;
  *(float *)(param_4 + 0x28) = (float)(dVar1 * param_1);
  *(float *)(param_4 + 0x2c) = (float)(dVar1 * param_2);
  *(float *)(param_4 + 0x30) = (float)(dVar1 * param_3);
  return;
}

