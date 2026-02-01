// Function: SetDisplayListMaterial__8CMapMeshFP12CMaterialSetPPcP13CAmemCacheSet
// Entry: 80027864
// Size: 132 bytes

void SetDisplayListMaterial__8CMapMeshFP12CMaterialSetPPcP13CAmemCacheSet
               (CMapMesh *mapMesh,CMaterialSet *materialSet,CAmemCacheSet *amemCacheSet)

{
  bool bVar1;
  undefined2 uVar2;
  int *piVar3;
  uint uVar4;
  
  uVar4 = (uint)(ushort)mapMesh->unkCount;
  piVar3 = (int *)mapMesh->field19_0x40;
  while (bVar1 = uVar4 != 0, uVar4 = uVar4 - 1, bVar1) {
    if (*piVar3 != 0) {
      if (*(ushort *)(piVar3 + 2) == 0xffff) {
        *(undefined2 *)(piVar3 + 2) = 0;
      }
      else {
        uVar2 = FindTexName__12CMaterialSetFPcPl
                          (materialSet,
                           *(char **)(&amemCacheSet->field_0x0 + (uint)*(ushort *)(piVar3 + 2) * 4),
                           0);
        *(undefined2 *)(piVar3 + 2) = uVar2;
      }
    }
    piVar3 = piVar3 + 4;
  }
  return;
}

