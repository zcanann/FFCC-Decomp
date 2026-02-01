// Function: WriteCallback
// Entry: 8019b1d4
// Size: 208 bytes

void WriteCallback(int param_1,int param_2)

{
  void *dstBuffer;
  code *pcVar1;
  void *dstBuffer_00;
  int iVar2;
  
  iVar2 = param_1 * 0x110;
  if (-1 < param_2) {
    dstBuffer_00 = (void *)((&DAT_803275c0)[param_1 * 0x44] + 0x2000);
    dstBuffer = (void *)((&DAT_803275c0)[param_1 * 0x44] + 0x4000);
    if (*(void **)(&DAT_803275c4 + iVar2) == dstBuffer_00) {
      *(void **)(&DAT_803275c4 + iVar2) = dstBuffer;
      memcpy(dstBuffer,dstBuffer_00,0x2000);
    }
    else {
      *(void **)(&DAT_803275c4 + iVar2) = dstBuffer_00;
      memcpy(dstBuffer_00,dstBuffer,0x2000);
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

