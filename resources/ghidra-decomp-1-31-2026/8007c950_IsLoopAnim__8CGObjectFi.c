// Function: IsLoopAnim__8CGObjectFi
// Entry: 8007c950
// Size: 224 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

uint IsLoopAnim__8CGObjectFi(CGObject *gObject,int mode)

{
  float fVar1;
  float fVar2;
  bool bVar3;
  CModel *pCVar4;
  CCharaPcsCHandle *pCVar5;
  double dVar6;
  
  pCVar5 = gObject->m_charaModelHandle;
  bVar3 = false;
  if ((pCVar5 != (CCharaPcsCHandle *)0x0) && (pCVar5->m_model != (CModel *)0x0)) {
    bVar3 = true;
  }
  if ((!bVar3) || (gObject->m_currentAnimSlot == -1)) {
    return 1;
  }
  pCVar4 = pCVar5->m_model;
  if (pCVar4->m_anim == (CAnim *)0x0) {
    return 1;
  }
  fVar2 = FLOAT_80330338 + (pCVar4->m_animEnd - pCVar4->m_animStart);
  if (FLOAT_80330338 == fVar2) {
    return 1;
  }
  if (mode == 0) {
    fVar1 = pCVar4->m_time;
  }
  else {
    fVar1 = gObject->m_turnSpeed;
  }
  dVar6 = (double)fVar1;
  if (mode == 2) {
    dVar6 = (double)(float)(dVar6 + DOUBLE_80330378);
  }
  if ((double)*(float *)gObject->m_lastBgAttr < (double)FLOAT_80330350) {
    return ((uint)(byte)((dVar6 <= (double)FLOAT_80330350) << 1) << 0x1c) >> 0x1d;
  }
  return ((uint)(byte)(((double)(fVar2 - FLOAT_80330338) < dVar6) << 3) << 0x1c) >> 0x1f;
}

