// Function: __CARDAllocBlock
// Entry: 8019af6c
// Size: 280 bytes

undefined4 __CARDAllocBlock(int chan,uint CBlock,void *param_3)

{
  undefined4 uVar1;
  int iVar2;
  uint16_t *fat;
  uint16_t uVar3;
  ushort uVar4;
  ushort uVar5;
  uint uVar6;
  ushort unaff_r31;
  
  iVar2 = chan * 0x110;
  if ((&DAT_80327540)[chan * 0x44] == 0) {
    uVar1 = 0xfffffffd;
  }
  else {
    fat = *(uint16_t **)(&DAT_803275c8 + iVar2);
    if (fat[3] < CBlock) {
      uVar1 = 0xfffffff7;
    }
    else {
      fat[3] = fat[3] - (short)CBlock;
      uVar3 = fat[4];
      uVar6 = 0;
      uVar5 = 0xffff;
      while (CBlock != 0) {
        uVar6 = uVar6 + 1;
        if ((int)(*(ushort *)(&DAT_80327550 + iVar2) - 5) < (int)(uVar6 & 0xffff)) {
          return 0xfffffffa;
        }
        uVar3 = uVar3 + 1;
        if ((uVar3 < 5) || ((uint)*(ushort *)(&DAT_80327550 + iVar2) <= (uint)uVar3)) {
          uVar3 = 5;
        }
        if (fat[uVar3] == 0) {
          uVar4 = uVar3;
          if (uVar5 != 0xffff) {
            fat[unaff_r31] = uVar3;
            uVar4 = uVar5;
          }
          fat[uVar3] = 0xffff;
          CBlock = CBlock - 1;
          unaff_r31 = uVar3;
          uVar5 = uVar4;
        }
      }
      fat[4] = uVar3;
      *(ushort *)(&DAT_803275fe + iVar2) = uVar5;
      uVar1 = __CARDUpdateFatBlock(chan,fat,param_3);
    }
  }
  return uVar1;
}

