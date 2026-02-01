// Function: __find_unopened_file
// Entry: 801b2f44
// Size: 144 bytes

undefined * __find_unopened_file(void)

{
  undefined *puVar1;
  undefined *puVar2;
  undefined *unaff_r30;
  
  puVar2 = PTR_DAT_8021d244;
  while( true ) {
    puVar1 = puVar2;
    if (puVar1 == (undefined *)0x0) {
      puVar2 = (undefined *)malloc(0x50);
      if (puVar2 == (undefined *)0x0) {
        puVar2 = (undefined *)0x0;
      }
      else {
        memset(puVar2,0,0x50);
        puVar2[0xc] = 1;
        *(undefined **)(unaff_r30 + 0x4c) = puVar2;
      }
      return puVar2;
    }
    if ((*(ushort *)(puVar1 + 4) >> 6 & 7) == 0) break;
    puVar2 = *(undefined **)(puVar1 + 0x4c);
    unaff_r30 = puVar1;
  }
  return puVar1;
}

