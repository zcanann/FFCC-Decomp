// Function: __GXFifoReadDisable
// Entry: 801a0a2c
// Size: 32 bytes

void __GXFifoReadDisable(void)

{
  int iVar1;
  
  iVar1 = DAT_80333828;
  *(uint *)(DAT_80333828 + 8) = *(uint *)(DAT_80333828 + 8) & 0xfffffffe;
  *(short *)(DAT_8032f2ec + 2) = (short)*(undefined4 *)(iVar1 + 8);
  return;
}

