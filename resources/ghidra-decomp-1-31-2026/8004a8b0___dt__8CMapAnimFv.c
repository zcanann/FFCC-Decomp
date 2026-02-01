// Function: __dt__8CMapAnimFv
// Entry: 8004a8b0
// Size: 192 bytes

CMapAnim * __dt__8CMapAnimFv(CMapAnim *mapAnim,short param_2)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  
  if (mapAnim != (CMapAnim *)0x0) {
    uVar3 = 0;
    while( true ) {
      uVar2 = GetSize__26CPtrArray<P12CMapAnimNode>Fv(&mapAnim->mapAnimNodes);
      if (uVar2 <= uVar3) break;
      iVar1 = __vc__26CPtrArray<P12CMapAnimNode>FUl(mapAnim,uVar3);
      if ((iVar1 != 0) && (iVar1 = __vc__26CPtrArray<P12CMapAnimNode>FUl(mapAnim,uVar3), iVar1 != 0)
         ) {
        *(undefined4 *)(iVar1 + 4) = 0;
        __dl__FPv();
      }
      uVar3 = uVar3 + 1;
    }
    RemoveAll__26CPtrArray<P12CMapAnimNode>Fv(&mapAnim->mapAnimNodes);
    __dt__26CPtrArray<P12CMapAnimNode>Fv(&mapAnim->mapAnimNodes,0xffff);
    if (0 < param_2) {
      __dl__FPv(mapAnim);
    }
  }
  return mapAnim;
}

