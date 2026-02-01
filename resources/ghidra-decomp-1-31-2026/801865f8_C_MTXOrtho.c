// Function: C_MTXOrtho
// Entry: 801865f8
// Size: 152 bytes

void C_MTXOrtho(float param_1,float param_2,float param_3,float param_4,float param_5,float param_6,
               Mtx *dest)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  
  fVar5 = FLOAT_80333704;
  fVar4 = FLOAT_80333700;
  fVar1 = FLOAT_80333700 / (param_4 - param_3);
  fVar2 = FLOAT_80333700 / (param_1 - param_2);
  dest->value[0][0] = FLOAT_80333704 * fVar1;
  fVar6 = FLOAT_80333708;
  dest->value[0][1] = FLOAT_80333708;
  fVar3 = fVar4 / (param_6 - param_5);
  dest->value[0][2] = fVar6;
  dest->value[0][3] = fVar1 * -(param_4 + param_3);
  dest->value[1][0] = fVar6;
  dest->value[1][1] = fVar5 * fVar2;
  dest->value[1][2] = fVar6;
  dest->value[1][3] = fVar2 * -(param_1 + param_2);
  dest->value[2][0] = fVar6;
  dest->value[2][1] = fVar6;
  dest->value[2][2] = FLOAT_8033370c * fVar3;
  dest->value[2][3] = -param_6 * fVar3;
  dest[1].value[0][0] = fVar6;
  dest[1].value[0][1] = fVar6;
  dest[1].value[0][2] = fVar6;
  dest[1].value[0][3] = fVar4;
  return;
}

