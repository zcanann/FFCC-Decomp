// Function: onCancelStat__9CGItemObjFi
// Entry: 80126eb4
// Size: 44 bytes

void onCancelStat__9CGItemObjFi(int param_1)

{
  float fVar1;
  
  fVar1 = FLOAT_80331b18;
  if (*(int *)(param_1 + 0x520) != 0x1b) {
    return;
  }
  *(uint *)(param_1 + 0x1c0) = *(uint *)(param_1 + 0x1c0) | 2;
  *(float *)(param_1 + 0x17c) = fVar1;
  *(float *)(param_1 + 0x178) = fVar1;
  *(float *)(param_1 + 0x174) = fVar1;
  return;
}

