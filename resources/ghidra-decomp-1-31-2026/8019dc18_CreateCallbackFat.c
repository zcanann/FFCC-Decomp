// Function: CreateCallbackFat
// Entry: 8019dc18
// Size: 304 bytes

void CreateCallbackFat(int param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  undefined4 extraout_r4;
  int iVar3;
  code *callback;
  void *dstBuffer;
  undefined8 uVar4;
  
  iVar3 = param_1 * 0x110;
  callback = *(code **)(&DAT_80327610 + iVar3);
  *(undefined4 *)(&DAT_80327610 + iVar3) = 0;
  if (-1 < param_2) {
    iVar2 = __CARDGetDirBlock((CARDControl *)(&DAT_80327540 + param_1 * 0x44));
    dstBuffer = (void *)(iVar2 + (uint)*(ushort *)(&DAT_803275fc + iVar3) * 0x40);
    memcpy(dstBuffer,(&DAT_8032764c)[param_1 * 0x44],4);
    memcpy((void *)((int)dstBuffer + 4),(&DAT_8032764c)[param_1 * 0x44] + 4,2);
    *(undefined *)((int)dstBuffer + 0x34) = 4;
    *(undefined *)((int)dstBuffer + 0x35) = 0;
    *(undefined2 *)((int)dstBuffer + 0x36) = *(undefined2 *)(&DAT_803275fe + iVar3);
    *(undefined *)((int)dstBuffer + 7) = 0;
    *(undefined4 *)((int)dstBuffer + 0x2c) = 0xffffffff;
    *(undefined2 *)((int)dstBuffer + 0x30) = 0;
    *(undefined2 *)((int)dstBuffer + 0x32) = 0;
    *(undefined4 *)((int)dstBuffer + 0x3c) = 0xffffffff;
    *(ushort *)((int)dstBuffer + 0x32) = *(ushort *)((int)dstBuffer + 0x32) & 0xfffc | 1;
    *(undefined4 *)(*(int *)(&DAT_80327600 + iVar3) + 8) = 0;
    *(undefined2 *)(*(int *)(&DAT_80327600 + iVar3) + 0x10) = *(undefined2 *)((int)dstBuffer + 0x36)
    ;
    uVar1 = DAT_800000f8 >> 2;
    uVar4 = OSGetTime();
    __div2i((int)((ulonglong)uVar4 >> 0x20),(int)uVar4,0,uVar1);
    *(undefined4 *)((int)dstBuffer + 0x28) = extraout_r4;
    param_2 = __CARDUpdateDir(param_1,callback);
    if (-1 < param_2) {
      return;
    }
  }
  __CARDPutControlBlock((CARDControl *)(&DAT_80327540 + param_1 * 0x44),param_2);
  if (callback != (code *)0x0) {
    (*callback)(param_1,param_2);
  }
  return;
}

