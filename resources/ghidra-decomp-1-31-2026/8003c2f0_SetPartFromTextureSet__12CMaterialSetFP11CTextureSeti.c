// Function: SetPartFromTextureSet__12CMaterialSetFP11CTextureSeti
// Entry: 8003c2f0
// Size: 428 bytes

void SetPartFromTextureSet__12CMaterialSetFP11CTextureSeti
               (CMaterialSet *materialSet,CTextureSet *textureSet,int param_3)

{
  float fVar1;
  int iVar2;
  CRef *ref;
  uint uVar3;
  uint uVar4;
  uint index;
  
  uVar4 = 0;
  do {
    uVar3 = GetSize__21CPtrArray<P8CTexture>Fv(&textureSet->textures);
    if (uVar3 <= uVar4) {
      return;
    }
    iVar2 = __vc__21CPtrArray<P8CTexture>FUl(&textureSet->textures,uVar4);
    if (iVar2 != 0) {
      uVar3 = _UnkMaterialSetGetter((CMaterial *)&materialSet->materials);
      index = uVar4 + 1;
      if (index < uVar3) {
        iVar2 = __vc__22CPtrArray<P9CMaterial>FUl(&materialSet->materials,index);
        if (iVar2 != 0) goto LAB_8003c474;
      }
      ref = (CRef *)_Alloc__7CMemoryFUlPQ27CMemory6CStagePcii
                              (&Memory,0xa8,MaterialMan._536_4_,s_materialman_cpp_801d7a38,0xee4,0);
      if (ref != (CRef *)0x0) {
        __ct__4CRefFv(ref);
        ref->vtable = &PTR_PTR_s_CMaterial_801e9bd4;
        __construct_array(&ref[9].refCount,__ct__10CTexScrollFv,__dt__10CTexScrollFv,0x14,4);
        memset(ref + 1,0,0x10);
        ref[0x13].refCount = -1;
        *(undefined *)&ref[0x14].vtable = 4;
        *(undefined *)((int)&ref[0x14].vtable + 1) = 1;
        *(undefined *)((int)&ref[0x14].vtable + 2) = 0;
        *(undefined *)&ref[0x14].refCount = 0;
        ref[7].refCount = 0;
        ref[8].vtable = (void *)0x0;
        ref[8].refCount = 0;
        ref[9].vtable = (void *)0x0;
        *(undefined *)&ref[6].refCount = 0;
        *(undefined *)((int)&ref[6].refCount + 1) = 0;
        *(undefined *)((int)&ref[6].refCount + 2) = 0;
        *(undefined *)((int)&ref[0x14].refCount + 1) = 0;
      }
      fVar1 = FLOAT_8032faf0;
      ref[4].refCount = -0xace10;
      ref[5].vtable = (void *)0x0;
      *(undefined2 *)&ref[3].vtable = 0;
      ref[6].vtable = (void *)fVar1;
      ref[5].refCount = (int)fVar1;
      *(undefined *)((int)&ref[0x14].refCount + 3) = 0;
      *(undefined2 *)&ref[3].vtable = 1;
      *(short *)((int)&ref[3].vtable + 2) = (short)uVar4;
      ref[0x13].refCount = param_3;
      uVar3 = _UnkMaterialSetGetter((CMaterial *)&materialSet->materials);
      if (index < uVar3) {
        SetAt__22CPtrArray<P9CMaterial>FUlP9CMaterial(&materialSet->materials,index,ref);
      }
      else {
        Add__22CPtrArray<P9CMaterial>FP9CMaterial(&materialSet->materials,ref);
      }
    }
LAB_8003c474:
    uVar4 = uVar4 + 1;
  } while( true );
}

