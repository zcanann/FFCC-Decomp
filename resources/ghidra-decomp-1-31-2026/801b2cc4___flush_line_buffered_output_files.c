// Function: __flush_line_buffered_output_files
// Entry: 801b2cc4
// Size: 140 bytes

undefined4 __flush_line_buffered_output_files(void)

{
  undefined *puVar1;
  int iVar2;
  undefined4 uVar3;
  
  puVar1 = &DAT_8021d158;
  uVar3 = 0;
  while( true ) {
    if (puVar1 == (undefined *)0x0) break;
    if (((((*(ushort *)(puVar1 + 4) >> 6 & 7) != 0) && (((byte)puVar1[4] >> 1 & 1) != 0)) &&
        ((byte)puVar1[8] >> 5 == 1)) && (iVar2 = fflush(puVar1), iVar2 != 0)) {
      uVar3 = 0xffffffff;
    }
    puVar1 = *(undefined **)(puVar1 + 0x4c);
  }
  return uVar3;
}

