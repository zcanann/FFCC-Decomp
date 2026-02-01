// Function: onDeleteObject__13CFlatRuntime2FPQ212CFlatRuntime7CObject
// Entry: 8006e014
// Size: 64 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void onDeleteObject__13CFlatRuntime2FPQ212CFlatRuntime7CObject
               (CFlatRuntime2 *flatRuntime2,CObject *object)

{
  Destroy__9CGBaseObjFv((CGBaseObj *)object);
  *(byte *)&object[1].m_id = *(byte *)&object[1].m_id & 0x7f;
  return;
}

