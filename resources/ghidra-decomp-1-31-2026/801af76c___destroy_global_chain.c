// Function: __destroy_global_chain
// Entry: 801af76c
// Size: 72 bytes

void __destroy_global_chain(void)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  
  while (DAT_8032f370 != (int *)0x0) {
    puVar1 = DAT_8032f370 + 1;
    puVar2 = DAT_8032f370 + 2;
    DAT_8032f370 = (int *)*DAT_8032f370;
    (*(code *)*puVar1)(*puVar2,0xffffffff);
  }
  return;
}

