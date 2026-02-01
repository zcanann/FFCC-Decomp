// Function: pppNormalize__FR3Vec3Vec
// Entry: 800574a0
// Size: 84 bytes

void pppNormalize__FR3Vec3Vec(Vec *param_1,Vec *param_2)

{
  if (((param_2->x != FLOAT_8032fddc) || (param_2->y != FLOAT_8032fddc)) ||
     (param_2->z != FLOAT_8032fddc)) {
    PSVECNormalize(param_2,param_1);
  }
  return;
}

