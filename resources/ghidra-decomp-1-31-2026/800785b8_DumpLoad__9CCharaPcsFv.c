// Function: DumpLoad__9CCharaPcsFv
// Entry: 800785b8
// Size: 1028 bytes

void DumpLoad__9CCharaPcsFv(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  
  if (2 < (uint)System.m_execParam) {
    Printf__7CSystemFPce(&System,&DAT_803302e4);
  }
  if (2 < (uint)System.m_execParam) {
    Printf__7CSystemFPce(&System,s_no_t_num_lv_mask_addr_a_a_addr_a_801d95a8);
  }
  if (2 < (uint)System.m_execParam) {
    Printf__7CSystemFPce(&System,s___________________________________801d95dc);
  }
  iVar2 = GetSize__36CPtrArray<PQ29CCharaPcs10CLoadModel>Fv((CPtrArray *)(param_1 + 0x50));
  for (iVar7 = 0; iVar7 < iVar2; iVar7 = iVar7 + 1) {
    iVar6 = __vc__36CPtrArray<PQ29CCharaPcs10CLoadModel>FUl(param_1 + 0x50,iVar7);
    if (2 < (uint)System.m_execParam) {
      if (*(int *)(iVar6 + 0x1c) == 0) {
        uVar4 = 0;
        uVar1 = 0;
      }
      else {
        uVar4 = *(undefined4 *)(iVar6 + 0x24);
        uVar1 = *(undefined4 *)(iVar6 + 0x20);
      }
      Printf__7CSystemFPce
                (&System,s__3d__1d__3d__3d__08x__08x__d__08_801d9614,iVar7,
                 *(undefined4 *)(iVar6 + 8),*(undefined4 *)(iVar6 + 0xc),
                 *(undefined4 *)(iVar6 + 0x10),*(undefined4 *)(iVar6 + 0x14),
                 *(undefined4 *)(iVar6 + 0x18),*(int *)(iVar6 + 0x1c),uVar1,uVar4);
    }
  }
  if (2 < (uint)System.m_execParam) {
    Printf__7CSystemFPce(&System,s_texture_801d963c);
  }
  if (2 < (uint)System.m_execParam) {
    Printf__7CSystemFPce(&System,s_no_t_num_t_lv_mask_addr_a_a_addr_801d9648);
  }
  if (2 < (uint)System.m_execParam) {
    Printf__7CSystemFPce(&System,s__________________________________801d9680);
  }
  iVar2 = GetSize__38CPtrArray<PQ29CCharaPcs12CLoadTexture>Fv((CPtrArray *)(param_1 + 0x88));
  for (iVar7 = 0; iVar7 < iVar2; iVar7 = iVar7 + 1) {
    iVar6 = __vc__38CPtrArray<PQ29CCharaPcs12CLoadTexture>FUl(param_1 + 0x88,iVar7);
    if (2 < (uint)System.m_execParam) {
      iVar3 = *(int *)(iVar6 + 0x20);
      if (iVar3 == 0) {
        uVar4 = 0;
      }
      else {
        uVar4 = *(undefined4 *)(iVar6 + 0x28);
      }
      if (iVar3 == 0) {
        uVar1 = 0;
      }
      else {
        uVar1 = *(undefined4 *)(iVar6 + 0x24);
      }
      Printf__7CSystemFPce
                (&System,s__3d__1d__3d__1d__3d__08x__08x__d_801d96b8,iVar7,
                 *(undefined4 *)(iVar6 + 8),*(undefined4 *)(iVar6 + 0xc),
                 *(undefined4 *)(iVar6 + 0x18),*(undefined4 *)(iVar6 + 0x10),
                 *(undefined4 *)(iVar6 + 0x14),*(undefined4 *)(iVar6 + 0x1c),iVar3,uVar1,uVar4);
    }
  }
  if (2 < (uint)System.m_execParam) {
    Printf__7CSystemFPce(&System,&DAT_803302ec);
  }
  if (2 < (uint)System.m_execParam) {
    Printf__7CSystemFPce(&System,s_no_t_num_t_pdt_hdl_lv_mask_801d96e4);
  }
  if (2 < (uint)System.m_execParam) {
    Printf__7CSystemFPce(&System,s__________________________________801d9708);
  }
  iVar2 = GetSize__33CPtrArray<PQ29CCharaPcs8CLoadPdt>Fv((CPtrArray *)(param_1 + 0xa4));
  for (iVar7 = 0; iVar7 < iVar2; iVar7 = iVar7 + 1) {
    iVar6 = __vc__33CPtrArray<PQ29CCharaPcs8CLoadPdt>FUl(param_1 + 0xa4,iVar7);
    if (2 < (uint)System.m_execParam) {
      Printf__7CSystemFPce
                (&System,s__3d__1d__3d__1d__8d__3d__08x_801d972c,iVar7,*(undefined4 *)(iVar6 + 8),
                 *(undefined4 *)(iVar6 + 0xc),*(undefined4 *)(iVar6 + 0x10),
                 *(undefined4 *)(iVar6 + 0x14),*(undefined4 *)(iVar6 + 0x18),
                 *(undefined4 *)(iVar6 + 0x1c));
    }
  }
  if (2 < (uint)System.m_execParam) {
    Printf__7CSystemFPce(&System,&DAT_803302f4);
  }
  if (2 < (uint)System.m_execParam) {
    Printf__7CSystemFPce(&System,s_no_t_num_name_lv_mask_addr_banks_801d974c);
  }
  if (2 < (uint)System.m_execParam) {
    Printf__7CSystemFPce(&System,s__________________________________801d9798);
  }
  iVar2 = GetSize__34CPtrArray<PQ29CCharaPcs9CLoadAnim>Fv((CPtrArray *)(param_1 + 0x6c));
  iVar6 = 0;
  for (iVar7 = 0; iVar7 < iVar2; iVar7 = iVar7 + 1) {
    iVar3 = __vc__34CPtrArray<PQ29CCharaPcs9CLoadAnim>FUl(param_1 + 0x6c,iVar7);
    if (2 < (uint)System.m_execParam) {
      iVar5 = *(int *)(iVar3 + 0x28);
      Printf__7CSystemFPce
                (&System,s__3d__1d__3d__14s__3d__08x__08x___801d97e4,iVar7,
                 *(undefined4 *)(iVar3 + 8),*(undefined4 *)(iVar3 + 0xc),iVar3 + 0x18,
                 *(undefined4 *)(iVar3 + 0x10),*(undefined4 *)(iVar3 + 0x14),iVar5,
                 *(undefined4 *)(iVar5 + 0x1c),iVar6,*(undefined4 *)(iVar5 + 0x24));
    }
    iVar6 = iVar6 + *(int *)(*(int *)(iVar3 + 0x28) + 0x1c);
  }
  return;
}

