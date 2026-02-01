// Function: EraseCallback
// Entry: 8019e598
// Size: 176 bytes

void EraseCallback(int param_1,int param_2)

{
  int iVar1;
  code *pcVar2;
  
  iVar1 = param_1 * 0x110;
  if ((param_2 < 0) ||
     (param_2 = __CARDWrite(param_1,*(int *)(&DAT_8032754c + iVar1) *
                                    (uint)*(ushort *)(*(int *)(&DAT_80327600 + iVar1) + 0x10),
                            *(int *)(&DAT_8032754c + iVar1),*(void **)(&DAT_803275f4 + iVar1),
                            WriteCallback), param_2 < 0)) {
    pcVar2 = *(code **)(&DAT_80327610 + iVar1);
    *(undefined4 *)(&DAT_80327610 + iVar1) = 0;
    __CARDPutControlBlock((CARDControl *)(&DAT_80327540 + param_1 * 0x44),param_2);
    (*pcVar2)(param_1,param_2);
  }
  return;
}

