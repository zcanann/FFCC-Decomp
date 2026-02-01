// Function: __CARDWrite
// Entry: 8019ad64
// Size: 100 bytes

undefined4 __CARDWrite(int chan,uint32_t addr,uint length,void *dst,void *callback)

{
  undefined4 uVar1;
  int iVar2;
  
  iVar2 = chan * 0x110;
  if ((&DAT_80327540)[chan * 0x44] == 0) {
    uVar1 = 0xfffffffd;
  }
  else {
    *(void **)(&DAT_80327614 + iVar2) = callback;
    *(uint *)(&DAT_803275ec + iVar2) = length >> 7;
    *(uint32_t *)(&DAT_803275f0 + iVar2) = addr;
    *(void **)(&DAT_803275f4 + iVar2) = dst;
    uVar1 = __CARDWritePage(chan,BlockWriteCallback);
  }
  return uVar1;
}

