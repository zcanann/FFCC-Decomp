// Function: __CARDMountCallback
// Entry: 8019c9c4
// Size: 312 bytes

void __CARDMountCallback(int chan,int result)

{
  int iVar1;
  int iVar2;
  code *pcVar3;
  
  iVar2 = chan * 0x110;
  if (result != -3) {
    if (-4 < result) {
      if (result == 1) {
        *(code **)(&DAT_8032761c + iVar2) = __CARDMountCallback;
        iVar1 = EXILock(chan,0,__CARDUnlockedHandler);
        if (iVar1 == 0) {
          return;
        }
        *(undefined4 *)(&DAT_8032761c + iVar2) = 0;
        result = DoMount(chan);
      }
      else {
        if ((0 < result) || (result < 0)) goto LAB_8019cab0;
        iVar1 = *(int *)(&DAT_80327564 + iVar2);
        *(int *)(&DAT_80327564 + iVar2) = iVar1 + 1;
        if (6 < iVar1 + 1) {
          result = __CARDVerify((CARDControl *)(&DAT_80327540 + chan * 0x44));
          goto LAB_8019cab0;
        }
        result = DoMount(chan);
      }
      if (-1 < result) {
        return;
      }
      goto LAB_8019cab0;
    }
    if (result != -5) goto LAB_8019cab0;
  }
  DoUnmount(chan,result);
LAB_8019cab0:
  pcVar3 = *(code **)(&DAT_80327610 + iVar2);
  *(undefined4 *)(&DAT_80327610 + iVar2) = 0;
  __CARDPutControlBlock((CARDControl *)(&DAT_80327540 + chan * 0x44),result);
  (*pcVar3)(chan,result);
  return;
}

