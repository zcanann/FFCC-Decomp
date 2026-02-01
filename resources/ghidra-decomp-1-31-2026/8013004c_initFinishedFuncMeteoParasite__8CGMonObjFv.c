// Function: initFinishedFuncMeteoParasite__8CGMonObjFv
// Entry: 8013004c
// Size: 444 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void initFinishedFuncMeteoParasite__8CGMonObjFv(CGMonObj *gMonObj)

{
  int iVar1;
  CModel *pCVar2;
  int iVar3;
  void *pvVar4;
  int iVar5;
  char acStack_118 [256];
  
  initFinishedFuncDefault__8CGMonObjFv(gMonObj);
  pvVar4 = (gMonObj->gObject).m_scriptHandle[4];
  if (pvVar4 == (void *)0x85) {
    iVar1 = SearchNode__Q26CChara6CModelFPc
                      (((gMonObj->gObject).m_charaModelHandle)->m_model,s_to_a_obj_801dd4e8);
    SoundBuffer._1260_4_ = ((gMonObj->gObject).m_charaModelHandle)->m_model->m_nodes + iVar1;
    ((CNode *)SoundBuffer._1260_4_)->m_flags = ((CNode *)SoundBuffer._1260_4_)->m_flags & 0x7f;
    iVar1 = SearchNode__Q26CChara6CModelFPc
                      (((gMonObj->gObject).m_charaModelHandle)->m_model,s_to_b_obj_801dd4f4);
    iVar5 = -0x7fcffeb4;
    iVar3 = 0;
    SoundBuffer._1264_4_ = ((gMonObj->gObject).m_charaModelHandle)->m_model->m_nodes + iVar1;
    ((CNode *)SoundBuffer._1264_4_)->m_flags = ((CNode *)SoundBuffer._1264_4_)->m_flags & 0x7f;
    do {
      sprintf(acStack_118,s_to_02d_obj_801dd500,iVar3 + 1);
      iVar1 = SearchNode__Q26CChara6CModelFPc
                        (((gMonObj->gObject).m_charaModelHandle)->m_model,acStack_118);
      *(CNode **)(iVar5 + 8) = ((gMonObj->gObject).m_charaModelHandle)->m_model->m_nodes + iVar1;
      if ((int)((uint)(byte)m_boss__8CGMonObj._92_1_ << 0x19 |
               (uint)((byte)m_boss__8CGMonObj._92_1_ >> 7)) < 0) {
        iVar1 = GetDispIndex__Q26CChara6CModelFPQ26CChara5CNode
                          (((gMonObj->gObject).m_charaModelHandle)->m_model,*(CNode **)(iVar5 + 8));
        pCVar2 = ((gMonObj->gObject).m_charaModelHandle)->m_model;
        pCVar2->m_meshVisibleMask = pCVar2->m_meshVisibleMask & ~(1 << iVar1);
      }
      iVar3 = iVar3 + 1;
      iVar5 = iVar5 + 4;
    } while (iVar3 < 0xc);
  }
  *(CGMonObj **)((int)&m_boss__8CGMonObj + ((int)pvVar4 + -0x85) * 4 + 0x48) = gMonObj;
  if ((int)((uint)(byte)m_boss__8CGMonObj._92_1_ << 0x19 |
           (uint)((byte)m_boss__8CGMonObj._92_1_ >> 7)) < 0) {
    SetAnimSlot__8CGObjectFii
              (&gMonObj->gObject,((int)~((int)pvVar4 - 0x87U | 0x87U - (int)pvVar4) >> 0x1f) + 0xe,0
              );
    reqAnim__8CGPrgObjFiii((CGPrgObj *)gMonObj,0,1,0);
  }
  return;
}

