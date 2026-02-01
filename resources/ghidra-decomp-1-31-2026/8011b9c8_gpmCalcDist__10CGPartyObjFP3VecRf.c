// Function: gpmCalcDist__10CGPartyObjFP3VecRf
// Entry: 8011b9c8
// Size: 448 bytes

/* WARNING: Removing unreachable block (ram,0x8011bb6c) */
/* WARNING: Removing unreachable block (ram,0x8011b9d8) */

void gpmCalcDist__10CGPartyObjFP3VecRf(int param_1,Vec *param_2,float *param_3)

{
  float fVar1;
  bool bVar2;
  Vec *vecB;
  int iVar3;
  int iVar4;
  double dVar5;
  double dVar6;
  Vec local_48;
  undefined auStack_3c [12];
  
  if (m_ghostWork__10CGPartyObj._40_4_ != 0) {
    __ct__7CVectorFv(auStack_3c);
    dVar5 = (double)FLOAT_80331a78;
    iVar3 = -0x7fcffe28;
    bVar2 = false;
    *param_3 = FLOAT_80331a78;
    for (iVar4 = 0; iVar4 < (int)m_ghostWork__10CGPartyObj._40_4_; iVar4 = iVar4 + 1) {
      if ((int)m_ghostWork__10CGPartyObj._44_4_ <= iVar4) {
        if (iVar4 == m_ghostWork__10CGPartyObj._44_4_) {
          vecB = (Vec *)(param_1 + 0x15c);
        }
        else {
          vecB = (Vec *)(&m_ghostWork__10CGPartyObj.field_0x24 + iVar4 * 0xc);
        }
        PSVECSubtract((Vec *)(iVar3 + 0x50),vecB,&local_48);
        dVar6 = (double)PSVECMag(&local_48);
        local_48.y = FLOAT_80331a78;
        *param_3 = (float)((double)*param_3 + dVar6);
        dVar6 = (double)PSVECMag(&local_48);
        dVar5 = (double)(float)(dVar5 + dVar6);
        if ((!bVar2) && (iVar4 == m_ghostWork__10CGPartyObj._44_4_)) {
          bVar2 = true;
          param_2->x = local_48.x;
          param_2->y = local_48.y;
          param_2->z = local_48.z;
          if (dVar6 < (double)*(float *)(param_1 + 0x134)) {
            m_ghostWork__10CGPartyObj._44_4_ = m_ghostWork__10CGPartyObj._44_4_ + 1;
          }
        }
      }
      iVar3 = iVar3 + 0xc;
    }
    if ((double)*param_3 < dVar5) {
      dVar5 = (double)*param_3;
    }
    *param_3 = (float)dVar5;
    if ((double)*param_3 <= DOUBLE_80331aa8) {
      return;
    }
  }
  fVar1 = FLOAT_80331a78;
  m_ghostWork__10CGPartyObj._40_4_ = 0;
  param_2->x = *(float *)(param_1 + 0x5e0);
  param_2->y = *(float *)(param_1 + 0x5e4);
  param_2->z = *(float *)(param_1 + 0x5e8);
  param_2->y = fVar1;
  dVar5 = (double)PSVECMag(param_2);
  *param_3 = (float)dVar5;
  fVar1 = *(float *)(param_1 + 0x5d0);
  if (*param_3 < fVar1) {
    fVar1 = *param_3;
  }
  *param_3 = fVar1;
  return;
}

