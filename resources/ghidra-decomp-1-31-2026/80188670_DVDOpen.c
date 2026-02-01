// Function: DVDOpen
// Entry: 80188670
// Size: 200 bytes

undefined4 DVDOpen(undefined4 param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined auStack_88 [128];
  
  iVar1 = DVDConvertPathToEntrynum();
  if (iVar1 < 0) {
    DVDGetCurrentDir(auStack_88,0x80);
    OSReport(s_Warning__DVDOpen____file___s__wa_80217538,param_1,auStack_88);
    uVar2 = 0;
  }
  else {
    iVar1 = iVar1 * 0xc;
    if ((*(uint *)(DAT_8032f064 + iVar1) & 0xff000000) == 0) {
      uVar2 = 1;
      *(undefined4 *)(param_2 + 0x30) = *(undefined4 *)(DAT_8032f064 + iVar1 + 4);
      *(undefined4 *)(param_2 + 0x34) = *(undefined4 *)(DAT_8032f064 + iVar1 + 8);
      *(undefined4 *)(param_2 + 0x38) = 0;
      *(undefined4 *)(param_2 + 0xc) = 0;
    }
    else {
      uVar2 = 0;
    }
  }
  return uVar2;
}

