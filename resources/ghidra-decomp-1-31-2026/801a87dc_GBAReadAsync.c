// Function: GBAReadAsync
// Entry: 801a87dc
// Size: 108 bytes

undefined4 GBAReadAsync(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = param_1 * 0x100;
  if (*(int *)(&DAT_8032833c + iVar1) == 0) {
    (&DAT_80328320)[iVar1] = 0x14;
    *(undefined4 *)(&DAT_80328338 + iVar1) = param_2;
    *(undefined4 *)(&DAT_80328334 + iVar1) = param_3;
    *(undefined4 *)(&DAT_8032833c + iVar1) = param_4;
    uVar2 = __GBATransfer(param_1,1,5,ReadProc);
  }
  else {
    uVar2 = 2;
  }
  return uVar2;
}

