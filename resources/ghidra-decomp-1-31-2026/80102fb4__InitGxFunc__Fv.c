// Function: _InitGxFunc__Fv
// Entry: 80102fb4
// Size: 460 bytes

void _InitGxFunc__Fv(void)

{
  int iVar1;
  undefined *puVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  
  iVar1 = 0;
  iVar8 = 0;
  iVar10 = 0;
  iVar9 = 0;
  puVar2 = s_GXSetTevOrder_Reg;
  iVar13 = 2;
  do {
    iVar3 = iVar1 + 1;
    iVar4 = iVar1 + 2;
    *(undefined4 *)(s_GXSetTevColorOp_Reg + iVar9) = 0xffffffff;
    iVar6 = iVar1 + 4;
    *(undefined4 *)(s_GXSetTevAlphaOp_Reg + iVar9) = 0xffffffff;
    iVar5 = iVar1 + 3;
    *(undefined4 *)(s_GXSetTevSwapMode_Reg + iVar10) = 0xffffffff;
    iVar7 = iVar1 + 5;
    *(undefined4 *)(s_GXSetTevColorIn_Reg + iVar8) = 0xffffffff;
    *(undefined4 *)(s_GXSetTevAlphaIn_Reg + iVar8) = 0xffffffff;
    iVar12 = iVar1 + 6;
    *(undefined4 *)puVar2 = 0xffffffff;
    iVar11 = iVar1 + 7;
    *(undefined4 *)(s_GXSetTevSwapMode_Reg + iVar3 * 8) = 0xffffffff;
    *(undefined4 *)(s_GXSetTevColorIn_Reg + iVar3 * 0x10) = 0xffffffff;
    *(undefined4 *)(s_GXSetTevAlphaIn_Reg + iVar3 * 0x10) = 0xffffffff;
    *(undefined4 *)(s_GXSetTevColorOp_Reg + iVar3 * 0x14) = 0xffffffff;
    *(undefined4 *)(s_GXSetTevAlphaOp_Reg + iVar3 * 0x14) = 0xffffffff;
    iVar1 = iVar1 + 8;
    *(undefined4 *)((int)puVar2 + 0xc) = 0xffffffff;
    iVar10 = iVar10 + 0x40;
    *(undefined4 *)(s_GXSetTevColorIn_Reg + iVar4 * 0x10) = 0xffffffff;
    iVar9 = iVar9 + 0xa0;
    iVar8 = iVar8 + 0x80;
    *(undefined4 *)(s_GXSetTevAlphaIn_Reg + iVar4 * 0x10) = 0xffffffff;
    *(undefined4 *)(s_GXSetTevColorOp_Reg + iVar4 * 0x14) = 0xffffffff;
    *(undefined4 *)(s_GXSetTevAlphaOp_Reg + iVar4 * 0x14) = 0xffffffff;
    *(undefined4 *)(s_GXSetTevSwapMode_Reg + iVar4 * 8) = 0xffffffff;
    *(undefined4 *)((int)puVar2 + 0x18) = 0xffffffff;
    *(undefined4 *)(s_GXSetTevColorIn_Reg + iVar5 * 0x10) = 0xffffffff;
    *(undefined4 *)(s_GXSetTevAlphaIn_Reg + iVar5 * 0x10) = 0xffffffff;
    *(undefined4 *)(s_GXSetTevColorOp_Reg + iVar5 * 0x14) = 0xffffffff;
    *(undefined4 *)(s_GXSetTevAlphaOp_Reg + iVar5 * 0x14) = 0xffffffff;
    *(undefined4 *)(s_GXSetTevSwapMode_Reg + iVar5 * 8) = 0xffffffff;
    *(undefined4 *)((int)puVar2 + 0x24) = 0xffffffff;
    *(undefined4 *)(s_GXSetTevColorIn_Reg + iVar6 * 0x10) = 0xffffffff;
    *(undefined4 *)(s_GXSetTevAlphaIn_Reg + iVar6 * 0x10) = 0xffffffff;
    *(undefined4 *)(s_GXSetTevColorOp_Reg + iVar6 * 0x14) = 0xffffffff;
    *(undefined4 *)(s_GXSetTevAlphaOp_Reg + iVar6 * 0x14) = 0xffffffff;
    *(undefined4 *)(s_GXSetTevSwapMode_Reg + iVar6 * 8) = 0xffffffff;
    *(undefined4 *)((int)puVar2 + 0x30) = 0xffffffff;
    *(undefined4 *)(s_GXSetTevColorIn_Reg + iVar7 * 0x10) = 0xffffffff;
    *(undefined4 *)(s_GXSetTevAlphaIn_Reg + iVar7 * 0x10) = 0xffffffff;
    *(undefined4 *)(s_GXSetTevColorOp_Reg + iVar7 * 0x14) = 0xffffffff;
    *(undefined4 *)(s_GXSetTevAlphaOp_Reg + iVar7 * 0x14) = 0xffffffff;
    *(undefined4 *)(s_GXSetTevSwapMode_Reg + iVar7 * 8) = 0xffffffff;
    *(undefined4 *)((int)puVar2 + 0x3c) = 0xffffffff;
    *(undefined4 *)(s_GXSetTevColorIn_Reg + iVar12 * 0x10) = 0xffffffff;
    *(undefined4 *)(s_GXSetTevAlphaIn_Reg + iVar12 * 0x10) = 0xffffffff;
    *(undefined4 *)(s_GXSetTevColorOp_Reg + iVar12 * 0x14) = 0xffffffff;
    *(undefined4 *)(s_GXSetTevAlphaOp_Reg + iVar12 * 0x14) = 0xffffffff;
    *(undefined4 *)(s_GXSetTevSwapMode_Reg + iVar12 * 8) = 0xffffffff;
    *(undefined4 *)((int)puVar2 + 0x48) = 0xffffffff;
    *(undefined4 *)((int)puVar2 + 0x54) = 0xffffffff;
    puVar2 = (undefined *)((int)puVar2 + 0x60);
    *(undefined4 *)(s_GXSetTevColorIn_Reg + iVar11 * 0x10) = 0xffffffff;
    *(undefined4 *)(s_GXSetTevAlphaIn_Reg + iVar11 * 0x10) = 0xffffffff;
    *(undefined4 *)(s_GXSetTevColorOp_Reg + iVar11 * 0x14) = 0xffffffff;
    *(undefined4 *)(s_GXSetTevAlphaOp_Reg + iVar11 * 0x14) = 0xffffffff;
    *(undefined4 *)(s_GXSetTevSwapMode_Reg + iVar11 * 8) = 0xffffffff;
    iVar13 = iVar13 + -1;
  } while (iVar13 != 0);
  s_GXSetTevSwapModeTable_Reg._0_4_ = 0xffffffff;
  s_GXSetTevSwapModeTable_Reg._16_4_ = 0xffffffff;
  s_GXSetTevSwapModeTable_Reg._32_4_ = 0xffffffff;
  s_GXSetTevSwapModeTable_Reg._48_4_ = 0xffffffff;
  ARRAY_802ffa50._0_4_ = 0xffffffff;
  DAT_8032ee40 = 0xffff;
  ARRAY_802ffa60._0_4_ = 0xffffffff;
  return;
}

