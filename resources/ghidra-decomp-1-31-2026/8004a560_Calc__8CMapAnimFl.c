// Function: Calc__8CMapAnimFl
// Entry: 8004a560
// Size: 120 bytes

void Calc__8CMapAnimFl(CMapAnim *mapAnim,undefined4 param_2)

{
  int iVar1;
  CMapAnimNode *mapAnimNode;
  int iVar2;
  
  iVar1 = GetSize__26CPtrArray<P12CMapAnimNode>Fv(&mapAnim->mapAnimNodes);
  for (iVar2 = 0; iVar2 < iVar1; iVar2 = iVar2 + 1) {
    mapAnimNode = (CMapAnimNode *)__vc__26CPtrArray<P12CMapAnimNode>FUl(mapAnim,iVar2);
    Interp__12CMapAnimNodeFi(mapAnimNode,param_2);
  }
  return;
}

