// Function: SetQuakeParameter__10CCameraPcsFiissffffffi
// Entry: 80039fa0
// Size: 256 bytes

void SetQuakeParameter__10CCameraPcsFiissffffffi
               (double param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,int param_7,int param_8,undefined4 param_9,undefined2 param_10,
               undefined2 param_11,int param_12)

{
  float fVar1;
  
  if (param_12 != 0) {
    *(int *)(param_7 + 0x494) = param_8;
    fVar1 = FLOAT_8032fa34;
    if (param_8 != 0) {
      *(undefined *)(param_7 + 0x490) = 2;
      *(float *)(param_7 + 0x4a4) = (float)param_1;
      *(float *)(param_7 + 0x4a8) = (float)param_2;
      *(float *)(param_7 + 0x4ac) = (float)param_3;
      *(float *)(param_7 + 0x4b0) = (float)param_4;
      *(float *)(param_7 + 0x4b4) = (float)param_5;
      *(float *)(param_7 + 0x4b8) = (float)param_6;
      return;
    }
    *(undefined *)(param_7 + 0x490) = 0;
    *(float *)(param_7 + 0x4ac) = fVar1;
    *(float *)(param_7 + 0x4a8) = fVar1;
    *(float *)(param_7 + 0x4a4) = fVar1;
    *(float *)(param_7 + 0x4b8) = fVar1;
    *(float *)(param_7 + 0x4b4) = fVar1;
    *(float *)(param_7 + 0x4b0) = fVar1;
    return;
  }
  if ((*(int *)(param_7 + 0x494) == 0) && (param_8 != 0)) {
    *(undefined4 *)(param_7 + 0x494) = 1;
    *(undefined *)(param_7 + 0x490) = 1;
    *(undefined4 *)(param_7 + 0x498) = param_9;
    *(undefined2 *)(param_7 + 0x4bc) = param_10;
    *(undefined2 *)(param_7 + 0x4be) = param_10;
    *(undefined2 *)(param_7 + 0x4c0) = param_11;
    *(undefined2 *)(param_7 + 0x4c2) = param_11;
    *(float *)(param_7 + 0x4a4) = (float)param_1;
    *(float *)(param_7 + 0x4a8) = (float)param_2;
    *(float *)(param_7 + 0x4ac) = (float)param_3;
    *(float *)(param_7 + 0x4b0) = (float)param_4;
    *(float *)(param_7 + 0x4b4) = (float)param_5;
    *(float *)(param_7 + 0x4b8) = (float)param_6;
    return;
  }
  if (*(int *)(param_7 + 0x494) != 1) {
    return;
  }
  if (param_8 != 0) {
    return;
  }
  *(undefined4 *)(param_7 + 0x494) = 0;
  *(undefined *)(param_7 + 0x490) = 1;
  *(undefined4 *)(param_7 + 0x498) = param_9;
  *(undefined2 *)(param_7 + 0x4bc) = 0;
  *(undefined2 *)(param_7 + 0x4be) = 0;
  *(undefined2 *)(param_7 + 0x4c0) = param_11;
  *(undefined2 *)(param_7 + 0x4c2) = param_11;
  *(float *)(param_7 + 0x4a4) = (float)param_1;
  *(float *)(param_7 + 0x4a8) = (float)param_2;
  *(float *)(param_7 + 0x4ac) = (float)param_3;
  *(float *)(param_7 + 0x4b0) = (float)param_4;
  *(float *)(param_7 + 0x4b4) = (float)param_5;
  *(float *)(param_7 + 0x4b8) = (float)param_6;
  return;
}

