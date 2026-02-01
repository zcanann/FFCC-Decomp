// Function: logicFuncSaw__8CGMonObjFv
// Entry: 80131d04
// Size: 212 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void logicFuncSaw__8CGMonObjFv(CGMonObj *gMonObj)

{
  if ((CFlat._4840_4_ == 0) && ((int)((uint)(byte)m_aiWork__8CGMonObj._0_1_ << 0x18) < 0)) {
    m_aiWork__8CGMonObj._0_1_ = m_aiWork__8CGMonObj._0_1_ & 0x7f;
  }
  if ((CFlat._4840_4_ == 0) || ((int)((uint)(byte)m_aiWork__8CGMonObj._0_1_ << 0x18) < 0)) {
    if ((*(int *)&gMonObj->field_0x520 == 100) && (*(int *)&gMonObj->field_0x52c == 1)) {
      addSubStat__8CGPrgObjFv((CGPrgObj *)gMonObj);
    }
  }
  else if (*(int *)&gMonObj->field_0x520 != 100) {
    changeStat__8CGPrgObjFiii((CGPrgObj *)gMonObj,100,0,0);
  }
  SoundBuffer._1268_4_ = SoundBuffer._1268_4_ - 1 & ~((int)(SoundBuffer._1268_4_ - 1) >> 0x1f);
  return;
}

