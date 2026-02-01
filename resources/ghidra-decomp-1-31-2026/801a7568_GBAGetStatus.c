// Function: GBAGetStatus
// Entry: 801a7568
// Size: 144 bytes

void GBAGetStatus(int param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = param_1 * 0x100;
  if (*(int *)(&DAT_8032833c + iVar1) == 0) {
    (&DAT_80328320)[iVar1] = 0;
    *(undefined4 *)(&DAT_80328334 + iVar1) = param_2;
    *(code **)(&DAT_8032833c + iVar1) = __GBASyncCallback;
    iVar1 = __GBATransfer(param_1,1,3,ShortCommandProc);
  }
  else {
    iVar1 = 2;
  }
  if (iVar1 == 0) {
    __GBASync(param_1);
  }
  return;
}

