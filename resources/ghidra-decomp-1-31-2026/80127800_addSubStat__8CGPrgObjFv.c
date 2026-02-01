// Function: addSubStat__8CGPrgObjFv
// Entry: 80127800
// Size: 32 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void addSubStat__8CGPrgObjFv(CGPrgObj *gPrgObj)

{
  gPrgObj->m_subState = gPrgObj->m_subState + 1;
  gPrgObj->m_subFrame = 0;
  gPrgObj->m_subFrameGate = 1;
  return;
}

