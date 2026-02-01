// Function: attackedFuncSaw__8CGMonObjFv
// Entry: 80131bd8
// Size: 76 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void attackedFuncSaw__8CGMonObjFv(CGMonObj *gMonObj)

{
  if (*(int *)&gMonObj->field_0x520 == 100) {
    addSubStat__8CGPrgObjFv((CGPrgObj *)gMonObj);
    m_aiWork__8CGMonObj._0_1_ = m_aiWork__8CGMonObj._0_1_ & 0x7f | 0x80;
    SoundBuffer._1268_4_ = 0xfa;
  }
  return;
}

