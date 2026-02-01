// Function: ReadCallback
// Entry: 8019e168
// Size: 304 bytes

void ReadCallback(int param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  code *pcVar5;
  int iVar6;
  
  iVar3 = param_1 * 0x110;
  if (-1 < param_2) {
    iVar6 = *(int *)(&DAT_80327600 + iVar3);
    if (*(int *)(iVar6 + 0xc) < 0) {
      param_2 = -0xe;
    }
    else {
      iVar4 = (~(*(int *)(&DAT_8032754c + iVar3) - 1U) &
              *(int *)(iVar6 + 8) + *(int *)(&DAT_8032754c + iVar3)) - *(int *)(iVar6 + 8);
      *(int *)(iVar6 + 0xc) = *(int *)(iVar6 + 0xc) - iVar4;
      if (0 < *(int *)(iVar6 + 0xc)) {
        iVar1 = __CARDGetFatBlock((CARDControl *)(&DAT_80327540 + param_1 * 0x44));
        *(int *)(iVar6 + 8) = *(int *)(iVar6 + 8) + iVar4;
        *(undefined2 *)(iVar6 + 0x10) = *(undefined2 *)(iVar1 + (uint)*(ushort *)(iVar6 + 0x10) * 2)
        ;
        uVar2 = (uint)*(ushort *)(iVar6 + 0x10);
        if ((uVar2 < 5) || (*(ushort *)(&DAT_80327550 + iVar3) <= uVar2)) {
          param_2 = -6;
        }
        else {
          iVar1 = *(int *)(&DAT_8032754c + iVar3);
          iVar4 = iVar1;
          if (*(int *)(iVar6 + 0xc) < iVar1) {
            iVar4 = *(int *)(iVar6 + 0xc);
          }
          param_2 = __CARDRead(param_1,iVar1 * uVar2,iVar4,*(void **)(&DAT_803275f4 + iVar3),
                               ReadCallback);
          if (-1 < param_2) {
            return;
          }
        }
      }
    }
  }
  pcVar5 = *(code **)(&DAT_80327610 + iVar3);
  *(undefined4 *)(&DAT_80327610 + iVar3) = 0;
  __CARDPutControlBlock((CARDControl *)(&DAT_80327540 + param_1 * 0x44),param_2);
  (*pcVar5)(param_1,param_2);
  return;
}

