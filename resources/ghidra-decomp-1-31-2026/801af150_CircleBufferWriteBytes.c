// Function: CircleBufferWriteBytes
// Entry: 801af150
// Size: 264 bytes

undefined4 CircleBufferWriteBytes(int param_1,int param_2,uint param_3)

{
  undefined4 uVar1;
  void *dstBuffer;
  uint count;
  
  if (*(uint *)(param_1 + 0x14) < param_3) {
    uVar1 = 0xffffffff;
  }
  else {
    MWEnterCriticalSection(param_1 + 0x18);
    dstBuffer = *(void **)(param_1 + 4);
    count = *(int *)(param_1 + 0xc) - ((int)dstBuffer - *(int *)(param_1 + 8));
    if (count < param_3) {
      memcpy(dstBuffer,param_2,count);
      memcpy(*(void **)(param_1 + 8),param_2 + count,param_3 - count);
      *(uint *)(param_1 + 4) = (*(int *)(param_1 + 8) + param_3) - count;
    }
    else {
      memcpy(dstBuffer,param_2,param_3);
      *(uint *)(param_1 + 4) = *(int *)(param_1 + 4) + param_3;
    }
    if (*(int *)(param_1 + 0xc) == *(int *)(param_1 + 4) - *(int *)(param_1 + 8)) {
      *(int *)(param_1 + 4) = *(int *)(param_1 + 8);
    }
    *(uint *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) - param_3;
    *(uint *)(param_1 + 0x10) = *(int *)(param_1 + 0x10) + param_3;
    MWExitCriticalSection(param_1 + 0x18);
    uVar1 = 0;
  }
  return uVar1;
}

