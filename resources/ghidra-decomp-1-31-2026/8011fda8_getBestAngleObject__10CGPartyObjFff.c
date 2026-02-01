// Function: getBestAngleObject__10CGPartyObjFff
// Entry: 8011fda8
// Size: 484 bytes

/* WARNING: Removing unreachable block (ram,0x8011ff64) */
/* WARNING: Removing unreachable block (ram,0x8011ff5c) */
/* WARNING: Removing unreachable block (ram,0x8011ff54) */
/* WARNING: Removing unreachable block (ram,0x8011fdc8) */
/* WARNING: Removing unreachable block (ram,0x8011fdc0) */
/* WARNING: Removing unreachable block (ram,0x8011fdb8) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

CGPrgObj * getBestAngleObject__10CGPartyObjFff(double param_1,CGPrgObj *param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  CGPrgObj *other;
  uint uVar4;
  CGPrgObj *pCVar5;
  double dVar6;
  double dVar7;
  double dVar8;
  double dVar9;
  double dVar10;
  double dVar11;
  Vec aVStack_58 [2];
  
  dVar11 = (double)FLOAT_80331a78;
  pCVar5 = (CGPrgObj *)0x0;
  for (other = (CGPrgObj *)FindGObjFirst__13CFlatRuntime2Fv((CFlatRuntime2 *)&CFlat);
      other != (CGPrgObj *)0x0;
      other = (CGPrgObj *)
              FindGObjNext__13CFlatRuntime2FP8CGObject((CFlatRuntime2 *)&CFlat,&other->object)) {
    uVar4 = (other->object).m_attrFlags;
    if (((uVar4 & 0x18) != 0) &&
       (((uVar4 & 8) == 0 ||
        ((((other->object).m_displayFlags & 1) != 0 &&
         (*(short *)((other->object).m_scriptHandle + 7) != 0)))))) {
      dVar7 = (double)(other->object).m_worldPosition.x;
      dVar6 = (double)(param_2->object).m_worldPosition.x;
      if (dVar7 != dVar6) {
        dVar9 = (double)(other->object).m_worldPosition.z;
        dVar8 = (double)(param_2->object).m_worldPosition.z;
        if (dVar9 != dVar8) {
          fVar1 = (other->object).m_bodyEllipsoidRadius;
          dVar10 = (double)(fVar1 + (float)(param_1 +
                                           (double)(param_2->object).m_bodyEllipsoidRadius));
          if (((((double)(float)(dVar6 - dVar10) <= dVar7) &&
               ((double)(float)(dVar8 - dVar10) <= dVar9)) &&
              (dVar7 <= (double)(float)(dVar6 + dVar10))) &&
             (dVar9 <= (double)(float)(dVar8 + dVar10))) {
            fVar2 = (param_2->object).m_worldPosition.y;
            fVar1 = FLOAT_80331ad4 * fVar1;
            fVar3 = (other->object).m_worldPosition.y;
            if ((fVar3 <= fVar2 + fVar1) && (fVar2 - fVar1 <= fVar3)) {
              PSVECSubtract(&(other->object).m_worldPosition,&(param_2->object).m_worldPosition,
                            aVStack_58);
              aVStack_58[0].y = FLOAT_80331a78;
              dVar6 = (double)PSVECSquareMag(aVStack_58);
              if (((double)FLOAT_80331a78 < dVar6) && (dVar6 < (double)(float)(dVar10 * dVar10))) {
                dVar6 = (double)dstTargetRot__8CGPrgObjFP8CGPrgObj(param_2,other);
                if (dVar11 < (double)(float)ABS(dVar6)) {
                  pCVar5 = other;
                  dVar11 = (double)(float)ABS(dVar6);
                }
              }
            }
          }
        }
      }
    }
  }
  return pCVar5;
}

