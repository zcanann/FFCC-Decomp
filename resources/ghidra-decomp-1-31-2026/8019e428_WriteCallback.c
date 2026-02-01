// Function: WriteCallback
// Entry: 8019e428
// Size: 368 bytes

void WriteCallback(int param_1,int param_2)

{
  int iVar1;
  undefined4 extraout_r4;
  void *callback;
  uint uVar2;
  int iVar3;
  int iVar4;
  code *pcVar5;
  CARDControl *cardControl;
  undefined8 uVar6;
  
  iVar3 = param_1 * 0x110;
  cardControl = (CARDControl *)(&DAT_80327540 + param_1 * 0x44);
  if (-1 < param_2) {
    iVar4 = *(int *)(&DAT_80327600 + iVar3);
    if (*(int *)(iVar4 + 0xc) < 0) {
      param_2 = -0xe;
    }
    else {
      *(int *)(iVar4 + 0xc) = *(int *)(iVar4 + 0xc) - *(int *)(&DAT_8032754c + iVar3);
      if (*(int *)(iVar4 + 0xc) < 1) {
        iVar1 = __CARDGetDirBlock(cardControl);
        iVar4 = *(int *)(iVar4 + 4);
        uVar2 = DAT_800000f8 >> 2;
        uVar6 = OSGetTime();
        __div2i((int)((ulonglong)uVar6 >> 0x20),(int)uVar6,0,uVar2);
        *(undefined4 *)(iVar1 + iVar4 * 0x40 + 0x28) = extraout_r4;
        callback = *(void **)(&DAT_80327610 + iVar3);
        *(undefined4 *)(&DAT_80327610 + iVar3) = 0;
        param_2 = __CARDUpdateDir(param_1,callback);
      }
      else {
        iVar1 = __CARDGetFatBlock(cardControl);
        *(int *)(iVar4 + 8) = *(int *)(iVar4 + 8) + *(int *)(&DAT_8032754c + iVar3);
        *(undefined2 *)(iVar4 + 0x10) = *(undefined2 *)(iVar1 + (uint)*(ushort *)(iVar4 + 0x10) * 2)
        ;
        uVar2 = (uint)*(ushort *)(iVar4 + 0x10);
        if ((uVar2 < 5) || (*(ushort *)(&DAT_80327550 + iVar3) <= uVar2)) {
          param_2 = -6;
          goto LAB_8019e54c;
        }
        param_2 = __CARDEraseSector(param_1,*(int *)(&DAT_8032754c + iVar3) * uVar2,EraseCallback);
      }
      if (-1 < param_2) {
        return;
      }
    }
  }
LAB_8019e54c:
  pcVar5 = *(code **)(&DAT_80327610 + iVar3);
  *(undefined4 *)(&DAT_80327610 + iVar3) = 0;
  __CARDPutControlBlock(cardControl,param_2);
  (*pcVar5)(param_1,param_2);
  return;
}

