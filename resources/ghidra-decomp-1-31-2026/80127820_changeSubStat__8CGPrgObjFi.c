// Function: changeSubStat__8CGPrgObjFi
// Entry: 80127820
// Size: 24 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void changeSubStat__8CGPrgObjFi(CGPrgObj *gPrgObj,int32_t subState)

{
  gPrgObj->m_subState = subState;
  gPrgObj->m_subFrame = 0;
  gPrgObj->m_subFrameGate = 1;
  return;
}

