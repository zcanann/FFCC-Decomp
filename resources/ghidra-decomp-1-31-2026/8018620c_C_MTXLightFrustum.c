// Function: C_MTXLightFrustum
// Entry: 8018620c
// Size: 148 bytes

void C_MTXLightFrustum(float param_1,float param_2,float param_3,float param_4,float param_5,
                      float param_6,float param_7,float param_8,Mtx *destination)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float in_stack_00000008;
  
  fVar2 = FLOAT_803336e0 / (param_4 - param_3);
  fVar1 = FLOAT_803336f0 * param_5;
  fVar3 = FLOAT_803336e0 / (param_1 - param_2);
  destination->value[0][0] = param_6 * fVar1 * fVar2;
  fVar4 = FLOAT_803336e4;
  destination->value[0][1] = FLOAT_803336e4;
  destination->value[0][2] = param_6 * fVar2 * (param_4 + param_3) - param_8;
  destination->value[0][3] = fVar4;
  destination->value[1][0] = fVar4;
  destination->value[1][1] = param_7 * fVar1 * fVar3;
  destination->value[1][2] = param_7 * fVar3 * (param_1 + param_2) - in_stack_00000008;
  destination->value[1][3] = fVar4;
  destination->value[2][0] = fVar4;
  destination->value[2][1] = fVar4;
  destination->value[2][2] = FLOAT_803336f4;
  destination->value[2][3] = fVar4;
  return;
}

