// Function: Find__11CTextureSetFPc
// Entry: 8003a6f0
// Size: 140 bytes

uint Find__11CTextureSetFPc(CTextureSet *textureSet,undefined4 param_2)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  
  uVar3 = 0;
  while( true ) {
    uVar2 = GetSize__21CPtrArray<P8CTexture>Fv(&textureSet->textures);
    if (uVar2 <= uVar3) {
      return 0xffffffff;
    }
    iVar1 = __vc__21CPtrArray<P8CTexture>FUl(&textureSet->textures,uVar3);
    if ((iVar1 != 0) && (iVar1 = strcmp(iVar1 + 8,param_2), iVar1 == 0)) break;
    uVar3 = uVar3 + 1;
  }
  return uVar3;
}

