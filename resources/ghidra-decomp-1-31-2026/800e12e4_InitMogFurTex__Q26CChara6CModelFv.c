// Function: InitMogFurTex__Q26CChara6CModelFv
// Entry: 800e12e4
// Size: 280 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void InitMogFurTex__Q26CChara6CModelFv(CModel *model)

{
  undefined4 uVar1;
  CTexture *texture;
  int iVar2;
  CTextureSet *pCVar3;
  void *dstBuffer;
  
  pCVar3 = model->m_texSet;
  uVar1 = Find__11CTextureSetFPc(pCVar3,&DAT_80331114);
  texture = (CTexture *)__vc__21CPtrArray<P8CTexture>FUl(&pCVar3->textures,uVar1);
  if ((texture != (CTexture *)0x0) && (texture->field93_0x60 == 4)) {
    texture->field93_0x60 = 5;
    _WaitDrawDone__8CGraphicFPci(&Graphic,s_chara_fur_cpp_801db72c,0x506);
    pCVar3 = model->m_texSet;
    uVar1 = Find__11CTextureSetFPc(pCVar3,&DAT_80331114);
    iVar2 = __vc__21CPtrArray<P8CTexture>FUl(&pCVar3->textures,uVar1);
    if (iVar2 != 0) {
      dstBuffer = *(void **)(iVar2 + 0x78);
      iVar2 = *(int *)(iVar2 + 100) * *(int *)(iVar2 + 0x68) * 2;
      DCInvalidateRange(dstBuffer,iVar2);
      memcpy(dstBuffer,0x802e78e4,0x2000);
      DCFlushRange(dstBuffer,iVar2);
      GXInvalidateTexAll();
    }
    InitTexObj__8CTextureFv(texture);
    model->m_flagsA0 = model->m_flagsA0 & 0xbf | 0x40;
  }
  return;
}

