// Function: Frame__12CFlatRuntimeFii
// Entry: 80068910
// Size: 756 bytes

undefined4 Frame__12CFlatRuntimeFii(CFlatRuntime *flatRuntime,int param_2)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  CObject *pCVar4;
  CObject *object;
  undefined4 uVar5;
  int iVar6;
  
  uVar5 = 0;
  pCVar4 = (flatRuntime->m_objRoot).m_next;
  do {
    object = pCVar4;
    if (object == &flatRuntime->m_objRoot) {
      return uVar5;
    }
    do {
      if (((int)((uint)object->m_flags << 0x18) < 0) || (param_2 == 0)) goto LAB_80068b54;
      object->m_flags = object->m_flags & 0xbf;
      iVar1 = objectFrame__12CFlatRuntimeFPQ212CFlatRuntime7CObject(flatRuntime,object);
      if (iVar1 == 0) goto LAB_80068b54;
      if (object->m_scriptPriority == 0) break;
      iVar1 = 0x1f;
      object->m_stackPointer = object->m_stackPointer + -1;
      uVar2 = (uint)(ushort)object->m_scriptPriority;
      iVar6 = 4;
      do {
        iVar3 = iVar1;
        if ((((((uVar2 & 0x80000000) != 0) || (iVar3 = iVar1 + -1, (uVar2 & 0x40000000) != 0)) ||
             (iVar3 = iVar1 + -2, (uVar2 & 0x20000000) != 0)) ||
            ((iVar3 = iVar1 + -3, (uVar2 & 0x10000000) != 0 ||
             (iVar3 = iVar1 + -4, (uVar2 & 0x8000000) != 0)))) ||
           ((iVar3 = iVar1 + -5, (uVar2 & 0x4000000) != 0 ||
            ((iVar3 = iVar1 + -6, (uVar2 & 0x2000000) != 0 ||
             (iVar3 = iVar1 + -7, (uVar2 & 0x1000000) != 0)))))) goto LAB_80068a44;
        uVar2 = uVar2 << 8;
        iVar1 = iVar1 + -8;
        iVar6 = iVar6 + -1;
      } while (iVar6 != 0);
      iVar3 = -1;
LAB_80068a44:
      (**(code **)((int)flatRuntime->vtable + 0x40))(flatRuntime,iVar3,object);
      object->m_scriptPriority = object->m_scriptPriority & ~(ushort)(1 << iVar3);
      iVar1 = 0x1f;
      uVar2 = (uint)(ushort)object->m_scriptPriority;
      iVar6 = 4;
      do {
        iVar3 = iVar1;
        if (((((uVar2 & 0x80000000) != 0) || (iVar3 = iVar1 + -1, (uVar2 & 0x40000000) != 0)) ||
            (iVar3 = iVar1 + -2, (uVar2 & 0x20000000) != 0)) ||
           (((iVar3 = iVar1 + -3, (uVar2 & 0x10000000) != 0 ||
             (iVar3 = iVar1 + -4, (uVar2 & 0x8000000) != 0)) ||
            ((iVar3 = iVar1 + -5, (uVar2 & 0x4000000) != 0 ||
             ((iVar3 = iVar1 + -6, (uVar2 & 0x2000000) != 0 ||
              (iVar3 = iVar1 + -7, (uVar2 & 0x1000000) != 0)))))))) goto LAB_80068b2c;
        uVar2 = uVar2 << 8;
        iVar1 = iVar1 + -8;
        iVar6 = iVar6 + -1;
      } while (iVar6 != 0);
      iVar3 = -1;
LAB_80068b2c:
    } while (-1 < iVar3);
    object->m_flags = object->m_flags & 0x7f | 0x80;
    if (object->m_particleId == 1) {
      uVar5 = 1;
    }
LAB_80068b54:
    pCVar4 = object->m_next;
    if ((int)((uint)object->m_flags << 0x18) < 0) {
      object->m_previous->m_next = pCVar4;
      object->m_next->m_previous = object->m_previous;
      *(void **)((int)*object->m_freeListNode + 4) = object->m_freeListNode[1];
      *(void **)object->m_freeListNode[1] = *object->m_freeListNode;
      object->m_freeListNode[1] = flatRuntime->m_freeHead;
      flatRuntime->m_freeHead = object->m_freeListNode;
      object->m_flags = object->m_flags & 0xef;
      (**(code **)((int)flatRuntime->vtable + 0x1c))(flatRuntime,object);
    }
  } while( true );
}

