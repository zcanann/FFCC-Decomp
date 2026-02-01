// Function: Create__11CTextureSetFPvPQ27CMemory6CStageiP13CAmemCacheSetii
// Entry: 8003a9ac
// Size: 712 bytes

void Create__11CTextureSetFPvPQ27CMemory6CStageiP13CAmemCacheSetii
               (CTextureSet *textureSet,void *param_2,CStage *stage,int param_4,
               CAmemCacheSet *amemCacheSet,undefined4 param_6,undefined4 param_7)

{
  CTexture *texture;
  uint uVar1;
  int iVar2;
  uint uVar3;
  undefined local_118 [32];
  CChunkFile aCStack_f8 [4];
  
  __ct__10CChunkFileFPv(aCStack_f8,param_2);
  do {
    do {
      iVar2 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk
                        (aCStack_f8,(CChunkFile *)(local_118 + 0x10));
      if (iVar2 == 0) {
        return;
      }
    } while ((uint8_t *)local_118._16_4_ != (uint8_t *)0x54455820);
    PushChunk__10CChunkFileFv(aCStack_f8);
    while (iVar2 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk
                             (aCStack_f8,(CChunkFile *)(local_118 + 0x10)), iVar2 != 0) {
      if ((uint8_t *)local_118._16_4_ == (uint8_t *)0x5343454e) {
        PushChunk__10CChunkFileFv(aCStack_f8);
        while (iVar2 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk
                                 (aCStack_f8,(CChunkFile *)(local_118 + 0x10)), iVar2 != 0) {
          if ((uint8_t *)local_118._16_4_ == (uint8_t *)0x54534554) {
            if (param_4 == 0) {
              ReleaseAndRemoveAll__21CPtrArray<P8CTexture>Fv(&textureSet->textures);
            }
            PushChunk__10CChunkFileFv(aCStack_f8);
LAB_8003ac08:
            iVar2 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk
                              (aCStack_f8,(CChunkFile *)local_118);
            if (iVar2 != 0) {
              if (local_118._0_4_ == 0x54585452) {
                texture = (CTexture *)
                          _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii
                                    (&Memory,0x80,TextureMan.memoryStage,s_textureman_cpp_801d7974,
                                     0x2ed,0);
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
                          (texture,aCStack_f8,stage,amemCacheSet,param_6,(undefined1)param_7);
                if (texture->field_0x8 != '\0') {
                  for (uVar3 = 0; uVar1 = GetSize__21CPtrArray<P8CTexture>Fv(&textureSet->textures),
                      uVar3 < uVar1; uVar3 = uVar3 + 1) {
                    iVar2 = __vc__21CPtrArray<P8CTexture>FUl(&textureSet->textures,uVar3);
                    if ((iVar2 != 0) && (iVar2 = strcmp(iVar2 + 8,&texture->field_0x8), iVar2 == 0))
                    goto LAB_8003ab40;
                  }
                  uVar3 = 0xffffffff;
LAB_8003ab40:
                  if (-1 < (int)uVar3) {
                    if (amemCacheSet != (CAmemCacheSet *)0x0) {
                      DestroyCache__13CAmemCacheSetFi
                                (amemCacheSet,(int)*(short *)&texture->field_0x72);
                      AmemPrev__13CAmemCacheSetFv(amemCacheSet);
                    }
                    iVar2 = *(int *)&texture->field_0x4 + -1;
                    *(int *)&texture->field_0x4 = iVar2;
                    if ((iVar2 == 0) && (texture != (CTexture *)0x0)) {
                      (**(code **)((int)texture->vtable + 8))(texture,1);
                    }
                    texture = (CTexture *)
                              __vc__21CPtrArray<P8CTexture>FUl(&textureSet->textures,uVar3);
                    *(int *)&texture->field_0x4 = *(int *)&texture->field_0x4 + 1;
                  }
                }
                if (param_4 != 0) {
                  for (uVar3 = 0; uVar1 = GetSize__21CPtrArray<P8CTexture>Fv(&textureSet->textures),
                      uVar3 < uVar1; uVar3 = uVar3 + 1) {
                    iVar2 = __vc__21CPtrArray<P8CTexture>FUl(&textureSet->textures,uVar3);
                    if (iVar2 == 0) {
                      SetAt__21CPtrArray<P8CTexture>FUlP8CTexture
                                (&textureSet->textures,uVar3,texture);
                      goto LAB_8003ac08;
                    }
                  }
                }
                Add__21CPtrArray<P8CTexture>FP8CTexture(&textureSet->textures,texture);
              }
              goto LAB_8003ac08;
            }
            PopChunk__10CChunkFileFv(aCStack_f8);
          }
        }
      }
    }
  } while( true );
}

