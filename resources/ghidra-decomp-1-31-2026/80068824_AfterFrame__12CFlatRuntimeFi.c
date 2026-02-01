// Function: AfterFrame__12CFlatRuntimeFi
// Entry: 80068824
// Size: 236 bytes

void AfterFrame__12CFlatRuntimeFi(CFlatRuntime *flatRuntime,int param_2)

{
  CObject *pCVar1;
  CObject *pCVar2;
  
  pCVar2 = (flatRuntime->m_objRoot).m_next;
  while (pCVar1 = pCVar2, pCVar1 != &flatRuntime->m_objRoot) {
    pCVar2 = pCVar1->m_next;
    if ((param_2 != 0) || ((int)((uint)pCVar1->m_flags << 0x18) < 0)) {
      pCVar1->m_previous->m_next = pCVar2;
      pCVar1->m_next->m_previous = pCVar1->m_previous;
      *(void **)((int)*pCVar1->m_freeListNode + 4) = pCVar1->m_freeListNode[1];
      *(void **)pCVar1->m_freeListNode[1] = *pCVar1->m_freeListNode;
      pCVar1->m_freeListNode[1] = flatRuntime->m_freeHead;
      flatRuntime->m_freeHead = pCVar1->m_freeListNode;
      pCVar1->m_flags = pCVar1->m_flags & 0xef;
      (**(code **)((int)flatRuntime->vtable + 0x1c))(flatRuntime);
    }
  }
  return;
}

