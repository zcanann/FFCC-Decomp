// Function: GXInitSpecularDirHA
// Entry: 801a37cc
// Size: 44 bytes

void GXInitSpecularDirHA(double param_1,double param_2,double param_3,double param_4,double param_5,
                        double param_6,int param_7)

{
  double dVar1;
  
  *(float *)(param_7 + 0x34) = (float)param_4;
  *(float *)(param_7 + 0x38) = (float)param_5;
  *(float *)(param_7 + 0x3c) = (float)param_6;
  dVar1 = (double)FLOAT_803338a0;
  *(float *)(param_7 + 0x28) = (float)(dVar1 * param_1);
  *(float *)(param_7 + 0x2c) = (float)(dVar1 * param_2);
  *(float *)(param_7 + 0x30) = (float)(dVar1 * param_3);
  return;
}

