// Function: __CARDUpdateFatBlock
// Entry: 8019b120
// Size: 172 bytes

void __CARDUpdateFatBlock(int chan,uint16_t *fat,void *callback)

{
  fat[2] = fat[2] + 1;
  __CARDCheckSum(fat + 2,0x1ffc,fat,fat + 1);
  DCStoreRange(fat,0x2000);
  *(void **)(&DAT_80327618 + chan * 0x110) = callback;
  __CARDEraseSector(chan,*(int *)(&DAT_8032754c + chan * 0x110) *
                         ((uint)((int)fat - (&DAT_803275c0)[chan * 0x44]) >> 0xd),EraseCallback);
  return;
}

