// Function: THPSimplePreLoad
// Entry: 80104c30
// Size: 544 bytes

undefined4 THPSimplePreLoad(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  uint uVar5;
  uint uVar6;
  
  if ((SimpleControl._160_4_ == 0) || (SimpleControl._164_1_ != '\0')) {
    uVar3 = 0;
  }
  else {
    uVar5 = 8;
    if ((param_1 == 0) && ((uint)SimpleControl._80_4_ < 8)) {
      uVar5 = SimpleControl._80_4_;
    }
    for (uVar6 = 0; uVar1 = SimpleControl._188_4_, uVar3 = SimpleControl._168_4_, uVar6 < uVar5;
        uVar6 = uVar6 + 1) {
      uVar4 = *(undefined4 *)(&SimpleControl.field_0xd4 + SimpleControl._184_4_ * 0xc);
      while (iVar2 = DVDReadAsyncPrio(&SimpleControl,uVar4,uVar1,uVar3,0,2), iVar2 == 0) {
        iVar2 = DVDGetCommandBlockStatus(&SimpleControl);
        if (((iVar2 == 0xb) || (iVar2 - 4U < 3)) || (iVar2 == -1)) {
          DrawError__5CFileFR11DVDFileInfoi(&File,(DVDFileInfo *)&SimpleControl,iVar2);
        }
      }
      while (iVar2 = DVDGetCommandBlockStatus(&SimpleControl), iVar2 != 0) {
        iVar2 = DVDGetCommandBlockStatus(&SimpleControl);
        if (((iVar2 == 0xb) || (iVar2 - 4U < 3)) || (iVar2 == -1)) {
          DrawError__5CFileFR11DVDFileInfoi(&File,(DVDFileInfo *)&SimpleControl,iVar2);
        }
      }
      SimpleControl._168_4_ = SimpleControl._168_4_ + SimpleControl._188_4_;
      SimpleControl._188_4_ =
           **(undefined4 **)(&SimpleControl.field_0xd4 + SimpleControl._184_4_ * 0xc);
      *(undefined4 *)(&SimpleControl.field_0xdc + SimpleControl._184_4_ * 0xc) = 1;
      *(undefined4 *)(&SimpleControl.field_0xd8 + SimpleControl._184_4_ * 0xc) =
           SimpleControl._192_4_;
      SimpleControl._192_4_ = SimpleControl._192_4_ + 1;
      SimpleControl._184_4_ =
           SimpleControl._184_4_ + 1 & ~-(uint)(SimpleControl._184_4_ - 7 < 0x7ffffff8);
      if ((SimpleControl._80_4_ - 1 < (uint)SimpleControl._192_4_) &&
         (SimpleControl._166_1_ == '\x01')) {
        SimpleControl._192_4_ = 0;
        SimpleControl._168_4_ = SimpleControl._100_4_;
        SimpleControl._188_4_ = SimpleControl._84_4_;
      }
    }
    SimpleControl._166_1_ = (undefined)param_1;
    uVar3 = 1;
    SimpleControl._164_1_ = 1;
  }
  return uVar3;
}

