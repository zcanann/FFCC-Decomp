// Function: CARDSetStatusAsync
// Entry: 8019ecc4
// Size: 372 bytes

int CARDSetStatusAsync(undefined4 param_1,int param_2,CARDStat *param_3,void *param_4)

{
  uint uVar1;
  int iVar2;
  uint32_t extraout_r4;
  CARDDir *cardDir;
  undefined8 uVar3;
  CARDControl *local_18 [2];
  
  if ((((param_2 < 0) || (0x7e < param_2)) ||
      ((param_3->iconAddr != 0xffffffff && (0x1ff < param_3->iconAddr)))) ||
     ((param_3->commentAddr != 0xffffffff && (0x1fc0 < (param_3->commentAddr & 0x1fff))))) {
    iVar2 = -0x80;
  }
  else {
    iVar2 = __CARDGetControlBlock(param_1,local_18);
    if (-1 < iVar2) {
      iVar2 = __CARDGetDirBlock(local_18[0]);
      cardDir = (CARDDir *)(iVar2 + param_2 * 0x40);
      iVar2 = __CARDAccess(local_18[0],cardDir);
      if (iVar2 < 0) {
        iVar2 = __CARDPutControlBlock(local_18[0],iVar2);
      }
      else {
        cardDir->bannerFormat = param_3->bannerFormat;
        cardDir->iconAddr = param_3->iconAddr;
        cardDir->iconFormat = param_3->iconFormat;
        cardDir->iconSpeed = param_3->iconSpeed;
        cardDir->commentAddr = param_3->commentAddr;
        UpdateIconOffsets(cardDir,param_3);
        if (cardDir->iconAddr == 0xffffffff) {
          cardDir->iconSpeed = cardDir->iconSpeed & 0xfffc | 1;
        }
        uVar1 = DAT_800000f8 >> 2;
        uVar3 = OSGetTime();
        __div2i((int)((ulonglong)uVar3 >> 0x20),(int)uVar3,0,uVar1);
        cardDir->time = extraout_r4;
        iVar2 = __CARDUpdateDir(param_1,param_4);
        if (iVar2 < 0) {
          __CARDPutControlBlock(local_18[0],iVar2);
        }
      }
    }
  }
  return iVar2;
}

