// Function: __GBAX02
// Entry: 801a8f20
// Size: 228 bytes

void __GBAX02(int param_1,undefined4 param_2)

{
  int iVar1;
  void *dstBuffer;
  
  iVar1 = param_1 * 0x100;
  dstBuffer = (void *)(&DAT_80328418)[param_1 * 0x40];
  memcpy(dstBuffer,param_2,4);
  *(undefined4 *)((int)dstBuffer + 4) = *(undefined4 *)(&DAT_80328360 + iVar1);
  *(undefined4 *)((int)dstBuffer + 8) = *(undefined4 *)(&DAT_80328364 + iVar1);
  *(undefined4 *)((int)dstBuffer + 0xc) = *(undefined4 *)(&DAT_8032836c + iVar1);
  *(int *)((int)dstBuffer + 0x10) = (int)dstBuffer + 0x20;
  DCInvalidateRange((int)dstBuffer + 0x20,0x20);
  DCFlushRange(dstBuffer,0x20);
  *(undefined4 *)(&DAT_803283cc + iVar1) = 0xff;
  *(undefined4 *)(&DAT_803283d4 + iVar1) = 0x21cb78;
  *(undefined4 *)(&DAT_803283d8 + iVar1) = 0x380;
  *(undefined4 *)(&DAT_803283dc + iVar1) = 0;
  *(undefined2 *)(&DAT_803283ec + iVar1) = 0x10;
  *(code **)(&DAT_803283f0 + iVar1) = F23;
  *(undefined4 *)(&DAT_803283f4 + iVar1) = 0;
  *(code **)(&DAT_803283f8 + iVar1) = F25;
  *(undefined4 *)(&DAT_803283fc + iVar1) = 0;
  DSPAddTask(iVar1 + -0x7fcd7c38);
  return;
}

