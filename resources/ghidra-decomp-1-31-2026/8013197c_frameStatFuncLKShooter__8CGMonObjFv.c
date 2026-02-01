// Function: frameStatFuncLKShooter__8CGMonObjFv
// Entry: 8013197c
// Size: 604 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void frameStatFuncLKShooter__8CGMonObjFv(CGMonObj *gMonObj)

{
  float fVar1;
  int iVar2;
  undefined4 *puVar3;
  CVector CStack_28;
  CVector aCStack_1c [2];
  
  SoundBuffer._1272_4_ = SoundBuffer._1272_4_ - 1 & ~((int)(SoundBuffer._1272_4_ - 1) >> 0x1f);
  SoundBuffer._1276_4_ = SoundBuffer._1276_4_ - 1 & ~((int)(SoundBuffer._1276_4_ - 1) >> 0x1f);
  iVar2 = *(int *)&gMonObj->field_0x520;
  if (iVar2 == 0x65) {
    if (*(int *)&gMonObj->field_0x528 == 0) {
      reqAnim__8CGPrgObjFiii((CGPrgObj *)gMonObj,0xffffffff,0,0);
      rotTarget__8CGMonObjFif((double)FLOAT_80331da4,gMonObj,*(undefined4 *)&gMonObj->field_0x6c4);
    }
    if (((int)((uint)(byte)m_aiWork__8CGMonObj._0_1_ << 0x18) < 0) ||
       (*(float *)(&gMonObj->field_0x5d0 + *(int *)&gMonObj->field_0x620 * 4) < FLOAT_80331da8)) {
      changeStat__8CGPrgObjFiii((CGPrgObj *)gMonObj,0,0,0);
    }
  }
  else if ((iVar2 < 0x65) && (99 < iVar2)) {
    gMonObj->field_0x63c = gMonObj->field_0x63c & 0x7f | 0x80;
    if (*(int *)&gMonObj->field_0x528 == 0) {
      memset(&gMonObj->field_0x70c,0,0x34);
      *(undefined4 *)&gMonObj->field_0x70c = 0x322;
      if (gMonObj->_bossBranchRelated == 1) {
        puVar3 = (undefined4 *)
                 __ct__7CVectorFfff(FLOAT_80331d9c,FLOAT_80331cf8,FLOAT_80331d9c,aCStack_1c);
      }
      else {
        puVar3 = (undefined4 *)
                 __ct__7CVectorFfff(FLOAT_80331d90,FLOAT_80331cf8,FLOAT_80331d94,&CStack_28);
      }
      fVar1 = FLOAT_80331da0;
      *(undefined4 *)&gMonObj->field_0x718 = *puVar3;
      *(undefined4 *)&gMonObj->field_0x71c = puVar3[1];
      *(undefined4 *)&gMonObj->field_0x720 = puVar3[2];
      *(float *)&gMonObj->field_0x728 = fVar1;
      *(undefined4 *)&gMonObj->field_0x738 = 0x65;
    }
    moveFrame__8CGMonObjFv(gMonObj);
    if ((((int)((uint)(byte)m_aiWork__8CGMonObj._0_1_ << 0x18) < 0) ||
        ((gMonObj->_bossBranchRelated == 1 && ((CFlat._4840_4_ & 1) != 0)))) ||
       ((gMonObj->_bossBranchRelated == 2 && ((CFlat._4840_4_ & 2) != 0)))) {
      changeStat__8CGPrgObjFiii((CGPrgObj *)gMonObj,0,0,0);
    }
  }
  else {
    if (gMonObj->_bossBranchRelated == 1) {
      gMonObj->_bossBranchRelated = 0;
      m_aiWork__8CGMonObj._0_1_ = m_aiWork__8CGMonObj._0_1_ & 0xdf;
      SoundBuffer._1276_4_ = 0xfa;
    }
    if (gMonObj->_bossBranchRelated == 2) {
      gMonObj->_bossBranchRelated = 0;
      m_aiWork__8CGMonObj._0_1_ = m_aiWork__8CGMonObj._0_1_ & 0xbf;
      SoundBuffer._1272_4_ = 0xfa;
    }
  }
  return;
}

