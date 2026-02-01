// Function: CacheLoadTexture__8CTextureFP13CAmemCacheSet
// Entry: 8003b090
// Size: 436 bytes

void CacheLoadTexture__8CTextureFP13CAmemCacheSet(CTexture *texture,CAmemCacheSet *amemCacheSet)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  
  if (*(short *)&texture->field_0x72 != -1) {
    iVar3 = IsEnable__13CAmemCacheSetFs(amemCacheSet,*(short *)&texture->field_0x72);
    if (iVar3 == 0) {
      iVar3 = GetData__13CAmemCacheSetFsPci
                        (amemCacheSet,*(undefined2 *)&texture->field_0x72,s_textureman_cpp_801d7974,
                         0x1dd);
      texture->field105_0x78 = iVar3;
      iVar3 = texture->field93_0x60;
      if ((iVar3 == 9) || (iVar3 == 8)) {
        GXInitTexObjCI(&texture->field_0x28,texture->field105_0x78,texture->field94_0x64 & 0xffff,
                       texture->field95_0x68 & 0xffff,iVar3,texture->field96_0x6c,
                       texture->field96_0x6c,0,0);
        iVar3 = *(int *)&texture->field_0x7c;
        uVar1 = 0x10;
        if (texture->field93_0x60 == 9) {
          uVar1 = 0x100;
        }
        GXInitTlutObj(&texture->field_0x48,iVar3,0,uVar1);
        uVar1 = 0x10;
        if (texture->field93_0x60 == 9) {
          uVar1 = 0x100;
        }
        iVar2 = 0x10;
        if (texture->field93_0x60 == 9) {
          iVar2 = 0x100;
        }
        GXInitTlutObj(&texture->field_0x54,iVar3 + iVar2 * 2,0,uVar1);
      }
      else {
        GXInitTexObj(&texture->field_0x28,texture->field105_0x78,texture->field94_0x64 & 0xffff,
                     texture->field95_0x68 & 0xffff,iVar3,texture->field96_0x6c,
                     texture->field96_0x6c,1 - texture->field101_0x74 >> 0x1f);
      }
      if (1 < texture->field101_0x74) {
        GXInitTexObjLOD((double)FLOAT_8032fad8,
                        (double)((float)((double)CONCAT44(0x43300000,(uint)texture->field101_0x74) -
                                        DOUBLE_8032fae0) - FLOAT_8032fadc),(double)FLOAT_8032fad8,
                        &texture->field_0x28,5,1,1,0,0);
      }
    }
    AddRef__13CAmemCacheSetFs(amemCacheSet,*(undefined2 *)&texture->field_0x72);
  }
  return;
}

