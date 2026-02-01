// Function: Create__11CTextureSetFR10CChunkFilePQ27CMemory6CStageiP13CAmemCacheSetii
// Entry: 8003a77c
// Size: 560 bytes

void Create__11CTextureSetFR10CChunkFilePQ27CMemory6CStageiP13CAmemCacheSetii
               (CTextureSet *textureSet,CChunkFile *chunkFile,CStage *stage,int param_4,
               CAmemCacheSet *amemCacheSet,undefined4 param_6,undefined4 param_7)

{
  CTexture *texture;
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint32_t local_48;
  
  if (param_4 == 0) {
    ReleaseAndRemoveAll__21CPtrArray<P8CTexture>Fv(&textureSet->textures);
  }
  PushChunk__10CChunkFileFv(chunkFile);
LAB_8003a97c:
  do {
    do {
      iVar2 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk(chunkFile,(CChunkFile *)&local_48);
      if (iVar2 == 0) {
        PopChunk__10CChunkFileFv(chunkFile);
        return;
      }
    } while (local_48 != 0x54585452);
    texture = (CTexture *)
              _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii
                        (&Memory,0x80,TextureMan.memoryStage,s_textureman_cpp_801d7974,0x2ed,0);
    if (texture != (CTexture *)0x0) {
      __ct__4CRefFv((CRef *)texture);
      texture->vtable = &PTR_PTR_s_CTexture_801e9b78;
      texture->field101_0x74 = 0;
      texture->field105_0x78 = 0;
      *(undefined4 *)&texture->field_0x7c = 0;
      texture->field_0x70 = 0;
      texture->field_0x71 = 0;
      texture->field_0x8 = 0;
      *(undefined2 *)&texture->field_0x72 = 0xffff;
      texture->field_0x75 = 0;
    }
    Create__8CTextureFR10CChunkFilePQ27CMemory6CStageP13CAmemCacheSetii
              (texture,chunkFile,stage,amemCacheSet,param_6,(undefined1)param_7);
    if (texture->field_0x8 != '\0') {
      for (uVar3 = 0; uVar1 = GetSize__21CPtrArray<P8CTexture>Fv(&textureSet->textures),
          uVar3 < uVar1; uVar3 = uVar3 + 1) {
        iVar2 = __vc__21CPtrArray<P8CTexture>FUl(&textureSet->textures,uVar3);
        if ((iVar2 != 0) && (iVar2 = strcmp(iVar2 + 8,&texture->field_0x8), iVar2 == 0))
        goto LAB_8003a8b4;
      }
      uVar3 = 0xffffffff;
LAB_8003a8b4:
      if (-1 < (int)uVar3) {
        if (amemCacheSet != (CAmemCacheSet *)0x0) {
          DestroyCache__13CAmemCacheSetFi(amemCacheSet,(int)*(short *)&texture->field_0x72);
          AmemPrev__13CAmemCacheSetFv(amemCacheSet);
        }
        iVar2 = *(int *)&texture->field_0x4 + -1;
        *(int *)&texture->field_0x4 = iVar2;
        if ((iVar2 == 0) && (texture != (CTexture *)0x0)) {
          (**(code **)((int)texture->vtable + 8))(texture,1);
        }
        texture = (CTexture *)__vc__21CPtrArray<P8CTexture>FUl(&textureSet->textures,uVar3);
        *(int *)&texture->field_0x4 = *(int *)&texture->field_0x4 + 1;
      }
    }
    if (param_4 != 0) {
      for (uVar3 = 0; uVar1 = GetSize__21CPtrArray<P8CTexture>Fv(&textureSet->textures),
          uVar3 < uVar1; uVar3 = uVar3 + 1) {
        iVar2 = __vc__21CPtrArray<P8CTexture>FUl(&textureSet->textures,uVar3);
        if (iVar2 == 0) {
          SetAt__21CPtrArray<P8CTexture>FUlP8CTexture(&textureSet->textures,uVar3,texture);
          goto LAB_8003a97c;
        }
      }
    }
    Add__21CPtrArray<P8CTexture>FP8CTexture(&textureSet->textures,texture);
  } while( true );
}

