// Function: GXSetTevSwapModeTable
// Entry: 801a5644
// Size: 152 bytes

void GXSetTevSwapModeTable(int param_1,uint param_2,int param_3,uint param_4,int param_5)

{
  int iVar1;
  uint *puVar2;
  uint *puVar3;
  
  iVar1 = DAT_80333828;
  puVar3 = (uint *)(DAT_80333828 + param_1 * 8 + 0x1b0);
  *puVar3 = *puVar3 & 0xfffffffc | param_2;
  *puVar3 = *puVar3 & 0xfffffff3 | param_3 << 2;
  puVar2 = (uint *)(iVar1 + (param_1 * 2 + 1) * 4 + 0x1b0);
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = *puVar3;
  *puVar2 = *puVar2 & 0xfffffffc | param_4;
  *puVar2 = *puVar2 & 0xfffffff3 | param_5 << 2;
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = *puVar2;
  *(undefined2 *)(iVar1 + 2) = 0;
  return;
}

