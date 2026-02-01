// Function: GXSetViewportJitter
// Entry: 801a66d8
// Size: 260 bytes

void GXSetViewportJitter(double param_1,double param_2,double param_3,double param_4,double param_5,
                        double param_6,int param_7)

{
  int iVar1;
  float fVar2;
  double dVar3;
  double dVar4;
  double dVar5;
  double dVar6;
  double dVar7;
  double dVar8;
  
  fVar2 = FLOAT_80333928;
  iVar1 = DAT_80333828;
  if (param_7 == 0) {
    param_2 = (double)(float)(param_2 - (double)FLOAT_80333918);
  }
  dVar4 = (double)FLOAT_80333918;
  dVar3 = (double)FLOAT_8033392c;
  dVar8 = (double)(float)(param_3 * dVar4);
  *(float *)(DAT_80333828 + 0x43c) = (float)param_1;
  dVar7 = (double)(float)(dVar3 * param_6);
  *(float *)(iVar1 + 0x440) = (float)param_2;
  *(float *)(iVar1 + 0x444) = (float)param_3;
  dVar6 = (double)(float)(-param_4 * dVar4);
  *(float *)(iVar1 + 0x448) = (float)param_4;
  dVar5 = (double)(fVar2 + (float)(param_1 + dVar8));
  *(float *)(iVar1 + 0x44c) = (float)param_5;
  dVar4 = (double)(fVar2 + (float)(param_2 + (double)(float)(param_4 * dVar4)));
  dVar3 = (double)(float)(dVar7 - (double)(float)(dVar3 * param_5));
  *(float *)(iVar1 + 0x450) = (float)param_6;
  if (*(char *)(iVar1 + 0x454) != '\0') {
    __GXSetRange(param_5,(double)*(float *)(iVar1 + 0x458));
  }
  DAT_cc008000._0_1_ = 0x10;
  DAT_cc008000 = 0x5101a;
  DAT_cc008000 = (float)dVar8;
  DAT_cc008000 = (float)dVar6;
  DAT_cc008000 = (float)dVar3;
  DAT_cc008000 = (float)dVar5;
  DAT_cc008000 = (float)dVar4;
  DAT_cc008000 = (float)dVar7;
  *(undefined2 *)(DAT_80333828 + 2) = 1;
  return;
}

