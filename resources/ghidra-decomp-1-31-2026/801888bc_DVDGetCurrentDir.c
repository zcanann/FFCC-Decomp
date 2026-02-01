// Function: DVDGetCurrentDir
// Entry: 801888bc
// Size: 196 bytes

undefined4 DVDGetCurrentDir(int param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  
  iVar1 = DAT_8032f070;
  iVar3 = entryToPath(DAT_8032f070,param_1,param_2);
  if (iVar3 == param_2) {
    uVar2 = 0;
    *(undefined *)(param_1 + param_2 + -1) = 0;
  }
  else {
    if ((*(uint *)(DAT_8032f064 + iVar1 * 0xc) & 0xff000000) != 0) {
      if (iVar3 == param_2 + -1) {
        *(undefined *)(param_1 + iVar3) = 0;
        return 0;
      }
      *(undefined *)(param_1 + iVar3) = 0x2f;
      iVar3 = iVar3 + 1;
    }
    *(undefined *)(param_1 + iVar3) = 0;
    uVar2 = 1;
  }
  return uVar2;
}

