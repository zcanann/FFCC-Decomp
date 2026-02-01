// Function: C_MTXLightOrtho
// Entry: 8018636c
// Size: 136 bytes

void C_MTXLightOrtho(float param_1,float param_2,float param_3,float param_4,float param_5,
                    float param_6,float param_7,float param_8,Mtx *destination)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  
  fVar5 = FLOAT_803336f0;
  fVar3 = FLOAT_803336e0;
  fVar1 = FLOAT_803336e0 / (param_4 - param_3);
  fVar2 = FLOAT_803336e0 / (param_1 - param_2);
  destination->value[0][0] = FLOAT_803336f0 * fVar1 * param_5;
  fVar4 = FLOAT_803336e4;
  destination->value[0][1] = FLOAT_803336e4;
  destination->value[0][2] = fVar4;
  destination->value[0][3] = param_7 + param_5 * fVar1 * -(param_4 + param_3);
  destination->value[1][0] = fVar4;
  destination->value[1][1] = fVar5 * fVar2 * param_6;
  destination->value[1][2] = fVar4;
  destination->value[1][3] = param_8 + param_6 * fVar2 * -(param_1 + param_2);
  destination->value[2][0] = fVar4;
  destination->value[2][1] = fVar4;
  destination->value[2][2] = fVar4;
  destination->value[2][3] = fVar3;
  return;
}

