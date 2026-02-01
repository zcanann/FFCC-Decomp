// Function: GBAResetAsync
// Entry: 801a75f8
// Size: 100 bytes

undefined4 GBAResetAsync(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = param_1 * 0x100;
  if (*(int *)(&DAT_8032833c + iVar1) == 0) {
    (&DAT_80328320)[iVar1] = 0xff;
    *(undefined4 *)(&DAT_80328334 + iVar1) = param_2;
    *(undefined4 *)(&DAT_8032833c + iVar1) = param_3;
    uVar2 = __GBATransfer(param_1,1,3,ShortCommandProc);
  }
  else {
    uVar2 = 2;
  }
  return uVar2;
}

