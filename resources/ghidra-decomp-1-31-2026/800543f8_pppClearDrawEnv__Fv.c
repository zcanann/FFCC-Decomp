// Function: pppClearDrawEnv__Fv
// Entry: 800543f8
// Size: 72 bytes

void pppClearDrawEnv__Fv(void)

{
  if (FLOAT_8032fddc != FLOAT_8032ed8c) {
    FLOAT_8032ed8c = FLOAT_8032fddc;
    ppvScreenMatrix.value[2][3] = FLOAT_8032ed60;
    GXSetProjection(&ppvScreenMatrix,0);
  }
  return;
}

