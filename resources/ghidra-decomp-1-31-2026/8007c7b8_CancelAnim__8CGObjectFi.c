// Function: CancelAnim__8CGObjectFi
// Entry: 8007c7b8
// Size: 80 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void CancelAnim__8CGObjectFi(CGObject *gObject,int param_2)

{
  float fVar1;
  
  gObject->m_currentAnimSlot = -1;
  fVar1 = FLOAT_80330350;
  *(byte *)&gObject->m_shieldNodeFlags = *(byte *)&gObject->m_shieldNodeFlags & 0xbf;
  gObject->m_turnSpeed = fVar1;
  if (param_2 != 0) {
    gObject->m_rotTargetY = gObject->m_rotBaseY;
  }
  *(byte *)&gObject->m_shieldNodeFlags = *(byte *)&gObject->m_shieldNodeFlags & 0xf7;
  *(byte *)&gObject->m_shieldNodeFlags = *(byte *)&gObject->m_shieldNodeFlags & 0x7f;
  return;
}

