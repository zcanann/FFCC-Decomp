// Function: reqAnim__8CGPrgObjFiii
// Entry: 801277c8
// Size: 56 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void reqAnim__8CGPrgObjFiii(CGPrgObj *gPrgObj,int32_t param_2,char param_3,char param_4)

{
  gPrgObj->m_animFlags = gPrgObj->m_animFlags & 0x7f | 0x80;
  gPrgObj->m_reqAnimId = param_2;
  gPrgObj->m_animFlags = (byte)((int)param_3 << 6) & 0x40 | gPrgObj->m_animFlags & 0xbf;
  gPrgObj->m_animFlags = (byte)((int)param_4 << 5) & 0x20 | gPrgObj->m_animFlags & 0xdf;
  return;
}

