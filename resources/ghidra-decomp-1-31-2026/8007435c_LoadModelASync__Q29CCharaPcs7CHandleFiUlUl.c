// Function: LoadModelASync__Q29CCharaPcs7CHandleFiUlUl
// Entry: 8007435c
// Size: 572 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void LoadModelASync__Q29CCharaPcs7CHandleFiUlUl
               (CCharaPcsCHandle *handle,int32_t param_2,int32_t param_3,int32_t param_4)

{
  int iVar1;
  CModel *pCVar2;
  CTextureSet *pCVar3;
  CRef *pCVar4;
  
  if (2 < (uint)System.m_execParam) {
    Printf__7CSystemFPce(&System,&DAT_801d91dc);
  }
  if (handle->m_asyncFileHandle != (CFileCHandle *)0x0) {
    if (1 < (uint)System.m_execParam) {
      Printf__7CSystemFPce(&System,&DAT_801d9170);
    }
    Close__5CFileFPQ25CFile7CHandle(&File,handle->m_asyncFileHandle);
    handle->m_asyncFileHandle = (CFileCHandle *)0x0;
  }
  handle->m_asyncState = 0;
  _WaitDrawDone__8CGraphicFPci(&Graphic,s_p_chara_cpp_801d91bc,0x8c9);
  pppDeleteCHandle__8CPartMngFPQ29CCharaPcs7CHandle(&PartMng,handle);
  pCVar2 = handle->m_model;
  if (pCVar2 != (CModel *)0x0) {
    iVar1 = (pCVar2->ref).refCount + -1;
    (pCVar2->ref).refCount = iVar1;
    if ((iVar1 == 0) && (pCVar2 != (CModel *)0x0)) {
      (**(code **)((int)(pCVar2->ref).vtable + 8))(pCVar2,1);
    }
    handle->m_model = (CModel *)0x0;
  }
  pCVar3 = handle->m_textureSet;
  if (pCVar3 != (CTextureSet *)0x0) {
    iVar1 = *(int *)&pCVar3->field_0x4 + -1;
    *(int *)&pCVar3->field_0x4 = iVar1;
    if ((iVar1 == 0) && (pCVar3 != (CTextureSet *)0x0)) {
      (**(code **)((int)pCVar3->vtable + 8))(pCVar3,1);
    }
    handle->m_textureSet = (CTextureSet *)0x0;
  }
  pCVar4 = handle->m_modelLoadRef;
  if (pCVar4 != (CRef *)0x0) {
    iVar1 = pCVar4->refCount + -1;
    pCVar4->refCount = iVar1;
    if ((iVar1 == 0) && (pCVar4 != (CRef *)0x0)) {
      (**(code **)((int)pCVar4->vtable + 8))(pCVar4,1);
    }
    handle->m_modelLoadRef = (CRef *)0x0;
  }
  pCVar4 = handle->m_texLoadRef;
  if (pCVar4 != (CRef *)0x0) {
    iVar1 = pCVar4->refCount + -1;
    pCVar4->refCount = iVar1;
    if ((iVar1 == 0) && (pCVar4 != (CRef *)0x0)) {
      (**(code **)((int)pCVar4->vtable + 8))(pCVar4,1);
    }
    handle->m_texLoadRef = (CRef *)0x0;
  }
  pCVar4 = handle->m_pdtLoadRef;
  if (pCVar4 != (CRef *)0x0) {
    iVar1 = pCVar4->refCount + -1;
    pCVar4->refCount = iVar1;
    if ((iVar1 == 0) && (pCVar4 != (CRef *)0x0)) {
      (**(code **)((int)pCVar4->vtable + 8))(pCVar4,1);
    }
    handle->m_pdtLoadRef = (CRef *)0x0;
  }
  releaseUnuseLoadModel__9CCharaPcsFi(&CharaPcs,0);
  handle->m_asyncCharaKind = param_2;
  handle->m_asyncCharaNo = param_3;
  handle->m_asyncTextureVariant = param_4;
  handle->m_asyncState = 1;
  loadModelASyncFrame__Q29CCharaPcs7CHandleFv(handle);
  return;
}

