// Function: C_MTXPerspective
// Entry: 80186528
// Size: 208 bytes

void C_MTXPerspective(float param_1,float param_2,float param_3,float param_4,Mtx *destination)

{
  float fVar1;
  float fVar2;
  double dVar3;
  double dVar4;
  double dVar5;
  double dVar6;
  double dVar7;
  
  dVar7 = (double)param_4;
  dVar5 = (double)param_3;
  dVar4 = (double)param_2;
  dVar3 = (double)tanf((double)(FLOAT_80333714 * FLOAT_80333710 * param_1));
  dVar6 = (double)FLOAT_80333700;
  fVar1 = (float)(dVar6 / dVar3);
  destination->value[0][0] = (float)((double)fVar1 / dVar4);
  fVar2 = FLOAT_80333708;
  dVar3 = (double)(float)(dVar6 / (double)(float)(dVar7 - dVar5));
  destination->value[0][1] = FLOAT_80333708;
  destination->value[0][2] = fVar2;
  destination->value[0][3] = fVar2;
  destination->value[1][0] = fVar2;
  destination->value[1][1] = fVar1;
  destination->value[1][2] = fVar2;
  destination->value[1][3] = fVar2;
  destination->value[2][0] = fVar2;
  destination->value[2][1] = fVar2;
  destination->value[2][2] = (float)(-dVar5 * dVar3);
  destination->value[2][3] = (float)(dVar3 * -(double)(float)(dVar7 * dVar5));
  destination[1].value[0][0] = fVar2;
  destination[1].value[0][1] = fVar2;
  destination[1].value[0][2] = FLOAT_8033370c;
  destination[1].value[0][3] = fVar2;
  return;
}

