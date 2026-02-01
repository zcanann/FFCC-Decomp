// Function: GXSetTevSwapMode
// Entry: 801a55f0
// Size: 84 bytes

void GXSetTevSwapMode(int param_1,uint param_2,int param_3)

{
  int iVar1;
  uint *puVar2;
  
  iVar1 = DAT_80333828;
  puVar2 = (uint *)(DAT_80333828 + param_1 * 4 + 0x170);
  *puVar2 = *puVar2 & 0xfffffffc | param_2;
  *puVar2 = *puVar2 & 0xfffffff3 | param_3 << 2;
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = *puVar2;
  *(undefined2 *)(iVar1 + 2) = 0;
  return;
}

