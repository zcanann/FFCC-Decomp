// Function: __CARDWritePage
// Entry: 801991f8
// Size: 284 bytes

int __CARDWritePage(int chan,void *callback)

{
  int iVar1;
  int iVar2;
  
  iVar2 = chan * 0x110;
  (&DAT_803275d4)[iVar2] = 0xf2;
  (&DAT_803275d5)[iVar2] = (byte)(*(uint *)(&DAT_803275f0 + iVar2) >> 0x11) & 0x7f;
  (&DAT_803275d6)[iVar2] = (char)(*(uint *)(&DAT_803275f0 + iVar2) >> 9);
  (&DAT_803275d7)[iVar2] = (byte)(*(uint *)(&DAT_803275f0 + iVar2) >> 7) & 3;
  (&DAT_803275d8)[iVar2] = (byte)*(undefined4 *)(&DAT_803275f0 + iVar2) & 0x7f;
  *(undefined4 *)(&DAT_803275e0 + iVar2) = 5;
  *(undefined4 *)(&DAT_803275e4 + iVar2) = 1;
  *(undefined4 *)(&DAT_803275e8 + iVar2) = 3;
  iVar1 = __CARDStart(chan,0,callback);
  if (iVar1 == -1) {
    iVar1 = 0;
  }
  else if (-1 < iVar1) {
    iVar1 = EXIImmEx(chan,&DAT_803275d4 + iVar2,*(undefined4 *)(&DAT_803275e0 + iVar2),1);
    if ((iVar1 == 0) ||
       (iVar1 = EXIDma(chan,*(undefined4 *)(&DAT_803275f4 + iVar2),0x80,
                       *(undefined4 *)(&DAT_803275e4 + iVar2),__CARDTxHandler), iVar1 == 0)) {
      *(undefined4 *)(&DAT_8032760c + iVar2) = 0;
      EXIDeselect(chan);
      EXIUnlock(chan);
      iVar1 = -3;
    }
    else {
      iVar1 = 0;
    }
  }
  return iVar1;
}

