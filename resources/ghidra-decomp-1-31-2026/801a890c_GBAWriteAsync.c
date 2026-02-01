// Function: GBAWriteAsync
// Entry: 801a890c
// Size: 148 bytes

undefined4 GBAWriteAsync(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = param_1 * 0x100;
  if (*(int *)(&DAT_8032833c + iVar1) == 0) {
    (&DAT_80328320)[iVar1] = 0x15;
    memcpy((void *)(iVar1 + -0x7fcd7cdf),param_2,4);
    *(undefined4 *)(&DAT_80328338 + iVar1) = param_2;
    *(undefined4 *)(&DAT_80328334 + iVar1) = param_3;
    *(undefined4 *)(&DAT_8032833c + iVar1) = param_4;
    uVar2 = __GBATransfer(param_1,5,1,WriteProc);
  }
  else {
    uVar2 = 2;
  }
  return uVar2;
}

