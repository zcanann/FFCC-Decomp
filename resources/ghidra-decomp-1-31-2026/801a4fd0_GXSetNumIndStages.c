// Function: GXSetNumIndStages
// Entry: 801a4fd0
// Size: 40 bytes

void GXSetNumIndStages(uint param_1)

{
  int iVar1;
  
  iVar1 = DAT_80333828;
  *(uint *)(DAT_80333828 + 0x204) =
       *(uint *)(DAT_80333828 + 0x204) & 0xfff8ffff | (param_1 & 0xff) << 0x10;
  *(uint *)(iVar1 + 0x4f4) = *(uint *)(iVar1 + 0x4f4) | 6;
  return;
}

