// Function: GXSetNumTevStages
// Entry: 801a598c
// Size: 48 bytes

void GXSetNumTevStages(uint param_1)

{
  int iVar1;
  
  iVar1 = DAT_80333828;
  *(uint *)(DAT_80333828 + 0x204) =
       *(uint *)(DAT_80333828 + 0x204) & 0xffffc3ff | ((param_1 & 0xff) - 1) * 0x400;
  *(uint *)(iVar1 + 0x4f4) = *(uint *)(iVar1 + 0x4f4) | 4;
  return;
}

