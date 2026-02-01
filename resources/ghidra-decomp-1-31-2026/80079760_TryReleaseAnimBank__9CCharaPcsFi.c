// Function: TryReleaseAnimBank__9CCharaPcsFi
// Entry: 80079760
// Size: 248 bytes

undefined4 TryReleaseAnimBank__9CCharaPcsFi(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  
  iVar2 = GetSize__34CPtrArray<PQ29CCharaPcs9CLoadAnim>Fv((CPtrArray *)(param_1 + 0x6c));
  iVar6 = 0;
  iVar7 = -1;
  while (iVar2 = iVar2 + -1, -1 < iVar2) {
    iVar3 = __vc__34CPtrArray<PQ29CCharaPcs9CLoadAnim>FUl(param_1 + 0x6c,iVar2);
    uVar5 = *(uint *)(*(int *)(iVar3 + 0x28) + 0x20);
    if (((int)(-uVar5 | uVar5) < 0) &&
       (iVar1 = *(int *)(*(int *)(iVar3 + 0x28) + 0x24), iVar7 < iVar1)) {
      iVar6 = iVar3;
      iVar7 = iVar1;
    }
  }
  if (iVar6 == 0) {
    uVar4 = 0;
  }
  else {
    iVar2 = *(int *)(iVar6 + 0x28);
    if (*(int *)(iVar2 + 0x20) != 0) {
      __dl__FPv();
      *(undefined4 *)(iVar2 + 0x20) = 0;
    }
    if (2 < (uint)System.m_execParam) {
      Printf__7CSystemFPce(&System,&DAT_801d9810,iVar7,iVar6 + 0x18);
    }
    uVar4 = 1;
  }
  return uVar4;
}

