// Function: C_MTXLightPerspective
// Entry: 801862a0
// Size: 204 bytes

void C_MTXLightPerspective
               (float param_1,float param_2,float param_3,float param_4,float param_5,float param_6,
               Mtx *destination)

{
  float fVar1;
  double dVar2;
  double dVar3;
  double dVar4;
  double dVar5;
  double dVar6;
  double dVar7;
  double dVar8;
  
  dVar8 = (double)param_6;
  dVar7 = (double)param_5;
  dVar6 = (double)param_4;
  dVar4 = (double)param_3;
  dVar3 = (double)param_2;
  dVar2 = (double)tanf((double)(FLOAT_803336f8 * FLOAT_803336e8 * param_1));
  dVar5 = (double)FLOAT_803336e0;
  destination->value[0][0] =
       (float)(dVar4 * (double)(float)((double)(float)(dVar5 / dVar2) / dVar3));
  fVar1 = FLOAT_803336e4;
  destination->value[0][1] = FLOAT_803336e4;
  destination->value[0][2] = (float)-dVar7;
  destination->value[0][3] = fVar1;
  destination->value[1][0] = fVar1;
  destination->value[1][1] = (float)((double)(float)(dVar5 / dVar2) * dVar6);
  destination->value[1][2] = (float)-dVar8;
  destination->value[1][3] = fVar1;
  destination->value[2][0] = fVar1;
  destination->value[2][1] = fVar1;
  destination->value[2][2] = FLOAT_803336f4;
  destination->value[2][3] = fVar1;
  return;
}

