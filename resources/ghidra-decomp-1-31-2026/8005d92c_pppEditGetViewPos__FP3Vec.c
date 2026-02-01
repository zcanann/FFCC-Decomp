// Function: pppEditGetViewPos__FP3Vec
// Entry: 8005d92c
// Size: 36 bytes

void pppEditGetViewPos__FP3Vec(Vec *param_1)

{
  param_1->x = ppvCameraMatrix0.value[0][3];
  param_1->y = ppvCameraMatrix0.value[1][3];
  param_1->z = ppvCameraMatrix0.value[2][3];
  return;
}

