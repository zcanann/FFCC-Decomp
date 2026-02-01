// Function: __GBATransfer
// Entry: 801a8d04
// Size: 116 bytes

undefined4 __GBATransfer(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = param_1 * 0x100;
  uVar2 = OSDisableInterrupts();
  *(undefined4 *)(&DAT_80328358 + iVar1) = param_4;
  *(undefined4 *)(&DAT_8032832c + iVar1) = param_2;
  *(undefined4 *)(&DAT_80328330 + iVar1) = param_3;
  SIGetTypeAsync(param_1,TypeAndStatusCallback);
  OSRestoreInterrupts(uVar2);
  return 0;
}

