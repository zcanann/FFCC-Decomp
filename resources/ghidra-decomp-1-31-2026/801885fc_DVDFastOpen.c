// Function: DVDFastOpen
// Entry: 801885fc
// Size: 116 bytes

undefined4 DVDFastOpen(uint param_1,int param_2)

{
  int iVar1;
  
  if (((-1 < (int)param_1) && (param_1 < DAT_8032f06c)) &&
     (iVar1 = param_1 * 0xc, (*(uint *)(DAT_8032f064 + iVar1) & 0xff000000) == 0)) {
    *(undefined4 *)(param_2 + 0x30) = *(undefined4 *)(DAT_8032f064 + iVar1 + 4);
    *(undefined4 *)(param_2 + 0x34) = *(undefined4 *)(DAT_8032f064 + iVar1 + 8);
    *(undefined4 *)(param_2 + 0x38) = 0;
    *(undefined4 *)(param_2 + 0xc) = 0;
    return 1;
  }
  return 0;
}

