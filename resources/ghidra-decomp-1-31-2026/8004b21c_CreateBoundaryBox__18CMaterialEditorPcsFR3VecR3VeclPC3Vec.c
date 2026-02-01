// Function: CreateBoundaryBox__18CMaterialEditorPcsFR3VecR3VeclPC3Vec
// Entry: 8004b21c
// Size: 176 bytes

void CreateBoundaryBox__18CMaterialEditorPcsFR3VecR3VeclPC3Vec
               (CMaterialEditorPcs *materialEditorPcs,float *param_2,float *param_3,int param_4,
               float *param_5)

{
  float fVar1;
  float fVar2;
  
  fVar2 = FLOAT_8032fcb0;
  fVar1 = FLOAT_8032fcac;
  param_2[2] = FLOAT_8032fcac;
  param_2[1] = fVar1;
  *param_2 = fVar1;
  param_3[2] = fVar2;
  param_3[1] = fVar2;
  *param_3 = fVar2;
  if (param_4 < 1) {
    return;
  }
  do {
    if (*param_5 < *param_2) {
      *param_2 = *param_5;
    }
    if (param_5[1] < param_2[1]) {
      param_2[1] = param_5[1];
    }
    if (param_5[2] < param_2[2]) {
      param_2[2] = param_5[2];
    }
    if (*param_3 < *param_5) {
      *param_3 = *param_5;
    }
    if (param_3[1] < param_5[1]) {
      param_3[1] = param_5[1];
    }
    if (param_3[2] < param_5[2]) {
      param_3[2] = param_5[2];
    }
    param_5 = param_5 + 3;
    param_4 = param_4 + -1;
  } while (param_4 != 0);
  return;
}

