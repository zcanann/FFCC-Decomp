// Function: __TRK_copy_vectors
// Entry: 801aded8
// Size: 300 bytes

void __TRK_copy_vectors(void)

{
  uint *puVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  
  if (((DAT_8032a6a0 < 0x45) && (0x44 < DAT_8032a6a0 + 0x4000)) && ((DAT_8032a400 & 3) != 0)) {
    puVar1 = (uint *)&DAT_00000044;
  }
  else {
    puVar1 = &DAT_80000044;
  }
  uVar4 = *puVar1;
  puVar1 = &DAT_8021cff8;
  iVar5 = 0;
  do {
    if (((uVar4 & 1 << iVar5) != 0) && (iVar5 != 4)) {
      uVar2 = *puVar1;
      uVar3 = uVar2;
      if (((uVar2 < DAT_8032a6a0) || ((DAT_8032a6a0 + 0x4000 <= uVar2 || ((DAT_8032a400 & 3) == 0)))
          ) && ((uVar2 < 0x7e000000 || (0x80000000 < uVar2)))) {
        uVar3 = uVar2 & 0x3fffffff | 0x80000000;
      }
      TRK_memcpy(uVar3,uVar2 + 0x800034ac,0x100);
      TRK_flush_cache(uVar3,0x100);
    }
    iVar5 = iVar5 + 1;
    puVar1 = puVar1 + 1;
  } while (iVar5 < 0xf);
  return;
}

