// Function: ReleaseTextureIdx__11CTextureSetFiP13CAmemCacheSet
// Entry: 8003a5fc
// Size: 244 bytes

void ReleaseTextureIdx__11CTextureSetFiP13CAmemCacheSet
               (CTextureSet *textureSet,undefined4 param_2,CAmemCacheSet *amemCacheSet)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = __vc__21CPtrArray<P8CTexture>FUl(&textureSet->textures);
  if (iVar1 != 0) {
    iVar1 = __vc__21CPtrArray<P8CTexture>FUl(&textureSet->textures,param_2);
    if (*(short *)(iVar1 + 0x72) != -1) {
      iVar1 = __vc__21CPtrArray<P8CTexture>FUl(&textureSet->textures,param_2);
      if (*(int *)(iVar1 + 4) < 2) {
        iVar1 = __vc__21CPtrArray<P8CTexture>FUl(&textureSet->textures,param_2);
        DestroyCache__13CAmemCacheSetFi(amemCacheSet,(int)*(short *)(iVar1 + 0x72));
        iVar1 = __vc__21CPtrArray<P8CTexture>FUl(&textureSet->textures,param_2);
        *(undefined4 *)(iVar1 + 0x78) = 0;
      }
    }
    piVar2 = (int *)__vc__21CPtrArray<P8CTexture>FUl(&textureSet->textures,param_2);
    iVar1 = piVar2[1];
    piVar2[1] = iVar1 + -1;
    if ((iVar1 + -1 == 0) && (piVar2 != (int *)0x0)) {
      (**(code **)(*piVar2 + 8))(piVar2,1);
    }
    SetAt__21CPtrArray<P8CTexture>FUlP8CTexture(&textureSet->textures,param_2,0);
  }
  return;
}

