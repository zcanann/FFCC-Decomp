// Function: correctLoadAnimAmem__9CCharaPcsFv
// Entry: 80079b40
// Size: 604 bytes

int correctLoadAnimAmem__9CCharaPcsFv(int param_1)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  uint uVar9;
  int iVar10;
  int iVar11;
  uint uVar12;
  int iVar13;
  int iVar14;
  
  if (2 < (uint)System.m_execParam) {
    Printf__7CSystemFPce(&System,&DAT_801d9840);
  }
  iVar3 = _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii
                    (&Memory,0x80000,*(undefined4 *)(param_1 + 0xd4),s_p_chara_cpp_801d91bc,0x162,1)
  ;
  if (iVar3 == 0) {
    if (1 < (uint)System.m_execParam) {
      Printf__7CSystemFPce(&System,&DAT_801d9868);
    }
    iVar4 = -1;
  }
  else {
    iVar5 = GetSize__34CPtrArray<PQ29CCharaPcs9CLoadAnim>Fv((CPtrArray *)(param_1 + 0x6c));
    iVar4 = 0;
    iVar13 = 0;
    iVar10 = 0;
    for (iVar8 = 0; iVar8 < iVar5; iVar8 = iVar8 + 1) {
      iVar14 = __vc__34CPtrArray<PQ29CCharaPcs9CLoadAnim>FUl(param_1 + 0x6c,iVar8);
      iVar14 = *(int *)(*(int *)(iVar14 + 0x28) + 0x28) + *(int *)(*(int *)(iVar14 + 0x28) + 0x1c);
      if (iVar13 < iVar14) {
        iVar13 = iVar14;
      }
      iVar10 = iVar10 + 1;
    }
    uVar9 = 0;
    if (2 < (uint)System.m_execParam) {
      Printf__7CSystemFPce(&System,&DAT_801d98c0,iVar10);
    }
    do {
      iVar14 = 0;
      iVar8 = 0;
      uVar12 = 0;
      for (iVar10 = 0; iVar10 < iVar5; iVar10 = iVar10 + 1) {
        iVar6 = __vc__34CPtrArray<PQ29CCharaPcs9CLoadAnim>FUl(param_1 + 0x6c,iVar10);
        uVar7 = *(uint *)(*(int *)(iVar6 + 0x28) + 0x28);
        iVar11 = *(int *)(*(int *)(iVar6 + 0x28) + 0x1c);
        if ((uVar9 <= uVar7) && (uVar1 = uVar7 + iVar11, uVar1 < uVar9 + 0x80000)) {
          if (uVar12 < uVar1) {
            uVar12 = uVar1;
          }
          iVar8 = iVar8 + 1;
          CopyFromAMemorySync__7CMemoryFPvPvUl
                    (&Memory,iVar3 + iVar14,uVar7 + *(int *)(*(int *)(param_1 + 0xc4) + 8),iVar11);
          iVar2 = iVar4 + iVar14;
          iVar14 = iVar14 + iVar11;
          *(int *)(*(int *)(iVar6 + 0x28) + 0x28) = iVar2;
        }
      }
      if (iVar8 != 0) {
        iVar10 = iVar4 + *(int *)(*(int *)(param_1 + 0xc4) + 8);
        CopyToAMemorySync__7CMemoryFPvPvUl(&Memory,iVar3,iVar10,iVar14);
        if (2 < (uint)System.m_execParam) {
          Printf__7CSystemFPce(&System,&DAT_801d9910,iVar8,iVar10,iVar10 + iVar14);
        }
      }
      iVar4 = iVar4 + iVar14;
      uVar9 = uVar12;
    } while ((int)uVar12 < iVar13);
    if (iVar3 != 0) {
      __dl__FPv(iVar3);
    }
    if (2 < (uint)System.m_execParam) {
      Printf__7CSystemFPce(&System,&DAT_801d9928,iVar4);
    }
  }
  return iVar4;
}

