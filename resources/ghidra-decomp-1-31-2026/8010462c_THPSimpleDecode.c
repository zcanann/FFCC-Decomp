// Function: THPSimpleDecode
// Entry: 8010462c
// Size: 1268 bytes

/* WARNING: Removing unreachable block (ram,0x8010480c) */

undefined4 THPSimpleDecode(uint param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int *piVar4;
  uint uVar5;
  SimpleControl *pSVar6;
  
  uVar2 = OSDisableInterrupts();
  if ((((*(int *)(&SimpleControl.field_0xdc + SimpleControl._184_4_ * 0xc) == 0) &&
       (SimpleControl._176_4_ == 0)) && (SimpleControl._172_4_ == 0)) &&
     (SimpleControl._164_1_ == '\x01')) {
    if (SimpleControl._80_4_ - 1 < (uint)SimpleControl._192_4_) {
      if (SimpleControl._166_1_ != '\x01') goto LAB_80104714;
      SimpleControl._192_4_ = 0;
      SimpleControl._168_4_ = SimpleControl._100_4_;
      SimpleControl._188_4_ = SimpleControl._84_4_;
    }
    SimpleControl._176_4_ = 1;
    iVar3 = DVDReadAsyncPrio(&SimpleControl,
                             *(undefined4 *)
                              (&SimpleControl.field_0xd4 + SimpleControl._184_4_ * 0xc),
                             SimpleControl._188_4_,SimpleControl._168_4_,
                             __THPSimpleDVDCallback__FlP11DVDFileInfo,2);
    if (iVar3 != 1) {
      SimpleControl._176_4_ = 0;
      SimpleControl._172_4_ = 1;
    }
  }
LAB_80104714:
  OSRestoreInterrupts(uVar2);
  if ((SimpleControl._176_4_ != 0) &&
     (((iVar3 = DVDGetCommandBlockStatus(&SimpleControl), iVar3 == 0xb || (iVar3 - 4U < 3)) ||
      (iVar3 == -1)))) {
    DrawError__5CFileFR11DVDFileInfoi(&File,(DVDFileInfo *)&SimpleControl,iVar3);
  }
  pSVar6 = &SimpleControl;
  if (*(int *)(&SimpleControl.field_0xdc + SimpleControl._180_4_ * 0xc) == 0) {
    return 2;
  }
  piVar4 = (int *)(*(int *)(&SimpleControl.field_0xd4 + SimpleControl._180_4_ * 0xc) + 8);
  iVar3 = *(int *)(&SimpleControl.field_0xd4 + SimpleControl._180_4_ * 0xc) +
          SimpleControl._108_4_ * 4 + 8;
  if (SimpleControl._167_1_ == '\0') {
    for (uVar5 = 0; uVar5 < (uint)SimpleControl._108_4_; uVar5 = uVar5 + 1) {
      if (pSVar6->field_0x70 == '\0') {
        iVar1 = THPVideoDecode(iVar3,SimpleControl._308_4_,SimpleControl._312_4_,
                               SimpleControl._316_4_,SimpleControl._156_4_);
        if (iVar1 != 0) {
          return 1;
        }
        SimpleControl._320_4_ =
             *(undefined4 *)(&SimpleControl.field_0xd8 + SimpleControl._180_4_ * 0xc);
      }
      iVar1 = *piVar4;
      piVar4 = piVar4 + 1;
      pSVar6 = (SimpleControl *)&pSVar6->field_0x1;
      iVar3 = iVar3 + iVar1;
    }
  }
  else {
    if (((int)param_1 < 0) || ((uint)SimpleControl._152_4_ <= param_1)) {
      return 4;
    }
    if (*(int *)(&SimpleControl.field_0x14c + SimpleControl._360_4_ * 0xc) != 0) {
      return 3;
    }
    for (uVar5 = 0; uVar5 < (uint)SimpleControl._108_4_; uVar5 = uVar5 + 1) {
      if (pSVar6->field_0x70 == '\x01') {
        uVar2 = THPAudioDecode(*(undefined4 *)
                                (&SimpleControl.field_0x144 + SimpleControl._360_4_ * 0xc),
                               iVar3 + *piVar4 * param_1,0);
        OSDisableInterrupts();
        *(undefined4 *)(&SimpleControl.field_0x14c + SimpleControl._360_4_ * 0xc) = uVar2;
        *(undefined4 *)(&SimpleControl.field_0x148 + SimpleControl._360_4_ * 0xc) =
             *(undefined4 *)(&SimpleControl.field_0x144 + SimpleControl._360_4_ * 0xc);
        OSRestoreInterrupts();
        SimpleControl._360_4_ = SimpleControl._360_4_ + 1;
        if (2 < (int)SimpleControl._360_4_) {
          SimpleControl._360_4_ = 0;
        }
      }
      else if (pSVar6->field_0x70 == '\0') {
        iVar1 = THPVideoDecode(iVar3,SimpleControl._308_4_,SimpleControl._312_4_,
                               SimpleControl._316_4_,SimpleControl._156_4_);
        if (iVar1 != 0) {
          return 1;
        }
        SimpleControl._320_4_ =
             *(undefined4 *)(&SimpleControl.field_0xd8 + SimpleControl._180_4_ * 0xc);
      }
      iVar1 = *piVar4;
      piVar4 = piVar4 + 1;
      pSVar6 = (SimpleControl *)&pSVar6->field_0x1;
      iVar3 = iVar3 + iVar1;
    }
  }
  *(undefined4 *)(&SimpleControl.field_0xdc + SimpleControl._180_4_ * 0xc) = 0;
  SimpleControl._180_4_ =
       SimpleControl._180_4_ + 1 & ~-(uint)(SimpleControl._180_4_ - 7 < 0x7ffffff8);
  uVar2 = OSDisableInterrupts();
  if ((((*(int *)(&SimpleControl.field_0xdc + SimpleControl._184_4_ * 0xc) == 0) &&
       (SimpleControl._176_4_ == 0)) && (SimpleControl._172_4_ == 0)) &&
     (SimpleControl._164_1_ == '\x01')) {
    if (SimpleControl._80_4_ - 1 < (uint)SimpleControl._192_4_) {
      if (SimpleControl._166_1_ != '\x01') goto LAB_80104aa8;
      SimpleControl._192_4_ = 0;
      SimpleControl._168_4_ = SimpleControl._100_4_;
      SimpleControl._188_4_ = SimpleControl._84_4_;
    }
    SimpleControl._176_4_ = 1;
    iVar3 = DVDReadAsyncPrio(&SimpleControl,
                             *(undefined4 *)
                              (&SimpleControl.field_0xd4 + SimpleControl._184_4_ * 0xc),
                             SimpleControl._188_4_,SimpleControl._168_4_,
                             __THPSimpleDVDCallback__FlP11DVDFileInfo,2);
    if (iVar3 != 1) {
      SimpleControl._176_4_ = 0;
      SimpleControl._172_4_ = 1;
    }
  }
LAB_80104aa8:
  OSRestoreInterrupts(uVar2);
  if ((SimpleControl._176_4_ != 0) &&
     (((iVar3 = DVDGetCommandBlockStatus(&SimpleControl), iVar3 == 0xb || (iVar3 - 4U < 3)) ||
      (iVar3 == -1)))) {
    DrawError__5CFileFR11DVDFileInfoi(&File,(DVDFileInfo *)&SimpleControl,iVar3);
  }
  return 0;
}

