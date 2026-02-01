// Function: update__8CGObjectFv
// Entry: 8007e698
// Size: 6216 bytes

/* WARNING: Removing unreachable block (ram,0x8007fec4) */
/* WARNING: Removing unreachable block (ram,0x8007febc) */
/* WARNING: Removing unreachable block (ram,0x8007feb4) */
/* WARNING: Removing unreachable block (ram,0x8007feac) */
/* WARNING: Removing unreachable block (ram,0x8007fea4) */
/* WARNING: Removing unreachable block (ram,0x8007fe9c) */
/* WARNING: Removing unreachable block (ram,0x8007e6d0) */
/* WARNING: Removing unreachable block (ram,0x8007e6c8) */
/* WARNING: Removing unreachable block (ram,0x8007e6c0) */
/* WARNING: Removing unreachable block (ram,0x8007e6b8) */
/* WARNING: Removing unreachable block (ram,0x8007e6b0) */
/* WARNING: Removing unreachable block (ram,0x8007e6a8) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void update__8CGObjectFv(CGObject *gObject)

{
  byte bVar1;
  uint8_t uVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  uint uVar7;
  uint uVar8;
  CCharaPcsCHandle *pCVar9;
  CModel *pCVar10;
  float fVar11;
  Vec *pVVar12;
  float *pfVar13;
  CAnim *pCVar14;
  uint uVar15;
  int iVar16;
  int iVar17;
  CGObject *pCVar18;
  char cVar19;
  CRef *pCVar20;
  CRef *pCVar21;
  bool bVar22;
  double dVar23;
  double dVar24;
  double dVar25;
  double dVar26;
  double dVar27;
  double dVar28;
  int local_2a4;
  uint local_2a0;
  CVector local_29c;
  Vec VStack_290;
  Vec VStack_284;
  CVector CStack_278;
  CVector CStack_26c;
  CVector CStack_260;
  CVector CStack_254;
  CVector CStack_248;
  CVector CStack_23c;
  CVector CStack_230;
  CVector CStack_224;
  CVector CStack_218;
  Vec local_20c;
  Vec local_200;
  Vec local_1f4;
  Vec local_1e8;
  Vec VStack_1dc;
  Vec VStack_1d0;
  Vec VStack_1c4;
  Vec VStack_1b8;
  Vec local_1ac;
  Mtx MStack_1a0;
  Mtx MStack_170;
  Vec local_140;
  float local_134;
  float local_130;
  float local_12c;
  float local_128;
  float local_124;
  float local_120;
  Mtx MStack_11c;
  Mtx MStack_ec;
  Mtx MStack_bc;
  undefined4 local_88;
  float fStack_84;
  undefined4 local_80;
  uint uStack_7c;
  
  bVar22 = false;
  iVar17 = (char)gObject->m_dispItemTimer + -1;
  uVar7 = MiniGamePcs._25732_4_ & 0x8000;
  gObject->m_dispItemTimer = (byte)iVar17 & ~(byte)(iVar17 >> 0x1f);
  uVar7 = countLeadingZeros(uVar7);
  uVar7 = uVar7 >> 5 & 0xff;
  if ((gObject->m_charaModelHandle != (CCharaPcsCHandle *)0x0) &&
     (gObject->m_charaModelHandle->m_model != (CModel *)0x0)) {
    bVar22 = true;
  }
  if (bVar22) {
    gObject->m_attackColliders[0].m_localEnd.y = gObject->m_attackColliders[0].m_worldPosition.y;
    gObject->m_attackColliders[0].m_localEnd.z = gObject->m_attackColliders[0].m_worldPosition.z;
    gObject->m_attackColliders[0].m_worldPosition.x = gObject->m_attackColliders[0].m_radius;
    gObject->m_attackColliders[1].m_localEnd.y = gObject->m_attackColliders[1].m_worldPosition.y;
    gObject->m_attackColliders[1].m_localEnd.z = gObject->m_attackColliders[1].m_worldPosition.z;
    gObject->m_attackColliders[1].m_worldPosition.x = gObject->m_attackColliders[1].m_radius;
    gObject->m_attackColliders[2].m_localEnd.y = gObject->m_attackColliders[2].m_worldPosition.y;
    gObject->m_attackColliders[2].m_localEnd.z = gObject->m_attackColliders[2].m_worldPosition.z;
    gObject->m_attackColliders[2].m_worldPosition.x = gObject->m_attackColliders[2].m_radius;
    gObject->m_attackColliders[3].m_localEnd.y = gObject->m_attackColliders[3].m_worldPosition.y;
    gObject->m_attackColliders[3].m_localEnd.z = gObject->m_attackColliders[3].m_worldPosition.z;
    gObject->m_attackColliders[3].m_worldPosition.x = gObject->m_attackColliders[3].m_radius;
    gObject->m_attackColliders[4].m_localEnd.y = gObject->m_attackColliders[4].m_worldPosition.y;
    gObject->m_attackColliders[4].m_localEnd.z = gObject->m_attackColliders[4].m_worldPosition.z;
    gObject->m_attackColliders[4].m_worldPosition.x = gObject->m_attackColliders[4].m_radius;
    gObject->m_attackColliders[5].m_localEnd.y = gObject->m_attackColliders[5].m_worldPosition.y;
    gObject->m_attackColliders[5].m_localEnd.z = gObject->m_attackColliders[5].m_worldPosition.z;
    gObject->m_attackColliders[5].m_worldPosition.x = gObject->m_attackColliders[5].m_radius;
    gObject->m_attackColliders[6].m_localEnd.y = gObject->m_attackColliders[6].m_worldPosition.y;
    gObject->m_attackColliders[6].m_localEnd.z = gObject->m_attackColliders[6].m_worldPosition.z;
    gObject->m_attackColliders[6].m_worldPosition.x = gObject->m_attackColliders[6].m_radius;
    gObject->m_attackColliders[7].m_localEnd.y = gObject->m_attackColliders[7].m_worldPosition.y;
    gObject->m_attackColliders[7].m_localEnd.z = gObject->m_attackColliders[7].m_worldPosition.z;
    gObject->m_attackColliders[7].m_worldPosition.x = gObject->m_attackColliders[7].m_radius;
  }
  pCVar9 = gObject->m_charaModelHandle;
  bVar22 = false;
  if ((pCVar9 != (CCharaPcsCHandle *)0x0) && (pCVar9->m_model != (CModel *)0x0)) {
    bVar22 = true;
  }
  if ((bVar22) && ((gObject->m_displayFlags & 2) != 0)) {
    cVar19 = gObject->m_currentAnimSlot;
    uVar15 = (uint)(char)((int)((uint)*(byte *)&gObject->m_shieldNodeFlags << 0x1c) >> 0x1f);
    uVar8 = countLeadingZeros((int)(char)((int)((uint)*(byte *)&gObject->m_shieldNodeFlags << 0x1e)
                                         >> 0x1f));
    if (cVar19 == -1) {
      iVar17 = -1;
      iVar16 = -1;
      cVar19 = gObject->m_animSlotSel;
    }
    else {
      iVar17 = (int)gObject->m_collisionPushTimer;
      iVar16 = (int)gObject->m_animExtraIndex;
    }
    iVar17 = SetAnim__Q29CCharaPcs7CHandleFiiiii
                       (pCVar9,(int)cVar19,iVar16,iVar17,-(uVar8 >> 5 & 1),
                        (-uVar15 | uVar15) >> 0x1f);
    if ((iVar17 != 0) && (gObject->m_currentAnimSlot != -1)) {
      fVar3 = FLOAT_80330350;
      if (*(float *)gObject->m_lastBgAttr < FLOAT_80330350) {
        pCVar10 = gObject->m_charaModelHandle->m_model;
        fVar3 = pCVar10->m_animEnd - pCVar10->m_animStart;
      }
      gObject->m_turnSpeed = fVar3;
      SetFrame__Q26CChara6CModelFf(gObject->m_turnSpeed,gObject->m_charaModelHandle->m_model);
    }
    *(byte *)&gObject->m_shieldNodeFlags = *(byte *)&gObject->m_shieldNodeFlags & 0xf7;
  }
  PSVECAdd(&gObject->m_worldPosition,&gObject->m_groundHitOffset,&gObject->m_worldPosition);
  dVar24 = (double)DstRot__5CMathFff((double)gObject->m_rotTargetY,(double)gObject->m_rotBaseY,&Math
                                    );
  if ((gObject->m_animSlotSel == -1) ||
     (-1 < (int)((uint)*(byte *)&gObject->m_shieldNodeFlags << 0x19 |
                (uint)(*(byte *)&gObject->m_shieldNodeFlags >> 7)))) {
    fVar3 = (gObject->m_hitNormal).x;
  }
  else {
    dVar27 = ABS((double)gObject->m_turnBaseSpeed);
    dVar23 = -dVar27;
    if ((dVar23 <= dVar24) && (dVar23 = dVar24, dVar27 < dVar24)) {
      dVar23 = dVar27;
    }
    dVar24 = (double)(float)dVar23;
    fVar3 = FLOAT_80330338;
  }
  gObject->m_rotBaseY = (float)(dVar24 * (double)fVar3 + (double)gObject->m_rotBaseY);
  if (Game.game.m_currentMapId == 0x21) {
    dVar24 = (double)atan2((double)(gObject->m_worldPosition).x,(double)(gObject->m_worldPosition).z
                          );
    PSMTXRotRad((float)dVar24,&MStack_bc,0x79);
    local_1ac.x = DAT_801d9b88;
    local_1ac.y = DAT_801d9b8c;
    local_1ac.z = DAT_801d9b90;
    PSVECNormalize(&gObject->m_worldPosition,&VStack_1b8);
    PSVECDotProduct(&local_1ac,&VStack_1b8);
    dVar24 = (double)acos();
    PSMTXRotRad((float)dVar24,&MStack_11c,0x78);
    PSMTXConcat(&MStack_bc,&MStack_11c,&MStack_bc);
    PSMTXRotRad(gObject->m_rotBaseY,&MStack_11c,0x79);
    PSMTXConcat(&MStack_bc,&MStack_11c,&MStack_bc);
    PSMTXScaleApply(gObject->m_rotationX,gObject->m_rotationY,gObject->m_rotationZ,&MStack_bc,
                    &MStack_bc);
    MStack_bc.value[0][3] = (gObject->m_worldPosition).x;
    MStack_bc.value[1][3] = (gObject->m_worldPosition).y;
    MStack_bc.value[2][3] = (gObject->m_worldPosition).z;
  }
  else {
    local_12c = FLOAT_80330350;
    local_130 = FLOAT_80330350;
    local_134 = FLOAT_80330350;
    local_120 = FLOAT_80330338;
    local_124 = FLOAT_80330338;
    local_128 = FLOAT_80330338;
    local_140.x = (gObject->m_worldPosition).x;
    local_140.y = (gObject->m_worldPosition).y;
    local_140.z = (gObject->m_worldPosition).z;
    PSVECAdd(&local_140,&gObject->m_extraMoveVec,&local_140);
    fVar3 = FLOAT_803303a4;
    local_134 = gObject->m_rotBaseX;
    local_130 = gObject->m_rotBaseY;
    local_12c = gObject->m_rotBaseZ;
    local_128 = gObject->m_rotationX;
    local_124 = gObject->m_rotationY;
    local_120 = gObject->m_rotationZ;
    fVar11 = gObject->m_worldParamA;
    if ((((fVar11 == 4.48416e-44) || (fVar11 == 2.66247e-44)) || ((int)fVar11 - 0x15U < 3)) ||
       (fVar11 == 2.8026e-44)) {
      fVar4 = FLOAT_803303a0;
      if (fVar11 == 4.48416e-44) {
        fVar4 = FLOAT_8033039c;
      }
      (gObject->m_radiusCtrl).z =
           (gObject->m_radiusCtrl).z + FLOAT_80330398 * (gObject->m_radiusCtrl).y + fVar4;
      (gObject->m_radiusCtrl).y = (gObject->m_radiusCtrl).y * fVar3;
      local_130 = local_130 + (gObject->m_radiusCtrl).z;
    }
    else if ((fVar11 == 5.04467e-44) || (gObject->m_worldParamB == 4.1058e-43)) {
      local_130 = FLOAT_803303a8 - (float)CameraPcs._248_4_;
      dVar24 = (double)cos((double)(FLOAT_80330368 * (gObject->m_radiusCtrl).y));
      local_130 = FLOAT_80330368 * (float)dVar24 + local_130;
      dVar24 = (double)sin((double)(gObject->m_radiusCtrl).y);
      local_140.y = local_140.y + FLOAT_80330338 + (float)dVar24;
      (gObject->m_radiusCtrl).y = (gObject->m_radiusCtrl).y + FLOAT_803303ac;
    }
    SRTToMatrix__5CMathFPA4_fP3SRT(&Math,&MStack_bc,&local_140);
    fVar3 = FLOAT_803303cc;
    bVar1 = gObject->m_stateFlags0;
    if ((int)((uint)bVar1 << 0x1b | (uint)(bVar1 >> 5)) < 0) {
      fVar3 = (gObject->m_groundHitOffset).x;
      if ((fVar3 == FLOAT_80330350) && ((gObject->m_groundHitOffset).z == FLOAT_80330350)) {
        PSMTXQuat(&MStack_1a0,&gObject->m_bgCollisionQuat);
      }
      else {
        fVar11 = (gObject->m_groundHitOffset).z;
        fVar3 = fVar3 * fVar3 + fVar11 * fVar11;
        dVar24 = (double)fVar3;
        if (dVar24 <= (double)FLOAT_80330350) {
          if (DOUBLE_803303c0 <= dVar24) {
            uVar8 = (uint)fVar3 & 0x7f800000;
            if (uVar8 == 0x7f800000) {
              if (((uint)fVar3 & 0x7fffff) == 0) {
                iVar17 = 2;
              }
              else {
                iVar17 = 1;
              }
            }
            else if ((uVar8 < 0x7f800000) && (uVar8 == 0)) {
              if (((uint)fVar3 & 0x7fffff) == 0) {
                iVar17 = 3;
              }
              else {
                iVar17 = 5;
              }
            }
            else {
              iVar17 = 4;
            }
            if (iVar17 == 1) {
              dVar24 = (double)DAT_8032ec20;
            }
          }
          else {
            dVar24 = (double)DAT_8032ec20;
          }
        }
        else {
          dVar23 = 1.0 / SQRT(dVar24);
          dVar23 = DOUBLE_803303b0 * dVar23 * -(dVar24 * dVar23 * dVar23 - DOUBLE_803303b8);
          dVar23 = DOUBLE_803303b0 * dVar23 * -(dVar24 * dVar23 * dVar23 - DOUBLE_803303b8);
          dVar24 = (double)(float)(dVar24 * DOUBLE_803303b0 * dVar23 *
                                            -(dVar24 * dVar23 * dVar23 - DOUBLE_803303b8));
        }
        pVVar12 = (Vec *)__ct__7CVectorFfff(FLOAT_80330350,FLOAT_80330338,FLOAT_80330350,&CStack_218
                                           );
        PSVECCrossProduct(&gObject->m_groundHitOffset,pVVar12,&VStack_1c4);
        PSMTXRotAxisRad((float)(-dVar24 / (double)FLOAT_803303c8),&MStack_170,&VStack_1c4);
        PSMTXQuat(&MStack_1a0,&gObject->m_bgCollisionQuat);
        PSMTXConcat(&MStack_170,&MStack_1a0,&MStack_1a0);
        C_QUATMtx(&gObject->m_bgCollisionQuat,&MStack_1a0);
      }
      dVar24 = (double)MStack_bc.value[0][3];
      dVar23 = (double)MStack_bc.value[1][3];
      dVar27 = (double)MStack_bc.value[2][3];
      pfVar13 = (float *)__ct__7CVectorFfff(FLOAT_80330350,FLOAT_80330350,FLOAT_80330350,&CStack_224
                                           );
      MStack_bc.value[0][3] = *pfVar13;
      iVar17 = __ct__7CVectorFfff(FLOAT_80330350,FLOAT_80330350,FLOAT_80330350,&CStack_230);
      MStack_bc.value[1][3] = *(float *)(iVar17 + 4);
      iVar17 = __ct__7CVectorFfff(FLOAT_80330350,FLOAT_80330350,FLOAT_80330350,&CStack_23c);
      MStack_bc.value[2][3] = *(float *)(iVar17 + 8);
      PSMTXConcat(&MStack_1a0,&MStack_bc,&MStack_bc);
      MStack_bc.value[0][3] = (float)dVar24;
      MStack_bc.value[1][3] = (float)dVar23;
      MStack_bc.value[2][3] = (float)dVar27;
    }
    else if (((gObject->m_objectFlags & 0x90) != 0) && ((int)((uint)bVar1 << 0x18) < 0)) {
      fVar11 = (gObject->m_groundHitOffset).x;
      if ((fVar11 != FLOAT_80330350) || ((gObject->m_groundHitOffset).z != FLOAT_80330350)) {
        (gObject->m_radiusCtrl).y = FLOAT_803303cc * fVar11 + (gObject->m_radiusCtrl).y;
        (gObject->m_radiusCtrlVel).x =
             fVar3 * (gObject->m_groundHitOffset).z + (gObject->m_radiusCtrlVel).x;
      }
      fVar11 = FLOAT_80330368;
      fVar3 = gObject->m_groundFriction;
      (gObject->m_radiusCtrlVel).y =
           FLOAT_80330368 * ((gObject->m_radiusCtrl).y - (gObject->m_radiusCtrlVel).y) +
           (gObject->m_radiusCtrlVel).y;
      gObject->m_groundFriction =
           fVar11 * ((gObject->m_radiusCtrlVel).x - fVar3) + gObject->m_groundFriction;
      PSVECNormalize((Vec *)&(gObject->m_radiusCtrlVel).y,&VStack_1d0);
      pVVar12 = (Vec *)__ct__7CVectorFfff(FLOAT_80330350,FLOAT_80330338,FLOAT_80330350,&CStack_248);
      dVar24 = (double)PSVECDotProduct(&VStack_1d0,pVVar12);
      if (dVar24 < (double)FLOAT_803303d0) {
        dVar23 = (double)acos();
        dVar23 = -(double)(float)dVar23;
        pVVar12 = (Vec *)__ct__7CVectorFfff(FLOAT_80330350,FLOAT_80330338,FLOAT_80330350,&CStack_254
                                           );
        PSVECCrossProduct(&VStack_1d0,pVVar12,&VStack_1dc);
        PSMTXRotAxisRad((float)dVar23,&MStack_170,&VStack_1dc);
        dVar27 = (double)MStack_bc.value[0][3];
        dVar25 = (double)MStack_bc.value[1][3];
        dVar28 = (double)MStack_bc.value[2][3];
        pfVar13 = (float *)__ct__7CVectorFfff(FLOAT_80330350,FLOAT_80330350,FLOAT_80330350,
                                              &CStack_260);
        MStack_bc.value[0][3] = *pfVar13;
        iVar17 = __ct__7CVectorFfff(FLOAT_80330350,FLOAT_80330350,FLOAT_80330350,&CStack_26c);
        MStack_bc.value[1][3] = *(float *)(iVar17 + 4);
        iVar17 = __ct__7CVectorFfff(FLOAT_80330350,FLOAT_80330350,FLOAT_80330350,&CStack_278);
        MStack_bc.value[2][3] = *(float *)(iVar17 + 8);
        PSMTXConcat(&MStack_170,&MStack_bc,&MStack_bc);
        dVar23 = (double)tan(dVar23);
        MStack_bc.value[0][3] = (float)dVar27;
        MStack_bc.value[2][3] = (float)dVar28;
        MStack_bc.value[1][3] = (float)(dVar25 - (double)(FLOAT_803303d4 * (float)dVar23));
      }
      dVar27 = (double)(gObject->m_radiusCtrl).y;
      dVar25 = (double)(gObject->m_radiusCtrlVel).x;
      dVar23 = (double)FLOAT_80330338;
      if (dVar24 < (double)FLOAT_80330338) {
        dVar23 = dVar24;
      }
      if (dVar23 < (double)FLOAT_80330350) {
        dVar23 = (double)FLOAT_80330350;
      }
      dVar24 = (double)sin(dVar23);
      dVar28 = (double)(float)dVar24;
      dVar24 = (double)cos(dVar23);
      fVar3 = FLOAT_803303d8;
      (gObject->m_radiusCtrl).y =
           (float)((double)(float)dVar24 * dVar27 - (double)(float)(dVar28 * dVar25));
      (gObject->m_radiusCtrlVel).x =
           (float)(dVar28 * dVar27 + (double)(float)((double)(float)dVar24 * dVar25));
      (gObject->m_radiusCtrl).y = (gObject->m_radiusCtrl).y * fVar3;
      (gObject->m_radiusCtrlVel).x = (gObject->m_radiusCtrlVel).x * fVar3;
    }
  }
  if ((*(byte *)&gObject->m_weaponNodeFlags & 1) != 0) {
    PSMTXCopy(&gObject->m_attachOwner->m_charaModelHandle->m_model->m_nodes[gObject->m_attachNode].
               m_mtx,&MStack_bc);
    if ((gObject->m_worldParamA == 5.04467e-44) || (gObject->m_worldParamB == 4.1058e-43)) {
      PSMTXRotRad(-gObject->m_attachOwner->m_rotBaseY,&MStack_ec,0x79);
      PSMTXConcat(&MStack_bc,&MStack_ec,&MStack_bc);
    }
    if ((gObject->m_worldParamA != 5.04467e-44) || (gObject->m_worldParamB == 4.1058e-43)) {
      PSMTXRotRad(gObject->m_rotBaseY,&MStack_ec,0x79);
      PSMTXConcat(&MStack_bc,&MStack_ec,&MStack_bc);
    }
    pCVar18 = gObject->m_attachOwner;
    local_1e8.x = (pCVar18->m_worldPosition).x;
    local_1e8.y = (pCVar18->m_worldPosition).y;
    local_1e8.z = (pCVar18->m_worldPosition).z;
    PSVECAdd(&local_1e8,&pCVar18->m_extraMoveVec,&local_1e8);
    PSMTXTransApply(local_1e8.x,local_1e8.y,local_1e8.z,&MStack_bc,&MStack_bc);
    local_1f4.x = MStack_bc.value[0][3];
    local_1f4.y = MStack_bc.value[1][3];
    local_1f4.z = MStack_bc.value[2][3];
    if ((gObject->m_moveMode == '\0') || (gObject->m_moveModePrevious == '\0')) {
      (gObject->m_worldPosition).x = MStack_bc.value[0][3];
      (gObject->m_worldPosition).y = MStack_bc.value[1][3];
      (gObject->m_worldPosition).z = MStack_bc.value[2][3];
    }
    else {
      fStack_84 = -(float)(int)(char)gObject->m_moveMode;
      uStack_7c = (int)(char)gObject->m_moveModePrevious ^ 0x80000000;
      local_88 = 0x43300000;
      local_80 = 0x43300000;
      dVar24 = (double)((float)((double)CONCAT44(0x43300000,fStack_84) - DOUBLE_80330348) /
                       (float)((double)CONCAT44(0x43300000,uStack_7c) - DOUBLE_80330348));
      PSVECScale((float)((double)FLOAT_80330338 - dVar24),&local_1f4,&VStack_290);
      PSVECScale((float)dVar24,&gObject->m_worldPosition,&VStack_284);
      PSVECAdd(&VStack_290,&VStack_284,&gObject->m_worldPosition);
      gObject->m_moveMode = gObject->m_moveMode + 0xff;
    }
    MStack_bc.value[0][3] = (gObject->m_worldPosition).x;
    MStack_bc.value[1][3] = (gObject->m_worldPosition).y;
    MStack_bc.value[2][3] = (gObject->m_worldPosition).z;
  }
  bVar22 = false;
  if ((gObject->m_charaModelHandle != (CCharaPcsCHandle *)0x0) &&
     (gObject->m_charaModelHandle->m_model != (CModel *)0x0)) {
    bVar22 = true;
  }
  if (bVar22) {
    fVar3 = gObject->m_bgAttrValue - gObject->m_animBlend;
    fVar11 = FLOAT_803303dc;
    if ((FLOAT_803303dc <= fVar3) && (fVar11 = fVar3, FLOAT_803303a0 < fVar3)) {
      fVar11 = FLOAT_803303a0;
    }
    gObject->m_animBlend = gObject->m_animBlend + fVar11;
    dVar23 = (double)gObject->m_lookAtAccumYaw;
    dVar24 = (double)gObject->m_lookAtAccumPitch;
    if (gObject->m_lookAtTarget != (CGObject *)0x0) {
      PSVECSubtract(&gObject->m_worldPosition,&gObject->m_lookAtTarget->m_worldPosition,&local_200);
      if (gObject->m_lookAtTargetNodeIndex == -1) {
        fVar3 = gObject->m_lookAtTarget->unk_0x184;
      }
      else {
        fVar3 = gObject->m_lookAtTarget->m_charaModelHandle->m_model->m_nodes
                [gObject->m_lookAtTargetNodeIndex].m_mtx.value[1][3];
      }
      local_200.y = local_200.y + (gObject->unk_0x184 - fVar3);
      dVar27 = (double)PSVECMag(&local_200);
      if ((double)FLOAT_80330350 != dVar27) {
        dVar25 = (double)atan2(-(double)local_200.x,-(double)local_200.z);
        dVar25 = (double)DstRot__5CMathFff((double)(float)dVar25,(double)gObject->m_rotBaseY,&Math);
        if (ABS(dVar25) < DOUBLE_803303e0) {
          dVar27 = (double)atan2((double)local_200.y,dVar27);
          if (ABS((double)(float)dVar27) < DOUBLE_803303e8) {
            dVar23 = (double)(float)(dVar23 + dVar25);
            dVar24 = (double)(float)(dVar24 + (double)(float)dVar27);
          }
        }
      }
    }
    fVar11 = FLOAT_8033036c;
    uStack_7c = (uint)(byte)gObject->field_0x56;
    pCVar10 = gObject->m_charaModelHandle->m_model;
    local_80 = 0x43300000;
    dVar27 = (double)(FLOAT_803303f0 *
                     (float)((double)CONCAT44(0x43300000,uStack_7c) - DOUBLE_80330408));
    pCVar10->m_chestAmp =
         (float)(dVar27 * (double)(float)(dVar23 - (double)pCVar10->m_chestAmp) +
                (double)pCVar10->m_chestAmp);
    pCVar10->m_chestTilt =
         (float)(dVar27 * (double)(float)(dVar24 - (double)pCVar10->m_chestTilt) +
                (double)pCVar10->m_chestTilt);
    pCVar10 = gObject->m_charaModelHandle->m_model;
    fVar3 = pCVar10->m_twistAngle;
    pCVar10->m_twistAngle = fVar11 * (*(float *)gObject->m_worldMode - fVar3) + fVar3;
    SetMatrix__Q26CChara6CModelFPA4_f(gObject->m_charaModelHandle->m_model,&MStack_bc);
    Calc__5CWindFP3VecPC3Veci(&Wind,&local_20c,&gObject->m_worldPosition,0);
    dVar24 = (double)RandF__5CMathFv(&Math);
    local_20c.x = -(float)((double)(gObject->m_groundHitOffset).x * dVar24 - (double)local_20c.x);
    dVar24 = (double)RandF__5CMathFv(&Math);
    local_20c.z = -(float)((double)(gObject->m_groundHitOffset).z * dVar24 - (double)local_20c.z);
    pCVar10 = gObject->m_charaModelHandle->m_model;
    __ct__7CVectorFRC3Vec(&local_29c,&local_20c);
    (pCVar10->m_unkVec_0xC4).x = local_29c.x;
    (pCVar10->m_unkVec_0xC4).y = local_29c.y;
    (pCVar10->m_unkVec_0xC4).z = local_29c.z;
    boundCheck__8CGObjectFv(gObject);
    if (Game.game.m_currentMapId == 0x21) {
      if (gObject->m_screenDepth <= FLOAT_803303f4) {
        dVar24 = (double)FLOAT_80330338;
      }
      else {
        dVar24 = (double)FLOAT_80330350;
      }
    }
    else if (gObject->m_screenDepth <= FLOAT_803303f8) {
      dVar24 = (double)FLOAT_80330338;
    }
    else {
      dVar24 = (double)FLOAT_80330350;
    }
    dVar23 = (double)(**(code **)((int)(gObject->base_object).object.m_vtable + 0x30))(gObject);
    fVar5 = FLOAT_80330350;
    fVar4 = gObject->m_bgDownDist;
    fVar11 = (float)((double)gObject->m_stepSlopeLimit * dVar23);
    fVar6 = -fVar4;
    fVar3 = (float)((double)fVar11 * dVar24 - (double)gObject->m_lookAtTimer);
    if ((fVar6 <= fVar3) && (fVar6 = fVar3, fVar4 < fVar3)) {
      fVar6 = fVar4;
    }
    gObject->m_lookAtTimer = gObject->m_lookAtTimer + fVar6;
    fVar3 = gObject->m_lookAtTimer;
    if ((fVar5 <= fVar3) && (fVar5 = fVar3, FLOAT_80330338 < fVar3)) {
      fVar5 = FLOAT_80330338;
    }
    gObject->m_lookAtTimer = fVar5;
    fVar3 = gObject->m_worldParam - FLOAT_803303a0;
    if (fVar3 < FLOAT_80330350) {
      fVar3 = FLOAT_80330350;
    }
    gObject->m_worldParam = fVar3;
    if ((gObject->m_displayFlags & 0x1000) != 0) {
      gObject->m_lookAtTimer = fVar11;
    }
    if (FLOAT_80330350 == gObject->m_lookAtTimer) {
      *(byte *)&gObject->m_weaponNodeFlags = *(byte *)&gObject->m_weaponNodeFlags & 0xdf;
    }
    bVar1 = *(byte *)&gObject->m_weaponNodeFlags;
    *(byte *)&gObject->m_weaponNodeFlags =
         (byte)(((int)((uint)bVar1 << 0x19 | (uint)(bVar1 >> 7) |
                      (uint)bVar1 << 0x1a | (uint)(bVar1 >> 6)) >> 0x1f) << 6) & 0x40 | bVar1 & 0xbf
    ;
    if ((gObject->m_displayFlags & 1) != 0) {
      if (((((int)((uint)*(byte *)&gObject->m_weaponNodeFlags << 0x1a |
                  (uint)(*(byte *)&gObject->m_weaponNodeFlags >> 6)) < 0) && (uVar7 == 0)) ||
          (gObject->m_currentAnimSlot != -1)) ||
         (gObject->m_animSlotSel != *(char *)((int)&gObject->m_shieldNodeFlags + 1))) {
        CalcMatrix__Q26CChara6CModelFv(gObject->m_charaModelHandle->m_model);
      }
      if (((int)((uint)*(byte *)&gObject->m_weaponNodeFlags << 0x1a |
                (uint)(*(byte *)&gObject->m_weaponNodeFlags >> 6)) < 0) && (uVar7 == 0)) {
        CalcSkin__Q26CChara6CModelFv(gObject->m_charaModelHandle->m_model);
      }
      gObject->m_charaModelHandle->m_model->m_lightAlpha = gObject->m_lookAtTimer;
      pCVar10 = gObject->m_charaModelHandle->m_model;
      pCVar10->m_flagsA0 =
           (byte)(((int)((uint)*(byte *)&gObject->m_weaponNodeFlags << 0x1a |
                        (uint)(*(byte *)&gObject->m_weaponNodeFlags >> 6)) >> 0x1f) << 5) & 0x20 |
           pCVar10->m_flagsA0 & 0xdf;
      pCVar10 = gObject->m_charaModelHandle->m_model;
      pCVar10->m_flagsA0 =
           (byte)((int)(char)((byte)(gObject->m_displayFlags >> 5) & 1) << 7) |
           pCVar10->m_flagsA0 & 0x7f;
    }
    CalcFurColor__Q26CChara6CModelFv(gObject->m_charaModelHandle->m_model);
    if ((gObject->m_displayFlags & 2) != 0) {
      if ((gObject->m_animSlotSel == -1) ||
         (-1 < (int)((uint)*(byte *)&gObject->m_shieldNodeFlags << 0x19 |
                    (uint)(*(byte *)&gObject->m_shieldNodeFlags >> 7)))) {
        fVar3 = *(float *)gObject->m_lastBgAttr;
        iVar17 = gObject->m_charaModelHandle->m_currentAnimIndex;
        fVar11 = fVar3;
        if ((-1 < iVar17) &&
           ((((uint)gObject->m_charaModelHandle->m_animSlot[iVar17][0xe].vtable & 4) != 0 &&
            (fVar11 = FLOAT_80330338, fVar3 < FLOAT_80330350)))) {
          fVar11 = FLOAT_80330390;
        }
        fVar3 = gObject->m_turnSpeed + fVar11 * FLOAT_803303fc;
      }
      else {
        pCVar14 = gObject->m_charaModelHandle->m_model->m_anim;
        if (pCVar14 == (CAnim *)0x0) {
          fVar3 = FLOAT_80330338;
          if (1 < (uint)System.m_execParam) {
            Printf__7CSystemFPce(&System,&DAT_801d9bdc);
            fVar3 = FLOAT_80330338;
          }
        }
        else {
          uStack_7c = (uint)*(ushort *)(pCVar14 + 0x10);
          fStack_84 = gObject->m_attackColliders[0].m_localStart.x;
          local_80 = 0x43300000;
          local_88 = 0x43300000;
          fVar3 = (float)((double)CONCAT44(0x43300000,uStack_7c) - DOUBLE_80330408) /
                  (float)((double)CONCAT44(0x43300000,fStack_84) - DOUBLE_80330408);
        }
        fVar3 = gObject->m_turnSpeed + fVar3;
      }
      dVar23 = (double)fVar3;
      pCVar10 = gObject->m_charaModelHandle->m_model;
      dVar24 = (double)pCVar10->m_time;
      SetFrame__Q26CChara6CModelFf(fVar3,pCVar10);
      pCVar9 = gObject->m_charaModelHandle;
      if (((-1 < pCVar9->m_currentAnimIndex) &&
          (pCVar21 = pCVar9->m_animSlot[pCVar9->m_currentAnimIndex], pCVar21 != (CRef *)0x0)) &&
         (*(short *)&pCVar21[5].refCount != 0)) {
        dVar27 = (double)(FLOAT_80330338 +
                         (pCVar9->m_model->m_animEnd - pCVar9->m_model->m_animStart));
        if ((double)FLOAT_80330350 <= dVar24) {
          dVar25 = (double)fmod(dVar24,dVar27);
          fVar3 = (float)dVar25;
        }
        else {
          dVar25 = (double)fmod(-dVar24,dVar27);
          fVar3 = (float)(dVar27 - (double)FLOAT_80330338) - (float)dVar25;
        }
        dVar28 = (double)fVar3;
        dVar25 = dVar28;
        if ((double)FLOAT_80330350 <= dVar23) {
          dVar26 = (double)fmod(dVar23,dVar27);
          fVar3 = (float)dVar26;
        }
        else {
          dVar26 = (double)fmod(-dVar23,dVar27);
          fVar3 = (float)(dVar27 - (double)FLOAT_80330338) - (float)dVar26;
        }
        dVar26 = (double)fVar3;
        if (dVar23 < dVar24) {
          dVar28 = (double)(float)((double)(float)(dVar27 - (double)FLOAT_80330338) - dVar25);
          dVar26 = (double)(float)((double)(float)(dVar27 - (double)FLOAT_80330338) - dVar26);
        }
        pCVar20 = pCVar21;
        dVar24 = DOUBLE_80330408;
        for (iVar17 = 0; iVar17 < (int)(uint)*(ushort *)&pCVar21[5].refCount; iVar17 = iVar17 + 1) {
          uStack_7c = (uint)*(ushort *)&pCVar20[6].vtable;
          local_80 = 0x43300000;
          dVar27 = (double)((float)((double)CONCAT44(0x43300000,uStack_7c) - dVar24) +
                           gObject->m_charaModelHandle->m_model->m_animStart);
          if ((dVar28 < dVar27) && ((dVar27 <= dVar26 || (dVar26 < dVar28)))) {
            local_2a4 = (int)gObject->m_animSlotSel;
            local_2a0 = (uint)*(ushort *)((int)&pCVar20[5].refCount + 2);
            SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack
                      (&CFlat,gObject,2,9,2,&local_2a4,(CStack *)0x0);
            (**(code **)((int)(gObject->base_object).object.m_vtable + 0x34))
                      (gObject,(int)gObject->m_animSlotSel,
                       *(undefined2 *)((int)&pCVar20[5].refCount + 2));
          }
          pCVar20 = (CRef *)&pCVar20->refCount;
        }
      }
      gObject->m_turnSpeed = (float)dVar23;
    }
    if ((gObject->m_currentAnimSlot != -1) &&
       ((*(byte *)((int)&gObject->m_weaponNodeFlags + 1) & 1) == 0)) {
      pCVar9 = gObject->m_charaModelHandle;
      bVar22 = false;
      if ((pCVar9 != (CCharaPcsCHandle *)0x0) && (pCVar9->m_model != (CModel *)0x0)) {
        bVar22 = true;
      }
      if ((bVar22) && (gObject->m_currentAnimSlot != -1)) {
        pCVar10 = pCVar9->m_model;
        if (pCVar10->m_anim == (CAnim *)0x0) {
          bVar22 = true;
        }
        else {
          fVar3 = FLOAT_80330338 + (pCVar10->m_animEnd - pCVar10->m_animStart);
          if (FLOAT_80330338 == fVar3) {
            bVar22 = true;
          }
          else if (FLOAT_80330350 <= *(float *)gObject->m_lastBgAttr) {
            bVar22 = fVar3 - FLOAT_80330338 < pCVar10->m_time;
          }
          else {
            bVar22 = pCVar10->m_time <= FLOAT_80330350;
          }
        }
      }
      else {
        bVar22 = true;
      }
      if (bVar22) {
        if ((int)((uint)*(byte *)&gObject->m_shieldNodeFlags << 0x18) < 0) {
          uVar2 = gObject->m_animQueuePos;
          gObject->m_animQueuePos = uVar2 + '\x01';
          fVar3 = FLOAT_80330350;
          if (gObject->m_animQueue[(char)uVar2] == -1) {
            gObject->m_currentAnimSlot = -1;
            fVar3 = FLOAT_80330350;
            *(byte *)&gObject->m_shieldNodeFlags = *(byte *)&gObject->m_shieldNodeFlags & 0xbf;
            gObject->m_turnSpeed = fVar3;
            gObject->m_rotTargetY = gObject->m_rotBaseY;
            *(byte *)&gObject->m_shieldNodeFlags = *(byte *)&gObject->m_shieldNodeFlags & 0xf7;
            *(byte *)&gObject->m_shieldNodeFlags = *(byte *)&gObject->m_shieldNodeFlags & 0x7f;
            SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack
                      (&CFlat,gObject,2,10,0,0,(CStack *)0x0);
          }
          else {
            gObject->m_currentAnimSlot =
                 gObject->m_animQueue[gObject->m_animQueue[(char)uVar2] + -0x41];
            *(byte *)((int)&gObject->m_weaponNodeFlags + 1) =
                 *(byte *)((int)&gObject->m_weaponNodeFlags + 1) & 0xfe;
            gObject->m_animExtraIndex = -1;
            gObject->m_collisionPushTimer = -1;
            *(byte *)&gObject->m_shieldNodeFlags = *(byte *)&gObject->m_shieldNodeFlags & 0xfd;
            *(byte *)&gObject->m_shieldNodeFlags = *(byte *)&gObject->m_shieldNodeFlags & 0x7f;
            *(byte *)&gObject->m_shieldNodeFlags = *(byte *)&gObject->m_shieldNodeFlags & 0xf7 | 8;
            gObject->m_turnSpeed = fVar3;
          }
        }
        else {
          gObject->m_currentAnimSlot = -1;
          fVar3 = FLOAT_80330350;
          *(byte *)&gObject->m_shieldNodeFlags = *(byte *)&gObject->m_shieldNodeFlags & 0xbf;
          gObject->m_turnSpeed = fVar3;
          gObject->m_rotTargetY = gObject->m_rotBaseY;
          *(byte *)&gObject->m_shieldNodeFlags = *(byte *)&gObject->m_shieldNodeFlags & 0xf7;
          *(byte *)&gObject->m_shieldNodeFlags = *(byte *)&gObject->m_shieldNodeFlags & 0x7f;
          SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack
                    (&CFlat,gObject,2,10,0,0,(CStack *)0x0);
        }
      }
    }
    bVar22 = false;
    if ((gObject->m_weaponModelHandle != (CCharaPcsCHandle *)0x0) &&
       (gObject->m_weaponModelHandle->m_model != (CModel *)0x0)) {
      bVar22 = true;
    }
    if (((bVar22) && ((gObject->m_displayFlags & 1) != 0)) && (-1 < gObject->m_weaponAttachNode)) {
      PSMTXCopy(&gObject->m_charaModelHandle->m_model->m_nodes[gObject->m_weaponAttachNode].m_mtx,
                &MStack_bc);
      PSMTXTransApply((gObject->m_worldPosition).x,(gObject->m_worldPosition).y,
                      (gObject->m_worldPosition).z,&MStack_bc,&MStack_ec);
      SetMatrix__Q26CChara6CModelFPA4_f(gObject->m_weaponModelHandle->m_model,&MStack_ec);
      CalcMatrix__Q26CChara6CModelFv(gObject->m_weaponModelHandle->m_model);
      if ((int)((uint)*(byte *)&gObject->m_weaponNodeFlags << 0x1a |
               (uint)(*(byte *)&gObject->m_weaponNodeFlags >> 6)) < 0) {
        CalcSkin__Q26CChara6CModelFv(gObject->m_weaponModelHandle->m_model);
      }
      gObject->m_weaponModelHandle->m_model->m_lightAlpha = gObject->m_lookAtTimer;
      pCVar10 = gObject->m_weaponModelHandle->m_model;
      pCVar10->m_flagsA0 =
           (byte)(((int)((uint)*(byte *)&gObject->m_weaponNodeFlags << 0x1a |
                        (uint)(*(byte *)&gObject->m_weaponNodeFlags >> 6)) >> 0x1f) << 5) & 0x20 |
           pCVar10->m_flagsA0 & 0xdf;
      pCVar10 = gObject->m_weaponModelHandle->m_model;
      pCVar10->m_flagsA0 =
           (byte)((int)(char)((byte)(gObject->m_displayFlags >> 5) & 1) << 7) |
           pCVar10->m_flagsA0 & 0x7f;
    }
    bVar22 = false;
    if ((gObject->m_shieldModelHandle != (CCharaPcsCHandle *)0x0) &&
       (gObject->m_shieldModelHandle->m_model != (CModel *)0x0)) {
      bVar22 = true;
    }
    if (((bVar22) && ((gObject->m_displayFlags & 1) != 0)) &&
       (-1 < gObject->m_shieldAttachNodeIndex)) {
      PSMTXCopy(&gObject->m_charaModelHandle->m_model->m_nodes[gObject->m_shieldAttachNodeIndex].
                 m_mtx,&MStack_bc);
      PSMTXTransApply((gObject->m_worldPosition).x,(gObject->m_worldPosition).y,
                      (gObject->m_worldPosition).z,&MStack_bc,&MStack_ec);
      SetMatrix__Q26CChara6CModelFPA4_f(gObject->m_shieldModelHandle->m_model,&MStack_ec);
      CalcMatrix__Q26CChara6CModelFv(gObject->m_shieldModelHandle->m_model);
      gObject->m_shieldModelHandle->m_model->m_lightAlpha = gObject->m_lookAtTimer;
      pCVar10 = gObject->m_shieldModelHandle->m_model;
      pCVar10->m_flagsA0 =
           (byte)(((int)((uint)*(byte *)&gObject->m_weaponNodeFlags << 0x1a |
                        (uint)(*(byte *)&gObject->m_weaponNodeFlags >> 6)) >> 0x1f) << 5) & 0x20 |
           pCVar10->m_flagsA0 & 0xdf;
      pCVar10 = gObject->m_shieldModelHandle->m_model;
      pCVar10->m_flagsA0 =
           (byte)((int)(char)((byte)(gObject->m_displayFlags >> 5) & 1) << 7) |
           pCVar10->m_flagsA0 & 0x7f;
      if ((int)((uint)*(byte *)&gObject->m_weaponNodeFlags << 0x1a |
               (uint)(*(byte *)&gObject->m_weaponNodeFlags >> 6)) < 0) {
        CalcSkin__Q26CChara6CModelFv(gObject->m_shieldModelHandle->m_model);
      }
    }
  }
  dVar24 = DOUBLE_80330400;
  (gObject->m_groundHitOffset).x = (gObject->m_groundHitOffset).x * (gObject->m_moveOffset).x;
  (gObject->m_groundHitOffset).y = (gObject->m_groundHitOffset).y * (gObject->m_moveOffset).y;
  (gObject->m_groundHitOffset).z = (gObject->m_groundHitOffset).z * (gObject->m_moveOffset).z;
  if (ABS((double)(gObject->m_groundHitOffset).x) < dVar24) {
    (gObject->m_groundHitOffset).x = FLOAT_80330350;
  }
  if (ABS((double)(gObject->m_groundHitOffset).y) < DOUBLE_80330400) {
    (gObject->m_groundHitOffset).y = FLOAT_80330350;
  }
  if (ABS((double)(gObject->m_groundHitOffset).z) < DOUBLE_80330400) {
    (gObject->m_groundHitOffset).z = FLOAT_80330350;
  }
  if ((int)((uint)gObject->m_stateFlags0 << 0x18) < 0) {
    (gObject->m_groundHitOffset).x = (gObject->m_groundHitOffset).x * gObject->m_bounceFactor;
    (gObject->m_groundHitOffset).z = (gObject->m_groundHitOffset).z * gObject->m_bounceFactor;
  }
  pCVar9 = gObject->m_charaModelHandle;
  bVar22 = false;
  if ((pCVar9 != (CCharaPcsCHandle *)0x0) && (pCVar9->m_model != (CModel *)0x0)) {
    bVar22 = true;
  }
  if (((bVar22) &&
      ((int)((uint)(byte)CFlat._4836_1_ << 0x1e | (uint)((byte)CFlat._4836_1_ >> 2)) < 0)) &&
     (bVar1 = pCVar9->m_model->m_flagsA0, (int)((uint)bVar1 << 0x19 | (uint)(bVar1 >> 7)) < 0)) {
    MogFurFrame__Q26CChara6CModelFP8CGObject(pCVar9->m_model,gObject);
  }
  return;
}

