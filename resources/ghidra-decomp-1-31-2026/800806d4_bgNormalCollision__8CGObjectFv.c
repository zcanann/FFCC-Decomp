// Function: bgNormalCollision__8CGObjectFv
// Entry: 800806d4
// Size: 1428 bytes

/* WARNING: Removing unreachable block (ram,0x80080c40) */
/* WARNING: Removing unreachable block (ram,0x80080c38) */
/* WARNING: Removing unreachable block (ram,0x80080c30) */
/* WARNING: Removing unreachable block (ram,0x800806f4) */
/* WARNING: Removing unreachable block (ram,0x800806ec) */
/* WARNING: Removing unreachable block (ram,0x800806e4) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void bgNormalCollision__8CGObjectFv(CGObject *gObject)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  int iVar5;
  double dVar6;
  double dVar7;
  double dVar8;
  Vec VStack_128;
  Vec local_11c;
  Vec local_110;
  float local_104;
  float local_100;
  float local_fc;
  float local_ec;
  float local_e8;
  float local_e4;
  float local_e0;
  float local_dc;
  float local_d8;
  float local_d4;
  float local_d0;
  float local_cc;
  float local_c8;
  float local_c4;
  float local_c0;
  float local_bc;
  float local_ac;
  float local_a8;
  float local_a4;
  float local_a0;
  float local_9c;
  float local_98;
  float local_94;
  float local_90;
  float local_8c;
  float local_88;
  float local_84;
  float local_80;
  float local_7c;
  float local_6c;
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  float local_48;
  
  if (ABS((double)(gObject->m_groundHitOffset).x) < DOUBLE_80330400) {
    (gObject->m_groundHitOffset).x = FLOAT_80330350;
  }
  if (ABS((double)(gObject->m_groundHitOffset).y) < DOUBLE_80330400) {
    (gObject->m_groundHitOffset).y = FLOAT_80330350;
  }
  if (ABS((double)(gObject->m_groundHitOffset).z) < DOUBLE_80330400) {
    (gObject->m_groundHitOffset).z = FLOAT_80330350;
  }
  if (((FLOAT_80330350 != (gObject->m_groundHitOffset).x) ||
      (FLOAT_80330350 != (gObject->m_groundHitOffset).y)) ||
     (FLOAT_80330350 != (gObject->m_groundHitOffset).z)) {
    local_110.x = (gObject->m_groundHitOffset).x;
    iVar5 = 4;
    dVar6 = (double)FLOAT_8033033c;
    local_110.z = (gObject->m_groundHitOffset).z;
    dVar7 = (double)FLOAT_80330340;
    local_110.y = FLOAT_80330350;
    local_11c.x = (gObject->m_worldPosition).x;
    local_11c.z = (gObject->m_worldPosition).z;
    local_11c.y = (gObject->m_worldPosition).y + FLOAT_80330360 + gObject->m_capsuleHalfHeight;
    dVar8 = DOUBLE_80330400;
    do {
      local_60 = gObject->m_capsuleHalfHeight;
      local_54 = (float)dVar6;
      local_58 = (float)dVar6;
      local_5c = (float)dVar6;
      local_48 = (float)dVar7;
      local_4c = (float)dVar7;
      local_50 = (float)dVar7;
      local_84 = local_11c.x;
      local_80 = local_11c.y;
      local_7c = local_11c.z;
      local_6c = local_110.x;
      local_68 = local_110.y;
      local_64 = local_110.z;
      iVar4 = CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl
                        (&MapMng,&local_84,&local_110,(gObject->m_moveVec).x);
      if (iVar4 == 0) break;
      gObject->m_stateFlags0 = gObject->m_stateFlags0 & 0xbf | 0x40;
      CalcHitSlide__7CMapObjFP3Vecf((CMapObj *)MapMng._141944_4_,&local_110);
      if (ABS((double)local_110.x) < dVar8) {
        local_110.x = FLOAT_80330350;
      }
      if (ABS((double)local_110.y) < dVar8) {
        local_110.y = FLOAT_80330350;
      }
      if (ABS((double)local_110.z) < dVar8) {
        local_110.z = FLOAT_80330350;
      }
      iVar5 = iVar5 + -1;
    } while (iVar5 != 0);
    fVar3 = FLOAT_80330350;
    if (iVar5 == 0) {
      (gObject->m_groundHitOffset).z = FLOAT_80330350;
      (gObject->m_groundHitOffset).y = fVar3;
      (gObject->m_groundHitOffset).x = fVar3;
    }
    else {
      PSVECAdd(&local_11c,&local_110,&local_11c);
      local_110.y = (gObject->m_groundHitOffset).y - FLOAT_80330360;
      local_110.x = FLOAT_80330350;
      local_110.z = FLOAT_80330350;
      local_a0 = gObject->m_capsuleHalfHeight;
      local_94 = FLOAT_8033033c;
      local_98 = FLOAT_8033033c;
      local_9c = FLOAT_8033033c;
      local_88 = FLOAT_80330340;
      local_8c = FLOAT_80330340;
      local_90 = FLOAT_80330340;
      local_c4 = local_11c.x;
      local_c0 = local_11c.y;
      local_bc = local_11c.z;
      local_ac = FLOAT_80330350;
      local_a4 = FLOAT_80330350;
      local_a8 = local_110.y;
      iVar5 = CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl
                        (&MapMng,&local_c4,&local_110,(gObject->m_moveVec).x);
      if (iVar5 == 0) {
        local_11c.y = local_11c.y - gObject->m_capsuleHalfHeight;
        PSVECAdd(&local_11c,&local_110,&local_11c);
        PSVECSubtract(&local_11c,&gObject->m_worldPosition,&gObject->m_groundHitOffset);
      }
      else {
        if ((*(uint *)(MapMng.mapIdGrpArr + *(byte *)(DAT_8032ec90 + 0x47)) & 0x20) == 0) {
          gObject->m_stateFlags0 = gObject->m_stateFlags0 & 0x7f | 0x80;
          (gObject->m_radiusCtrl).x =
               *(float *)(MapMng.mapIdGrpArr + *(byte *)(DAT_8032ec90 + 0x47));
          if (*(char *)(DAT_8032ec90 + 0x47) != '\0') {
            *(char *)&gObject->m_lastBgGroup = *(char *)(DAT_8032ec90 + 0x47);
          }
          GetHitFaceNormal__7CMapObjFP3Vec(MapMng._141944_4_,&(gObject->m_hitNormal).y);
        }
        iVar5 = CalcHitSlide__7CMapObjFP3Vecf((CMapObj *)MapMng._141944_4_,&local_110);
        if (iVar5 != 0) {
          local_e0 = gObject->m_capsuleHalfHeight;
          local_d4 = FLOAT_8033033c;
          local_d8 = FLOAT_8033033c;
          local_dc = FLOAT_8033033c;
          local_c8 = FLOAT_80330340;
          local_cc = FLOAT_80330340;
          local_d0 = FLOAT_80330340;
          local_104 = local_11c.x;
          local_100 = local_11c.y;
          local_fc = local_11c.z;
          local_ec = local_110.x;
          local_e8 = local_110.y;
          local_e4 = local_110.z;
          iVar5 = CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl
                            (&MapMng,&local_104,&local_110,(gObject->m_moveVec).x);
          if (iVar5 != 0) {
            CalcHitPosition__7CMapObjFP3Vec(MapMng._141944_4_,&VStack_128);
            PSVECSubtract(&VStack_128,&local_11c,&local_110);
          }
        }
        local_11c.y = local_11c.y - gObject->m_capsuleHalfHeight;
        PSVECAdd(&local_11c,&local_110,&local_11c);
        fVar3 = FLOAT_80330350;
        if ((gObject->m_jumpLandingDampening <= FLOAT_80330350) ||
           (fVar1 = (gObject->m_groundHitOffset).y, FLOAT_8033041c <= fVar1)) {
          (gObject->m_groundHitOffset).y = local_11c.y - (gObject->m_worldPosition).y;
          (gObject->m_groundHitOffset).x = local_11c.x - (gObject->m_worldPosition).x;
          (gObject->m_groundHitOffset).z = local_11c.z - (gObject->m_worldPosition).z;
        }
        else {
          fVar2 = fVar1;
          if (fVar1 < FLOAT_80330420) {
            fVar2 = FLOAT_80330420;
          }
          if (fVar1 < FLOAT_80330420) {
            fVar1 = FLOAT_80330420;
          }
          (gObject->m_worldPosition).y = local_11c.y;
          (gObject->m_groundHitOffset).y = fVar3;
          (gObject->m_groundHitOffset).x = local_11c.x - (gObject->m_worldPosition).x;
          (gObject->m_groundHitOffset).z = local_11c.z - (gObject->m_worldPosition).z;
          gObject->m_gravityY =
               gObject->m_jumpLandingDampening *
               -((fVar1 - (fVar2 - local_110.y)) + (fVar2 - local_110.y));
          if (((gObject->m_displayFlags & 1) != 0) &&
             ((*(byte *)&gObject->m_weaponNodeFlags & 1) == 0)) {
            PlaySe3D__6CSoundFiP3Vecffi
                      ((double)(FLOAT_80330424 +
                               (FLOAT_80330424 * gObject->m_gravityY) / FLOAT_80330360),
                       (double)(FLOAT_80330410 +
                               (FLOAT_80330410 * gObject->m_gravityY) / FLOAT_80330360),&Sound,0x26,
                       &gObject->m_worldPosition,0);
          }
        }
      }
    }
  }
  return;
}

