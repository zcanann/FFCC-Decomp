// Function: CircleBufferInitialize
// Entry: 801af258
// Size: 80 bytes

void CircleBufferInitialize(undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  param_1[2] = param_2;
  param_1[3] = param_3;
  *param_1 = param_1[2];
  param_1[1] = param_1[2];
  param_1[4] = 0;
  param_1[5] = param_1[3];
  MWInitializeCriticalSection(param_1 + 6);
  return;
}

