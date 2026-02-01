// Function: __GXFifoLink
// Entry: 801a0a4c
// Size: 60 bytes

void __GXFifoLink(char param_1)

{
  int iVar1;
  
  iVar1 = DAT_80333828;
  *(uint *)(DAT_80333828 + 8) =
       *(uint *)(DAT_80333828 + 8) & 0xffffffef | (uint)(param_1 != '\0') << 4;
  *(short *)(DAT_8032f2ec + 2) = (short)*(undefined4 *)(iVar1 + 8);
  return;
}

