// Function: __close_all
// Entry: 801b2dc0
// Size: 168 bytes

void __close_all(void)

{
  undefined *puVar1;
  undefined *puVar2;
  
  __begin_critical_region(2);
  puVar1 = &DAT_8021d158;
  while( true ) {
    puVar2 = puVar1;
    if (puVar2 == (undefined *)0x0) break;
    if ((*(ushort *)(puVar2 + 4) >> 6 & 7) != 0) {
      fclose(puVar2);
    }
    puVar1 = *(undefined **)(puVar2 + 0x4c);
    if (puVar2[0xc] == '\0') {
      *(ushort *)(puVar2 + 4) = *(ushort *)(puVar2 + 4) & 0xfe3f | 0xc0;
      if ((puVar1 != (undefined *)0x0) && (puVar1[0xc] != '\0')) {
        *(undefined4 *)(puVar2 + 0x4c) = 0;
      }
    }
    else {
      free();
    }
  }
  __end_critical_region(2);
  return;
}

