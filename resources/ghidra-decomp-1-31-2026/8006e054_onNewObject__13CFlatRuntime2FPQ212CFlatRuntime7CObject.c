// Function: onNewObject__13CFlatRuntime2FPQ212CFlatRuntime7CObject
// Entry: 8006e054
// Size: 52 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void onNewObject__13CFlatRuntime2FPQ212CFlatRuntime7CObject
               (CFlatRuntime2 *flatRuntime2,CGBaseObj *baseObj)

{
  baseObj->m_isActive = baseObj->m_isActive & 0x7f | 0x80;
  Create__9CGBaseObjFv(baseObj);
  return;
}

