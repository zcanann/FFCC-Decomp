// Function: SetDispItemName__8CGObjectFi
// Entry: 8007c6e4
// Size: 28 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void SetDispItemName__8CGObjectFi(CGObject *gObject,char param_2)

{
  *(byte *)&gObject->m_shieldNodeFlags =
       (byte)((int)param_2 << 4) & 0x10 | *(byte *)&gObject->m_shieldNodeFlags & 0xef;
  gObject->m_dispItemTimer = '\r';
  return;
}

