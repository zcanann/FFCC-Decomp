// Function: WriteCallback
// Entry: 8019add0
// Size: 212 bytes

void WriteCallback(int param_1,int param_2)

{
  code *pcVar1;
  void *dstBuffer;
  int iVar2;
  void *dstBuffer_00;
  
  iVar2 = param_1 * 0x110;
  if (-1 < param_2) {
    dstBuffer = (void *)((&DAT_803275c0)[param_1 * 0x44] + 0x6000);
    dstBuffer_00 = (void *)((&DAT_803275c0)[param_1 * 0x44] + 0x8000);
    if (*(void **)(&DAT_803275c8 + iVar2) == dstBuffer) {
      *(void **)(&DAT_803275c8 + iVar2) = dstBuffer_00;
      memcpy(dstBuffer_00,dstBuffer,0x2000);
    }
    else {
      *(void **)(&DAT_803275c8 + iVar2) = dstBuffer;
      memcpy(dstBuffer,dstBuffer_00,0x2000);
    }
  }
  if (*(int *)(&DAT_80327610 + iVar2) == 0) {
    __CARDPutControlBlock((CARDControl *)(&DAT_80327540 + param_1 * 0x44),param_2);
  }
  pcVar1 = *(code **)(&DAT_80327618 + iVar2);
  if (pcVar1 != (code *)0x0) {
    *(undefined4 *)(&DAT_80327618 + iVar2) = 0;
    (*pcVar1)(param_1,param_2);
  }
  return;
}

