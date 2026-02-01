// Function: attackCheckFuncLKShooter__8CGMonObjFi
// Entry: 80131828
// Size: 340 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

undefined4 attackCheckFuncLKShooter__8CGMonObjFi(CGMonObj *gMonObj)

{
  Vec *pVVar1;
  double dVar2;
  CVector CStack_28;
  CVector CStack_1c;
  
  if (SoundBuffer._1268_4_ == 0) {
    if ((-1 < (int)((uint)(byte)m_aiWork__8CGMonObj._0_1_ << 0x19 |
                   (uint)((byte)m_aiWork__8CGMonObj._0_1_ >> 7))) && ((CFlat._4840_4_ & 2) == 0)) {
      pVVar1 = (Vec *)__ct__7CVectorFfff(FLOAT_80331d90,FLOAT_80331cf8,FLOAT_80331d94,&CStack_1c);
      dVar2 = (double)PSVECDistance(pVVar1,&(gMonObj->gObject).m_worldPosition);
      if ((dVar2 < (double)FLOAT_80331d98) && (SoundBuffer._1272_4_ == 0)) {
        m_aiWork__8CGMonObj._0_1_ = m_aiWork__8CGMonObj._0_1_ & 0xbf | 0x40;
        SoundBuffer._1272_4_ = 300;
        gMonObj->_bossBranchRelated = 2;
        return 100;
      }
    }
    if ((-1 < (int)((uint)(byte)m_aiWork__8CGMonObj._0_1_ << 0x1a |
                   (uint)((byte)m_aiWork__8CGMonObj._0_1_ >> 6))) && ((CFlat._4840_4_ & 1) == 0)) {
      pVVar1 = (Vec *)__ct__7CVectorFfff(FLOAT_80331d9c,FLOAT_80331cf8,FLOAT_80331d9c,&CStack_28);
      dVar2 = (double)PSVECDistance(pVVar1,&(gMonObj->gObject).m_worldPosition);
      if ((dVar2 < (double)FLOAT_80331d98) && (SoundBuffer._1276_4_ == 0)) {
        m_aiWork__8CGMonObj._0_1_ = m_aiWork__8CGMonObj._0_1_ & 0xdf | 0x20;
        gMonObj->_bossBranchRelated = 1;
        return 100;
      }
    }
  }
  return 0xffffffff;
}

