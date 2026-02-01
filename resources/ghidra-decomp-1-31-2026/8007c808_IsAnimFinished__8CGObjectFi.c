// Function: IsAnimFinished__8CGObjectFi
// Entry: 8007c808
// Size: 328 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

uint IsAnimFinished__8CGObjectFi(CGObject *gObject,int param_2)

{
  float fVar1;
  float fVar2;
  bool bVar3;
  uint uVar4;
  uint uVar5;
  CModel *pCVar6;
  CCharaPcsCHandle *pCVar7;
  double dVar8;
  
  pCVar7 = gObject->m_charaModelHandle;
  bVar3 = false;
  if ((pCVar7 != (CCharaPcsCHandle *)0x0) && (pCVar7->m_model != (CModel *)0x0)) {
    bVar3 = true;
  }
  if (bVar3) {
    if (gObject->m_currentAnimSlot != -1) {
      uVar5 = countLeadingZeros((int)(char)((int)((uint)*(byte *)&gObject->m_shieldNodeFlags << 0x1c
                                                 ) >> 0x1f));
      uVar4 = uVar5 >> 5;
      if ((uVar5 >> 5 & 0xff) != 0) {
        bVar3 = false;
        if ((pCVar7 != (CCharaPcsCHandle *)0x0) && (pCVar7->m_model != (CModel *)0x0)) {
          bVar3 = true;
        }
        if ((bVar3) && (gObject->m_currentAnimSlot != -1)) {
          pCVar6 = pCVar7->m_model;
          if (pCVar6->m_anim == (CAnim *)0x0) {
            uVar4 = 1;
          }
          else {
            fVar2 = FLOAT_80330338 + (pCVar6->m_animEnd - pCVar6->m_animStart);
            if (FLOAT_80330338 == fVar2) {
              uVar4 = 1;
            }
            else {
              if (param_2 == 0) {
                fVar1 = pCVar6->m_time;
              }
              else {
                fVar1 = gObject->m_turnSpeed;
              }
              dVar8 = (double)fVar1;
              if (param_2 == 2) {
                dVar8 = (double)(float)(dVar8 + DOUBLE_80330378);
              }
              if ((double)FLOAT_80330350 <= (double)*(float *)gObject->m_lastBgAttr) {
                uVar4 = ((uint)(byte)(((double)(fVar2 - FLOAT_80330338) < dVar8) << 3) << 0x1c) >>
                        0x1f;
              }
              else {
                uVar4 = ((uint)(byte)((dVar8 <= (double)FLOAT_80330350) << 1) << 0x1c) >> 0x1d;
              }
            }
          }
        }
        else {
          uVar4 = 1;
        }
        uVar4 = -uVar4 >> 0x1f;
      }
      return uVar4 & 0xff;
    }
  }
  return 1;
}

