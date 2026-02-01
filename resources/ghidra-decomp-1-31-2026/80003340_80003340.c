// Function: 80003340
// Entry: 80003340
// Size: 192 bytes

void _0003340(void)

{
  undefined **ppuVar1;
  undefined *count;
  undefined *dstBuffer;
  
  ppuVar1 = &_rom_copy_info;
  while( true ) {
    count = ppuVar1[2];
    if (count == (undefined *)0x0) break;
    dstBuffer = ppuVar1[1];
    if ((count != (undefined *)0x0) && (dstBuffer != *ppuVar1)) {
      memcpy(dstBuffer,*ppuVar1,count);
      __flush_cache(dstBuffer,count);
    }
    ppuVar1 = ppuVar1 + 3;
  }
  ppuVar1 = &_bss_init_info;
  while( true ) {
    if (ppuVar1[1] == (undefined *)0x0) break;
    if (ppuVar1[1] != (undefined *)0x0) {
      memset(*ppuVar1,0);
    }
    ppuVar1 = ppuVar1 + 2;
  }
  return;
}

