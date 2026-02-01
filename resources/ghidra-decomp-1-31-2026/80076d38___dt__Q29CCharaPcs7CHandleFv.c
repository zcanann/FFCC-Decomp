// Function: __dt__Q29CCharaPcs7CHandleFv
// Entry: 80076d38
// Size: 840 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

CCharaPcsCHandle * __dt__Q29CCharaPcs7CHandleFv(CCharaPcsCHandle *handle,short param_2)

{
  int iVar1;
  int iVar2;
  CModel *pCVar3;
  CTextureSet *pCVar4;
  CRef *pCVar5;
  int *piVar6;
  CCharaPcsCHandle *pCVar7;
  
  if (handle != (CCharaPcsCHandle *)0x0) {
    if (handle->m_asyncFileHandle != (CFileCHandle *)0x0) {
      if (1 < (uint)System.m_execParam) {
        Printf__7CSystemFPce(&System,&DAT_801d9170);
      }
      Close__5CFileFPQ25CFile7CHandle(&File,handle->m_asyncFileHandle);
      handle->m_asyncFileHandle = (CFileCHandle *)0x0;
    }
    handle->m_asyncState = 0;
    pppDeleteCHandle__8CPartMngFPQ29CCharaPcs7CHandle(&PartMng,handle);
    if ((handle->m_next != (CCharaPcsCHandle *)0x0) &&
       (handle->m_previous != (CCharaPcsCHandle *)0x0)) {
      handle->m_previous->m_next = handle->m_next;
      handle->m_next->m_previous = handle->m_previous;
      handle->m_previous = (CCharaPcsCHandle *)0x0;
      handle->m_next = (CCharaPcsCHandle *)0x0;
    }
    _WaitDrawDone__8CGraphicFPci(&Graphic,s_p_chara_cpp_801d91bc,0x717);
    _WaitDrawDone__8CGraphicFPci(&Graphic,s_p_chara_cpp_801d91bc,0x8c9);
    pppDeleteCHandle__8CPartMngFPQ29CCharaPcs7CHandle(&PartMng,handle);
    pCVar3 = handle->m_model;
    if (pCVar3 != (CModel *)0x0) {
      iVar1 = (pCVar3->ref).refCount + -1;
      (pCVar3->ref).refCount = iVar1;
      if ((iVar1 == 0) && (pCVar3 != (CModel *)0x0)) {
        (**(code **)((int)(pCVar3->ref).vtable + 8))(pCVar3,1);
      }
      handle->m_model = (CModel *)0x0;
    }
    pCVar4 = handle->m_textureSet;
    if (pCVar4 != (CTextureSet *)0x0) {
      iVar1 = *(int *)&pCVar4->field_0x4 + -1;
      *(int *)&pCVar4->field_0x4 = iVar1;
      if ((iVar1 == 0) && (pCVar4 != (CTextureSet *)0x0)) {
        (**(code **)((int)pCVar4->vtable + 8))(pCVar4,1);
      }
      handle->m_textureSet = (CTextureSet *)0x0;
    }
    pCVar5 = handle->m_modelLoadRef;
    if (pCVar5 != (CRef *)0x0) {
      iVar1 = pCVar5->refCount + -1;
      pCVar5->refCount = iVar1;
      if ((iVar1 == 0) && (pCVar5 != (CRef *)0x0)) {
        (**(code **)((int)pCVar5->vtable + 8))(pCVar5,1);
      }
      handle->m_modelLoadRef = (CRef *)0x0;
    }
    pCVar5 = handle->m_texLoadRef;
    if (pCVar5 != (CRef *)0x0) {
      iVar1 = pCVar5->refCount + -1;
      pCVar5->refCount = iVar1;
      if ((iVar1 == 0) && (pCVar5 != (CRef *)0x0)) {
        (**(code **)((int)pCVar5->vtable + 8))(pCVar5,1);
      }
      handle->m_texLoadRef = (CRef *)0x0;
    }
    pCVar5 = handle->m_pdtLoadRef;
    if (pCVar5 != (CRef *)0x0) {
      iVar1 = pCVar5->refCount + -1;
      pCVar5->refCount = iVar1;
      if ((iVar1 == 0) && (pCVar5 != (CRef *)0x0)) {
        (**(code **)((int)pCVar5->vtable + 8))(pCVar5,1);
      }
      handle->m_pdtLoadRef = (CRef *)0x0;
    }
    releaseUnuseLoadModel__9CCharaPcsFi(&CharaPcs,0);
    iVar1 = 0;
    pCVar7 = handle;
    do {
      pCVar5 = pCVar7->m_animSlot[0];
      if ((pCVar5 != (CRef *)0x0) && (pCVar5 != (CRef *)0x0)) {
        iVar2 = pCVar5->refCount + -1;
        pCVar5->refCount = iVar2;
        if ((iVar2 == 0) && (pCVar5 != (CRef *)0x0)) {
          (**(code **)((int)pCVar5->vtable + 8))(pCVar5,1);
        }
        pCVar7->m_animSlot[0] = (CRef *)0x0;
      }
      iVar1 = iVar1 + 1;
      pCVar7 = (CCharaPcsCHandle *)&pCVar7->m_charaNo;
    } while (iVar1 < 0x40);
    iVar1 = GetSize__34CPtrArray<PQ29CCharaPcs9CLoadAnim>Fv((CPtrArray *)&CharaPcs.field_0x6c);
    while (iVar1 = iVar1 + -1, -1 < iVar1) {
      piVar6 = (int *)__vc__34CPtrArray<PQ29CCharaPcs9CLoadAnim>FUl(0x802e99d0,iVar1);
      if ((piVar6[4] < 0) && (piVar6[1] == 1)) {
        piVar6[1] = 0;
        if (piVar6 != (int *)0x0) {
          (**(code **)(*piVar6 + 8))(piVar6,1);
        }
        RemoveAt__34CPtrArray<PQ29CCharaPcs9CLoadAnim>FUl((CPtrArray *)&CharaPcs.field_0x6c,iVar1);
      }
    }
    if (0 < param_2) {
      __dl__FPv(handle);
    }
  }
  return handle;
}

