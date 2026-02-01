// Function: GetTexture__8CMapMeshFP12CMaterialSetRi
// Entry: 800278e8
// Size: 88 bytes

undefined4
GetTexture__8CMapMeshFP12CMaterialSetRi(CMapMesh *mapMesh,CMaterialSet *materialSet,uint *param_3)

{
  int iVar1;
  undefined4 uVar2;
  int *piVar3;
  
  if ((mapMesh->unkCount == 0) || (piVar3 = (int *)mapMesh->field19_0x40, *piVar3 == 0)) {
    uVar2 = 0;
  }
  else {
    *param_3 = (uint)*(ushort *)(piVar3 + 2);
    iVar1 = __vc__22CPtrArray<P9CMaterial>FUl(&materialSet->materials,*(undefined2 *)(piVar3 + 2));
    uVar2 = *(undefined4 *)(iVar1 + 0x3c);
  }
  return uVar2;
}

