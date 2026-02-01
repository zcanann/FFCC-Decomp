// Function: enableDamageCol__8CGMonObjFi
// Entry: 80117b08
// Size: 40 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void enableDamageCol__8CGMonObjFi(CGMonObj *gMonObj,int param_2)

{
  if (param_2 != 0) {
    (gMonObj->gObject).m_damageColliders[1].m_localPosition.x = 1.4013e-45;
    (gMonObj->gObject).m_damageColliders[2].m_localPosition.x = 1.4013e-45;
    return;
  }
  (gMonObj->gObject).m_damageColliders[1].m_localPosition.x = 0.0;
  (gMonObj->gObject).m_damageColliders[2].m_localPosition.x = 0.0;
  return;
}

