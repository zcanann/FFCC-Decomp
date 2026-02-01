// Function: GBARead
// Entry: 801a8848
// Size: 148 bytes

void GBARead(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  
  iVar1 = param_1 * 0x100;
  if (*(int *)(&DAT_8032833c + iVar1) == 0) {
    (&DAT_80328320)[iVar1] = 0x14;
    *(undefined4 *)(&DAT_80328338 + iVar1) = param_2;
    *(undefined4 *)(&DAT_80328334 + iVar1) = param_3;
    *(code **)(&DAT_8032833c + iVar1) = __GBASyncCallback;
    iVar1 = __GBATransfer(param_1,1,5,ReadProc);
  }
  else {
    iVar1 = 2;
  }
  if (iVar1 == 0) {
    __GBASync(param_1);
  }
  return;
}

