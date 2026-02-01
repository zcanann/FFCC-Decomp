// Function: DeleteCallback
// Entry: 8019e7a4
// Size: 164 bytes

void DeleteCallback(int param_1,int param_2)

{
  int iVar1;
  code *pcVar2;
  
  iVar1 = param_1 * 0x110;
  pcVar2 = *(code **)(&DAT_80327610 + iVar1);
  *(undefined4 *)(&DAT_80327610 + iVar1) = 0;
  if (((param_2 < 0) ||
      (param_2 = __CARDFreeBlock(param_1,*(undefined2 *)(&DAT_803275fe + iVar1),pcVar2), param_2 < 0
      )) && (__CARDPutControlBlock((CARDControl *)(&DAT_80327540 + param_1 * 0x44),param_2),
            pcVar2 != (code *)0x0)) {
    (*pcVar2)(param_1,param_2);
  }
  return;
}

