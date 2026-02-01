// Function: onCreate__8CGPrgObjFv
// Entry: 80127af0
// Size: 100 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void onCreate__8CGPrgObjFv(CGPrgObj *gPrgObj)

{
  onCreate__8CGObjectFv(&gPrgObj->object);
  gPrgObj->m_lastStateId = 0;
  gPrgObj->m_stateArg = 0;
  gPrgObj->m_animFlags = gPrgObj->m_animFlags & 0x7f;
  gPrgObj->m_animFlags = gPrgObj->m_animFlags & 0xbf;
  gPrgObj->m_animFlags = gPrgObj->m_animFlags & 0xdf;
  gPrgObj->m_reqAnimId = -1;
  return;
}

