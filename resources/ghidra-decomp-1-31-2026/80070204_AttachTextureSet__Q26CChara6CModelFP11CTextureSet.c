// Function: AttachTextureSet__Q26CChara6CModelFP11CTextureSet
// Entry: 80070204
// Size: 176 bytes

void AttachTextureSet__Q26CChara6CModelFP11CTextureSet(CModel *model,CTexture *texture)

{
  int iVar1;
  CTexture *pCVar2;
  CMaterialSet *pCVar3;
  CTextureSet *pCVar4;
  
  pCVar2 = (CTexture *)model->m_texSet;
  if (texture != pCVar2) {
    if (pCVar2 != (CTexture *)0x0) {
      iVar1 = *(int *)&pCVar2->field_0x4 + -1;
      *(int *)&pCVar2->field_0x4 = iVar1;
      if ((iVar1 == 0) && (pCVar2 != (CTexture *)0x0)) {
        (**(code **)((int)pCVar2->vtable + 8))(pCVar2,1);
      }
      model->m_texSet = (CTextureSet *)0x0;
    }
    model->m_texSet = (CTextureSet *)texture;
    pCVar4 = model->m_texSet;
    if (pCVar4 != (CTextureSet *)0x0) {
      *(int *)&pCVar4->field_0x4 = *(int *)&pCVar4->field_0x4 + 1;
    }
  }
  pCVar3 = model->m_data->m_materialSet;
  if (pCVar3 != (CMaterialSet *)0x0) {
    SetTextureSet__12CMaterialSetFP11CTextureSet(pCVar3,model->m_texSet);
  }
  return;
}

