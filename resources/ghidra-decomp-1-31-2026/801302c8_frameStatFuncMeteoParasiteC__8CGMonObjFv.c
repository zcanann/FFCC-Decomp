// Function: frameStatFuncMeteoParasiteC__8CGMonObjFv
// Entry: 801302c8
// Size: 1008 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void frameStatFuncMeteoParasiteC__8CGMonObjFv(CGMonObj *gMonObj)

{
  int iVar1;
  
  iVar1 = *(int *)&gMonObj->field_0x520;
  if (iVar1 == 0x67) {
    iVar1 = *(int *)&gMonObj->field_0x52c;
    if (iVar1 == 0) {
      if (*(int *)&gMonObj->field_0x530 == 0) {
        damageDelete__10CGCharaObjFv();
        reqAnim__8CGPrgObjFiii((CGPrgObj *)gMonObj,m_boss__8CGMonObj._88_4_ * 3 + 0x1c,0,0);
      }
      else {
        iVar1 = isLoopAnim__8CGPrgObjFv((CGPrgObj *)gMonObj);
        if (iVar1 != 0) {
          changeSubStat__8CGPrgObjFi((CGPrgObj *)gMonObj,1);
        }
      }
    }
    else if (iVar1 == 1) {
      if (*(int *)&gMonObj->field_0x530 == 0) {
        m_boss__8CGMonObj._92_1_ = m_boss__8CGMonObj._92_1_ & 0x7f | 0x80;
        m_boss__8CGMonObj._96_4_ = 1;
        reqAnim__8CGPrgObjFiii((CGPrgObj *)gMonObj,m_boss__8CGMonObj._88_4_ * 3 + 0x1d,1,0);
      }
      else if (-1 < (int)((uint)(byte)m_boss__8CGMonObj._92_1_ << 0x18)) {
        changeSubStat__8CGPrgObjFi((CGPrgObj *)gMonObj,2);
      }
    }
    else if (iVar1 == 2) {
      if (*(int *)&gMonObj->field_0x530 == 0) {
        reqAnim__8CGPrgObjFiii((CGPrgObj *)gMonObj,m_boss__8CGMonObj._88_4_ * 3 + 0x1e,0,0);
        playSe3D__8CGPrgObjFiiiiP3Vec
                  ((CGPrgObj *)gMonObj,m_boss__8CGMonObj._88_4_ * 2 + 0x11d34,0x32,0x96,0,0);
      }
      else {
        iVar1 = isLoopAnim__8CGPrgObjFv((CGPrgObj *)gMonObj);
        if (iVar1 != 0) {
          SetAnimSlot__8CGObjectFii(&gMonObj->gObject,0,0);
          changeStat__8CGPrgObjFiii((CGPrgObj *)gMonObj,0,0,0);
          gMonObj->_bossBranchRelated = 0;
          m_boss__8CGMonObj._100_4_ = 0x177;
          *(undefined4 *)&gMonObj->field_0x6c8 = 0;
        }
      }
    }
  }
  else if (iVar1 < 0x67) {
    if (iVar1 == 0x65) {
      if (*(int *)&gMonObj->field_0x52c == 0) {
        if (*(int *)&gMonObj->field_0x530 == 0) {
          m_boss__8CGMonObj._92_1_ = m_boss__8CGMonObj._92_1_ & 0x7f | 0x80;
          m_boss__8CGMonObj._96_4_ = 0;
        }
        else if (-1 < (int)((uint)(byte)m_boss__8CGMonObj._92_1_ << 0x18)) {
          addSubStat__8CGPrgObjFv((CGPrgObj *)gMonObj);
        }
      }
      else if (*(int *)&gMonObj->field_0x52c == 1) {
        if (*(int *)&gMonObj->field_0x530 == 0) {
          reqAnim__8CGPrgObjFiii((CGPrgObj *)gMonObj,m_boss__8CGMonObj._88_4_ + 0x16,0,0);
          playSe3D__8CGPrgObjFiiiiP3Vec
                    ((CGPrgObj *)gMonObj,m_boss__8CGMonObj._88_4_ * 2 + 0x11d35,0x32,0x96,0,0);
        }
        else {
          iVar1 = isLoopAnim__8CGPrgObjFv((CGPrgObj *)gMonObj);
          if (iVar1 != 0) {
            SetAnimSlot__8CGObjectFii(&gMonObj->gObject,m_boss__8CGMonObj._88_4_ + 0x19,0);
            changeStat__8CGPrgObjFiii((CGPrgObj *)gMonObj,0,0,0);
            gMonObj->_bossBranchRelated = 1;
            (gMonObj->gObject).m_bgColMask = (gMonObj->gObject).m_bgColMask | 0x80000;
          }
        }
      }
    }
    else if (100 < iVar1) {
      if (*(int *)&gMonObj->field_0x528 == 0) {
        damageDelete__10CGCharaObjFv();
        changeStat__8CGPrgObjFiii
                  (*(CGPrgObj **)(&m_boss__8CGMonObj.field_0x48 + m_boss__8CGMonObj._88_4_ * 4),0x65
                   ,0,0);
        reqAnim__8CGPrgObjFiii((CGPrgObj *)gMonObj,m_boss__8CGMonObj._88_4_ + 0x25,0,0);
        CFlat._4836_1_ = CFlat._4836_1_ & 0xdf | 0x20;
        CFlat._4840_4_ = CFlat._4840_4_ + 1;
      }
      else {
        iVar1 = isLoopAnim__8CGPrgObjFv((CGPrgObj *)gMonObj);
        if (iVar1 != 0) {
          SetAnimSlot__8CGObjectFii(&gMonObj->gObject,0,0);
          changeStat__8CGPrgObjFiii((CGPrgObj *)gMonObj,0,0,0);
          gMonObj->_bossBranchRelated = 0;
          m_boss__8CGMonObj._100_4_ = 0x177;
          m_boss__8CGMonObj._88_4_ = m_boss__8CGMonObj._88_4_ + 1;
          if (2 < (int)m_boss__8CGMonObj._88_4_) {
            m_boss__8CGMonObj._88_4_ = 0;
          }
          *(undefined4 *)&gMonObj->field_0x6c8 = 0;
        }
      }
    }
  }
  else if ((iVar1 < 0x69) && (*(int *)&gMonObj->field_0x528 == 0)) {
    reqAnim__8CGPrgObjFiii((CGPrgObj *)gMonObj,0x35,1,0);
  }
  return;
}

