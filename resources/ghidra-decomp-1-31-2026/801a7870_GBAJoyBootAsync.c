// Function: GBAJoyBootAsync
// Entry: 801a7870
// Size: 316 bytes

int GBAJoyBootAsync(uint param_1,int param_2,int param_3,int param_4,int param_5,undefined4 param_6,
                   undefined4 param_7)

{
  int iVar1;
  int iVar2;
  undefined auStack_24 [4];
  
  iVar1 = param_1 * 0x100;
  if ((param_1 & 0xfffffffc) == 0) {
    if ((param_5 == 0) || (0x40000 < param_5)) {
      iVar2 = 4;
    }
    else if ((param_3 < -4) || (4 < param_3)) {
      iVar2 = 4;
    }
    else if ((param_2 < 0) || (6 < param_2)) {
      iVar2 = 4;
    }
    else if ((uint)*(byte *)(param_4 + 0xaf) *
             (uint)*(byte *)(param_4 + 0xae) *
             (uint)*(byte *)(param_4 + 0xac) * (uint)*(byte *)(param_4 + 0xad) == 0) {
      iVar2 = 4;
    }
    else {
      iVar2 = GBAGetProcessStatus(param_1,auStack_24);
      if (iVar2 == 0) {
        *(int *)(&DAT_80328360 + iVar1) = param_2;
        *(int *)(&DAT_80328364 + iVar1) = param_3;
        *(int *)(&DAT_80328368 + iVar1) = param_4;
        *(int *)(&DAT_8032836c + iVar1) = param_5;
        *(undefined4 *)(&DAT_80328370 + iVar1) = param_6;
        *(undefined4 *)(&DAT_80328374 + iVar1) = param_7;
        *(uint *)(&DAT_80328394 + iVar1) = (uint)DAT_8021cb50;
        iVar2 = GBAGetStatusAsync(param_1,*(undefined4 *)(&DAT_80328370 + iVar1),F23);
        if (iVar2 != 0) {
          *(undefined4 *)(&DAT_80328374 + iVar1) = 0;
        }
      }
    }
  }
  else {
    iVar2 = 4;
  }
  return iVar2;
}

