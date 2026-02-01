// Function: Destroy__12CFlatRuntimeFv
// Entry: 800697cc
// Size: 416 bytes

void Destroy__12CFlatRuntimeFv(CFlatRuntime *flatRuntime)

{
  void *pvVar1;
  CObject *pCVar2;
  CObject *pCVar3;
  int iVar4;
  int iVar5;
  
  pCVar2 = (flatRuntime->m_objRoot).m_next;
  while (pCVar2 != &flatRuntime->m_objRoot) {
    pCVar3 = pCVar2->m_next;
    pCVar2->m_previous->m_next = pCVar3;
    pCVar2->m_next->m_previous = pCVar2->m_previous;
    *(void **)((int)*pCVar2->m_freeListNode + 4) = pCVar2->m_freeListNode[1];
    *(void **)pCVar2->m_freeListNode[1] = *pCVar2->m_freeListNode;
    pCVar2->m_freeListNode[1] = flatRuntime->m_freeHead;
    flatRuntime->m_freeHead = pCVar2->m_freeListNode;
    pCVar2->m_flags = pCVar2->m_flags & 0xef;
    (**(code **)((int)flatRuntime->vtable + 0x1c))(flatRuntime);
    pCVar2 = pCVar3;
  }
  if (flatRuntime->m_variableDefs != (void *)0x0) {
    __dla__FPv(flatRuntime->m_variableDefs);
  }
  iVar5 = 0;
  for (iVar4 = 0; iVar4 < flatRuntime->m_funcCount; iVar4 = iVar4 + 1) {
    __dla__FPv(*(void **)((int)flatRuntime->m_funcsPtr + iVar5 + 0x34));
    __dla__FPv(*(void **)((int)flatRuntime->m_funcsPtr + iVar5 + 0x3c));
    iVar5 = iVar5 + 0x50;
  }
  if (flatRuntime->m_funcsPtr != (void *)0x0) {
    __dla__FPv(flatRuntime->m_funcsPtr);
  }
  pvVar1 = flatRuntime->m_classesPtr;
  if ((pvVar1 != (void *)0x0) && (pvVar1 != (void *)0x0)) {
    __dla__FPv((void *)((int)pvVar1 + -0x10));
  }
  if (flatRuntime->m_strBlob != (char *)0x0) {
    __dla__FPv(flatRuntime->m_strBlob);
  }
  if (flatRuntime->m_strOffs != (uint16_t *)0x0) {
    __dla__FPv(flatRuntime->m_strOffs);
  }
  if (flatRuntime->m_fstrBlob != (char *)0x0) {
    __dla__FPv(flatRuntime->m_fstrBlob);
  }
  if (flatRuntime->m_fstrOffs != (uint16_t *)0x0) {
    __dla__FPv(flatRuntime->m_fstrOffs);
  }
  if (flatRuntime->m_vstrBlob != (char *)0x0) {
    __dla__FPv(flatRuntime->m_vstrBlob);
  }
  if (flatRuntime->m_vstrOffs != (uint16_t *)0x0) {
    __dla__FPv(flatRuntime->m_vstrOffs);
  }
  clear__12CFlatRuntimeFv(flatRuntime);
  return;
}

