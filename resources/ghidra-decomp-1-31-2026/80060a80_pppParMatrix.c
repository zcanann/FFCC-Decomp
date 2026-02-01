// Function: pppParMatrix
// Entry: 80060a80
// Size: 108 bytes

void pppParMatrix(int param_1)

{
  Vec local_18;
  
  local_18.x = *(float *)(param_1 + 0x1c);
  local_18.y = *(float *)(param_1 + 0x2c);
  local_18.z = *(float *)(param_1 + 0x3c);
  PSMTXMultVec((Mtx *)(*(int *)(param_1 + 4) + 0x10),&local_18,&local_18);
  *(float *)(param_1 + 0x1c) = local_18.x;
  *(float *)(param_1 + 0x2c) = local_18.y;
  *(float *)(param_1 + 0x3c) = local_18.z;
  return;
}

