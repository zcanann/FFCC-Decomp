// Function: BlockReadCallback
// Entry: 8019ab48
// Size: 220 bytes

void BlockReadCallback(int param_1,int param_2)

{
  code *pcVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = param_1 * 0x110;
  if (-1 < param_2) {
    *(int *)(&DAT_803275f8 + iVar3) = *(int *)(&DAT_803275f8 + iVar3) + 0x200;
    *(int *)(&DAT_803275f0 + iVar3) = *(int *)(&DAT_803275f0 + iVar3) + 0x200;
    *(int *)(&DAT_803275f4 + iVar3) = *(int *)(&DAT_803275f4 + iVar3) + 0x200;
    iVar2 = *(int *)(&DAT_803275ec + iVar3);
    *(int *)(&DAT_803275ec + iVar3) = iVar2 + -1;
    if ((0 < iVar2 + -1) && (param_2 = __CARDReadSegment(param_1,BlockReadCallback), -1 < param_2))
    {
      return;
    }
  }
  if (*(int *)(&DAT_80327610 + iVar3) == 0) {
    __CARDPutControlBlock((CARDControl *)(&DAT_80327540 + param_1 * 0x44),param_2);
  }
  pcVar1 = *(code **)(&DAT_80327614 + iVar3);
  if (pcVar1 != (code *)0x0) {
    *(undefined4 *)(&DAT_80327614 + iVar3) = 0;
    (*pcVar1)(param_1,param_2);
  }
  return;
}

