// Function: calcAfter__9CCharaPcsFv
// Entry: 80079858
// Size: 224 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void calcAfter__9CCharaPcsFv(int param_1)

{
  int iVar1;
  int iVar2;
  
  FlipDBuffer__6CCharaFv(&Chara);
  iVar1 = GetSize__34CPtrArray<PQ29CCharaPcs9CLoadAnim>Fv((CPtrArray *)(param_1 + 0x6c));
  while (iVar1 = iVar1 + -1, -1 < iVar1) {
    iVar2 = __vc__34CPtrArray<PQ29CCharaPcs9CLoadAnim>FUl(param_1 + 0x6c,iVar1);
    iVar2 = *(int *)(iVar2 + 0x28);
    if ((*(int *)(iVar2 + 4) == 1) && (*(int *)(iVar2 + 0x20) != 0)) {
      __dl__FPv();
      *(undefined4 *)(iVar2 + 0x20) = 0;
    }
  }
  iVar1 = GetSize__34CPtrArray<PQ29CCharaPcs9CLoadAnim>Fv((CPtrArray *)(param_1 + 0x6c));
  while (iVar1 = iVar1 + -1, -1 < iVar1) {
    iVar2 = __vc__34CPtrArray<PQ29CCharaPcs9CLoadAnim>FUl(param_1 + 0x6c,iVar1);
    iVar2 = *(int *)(iVar2 + 0x28);
    if (*(int *)(iVar2 + 4) == 1) {
      *(int *)(iVar2 + 0x24) = *(int *)(iVar2 + 0x24) + 1;
    }
  }
  return;
}

