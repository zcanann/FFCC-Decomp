// Function: EraseCallback
// Entry: 8019b2a4
// Size: 200 bytes

void EraseCallback(int param_1,int param_2)

{
  code *pcVar1;
  int iVar2;
  
  iVar2 = param_1 * 0x110;
  if ((param_2 < 0) ||
     (param_2 = __CARDWrite(param_1,*(int *)(&DAT_8032754c + iVar2) *
                                    ((uint)((int)*(void **)(&DAT_803275c4 + iVar2) -
                                           (&DAT_803275c0)[param_1 * 0x44]) >> 0xd),0x2000,
                            *(void **)(&DAT_803275c4 + iVar2),WriteCallback), param_2 < 0)) {
    if (*(int *)(&DAT_80327610 + iVar2) == 0) {
      __CARDPutControlBlock((CARDControl *)(&DAT_80327540 + param_1 * 0x44),param_2);
    }
    pcVar1 = *(code **)(&DAT_80327618 + iVar2);
    if (pcVar1 != (code *)0x0) {
      *(undefined4 *)(&DAT_80327618 + iVar2) = 0;
      (*pcVar1)(param_1,param_2);
    }
  }
  return;
}

