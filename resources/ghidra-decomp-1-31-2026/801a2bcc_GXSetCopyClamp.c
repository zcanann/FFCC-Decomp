// Function: GXSetCopyClamp
// Entry: 801a2bcc
// Size: 104 bytes

void GXSetCopyClamp(uint param_1)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  
  iVar1 = DAT_80333828;
  uVar2 = countLeadingZeros((param_1 & 1) - 1);
  uVar3 = uVar2 >> 5 & 0xff;
  *(uint *)(DAT_80333828 + 0x1ec) = *(uint *)(DAT_80333828 + 0x1ec) & 0xfffffffe | uVar3;
  uVar2 = countLeadingZeros((param_1 & 2) - 2);
  uVar2 = uVar2 >> 4 & 0x1fe;
  *(uint *)(iVar1 + 0x1ec) = *(uint *)(iVar1 + 0x1ec) & 0xfffffffd | uVar2;
  *(uint *)(iVar1 + 0x1fc) = *(uint *)(iVar1 + 0x1fc) & 0xfffffffe | uVar3;
  *(uint *)(iVar1 + 0x1fc) = *(uint *)(iVar1 + 0x1fc) & 0xfffffffd | uVar2;
  return;
}

