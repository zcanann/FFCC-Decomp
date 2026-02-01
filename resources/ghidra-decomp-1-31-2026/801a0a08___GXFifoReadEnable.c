// Function: __GXFifoReadEnable
// Entry: 801a0a08
// Size: 36 bytes

void __GXFifoReadEnable(void)

{
  int iVar1;
  
  iVar1 = DAT_80333828;
  *(uint *)(DAT_80333828 + 8) = *(uint *)(DAT_80333828 + 8) & 0xfffffffe | 1;
  *(short *)(DAT_8032f2ec + 2) = (short)*(undefined4 *)(iVar1 + 8);
  return;
}

