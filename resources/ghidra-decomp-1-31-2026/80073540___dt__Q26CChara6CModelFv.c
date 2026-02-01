// Function: __dt__Q26CChara6CModelFv
// Entry: 80073540
// Size: 420 bytes

CModel * __dt__Q26CChara6CModelFv(CModel *model,short param_2)

{
  int iVar1;
  CTextureSet *pCVar2;
  CAnim *pCVar3;
  CTexAnimSet *pCVar4;
  CModelCRefData *pCVar5;
  
  if (model != (CModel *)0x0) {
    (model->ref).vtable = &PTR_PTR_s_CChara_CModel_801fccf4;
    pCVar2 = model->m_texSet;
    if (pCVar2 != (CTextureSet *)0x0) {
      iVar1 = *(int *)&pCVar2->field_0x4 + -1;
      *(int *)&pCVar2->field_0x4 = iVar1;
      if ((iVar1 == 0) && (pCVar2 != (CTextureSet *)0x0)) {
        (**(code **)((int)pCVar2->vtable + 8))(pCVar2,1);
      }
      model->m_texSet = (CTextureSet *)0x0;
    }
    pCVar3 = model->m_anim;
    if (pCVar3 != (CAnim *)0x0) {
      iVar1 = *(int *)(pCVar3 + 4);
      *(int *)(pCVar3 + 4) = iVar1 + -1;
      if ((iVar1 + -1 == 0) && (pCVar3 != (CAnim *)0x0)) {
        (**(code **)(*(int *)pCVar3 + 8))(pCVar3,1);
      }
      model->m_anim = (CAnim *)0x0;
    }
    pCVar4 = model->m_texAnimSet;
    if (pCVar4 != (CTexAnimSet *)0x0) {
      iVar1 = (pCVar4->texAnims).numItems + -1;
      (pCVar4->texAnims).numItems = iVar1;
      if ((iVar1 == 0) && (pCVar4 != (CTexAnimSet *)0x0)) {
        (**(code **)((int)(pCVar4->texAnims).vtable + 8))(pCVar4,1);
      }
      model->m_texAnimSet = (CTexAnimSet *)0x0;
    }
    pCVar5 = model->m_data;
    if (pCVar5 != (CModelCRefData *)0x0) {
      iVar1 = (pCVar5->ref).refCount + -1;
      (pCVar5->ref).refCount = iVar1;
      if ((iVar1 == 0) && (pCVar5 != (CModelCRefData *)0x0)) {
        (**(code **)((int)(pCVar5->ref).vtable + 8))(pCVar5,1);
      }
      model->m_data = (CModelCRefData *)0x0;
    }
    if (model->m_nodes != (CNode *)0x0) {
      __destroy_new_array(model->m_nodes,__dt__Q26CChara5CNodeFv);
      model->m_nodes = (CNode *)0x0;
    }
    if (model->m_meshes != (CMesh *)0x0) {
      __destroy_new_array(model->m_meshes,__dt__Q26CChara5CMeshFv);
      model->m_meshes = (CMesh *)0x0;
    }
    __dt__4CRefFv(&model->ref,0);
    if (0 < param_2) {
      __dl__FPv(model);
    }
  }
  return model;
}

