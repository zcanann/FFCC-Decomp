// Function: __CARDFreeBlock
// Entry: 8019b084
// Size: 156 bytes

undefined4 __CARDFreeBlock(int chan,ushort nBlock,void *param_3)

{
  uint uVar1;
  undefined4 uVar2;
  uint16_t *fat;
  
  if ((&DAT_80327540)[chan * 0x44] == 0) {
    uVar2 = 0xfffffffd;
  }
  else {
    fat = *(uint16_t **)(&DAT_803275c8 + chan * 0x110);
    while (nBlock != 0xffff) {
      uVar1 = (uint)nBlock;
      if ((uVar1 < 5) || (*(ushort *)(&DAT_80327550 + chan * 0x110) <= uVar1)) {
        return 0xfffffffa;
      }
      nBlock = fat[uVar1];
      fat[uVar1] = 0;
      fat[3] = fat[3] + 1;
    }
    uVar2 = __CARDUpdateFatBlock(chan,fat,param_3);
  }
  return uVar2;
}

