// Function: __CARDRead
// Entry: 8019ac24
// Size: 100 bytes

undefined4 __CARDRead(int chan,undefined4 addr,uint length,void *dest,void *callback)

{
  undefined4 uVar1;
  int iVar2;
  
  iVar2 = chan * 0x110;
  if ((&DAT_80327540)[chan * 0x44] == 0) {
    uVar1 = 0xfffffffd;
  }
  else {
    *(void **)(&DAT_80327614 + iVar2) = callback;
    *(uint *)(&DAT_803275ec + iVar2) = length >> 9;
    *(undefined4 *)(&DAT_803275f0 + iVar2) = addr;
    *(void **)(&DAT_803275f4 + iVar2) = dest;
    uVar1 = __CARDReadSegment(chan,BlockReadCallback);
  }
  return uVar1;
}

