// Function: THPSimpleOpen
// Entry: 80105284
// Size: 1412 bytes

/* WARNING: Removing unreachable block (ram,0x80105588) */

undefined4 THPSimpleOpen(undefined4 param_1)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  SimpleControl *pSVar4;
  uint uVar5;
  
  if (DAT_8032ee48 == 0) {
    uVar1 = 0;
  }
  else if (SimpleControl._160_4_ == 0) {
    memset(0x802ffb00,0,0xc);
    memset(0x802ffb0c,0,0x10);
    iVar2 = DVDOpen(param_1,&SimpleControl);
    if (iVar2 == 0) {
      uVar1 = 0;
    }
    else {
      while (iVar2 = DVDReadAsyncPrio(&SimpleControl,0x802ffc00,0x40,0,0,2), iVar2 == 0) {
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
      memcpy(&SimpleControl.field_0x3c,0x802ffc00,0x30);
      iVar2 = strcmp(0x802ffabc,&DAT_80331868);
      uVar1 = SimpleControl._92_4_;
      if (iVar2 == 0) {
        if (SimpleControl._64_4_ == 0x11000) {
          while (iVar2 = DVDReadAsyncPrio(&SimpleControl,0x802ffc00,0x20,uVar1,0,2), iVar2 == 0) {
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
          memcpy(&SimpleControl.field_0x6c,0x802ffc00,0x14);
          pSVar4 = &SimpleControl;
          SimpleControl._167_1_ = 0;
          iVar2 = uVar1 + 0x14;
          for (uVar5 = 0; uVar5 < (uint)SimpleControl._108_4_; uVar5 = uVar5 + 1) {
            if (pSVar4->field_0x70 == '\x01') {
              while (iVar3 = DVDReadAsyncPrio(&SimpleControl,0x802ffc00,0x20,iVar2,0,2), iVar3 == 0)
              {
                iVar3 = DVDGetCommandBlockStatus(&SimpleControl);
                if (((iVar3 == 0xb) || (iVar3 - 4U < 3)) || (iVar3 == -1)) {
                  DrawError__5CFileFR11DVDFileInfoi(&File,(DVDFileInfo *)&SimpleControl,iVar3);
                }
              }
              while (iVar3 = DVDGetCommandBlockStatus(&SimpleControl), iVar3 != 0) {
                iVar3 = DVDGetCommandBlockStatus(&SimpleControl);
                if (((iVar3 == 0xb) || (iVar3 - 4U < 3)) || (iVar3 == -1)) {
                  DrawError__5CFileFR11DVDFileInfoi(&File,(DVDFileInfo *)&SimpleControl,iVar3);
                }
              }
              memcpy(&SimpleControl.field_0x8c,0x802ffc00,0x10);
              iVar2 = iVar2 + 0x10;
              SimpleControl._167_1_ = 1;
            }
            else {
              if (pSVar4->field_0x70 != '\0') {
                return 0;
              }
              while (iVar3 = DVDReadAsyncPrio(&SimpleControl,0x802ffc00,0x20,iVar2,0,2), iVar3 == 0)
              {
                iVar3 = DVDGetCommandBlockStatus(&SimpleControl);
                if (((iVar3 == 0xb) || (iVar3 - 4U < 3)) || (iVar3 == -1)) {
                  DrawError__5CFileFR11DVDFileInfoi(&File,(DVDFileInfo *)&SimpleControl,iVar3);
                }
              }
              while (iVar3 = DVDGetCommandBlockStatus(&SimpleControl), iVar3 != 0) {
                iVar3 = DVDGetCommandBlockStatus(&SimpleControl);
                if (((iVar3 == 0xb) || (iVar3 - 4U < 3)) || (iVar3 == -1)) {
                  DrawError__5CFileFR11DVDFileInfoi(&File,(DVDFileInfo *)&SimpleControl,iVar3);
                }
              }
              memcpy(&SimpleControl.field_0x80,0x802ffc00,0xc);
              iVar2 = iVar2 + 0xc;
            }
            pSVar4 = (SimpleControl *)&pSVar4->field_0x1;
          }
          uVar1 = 1;
          SimpleControl._168_4_ = SimpleControl._100_4_;
          SimpleControl._188_4_ = SimpleControl._84_4_;
          SimpleControl._184_4_ = 0;
          SimpleControl._192_4_ = 0;
          SimpleControl._172_4_ = 0;
          SimpleControl._320_4_ = 0xffffffff;
          SimpleControl._180_4_ = 0;
          SimpleControl._360_4_ = 0;
          SimpleControl._364_4_ = 0;
          SimpleControl._164_1_ = 0;
          SimpleControl._165_1_ = 0;
          SimpleControl._166_1_ = 0;
          SimpleControl._160_4_ = 1;
          SimpleControl._196_4_ = FLOAT_8033186c;
          SimpleControl._200_4_ = FLOAT_8033186c;
          SimpleControl._208_4_ = 0;
        }
        else {
          DVDClose((DVDFileInfo *)&SimpleControl);
          uVar1 = 0;
        }
      }
      else {
        DVDClose((DVDFileInfo *)&SimpleControl);
        uVar1 = 0;
      }
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

