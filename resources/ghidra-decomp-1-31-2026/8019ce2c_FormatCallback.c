// Function: FormatCallback
// Entry: 8019ce2c
// Size: 324 bytes

void FormatCallback(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  code *pcVar3;
  
  iVar2 = param_1 * 0x110;
  if (-1 < param_2) {
    *(int *)(&DAT_80327568 + iVar2) = *(int *)(&DAT_80327568 + iVar2) + 1;
    iVar1 = *(int *)(&DAT_80327568 + iVar2);
    if (iVar1 < 5) {
      param_2 = __CARDEraseSector(param_1,*(int *)(&DAT_8032754c + iVar2) * iVar1,FormatCallback);
    }
    else {
      if (9 < iVar1) {
        *(int *)(&DAT_803275c4 + iVar2) = (&DAT_803275c0)[param_1 * 0x44] + 0x2000;
        memcpy(*(void **)(&DAT_803275c4 + iVar2),(&DAT_803275c0)[param_1 * 0x44] + 0x4000,0x2000);
        *(int *)(&DAT_803275c8 + iVar2) = (&DAT_803275c0)[param_1 * 0x44] + 0x6000;
        memcpy(*(void **)(&DAT_803275c8 + iVar2),(&DAT_803275c0)[param_1 * 0x44] + 0x8000,0x2000);
        goto LAB_8019cf24;
      }
      param_2 = __CARDWrite(param_1,*(int *)(&DAT_8032754c + iVar2) * (iVar1 + -5),0x2000,
                            (void *)((&DAT_803275c0)[param_1 * 0x44] + (iVar1 + -5) * 0x2000),
                            FormatCallback);
    }
    if (-1 < param_2) {
      return;
    }
  }
LAB_8019cf24:
  pcVar3 = *(code **)(&DAT_80327610 + iVar2);
  *(undefined4 *)(&DAT_80327610 + iVar2) = 0;
  __CARDPutControlBlock((CARDControl *)(&DAT_80327540 + param_1 * 0x44),param_2);
  (*pcVar3)(param_1,param_2);
  return;
}

