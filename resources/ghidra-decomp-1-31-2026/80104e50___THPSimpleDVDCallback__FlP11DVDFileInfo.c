// Function: __THPSimpleDVDCallback__FlP11DVDFileInfo
// Entry: 80104e50
// Size: 380 bytes

void __THPSimpleDVDCallback__FlP11DVDFileInfo(int param_1)

{
  int iVar1;
  
  if (param_1 == -1) {
    SimpleControl._172_4_ = 1;
  }
  else if (param_1 != -3) {
    SimpleControl._176_4_ = 0;
    *(undefined4 *)(&SimpleControl.field_0xd8 + SimpleControl._184_4_ * 0xc) = SimpleControl._192_4_
    ;
    SimpleControl._192_4_ = SimpleControl._192_4_ + 1;
    *(undefined4 *)(&SimpleControl.field_0xdc + SimpleControl._184_4_ * 0xc) = 1;
    SimpleControl._168_4_ = SimpleControl._168_4_ + SimpleControl._188_4_;
    iVar1 = SimpleControl._184_4_ * 0xc;
    SimpleControl._184_4_ =
         SimpleControl._184_4_ + 1 & ~-(uint)(SimpleControl._184_4_ - 7 < 0x7ffffff8);
    SimpleControl._188_4_ = **(undefined4 **)(&SimpleControl.field_0xd4 + iVar1);
    if (((*(int *)(&SimpleControl.field_0xdc + SimpleControl._184_4_ * 0xc) == 0) &&
        (SimpleControl._172_4_ == 0)) && (SimpleControl._164_1_ == '\x01')) {
      if (SimpleControl._80_4_ - 1 < (uint)SimpleControl._192_4_) {
        if (SimpleControl._166_1_ != '\x01') {
          return;
        }
        SimpleControl._192_4_ = 0;
        SimpleControl._168_4_ = SimpleControl._100_4_;
        SimpleControl._188_4_ = SimpleControl._84_4_;
      }
      SimpleControl._176_4_ = 1;
      iVar1 = DVDReadAsyncPrio(&SimpleControl,
                               *(undefined4 *)
                                (&SimpleControl.field_0xd4 + SimpleControl._184_4_ * 0xc),
                               SimpleControl._188_4_,SimpleControl._168_4_,
                               __THPSimpleDVDCallback__FlP11DVDFileInfo,2);
      if (iVar1 != 1) {
        SimpleControl._176_4_ = 0;
        SimpleControl._172_4_ = 1;
      }
    }
  }
  return;
}

