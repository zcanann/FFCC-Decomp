// Function: DrawMeshCharaShadow__8CMapMeshFUsUs
// Entry: 80027a7c
// Size: 168 bytes

void DrawMeshCharaShadow__8CMapMeshFUsUs(CMapMesh *mapMesh,uint indexA,uint indexB)

{
  bool bVar1;
  int iVar2;
  int *piVar3;
  uint uVar4;
  
  uVar4 = indexB & 0xffff;
  piVar3 = (int *)(mapMesh->field19_0x40 + (indexA & 0xffff) * 0x10);
  while (bVar1 = uVar4 != 0, uVar4 = uVar4 - 1, bVar1) {
    if ((*piVar3 != 0) &&
       (iVar2 = __vc__22CPtrArray<P9CMaterial>FUl(MapMng._136148_4_ + 8,*(undefined2 *)(piVar3 + 2))
       , (*(uint *)(iVar2 + 0x24) & 0x100000) != 0)) {
      SetMaterialCharaShadow__12CMaterialManFP9CMaterial(&MaterialMan,iVar2);
      GXCallDisplayList(piVar3[1],*piVar3);
    }
    piVar3 = piVar3 + 4;
  }
  return;
}

