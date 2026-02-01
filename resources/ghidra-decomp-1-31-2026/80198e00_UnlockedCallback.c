// Function: UnlockedCallback
// Entry: 80198e00
// Size: 272 bytes

void UnlockedCallback(int param_1,int param_2)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  code *pcVar4;
  
  iVar3 = param_1 * 0x110;
  if (-1 < param_2) {
    *(code **)(&DAT_8032761c + iVar3) = UnlockedCallback;
    iVar2 = EXILock(param_1,0,__CARDUnlockedHandler);
    if (iVar2 == 0) {
      param_2 = 0;
    }
    else {
      *(undefined4 *)(&DAT_8032761c + iVar3) = 0;
      param_2 = Retry(param_1);
    }
  }
  if (param_2 < 0) {
    bVar1 = (&DAT_803275d4)[iVar3];
    if (bVar1 != 0xf3) {
      if (bVar1 < 0xf3) {
        if (bVar1 == 0x52) {
          pcVar4 = *(code **)(&DAT_80327608 + iVar3);
          if (pcVar4 == (code *)0x0) {
            return;
          }
          *(undefined4 *)(&DAT_80327608 + iVar3) = 0;
          (*pcVar4)(param_1);
          return;
        }
        if (bVar1 < 0x52) {
          return;
        }
        if (bVar1 < 0xf1) {
          return;
        }
      }
      else if (0xf4 < bVar1) {
        return;
      }
      pcVar4 = *(code **)(&DAT_8032760c + iVar3);
      if (pcVar4 != (code *)0x0) {
        *(undefined4 *)(&DAT_8032760c + iVar3) = 0;
        (*pcVar4)(param_1);
      }
    }
  }
  return;
}

