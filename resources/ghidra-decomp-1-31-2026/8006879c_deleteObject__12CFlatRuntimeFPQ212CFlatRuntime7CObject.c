// Function: deleteObject__12CFlatRuntimeFPQ212CFlatRuntime7CObject
// Entry: 8006879c
// Size: 136 bytes

void deleteObject__12CFlatRuntimeFPQ212CFlatRuntime7CObject
               (CFlatRuntime *flatRuntime,CObject *object)

{
  object->m_previous->m_next = object->m_next;
  object->m_next->m_previous = object->m_previous;
  *(void **)((int)*object->m_freeListNode + 4) = object->m_freeListNode[1];
  *(void **)object->m_freeListNode[1] = *object->m_freeListNode;
  object->m_freeListNode[1] = flatRuntime->m_freeHead;
  flatRuntime->m_freeHead = object->m_freeListNode;
  object->m_flags = object->m_flags & 0xef;
  (**(code **)((int)flatRuntime->vtable + 0x1c))();
  return;
}

