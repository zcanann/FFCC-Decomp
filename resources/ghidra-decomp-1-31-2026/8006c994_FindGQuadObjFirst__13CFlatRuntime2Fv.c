// Function: FindGQuadObjFirst__13CFlatRuntime2Fv
// Entry: 8006c994
// Size: 164 bytes

CObject * FindGQuadObjFirst__13CFlatRuntime2Fv(CFlatRuntime2 *flatRuntime2)

{
  byte bVar1;
  uint uVar2;
  CObject *pCVar3;
  
  pCVar3 = ((flatRuntime2->flatRuntimeBase).m_objRoot.m_next)->m_next;
  do {
    if (pCVar3 == &(flatRuntime2->flatRuntimeBase).m_objRoot) {
      return (CObject *)0x0;
    }
    if (-1 < pCVar3->m_classIndex) {
      bVar1 = pCVar3->m_flags;
      if (((-1 < (int)((uint)bVar1 << 0x18)) &&
          (-1 < (int)((uint)bVar1 << 0x19 | (uint)(bVar1 >> 7)))) &&
         (uVar2 = (**(code **)((int)pCVar3->m_vtable + 0xc))(pCVar3), (uVar2 & 3) == 3)) {
        return pCVar3;
      }
    }
    pCVar3 = pCVar3->m_next;
  } while( true );
}

