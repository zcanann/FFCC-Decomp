// Function: DVDCheckDisk
// Entry: 8018af58
// Size: 248 bytes

undefined4 DVDCheckDisk(void)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 unaff_r31;
  
  OSDisableInterrupts();
  if (DAT_8032f098 == 0) {
    if (DAT_8032f090 == 0) {
      if (DAT_8032f080 == (undefined *)0x0) {
        uVar2 = 0;
      }
      else if (DAT_8032f080 == &DAT_8030ca60) {
        uVar2 = 0;
      }
      else {
        uVar2 = *(undefined4 *)(DAT_8032f080 + 0xc);
      }
    }
    else {
      uVar2 = 8;
    }
  }
  else {
    uVar2 = 0xffffffff;
  }
  switch(uVar2) {
  case 0:
  case 8:
    uVar1 = DAT_cc006004;
    if (((uVar1 >> 2 & 1) == 0) && ((uVar1 & 1) == 0)) {
      if (DAT_8032f0a8 == 0) {
        unaff_r31 = 1;
      }
      else {
        unaff_r31 = 0;
      }
    }
    else {
      unaff_r31 = 0;
    }
    break;
  case 1:
  case 2:
  case 9:
  case 10:
    unaff_r31 = 1;
    break;
  case 0xffffffff:
  case 3:
  case 4:
  case 5:
  case 6:
  case 7:
  case 0xb:
    unaff_r31 = 0;
  }
  OSRestoreInterrupts();
  return unaff_r31;
}

