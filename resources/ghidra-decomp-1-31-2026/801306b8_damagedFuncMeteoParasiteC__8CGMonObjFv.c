// Function: damagedFuncMeteoParasiteC__8CGMonObjFv
// Entry: 801306b8
// Size: 284 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void damagedFuncMeteoParasiteC__8CGMonObjFv(CGMonObj *gMonObj)

{
  void **ppvVar1;
  
  if (-1 < (int)((uint)(byte)m_boss__8CGMonObj._92_1_ << 0x19 |
                (uint)((byte)m_boss__8CGMonObj._92_1_ >> 7))) {
    if (((m_boss__8CGMonObj._88_4_ == 0) &&
        (ppvVar1 = (gMonObj->gObject).m_scriptHandle,
        (uint)*(ushort *)(ppvVar1 + 7) < ((uint)*(ushort *)((int)ppvVar1 + 0x1a) << 1) / 3)) ||
       ((m_boss__8CGMonObj._88_4_ == 1 &&
        (ppvVar1 = (gMonObj->gObject).m_scriptHandle,
        (uint)*(ushort *)(ppvVar1 + 7) < *(ushort *)((int)ppvVar1 + 0x1a) / 3)))) {
      m_boss__8CGMonObj._104_4_ = 0;
      changeStat__8CGPrgObjFiii((CGPrgObj *)gMonObj,0x66,0,0);
      (gMonObj->gObject).m_bgColMask = (gMonObj->gObject).m_bgColMask & 0xfff7ffff;
    }
    else if (0x31 < (int)m_boss__8CGMonObj._104_4_) {
      m_boss__8CGMonObj._104_4_ = 0;
      changeStat__8CGPrgObjFiii((CGPrgObj *)gMonObj,0x67,0,0);
      (gMonObj->gObject).m_bgColMask = (gMonObj->gObject).m_bgColMask & 0xfff7ffff;
    }
  }
  return;
}

