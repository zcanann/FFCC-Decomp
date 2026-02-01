// Function: __CARDUpdateDir
// Entry: 8019b36c
// Size: 196 bytes

undefined4 __CARDUpdateDir(int chan,void *callback)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = chan * 0x110;
  if ((&DAT_80327540)[chan * 0x44] == 0) {
    uVar1 = 0xfffffffd;
  }
  else {
    iVar3 = *(int *)(&DAT_803275c4 + iVar2);
    *(short *)(iVar3 + 0x1ffa) = *(short *)(iVar3 + 0x1ffa) + 1;
    __CARDCheckSum(iVar3,0x1ffc,iVar3 + 0x1ffc,iVar3 + 0x1ffe);
    DCStoreRange(iVar3,0x2000);
    *(void **)(&DAT_80327618 + iVar2) = callback;
    uVar1 = __CARDEraseSector(chan,*(int *)(&DAT_8032754c + iVar2) *
                                   ((uint)(iVar3 - (&DAT_803275c0)[chan * 0x44]) >> 0xd),
                              EraseCallback);
  }
  return uVar1;
}

