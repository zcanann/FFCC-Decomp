// Function: __CARDEraseSector
// Entry: 80199314
// Size: 224 bytes

int __CARDEraseSector(int chan,uint addr)

{
  int iVar1;
  int iVar2;
  
  iVar2 = chan * 0x110;
  (&DAT_803275d4)[iVar2] = 0xf1;
  (&DAT_803275d5)[iVar2] = (byte)(addr >> 0x11) & 0x7f;
  (&DAT_803275d6)[iVar2] = (char)(addr >> 9);
  *(undefined4 *)(&DAT_803275e0 + iVar2) = 3;
  *(undefined4 *)(&DAT_803275e4 + iVar2) = 0xffffffff;
  *(undefined4 *)(&DAT_803275e8 + iVar2) = 3;
  iVar1 = __CARDStart(chan,0);
  if (iVar1 == -1) {
    iVar1 = 0;
  }
  else if (-1 < iVar1) {
    iVar1 = EXIImmEx(chan,&DAT_803275d4 + iVar2,*(undefined4 *)(&DAT_803275e0 + iVar2),1);
    if (iVar1 == 0) {
      *(undefined4 *)(&DAT_8032760c + iVar2) = 0;
      iVar1 = -3;
    }
    else {
      iVar1 = 0;
    }
    EXIDeselect(chan);
    EXIUnlock(chan);
  }
  return iVar1;
}

