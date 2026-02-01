// Function: SetSeBlockData__10CRedDriverFiPv
// Entry: 801bf0c4
// Size: 168 bytes

void * SetSeBlockData__10CRedDriverFiPv(undefined4 redDriver,int param_2,int param_3)

{
  void *dstBuffer;
  int count;
  
  if (param_3 == 0) {
    dstBuffer = (void *)0x0;
  }
  else {
    count = *(int *)(param_3 + 0xc);
    if (count < 1) {
      dstBuffer = (void *)0x0;
    }
    else {
      dstBuffer = (void *)RedNew__Fi(count);
      if (dstBuffer != (void *)0x0) {
        memcpy(dstBuffer,param_3,count);
      }
    }
  }
  _EntryExecCommand__FPFPi_viiiiiii(_SetSeBlockData__FPi,param_2,dstBuffer,0,0,0,0,0);
  return dstBuffer;
}

