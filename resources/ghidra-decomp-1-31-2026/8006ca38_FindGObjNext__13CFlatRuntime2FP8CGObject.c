// Function: FindGObjNext__13CFlatRuntime2FP8CGObject
// Entry: 8006ca38
// Size: 164 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

CObject * FindGObjNext__13CFlatRuntime2FP8CGObject(CFlatRuntime2 *flatRuntime2,CGObject *gObject)

{
  byte bVar1;
  uint uVar2;
  CObject *pCVar3;
  
  pCVar3 = (gObject->base_object).object.m_next;
  do {
    if (pCVar3 == &(flatRuntime2->flatRuntimeBase).m_objRoot) {
      return (CObject *)0x0;
    }
    if (-1 < pCVar3->m_classIndex) {
      bVar1 = pCVar3->m_flags;
      if (((-1 < (int)((uint)bVar1 << 0x18)) &&
          (-1 < (int)((uint)bVar1 << 0x19 | (uint)(bVar1 >> 7)))) &&
         (uVar2 = (**(code **)((int)pCVar3->m_vtable + 0xc))(pCVar3), (uVar2 & 5) == 5)) {
        return pCVar3;
      }
    }
    pCVar3 = pCVar3->m_next;
  } while( true );
}

