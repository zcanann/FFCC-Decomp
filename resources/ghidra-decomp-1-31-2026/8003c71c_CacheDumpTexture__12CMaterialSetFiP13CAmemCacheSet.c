// Function: CacheDumpTexture__12CMaterialSetFiP13CAmemCacheSet
// Entry: 8003c71c
// Size: 132 bytes

void CacheDumpTexture__12CMaterialSetFiP13CAmemCacheSet
               (CMaterialSet *materialSet,undefined4 param_2,CAmemCacheSet *amemCacheSet)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar1 = __vc__22CPtrArray<P9CMaterial>FUl(&materialSet->materials);
  if (iVar1 != 0) {
    iVar2 = iVar1;
    for (iVar3 = 0; iVar3 < (int)(uint)*(ushort *)(iVar1 + 0x18); iVar3 = iVar3 + 1) {
      if (*(CTexture **)(iVar2 + 0x3c) != (CTexture *)0x0) {
        CacheUnLoadTexture__8CTextureFP13CAmemCacheSet(*(CTexture **)(iVar2 + 0x3c),amemCacheSet);
      }
      iVar2 = iVar2 + 4;
    }
  }
  return;
}

