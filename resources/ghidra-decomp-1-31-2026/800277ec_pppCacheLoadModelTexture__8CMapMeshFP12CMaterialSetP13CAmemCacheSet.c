// Function: pppCacheLoadModelTexture__8CMapMeshFP12CMaterialSetP13CAmemCacheSet
// Entry: 800277ec
// Size: 120 bytes

void pppCacheLoadModelTexture__8CMapMeshFP12CMaterialSetP13CAmemCacheSet
               (CMapMesh *mapMesh,CMaterialSet *materialSet,CAmemCacheSet *amemCacheSet)

{
  bool bVar1;
  int *piVar2;
  uint uVar3;
  
  uVar3 = (uint)(ushort)mapMesh->unkCount;
  piVar2 = (int *)mapMesh->field19_0x40;
  while (bVar1 = uVar3 != 0, uVar3 = uVar3 - 1, bVar1) {
    if (*piVar2 != 0) {
      if (*(ushort *)(piVar2 + 2) == 0xffff) {
        *(undefined2 *)(piVar2 + 2) = 0;
      }
      else {
        CacheLoadTexture__12CMaterialSetFiP13CAmemCacheSet
                  (materialSet,(uint)*(ushort *)(piVar2 + 2),amemCacheSet);
      }
    }
    piVar2 = piVar2 + 4;
  }
  return;
}

