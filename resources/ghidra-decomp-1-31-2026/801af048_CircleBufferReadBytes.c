// Function: CircleBufferReadBytes
// Entry: 801af048
// Size: 264 bytes

undefined4 CircleBufferReadBytes(int *param_1,void *param_2,uint param_3)

{
  undefined4 uVar1;
  int srcBuffer;
  uint count;
  
  if ((uint)param_1[4] < param_3) {
    uVar1 = 0xffffffff;
  }
  else {
    MWEnterCriticalSection(param_1 + 6);
    srcBuffer = *param_1;
    count = param_1[3] - (srcBuffer - param_1[2]);
    if (param_3 < count) {
      memcpy(param_2,srcBuffer,param_3);
      *param_1 = *param_1 + param_3;
    }
    else {
      memcpy(param_2,srcBuffer,count);
      memcpy((void *)((int)param_2 + count),param_1[2],param_3 - count);
      *param_1 = (param_1[2] + param_3) - count;
    }
    if (param_1[3] == *param_1 - param_1[2]) {
      *param_1 = param_1[2];
    }
    param_1[5] = param_1[5] + param_3;
    param_1[4] = param_1[4] - param_3;
    MWExitCriticalSection(param_1 + 6);
    uVar1 = 0;
  }
  return uVar1;
}

